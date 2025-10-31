/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DSP/TrimProcessor.h"
#include "DSP/SaturationProcessor.h"
#include "DSP/SoftClipProcessor.h"
#include "DSP/BlendProcessor.h"
#include "DSP/IpsProcessor.h"
#include "DSP/SilkProcessor.h"
#include "DSP/LevelMeterProcessor.h"
#include "DSP/DriveMeterProcessor.h"

//==============================================================================
/**
*/
class Tape542AudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    Tape542AudioProcessor();
    ~Tape542AudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    // audio plugins needs parameteres to control the DSP, we just this to coordinate the sync of there paremters to the GUI and the paremters, GUI attaches to this 
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    juce::AudioProcessorValueTreeState apvts{*this, nullptr, "Parameters", createParameterLayout()};

private:
    //==============================================================================

  


    using Filter = juce::dsp::IIR::Filter<float>;

    // DSP Modules //

    // Input → Trim → Saturation (with soft clip) → IPS filter → Blend → Silk (Red/Blue + Texture) → Output //
    TrimProcessor trimProcessor;
    SaturationProcessor saturationProcessor;
    SoftClipProcessor softClipProcessor;
    BlendProcessor blendProcessor;
    IPSProcessor ipsProcessor;
    SilkProcessor silkProcessor;
    LevelMeterProcessor levelMeter;
    DriveMeterProcessor driveMeter;

    void updateParameters(); // internal helper


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Tape542AudioProcessor)
};
