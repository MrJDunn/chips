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

	/**
	 * Calculates the required gradient for the given note's frequency and amplitude
	 * @param note	The note to calculate a gradient for
	 * 
	 */
	void updateNoteAngleDelta(Note& note);
	void fillBuffer(Note& note, float* writePointer) override;
};