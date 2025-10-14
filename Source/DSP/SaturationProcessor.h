/*
  ==============================================================================

    SaturationProcessor.h
    Created: 13 Oct 2025 10:35:51pm
    Author:  Gen3r

  ==============================================================================
*/

#pragma once
class SaturationProcessor
{
public:
	SaturationProcessor();
	~SaturationProcessor();

    void prepare(float sr);
    void setDrive(float d);
    void setPreEmphasisHz(float hz);
    float processSample(float x);
 

private:
    float drive;
    float preEmphCutHz;
    double sampleRate;

    // states for simple filteres
    float hpSate, hp_x1;
    float lpState;

    // coeffs
    float hp_a0, hp_a1;
    float hp_b0, lp_b1;

    void updateCoeffs();

    float makeupGain();
};
