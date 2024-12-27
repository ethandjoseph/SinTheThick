#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Components/SynthVoiceEditor.h"

SinthethiccAudioProcessorEditor::SinthethiccAudioProcessorEditor (SinthethiccAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
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
	saturationSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	thiccGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	outputGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);

	synthAttackSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lime);
	synthDecaySlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lime);
	synthSustainSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lime);
	synthReleaseSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lime);
	juverbSizeSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lime);
	juverbDampingSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lime);
	juverbWidthSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lime);
	juverbDrySlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lime);
	juverbWetSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lime);
	irDrySlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lime);
	irWetSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lime);
	synthGainSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lime);
	saturationSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lime);
	thiccGainSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lime);
	outputGainSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lime);

	//juverbFreezeButton.setClickingTogglesState(true);
	/*loadButton.onClick = [this]
		{
			fileChooser = std::make_unique<juce::FileChooser>("Select .wav IR file to load", audioProcessor.root, "*.wav");
			const auto fileChooserFlags = juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles;
			fileChooser->launchAsync(fileChooserFlags, [this](const juce::FileChooser& fc)
				{
					auto file = fc.getResult();
					if (file.exists())
					{
						audioProcessor.setIR(file);
						irName.setText(file.getFileName().substring(0, 14), juce::dontSendNotification);
						irName.setJustificationType(juce::Justification::centred);
					}
				});
		};*/

	loadButton.onClick = [this] {showReverberationSettingsWindow(); };

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
	saturationSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
	thiccGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
	outputGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);

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
	saturationSlider.setTextValueSuffix("%");
	thiccGainSlider.setTextValueSuffix("%");
	outputGainSlider.setTextValueSuffix("dB");

	synthAttackLabel.setText("Attack", juce::dontSendNotification);
	synthDecayLabel.setText("Decay", juce::dontSendNotification);
	synthSustainLabel.setText("Sustain", juce::dontSendNotification);
	synthReleaseLabel.setText("Release", juce::dontSendNotification);
	juverbSizeLabel.setText("Room Size", juce::dontSendNotification);
	juverbDampingLabel.setText("Damping", juce::dontSendNotification);
	juverbWidthLabel.setText("Width", juce::dontSendNotification);
	juverbFreezeButton.setButtonText("Freeze");
	loadButton.setButtonText("Load IR");
	loadButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xff1e2545));
	juverbDryLabel.setText("Ju Dry", juce::dontSendNotification);
	juverbWetLabel.setText("Ju Wet", juce::dontSendNotification);
	irDryLabel.setText("IR Dry", juce::dontSendNotification);
	irWetLabel.setText("IR Wet", juce::dontSendNotification);
	loadButton.setButtonText("Load IR");

	synthGainLabel.setText("Synth Gain", juce::dontSendNotification);
	saturationLabel.setText("Thicc Saturation", juce::dontSendNotification);
	thiccGainLabel.setText("Thicc Gain", juce::dontSendNotification);
	outputGainLabel.setText("Output Gain", juce::dontSendNotification);

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
	saturationLabel.attachToComponent(&saturationSlider, false);
	thiccGainLabel.attachToComponent(&thiccGainSlider, false);
	outputGainLabel.attachToComponent(&outputGainSlider, false);

	addAndMakeVisible(synthAttackSlider);
	addAndMakeVisible(synthDecaySlider);
	addAndMakeVisible(synthSustainSlider);
	addAndMakeVisible(synthReleaseSlider);
	/*addAndMakeVisible(juverbSizeSlider);
	addAndMakeVisible(juverbDampingSlider);
	addAndMakeVisible(juverbWidthSlider);
	addAndMakeVisible(juverbFreezeButton);*/
	addAndMakeVisible(loadButton);
	/*addAndMakeVisible(irName);
	addAndMakeVisible(juverbDrySlider);
	addAndMakeVisible(juverbWetSlider);
	addAndMakeVisible(irDrySlider);
	addAndMakeVisible(irWetSlider);*/

	addAndMakeVisible(synthGainSlider);
	addAndMakeVisible(saturationSlider);
	addAndMakeVisible(thiccGainSlider);
	addAndMakeVisible(outputGainSlider);

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
	saturationSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "THICC_SATURATION", saturationSlider);
	thiccGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "THICC_GAIN", thiccGainSlider);
	outputGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "OUTPUT_GAIN", outputGainSlider);

    setSize (600, 840);
}

