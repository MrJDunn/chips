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

	Slider sVolume;

	Slider sAttack;
	Slider sDecay;
	Slider sSustain;
	Slider sRelease;

	Label lVolume;
	Label lAttack;
	Label lDecay;
	Label lSustain;
	Label lRelease;

	ComboBox cWaveform;

	WaveformView waveView;

	struct TextValues
	{
		static constexpr char* VOLUME = "Volume";
		static constexpr char* ATTACK = "Attack";
		static constexpr char* DECAY = "Decay";
		static constexpr char* SUSTAIN = "Sustain";
		static constexpr char* RELEASE = "Release";
	};

	struct SizeValues
	{
		static constexpr int LABEL_WIDTH = 75;
		static constexpr int SLIDER_HEIGHT = 25;
	};

	void initialiseParameters();

	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChipsAudioProcessorEditor)
};
