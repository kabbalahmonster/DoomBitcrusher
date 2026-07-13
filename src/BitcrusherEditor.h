/**
 * DoomBitcrusher Editor - UI Component
 * Custom look and feel with modern/grime aesthetic
 */

#pragma once

#include <JuceHeader.h>
#include "BitcrusherPlugin.h"

// Custom LookAndFeel for the grime aesthetic
class GrimeLookAndFeel : public juce::LookAndFeel_V4
{
public:
    GrimeLookAndFeel();
    
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                          float sliderPosProportional, float rotaryStartAngle,
                          float rotaryEndAngle, juce::Slider& slider) override;
    
    void drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
                          float sliderPos, float minSliderPos, float maxSliderPos,
                          const juce::Slider::SliderStyle style, juce::Slider& slider) override;

private:
    juce::Colour accentColour;
    juce::Colour backgroundColour;
};

class DoomBitcrusherEditor : public juce::AudioProcessorEditor
{
public:
    DoomBitcrusherEditor(DoomBitcrusherAudioProcessor&);
    ~DoomBitcrusherEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    DoomBitcrusherAudioProcessor& audioProcessor;
    
    // Custom look and feel
    GrimeLookAndFeel grimeLAF;
    
    // UI Components
    juce::Slider bitDepthSlider;
    juce::Slider downsampleSlider;
    juce::Slider driveSlider;
    juce::Slider mixSlider;
    juce::Slider outputSlider;
    
    juce::Label bitDepthLabel;
    juce::Label downsampleLabel;
    juce::Label driveLabel;
    juce::Label mixLabel;
    juce::Label outputLabel;
    juce::Label titleLabel;
    
    // Parameter attachments (connect UI to DSP)
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> bitDepthAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> downsampleAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> driveAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> outputAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DoomBitcrusherEditor)
};
