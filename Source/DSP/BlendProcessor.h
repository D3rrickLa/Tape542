/*
  ==============================================================================

    BlendProcessor.h
    Created: 11 Oct 2025 10:08:39pm
    Author:  Gen3r

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class BlendProcessor  : public juce::Component
{
public:
    BlendProcessor();
    ~BlendProcessor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BlendProcessor)
};
