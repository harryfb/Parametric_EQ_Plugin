/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "FilterComponent.h"

//==============================================================================
/**
*/
class MoogParametricEqAudioProcessorEditor  : public AudioProcessorEditor,
                                              public Slider::Listener
{
public:
    MoogParametricEqAudioProcessorEditor (MoogParametricEqAudioProcessor&);
    ~MoogParametricEqAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void sliderValueChanged (Slider* slider) override
    {
        if (slider == &lowBandComponent.cutoffFreq)
        {
            processor.lowCutoff = lowBandComponent.cutoffFreq.getValue();
        }
        else if (slider == &midBandComponent.cutoffFreq)
        {
            processor.midCutoff = midBandComponent.cutoffFreq.getValue();
        }
        else
        {
            processor.highCutoff = highBandComponent.cutoffFreq.getValue();
        }
    }

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MoogParametricEqAudioProcessor& processor;
    
    int leftRightMargin;
    int topBottomMargin;
    int numberOfSections;
    int filterSectionWidth;
    Rectangle <float> perimeterBox;
    Rectangle <float> fixingHoleTopLeft;
    Rectangle <float> fixingHoleTopRight;
    Rectangle <float> fixingHoleBottomLeft;
    Rectangle <float> fixingHoleBottomRight;
    
    Rectangle <float> modelAndBrandSection;
    Rectangle <float> modelNameBox;
    
    Font modelFont;
    AttributedString modelName;
    
    FilterComponent lowBandComponent;
    FilterComponent midBandComponent;
    FilterComponent highBandComponent;
    
    StringArray lowBandTickLabels;
    StringArray midBandTickLabels;
    StringArray highBandTickLabels;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MoogParametricEqAudioProcessorEditor)
};
