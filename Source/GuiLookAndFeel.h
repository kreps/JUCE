/*
  ==============================================================================

    GuiLookAndFeel.h
    Created: 9 Jan 2015 11:37:13am
    Author:  kristian

  ==============================================================================
*/

#ifndef GUILOOKANDFEEL_H_INCLUDED
#define GUILOOKANDFEEL_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class GuiLookAndFeel    : public LookAndFeel_V3
{
public:
    GuiLookAndFeel();
    ~GuiLookAndFeel();
    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
                                          float rotaryStartAngle, float rotaryEndAngle, Slider& slider);
    void drawTickBox(Graphics& g, Component& component,
                                     float x, float y, float w, float h,
                                     bool ticked,
                                     bool isEnabled,
                                     bool /*isMouseOverButton*/,
                                     bool /*isButtonDown*/);
    void drawToggleButton(Graphics& g, ToggleButton& button,bool isMouseOverButton, bool isButtonDown);
    void drawGroupComponentOutline(Graphics& g, int width, int height,
                                                   const String& text, const Justification& position,
                                                   GroupComponent& group);
    void setImage(Image& img);
    void GuiLookAndFeel::drawLabel(Graphics& g, Label& label);
private:
    Image img;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuiLookAndFeel)
};


#endif  // GUILOOKANDFEEL_H_INCLUDED
