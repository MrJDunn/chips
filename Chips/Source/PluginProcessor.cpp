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
	pulseWidthIdentifier("pulseWidth")
{
	state.setProperty(waveIdentifier, 1.0f, nullptr);
	state.setProperty(amplitudeIdentifier, 50.0f, nullptr);
	state.setProperty(attackIdentifier, 50.0f, nullptr);
	state.setProperty(decayIdentifier, 50.0f, nullptr);
	state.setProperty(sustainPathsIdentifier, 50.0f, nullptr);
	state.setProperty(releaseIdentifier, 50.0f, nullptr);
	state.setProperty(pulseWidthIdentifier, 0.0f, nullptr);

	wave = nullptr;
}

ChipsAudioProcessor::~ChipsAudioProcessor()
{
	delete wave;
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

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.

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
		// play a sound for each note held!
		// https://docs.juce.com/master/tutorial_mpe_introduction.html
		// https://docs.juce.com/master/tutorial_synth_using_midi_input.html
	}

	if (wave)
	{
		wave->setSampleRate(getSampleRate());
		for (int i = 0; i < 127; i++)
		{
			calculateMagintude(&noteTracker[i]);

			if (noteTracker[i].state != Note::Off)// || i == 64)
			{
				noteTracker[i].pulseWidth = envelope.pulseWidth;

				//wave->reset(buffer);
				wave->perform(noteTracker[i], buffer);
			}
		}
	}
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

			if(state.hasProperty("wave"))
				setWaveform(state.getProperty("wave"));

			if (state.hasProperty("amplitude"))
				setAmplitude(state.getProperty("amplitude"));

			if (state.hasProperty("attack"))
				setAttack(state.getProperty("attack"));

			if (state.hasProperty("decay"))
				setDecay(state.getProperty("decay"));

			if (state.hasProperty("sustain"))
				setSustain(state.getProperty("sustain"));
	
			if (state.hasProperty("release"))
				setRelease(state.getProperty("release"));

			if (state.hasProperty("pulseWidth"))
				setPulseWidth(state.getProperty("pulseWidth"));

		}
	}
}

void ChipsAudioProcessor::setWaveform(int newWaveform)
{
	switch (newWaveform)
	{
	case 1:
	{
		delete wave;
		wave = new Square();
		break;
	}
	case 2:
	{
		delete wave;
		wave = new AtonalBeep();
		break;
	}
	case 3:
	{
		delete wave;
		wave = new Sine();
		break;
	}
	case 4:
	{
		delete wave;
		wave = new Triangle();
		break;
	}
	case 5:
	{
		delete wave;
		wave = new Saw();
		break;
	}
	case 6:
	{
		delete wave;
		wave = new Noise();
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
	envelope.amplitude = value / 100.1f;
	state.setProperty(amplitudeIdentifier, value, nullptr);
}

void ChipsAudioProcessor::setAttack(int value)
{
	envelope.attack = value / 500.1f;
	state.setProperty(attackIdentifier, value, nullptr);
}

void ChipsAudioProcessor::setDecay(int value)
{
	envelope.decay = value / 500.1f;
	state.setProperty(decayIdentifier, value, nullptr);
}

void ChipsAudioProcessor::setSustain(int value)
{
	envelope.sustain = value / 100.1f;
	state.setProperty(sustainPathsIdentifier, value, nullptr);
}

void ChipsAudioProcessor::setRelease(int value)
{
	envelope.release = value / 500.1f;
	state.setProperty(releaseIdentifier, value, nullptr);
}

void ChipsAudioProcessor::setPulseWidth(int value)
{
	envelope.pulseWidth = value / 50.1f;
	state.setProperty(pulseWidthIdentifier, value, nullptr);
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

void ChipsAudioProcessor::calculateMagintude(Note* note)
{
	switch (note->state)
	{
	case Note::Off: break;
	case Note::A:
	{
		note->smoothingFactor *= 10.01;
		if (note->amplitude < envelope.amplitude)
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
		if (note->amplitude > envelope.sustain)
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
		note->smoothingFactor *= 0.01;

		if (note->amplitude > 0.0f)
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
