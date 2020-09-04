/*
  ==============================================================================

    AtonalBeep.cpp
    Created: 18 Aug 2020 12:03:36pm
    Author:  Jeff

  ==============================================================================
*/

#include "AtonalBeep.h"

AtonalBeep::AtonalBeep()
{
}

AtonalBeep::~AtonalBeep()
{
}

void AtonalBeep::fillBuffer(Note& note, float* writePointer)
{
	*writePointer = *writePointer + (std::sin(note.time * note.midiValue / 50)) * note.amplitude;
}
