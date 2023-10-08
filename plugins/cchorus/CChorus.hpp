
//------------------------------------------------------------------------------
// This file was generated using the Faust compiler (https://faust.grame.fr),
// and the Faust post-processor (https://github.com/jpcima/faustpp).
//
// Source: cchorus.dsp
// Name: CChorus
// Author: Christopher Arndt
// Copyright:
// License: MIT License
// Version: 0.5
//------------------------------------------------------------------------------






#pragma once
#ifndef CChorus_Faust_pp_Gen_HPP_
#define CChorus_Faust_pp_Gen_HPP_

#include <memory>

class CChorus {
public:
    CChorus();
    ~CChorus();

    void init(float sample_rate);
    void clear() noexcept;

    void process(
        const float *in0,const float *in1,
        float *out0,float *out1,
        unsigned count) noexcept;

    enum { NumInputs = 2 };
    enum { NumOutputs = 2 };
    enum { NumActives = 11 };
    enum { NumPassives = 0 };
    enum { NumParameters = 11 };

    enum Parameter {
        p_Delay,
        p_Mod_Amount,
        p_LPF_Cutoff,
        p_HPF_Cutoff,
        p_Waveform,
        p_Freq_L,
        p_Freq_R_Ratio,
        p_L_R_Phase_Offset,
        p_Dry,
        p_Wet,
        p_Bypass,
    };

    struct ParameterRange {
        float init;
        float min;
        float max;
    };

    static const char *parameter_label(unsigned index) noexcept;
    static const char *parameter_short_label(unsigned index) noexcept;
    static const char *parameter_symbol(unsigned index) noexcept;
    static const char *parameter_unit(unsigned index) noexcept;
    static const ParameterRange *parameter_range(unsigned index) noexcept;
    static bool parameter_is_trigger(unsigned index) noexcept;
    static bool parameter_is_boolean(unsigned index) noexcept;
    static bool parameter_is_integer(unsigned index) noexcept;
    static bool parameter_is_logarithmic(unsigned index) noexcept;

    float get_parameter(unsigned index) const noexcept;
    void set_parameter(unsigned index, float value) noexcept;


    float get_Delay() const noexcept;

    float get_Mod_Amount() const noexcept;

    float get_LPF_Cutoff() const noexcept;

    float get_HPF_Cutoff() const noexcept;

    float get_Waveform() const noexcept;

    float get_Freq_L() const noexcept;

    float get_Freq_R_Ratio() const noexcept;

    float get_L_R_Phase_Offset() const noexcept;

    float get_Dry() const noexcept;

    float get_Wet() const noexcept;

    float get_Bypass() const noexcept;


    void set_Delay(float value) noexcept;

    void set_Mod_Amount(float value) noexcept;

    void set_LPF_Cutoff(float value) noexcept;

    void set_HPF_Cutoff(float value) noexcept;

    void set_Waveform(float value) noexcept;

    void set_Freq_L(float value) noexcept;

    void set_Freq_R_Ratio(float value) noexcept;

    void set_L_R_Phase_Offset(float value) noexcept;

    void set_Dry(float value) noexcept;

    void set_Wet(float value) noexcept;

    void set_Bypass(float value) noexcept;


public:
    class BasicDsp;

private:
    std::unique_ptr<BasicDsp> fDsp;



};




#endif // CChorus_Faust_pp_Gen_HPP_
