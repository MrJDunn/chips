/*
  ==============================================================================

    Saw.h
    Created: 30 Aug 2020 12:43:47pm
    Author:  Jeff

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "WaveBase.h"

#include "../Models/Note.h"

#include "../Utility/Converter.h"

class Saw : public WaveBase
{
public:
	Saw();
	~Saw() override;
protected:
	void updateNoteAngleDelta(Note& note);

	void fillBuffer(Note& note, float* writePointer) override;

	double lastAmplitude = 0.0;

};