/*
  ==============================================================================

    DriveMeterProcessor.h
    Created: 13 Oct 2025 10:38:07pm
    Author:  Gen3r

  ==============================================================================
*/

#pragma once
class DriveMeterProcessor
{
public:
    DriveMeterProcessor();
    ~DriveMeterProcessor();

    void prepare(float sr);
    void setAttackMs(float ms);
    void setReleaseMs(float ms);

    float processSample(float x);
    float getNormalizedLevel();
    int getLedSegmentIndex(int);
private:
    float sampleRate;
    float attackMs, releaseMs;
    float attackCoeff, releaseCoeff;
    float state;

    void updateCoeffs();
    bool isStandardSampleRate(float sr);

};
