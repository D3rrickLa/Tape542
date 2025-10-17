/*
  ==============================================================================

    SaturationProcessor.cpp
    Created: 13 Oct 2025 10:35:51pm
    Author:  Gen3r

  ==============================================================================
*/

#include "SaturationProcessor.h"
#include <cmath>
#include <algorithm>
#define M_PI 3.14159265358979323846

SaturationProcessor::SaturationProcessor() : drive(1.0f), preEmphCutHz(8000.0f), sampleRate(44100.0f)
{
    hpState = 0.0f; lpState = 0.0f; 
    updateCoeffs();
}

SaturationProcessor::~SaturationProcessor()
{
}

void SaturationProcessor::prepare(float sr)
{
    if (isStandardSampleRate(sr))
    {
        sampleRate = sr; 
        updateCoeffs();
    }
}

void SaturationProcessor::setDrive(float d)
{
    drive = std::max(0.0f, d);
}

void SaturationProcessor::setPreEmphasisHz(float hz)
{
    preEmphCutHz = hz; 
    updateCoeffs();
}

float SaturationProcessor::processSample(float x)
{
    // pre-emphasis (simple one-pole HP)
    float pre = hp_a0 * (x - hp_x1) - hp_a1 * hpState;
    hpState = pre; 
    hp_x1 = x;
    
    // driven into tanh-based soft-satuartion;
    float driven = std::tanh(pre * drive);

    //de-emphasis (simple one-pole LP to smooht highs) 
    float out = lp_b0 * driven + lp_b1 * lpState;
    lpState = driven; 

    return out * makeupGain();
}

/*
* defines coefficients for the pre-emphasis and de-emphasis filters that shape the sound before and after the saturation 
* input -> [pre-emp filter] -> tanh(distortion) -> [de-emp filter] -> output
*/
void SaturationProcessor::updateCoeffs()
{
    // simple single-pole approx.
    float rc_hp = 1.0f / (2.0f * float((M_PI)*preEmphCutHz));
    float dt = 1.0f / float(sampleRate);
    float alpha_hp = rc_hp / (rc_hp + dt);

    hp_a0 = 1.0f - alpha_hp;
    hp_a1 = alpha_hp;

    // LP for de-emp
    float cutoffLP = preEmphCutHz;
    float rc_lp = 1.0f / (2.0f * float(M_PI) * cutoffLP);
    float alpha_lp = dt / (rc_lp + dt);
    lp_b0 = alpha_lp;
    lp_b1 = 1.0f - alpha_lp;
}

float SaturationProcessor::makeupGain()
{
    // higher drive reduces output
    return 1.0f + (drive - 1.0f) * 0.15f;
}

bool SaturationProcessor::isStandardSampleRate(float sr)
{
    switch (int(sr)) {
    case 44100: case 48000: case 88200: case 96000: case 192000: return true;
    default: return false;
    }
}