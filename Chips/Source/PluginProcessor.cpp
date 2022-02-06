/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
ChipsAudioProcessor::ChipsAudioProcessor(): 
	AudioProcessor(BusesProperties()
		.withInput("Input", AudioChannelSet::stereo(), false)
		.withOutput ("Output", AudioChannelSet::stereo(), true)),
	state("ChipsState"),
	waveIdentifier("wave"),
	amplitudeIdentifier("amplitude"),
	attackIdentifier("attack"),
	decayIdentifier("decay"),
	sustainPathsIdentifier("sustain"),
	releaseIdentifier("release"),
	pulseWidthIdentifier("pulseWidth"),
	pitchIdentifier("pitch"),
	vibratoIdentifier("vibrato")
{
	state.setProperty(waveIdentifier, 1.0f, nullptr);
	state.setProperty(amplitudeIdentifier, 50.0f, nullptr);
	state.setProperty(attackIdentifier, 50.0f, nullptr);
	state.setProperty(decayIdentifier, 50.0f, nullptr);
	state.setProperty(sustainPathsIdentifier, 50.0f, nullptr);
	state.setProperty(releaseIdentifier, 50.0f, nullptr);
	state.setProperty(pulseWidthIdentifier, 0.0f, nullptr);
	state.setProperty(pitchIdentifier, 1.0f, nullptr);
	state.setProperty(vibratoIdentifier, -50.0f, nullptr);
}

ChipsAudioProcessor::~ChipsAudioProcessor()
{
}

//==============================================================================
const String ChipsAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ChipsAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ChipsAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ChipsAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ChipsAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ChipsAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ChipsAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ChipsAudioProcessor::setCurrentProgram (int index)
{
}

const String ChipsAudioProcessor::getProgramName (int index)
{
    return {};
}

void ChipsAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void ChipsAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

	String message;
	message << "prepareToPlay()\n";
	message << "      sampleRate: " << sampleRate << "\n";
	message << " samplesPerBlock: " << samplesPerBlock << "\n";
	Logger::getCurrentLogger()->writeToLog(message);

	pitchShifter.prepareToPlay(sampleRate, samplesPerBlock);
	vibrato.prepareToPlay(sampleRate, samplesPerBlock);
}

void ChipsAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ChipsAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ChipsAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

	buffer.clear();

	int t;
	MidiMessage m;
	for (auto it = MidiBuffer::Iterator(midiMessages); it.getNextEvent(m, t);)
	{
		if (m.isNoteOn())
		{
			noteTracker.add(m.getNoteNumber());
		}
		if (m.isNoteOff())
		{
			noteTracker.remove(m.getNoteNumber());
		}
	}

	if (wave)
	{
		wave->setSampleRate(getSampleRate());
		for (int i = 0; i < 127; i++)
		{
			calculateMagintude(&noteTracker[i]);

			if (noteTracker[i].state != Note::Off)
			{
				noteTracker[i].pulseWidth = envelope.pulseWidth;
				wave->perform(noteTracker[i], buffer);
			}
		}
	}

	pitchShifter.processBlock(buffer, midiMessages);
	vibrato.processBlock(buffer, midiMessages);

	bufferHelper.saveBuffer(buffer);
}

//==============================================================================
bool ChipsAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ChipsAudioProcessor::createEditor()
{
    return new ChipsAudioProcessorEditor (*this);
}

//==============================================================================
void ChipsAudioProcessor::getStateInformation (MemoryBlock& destData)
{
	DBG(state.toXmlString());

	std::unique_ptr<juce::XmlElement> xml(state.createXml());
	copyXmlToBinary(*xml, destData);
}

void ChipsAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	if (xmlState.get() != nullptr)
	{
		if (xmlState->hasTagName("ChipsState"))
		{
			ValueTree state = juce::ValueTree::fromXml(*xmlState);

			// Set a default value if property not present

			setWaveform(state.hasProperty("wave") ? state.getProperty("wave") : 1.0f);
			setAmplitude(state.hasProperty("amplitude") ? state.getProperty("amplitude") : 50.0f);
			setAttack(state.hasProperty("attack") ? state.getProperty("attack") : 50.0f);
			setDecay(state.hasProperty("decay") ? state.getProperty("decay") : 50.0f);
			setSustain(state.hasProperty("sustain") ? state.getProperty("sustain") : 50.0f);
			setRelease(state.hasProperty("release") ? state.getProperty("release") : 50.0f);
			setPulseWidth(state.hasProperty("pulseWidth") ? state.getProperty("pulseWidth") : 0.0f);
			setPitch(state.hasProperty("pitch") ? state.getProperty("pitch") : 1.0f);
			setVibrato(state.hasProperty("vibrato") ? state.getProperty("vibrato") : -50.0f);

		}
	}
}

