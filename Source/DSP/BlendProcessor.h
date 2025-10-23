/*
  ==============================================================================

    BlendProcessor.h
    Created: 13 Oct 2025 10:36:31pm
    Author:  Gen3r

  ==============================================================================
*/

#pragma once
class BlendProcessor
{
public:
	BlendProcessor();
	~BlendProcessor();
    void setBlend(float v);
    float processSample(float dry, float wet);

private:
    float blend;
};
