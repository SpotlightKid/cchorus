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
        Delay,
        Mod_Amount,
        LPF_Cutoff,
        HPF_Cutoff,
        Waveform,
        Freq_L,
        Freq_R_Ratio,
        L_R_Phase_Offset,
        Dry,
        Wet,
        BypassProcess,
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
        return d_version(0, 1, 0);
    }

    int64_t getUniqueId() const noexcept override {
        return d_cconst('c', 'c', 'h', 'r');
    }

    // -------------------------------------------------------------------
    // Init

    void initParameter(uint32_t index, Parameter& parameter) override;
    void initProgramName(uint32_t index, String& programName) override;

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
    {
        "Default",
        {
            3.5f,    // Delay
            0.35f,   // Mod_Amount
            6000.0f, // LPF_Cutoff
            100.0f,  // HPF_Cutoff
            1.0f,    // Waveform
            0.8f,    // Freq_L
            1.0f,    // Freq_R_Ratio
            90.0f,   // L_R_Phase_Offset
            -3.5f,   // Dry
            -3.5f,   // Wet
            0.0,     // BypassProcess
        }
    }
    //,{
    //    "Another preset",  // preset name
    //    {-14.0f, ...}      // array of PluginCChorus::paramCount float param values
    //}
};

const uint presetCount = sizeof(factoryPresets) / sizeof(Preset);

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif  // #ifndef PLUGIN_CCHORUS_H
