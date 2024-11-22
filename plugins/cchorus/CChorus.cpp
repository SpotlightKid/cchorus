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
// FAUST compilation options: -a /home/chris/tmp/tmpvgnhasfj.cpp -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
//------------------------------------------------------------------------------




#include "CChorus.hpp"

#include <utility>
#include <cmath>

class CChorus::BasicDsp {
public:
    virtual ~BasicDsp() {}
};

//------------------------------------------------------------------------------
// Begin the Faust code section

namespace {

template <class T> inline T min(T a, T b) { return (a < b) ? a : b; }
template <class T> inline T max(T a, T b) { return (a > b) ? a : b; }

class Meta {
public:
    // dummy
    void declare(...) {}
};

class UI {
public:
    // dummy
    void openHorizontalBox(...) {}
    void openVerticalBox(...) {}
    void closeBox(...) {}
    void declare(...) {}
    void addButton(...) {}
    void addCheckButton(...) {}
    void addVerticalSlider(...) {}
    void addHorizontalSlider(...) {}
    void addVerticalBargraph(...) {}
    void addHorizontalBargraph(...) {}
};

typedef CChorus::BasicDsp dsp;

} // namespace

#define FAUSTDR_VIRTUAL // do not declare any methods virtual
#define FAUSTDR_PRIVATE public // do not hide any members
#define FAUSTDR_PROTECTED public // do not hide any members

// define the DSP in the anonymous namespace
#define FAUSTDR_BEGIN_NAMESPACE namespace {
#define FAUSTDR_END_NAMESPACE }


#if defined(__GNUC__)
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#ifndef FAUSTDR_PRIVATE
#   define FAUSTDR_PRIVATE private
#endif
#ifndef FAUSTDR_PROTECTED
#   define FAUSTDR_PROTECTED protected
#endif
#ifndef FAUSTDR_VIRTUAL
#   define FAUSTDR_VIRTUAL virtual
#endif

#ifndef FAUSTDR_BEGIN_NAMESPACE
#   define FAUSTDR_BEGIN_NAMESPACE
#endif
#ifndef FAUSTDR_END_NAMESPACE
#   define FAUSTDR_END_NAMESPACE
#endif

FAUSTDR_BEGIN_NAMESPACE

// END PREAMBLE
// START INTRINSICS
// END INTRINSICS
// START CLASS CODE
#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

FAUSTDR_END_NAMESPACE
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>
FAUSTDR_BEGIN_NAMESPACE

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif

static float mydsp_faustpower2_f(float value) {
	return value * value;
}

class mydsp : public dsp {
	
 FAUSTDR_PRIVATE:
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fHslider0;
	float fRec0[2];
	float fConst3;
	FAUSTFLOAT fHslider1;
	float fRec2[2];
	FAUSTFLOAT fHslider2;
	float fRec3[2];
	float fConst4;
	FAUSTFLOAT fHslider3;
	float fRec4[2];
	float fRec5[3];
	int IOTA0;
	float fVec0[16384];
	float fConst5;
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT fHslider5;
	float fConst6;
	float fRec6[2];
	FAUSTFLOAT fHslider6;
	float fRec7[2];
	FAUSTFLOAT fHslider7;
	float fRec8[2];
	float fConst7;
	float fRec1[3];
	FAUSTFLOAT fHslider8;
	FAUSTFLOAT fHslider9;
	float fRec10[3];
	float fVec1[16384];
	FAUSTFLOAT fHslider10;
	float fConst8;
	float fRec11[2];
	FAUSTFLOAT fHslider11;
	float fRec12[2];
	float fRec9[3];
	
 public:
	mydsp() {
	}
	
