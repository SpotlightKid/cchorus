
//------------------------------------------------------------------------------
// This file was generated using the Faust compiler (https://faust.grame.fr),
// and the Faust post-processor (https://github.com/jpcima/faustpp).
//
// Source: cchorus.dsp
// Name: CChorus
// Author: Christopher Arndt
// Copyright: 
// License: MIT License
// Version: 0.6
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
    enum { NumActives = 10 };
    enum { NumPassives = 0 };
    enum { NumParameters = 10 };

    enum Parameter {
        p_delay,
        p_mod_amount,
        p_lpf_cutoff,
        p_hpf_cutoff,
        p_waveform,
        p_freq_l,
        p_freq_r_ratio,
        p_phase_offset,
        p_dryy,
        p_wet,
        
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

    
    float get_delay() const noexcept;
    
    float get_mod_amount() const noexcept;
    
    float get_lpf_cutoff() const noexcept;
    
    float get_hpf_cutoff() const noexcept;
    
    float get_waveform() const noexcept;
    
    float get_freq_l() const noexcept;
    
    float get_freq_r_ratio() const noexcept;
    
    float get_phase_offset() const noexcept;
    
    float get_dryy() const noexcept;
    
    float get_wet() const noexcept;
    
    
    void set_delay(float value) noexcept;
    
    void set_mod_amount(float value) noexcept;
    
    void set_lpf_cutoff(float value) noexcept;
    
    void set_hpf_cutoff(float value) noexcept;
    
    void set_waveform(float value) noexcept;
    
    void set_freq_l(float value) noexcept;
    
    void set_freq_r_ratio(float value) noexcept;
    
    void set_phase_offset(float value) noexcept;
    
    void set_dryy(float value) noexcept;
    
    void set_wet(float value) noexcept;
    

public:
    class BasicDsp;

private:
    std::unique_ptr<BasicDsp> fDsp;



};




#endif // CChorus_Faust_pp_Gen_HPP_