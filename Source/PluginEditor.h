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
#include "GuiLookAndFeel2.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
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

    // Binary resources:
    static const char* kreps_logo_jpeg;
    static const int kreps_logo_jpegSize;
    static const char* chickknob_png;
    static const int chickknob_pngSize;
    static const char* uibg_png;
    static const int uibg_pngSize;
    static const char* off_png;
    static const int off_pngSize;
    static const char* on_orange_png;
    static const int on_orange_pngSize;
    static const char* on_red_png;
    static const int on_red_pngSize;
    static const char* on_yellow_png;
    static const int on_yellow_pngSize;
    static const char* images1_jpg;
    static const int images1_jpgSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    ScopedPointer<ResizableCornerComponent> resizer;
    ComponentBoundsConstrainer resizeLimits;
    AudioPlayHead::CurrentPositionInfo lastDisplayedPosition;

    JuceDemoPluginAudioProcessor* getProcessor() const
    {
        return static_cast <JuceDemoPluginAudioProcessor*> (getAudioProcessor());
    }

    void displayPositionInfo (const AudioPlayHead::CurrentPositionInfo& pos);

    //CustomLookAndFeel laf;
    GuiLookAndFeel guilaf;
	GuiLookAndFeel2 guilaf2;
    LookAndFeel_V1 lookAndFeelV1;
    LookAndFeel_V2 lookAndFeelV2;
    LookAndFeel_V3 lookAndFeelV3;
    TooltipWindow tooltipWindow;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> groupComponent;
    ScopedPointer<GroupComponent> reverGroupComponent;
    ScopedPointer<GroupComponent> delayGroupComponent;
    ScopedPointer<Slider> panSlider;
    ScopedPointer<Label> infoLabel;
    ScopedPointer<Slider> gainSlider;
    ScopedPointer<Slider> delaySlider;
    ScopedPointer<Label> gainInfoLabel;
    ScopedPointer<Label> panInfoLabel;
    ScopedPointer<Slider> delayTimeSlider;
    ScopedPointer<Label> delayTimeValueLabel;
    ScopedPointer<Label> panHeader;
    ScopedPointer<Slider> midSideSlider;
    ScopedPointer<Label> midsideHeader;
    ScopedPointer<Slider> saturationSlider;
    ScopedPointer<Label> distortionHeader;
    ScopedPointer<Label> hpfHeader;
    ScopedPointer<Slider> hpfSlider;
    ScopedPointer<Slider> reverbSizeSlider;
    ScopedPointer<Label> midsideInfoLabel;
    ScopedPointer<Label> reverbSizeHeader;
    ScopedPointer<Slider> delayFeedbackSlider;
    ScopedPointer<Label> delayTimeValueLabel2;
    ScopedPointer<Label> delayAmountHeader;
    ScopedPointer<TextButton> lnf3Btn;
    ScopedPointer<TextButton> guilafBtn;
    ScopedPointer<TextButton> guilaf2Btn;
    ScopedPointer<ToggleButton> dryBtn;
    ScopedPointer<Slider> slider;
    ScopedPointer<Label> reverbSizeHeader2;
    ScopedPointer<Slider> slider2;
    ScopedPointer<Label> reverbSizeHeader3;
    ScopedPointer<Slider> slider3;
    ScopedPointer<Label> reverbSizeHeader4;
    ScopedPointer<Slider> slider4;
    ScopedPointer<ToggleButton> bypassBtn;
    Image cachedImage_uibg_png;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceDemoPluginAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_C36CAE205C9D333E__
