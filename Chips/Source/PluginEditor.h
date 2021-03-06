/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

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

	ChipsLookAndFeel style;

	Slider sVolume;

	Slider sAttack;
	Slider sDecay;
	Slider sSustain;
	Slider sRelease;
	Slider sPulseWidth;

	Label lVolume;
	Label lAttack;
	Label lDecay;
	Label lSustain;
	Label lRelease;
	Label lPulseWidth;

	ComboBox cWaveform;

	WaveformView waveView;

	struct TextValues
	{
		static constexpr char* VOLUME = "vol";
		static constexpr char* ATTACK = "atk";
		static constexpr char* DECAY = "dcy";
		static constexpr char* SUSTAIN = "sus";
		static constexpr char* RELEASE = "rel";
		static constexpr char* PULSE_WIDTH = "pwm";
	};

	struct SizeValues
	{
		static constexpr int LABEL_WIDTH = 50;
		static constexpr int SLIDER_HEIGHT = 25;
	};

	void initialiseParameters();

	void initialiseSlider(Slider* slider);
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChipsAudioProcessorEditor)
};
