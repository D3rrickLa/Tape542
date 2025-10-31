/*
  ==============================================================================

    IpsProcessor.h
    Created: 13 Oct 2025 10:36:42pm
    Author:  Gen3r

  ==============================================================================
*/

#pragma once
enum IPSMode { IPS_7_5, IPS_15, IPS_30 };

class BiQuad
{
public:
	//BiQuad();
	//~BiQuad();
    void setCoeffs(float b0, float b1, float b2, float a1, float a2);
    float process(float x);

private:
    float b0 = 1, b1 = 0, b2 = 0, a1 = 0, a2 = 0;
    float x1 = 0, x2 = 0, y1 = 0, y2 = 0;
};

class IPSProcessor
{
public:
	IPSProcessor();
	~IPSProcessor();
    void prepare(double sr);
    void setMode(IPSMode m);
    float processSample(float x);


private:
    IPSMode mode;
    double sampleRate;
    BiQuad bqLow7_5, bqHi7_5, bqLow15, bqHi15, bqLow30, bqHi30;

    void buildPresets();
    bool isStandardSampleRate(float sr);
};
