declare name "CChorus";
declare version "0.6";
declare author "Christopher Arndt";
declare license "MIT License";
declare description "A versatile stereo chorus effect";

import("stdfaust.lib");

PI = ma.PI;
TWOPI = 2.0 * ma.PI;
MAX_DELAY_MS = 30.0;

// Parameters

// Input Section

inp_group(x) = hgroup("Input", x);

peak_freq = inp_group(hslider("[1] Pre-EQ Freqency [abbrev:EQ Freq] [symbol:eq_freq] [unit:Hz] [scale:log] [style:knob]", 750, 20, 4000, 0.1)): si.smoo;
peak_gain = inp_group(hslider("[2] Pre-EQ Gain [abbrev:EQ Gain] [symbol:eq_gain] [unit:db] [style:knob]", 0, -12, 12, 0.1)): si.smoo;
peak_q = inp_group(hslider("[3] Pre-EQ Q [abbrev:EQ Q] [symbol:eq_q] [style:knob]", 0.7, 0.1, 16.0, 0.1)): si.smoo;

// Delay section

del_group(x) = hgroup("Delay", x);
delay_ms = del_group(hslider("[1] Delay Length [abbrev:Delay] [symbol:delay] [unit:ms]", 3.5, 0, MAX_DELAY_MS, 0.001) : si.smoo);
delay_mod = del_group(hslider("[2] Modulation Amount [abbrev:Mod. Amount] [symbol:mod_amount] [style:knob]", 0.35, 0.001, 1, 0.001) : si.smoo);

lpf_cutoff = del_group(hslider("[3] Post-Delay LPF Cutoff [abbrev:LPF] [symbol:lpf_cutoff] [unit:Hz] [scale:log] [style:knob]", 10000, 20, 10000, 0.1)): si.smoo;

// LFO section

lfo_group(x) = hgroup("LFO", x);
lfo_switch = lfo_group(hslider("[1] LFO Waveform [abbrev:Waveform] [symbol:waveform] [style:radio{'Sine':0;'Triangle':1}]", 1, 0, 1, 1));
lfo_freq_l = lfo_group(hslider("[2] LFO L Frequency [abbrev:Freq L] [symbol:freq_l] [unit:Hz] [style:knob]", 0.8, 0.01, 10, 0.01));
lfo_freq_r = lfo_group(hslider("[3] LFO R Frequency Ratio [abbrev:F. Ratio] [symbol:freq_r_ratio] [style:knob]", 1.0, 0.01, 2, 0.01)) * lfo_freq_l;
lfo_phase_r = lfo_group(hslider("[4] LFO L/R Phase Offset [abbrev:Ph. Offset] [symbol:phase_offset] [unit:degree] [style:knob]", 90, -180, 180, 1) / TWOPI : si.smoo);

// Output section

out_group(x) = hgroup("Output", x);
dry = out_group(hslider("[1] Dry Gain [abbrev:Dry] [symbol:dry] [unit:dB] [style:knob]", -3.5, -60, 10, 0.1) : ba.db2linear);
wet = out_group(hslider("[2] Wet Gain [abbrev:Wet] [symbol:wet] [unit:dB] [style:knob]", -3.5, -60, 10, 0.1) : ba.db2linear);

// Modulation LFOs

// Oscillator with run-time controllable phase
// by Dr Dario Sanfilippo
phasor(freq, phase) = ma.frac((loop ~ _) + phase / TWOPI)
with {
    loop(y) = ma.frac(freq / ma.SR + y);
};

tri(ph) = abs(ma.frac(ph - .25) * 4.0 - 2.0) - 1.0;

lfo_l = select2(lfo_switch, sin(phasor(lfo_freq_l, 0) * TWOPI), tri(phasor(lfo_freq_l, 0)));
lfo_r = select2(lfo_switch, sin(phasor(lfo_freq_r, lfo_phase_r) * TWOPI), tri(phasor(lfo_freq_r, lfo_phase_r)));

// L/R delay lines

delay_l = delay_ms + delay_ms * delay_mod * lfo_l;
delay_r = delay_ms + delay_ms * delay_mod * lfo_r;

// Delay filters
lpf = fi.lowpass(2, lpf_cutoff);
peak_eq = fi.peak_eq_cq(peak_gain, peak_freq, peak_q);

// Chorus

chorus_mono(curdel, prefilter, postfilter, dry, wet) =  _ : prefilter <: _ * dry + wet_signal * wet
with {
    dmax = ma.SR * 0.001 * MAX_DELAY_MS * 2;  // Mod Amount = 1 => double max delay time
    wet_signal = de.fdelay(dmax, curdel * 0.001 * ma.SR) : postfilter;
};

// L/R FX chains

chorus_l = chorus_mono(delay_l, peak_eq, lpf, dry, wet);
chorus_r = chorus_mono(delay_r, peak_eq, lpf, dry, wet);

process = chorus_l, chorus_r;
