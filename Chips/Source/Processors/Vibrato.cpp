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

void Vibrato::processBlock(AudioBuffer<float>& buffer, MidiBuffer & midiMessages)
{
	int numChannels = buffer.getNumChannels();
	int numSamples = buffer.getNumSamples();

	float* samplesL = buffer.getWritePointer(0);
	float* samplesR = buffer.getWritePointer(1);

	float dc = delayInSeconds;
	float d = (dc * lastSampleRate) / 100.f;

	for (int i = 0; i < numSamples; ++i)
	{
		ringBufferL[writePosL] = samplesL[i];
		samplesL[i] = ringBufferL[readPosL] * 0.5f;
		readPosL = int(writePosL - int(d + std::sin(2 * MathConstants<float>().pi * count) * d)) & (WRAP_MASK);
		jassert(readPosL >= 0);
		writePosL = (writePosL + 1) & WRAP_MASK;

		ringBufferR[writePosR] = samplesR[i];
		samplesR[i] = ringBufferR[readPosR] * 0.5f;
		readPosR = int(writePosR - int(d + std::sin(2 * MathConstants<float>().pi * count) * d)) & (WRAP_MASK);
		jassert(readPosR >= 0);
		writePosR = (writePosR + 1) & WRAP_MASK;

		count += (dc / lastSampleRate) * 100.f;
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
	prepareToPlay(lastSampleRate, 0);
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
