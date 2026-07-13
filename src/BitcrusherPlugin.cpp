#include "BitcrusherPlugin.h"
#include "BitcrusherEditor.h"

DoomBitcrusherAudioProcessor::DoomBitcrusherAudioProcessor()
    : AudioProcessor(BusesProperties()
                     .withInput("Input", juce::AudioChannelSet::stereo(), true)
                     .withOutput("Output", juce::AudioChannelSet::stereo(), true))
{
    apvts = std::make_unique<juce::AudioProcessorValueTreeState>(*this, nullptr, juce::Identifier("DoomBitcrusher"), createParameterLayout());
}

DoomBitcrusherAudioProcessor::~DoomBitcrusherAudioProcessor() = default;

juce::AudioProcessorValueTreeState::ParameterLayout DoomBitcrusherAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // Bit Depth: 1-16 bits, default 8
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID("bitDepth", 1),
        "Bit Depth",
        juce::NormalisableRange<float>(1.0f, 16.0f, 0.1f),
        8.0f,
        juce::AudioParameterFloatAttributes().withLabel("bits")
    ));

    // Sample Rate Reduction: 1x to 100x downsampling
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID("downsample", 1),
        "Downsample",
        juce::NormalisableRange<float>(1.0f, 100.0f, 0.1f),
        1.0f,
        juce::AudioParameterFloatAttributes().withLabel("x")
    ));

    // Drive/Saturation: 0-100%
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID("drive", 1),
        "Drive",
        juce::NormalisableRange<float>(0.0f, 100.0f, 0.1f),
        0.0f,
        juce::AudioParameterFloatAttributes().withLabel("%")
    ));

    // Wet/Dry Mix: 0-100%
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID("mix", 1),
        "Mix",
        juce::NormalisableRange<float>(0.0f, 100.0f, 0.1f),
        100.0f,
        juce::AudioParameterFloatAttributes().withLabel("%")
    ));

    // Output Gain: -24 to +24 dB
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID("output", 1),
        "Output",
        juce::NormalisableRange<float>(-24.0f, 24.0f, 0.1f),
        0.0f,
        juce::AudioParameterFloatAttributes().withLabel("dB")
    ));

    return { params.begin(), params.end() };
}

void DoomBitcrusherAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    currentSampleRate = static_cast<float>(sampleRate);
    
    // Reset sample rate reduction state
    for (int ch = 0; ch < 2; ++ch)
    {
        sampleRateCounter[ch] = 0.0f;
        lastSample[ch] = 0.0f;
    }
}

void DoomBitcrusherAudioProcessor::releaseResources()
{
    // Nothing to release
}

void DoomBitcrusherAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    
    const int numChannels = buffer.getNumChannels();
    const int numSamples = buffer.getNumSamples();

    // Get parameter values
    const float bitDepth = apvts->getRawParameterValue("bitDepth")->load();
    const float downsample = apvts->getRawParameterValue("downsample")->load();
    const float drive = apvts->getRawParameterValue("drive")->load() / 100.0f;
    const float mix = apvts->getRawParameterValue("mix")->load() / 100.0f;
    const float outputGain = juce::Decibels::decibelsToGain(apvts->getRawParameterValue("output")->load());

    // Calculate quantization levels
    const float quantLevels = std::pow(2.0f, bitDepth - 1.0f);

    for (int channel = 0; channel < numChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);
        const int chIndex = channel % 2; // Handle mono or >2 channels safely

        for (int sample = 0; sample < numSamples; ++sample)
        {
            float inputSample = channelData[sample];
            float processedSample = inputSample;

            // Apply drive/saturation (soft clipping)
            if (drive > 0.0f)
            {
                const float driveAmount = drive * 10.0f; // Scale up for effect
                processedSample = std::tanh(processedSample * (1.0f + driveAmount));
            }

            // Bit depth reduction (quantization)
            processedSample = std::round(processedSample * quantLevels) / quantLevels;

            // Sample rate reduction (downsampling)
            if (downsample > 1.0f)
            {
                sampleRateCounter[chIndex] += 1.0f;
                
                if (sampleRateCounter[chIndex] >= downsample)
                {
                    lastSample[chIndex] = processedSample;
                    sampleRateCounter[chIndex] = 0.0f;
                }
                
                processedSample = lastSample[chIndex];
            }

            // Wet/dry mix
            processedSample = (processedSample * mix) + (inputSample * (1.0f - mix));

            // Output gain
            processedSample *= outputGain;

            channelData[sample] = processedSample;
        }
    }
}

juce::AudioProcessorEditor* DoomBitcrusherAudioProcessor::createEditor()
{
    return new DoomBitcrusherEditor(*this);
}

void DoomBitcrusherAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = apvts->copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void DoomBitcrusherAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(apvts->state.getType()))
            apvts->replaceState(juce::ValueTree::fromXml(*xmlState));
}

// This creates the plugin factory function
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DoomBitcrusherAudioProcessor();
}
