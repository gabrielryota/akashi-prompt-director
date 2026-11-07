#include "PluginProcessor.h"

// -----------------------------------------------------------------------------
// Valores extraídos do arquivo AM_Music_Fix.prfpset.
// O Premiere guarda versões separadas para Stereo, Mono e 5.1. O preset de
// fábrica 0 ("Stereo") é o que o Premiere aplica numa faixa de música estéreo;
// o preset 1 replica a versão Mono / 5.1.
// Conversões: frequência = 20 + norm * 19980 Hz; ganho EQ = -30 + norm * 45 dB;
// Q = 0.2 + norm * 11.8; volume Premiere: 0 dB = 0.177828 (máx. +15 dB = 1.0).
// -----------------------------------------------------------------------------
namespace
{
struct PresetValues
{
    const char* name;
    float lowpassHz;
    bool  b1On; float b1Hz, b1Gain;
    bool  b2On; float b2Hz, b2Gain, b2Q;
    bool  b3On; float b3Hz, b3Gain;
    float reverb, width, exciter; int exciterMode;
    float maximizer, outputDb, volumeDb;
};

constexpr PresetValues kPresets[] =
{
    // Stereo (Lowpass 0.337791 | Mastering | Volume 0.005623 = -30 dB)
    { "AM Music Fix (Stereo)", 6769.1f,
      false, 30.0f, 0.0f,
      true, 2168.53f, -11.55f, 0.3f,
      false, 12000.0f, 0.0f,
      0.0f, 100.0f, 20.0f, 2,
      20.0f, 0.0f, -30.0f },

    // Mono / 5.1 (Lowpass 0.25 | Mastering | Volume 0.177828 = 0 dB)
    { "AM Music Fix (Mono / 5.1)", 5015.0f,
      false, 30.0f, 0.0f,
      true, 361.5f, -2.8f, 0.5f,
      true, 2722.0f, 1.9f,
      10.0f, 0.0f, 80.0f, 2,
      20.0f, 0.0f, 0.0f },
};

juce::NormalisableRange<float> freqRange()
{
    juce::NormalisableRange<float> r (20.0f, 20000.0f);
    r.setSkewForCentre (1000.0f);
    return r;
}
} // namespace

