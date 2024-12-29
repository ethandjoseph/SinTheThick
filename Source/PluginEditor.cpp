#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Components/SynthVoiceEditor.h"
#include "Components/ReverberationEditor.h"

SinthethiccAudioProcessorEditor::SinthethiccAudioProcessorEditor (SinthethiccAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
	inputNoteLabel.setText("Input Note", juce::dontSendNotification);
	inputNoteLabel.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(inputNoteLabel);

	inputNoteValueLabel.setColour(juce::Label::textColourId, juce::Colours::black);
	inputNoteValueLabel.setText("Play a Note", juce::dontSendNotification);
	inputNoteValueLabel.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(inputNoteValueLabel);

	voicingLabel.setText("Voicing", juce::dontSendNotification);
	voicingLabel.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(voicingLabel);

	synthVoiceButton.setButtonText("Synth");
	synthVoiceButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xff3E4D8F));
	synthVoiceButton.onClick = [this] { showSynthVoiceEditorWindow(); };
	addAndMakeVisible(synthVoiceButton);

	reverbButton.setButtonText("Reverberators");
	reverbButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xff3D4B8C));
	reverbButton.onClick = [this] { showReverberationEditorWindow(); };
	addAndMakeVisible(reverbButton);

	adsrLabel.setText("ADSR", juce::dontSendNotification);
	adsrLabel.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(adsrLabel);

	synthAttackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
	synthAttackSlider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentWhite);
	synthAttackSlider.setScrollWheelEnabled(true);
	synthAttackSlider.setTextValueSuffix("s");
	synthAttackSlider.setColour(juce::Slider::trackColourId, juce::Colours::lime);
	synthAttackSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "ATTACK", synthAttackSlider);
	addAndMakeVisible(synthAttackSlider);

	synthDecaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
	synthDecaySlider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentWhite);
	synthDecaySlider.setScrollWheelEnabled(true);
	synthDecaySlider.setTextValueSuffix("s");
	synthDecaySlider.setColour(juce::Slider::trackColourId, juce::Colours::lime);
	synthDecaySliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DECAY", synthDecaySlider);
	addAndMakeVisible(synthDecaySlider);

	synthSustainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
	synthSustainSlider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentWhite);
	synthSustainSlider.setScrollWheelEnabled(true);
	synthSustainSlider.setTextValueSuffix("s");
	synthSustainSlider.setColour(juce::Slider::trackColourId, juce::Colours::lime);
	synthSustainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "SUSTAIN", synthSustainSlider);
	addAndMakeVisible(synthSustainSlider);

	synthReleaseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
	synthReleaseSlider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentWhite);
	synthReleaseSlider.setScrollWheelEnabled(true);
	synthReleaseSlider.setTextValueSuffix("s");
	synthReleaseSlider.setColour(juce::Slider::trackColourId, juce::Colours::lime);
	synthReleaseSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "RELEASE", synthReleaseSlider);
	addAndMakeVisible(synthReleaseSlider);

	synthGainLabel.setText("Synth Level", juce::dontSendNotification);
	synthGainLabel.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(synthGainLabel);

	synthGainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
	synthGainSlider.setScrollWheelEnabled(true);
	synthGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
	synthGainSlider.setTextValueSuffix("%");
	synthGainSlider.setColour(juce::Slider::trackColourId, juce::Colours::lime);
	synthGainSlider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentWhite);
	synthGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "SYNTH_GAIN", synthGainSlider);
	addAndMakeVisible(synthGainSlider);

	saturationLabel.setText("Thicc Drive", juce::dontSendNotification);
	saturationLabel.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(saturationLabel);

	saturationSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
	saturationSlider.setScrollWheelEnabled(true);
	saturationSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
	saturationSlider.setTextValueSuffix("dB");
	saturationSlider.setColour(juce::Slider::trackColourId, juce::Colours::lime);
	saturationSlider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentWhite);
	saturationSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "SATURATION", saturationSlider);
	addAndMakeVisible(saturationSlider);

	thiccGainLabel.setText("Thicc Level", juce::dontSendNotification);
	thiccGainLabel.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(thiccGainLabel);

	thiccGainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
	thiccGainSlider.setScrollWheelEnabled(true);
	thiccGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
	thiccGainSlider.setTextValueSuffix("%");
	thiccGainSlider.setColour(juce::Slider::trackColourId, juce::Colours::lime);
	thiccGainSlider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentWhite);
	thiccGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "THICC_GAIN", thiccGainSlider);
	addAndMakeVisible(thiccGainSlider);

	outputGainLabel.setText("Output", juce::dontSendNotification);
	outputGainLabel.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(outputGainLabel);

	outputGainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
	outputGainSlider.setScrollWheelEnabled(true);
	outputGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
	outputGainSlider.setTextValueSuffix("dB");
	outputGainSlider.setColour(juce::Label::textColourId, juce::Colours::transparentWhite);
	outputGainSlider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentWhite);
	outputGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "OUTPUT_GAIN", outputGainSlider);
	addAndMakeVisible(outputGainSlider);

	addAndMakeVisible(outputVUMeterLeft);
	addAndMakeVisible(outputVUMeterRight);

	outputGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "OUTPUT_GAIN", outputGainSlider);

	startTimerHz(30);

    setSize (608, 220);
}

