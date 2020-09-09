/*
  ==============================================================================

    Square.cpp
    Created: 23 Aug 2020 7:12:29pm
    Author:  Jeff

  ==============================================================================
*/

#include "Square.h"

Square::Square()
{
}

Square::~Square()
{
}

void Square::updateAngleDelta(double hz)
{
	angleDelta = (hz / sampleRate) * 2.0 * juce::MathConstants<double>::pi;
}

void Square::updateNoteAngleDelta(Note& note)
{
	note.angleDelta = (Converter::midiNoteToFrequency(note.midiValue) / sampleRate) * 2.0 * juce::MathConstants<double>::pi;
}

void Square::fillBuffer(Note& note, float *writePointer)
{
	updateNoteAngleDelta(note);

	*writePointer += (sin(note.currentAngle) - note.pulseWidth > 0 ? 1 : -1) * (note.amplitude / 2.0);

	note.currentAngle += note.angleDelta;
}