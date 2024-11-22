//------------------------------------------------------------------------------
// This file was generated using the Faust compiler (https://faust.grame.fr),
// and the Faust post-processor (https://github.com/SpotlightKid/faustdoctor).
//
// Source: cchorus.dsp
// Name: CChorus
// Author: Christopher Arndt
// Copyright: 
// License: MIT License
// Version: 0.6
// FAUST version: 2.76.0
// FAUST compilation options: -a /home/chris/tmp/tmpoc6ozmi5.cpp -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
//------------------------------------------------------------------------------



#pragma once
#ifndef CChorus_Faust_pp_Gen_HPP_
#define CChorus_Faust_pp_Gen_HPP_

#include <memory>
#include <string>

class CChorus {
public:
    CChorus();
    ~CChorus();

    void init(float sample_rate);
    void clear() noexcept;

    void process(
        const float *in0, const float *in1, 
        float *out0, float *out1, 
        unsigned count) noexcept;

    enum { NumInputs = 2 };
    enum { NumOutputs = 2 };
    enum { NumActives = 12 };
    enum { NumPassives = 0 };
    enum { NumParameters = 12 };

    enum Parameter {
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
        
    };

    struct ParameterRange {
        float init;
        float min;
        float max;
    };

    struct ParameterScalePoint {
        std::string label;
        float value;
    };

    int parameter_group(unsigned index) noexcept;
    int parameter_order(unsigned index) noexcept;
    static const char *parameter_group_label(unsigned group_id) noexcept;
    static const char *parameter_group_symbol(unsigned group_id) noexcept;
    static const char *parameter_label(unsigned index) noexcept;
    static const char *parameter_short_label(unsigned index) noexcept;
    static const char *parameter_style(unsigned index) noexcept;
    static const char *parameter_symbol(unsigned index) noexcept;
    static const char *parameter_unit(unsigned index) noexcept;
    static const ParameterRange *parameter_range(unsigned index) noexcept;
    unsigned parameter_scale_point_count(unsigned index) noexcept;
    static const ParameterScalePoint *parameter_scale_point(unsigned index, unsigned point) noexcept;
    static bool parameter_is_trigger(unsigned index) noexcept;
    static bool parameter_is_boolean(unsigned index) noexcept;
    static bool parameter_is_enum(unsigned index) noexcept;
    static bool parameter_is_integer(unsigned index) noexcept;
    static bool parameter_is_logarithmic(unsigned index) noexcept;

    float get_parameter(unsigned index) const noexcept;
    void set_parameter(unsigned index, float value) noexcept;
    float get_delay() const noexcept;
    float get_mod_amount() const noexcept;
    float get_lpf_cutoff() const noexcept;
    float get_eq_freq() const noexcept;
    float get_eq_gain() const noexcept;
    float get_eq_q() const noexcept;
    float get_waveform() const noexcept;
    float get_freq_l() const noexcept;
    float get_freq_r_ratio() const noexcept;
    float get_phase_offset() const noexcept;
    float get_dry() const noexcept;
    float get_wet() const noexcept;
    void set_delay(float value) noexcept;
    void set_mod_amount(float value) noexcept;
    void set_lpf_cutoff(float value) noexcept;
    void set_eq_freq(float value) noexcept;
    void set_eq_gain(float value) noexcept;
    void set_eq_q(float value) noexcept;
    void set_waveform(float value) noexcept;
    void set_freq_l(float value) noexcept;
    void set_freq_r_ratio(float value) noexcept;
    void set_phase_offset(float value) noexcept;
    void set_dry(float value) noexcept;
    void set_wet(float value) noexcept;

public:
    class BasicDsp;

private:
    std::unique_ptr<BasicDsp> fDsp;


};



#endif // CChorus_Faust_pp_Gen_HPP_