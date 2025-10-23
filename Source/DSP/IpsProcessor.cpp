/*
  ==============================================================================

    IpsProcessor.cpp
    Created: 13 Oct 2025 10:36:42pm
    Author:  Gen3r

  ==============================================================================
*/

#include "IpsProcessor.h"
void BiQuad::setCoeffs(float b0, float b1, float b2, float a1, float a2)
{
    this->b0 = b0; this->b1 = b1; this->b2 = b2; this->a1 = a1; this->a2 = a2;
}
float BiQuad::process(float x)
{
    float y = b0 * x + b1 * x1 + b2 * x2 - a1 * y1 - a2 * y2;
    x2 = x1; x1 = x;
    y2 = y1; y1 = y;
    return y;
}

IPSProcessor::IPSProcessor()
    : mode(IPS_15), sampleRate(44100.0)
{
    buildPresets();
}

IPSProcessor::~IPSProcessor()
{

}

void IPSProcessor::prepare(double sr)
{
    if (isStandardSampleRate(sr))
    {
        sampleRate = sr;
        buildPresets();
    }
}

void IPSProcessor::setMode(IPSMode m)
{
    mode = m;
}

float IPSProcessor::processSample(float x)
{
    if (mode == IPS_7_5)
    {
        return bqLow7_5.process(bqHi7_5.process(x));
    }
    else if (mode == IPS_15)
    {
        return bqLow15.process(bqHi15.process(x));
    }
    else
    {
        return bqLow30.process(bqHi30.process(x));
    }
}

bool IPSProcessor::isStandardSampleRate(float sr)
{
    switch (int(sr)) {
    case 44100: case 48000: case 88200: case 96000: case 192000: return true;
    default: return false;
    }
}

void IPSProcessor::buildPresets()
{
    // 7.5 IPS: flat lows, HF extension
    bqLow7_5.setCoeffs(1.f, 0.0f, 0.0f, 0.0f, 0.0f);
    bqHi7_5.setCoeffs(1.47f, 0.0, 0.0f, 0.0f, 0.0f);

    // 15 IPS: small low boost + HF attenuation
    bqLow15.setCoeffs(1.2f, 0.0f, 0.0f, 0.0f, 0.0f);
    bqHi15.setCoeffs(0.8f, 0.0f, 0.0f, 0.0f, 0.0f);

    // 30 IPS: flatter low, slight HF extension
    bqLow30.setCoeffs(1.05f, 0, 0, 0, 0);
    bqHi30.setCoeffs(1.1f, 0, 0, 0, 0);
}