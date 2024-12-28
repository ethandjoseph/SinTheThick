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
	juce::Label oscGainLabel;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> oscGainSliderAttachment;

	juce::Slider oscDelaySlider;
	juce::Label oscDelayLabel;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> oscDelaySliderAttachment;
	
	juce::Slider noiseGainSlider;
	juce::Label noiseGainLabel;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> noiseGainSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthVoiceEditor)
};