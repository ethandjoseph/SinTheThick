#include <JuceHeader.h>
#include "ReverberationEditor.h"
#include "../PluginProcessor.h"

ReverberationEditor::ReverberationEditor(juce::AudioProcessorValueTreeState& apvts, juce::AudioProcessor& audioProcessor)
{
	juverbSizeLabel.setText("Room Size", juce::dontSendNotification);
	juverbSizeLabel.setJustificationType(juce::Justification::centred);

	juverbSizeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	juverbSizeSlider.setScrollWheelEnabled(true);
	juverbSizeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
	juverbSizeSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lime);
	juverbSizeSlider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentWhite);
	//juverbSizeSlider.setTextValueSuffix("m");
	addAndMakeVisible(juverbSizeSlider);
	addAndMakeVisible(juverbSizeLabel);
	juverbSizeSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "JUVERB_ROOM_SIZE", juverbSizeSlider);

	juverbDampingLabel.setText("Damping", juce::dontSendNotification);
	juverbDampingLabel.setJustificationType(juce::Justification::centred);

	juverbDampingSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	juverbDampingSlider.setScrollWheelEnabled(true);
	juverbDampingSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
	juverbDampingSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lime);
	juverbDampingSlider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentWhite);
	//juverbDampingSlider.setTextValueSuffix("m");
	addAndMakeVisible(juverbDampingSlider);
	addAndMakeVisible(juverbDampingLabel);
	juverbDampingSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "JUVERB_DAMPING", juverbDampingSlider);

	juverbWidthLabel.setText("Width", juce::dontSendNotification);
	juverbWidthLabel.setJustificationType(juce::Justification::centred);

	juverbWidthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	juverbWidthSlider.setScrollWheelEnabled(true);
	juverbWidthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
	juverbWidthSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lime);
	juverbWidthSlider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentWhite);
	//juverbWidthSlider.setTextValueSuffix("m");
	addAndMakeVisible(juverbWidthSlider);
	addAndMakeVisible(juverbWidthLabel);
	juverbWidthSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "JUVERB_WIDTH", juverbWidthSlider);

	irLabel.setText("Impulse Response", juce::dontSendNotification);
	irLabel.setJustificationType(juce::Justification::centred);
	loadImpulseResponseButton.setButtonText("Load new IR");
	loadImpulseResponseButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xff2D3766));
	loadImpulseResponseButton.onClick = [this, &audioProcessor]
		{
			auto& derivedProcessor = dynamic_cast<SinthethiccAudioProcessor&>(audioProcessor);
			fileChooser = std::make_unique<juce::FileChooser>("Select .wav IR file to load", derivedProcessor.root, "*.wav");
			const auto fileChooserFlags = juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles;
			fileChooser->launchAsync(fileChooserFlags, [this, &derivedProcessor](const juce::FileChooser& fc)
				{
					auto file = fc.getResult();
					if (file.exists())
					{
						derivedProcessor.setIR(file);
						irName.setText(file.getFileName().substring(0, 48), juce::dontSendNotification);
						irName.setJustificationType(juce::Justification::centred);
					}
				});
		};
	irName.setText("Default (chamber)", juce::dontSendNotification);
	irName.setColour(juce::Label::textColourId, juce::Colours::lime);
	irName.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(irLabel);
	addAndMakeVisible(loadImpulseResponseButton);
	addAndMakeVisible(irName);

	juceReverbLabel.setText("JUCE Reverb", juce::dontSendNotification);
	juceReverbLabel.setJustificationType(juce::Justification::left);
	balanceLabel.setText("Balance", juce::dontSendNotification);
	balanceLabel.setJustificationType(juce::Justification::centred);
	irReverbLabel.setText("IR Reverb", juce::dontSendNotification);
	irReverbLabel.setJustificationType(juce::Justification::right);

	balanceSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
	balanceSlider.setScrollWheelEnabled(true);
	balanceSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
	balanceSlider.setColour(juce::Slider::trackColourId, juce::Colour(0xff263238));
	balanceSlider.setColour(juce::Slider::thumbColourId, juce::Colours::lime);
	balanceSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "BALANCE", balanceSlider);
	addAndMakeVisible(juceReverbLabel);
	//addAndMakeVisible(balanceLabel);
	addAndMakeVisible(irReverbLabel);
	addAndMakeVisible(balanceSlider);

	setSize(780, 261);
}

ReverberationEditor::~ReverberationEditor()
{
}

void ReverberationEditor::paint (juce::Graphics& g)
{
	g.fillAll(juce::Colour(0xff1e2545));
	juce::Image bg = juce::ImageCache::getFromMemory(BinaryData::verb_bg_png, BinaryData::verb_bg_pngSize);
	g.drawImageAt(bg, 0, 0);
}

void ReverberationEditor::resized()
{
	juverbSizeLabel.setBounds(20, 20, 100, 20);
	juverbSizeSlider.setBounds(20, 40, 100, 160);

	juverbDampingLabel.setBounds(140, 20, 100, 20);
	juverbDampingSlider.setBounds(140, 40, 100, 160);

	juverbWidthLabel.setBounds(260, 20, 100, 20);
	juverbWidthSlider.setBounds(260, 40, 100, 160);

	irLabel.setBounds(420, 20, 340, 20);
	loadImpulseResponseButton.setBounds(420, 50, 340, 120);
	irName.setBounds(420, 180, 340, 20);

	juceReverbLabel.setBounds(20, 220, 100, 20);
	//balanceLabel.setBounds(340, 220, 100, 20);
	irReverbLabel.setBounds(660, 220, 100, 20);

	balanceSlider.setBounds(120, 213, 540, 34);

	setSize(780, 261);
}