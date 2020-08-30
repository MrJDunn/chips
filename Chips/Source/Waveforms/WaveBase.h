/*
  ==============================================================================

    WaveBase.h
    Created: 18 Aug 2020 12:03:10pm
    Author:  Jeff

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

#include "../Models/Note.h"

class WaveBase
{
public: 
	WaveBase();
	virtual ~WaveBase();
	void perform(Note& note, AudioBuffer<float>& buffer);
	void setSampleRate(double newSampleRate);

	void reset(AudioBuffer<float>& buffer);
protected:
	double sampleRate = 0.0;

	void clip(float* writePointer);
	virtual void fillBuffer(Note&, float* writePointer) = 0;

	double frequencies[12] = { 16.35, 17.42, 18.35, 19.45, 20.60, 21.83, 23.12, 24.50, 25.96, 27.50, 29.14, 30.87 };
};