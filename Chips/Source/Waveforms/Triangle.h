/*
  ==============================================================================

    Triangle.h
    Created: 30 Aug 2020 12:43:53pm
    Author:  Jeff

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "WaveBase.h"

#include "../Models/Note.h"

#include "../Utility/Converter.h"

class Triangle : public WaveBase
{
public:
	Triangle();
	~Triangle() override;
protected:
	void updateNoteAngleDelta(Note& note);
	void fillBuffer(Note& note, float* writePointer) override;

	double lastAmplitude = 0.0;
	bool rising = false;
};