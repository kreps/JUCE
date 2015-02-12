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

//[Headers] You can add your own extra header files here...
#include "PluginProcessor.h"
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//==============================================================================
//==============================================================================
/** Another really simple look and feel that is very flat and square.
This inherits from CustomLookAndFeel above for the linear bar and slider backgrounds.
*/

void setupCustomLookAndFeelColours (LookAndFeel& laf)
{
	//laf.setColour (Slider::thumbColourId, Colour::greyLevel (0.95f));
	laf.setColour (Slider::textBoxOutlineColourId, Colours::black);
	laf.setColour(Slider::textBoxBackgroundColourId,Colour((0x00ffb5f6)));
	laf.setColour (Slider::rotarySliderFillColourId, Colours::darkorange);
	//laf.setColour (Slider::rotarySliderOutlineColourId, Colours::white);
    laf.setColour(Slider::thumbColourId, Colours::brown);

	laf.setColour (TextButton::buttonColourId, Colours::white);
    laf.setColour(TextButton::buttonOnColourId, laf.findColour(TextButton::textColourOffId));
    //laf.setColour (TextButton::textColourOnId, laf.findColour (TextButton::buttonColourId));
	//laf.setColour (TextButton::textColourOffId, Colour (0xff00b5f6));

    laf.setColour(GroupComponent::textColourId, Colour(0xff000000));

    //laf.setColour(Label::backgroundColourId, Colour(0x33ffffff));
};

class CParamSmooth
{
public:
    CParamSmooth(float smoothingTimeInMs, float samplingRate)
    {
        const float c_twoPi = 6.283185307179586476925286766559f;

        a = exp(-c_twoPi / (smoothingTimeInMs * 0.001f * samplingRate));
        b = 1.0f - a;
        z = 0.0f;
    }

    ~CParamSmooth()
    {

    }

    inline float process(float in)
    {
        z = (in * b) + (z * a);
        return z;
    }

private:
    float a;
    float b;
    float z;
};
//[/MiscUserDefs]

