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
	note.angleDelta = cyclesPerSample * note.amplitude;
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
	double sampleToAdd = 0.0;

	if (note.lastAmplitude - note.angleDelta > abs(note.amplitude / 2.0) * -1)
	{
		sampleToAdd = note.lastAmplitude - note.angleDelta;
	}
	else
	{
		sampleToAdd = abs(note.amplitude / 2.0);
	}

	note.lastAmplitude = sampleToAdd;
	*writePointer += sampleToAdd;
	note.currentAngle = note.angleDelta;
}
