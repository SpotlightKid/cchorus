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

#ifndef PLUGIN_CCHORUS_H
#define PLUGIN_CCHORUS_H

#include "DistrhoPlugin.hpp"
#include "CChorus.hpp"

START_NAMESPACE_DISTRHO

#ifndef MIN
#define MIN(a,b) ( (a) < (b) ? (a) : (b) )
#endif

#ifndef MAX
#define MAX(a,b) ( (a) > (b) ? (a) : (b) )
#endif

#ifndef CLAMP
#define CLAMP(v, min, max) (MIN((max), MAX((min), (v))))
#endif

// -----------------------------------------------------------------------

class PluginCChorus : public Plugin {
public:
    enum Parameters {
        p_delay,
        p_mod_amount,
        p_lpf_cutoff,
        p_eq_freq,
        p_eq_gain,
        p_eq_q,
        p_waveform,
        p_freq_l,
        p_freq_r_ratio,
        p_phase_offset,
        p_dry,
        p_wet,
        bypass_process,
        paramCount
    };

    PluginCChorus();

    ~PluginCChorus();

protected:
    // -------------------------------------------------------------------
    // Information

    const char* getLabel() const noexcept override {
        return "CChorus";
    }

    const char* getDescription() const override {
        return "A versatile stereo chorus effect";
    }

    const char* getMaker() const noexcept override {
        return "chrisarndt.de";
    }

    const char* getHomePage() const override {
        return DISTRHO_PLUGIN_URI;
    }

    const char* getLicense() const noexcept override {
        return "https://spdx.org/licenses/MIT";
    }

    uint32_t getVersion() const noexcept override {
        return d_version(2, 2, 0);
    }

    int64_t getUniqueId() const noexcept override {
        return d_cconst('c', 'c', 'h', 'r');
    }

    // -------------------------------------------------------------------
    // Init

    void initParameter(uint32_t index, Parameter& parameter) override;
    void initProgramName(uint32_t index, String& programName) override;
    void initPortGroup(uint32_t groupId, PortGroup& portGroup) override;

    // -------------------------------------------------------------------
    // Internal data

    float getParameterValue(uint32_t index) const override;
    void setParameterValue(uint32_t index, float value) override;
    void loadProgram(uint32_t index) override;

    // -------------------------------------------------------------------
    // Optional

    // Optional callback to inform the plugin about a sample rate change.
    void sampleRateChanged(double newSampleRate) override;

    // -------------------------------------------------------------------
    // Process

    void activate() override;
    void run(const float**, float** outputs, uint32_t frames) override;

    // -------------------------------------------------------------------

private:
    // pointer to dsp class
    CChorus* dsp;
    // sample rate
    double sample_rate;
    bool sr_changed;
    // enable/bypass ramping
    bool needs_ramp_down;
    bool needs_ramp_up;
    float ramp_down;
    float ramp_up;
    float ramp_up_step;
    float ramp_down_step;
    bool state_bypass;
    bool old_bypass;
    float param_bypass;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginCChorus)
};

struct Preset {
    const char* name;
    float params[PluginCChorus::paramCount];
};

const Preset factoryPresets[] = {
    //{
    //    "Preset name",  // preset name
    //    {0.0, ...}      // array of PluginCChorus::paramCount float param values
    //},
    {
        "[F] Default",
        {
            3.5,    // p_delay
            0.35,   // p_mod_amount
            10000.0,// p_lpf_cutoff
            750.0,  // p_eq_freq
            0.0,    // p_eq_gain
            0.7,    // p_eq_q
            1.0,    // p_waveform
            0.8,    // p_freq_l
            1.0,    // p_freq_r_ratio
            90.0,   // p_phase_offset
            -3.5,   // p_dry
            -3.5,   // p_wet
            0.0     // bypass_process
        }
    },
    { "[F] Picked Clean", {3.5, 0.3, 4000.0, 80.0, -6.0, 1.0, 1.0, 1.4, 1.0, 90.0, -3.5, -3.5, 0.0}},
    { "[F] Double Play", {1.2, 0.4, 10000.0, 3200.0, 3.5, 0.7, 1.0, 1.5, 1.0, 60.0, -1.0, -2.5, 0.0}},
    { "[F] Air Supply", {2.95, 0.45, 700.0, 150.0, -4.5, 1.0, 0.0, 2.3, 0.5, 110.0, -2.0, -4.0, 0.0}},
    { "[F] Open Mic Night", {19.0, 0.02, 4000.0, 260.0, -5.0, 0.55, 0.0, 2.4, 1.5, 0.0, -3.0, -3.0, 0.0}},
    { "[F] Rotary Club", {22.5, 0.02, 4500.0, 1500.0, 6.4, 0.7, 0.0, 4.8, 1.5, 89.0, -3.0, -5.0, 0.0}},
    { "[F] Hairy Eighty-Six", {3.2, 0.4, 3800.0, 915.0, 3.0, 1.0, 1.0, 0.8, 2.0, 50.0, -1.5, -1.5, 0.0}},
};

const uint presetCount = sizeof(factoryPresets) / sizeof(Preset);

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif  // #ifndef PLUGIN_CCHORUS_H
