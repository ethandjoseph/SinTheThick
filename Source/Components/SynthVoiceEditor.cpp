
#include <JuceHeader.h>
#include "SynthVoiceEditor.h"

//==============================================================================
SynthVoiceEditor::SynthVoiceEditor(juce::AudioProcessorValueTreeState& apvts)
{
	oscGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	oscDelaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	noiseGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);

	oscGainSlider.setScrollWheelEnabled(true);
	oscDelaySlider.setScrollWheelEnabled(true);
	noiseGainSlider.setScrollWheelEnabled(true);

	oscGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
	oscDelaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
	noiseGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);

	oscGainSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lime);
	oscDelaySlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lime);
	noiseGainSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lime);

	oscGainSlider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentWhite);
	oscDelaySlider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentWhite);
	noiseGainSlider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentWhite);

	oscGainLabel.setJustificationType(juce::Justification::centred);
	oscDelayLabel.setJustificationType(juce::Justification::centred);
	noiseGainLabel.setJustificationType(juce::Justification::centred);

	oscGainLabel.setText("Sine Osc Amp", juce::dontSendNotification);
	oscDelayLabel.setText("Sine Delay", juce::dontSendNotification);
	noiseGainLabel.setText("Noise Amp", juce::dontSendNotification);

	oscGainSlider.setTextValueSuffix("%");
	oscDelaySlider.setTextValueSuffix("s");
	noiseGainSlider.setTextValueSuffix("%");

	addAndMakeVisible(oscGainSlider);
	addAndMakeVisible(oscDelaySlider);
	addAndMakeVisible(noiseGainSlider);

	addAndMakeVisible(oscGainLabel);
	addAndMakeVisible(oscDelayLabel);
	addAndMakeVisible(noiseGainLabel);

	oscGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "OSC_GAIN", oscGainSlider);
	oscDelaySliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "SIN_DELAY", oscDelaySlider);
	noiseGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "NOISE_GAIN", noiseGainSlider);

	setSize(380, 220);
}

SynthVoiceEditor::~SynthVoiceEditor()
{
}

void SynthVoiceEditor::paint (juce::Graphics& g)
{
	g.fillAll(juce::Colour(0xff1e2545));
	juce::Image bg = juce::ImageCache::getFromMemory(BinaryData::synth_bg_png, BinaryData::synth_bg_pngSize);
	g.drawImageAt(bg, 0, 0);
}

void SynthVoiceEditor::resized()
{
	int padding = 20;
	int spacing = 20;
	auto area = getLocalBounds().reduced(padding);
	int sliderWidth = 100;
	int sliderHeight = 160;
	int labelHeight = 20;
	int buttonWidth = sliderWidth;
	int buttonHeight = 20;

	oscGainLabel.setBounds(padding, padding, sliderWidth, labelHeight);
	oscGainSlider.setBounds(padding, padding+labelHeight, sliderWidth, sliderHeight);

	oscDelayLabel.setBounds(padding + sliderWidth + spacing, padding, sliderWidth, labelHeight);
	oscDelaySlider.setBounds(padding + sliderWidth + spacing, padding + labelHeight, sliderWidth, sliderHeight);

	noiseGainLabel.setBounds(padding + 2 * (sliderWidth + spacing), padding, sliderWidth, labelHeight);
	noiseGainSlider.setBounds(padding + 2 * (sliderWidth + spacing), padding + labelHeight, sliderWidth, sliderHeight);

	setSize(380, 220);
}