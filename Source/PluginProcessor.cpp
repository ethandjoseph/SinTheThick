#include "PluginProcessor.h"
#include "PluginEditor.h"

SinthethiccAudioProcessor::SinthethiccAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
    apvts(*this, nullptr, "Parameters", createParameterLayout())
#endif
{
    synth.addVoice(new SynthVoice());
    synth.addSound(new SynthSound());
}

SinthethiccAudioProcessor::~SinthethiccAudioProcessor()
{
}

const juce::String SinthethiccAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SinthethiccAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SinthethiccAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SinthethiccAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SinthethiccAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SinthethiccAudioProcessor::getNumPrograms()
{
    return 1;
}

int SinthethiccAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SinthethiccAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SinthethiccAudioProcessor::getProgramName (int index)
{
    return {};
}

void SinthethiccAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

void SinthethiccAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
}

void SinthethiccAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SinthethiccAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

// Process Block ==============================================================================
void SinthethiccAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    setParameters();
    
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}
// ============================================================================================

bool SinthethiccAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* SinthethiccAudioProcessor::createEditor()
{
    return new SinthethiccAudioProcessorEditor (*this);
}

void SinthethiccAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
}

void SinthethiccAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SinthethiccAudioProcessor();
}

// Custom Methods ==============================================================================

int SinthethiccAudioProcessor::getCurrentMidiNoteNumber() const
{
    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            if (voice->isVoiceActive())
                return voice->getCurrentMidiNoteNumber();
        }
    }
    return -1;
}

void SinthethiccAudioProcessor::setIR(juce::File file)
{
    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->setIR(file);
        }
    }
}

juce::AudioProcessorValueTreeState::ParameterLayout SinthethiccAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float> { 0.1f, 3.0f, 0.1f }, 0.4f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERATTACK", "Filter Attack", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01f }, 0.01f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERDECAY", "Filter Decay", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.1f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERSUSTAIN", "Filter Sustain", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.1f }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERRELEASE", "Filter Release", juce::NormalisableRange<float> { 0.0f, 3.0f, 0.1f }, 0.1f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("JUVERB_ROOM_SIZE", "Room Size", 0.0f, 1.0f, 0.4f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("JUVERB_DAMPING", "Damping", 0.0f, 1.0f, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("JUVERB_WIDTH", "Width", 0.0f, 1.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterBool>("JUVERB_FREEZE", "Freeze", false));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("JUVERB_DRY", "Ju Dry", 0.0f, 100.0f, 00.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("JUVERB_WET", "Ju Wet", 0.0f, 100.0f, 100.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("IR_DRY", "IR Dry", 0.0f, 100.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("IR_WET", "IR Wet", 0.0f, 100.0f, 100.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("SYNTH_GAIN", "Synth Dry", 0.0f, 100.0f, 100.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("THICC_GAIN", "Thicc Wet", 0.0f, 100.0f, 50.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("THICC_SATURATION", "Thicc Saturation", juce::NormalisableRange<float> { 0.0f, 100.0f, 1.f }, 50.f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("OUTPUT_GAIN", "Output Level", juce::NormalisableRange<float> { -60.0f, 18.0f, 0.1f }, 0.f, "dB"));

    return { params.begin(), params.end() };
}

void SinthethiccAudioProcessor::setParameters()
{
    juce::ADSR::Parameters adsrParameters;
    adsrParameters.attack = *apvts.getRawParameterValue("ATTACK");
    adsrParameters.decay = *apvts.getRawParameterValue("DECAY");
    adsrParameters.sustain = *apvts.getRawParameterValue("SUSTAIN");
    adsrParameters.release = *apvts.getRawParameterValue("RELEASE");

	juce::ADSR::Parameters filterAdsrParameters;
	filterAdsrParameters.attack = *apvts.getRawParameterValue("FILTERATTACK");
	filterAdsrParameters.decay = *apvts.getRawParameterValue("FILTERDECAY");
	filterAdsrParameters.sustain = *apvts.getRawParameterValue("FILTERSUSTAIN");
	filterAdsrParameters.release = *apvts.getRawParameterValue("FILTERRELEASE");

	float juverbSize = *apvts.getRawParameterValue("JUVERB_ROOM_SIZE");
	float juverbDamping = *apvts.getRawParameterValue("JUVERB_DAMPING");
	float juverbWidth = *apvts.getRawParameterValue("JUVERB_WIDTH");
	bool juverbFreeze = *apvts.getRawParameterValue("JUVERB_FREEZE");
	float juverbDry = *apvts.getRawParameterValue("JUVERB_DRY");
	float juverbWet = *apvts.getRawParameterValue("JUVERB_WET");

	float irDry = *apvts.getRawParameterValue("IR_DRY");
	float irWet = *apvts.getRawParameterValue("IR_WET");

	float synthGain = *apvts.getRawParameterValue("SYNTH_GAIN");
	float thiccGain = *apvts.getRawParameterValue("THICC_GAIN");
	float thiccSaturationPercent = *apvts.getRawParameterValue("THICC_SATURATION");

    float gain = *apvts.getRawParameterValue("OUTPUT_GAIN");
    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->setParameters(
                adsrParameters,
                filterAdsrParameters,
				juverbSize,
				juverbDamping,
				juverbWidth,
				juverbFreeze,
				juverbDry,
				juverbWet,
				irDry,
				irWet,
				synthGain,
                thiccSaturationPercent,
				thiccGain,
                gain
                );
        }
    }
}