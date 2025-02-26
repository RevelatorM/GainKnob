/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor(NewProjectAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(400, 400);


    auto& params = processor.getParameters();
    juce::AudioParameterFloat* gainParameter = (juce::AudioParameterFloat*)params.getUnchecked(0);

    //.setBounds(50,20,200,200); x,y,w,h - positions
    mGainControlSlider.setBounds(getLocalBounds().withSizeKeepingCentre(300, 300));
    mGainControlSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mGainControlSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    mGainControlSlider.setRange(gainParameter->range.start, gainParameter->range.end);
    mGainControlSlider.setValue(*gainParameter);
    mGainControlSlider.addListener(this);
    addAndMakeVisible(mGainControlSlider);

}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::lightcyan);

    g.setColour(juce::Colours::darkviolet);
    g.setFont(24.0f);
    g.drawFittedText("Gain", getLocalBounds(), juce::Justification::centredTop, 1);
}

void NewProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
void NewProjectAudioProcessorEditor::sliderValueChanged(juce::Slider* slider) {

    auto& params = processor.getParameters();
    if (slider == &mGainControlSlider) {

        juce::AudioParameterFloat* gainParameter = (juce::AudioParameterFloat*)params.getUnchecked(0);
        *gainParameter = mGainControlSlider.getValue();

        DBG("Slider value is changed");
    }

    DBG("Slider value is changed");
}