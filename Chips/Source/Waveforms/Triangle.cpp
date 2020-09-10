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
	double run = 1 / cyclesPerSample;
	double rise = note.amplitude * 2;
	double gradient = rise / run;
	note.angleDelta = gradient;
}

void Triangle::fillBuffer(Note& note, float* writePointer)
{
	updateNoteAngleDelta(note);
	double sampleToAdd = 0.0;
	if (rising)
	{
		if (note.lastAmplitude - note.angleDelta < abs(note.amplitude / 4.0) * -1)
		{
			rising = !rising;
			sampleToAdd = abs(note.amplitude / 4.0) * -1;
		}
		else
		{
			sampleToAdd = note.lastAmplitude - note.angleDelta;
		}
	}
	else
	{
		if (note.lastAmplitude + note.angleDelta > abs(note.amplitude / 4.0))
		{
			rising = !rising;
			sampleToAdd = abs(note.amplitude / 4.0);
		}
		else
		{
			sampleToAdd = note.lastAmplitude + note.angleDelta;
		}
	}

	note.lastAmplitude = sampleToAdd;

	*writePointer += sampleToAdd;
	note.currentAngle = note.angleDelta;
}
