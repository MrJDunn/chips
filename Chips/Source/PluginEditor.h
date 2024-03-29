/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Utility/FileManager.h"

#include "Components/WaveformView.h"

#include "Style/ChipsLookAndFeel.h"

//==============================================================================
/**
*/
class ChipsAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    ChipsAudioProcessorEditor (ChipsAudioProcessor&);
    ~ChipsAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ChipsAudioProcessor& processor;
	FileManager fileManager;

	ChipsLookAndFeel style;

	Slider sVolume;

	Slider sAttack;
	Slider sDecay;
	Slider sSustain;
	Slider sRelease;
	Slider sPulseWidth;
	Slider sPitch;
	Slider sVibrato;

	Label lVolume;
	Label lAttack;
	Label lDecay;
	Label lSustain;
	Label lRelease;
	Label lPulseWidth;
	Label lPitch;
	Label lVibrato;

	ComboBox cWaveform;
	
	ComboBox cPreset;

	WaveformView waveView;

	struct TextValues
	{
		static constexpr char* VOLUME = "vol";
		static constexpr char* ATTACK = "a";
		static constexpr char* DECAY = "d";
		static constexpr char* SUSTAIN = "s";
		static constexpr char* RELEASE = "r";
		static constexpr char* PULSE_WIDTH = "pwm";
		static constexpr char* PITCH = "pch";
		static constexpr char* VIBRATO = "vib";
	};

	struct SizeValues
	{
		static constexpr int LABEL_WIDTH = 30;
		static constexpr int SLIDER_HEIGHT = 25;
	};

	void initialiseParameters();

	void initialiseSlider(Slider* slider);
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChipsAudioProcessorEditor)
};
