/*
  ==============================================================================

    ReberberationEditor.h
    Created: 27 Dec 2024 4:47:03pm
    Author:  ethan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ReberberationEditor  : public juce::Component
{
public:
    ReberberationEditor();
    ~ReberberationEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReberberationEditor)
};
