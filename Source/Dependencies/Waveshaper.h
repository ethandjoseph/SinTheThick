#pragma once
#include <JuceHeader.h>

class Waveshaper : public juce::dsp::ProcessorBase
{
public:
    Waveshaper()
    {
        waveshaper.functionToUse = [](float in)
            {
                float out = in;

                if (in <= -1.0f)
                    out = -1.0f;
                else if (in >= 1.0f)
                    out = 1.0f;
                else
                    out = in * (1.5f - 0.5f * std::exp(-2.0f * in * in));

                return out;
            };
    }

    void prepare(const juce::dsp::ProcessSpec& spec) override
    {
        constexpr size_t oversamplingOrder = 4;
        constexpr auto filterType = juce::dsp::Oversampling<float>::filterHalfBandPolyphaseIIR;

        oversampler = std::make_unique<juce::dsp::Oversampling<float>>(spec.numChannels, oversamplingOrder, filterType);
        oversampler->initProcessing(spec.maximumBlockSize);
    }

    void process(const juce::dsp::ProcessContextReplacing<float>& context) override
    {
        auto oversampledBlock = oversampler->processSamplesUp(context.getInputBlock());
        waveshaper.process(juce::dsp::ProcessContextReplacing<float>(oversampledBlock));
        oversampler->processSamplesDown(context.getOutputBlock());
    }

    void reset() override { oversampler->reset(); }

    float getLatencyInSamples()
    {
        return oversampler == nullptr ? 0.0f : oversampler->getLatencyInSamples();
    }

private:

    std::unique_ptr<juce::dsp::Oversampling<float>> oversampler;
    juce::dsp::WaveShaper<float> waveshaper;
};