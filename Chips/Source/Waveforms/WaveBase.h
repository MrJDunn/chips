/*
  ==============================================================================

    WaveBase.h
    Created: 18 Aug 2020 12:03:10pm
    Author:  Jeff

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

#include "../Models/Note.h"

class WaveBase
{
public: 
	WaveBase();
	virtual ~WaveBase();

	/**
	 * Executes the fill-buffer implementation for all channels
	 * @param note		The note to perform
	 * @param buffer	The buffer to fill
	 */
	void perform(Note& note, AudioBuffer<float>& buffer);
	void setSampleRate(double newSampleRate);

	/**
	 * Clear the buffer
	 * @param buffer	The buffer to clear
	 */
	void reset(AudioBuffer<float>& buffer);
protected:
	double sampleRate = 0.0;

	/**
	 * Ensures values do not exceed the minimum and maximum normalised values (-1,1)
	 * @param writePointer	Pointer to the buffer that needs clipping
	 */
	void clip(float* writePointer);

	/**
	 * Child classes will be given a note value and a pointer to the audio buffer to fill
	 * @param note			The note to play
	 * @param writePointer	Pointer to the buffer that needs filling
	 */
	virtual void fillBuffer(Note& note, float* writePointer) = 0;

	// The first octave of the chromatic scale
	double frequencies[12] = { 16.35, 17.42, 18.35, 19.45, 20.60, 21.83, 23.12, 24.50, 25.96, 27.50, 29.14, 30.87 };
};