/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ChipsAudioProcessorEditor::ChipsAudioProcessorEditor (ChipsAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

	addAndMakeVisible(sVolume);
	sVolume.setSliderStyle(Slider::SliderStyle::LinearBar);
	sVolume.onValueChange = [this] 
	{
		processor.setAmplitude(sVolume.getValue());
	};
	sVolume.setRange({ 0, 100 }, 1);
}

ChipsAudioProcessorEditor::~ChipsAudioProcessorEditor()
{
}

//==============================================================================
void ChipsAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void ChipsAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

	auto area = getLocalBounds();
	sVolume.setBounds(area.removeFromTop(50));
}
