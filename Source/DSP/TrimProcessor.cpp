/*
  ==============================================================================

    TrimProcessor.cpp
    Created: 13 Oct 2025 10:11:48pm
    Author:  Gen3r

  ==============================================================================
*/

#include "TrimProcessor.h"
#include <cmath>
#include <unordered_set>


TrimProcessor::TrimProcessor()
    : trimDb(0.0f), gainLinear(1.0f), sampleRate(44100.0f)
{
    updateGain();
}

TrimProcessor::~TrimProcessor()
{

}

void TrimProcessor::prepare(double sr) {
    // we only want standard sampleRates
    std::unordered_set<float> standardSampleRate{ 44100, 48000, 88200, 96000, 192000 };
    if (standardSampleRate.find(sr)) 
    {
        sampleRate = sr;
        updateGain();
    }

}

void TrimProcessor::setTrimDb(float db)
{
    if (db <= 12.f && db >= -12) 
    {
        trimDb = db;
        updateGain();
    }
}

float TrimProcessor::processSample(float x)
{
    return x * gainLinear;
}

void TrimProcessor::updateGain() {
    gainLinear = std::pow(10.0f, trimDb / 20.0f); // dB -> linear
}