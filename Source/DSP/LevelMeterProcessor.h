/*
  ==============================================================================

    LevelMeterProcessor.h
    Created: 11 Oct 2025 10:09:38pm
    Author:  Gen3r

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class LevelMeterProcessor  : public juce::Component
{
public:
    LevelMeterProcessor();
    ~LevelMeterProcessor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LevelMeterProcessor)
};
