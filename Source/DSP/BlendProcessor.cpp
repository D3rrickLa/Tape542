/*
  ==============================================================================

    BlendProcessor.cpp
    Created: 13 Oct 2025 10:36:31pm
    Author:  Gen3r

  ==============================================================================
*/

#include "BlendProcessor.h"
#include <cmath>
#include <algorithm>
#define M_PI 3.14159265358979323846

BlendProcessor::BlendProcessor()
    :blend(0.5f)
{
}

BlendProcessor::~BlendProcessor()
{
}

void BlendProcessor::setBlend(float v)
{
    blend = std::clamp(v, 0.0f, 1.0f);
}

float BlendProcessor::processSample(float dry, float wet)
{
    float a = cos(blend * (float)M_PI * 0.5f);
    float b = sin(blend * (float)M_PI * 0.5f);
    return dry * a + wet * b;
}
