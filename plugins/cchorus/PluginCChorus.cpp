/*
 * CChorus audio effect based on DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier: MIT
 *
 * Copyright (C) 2022-2024 Christopher Arndt <dev@chrisarndt.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <string.h>
#include "PluginCChorus.hpp"
#include "DistrhoUtils.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

PluginCChorus::PluginCChorus()
    : Plugin(paramCount, presetCount, 0),  // # of params, # of programs, 0 states
      sr_changed(false),
      needs_ramp_down(false),
      needs_ramp_up(false),
      state_bypass(false),
      old_bypass(1)
{
    dsp = new CChorus;
    sample_rate = getSampleRate();

    for (unsigned p = 0; p < paramCount; ++p) {
        Parameter param;
        initParameter(p, param);
        setParameterValue(p, param.ranges.def);
    }
}

PluginCChorus::~PluginCChorus() {
    delete dsp;
}

// -----------------------------------------------------------------------
// Init

void PluginCChorus::initParameter(uint32_t index, Parameter& parameter) {
    if (index >= paramCount)
        return;

    if (index == bypass_process) {
        parameter.name = "Bypass";
        parameter.shortName = "Bypass";
        parameter.symbol = "bypass";
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 1.0f;
        parameter.ranges.def = 0.0f;
        parameter.designation = kParameterDesignationBypass;
        parameter.hints = kParameterIsAutomatable|kParameterIsBoolean|kParameterIsInteger;
    }
    else {
        const CChorus::ParameterRange* range = dsp->parameter_range(index);
        parameter.name = dsp->parameter_label(index);
        parameter.shortName = dsp->parameter_short_label(index);
        parameter.symbol = dsp->parameter_symbol(index);
        parameter.unit = dsp->parameter_unit(index);
        parameter.ranges.min = range->min;
        parameter.ranges.max = range->max;
        parameter.ranges.def = range->init;
        parameter.hints = kParameterIsAutomatable;

        if (dsp->parameter_is_boolean(index))
            parameter.hints |= kParameterIsBoolean;
        if (dsp->parameter_is_integer(index))
            parameter.hints |= kParameterIsInteger;
        if (dsp->parameter_is_logarithmic(index))
            parameter.hints |= kParameterIsLogarithmic;
        if (dsp->parameter_is_trigger(index))
            parameter.hints |= kParameterIsTrigger;

        int group_id = dsp->parameter_group(index);
        if (group_id != -1) {
            parameter.groupId = group_id;
        }

        unsigned sp_count = dsp->parameter_scale_point_count(index);

        if (sp_count > 0) {
            parameter.enumValues.count = sp_count;

            const char *style = dsp->parameter_style(index);
            if (strcmp(style, "menu") || strcmp(style, "radio")) {
                parameter.enumValues.restrictedMode = true;
            }

            {
                ParameterEnumerationValue* const values = new ParameterEnumerationValue[sp_count];
                parameter.enumValues.values = values;
                for (unsigned point=0; point<sp_count; point++) {
                    const CChorus::ParameterScalePoint* sp = dsp->parameter_scale_point(index, point);
                    values[point].label = sp->label.c_str();
                    values[point].value = sp->value;
                }
            }
        }
    }
}

/**
   Initialize the port group @a groupId.@n
   This function will be called once,
   shortly after the plugin is created and all audio ports and parameters have been enumerated.
 */
void PluginCChorus::initPortGroup(uint32_t groupId, PortGroup& portGroup) {
    portGroup.name = dsp->parameter_group_label(groupId);
    portGroup.symbol = dsp->parameter_group_symbol(groupId);
}

/**
  Set the name of the program @a index.
  This function will be called once, shortly after the plugin is created.
*/
void PluginCChorus::initProgramName(uint32_t index, String& programName) {
    if (index < presetCount) {
        programName = factoryPresets[index].name;
    }
}

// -----------------------------------------------------------------------
// Internal data

/**
  Optional callback to inform the plugin about a sample rate change.
*/
void PluginCChorus::sampleRateChanged(double newSampleRate) {
    (void)newSampleRate;
    sr_changed = true;
    activate();
    sr_changed = false;
}

