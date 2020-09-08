/*
  ==============================================================================

    ChipsLookAndFeel.h
    Created: 4 Sep 2020 9:53:04am
    Author:  Jeff

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class ChipsLookAndFeel : public LookAndFeel_V4
{
public:

	struct ChipsColours
	{
	public:
		
		Colour getMenuBackground()
		{
			return Colours::black;//primary;
		}
		Colour getButtonBackground()
		{
			return Colours::black;//primaryDark;
		}
		Colour getBorder()
		{
			return Colours::lawngreen;//primaryLight;
		}
		Colour getHighlight()
		{
			return Colours::lawngreen;//primaryLight;
		}
		Colour getTransperent()
		{
			return invisible;
		}
		Colour getText()
		{
			return Colours::lawngreen;//textColour;
		}
		Colour getTextInverse()
		{
			return Colours::black;//textColourInverted;
		}
		Colour getBackgroundLight()
		{
			return Colours::black;//backgorundLight;
		}
		Colour getBackgroundDark()
		{
			return Colours::black;// backgorundDark;
		}
		Colour getSliderColour()
		{
			return Colours::lawngreen;// secondary;
		}
	private:
		Colour invisible = Colour::fromRGBA(0, 0, 0, 0);

		Colour black = Colour::fromRGB(0, 0, 0);
		Colour white = Colour::fromRGB(255, 255, 255);

		Colour primary = Colour::fromRGB(3, 155, 229);
		Colour primaryLight = Colour::fromRGB(99, 204, 255);
		Colour primaryDark = Colour::fromRGB(0, 109, 179);

		Colour secondary = Colour::fromRGB(255, 160, 0);
		Colour secondaryLight = Colour::fromRGB(255, 209, 73);
		Colour secondaryDark = Colour::fromRGB(192, 112, 0);

		Colour backgorundLight = Colours::lightgrey;
		Colour backgorundDark = Colours::grey.brighter();

		Colour textColour = Colour::fromRGB(0, 0, 0);
		Colour textColourInverted = Colour::fromRGB(255, 255, 255);

	} colours;

	ChipsLookAndFeel()
	{
		setColour(ComboBox::ColourIds::backgroundColourId, colours.getButtonBackground());
		setColour(ComboBox::ColourIds::outlineColourId, colours.getBorder());
		setColour(ComboBox::ColourIds::textColourId, colours.getText());
		setColour(ComboBox::ColourIds::arrowColourId, colours.getHighlight());

		setColour(Slider::ColourIds::backgroundColourId, colours.getBackgroundDark());
		setColour(Slider::ColourIds::textBoxTextColourId, colours.getText());
		setColour(Slider::ColourIds::textBoxOutlineColourId, colours.getTransperent());
		setColour(Slider::ColourIds::textBoxHighlightColourId, colours.getHighlight());
		setColour(Slider::ColourIds::textBoxBackgroundColourId, colours.getTransperent());
		setColour(Slider::ColourIds::thumbColourId, colours.getSliderColour());
		setColour(Slider::ColourIds::trackColourId, colours.getSliderColour());

		setColour(TextEditor::ColourIds::textColourId, colours.getText());

		setColour(Label::ColourIds::textColourId, colours.getText());

		setColour(PopupMenu::ColourIds::backgroundColourId, colours.getMenuBackground());
		setColour(PopupMenu::ColourIds::highlightedBackgroundColourId, colours.getHighlight());
		setColour(PopupMenu::ColourIds::highlightedTextColourId, colours.getTextInverse());
		setColour(PopupMenu::ColourIds::textColourId, colours.getText());
	}

	Typeface::Ptr getTypefaceForFont(const Font& f) override
	{
		static Typeface::Ptr myFont = Typeface::createSystemTypefaceFor(BinaryData::PressStart2PvaV7_ttf, BinaryData::PressStart2PvaV7_ttfSize);
		setDefaultSansSerifTypeface(myFont);
		return myFont;
	}

};