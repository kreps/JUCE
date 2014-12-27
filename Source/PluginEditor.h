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
    static const char* offMaya_png;
    static const int offMaya_pngSize;
    static const char* onMaya_png;
    static const int onMaya_pngSize;
    static const char* downMaya_png;
    static const int downMaya_pngSize;
    static const char* mayaKnobtest_png;
    static const int mayaKnobtest_pngSize;
    static const char* untitled1_png;
    static const int untitled1_pngSize;
    static const char* vibratingsilveryspeakeranimatedgif_gif;
    static const int vibratingsilveryspeakeranimatedgif_gifSize;
    static const char* download_jpg;
    static const int download_jpgSize;


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


    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Slider> panSlider;
    ScopedPointer<Label> infoLabel;
    ScopedPointer<Slider> gainSlider;
    ScopedPointer<Slider> delaySlider;
    ScopedPointer<ToggleButton> bypassButton;
    ScopedPointer<Label> gainInfoLabel;
    ScopedPointer<Label> panInfoLabel;
    Image cachedImage_untitled1_png;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceDemoPluginAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_C36CAE205C9D333E__