/**
  Get the current value of a parameter.
*/
float PluginCChorus::getParameterValue(uint32_t index) const {
    if (index == bypass_process) {
        return param_bypass ? 1.0 : 0.0;
    }
    else {
        return dsp->get_parameter(index);
    }
}

/**
  Change a parameter value.
*/
void PluginCChorus::setParameterValue(uint32_t index, float value) {
    if (index >= paramCount)
        return;

    if (index == bypass_process) {
        param_bypass = value > 0.0f ? 1.0 : 0.0;
    }
    else {
        const CChorus::ParameterRange* range = dsp->parameter_range(index);
        dsp->set_parameter(index, CLAMP(value, range->min, range->max));
    }
}

/**
  Load a program.
  The host may call this function from any context,
  including realtime processing.
*/
void PluginCChorus::loadProgram(uint32_t index) {
    if (index < presetCount) {
        for (int i=0; i < paramCount; i++) {
            setParameterValue(i, factoryPresets[index].params[i]);
        }
    }
}

// -----------------------------------------------------------------------
// Process

/**
  Plugin is activated.
*/
void PluginCChorus::activate() {
    sample_rate = getSampleRate();
    dsp->init(sample_rate);
    ramp_down_step = 32 * (256 * sample_rate) / 48000;
    ramp_up_step = ramp_down_step;
    ramp_down = ramp_down_step;
    ramp_up = 0.0;
}


void PluginCChorus::run(const float** inputs, float** outputs, uint32_t frames) {
    if (sr_changed || frames < 1)
        return;

    // get the left and right audio inputs
    const float* const inpL = inputs[0];
    const float* const inpR = inputs[1];

    // get the left and right audio outputs
    float* const outL = outputs[0];
    float* const outR = outputs[1];

    float bufL[frames], bufR[frames];

    // check if bypass was toggled
    if (old_bypass != param_bypass) {
        if ((old_bypass = param_bypass)) {
            needs_ramp_down = true;
            needs_ramp_up = false;
        } else {
            needs_ramp_down = false;
            needs_ramp_up = true;
            state_bypass = false;
        }
    }

    if (needs_ramp_down || needs_ramp_up) {
        memcpy(bufL, inpL, frames * sizeof(float));
        memcpy(bufR, inpR, frames * sizeof(float));
    }

    if (!state_bypass) {
        dsp->process(inpL, inpR, outL, outR, (unsigned)frames);
    }
    else if (outL != inpL && outR != inpR) {
        memcpy(outL, inpL, frames * sizeof(float));
        memcpy(outR, inpR, frames * sizeof(float));
    }

    // check if ramping is needed
    if (needs_ramp_down) {
        float fade = 0;
        for (uint32_t i=0; i<frames; i++) {
            if (ramp_down >= 0.0) {
                --ramp_down;
            }
            fade = MAX(0.0f, ramp_down) / ramp_down_step ;
            outL[i] = outL[i] * fade + bufL[i] * (1.0 - fade);
            outR[i] = outR[i] * fade + bufR[i] * (1.0 - fade);
        }
        if (ramp_down <= 0.0) {
            // when ramped down, clear buffer from dsp
            dsp->clear();
            needs_ramp_down = false;
            state_bypass = true;
            ramp_down = ramp_down_step;
            ramp_up = 0.0;
        } else {
            ramp_up = ramp_down;
        }
    } else if (needs_ramp_up) {
        state_bypass = false;
        float fade = 0;

        for (uint32_t i=0; i<frames; i++) {
            if (ramp_up < ramp_up_step) {
                ++ramp_up ;
            }
            fade = MIN(ramp_up_step, ramp_up) / ramp_up_step;
            outL[i] = outL[i] * fade + bufL[i] * (1.0 - fade);
            outR[i] = outR[i] * fade + bufR[i] * (1.0 - fade);
        }

        if (ramp_up >= ramp_up_step) {
            needs_ramp_up = false;
            ramp_up = 0.0;
            ramp_down = ramp_down_step;
        }
        else {
            ramp_down = ramp_up;
        }
    }
}

// -----------------------------------------------------------------------

Plugin* createPlugin() {
    return new PluginCChorus();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
