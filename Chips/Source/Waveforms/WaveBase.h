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
};