AMMusicFixProcessor::AMMusicFixProcessor()
    : AudioProcessor (BusesProperties()
                          .withInput ("Input", juce::AudioChannelSet::stereo(), true)
                          .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
      apvts (*this, nullptr, "AMMusicFix", createLayout())
{
    setCurrentProgram (0);
}

juce::AudioProcessorValueTreeState::ParameterLayout AMMusicFixProcessor::createLayout()
{
    using namespace juce;
    const auto& d = kPresets[0];
    AudioProcessorValueTreeState::ParameterLayout l;
    auto add = [&] (auto p) { l.add (std::move (p)); };
    auto fl = [&] (const char* id, const char* name, NormalisableRange<float> r, float def, const char* unit)
    {
        add (std::make_unique<AudioParameterFloat> (ParameterID { id, 1 }, name, r, def,
                                                     AudioParameterFloatAttributes().withLabel (unit)));
    };
    auto bl = [&] (const char* id, const char* name, bool def)
    {
        add (std::make_unique<AudioParameterBool> (ParameterID { id, 1 }, name, def));
    };

    fl ("lpHz", "Lowpass Cutoff", freqRange(), d.lowpassHz, "Hz");

    bl ("b1On", "EQ Low Shelf On", d.b1On);
    fl ("b1Hz", "EQ Low Shelf Freq", freqRange(), d.b1Hz, "Hz");
    fl ("b1Gain", "EQ Low Shelf Gain", { -30.0f, 15.0f, 0.01f }, d.b1Gain, "dB");

    bl ("b2On", "EQ Peak On", d.b2On);
    fl ("b2Hz", "EQ Peak Freq", freqRange(), d.b2Hz, "Hz");
    fl ("b2Gain", "EQ Peak Gain", { -30.0f, 15.0f, 0.01f }, d.b2Gain, "dB");
    fl ("b2Q", "EQ Peak Q", { 0.2f, 12.0f, 0.001f }, d.b2Q, "");

    bl ("b3On", "EQ High Shelf On", d.b3On);
    fl ("b3Hz", "EQ High Shelf Freq", freqRange(), d.b3Hz, "Hz");
    fl ("b3Gain", "EQ High Shelf Gain", { -30.0f, 15.0f, 0.01f }, d.b3Gain, "dB");

    fl ("reverb", "Reverb Amount", { 0.0f, 100.0f, 0.1f }, d.reverb, "%");
    fl ("width", "Widener Width", { -100.0f, 100.0f, 0.1f }, d.width, "");
    fl ("exciter", "Exciter Amount", { 0.0f, 100.0f, 0.1f }, d.exciter, "%");
    add (std::make_unique<AudioParameterChoice> (ParameterID { "exMode", 1 }, "Exciter Mode",
                                                  StringArray { "Retro", "Tape", "Tube" }, d.exciterMode));
    fl ("maximizer", "Loudness Maximizer", { 0.0f, 100.0f, 0.1f }, d.maximizer, "%");
    fl ("outDb", "Output Gain", { -18.0f, 9.0f, 0.01f }, d.outputDb, "dB");
    fl ("volDb", "Volume", { -60.0f, 15.0f, 0.01f }, d.volumeDb, "dB");
    bl ("bypass", "Bypass", false);
    return l;
}

int AMMusicFixProcessor::getNumPrograms() { return (int) std::size (kPresets); }

const juce::String AMMusicFixProcessor::getProgramName (int index)
{
    return juce::isPositiveAndBelow (index, getNumPrograms()) ? kPresets[index].name : "";
}

void AMMusicFixProcessor::setCurrentProgram (int index)
{
    if (! juce::isPositiveAndBelow (index, getNumPrograms()))
        return;
    currentProgram = index;
    const auto& v = kPresets[index];
    auto set = [this] (const char* id, float value)
    {
        if (auto* prm = apvts.getParameter (id))
            prm->setValueNotifyingHost (prm->convertTo0to1 (value));
    };
    set ("lpHz", v.lowpassHz);
    set ("b1On", v.b1On ? 1.0f : 0.0f); set ("b1Hz", v.b1Hz); set ("b1Gain", v.b1Gain);
    set ("b2On", v.b2On ? 1.0f : 0.0f); set ("b2Hz", v.b2Hz); set ("b2Gain", v.b2Gain); set ("b2Q", v.b2Q);
    set ("b3On", v.b3On ? 1.0f : 0.0f); set ("b3Hz", v.b3Hz); set ("b3Gain", v.b3Gain);
    set ("reverb", v.reverb); set ("width", v.width); set ("exciter", v.exciter);
    set ("exMode", (float) v.exciterMode); set ("maximizer", v.maximizer);
    set ("outDb", v.outputDb); set ("volDb", v.volumeDb); set ("bypass", 0.0f);
}

bool AMMusicFixProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    const auto out = layouts.getMainOutputChannelSet();
    if (out != layouts.getMainInputChannelSet())
        return false;
    return out == juce::AudioChannelSet::mono() || out == juce::AudioChannelSet::stereo();
}

void AMMusicFixProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    sr = sampleRate;
    updateFilters();
    juce::dsp::ProcessSpec spec { sampleRate, (juce::uint32) samplesPerBlock,
                                  (juce::uint32) juce::jmax (1, getTotalNumOutputChannels()) };
    for (int c = 0; c < maxCh; ++c)
    {
        lowpass[c].reset(); eqLow[c].reset(); eqMid[c].reset(); eqHigh[c].reset(); exciterHP[c].reset();
    }
    reverb.setSampleRate (sampleRate);
    reverb.reset();
    limiter.prepare (spec);
    limiter.setThreshold (-0.3f);
    limiter.setRelease (60.0f);

    for (auto* s : { &volumeGain, &outputGain, &makeupGain })
        s->reset (sampleRate, 0.02);
    volumeGain.setCurrentAndTargetValue (juce::Decibels::decibelsToGain (p ("volDb"), -100.0f));
    outputGain.setCurrentAndTargetValue (juce::Decibels::decibelsToGain (p ("outDb")));
    makeupGain.setCurrentAndTargetValue (juce::Decibels::decibelsToGain (p ("maximizer") * 0.12f));
}

