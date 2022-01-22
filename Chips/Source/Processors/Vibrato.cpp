/*
  ==============================================================================

    Vibrato.cpp
    Created: 6 Nov 2021 6:34:26pm
    Author:  Jeff

  ==============================================================================
*/

#include "Vibrato.h"

Vibrato::Vibrato()
{
}

Vibrato::~Vibrato()
{
}

const String Vibrato::getName() const
{
	return String();
}

void Vibrato::prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock)
{
	lastSampleRate = sampleRate;
	writePosL = (int)(delayInSeconds);
	writePosR = (int)(delayInSeconds);
	reset();
}

void Vibrato::releaseResources()
{
}

void Vibrato::processBlock(AudioBuffer<float>& buffer, MidiBuffer & midiMessages)
{
	int numChannels = buffer.getNumChannels();
	int numSamples = buffer.getNumSamples();

	float d = delayInSeconds.load();
	float s = lastSampleRate;

	for (int c = 0; c < numChannels; ++c)
	{
		float* samples = buffer.getWritePointer(c);

		if (c == 0)
		{
			for (int i = 0; i < numSamples; ++i)
			{
				ringBufferL[writePosL] = samples[i];
				samples[i] += ringBufferL[readPosL];
				readPosL = int(writePosL - d) & (WRAP_MASK);
				jassert(readPosL >= 0);
				writePosL = (writePosL + 1) & WRAP_MASK;
			}
		}
		if (c == 1)
		{
			for (int i = 0; i < numSamples; ++i)
			{
				ringBufferR[writePosR] = samples[i]; 
				samples[i] += ringBufferR[readPosR];
				readPosR = int(writePosR  - d) & (WRAP_MASK);
				jassert(readPosR >= 0);
				writePosR = (writePosR + 1) & WRAP_MASK;
			}
		}
	}

}

double Vibrato::getTailLengthSeconds() const
{
	return 0.0;
}

bool Vibrato::acceptsMidi() const
{
	return false;
}

bool Vibrato::producesMidi() const
{
	return false;
}

AudioProcessorEditor * Vibrato::createEditor()
{
	return nullptr;
}

bool Vibrato::hasEditor() const
{
	return false;
}

int Vibrato::getNumPrograms()
{
	return 0;
}

int Vibrato::getCurrentProgram()
{
	return 0;
}

void Vibrato::setCurrentProgram(int index)
{
}

const String Vibrato::getProgramName(int index)
{
	return String();
}

void Vibrato::changeProgramName(int index, const String & newName)
{
}

void Vibrato::getStateInformation(juce::MemoryBlock & destData)
{
}

void Vibrato::setStateInformation(const void * data, int sizeInBytes)
{
}

void Vibrato::setFactor(float val)
{
	delayInSeconds.store((50 + val) / 50.0f * lastSampleRate);
}

void Vibrato::reset()
{
	for(int i = 0; i < WRAP_MASK; ++i)
	{
		ringBufferL[i] = 0;
		ringBufferR[i] = 0;
	}
}

int Vibrato::getWritePos()
{
	return 0;
}
