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
	writePosL = (int)(delayInSeconds * lastSampleRate);
	writePosR = (int)(delayInSeconds * lastSampleRate);
	readPosL = 0;
	readPosR = 0;
	reset();
}

void Vibrato::releaseResources()
{
}

	int lastVal1 = 0, lastVal2 = 0;
	float lastCount = 0.f;
	int linkL = 0, linkR = 0;
void Vibrato::processBlock(AudioBuffer<float>& buffer, MidiBuffer & midiMessages)
{
	int numChannels = buffer.getNumChannels();
	int numSamples = buffer.getNumSamples();

	float* samplesL = buffer.getWritePointer(0);
	float* samplesR = buffer.getWritePointer(1);

	float dc = delayInSeconds;
	float d = (dc * lastSampleRate) / 1000.f;

	for (int i = 0; i < numSamples; ++i)
	{
		jassert(writePosL >= 0 && writePosL <= WRAP_MASK);
		ringBufferL[writePosL] = samplesL[i];
		jassert(readPosL >= 0 && readPosL <= WRAP_MASK);
		samplesL[i] = ringBufferL[readPosL] * 0.5f;

		if(writePosL < readPosL)
		{
			// For wrapping buffer, need to use another counter so readPos doesn't get less than 0
			readPosL = int(linkL++ - int(d + std::sin(2 * MathConstants<float>().pi * count) * d)) % (WRAP_MASK);
		}
		else
		{
			linkL = writePosL;
			readPosL = int(writePosL - int(d + std::sin(2 * MathConstants<float>().pi * count) * d)) % (WRAP_MASK);
		}
		writePosL = (writePosL + 1) % WRAP_MASK;

		jassert(writePosR >= 0 && writePosR <= WRAP_MASK);
		ringBufferR[writePosR] = samplesR[i];
		jassert(readPosR >= 0 && readPosR <= WRAP_MASK);
		samplesR[i] = ringBufferR[readPosR] * 0.5f;

		if(writePosR < readPosR)
		{
			readPosR = int(linkR++ - int(d + std::sin(2 * MathConstants<float>().pi * count) * d)) % (WRAP_MASK);
		}
		else
		{
			linkR = writePosR;
			readPosR = int(writePosR - int(d + std::sin(2 * MathConstants<float>().pi * count) * d)) % (WRAP_MASK);
		}
		writePosR = (writePosR + 1) % WRAP_MASK;

		count += (dc / lastSampleRate) * 10.f;
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
	delayInSeconds.store((50 + val) / 50.0f);
//	prepareToPlay(lastSampleRate, 0);
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
