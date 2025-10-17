/*
  ==============================================================================

    SoftClipProcessor.cpp
    Created: 13 Oct 2025 10:36:19pm
    Author:  Gen3r

  ==============================================================================
*/

#include "SoftClipProcessor.h"
#include <cmath>
#include <algorithm>

SoftClipProcessor::SoftClipProcessor():
        thresholdLevel(0.05f), isActive(false)
{
}

SoftClipProcessor::~SoftClipProcessor()
{

}

void SoftClipProcessor::setThreshold(float t)
{
    thresholdLevel = t;
}

void SoftClipProcessor::setActive(bool a) 
{
    isActive = a;
}

void SoftClipProcessor::setDrive(float d)
{
    float driveAmount = std::clamp(d, 1.0f, 7.0f);
    thresholdLevel = 0.1f / driveAmount;
}

float SoftClipProcessor::processSample(float x)
{
    if (!isActive)
    {
        return x;
    }

    float absx = std::abs(x);
    if (absx <= thresholdLevel)
    {
        return x;
    }
    // soft cubic knee: y = sign(x) * (a*x + b*x^3)
    // choose a and b so function is continuous at threshold
    float a = 0.8f;
    float b = 0.2f;
    float y = a * x + b * x * x * x;
    
    return y;

}