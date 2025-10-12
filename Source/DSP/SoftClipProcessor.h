/*
  ==============================================================================

    SoftClipProcessor.h
    Created: 11 Oct 2025 10:08:27pm
    Author:  Gen3r

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SoftClipProcessor  : public juce::Component
{
public:
    SoftClipProcessor();
    ~SoftClipProcessor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoftClipProcessor)
};
