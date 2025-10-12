/*
  ==============================================================================

    BlendProcessor.cpp
    Created: 11 Oct 2025 10:08:39pm
    Author:  Gen3r

  ==============================================================================
*/

#include <JuceHeader.h>
#include "BlendProcessor.h"

//==============================================================================
BlendProcessor::BlendProcessor()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

BlendProcessor::~BlendProcessor()
{
}

void BlendProcessor::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (14.0f));
    g.drawText ("BlendProcessor", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void BlendProcessor::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
