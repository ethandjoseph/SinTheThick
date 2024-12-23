#include "PluginProcessor.h"
#include "PluginEditor.h"

SinthethiccAudioProcessorEditor::SinthethiccAudioProcessorEditor (SinthethiccAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // set all slider styles to rotary vertical drag
	synthAttackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	synthDecaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	synthSustainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	synthReleaseSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	juverbSizeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	juverbDampingSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	juverbWidthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	juverbDrySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	juverbWetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	irDrySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	irWetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	synthGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	thiccGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	outputGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	juverbFreezeButton.setClickingTogglesState(true);

	// set all slider textboxes styles to below and 100 by 20
	synthAttackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
	synthDecaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
	synthSustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
	synthReleaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
	juverbSizeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
	juverbDampingSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
	juverbWidthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
	juverbDrySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
	juverbWetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
	irDrySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
	irWetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
	synthGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
	thiccGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
	outputGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);

	// set suffix values for all sliders
	synthAttackSlider.setTextValueSuffix("s");
	synthDecaySlider.setTextValueSuffix("s");
	synthSustainSlider.setTextValueSuffix("s");
	synthReleaseSlider.setTextValueSuffix("s");
	juverbSizeSlider.setTextValueSuffix("m");
	juverbDampingSlider.setTextValueSuffix("Hz");
	juverbWidthSlider.setTextValueSuffix("Hz");
	juverbDrySlider.setTextValueSuffix("%");
	juverbWetSlider.setTextValueSuffix("%");
	irDrySlider.setTextValueSuffix("%");
	irWetSlider.setTextValueSuffix("%");
	synthGainSlider.setTextValueSuffix("%");
	thiccGainSlider.setTextValueSuffix("%");
	outputGainSlider.setTextValueSuffix("dB");

	// set all slider labels
	synthAttackLabel.setText("Attack", juce::dontSendNotification);
	synthDecayLabel.setText("Decay", juce::dontSendNotification);
	synthSustainLabel.setText("Sustain", juce::dontSendNotification);
	synthReleaseLabel.setText("Release", juce::dontSendNotification);
	juverbSizeLabel.setText("Room Size", juce::dontSendNotification);
	juverbDampingLabel.setText("Damping", juce::dontSendNotification);
	juverbWidthLabel.setText("Width", juce::dontSendNotification);
	juverbFreezeButton.setButtonText("Freeze");
	juverbDryLabel.setText("Ju Dry", juce::dontSendNotification);
	juverbWetLabel.setText("Ju Wet", juce::dontSendNotification);
	irDryLabel.setText("IR Dry", juce::dontSendNotification);
	irWetLabel.setText("IR Wet", juce::dontSendNotification);
	synthGainLabel.setText("Synth Gain", juce::dontSendNotification);
	thiccGainLabel.setText("Thicc Gain", juce::dontSendNotification);
	outputGainLabel.setText("Output Gain", juce::dontSendNotification);

	// attach labels to respective sliders
	synthAttackLabel.attachToComponent(&synthAttackSlider, false);
	synthDecayLabel.attachToComponent(&synthDecaySlider, false);
	synthSustainLabel.attachToComponent(&synthSustainSlider, false);
	synthReleaseLabel.attachToComponent(&synthReleaseSlider, false);
	juverbSizeLabel.attachToComponent(&juverbSizeSlider, false);
	juverbDampingLabel.attachToComponent(&juverbDampingSlider, false);
	juverbWidthLabel.attachToComponent(&juverbWidthSlider, false);
	juverbDryLabel.attachToComponent(&juverbDrySlider, false);
	juverbWetLabel.attachToComponent(&juverbWetSlider, false);
	irDryLabel.attachToComponent(&irDrySlider, false);
	irWetLabel.attachToComponent(&irWetSlider, false);
	synthGainLabel.attachToComponent(&synthGainSlider, false);
	thiccGainLabel.attachToComponent(&thiccGainSlider, false);
	outputGainLabel.attachToComponent(&outputGainSlider, false);

	// add all sliders to the editor
	addAndMakeVisible(synthAttackSlider);
	addAndMakeVisible(synthDecaySlider);
	addAndMakeVisible(synthSustainSlider);
	addAndMakeVisible(synthReleaseSlider);
	addAndMakeVisible(juverbSizeSlider);
	addAndMakeVisible(juverbDampingSlider);
	addAndMakeVisible(juverbWidthSlider);
	addAndMakeVisible(juverbFreezeButton);
	addAndMakeVisible(juverbDrySlider);
	addAndMakeVisible(juverbWetSlider);
	addAndMakeVisible(irDrySlider);
	addAndMakeVisible(irWetSlider);
	addAndMakeVisible(synthGainSlider);
	addAndMakeVisible(thiccGainSlider);
	addAndMakeVisible(outputGainSlider);

	// attach attachments
	synthAttackSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "ATTACK", synthAttackSlider);
	synthDecaySliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DECAY", synthDecaySlider);
	synthSustainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "SUSTAIN", synthSustainSlider);
	synthReleaseSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "RELEASE", synthReleaseSlider);
	juverbSizeSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "JUVERB_ROOM_SIZE", juverbSizeSlider);
	juverbDampingSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "JUVERB_DAMPING", juverbDampingSlider);
	juverbWidthSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "JUVERB_WIDTH", juverbWidthSlider);
	juverbFreezeButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.apvts, "JUVERB_FREEZE", juverbFreezeButton);
	juverbDrySliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "JUVERB_DRY", juverbDrySlider);
	juverbWetSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "JUVERB_WET", juverbWetSlider);
	irDrySliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "IR_DRY", irDrySlider);
	irWetSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "IR_WET", irWetSlider);
	synthGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "SYNTH_GAIN", synthGainSlider);
	thiccGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "THICC_GAIN", thiccGainSlider);
	outputGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "OUTPUT_GAIN", outputGainSlider);

    setSize (840, 840);
}

