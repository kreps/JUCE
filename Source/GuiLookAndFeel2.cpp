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

    if (slider.isEnabled())
        g.setColour(slider.findColour(Slider::rotarySliderFillColourId).withAlpha(isMouseOver ? 1.0f : 0.7f));
    else
        g.setColour(Colour(0x80808080));

    {
        Path filledArc2;
        //filledArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, angle, 0.0);
        filledArc2.addEllipse(rx, ry, rw, rw);

        g.setGradientFill(ColourGradient(Colours::white, 0, 0, Colours::black, rw*2, rw*2, true));
        g.fillPath(filledArc2);
    }

        {
            /*const float lineThickness = jmin (15.0f, jmin (width, height) * 0.45f) * 0.1f;
            Path outlineArc;
            outlineArc.addEllipse(rx, ry, rw, rw);
            g.strokePath (outlineArc, PathStrokeType (lineThickness));*/
        }
        Path needle;
        Rectangle<float> r(rx, ry, rw, rw);
        Rectangle<float> r2(0.0f, 0.0f, rw*0.05f, rw * 0.3f);
        needle.addRectangle(r2.withPosition(Point<float>(r.getCentreX() - (r2.getWidth() / 2.0f), r.getY())));

        //g.setColour (slider.findColour (Slider::rotarySliderOutlineColourId));
        g.setGradientFill(ColourGradient(Colours::grey, 0, 0, Colours::black, rw, rw, true));
        //g.setColour(Colours::black);
        g.fillPath(needle, AffineTransform::rotation(angle, r.getCentreX(), r.getCentreY()));
}

