#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
	return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
	overtonePassFilter.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
	thiccOvertonePassFilter.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
	osc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    adsr.noteOn();
    currentMidiNoteNumber = midiNoteNumber;
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
	adsr.noteOff();
    if (!allowTailOff || !adsr.isActive())
        clearCurrentNote();
        currentMidiNoteNumber = -1;
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
	juce::dsp::ProcessSpec spec;
	spec.maximumBlockSize = samplesPerBlock;
	spec.sampleRate = sampleRate;
	spec.numChannels = outputChannels;

	synthBuffer.setSize(spec.numChannels, spec.maximumBlockSize);
	noiseBuffer.setSize(spec.numChannels, spec.maximumBlockSize);
	oscBuffer.setSize(spec.numChannels, spec.maximumBlockSize);
	juverbBuffer.setSize(spec.numChannels, spec.maximumBlockSize);
	irBuffer.setSize(spec.numChannels, spec.maximumBlockSize);
	thiccBuffer.setSize(spec.numChannels, spec.maximumBlockSize);
	sumBuffer.setSize(spec.numChannels, spec.maximumBlockSize);

	osc.prepare(spec);
	overtonePassFilter.prepare(spec);
	thiccOvertonePassFilter.prepare(spec);
	adsr.reset();
	filterAdsr.reset();
	adsr.setSampleRate(sampleRate);
	filterAdsr.setSampleRate(sampleRate);
	juVerb.prepare(spec);
	conv.prepare(spec);

	synthDryGain.reset();
	thiccGain.reset();
    outputGain.reset();

	synthDryGain.prepare(spec);
	thiccGain.prepare(spec);
	outputGain.prepare(spec);

	isPrepared = true;
}

void SynthVoice::setParameters(
		juce::ADSR::Parameters adsrParameters,
		juce::ADSR::Parameters filterAdsrParameters,
		float juverbSize,
		float juverbDamping,
		float juverbWidth,
		bool juverbFreeze,
		float juverbDry,
		float juverbWet,
		float irDry,
		float irWet,
		float synth_gain,
		float thicc_gain,
		float output_gain
		)
{
    adsr.setParameters(adsrParameters);
	filterAdsr.setParameters(filterAdsrParameters);
	juVerb.setParameters(juverbSize, juverbDamping, juverbWidth, juverbFreeze, juverbDry/100, juverbWet/100);
	conv.setParameters(irDry, irWet);
	synthDryGain.setGainLinear(synth_gain/100.);
	thiccGain.setGainLinear(thicc_gain/100.);
	outputGain.setGainDecibels(output_gain);
}

// renderNextBlock =======================================================================================
void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
	jassert(isPrepared);

    if (!isVoiceActive())
        return;

	synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
	noiseBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
	oscBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
	juverbBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
	irBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
	thiccBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
	sumBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);

    synthBuffer.clear();
	noiseBuffer.clear();
	oscBuffer.clear();
	juverbBuffer.clear();
	irBuffer.clear();
	thiccBuffer.clear();
	sumBuffer.clear();

    for (int ch = 0; ch < noiseBuffer.getNumChannels(); ++ch)
    {
        auto* buffer = noiseBuffer.getWritePointer(ch, 0);

        for (int s = 0; s < noiseBuffer.getNumSamples(); ++s)
        {
            buffer[s] = random.nextFloat() * 0.25f - 0.125f;
        }
    }

	overtonePassFilter.process(noiseBuffer);

	juce::dsp::AudioBlock<float> oscBlock(oscBuffer);
	osc.process(juce::dsp::ProcessContextReplacing<float>(oscBlock));

	// sum noise and osc into synth
	for (int ch = 0; ch < synthBuffer.getNumChannels(); ++ch)
	{
		auto* noiseBufferPtr = noiseBuffer.getReadPointer(ch);
		auto* oscBufferPtr = oscBuffer.getReadPointer(ch);
		auto* synthBufferPtr = synthBuffer.getWritePointer(ch);
		for (int s = 0; s < synthBuffer.getNumSamples(); ++s)
		{
			synthBufferPtr[s] = (noiseBufferPtr[s] + oscBufferPtr[s]/8.0f) / 2.0f;
		}
	}

    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());

	// thicc'ning
	juverbBuffer = synthBuffer;
	juVerb.process(juverbBuffer);

	irBuffer = synthBuffer;
	conv.process(irBuffer);

	// sum juverb and ir into thicc
	for (int ch = 0; ch < thiccBuffer.getNumChannels(); ++ch)
	{
		auto* juverbBufferPtr = juverbBuffer.getReadPointer(ch);
		auto* irBufferPtr = irBuffer.getReadPointer(ch);
		auto* thiccBufferPtr = thiccBuffer.getWritePointer(ch);
		for (int s = 0; s < thiccBuffer.getNumSamples(); ++s)
		{
			thiccBufferPtr[s] = juverbBufferPtr[s] + irBufferPtr[s]*8.0;
		}
	}

	thiccOvertonePassFilter.process(thiccBuffer);

	// saturate thiccBuffer
	for (int ch = 0; ch < thiccBuffer.getNumChannels(); ++ch)
	{
		auto* thiccBufferPtr = thiccBuffer.getWritePointer(ch);
		for (int s = 0; s < thiccBuffer.getNumSamples(); ++s)
		{
			thiccBufferPtr[s] = std::tanh(thiccBufferPtr[s]);
		}
	}

	//filterAdsr.applyEnvelopeToBuffer(thiccBuffer, 0, thiccBuffer.getNumSamples());
	adsr.applyEnvelopeToBuffer(thiccBuffer, 0, thiccBuffer.getNumSamples());

	juce::dsp::AudioBlock<float> thiccBlock(thiccBuffer);

	juce::dsp::AudioBlock<float> synthBlock(synthBuffer);
	synthDryGain.process(juce::dsp::ProcessContextReplacing<float>(synthBlock));
	thiccGain.process(juce::dsp::ProcessContextReplacing<float>(thiccBlock));

	// merge synth and thicc
	for (int ch = 0; ch < sumBuffer.getNumChannels(); ++ch)
	{
		auto* synthBufferPtr = synthBuffer.getReadPointer(ch);
		auto* thiccBufferPtr = thiccBuffer.getReadPointer(ch);
		auto* sumBufferPtr = sumBuffer.getWritePointer(ch);
		for (int s = 0; s < sumBuffer.getNumSamples(); ++s)
		{
			sumBufferPtr[s] = (synthBufferPtr[s] + thiccBufferPtr[s]) / 2.0f;
		}
	}

	juce::dsp::AudioBlock<float> sumBlock(sumBuffer);
	outputGain.process(juce::dsp::ProcessContextReplacing<float>(sumBlock));

    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, sumBuffer, channel, 0, numSamples);

        if (!adsr.isActive())
            clearCurrentNote();
    }
}
// =========================================================================================================

int SynthVoice::getCurrentMidiNoteNumber() const
{
	return currentMidiNoteNumber;
}

void SynthVoice::setIR(juce::File file)
{
	conv.reset();
	conv.loadImpulseResponse(file, juce::dsp::Convolution::Stereo::yes, juce::dsp::Convolution::Trim::yes, 0);
}