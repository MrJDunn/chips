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
	double sampleToAdd = 0.0;
	if (rising)
	{
		if (lastAmplitude - note.angleDelta < abs(note.amplitude / 4) * -1)
		{
			rising = !rising;
		}
		sampleToAdd = lastAmplitude - note.angleDelta;
	}
	else
	{
		if (lastAmplitude + note.angleDelta > abs(note.amplitude / 4))
		{
			rising = !rising;
		}
		sampleToAdd = lastAmplitude + note.angleDelta;
	}

	lastAmplitude = sampleToAdd;

	*writePointer += sampleToAdd;
	note.currentAngle = note.angleDelta;
}
