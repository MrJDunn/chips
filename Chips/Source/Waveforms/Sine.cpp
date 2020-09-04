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
	auto cyclesPerSample = hz / sampleRate;
	angleDelta = cyclesPerSample * 2.0 * juce::MathConstants<double>::pi;
}

void Sine::updateNoteAngleDelta(Note& note)
{
	auto cyclesPerSample = Converter::midiNoteToFrequency(note.midiValue) / sampleRate;
	note.angleDelta = cyclesPerSample * 2.0 * juce::MathConstants<double>::pi;
}

void Sine::fillBuffer(Note& note, float *writePointer)
{
	updateNoteAngleDelta(note);
	*writePointer += sin(note.currentAngle - note.pulseWidth) * (note.amplitude / 2);
	note.currentAngle += note.angleDelta;
}