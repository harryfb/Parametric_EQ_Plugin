//
//  CustomLookAndFeel.h
//  MoogParametricEQ
//
//  Created by Harry Bullough on 28/02/2019.
//

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
 */
class FrontPanelLookAndFeel     : public LookAndFeel_V4
{
public:
    FrontPanelLookAndFeel()
    {
        FrontPanelLookAndFeel::setColour (Slider::thumbColourId, Colours::silver);
    }
    
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                           const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
    {
        auto radius = 20;
        auto centreX = x + width  * 0.5f;
        auto centreY = y + height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        
        // fill
        g.setColour (Colours::silver);
        g.fillEllipse (rx, ry, rw, rw);
        
        Path p;
        auto pointerLength = radius;
        auto pointerThickness = 3.0f;
        p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        p.applyTransform (AffineTransform::rotation (angle).translated (centreX, centreY));
        
        // pointer
        g.setColour (Colours::black);
        g.fillPath (p);
        
        
        
    }
    
private:
    
};
