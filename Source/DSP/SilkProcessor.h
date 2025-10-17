/*
  ==============================================================================

    SilkProcessor.h
    Created: 13 Oct 2025 10:37:15pm
    Author:  Gen3r

  ==============================================================================
*/

#pragma once
enum SilkMode { SILK_OFF, SILK_RED, SILK_BLUE };

class SilkProcessor
{
public:
	SilkProcessor();
	~SilkProcessor();

	void prepare(float sr);
	void setMode(SilkMode m);
	void setTexture(float t);
	float processSample(float input);

private:
	SilkMode mode;
	float texture;
	float sampleRate;
	OnePoleBandpass bpRed, bpBlue;
};

class OnePoleBandpass
{
public:
	OnePoleBandpass();
	~OnePoleBandpass();

	void set(float centerHz, float qVal, float sr);
	float process(float x);

private:
	float center, q, q, alpha;
	float sampleRate;
	float lpState;
};
