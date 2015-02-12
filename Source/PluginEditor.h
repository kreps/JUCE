/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.1

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_C36CAE205C9D333E__
#define __JUCE_HEADER_C36CAE205C9D333E__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "GuiLookAndFeel.h"
#include "VectorLookAndFeel.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
                                                                    test
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class JuceDemoPluginAudioProcessorEditor  : public AudioProcessorEditor,
                                            public Timer,
                                            public SliderListener,
                                            public ButtonListener
{
public:
    //==============================================================================
    JuceDemoPluginAudioProcessorEditor (JuceDemoPluginAudioProcessor* ownerFilter);
    ~JuceDemoPluginAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void timerCallback();
	String amountToDb(float amount);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //ScopedPointer<ResizableCornerComponent> resizer;
    //ComponentBoundsConstrainer resizeLimits;
    AudioPlayHead::CurrentPositionInfo lastDisplayedPosition;

    JuceDemoPluginAudioProcessor* getProcessor() const
    {
        return static_cast <JuceDemoPluginAudioProcessor*> (getAudioProcessor());
    }

    //CustomLookAndFeel laf;
    VectorLookAndFeel vLaf;
    TooltipWindow tooltipWindow;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> label2;
    ScopedPointer<Label> labelReverb2;
    ScopedPointer<Slider> panSlider;
    ScopedPointer<Slider> delaySlider;
    ScopedPointer<Slider> delayTimeSlider;
    ScopedPointer<Label> delayTimeValueLabel;
    ScopedPointer<Label> panHeader;
    ScopedPointer<Slider> midSideSlider;
    ScopedPointer<Label> midsideHeader;
    ScopedPointer<Slider> saturationSlider;
    ScopedPointer<Label> hpfHeader;
    ScopedPointer<Slider> hpfSlider;
    ScopedPointer<Slider> reverbSizeSlider;
    ScopedPointer<Label> labelReverb;
    ScopedPointer<Label> delayAmountHeader;
    ScopedPointer<Slider> wetGainSlider;
    ScopedPointer<Label> label;
    ScopedPointer<Slider> roomDampSlider;
    ScopedPointer<Slider> lpfSlider;
    ScopedPointer<TextButton> dryOnButton;
    ScopedPointer<TextButton> wetToggleBtn;
    ScopedPointer<TextButton> panWidthDryOn;
    ScopedPointer<TextButton> filterDryBtn;
    ScopedPointer<Label> label3;
    ScopedPointer<Label> label4;
    ScopedPointer<TextButton> drySaturationOnBtn;
    ScopedPointer<Label> hpfHeader3;
    ScopedPointer<Label> delayFeedbackLabel;
    ScopedPointer<Slider> delayFeedbackSlider;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceDemoPluginAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_C36CAE205C9D333E__