SinthethiccAudioProcessorEditor::~SinthethiccAudioProcessorEditor()
{
}

void SinthethiccAudioProcessorEditor::timerCallback()
{
	auto midiNoteNumber = audioProcessor.getCurrentMidiNoteNumber();
	if (midiNoteNumber >= 0)
	{
		auto noteName = juce::MidiMessage::getMidiNoteName(midiNoteNumber, true, true, 3);
		inputNoteValueLabel.setColour(juce::Label::textColourId, juce::Colours::lime);
		inputNoteValueLabel.setText(noteName, juce::dontSendNotification);
	}
	else
	{
		inputNoteValueLabel.setColour(juce::Label::textColourId, juce::Colours::grey);
		inputNoteValueLabel.setText("Play a Note!", juce::dontSendNotification);
	}

	/*float inputLevelLeft = audioProcessor.getRMSValue(0, 0);
	float inputLevelRight = audioProcessor.getRMSValue(0, 1);*/
	float outputLevelLeft = audioProcessor.getRMSValue(1, 0);
	float outputLevelRight = audioProcessor.getRMSValue(1, 1);

	/*inputVUMeterLeft.setLevel(inputLevelLeft);
	inputVUMeterRight.setLevel(inputLevelRight);*/
	outputVUMeterLeft.setLevel(outputLevelLeft);
	outputVUMeterRight.setLevel(outputLevelRight);

	/*inputVUMeterLeft.repaint();
	inputVUMeterRight.repaint();*/
	outputVUMeterLeft.repaint();
	outputVUMeterRight.repaint();
}

void SinthethiccAudioProcessorEditor::paint (juce::Graphics& g)
{
	g.fillAll(juce::Colour(0xff1e2545));
	juce::Image bg = juce::ImageCache::getFromMemory(BinaryData::main_bg_png, BinaryData::main_bg_pngSize);
	g.drawImageAt(bg, 0, 0);
}

void SinthethiccAudioProcessorEditor::resized()
{
	inputNoteLabel.setBounds(20, 20, 100, 20);
	inputNoteValueLabel.setBounds(20, 50, 100, 50);

	voicingLabel.setBounds(140, 20, 100, 20);
	synthVoiceButton.setBounds(140, 50, 100, 20);
	reverbButton.setBounds(140, 80, 100, 20);

	adsrLabel.setBounds(20, 110, 220, 20);
	synthAttackSlider.setBounds(20, 140, 46, 60);
	synthDecaySlider.setBounds(78, 140, 46, 60);
	synthSustainSlider.setBounds(136, 140, 46, 60);
	synthReleaseSlider.setBounds(194, 140, 46, 60);

	synthGainLabel.setBounds(260, 20, 80, 20);
	synthGainSlider.setBounds(260, 40, 80, 160);

	saturationLabel.setBounds(350, 20, 80, 20);
	saturationSlider.setBounds(350, 40, 80, 160);

	thiccGainLabel.setBounds(440, 20, 80, 20);
	thiccGainSlider.setBounds(440, 40, 80, 160);

	outputVUMeterLeft.setBounds(546, 55, 4, 110);
	outputVUMeterRight.setBounds(582, 55, 4, 110);

	outputGainLabel.setBounds(534, 20, 64, 20);
	outputGainSlider.setBounds(534, 40, 64, 160);
}

void SinthethiccAudioProcessorEditor::showSynthVoiceEditorWindow()
{
	juce::DialogWindow::LaunchOptions options;
	options.content.setOwned(new SynthVoiceEditor(audioProcessor.apvts));
	options.content->setSize(380, 220);
	options.dialogTitle = "Synth Voice Settings";
	options.dialogBackgroundColour = juce::Colour(0xff1e2545);
	options.escapeKeyTriggersCloseButton = true;
	options.useNativeTitleBar = true;
	options.resizable = false;
	options.launchAsync();
}

void SinthethiccAudioProcessorEditor::showReverberationEditorWindow()
{
	juce::DialogWindow::LaunchOptions options;
	options.content.setOwned(new ReverberationEditor(audioProcessor.apvts, audioProcessor));
	options.content->setSize(780, 261);
	options.dialogTitle = "Reverberators Settings";
	options.dialogBackgroundColour = juce::Colour(0xff1e2545);
	options.escapeKeyTriggersCloseButton = true;
	options.useNativeTitleBar = true;
	options.resizable = false;
	options.launchAsync();
}