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

private:

	WaveBase* wave;

	struct Envelope
	{
		float amplitude = 0.0f;
		float attack = 0.0f;	// the duration taken to achieve the volume
		float decay = 0.0f;		// time taken to fallof after sustain period
		float sustain = 0.0f;	// the duration of the sustain
		float release = 0.0f;	// the duration taken to reach 0 after release
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