//==============================================================================
JuceDemoPluginAudioProcessorEditor::JuceDemoPluginAudioProcessorEditor (JuceDemoPluginAudioProcessor* ownerFilter)
    : AudioProcessorEditor (ownerFilter)
{
    addAndMakeVisible (label2 = new Label ("new label",
                                           String::empty));
    label2->setFont (Font (15.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (Label::backgroundColourId, Colour (0x2bdeb887));
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (labelReverb2 = new Label ("new label",
                                                 TRANS("damp")));
    labelReverb2->setFont (Font ("Aharoni", 10.00f, Font::plain));
    labelReverb2->setJustificationType (Justification::centred);
    labelReverb2->setEditable (false, false, false);
    labelReverb2->setColour (Label::textColourId, Colour (0xffa8a8a8));
    labelReverb2->setColour (TextEditor::textColourId, Colours::black);
    labelReverb2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (panSlider = new Slider ("panSlider"));
    panSlider->setRange (0, 1, 0);
    panSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    panSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    panSlider->setColour (Slider::rotarySliderFillColourId, Colours::bisque);
    panSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffffff48));
    panSlider->addListener (this);

    addAndMakeVisible (delaySlider = new Slider ("delaySlider"));
    delaySlider->setTooltip (TRANS("delay gain\n"));
    delaySlider->setRange (0, 1, 0);
    delaySlider->setSliderStyle (Slider::RotaryVerticalDrag);
    delaySlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    delaySlider->setColour (Slider::trackColourId, Colours::white);
    delaySlider->setColour (Slider::rotarySliderOutlineColourId, Colours::chartreuse);
    delaySlider->setColour (Slider::textBoxHighlightColourId, Colour (0xff1111ee));
    delaySlider->setColour (Slider::textBoxOutlineColourId, Colours::grey);
    delaySlider->addListener (this);

    addAndMakeVisible (delayTimeSlider = new Slider ("delayTimeSlider"));
    delayTimeSlider->setRange (0, 1, 0);
    delayTimeSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    delayTimeSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    delayTimeSlider->setColour (Slider::rotarySliderOutlineColourId, Colours::chartreuse);
    delayTimeSlider->addListener (this);

    addAndMakeVisible (delayTimeValueLabel = new Label ("new label",
                                                        TRANS("delay")));
    delayTimeValueLabel->setFont (Font ("Aharoni", 10.00f, Font::plain));
    delayTimeValueLabel->setJustificationType (Justification::centred);
    delayTimeValueLabel->setEditable (false, false, false);
    delayTimeValueLabel->setColour (Label::textColourId, Colour (0xffababab));
    delayTimeValueLabel->setColour (TextEditor::textColourId, Colours::black);
    delayTimeValueLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (panHeader = new Label ("new label",
                                              TRANS("pan\n")));
    panHeader->setFont (Font ("Aharoni", 10.00f, Font::plain));
    panHeader->setJustificationType (Justification::centred);
    panHeader->setEditable (false, false, false);
    panHeader->setColour (Label::textColourId, Colour (0xffababab));
    panHeader->setColour (TextEditor::textColourId, Colours::black);
    panHeader->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (midSideSlider = new Slider ("mid/side slider"));
    midSideSlider->setRange (0, 1, 0.005);
    midSideSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    midSideSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    midSideSlider->setColour (Slider::rotarySliderFillColourId, Colours::blanchedalmond);
    midSideSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffffff48));
    midSideSlider->addListener (this);

    addAndMakeVisible (midsideHeader = new Label ("new label",
                                                  TRANS("width")));
    midsideHeader->setFont (Font ("Aharoni", 10.00f, Font::plain));
    midsideHeader->setJustificationType (Justification::centred);
    midsideHeader->setEditable (false, false, false);
    midsideHeader->setColour (Label::textColourId, Colour (0xffababab));
    midsideHeader->setColour (TextEditor::textColourId, Colours::black);
    midsideHeader->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (saturationSlider = new Slider ("mid/side slider"));
    saturationSlider->setRange (0.001, 1, 0);
    saturationSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    saturationSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    saturationSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff9bb0ff));
    saturationSlider->addListener (this);

    addAndMakeVisible (hpfHeader = new Label ("new label",
                                              TRANS("hpf")));
    hpfHeader->setFont (Font ("Aharoni", 10.00f, Font::plain));
    hpfHeader->setJustificationType (Justification::centred);
    hpfHeader->setEditable (false, false, false);
    hpfHeader->setColour (Label::textColourId, Colour (0xffababab));
    hpfHeader->setColour (TextEditor::textColourId, Colours::black);
    hpfHeader->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (hpfSlider = new Slider ("hpfSlider_violet"));
    hpfSlider->setTooltip (TRANS("hi pass filter (hz)"));
    hpfSlider->setRange (1e-005, 1, 0);
    hpfSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    hpfSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    hpfSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffff8af4));
    hpfSlider->setColour (Slider::textBoxTextColourId, Colour (0xffababab));
    hpfSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    hpfSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x00808080));
    hpfSlider->addListener (this);
    hpfSlider->setSkewFactor (0.5);

    addAndMakeVisible (reverbSizeSlider = new Slider ("new slider"));
    reverbSizeSlider->setRange (0, 1, 0);
    reverbSizeSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    reverbSizeSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    reverbSizeSlider->setColour (Slider::rotarySliderOutlineColourId, Colours::aqua);
    reverbSizeSlider->setColour (Slider::textBoxTextColourId, Colour (0xffababab));
    reverbSizeSlider->addListener (this);

    addAndMakeVisible (labelReverb = new Label ("new label",
                                                TRANS("reverb")));
    labelReverb->setFont (Font ("Aharoni", 10.00f, Font::plain));
    labelReverb->setJustificationType (Justification::centred);
    labelReverb->setEditable (false, false, false);
    labelReverb->setColour (Label::textColourId, Colour (0xffa8a8a8));
    labelReverb->setColour (TextEditor::textColourId, Colours::black);
    labelReverb->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (delayAmountHeader = new Label ("new label",
                                                      TRANS("amount")));
    delayAmountHeader->setFont (Font ("Aharoni", 10.00f, Font::plain));
    delayAmountHeader->setJustificationType (Justification::centred);
    delayAmountHeader->setEditable (false, false, false);
    delayAmountHeader->setColour (Label::textColourId, Colour (0xffababab));
    delayAmountHeader->setColour (TextEditor::textColourId, Colours::black);
    delayAmountHeader->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (wetGainSlider = new Slider ("gainSlider"));
    wetGainSlider->setTooltip (TRANS("gain"));
    wetGainSlider->setRange (0, 1, 0);
    wetGainSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    wetGainSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    wetGainSlider->setColour (Slider::rotarySliderOutlineColourId, Colours::coral);
    wetGainSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    wetGainSlider->setColour (Slider::textBoxHighlightColourId, Colour (0x881111ee));
    wetGainSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x00000000));
    wetGainSlider->addListener (this);
    wetGainSlider->setSkewFactor (0.3);

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("saturation")));
    label->setFont (Font ("Aharoni", 10.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (Label::textColourId, Colour (0xffb2b2b2));
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (roomDampSlider = new Slider ("new slider"));
    roomDampSlider->setRange (0, 1, 0);
    roomDampSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    roomDampSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    roomDampSlider->setColour (Slider::rotarySliderOutlineColourId, Colours::aqua);
    roomDampSlider->addListener (this);

    addAndMakeVisible (lpfSlider = new Slider ("violet"));
    lpfSlider->setTooltip (TRANS("low pass filter"));
    lpfSlider->setRange (1e-005, 1, 0);
    lpfSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    lpfSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    lpfSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffff8af4));
    lpfSlider->setColour (Slider::textBoxTextColourId, Colour (0xffababab));
    lpfSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    lpfSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x00808080));
    lpfSlider->addListener (this);
    lpfSlider->setSkewFactor (0.5);

    addAndMakeVisible (dryOnButton = new TextButton ("new button"));
    dryOnButton->setButtonText (TRANS("dry"));
    dryOnButton->addListener (this);
    dryOnButton->setColour (TextButton::buttonColourId, Colours::burlywood);
    dryOnButton->setColour (TextButton::buttonOnColourId, Colours::crimson);
    dryOnButton->setColour (TextButton::textColourOnId, Colour (0xffa8a8a8));
    dryOnButton->setColour (TextButton::textColourOffId, Colour (0xff313131));

    addAndMakeVisible (wetToggleBtn = new TextButton ("new button"));
    wetToggleBtn->setButtonText (TRANS("wet"));
    wetToggleBtn->addListener (this);
    wetToggleBtn->setColour (TextButton::buttonColourId, Colours::coral);
    wetToggleBtn->setColour (TextButton::buttonOnColourId, Colours::crimson);
    wetToggleBtn->setColour (TextButton::textColourOnId, Colour (0xffa8a8a8));
    wetToggleBtn->setColour (TextButton::textColourOffId, Colour (0xff313131));

    addAndMakeVisible (panWidthDryOn = new TextButton ("new button"));
    panWidthDryOn->setButtonText (TRANS("on"));
    panWidthDryOn->addListener (this);
    panWidthDryOn->setColour (TextButton::buttonColourId, Colour (0xffffff48));
    panWidthDryOn->setColour (TextButton::buttonOnColourId, Colours::crimson);
    panWidthDryOn->setColour (TextButton::textColourOnId, Colour (0xffa8a8a8));
    panWidthDryOn->setColour (TextButton::textColourOffId, Colour (0xff313131));

    addAndMakeVisible (filterDryBtn = new TextButton ("new button"));
    filterDryBtn->setButtonText (TRANS("on"));
    filterDryBtn->addListener (this);
    filterDryBtn->setColour (TextButton::buttonColourId, Colour (0xffff8af4));
    filterDryBtn->setColour (TextButton::buttonOnColourId, Colours::crimson);
    filterDryBtn->setColour (TextButton::textColourOnId, Colour (0xffa8a8a8));
    filterDryBtn->setColour (TextButton::textColourOffId, Colour (0xff313131));

    addAndMakeVisible (label3 = new Label ("new label",
                                           String::empty));
    label3->setFont (Font (15.00f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (Label::backgroundColourId, Colour (0x2bdeb887));
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label4 = new Label ("new label",
                                           String::empty));
    label4->setFont (Font (15.00f, Font::plain));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (Label::backgroundColourId, Colour (0x2bdeb887));
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (drySaturationOnBtn = new TextButton ("new button"));
    drySaturationOnBtn->setButtonText (TRANS("on"));
    drySaturationOnBtn->addListener (this);
    drySaturationOnBtn->setColour (TextButton::buttonColourId, Colour (0xff9bb0ff));
    drySaturationOnBtn->setColour (TextButton::buttonOnColourId, Colours::crimson);
    drySaturationOnBtn->setColour (TextButton::textColourOnId, Colour (0xffa8a8a8));
    drySaturationOnBtn->setColour (TextButton::textColourOffId, Colour (0xff313131));

    addAndMakeVisible (hpfHeader3 = new Label ("new label",
                                               TRANS("lpf")));
    hpfHeader3->setFont (Font ("Aharoni", 10.00f, Font::plain));
    hpfHeader3->setJustificationType (Justification::centred);
    hpfHeader3->setEditable (false, false, false);
    hpfHeader3->setColour (Label::textColourId, Colour (0xffababab));
    hpfHeader3->setColour (TextEditor::textColourId, Colours::black);
    hpfHeader3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (delayFeedbackLabel = new Label ("new label",
                                                       TRANS("feedback")));
    delayFeedbackLabel->setFont (Font ("Aharoni", 10.00f, Font::plain));
    delayFeedbackLabel->setJustificationType (Justification::centred);
    delayFeedbackLabel->setEditable (false, false, false);
    delayFeedbackLabel->setColour (Label::textColourId, Colour (0xffababab));
    delayFeedbackLabel->setColour (TextEditor::textColourId, Colours::black);
    delayFeedbackLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (delayFeedbackSlider = new Slider (String::empty));
    delayFeedbackSlider->setRange (0, 1, 0);
    delayFeedbackSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    delayFeedbackSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    delayFeedbackSlider->setColour (Slider::rotarySliderOutlineColourId, Colours::chartreuse);
    delayFeedbackSlider->addListener (this);


    //[UserPreSize]

    //[/UserPreSize]

    setSize (550, 200);


    //[Constructor] You can add your own custom stuff here..
	// set our component's initial size to be the last one that was stored in the filter's settings
	//setSize(ownerFilter->lastUIWidth, ownerFilter->lastUIHeight);
	startTimer(50);
	wetGainSlider->setDoubleClickReturnValue(true,0.2f);
	panSlider->setDoubleClickReturnValue(true,0.5f);
	midSideSlider->setDoubleClickReturnValue(true,0.5f);
	LookAndFeel::setDefaultLookAndFeel(&vLaf);
	setupCustomLookAndFeelColours(vLaf);
    vLaf.setDefaultSansSerifTypefaceName("Aharoni");
    /*guilaf.setImages(
		ImageCache::getFromMemory(chickknob_png,chickknob_pngSize),
		ImageCache::getFromMemory(off_png,off_pngSize),
		ImageCache::getFromMemory(on_red_png,on_red_pngSize)
		);*/
    wetToggleBtn->setClickingTogglesState(true);
    dryOnButton->setClickingTogglesState(true);
    filterDryBtn->setClickingTogglesState(true);
    panWidthDryOn->setClickingTogglesState(true);
    //[/Constructor]
}

