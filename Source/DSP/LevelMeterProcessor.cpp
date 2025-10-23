/*
  ==============================================================================

    LevelMeterProcessor.cpp
    Created: 13 Oct 2025 10:37:58pm
    Author:  Gen3r

  ==============================================================================
*/

#include "LevelMeterProcessor.h"
#include <cmath>
#include <algorithm>

LevelMeterProcessor::LevelMeterProcessor()
    : sampleRate(44100.0), attackMs(1.0f), releaseMs(100.0f), state(0.0f)
{
    updateCoeffs();
}

LevelMeterProcessor::~LevelMeterProcessor()
{

}


void LevelMeterProcessor::prepare(float sr)
{
    if (isStandardSampleRate(sr))
    {
        sampleRate = sr;
        updateCoeffs();
    }
}

void LevelMeterProcessor::setAttackMs(float ms)
{
    attackMs = ms;
    updateCoeffs();
}

void LevelMeterProcessor::setReleaseMs(float ms)
{
    releaseMs = ms;
    updateCoeffs();
}

float LevelMeterProcessor::processSample(float x)
{
  
    float val = std::abs(x); // peak detection
    if (val > state)
    {
        state = attackCoeff * (state - val) + val; // faster rise
    }
    else 
    {
        state = releaseCoeff * (state - val) + val; // slower fall
    }
    return state;

    
}

float LevelMeterProcessor::getNormalizedLevel()
{
    // convert amplitude to dBFS
    float db = 20.0f * std::log10(std::max(1e-7f, state));
    // map -60 dB .. 0 dB to 0..1
    float norm = (db + 60.0f) / 60.0f;
    return std::clamp(norm, 0.0f, 1.0f);

}

int LevelMeterProcessor::getLedSegmentIndex(int segments = 8)
{
    return int(getNormalizedLevel() * (segments - 1) + 0.5f);

}

bool LevelMeterProcessor::isStandardSampleRate(float sr)
{
    switch (int(sr)) {
    case 44100: case 48000: case 88200: case 96000: case 192000: return true;
    default: return false;
    }
}

void LevelMeterProcessor::updateCoeffs()
{
    attackCoeff = std::exp(-1.0f / (0.001f * attackMs * float(sampleRate)));
    releaseCoeff = std::exp(-1.0f / (0.001f * releaseMs * float(sampleRate)));
}