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
	double frequencies[12] = { 16.35, 17.42, 18.35, 19.45, 20.60, 21.83, 23.12, 24.50, 25.96, 27.50, 29.14, 30.87 };

	double currentAngle = 0.0, angleDelta = 0.0, tailOff = 0.0;
};