/*
  ==============================================================================

    Noise.h
    Created: 18 Aug 2020 12:03:22pm
    Author:  Jeff

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "WaveBase.h"

#include "../Models/Note.h"

class Noise: public WaveBase
{
public:
	Noise();
	~Noise() override;
protected:
	void fillBuffer(Note& note, float* writePointer) override;
private:
	Random* random;
};