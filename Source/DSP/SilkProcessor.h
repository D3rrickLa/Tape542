/*
  ==============================================================================

    SilkProcessor.h
    Created: 11 Oct 2025 10:09:11pm
    Author:  Gen3r

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SilkProcessor  : public juce::Component
{
public:
    SilkProcessor();
    ~SilkProcessor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SilkProcessor)
};
