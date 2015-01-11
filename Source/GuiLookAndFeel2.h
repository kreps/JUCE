/*
  ==============================================================================

    GuiLookAndFeel2.h
    Created: 10 Jan 2015 4:12:59pm
    Author:  user

  ==============================================================================
*/

#ifndef GUILOOKANDFEEL2_H_INCLUDED
#define GUILOOKANDFEEL2_H_INCLUDED
#include "../JuceLibraryCode/JuceHeader.h"
#include "GuiLookAndFeel.h"
//==============================================================================
/*
*/
class GuiLookAndFeel2    : public GuiLookAndFeel
{
public:
	 GuiLookAndFeel2();
    ~GuiLookAndFeel2();
    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
                                          float rotaryStartAngle, float rotaryEndAngle, Slider& slider);
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuiLookAndFeel2)
};





#endif  // GUILOOKANDFEEL2_H_INCLUDED
