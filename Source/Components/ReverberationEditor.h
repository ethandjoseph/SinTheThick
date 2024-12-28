#pragma once
#include <JuceHeader.h>

class ReverberationEditor  : public juce::Component
{
public:
    ReverberationEditor(juce::AudioProcessorValueTreeState& apvts, juce::AudioProcessor& audioProcessor);
    ~ReverberationEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Label juverbSizeLabel;
    juce::Slider juverbSizeSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> juverbSizeSliderAttachment;

	juce::Label juverbDampingLabel;
	juce::Slider juverbDampingSlider;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> juverbDampingSliderAttachment;

    juce::Label juverbWidthLabel;
    juce::Slider juverbWidthSlider;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> juverbWidthSliderAttachment;

    juce::Label irLabel;
	juce::TextButton loadImpulseResponseButton;
	std::unique_ptr<juce::FileChooser> fileChooser;
	juce::Label irName;

    juce::Label juceReverbLabel;
    juce::Label balanceLabel;
    juce::Label irReverbLabel;
	juce::Slider balanceSlider;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> balanceSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverberationEditor)
};