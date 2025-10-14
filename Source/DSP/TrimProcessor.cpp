/*
  ==============================================================================

    TrimProcessor.cpp
    Created: 13 Oct 2025 10:11:48pm
    Author:  Gen3r

  ==============================================================================
*/

#include "TrimProcessor.h"
#include <cmath>


TrimProcessor::TrimProcessor()
    : trimDb(0.0f), gainLinear(1.0f), sampleRate(44100.0f)
{
    updateGain();
}

TrimProcessor::~TrimProcessor()
{

}

void TrimProcessor::prepare(double sr) {
    sampleRate = sr; 
    updateGain();
}

void TrimProcessor::setTrimDb(float db)
{
    trimDb = db;
    updateGain();
}

float TrimProcessor::processSample(float x)
{
    return x * gainLinear;
}

void TrimProcessor::updateGain() {
    gainLinear = std::pow(10.0f, trimDb / 20.0f); // dB -> linear
}