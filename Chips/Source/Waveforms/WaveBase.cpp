/*
  ==============================================================================

    WaveBase.cpp
    Created: 18 Aug 2020 12:03:10pm
    Author:  Jeff

  ==============================================================================
*/

#include "WaveBase.h"

WaveBase::WaveBase()
{
}

WaveBase::~WaveBase()
{
}

void WaveBase::perform(Note& note, AudioBuffer<float>& buffer)
{
	bool s = true;
	int numSamples = buffer.getNumSamples();

	for (auto sample = 0; sample < numSamples; sample++)
	{
		for (int channel = 0; channel < buffer.getNumChannels(); channel++)
		{
			float* ptr = buffer.getWritePointer(channel);
			fillBuffer(note, &ptr[sample]);

			clip(&ptr[sample]);
		}

		note.time++;
	}

}

void WaveBase::setSampleRate(double newSampleRate)
{
	sampleRate = newSampleRate;
}

void WaveBase::reset(AudioBuffer<float>& buffer)
{
	for (int sample = 0; sample < buffer.getNumSamples(); sample++)
	{
		for (int channel = 0; channel < buffer.getNumChannels(); channel++)
		{
			float* ptr = buffer.getWritePointer(channel);
			ptr[sample] = 0;
		}
	}
}

void WaveBase::clip(float* writePointer)
{
	if (*writePointer > 1.0f)
		*writePointer = 1.0f;
	if (*writePointer < -1.0f)
		*writePointer = -1.0f;
}
