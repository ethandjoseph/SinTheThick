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
	sinAdsr.noteOn();
    currentMidiNoteNumber = midiNoteNumber;
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
	adsr.noteOff();
	sinAdsr.noteOff();
	juVerb.reset();
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
	oscGain.reset();
	oscGain.prepare(spec);
	overtonePassFilter.prepare(spec);
	thiccOvertonePassFilter.prepare(spec);
	adsr.reset();
	sinAdsr.reset();
	filterAdsr.reset();
	adsr.setSampleRate(sampleRate);
	sinAdsr.setSampleRate(sampleRate);
	filterAdsr.setSampleRate(sampleRate);
	juVerb.prepare(spec);
	conv.prepare(spec);

	saturationGain.reset();
	saturationGain.prepare(spec);

	//waveshaper.reset();
	waveshaper.prepare(spec);

	saturationCompensationGain.reset();
	saturationCompensationGain.prepare(spec);

	synthDryGain.reset();
	thiccGain.reset();

	synthDryGain.prepare(spec);
	thiccGain.prepare(spec);

	isPrepared = true;
}

void SynthVoice::setParameters(
		juce::ADSR::Parameters adsrParameters,
		juce::ADSR::Parameters filterAdsrParameters,
		float newSinDelay,
		float juverbSize,
		float juverbDamping,
		float juverbWidth,
		bool juverbFreeze,
		float juverbDry,
		float juverbWet,
		float irDry,
		float irWet,
		float balance,
		float newSinGain,
		float newNoiseGain,
		float synth_gain,
		float thicc_saturation_gain,
		float thicc_gain
		)
{
    adsr.setParameters(adsrParameters);
	sinAdsrParameters.attack = adsrParameters.attack + newSinDelay;
	sinAdsrParameters.decay = adsrParameters.decay;
	sinAdsrParameters.sustain = adsrParameters.sustain;
	sinAdsrParameters.release = adsrParameters.release;
	sinAdsr.setParameters(sinAdsrParameters);
	filterAdsr.setParameters(filterAdsrParameters);
	juVerb.setParameters(juverbSize, juverbDamping, juverbWidth, juverbFreeze, juverbDry/100, juverbWet/100);
	conv.setParameters(irDry, irWet);
	oscGain.setGainLinear(newSinGain);
	noiseGain = newNoiseGain;
	synthDryGain.setGainLinear(synth_gain/100.);
	saturationGain.setGainDecibels(thicc_saturation_gain);
	saturationCompensationGain.setGainDecibels(-thicc_saturation_gain);
	thiccGain.setGainLinear(thicc_gain/100.);
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
			buffer[s] *= noiseGain*4;
        }
    }

	overtonePassFilter.process(noiseBuffer);

	juce::dsp::AudioBlock<float> oscBlock(oscBuffer);
	osc.process(juce::dsp::ProcessContextReplacing<float>(oscBlock));
	oscGain.process(juce::dsp::ProcessContextReplacing<float>(oscBlock));
	sinAdsr.applyEnvelopeToBuffer(oscBuffer, 0, oscBuffer.getNumSamples());

	// sum noise and osc into synth
	for (int ch = 0; ch < synthBuffer.getNumChannels(); ++ch)
	{
		auto* noiseBufferPtr = noiseBuffer.getReadPointer(ch);
		auto* oscBufferPtr = oscBuffer.getReadPointer(ch);
		auto* synthBufferPtr = synthBuffer.getWritePointer(ch);
		for (int s = 0; s < synthBuffer.getNumSamples(); ++s)
		{
			synthBufferPtr[s] = (noiseBufferPtr[s] + oscBufferPtr[s]) / 2.0f;
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
		juverbBalanceGain = balance;
		irBalanceGain = 1.0f - balance;
		for (int s = 0; s < thiccBuffer.getNumSamples(); ++s)
		{
			thiccBufferPtr[s] = juverbBufferPtr[s]*juverbBalanceGain + irBufferPtr[s]*irBalanceGain*8.0;
		}
	}

	thiccOvertonePassFilter.process(thiccBuffer);

	juce::dsp::AudioBlock<float> thiccBlock(thiccBuffer);
	saturationGain.process(juce::dsp::ProcessContextReplacing<float>(thiccBlock));
	
	/*std::vector<float> beforeProcessing;
	for (int ch = 0; ch < thiccBuffer.getNumChannels(); ++ch)
	{
		auto* thiccBufferPtr = thiccBuffer.getReadPointer(ch);
		beforeProcessing.insert(beforeProcessing.end(), thiccBufferPtr, thiccBufferPtr + thiccBuffer.getNumSamples());
	}*/

	waveshaper.process(juce::dsp::ProcessContextReplacing<float>(thiccBlock));

	/*for (int ch = 0; ch < thiccBuffer.getNumChannels(); ++ch)
	{
		auto* thiccBufferPtr = thiccBuffer.getReadPointer(ch);
		for (int s = 0; s < thiccBuffer.getNumSamples(); ++s)
		{
			jassert(thiccBufferPtr[s] != beforeProcessing[s + ch * thiccBuffer.getNumSamples()]);
		}
	}*/

	saturationCompensationGain.process(juce::dsp::ProcessContextReplacing<float>(thiccBlock));

	//filterAdsr.applyEnvelopeToBuffer(thiccBuffer, 0, thiccBuffer.getNumSamples());
	adsr.applyEnvelopeToBuffer(thiccBuffer, 0, thiccBuffer.getNumSamples());

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