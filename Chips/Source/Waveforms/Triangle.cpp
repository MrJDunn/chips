/*
  ==============================================================================

    Triangle.cpp
    Created: 30 Aug 2020 12:43:53pm
    Author:  Jeff

  ==============================================================================
*/

#include "Triangle.h"

Triangle::Triangle()
{
}

Triangle::~Triangle()
{
}

void Triangle::updateNoteAngleDelta(Note & note)
{
	auto cyclesPerSample = Converter::midiNoteToFrequency(note.midiValue) / sampleRate;
	note.angleDelta = cyclesPerSample;
}

void Triangle::fillBuffer(Note& note, float* writePointer)
{
	updateNoteAngleDelta(note);

	if (rising)
	{
		if (lastAmplitude + note.angleDelta < (note.amplitude) / 2)
		{
			*writePointer = lastAmplitude + note.angleDelta;
		}
		else
		{
			*writePointer = note.amplitude / 2;
			rising = !rising;
		}
	}
	else
	{
		if (lastAmplitude - note.angleDelta > (note.amplitude * -1) / 2)
		{
			*writePointer = lastAmplitude - note.angleDelta;
		}
		else
		{
			*writePointer = (note.amplitude * -1) / 2;
			rising = !rising;
		}
	}

	lastAmplitude = *writePointer;
	note.currentAngle = note.angleDelta;
}
