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

                if (in <= -1.7f)
                    out = -1.0f;
                else if ((in > -1.7f) && (in < -0.3f))
                {
                    in += 0.3f;
                    out = in + (in * in) / (4 * (1 - 0.3f)) - 0.3f;
                }
                else if ((in > 0.9f) && (in < 1.1f))
                {
                    in -= 0.9f;
                    out = in - (in * in) / (4 * (1 - 0.9f)) + 0.9f;
                }
                else if (in > 1.1f)
                    out = 1.0f;

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