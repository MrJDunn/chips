/*
  ==============================================================================

    PitchShifter.cpp
    Created: 10 Jul 2021 4:20:00pm
    Author:  Jeff

  ==============================================================================
*/

#include "PitchShifter.h"

BitCrush::BitCrush()
{
}

BitCrush::~BitCrush()
{
}

void BitCrush::setFactor(float val)
{
	factor.store(val);
}

float BitCrush::getFactor()
{
	return factor.load();
}

const String BitCrush::getName() const
{
	return "PitchShifter";
}

void BitCrush::prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock)
{
	this->sampleRate = sampleRate;
	this->blockSize = maximumExpectedSamplesPerBlock;
}

void BitCrush::releaseResources()
{
}

void BitCrush::processBlock(AudioBuffer<float>& buffer, MidiBuffer & midiMessages)
{
	const float factorCopy = factor.load();

	int numChannels = buffer.getNumChannels();
	int numSamples = buffer.getNumSamples();

	for (int channel = 0; channel < numChannels; ++channel)
	{
		float* out = buffer.getWritePointer(channel);
		for (int s = 0; s < numSamples; s += factorCopy)
		{
			float avg = 0.0f;
			for (int i = 0; i < factorCopy; ++i)
			{
				if(s + i >= numSamples)
				{
					break;
				}
				avg += out[s + i];
			}
			avg /= (float)factorCopy;
			for (int i = 0; i < factorCopy; ++i)
			{	
				if(s + i >= numSamples)
				{
					break;
				}
				out[s + i] = avg;
			}
		}
	}

	
}

double BitCrush::getTailLengthSeconds() const
{
	return 0.0;
}

bool BitCrush::acceptsMidi() const
{
	return false;
}

bool BitCrush::producesMidi() const
{
	return false;
}

AudioProcessorEditor * BitCrush::createEditor()
{
	return nullptr;
}

bool BitCrush::hasEditor() const
{
	return false;
}

int BitCrush::getNumPrograms()
{
	return 0;
}

int BitCrush::getCurrentProgram()
{
	return 0;
}

void BitCrush::setCurrentProgram(int index)
{
}

const String BitCrush::getProgramName(int index)
{
	return String();
}

void BitCrush::changeProgramName(int index, const String & newName)
{
}

void BitCrush::getStateInformation(juce::MemoryBlock & destData)
{
}

void BitCrush::setStateInformation(const void * data, int sizeInBytes)
{
}