	void metadata(Meta* m) { 
		m->declare("author", "Christopher Arndt");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/tabulateNd", "Copyright (C) 2023 Bart Brouns <bart@magnetophon.nl>");
		m->declare("basics.lib/version", "1.19.1");
		m->declare("compile_options", "-a /home/chris/tmp/tmpvgnhasfj.cpp -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "1.1.0");
		m->declare("description", "A versatile stereo chorus effect");
		m->declare("filename", "cchorus.dsp");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/peak_eq:author", "Julius O. Smith III");
		m->declare("filters.lib/peak_eq:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/peak_eq:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/peak_eq_cq:author", "Julius O. Smith III");
		m->declare("filters.lib/peak_eq_cq:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/peak_eq_cq:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "1.3.0");
		m->declare("license", "MIT License");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.8.0");
		m->declare("name", "CChorus");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.6.0");
		m->declare("version", "0.6");
	}

	FAUSTDR_VIRTUAL int getNumInputs() {
		return 2;
	}
	FAUSTDR_VIRTUAL int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
	}
	
	FAUSTDR_VIRTUAL void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = 44.1f / fConst0;
		fConst2 = 1.0f - fConst1;
		fConst3 = 3.1415927f / fConst0;
		fConst4 = 6.2831855f / fConst0;
		fConst5 = 0.06f * fConst0 + 1.0f;
		fConst6 = 1.0f / fConst0;
		fConst7 = 0.001f * fConst0;
		fConst8 = 7.018733f / fConst0;
	}
	
