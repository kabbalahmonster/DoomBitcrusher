#include "BitcrusherEditor.h"

// GrimeLookAndFeel Implementation
GrimeLookAndFeel::GrimeLookAndFeel()
{
    // Grime aesthetic colors - dark with harsh accents
    accentColour = juce::Colour(0xFFFF6B35);      // Burnt orange
    backgroundColour = juce::Colour(0xFF1A1A1A);  // Dark charcoal
    
    setColour(juce::Slider::thumbColourId, accentColour);
    setColour(juce::Slider::rotarySliderFillColourId, accentColour);
    setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour(0xFF333333));
    setColour(juce::Slider::trackColourId, juce::Colour(0xFF444444));
    setColour(juce::Label::textColourId, juce::Colour(0xFFCCCCCC));
}

void GrimeLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                                        float sliderPosProportional, float rotaryStartAngle,
                                        float rotaryEndAngle, juce::Slider& slider)
{
    const float radius = juce::jmin(width / 2, height / 2) - 4.0f;
    const float centreX = x + width * 0.5f;
    const float centreY = y + height * 0.5f;
    const float rx = centreX - radius;
    const float ry = centreY - radius;
    const float rw = radius * 2.0f;
    const float angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);

    // Background arc
    g.setColour(juce::Colour(0xFF2A2A2A));
    g.fillEllipse(rx, ry, rw, rw);
    
    // Outline
    g.setColour(juce::Colour(0xFF444444));
    g.drawEllipse(rx, ry, rw, rw, 2.0f);

    // Value arc
    juce::Path valueArc;
    valueArc.addCentredArc(centreX, centreY, radius * 0.85f, radius * 0.85f,
                           0.0f, rotaryStartAngle, angle, true);
    g.setColour(accentColour);
    g.strokePath(valueArc, juce::PathStrokeType(4.0f));

    // Knob indicator
    juce::Path indicator;
    const float indicatorLength = radius * 0.6f;
    const float indicatorX = centreX + indicatorLength * std::cos(angle - juce::MathConstants<float>::halfPi);
    const float indicatorY = centreY + indicatorLength * std::sin(angle - juce::MathConstants<float>::halfPi);
    
    indicator.addLineSegment(juce::Line<float>(centreX, centreY, indicatorX, indicatorY), 3.0f);
    g.setColour(juce::Colour(0xFFEEEEEE));
    g.strokePath(indicator, juce::PathStrokeType(3.0f));

    // Center dot
    g.setColour(juce::Colour(0xFF333333));
    g.fillEllipse(centreX - 4.0f, centreY - 4.0f, 8.0f, 8.0f);
}

