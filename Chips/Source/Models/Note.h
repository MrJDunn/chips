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
	float magnitude = 0.0f;
	int time = 0;

	enum NoteState
	{
		Off = 0,
		A,
		S,
		D,
		R
	} state = NoteState::Off;
};