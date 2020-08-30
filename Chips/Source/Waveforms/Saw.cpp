/*
  ==============================================================================

    Saw.cpp
    Created: 30 Aug 2020 12:43:47pm
    Author:  Jeff

  ==============================================================================
*/

#include "Saw.h"

Saw::Saw()
{
}

Saw::~Saw()
{
}

void Saw::updateNoteAngleDelta(Note& note)
{
	auto cyclesPerSample = Converter::midiNoteToFrequency(note.midiValue) / sampleRate;
	note.angleDelta = cyclesPerSample;// *2.0 * juce::MathConstants<double>::pi;
}

/*
    amp
	 |\     |\     |\     |\
	 | \    | \    | \    | \
 _  _| _\ _ | _\ _ | _\ _ | _\ _  _
	 |   \  |   \  |   \  |   \
 	 |    \ |    \ |    \ |    \
 	 |     \|     \|     \|     \
    x[n]  -amp

	- Need to figure out how many samples are in a cycle for the given fq spc()
	- Each sample is then n * / spc(fq)[n]

*/

void Saw::fillBuffer(Note& note, float* writePointer)
{
	updateNoteAngleDelta(note);
	if (lastAmplitude - note.angleDelta > (note.amplitude * -1) / 2)
	{
		*writePointer = lastAmplitude - note.angleDelta;
	}
	else
	{
		*writePointer = note.amplitude / 2;
	}

	lastAmplitude = *writePointer;
	note.currentAngle = note.angleDelta;
}
