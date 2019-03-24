/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "FilterComponent.h"

//==============================================================================
MoogParametricEqAudioProcessorEditor::MoogParametricEqAudioProcessorEditor (MoogParametricEqAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)

{
    leftRightMargin = 50;
    numberOfSections = 5;
    fixingHoleTopLeft.setSize (18, 8);
    fixingHoleTopRight.setSize (18, 8);
    fixingHoleBottomLeft.setSize (18, 8);
    fixingHoleBottomRight.setSize (18, 8);
    
    setSize (1055, 200);        //1040, 180
    setResizable (true, true);
    
    lowBandComponent.cutoffFreq.addListener (this);
    midBandComponent.cutoffFreq.addListener (this);
    highBandComponent.cutoffFreq.addListener (this);
    

    addAndMakeVisible (lowBandComponent);
    addAndMakeVisible (midBandComponent);
    addAndMakeVisible (highBandComponent);
    
    lowBandComponent.setFilterParameters (31, 4000, "LOW");
    midBandComponent.setFilterParameters(62, 8000, "MID");
    highBandComponent.setFilterParameters(125, 18000, "HIGH");
    
    lowBandTickLabels.add("31");
    lowBandTickLabels.add("62");
    lowBandTickLabels.add("125");
    lowBandTickLabels.add("250");
    lowBandTickLabels.add("500");
    lowBandTickLabels.add("1K");
    lowBandTickLabels.add("2K");
    lowBandTickLabels.add("4K");
    
    midBandTickLabels.add("62");
    midBandTickLabels.add("125");
    midBandTickLabels.add("250");
    midBandTickLabels.add("500");
    midBandTickLabels.add("1K");
    midBandTickLabels.add("2K");
    midBandTickLabels.add("4K");
    midBandTickLabels.add("8K");
    
    highBandTickLabels.add("125");
    highBandTickLabels.add("250");
    highBandTickLabels.add("500");
    highBandTickLabels.add("1K");
    highBandTickLabels.add("2K");
    highBandTickLabels.add("4K");
    highBandTickLabels.add("8K");
    highBandTickLabels.add("16K");
    
    lowBandComponent.setTickLabels(lowBandTickLabels);
    midBandComponent.setTickLabels(midBandTickLabels);
    highBandComponent.setTickLabels(highBandTickLabels);
    
    modelFont.setTypefaceName ("Times New Roman");
    modelFont.setBold (true);
    modelFont.setHeight (15);
    modelFont.setHorizontalScale (5);
    modelName.setText ("Three Band Parametric Equaliser");
    modelName.setFont (modelFont);
    modelName.setWordWrap (AttributedString::WordWrap::byWord);
}

MoogParametricEqAudioProcessorEditor::~MoogParametricEqAudioProcessorEditor()
{
}

//==============================================================================
void MoogParametricEqAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::black);
    g.setColour(Colours::white);
    
    //Draw perimeter of front panel
    g.drawRoundedRectangle (perimeterBox, 0, 2);
    
    //Draw four rackmount holes in the corners of the GUI
    g.fillRoundedRectangle(fixingHoleTopLeft, 4);
    g.fillRoundedRectangle(fixingHoleTopRight, 4);
    g.fillRoundedRectangle(fixingHoleBottomLeft, 4);
    g.fillRoundedRectangle(fixingHoleBottomRight, 4);
    
    //Draw brand and model section
    g.drawRoundedRectangle(modelAndBrandSection, 5, 4);
    g.drawText(modelName.getText(), modelNameBox, Justification::centred);

}

void MoogParametricEqAudioProcessorEditor::resized()
{

    perimeterBox.setBounds(leftRightMargin - 1, 1, getWidth() - ((leftRightMargin - 1) * 2), getHeight() - 1);
    
    filterSectionWidth = (getWidth() - (leftRightMargin * 2)) / numberOfSections;
    
    lowBandComponent.setBounds(leftRightMargin + (filterSectionWidth * 0), 0, filterSectionWidth, getHeight());
    midBandComponent.setBounds(leftRightMargin + (filterSectionWidth * 1), 0, filterSectionWidth, getHeight());
    highBandComponent.setBounds(leftRightMargin + (filterSectionWidth * 2), 0, filterSectionWidth, getHeight());
    
    fixingHoleTopLeft.setCentre(leftRightMargin / 2, (fixingHoleTopLeft.getHeight() / 2) + 20);
    fixingHoleTopRight.setCentre(leftRightMargin / 2, getHeight() - (fixingHoleTopRight.getHeight() / 2) - 20);
    fixingHoleBottomLeft.setCentre(getWidth() -(leftRightMargin / 2), (fixingHoleBottomLeft.getHeight() / 2) + 20);
    fixingHoleBottomRight.setCentre(getWidth() -(leftRightMargin / 2), getHeight() - (fixingHoleBottomRight.getHeight() / 2) - 20);
    
    modelAndBrandSection.setBounds(leftRightMargin + (filterSectionWidth * 3), 0, filterSectionWidth, getHeight());
    modelNameBox.setBounds(leftRightMargin + (filterSectionWidth * 3), modelAndBrandSection.getHeight()/2, filterSectionWidth, modelAndBrandSection.getHeight()/2);
}
