/*
  ==============================================================================

    FilterComponent.cpp
    Created: 25 Feb 2019 9:39:15pm
    Author:  Harry Bullough

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent()
{
    addAndMakeVisible (cutoffFreq);
    addAndMakeVisible (width);
    addAndMakeVisible (height);
    
    cutoffFreq.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    width.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    height.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    
    cutoffFreq.setLookAndFeel (&frontPanelLookAndFeel);
    width.setLookAndFeel(&frontPanelLookAndFeel);
    height.setLookAndFeel(&frontPanelLookAndFeel);
    
    startAngleDegrees = 180.0f + (bottomTickSpace / 2);
    endAngleDegrees = startAngleDegrees + 360.0f - bottomTickSpace;
    
    cutoffFreq.setRotaryParameters((startAngleDegrees / 360) * MathConstants<float>::twoPi, (endAngleDegrees / 360) * MathConstants<float>::twoPi, true);
    
    width.setRange(0, 10);
    height.setRange(0, 10);
    
    cutoffFreq.setTextValueSuffix (" Hz");
    width.setTextValueSuffix("Oct");
    height.setTextValueSuffix("dB");
    
    cutoffFreq.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    width.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    height.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);

    edgeSpacing = 30;
}

FilterComponent::~FilterComponent()
{
    //Clear up references to look and feel object, before they are destroyed
    cutoffFreq.setLookAndFeel (nullptr);
    width.setLookAndFeel (nullptr);
    height.setLookAndFeel(nullptr);
}

void FilterComponent::paint (Graphics& g)
{
    Font freqBandFont("Helvetica", 12, Font::bold);  //Hangangche
    Font knobLabelFont("Helvetica", 10, Font::bold);
    Font tickFont("Helvetica", 10, Font::plain);

    perimeterBox.setBounds (0, 0, getWidth(), getHeight());
    
    g.setColour (Colours::white);
    g.drawRoundedRectangle (perimeterBox, 5, 4);
    

    g.setFont(knobLabelFont);
    g.drawText ("FREQUENCY Hz", freqHzLabelBox, Justification::centred);
    g.setFont(freqBandFont);
    g.drawText (freqBand, freqBandBox, Justification::centred);
    

    auto radius = 30.0f;                                                //Could be pulled out to .h as const
    auto centreX = getWidth() / 2;
    auto centreY = (cutoffFreq.getHeight() / 2) + edgeSpacing;
    float angleDegrees;
    float angleRadians;
    
    Path tick;
    auto tickLength = radius;
    auto tickThickness = 0.75f;                                        //Could be pulled out to .h as const
    
    g.setColour(Colours::whitesmoke);
    for (int i = 0; i < cutoffFreqTickLabels.size(); i++)
    {
        //Find the angle of the current tick from the origin of the rotary slider
        angleDegrees = startAngleDegrees + ((endAngleDegrees - startAngleDegrees) * i / (cutoffFreqTickLabels.size() - 1));
        if (angleDegrees > 360) angleDegrees -= 360;
        angleRadians = (angleDegrees / 360) * MathConstants<float>::twoPi;
        
        //Create the tick path and draw it
        tick.addRectangle (-tickThickness * 0.5f, -radius, tickThickness, tickLength);
        tick.applyTransform (AffineTransform::rotation (angleRadians).translated (centreX, centreY));
        g.strokePath(tick, PathStrokeType(tickThickness));
        tick.clear();
        
        //Add a longer version of the same path to derive the centre position of the text label
        tick.addRectangle (-tickThickness * 0.5f, -radius - 10, tickThickness, tickLength);
        tick.applyTransform (AffineTransform::rotation (angleRadians).translated (centreX, centreY));
        
        //Find the end point of the path & centre the label here
        Point <float> endPoint;
        endPoint = tick.getPointAlongPath(radius);
        
        Rectangle<float> tickText;
        tickText.setSize(50, 10);
        tickText.setCentre(endPoint.getX(), endPoint.getY());
        g.setFont(tickFont);
        
        //Determine the label justifiction based on the angle of the tick being drawn
        if (angleDegrees > 45 && angleDegrees < 135)
        {
            tickText.setLeft(endPoint.getX() - 4);
            g.drawText(cutoffFreqTickLabels.operator[](i), tickText, Justification::left);
        }
        else if (angleDegrees > 225 && angleDegrees <  315)
        {
            tickText.setRight(endPoint.getX() + 4);
            g.drawText(cutoffFreqTickLabels.operator[](i), tickText, Justification::right);
        }
        else
        {
            g.drawText(cutoffFreqTickLabels.operator[](i), tickText, Justification::centred);
        }
        tick.clear();

    }
}

void FilterComponent::resized()
{
    cutoffFreq.setBounds (0 , 0, getWidth() / 2, 50);
    cutoffFreq.setCentrePosition (getWidth() / 2, (cutoffFreq.getHeight() / 2) + edgeSpacing);

    freqHzLabelBox.setBounds(0, 0, 100, 10);
    freqHzLabelBox.setCentre(getWidth() / 2, (getHeight() / 2) + 5);
    
    freqBandBox.setBounds (0, 0, 30, 10);
    freqBandBox.setCentre (getWidth() / 2, (getHeight() / 2) + 30);
    
    width.setBounds (0, 0, getWidth() / 2, 50);
    width.setCentrePosition(width.getWidth() / 2, getHeight() - (width.getHeight() / 2) - edgeSpacing);
    
    height.setBounds (0, 0, getWidth() / 2, 50);
    height.setCentrePosition(getWidth() - (width.getWidth() / 2), getHeight() - (height.getHeight() / 2) - edgeSpacing);
}

void FilterComponent::setFilterParameters(float rangeLow, float rangeHigh, String inputFreqBand)
{
    NormalisableRange<double> sliderMapping (rangeLow, rangeHigh, 0, 1, 2.2, false);
    cutoffFreq.setNormalisableRange (sliderMapping);
    freqBand = inputFreqBand;
}

void FilterComponent::setTickLabels(StringArray tickLabels)
{
    cutoffFreqTickLabels = tickLabels;
}
