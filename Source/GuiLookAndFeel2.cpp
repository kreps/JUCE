/*
==============================================================================

GuiLookAndFeel.cpp
Created: 9 Jan 2015 11:37:13am
Author:  kristian

==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "GuiLookAndFeel2.h"

/*Gradient rotary knobs drawable*/
//==============================================================================
GuiLookAndFeel2::GuiLookAndFeel2()
{
	// In your constructor, you should add any child components, and
	// initialise any special settings that your component needs.

}

GuiLookAndFeel2::~GuiLookAndFeel2()
{
}
void GuiLookAndFeel2::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
									   float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{
	const float radius = jmin(width / 2, height / 2) - 2.0f;
	const float centreX = x + width * 0.5f;
	const float centreY = y + height * 0.5f;
	const float rx = centreX - radius;
	const float ry = centreY - radius;
	const float rw = radius * 2.0f;
	const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
	const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();
	const String name = slider.getName();

	if (isMouseOver )
		slider.setMouseCursor(MouseCursor::PointingHandCursor);

	if(name == "gainSlider")
		g.setColour((Colours::yellow).withAlpha(isMouseOver? 1.0f: 0.5f));
	else if ( name == "panSlider")
		g.setColour((Colours::coral).withAlpha(isMouseOver? 1.0f: 0.5f));
	else if (name == "delaySlider")
		g.setColour((Colours::yellowgreen).withAlpha(isMouseOver? 1.0f: 0.5f));
	else if (name == "delayTimeSlider")
		g.setColour((Colours::limegreen).withAlpha(isMouseOver? 1.0f: 0.5f));
	else if (name == "hpfSlider")
		g.setColour((Colours::white).withAlpha(isMouseOver? 1.0f: 0.5f));
	else if (name == "dfs_violet")
		g.setColour((Colours::violet).withAlpha(isMouseOver? 1.0f: 0.5f));
	else 
		g.setColour(slider.findColour(Slider::rotarySliderFillColourId).withAlpha(isMouseOver? 1.0f: 0.5f));

	if(!slider.isEnabled())
		g.setColour((Colours::black).withAlpha(0.3f));

	{
		const float lineThickness = jmin (15.0f, jmin (width, height) * 0.45f) * 0.1f;
		Path outlineArc;
		outlineArc.addEllipse(rx+6, ry+6, rw-12, rw-12);
		g.strokePath (outlineArc,PathStrokeType (lineThickness));  
	}
	if (slider.isEnabled())
		g.setColour(slider.findColour(Slider::rotarySliderFillColourId).withAlpha(isMouseOver ? 1.0f : 0.7f));
	else
		g.setColour(Colour(0x80808080));

	{
		Path filledArc2;
		filledArc2.addEllipse(rx+12, ry+12, rw-24, rw-24);
		g.setColour(Colours::darkgrey);
		g.fillPath(filledArc2);
	}

	Path needle;
	Rectangle<float> r(rx+12, ry+12, rw-24, rw-24);
	Rectangle<float> r2(0.0f, 0.0f, rw*0.05f, rw * 0.2f);
	needle.addRectangle(r2.withPosition(Point<float>(r.getCentreX() - (r2.getWidth() / 2.0f), r.getY())));

	g.setColour (Colours::whitesmoke);
	g.fillPath(needle, AffineTransform::rotation(angle, r.getCentreX(), r.getCentreY()));
}

