/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ChipsAudioProcessor::ChipsAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	amplitude = 1.0f;
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

	for (int i = 0; i < 127; i++)
	{
		if (noteTracker[i])
		{
			// play our sound
			for (int channel = 0; channel < totalNumInputChannels; ++channel)
			{
				auto* channelData = buffer.getWritePointer(channel);

				for (auto sample = 0; sample < buffer.getNumSamples(); ++sample)
				{
					channelData[sample] = (random.nextFloat() * 2.0f - 1.0f) * amplitude;
				}
				// ..do something to the data...
			}
		}
	}


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
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ChipsAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void ChipsAudioProcessor::setAmplitude(int value)
{
	amplitude = value / 100.0f;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ChipsAudioProcessor();
}
