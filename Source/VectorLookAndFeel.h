/*
  ==============================================================================

    GuiLookAndFeel2.h
    Created: 10 Jan 2015 4:12:59pm
    Author:  kreps

  ==============================================================================
*/

#ifndef GUILOOKANDFEEL2_H_INCLUDED
#define GUILOOKANDFEEL2_H_INCLUDED
#include "../JuceLibraryCode/JuceHeader.h"
#include "GuiLookAndFeel.h"
//==============================================================================
class JUCE_API VectorLookAndFeel : public LookAndFeel_V2
{
public:
	 VectorLookAndFeel();
    ~VectorLookAndFeel();
    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
                                          float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override;
    void drawTickBox(Graphics& g, Component& component,
                                      float x, float y, float w, float h,
                                      const bool ticked,
                                      const bool isEnabled,
                                      const bool isMouseOverButton,
                                      const bool isButtonDown);
    void drawToggleButton(Graphics&, ToggleButton&, bool isMouseOverButton, bool isButtonDown) override;
    void drawButtonBackground(Graphics&, Button&, const Colour& backgroundColour,
                              bool isMouseOverButton, bool isButtonDown) override;
    void drawButtonText(Graphics&, TextButton&, bool isMouseOverButton, bool isButtonDown) override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VectorLookAndFeel)
};





#endif  // GUILOOKANDFEEL2_H_INCLUDED
