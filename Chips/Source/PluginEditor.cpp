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

	// Waveform
	addAndMakeVisible(cWaveform);
	cWaveform.addItemList(StringArray{"Noise","Sine"}, 1);
	cWaveform.onChange = [this]
	{
		processor.setWaveform(cWaveform.getSelectedId());
	};

	// Volume
	addAndMakeVisible(sVolume);
	sVolume.setSliderStyle(Slider::SliderStyle::LinearBar);
	sVolume.onValueChange = [this] 
	{
		processor.setAmplitude(sVolume.getValue());
	};
	sVolume.setRange({ 0, 100 }, 1);

	addAndMakeVisible(lVolume);
	lVolume.attachToComponent(&sVolume, true);
	lVolume.setText(String(TextValues::VOLUME), dontSendNotification);

	// Attack
	addAndMakeVisible(sAttack);
	sAttack.setSliderStyle(Slider::SliderStyle::LinearBar);
	sAttack.onValueChange = [this]
	{
		processor.setAttack(sAttack.getValue());
	};
	sAttack.setRange({ 0, 100 }, 1);

	addAndMakeVisible(lAttack);
	lAttack.attachToComponent(&sAttack, true);
	lAttack.setText(String(TextValues::ATTACK), dontSendNotification);

	// Decay
	addAndMakeVisible(sDecay);
	sDecay.setSliderStyle(Slider::SliderStyle::LinearBar);
	sDecay.onValueChange = [this]
	{
		processor.setDecay(sDecay.getValue());
	};
	sDecay.setRange({ 0, 100 }, 1);

	addAndMakeVisible(lDecay);
	lDecay.attachToComponent(&sDecay, true);
	lDecay.setText(String(TextValues::DECAY), dontSendNotification);

	// Sustain
	addAndMakeVisible(sSustain);
	sSustain.setSliderStyle(Slider::SliderStyle::LinearBar);
	sSustain.onValueChange = [this]
	{
		processor.setSustain(sSustain.getValue());
	};
	sSustain.setRange({ 0, 100 }, 1);

	addAndMakeVisible(lSustain);
	lSustain.attachToComponent(&sSustain, true);
	lSustain.setText(String(TextValues::SUSTAIN), dontSendNotification);

	// Release
	addAndMakeVisible(sRelease);
	sRelease.setSliderStyle(Slider::SliderStyle::LinearBar);
	sRelease.onValueChange = [this]
	{
		processor.setRelease(sRelease.getValue());
	};
	sRelease.setRange({ 0, 100 }, 1);

	addAndMakeVisible(lRelease);
	lRelease.attachToComponent(&sRelease, true);
	lRelease.setText(String(TextValues::RELEASE), dontSendNotification);
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

	cWaveform.setBounds(area.removeFromTop(SizeValues::SLIDER_HEIGHT));

	auto volumeArea = area.removeFromTop(SizeValues::SLIDER_HEIGHT);
	lVolume.setBounds(volumeArea.removeFromLeft(SizeValues::LABEL_WIDTH));
	sVolume.setBounds(volumeArea);

	auto attackArea = area.removeFromTop(SizeValues::SLIDER_HEIGHT);
	lAttack.setBounds(attackArea.removeFromLeft(SizeValues::LABEL_WIDTH));
	sAttack.setBounds(attackArea);

	auto decayArea = area.removeFromTop(SizeValues::SLIDER_HEIGHT);
	lDecay.setBounds(decayArea.removeFromLeft(SizeValues::LABEL_WIDTH));
	sDecay.setBounds(decayArea);

	auto sustainArea = area.removeFromTop(SizeValues::SLIDER_HEIGHT);
	lSustain.setBounds(sustainArea.removeFromLeft(SizeValues::LABEL_WIDTH));
	sSustain.setBounds(sustainArea);

	auto releaseArea = area.removeFromTop(SizeValues::SLIDER_HEIGHT);
	lRelease.setBounds(releaseArea.removeFromLeft(SizeValues::LABEL_WIDTH));
	sRelease.setBounds(releaseArea);
}
