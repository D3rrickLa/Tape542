/*
  ==============================================================================

    SoftClipProcessor.h
    Created: 13 Oct 2025 10:36:19pm
    Author:  Gen3r

  ==============================================================================
*/

#pragma once
class SoftClipProcessor
{
public:
	SoftClipProcessor();
	~SoftClipProcessor();

    void setThreshold(float t);
    void setActive(bool a);
    void setDrive(float d); // will take in saturation drive and respond accordingly

    float processSample(float x);


private:
    float thresholdLevel;
    bool isActive;
};
