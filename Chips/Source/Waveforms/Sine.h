/*
  ==============================================================================

    Sine.h
    Created: 18 Aug 2020 5:10:04pm
    Author:  Jeff

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

#include "WaveBase.h"

#include "../Models/Note.h"

class Sine : public WaveBase
{
public:
	Sine();
	~Sine() override;
protected:
	void updateAngleDelta(float hz);
	void fillBuffer(const Note& note, float* writePointer) override;
	float frequencies[12] = { 16.35f, 17.42f, 18.35f, 19.45f, 20.60f, 21.83f, 23.12f, 24.50f, 25.96f, 27.50f, 29.14f, 30.87f };

	double currentAngle = 0.0, angleDelta = 0.0;
};