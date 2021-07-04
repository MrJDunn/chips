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
		setColour(Slider::ColourIds::textBoxOutlineColourId, colours.getBorder());
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

	void drawLinearSlider(Graphics& g, int x, int y, int width, int height,
		float sliderPos,
		float minSliderPos,
		float maxSliderPos,
		const Slider::SliderStyle style, Slider& slider) override
	{
		if (slider.isBar())
		{
			for (int i = 0; i < sliderPos; i++)
			{
				if (i % 2 == 0)
				{
					g.setColour(slider.findColour(Slider::trackColourId));
					g.fillRect(slider.isHorizontal() ? Rectangle<float>(static_cast<float>(i - x + 0.1f), y + 0.5f, static_cast<float>(sliderPos - i - 0.2f), height - 1.0f)
						: Rectangle<float>(x + 0.5f, static_cast<float>(i +  0.1f), width - 1.0f, 1.0f));

					g.setColour(slider.findColour(Slider::backgroundColourId));
					g.drawRect(slider.isHorizontal() ? Rectangle<float>(static_cast<float>(i - x + 0.1f), y + 0.5f, static_cast<float>(sliderPos - i), height - 1.0f)
						: Rectangle<float>(x + 0.5f, static_cast<float>(i + 0.1f), width - 1.0f, 0.1f));
				}
			}
		}
		else
		{
			auto isTwoVal = (style == Slider::SliderStyle::TwoValueVertical || style == Slider::SliderStyle::TwoValueHorizontal);
			auto isThreeVal = (style == Slider::SliderStyle::ThreeValueVertical || style == Slider::SliderStyle::ThreeValueHorizontal);

			auto trackWidth = jmin(6.0f, slider.isHorizontal() ? height * 0.25f : width * 0.25f);

			Point<float> startPoint(slider.isHorizontal() ? x : x + width * 0.5f,
				slider.isHorizontal() ? y + height * 0.5f : height + y);

			Point<float> endPoint(slider.isHorizontal() ? width + x : startPoint.x,
				slider.isHorizontal() ? startPoint.y : y);

			Path backgroundTrack;
			backgroundTrack.startNewSubPath(startPoint);
			backgroundTrack.lineTo(endPoint);
			g.setColour(slider.findColour(Slider::backgroundColourId));
			g.strokePath(backgroundTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

			Path valueTrack;
			Point<float> minPoint, maxPoint, thumbPoint;

			if (isTwoVal || isThreeVal)
			{
				minPoint = { slider.isHorizontal() ? minSliderPos : width * 0.5f,
							 slider.isHorizontal() ? height * 0.5f : minSliderPos };

				if (isThreeVal)
					thumbPoint = { slider.isHorizontal() ? sliderPos : width * 0.5f,
								   slider.isHorizontal() ? height * 0.5f : sliderPos };

				maxPoint = { slider.isHorizontal() ? maxSliderPos : width * 0.5f,
							 slider.isHorizontal() ? height * 0.5f : maxSliderPos };
			}
			else
			{
				auto kx = slider.isHorizontal() ? sliderPos : (x + width * 0.5f);
				auto ky = slider.isHorizontal() ? (y + height * 0.5f) : sliderPos;

				minPoint = startPoint;
				maxPoint = { kx, ky };
			}

			auto thumbWidth = getSliderThumbRadius(slider);

			valueTrack.startNewSubPath(minPoint);
			valueTrack.lineTo(isThreeVal ? thumbPoint : maxPoint);
			g.setColour(slider.findColour(Slider::trackColourId));
			g.strokePath(valueTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

			if (!isTwoVal)
			{
				g.setColour(slider.findColour(Slider::thumbColourId));
				g.fillEllipse(Rectangle<float>(static_cast<float> (thumbWidth), static_cast<float> (thumbWidth)).withCentre(isThreeVal ? thumbPoint : maxPoint));
			}

			if (isTwoVal || isThreeVal)
			{
				auto sr = jmin(trackWidth, (slider.isHorizontal() ? height : width) * 0.4f);
				auto pointerColour = slider.findColour(Slider::thumbColourId);

				if (slider.isHorizontal())
				{
					drawPointer(g, minSliderPos - sr,
						jmax(0.0f, y + height * 0.5f - trackWidth * 2.0f),
						trackWidth * 2.0f, pointerColour, 2);

					drawPointer(g, maxSliderPos - trackWidth,
						jmin(y + height - trackWidth * 2.0f, y + height * 0.5f),
						trackWidth * 2.0f, pointerColour, 4);
				}
				else
				{
					drawPointer(g, jmax(0.0f, x + width * 0.5f - trackWidth * 2.0f),
						minSliderPos - trackWidth,
						trackWidth * 2.0f, pointerColour, 1);

					drawPointer(g, jmin(x + width - trackWidth * 2.0f, x + width * 0.5f), maxSliderPos - sr,
						trackWidth * 2.0f, pointerColour, 3);
				}
			}
		}
	}
};