/*
 * CChorus audio effect based on DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier: MIT
 *
 * Copyright (C) 2022 Christopher Arndt <dev@chrisarndt.de>
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

#include "PluginCChorus.hpp"
#include <string.h>

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

PluginCChorus::PluginCChorus()
    : Plugin(CChorus::NumParameters, presetCount, 0)  // # of params, # of programs, 0 states
{
    dsp = new CChorus;
    fSampleRate = getSampleRate();

    for (unsigned p = 0; p < CChorus::NumParameters; ++p) {
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
    if (index >= CChorus::NumParameters)
        return;

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
}

/**
  Set the name of the program @a index.
  This function will be called once, shortly after the plugin is created.
*/
void PluginCChorus::initProgramName(uint32_t index, String& programName) {
    if (index < presetCount) {
        if (index =
        programName = factoryPresets[index].name;
    }
}

// -----------------------------------------------------------------------
// Internal data

/**
  Optional callback to inform the plugin about a sample rate change.
*/
void PluginCChorus::sampleRateChanged(double newSampleRate) {
    fSampleRate = newSampleRate;
    dsp->init(newSampleRate);
}

/**
  Get the current value of a parameter.
*/
float PluginCChorus::getParameterValue(uint32_t index) const {
    return dsp->get_parameter(index);
}

/**
  Change a parameter value.
*/
void PluginCChorus::setParameterValue(uint32_t index, float value) {
    if (index >= CChorus::NumParameters)
        return;

    const CChorus::ParameterRange* range = dsp->parameter_range(index);
    dsp->set_parameter(index, CLAMP(value, range->min, range->max));
}

/**
  Load a program.
  The host may call this function from any context,
  including realtime processing.
*/
void PluginCChorus::loadProgram(uint32_t index) {
    if (index < presetCount) {
        for (int i=0; i < CChorus::NumParameters; i++) {
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
    fSampleRate = getSampleRate();
    dsp->init(fSampleRate);
}


void PluginCChorus::run(const float** inputs, float** outputs,
                        uint32_t frames) {
    if (frames<1) return;

    // do inplace processing by default
    if (outputs[0] != inputs[0]) {
        memcpy(output[0], input[0], frames * sizeof(float));
        memcpy(output[1], input[1], frames * sizeof(float));
    }

    float buf0[frames];

    // check if bypass is pressed
    if (bypass_ != static_cast<uint32_t>(*(bypass))) {
        bypass_ = static_cast<uint32_t>(*(bypass));

        if (!bypass_) {
            needs_ramp_down = true;
            needs_ramp_up = false;
        } else {
            needs_ramp_down = false;
            needs_ramp_up = true;
            bypassed = false;
        }
    }

    if (needs_ramp_down || needs_ramp_up) {
        memcpy(buf0, input0, frames * sizeof(float));
    }

    if (!bypassed) {
        dsp->process(inputs[0], inputs[1], outputs[0], outputs[1], (unsigned)frames);
        //dsp->compute(frames, output0, output0);
    }

    // check if ramping is needed
    if (needs_ramp_down) {
        float fade = 0;
        for (uint32_t i=0; i<frames; i++) {
            if (ramp_down >= 0.0) {
                --ramp_down;
            }
            fade = max(0.0f,ramp_down) /ramp_down_step ;
            output0[i] = output0[i] * fade + buf0[i] * (1.0 - fade);
        }
        if (ramp_down <= 0.0) {
            // when ramped down, clear buffer from dsp
            dsp->clear_state_f();
            needs_ramp_down = false;
            bypassed = true;
            ramp_down = ramp_down_step;
            ramp_up = 0.0;
        } else {
            ramp_up = ramp_down;
        }
    } else if (needs_ramp_up) {
        bypassed = false;
        float fade = 0;

        for (uint32_t i=0; i<frames; i++) {
            if (ramp_up < ramp_up_step) {
                ++ramp_up ;
            }
            fade = min(ramp_up_step,ramp_up) / ramp_up_step;
            output0[i] = output0[i] * fade + buf0[i] * (1.0 - fade);
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
