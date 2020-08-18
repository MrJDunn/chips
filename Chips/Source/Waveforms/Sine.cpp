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

void Sine::updateAngleDelta(float hz)
{
	auto cyclesPerSample = hz / sampleRate;
	angleDelta = cyclesPerSample * 2.0 * juce::MathConstants<double>::pi;
}

void Sine::fillBuffer(const Note& note, float *writePointer)
{
	updateAngleDelta(frequencies[note.midiValue % 12] * pow(2, floor(note.midiValue / 12.0f)));
	*writePointer = *writePointer + (std::sin(currentAngle)) * note.magnitude;
	currentAngle += angleDelta;
}