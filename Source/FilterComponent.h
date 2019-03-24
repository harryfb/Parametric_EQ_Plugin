/*
  ==============================================================================

    FilterComponent.h
    Created: 25 Feb 2019 9:39:15pm
    Author:  Harry Bullough

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "CustomLookAndFeel.h"

//==============================================================================
/*
*/
//class CustomLookAndFeel     : public LookAndFeel_V4
//{
//public:
//    CustomLookAndFeel()
//    {
//        CustomLookAndFeel::setColour (Slider::thumbColourId, Colours::silver);
//    }
//
//private:
//
//};

class FilterComponent    : public Component
{
public:
    FilterComponent();
    ~FilterComponent();

    void paint (Graphics&) override;
    void resized () override;
    void setFilterParameters (float, float, String);
    void setTickLabels(StringArray);
    
    Slider cutoffFreq;
    Slider width;
    Slider height;

private:
    Rectangle <float> perimeterBox;
    Rectangle <float> freqBandBox;
    Rectangle <float> freqHzLabelBox;
    float edgeSpacing;
    
    FrontPanelLookAndFeel  frontPanelLookAndFeel;
    
    String freqBand;
    
    //Cutoff frequency section parameters
//    Slider cutoffFreq;
    const float bottomTickSpace = 60.0f;
    float startAngleDegrees;
    float endAngleDegrees;
    StringArray cutoffFreqTickLabels;    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