void ChipsAudioProcessor::setWaveform(int newWaveform)
{
	switch (newWaveform)
	{
	case 1:
	{
		wave = std::make_unique<Square>();
		break;
	}
	case 2:
	{
		wave = std::make_unique<AtonalBeep>();
		break;
	}
	case 3:
	{
		wave = std::make_unique<Sine>();
		break;
	}
	case 4:
	{
		wave = std::make_unique<Triangle>();
		break;
	}
	case 5:
	{
		wave = std::make_unique<Saw>();
		break;
	}
	case 6:
	{
		wave = std::make_unique<Noise>();
		break;
	}
	default:
	{
		// invalid waveform
		jassertfalse;
		break;
	}
	}
	state.setProperty(waveIdentifier, newWaveform, nullptr);
}

void ChipsAudioProcessor::setAmplitude(int value)
{
	envelope.amplitude = value / 50.1f;
	state.setProperty(amplitudeIdentifier, value, nullptr);
}

void ChipsAudioProcessor::setAttack(int value)
{
	envelope.attack = abs(0.4 - value / 259.99f);
	state.setProperty(attackIdentifier, value, nullptr);
}

void ChipsAudioProcessor::setDecay(int value)
{
	envelope.decay = abs(0.4 - value / 259.99f);
	state.setProperty(decayIdentifier, value, nullptr);
}

void ChipsAudioProcessor::setSustain(int value)
{
	envelope.sustain = value / 100.1f;
	state.setProperty(sustainPathsIdentifier, value, nullptr);
}

void ChipsAudioProcessor::setRelease(int value)
{
	envelope.release = abs(0.4 - value / 259.99f);
	state.setProperty(releaseIdentifier, value, nullptr);
}

void ChipsAudioProcessor::setPulseWidth(int value)
{
	envelope.pulseWidth = value / 50.1f;
	state.setProperty(pulseWidthIdentifier, value, nullptr);
}

void ChipsAudioProcessor::setPitch(int value)
{
	pitchShifter.setFactor(value + 1);
	state.setProperty(pitchIdentifier, value, nullptr);
}

void ChipsAudioProcessor::setVibrato(int value)
{	
	//TODO set vibrato value
	vibrato.setFactor(value);
	state.setProperty(vibratoIdentifier, value, nullptr);
}

int ChipsAudioProcessor::getWaveform()
{
	return state.getProperty("wave");
}

int ChipsAudioProcessor::getAmplitude()
{
	return state.getProperty("amplitude");
}

int ChipsAudioProcessor::getAttack()
{
	return state.getProperty("attack");
}

int ChipsAudioProcessor::getDecay()
{
	return state.getProperty("decay");
}

int ChipsAudioProcessor::getSustain()
{
	return state.getProperty("sustain");
}

int ChipsAudioProcessor::getRelease()
{
	return state.getProperty("release");
}

int ChipsAudioProcessor::getPulseWidth()
{
	return state.getProperty("pulseWidth");
}

int ChipsAudioProcessor::getPitch()
{
	return state.getProperty("pitch");
}

int ChipsAudioProcessor::getVibrato()
{
	return state.getProperty("vibrato");
}

void ChipsAudioProcessor::calculateMagintude(Note* note)
{
	switch (note->state)
	{
	case Note::Off: break;
	case Note::A:
	{
		switch(pitchModMode)
		{
		case OFF:
			break;
		case ASC:
			pitchShifter.setFactor(100);
			break;
		case DSC:
			pitchShifter.setFactor(1);
			break;
		}
		note->smoothingFactor *= 10.01;
		if (note->amplitude + envelope.attack < envelope.amplitude)
		{
			note->amplitude += envelope.attack;
		}
		else
		{
			note->amplitude = envelope.amplitude;
			note->state = Note::D;
		}
		break;
	};
	case Note::D:
	{
		if (note->amplitude - envelope.decay > envelope.sustain)
		{
			note->amplitude -= envelope.decay;
		}
		else
		{
			note->amplitude = envelope.sustain;
			note->state = Note::S;
		}
		break;
	};
	case Note::S: break;
	case Note::R:
	{	
		switch(pitchModMode)
		{
		case OFF:
			break;
		case ASC:
			if(pitchShifter.getFactor() > 1)
				pitchShifter.setFactor(pitchShifter.getFactor() - 1);
			break;
		case DSC:	
			if(pitchShifter.getFactor() < 100)
				pitchShifter.setFactor(pitchShifter.getFactor() + 1);
			break;
		}

		note->smoothingFactor *= 0.01;

		if (note->amplitude - envelope.release > 0.0f)
		{
			note->amplitude -= envelope.release;
		}
		else
		{
			note->amplitude = 0.0f;
			note->state = Note::Off;
		}
		break;
	};
	}
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ChipsAudioProcessor();
}
