#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "OvertonePassFilter.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
	bool canPlaySound(juce::SynthesiserSound* sound) override;
	void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
	void stopNote(float velocity, bool allowTailOff) override;
	void pitchWheelMoved(int newPitchWheelValue) override;
	void controllerMoved(int controllerNumber, int newControllerValue) override;
	void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
	void setParameters(juce::ADSR::Parameters adsrParameters, float synth_gain);
	void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
	int getCurrentMidiNoteNumber() const;
private:
	juce::Random random;
	OvertonePassFilter overtonePassFilter;
	juce::AudioBuffer<float> synthBuffer;
	juce::ADSR adsr;
	juce::ADSR::Parameters adsrParameters;
	juce::dsp::Oscillator<float> osc{ [](float x) { return std::sin(x); } };
	juce::dsp::Gain<float> gain;
	int currentMidiNoteNumber{ -1 };
	bool isPrepared{ false };
};