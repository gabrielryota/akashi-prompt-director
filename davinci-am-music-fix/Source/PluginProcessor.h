#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_dsp/juce_dsp.h>

// AM Music Fix — port do preset de Premiere "AM Music Fix.prfpset" para DaVinci Resolve.
// Cadeia (mesma ordem do preset): Lowpass -> Mastering (EQ, Reverb, Widener,
// Exciter, Loudness Maximizer, Output Gain) -> Volume.
class AMMusicFixProcessor : public juce::AudioProcessor
{
public:
    AMMusicFixProcessor();
    ~AMMusicFixProcessor() override = default;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override {}
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return "AM Music Fix"; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 2.0; }

    int getNumPrograms() override;
    int getCurrentProgram() override { return currentProgram; }
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int, const juce::String&) override {}

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState apvts;

private:
    static juce::AudioProcessorValueTreeState::ParameterLayout createLayout();
    float p (const char* id) const { return apvts.getRawParameterValue (id)->load(); }
    void updateFilters();
    void updateFiltersIfNeeded();
    float lastFilterParams[10] {};

    using Biquad = juce::dsp::IIR::Filter<float>;
    using Coeffs = juce::dsp::IIR::Coefficients<float>;

    static constexpr int maxCh = 8;
    double sr = 48000.0;
    int currentProgram = 0;

    Biquad lowpass[maxCh], eqLow[maxCh], eqMid[maxCh], eqHigh[maxCh];
    Biquad exciterHP[maxCh];
    juce::Reverb reverb;
    juce::dsp::Limiter<float> limiter;

    juce::SmoothedValue<float> volumeGain, outputGain, makeupGain;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AMMusicFixProcessor)
};
