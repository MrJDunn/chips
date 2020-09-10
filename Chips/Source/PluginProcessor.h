/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <queue>
#include "Models/Note.h"

#include "Waveforms/WaveBase.h"
#include "Waveforms/Noise.h"
#include "Waveforms/AtonalBeep.h"
#include "Waveforms/Sine.h"
#include "Waveforms/Square.h"
#include "Waveforms/Saw.h"
#include "Waveforms/Triangle.h"

//==============================================================================
/**
*/
class ChipsAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    ChipsAudioProcessor();
    ~ChipsAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	//==============================================================================
	// Params
	void setWaveform(int);
	void setAmplitude(int);

	void setAttack(int);
	void setDecay(int);
	void setSustain(int);
	void setRelease(int);
	void setPulseWidth(int);

	int getWaveform();
	int getAmplitude();

	int getAttack();
	int getDecay();
	int getSustain();
	int getRelease();
	int getPulseWidth();

	//==============================================================================
	// UI hooks
	struct BufferHelper
	{
		void giveMeBufferStuff(std::vector<float>& bufferToFill)
		{
			//ScopedLock lock(section);

			size_t size = lastBuffer.size();
			bufferToFill.resize(size);

			for (int i = 0; i < size; i++)
			{
				jassert(i < lastBuffer.size());
				bufferToFill[i] = lastBuffer.at(i);
			}
		}

		void clearBuffer(size_t numSamples)
		{
			lastBuffer.resize(numSamples);

			for (int i = 0; i < numSamples; i++)
			{
				jassert(i < numSamples);
				lastBuffer[i] = 0;
			}	
		}

		void saveBuffer(AudioBuffer<float>& bufferRef)
		{
			//ScopedLock lock(section);

			auto numChannels = bufferRef.getNumChannels();
			auto numSamples = bufferRef.getNumSamples();

			clearBuffer(numSamples);	

			for (int i = 0; i < numSamples; i++)
			{
				for (int channel = 0; channel < numChannels; channel++)
				{
					auto readPtr = bufferRef.getReadPointer(channel);
					jassert(i < numSamples);
					lastBuffer[i] += readPtr[i];
				}
			}
		}
		std::vector<float> lastBuffer;
		CriticalSection section;
	} bufferHelper;

private:

	WaveBase* wave;
	ValueTree state;

	Identifier waveIdentifier;
	Identifier amplitudeIdentifier;
	Identifier attackIdentifier;
	Identifier decayIdentifier;
	Identifier sustainPathsIdentifier;
	Identifier releaseIdentifier;
	Identifier pulseWidthIdentifier;

	struct Envelope
	{
		float wave = 1.0f;
		float amplitude = 50.0f;
		float attack = 50.0f;		// the duration taken to achieve the volume
		float decay = 50.0f;			// time taken to fallof after sustain period
		float sustain = 50.0f;		// the duration of the sustain
		float release = 50.0f;		// the duration taken to reach 0 after release
		float pulseWidth = 0.0f;
	} envelope;

	//==============================================================================
	void calculateMagintude(Note*);

	struct NoteTracker
	{
	public:
		Note& operator[](int8 note)
		{
			return notes[note];
		}
		void add(int8 note)
		{
			Note newNote;
			newNote.state = Note::A;
			newNote.midiValue = note;
			newNote.lastAmplitude = 0.0;
			notes[note] = newNote;
		}
		void remove(int8 note)
		{
			notes[note].state = Note::R;
		}
	private:
		Note notes[128];
	} noteTracker;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChipsAudioProcessor)
};