void GrimeLookAndFeel::drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
                                        float sliderPos, float minSliderPos, float maxSliderPos,
                                        const juce::Slider::SliderStyle style, juce::Slider& slider)
{
    LookAndFeel_V4::drawLinearSlider(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
}

// Editor Implementation
DoomBitcrusherEditor::DoomBitcrusherEditor(DoomBitcrusherAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    // Set custom look and feel
    setLookAndFeel(&grimeLAF);
    
    // Title
    titleLabel.setText("DOOM BITCRUSHER", juce::dontSendNotification);
    titleLabel.setFont(juce::Font(juce::Font::getDefaultSansSerifFontName(), 24.0f, juce::Font::bold));
    titleLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFFF6B35));
    titleLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(titleLabel);

    // Bit Depth Slider
    bitDepthSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    bitDepthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    bitDepthSlider.setRange(1.0, 16.0, 0.1);
    bitDepthSlider.setValue(8.0);
    addAndMakeVisible(bitDepthSlider);
    
    bitDepthLabel.setText("BIT DEPTH", juce::dontSendNotification);
    bitDepthLabel.setJustificationType(juce::Justification::centred);
    bitDepthLabel.attachToComponent(&bitDepthSlider, false);
    addAndMakeVisible(bitDepthLabel);

    // Downsample Slider
    downsampleSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    downsampleSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    downsampleSlider.setRange(1.0, 100.0, 0.1);
    downsampleSlider.setValue(1.0);
    addAndMakeVisible(downsampleSlider);
    
    downsampleLabel.setText("DOWNSAMPLE", juce::dontSendNotification);
    downsampleLabel.setJustificationType(juce::Justification::centred);
    downsampleLabel.attachToComponent(&downsampleSlider, false);
    addAndMakeVisible(downsampleLabel);

    // Drive Slider
    driveSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    driveSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    driveSlider.setRange(0.0, 100.0, 0.1);
    driveSlider.setValue(0.0);
    addAndMakeVisible(driveSlider);
    
    driveLabel.setText("DRIVE", juce::dontSendNotification);
    driveLabel.setJustificationType(juce::Justification::centred);
    driveLabel.attachToComponent(&driveSlider, false);
    addAndMakeVisible(driveLabel);

    // Mix Slider
    mixSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    mixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    mixSlider.setRange(0.0, 100.0, 0.1);
    mixSlider.setValue(100.0);
    addAndMakeVisible(mixSlider);
    
    mixLabel.setText("MIX", juce::dontSendNotification);
    mixLabel.setJustificationType(juce::Justification::centred);
    mixLabel.attachToComponent(&mixSlider, false);
    addAndMakeVisible(mixLabel);

    // Output Slider
    outputSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    outputSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    outputSlider.setRange(-24.0, 24.0, 0.1);
    outputSlider.setValue(0.0);
    addAndMakeVisible(outputSlider);
    
    outputLabel.setText("OUTPUT", juce::dontSendNotification);
    outputLabel.setJustificationType(juce::Justification::centred);
    outputLabel.attachToComponent(&outputSlider, false);
    addAndMakeVisible(outputLabel);

    // Attach parameters
    auto& apvts = audioProcessor.getAPVTS();
    bitDepthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "bitDepth", bitDepthSlider);
    downsampleAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "downsample", downsampleSlider);
    driveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "drive", driveSlider);
    mixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "mix", mixSlider);
    outputAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "output", outputSlider);

    // Window size
    setSize(500, 400);
}

DoomBitcrusherEditor::~DoomBitcrusherEditor()
{
    setLookAndFeel(nullptr);
}

void DoomBitcrusherEditor::paint(juce::Graphics& g)
{
    // Background gradient
    juce::ColourGradient gradient(
        juce::Colour(0xFF1A1A1A), 0.0f, 0.0f,
        juce::Colour(0xFF0D0D0D), 0.0f, static_cast<float>(getHeight()),
        false
    );
    g.setGradientFill(gradient);
    g.fillAll();
    
    // Subtle border
    g.setColour(juce::Colour(0xFF333333));
    g.drawRect(getLocalBounds(), 2);
}

void DoomBitcrusherEditor::resized()
{
    auto area = getLocalBounds().reduced(20);
    
    // Title at top
    titleLabel.setBounds(area.removeFromTop(40));
    area.removeFromTop(20);
    
    // Knob layout: 3 on top row, 2 on bottom row
    auto topRow = area.removeFromTop(120);
    auto bottomRow = area.removeFromTop(120);
    
    const int knobWidth = 100;
    const int knobHeight = 100;
    
    // Top row: Bit Depth, Downsample, Drive
    bitDepthSlider.setBounds(topRow.removeFromLeft(knobWidth).withSizeKeepingCentre(knobWidth, knobHeight));
    topRow.removeFromLeft(20);
    downsampleSlider.setBounds(topRow.removeFromLeft(knobWidth).withSizeKeepingCentre(knobWidth, knobHeight));
    topRow.removeFromLeft(20);
    driveSlider.setBounds(topRow.removeFromLeft(knobWidth).withSizeKeepingCentre(knobWidth, knobHeight));
    
    // Bottom row: Mix, Output (centered)
    bottomRow.removeFromLeft(50);
    mixSlider.setBounds(bottomRow.removeFromLeft(knobWidth).withSizeKeepingCentre(knobWidth, knobHeight));
    bottomRow.removeFromLeft(40);
    outputSlider.setBounds(bottomRow.removeFromLeft(knobWidth).withSizeKeepingCentre(knobWidth, knobHeight));
}
