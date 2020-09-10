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
    : AudioProcessorEditor (&p), processor(p), waveView(p)
{
	LookAndFeel::setDefaultLookAndFeel(&style);
	LookAndFeel::getDefaultLookAndFeel().setDefaultSansSerifTypefaceName("Consolas");

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

	// Waveform
	addAndMakeVisible(cWaveform);
	cWaveform.addItemList(StringArray{"square","atonal beep","sine","triangle","saw","noise"}, 1);
	cWaveform.onChange = [this]
	{
		processor.setWaveform(cWaveform.getSelectedId());
	};

	// Volume
	initialiseSlider(&sVolume);
	sVolume.onValueChange = [this] 
	{
		processor.setAmplitude(sVolume.getValue());
	};
	sVolume.setRange({ 0, 100 }, 1);

	addAndMakeVisible(lVolume);
	lVolume.attachToComponent(&sVolume, true);
	lVolume.setText(String(TextValues::VOLUME), dontSendNotification);

	// Attack
	initialiseSlider(&sAttack);
	sAttack.onValueChange = [this]
	{
		processor.setAttack(sAttack.getValue());
	};
	sAttack.setRange({ 0, 100 }, 1);

	addAndMakeVisible(lAttack);
	lAttack.attachToComponent(&sAttack, true);
	lAttack.setText(String(TextValues::ATTACK), dontSendNotification);

	// Decay
	initialiseSlider(&sDecay);
	sDecay.onValueChange = [this]
	{
		processor.setDecay(sDecay.getValue());
	};
	sDecay.setRange({ 0, 100 }, 1);

	addAndMakeVisible(lDecay);
	lDecay.attachToComponent(&sDecay, true);
	lDecay.setText(String(TextValues::DECAY), dontSendNotification);

	// Sustain
	initialiseSlider(&sSustain);
	sSustain.onValueChange = [this]
	{
		processor.setSustain(sSustain.getValue());
	};
	sSustain.setRange({ 0, 100 }, 1);

	addAndMakeVisible(lSustain);
	lSustain.attachToComponent(&sSustain, true);
	lSustain.setText(String(TextValues::SUSTAIN), dontSendNotification);

	// Release
	initialiseSlider(&sRelease);
	sRelease.onValueChange = [this]
	{
		processor.setRelease(sRelease.getValue());
	};
	sRelease.setRange({ 0, 100 }, 1);

	addAndMakeVisible(lRelease);
	lRelease.attachToComponent(&sRelease, true);
	lRelease.setText(String(TextValues::RELEASE), dontSendNotification);

	// Pulse Width
	initialiseSlider(&sPulseWidth);
	sPulseWidth.onValueChange = [this]
	{
		processor.setPulseWidth(sPulseWidth.getValue());
	};
	sPulseWidth.setRange({ -50, 50 }, 1);

	addAndMakeVisible(lPulseWidth);
	lPulseWidth.attachToComponent(&sPulseWidth, true);
	lPulseWidth.setText(String(TextValues::PULSE_WIDTH), dontSendNotification);

	// Wave view
	addAndMakeVisible(waveView);

	initialiseParameters();
}

ChipsAudioProcessorEditor::~ChipsAudioProcessorEditor()
{
	setLookAndFeel(nullptr);
}

//==============================================================================
void ChipsAudioProcessorEditor::paint (Graphics& g)
{
	g.setColour(style.colours.getBackgroundLight());
	g.fillAll();
	g.setColour(style.colours.getBackgroundLight());
	g.fillAll();
	g.setColour(style.colours.getBorder());
	g.drawRect(getLocalBounds());
}

void ChipsAudioProcessorEditor::resized()
{
	auto area = getLocalBounds();

	cWaveform.setBounds(area.removeFromTop(SizeValues::SLIDER_HEIGHT));

	auto parameterDisplayArea = area.removeFromTop(area.getHeight() / 3);
	auto rightColumn = parameterDisplayArea.removeFromRight(area.getWidth() / 2);
	auto leftColumn = parameterDisplayArea;

	auto volumeArea = leftColumn.removeFromTop(SizeValues::SLIDER_HEIGHT).reduced(1);
	lVolume.setBounds(volumeArea.removeFromLeft(SizeValues::LABEL_WIDTH));
	sVolume.setBounds(volumeArea.reduced(5));

	auto attackArea = leftColumn.removeFromTop(SizeValues::SLIDER_HEIGHT).reduced(1);
	lAttack.setBounds(attackArea.removeFromLeft(SizeValues::LABEL_WIDTH));
	sAttack.setBounds(attackArea.reduced(5));

	auto decayArea = leftColumn.removeFromTop(SizeValues::SLIDER_HEIGHT).reduced(1);
	lDecay.setBounds(decayArea.removeFromLeft(SizeValues::LABEL_WIDTH));
	sDecay.setBounds(decayArea.reduced(5));

	auto sustainArea = rightColumn.removeFromTop(SizeValues::SLIDER_HEIGHT).reduced(1);
	lSustain.setBounds(sustainArea.removeFromLeft(SizeValues::LABEL_WIDTH));
	sSustain.setBounds(sustainArea.reduced(5));

	auto releaseArea = rightColumn.removeFromTop(SizeValues::SLIDER_HEIGHT).reduced(1);
	lRelease.setBounds(releaseArea.removeFromLeft(SizeValues::LABEL_WIDTH));
	sRelease.setBounds(releaseArea.reduced(5));

	auto pulseWidthArea = rightColumn.removeFromTop(SizeValues::SLIDER_HEIGHT).reduced(1);
	lPulseWidth.setBounds(pulseWidthArea.removeFromLeft(SizeValues::LABEL_WIDTH));
	sPulseWidth.setBounds(pulseWidthArea.reduced(5));

	waveView.setBounds(area.reduced(10));
}

void ChipsAudioProcessorEditor::initialiseParameters()
{
	cWaveform.setSelectedId(processor.getWaveform());
	sVolume.setValue(processor.getAmplitude());
	sAttack.setValue(processor.getAttack());
	sDecay.setValue(processor.getDecay());
	sSustain.setValue(processor.getSustain());
	sRelease.setValue(processor.getRelease());
	sPulseWidth.setValue(processor.getPulseWidth());
}

void ChipsAudioProcessorEditor::initialiseSlider(Slider* slider)
{
	addAndMakeVisible(*slider);
	slider->setSliderStyle(Slider::SliderStyle::LinearHorizontal);
	slider->setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
}
