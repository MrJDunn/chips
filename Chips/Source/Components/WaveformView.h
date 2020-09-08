/*
  ==============================================================================

    WaveformView.h
    Created: 30 Aug 2020 7:29:07pm
    Author:  Jeff

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "../PluginProcessor.h"

class WaveformView : public Component, public Timer
{
public: 
	WaveformView(ChipsAudioProcessor& p);
	~WaveformView();

	void paint(Graphics& g) override;
	void resized() override;

	void timerCallback() override;

private:

	void paintVerticalLines(Graphics& g);
	void paintHorizontalLines(Graphics& g);

	ChipsAudioProcessor& processor;
	std::vector<float> buffer;
};