#pragma once
#include <JuceHeader.h>

class SynthVoiceEditor  : public juce::Component
{
public:
    SynthVoiceEditor(juce::AudioProcessorValueTreeState& apvts);
    ~SynthVoiceEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
	juce::Slider oscGainSlider;
	juce::Slider noiseGainSlider;

	juce::Label oscGainLabel;
	juce::Label noiseGainLabel;

	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> oscGainSliderAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> noiseGainSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthVoiceEditor)
};