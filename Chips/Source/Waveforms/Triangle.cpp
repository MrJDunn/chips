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

void Triangle::updateNoteAngleDelta(Note& note)
{
	auto cyclesPerSample = Converter::midiNoteToFrequency(note.midiValue) / sampleRate;
	note.angleDelta = cyclesPerSample * note.amplitude * 4;
}

void Triangle::fillBuffer(Note& note, float* writePointer)
{
	updateNoteAngleDelta(note);

	if (rising)
	{
		if (lastAmplitude - note.angleDelta < abs(note.amplitude) * -1)
		{
			rising = !rising;
		}
		*writePointer = lastAmplitude - note.angleDelta;
	}
	else
	{
		if (lastAmplitude + note.angleDelta > abs(note.amplitude))
		{
			rising = !rising;
		}
		*writePointer = lastAmplitude + note.angleDelta;
	}

	lastAmplitude = *writePointer;
	note.currentAngle = note.angleDelta;
}
