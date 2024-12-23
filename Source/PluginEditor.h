#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class SinthethiccAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SinthethiccAudioProcessorEditor (SinthethiccAudioProcessor&);
    ~SinthethiccAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // ADSR sliders
	juce::Slider synthAttackSlider;
	juce::Slider synthDecaySlider;
	juce::Slider synthSustainSlider;
	juce::Slider synthReleaseSlider;
	juce::Label synthAttackLabel;
	juce::Label synthDecayLabel;
	juce::Label synthSustainLabel;
	juce::Label synthReleaseLabel;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> synthAttackSliderAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> synthDecaySliderAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> synthSustainSliderAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> synthReleaseSliderAttachment;
	// juverb sliders
	juce::Slider juverbSizeSlider;
	juce::Slider juverbDampingSlider;
	juce::Slider juverbWidthSlider;
	juce::ToggleButton juverbFreezeButton;
	juce::Slider juverbDrySlider;
	juce::Slider juverbWetSlider;
	juce::Label juverbSizeLabel;
	juce::Label juverbDampingLabel;
	juce::Label juverbWidthLabel;
	juce::Label juverbDryLabel;
	juce::Label juverbWetLabel;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> juverbSizeSliderAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> juverbDampingSliderAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> juverbWidthSliderAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> juverbFreezeButtonAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> juverbDrySliderAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> juverbWetSliderAttachment;
	// IR sliders
	juce::Slider irDrySlider;
	juce::Slider irWetSlider;
	juce::Label irDryLabel;
	juce::Label irWetLabel;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> irDrySliderAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> irWetSliderAttachment;
	// output sliders
	juce::Slider synthGainSlider;
	juce::Slider thiccGainSlider;
	juce::Slider outputGainSlider;
	juce::Label synthGainLabel;
	juce::Label thiccGainLabel;
	juce::Label outputGainLabel;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> synthGainSliderAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> thiccGainSliderAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> outputGainSliderAttachment;

    SinthethiccAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SinthethiccAudioProcessorEditor)
};