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

void WaveBase::perform(Note& note, AudioBuffer<float>& buffer, int channel)
{
	auto* writePointer = buffer.getWritePointer(channel);

	for (auto sample = 0; sample < buffer.getNumSamples(); ++sample)
	{
		fillBuffer(note, &writePointer[sample]);

		// clip
		if (writePointer[sample] < 0.0f)
		{
			writePointer[sample] = 0.0f;
		}
		if (writePointer[sample] > 1.0f)
		{
			writePointer[sample] = 1.0f;
		}

		note.time++;
	}
}