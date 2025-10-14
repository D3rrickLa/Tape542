/*
  ==============================================================================

    TrimProcessor.h
    Created: 13 Oct 2025 10:11:48pm
    Author:  Gen3r

  ==============================================================================
*/

#pragma once
class TrimProcessor
{
public:
	TrimProcessor();
	~TrimProcessor();

    void prepare(double sr);
    void setTrimDb(float db);

    float processSample(float x);

private:
    float trimDb;  
    float gainLinear; 
    double sampleRate;

    void updateGain();
};
