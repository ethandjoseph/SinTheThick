#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Components/VerticalMeter.h"

class SinthethiccAudioProcessorEditor : public juce::AudioProcessorEditor, public juce::Timer
{
public:
    SinthethiccAudioProcessorEditor (SinthethiccAudioProcessor&);
    ~SinthethiccAudioProcessorEditor() override;

	void timerCallback() override;
    void paint (juce::Graphics&) override;
    void resized() override;

	void showSynthVoiceEditorWindow();

	void showReverberationEditorWindow();

	VerticalGradientMeter inputVUMeterLeft, inputVUMeterRight, outputVUMeterLeft, outputVUMeterRight;

private:
    
    juce::Label inputNoteLabel;
	juce::Label inputNoteValueLabel;
    
    juce::Label voicingLabel;

    juce::TextButton synthVoiceButton;
	juce::TextButton reverbButton;

    juce::Label adsrLabel;
	juce::Slider synthAttackSlider;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> synthAttackSliderAttachment;
	juce::Slider synthDecaySlider;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> synthDecaySliderAttachment;
	juce::Slider synthSustainSlider;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> synthSustainSliderAttachment;
	juce::Slider synthReleaseSlider;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> synthReleaseSliderAttachment;

	juce::Label synthGainLabel;
	juce::Slider synthGainSlider;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> synthGainSliderAttachment;

	juce::Label saturationLabel;
	juce::Slider saturationSlider;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> saturationSliderAttachment;

	juce::Label thiccGainLabel;
	juce::Slider thiccGainSlider;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> thiccGainSliderAttachment;

	juce::Label outputGainLabel;
	juce::Slider outputGainSlider;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> outputGainSliderAttachment;

    SinthethiccAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SinthethiccAudioProcessorEditor)
};