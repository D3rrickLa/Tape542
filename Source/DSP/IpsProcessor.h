/*
  ==============================================================================

    IpsProcessor.h
    Created: 11 Oct 2025 10:08:59pm
    Author:  Gen3r

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class IpsProcessor  : public juce::Component
{
public:
    IpsProcessor();
    ~IpsProcessor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IpsProcessor)
};
