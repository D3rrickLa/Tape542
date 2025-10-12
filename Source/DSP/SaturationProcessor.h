/*
  ==============================================================================

    SaturationProcessor.h
    Created: 11 Oct 2025 10:08:10pm
    Author:  Gen3r

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SaturationProcessor  : public juce::Component
{
public:
    SaturationProcessor();
    ~SaturationProcessor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SaturationProcessor)
};
