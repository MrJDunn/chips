/*
  ==============================================================================

    Sine.h
    Created: 18 Aug 2020 5:10:04pm
    Author:  Jeff

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

#include "WaveBase.h"

#include "../Models/Note.h"

#include "../Utility/Converter.h"

class Sine : public WaveBase
{
public:
	Sine();
	~Sine() override;
protected:
	void updateAngleDelta(double hz);
	void updateNoteAngleDelta(Note& note);

	void fillBuffer(Note& note, float* writePointer) override;

	double currentAngle = 0.0, angleDelta = 0.0, tailOff = 0.0;
};