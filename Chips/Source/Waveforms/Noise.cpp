/*
  ==============================================================================

    Noise.cpp
    Created: 18 Aug 2020 12:03:22pm
    Author:  Jeff

  ==============================================================================
*/

#include "Noise.h"

Noise::Noise(): random(new Random)
{
}

Noise::~Noise()
{
	delete random;
}

void Noise::fillBuffer(Note& note, float *writePointer)
{
	*writePointer = *writePointer + (random->nextFloat() * 2.0f - 1.0f) * note.amplitude;
}
