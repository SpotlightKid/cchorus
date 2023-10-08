
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

#define FAUSTPP_VIRTUAL // do not declare any methods virtual
#define FAUSTPP_PRIVATE public // do not hide any members
#define FAUSTPP_PROTECTED public // do not hide any members

// define the DSP in the anonymous namespace
#define FAUSTPP_BEGIN_NAMESPACE namespace {
#define FAUSTPP_END_NAMESPACE }


#if defined(__GNUC__)
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#ifndef FAUSTPP_PRIVATE
#   define FAUSTPP_PRIVATE private
#endif
#ifndef FAUSTPP_PROTECTED
#   define FAUSTPP_PROTECTED protected
#endif
#ifndef FAUSTPP_VIRTUAL
#   define FAUSTPP_VIRTUAL virtual
#endif

#ifndef FAUSTPP_BEGIN_NAMESPACE
#   define FAUSTPP_BEGIN_NAMESPACE
#endif
#ifndef FAUSTPP_END_NAMESPACE
#   define FAUSTPP_END_NAMESPACE
#endif

FAUSTPP_BEGIN_NAMESPACE

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

FAUSTPP_END_NAMESPACE
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>
FAUSTPP_BEGIN_NAMESPACE

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
	
 FAUSTPP_PRIVATE:
	
	FAUSTFLOAT fCheckbox0;
	int fSampleRate;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fHslider0;
	float fRec0[2];
	float fConst3;
	FAUSTFLOAT fHslider1;
	float fRec2[2];
	int IOTA0;
	float fVec0[8192];
	float fConst4;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	float fConst5;
	float fRec4[2];
	FAUSTFLOAT fHslider4;
	float fRec5[2];
	FAUSTFLOAT fHslider5;
	float fRec6[2];
	float fConst6;
	float fRec3[3];
	float fRec1[3];
	FAUSTFLOAT fHslider6;
	FAUSTFLOAT fHslider7;
	FAUSTFLOAT fHslider8;
	float fConst7;
	float fRec9[2];
	FAUSTFLOAT fHslider9;
	float fRec10[2];
	float fRec8[3];
	float fRec7[3];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("author", "Christopher Arndt");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.9");
		m->declare("compile_options", "-a /home/chris/tmp/tmp47mje5r_.cpp -lang cpp -es 1 -mcd 16 -single -ftz 0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.1");
		m->declare("description", "A versatile stereo chorus effect");
		m->declare("filename", "cchorus.dsp");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/highpass:author", "Julius O. Smith III");
		m->declare("filters.lib/highpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "0.3");
		m->declare("license", "MIT License");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.5");
		m->declare("name", "CChorus");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "0.3");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.3");
		m->declare("version", "0.5");
	}

	FAUSTPP_VIRTUAL int getNumInputs() {
		return 2;
	}
	FAUSTPP_VIRTUAL int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
	}
	
	FAUSTPP_VIRTUAL void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		float fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = 44.1f / fConst0;
		fConst2 = 1.0f - fConst1;
		fConst3 = 3.1415927f / fConst0;
		fConst4 = 0.04f * fConst0 + 1.0f;
		fConst5 = 1.0f / fConst0;
		fConst6 = 0.001f * fConst0;
		fConst7 = 7.018733f / fConst0;
	}
	
	FAUSTPP_VIRTUAL void instanceResetUserInterface() {
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fHslider0 = FAUSTFLOAT(2e+01f);
		fHslider1 = FAUSTFLOAT(5e+03f);
		fHslider2 = FAUSTFLOAT(1.0f);
		fHslider3 = FAUSTFLOAT(0.8f);
		fHslider4 = FAUSTFLOAT(0.35f);
		fHslider5 = FAUSTFLOAT(3.5f);
		fHslider6 = FAUSTFLOAT(-3.5f);
		fHslider7 = FAUSTFLOAT(-3.5f);
		fHslider8 = FAUSTFLOAT(9e+01f);
		fHslider9 = FAUSTFLOAT(1.0f);
	}
	
	FAUSTPP_VIRTUAL void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec0[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec2[l1] = 0.0f;
		}
		IOTA0 = 0;
		for (int l2 = 0; l2 < 8192; l2 = l2 + 1) {
			fVec0[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec4[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec5[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec6[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 3; l6 = l6 + 1) {
			fRec3[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 3; l7 = l7 + 1) {
			fRec1[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec9[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec10[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 3; l10 = l10 + 1) {
			fRec8[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 3; l11 = l11 + 1) {
			fRec7[l11] = 0.0f;
		}
	}
	
	FAUSTPP_VIRTUAL void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	FAUSTPP_VIRTUAL void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	FAUSTPP_VIRTUAL mydsp* clone() {
		return new mydsp();
	}
	
	FAUSTPP_VIRTUAL int getSampleRate() {
		return fSampleRate;
	}
	
	FAUSTPP_VIRTUAL void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("CChorus");
		ui_interface->openHorizontalBox("Delay");
		ui_interface->declare(&fHslider5, "1", "");
		ui_interface->declare(&fHslider5, "style", "knob");
		ui_interface->declare(&fHslider5, "unit", "ms");
		ui_interface->addHorizontalSlider("Delay", &fHslider5, FAUSTFLOAT(3.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider4, "2", "");
		ui_interface->declare(&fHslider4, "style", "knob");
		ui_interface->addHorizontalSlider("Mod Amount", &fHslider4, FAUSTFLOAT(0.35f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider1, "3", "");
		ui_interface->declare(&fHslider1, "scale", "log");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->declare(&fHslider1, "unit", "Hz");
		ui_interface->addHorizontalSlider("LPF Cutoff", &fHslider1, FAUSTFLOAT(5e+03f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(1e+04f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider0, "4", "");
		ui_interface->declare(&fHslider0, "scale", "log");
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->declare(&fHslider0, "unit", "Hz");
		ui_interface->addHorizontalSlider("HPF Cutoff", &fHslider0, FAUSTFLOAT(2e+01f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(5e+03f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("LFO");
		ui_interface->declare(&fHslider2, "1", "");
		ui_interface->declare(&fHslider2, "style", "radio{'Sine':0;'Triangle':1}");
		ui_interface->addHorizontalSlider("Waveform", &fHslider2, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider3, "2", "");
		ui_interface->declare(&fHslider3, "style", "knob");
		ui_interface->declare(&fHslider3, "unit", "Hz");
		ui_interface->addHorizontalSlider("Freq L", &fHslider3, FAUSTFLOAT(0.8f), FAUSTFLOAT(0.001f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider9, "3", "");
		ui_interface->declare(&fHslider9, "style", "knob");
		ui_interface->addHorizontalSlider("Freq R Ratio", &fHslider9, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f), FAUSTFLOAT(2.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider8, "4", "");
		ui_interface->declare(&fHslider8, "style", "knob");
		ui_interface->declare(&fHslider8, "unit", "degree");
		ui_interface->addHorizontalSlider("L/R Phase Offset", &fHslider8, FAUSTFLOAT(9e+01f), FAUSTFLOAT(-1.8e+02f), FAUSTFLOAT(1.8e+02f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Output");
		ui_interface->declare(&fHslider7, "1", "");
		ui_interface->declare(&fHslider7, "style", "knob");
		ui_interface->declare(&fHslider7, "unit", "dB");
		ui_interface->addHorizontalSlider("Dry", &fHslider7, FAUSTFLOAT(-3.5f), FAUSTFLOAT(-6e+01f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider6, "2", "");
		ui_interface->declare(&fHslider6, "style", "knob");
		ui_interface->declare(&fHslider6, "unit", "dB");
		ui_interface->addHorizontalSlider("Wet", &fHslider6, FAUSTFLOAT(-3.5f), FAUSTFLOAT(-6e+01f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fCheckbox0, "3", "");
		ui_interface->addCheckButton("Bypass", &fCheckbox0);
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	FAUSTPP_VIRTUAL void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		int iSlow0 = int(float(fCheckbox0));
		float fSlow1 = fConst1 * float(fHslider0);
		float fSlow2 = fConst1 * float(fHslider1);
		int iSlow3 = int(float(fHslider2));
		float fSlow4 = float(fHslider3);
		float fSlow5 = fConst5 * fSlow4;
		float fSlow6 = fConst1 * float(fHslider4);
		float fSlow7 = fConst1 * float(fHslider5);
		float fSlow8 = std::pow(1e+01f, 0.05f * float(fHslider6));
		float fSlow9 = std::pow(1e+01f, 0.05f * float(fHslider7));
		float fSlow10 = fConst7 * float(fHslider8);
		float fSlow11 = fConst5 * fSlow4 * float(fHslider9);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec0[0] = fSlow1 + fConst2 * fRec0[1];
			float fTemp0 = std::tan(fConst3 * fRec0[0]);
			float fTemp1 = 1.0f / fTemp0;
			float fTemp2 = (fTemp1 + 1.4142135f) / fTemp0 + 1.0f;
			float fTemp3 = mydsp_faustpower2_f(fTemp0);
			float fTemp4 = 1.0f - 1.0f / fTemp3;
			float fTemp5 = (fTemp1 + -1.4142135f) / fTemp0 + 1.0f;
			fRec2[0] = fSlow2 + fConst2 * fRec2[1];
			float fTemp6 = std::tan(fConst3 * fRec2[0]);
			float fTemp7 = 1.0f / fTemp6;
			float fTemp8 = (fTemp7 + 1.4142135f) / fTemp6 + 1.0f;
			float fTemp9 = 1.0f - 1.0f / mydsp_faustpower2_f(fTemp6);
			float fTemp10 = (fTemp7 + -1.4142135f) / fTemp6 + 1.0f;
			float fTemp11 = float(input0[i0]);
			fVec0[IOTA0 & 8191] = fTemp11;
			fRec4[0] = fSlow5 + (fRec4[1] - std::floor(fSlow5 + fRec4[1]));
			float fTemp12 = std::floor(fRec4[0]);
			fRec5[0] = fSlow6 + fConst2 * fRec5[1];
			fRec6[0] = fSlow7 + fConst2 * fRec6[1];
			float fTemp13 = fConst6 * fRec6[0] * (fRec5[0] * ((iSlow3) ? std::fabs(4.0f * (fRec4[0] + (-0.25f - (fTemp12 + std::floor(fRec4[0] + (-0.25f - fTemp12))))) + -2.0f) + -1.0f : std::sin(6.2831855f * (fRec4[0] - fTemp12))) + 1.0f);
			int iTemp14 = int(fTemp13);
			float fTemp15 = std::floor(fTemp13);
			fRec3[0] = fVec0[(IOTA0 - int(std::min<float>(fConst4, float(std::max<int>(0, iTemp14))))) & 8191] * (fTemp15 + (1.0f - fTemp13)) + (fTemp13 - fTemp15) * fVec0[(IOTA0 - int(std::min<float>(fConst4, float(std::max<int>(0, iTemp14 + 1))))) & 8191] - (fRec3[2] * fTemp10 + 2.0f * fRec3[1] * fTemp9) / fTemp8;
			fRec1[0] = (fRec3[2] + fRec3[0] + 2.0f * fRec3[1]) / fTemp8 - (fRec1[2] * fTemp5 + 2.0f * fRec1[1] * fTemp4) / fTemp2;
			float fTemp16 = 0.0f - 2.0f / fTemp3;
			float fTemp17 = fSlow9 * fTemp11;
			float fTemp18 = float(input1[i0]);
			output0[i0] = FAUSTFLOAT(((iSlow0) ? fTemp18 : fTemp17 + fSlow8 * ((fRec1[1] * fTemp16 + fRec1[0] / fTemp3 + fRec1[2] / fTemp3) / fTemp2)));
			fRec9[0] = fSlow10 + fConst2 * fRec9[1];
			fRec10[0] = fSlow11 + (fRec10[1] - std::floor(fSlow11 + fRec10[1]));
			float fTemp19 = fRec10[0] + 0.15915494f * fRec9[0];
			float fTemp20 = std::floor(fTemp19);
			float fTemp21 = fConst6 * fRec6[0] * (fRec5[0] * ((iSlow3) ? std::fabs(4.0f * (fTemp19 + (-0.25f - (fTemp20 + std::floor(fTemp19 + (-0.25f - fTemp20))))) + -2.0f) + -1.0f : std::sin(6.2831855f * (fTemp19 - fTemp20))) + 1.0f);
			int iTemp22 = int(fTemp21);
			float fTemp23 = std::floor(fTemp21);
			fRec8[0] = fVec0[(IOTA0 - int(std::min<float>(fConst4, float(std::max<int>(0, iTemp22))))) & 8191] * (fTemp23 + (1.0f - fTemp21)) + (fTemp21 - fTemp23) * fVec0[(IOTA0 - int(std::min<float>(fConst4, float(std::max<int>(0, iTemp22 + 1))))) & 8191] - (fTemp10 * fRec8[2] + 2.0f * fTemp9 * fRec8[1]) / fTemp8;
			fRec7[0] = (fRec8[2] + fRec8[0] + 2.0f * fRec8[1]) / fTemp8 - (fTemp5 * fRec7[2] + 2.0f * fTemp4 * fRec7[1]) / fTemp2;
			output1[i0] = FAUSTFLOAT(((iSlow0) ? fTemp18 : fTemp17 + fSlow8 * ((fTemp16 * fRec7[1] + fRec7[0] / fTemp3 + fRec7[2] / fTemp3) / fTemp2)));
			fRec0[1] = fRec0[0];
			fRec2[1] = fRec2[0];
			IOTA0 = IOTA0 + 1;
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec9[1] = fRec9[0];
			fRec10[1] = fRec10[0];
			fRec8[2] = fRec8[1];
			fRec8[1] = fRec8[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
		}
	}

};
FAUSTPP_END_NAMESPACE


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
    const float *in0,const float *in1,
    float *out0,float *out1,
    unsigned count) noexcept
{

    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    float *inputs[] = {
        const_cast<float *>(in0),const_cast<float *>(in1),
    };
    float *outputs[] = {
        out0,out1,
    };
    dsp.compute(count, inputs, outputs);

}

const char *CChorus::parameter_label(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "Delay";
    
    case 1:
        return "Mod Amount";
    
    case 2:
        return "LPF Cutoff";
    
    case 3:
        return "HPF Cutoff";
    
    case 4:
        return "Waveform";
    
    case 5:
        return "Freq L";
    
    case 6:
        return "Freq R Ratio";
    
    case 7:
        return "L/R Phase Offset";
    
    case 8:
        return "Dry";
    
    case 9:
        return "Wet";
    
    case 10:
        return "Bypass";
    
    default:
        return 0;
    }
}

const char *CChorus::parameter_short_label(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "";
    
    case 1:
        return "";
    
    case 2:
        return "";
    
    case 3:
        return "";
    
    case 4:
        return "";
    
    case 5:
        return "";
    
    case 6:
        return "";
    
    case 7:
        return "";
    
    case 8:
        return "";
    
    case 9:
        return "";
    
    case 10:
        return "";
    
    default:
        return 0;
    }
}

const char *CChorus::parameter_symbol(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "Delay";
    
    case 1:
        return "Mod_Amount";
    
    case 2:
        return "LPF_Cutoff";
    
    case 3:
        return "HPF_Cutoff";
    
    case 4:
        return "Waveform";
    
    case 5:
        return "Freq_L";
    
    case 6:
        return "Freq_R_Ratio";
    
    case 7:
        return "L_R_Phase_Offset";
    
    case 8:
        return "Dry";
    
    case 9:
        return "Wet";
    
    case 10:
        return "Bypass";
    
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
        return "";
    
    case 5:
        return "Hz";
    
    case 6:
        return "";
    
    case 7:
        return "degree";
    
    case 8:
        return "dB";
    
    case 9:
        return "dB";
    
    case 10:
        return "";
    
    default:
        return 0;
    }
}

const CChorus::ParameterRange *CChorus::parameter_range(unsigned index) noexcept
{
    switch (index) {
    
    case 0: {
        static const ParameterRange range = { 3.5, 0.0, 20.0 };
        return &range;
    }
    
    case 1: {
        static const ParameterRange range = { 0.35, 0.0, 1.0 };
        return &range;
    }
    
    case 2: {
        static const ParameterRange range = { 5000.0, 20.0, 10000.0 };
        return &range;
    }
    
    case 3: {
        static const ParameterRange range = { 20.0, 20.0, 5000.0 };
        return &range;
    }
    
    case 4: {
        static const ParameterRange range = { 1.0, 0.0, 1.0 };
        return &range;
    }
    
    case 5: {
        static const ParameterRange range = { 0.8, 0.001, 10.0 };
        return &range;
    }
    
    case 6: {
        static const ParameterRange range = { 1.0, 0.01, 2.0 };
        return &range;
    }
    
    case 7: {
        static const ParameterRange range = { 90.0, -180.0, 180.0 };
        return &range;
    }
    
    case 8: {
        static const ParameterRange range = { -3.5, -60.0, 10.0 };
        return &range;
    }
    
    case 9: {
        static const ParameterRange range = { -3.5, -60.0, 10.0 };
        return &range;
    }
    
    case 10: {
        static const ParameterRange range = { 0, 0, 1 };
        return &range;
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
    
    case 10:
        return true;
    
    default:
        return false;
    }
}

bool CChorus::parameter_is_integer(unsigned index) noexcept
{
    switch (index) {
    
    case 10:
        return true;
    
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
        return dsp.fHslider5;
    
    case 1:
        return dsp.fHslider4;
    
    case 2:
        return dsp.fHslider1;
    
    case 3:
        return dsp.fHslider0;
    
    case 4:
        return dsp.fHslider2;
    
    case 5:
        return dsp.fHslider3;
    
    case 6:
        return dsp.fHslider9;
    
    case 7:
        return dsp.fHslider8;
    
    case 8:
        return dsp.fHslider7;
    
    case 9:
        return dsp.fHslider6;
    
    case 10:
        return dsp.fCheckbox0;
    
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
        dsp.fHslider5 = value;
        break;
    
    case 1:
        dsp.fHslider4 = value;
        break;
    
    case 2:
        dsp.fHslider1 = value;
        break;
    
    case 3:
        dsp.fHslider0 = value;
        break;
    
    case 4:
        dsp.fHslider2 = value;
        break;
    
    case 5:
        dsp.fHslider3 = value;
        break;
    
    case 6:
        dsp.fHslider9 = value;
        break;
    
    case 7:
        dsp.fHslider8 = value;
        break;
    
    case 8:
        dsp.fHslider7 = value;
        break;
    
    case 9:
        dsp.fHslider6 = value;
        break;
    
    case 10:
        dsp.fCheckbox0 = value;
        break;
    
    default:
        (void)dsp;
        (void)value;
        break;
    }
}


float CChorus::get_Delay() const noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    return dsp.fHslider5;
}

float CChorus::get_Mod_Amount() const noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    return dsp.fHslider4;
}

float CChorus::get_LPF_Cutoff() const noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    return dsp.fHslider1;
}

float CChorus::get_HPF_Cutoff() const noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    return dsp.fHslider0;
}

float CChorus::get_Waveform() const noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    return dsp.fHslider2;
}

float CChorus::get_Freq_L() const noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    return dsp.fHslider3;
}

float CChorus::get_Freq_R_Ratio() const noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    return dsp.fHslider9;
}

float CChorus::get_L_R_Phase_Offset() const noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    return dsp.fHslider8;
}

float CChorus::get_Dry() const noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    return dsp.fHslider7;
}

float CChorus::get_Wet() const noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    return dsp.fHslider6;
}

float CChorus::get_Bypass() const noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    return dsp.fCheckbox0;
}


void CChorus::set_Delay(float value) noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.fHslider5 = value;
}

void CChorus::set_Mod_Amount(float value) noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.fHslider4 = value;
}

void CChorus::set_LPF_Cutoff(float value) noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.fHslider1 = value;
}

void CChorus::set_HPF_Cutoff(float value) noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.fHslider0 = value;
}

void CChorus::set_Waveform(float value) noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.fHslider2 = value;
}

void CChorus::set_Freq_L(float value) noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.fHslider3 = value;
}

void CChorus::set_Freq_R_Ratio(float value) noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.fHslider9 = value;
}

void CChorus::set_L_R_Phase_Offset(float value) noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.fHslider8 = value;
}

void CChorus::set_Dry(float value) noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.fHslider7 = value;
}

void CChorus::set_Wet(float value) noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.fHslider6 = value;
}

void CChorus::set_Bypass(float value) noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.fCheckbox0 = value;
}


