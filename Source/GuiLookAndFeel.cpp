/*
  ==============================================================================

    GuiLookAndFeel.cpp
    Created: 9 Jan 2015 11:37:13am
    Author:  kristian

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "GuiLookAndFeel.h"

//==============================================================================
GuiLookAndFeel::GuiLookAndFeel()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

GuiLookAndFeel::~GuiLookAndFeel()
{
}

void GuiLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
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

        g.setGradientFill(ColourGradient(Colours::white, 0, 0, Colours::black, 100, 100, true));
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
        g.setGradientFill(ColourGradient(Colours::grey, 0, 0, Colours::black, 50, 50, true));
        //g.setColour(Colours::black);
        g.fillPath(needle, AffineTransform::rotation(angle, r.getCentreX(), r.getCentreY()));
}

void GuiLookAndFeel::drawTickBox(Graphics& g, Component& component,
                 float x, float y, float w, float h,
                 bool ticked,
                 bool isEnabled,
                 bool /*isMouseOverButton*/,
                 bool /*isButtonDown*/) 
{
    const float boxSize = w * 0.7f;

    bool isDownOrDragging = component.isEnabled() && (component.isMouseOverOrDragging() || component.isMouseButtonDown());
    const Colour colour(component.findColour(TextButton::buttonOnColourId).withMultipliedSaturation((component.hasKeyboardFocus(false) || isDownOrDragging) ? 1.3f : 0.9f)
                        .withMultipliedAlpha(component.isEnabled() ? 1.0f : 0.7f));
    g.setColour(colour);

    Rectangle<float> r(x, y + (h - boxSize) * 0.5f, boxSize, boxSize);
    //g.drawRoundedRectangle(r,1.0f,0);
    //g.fillRect (r);
    g.fillRoundedRectangle(r, 3.0f);

    if (ticked)
    {
        //const Path tick (LookAndFeel_V3::getTickShape (6.0f));
        g.setColour(isEnabled ? findColour(TextButton::buttonColourId) : Colours::grey);
        g.setColour(Colours::white);
        /*const AffineTransform trans (RectanglePlacement (RectanglePlacement::centred)
        .getTransformToFit (tick.getBounds(), r.reduced (r.getHeight() * 0.05f)));*/
        //g.drawRoundedRectangle (r*0.1f,1.0f,0);
        float boxsize2 = boxSize*0.5f;
        Rectangle<float> r2(x + boxsize2 / 2.0f, y + (h - boxsize2) * 0.5f, boxsize2, boxsize2);
        g.fillRoundedRectangle(r2, 1.0f);
    }
}