	FAUSTDR_VIRTUAL void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(1e+04f);
		fHslider1 = FAUSTFLOAT(7.5e+02f);
		fHslider2 = FAUSTFLOAT(0.0f);
		fHslider3 = FAUSTFLOAT(0.7f);
		fHslider4 = FAUSTFLOAT(1.0f);
		fHslider5 = FAUSTFLOAT(0.8f);
		fHslider6 = FAUSTFLOAT(0.35f);
		fHslider7 = FAUSTFLOAT(3.5f);
		fHslider8 = FAUSTFLOAT(-3.5f);
		fHslider9 = FAUSTFLOAT(-3.5f);
		fHslider10 = FAUSTFLOAT(9e+01f);
		fHslider11 = FAUSTFLOAT(1.0f);
	}
	
	FAUSTDR_VIRTUAL void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec0[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec2[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec3[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec4[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 3; l4 = l4 + 1) {
			fRec5[l4] = 0.0f;
		}
		IOTA0 = 0;
		for (int l5 = 0; l5 < 16384; l5 = l5 + 1) {
			fVec0[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec6[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec7[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec8[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 3; l9 = l9 + 1) {
			fRec1[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 3; l10 = l10 + 1) {
			fRec10[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 16384; l11 = l11 + 1) {
			fVec1[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			fRec11[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fRec12[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 3; l14 = l14 + 1) {
			fRec9[l14] = 0.0f;
		}
	}
	
	FAUSTDR_VIRTUAL void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	
	FAUSTDR_VIRTUAL void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	FAUSTDR_VIRTUAL mydsp* clone() {
		return new mydsp();
	}
	
	FAUSTDR_VIRTUAL int getSampleRate() {
		return fSampleRate;
	}
	
	FAUSTDR_VIRTUAL void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("CChorus");
		ui_interface->openHorizontalBox("Delay");
		ui_interface->declare(&fHslider7, "1", "");
		ui_interface->declare(&fHslider7, "abbrev", "Delay");
		ui_interface->declare(&fHslider7, "symbol", "delay");
		ui_interface->declare(&fHslider7, "unit", "ms");
		ui_interface->addHorizontalSlider("Delay Length", &fHslider7, FAUSTFLOAT(3.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(3e+01f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider6, "2", "");
		ui_interface->declare(&fHslider6, "abbrev", "Mod. Amount");
		ui_interface->declare(&fHslider6, "style", "knob");
		ui_interface->declare(&fHslider6, "symbol", "mod_amount");
		ui_interface->addHorizontalSlider("Modulation Amount", &fHslider6, FAUSTFLOAT(0.35f), FAUSTFLOAT(0.001f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider0, "3", "");
		ui_interface->declare(&fHslider0, "abbrev", "LPF");
		ui_interface->declare(&fHslider0, "scale", "log");
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->declare(&fHslider0, "symbol", "lpf_cutoff");
		ui_interface->declare(&fHslider0, "unit", "Hz");
		ui_interface->addHorizontalSlider("Post-Delay LPF Cutoff", &fHslider0, FAUSTFLOAT(1e+04f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(1e+04f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Input");
		ui_interface->declare(&fHslider1, "1", "");
		ui_interface->declare(&fHslider1, "abbrev", "EQ Freq");
		ui_interface->declare(&fHslider1, "scale", "log");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->declare(&fHslider1, "symbol", "eq_freq");
		ui_interface->declare(&fHslider1, "unit", "Hz");
		ui_interface->addHorizontalSlider("Pre-EQ Freqency", &fHslider1, FAUSTFLOAT(7.5e+02f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(4e+03f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider2, "2", "");
		ui_interface->declare(&fHslider2, "abbrev", "EQ Gain");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->declare(&fHslider2, "symbol", "eq_gain");
		ui_interface->declare(&fHslider2, "unit", "db");
		ui_interface->addHorizontalSlider("Pre-EQ Gain", &fHslider2, FAUSTFLOAT(0.0f), FAUSTFLOAT(-12.0f), FAUSTFLOAT(12.0f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider3, "3", "");
		ui_interface->declare(&fHslider3, "abbrev", "EQ Q");
		ui_interface->declare(&fHslider3, "style", "knob");
		ui_interface->declare(&fHslider3, "symbol", "eq_q");
		ui_interface->addHorizontalSlider("Pre-EQ Q", &fHslider3, FAUSTFLOAT(0.7f), FAUSTFLOAT(0.1f), FAUSTFLOAT(16.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("LFO");
		ui_interface->declare(&fHslider4, "1", "");
		ui_interface->declare(&fHslider4, "abbrev", "Waveform");
		ui_interface->declare(&fHslider4, "style", "radio{'Sine':0;'Triangle':1}");
		ui_interface->declare(&fHslider4, "symbol", "waveform");
		ui_interface->addHorizontalSlider("LFO Waveform", &fHslider4, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider5, "2", "");
		ui_interface->declare(&fHslider5, "abbrev", "Freq L");
		ui_interface->declare(&fHslider5, "style", "knob");
		ui_interface->declare(&fHslider5, "symbol", "freq_l");
		ui_interface->declare(&fHslider5, "unit", "Hz");
		ui_interface->addHorizontalSlider("LFO L Frequency", &fHslider5, FAUSTFLOAT(0.8f), FAUSTFLOAT(0.01f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider11, "3", "");
		ui_interface->declare(&fHslider11, "abbrev", "F. Ratio");
		ui_interface->declare(&fHslider11, "style", "knob");
		ui_interface->declare(&fHslider11, "symbol", "freq_r_ratio");
		ui_interface->addHorizontalSlider("LFO R Frequency Ratio", &fHslider11, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f), FAUSTFLOAT(2.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider10, "4", "");
		ui_interface->declare(&fHslider10, "abbrev", "Ph. Offset");
		ui_interface->declare(&fHslider10, "style", "knob");
		ui_interface->declare(&fHslider10, "symbol", "phase_offset");
		ui_interface->declare(&fHslider10, "unit", "degree");
		ui_interface->addHorizontalSlider("LFO L/R Phase Offset", &fHslider10, FAUSTFLOAT(9e+01f), FAUSTFLOAT(-1.8e+02f), FAUSTFLOAT(1.8e+02f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Output");
		ui_interface->declare(&fHslider9, "1", "");
		ui_interface->declare(&fHslider9, "abbrev", "Dry");
		ui_interface->declare(&fHslider9, "style", "knob");
		ui_interface->declare(&fHslider9, "symbol", "dry");
		ui_interface->declare(&fHslider9, "unit", "dB");
		ui_interface->addHorizontalSlider("Dry Gain", &fHslider9, FAUSTFLOAT(-3.5f), FAUSTFLOAT(-6e+01f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider8, "2", "");
		ui_interface->declare(&fHslider8, "abbrev", "Wet");
		ui_interface->declare(&fHslider8, "style", "knob");
		ui_interface->declare(&fHslider8, "symbol", "wet");
		ui_interface->declare(&fHslider8, "unit", "dB");
		ui_interface->addHorizontalSlider("Wet Gain", &fHslider8, FAUSTFLOAT(-3.5f), FAUSTFLOAT(-6e+01f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	FAUSTDR_VIRTUAL void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = fConst1 * float(fHslider0);
		float fSlow1 = fConst1 * float(fHslider1);
		float fSlow2 = fConst1 * float(fHslider2);
		float fSlow3 = fConst1 * float(fHslider3);
		int iSlow4 = int(float(fHslider4));
		float fSlow5 = float(fHslider5);
		float fSlow6 = fConst6 * fSlow5;
		float fSlow7 = fConst1 * float(fHslider6);
		float fSlow8 = fConst1 * float(fHslider7);
		float fSlow9 = std::pow(1e+01f, 0.05f * float(fHslider8));
		float fSlow10 = std::pow(1e+01f, 0.05f * float(fHslider9));
		float fSlow11 = fConst8 * float(fHslider10);
		float fSlow12 = fConst6 * fSlow5 * float(fHslider11);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec0[0] = fSlow0 + fConst2 * fRec0[1];
			float fTemp0 = std::tan(fConst3 * fRec0[0]);
			float fTemp1 = 1.0f / fTemp0;
			float fTemp2 = (fTemp1 + 1.4142135f) / fTemp0 + 1.0f;
			float fTemp3 = 1.0f - 1.0f / mydsp_faustpower2_f(fTemp0);
			float fTemp4 = (fTemp1 + -1.4142135f) / fTemp0 + 1.0f;
			fRec2[0] = fSlow1 + fConst2 * fRec2[1];
			float fTemp5 = std::tan(fConst3 * fRec2[0]);
			fRec3[0] = fSlow2 + fConst2 * fRec3[1];
			int iTemp6 = fRec3[0] > 0.0f;
			fRec4[0] = fSlow3 + fConst2 * fRec4[1];
			float fTemp7 = fRec4[0] * std::sin(fConst4 * fRec2[0]);
			float fTemp8 = fConst3 * (fRec2[0] * std::pow(1e+01f, 0.05f * std::fabs(fRec3[0])) / fTemp7);
			float fTemp9 = fConst3 * (fRec2[0] / fTemp7);
			float fTemp10 = ((iTemp6) ? fTemp9 : fTemp8);
			float fTemp11 = 1.0f / fTemp5;
			float fTemp12 = (fTemp11 + fTemp10) / fTemp5 + 1.0f;
			float fTemp13 = ((iTemp6) ? fTemp8 : fTemp9);
			float fTemp14 = (fTemp11 - fTemp13) / fTemp5 + 1.0f;
			float fTemp15 = 1.0f - 1.0f / mydsp_faustpower2_f(fTemp5);
			float fTemp16 = 2.0f * fRec5[1] * fTemp15;
			float fTemp17 = (fTemp11 - fTemp10) / fTemp5 + 1.0f;
			fRec5[0] = float(input0[i0]) - (fRec5[2] * fTemp17 + fTemp16) / fTemp12;
			float fTemp18 = (fTemp11 + fTemp13) / fTemp5 + 1.0f;
			float fTemp19 = (fTemp16 + fRec5[0] * fTemp18 + fRec5[2] * fTemp14) / fTemp12;
			fVec0[IOTA0 & 16383] = fTemp19;
			fRec6[0] = fSlow6 + (fRec6[1] - std::floor(fSlow6 + fRec6[1]));
			float fTemp20 = std::floor(fRec6[0]);
			fRec7[0] = fSlow7 + fConst2 * fRec7[1];
			fRec8[0] = fSlow8 + fConst2 * fRec8[1];
			float fTemp21 = fConst7 * fRec8[0] * (fRec7[0] * ((iSlow4) ? std::fabs(4.0f * (fRec6[0] + (-0.25f - (fTemp20 + std::floor(fRec6[0] + (-0.25f - fTemp20))))) + -2.0f) + -1.0f : std::sin(6.2831855f * (fRec6[0] - fTemp20))) + 1.0f);
			int iTemp22 = int(fTemp21);
			float fTemp23 = std::floor(fTemp21);
			fRec1[0] = fVec0[(IOTA0 - int(std::min<float>(fConst5, float(std::max<int>(0, iTemp22))))) & 16383] * (fTemp23 + (1.0f - fTemp21)) + (fTemp21 - fTemp23) * fVec0[(IOTA0 - int(std::min<float>(fConst5, float(std::max<int>(0, iTemp22 + 1))))) & 16383] - (fRec1[2] * fTemp4 + 2.0f * fRec1[1] * fTemp3) / fTemp2;
			output0[i0] = FAUSTFLOAT(fSlow10 * fTemp19 + fSlow9 * ((fRec1[2] + fRec1[0] + 2.0f * fRec1[1]) / fTemp2));
			float fTemp24 = 2.0f * fTemp15 * fRec10[1];
			fRec10[0] = float(input1[i0]) - (fTemp17 * fRec10[2] + fTemp24) / fTemp12;
			float fTemp25 = (fTemp24 + fRec10[0] * fTemp18 + fTemp14 * fRec10[2]) / fTemp12;
			fVec1[IOTA0 & 16383] = fTemp25;
			fRec11[0] = fSlow11 + fConst2 * fRec11[1];
			fRec12[0] = fSlow12 + (fRec12[1] - std::floor(fSlow12 + fRec12[1]));
			float fTemp26 = fRec12[0] + 0.15915494f * fRec11[0];
			float fTemp27 = std::floor(fTemp26);
			float fTemp28 = fConst7 * fRec8[0] * (fRec7[0] * ((iSlow4) ? std::fabs(4.0f * (fTemp26 + (-0.25f - (fTemp27 + std::floor(fTemp26 + (-0.25f - fTemp27))))) + -2.0f) + -1.0f : std::sin(6.2831855f * (fTemp26 - fTemp27))) + 1.0f);
			int iTemp29 = int(fTemp28);
			float fTemp30 = std::floor(fTemp28);
			fRec9[0] = fVec1[(IOTA0 - int(std::min<float>(fConst5, float(std::max<int>(0, iTemp29))))) & 16383] * (fTemp30 + (1.0f - fTemp28)) + (fTemp28 - fTemp30) * fVec1[(IOTA0 - int(std::min<float>(fConst5, float(std::max<int>(0, iTemp29 + 1))))) & 16383] - (fTemp4 * fRec9[2] + 2.0f * fTemp3 * fRec9[1]) / fTemp2;
			output1[i0] = FAUSTFLOAT(fSlow10 * fTemp25 + fSlow9 * ((fRec9[2] + fRec9[0] + 2.0f * fRec9[1]) / fTemp2));
			fRec0[1] = fRec0[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec5[2] = fRec5[1];
			fRec5[1] = fRec5[0];
			IOTA0 = IOTA0 + 1;
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec10[2] = fRec10[1];
			fRec10[1] = fRec10[0];
			fRec11[1] = fRec11[0];
			fRec12[1] = fRec12[0];
			fRec9[2] = fRec9[1];
			fRec9[1] = fRec9[0];
		}
	}

};
// END CLASS CODE
// START EPILOG
FAUSTDR_END_NAMESPACE



#if defined(__GNUC__)
#   pragma GCC diagnostic pop
#endif


//------------------------------------------------------------------------------
// End the Faust code section




CChorus::CChorus()
{
mydsp *dsp = new mydsp;
    fDsp.reset(dsp);
    dsp->instanceResetUserInterface();
}

CChorus::~CChorus()
{
}

void CChorus::init(float sample_rate)
{
mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.classInit(sample_rate);
    dsp.instanceConstants(sample_rate);
    clear();
}

void CChorus::clear() noexcept
{
mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.instanceClear();
}

void CChorus::process(
    const float *in0, const float *in1, 
    float *out0, float *out1, 
    unsigned count) noexcept
{
mydsp &dsp = static_cast<mydsp &>(*fDsp);
    float *inputs[] = {
        const_cast<float *>(in0), const_cast<float *>(in1), 
    };
    float *outputs[] = {
        out0, out1, 
    };
    dsp.compute(count, inputs, outputs);
}

int CChorus::parameter_group(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return 0;
    case 1:
        return 0;
    case 2:
        return 0;
    case 3:
        return 1;
    case 4:
        return 1;
    case 5:
        return 1;
    case 6:
        return 2;
    case 7:
        return 2;
    case 8:
        return 2;
    case 9:
        return 2;
    case 10:
        return 3;
    case 11:
        return 3;
    default:
        return -1;
    }
}

const char *CChorus::parameter_group_label(unsigned group_id) noexcept
{
    switch (group_id) {
    
    case 0:
        return "Delay";
    case 1:
        return "Input";
    case 2:
        return "LFO";
    case 3:
        return "Output";
    default:
        return 0;
    }
}

const char *CChorus::parameter_group_symbol(unsigned group_id) noexcept
{
    switch (group_id) {
    
    case 0:
        return "delay";
    case 1:
        return "input";
    case 2:
        return "lfo";
    case 3:
        return "output";
    default:
        return 0;
    }
}


int CChorus::parameter_order(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return 1;
    case 1:
        return 2;
    case 2:
        return 3;
    case 3:
        return 1;
    case 4:
        return 2;
    case 5:
        return 3;
    case 6:
        return 1;
    case 7:
        return 2;
    case 8:
        return 3;
    case 9:
        return 4;
    case 10:
        return 1;
    case 11:
        return 2;
    default:
        return -1;
    }
}

const char *CChorus::parameter_label(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "Delay Length";
    case 1:
        return "Modulation Amount";
    case 2:
        return "Post-Delay LPF Cutoff";
    case 3:
        return "Pre-EQ Freqency";
    case 4:
        return "Pre-EQ Gain";
    case 5:
        return "Pre-EQ Q";
    case 6:
        return "LFO Waveform";
    case 7:
        return "LFO L Frequency";
    case 8:
        return "LFO R Frequency Ratio";
    case 9:
        return "LFO L/R Phase Offset";
    case 10:
        return "Dry Gain";
    case 11:
        return "Wet Gain";
    default:
        return 0;
    }
}

const char *CChorus::parameter_short_label(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "Delay";
    case 1:
        return "Mod. Amount";
    case 2:
        return "LPF";
    case 3:
        return "EQ Freq";
    case 4:
        return "EQ Gain";
    case 5:
        return "EQ Q";
    case 6:
        return "Waveform";
    case 7:
        return "Freq L";
    case 8:
        return "F. Ratio";
    case 9:
        return "Ph. Offset";
    case 10:
        return "Dry";
    case 11:
        return "Wet";
    default:
        return 0;
    }
}

const char *CChorus::parameter_style(unsigned index) noexcept
{
    switch (index) {
    
    case 6: {
        return "radio";
    }
    default:
        return "knob";
    }
}

const char *CChorus::parameter_symbol(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "delay";
    case 1:
        return "mod_amount";
    case 2:
        return "lpf_cutoff";
    case 3:
        return "eq_freq";
    case 4:
        return "eq_gain";
    case 5:
        return "eq_q";
    case 6:
        return "waveform";
    case 7:
        return "freq_l";
    case 8:
        return "freq_r_ratio";
    case 9:
        return "phase_offset";
    case 10:
        return "dry";
    case 11:
        return "wet";
    default:
        return 0;
    }
}

const char *CChorus::parameter_unit(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "ms";
    case 1:
        return "";
    case 2:
        return "Hz";
    case 3:
        return "Hz";
    case 4:
        return "db";
    case 5:
        return "";
    case 6:
        return "";
    case 7:
        return "Hz";
    case 8:
        return "";
    case 9:
        return "degree";
    case 10:
        return "dB";
    case 11:
        return "dB";
    default:
        return 0;
    }
}

const CChorus::ParameterRange *CChorus::parameter_range(unsigned index) noexcept
{
    switch (index) {
    
    case 0: {
        static const ParameterRange range = { 3.5, 0.0, 30.0 };
        return &range;
    }
    case 1: {
        static const ParameterRange range = { 0.35, 0.001, 1.0 };
        return &range;
    }
    case 2: {
        static const ParameterRange range = { 10000.0, 20.0, 10000.0 };
        return &range;
    }
    case 3: {
        static const ParameterRange range = { 750.0, 20.0, 4000.0 };
        return &range;
    }
    case 4: {
        static const ParameterRange range = { 0.0, -12.0, 12.0 };
        return &range;
    }
    case 5: {
        static const ParameterRange range = { 0.7, 0.1, 16.0 };
        return &range;
    }
    case 6: {
        static const ParameterRange range = { 1.0, 0.0, 1.0 };
        return &range;
    }
    case 7: {
        static const ParameterRange range = { 0.8, 0.01, 10.0 };
        return &range;
    }
    case 8: {
        static const ParameterRange range = { 1.0, 0.01, 2.0 };
        return &range;
    }
    case 9: {
        static const ParameterRange range = { 90.0, -180.0, 180.0 };
        return &range;
    }
    case 10: {
        static const ParameterRange range = { -3.5, -60.0, 10.0 };
        return &range;
    }
    case 11: {
        static const ParameterRange range = { -3.5, -60.0, 10.0 };
        return &range;
    }
    default:
        return 0;
    }
}

unsigned CChorus::parameter_scale_point_count(unsigned index) noexcept
{
    switch (index) {
    
    case 6:
        return 2;
    default:
        return 0;
    }
}

const CChorus::ParameterScalePoint *CChorus::parameter_scale_point(unsigned index, unsigned point) noexcept
{
    switch (index) {
    
    case 6:
        switch (point) {
        
        case 0: {
            static const ParameterScalePoint scale_point = { "Sine", 0.0 };
            return &scale_point;
        }
        case 1: {
            static const ParameterScalePoint scale_point = { "Triangle", 1.0 };
            return &scale_point;
        }
        default:
            return 0;
        }
    default:
        return 0;
    }
}

bool CChorus::parameter_is_trigger(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return false;
    }
}

bool CChorus::parameter_is_boolean(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return false;
    }
}

bool CChorus::parameter_is_enum(unsigned index) noexcept
{
    switch (index) {
    
    case 6:
        return true;
    default:
        return false;
    }
}

bool CChorus::parameter_is_integer(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return false;
    }
}

bool CChorus::parameter_is_logarithmic(unsigned index) noexcept
{
    switch (index) {
    
    case 2:
        return true;
    case 3:
        return true;
    default:
        return false;
    }
}

float CChorus::get_parameter(unsigned index) const noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    switch (index) {
    
    case 0:
        return dsp.fHslider7;
    case 1:
        return dsp.fHslider6;
    case 2:
        return dsp.fHslider0;
    case 3:
        return dsp.fHslider1;
    case 4:
        return dsp.fHslider2;
    case 5:
        return dsp.fHslider3;
    case 6:
        return dsp.fHslider4;
    case 7:
        return dsp.fHslider5;
    case 8:
        return dsp.fHslider11;
    case 9:
        return dsp.fHslider10;
    case 10:
        return dsp.fHslider9;
    case 11:
        return dsp.fHslider8;
    default:
        (void)dsp;
        return 0;
    }
}

void CChorus::set_parameter(unsigned index, float value) noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    switch (index) {
    
    case 0:
        dsp.fHslider7 = value;
        break;
    case 1:
        dsp.fHslider6 = value;
        break;
    case 2:
        dsp.fHslider0 = value;
        break;
    case 3:
        dsp.fHslider1 = value;
        break;
    case 4:
        dsp.fHslider2 = value;
        break;
    case 5:
        dsp.fHslider3 = value;
        break;
    case 6:
        dsp.fHslider4 = value;
        break;
    case 7:
        dsp.fHslider5 = value;
        break;
    case 8:
        dsp.fHslider11 = value;
        break;
    case 9:
        dsp.fHslider10 = value;
        break;
    case 10:
        dsp.fHslider9 = value;
        break;
    case 11:
        dsp.fHslider8 = value;
        break;
    default:
        (void)dsp;
        (void)value;
        break;
    }
}


float CChorus::get_delay() const noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    return dsp.fHslider7;
}

float CChorus::get_mod_amount() const noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    return dsp.fHslider6;
}

float CChorus::get_lpf_cutoff() const noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    return dsp.fHslider0;
}

float CChorus::get_eq_freq() const noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    return dsp.fHslider1;
}

float CChorus::get_eq_gain() const noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    return dsp.fHslider2;
}

float CChorus::get_eq_q() const noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    return dsp.fHslider3;
}

float CChorus::get_waveform() const noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    return dsp.fHslider4;
}

float CChorus::get_freq_l() const noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    return dsp.fHslider5;
}

float CChorus::get_freq_r_ratio() const noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    return dsp.fHslider11;
}

float CChorus::get_phase_offset() const noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    return dsp.fHslider10;
}

float CChorus::get_dry() const noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    return dsp.fHslider9;
}

float CChorus::get_wet() const noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    return dsp.fHslider8;
}


void CChorus::set_delay(float value) noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.fHslider7 = value;
}

void CChorus::set_mod_amount(float value) noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.fHslider6 = value;
}

void CChorus::set_lpf_cutoff(float value) noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.fHslider0 = value;
}

void CChorus::set_eq_freq(float value) noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.fHslider1 = value;
}

void CChorus::set_eq_gain(float value) noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.fHslider2 = value;
}

void CChorus::set_eq_q(float value) noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.fHslider3 = value;
}

void CChorus::set_waveform(float value) noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.fHslider4 = value;
}

void CChorus::set_freq_l(float value) noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.fHslider5 = value;
}

void CChorus::set_freq_r_ratio(float value) noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.fHslider11 = value;
}

void CChorus::set_phase_offset(float value) noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.fHslider10 = value;
}

void CChorus::set_dry(float value) noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.fHslider9 = value;
}

void CChorus::set_wet(float value) noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.fHslider8 = value;
}