SinthethiccAudioProcessorEditor::~SinthethiccAudioProcessorEditor()
{
}

void SinthethiccAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void SinthethiccAudioProcessorEditor::resized()
{
	auto area = getLocalBounds().reduced(20);
	int sliderWidth = area.getWidth() / 4;
	int sliderHeightWithLabel = area.getHeight() / 4;
	int sliderHeight = sliderHeightWithLabel * 4 / 5;
	int labelHeight = sliderHeightWithLabel - sliderHeight;

	// first row of sliders
	auto row1 = area.removeFromTop(sliderHeight + labelHeight);
	synthAttackSlider.setBounds(row1.removeFromLeft(sliderWidth).reduced(0, labelHeight));
	synthDecaySlider.setBounds(row1.removeFromLeft(sliderWidth).reduced(0, labelHeight));
	synthSustainSlider.setBounds(row1.removeFromLeft(sliderWidth).reduced(0, labelHeight));
	synthReleaseSlider.setBounds(row1.removeFromLeft(sliderWidth).reduced(0, labelHeight));

	// second row of sliders
	auto row2 = area.removeFromTop(sliderHeight + labelHeight);
	juverbSizeSlider.setBounds(row2.removeFromLeft(sliderWidth).reduced(0, labelHeight));
	juverbDampingSlider.setBounds(row2.removeFromLeft(sliderWidth).reduced(0, labelHeight));
	juverbWidthSlider.setBounds(row2.removeFromLeft(sliderWidth).reduced(0, labelHeight));
	juverbFreezeButton.setBounds(row2.removeFromLeft(sliderWidth).reduced(0, labelHeight));

	// third row of sliders
	auto row3 = area.removeFromTop(sliderHeight + labelHeight);
	juverbDrySlider.setBounds(row3.removeFromLeft(sliderWidth).reduced(0, labelHeight));
	juverbWetSlider.setBounds(row3.removeFromLeft(sliderWidth).reduced(0, labelHeight));
	irDrySlider.setBounds(row3.removeFromLeft(sliderWidth).reduced(0, labelHeight));
	irWetSlider.setBounds(row3.removeFromLeft(sliderWidth).reduced(0, labelHeight));

	// fourth row of sliders centered
	auto row4 = area.removeFromTop(sliderHeight + labelHeight);
	synthGainSlider.setBounds(row4.removeFromLeft(sliderWidth).reduced(0, labelHeight));
	thiccGainSlider.setBounds(row4.removeFromLeft(sliderWidth).reduced(0, labelHeight));
	outputGainSlider.setBounds(row4.removeFromLeft(sliderWidth).reduced(0, labelHeight));
}