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
	paintVerticalLines(g);
}

void WaveformView::resized()
{
}

void WaveformView::timerCallback()
{
	processor.bufferHelper.loadBuffer(buffer);
	repaint();
}

void WaveformView::paintVerticalLines(Graphics & g)
{
	g.setColour(Colours::black);
	g.fillAll();
	auto bufferLength = buffer.size();
	auto width = getLocalBounds().getWidth();
	auto height = getLocalBounds().getHeight();
	float divisor = 1.0f;
	float amplitude = 25.0f;

	g.setColour(Colours::lawngreen);

	g.drawRect(getLocalBounds());
	float thisSample = 0.0f;
	float lastSample = 0.0f;
	for (int i = 0; i < 2 * bufferLength; ++i)
	{
		if (i % 2 == 0)
		{
			thisSample = buffer.at(i / 2) * amplitude + height / 2.0f;
			g.drawLine({(float)i / divisor, (float)height / 2.0f, (float)(i + 1.0f) / divisor, thisSample });
			lastSample = thisSample;
		}
	}
}

void WaveformView::paintHorizontalLines(Graphics & g)
{
	g.setColour(Colours::grey.brighter());
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

		thisSample = buffer.at(i) * amplitude + height / 2;
		g.drawLine({ (float)i / divisor, lastSample,(float)(i + 1.0f) / divisor, thisSample });
		lastSample = thisSample;
	}
}
