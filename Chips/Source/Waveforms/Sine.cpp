/*
  ==============================================================================

    Sine.cpp
    Created: 18 Aug 2020 5:10:04pm
    Author:  Jeff

  ==============================================================================
*/

#include "Sine.h"

Sine::Sine()
{
}

Sine::~Sine()
{
}

void Sine::updateAngleDelta(double hz)
{
	angleDelta = (hz / sampleRate) * 2.0 * juce::MathConstants<double>::pi;
}

void Sine::updateNoteAngleDelta(Note& note)
{
	note.angleDelta = (Converter::midiNoteToFrequency(note.midiValue) / sampleRate) * 2.0 * juce::MathConstants<double>::pi;
}

void Sine::fillBuffer(Note& note, float *writePointer)
{
	updateNoteAngleDelta(note);
	*writePointer += (sin(note.currentAngle)  > 0 ? sin(note.currentAngle + 2.0 * note.pulseWidth)  : sin(note.currentAngle - 2.0 * note.pulseWidth)) * (note.amplitude / 2.0);
	note.currentAngle += note.angleDelta;
}