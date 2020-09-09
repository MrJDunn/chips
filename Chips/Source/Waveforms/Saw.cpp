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
	double run = 1 / cyclesPerSample;
	double rise = note.amplitude * 2;
	double gradient = rise / run;
	note.angleDelta = gradient;
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
	double sampleToAdd = lastAmplitude - note.angleDelta;
	
	if(sampleToAdd < abs(note.amplitude / 2.0) * -1)
	{
		sampleToAdd = abs(note.amplitude / 2.0);
	}

	lastAmplitude = sampleToAdd;
	
	*writePointer += sampleToAdd;

	note.currentAngle += note.angleDelta;
}
