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
			return primary;
		}
		Colour getButtonBackground()
		{
			return primaryDark;
		}
		Colour getHighlight()
		{
			return primaryLight;
		}
		Colour getTransperent()
		{
			return invisible;
		}
		Colour getText()
		{
			return textColour;
		}
		Colour getTextInverse()
		{
			return textColourInverted;
		}
		Colour getBackgroundLight()
		{
			return backgorundLight;
		}
		Colour getBackgroundDark()
		{
			return backgorundDark;
		}
		Colour getSliderColour()
		{
			return secondary;
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
		setColour(ComboBox::ColourIds::outlineColourId, colours.getTransperent());
		setColour(ComboBox::ColourIds::textColourId, colours.getTextInverse());

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
		setColour(PopupMenu::ColourIds::highlightedTextColourId, colours.getText());
		setColour(PopupMenu::ColourIds::textColourId, colours.getText());

	}
};