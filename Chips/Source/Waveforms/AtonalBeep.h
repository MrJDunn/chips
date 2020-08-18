/*
  ==============================================================================

    AtonalBeep.h
    Created: 18 Aug 2020 12:03:36pm
    Author:  Jeff

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "WaveBase.h"

#include "../Models/Note.h"

class AtonalBeep : public WaveBase
{
public:
	AtonalBeep();
	~AtonalBeep() override;
protected:
	void fillBuffer(const Note& note, float* writePointer) override;
};