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
	float delayInSeconds = 0.5;
	writePos = (int)(delayInSeconds * sampleRate);
	reset();
}

void Vibrato::releaseResources()
{
}

void Vibrato::processBlock(AudioBuffer<float>& buffer, MidiBuffer & midiMessages)
{
	int numChannels = buffer.getNumChannels();
	int numSamples = buffer.getNumSamples();

	for(int c = 0; c < numChannels; ++c)
	{
		float* samples = buffer.getWritePointer(c);

		for (int i = 0; i < numSamples; ++i)
		{
			ringBuffer[writePos + numSamples * c] = samples[i]; // unsafe if lots of channels
			samples[i] += ringBuffer[readPos + numSamples * c]; // unsafe if lots of channels

			writePos = (writePos + 1) & WRAP_MASK;
			readPos = (readPos + 1) & WRAP_MASK;
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

void Vibrato::reset()
{
	for(int i = 0; i < WRAP_MASK; ++i)
	{
		ringBuffer[i] = 0;
	}
}
