/*
  ==============================================================================

    DriverMeterProcessor.h
    Created: 11 Oct 2025 10:09:25pm
    Author:  Gen3r

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class DriveMeterProcessor : public juce::Component
{
public:
    DriveMeterProcessor();
    ~DriveMeterProcessor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DriveMeterProcessor)
};
