/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
Tape542AudioProcessor::Tape542AudioProcessor()
   
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
     ),  apvts(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
    
}

Tape542AudioProcessor::~Tape542AudioProcessor()
{
}

//==============================================================================
const juce::String Tape542AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Tape542AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Tape542AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Tape542AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Tape542AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Tape542AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Tape542AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Tape542AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Tape542AudioProcessor::getProgramName (int index)
{
    return {};
}

void Tape542AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Tape542AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    trimProcessor.prepare(sampleRate);
    saturationProcessor.prepare(sampleRate);
    //softClipProcessor.prepare(sampleRate);
    ipsProcessor.prepare(sampleRate);
    //blendProcessor.prepare(sampleRate);
    silkProcessor.prepare(sampleRate);
}

void Tape542AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Tape542AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Tape542AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

    updateParameters();

    const int totalNumInputChannels = getTotalNumInputChannels();

    for (int ch = 0; ch < totalNumInputChannels; ++ch)
    {
        auto* channelData = buffer.getWritePointer(ch);

        for (int n = 0; n < buffer.getNumSamples(); ++n)
        {
            float drySample = channelData[n];
            float x = drySample;

            x = trimProcessor.processSample(x);
            x = saturationProcessor.processSample(x);
            x = softClipProcessor.processSample(x);
            x = ipsProcessor.processSample(x);

            // blend between dry and wet
            x = blendProcessor.processSample(drySample, x);

            x = silkProcessor.processSample(x);

            channelData[n] = x;
        }
    }

}

//==============================================================================
bool Tape542AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Tape542AudioProcessor::createEditor()
{
    //return new Tape542AudioProcessorEditor (*this);
    return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void Tape542AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Tape542AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

juce::AudioProcessorValueTreeState::ParameterLayout Tape542AudioProcessor::createParameterLayout()
{
    // define what we want
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    // we are defining what to add for the plugin here
    // layout.add(), depending on what type of 'GUI' we are making we will use a float, etc.
    /*
        based on the Rupert Neve Design, we have the following things to implement:
        TRIM -> +/- 12 dB adjustment of level on incoming signal levels, prior to the tape circut
    */



    layout.add(std::make_unique<juce::AudioParameterBool>("tapeEnable", "Tape Enable", true)); // like or on/off/bypass button. The "Tape Effect In"
    layout.add(std::make_unique<juce::AudioParameterFloat>("trim", "Trim", juce::NormalisableRange<float>(-12.f, 12.f, 0.1f), 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("saturation", "Saturation", juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.05f));
    layout.add(std::make_unique<juce::AudioParameterBool>("softClip", "Soft Clip", false));
    layout.add(std::make_unique<juce::AudioParameterChoice>("ips", "IPS", juce::StringArray{"7.5 IPS", "15 IPS", "30, IPS"}, 1));
    layout.add(std::make_unique<juce::AudioParameterFloat>("blend", "Blend", juce::NormalisableRange<float>(0.0f, 1.f, 0.01f), 1.f));
    layout.add(std::make_unique<juce::AudioParameterChoice>("silkMode", "Silk Mode", juce::StringArray{ "OFF", "RED", "BLUE" }, 0));
    layout.add(std::make_unique<juce::AudioParameterFloat>("texture", "Texture", 0.0f, 1.0f, 0.5f));


    layout.add(std::make_unique<juce::AudioParameterBool>("stereoLink", "Stereo Link", true));
        
    return layout;
}

void Tape542AudioProcessor::updateParameters()
{
    trimProcessor.setTrimDb(apvts.getRawParameterValue("trim")->load());
    saturationProcessor.setDrive(apvts.getRawParameterValue("saturation")->load());
    softClipProcessor.setActive(apvts.getRawParameterValue("softClip")->load() > 0.5f);
    
    blendProcessor.setBlend(apvts.getRawParameterValue("blend")->load());


    // convert float -" int -" enum
    int ipsIndex = static_cast<int>(apvts.getRawParameterValue("ips")->load());
    switch (ipsIndex)
    {
        case 0: ipsProcessor.setMode(IPS_7_5); break;
        case 1: ipsProcessor.setMode(IPS_15); break;
        case 2: ipsProcessor.setMode(IPS_30); break;
     }

    int silkIndex = static_cast<int>(apvts.getRawParameterValue("silkMode")->load());
    switch (silkIndex)
    {
        case 1:  silkProcessor.setMode(SILK_RED);  break;
        case 2:  silkProcessor.setMode(SILK_BLUE); break;
        default: silkProcessor.setMode(SILK_OFF);  break;
    }

    silkProcessor.setTexture(apvts.getRawParameterValue("texture")->load());
 
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Tape542AudioProcessor();
}