JuceDemoPluginAudioProcessorEditor::~JuceDemoPluginAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	//deleteAllChildren ();
    //[/Destructor_pre]

    label2 = nullptr;
    labelReverb2 = nullptr;
    panSlider = nullptr;
    delaySlider = nullptr;
    delayTimeSlider = nullptr;
    delayTimeValueLabel = nullptr;
    panHeader = nullptr;
    midSideSlider = nullptr;
    midsideHeader = nullptr;
    saturationSlider = nullptr;
    hpfHeader = nullptr;
    hpfSlider = nullptr;
    reverbSizeSlider = nullptr;
    labelReverb = nullptr;
    delayAmountHeader = nullptr;
    wetGainSlider = nullptr;
    label = nullptr;
    roomDampSlider = nullptr;
    lpfSlider = nullptr;
    dryOnButton = nullptr;
    wetToggleBtn = nullptr;
    panWidthDryOn = nullptr;
    filterDryBtn = nullptr;
    label3 = nullptr;
    label4 = nullptr;
    drySaturationOnBtn = nullptr;
    hpfHeader3 = nullptr;
    delayFeedbackLabel = nullptr;
    delayFeedbackSlider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..

    //[/Destructor]
}

//==============================================================================
void JuceDemoPluginAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff19140d));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void JuceDemoPluginAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    label2->setBounds (58, 11, 39, 2);
    labelReverb2->setBounds (270, 145, 60, 15);
    panSlider->setBounds (80, 95, 60, 40);
    delaySlider->setBounds (334, 107, 60, 40);
    delayTimeSlider->setBounds (334, 43, 60, 40);
    delayTimeValueLabel->setBounds (334, 35, 60, 10);
    panHeader->setBounds (80, 85, 60, 10);
    midSideSlider->setBounds (80, 45, 60, 40);
    midsideHeader->setBounds (80, 35, 60, 10);
    saturationSlider->setBounds (210, 45, 60, 40);
    hpfHeader->setBounds (145, 35, 30, 10);
    hpfSlider->setBounds (145, 45, 60, 40);
    reverbSizeSlider->setBounds (270, 45, 60, 40);
    labelReverb->setBounds (270, 35, 60, 10);
    delayAmountHeader->setBounds (334, 99, 60, 10);
    wetGainSlider->setBounds (10, 55, 70, 70);
    label->setBounds (210, 35, 60, 10);
    roomDampSlider->setBounds (270, 95, 60, 40);
    lpfSlider->setBounds (143, 101, 60, 40);
    dryOnButton->setBounds (35, 6, 20, 12);
    wetToggleBtn->setBounds (35, 32, 20, 12);
    panWidthDryOn->setBounds (100, 6, 20, 12);
    filterDryBtn->setBounds (165, 6, 20, 12);
    label3->setBounds (128, 11, 34, 2);
    label4->setBounds (188, 11, 33, 2);
    drySaturationOnBtn->setBounds (229, 6, 20, 12);
    hpfHeader3->setBounds (143, 91, 30, 10);
    delayFeedbackLabel->setBounds (406, 42, 60, 10);
    delayFeedbackSlider->setBounds (406, 50, 60, 40);
    //[UserResized] Add your own custom resize handling here..
	//resizer->setBounds(getWidth() - 16, getHeight() - 16, 16, 16);

	getProcessor()->lastUIWidth = getWidth();
	getProcessor()->lastUIHeight = getHeight();
    //[/UserResized]
}

void JuceDemoPluginAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == panSlider)
    {
        //[UserSliderCode_panSlider] -- add your slider handling code here..
		getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::PAN,                                                  (float)panSlider->getValue());
        //[/UserSliderCode_panSlider]
    }
    else if (sliderThatWasMoved == delaySlider)
    {
        //[UserSliderCode_delaySlider] -- add your slider handling code here..
		getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::DELAYAMOUNT,                                                  (float)delaySlider->getValue());
        //[/UserSliderCode_delaySlider]
    }
    else if (sliderThatWasMoved == delayTimeSlider)
    {
        //[UserSliderCode_delayTimeSlider] -- add your slider handling code here..
		getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::DELAYTIME, (float)delayTimeSlider->getValue());
        //[/UserSliderCode_delayTimeSlider]
    }
    else if (sliderThatWasMoved == midSideSlider)
    {
        //[UserSliderCode_midSideSlider] -- add your slider handling code here..
		getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::WIDTH,                                                  (float)midSideSlider->getValue());
        //[/UserSliderCode_midSideSlider]
    }
    else if (sliderThatWasMoved == saturationSlider)
    {
        //[UserSliderCode_saturationSlider] -- add your slider handling code here..
		getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::SATURATION,                                                  (float)saturationSlider->getValue());
        //[/UserSliderCode_saturationSlider]
    }
    else if (sliderThatWasMoved == hpfSlider)
    {
        //[UserSliderCode_hpfSlider] -- add your slider handling code here..
        double lpfFreq = lpfSlider->getValue();
        double hpfFreq = hpfSlider->getValue();
        if (hpfFreq > lpfFreq)
        {
            lpfSlider->setValue(hpfFreq);
            getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::LPFFREQ, (float)lpfFreq);
        }
		getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::HPFFREQ,			(float)hpfSlider->getValue());
        //[/UserSliderCode_hpfSlider]
    }
    else if (sliderThatWasMoved == reverbSizeSlider)
    {
        //[UserSliderCode_reverbSizeSlider] -- add your slider handling code here..
		getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::ROOMSIZE,			(float)reverbSizeSlider->getValue());
        //[/UserSliderCode_reverbSizeSlider]
    }
    else if (sliderThatWasMoved == wetGainSlider)
    {
        //[UserSliderCode_wetGainSlider] -- add your slider handling code here..
        getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::WETAMOUNT, (float)wetGainSlider->getValue());
        //[/UserSliderCode_wetGainSlider]
    }
    else if (sliderThatWasMoved == roomDampSlider)
    {
        //[UserSliderCode_roomDampSlider] -- add your slider handling code here..
		getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::ROOMDAMP, (float)roomDampSlider->getValue());
        //[/UserSliderCode_roomDampSlider]
    }
    else if (sliderThatWasMoved == lpfSlider)
    {
        //[UserSliderCode_lpfSlider] -- add your slider handling code here..
        double lpfFreq = lpfSlider->getValue();
        double hpfFreq = hpfSlider->getValue();
        if (lpfFreq < hpfFreq)
        {
            hpfSlider->setValue(lpfFreq);
            getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::HPFFREQ, (float)hpfFreq);
        }
        getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::LPFFREQ, (float)lpfFreq);

        //[/UserSliderCode_lpfSlider]
    }
    else if (sliderThatWasMoved == delayFeedbackSlider)
    {
        //[UserSliderCode_delayFeedbackSlider] -- add your slider handling code here..
        getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::DELAYFEEDBACK, (float)delayFeedbackSlider->getValue());
        //[/UserSliderCode_delayFeedbackSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void JuceDemoPluginAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == dryOnButton)
    {
        //[UserButtonCode_dryOnButton] -- add your button handler code here..
        getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::DRYON, (dryOnButton->getToggleState() == true) ? 1.0f : 0.0f);
        //[/UserButtonCode_dryOnButton]
    }
    else if (buttonThatWasClicked == wetToggleBtn)
    {
        //[UserButtonCode_wetToggleBtn] -- add your button handler code here..
        getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::WETON, (wetToggleBtn->getToggleState() == true) ? 1.0f : 0.0f);
        if (!wetToggleBtn->getToggleState())
        {
            wetGainSlider->setEnabled(false);
        } else
        {
            wetGainSlider->setEnabled(true);
        }
        //[/UserButtonCode_wetToggleBtn]
    }
    else if (buttonThatWasClicked == panWidthDryOn)
    {
        //[UserButtonCode_panWidthDryOn] -- add your button handler code here..
        //[/UserButtonCode_panWidthDryOn]
    }
    else if (buttonThatWasClicked == filterDryBtn)
    {
        //[UserButtonCode_filterDryBtn] -- add your button handler code here..
        //[/UserButtonCode_filterDryBtn]
    }
    else if (buttonThatWasClicked == drySaturationOnBtn)
    {
        //[UserButtonCode_drySaturationOnBtn] -- add your button handler code here..
        //[/UserButtonCode_drySaturationOnBtn]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...


// This timer periodically checks whether any of the filter's parameters have changed...
void JuceDemoPluginAudioProcessorEditor::timerCallback()
{
	JuceDemoPluginAudioProcessor* ourProcessor = getProcessor();
	wetGainSlider->setValue(ourProcessor->wetGain,dontSendNotification);
    dryOnButton->setToggleState(ourProcessor->dryOn == 1.0f, dontSendNotification);
    wetToggleBtn->setToggleState(ourProcessor->wetOn == 1.0f, dontSendNotification);
	delaySlider->setValue(ourProcessor->delayAmount, dontSendNotification);
	delayTimeSlider->setValue(ourProcessor->delayTime, dontSendNotification);
    delayFeedbackSlider->setValue(ourProcessor->delayFeedbackAmount, dontSendNotification);
	panSlider->setValue(ourProcessor->pan, dontSendNotification);
	midSideSlider->setValue(ourProcessor->midSide, dontSendNotification);
	reverbSizeSlider->setValue(ourProcessor->roomSize, dontSendNotification);
	roomDampSlider->setValue(ourProcessor->roomDamp, dontSendNotification);
    hpfSlider->setValue(ourProcessor->hpfFreq,dontSendNotification);
    saturationSlider->setValue(ourProcessor->saturationAmount,dontSendNotification);
    lpfSlider->setValue(ourProcessor->lpfFreqValue,dontSendNotification);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="JuceDemoPluginAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams="JuceDemoPluginAudioProcessor* ownerFilter"
                 variableInitialisers="AudioProcessorEditor (ownerFilter)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="1"
                 initialWidth="550" initialHeight="200">
  <BACKGROUND backgroundColour="ff19140d"/>
  <LABEL name="new label" id="2161a83913cf5043" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="58 11 39 2" bkgCol="2bdeb887" edTextCol="ff000000"
         edBkgCol="0" labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="3c6e767fb7f8dbd7" memberName="labelReverb2"
         virtualName="" explicitFocusOrder="0" pos="270 145 60 15" textCol="ffa8a8a8"
         edTextCol="ff000000" edBkgCol="0" labelText="damp" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="panSlider" id="324eec4d274919f3" memberName="panSlider"
          virtualName="" explicitFocusOrder="0" pos="80 95 60 40" rotarysliderfill="ffffe4c4"
          rotaryslideroutline="ffffff48" min="0" max="1" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="delaySlider" id="37878e5e9fd60a08" memberName="delaySlider"
          virtualName="" explicitFocusOrder="0" pos="334 107 60 40" tooltip="delay gain&#10;"
          trackcol="ffffffff" rotaryslideroutline="ff7fff00" textboxhighlight="ff1111ee"
          textboxoutline="ff808080" min="0" max="1" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="delayTimeSlider" id="ead45d255e5f5831" memberName="delayTimeSlider"
          virtualName="" explicitFocusOrder="0" pos="334 43 60 40" rotaryslideroutline="ff7fff00"
          min="0" max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="3b34631ac55e0fe6" memberName="delayTimeValueLabel"
         virtualName="" explicitFocusOrder="0" pos="334 35 60 10" textCol="ffababab"
         edTextCol="ff000000" edBkgCol="0" labelText="delay" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="ec32effd76232b82" memberName="panHeader"
         virtualName="" explicitFocusOrder="0" pos="80 85 60 10" textCol="ffababab"
         edTextCol="ff000000" edBkgCol="0" labelText="pan&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="mid/side slider" id="84706171dc5b90dd" memberName="midSideSlider"
          virtualName="" explicitFocusOrder="0" pos="80 45 60 40" rotarysliderfill="ffffebcd"
          rotaryslideroutline="ffffff48" min="0" max="1" int="0.0050000000000000001"
          style="RotaryVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="fcf994bed06bf6ab" memberName="midsideHeader"
         virtualName="" explicitFocusOrder="0" pos="80 35 60 10" textCol="ffababab"
         edTextCol="ff000000" edBkgCol="0" labelText="width" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="mid/side slider" id="2a577f0fc0372cc6" memberName="saturationSlider"
          virtualName="" explicitFocusOrder="0" pos="210 45 60 40" rotaryslideroutline="ff9bb0ff"
          min="0.001" max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="f53c45ed3e69f449" memberName="hpfHeader"
         virtualName="" explicitFocusOrder="0" pos="145 35 30 10" textCol="ffababab"
         edTextCol="ff000000" edBkgCol="0" labelText="hpf" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="hpfSlider_violet" id="253b421224cbac37" memberName="hpfSlider"
          virtualName="" explicitFocusOrder="0" pos="145 45 60 40" tooltip="hi pass filter (hz)"
          rotaryslideroutline="ffff8af4" textboxtext="ffababab" textboxbkgd="ffffff"
          textboxoutline="808080" min="1.0000000000000004e-005" max="1"
          int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="new slider" id="81b8a5f3e2f90d2e" memberName="reverbSizeSlider"
          virtualName="" explicitFocusOrder="0" pos="270 45 60 40" rotaryslideroutline="ff00ffff"
          textboxtext="ffababab" min="0" max="1" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="9e5a6f98ed1157ee" memberName="labelReverb"
         virtualName="" explicitFocusOrder="0" pos="270 35 60 10" textCol="ffa8a8a8"
         edTextCol="ff000000" edBkgCol="0" labelText="reverb" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="17713b10facdb0a1" memberName="delayAmountHeader"
         virtualName="" explicitFocusOrder="0" pos="334 99 60 10" textCol="ffababab"
         edTextCol="ff000000" edBkgCol="0" labelText="amount" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="gainSlider" id="c31acc4ca22491a9" memberName="wetGainSlider"
          virtualName="" explicitFocusOrder="0" pos="10 55 70 70" tooltip="gain"
          rotaryslideroutline="ffff7f50" textboxbkgd="ffffff" textboxhighlight="881111ee"
          textboxoutline="0" min="0" max="1" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="0.29999999999999999"/>
  <LABEL name="new label" id="dce9f23eacc8bf8e" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="210 35 60 10" textCol="ffb2b2b2"
         edTextCol="ff000000" edBkgCol="0" labelText="saturation" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="c7507ca4c1878f93" memberName="roomDampSlider"
          virtualName="" explicitFocusOrder="0" pos="270 95 60 40" rotaryslideroutline="ff00ffff"
          min="0" max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="violet" id="7a4da3da58b2809f" memberName="lpfSlider" virtualName="Slider"
          explicitFocusOrder="0" pos="143 101 60 40" tooltip="low pass filter"
          rotaryslideroutline="ffff8af4" textboxtext="ffababab" textboxbkgd="ffffff"
          textboxoutline="808080" min="1.0000000000000004e-005" max="1"
          int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="0.5"/>
  <TEXTBUTTON name="new button" id="1e4e33d2149de345" memberName="dryOnButton"
              virtualName="" explicitFocusOrder="0" pos="35 6 20 12" bgColOff="ffdeb887"
              bgColOn="ffdc143c" textCol="ffa8a8a8" textColOn="ff313131" buttonText="dry"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="55e598d305767f9a" memberName="wetToggleBtn"
              virtualName="" explicitFocusOrder="0" pos="35 32 20 12" bgColOff="ffff7f50"
              bgColOn="ffdc143c" textCol="ffa8a8a8" textColOn="ff313131" buttonText="wet"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="a037e3f47054fb7b" memberName="panWidthDryOn"
              virtualName="" explicitFocusOrder="0" pos="100 6 20 12" bgColOff="ffffff48"
              bgColOn="ffdc143c" textCol="ffa8a8a8" textColOn="ff313131" buttonText="on"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="64eb3c75a3f9dba5" memberName="filterDryBtn"
              virtualName="" explicitFocusOrder="0" pos="165 6 20 12" bgColOff="ffff8af4"
              bgColOn="ffdc143c" textCol="ffa8a8a8" textColOn="ff313131" buttonText="on"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="6ab6ec97bcc368f1" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="128 11 34 2" bkgCol="2bdeb887" edTextCol="ff000000"
         edBkgCol="0" labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="657efacf973d7685" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="188 11 33 2" bkgCol="2bdeb887" edTextCol="ff000000"
         edBkgCol="0" labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="new button" id="f157b894b9e3b918" memberName="drySaturationOnBtn"
              virtualName="" explicitFocusOrder="0" pos="229 6 20 12" bgColOff="ff9bb0ff"
              bgColOn="ffdc143c" textCol="ffa8a8a8" textColOn="ff313131" buttonText="on"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="3c0b2bafd9f39a71" memberName="hpfHeader3"
         virtualName="" explicitFocusOrder="0" pos="143 91 30 10" textCol="ffababab"
         edTextCol="ff000000" edBkgCol="0" labelText="lpf" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="3510560481fbb71f" memberName="delayFeedbackLabel"
         virtualName="" explicitFocusOrder="0" pos="406 42 60 10" textCol="ffababab"
         edTextCol="ff000000" edBkgCol="0" labelText="feedback" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="" id="d66a3c141b50ff4f" memberName="delayFeedbackSlider"
          virtualName="" explicitFocusOrder="0" pos="406 50 60 40" rotaryslideroutline="ff7fff00"
          min="0" max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
