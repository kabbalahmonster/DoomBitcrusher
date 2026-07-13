/**
 * DoomBitcrusher - Simple Bitcrusher VST Plugin
 * Created for Doomscroller (Cult of the Shell)
 * 
 * Features:
 * - Bit depth reduction (1-16 bits)
 * - Sample rate reduction (downsampling)
 * - Drive/saturation (optional)
 * - Wet/dry mix
 * - Real-time bit depth visualizer
 */

#pragma once

#include <JuceHeader.h>

class DoomBitcrusherAudioProcessor : public juce::AudioProcessor
{
public:
    DoomBitcrusherAudioProcessor();
    ~DoomBitcrusherAudioProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return JucePlugin_Name; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const juce::String getProgramName(int) override { return {}; }
    void changeProgramName(int, const juce::String&) override {}

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    // Parameter getters for UI
    juce::AudioProcessorValueTreeState& getAPVTS() { return *apvts; }

private:
    // DSP Parameters
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    std::unique_ptr<juce::AudioProcessorValueTreeState> apvts;

    // Sample rate reduction state
    float sampleRateCounter[2] = {0.0f, 0.0f};
    float lastSample[2] = {0.0f, 0.0f};
    
    float currentSampleRate = 44100.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DoomBitcrusherAudioProcessor)
};