void AMMusicFixProcessor::updateFiltersIfNeeded()
{
    static const char* ids[] = { "lpHz", "b1Hz", "b1Gain", "b2Hz", "b2Gain", "b2Q",
                                 "b3Hz", "b3Gain", "reverb", "exMode" };
    bool changed = false;
    for (size_t i = 0; i < std::size (ids); ++i)
    {
        const float v = p (ids[i]);
        if (v != lastFilterParams[i]) { lastFilterParams[i] = v; changed = true; }
    }
    if (changed)
        updateFilters();
}

void AMMusicFixProcessor::updateFilters()
{
    const auto nyq = (float) sr * 0.49f;
    auto lp = Coeffs::makeLowPass (sr, juce::jmin (p ("lpHz"), nyq), 0.70710678f);
    auto lo = Coeffs::makeLowShelf (sr, juce::jmin (p ("b1Hz"), nyq), 0.70710678f,
                                    juce::Decibels::decibelsToGain (p ("b1Gain")));
    auto mid = Coeffs::makePeakFilter (sr, juce::jmin (p ("b2Hz"), nyq), p ("b2Q"),
                                       juce::Decibels::decibelsToGain (p ("b2Gain")));
    auto hi = Coeffs::makeHighShelf (sr, juce::jmin (p ("b3Hz"), nyq), 0.70710678f,
                                     juce::Decibels::decibelsToGain (p ("b3Gain")));
    // Banda do exciter: harmônicos são gerados acima de ~3 kHz (Retro/Tape/Tube).
    const float exHz[] = { 2000.0f, 3000.0f, 4000.0f };
    auto ex = Coeffs::makeHighPass (sr, juce::jmin (exHz[(int) p ("exMode")], nyq), 0.70710678f);
    for (int c = 0; c < maxCh; ++c)
    {
        *lowpass[c].coefficients = *lp;
        *eqLow[c].coefficients = *lo;
        *eqMid[c].coefficients = *mid;
        *eqHigh[c].coefficients = *hi;
        *exciterHP[c].coefficients = *ex;
    }

    juce::Reverb::Parameters rp;
    const float amt = p ("reverb") / 100.0f;
    rp.roomSize = 0.6f;
    rp.damping = 0.5f;
    rp.wetLevel = amt * 0.5f;
    rp.dryLevel = 1.0f - amt * 0.3f;
    rp.width = 1.0f;
    reverb.setParameters (rp);
}

void AMMusicFixProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    const int numCh = juce::jmin (buffer.getNumChannels(), maxCh);
    const int n = buffer.getNumSamples();
    for (int c = getTotalNumInputChannels(); c < buffer.getNumChannels(); ++c)
        buffer.clear (c, 0, n);

    if (p ("bypass") > 0.5f || n == 0)
        return;

    updateFiltersIfNeeded();

    // 1) Lowpass
    for (int c = 0; c < numCh; ++c)
    {
        auto* d = buffer.getWritePointer (c);
        for (int i = 0; i < n; ++i)
            d[i] = lowpass[c].processSample (d[i]);
    }

    // 2) Mastering — EQ (low shelf / peak / high shelf)
    const bool b1 = p ("b1On") > 0.5f, b2 = p ("b2On") > 0.5f, b3 = p ("b3On") > 0.5f;
    for (int c = 0; c < numCh; ++c)
    {
        auto* d = buffer.getWritePointer (c);
        for (int i = 0; i < n; ++i)
        {
            float x = d[i];
            if (b1) x = eqLow[c].processSample (x);
            if (b2) x = eqMid[c].processSample (x);
            if (b3) x = eqHigh[c].processSample (x);
            d[i] = x;
        }
    }

    // Mastering — Reverb
    if (p ("reverb") > 0.0f)
    {
        if (numCh >= 2)
            reverb.processStereo (buffer.getWritePointer (0), buffer.getWritePointer (1), n);
        else
            reverb.processMono (buffer.getWritePointer (0), n);
    }

    // Mastering — Widener (M/S: -100 = mono, 0 = original, +100 = lados x2)
    if (numCh >= 2)
    {
        const float w = p ("width");
        const float sideGain = 1.0f + w / 100.0f;
        if (std::abs (sideGain - 1.0f) > 1.0e-4f)
        {
            auto* l = buffer.getWritePointer (0);
            auto* r = buffer.getWritePointer (1);
            for (int i = 0; i < n; ++i)
            {
                const float m = 0.5f * (l[i] + r[i]);
                const float s = 0.5f * (l[i] - r[i]) * sideGain;
                l[i] = m + s;
                r[i] = m - s;
            }
        }
    }

    // Mastering — Exciter (saturação harmônica das altas, somada ao sinal)
    const float exAmt = p ("exciter") / 100.0f;
    if (exAmt > 0.0f)
    {
        const int mode = (int) p ("exMode");
        const float drive = mode == 0 ? 6.0f : (mode == 1 ? 3.0f : 4.0f);
        const float bias = mode == 2 ? 0.15f : 0.0f; // tube: harmônicos pares
        for (int c = 0; c < numCh; ++c)
        {
            auto* d = buffer.getWritePointer (c);
            for (int i = 0; i < n; ++i)
            {
                const float h = exciterHP[c].processSample (d[i]);
                const float sat = std::tanh (drive * h + bias) - std::tanh (bias);
                d[i] += exAmt * 0.5f * (sat / drive);
            }
        }
    }

    // Mastering — Loudness Maximizer (ganho até +12 dB em 100% + limiter -0.3 dBFS)
    makeupGain.setTargetValue (juce::Decibels::decibelsToGain (p ("maximizer") * 0.12f));
    outputGain.setTargetValue (juce::Decibels::decibelsToGain (p ("outDb")));
    volumeGain.setTargetValue (juce::Decibels::decibelsToGain (p ("volDb"), -100.0f));

    if (p ("maximizer") > 0.0f)
    {
        for (int i = 0; i < n; ++i)
        {
            const float g = makeupGain.getNextValue();
            for (int c = 0; c < numCh; ++c)
                buffer.getWritePointer (c)[i] *= g;
        }
        juce::dsp::AudioBlock<float> block (buffer.getArrayOfWritePointers(), (size_t) numCh, (size_t) n);
        limiter.process (juce::dsp::ProcessContextReplacing<float> (block));
    }
    else
    {
        makeupGain.skip (n);
    }

    // Mastering — Output Gain, depois Volume (clip volume do Premiere)
    for (int i = 0; i < n; ++i)
    {
        const float g = outputGain.getNextValue() * volumeGain.getNextValue();
        for (int c = 0; c < numCh; ++c)
            buffer.getWritePointer (c)[i] *= g;
    }
}

juce::AudioProcessorEditor* AMMusicFixProcessor::createEditor()
{
    return new juce::GenericAudioProcessorEditor (*this);
}

void AMMusicFixProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    if (auto xml = apvts.copyState().createXml())
        copyXmlToBinary (*xml, destData);
}

void AMMusicFixProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    if (auto xml = getXmlFromBinary (data, sizeInBytes))
        if (xml->hasTagName (apvts.state.getType()))
            apvts.replaceState (juce::ValueTree::fromXml (*xml));
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AMMusicFixProcessor();
}
