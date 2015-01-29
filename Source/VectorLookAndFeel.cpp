/*
==============================================================================

GuiLookAndFeel.cpp
Created: 9 Jan 2015 11:37:13am
Author:  kristian

==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "VectorLookAndFeel.h"

/*Gradient rotary knobs drawable*/
//==============================================================================
VectorLookAndFeel::VectorLookAndFeel()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

VectorLookAndFeel::~VectorLookAndFeel()
{}
void VectorLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
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

    if (isMouseOver)
        slider.setMouseCursor(MouseCursor::PointingHandCursor);

    g.setColour(slider.findColour(Slider::rotarySliderOutlineColourId).withAlpha(isMouseOver ? 1.0f : 0.5f));

    if (!slider.isEnabled())
        g.setColour((Colours::black).withAlpha(0.3f));

    const float lineThickness = jmin(15.0f, jmin(width, height) * 0.45f) * 0.1f;
    Path outlineArc;
    outlineArc.addEllipse(rx, ry, rw, rw);
    g.strokePath(outlineArc, PathStrokeType(lineThickness));

    float f = 1.0f + radius*0.1f;
    {
        Path filledArc2;
        filledArc2.addEllipse(rx + f, ry + f, rw - 2 * f, rw - 2 * f);
        g.setGradientFill(ColourGradient(Colours::whitesmoke, 0, 0, Colours::darkgrey,rw, rw, true));
        g.fillPath(filledArc2);
    }

    Path needle;

    Rectangle<float> r(rx + f, ry + f, rw - 2.0f*f, rw - 2 * f);
    
    Rectangle<float> r2(0.0f, 0.0f, 2.0f + f*0.25f, f*3.5f);
    needle.addRectangle(r2.withPosition(Point<float>(r.getCentreX() - (r2.getWidth() / 2.0f), r.getY())));

    g.setColour(Colour(0xff19140d));
    g.fillPath(needle, AffineTransform::rotation(angle, r.getCentreX(), r.getCentreY()));
}

//void VectorLookAndFeel::drawToggleButton(Graphics& g, ToggleButton& button,
//                                      bool isMouseOverButton, bool isButtonDown)
//{
//    const bool isMouseOver = button.isMouseOverOrDragging() && button.isEnabled();
//    if (isMouseOver)
//        button.setMouseCursor(MouseCursor::PointingHandCursor);
//
//    float fontSize = 10.0f;
//    const float tickWidth = button.getHeight()-4.0f;
//
//    VectorLookAndFeel::drawTickBox(g, button, 
//                                 0.0f, //x 
//                                 1.0f, //y
//                tickWidth*1.5f, //w 
//                tickWidth,    //h
//                button.getToggleState(),
//                button.isEnabled(),
//                isMouseOverButton,
//                isButtonDown);
//
//    g.setColour(button.findColour(ToggleButton::textColourId));
//    g.setFont(fontSize);
//
//    if (!button.isEnabled())
//        g.setOpacity(0.5f);
//
//    const int textX = (int)tickWidth + 5;
//
//    g.drawFittedText(button.getButtonText(),
//                     tickWidth*1.5f +2.0f,
//                     0,
//                     button.getWidth() - textX - 2, button.getHeight(),
//                     Justification::centredLeft, 10.0f);
//}

//void VectorLookAndFeel::drawTickBox(Graphics& g, Component& component,
//                                 float x, float y, float w, float h,
//                                 const bool ticked,
//                                 const bool isEnabled,
//                                 const bool isMouseOverButton,
//                                 const bool isButtonDown)
//{
//    float alpha = 0.4f;
//    if (ticked)
//        alpha = 1.0f;
//    Path box;
//    box.addRoundedRectangle(x, y, w, h, 2.0f, 2.0f);
//    g.setColour(component.findColour(Slider::rotarySliderFillColourId).withAlpha(alpha));
//    g.fillPath(box);
//}

void VectorLookAndFeel::drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
                                          bool isMouseOverButton, bool isButtonDown)
{
    const bool isMouseOver = button.isMouseOverOrDragging() && button.isEnabled();
    if (isMouseOver)
        button.setMouseCursor(MouseCursor::PointingHandCursor);

    const bool flatOnLeft = button.isConnectedOnLeft();
    const bool flatOnRight = button.isConnectedOnRight();
    const bool flatOnTop = button.isConnectedOnTop();
    const bool flatOnBottom = button.isConnectedOnBottom();

    const float width = static_cast<float>(button.getWidth());
    const float height = static_cast<float>(button.getHeight());

    if (width > 0 && height > 0)
    {
        const float cornerSize = 2.0f;

        Path outline;
        outline.addRoundedRectangle(0.0f, 0.0f, width, height, cornerSize, cornerSize,
                                    !(flatOnLeft || flatOnTop),
                                    !(flatOnRight || flatOnTop),
                                    !(flatOnLeft || flatOnBottom),
                                    !(flatOnRight || flatOnBottom));
        
        if (button.getToggleState())
        {
            g.setColour(button.findColour(TextButton::buttonColourId).withAlpha(0.6f));
        } else { 
            if (isMouseOver)
                g.setColour(button.findColour(TextButton::buttonColourId).withAlpha(0.15f));
            else
                g.setColour(button.findColour(TextButton::buttonColourId).withAlpha(0.1f));
        }
        
        g.fillPath(outline);
    }
}



void VectorLookAndFeel::drawButtonText(Graphics& g, TextButton& button, bool /*isMouseOverButton*/, bool /*isButtonDown*/)
{

    g.setFont(Font(10.0f));
    if (button.getToggleState())
    {
        g.setColour(button.findColour(TextButton::textColourOffId));
    } else
    {
        g.setColour(button.findColour(TextButton::textColourOnId));
    }
    g.drawFittedText(button.getButtonText(),
                     0,//leftIndent,
                     1,//yIndent,
                     button.getWidth(),// - leftIndent - rightIndent,
                     button.getHeight(),// - yIndent * 2,
                     Justification::centred, 2);
}
