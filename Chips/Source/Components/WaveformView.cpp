/*
  ==============================================================================

    WaveformView.cpp
    Created: 30 Aug 2020 7:29:07pm
    Author:  Jeff

  ==============================================================================
*/

#include "WaveformView.h"

WaveformView::WaveformView(ChipsAudioProcessor& p): processor(p)
{
	startTimer(30);
}

WaveformView::~WaveformView()
{
}

void WaveformView::paint(Graphics& g)
{
	g.setColour(Colours::grey);
	g.fillAll();
	auto bufferLength = buffer.size();
	auto width = getLocalBounds().getWidth();
	auto height = getLocalBounds().getHeight();
	float divisor = 1.0f;
	float amplitude = 25.0f;

	g.setColour(Colours::white);

	float thisSample = 0.0f;
	float lastSample = 0.0f;
	for (int i = 0; i < bufferLength; ++i)
	{
		jassert(i < buffer.size());

		thisSample = buffer.at(i) * amplitude + 80.0f;
		g.drawLine({(float)i/ divisor, lastSample,(float)(i + 1.0f) / divisor, thisSample });
		lastSample = thisSample;
	}
}

void WaveformView::resized()
{
}

void WaveformView::timerCallback()
{
	processor.bufferHelper.giveMeBufferStuff(buffer);
	repaint();
}