SinthethiccAudioProcessorEditor::~SinthethiccAudioProcessorEditor()
{
}

void SinthethiccAudioProcessorEditor::paint (juce::Graphics& g)
{
	g.fillAll(juce::Colour(0xff1e2545));
}

void SinthethiccAudioProcessorEditor::resized()
{
	auto area = getLocalBounds().reduced(20);
	int sliderWidth = area.getWidth() / 4;
	int sliderHeightWithLabel = area.getHeight() / 4;
	int sliderHeight = sliderHeightWithLabel * 4 / 5;
	int labelHeight = sliderHeightWithLabel - sliderHeight;

	auto row1 = area.removeFromTop(sliderHeight + labelHeight);
	synthAttackSlider.setBounds(row1.removeFromLeft(sliderWidth).reduced(0, labelHeight));
	synthDecaySlider.setBounds(row1.removeFromLeft(sliderWidth).reduced(0, labelHeight));
	synthSustainSlider.setBounds(row1.removeFromLeft(sliderWidth).reduced(0, labelHeight));
	synthReleaseSlider.setBounds(row1.removeFromLeft(sliderWidth).reduced(0, labelHeight));

	auto row2 = area.removeFromTop(sliderHeight + labelHeight);
	/*juverbSizeSlider.setBounds(row2.removeFromLeft(sliderWidth).reduced(0, labelHeight));
	juverbDampingSlider.setBounds(row2.removeFromLeft(sliderWidth).reduced(0, labelHeight));
	juverbWidthSlider.setBounds(row2.removeFromLeft(sliderWidth).reduced(0, labelHeight));
	juverbFreezeButton.setBounds(row2.removeFromLeft(sliderWidth).reduced(0, labelHeight));*/
	loadButton.setBounds(row2.removeFromLeft(sliderWidth).reduced(0, labelHeight));
	irName.setBounds(loadButton.getBounds().removeFromBottom(32));

	auto row3 = area.removeFromTop(sliderHeight + labelHeight);
	juverbDrySlider.setBounds(row3.removeFromLeft(sliderWidth).reduced(0, labelHeight));
	juverbWetSlider.setBounds(row3.removeFromLeft(sliderWidth).reduced(0, labelHeight));
	irDrySlider.setBounds(row3.removeFromLeft(sliderWidth).reduced(0, labelHeight));
	irWetSlider.setBounds(row3.removeFromLeft(sliderWidth).reduced(0, labelHeight));

	auto row4 = area.removeFromTop(sliderHeight + labelHeight);
	synthGainSlider.setBounds(row4.removeFromLeft(sliderWidth).reduced(0, labelHeight));
	saturationSlider.setBounds(row4.removeFromLeft(sliderWidth).reduced(0, labelHeight));
	thiccGainSlider.setBounds(row4.removeFromLeft(sliderWidth).reduced(0, labelHeight));
	outputGainSlider.setBounds(row4.removeFromLeft(sliderWidth).reduced(0, labelHeight));
}

void SinthethiccAudioProcessorEditor::showReverberationSettingsWindow()
{
	juce::DialogWindow::LaunchOptions options;
	options.content.setOwned(new SynthVoiceEditor(audioProcessor.apvts));

	options.content->setSize(400, 200);
	options.dialogTitle = "Row 4 Sliders";
	options.dialogBackgroundColour = juce::Colour(0xff1e2545);
	options.escapeKeyTriggersCloseButton = true;
	options.useNativeTitleBar = true;
	options.resizable = false;

	options.launchAsync();
}