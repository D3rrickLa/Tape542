/*
  ==============================================================================

    TrimProcessor.h
    Created: 11 Oct 2025 10:06:39pm
    Author:  Gen3r

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class TrimProcessor  : public juce::Component
{
public:
    TrimProcessor();
    ~TrimProcessor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrimProcessor)
};
