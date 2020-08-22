/*
  ==============================================================================

    Converter.h
    Created: 21 Aug 2020 5:12:25pm
    Author:  Jeff

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h" 

class Converter
{
public:
	static float midiNoteToFrequency(int midiNoteNumber)
	{
		return pow(2.0, (midiNoteNumber - 69) / 12.0f) * 440.0f;
	}

	static int frequencyToMidiNote(float frequency)
	{
		return 12 * log2(frequency/440.0f) + 69;
	}
};