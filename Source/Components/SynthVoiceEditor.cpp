
#include <JuceHeader.h>
#include "SynthVoiceEditor.h"

//==============================================================================
SynthVoiceEditor::SynthVoiceEditor(juce::AudioProcessorValueTreeState& apvts)
{
	oscGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	noiseGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);

	oscGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
	noiseGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);

	oscGainLabel.setText("Sine Osc Amp", juce::dontSendNotification);
	noiseGainLabel.setText("Noise Amp", juce::dontSendNotification);

	oscGainSlider.setTextValueSuffix("%");
	noiseGainSlider.setTextValueSuffix("%");

	addAndMakeVisible(oscGainSlider);
	addAndMakeVisible(noiseGainSlider);
	addAndMakeVisible(oscGainLabel);
	addAndMakeVisible(noiseGainLabel);

	oscGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "OSC_GAIN", oscGainSlider);
	noiseGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "NOISE_GAIN", noiseGainSlider);
}

SynthVoiceEditor::~SynthVoiceEditor()
{
}

void SynthVoiceEditor::paint (juce::Graphics& g)
{
	g.fillAll(juce::Colour(0xff1e2545));
}

void SynthVoiceEditor::resized()
{
	auto area = getLocalBounds().reduced(20);
	int sliderWidth = area.getWidth() / 2;
	int sliderHeightWithLabel = area.getHeight() / 2;
	int sliderHeight = sliderHeightWithLabel * 4 / 5;
	int labelHeight = sliderHeightWithLabel - sliderHeight;

	auto row1 = area.removeFromTop(sliderHeight + labelHeight);
	oscGainSlider.setBounds(row1.removeFromLeft(sliderWidth).reduced(0, labelHeight));
	noiseGainSlider.setBounds(row1.removeFromLeft(sliderWidth).reduced(0, labelHeight));
}