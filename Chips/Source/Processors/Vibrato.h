/*
  ==============================================================================

    Vibrato.h
    Created: 6 Nov 2021 6:34:26pm
    Author:  Jeff

  ==============================================================================
*/

#include <JuceHeader.h>

#pragma once
class Vibrato : public AudioProcessor
{
public:
	Vibrato();
	~Vibrato();

	// Inherited via AudioProcessor
	virtual const String getName() const override;
	virtual void prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock) override;
	virtual void releaseResources() override;
	virtual void processBlock(AudioBuffer<float>& buffer, MidiBuffer & midiMessages) override;
	virtual double getTailLengthSeconds() const override;
	virtual bool acceptsMidi() const override;
	virtual bool producesMidi() const override;
	virtual AudioProcessorEditor * createEditor() override;
	virtual bool hasEditor() const override;
	virtual int getNumPrograms() override;
	virtual int getCurrentProgram() override;
	virtual void setCurrentProgram(int index) override;
	virtual const String getProgramName(int index) override;
	virtual void changeProgramName(int index, const String & newName) override;
	virtual void getStateInformation(juce::MemoryBlock & destData) override;
	virtual void setStateInformation(const void * data, int sizeInBytes) override;

	void setFactor(float);

private:
	void reset();

	int getWritePos();

	static const int WRAP_MASK = 0x00FFFFFF;
	float ringBufferL[WRAP_MASK];
	float ringBufferR[WRAP_MASK];
	int readPosL = 0, writePosL = 0;
	int readPosR = 0, writePosR = 0;

	double lastSampleRate = 48000.0;
	int countL = 1;
	int countR = 1;
	bool asc = true;
	std::atomic<float> delayInSeconds = 0.5f;
};
