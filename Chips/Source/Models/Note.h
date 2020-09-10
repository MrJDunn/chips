/*
  ==============================================================================

    Note.h
    Created: 18 Aug 2020 12:09:54pm
    Author:  Jeff

  ==============================================================================
*/

#pragma once

struct Note
{
	int midiValue = 0;
	double amplitude = 0.005;
	int time = 0;
	double smoothingFactor = 0.1;
	double angleDelta = 0.0;
	double currentAngle = 0.0;
	double pulseWidth = 0.0;
	double lastAmplitude = 0.0;

	enum NoteState
	{
		Off = 0,
		A,
		S,
		D,
		R
	} state = NoteState::Off;
};