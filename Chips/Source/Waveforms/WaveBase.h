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
	void perform(Note& note, AudioBuffer<float>& buffer, int channel);
protected:
	virtual void fillBuffer(const Note&, float* writePointer) = 0;
};