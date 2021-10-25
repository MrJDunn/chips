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

	setSize (400, 300);

	// Waveform
	addAndMakeVisible(cWaveform);
	cWaveform.addItemList(StringArray{"square","atonal beep","sine","triangle","saw","noise"}, 1);
	cWaveform.onChange = [this]
	{
		processor.setWaveform(cWaveform.getSelectedId());
	};
	cWaveform.setSelectedId(processor.getWaveform(), dontSendNotification);

	// Preset
	addAndMakeVisible(cPreset);
	StringArray presets = fileManager.getPresets();
	cPreset.addItem("save...", 1);
	cPreset.addItemList(presets, 2);
	cPreset.onChange = [this]
	{
		int id = cPreset.getSelectedId();
		switch (id)
		{
			case 1: // Save
			{
				AlertWindow saveWindow("save", "save preset", AlertWindow::AlertIconType::NoIcon);
				saveWindow.getLookAndFeel().setDefaultSansSerifTypefaceName("Consolas");
				saveWindow.setEscapeKeyCancels(true);
				saveWindow.addTextEditor("presetName", "", "preset name", false);
				saveWindow.addButton("save", 1, KeyPress(KeyPress::returnKey));

				int result = saveWindow.runModalLoop();

				if(result == 1) // Enter
				{
					String presetName = saveWindow.getTextEditorContents("presetName");

					MemoryBlock block(2048);
					processor.getStateInformation(block);
					fileManager.savePresetFile(presetName, block);

					StringArray presets = fileManager.getPresets();
					if(!presets.contains(presetName))
						cPreset.addItem(presetName, presets.size() + 1);
					cPreset.setText(presetName, false);
				}
				if(result == 0) // Cancel
				{
					cPreset.setSelectedId(0, dontSendNotification);
					break;
				}
			}
			default: // Load selected preset
			{
				String text = cPreset.getText();
				MemoryBlock block(2048);
				fileManager.loadPresetFile(text, block);
				processor.setStateInformation(block.getData(), block.getSize());

				initialiseParameters();
			}
		}
	};

	// Volume
	initialiseSlider(&sVolume);
	sVolume.setSliderStyle(Slider::SliderStyle::LinearBar);
	sVolume.onValueChange = [this] 
	{
		processor.setAmplitude(sVolume.getValue());
		DBG("vol: " + String(sVolume.getValue()));
	};
	sVolume.setRange({ 0, 100 }, 1);

	addAndMakeVisible(lVolume);
	lVolume.attachToComponent(&sVolume, true);
	lVolume.setText(String(TextValues::VOLUME), dontSendNotification);

	// Pitch
	initialiseSlider(&sPitch);
	sPitch.setSliderStyle(Slider::SliderStyle::LinearBar);
	sPitch.onValueChange = [this] 
	{
		processor.setPitch(sPitch.getValue());
		DBG("pch: " + String(sPitch.getValue()));
	};
	sPitch.setRange({ 0, 100 }, 1);

	addAndMakeVisible(lPitch);
	lPitch.attachToComponent(&sPitch, true);
	lPitch.setText(String(TextValues::PITCH), dontSendNotification);

	// Attack
	initialiseSlider(&sAttack);
	sAttack.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
	sAttack.onValueChange = [this]
	{
		processor.setAttack(sAttack.getValue());
		DBG("atk: " + String(sAttack.getValue()));
	};
	sAttack.setRange({ 0, 100 }, 1);

	addAndMakeVisible(lAttack);
	lAttack.setText(String(TextValues::ATTACK), dontSendNotification);
	lAttack.setJustificationType(Justification::centred);

	// Decay
	initialiseSlider(&sDecay);
	sDecay.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
	sDecay.onValueChange = [this]
	{
		processor.setDecay(sDecay.getValue());
		DBG("dcy: " + String(sDecay.getValue()));
	};
	sDecay.setRange({ 0, 100 }, 1);

	addAndMakeVisible(lDecay);
	lDecay.setText(String(TextValues::DECAY), dontSendNotification);
	lDecay.setJustificationType(Justification::centred);

	// Sustain
	initialiseSlider(&sSustain);
	sSustain.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
	sSustain.onValueChange = [this]
	{
		processor.setSustain(sSustain.getValue());
		DBG("sus: " + String(sSustain.getValue()));
	};
	sSustain.setRange({ 0, 100 }, 1);

	addAndMakeVisible(lSustain);
	lSustain.setText(String(TextValues::SUSTAIN), dontSendNotification);
	lSustain.setJustificationType(Justification::centred);

	// Release
	initialiseSlider(&sRelease);
	sRelease.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
	sRelease.onValueChange = [this]
	{
		processor.setRelease(sRelease.getValue());
		DBG("rel: " + String(sRelease.getValue()));
	};
	sRelease.setRange({ 0, 100 }, 1);

	addAndMakeVisible(lRelease);
	lRelease.setText(String(TextValues::RELEASE), dontSendNotification);
	lRelease.setJustificationType(Justification::centred);

	// Pulse Width
	initialiseSlider(&sPulseWidth);
	sPulseWidth.setSliderStyle(Slider::SliderStyle::LinearBar);
	sPulseWidth.onValueChange = [this]
	{
		processor.setPulseWidth(sPulseWidth.getValue());
		DBG("pwm: " + String(sPulseWidth.getValue()));
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

	cPreset.setBounds(area.removeFromTop(SizeValues::SLIDER_HEIGHT));

	auto parameterDisplayArea = area.removeFromTop(area.getHeight() / 3);
	auto rightColumn = parameterDisplayArea.removeFromRight(area.getWidth() / 2);
	auto leftColumn = parameterDisplayArea;

	auto volumeArea = leftColumn.removeFromTop(SizeValues::SLIDER_HEIGHT).reduced(1);
	lVolume.setBounds(volumeArea.removeFromLeft(SizeValues::LABEL_WIDTH));
	sVolume.setBounds(volumeArea.reduced(5));

	auto pulseWidthArea = leftColumn.removeFromTop(SizeValues::SLIDER_HEIGHT).reduced(1);
	lPulseWidth.setBounds(pulseWidthArea.removeFromLeft(SizeValues::LABEL_WIDTH));
	sPulseWidth.setBounds(pulseWidthArea.reduced(5));

	auto pitchArea = leftColumn.removeFromTop(SizeValues::SLIDER_HEIGHT).reduced(1);
	lPitch.setBounds(pitchArea.removeFromLeft(SizeValues::LABEL_WIDTH));
	sPitch.setBounds(pitchArea.reduced(5));

	//Put in the pitch control here

	auto attackArea = rightColumn.removeFromLeft(SizeValues::SLIDER_HEIGHT).reduced(1);
	sAttack.setBounds(attackArea.removeFromTop(attackArea.getHeight() - SizeValues::SLIDER_HEIGHT).reduced(5));
	lAttack.setBounds(attackArea);

	auto decayArea = rightColumn.removeFromLeft(SizeValues::SLIDER_HEIGHT).reduced(1);
	sDecay.setBounds(decayArea.removeFromTop(decayArea.getHeight() - SizeValues::SLIDER_HEIGHT).reduced(5));
	lDecay.setBounds(decayArea);

	auto sustainArea = rightColumn.removeFromLeft(SizeValues::SLIDER_HEIGHT).reduced(1);
	sSustain.setBounds(sustainArea.removeFromTop(sustainArea.getHeight() - SizeValues::SLIDER_HEIGHT).reduced(5));
	lSustain.setBounds(sustainArea);

	auto releaseArea = rightColumn.removeFromLeft(SizeValues::SLIDER_HEIGHT).reduced(1);
	sRelease.setBounds(releaseArea.removeFromTop(releaseArea.getHeight() - SizeValues::SLIDER_HEIGHT).reduced(5));
	lRelease.setBounds(releaseArea);

	cWaveform.setBounds(rightColumn.reduced(10));

	waveView.setBounds(area.reduced(10));
}

void ChipsAudioProcessorEditor::initialiseParameters()
{
	cWaveform.setSelectedId(processor.getWaveform());
	sAttack.setValue(processor.getAttack());
	sDecay.setValue(processor.getDecay());
	sSustain.setValue(processor.getSustain());
	sRelease.setValue(processor.getRelease());
	sPulseWidth.setValue(processor.getPulseWidth());
	sPitch.setValue(processor.getPitch());
}

void ChipsAudioProcessorEditor::initialiseSlider(Slider* slider)
{
	addAndMakeVisible(*slider);
	slider->setSliderStyle(Slider::SliderStyle::LinearHorizontal);
	slider->setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
}
