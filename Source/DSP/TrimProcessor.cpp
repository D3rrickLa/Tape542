/*
  ==============================================================================

    TrimProcessor.cpp
    Created: 13 Oct 2025 10:11:48pm
    Author:  Gen3r

  ==============================================================================
*/

#include "TrimProcessor.h"
#include <cmath>
#include <algorithm>


TrimProcessor::TrimProcessor()
    : trimDb(0.0f), gainLinear(1.0f), sampleRate(44100.0f)
{
    updateGain();
}

TrimProcessor::~TrimProcessor()
{

}

void TrimProcessor::prepare(double sr) 
{

    if (isStandardSampleRate(sr)) 
    {
        sampleRate = sr;
        updateGain();
    }

}

void TrimProcessor::setTrimDb(float db)
{
   
    trimDb = std::clamp(db, -12.0f, 12.0f);
    updateGain();
    
}

// doesn't modify a member state so we cna mske it as const
float TrimProcessor::processSample(float x) const noexcept
{
    // TODO: optional oversampling before nonlinear stages
    return x * gainLinear;
}

void TrimProcessor::updateGain() 
{
    gainLinear = std::pow(10.0f, trimDb / 20.0f); // dB -> linear
}

bool TrimProcessor::isStandardSampleRate(float sr)
{
    switch (int(sr)) {
        case 44100: case 48000: case 88200: case 96000: case 192000: return true;
        default: return false;
    }
}