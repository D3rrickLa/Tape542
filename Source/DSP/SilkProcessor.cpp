/*
  ==============================================================================

    SilkProcessor.cpp
    Created: 13 Oct 2025 10:37:15pm
    Author:  Gen3r

  ==============================================================================
*/

#include "SilkProcessor.h"
#include <cmath>
#include <algorithm>
#define M_PI 3.14159265358979323846

SilkProcessor::SilkProcessor()
    : mode(SILK_OFF), texture(0.0f), sampleRate(44100.0)
{
}

SilkProcessor::~SilkProcessor()
{
}


void SilkProcessor::prepare(float sr)
{
    if (isStandardSampleRate(sr))
    {
        sampleRate = sr;
        bpRed.set(4000.0f, 0.8, sr);  // Red emphasizes highs
        bpBlue.set(150.f, 0.8f, sr); // Blue emphasizes low/mids
    }
}

void SilkProcessor::setMode(SilkMode m) 
{
    mode = m;
}

void SilkProcessor::setTexture(float t)
{
    texture = std::clamp(t, 0.0f, 1.0f);
}

float SilkProcessor::processSample(float input)
{
    if (mode == SILK_OFF)
    {
        return input;
    }

    // choose band and process 
    float band = (mode == SILK_RED) ? bpRed.process(input) : bpBlue.process(input);

    // no-linearity on the band
    float distorted = std::tanh(band * (1.0f + texture * 4.0f));
    float out = input + distorted * texture * 0.5f;
    return out;
}

bool SilkProcessor::isStandardSampleRate(float sr)
{
    switch (int(sr)) {
    case 44100: case 48000: case 88200: case 96000: case 192000: return true;
    default: return false;
    }
}


// OnePoleBandpass //
OnePoleBandpass::OnePoleBandpass()
    : center(1000.0f), q(1.0f), sampleRate(44100.0)
{
    set(center, q, sampleRate);
}

OnePoleBandpass::~OnePoleBandpass()
{

}

void OnePoleBandpass::set(float centerHz, float qVal, float sr)
{
    // naive/resonant bandpass - need to fix
    center = centerHz; q = qVal; sampleRate = sr;

    // compute simplistic coefficients (not butterworth)
    w = 2.0f * float(M_PI) * center / float(sr); 
    alpha = std::sin(w) / (2.0f * q);

}

float OnePoleBandpass::process(float x)
{
    // very simple resonant shell (toy)
    float out = x - lpState;
    lpState = x * 0.1f + lpState * 0.9f;
    return out;
}