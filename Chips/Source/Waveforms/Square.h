/*
  ==============================================================================

    Square.h
    Created: 23 Aug 2020 7:12:29pm
    Author:  Jeff

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "WaveBase.h"

#include "../Models/Note.h"

#include "../Utility/Converter.h"

class Square : public WaveBase
{
public:
	Square();
	~Square() override;
protected:
	void updateAngleDelta(double hz);
	void updateNoteAngleDelta(Note& note);

	void fillBuffer(Note& note, float* writePointer) override;

	double currentAngle = 0.0, angleDelta = 0.0, tailOff = 0.0;
};