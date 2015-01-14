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
	laf.setColour (Slider::thumbColourId, Colour::greyLevel (0.95f));
	laf.setColour (Slider::textBoxOutlineColourId, Colours::black);
	laf.setColour(Slider::textBoxBackgroundColourId,Colour((0x00ffb5f6)));
	laf.setColour (Slider::rotarySliderFillColourId, Colour (0xff00b5f6));
	laf.setColour (Slider::rotarySliderOutlineColourId, Colours::white);

	laf.setColour (TextButton::buttonColourId, Colours::white);
	laf.setColour (TextButton::textColourOffId, Colour (0xff00b5f6));
    laf.setColour(GroupComponent::textColourId, Colour(0xff000000));
	laf.setColour (TextButton::buttonOnColourId, laf.findColour (TextButton::textColourOffId));
	laf.setColour (TextButton::textColourOnId, laf.findColour (TextButton::buttonColourId));
	//laf.setColour(Label::backgroundColourId, Colour(0x33ffffff));
};

//[/MiscUserDefs]

//==============================================================================
JuceDemoPluginAudioProcessorEditor::JuceDemoPluginAudioProcessorEditor (JuceDemoPluginAudioProcessor* ownerFilter)
    : AudioProcessorEditor (ownerFilter)
{
    addAndMakeVisible (panSlider = new Slider ("panSlider"));
    panSlider->setRange (0, 1, 0);
    panSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    panSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    panSlider->addListener (this);

    addAndMakeVisible (infoLabel = new Label (String::empty,
                                              TRANS("aaa")));
    infoLabel->setFont (Font ("Aharoni", 12.00f, Font::plain));
    infoLabel->setJustificationType (Justification::centredLeft);
    infoLabel->setEditable (false, false, false);
    infoLabel->setColour (Label::textColourId, Colour (0xff414141));
    infoLabel->setColour (TextEditor::textColourId, Colours::black);
    infoLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (delaySlider = new Slider ("delaySlider"));
    delaySlider->setTooltip (TRANS("delay gain\n"));
    delaySlider->setRange (0, 1, 0);
    delaySlider->setSliderStyle (Slider::RotaryVerticalDrag);
    delaySlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    delaySlider->setColour (Slider::trackColourId, Colours::white);
    delaySlider->setColour (Slider::textBoxHighlightColourId, Colour (0xff1111ee));
    delaySlider->setColour (Slider::textBoxOutlineColourId, Colours::grey);
    delaySlider->addListener (this);

    addAndMakeVisible (gainInfoLabel = new Label ("gainInfoLabel",
                                                  TRANS("0.0 dB\n")));
    gainInfoLabel->setFont (Font ("Aharoni", 12.00f, Font::plain));
    gainInfoLabel->setJustificationType (Justification::centred);
    gainInfoLabel->setEditable (false, false, false);
    gainInfoLabel->setColour (Label::textColourId, Colour (0xff323232));
    gainInfoLabel->setColour (TextEditor::textColourId, Colours::black);
    gainInfoLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (panInfoLabel = new Label ("new label",
                                                 TRANS("C")));
    panInfoLabel->setFont (Font ("Aharoni", 10.00f, Font::plain));
    panInfoLabel->setJustificationType (Justification::centred);
    panInfoLabel->setEditable (false, false, false);
    panInfoLabel->setColour (Label::textColourId, Colour (0xff282828));
    panInfoLabel->setColour (TextEditor::textColourId, Colours::black);
    panInfoLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (delayTimeSlider = new Slider ("delayTimeSlider"));
    delayTimeSlider->setRange (0, 1, 0);
    delayTimeSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    delayTimeSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    delayTimeSlider->addListener (this);

    addAndMakeVisible (delayTimeValueLabel = new Label ("new label",
                                                        TRANS("time")));
    delayTimeValueLabel->setFont (Font ("Aharoni", 10.00f, Font::plain));
    delayTimeValueLabel->setJustificationType (Justification::centred);
    delayTimeValueLabel->setEditable (false, false, false);
    delayTimeValueLabel->setColour (Label::textColourId, Colour (0xff282828));
    delayTimeValueLabel->setColour (TextEditor::textColourId, Colours::black);
    delayTimeValueLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (panHeader = new Label ("new label",
                                              TRANS("pan\n")));
    panHeader->setFont (Font ("Aharoni", 10.00f, Font::plain));
    panHeader->setJustificationType (Justification::centred);
    panHeader->setEditable (false, false, false);
    panHeader->setColour (Label::textColourId, Colour (0xff363636));
    panHeader->setColour (TextEditor::textColourId, Colours::black);
    panHeader->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (midSideSlider = new Slider ("mid/side slider"));
    midSideSlider->setRange (0, 1, 0.005);
    midSideSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    midSideSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    midSideSlider->addListener (this);

    addAndMakeVisible (midsideHeader = new Label ("new label",
                                                  TRANS("mid/side")));
    midsideHeader->setFont (Font ("Aharoni", 10.00f, Font::plain));
    midsideHeader->setJustificationType (Justification::centred);
    midsideHeader->setEditable (false, false, false);
    midsideHeader->setColour (Label::textColourId, Colour (0xff363636));
    midsideHeader->setColour (TextEditor::textColourId, Colours::black);
    midsideHeader->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (saturationSlider = new Slider ("mid/side slider"));
    saturationSlider->setRange (0.001, 1, 0);
    saturationSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    saturationSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    saturationSlider->addListener (this);

    addAndMakeVisible (distortionHeader = new Label ("saturation fx",
                                                     TRANS("saturation")));
    distortionHeader->setFont (Font ("Aharoni", 10.00f, Font::plain));
    distortionHeader->setJustificationType (Justification::centredTop);
    distortionHeader->setEditable (false, false, false);
    distortionHeader->setColour (Label::textColourId, Colour (0xff363636));
    distortionHeader->setColour (TextEditor::textColourId, Colours::black);
    distortionHeader->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (hpfHeader = new Label ("new label",
                                              TRANS("hi pass filter")));
    hpfHeader->setFont (Font ("Aharoni", 10.00f, Font::plain));
    hpfHeader->setJustificationType (Justification::centred);
    hpfHeader->setEditable (false, false, false);
    hpfHeader->setColour (Label::textColourId, Colour (0xff363636));
    hpfHeader->setColour (TextEditor::textColourId, Colours::black);
    hpfHeader->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (hpfSlider = new Slider ("hpfSlider"));
    hpfSlider->setTooltip (TRANS("hi pass filter (hz)"));
    hpfSlider->setRange (20, 10000, 0);
    hpfSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    hpfSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    hpfSlider->addListener (this);
    hpfSlider->setSkewFactor (0.2);

    addAndMakeVisible (reverbSizeSlider = new Slider ("new slider"));
    reverbSizeSlider->setRange (0.01, 1, 0);
    reverbSizeSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    reverbSizeSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    reverbSizeSlider->addListener (this);

    addAndMakeVisible (midsideInfoLabel = new Label ("new label",
                                                     TRANS("80%")));
    midsideInfoLabel->setFont (Font ("Aharoni", 15.00f, Font::plain));
    midsideInfoLabel->setJustificationType (Justification::centred);
    midsideInfoLabel->setEditable (false, false, false);
    midsideInfoLabel->setColour (Label::textColourId, Colour (0xff363636));
    midsideInfoLabel->setColour (TextEditor::textColourId, Colours::black);
    midsideInfoLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (reverbSizeHeader = new Label ("new label",
                                                     TRANS("room size")));
    reverbSizeHeader->setFont (Font ("Aharoni", 10.00f, Font::plain));
    reverbSizeHeader->setJustificationType (Justification::centred);
    reverbSizeHeader->setEditable (false, false, false);
    reverbSizeHeader->setColour (Label::textColourId, Colour (0xff363636));
    reverbSizeHeader->setColour (TextEditor::textColourId, Colours::black);
    reverbSizeHeader->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (delayFeedbackSlider = new Slider ("dfs_violet"));
    delayFeedbackSlider->setRange (0, 1, 0);
    delayFeedbackSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    delayFeedbackSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    delayFeedbackSlider->addListener (this);

    addAndMakeVisible (delayTimeValueLabel2 = new Label ("new label",
                                                         TRANS("feedback")));
    delayTimeValueLabel2->setFont (Font ("Aharoni", 10.00f, Font::plain));
    delayTimeValueLabel2->setJustificationType (Justification::centred);
    delayTimeValueLabel2->setEditable (false, false, false);
    delayTimeValueLabel2->setColour (Label::textColourId, Colour (0xff282828));
    delayTimeValueLabel2->setColour (TextEditor::textColourId, Colours::black);
    delayTimeValueLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (delayAmountHeader = new Label ("new label",
                                                      TRANS("amount")));
    delayAmountHeader->setFont (Font ("Aharoni", 10.00f, Font::plain));
    delayAmountHeader->setJustificationType (Justification::centred);
    delayAmountHeader->setEditable (false, false, false);
    delayAmountHeader->setColour (TextEditor::textColourId, Colours::black);
    delayAmountHeader->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lnf3Btn = new TextButton ("new button"));
    lnf3Btn->setButtonText (TRANS("lfv3"));
    lnf3Btn->addListener (this);

    addAndMakeVisible (guilafBtn = new TextButton ("new button"));
    guilafBtn->setButtonText (TRANS("guilaf"));
    guilafBtn->addListener (this);

    addAndMakeVisible (guilaf2Btn = new TextButton ("new button"));
    guilaf2Btn->setButtonText (TRANS("guilaf2"));
    guilaf2Btn->addListener (this);

    addAndMakeVisible (dryBtn = new ToggleButton ("new toggle button"));
    dryBtn->setButtonText (TRANS("dry +"));
    dryBtn->addListener (this);
    dryBtn->setToggleState (true, dontSendNotification);

    addAndMakeVisible (slider = new Slider ("new slider"));
    slider->setRange (0, 10, 0);
    slider->setSliderStyle (Slider::RotaryVerticalDrag);
    slider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    slider->addListener (this);

    addAndMakeVisible (reverbSizeHeader2 = new Label ("new label",
                                                      TRANS("damp todo")));
    reverbSizeHeader2->setFont (Font ("Aharoni", 10.00f, Font::plain));
    reverbSizeHeader2->setJustificationType (Justification::centred);
    reverbSizeHeader2->setEditable (false, false, false);
    reverbSizeHeader2->setColour (Label::textColourId, Colour (0xff363636));
    reverbSizeHeader2->setColour (TextEditor::textColourId, Colours::black);
    reverbSizeHeader2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (slider2 = new Slider ("new slider"));
    slider2->setRange (0, 10, 0);
    slider2->setSliderStyle (Slider::RotaryVerticalDrag);
    slider2->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    slider2->addListener (this);

    addAndMakeVisible (reverbSizeHeader3 = new Label ("new label",
                                                      TRANS("freeze todo")));
    reverbSizeHeader3->setFont (Font ("Aharoni", 10.00f, Font::plain));
    reverbSizeHeader3->setJustificationType (Justification::centred);
    reverbSizeHeader3->setEditable (false, false, false);
    reverbSizeHeader3->setColour (Label::textColourId, Colour (0xff363636));
    reverbSizeHeader3->setColour (TextEditor::textColourId, Colours::black);
    reverbSizeHeader3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (slider3 = new Slider ("new slider"));
    slider3->setRange (0, 10, 0);
    slider3->setSliderStyle (Slider::RotaryVerticalDrag);
    slider3->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    slider3->addListener (this);

    addAndMakeVisible (reverbSizeHeader4 = new Label ("new label",
                                                      TRANS("width todo")));
    reverbSizeHeader4->setFont (Font ("Aharoni", 10.00f, Font::plain));
    reverbSizeHeader4->setJustificationType (Justification::centred);
    reverbSizeHeader4->setEditable (false, false, false);
    reverbSizeHeader4->setColour (Label::textColourId, Colour (0xff363636));
    reverbSizeHeader4->setColour (TextEditor::textColourId, Colours::black);
    reverbSizeHeader4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (bypassBtn = new ToggleButton ("new toggle button"));
    bypassBtn->setButtonText (String::empty);
    bypassBtn->addListener (this);

    addAndMakeVisible (dryOnBtn = new ImageButton ("new button"));
    dryOnBtn->addListener (this);

    dryOnBtn->setImages (false, true, true,
                         ImageCache::getFromMemory (dry_off_png, dry_off_pngSize), 1.000f, Colour (0x00000000),
                         Image(), 1.000f, Colour (0x00000000),
                         ImageCache::getFromMemory (dry_on_png, dry_on_pngSize), 1.000f, Colour (0x00000000));
    addAndMakeVisible (wetOnBtn = new ImageButton ("new button"));
    wetOnBtn->addListener (this);

    wetOnBtn->setImages (false, true, true,
                         ImageCache::getFromMemory (wet_off_png, wet_off_pngSize), 1.000f, Colour (0x00000000),
                         Image(), 1.000f, Colour (0x00000000),
                         ImageCache::getFromMemory (wet_on_png, wet_on_pngSize), 1.000f, Colour (0x00000000));
    addAndMakeVisible (gainSlider = new Slider ("gainSlider"));
    gainSlider->setTooltip (TRANS("gain"));
    gainSlider->setRange (0, 1, 0);
    gainSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    gainSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    gainSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    gainSlider->setColour (Slider::textBoxHighlightColourId, Colour (0x881111ee));
    gainSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x00000000));
    gainSlider->addListener (this);
    gainSlider->setSkewFactor (0.3);

    cachedImage_uibg_png = ImageCache::getFromMemory (uibg_png, uibg_pngSize);

    //[UserPreSize]
	addAndMakeVisible(resizer = new ResizableCornerComponent(this, &resizeLimits));
	resizeLimits.setSizeLimits(150, 150, 800, 300);
    //[/UserPreSize]

    setSize (800, 400);


    //[Constructor] You can add your own custom stuff here..
	// set our component's initial size to be the last one that was stored in the filter's settings
	setSize(ownerFilter->lastUIWidth, ownerFilter->lastUIHeight);
	startTimer(50);
	gainSlider->setDoubleClickReturnValue(true,0.0f);
	panSlider->setDoubleClickReturnValue(true,0.5f);
	midSideSlider->setDoubleClickReturnValue(true,0.5f);
	LookAndFeel::setDefaultLookAndFeel(&guilaf);
	setupCustomLookAndFeelColours(guilaf);
    guilaf.setDefaultSansSerifTypefaceName("Aharoni");
    guilaf.setImages(
		ImageCache::getFromMemory(chickknob_png,chickknob_pngSize),
		ImageCache::getFromMemory(off_png,off_pngSize),
		ImageCache::getFromMemory(on_red_png,on_red_pngSize)
		);
	 guilaf2.setImages(
		ImageCache::getFromMemory(chickknob_png,chickknob_pngSize),
		ImageCache::getFromMemory(off_png,off_pngSize),
		ImageCache::getFromMemory(on_red_png,on_red_pngSize)
		);
	 //gainSlider->setScrollWheelEnabled(false);
	 bypassBtn->setClickingTogglesState(true);
     dryOnBtn->setClickingTogglesState(true);
     wetOnBtn->setClickingTogglesState(true);
     wetOnBtn->setToggleState(true,dontSendNotification);
     dryOnBtn->setToggleState(true, dontSendNotification);
    //[/Constructor]
}

JuceDemoPluginAudioProcessorEditor::~JuceDemoPluginAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	//deleteAllChildren ();
    //[/Destructor_pre]

    panSlider = nullptr;
    infoLabel = nullptr;
    delaySlider = nullptr;
    gainInfoLabel = nullptr;
    panInfoLabel = nullptr;
    delayTimeSlider = nullptr;
    delayTimeValueLabel = nullptr;
    panHeader = nullptr;
    midSideSlider = nullptr;
    midsideHeader = nullptr;
    saturationSlider = nullptr;
    distortionHeader = nullptr;
    hpfHeader = nullptr;
    hpfSlider = nullptr;
    reverbSizeSlider = nullptr;
    midsideInfoLabel = nullptr;
    reverbSizeHeader = nullptr;
    delayFeedbackSlider = nullptr;
    delayTimeValueLabel2 = nullptr;
    delayAmountHeader = nullptr;
    lnf3Btn = nullptr;
    guilafBtn = nullptr;
    guilaf2Btn = nullptr;
    dryBtn = nullptr;
    slider = nullptr;
    reverbSizeHeader2 = nullptr;
    slider2 = nullptr;
    reverbSizeHeader3 = nullptr;
    slider3 = nullptr;
    reverbSizeHeader4 = nullptr;
    bypassBtn = nullptr;
    dryOnBtn = nullptr;
    wetOnBtn = nullptr;
    gainSlider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..

    //[/Destructor]
}

//==============================================================================
void JuceDemoPluginAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff777777));

    g.setColour (Colours::black);
    g.drawImageWithin (cachedImage_uibg_png,
                       0, 0, 400, 230,
                       RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize,
                       false);

    g.setColour (Colour (0xff32a52a));
    g.fillRect (0, 0, 1, 1);

    //[UserPaint] Add your own custom painting code here..

    //[/UserPaint]
}

void JuceDemoPluginAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    panSlider->setBounds (100, 159, 80, 50);
    infoLabel->setBounds (40, 432, 400, 25);
    delaySlider->setBounds (208, 47, 80, 50);
    gainInfoLabel->setBounds (56, 88, 80, 20);
    panInfoLabel->setBounds (100, 209, 80, 20);
    delayTimeSlider->setBounds (288, 47, 80, 50);
    delayTimeValueLabel->setBounds (288, 27, 80, 20);
    panHeader->setBounds (100, 139, 80, 20);
    midSideSlider->setBounds (28, 170, 80, 50);
    midsideHeader->setBounds (18, 150, 80, 20);
    saturationSlider->setBounds (144, 253, 100, 50);
    distortionHeader->setBounds (156, 240, 80, 10);
    hpfHeader->setBounds (258, 150, 80, 30);
    hpfSlider->setBounds (268, 170, 60, 50);
    reverbSizeSlider->setBounds (472, 48, 50, 50);
    midsideInfoLabel->setBounds (18, 225, 80, 30);
    reverbSizeHeader->setBounds (456, 24, 80, 30);
    delayFeedbackSlider->setBounds (368, 47, 80, 50);
    delayTimeValueLabel2->setBounds (368, 27, 80, 20);
    delayAmountHeader->setBounds (208, 24, 80, 24);
    lnf3Btn->setBounds (216, 384, 88, 24);
    guilafBtn->setBounds (320, 384, 88, 24);
    guilaf2Btn->setBounds (432, 384, 88, 24);
    dryBtn->setBounds (24, 304, 70, 24);
    slider->setBounds (472, 96, 50, 50);
    reverbSizeHeader2->setBounds (520, 24, 80, 30);
    slider2->setBounds (472, 144, 50, 50);
    reverbSizeHeader3->setBounds (600, 24, 80, 30);
    slider3->setBounds (472, 192, 50, 50);
    reverbSizeHeader4->setBounds (680, 24, 80, 30);
    bypassBtn->setBounds (24, 272, 50, 20);
    dryOnBtn->setBounds (7, 9, 35, 13);
    wetOnBtn->setBounds (7, 27, 22, 23);
    gainSlider->setBounds (18, 19, 70, 50);
    //[UserResized] Add your own custom resize handling here..
	resizer->setBounds(getWidth() - 16, getHeight() - 16, 16, 16);

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
		getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::panParam,                                                  (float)panSlider->getValue());
        //[/UserSliderCode_panSlider]
    }
    else if (sliderThatWasMoved == delaySlider)
    {
        //[UserSliderCode_delaySlider] -- add your slider handling code here..
		getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::delayParam,                                                  (float)delaySlider->getValue());
        //[/UserSliderCode_delaySlider]
    }
    else if (sliderThatWasMoved == delayTimeSlider)
    {
        //[UserSliderCode_delayTimeSlider] -- add your slider handling code here..
		getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::delayTimeParam,			(float)delayTimeSlider->getValue());
        //[/UserSliderCode_delayTimeSlider]
    }
    else if (sliderThatWasMoved == midSideSlider)
    {
        //[UserSliderCode_midSideSlider] -- add your slider handling code here..
		getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::midSideParam,                                                  (float)midSideSlider->getValue());
        //[/UserSliderCode_midSideSlider]
    }
    else if (sliderThatWasMoved == saturationSlider)
    {
        //[UserSliderCode_saturationSlider] -- add your slider handling code here..
		getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::thresholdParam,                                                  (float)saturationSlider->getValue());
        //[/UserSliderCode_saturationSlider]
    }
    else if (sliderThatWasMoved == hpfSlider)
    {
        //[UserSliderCode_hpfSlider] -- add your slider handling code here..
		getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::hpfParam,			(float)hpfSlider->getValue());
        //[/UserSliderCode_hpfSlider]
    }
    else if (sliderThatWasMoved == reverbSizeSlider)
    {
        //[UserSliderCode_reverbSizeSlider] -- add your slider handling code here..
		getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::reverbSizeParam,			(float)reverbSizeSlider->getValue());
        //[/UserSliderCode_reverbSizeSlider]
    }
    else if (sliderThatWasMoved == delayFeedbackSlider)
    {
        //[UserSliderCode_delayFeedbackSlider] -- add your slider handling code here..
        //[/UserSliderCode_delayFeedbackSlider]
    }
    else if (sliderThatWasMoved == slider)
    {
        //[UserSliderCode_slider] -- add your slider handling code here..
        //[/UserSliderCode_slider]
    }
    else if (sliderThatWasMoved == slider2)
    {
        //[UserSliderCode_slider2] -- add your slider handling code here..
        //[/UserSliderCode_slider2]
    }
    else if (sliderThatWasMoved == slider3)
    {
        //[UserSliderCode_slider3] -- add your slider handling code here..
        //[/UserSliderCode_slider3]
    }
    else if (sliderThatWasMoved == gainSlider)
    {
        //[UserSliderCode_gainSlider] -- add your slider handling code here..
		// It's vital to use setParameterNotifyingHost to change any parameters that are automatable
		// by the host, rather than just modifying them directly, otherwise the host won't know
		// that they've changed.
		getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::gainParam,                                                  (float)gainSlider->getValue());
        //[/UserSliderCode_gainSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void JuceDemoPluginAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == lnf3Btn)
    {
        //[UserButtonCode_lnf3Btn] -- add your button handler code here..
		LookAndFeel::setDefaultLookAndFeel(&lookAndFeelV3);
        //[/UserButtonCode_lnf3Btn]
    }
    else if (buttonThatWasClicked == guilafBtn)
    {
        //[UserButtonCode_guilafBtn] -- add your button handler code here..
		LookAndFeel::setDefaultLookAndFeel(&guilaf);
        //[/UserButtonCode_guilafBtn]
    }
    else if (buttonThatWasClicked == guilaf2Btn)
    {
        //[UserButtonCode_guilaf2Btn] -- add your button handler code here..
		LookAndFeel::setDefaultLookAndFeel(&guilaf2);
        //[/UserButtonCode_guilaf2Btn]
    }
    else if (buttonThatWasClicked == dryBtn)
    {
        //[UserButtonCode_dryBtn] -- add your button handler code here..
		getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::dryOnParam, (dryBtn->getToggleState() == true)?1.0f:0.0f);
        //[/UserButtonCode_dryBtn]
    }
    else if (buttonThatWasClicked == bypassBtn)
    {
        //[UserButtonCode_bypassBtn] -- add your button handler code here..
		getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::bypassParam, (bypassBtn->getToggleState() == true)?1.0f:0.0f);
		gainSlider->setEnabled(bypassBtn->getToggleState());
        //[/UserButtonCode_bypassBtn]
    }
    else if (buttonThatWasClicked == dryOnBtn)
    {
        //[UserButtonCode_dryOnBtn] -- add your button handler code here..
        //[/UserButtonCode_dryOnBtn]
    }
    else if (buttonThatWasClicked == wetOnBtn)
    {
        //[UserButtonCode_wetOnBtn] -- add your button handler code here..
        getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::bypassParam, (wetOnBtn->getToggleState() == true) ? 1.0f : 0.0f);
        gainSlider->setEnabled(wetOnBtn->getToggleState());
        //[/UserButtonCode_wetOnBtn]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void JuceDemoPluginAudioProcessorEditor::mouseEnter (const MouseEvent& e)
{
    //[UserCode_mouseEnter] -- Add your code here...
    //[/UserCode_mouseEnter]
}

bool JuceDemoPluginAudioProcessorEditor::keyPressed (const KeyPress& key)
{
    //[UserCode_keyPressed] -- Add your code here...
    return false;  // Return true if your handler uses this key event, or false to allow it to be passed-on.
    //[/UserCode_keyPressed]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...


// This timer periodically checks whether any of the filter's parameters have changed...
void JuceDemoPluginAudioProcessorEditor::timerCallback()
{
	JuceDemoPluginAudioProcessor* ourProcessor = getProcessor();

	AudioPlayHead::CurrentPositionInfo newPos(ourProcessor->lastPosInfo);

	if (lastDisplayedPosition != newPos)
	{
		displayPositionInfo(newPos);
	}

	gainSlider->setValue(ourProcessor->m_fGain);

	//set db display
	String dbString = amountToDb(ourProcessor->m_fGain);
	gainInfoLabel->setText(dbString, dontSendNotification);

	delaySlider->setValue(ourProcessor->m_fDelay);

	panSlider->setValue(ourProcessor->m_fPan);

	midSideSlider->setValue(ourProcessor->m_fMidSideParam);

	reverbSizeSlider->setValue(ourProcessor->m_fReverbSize);

	float pan = ourProcessor->m_fPan;

	float leftGain = 1.0f;
	float rightGain = 1.0f;
	String panString = "0.0\nC";
	if (pan > 0.5f){
		leftGain = 1 - (pan-0.5f)*2.0f;
		float panvalue = std::floor((pan-0.5f)*100.0f * 10.0f + 0.5f) / 10.0f;
		panString = String(panvalue);
		if (panString.contains(".") == false)
		{
			panString += ".0";
		}
		panString+="\nR";
	}
	if (pan < 0.5f){
		rightGain -= (0.5f-pan)*2.0f;
		float panvalue = std::floor((0.5f-pan)*100.0f * 10.0f + 0.5f) / 10.0f;
		panString = String(panvalue);
		if (panString.contains(".") == false)
		{
			panString += ".0";
		}
		panString+="\nL";
	}

	//0 - 0.5 = left 100
	//0.5 - 1 = right 100
	//dbString = amountToDb(leftGain);
	panInfoLabel->setText(panString,dontSendNotification);
	midsideInfoLabel->setText(String((int)(midSideSlider->getValue()*200)) + "%",dontSendNotification);
}

String JuceDemoPluginAudioProcessorEditor::amountToDb(float amount)
{
	float dBs = Decibels::gainToDecibels(amount);
	float dBsRoundedOnedecimal = std::floor(dBs * 10.0f + 0.5f) / 10.0f;
	String dbString = juce::String(dBsRoundedOnedecimal);
	if (dbString.contains(".") == false)
	{
		dbString += ".0";
	}
	if (dBsRoundedOnedecimal == -100.0f)
	{
		dbString = "-inF";
	}
	dbString += "\ndB";
	return dbString;
}


// quick-and-dirty function to format a timecode string
static const String timeToTimecodeString(const double seconds)
{
	const double absSecs = fabs(seconds);

	const int hours = (int)(absSecs / (60.0 * 60.0));
	const int mins = ((int)(absSecs / 60.0)) % 60;
	const int secs = ((int)absSecs) % 60;

	String s;
	if (seconds < 0)
		s = "-";

	s << String(hours).paddedLeft('0', 2) << ":"
		<< String(mins).paddedLeft('0', 2) << ":"
		<< String(secs).paddedLeft('0', 2) << ":"
		<< String(roundToInt(absSecs * 1000) % 1000).paddedLeft('0', 3);

	return s;
}

// quick-and-dirty function to format a bars/beats string
static const String ppqToBarsBeatsString(double ppq, double /*lastBarPPQ*/, int numerator, int denominator)
{
	if (numerator == 0 || denominator == 0)
		return "1|1|0";

	const int ppqPerBar = (numerator * 4 / denominator);
	const double beats = (fmod(ppq, ppqPerBar) / ppqPerBar) * numerator;

	const int bar = ((int)ppq) / ppqPerBar + 1;
	const int beat = ((int)beats) + 1;
	const int ticks = ((int)(fmod(beats, 1.0) * 960.0));

	String s;
	s << bar << '|' << beat << '|' << ticks;
	return s;
}

// Updates the text in our position label.
void JuceDemoPluginAudioProcessorEditor::displayPositionInfo(const AudioPlayHead::CurrentPositionInfo& pos)
{
	lastDisplayedPosition = pos;
	String displayText;
	displayText.preallocateBytes(128);

	displayText << String(pos.bpm, 2) << " bpm, "
		<< pos.timeSigNumerator << '/' << pos.timeSigDenominator
		<< "  -  " << timeToTimecodeString(pos.timeInSeconds)
		<< "  -  " << ppqToBarsBeatsString(pos.ppqPosition, pos.ppqPositionOfLastBarStart,
		pos.timeSigNumerator, pos.timeSigDenominator);

	if (pos.isRecording)
		displayText << "  (recording)";
	else if (pos.isPlaying)
		displayText << "  (playing)";

	infoLabel->setText(displayText, NotificationType::sendNotification);
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
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="0"
                 initialWidth="800" initialHeight="400">
  <METHODS>
    <METHOD name="mouseEnter (const MouseEvent&amp; e)"/>
    <METHOD name="keyPressed (const KeyPress&amp; key)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ff777777">
    <IMAGE pos="0 0 400 230" resource="uibg_png" opacity="1" mode="2"/>
    <RECT pos="0 0 1 1" fill="solid: ff32a52a" hasStroke="0"/>
  </BACKGROUND>
  <SLIDER name="panSlider" id="324eec4d274919f3" memberName="panSlider"
          virtualName="" explicitFocusOrder="0" pos="100 159 80 50" min="0"
          max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="" id="3084384ee25f6d12" memberName="infoLabel" virtualName=""
         explicitFocusOrder="0" pos="40 432 400 25" textCol="ff414141"
         edTextCol="ff000000" edBkgCol="0" labelText="aaa" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <SLIDER name="delaySlider" id="37878e5e9fd60a08" memberName="delaySlider"
          virtualName="" explicitFocusOrder="0" pos="208 47 80 50" tooltip="delay gain&#10;"
          trackcol="ffffffff" textboxhighlight="ff1111ee" textboxoutline="ff808080"
          min="0" max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="gainInfoLabel" id="dde6ff72637f37e7" memberName="gainInfoLabel"
         virtualName="" explicitFocusOrder="0" pos="56 88 80 20" textCol="ff323232"
         edTextCol="ff000000" edBkgCol="0" labelText="0.0 dB&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="64ddab567eb77e3c" memberName="panInfoLabel"
         virtualName="" explicitFocusOrder="0" pos="100 209 80 20" textCol="ff282828"
         edTextCol="ff000000" edBkgCol="0" labelText="C" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="delayTimeSlider" id="ead45d255e5f5831" memberName="delayTimeSlider"
          virtualName="" explicitFocusOrder="0" pos="288 47 80 50" min="0"
          max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="3b34631ac55e0fe6" memberName="delayTimeValueLabel"
         virtualName="" explicitFocusOrder="0" pos="288 27 80 20" textCol="ff282828"
         edTextCol="ff000000" edBkgCol="0" labelText="time" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="ec32effd76232b82" memberName="panHeader"
         virtualName="" explicitFocusOrder="0" pos="100 139 80 20" textCol="ff363636"
         edTextCol="ff000000" edBkgCol="0" labelText="pan&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="mid/side slider" id="84706171dc5b90dd" memberName="midSideSlider"
          virtualName="" explicitFocusOrder="0" pos="28 170 80 50" min="0"
          max="1" int="0.0050000000000000001" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="fcf994bed06bf6ab" memberName="midsideHeader"
         virtualName="" explicitFocusOrder="0" pos="18 150 80 20" textCol="ff363636"
         edTextCol="ff000000" edBkgCol="0" labelText="mid/side" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="mid/side slider" id="2a577f0fc0372cc6" memberName="saturationSlider"
          virtualName="" explicitFocusOrder="0" pos="144 253 100 50" min="0.001"
          max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="saturation fx" id="eda4710f044030be" memberName="distortionHeader"
         virtualName="" explicitFocusOrder="0" pos="156 240 80 10" textCol="ff363636"
         edTextCol="ff000000" edBkgCol="0" labelText="saturation" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="12"/>
  <LABEL name="new label" id="f53c45ed3e69f449" memberName="hpfHeader"
         virtualName="" explicitFocusOrder="0" pos="258 150 80 30" textCol="ff363636"
         edTextCol="ff000000" edBkgCol="0" labelText="hi pass filter"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Aharoni" fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="hpfSlider" id="253b421224cbac37" memberName="hpfSlider"
          virtualName="" explicitFocusOrder="0" pos="268 170 60 50" tooltip="hi pass filter (hz)"
          min="20" max="10000" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.20000000000000001"/>
  <SLIDER name="new slider" id="81b8a5f3e2f90d2e" memberName="reverbSizeSlider"
          virtualName="" explicitFocusOrder="0" pos="472 48 50 50" min="0.01"
          max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="63580ead55c45fe" memberName="midsideInfoLabel"
         virtualName="" explicitFocusOrder="0" pos="18 225 80 30" textCol="ff363636"
         edTextCol="ff000000" edBkgCol="0" labelText="80%" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="9e5a6f98ed1157ee" memberName="reverbSizeHeader"
         virtualName="" explicitFocusOrder="0" pos="456 24 80 30" textCol="ff363636"
         edTextCol="ff000000" edBkgCol="0" labelText="room size" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="dfs_violet" id="f86ed4bd47474957" memberName="delayFeedbackSlider"
          virtualName="" explicitFocusOrder="0" pos="368 47 80 50" min="0"
          max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="b702d23a464e1ffe" memberName="delayTimeValueLabel2"
         virtualName="" explicitFocusOrder="0" pos="368 27 80 20" textCol="ff282828"
         edTextCol="ff000000" edBkgCol="0" labelText="feedback" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="17713b10facdb0a1" memberName="delayAmountHeader"
         virtualName="" explicitFocusOrder="0" pos="208 24 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="amount" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Aharoni" fontsize="10" bold="0"
         italic="0" justification="36"/>
  <TEXTBUTTON name="new button" id="877f25c71c1bc232" memberName="lnf3Btn"
              virtualName="" explicitFocusOrder="0" pos="216 384 88 24" buttonText="lfv3"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="bcef889c607949af" memberName="guilafBtn"
              virtualName="" explicitFocusOrder="0" pos="320 384 88 24" buttonText="guilaf"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="c18db766ecc28fe6" memberName="guilaf2Btn"
              virtualName="" explicitFocusOrder="0" pos="432 384 88 24" buttonText="guilaf2"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="new toggle button" id="9fec732da680abce" memberName="dryBtn"
                virtualName="" explicitFocusOrder="0" pos="24 304 70 24" buttonText="dry +"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="1"/>
  <SLIDER name="new slider" id="64dc86b4ed912be" memberName="slider" virtualName=""
          explicitFocusOrder="0" pos="472 96 50 50" min="0" max="10" int="0"
          style="RotaryVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="cf93cb9c05f6ea83" memberName="reverbSizeHeader2"
         virtualName="" explicitFocusOrder="0" pos="520 24 80 30" textCol="ff363636"
         edTextCol="ff000000" edBkgCol="0" labelText="damp todo" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="19c54baf5cf03b32" memberName="slider2"
          virtualName="" explicitFocusOrder="0" pos="472 144 50 50" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="629d011e42cdcd54" memberName="reverbSizeHeader3"
         virtualName="" explicitFocusOrder="0" pos="600 24 80 30" textCol="ff363636"
         edTextCol="ff000000" edBkgCol="0" labelText="freeze todo" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="935f633b2a015b36" memberName="slider3"
          virtualName="" explicitFocusOrder="0" pos="472 192 50 50" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="7c566ba924521d30" memberName="reverbSizeHeader4"
         virtualName="" explicitFocusOrder="0" pos="680 24 80 30" textCol="ff363636"
         edTextCol="ff000000" edBkgCol="0" labelText="width todo" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <TOGGLEBUTTON name="new toggle button" id="6a90886856c6d4a2" memberName="bypassBtn"
                virtualName="" explicitFocusOrder="0" pos="24 272 50 20" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <IMAGEBUTTON name="new button" id="e6bfce1ed1163934" memberName="dryOnBtn"
               virtualName="" explicitFocusOrder="0" pos="7 9 35 13" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="dry_off_png" opacityNormal="1" colourNormal="0"
               resourceOver="" opacityOver="1" colourOver="0" resourceDown="dry_on_png"
               opacityDown="1" colourDown="0"/>
  <IMAGEBUTTON name="new button" id="d1b3d57fbe1550e7" memberName="wetOnBtn"
               virtualName="" explicitFocusOrder="0" pos="7 27 22 23" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="wet_off_png" opacityNormal="1" colourNormal="0"
               resourceOver="" opacityOver="1" colourOver="0" resourceDown="wet_on_png"
               opacityDown="1" colourDown="0"/>
  <SLIDER name="gainSlider" id="c31acc4ca22491a9" memberName="gainSlider"
          virtualName="" explicitFocusOrder="0" pos="18 19 70 50" tooltip="gain"
          textboxbkgd="ffffff" textboxhighlight="881111ee" textboxoutline="0"
          min="0" max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.29999999999999999"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

// JUCER_RESOURCE: kreps_logo_jpeg, 11931, "../../../Desktop/kreps_logo.jpeg"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_kreps_logo_jpeg[] = { 255,216,255,224,0,16,74,70,73,70,0,1,1,0,0,1,0,1,0,0,255,219,0,67,0,5,3,4,4,4,3,5,4,4,4,5,5,5,6,7,12,8,7,7,
7,7,15,11,11,9,12,17,15,18,18,17,15,17,17,19,22,28,23,19,20,26,21,17,17,24,33,24,26,29,29,31,31,31,19,23,34,36,34,30,36,28,30,31,30,255,219,0,67,1,5,5,5,7,6,7,14,8,8,14,30,20,17,20,30,30,30,30,30,30,30,
30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,255,192,0,17,8,1,144,1,144,3,1,34,0,2,17,1,3,17,1,255,196,0,29,0,1,0,1,
5,1,1,1,0,0,0,0,0,0,0,0,0,0,1,2,3,5,6,7,4,8,9,255,196,0,56,16,0,1,3,3,4,1,3,4,1,2,5,3,4,3,0,0,1,0,2,3,4,5,17,6,18,33,49,65,19,34,81,7,20,50,97,113,66,129,21,35,82,145,161,36,51,98,8,69,177,193,99,209,
241,255,196,0,23,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,255,196,0,26,17,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,17,2,18,49,33,255,218,0,12,3,1,0,2,17,3,17,0,63,0,251,45,67,142,6,83,33,65,32,251,71,104,
41,46,80,11,186,10,166,183,229,84,0,8,40,217,187,181,62,152,85,97,48,130,147,24,194,167,211,106,185,133,56,65,107,211,106,122,109,87,112,152,65,107,211,106,122,109,87,112,152,65,107,211,106,122,109,87,
112,152,65,107,211,106,122,109,87,112,152,65,107,211,106,122,109,87,112,152,65,107,211,106,122,109,87,112,152,65,107,211,106,122,109,87,112,152,65,107,211,106,122,109,87,112,152,65,107,211,106,122,109,
87,112,152,65,107,211,106,122,109,87,112,152,65,107,211,106,122,109,87,112,152,65,107,211,106,122,109,87,112,152,65,107,211,106,122,109,87,112,163,132,22,253,54,167,166,213,115,33,56,8,45,250,109,79,77,
170,224,193,83,194,11,94,155,83,211,106,185,194,12,20,22,253,54,167,166,213,115,133,60,32,181,233,181,75,99,30,21,204,40,194,10,125,48,160,177,87,143,218,142,80,91,193,111,33,84,215,124,169,0,231,144,
133,185,65,57,30,20,130,173,227,111,10,166,242,56,65,15,63,10,99,28,103,202,0,7,237,72,237,5,72,136,128,136,136,8,136,128,136,136,8,136,128,136,136,8,136,128,136,136,8,136,128,136,136,8,136,128,136,136,
8,136,128,136,136,8,163,41,148,77,74,131,210,101,82,79,56,199,31,40,163,124,169,228,171,18,212,193,7,50,207,27,7,236,172,53,211,88,89,104,90,127,234,227,149,223,13,40,54,12,142,148,110,25,193,192,90,28,
186,229,213,4,182,138,145,220,244,247,116,170,134,233,116,172,231,241,254,16,111,69,204,105,229,195,253,208,57,174,252,92,22,156,215,87,227,15,145,197,95,130,74,168,249,222,79,242,131,106,28,249,70,130,
29,218,196,82,92,240,118,200,0,89,72,38,100,184,45,112,40,47,34,4,64,68,68,4,68,65,75,128,42,159,199,165,94,220,156,161,104,40,37,17,16,17,17,1,17,16,17,17,1,17,16,17,17,1,17,16,17,17,1,17,16,17,17,1,
17,16,17,17,1,17,16,17,17,1,20,56,100,114,168,118,90,59,246,252,160,168,149,106,89,89,19,12,146,59,107,91,217,43,5,169,117,77,190,209,25,46,148,57,254,0,92,175,83,234,235,197,226,71,71,19,139,41,93,222,
14,20,210,71,68,191,107,235,61,185,207,137,147,9,37,30,50,180,155,175,212,187,141,70,232,233,153,233,15,31,181,166,54,133,239,151,212,148,238,113,249,229,101,237,118,134,72,253,239,105,39,56,9,43,175,
49,106,75,141,234,238,242,38,158,65,159,130,178,246,45,55,60,238,204,205,223,251,206,86,207,96,211,204,218,30,232,248,254,22,217,77,73,28,13,1,160,14,62,21,46,48,246,123,4,52,241,135,150,158,63,164,133,
153,138,24,226,102,26,192,21,211,147,215,74,8,225,28,234,203,128,207,42,219,202,185,39,149,109,255,0,130,34,196,152,35,145,133,16,77,44,50,7,53,231,1,75,250,86,252,32,206,91,238,109,120,216,255,0,201,
101,24,114,50,180,185,222,91,135,52,227,31,11,41,100,187,182,79,242,158,121,7,3,40,54,20,80,8,45,202,144,128,136,136,8,136,128,136,136,8,136,128,136,136,8,136,128,136,136,8,136,128,136,136,8,136,128,136,
136,8,136,128,136,136,8,136,128,136,136,10,11,128,71,126,42,128,14,79,60,5,1,228,17,201,192,239,43,73,215,90,167,236,218,105,40,228,221,47,233,122,181,182,160,52,180,206,166,133,224,72,71,96,174,109,54,
217,94,106,106,166,220,226,126,83,90,145,226,168,19,85,72,100,168,204,132,156,224,149,49,211,23,116,221,128,120,87,95,93,71,8,59,61,197,32,171,150,160,237,138,35,207,233,97,191,50,61,84,54,227,35,131,
157,200,11,111,177,218,90,231,181,196,96,5,143,211,180,117,14,45,15,140,224,254,150,241,71,19,96,136,13,188,171,202,90,187,12,126,147,67,6,0,82,88,59,37,73,37,195,42,79,75,108,106,143,214,16,227,9,242,
165,17,98,86,149,101,224,237,199,149,234,147,162,188,238,237,7,154,78,59,86,137,192,85,61,196,184,175,61,84,155,90,80,121,106,167,32,150,183,149,228,142,71,195,32,153,167,4,21,50,63,115,138,178,247,6,
251,201,224,32,222,116,253,197,149,80,134,61,254,252,116,179,0,248,92,186,221,114,125,45,104,144,59,219,240,186,69,182,165,149,116,205,149,167,57,1,7,171,40,160,15,42,80,17,17,1,17,16,17,17,1,17,16,17,
17,1,17,16,17,17,1,17,16,17,17,1,17,16,17,17,1,17,16,17,19,194,10,75,136,76,159,42,10,199,222,238,244,214,170,115,44,199,160,131,221,60,141,99,73,123,218,214,249,36,173,59,86,235,171,117,181,175,134,9,
4,147,99,24,7,133,163,234,205,101,87,116,145,240,211,61,205,132,246,65,90,150,3,164,50,75,151,56,249,42,53,204,122,174,183,218,203,141,83,230,199,4,249,94,54,54,174,165,252,185,248,248,11,211,75,4,147,
63,134,140,101,109,122,118,199,35,200,37,138,58,72,196,217,244,235,231,195,178,93,252,173,242,201,167,34,129,140,115,218,63,217,101,237,22,168,105,97,201,103,63,194,200,189,189,108,24,10,227,54,173,83,
211,197,16,27,90,6,21,230,144,115,231,149,67,79,56,42,179,128,120,76,115,213,204,229,187,122,81,227,10,150,149,80,233,81,5,191,29,170,120,29,158,85,103,174,21,137,220,200,88,94,243,210,9,127,33,121,223,
144,121,33,120,170,47,12,144,150,211,243,142,15,242,188,159,115,43,142,94,236,4,30,215,241,146,122,88,154,233,131,165,216,222,151,165,243,56,176,183,61,172,108,251,99,36,189,5,47,59,65,57,88,234,186,142,
8,200,194,243,93,46,145,71,150,238,88,200,103,150,186,79,78,3,156,158,80,122,254,224,203,38,216,242,72,93,15,67,86,185,180,254,132,228,15,133,170,80,80,50,146,16,100,110,100,42,252,85,82,67,48,145,167,
13,5,7,82,105,4,100,116,167,37,98,180,245,193,181,148,163,231,11,40,130,91,202,149,13,242,165,1,17,16,17,17,1,17,16,17,17,1,17,16,17,17,1,17,16,17,17,1,17,16,17,50,163,33,5,42,115,132,65,140,225,25,145,
57,240,169,35,7,32,243,133,14,60,28,120,90,134,180,213,180,246,200,29,79,4,129,243,150,231,143,8,220,140,142,167,212,180,150,122,103,23,74,215,75,240,184,253,250,251,89,123,172,116,146,72,67,71,77,207,
24,94,59,149,201,247,10,147,60,206,115,206,127,19,210,242,122,153,252,35,218,127,75,45,201,131,90,236,191,219,131,224,175,101,5,4,147,247,207,42,245,182,223,53,78,55,30,15,133,186,233,203,3,218,192,92,
223,249,69,248,243,88,44,59,139,65,111,11,121,183,209,69,74,192,208,6,112,174,82,83,50,158,48,26,209,149,127,174,64,201,70,45,2,135,126,37,72,67,210,211,43,120,63,164,111,124,170,191,149,30,80,82,254,
149,76,113,198,229,14,25,86,91,33,13,45,248,60,160,187,52,236,138,39,77,41,195,90,23,59,189,95,43,47,55,159,177,166,200,167,105,193,112,56,91,30,183,171,124,118,210,200,142,119,96,45,115,75,209,54,48,
247,176,228,184,228,146,162,198,102,138,157,176,179,210,141,248,120,231,145,156,171,161,193,217,46,221,129,216,199,106,151,146,32,147,102,26,99,27,183,17,218,225,154,143,234,62,164,126,175,124,116,172,
12,167,167,118,8,219,249,97,69,119,108,130,221,205,57,35,199,192,90,46,187,190,31,87,237,232,220,92,255,0,45,106,204,216,238,21,26,134,212,217,99,140,211,72,90,3,191,217,100,173,154,90,215,74,125,105,
191,207,157,220,151,31,11,76,185,245,130,197,116,187,206,38,168,15,100,121,242,86,255,0,109,182,83,91,160,218,0,200,236,225,101,164,17,83,197,178,22,134,1,240,177,85,147,228,237,249,8,45,212,204,30,242,
6,87,150,119,134,60,140,231,33,81,81,56,140,19,198,87,130,89,203,134,236,242,131,97,210,87,115,75,112,108,78,39,107,142,23,75,132,131,19,72,60,56,101,112,232,166,115,37,108,157,16,66,235,122,78,189,149,
182,182,188,63,113,96,193,65,154,111,145,240,165,67,8,35,112,232,169,64,68,68,4,68,64,68,68,4,68,64,68,68,4,68,64,68,68,4,68,64,68,40,58,65,7,180,66,60,168,29,112,130,57,12,36,114,85,185,230,100,49,23,
204,240,214,142,121,42,221,125,101,61,13,35,166,168,144,49,163,158,74,228,154,215,90,203,112,145,244,212,78,13,140,113,144,83,86,70,107,91,235,135,179,125,45,168,228,244,231,5,205,106,159,45,76,206,154,
121,156,231,59,147,146,169,115,223,146,237,222,231,118,84,197,19,164,112,0,101,71,94,102,41,104,222,54,198,9,43,51,102,180,201,51,198,230,149,234,211,246,103,74,237,197,135,253,151,64,178,89,153,8,220,
224,83,11,99,199,96,177,178,61,165,205,233,108,240,193,28,17,128,208,21,81,181,172,27,90,21,88,202,99,157,168,28,133,33,67,142,60,4,97,202,99,23,82,20,168,229,7,237,85,67,188,171,103,242,85,254,68,176,
126,127,240,188,55,91,141,61,28,71,220,12,160,114,16,199,170,66,198,142,92,2,240,201,81,16,115,176,238,22,23,239,167,174,4,254,3,244,171,25,218,70,73,207,148,49,230,213,239,222,200,139,121,111,149,228,
177,72,195,25,107,79,43,35,83,24,158,31,76,128,112,56,90,101,69,115,236,183,113,28,152,244,222,123,114,139,27,187,154,28,194,194,59,28,149,175,205,163,236,117,21,198,177,208,52,28,251,184,237,102,169,
170,27,83,78,217,96,120,45,35,156,43,164,19,128,209,150,249,194,98,173,82,211,195,73,79,232,211,176,53,190,48,175,2,70,48,121,65,141,248,193,192,70,103,36,134,113,254,162,171,56,137,131,159,17,229,107,
181,213,6,57,12,103,191,11,99,57,229,191,43,85,213,69,180,178,7,140,146,71,148,30,57,100,57,37,206,86,36,169,96,7,149,139,150,181,206,46,235,133,230,116,174,32,151,56,32,200,75,87,144,67,79,43,126,250,
71,116,50,62,90,87,185,114,177,44,109,126,75,214,205,244,198,233,20,26,133,140,221,255,0,112,225,7,122,140,97,160,41,84,199,203,114,14,66,169,1,17,16,17,17,1,17,16,17,17,1,17,16,17,17,1,17,16,17,20,100,
32,148,80,79,10,147,130,11,1,63,202,3,137,232,116,177,90,134,247,71,103,166,47,168,120,11,193,170,245,61,61,150,23,53,175,15,159,111,1,114,43,221,202,186,239,84,233,42,11,182,56,240,51,194,53,57,215,175,
86,106,122,171,220,199,116,142,142,48,125,160,30,194,215,137,220,64,12,199,237,122,89,74,231,31,192,240,189,212,182,135,74,224,72,32,44,183,152,199,83,211,186,105,0,91,85,134,196,94,230,146,60,175,125,
134,200,215,184,101,189,126,150,237,111,160,138,158,32,48,63,217,88,122,88,181,91,35,166,140,101,163,253,150,81,164,237,225,8,220,48,20,142,149,98,209,191,137,249,82,158,17,25,65,28,21,67,78,9,85,30,209,
4,132,84,198,242,221,237,35,219,142,214,183,171,117,44,86,184,61,40,78,100,60,101,21,238,189,94,98,165,140,194,195,255,0,80,120,11,1,12,18,78,243,81,84,226,73,240,188,122,122,122,123,134,249,220,253,242,
147,158,78,86,100,231,140,12,144,138,1,129,195,54,199,242,160,47,53,214,176,91,237,211,87,72,199,59,104,252,66,228,20,218,251,83,92,117,41,108,81,98,140,59,7,3,194,14,210,14,14,71,133,167,253,84,183,138,
139,11,238,48,240,232,134,114,22,209,111,151,238,104,97,145,160,242,61,202,46,116,176,214,91,231,130,86,251,92,210,49,225,7,207,26,79,235,60,54,74,195,71,114,127,249,45,126,11,137,93,78,217,245,99,74,
214,192,29,79,92,192,92,58,202,230,21,31,69,161,190,106,90,151,211,179,32,184,146,9,224,45,206,201,244,235,79,105,225,28,81,82,182,162,165,191,144,236,101,6,79,82,253,71,125,37,11,223,107,160,146,169,
196,112,64,43,86,209,90,171,88,94,111,13,150,170,41,96,164,221,238,105,255,0,133,214,173,182,138,22,210,24,230,166,140,18,56,27,2,198,73,105,154,10,189,148,209,53,177,19,216,24,65,178,192,92,248,98,255,
0,89,28,173,99,234,57,17,91,61,64,57,7,11,103,167,141,209,194,192,247,140,225,106,31,84,230,107,45,77,96,118,73,57,68,115,231,86,201,206,7,133,103,238,100,57,203,138,176,227,147,187,244,170,29,34,14,145,
196,254,92,172,214,134,144,13,77,74,3,185,220,22,20,240,22,83,74,251,53,13,33,31,235,8,62,166,163,59,169,152,127,241,10,234,243,90,206,104,34,63,248,133,233,64,68,68,4,68,64,68,68,4,68,64,68,68,4,61,34,
32,167,5,72,227,180,200,80,74,9,200,84,255,0,117,33,88,158,88,224,99,164,145,205,108,99,188,149,53,100,213,209,207,25,90,254,174,212,16,219,104,222,198,72,209,49,24,237,107,90,195,234,12,52,155,233,109,
109,223,39,91,151,50,186,220,107,238,53,14,154,166,103,114,122,202,106,206,89,122,250,200,234,106,29,53,76,198,66,238,121,241,250,94,67,116,166,143,32,51,113,29,12,44,84,112,62,67,249,19,240,179,22,107,
44,147,59,37,164,255,0,100,215,110,100,136,167,169,169,159,134,69,140,244,182,157,59,67,86,247,52,189,153,207,133,149,176,105,246,183,6,72,199,251,45,162,158,142,42,118,251,90,56,76,98,244,139,101,35,
33,132,29,163,114,245,144,29,250,194,166,51,225,92,198,60,170,231,170,70,91,210,149,40,136,128,19,40,120,28,40,29,100,161,38,39,4,158,21,14,123,90,9,113,192,30,74,166,106,136,161,137,207,149,193,172,11,
85,186,221,42,46,82,58,142,159,45,135,173,193,7,174,227,125,113,145,208,210,141,249,227,43,89,213,86,179,91,64,101,113,34,81,207,30,22,106,154,154,58,102,109,119,185,255,0,42,232,97,115,28,215,140,135,
34,199,53,210,213,238,182,220,140,68,146,204,224,146,186,76,111,223,19,37,107,255,0,62,87,57,214,118,241,111,184,138,136,143,180,156,156,45,151,70,92,217,83,77,233,61,249,112,60,35,82,54,23,176,62,25,
34,149,162,86,60,116,86,155,117,181,211,91,42,200,164,164,0,188,231,133,185,128,75,143,60,5,68,144,71,43,247,200,208,72,233,18,188,246,176,230,209,69,159,242,206,57,106,245,72,28,99,115,55,115,142,85,
99,24,192,24,1,98,53,53,206,43,117,190,71,239,30,161,235,148,77,88,168,185,211,216,40,106,94,208,13,68,164,144,224,122,11,195,163,234,168,170,228,116,222,167,169,51,221,151,2,121,11,94,191,81,213,221,
244,223,223,83,188,153,27,224,124,46,99,14,171,158,199,116,19,7,185,178,68,112,230,158,144,215,211,14,218,93,144,115,143,210,169,190,227,184,145,129,224,240,180,125,19,245,34,193,124,136,54,106,182,83,
212,96,112,79,101,109,82,221,45,141,137,210,77,84,199,99,162,10,26,246,58,70,54,55,200,254,3,71,149,201,117,229,215,252,66,187,210,140,229,140,224,172,174,174,213,174,168,221,75,64,236,55,172,133,164,
238,115,156,231,56,229,196,242,81,14,58,241,133,1,74,32,142,60,244,179,58,38,39,77,169,41,155,140,225,193,97,136,207,11,113,250,65,74,106,181,11,94,230,228,52,160,250,30,129,187,104,227,31,248,133,125,
81,11,118,198,27,240,171,64,68,68,4,68,64,68,68,4,68,64,68,68,5,14,233,74,30,144,80,238,58,66,118,140,159,248,81,222,73,88,109,73,127,164,179,210,186,105,72,50,99,218,223,148,88,247,92,238,52,212,20,174,
158,121,3,64,240,74,228,90,211,88,85,92,230,48,82,73,178,28,224,237,43,27,170,117,5,93,238,119,59,213,115,35,207,13,5,97,27,150,59,218,222,49,202,203,114,33,205,5,197,251,137,62,73,237,87,20,79,149,225,
187,119,2,171,164,166,116,239,32,116,86,215,96,178,110,45,36,35,85,227,178,89,156,247,0,26,78,79,144,183,235,21,153,176,180,25,27,142,62,23,170,209,106,138,8,193,32,103,60,44,168,0,251,115,194,49,122,
197,44,104,96,195,66,17,193,229,72,225,15,75,76,90,143,28,42,153,215,37,80,135,40,204,171,153,62,20,2,75,241,225,80,31,133,94,114,223,111,148,105,45,59,156,71,194,177,93,85,21,37,59,166,157,224,48,116,
60,171,23,107,156,22,218,114,101,56,62,63,149,169,204,250,139,165,81,168,149,228,52,31,108,127,40,46,85,213,207,118,159,13,246,83,142,6,59,43,209,20,81,192,3,6,127,149,48,198,214,51,218,54,159,33,84,55,
103,56,202,1,60,103,25,255,0,229,98,175,183,136,237,177,144,15,171,51,135,181,141,86,239,87,129,79,55,163,76,55,84,191,218,24,173,91,237,108,183,147,112,186,31,86,165,252,182,55,120,202,44,97,238,22,218,
234,235,11,174,21,45,112,115,185,107,86,189,97,174,117,182,224,199,124,112,65,233,116,214,62,106,248,68,47,2,56,60,12,46,119,170,173,175,160,185,189,205,25,143,57,202,55,29,34,142,165,181,52,205,150,51,
237,112,247,43,248,220,50,210,74,211,116,45,216,57,194,146,83,237,60,45,195,27,7,183,172,163,53,230,187,215,71,111,162,124,206,201,218,58,92,139,83,94,103,184,84,60,189,174,107,55,112,2,236,85,180,208,
212,68,89,35,67,178,58,90,133,85,146,141,207,123,100,136,55,158,56,70,81,162,229,107,108,14,107,189,192,156,96,173,23,234,38,129,167,187,195,45,85,27,253,25,79,60,45,254,134,149,180,177,152,162,119,183,
188,47,5,246,65,246,18,52,130,223,225,7,207,116,31,79,238,116,85,251,223,113,198,15,109,39,43,160,208,50,170,158,144,67,45,116,146,227,193,43,213,86,214,250,227,0,117,242,172,251,183,30,91,143,209,65,
36,19,206,72,83,253,177,255,0,218,34,2,131,159,10,83,32,48,146,130,156,231,129,217,93,139,232,117,165,204,140,213,202,194,15,142,23,42,177,81,58,190,225,12,45,237,206,95,75,104,235,115,45,150,136,99,218,
1,45,8,51,141,243,202,149,13,242,165,1,17,16,17,17,1,17,16,17,17,1,19,42,3,129,25,240,130,130,226,31,250,81,147,201,14,220,223,132,115,196,108,62,161,24,249,43,65,214,218,217,148,97,244,118,236,25,79,
27,135,133,149,145,150,213,218,170,27,92,78,142,153,237,50,227,162,185,13,218,229,85,114,170,124,213,50,146,73,224,103,140,47,53,108,245,21,147,190,162,121,139,158,227,156,101,88,104,46,224,183,148,116,
230,46,0,209,253,97,122,104,169,196,142,192,107,138,189,109,182,25,255,0,38,30,127,107,120,176,88,65,0,236,24,1,26,181,227,211,246,70,191,105,217,143,236,183,123,109,4,52,209,14,6,85,202,42,72,233,226,
246,129,144,189,36,126,149,142,93,84,131,159,24,194,97,78,115,142,49,132,85,145,70,19,33,50,130,28,168,61,170,156,85,36,28,160,165,234,193,145,205,115,135,244,227,133,92,243,197,31,230,240,23,130,74,198,
200,237,153,195,1,237,7,50,215,183,75,129,185,186,41,67,131,1,246,172,158,137,186,137,98,251,105,78,93,242,86,71,93,90,153,95,78,234,136,128,46,140,113,251,92,242,207,85,37,190,188,228,144,67,176,141,
79,142,180,252,14,7,63,180,198,88,188,214,202,166,85,208,182,64,125,216,229,122,155,195,74,35,17,29,45,45,170,71,212,200,61,74,135,146,91,184,103,25,87,41,233,100,168,155,238,171,137,220,79,176,19,225,
123,165,134,57,72,116,173,206,58,42,235,134,240,208,238,155,210,34,6,208,67,0,192,253,44,62,172,183,71,89,111,120,121,13,199,71,202,202,86,85,67,75,78,233,106,8,96,3,131,242,180,230,84,220,245,5,234,56,
105,218,239,180,107,176,231,4,88,214,41,42,37,162,174,252,72,244,79,31,181,212,45,21,109,173,163,108,205,57,59,70,66,212,53,173,130,90,106,231,58,15,115,118,241,143,37,91,209,119,39,210,213,253,180,206,
33,167,142,126,81,91,254,8,198,63,34,177,247,138,92,179,126,57,253,44,139,121,27,220,113,159,197,88,174,150,56,104,164,146,103,129,129,198,81,26,241,33,141,206,64,3,130,181,253,71,51,36,140,181,174,11,
19,120,191,212,73,83,44,113,28,52,28,44,59,234,230,126,75,158,114,136,162,168,229,202,208,82,243,184,229,82,78,57,240,130,164,81,148,60,55,119,132,19,225,67,26,93,47,164,214,151,23,35,125,199,0,18,126,
48,183,157,1,165,37,158,161,179,213,180,231,176,59,65,176,125,38,210,237,143,109,84,209,251,243,145,144,187,3,24,35,12,104,232,12,47,13,150,134,58,74,118,48,55,107,177,199,11,37,142,58,65,45,242,165,64,
253,169,64,68,68,4,68,64,68,68,4,84,188,237,110,80,147,159,24,64,35,14,221,231,11,207,85,83,21,52,70,74,151,181,141,254,85,155,181,206,158,221,74,250,137,156,6,7,1,114,45,89,169,171,110,211,62,8,137,100,
89,224,130,166,172,140,142,182,214,210,212,189,244,150,247,98,62,139,130,208,156,231,111,113,124,134,66,227,201,43,211,29,35,220,75,137,57,243,251,87,98,161,46,56,24,201,81,210,71,138,54,110,118,7,149,
153,181,90,95,43,193,218,78,74,247,219,44,130,71,52,243,149,188,217,44,194,22,53,206,111,252,42,187,35,199,167,236,108,99,65,145,171,104,167,134,56,89,134,180,42,154,208,193,128,0,85,231,62,19,24,189,
33,163,0,149,42,20,171,24,17,82,79,40,78,16,7,149,4,2,48,227,128,170,192,29,158,74,162,87,197,19,11,166,118,214,132,49,36,226,50,231,16,26,60,149,128,186,223,61,230,158,151,221,199,36,124,175,21,234,247,
53,92,198,150,151,134,116,72,86,104,169,4,30,226,237,207,119,39,40,98,252,78,149,205,221,51,142,79,133,80,4,121,71,99,126,123,253,32,201,113,193,24,67,9,48,88,90,254,90,120,43,67,214,214,83,75,47,220,
211,183,218,121,56,91,219,114,252,241,192,94,123,157,51,106,45,210,64,225,187,142,252,163,83,241,167,232,91,169,101,87,219,78,239,107,185,25,91,203,70,55,59,57,7,165,200,229,100,212,55,55,6,228,22,187,
45,207,144,186,70,156,175,109,109,4,110,220,12,140,30,240,137,140,167,113,43,21,245,81,82,83,25,166,252,26,50,85,252,156,96,116,85,170,170,56,171,32,49,72,73,7,176,136,211,98,23,93,95,118,244,225,14,138,
138,35,238,63,33,109,83,207,73,99,165,109,5,165,141,146,165,195,220,239,218,162,122,218,123,93,33,183,90,227,196,143,225,199,28,169,181,208,8,63,207,152,23,76,238,114,124,33,21,209,82,200,92,31,92,224,
249,164,231,7,194,210,181,101,182,75,125,120,168,135,134,238,201,199,242,186,24,192,105,221,135,103,250,143,97,97,117,101,60,117,22,121,28,233,3,92,7,25,69,213,171,21,238,149,246,189,243,74,55,48,124,
173,31,88,234,89,46,21,14,166,166,121,107,71,28,45,101,146,213,69,44,177,137,137,143,62,10,131,201,206,48,126,81,16,220,243,147,147,229,74,133,40,10,19,148,207,232,147,156,12,32,128,0,237,122,40,40,42,
235,102,17,211,66,226,79,245,99,128,182,157,55,163,159,87,27,42,171,165,217,25,228,6,246,87,69,211,186,112,0,25,73,6,216,186,115,220,61,217,65,167,233,77,25,233,72,39,172,255,0,62,79,244,97,117,205,63,
102,101,13,56,118,208,9,25,3,29,47,77,166,209,5,7,32,110,113,242,86,76,242,49,142,16,27,146,1,56,225,84,169,3,145,227,10,164,4,68,64,68,68,4,68,202,2,40,202,160,146,50,119,0,193,217,40,43,121,195,114,
177,23,171,237,13,162,55,62,166,76,59,28,5,133,213,250,194,158,213,4,177,82,188,73,62,48,60,174,69,115,184,212,220,42,31,61,68,143,33,199,162,226,84,89,53,154,213,218,172,221,106,28,198,60,136,199,64,
30,214,1,247,7,146,209,28,120,3,178,172,49,128,28,128,51,225,123,40,104,164,168,119,35,1,70,228,81,20,181,117,7,17,140,44,245,154,209,85,35,154,92,78,86,83,79,216,247,184,101,184,254,203,120,182,219,98,
166,96,32,2,224,62,17,109,120,116,253,171,211,96,47,236,44,248,5,132,52,124,43,109,246,158,56,87,26,236,140,171,28,237,64,252,249,82,60,168,33,84,21,65,17,16,82,123,66,161,253,114,50,223,210,177,83,83,
29,60,91,158,241,183,227,202,10,234,42,34,166,167,116,239,57,192,90,141,194,227,61,218,87,71,27,139,97,207,36,44,38,177,212,21,31,112,214,156,182,44,248,248,89,107,37,84,21,52,45,124,88,224,115,128,138,
244,211,195,29,43,61,173,5,199,202,186,214,12,151,23,118,20,114,57,33,87,25,201,231,132,86,35,83,95,232,108,22,199,213,85,56,0,60,149,167,104,255,0,168,147,222,238,70,38,82,22,196,93,128,126,66,217,171,
180,219,46,213,19,138,179,152,79,135,114,22,2,217,67,65,65,114,251,106,54,55,45,118,50,214,160,232,13,45,45,14,107,176,79,97,75,136,13,118,122,194,183,22,76,77,200,198,2,75,145,19,201,248,225,17,162,106,
250,3,49,117,68,3,5,135,156,124,47,14,146,186,154,43,142,9,62,147,248,43,109,176,91,170,42,43,43,69,75,79,164,246,144,220,173,26,251,64,251,101,105,141,224,143,126,71,251,163,81,213,99,120,123,65,30,70,
66,147,145,209,194,215,52,109,216,84,211,253,172,135,222,7,25,91,32,47,39,156,13,188,35,11,70,158,15,185,19,182,48,72,242,175,13,219,156,231,126,39,149,3,216,194,55,12,149,106,174,162,58,122,115,60,207,
1,173,30,80,69,84,240,211,82,62,121,223,134,5,204,53,134,167,125,123,204,48,18,200,243,142,20,235,77,73,45,125,73,166,132,145,15,92,116,181,110,243,158,80,0,107,71,183,39,61,149,42,20,160,34,39,132,20,
151,109,43,223,99,163,125,109,202,8,89,249,57,203,194,24,227,46,214,55,116,142,224,5,213,62,148,233,99,28,140,171,149,135,113,231,159,8,58,30,157,211,244,98,217,79,235,48,239,0,45,138,40,219,27,118,176,
6,134,240,48,166,38,8,216,198,129,208,194,173,153,231,35,202,0,207,103,149,82,34,2,34,32,34,34,2,30,145,16,83,252,168,42,93,229,90,150,70,67,25,150,71,0,208,16,76,178,178,40,204,146,60,53,163,201,92,239,
92,107,96,214,58,150,128,231,193,33,121,181,166,163,168,172,169,117,29,35,203,91,156,100,45,52,210,111,113,116,142,46,118,84,214,185,154,240,84,75,44,242,25,37,203,158,238,114,74,180,198,61,195,105,28,
172,195,40,179,201,28,5,239,183,91,65,126,92,204,133,53,211,204,140,85,182,218,249,92,210,246,144,122,194,221,244,253,135,112,25,110,23,174,197,104,14,112,118,206,1,91,92,48,54,6,0,214,140,171,19,113,
106,146,150,42,118,97,173,25,1,94,198,57,85,4,61,38,57,234,130,10,52,129,229,84,71,10,223,149,113,23,90,66,43,91,176,174,181,192,160,110,29,32,32,168,39,105,200,88,155,229,234,158,138,51,28,103,116,174,
227,132,88,189,120,186,197,111,136,187,33,207,35,134,173,93,175,170,184,78,103,168,113,100,68,240,208,84,71,79,53,76,134,122,199,18,9,203,65,248,94,240,214,49,185,140,112,16,198,155,245,6,18,26,54,55,
44,199,107,193,162,110,142,167,153,180,210,28,49,222,86,195,119,124,83,220,77,20,160,18,225,194,209,174,20,211,218,238,50,55,4,12,229,165,21,214,152,239,82,38,150,249,82,121,32,15,29,172,22,145,186,54,
186,222,34,115,191,204,104,249,89,192,113,129,229,17,69,96,145,244,146,71,31,14,112,225,97,236,150,104,169,156,233,230,105,245,179,149,156,112,200,81,184,244,6,80,208,16,123,56,10,14,92,204,56,127,10,
160,214,145,146,221,165,67,195,177,199,72,139,208,207,134,8,203,3,91,217,33,107,186,230,208,203,133,27,170,162,104,47,96,246,254,214,117,164,143,113,30,48,160,99,210,119,169,203,79,132,93,114,107,61,92,
148,23,6,200,236,183,7,5,117,26,42,145,83,76,201,50,14,225,225,107,154,135,76,71,80,215,77,69,193,237,120,52,221,233,182,146,234,75,155,136,112,235,40,55,74,218,136,169,41,221,81,46,3,64,242,185,126,178,
212,147,92,36,48,64,237,177,99,28,41,214,122,154,123,133,71,161,72,226,32,253,45,88,99,39,14,207,202,0,200,110,220,231,246,129,74,34,8,136,130,20,128,78,112,51,250,242,163,110,252,51,4,130,120,199,202,
223,116,54,145,124,179,50,178,181,132,159,232,110,59,64,208,154,70,73,102,101,93,72,62,161,193,107,127,75,182,216,109,194,138,152,2,0,36,116,172,88,45,17,209,192,28,230,12,248,89,166,231,142,48,16,79,
133,33,17,1,17,16,17,17,1,17,16,16,244,136,80,80,226,119,227,250,113,202,211,53,221,223,108,70,146,23,0,72,236,30,86,215,114,159,208,163,145,254,112,185,93,198,79,185,173,146,73,14,72,56,8,215,51,107,
28,248,250,39,59,143,159,42,166,196,59,219,149,232,219,206,227,208,70,224,60,133,151,76,197,17,64,102,120,104,200,254,22,195,107,163,221,35,24,27,192,237,121,236,20,193,251,229,35,241,91,37,162,16,220,
188,133,18,214,66,154,38,197,24,13,24,87,121,39,57,42,24,114,9,82,22,163,157,169,8,160,41,85,17,253,149,37,163,4,229,86,160,140,240,130,193,7,60,42,61,77,174,32,248,87,220,54,44,85,109,92,44,115,220,215,
114,16,77,246,185,244,244,5,209,227,121,249,90,173,167,254,166,169,242,206,55,156,249,89,107,220,230,162,215,234,1,192,88,173,60,57,122,44,101,216,0,39,250,191,71,194,142,129,0,112,84,183,202,131,218,
43,68,212,117,159,109,171,161,39,245,218,202,235,75,80,171,182,199,93,8,37,196,2,112,181,47,168,115,185,151,246,72,70,48,66,232,218,102,86,86,233,248,183,251,134,220,96,160,230,214,27,139,173,247,16,224,
113,24,56,57,93,66,150,161,181,52,236,157,132,16,225,149,206,117,109,161,214,234,247,63,24,137,199,43,55,161,110,249,205,36,199,207,179,248,68,110,127,211,199,106,130,118,135,15,24,224,142,242,165,174,
252,156,58,64,73,36,6,227,111,37,17,194,245,39,213,27,213,151,88,75,69,89,74,62,217,142,195,59,247,15,218,233,154,51,89,91,117,5,27,12,21,49,178,108,114,215,149,136,250,171,161,98,212,84,226,182,143,211,
108,224,119,128,184,45,101,29,235,74,92,140,153,145,141,99,187,7,130,131,235,141,195,111,57,63,177,209,80,119,17,146,6,197,198,254,158,253,87,100,134,58,75,163,128,28,12,149,213,163,187,80,75,68,107,161,
156,24,136,202,15,85,93,76,84,144,185,242,16,198,0,185,30,178,185,83,220,174,37,208,53,160,55,140,133,237,213,218,158,123,132,230,42,98,68,64,224,225,106,195,104,39,30,123,68,208,100,48,180,19,207,148,
24,232,12,127,246,165,71,148,37,74,34,34,161,72,4,144,51,146,122,194,129,201,198,51,158,22,235,161,116,148,181,47,109,77,92,68,198,78,70,80,92,208,90,93,245,51,54,162,161,133,195,112,195,72,227,249,93,
182,205,105,134,150,38,59,25,112,28,2,56,10,214,158,180,67,73,11,14,192,208,7,28,44,206,223,126,65,225,5,192,222,49,148,194,144,136,8,136,128,136,136,8,136,128,136,136,41,67,209,79,40,161,90,214,185,169,
48,219,27,30,72,115,191,107,65,7,178,123,43,104,250,137,57,251,152,226,207,1,106,91,137,115,191,158,22,93,120,248,187,185,72,32,184,15,144,172,228,252,133,44,119,189,164,30,187,70,219,141,138,17,21,144,
56,129,146,229,149,163,27,98,35,229,120,105,65,22,104,24,59,39,43,32,194,208,214,129,240,181,203,159,75,161,221,41,14,86,114,114,113,210,144,85,114,175,72,235,180,193,3,35,181,97,174,42,227,100,69,78,
224,123,84,77,43,98,141,211,110,13,13,28,229,91,173,171,134,146,153,211,72,224,22,155,91,112,154,245,57,134,41,118,68,56,36,30,209,99,215,116,188,79,113,145,208,80,228,68,56,115,148,65,79,233,53,205,113,
39,35,207,42,170,106,120,224,135,107,125,132,119,251,87,71,185,174,221,222,56,66,188,247,86,134,91,123,225,120,236,0,97,228,47,125,92,70,122,79,72,246,188,54,120,253,25,28,206,123,69,140,152,57,207,242,
167,132,242,136,205,105,55,77,45,83,120,190,9,170,65,17,3,255,0,11,117,181,91,227,183,82,8,33,229,184,87,160,168,49,130,221,161,195,229,122,35,49,158,143,104,48,218,162,216,202,251,107,226,0,23,129,149,
203,97,116,246,235,129,7,45,49,187,31,217,118,146,192,55,30,201,92,255,0,95,217,94,209,247,112,179,156,115,132,88,216,244,253,115,43,232,3,243,239,3,175,149,145,11,155,105,27,171,169,42,219,30,125,190,
65,93,30,57,26,246,135,180,228,17,148,42,162,56,192,194,213,181,126,157,163,184,181,194,104,216,114,63,210,22,210,224,72,199,89,94,59,204,145,65,111,124,146,17,144,60,148,71,205,250,191,65,255,0,134,215,
137,104,158,67,28,236,158,122,43,49,102,251,218,42,51,78,234,135,144,91,209,113,194,204,95,238,6,186,103,52,14,26,238,22,48,2,237,197,220,28,112,130,70,83,253,144,116,165,4,114,164,34,143,25,65,42,59,
119,28,191,192,66,113,223,252,45,191,68,105,131,93,80,218,138,150,56,15,8,42,208,218,102,122,201,153,87,60,121,0,240,210,59,93,191,78,218,34,162,167,97,115,60,116,169,211,182,86,81,83,183,44,13,62,7,202,
207,17,200,231,128,130,166,99,28,14,20,224,40,10,80,17,17,1,17,16,17,17,1,17,16,17,17,5,62,84,166,17,7,56,250,144,253,183,22,173,76,203,201,91,55,213,82,97,172,141,254,10,210,93,63,184,228,255,0,11,24,
235,195,223,234,41,100,152,121,229,99,126,224,124,160,168,203,206,74,99,110,155,108,156,73,108,135,158,150,77,174,233,106,58,98,171,125,40,102,127,19,194,218,65,195,65,253,45,71,62,151,131,249,41,234,
43,1,220,149,5,255,0,194,174,86,47,250,152,81,235,227,165,230,115,206,21,162,226,120,69,96,190,160,154,167,208,23,66,227,129,222,22,137,166,110,239,163,184,1,35,142,210,121,202,234,149,16,178,104,95,78,
241,184,17,217,92,171,86,219,36,183,85,185,205,97,13,39,112,40,177,210,161,153,146,196,42,26,65,4,103,10,177,207,63,43,81,209,87,118,202,198,211,204,225,159,1,109,217,0,156,255,0,100,42,115,130,160,70,
198,251,154,57,78,212,183,132,89,112,206,81,71,88,253,149,61,185,192,30,145,149,39,142,66,169,175,118,56,64,220,142,249,78,129,7,25,253,32,189,21,64,252,92,166,174,142,42,234,89,32,112,7,35,33,121,241,
253,148,181,207,104,200,113,198,81,99,147,223,104,38,182,92,165,104,4,12,240,86,231,162,174,237,169,165,244,164,119,188,12,12,172,142,160,180,193,118,139,203,101,241,143,43,69,185,71,85,165,106,219,43,
154,75,114,133,174,147,85,81,29,37,59,164,157,224,52,12,246,185,94,177,212,146,92,101,125,53,59,203,88,211,133,107,82,106,153,238,193,141,136,150,48,142,112,86,187,180,100,159,39,178,136,150,245,242,124,
169,80,6,20,160,34,167,37,72,63,40,37,82,238,6,224,9,57,198,16,56,30,0,57,253,173,179,68,233,153,174,85,45,154,86,56,70,211,214,59,65,119,67,233,103,215,78,218,153,216,118,31,4,46,219,166,236,145,82,211,
96,196,6,58,225,81,165,236,204,164,128,110,140,53,173,28,112,182,48,56,227,128,130,35,104,218,7,194,171,106,134,241,194,169,0,12,34,34,2,34,32,34,34,2,34,32,34,34,2,34,32,40,62,84,170,95,210,13,11,234,
237,31,169,106,101,72,237,171,145,26,188,249,235,133,244,46,167,160,255,0,16,179,84,211,224,18,90,112,190,104,187,7,209,92,100,164,127,181,204,113,28,249,71,78,89,3,83,251,81,247,96,30,214,12,213,255,
0,221,37,220,129,194,183,247,184,110,220,246,178,214,186,54,141,184,230,80,204,246,186,69,60,187,226,111,240,184,5,142,236,218,90,216,195,156,64,207,202,237,26,110,226,202,202,54,22,159,10,198,107,47,
156,19,252,170,75,148,18,51,194,100,42,194,146,228,104,37,220,41,8,136,128,114,237,195,176,177,26,158,216,46,148,15,104,96,245,27,231,244,179,24,80,120,63,163,193,66,56,204,111,150,215,113,32,126,76,43,
165,88,235,217,112,160,18,142,192,25,88,13,127,101,216,239,188,133,191,206,2,196,105,11,169,161,172,16,60,255,0,148,238,255,0,148,105,209,135,37,165,84,173,195,32,123,114,222,90,238,65,87,17,16,239,199,
63,181,231,184,77,246,148,51,84,31,1,122,7,50,109,61,21,225,189,49,175,180,84,196,243,198,17,26,158,152,250,139,106,184,85,190,146,162,64,217,3,203,71,63,5,111,49,190,55,198,31,25,220,215,116,87,204,26,
159,75,92,173,181,242,87,80,181,229,187,139,178,211,251,89,141,11,245,54,233,107,149,180,181,207,204,64,225,193,220,148,31,68,160,25,56,7,145,206,22,15,78,106,75,93,234,6,77,73,48,245,72,247,52,149,150,
170,168,138,154,7,79,43,131,64,65,53,85,48,211,64,234,185,206,198,51,181,202,181,174,160,117,222,164,177,152,123,1,192,254,21,122,211,82,77,95,82,105,161,113,244,115,142,15,11,87,30,80,48,124,0,0,237,
74,34,2,34,32,164,121,78,60,158,20,129,191,45,119,31,11,116,250,125,166,159,112,120,170,171,143,217,25,246,130,59,248,65,227,209,250,94,170,225,35,102,171,143,108,89,246,159,149,219,244,181,146,58,72,
24,226,192,198,183,129,199,105,97,177,178,32,202,154,150,109,216,61,172,28,15,246,91,27,63,30,176,15,65,5,96,0,221,173,3,106,168,5,13,82,128,136,136,8,136,128,136,136,8,136,128,136,136,8,136,128,136,136,
10,151,116,85,74,15,72,45,225,216,0,142,248,114,225,159,94,244,164,148,225,215,138,40,207,239,106,238,235,195,121,183,211,221,40,37,162,168,96,115,94,211,140,142,145,117,241,131,170,100,24,60,151,17,200,
80,234,151,19,159,43,97,250,145,166,106,116,237,250,104,222,15,162,247,18,211,142,2,213,130,152,178,175,10,151,135,135,249,11,164,253,50,212,206,14,20,210,59,7,165,204,60,175,93,186,174,90,26,150,79,19,
136,0,140,163,79,168,169,164,19,68,215,55,158,57,85,103,146,62,22,163,160,47,237,174,164,99,92,241,187,128,183,2,79,36,0,83,83,202,66,35,122,69,88,20,99,57,7,165,40,17,99,207,87,74,202,170,115,20,163,
33,114,189,71,108,125,182,184,176,2,25,184,184,21,215,22,7,88,218,197,125,11,165,99,6,246,132,107,24,189,21,120,251,170,127,182,148,128,91,195,127,107,102,200,206,60,174,75,65,60,214,218,241,201,105,105,
228,46,155,103,173,142,178,137,143,105,203,128,229,18,199,183,250,185,233,90,169,129,149,17,73,12,135,13,112,224,171,164,229,70,17,138,213,231,183,69,0,117,60,140,18,177,222,72,233,115,237,103,244,230,
146,172,73,61,8,217,33,231,130,187,5,202,3,53,49,44,111,188,44,5,92,130,40,93,185,205,220,7,57,69,124,253,105,134,253,97,187,122,84,178,61,161,174,249,93,6,183,81,220,174,22,230,83,206,226,210,6,28,114,
188,151,183,9,110,15,45,13,7,61,175,43,73,61,248,65,57,195,54,231,39,201,80,20,162,2,34,32,140,243,132,39,130,124,40,120,14,102,199,117,156,229,108,90,71,79,205,117,168,107,223,25,20,205,239,35,180,21,
232,253,57,37,210,102,201,59,28,216,129,224,174,237,165,44,209,209,209,179,252,176,3,127,31,218,177,164,172,49,83,83,55,49,6,180,1,142,22,208,26,208,0,111,0,120,65,59,79,124,31,210,0,238,73,255,0,248,
171,29,34,8,106,148,68,4,68,64,68,68,4,68,64,68,68,4,68,64,68,68,4,68,64,68,68,17,133,28,7,115,254,234,165,75,187,31,202,13,27,234,198,147,139,80,233,233,222,200,255,0,234,154,61,152,29,175,150,107,169,
39,162,157,212,243,176,181,237,113,111,63,165,246,225,0,185,217,32,183,200,92,27,235,222,139,49,73,254,45,67,24,108,125,187,1,22,56,184,32,31,218,109,246,237,201,194,110,240,71,62,84,130,163,109,147,68,
95,31,111,184,50,55,59,13,200,242,187,221,130,185,149,180,173,120,120,57,1,124,192,210,67,193,103,228,60,174,161,244,191,82,109,34,150,119,158,56,81,93,127,162,126,20,255,0,10,221,59,196,209,110,29,97,
84,193,128,86,156,149,40,242,165,16,17,192,147,187,0,131,198,60,34,158,54,237,5,13,115,205,127,101,52,243,26,216,90,118,159,203,142,151,147,69,93,254,218,163,237,229,198,194,124,246,186,37,194,149,149,
148,175,167,120,14,36,112,185,61,230,138,91,85,212,130,48,55,100,35,124,205,142,166,194,28,3,193,203,8,200,42,91,238,4,14,15,140,172,6,146,186,253,237,55,160,227,239,105,192,31,165,152,174,169,138,158,
19,52,231,99,88,137,98,186,170,152,232,224,146,89,220,1,3,175,11,145,106,27,188,149,21,211,122,50,97,132,248,43,217,172,53,36,183,25,204,116,239,62,152,227,130,181,102,142,73,206,126,81,149,79,203,221,
185,221,168,31,198,20,162,2,34,32,0,73,192,237,83,184,22,238,110,112,59,202,151,117,222,22,123,73,105,218,139,189,67,93,43,118,83,131,223,202,11,154,59,78,205,117,170,108,146,53,194,16,122,199,107,182,
233,93,63,29,52,96,186,61,145,180,116,7,106,157,33,167,153,71,19,92,90,26,198,240,56,237,109,140,110,195,181,163,218,130,227,26,3,64,111,3,28,5,59,66,145,210,32,4,68,64,68,68,4,68,64,68,68,4,68,64,68,
68,4,68,64,68,68,4,68,64,68,68,4,68,65,65,237,120,47,86,232,110,150,201,169,42,3,75,30,220,12,133,144,32,170,26,194,214,236,236,103,57,65,242,31,212,93,47,62,156,190,203,27,154,125,9,29,150,149,173,55,
220,55,56,112,23,213,63,87,116,140,90,138,201,44,177,183,254,162,32,11,113,229,124,187,112,164,150,138,178,106,89,73,105,99,177,130,20,88,177,187,224,96,101,122,173,213,110,162,174,108,236,39,251,21,228,
105,14,110,215,120,64,72,31,42,58,71,208,90,6,254,203,133,27,88,93,238,192,91,120,36,143,210,249,215,66,222,229,183,87,181,175,126,216,201,237,119,171,29,123,42,232,218,240,236,238,8,205,140,130,144,158,
51,225,2,177,140,19,8,132,227,181,68,28,14,86,185,174,109,76,172,162,51,128,1,104,206,112,182,50,230,129,147,210,215,245,93,192,50,137,241,51,144,66,44,184,229,244,23,255,0,240,187,134,6,114,195,133,232,
212,250,162,123,179,4,108,203,70,60,21,131,185,71,25,170,123,131,114,73,201,86,156,7,27,80,208,117,251,82,129,17,4,29,20,70,249,31,221,5,37,72,60,23,1,253,148,30,70,124,45,183,76,105,23,87,22,214,214,
60,196,193,140,55,188,160,199,105,59,20,247,90,150,186,72,220,218,124,242,74,238,58,79,79,197,13,60,99,104,107,90,62,59,84,105,59,4,108,137,135,211,219,16,253,99,43,113,99,3,26,24,198,128,209,229,5,113,
177,173,96,96,3,1,84,161,190,84,160,34,34,2,34,32,34,34,2,34,32,34,34,2,34,32,34,34,2,34,32,34,34,2,34,32,34,34,2,34,32,40,61,41,66,130,211,192,45,33,195,32,240,66,224,255,0,94,180,67,160,155,252,106,
129,159,229,246,224,208,187,217,104,1,120,47,54,248,110,86,201,232,230,96,123,92,211,140,168,177,241,73,236,159,39,180,11,106,250,147,166,102,211,247,201,26,99,112,129,249,112,56,253,173,87,24,35,61,30,
147,27,149,91,30,230,179,115,14,28,10,234,95,76,53,46,230,50,150,121,57,235,146,185,95,32,156,47,85,162,178,74,26,198,76,195,128,10,141,253,125,73,11,219,36,45,45,57,200,85,3,158,62,22,165,160,239,204,
184,209,177,165,205,220,7,202,219,7,68,249,37,88,231,212,84,160,145,158,83,39,110,124,175,45,76,251,71,9,172,45,215,84,6,100,2,180,141,77,82,231,53,195,60,44,253,202,163,45,114,212,47,50,110,107,178,85,
70,163,87,255,0,124,171,74,186,130,61,98,173,160,15,42,80,40,224,119,210,42,85,59,67,203,155,156,28,101,79,1,155,156,71,233,101,116,221,142,123,181,99,64,5,177,121,112,65,232,209,214,41,110,213,177,57,
204,34,54,158,120,237,119,235,37,138,146,58,102,111,102,30,208,48,22,39,68,105,248,233,97,102,216,246,199,31,100,142,74,221,26,214,142,154,63,69,4,196,208,214,134,237,219,142,130,185,181,82,209,206,73,
36,170,208,0,194,34,32,34,34,2,34,32,34,34,2,34,32,34,34,2,34,32,34,34,2,34,32,34,34,2,34,32,34,34,2,34,32,34,34,8,61,42,120,239,42,163,210,132,88,209,190,171,233,24,181,14,158,152,70,209,247,12,4,180,
227,156,47,150,110,52,210,81,85,190,150,95,202,23,16,87,219,143,3,39,112,203,72,193,92,55,235,183,211,175,94,23,223,108,241,23,76,57,44,104,237,7,15,14,242,128,231,160,176,50,87,79,79,82,234,121,65,14,
105,195,129,249,242,161,183,86,189,228,140,179,111,237,101,189,116,125,7,126,125,182,189,177,189,196,2,126,87,120,179,214,182,174,149,178,180,228,16,190,66,101,220,140,57,175,25,105,237,117,191,165,122,
242,19,35,40,234,38,192,224,114,81,45,215,106,158,93,167,1,99,170,230,28,171,130,88,234,97,50,66,240,230,184,103,33,99,170,222,224,210,28,81,156,99,238,18,131,158,86,179,116,120,33,203,55,88,243,181,199,
28,124,173,122,188,228,57,88,53,201,177,234,156,42,85,83,1,235,17,158,85,14,60,96,183,42,162,84,30,186,207,233,67,67,136,196,92,255,0,61,255,0,178,216,116,238,151,168,184,189,146,84,70,246,195,219,156,
125,168,60,90,106,203,61,218,165,160,70,75,1,93,191,71,105,136,32,137,131,102,200,219,203,142,59,42,52,110,156,100,16,176,53,129,173,111,156,45,226,56,219,27,3,0,0,15,210,8,141,140,99,67,88,54,237,232,
124,171,192,112,141,1,74,10,71,106,164,68,4,68,64,68,68,4,68,64,68,68,4,68,64,68,68,4,68,64,68,68,4,68,64,68,68,4,68,65,64,32,244,84,142,213,47,24,233,76,103,35,246,130,180,68,64,68,68,3,210,167,149,82,
32,160,131,159,254,149,6,38,186,55,71,35,3,154,124,16,174,158,209,7,12,250,207,244,62,135,81,68,250,251,33,251,58,177,147,177,191,212,87,202,154,191,73,234,189,47,87,36,21,244,51,24,218,113,189,160,144,
191,71,27,217,192,88,203,213,138,209,117,167,124,53,246,248,103,14,236,22,140,149,49,117,249,159,254,45,36,78,44,123,92,210,59,4,97,95,162,212,114,82,206,36,129,228,61,167,231,11,238,93,65,244,23,65,94,
92,247,190,217,37,60,142,242,194,2,210,171,191,244,175,166,36,46,251,122,201,153,158,183,18,83,13,115,143,165,191,88,217,19,91,73,114,147,0,113,156,101,119,43,93,238,209,124,128,24,39,143,220,1,224,133,
207,106,63,244,163,3,65,251,59,195,227,63,57,43,209,108,250,1,172,108,143,14,183,234,70,60,15,4,57,49,125,55,122,219,5,76,140,116,148,175,245,91,254,156,225,107,151,43,37,209,129,217,165,119,246,57,89,
203,86,147,250,133,111,45,107,238,48,205,129,248,150,158,86,106,10,45,108,207,108,141,165,119,243,25,85,53,202,133,134,237,36,174,63,100,252,231,181,147,182,104,123,133,67,247,214,59,208,103,242,186,117,
61,167,84,206,240,217,93,71,14,127,252,101,102,104,116,180,191,251,141,75,166,253,70,236,127,242,136,209,236,58,86,215,70,240,125,7,87,84,255,0,75,177,181,163,251,45,238,209,98,149,251,95,88,27,27,71,
226,198,12,5,158,162,160,165,163,96,108,81,2,124,103,181,233,105,240,225,131,225,2,158,38,195,16,141,141,0,5,81,7,249,85,142,145,4,53,74,34,2,34,32,34,34,2,34,32,34,34,2,34,32,34,34,2,34,32,34,34,2,34,
32,34,34,2,34,32,140,140,225,11,128,237,14,21,183,101,221,32,185,181,65,110,223,114,169,67,134,70,16,64,118,84,131,149,70,220,40,25,65,117,70,85,33,248,83,184,32,156,169,84,151,55,10,157,205,249,65,94,
63,105,129,242,168,220,223,148,220,223,148,21,17,159,234,71,49,142,252,128,42,157,205,249,77,205,249,65,83,90,26,48,14,20,224,124,170,55,55,229,55,55,229,5,120,24,80,26,0,192,225,83,185,191,41,185,191,
40,43,0,14,249,77,173,248,10,141,205,249,77,205,249,65,89,0,140,42,61,40,255,0,210,19,115,126,83,115,126,80,86,0,29,112,132,3,255,0,237,81,185,191,41,185,191,40,46,4,86,247,55,229,55,55,229,5,196,86,247,
55,229,55,55,229,5,196,86,247,55,229,55,55,229,5,196,86,247,55,229,55,55,229,5,196,86,247,55,229,55,55,229,5,196,86,247,55,229,55,55,229,5,196,86,247,55,229,55,55,229,5,196,86,247,55,229,55,55,229,5,196,
86,247,55,229,55,55,229,5,196,86,247,55,229,55,55,229,5,197,25,84,110,111,202,144,230,255,0,40,42,202,114,163,112,77,216,64,201,66,224,59,42,146,239,142,212,6,18,114,80,73,118,238,148,176,97,48,60,42,
128,65,255,217,0,0};

const char* JuceDemoPluginAudioProcessorEditor::kreps_logo_jpeg = (const char*) resource_JuceDemoPluginAudioProcessorEditor_kreps_logo_jpeg;
const int JuceDemoPluginAudioProcessorEditor::kreps_logo_jpegSize = 11931;

// JUCER_RESOURCE: chickknob_png, 8824, "../../../Desktop/chickknob.png"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_chickknob_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,120,0,0,0,120,8,6,0,0,0,57,100,54,210,0,0,0,9,112,72,89,115,
0,0,11,19,0,0,11,19,1,0,154,156,24,0,0,0,4,103,65,77,65,0,0,177,142,124,251,81,147,0,0,0,32,99,72,82,77,0,0,122,37,0,0,128,131,0,0,249,255,0,0,128,233,0,0,117,48,0,0,234,96,0,0,58,152,0,0,23,111,146,95,
197,70,0,0,33,238,73,68,65,84,120,218,236,125,121,140,93,215,125,222,119,150,123,223,50,43,135,195,77,92,68,145,20,105,137,162,72,73,150,184,152,50,36,138,108,2,3,241,31,74,29,52,50,160,0,70,139,194,72,
155,34,73,91,180,5,10,187,104,145,162,70,81,255,17,160,9,208,58,168,157,34,168,131,218,40,170,216,46,224,45,145,28,145,116,101,114,108,137,187,184,136,203,80,179,191,229,190,187,156,123,150,254,113,239,
185,115,222,229,12,73,39,172,56,51,122,7,24,112,248,230,206,125,111,206,119,127,219,247,91,14,49,198,160,183,86,238,162,189,45,232,1,220,91,61,128,123,171,7,112,111,245,0,238,173,30,192,189,245,75,46,
190,18,255,168,201,169,73,252,239,191,248,11,124,255,251,223,199,248,237,219,95,63,122,244,232,127,251,252,107,175,221,90,183,97,61,222,59,115,6,127,252,159,255,232,223,92,60,127,254,55,15,31,60,132,191,
251,185,207,97,255,254,253,61,128,151,211,50,6,136,147,4,157,48,4,99,236,83,213,106,245,117,198,24,40,99,168,214,170,48,4,178,25,180,191,52,61,55,123,113,110,118,182,167,162,151,219,138,146,24,113,28,
163,211,233,32,142,227,129,56,142,209,104,54,145,138,20,34,17,208,90,115,101,244,209,153,185,89,220,188,117,19,65,59,232,1,188,156,86,163,209,192,228,212,20,140,49,251,146,36,89,21,134,33,148,209,208,
70,131,113,14,74,41,168,198,43,65,171,141,201,233,25,52,91,205,30,192,203,105,37,113,130,48,83,207,85,66,136,23,37,49,40,165,96,156,67,74,9,10,2,70,233,110,24,32,8,218,152,107,53,122,0,47,43,9,110,53,
160,148,130,16,98,91,39,10,161,148,130,82,10,158,231,161,94,173,194,247,60,40,165,182,7,157,160,62,55,55,135,217,153,217,30,192,203,105,181,115,155,170,140,62,148,36,9,226,56,134,54,6,140,16,112,74,161,
164,68,28,199,60,77,211,151,166,166,166,112,227,198,13,180,218,173,30,192,203,97,77,76,77,161,213,110,131,80,2,74,233,6,165,20,130,32,128,150,10,144,10,90,105,196,113,12,165,20,8,33,47,38,73,130,70,163,
1,41,101,15,224,229,176,98,145,32,85,41,140,49,80,74,237,74,83,9,33,18,76,220,190,141,48,138,80,171,213,80,171,213,64,8,1,99,236,5,33,4,90,173,22,68,154,246,0,94,14,203,247,43,96,148,195,24,131,36,73,
214,104,173,0,13,244,85,171,80,74,129,82,10,41,37,164,148,8,195,240,133,137,137,137,250,228,228,36,110,221,186,213,3,120,121,216,223,54,154,205,6,162,40,58,160,181,26,38,198,0,198,160,90,171,161,94,175,
67,74,137,106,181,10,207,243,144,36,73,63,165,116,245,220,220,28,166,166,166,122,0,47,135,53,219,156,69,28,199,8,163,168,166,164,242,125,206,161,164,196,224,240,48,140,49,240,125,31,140,49,120,158,7,0,
168,84,42,27,231,230,230,48,57,57,217,3,120,57,172,233,233,41,36,73,2,37,37,148,72,65,41,7,33,4,90,41,164,105,138,190,190,62,84,42,21,40,165,192,24,131,148,242,139,73,146,96,124,124,188,7,240,114,88,173,
217,38,162,48,2,180,217,71,8,133,16,9,162,40,194,220,220,28,140,49,72,211,20,113,28,99,98,98,2,105,154,66,8,241,28,0,52,155,77,76,207,206,244,0,94,218,210,59,141,36,140,160,68,130,36,142,14,39,137,0,231,
28,140,49,48,198,96,140,129,148,18,157,78,7,190,239,163,211,233,32,8,130,199,130,32,192,212,212,20,166,38,38,123,0,47,229,37,68,138,118,187,9,173,4,164,136,247,38,73,12,74,25,8,33,144,82,130,115,142,48,
12,193,57,135,239,251,160,148,130,16,82,79,211,20,183,110,221,194,181,15,174,117,221,175,217,110,247,0,94,82,49,112,28,34,8,219,104,7,109,104,163,215,112,78,33,101,2,206,57,180,214,72,146,4,132,16,212,
235,117,84,42,21,248,190,15,207,243,32,165,220,217,108,54,49,57,61,221,117,191,161,129,129,30,192,75,105,5,97,11,137,72,32,165,217,169,148,169,82,74,224,121,12,113,28,131,16,2,0,72,211,20,74,41,0,128,
214,26,74,41,116,58,157,215,218,237,54,198,87,96,44,188,162,0,158,156,154,128,16,18,140,121,27,211,52,245,195,48,68,187,29,64,169,20,105,154,98,116,245,40,40,165,208,90,131,82,90,0,45,165,252,123,141,
70,3,231,206,157,195,119,190,247,93,156,191,112,30,147,211,43,195,30,175,136,138,142,107,215,175,226,194,197,115,248,233,79,127,138,201,137,73,36,73,252,68,146,36,144,82,128,82,10,207,171,64,74,9,109,
52,134,134,134,80,171,213,16,134,33,180,214,48,198,192,243,188,71,149,82,56,125,250,52,218,237,54,134,135,135,176,245,177,71,241,244,83,79,99,251,142,29,216,176,254,17,172,25,29,237,1,252,81,174,70,163,
129,139,23,47,226,242,149,11,56,119,238,28,174,125,112,13,73,146,81,144,198,152,103,56,231,224,220,135,148,10,90,107,0,128,49,26,148,18,40,165,11,218,50,73,18,0,168,102,94,117,136,119,223,253,5,146,36,
129,231,49,60,242,200,70,172,93,187,14,251,95,216,143,151,143,188,132,109,219,182,97,116,100,77,15,224,255,223,235,194,133,11,56,125,122,12,199,79,190,141,241,241,235,8,195,8,73,34,80,173,214,0,16,164,
169,56,152,229,127,171,0,4,0,32,12,67,116,194,16,181,106,31,6,7,135,224,251,21,104,45,145,166,89,40,85,169,84,222,247,60,111,135,82,18,156,83,164,169,196,213,171,87,113,230,204,25,156,60,121,28,111,159,
248,107,236,223,191,31,7,15,30,196,190,167,247,97,213,240,72,15,224,7,189,174,92,185,130,177,177,49,188,243,206,59,184,53,126,11,141,230,28,132,136,160,148,129,49,4,74,41,112,206,222,147,50,221,221,233,
132,0,12,8,33,136,162,40,171,232,32,28,179,205,57,68,81,140,138,95,129,84,12,113,28,162,90,53,48,6,219,57,167,239,51,198,191,198,88,245,123,156,243,177,52,77,33,165,68,20,71,56,123,246,44,166,38,166,240,
179,119,222,193,75,47,189,140,67,135,14,97,199,246,29,24,26,28,238,1,252,183,93,183,110,221,194,153,247,206,224,237,227,111,227,250,7,215,49,61,51,5,194,84,110,67,9,140,209,208,90,125,65,74,242,207,61,
143,239,74,211,66,85,219,188,47,124,223,47,238,87,175,213,80,169,84,97,226,4,74,17,120,158,143,161,161,126,164,169,216,110,12,254,128,49,246,7,156,243,219,149,74,229,127,80,74,191,225,121,222,152,214,
26,157,78,7,31,124,112,29,223,252,230,55,113,241,226,69,28,125,229,21,28,56,112,16,235,214,174,239,1,252,55,89,237,184,131,235,87,175,225,228,241,147,120,231,157,159,225,246,237,113,0,6,32,26,82,42,40,
165,71,133,80,127,104,140,254,44,128,186,82,18,74,105,4,65,132,56,78,64,41,69,163,209,128,146,18,21,191,2,207,243,81,175,215,161,181,134,16,41,8,37,168,85,107,200,90,104,9,40,101,72,83,9,198,0,99,204,
6,99,204,239,106,173,127,87,8,241,109,66,200,191,173,213,106,99,150,48,57,115,230,12,102,102,102,240,225,196,4,94,126,249,8,118,238,216,217,3,248,151,89,51,237,6,206,158,63,139,255,123,226,4,206,157,59,
135,91,215,199,81,229,21,72,35,160,180,68,146,164,255,82,74,245,207,140,49,171,140,1,40,37,48,198,32,142,19,84,171,21,192,160,8,135,60,175,2,206,43,72,146,140,244,136,162,236,1,48,26,16,105,2,198,1,41,
21,56,103,72,83,129,56,142,225,121,94,65,115,26,99,94,213,90,191,202,24,59,193,57,255,13,66,200,13,41,37,174,95,191,142,55,222,120,3,173,86,11,127,231,216,175,96,239,211,123,123,0,223,207,186,49,113,19,
63,255,249,47,48,118,122,12,231,206,159,69,24,119,160,161,144,168,24,169,20,95,144,169,252,119,82,202,13,74,101,222,49,165,12,198,0,90,27,164,105,2,74,9,60,223,131,78,52,42,126,21,3,3,67,32,4,32,132,160,
82,169,160,94,175,131,128,32,149,2,82,37,72,18,131,40,10,49,48,48,0,198,56,180,206,226,230,52,77,225,121,30,42,149,74,238,133,155,3,198,152,235,198,152,111,120,158,247,251,90,235,233,70,163,129,183,222,
122,11,237,32,64,146,132,120,225,249,131,61,128,239,182,38,102,39,241,230,155,111,225,212,169,83,184,113,227,6,162,168,147,217,82,45,63,35,37,190,162,181,220,157,57,63,10,198,100,78,20,33,128,82,4,105,
170,51,41,20,153,253,133,201,36,83,136,4,149,74,5,198,24,68,81,12,238,249,16,169,0,165,58,175,176,212,104,183,3,112,238,229,215,1,74,101,118,60,77,179,242,31,155,172,200,25,177,215,141,49,199,56,231,175,
86,171,213,19,179,179,179,56,125,250,20,8,128,84,2,159,58,120,176,7,240,130,106,185,57,131,31,255,229,143,113,252,248,241,12,220,56,68,173,94,171,203,88,252,107,163,204,239,41,165,125,165,84,17,219,18,
66,242,12,145,130,214,153,29,101,204,135,76,83,80,66,32,68,6,206,248,248,56,60,207,131,231,121,104,181,2,80,194,192,88,150,128,240,124,191,112,200,40,165,160,148,66,8,9,99,44,157,105,138,178,91,11,178,
214,26,140,177,13,132,144,191,102,140,253,211,138,239,127,53,142,98,188,247,222,89,112,175,130,74,197,199,39,159,125,174,7,112,23,113,17,180,240,179,83,167,240,87,111,190,133,153,153,105,68,113,8,238,
177,157,20,248,163,84,136,35,74,102,155,108,235,169,230,1,33,144,50,179,183,158,199,65,40,129,54,0,167,62,40,229,168,84,42,168,213,234,152,153,153,129,239,251,80,74,67,164,49,64,20,164,82,96,25,88,54,
179,4,33,4,226,56,2,64,192,121,246,26,165,4,90,155,2,92,7,108,106,140,249,79,156,177,237,148,121,255,40,74,18,156,57,115,6,21,223,199,224,192,32,118,62,254,120,15,96,187,78,157,62,133,31,253,240,135,152,
153,153,65,20,133,48,208,7,56,245,255,123,28,196,219,101,170,138,144,71,74,9,165,230,217,169,204,102,26,80,154,149,225,24,165,97,12,96,8,1,144,61,4,213,106,5,190,159,169,94,109,20,154,205,89,248,190,143,
40,138,1,100,182,89,41,85,148,211,198,113,214,9,1,120,200,75,186,64,105,38,205,90,211,162,66,132,100,118,25,0,126,155,104,189,197,72,249,217,185,70,3,167,199,198,48,52,60,140,117,235,215,97,104,96,176,
151,108,56,253,222,24,222,122,235,77,92,187,126,29,50,21,16,105,188,147,0,223,21,177,216,46,18,1,157,83,139,54,19,100,37,73,107,93,216,73,41,211,92,101,211,92,181,42,235,24,33,12,67,124,112,253,6,26,141,
38,130,160,137,185,185,25,196,113,98,75,103,139,207,225,62,64,73,18,35,8,66,36,137,128,16,2,214,238,219,247,19,89,241,60,68,42,17,167,18,97,20,253,90,28,199,95,79,146,4,51,179,179,56,113,242,36,222,62,
254,118,79,130,63,24,191,129,19,39,79,226,226,251,151,16,39,49,164,20,163,156,241,63,151,82,174,74,211,20,218,104,40,157,129,107,65,181,210,11,0,105,42,32,165,66,181,90,7,165,28,30,207,8,141,40,12,33,
68,2,41,21,102,103,155,56,113,226,56,234,125,21,76,79,77,224,210,165,203,136,162,8,253,253,253,96,140,65,8,81,220,47,115,218,8,164,84,160,212,128,16,32,142,51,14,155,115,6,70,41,12,12,168,148,208,158,
7,120,26,58,103,188,36,101,175,123,158,55,198,24,251,234,212,212,20,126,252,151,127,133,145,145,213,216,255,201,231,63,158,0,55,195,22,198,126,126,26,239,190,251,30,90,173,22,82,153,128,49,246,6,52,246,
74,33,161,149,134,204,189,89,43,89,198,24,171,22,97,169,68,198,57,64,12,146,56,132,241,12,170,213,106,94,80,167,65,8,69,16,180,241,163,31,127,31,103,207,253,2,70,27,220,186,117,171,72,248,11,33,208,233,
116,64,8,1,231,60,183,185,180,40,18,200,156,57,192,24,130,52,149,224,140,194,243,24,140,77,59,74,9,195,24,8,0,105,36,180,214,255,209,243,188,63,85,74,77,95,185,114,5,223,255,225,15,48,208,223,143,39,63,
241,196,199,15,224,43,87,174,224,212,169,211,152,156,156,128,76,5,164,146,255,197,40,125,64,37,170,176,179,214,131,181,255,183,224,82,74,11,187,12,66,144,196,17,96,52,24,103,144,146,33,8,66,40,101,224,
251,28,156,19,76,220,254,16,183,110,222,180,137,5,48,198,144,36,73,87,110,88,74,121,71,253,86,182,76,46,221,64,42,83,40,45,225,87,171,128,84,32,68,192,247,188,92,242,41,164,84,84,8,241,19,223,247,63,161,
164,194,205,155,55,113,106,236,52,54,111,222,140,129,190,254,143,143,13,190,245,225,56,198,126,241,115,124,248,225,4,148,76,97,96,94,35,26,95,176,146,155,217,81,93,128,236,74,174,173,206,32,132,100,180,
99,14,20,231,28,3,131,253,160,76,231,42,221,64,27,13,99,20,170,181,10,42,149,10,120,222,31,44,132,64,20,69,0,128,90,173,86,216,98,27,235,218,144,201,190,111,33,217,140,131,144,140,88,97,132,64,105,13,
165,53,12,0,67,0,3,141,68,36,187,226,56,254,86,28,199,152,158,158,198,213,107,215,112,249,234,213,143,151,147,245,222,217,51,56,127,254,60,194,56,0,225,116,148,0,255,193,104,67,137,33,0,193,29,246,214,
110,178,221,240,56,142,33,132,40,72,8,219,173,128,156,182,244,124,130,74,133,129,115,2,33,83,80,202,80,171,213,192,243,30,97,99,12,56,231,69,124,12,32,43,10,40,212,50,41,222,215,74,55,0,168,252,231,70,
101,95,52,151,111,59,16,82,35,115,0,195,48,122,53,140,162,47,71,97,132,203,151,46,227,194,133,11,104,135,225,199,3,224,86,171,141,15,46,95,197,204,212,52,96,12,136,193,191,55,202,108,34,154,116,121,200,
86,45,91,213,156,247,27,33,12,67,132,97,88,80,143,182,12,167,240,112,19,1,101,36,8,51,96,140,130,128,20,106,222,218,115,215,206,10,33,138,7,201,198,195,238,247,246,222,246,1,72,211,20,89,197,136,132,145,
26,40,204,135,134,209,6,6,128,50,10,137,72,126,63,78,146,250,204,236,12,46,93,186,132,219,19,31,126,60,0,190,122,245,10,46,191,127,25,157,70,128,40,136,62,147,68,201,235,70,153,46,181,92,6,216,117,170,
172,132,89,181,105,109,166,82,170,232,90,144,105,246,123,54,182,181,42,221,182,173,248,190,127,135,38,176,247,114,107,169,173,74,183,15,158,125,79,99,12,132,16,25,208,169,132,145,42,3,87,107,208,220,97,
83,90,245,107,163,191,162,181,194,213,171,87,113,233,226,197,143,7,192,151,46,93,66,179,217,4,180,1,209,228,43,90,72,31,133,189,156,103,139,48,79,36,20,113,176,231,121,168,86,171,69,109,179,205,250,104,
173,115,231,137,162,213,238,32,77,37,160,81,72,190,5,203,247,125,112,206,139,123,187,160,149,67,37,66,72,241,126,110,62,217,50,95,153,90,79,33,132,128,20,2,90,72,40,169,160,140,130,129,177,83,6,94,75,
165,172,183,90,45,188,127,249,125,76,124,196,197,124,31,57,192,31,126,248,33,46,93,186,4,33,4,184,207,235,70,171,93,132,18,72,173,186,108,160,221,124,11,144,148,178,75,122,236,166,91,175,152,82,138,90,
173,138,185,185,6,154,173,118,166,250,41,41,164,214,218,111,123,127,75,154,88,103,202,106,15,171,230,173,74,207,139,242,138,135,202,126,30,247,247,100,154,66,36,9,210,84,64,43,5,41,100,241,217,163,40,
90,21,39,201,63,76,100,138,169,201,41,76,78,77,175,108,128,207,157,59,135,241,241,241,60,110,84,95,81,70,113,233,48,72,229,144,200,170,94,91,153,81,150,72,171,74,125,223,71,146,8,76,79,207,66,43,9,98,
255,192,92,237,206,39,38,100,17,26,185,146,235,50,99,66,136,66,253,90,251,204,24,43,188,240,178,183,13,0,218,122,249,90,67,167,18,58,157,215,64,82,202,223,22,73,130,243,151,46,224,103,167,126,182,178,
227,224,155,55,111,66,136,4,169,78,161,100,250,57,91,94,83,166,32,93,41,182,44,150,221,80,107,67,61,207,67,28,199,8,130,44,213,167,117,102,23,149,202,18,9,86,157,90,112,173,147,229,18,26,238,64,116,247,
161,178,82,154,209,150,89,186,209,243,188,34,196,178,159,215,2,92,132,84,214,243,150,18,212,48,16,70,1,130,237,132,144,3,34,17,39,174,188,127,121,101,75,240,245,235,215,33,82,1,99,204,1,41,213,218,178,
211,228,46,43,113,110,88,99,25,40,75,84,4,65,27,51,51,51,8,130,14,58,157,176,0,209,221,124,11,158,205,2,89,192,221,152,218,13,137,92,167,204,254,174,117,240,56,231,69,72,230,222,199,125,56,243,23,192,
9,1,37,4,4,4,220,243,126,35,137,34,164,89,153,238,202,5,120,118,110,6,32,128,82,234,171,46,51,229,74,153,125,221,214,45,103,169,64,15,125,125,125,240,125,31,132,144,28,220,0,237,118,0,198,120,65,92,88,
233,114,157,37,151,172,176,132,134,235,72,149,191,40,165,133,93,119,63,151,181,205,214,89,179,13,108,238,3,226,106,1,16,2,78,25,140,148,144,34,253,226,112,255,32,218,173,246,202,6,120,110,110,14,82,74,
36,73,242,180,149,52,87,202,92,41,176,223,83,74,139,198,109,11,110,167,211,65,24,134,185,100,123,197,245,46,11,85,94,94,65,41,146,46,54,204,94,111,189,99,171,33,172,180,187,210,109,181,138,37,72,202,164,
136,251,55,104,173,161,85,54,217,71,138,164,154,196,241,103,226,56,94,217,0,115,143,129,115,190,83,74,89,119,71,23,185,113,175,149,22,11,160,239,251,168,213,106,69,220,26,134,33,162,40,202,157,159,121,
123,106,55,218,5,199,37,45,236,53,174,164,150,77,130,251,189,123,95,171,166,227,56,70,154,166,5,201,98,89,48,87,213,219,191,65,136,44,211,5,24,104,37,17,198,225,139,169,20,43,27,96,173,13,164,148,175,
89,105,180,53,79,174,247,60,159,227,149,168,84,42,232,235,235,3,99,12,97,24,34,8,130,220,179,53,249,199,39,11,2,179,16,184,174,196,150,99,94,215,185,114,237,176,149,234,50,185,209,206,123,135,171,213,
234,29,30,185,109,141,201,138,2,179,47,66,9,252,154,191,181,221,249,104,85,244,71,238,69,39,73,2,223,247,95,180,182,213,58,69,110,141,149,85,133,181,90,13,253,253,253,168,213,106,8,130,0,179,179,115,144,
50,45,188,96,11,174,235,236,148,37,177,236,188,149,157,42,87,189,186,94,181,155,181,178,68,138,37,92,236,103,23,66,192,243,60,48,198,144,166,105,151,22,201,170,76,144,151,20,41,80,80,120,204,123,194,37,
76,86,36,192,140,49,68,81,244,68,16,4,133,83,228,74,157,149,28,206,57,250,250,250,80,171,213,160,181,70,118,125,152,111,184,119,7,168,174,163,102,255,117,165,214,5,205,189,110,177,107,221,251,115,206,
139,135,142,49,214,101,119,45,229,105,181,79,6,50,0,40,80,58,255,190,82,73,8,33,182,80,70,87,186,138,214,155,149,82,171,109,122,207,218,48,55,36,178,82,99,227,206,249,228,66,54,232,204,142,101,184,219,
42,219,229,178,52,187,106,183,44,217,101,135,207,122,223,243,154,163,155,230,180,172,90,118,189,234,74,92,88,127,32,207,86,213,68,34,234,43,26,96,74,233,106,41,165,239,146,3,54,180,88,8,0,173,117,33,233,
156,251,185,199,108,138,66,118,87,50,93,137,46,219,217,197,254,93,40,254,182,203,58,123,46,77,234,198,197,157,78,167,200,41,103,158,55,135,82,89,254,185,76,145,230,142,89,181,90,173,62,189,162,1,246,60,
127,149,75,32,148,171,52,172,148,216,56,211,198,183,148,178,162,50,210,226,88,142,95,23,115,162,220,127,93,135,232,126,142,245,115,211,137,229,223,205,74,108,51,175,218,74,184,125,248,220,28,179,237,146,
200,193,126,118,69,3,220,223,223,87,243,60,15,245,122,189,216,40,75,9,186,25,36,27,179,134,97,198,78,89,130,195,24,75,36,220,61,172,185,151,164,222,15,184,174,20,186,73,127,91,191,101,105,203,52,181,102,
133,22,206,95,217,121,115,239,179,162,1,110,54,27,69,60,233,38,16,92,206,121,94,61,10,132,97,152,171,107,118,7,160,101,111,185,156,172,47,219,214,133,156,173,251,181,229,246,51,150,223,43,75,78,36,0,52,
40,237,246,37,220,80,203,122,219,0,134,86,180,23,173,82,245,211,52,77,53,33,132,118,135,21,243,234,218,50,73,89,239,175,185,235,115,232,170,247,133,192,185,151,196,150,65,95,236,247,23,211,4,25,136,6,
198,216,82,94,109,99,253,130,98,181,159,45,215,50,31,172,104,9,94,179,102,221,116,197,175,54,181,234,174,125,114,61,206,204,158,49,36,137,0,165,188,203,123,93,104,179,127,25,32,23,251,89,89,173,47,246,
59,214,20,88,31,193,247,189,60,140,202,58,42,8,153,255,59,108,103,162,13,165,114,98,228,236,138,150,96,2,2,206,248,117,16,178,74,107,83,216,51,235,196,100,155,168,161,53,238,40,0,88,76,69,223,175,20,186,
14,221,221,174,187,215,195,112,39,11,166,64,8,7,165,164,0,211,74,174,235,56,74,41,133,117,190,86,172,4,143,172,30,1,99,236,114,214,220,197,139,13,232,14,153,0,41,77,87,113,155,155,33,186,31,27,90,6,179,
252,128,44,6,222,98,215,45,20,146,101,45,172,128,82,243,132,136,77,66,216,193,227,182,120,32,39,110,46,13,13,13,141,173,104,128,251,250,250,16,199,241,79,140,54,224,212,131,214,128,210,170,136,57,179,
148,28,96,76,55,97,224,102,120,202,33,206,98,160,100,125,197,26,166,212,238,114,175,117,55,237,224,250,12,118,200,139,201,251,144,141,33,197,231,115,57,117,75,234,8,33,46,172,91,183,110,101,83,149,195,
195,195,224,156,127,96,116,214,86,2,101,144,230,197,238,153,87,157,121,204,140,117,179,89,174,83,115,175,80,163,11,236,60,164,34,200,10,211,239,21,243,186,247,176,102,163,156,243,45,199,212,22,100,99,
72,110,131,109,181,116,22,15,215,106,53,155,34,253,206,250,245,235,87,54,192,27,54,108,64,127,127,255,155,205,102,51,100,140,213,25,103,240,180,135,138,95,65,154,55,118,51,70,51,240,75,222,181,155,111,
117,59,17,22,5,23,0,49,119,126,191,16,208,46,135,237,170,106,27,202,217,210,220,178,202,158,239,45,166,197,191,132,152,226,111,112,138,20,210,190,190,190,63,121,242,201,39,87,182,13,222,180,105,19,182,
110,221,58,93,175,215,47,73,41,193,189,204,75,102,156,23,167,161,24,163,187,170,26,221,250,44,107,235,238,21,191,254,173,157,193,5,74,121,44,160,229,135,98,62,191,76,138,152,189,82,169,162,86,171,22,69,
1,81,20,253,159,157,187,118,226,224,254,67,43,27,224,245,235,215,99,251,246,237,232,239,239,255,95,4,153,38,75,243,97,99,118,83,221,204,141,85,211,217,104,66,94,56,100,139,217,204,197,164,247,126,94,95,
204,75,118,235,185,92,173,226,74,188,59,37,32,51,8,180,40,179,85,90,97,104,104,232,179,187,159,216,253,81,111,247,71,15,240,170,85,171,176,107,215,46,172,91,183,238,107,204,243,230,24,231,48,57,103,107,
187,251,236,70,185,201,118,183,216,124,49,111,88,107,13,99,59,1,239,193,68,18,147,127,129,220,53,22,46,108,89,30,202,149,251,151,220,248,189,155,210,36,0,88,230,124,1,241,166,205,155,176,123,207,199,0,
96,0,24,29,29,197,234,213,171,111,48,202,190,229,121,30,134,134,6,139,2,54,75,32,44,212,54,82,206,56,45,148,228,39,26,184,95,229,77,74,95,11,37,39,92,222,185,60,172,197,254,204,153,167,85,20,229,101,215,
103,96,247,247,13,254,249,227,59,30,199,99,91,30,253,120,0,188,121,243,102,236,122,226,9,172,94,59,250,61,198,231,11,215,203,229,49,174,115,83,6,183,92,106,3,146,73,163,201,216,194,251,138,121,137,229,
171,187,32,238,6,183,156,36,112,31,60,91,198,107,61,125,155,27,206,38,7,144,188,250,196,195,182,173,143,125,245,153,103,158,195,200,67,152,84,251,208,218,71,247,236,217,141,79,236,218,245,237,90,173,118,
211,37,244,221,46,64,27,63,186,118,183,12,92,17,170,100,21,231,217,53,48,247,69,77,118,121,197,11,0,61,95,99,165,186,210,133,238,61,220,14,139,74,165,130,129,129,1,84,171,213,194,171,30,26,26,122,107,
247,83,187,199,246,60,245,212,67,217,231,135,6,240,182,173,219,176,251,169,221,24,30,30,254,82,206,209,22,5,108,229,184,212,110,160,187,193,229,120,148,146,28,232,18,56,11,213,100,45,102,107,11,120,29,
109,225,214,104,187,15,89,54,189,167,90,164,49,93,117,237,72,179,220,182,109,219,231,247,61,179,15,35,171,70,62,94,0,3,192,222,61,123,177,107,215,174,63,225,156,95,48,198,20,135,101,184,97,144,219,198,
233,134,40,5,72,0,40,33,160,14,201,127,55,112,23,42,227,233,218,144,124,20,131,205,81,187,108,154,11,174,61,228,210,125,16,221,88,29,0,214,175,91,255,63,15,28,56,112,227,241,29,15,111,94,214,67,5,120,
227,35,143,224,211,159,254,52,118,239,222,253,123,181,90,173,200,190,88,187,231,146,245,174,221,179,15,0,193,157,29,9,229,18,89,23,232,197,128,117,127,174,75,221,131,229,210,27,203,78,149,11,22,92,109,
162,148,66,181,90,157,121,254,249,231,255,241,11,47,188,128,225,193,161,135,182,199,15,125,140,210,115,207,60,139,219,183,63,252,110,187,221,254,198,141,27,55,94,119,187,23,144,135,79,182,205,211,2,155,
197,201,128,193,60,101,105,104,119,53,229,66,117,90,11,165,28,187,60,112,100,67,86,104,46,193,158,231,21,92,178,189,198,247,179,145,196,110,87,131,107,62,108,209,224,206,157,59,127,103,255,129,253,211,
91,31,130,231,188,164,0,6,128,231,62,249,28,166,103,166,127,171,221,106,125,106,174,209,216,110,55,63,205,207,244,181,206,151,107,159,179,241,73,4,50,85,160,148,101,46,18,153,47,228,115,231,74,222,79,
121,14,0,40,147,199,209,4,119,140,146,176,132,75,189,94,207,157,168,238,9,3,110,172,188,109,219,182,55,142,29,59,246,103,79,60,249,196,67,223,219,37,49,233,110,195,218,117,56,122,244,40,118,126,226,19,
255,192,247,253,216,142,98,176,45,162,182,220,101,126,67,41,140,81,136,147,236,48,104,165,85,86,101,9,114,135,138,94,172,132,231,14,219,204,40,40,163,249,224,112,175,171,73,220,178,88,181,90,173,171,17,
220,181,249,246,254,219,182,109,187,118,228,200,145,191,127,232,208,33,172,90,2,227,254,217,151,191,252,229,165,128,49,6,7,6,64,61,126,173,221,106,157,110,183,219,159,183,116,165,5,181,187,119,183,212,
114,74,9,24,165,64,1,40,233,42,171,45,59,72,101,144,141,49,160,140,130,81,222,21,135,219,208,200,134,63,182,1,206,190,183,115,60,30,124,223,199,35,143,60,210,58,118,236,216,11,135,95,60,60,190,97,137,
140,249,95,82,227,132,63,181,255,0,56,101,223,173,213,106,223,62,117,234,212,171,246,48,13,151,243,205,200,3,130,74,37,83,147,113,28,103,69,1,74,22,222,47,213,128,210,40,84,182,245,116,23,2,87,231,205,
218,74,166,224,148,131,50,218,85,231,101,109,110,189,94,71,127,127,63,226,56,46,230,129,216,48,170,90,173,98,221,186,117,193,145,35,71,126,253,240,225,195,215,183,108,220,188,100,246,116,201,13,4,223,
255,252,243,224,62,251,117,24,124,253,252,133,243,175,207,206,206,229,32,101,217,26,33,0,74,43,168,213,106,69,215,195,204,204,12,226,36,206,189,112,31,42,85,48,66,194,228,64,26,152,59,138,4,178,89,180,
40,102,79,166,105,138,212,164,240,136,215,21,103,219,218,42,219,244,109,199,253,215,106,181,226,52,151,53,107,214,196,47,189,244,210,111,30,126,241,240,15,30,221,188,101,73,237,231,146,28,233,255,220,
222,103,193,192,126,171,82,173,52,198,198,126,254,59,65,16,228,106,81,35,59,215,136,23,97,138,245,90,41,201,230,97,81,66,161,169,6,229,180,168,159,38,25,143,217,229,49,27,99,178,151,40,1,39,188,139,142,
92,168,21,212,86,103,216,48,206,218,229,141,27,55,138,131,7,15,254,218,177,99,199,126,176,233,145,141,75,110,47,151,236,161,28,251,246,238,5,99,236,159,112,206,59,99,99,99,255,2,80,36,12,85,87,234,208,
102,119,220,129,104,169,204,218,81,9,39,128,34,128,54,243,99,232,156,40,201,144,140,185,54,14,243,229,114,224,214,6,187,157,9,150,185,10,195,16,158,231,225,209,71,31,13,94,121,229,149,95,121,254,249,231,
223,94,138,224,46,105,128,1,96,207,83,79,193,175,248,255,106,96,160,239,202,217,179,103,255,240,234,213,171,85,74,67,248,190,143,106,181,138,32,8,138,80,202,78,191,233,170,189,162,57,166,26,133,3,86,12,
88,33,0,8,5,28,22,170,204,113,151,51,88,22,224,90,173,134,237,219,183,223,60,124,248,240,175,238,63,112,224,204,134,181,235,150,236,30,46,249,131,177,118,61,190,19,171,134,135,255,235,150,205,91,190,115,
252,196,241,111,159,59,119,238,128,37,28,218,237,118,145,194,115,29,49,87,5,27,146,7,131,78,63,83,89,93,219,215,237,255,221,14,134,242,225,90,107,215,174,197,99,143,61,246,163,67,135,14,253,234,51,123,
247,165,3,75,252,140,225,101,113,242,217,218,53,107,177,246,165,35,183,25,99,7,59,97,231,205,86,179,245,162,91,177,232,182,114,186,171,0,48,23,99,3,146,215,122,145,249,14,54,96,65,9,118,29,45,183,46,172,
175,175,239,71,59,118,236,248,204,147,79,62,185,228,193,93,50,68,199,253,174,173,91,183,98,237,154,181,159,174,84,42,111,217,56,121,177,250,172,238,215,114,91,75,178,88,185,139,158,116,120,104,247,53,
151,161,178,78,86,16,4,147,157,78,231,139,190,239,39,163,35,171,151,197,158,45,43,128,163,40,66,146,36,48,198,252,177,203,77,187,147,121,22,42,94,183,229,172,11,181,152,46,52,37,192,37,58,220,209,135,
157,78,39,108,181,90,23,131,32,192,92,99,174,7,240,3,7,56,39,25,60,207,43,10,229,147,36,65,20,69,11,246,252,206,51,89,164,40,195,45,75,175,171,138,23,42,7,114,11,1,147,36,65,208,9,242,198,239,176,7,240,
131,94,157,48,0,99,12,253,253,253,197,73,40,0,138,209,134,214,65,234,230,153,233,162,127,102,57,133,232,178,102,238,107,110,159,145,84,42,27,60,42,100,15,224,7,189,102,166,102,108,95,241,163,198,152,34,
246,181,203,2,158,205,240,64,238,58,119,215,55,47,164,146,221,66,130,197,28,47,198,24,40,163,35,173,70,115,115,208,14,150,205,158,45,43,128,165,74,225,121,28,113,20,111,180,243,49,44,251,100,67,153,44,
251,100,107,184,238,254,231,149,115,198,229,158,164,242,24,195,84,164,131,140,210,61,81,62,109,126,57,172,101,117,2,56,101,28,50,75,223,237,176,237,43,182,10,164,123,44,82,118,112,244,221,194,160,50,168,
229,241,73,221,103,35,202,220,171,230,8,59,97,181,147,79,253,233,1,252,128,87,24,132,48,218,32,149,233,110,183,172,198,157,48,155,113,202,5,65,117,79,213,187,144,83,182,16,216,30,99,160,185,77,182,115,
67,122,0,63,104,39,43,8,161,82,5,145,166,104,182,154,96,148,21,83,110,230,37,242,14,14,99,81,64,203,204,87,153,170,180,63,231,140,131,243,172,240,192,29,179,216,3,248,1,174,219,183,111,35,73,98,0,4,70,
26,196,81,156,159,110,38,139,41,60,54,123,180,24,233,177,216,100,188,133,174,41,42,48,1,240,249,65,102,136,162,104,87,179,217,68,16,44,15,71,107,217,56,89,246,68,208,190,190,62,104,169,6,141,50,240,184,
7,33,4,24,227,249,212,89,118,207,251,44,86,120,183,224,230,20,71,206,38,217,153,196,89,2,98,176,211,233,224,163,30,11,188,226,37,184,217,108,22,53,82,237,32,168,43,169,192,153,7,143,250,0,93,88,114,239,
87,146,93,105,190,99,6,102,86,22,146,13,247,206,210,148,3,86,77,247,0,126,144,33,82,214,33,143,40,138,94,142,147,152,25,0,97,24,66,170,20,196,204,115,204,247,90,11,141,114,88,76,138,187,234,163,41,65,
146,77,188,219,241,48,6,154,173,120,128,227,56,182,67,77,30,211,90,19,74,41,140,61,55,208,152,172,187,161,212,181,112,55,239,249,94,234,187,236,93,75,173,144,38,10,105,42,86,43,165,208,104,52,122,54,248,
65,46,207,243,48,48,48,0,207,243,158,5,242,17,191,90,131,114,86,76,159,189,223,73,58,247,178,189,101,27,92,212,64,19,2,238,121,53,155,244,232,73,240,131,124,18,243,102,47,198,216,0,236,252,12,163,51,112,
209,157,164,255,101,29,173,197,174,233,106,84,67,86,59,173,148,170,78,205,76,99,98,114,178,39,193,15,114,217,26,100,163,141,31,39,9,18,33,160,156,97,44,11,169,227,251,234,17,38,119,114,213,110,95,146,
251,125,110,195,215,165,105,138,70,179,129,169,169,169,30,192,15,106,173,89,179,6,27,54,108,64,42,211,153,84,165,243,159,188,52,125,199,173,190,40,143,64,186,31,251,188,16,23,237,74,51,231,217,25,242,
66,8,36,34,233,1,252,160,22,33,4,3,3,253,208,70,127,43,73,178,99,0,100,206,40,217,234,142,178,36,186,173,164,139,217,224,242,172,76,91,64,224,146,29,174,153,224,156,251,118,24,184,88,6,108,214,178,1,184,
175,158,181,141,196,34,27,49,44,211,121,202,208,13,89,92,181,235,142,245,117,195,163,50,184,54,105,225,54,111,187,78,150,187,242,92,244,190,137,137,9,180,91,173,30,192,15,106,13,14,13,66,3,136,163,232,
93,173,245,183,235,245,122,113,78,130,43,109,101,155,233,122,194,101,112,221,4,127,249,20,54,183,37,148,16,130,90,173,134,122,189,110,15,169,126,36,8,2,136,101,224,73,47,171,100,195,224,224,32,194,48,
156,86,74,161,86,171,161,211,233,20,32,186,95,54,55,188,216,89,136,118,220,130,125,205,230,123,237,234,238,100,204,156,56,219,85,232,121,30,70,70,70,214,3,243,245,244,61,9,126,64,43,73,18,196,113,12,198,
216,187,182,255,183,108,55,45,104,110,55,162,59,48,197,130,236,14,124,113,237,55,207,39,238,217,226,250,161,161,33,172,89,179,6,163,163,163,238,189,158,141,227,120,89,144,29,203,74,130,221,241,13,22,0,
219,24,158,36,73,241,186,165,36,231,15,202,64,215,144,238,114,229,134,123,180,143,37,84,108,39,131,237,69,138,162,8,81,20,193,24,131,193,193,193,213,132,16,204,205,205,245,0,126,144,171,226,87,208,223,
223,223,53,60,220,14,103,177,18,107,59,1,221,243,151,220,217,30,245,122,189,40,131,181,29,131,182,207,201,118,242,15,12,12,20,167,164,216,67,162,131,32,64,16,4,168,84,42,216,188,121,51,70,70,70,176,105,
211,166,30,192,15,114,173,90,189,10,219,182,109,195,248,248,120,211,109,10,179,77,218,118,248,246,240,240,112,87,184,228,126,185,69,118,182,220,199,62,12,22,228,40,138,48,51,51,83,220,219,30,159,99,127,
111,116,116,116,213,209,163,71,177,103,207,158,30,192,15,148,236,24,25,197,254,3,251,209,108,54,127,124,230,204,25,112,206,145,36,9,194,48,44,60,234,40,138,192,57,239,26,222,226,118,227,91,48,109,243,
184,37,45,172,20,219,135,160,217,108,22,13,224,22,232,220,25,107,173,95,191,254,213,67,135,14,97,176,127,160,7,240,131,94,251,158,222,139,70,163,49,54,49,49,241,214,141,27,55,94,116,11,211,237,169,224,
141,70,163,176,177,214,9,179,101,61,246,236,95,11,152,61,149,12,0,42,149,10,210,52,45,236,118,95,95,95,225,145,219,235,235,245,250,23,119,236,216,17,46,181,70,239,21,225,69,3,192,240,208,48,158,126,234,
105,244,247,247,191,42,132,184,105,157,164,74,165,82,12,110,41,179,83,246,1,112,15,161,116,199,19,218,33,47,214,126,91,231,202,62,32,190,239,163,191,191,31,235,215,175,23,123,246,236,249,179,29,219,183,
47,31,199,20,203,112,121,156,99,116,245,234,233,157,59,119,126,233,246,237,219,95,75,146,4,213,106,21,73,146,20,78,147,13,131,250,251,251,11,135,201,170,108,247,28,5,107,131,173,26,166,148,98,112,96,16,
137,72,64,41,197,218,181,107,49,56,56,136,45,91,182,96,227,198,141,63,89,189,122,53,246,238,221,183,108,246,138,220,239,12,169,165,182,78,156,60,137,75,239,95,58,114,249,242,229,55,102,102,102,234,132,
16,180,219,109,180,219,109,116,58,157,130,166,244,60,15,65,16,116,157,130,82,173,86,193,61,15,70,107,112,198,225,249,89,181,164,29,79,56,58,58,138,213,163,171,49,178,106,100,102,203,150,45,95,95,179,102,
205,183,54,110,218,56,54,50,180,42,34,148,152,135,53,119,242,111,178,254,223,0,116,193,116,130,198,25,252,148,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* JuceDemoPluginAudioProcessorEditor::chickknob_png = (const char*) resource_JuceDemoPluginAudioProcessorEditor_chickknob_png;
const int JuceDemoPluginAudioProcessorEditor::chickknob_pngSize = 8824;

// JUCER_RESOURCE: uibg_png, 65211, "../Graphics/uibg.png"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_uibg_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,1,144,0,0,0,230,8,2,0,0,0,116,209,68,243,0,0,0,4,103,65,77,65,0,
0,175,200,55,5,138,233,0,0,0,25,116,69,88,116,83,111,102,116,119,97,114,101,0,65,100,111,98,101,32,73,109,97,103,101,82,101,97,100,121,113,201,101,60,0,0,254,77,73,68,65,84,120,218,236,189,89,151,101,
199,117,30,24,113,230,59,223,155,115,85,161,48,21,0,18,28,68,210,162,68,145,32,64,128,182,40,201,178,101,137,90,221,253,79,220,47,253,210,47,253,79,250,165,173,37,75,171,123,45,173,238,213,182,213,214,
64,15,146,53,144,2,72,12,5,160,134,172,172,28,239,120,230,19,209,123,136,56,247,102,86,102,86,142,5,66,102,146,168,202,202,220,55,206,57,113,34,118,236,225,219,223,150,255,228,127,255,210,175,255,253,
191,20,87,247,165,188,134,35,101,89,149,190,235,195,63,139,170,208,90,56,210,81,74,9,137,2,240,91,233,56,151,145,145,14,72,73,215,117,139,178,132,95,249,158,39,241,99,18,254,212,66,85,90,105,165,180,208,
87,34,3,63,135,59,241,28,144,41,64,222,115,61,184,13,124,76,165,42,85,9,248,135,148,46,220,233,211,100,226,233,100,105,105,229,146,131,156,69,6,254,25,136,226,34,111,206,193,121,214,248,63,28,149,222,
131,132,111,37,141,137,63,147,56,255,207,70,166,146,46,188,14,243,27,148,209,230,139,94,25,44,141,178,170,248,149,213,50,240,217,35,175,117,111,111,183,219,235,95,235,242,56,131,12,60,159,230,229,92,85,
21,62,172,174,20,190,40,250,130,23,10,143,35,29,250,20,141,72,99,194,227,40,124,34,1,43,29,127,41,240,27,126,75,48,44,77,7,10,153,113,28,23,22,6,238,29,129,43,68,211,132,29,183,108,28,88,54,240,75,148,
49,67,160,32,14,137,147,200,115,143,31,166,183,97,254,65,191,180,87,254,57,248,146,255,243,255,242,191,94,173,114,129,63,175,100,227,157,34,131,203,66,194,236,231,240,67,120,199,121,81,240,140,211,93,
8,154,121,250,248,85,200,240,27,131,251,162,55,42,105,127,225,221,177,114,182,179,40,159,42,51,30,13,219,221,238,37,7,57,147,12,188,145,42,189,192,82,168,132,67,111,211,225,145,225,193,93,233,214,11,150,
118,146,226,69,125,61,50,158,182,143,128,50,210,85,244,116,184,8,28,135,183,17,140,195,239,69,129,182,146,2,246,255,17,153,35,175,117,54,25,119,122,253,107,93,30,103,146,193,3,22,118,71,1,255,194,103,
215,218,129,85,109,21,174,85,112,226,168,18,116,92,216,74,32,227,185,174,156,107,12,80,48,164,204,80,9,226,165,43,212,56,52,143,120,89,214,54,90,208,171,60,110,217,208,29,225,24,172,159,72,109,205,53,
17,107,174,67,95,102,141,209,127,116,214,152,17,15,235,175,250,251,250,231,242,137,245,245,164,140,88,144,60,171,54,132,89,214,129,23,28,81,10,184,124,73,113,84,180,27,148,227,156,93,70,226,210,17,121,
153,243,209,81,209,139,145,184,212,28,207,21,139,51,120,97,25,124,145,248,130,80,69,194,132,210,162,145,164,57,249,108,162,67,13,222,202,85,200,240,41,3,223,210,113,39,14,29,137,160,181,249,72,164,69,
118,186,12,253,121,217,65,206,34,115,241,179,139,30,155,85,3,43,20,62,228,205,111,29,208,58,142,182,219,230,114,50,164,191,180,89,167,36,67,59,121,46,227,208,62,167,109,194,74,141,198,131,245,70,102,9,
110,104,54,169,142,200,28,121,173,21,125,93,235,242,56,69,70,177,133,14,162,206,252,165,120,112,4,75,9,167,126,232,7,199,42,56,56,163,93,50,1,64,9,194,134,82,66,21,86,70,90,29,136,234,25,205,46,89,42,
120,58,23,174,11,246,166,228,89,192,95,56,79,89,54,52,144,49,217,208,216,50,102,32,27,185,218,170,39,243,31,207,56,61,41,235,56,18,81,242,144,74,146,115,181,195,179,35,22,134,121,82,230,144,146,98,73,
249,132,118,147,199,106,49,239,202,149,203,85,109,188,83,100,114,48,229,28,95,161,11,97,252,5,99,6,41,61,95,253,66,95,141,12,221,83,224,123,96,243,131,164,207,71,153,61,124,212,130,159,114,186,12,252,
59,240,253,75,14,114,22,153,11,43,44,180,154,97,33,146,179,166,204,33,44,172,210,22,102,59,193,156,92,78,134,119,192,97,153,138,100,156,90,219,226,99,57,102,115,152,45,66,91,138,245,4,152,39,52,15,70,
213,45,200,232,35,175,149,151,229,245,46,143,83,101,112,59,72,252,33,106,105,94,213,224,16,226,71,157,83,149,160,196,233,1,25,48,185,200,28,163,223,146,154,49,143,9,186,91,208,200,130,163,22,96,169,145,
189,41,78,93,54,224,172,84,230,162,70,70,226,244,91,55,130,55,153,162,11,56,214,55,215,214,71,196,159,25,135,222,234,23,121,196,103,52,14,201,130,75,41,15,201,212,170,73,139,67,86,216,49,170,73,158,100,
166,121,232,132,93,169,114,185,170,29,126,138,76,81,148,188,1,192,90,134,47,190,131,192,13,42,93,241,36,193,51,93,149,12,156,114,124,220,157,124,36,186,181,95,112,138,140,231,6,48,252,37,7,57,139,12,110,
23,167,81,123,22,139,177,33,214,191,224,182,43,142,97,60,33,227,56,62,89,175,176,1,162,90,70,209,102,36,151,128,94,252,57,101,104,121,137,35,50,14,25,1,37,57,41,174,27,42,179,49,230,50,46,185,138,100,
72,72,86,82,240,13,88,88,21,14,135,142,18,252,138,99,49,11,50,206,145,215,10,35,94,247,242,56,69,6,231,86,227,61,151,104,229,25,83,253,188,74,80,242,91,67,101,33,209,140,18,181,30,208,142,64,69,70,26,
143,162,49,158,15,99,93,104,217,184,194,65,171,142,156,62,208,173,48,171,138,66,132,243,176,3,135,198,208,253,148,160,239,92,86,62,172,94,173,93,46,200,43,231,187,21,46,29,42,86,198,60,26,13,78,134,176,
212,86,198,170,105,57,95,135,44,195,107,149,253,185,197,181,234,93,185,114,185,170,29,126,138,12,152,42,218,70,98,201,221,160,8,26,250,11,130,15,33,88,58,244,216,87,32,115,85,238,103,165,202,103,230,195,
162,175,116,161,77,200,171,19,126,148,235,130,150,169,139,154,130,94,178,235,120,218,120,122,103,149,209,135,100,28,57,143,103,153,197,131,251,65,169,18,3,11,130,220,28,23,195,56,24,21,118,225,174,28,
58,14,165,53,164,240,5,129,161,34,92,227,108,26,255,99,46,115,204,107,21,215,190,60,78,145,113,48,98,133,33,20,222,201,168,113,84,121,94,37,136,203,93,209,181,96,114,156,185,25,3,159,226,21,101,109,4,
212,140,23,94,54,120,24,80,104,140,222,72,225,226,242,113,217,171,39,69,89,242,6,103,67,15,143,12,173,48,162,141,247,207,239,212,193,232,144,117,3,43,58,156,200,255,133,223,184,108,29,195,152,244,140,
198,40,174,227,143,188,126,72,6,215,6,154,228,148,97,128,159,144,8,222,176,15,115,72,115,5,223,123,129,31,94,173,114,121,54,1,38,151,126,14,171,97,49,15,0,79,184,152,7,184,18,25,125,69,190,131,99,28,132,
107,247,97,233,125,139,11,108,48,78,63,73,90,62,164,15,104,68,124,193,228,206,208,200,116,4,158,85,70,154,32,173,9,130,96,38,11,86,42,201,72,82,121,194,106,26,218,0,194,245,252,188,144,60,142,36,21,175,
57,54,172,76,52,221,17,252,198,48,120,138,134,0,122,70,115,25,45,142,190,86,216,12,176,99,174,117,121,156,36,99,158,110,238,4,95,80,9,74,205,78,54,198,239,216,193,210,198,11,198,15,112,144,236,130,203,
70,114,232,10,101,42,154,112,207,241,20,5,236,109,42,195,88,115,158,231,218,108,174,52,46,29,104,31,24,223,17,54,188,69,105,95,99,160,97,210,82,139,250,1,197,220,186,183,47,10,254,242,60,79,91,103,223,
228,12,236,234,229,121,160,3,204,225,57,80,11,243,224,254,218,119,223,194,39,167,47,135,114,115,100,107,147,125,168,140,253,164,72,119,156,85,70,43,120,114,235,154,234,197,244,16,191,62,154,14,125,57,
25,188,125,206,72,130,218,198,67,204,60,51,7,77,234,192,225,21,200,148,37,234,121,243,224,124,236,8,13,71,34,231,129,217,10,40,201,246,60,93,38,137,99,47,8,46,57,200,89,100,40,162,225,211,54,40,201,27,
227,108,154,209,2,184,193,72,185,192,83,31,145,17,100,194,176,225,67,102,63,158,234,152,216,82,230,48,228,57,57,187,12,43,41,118,223,28,58,132,53,7,107,233,227,146,92,15,16,138,167,147,123,247,62,126,
188,253,248,96,127,55,12,124,73,230,24,140,131,234,134,20,227,161,144,46,218,23,56,96,133,87,84,124,62,207,243,89,135,95,235,44,158,194,156,95,235,242,120,82,134,95,4,37,4,43,99,105,218,77,66,51,115,226,
252,63,249,142,28,178,169,64,41,75,122,100,147,78,117,60,210,2,14,191,110,243,193,83,151,132,181,120,96,56,28,26,70,246,92,240,135,194,74,113,150,25,95,22,44,45,134,57,152,192,189,102,167,204,225,89,167,
195,70,249,52,3,156,62,226,251,33,195,138,85,12,111,83,101,206,15,154,25,92,33,90,88,195,74,154,32,35,69,144,140,238,147,11,50,122,158,11,197,44,49,71,159,164,177,46,37,201,192,71,221,183,190,247,253,
171,85,46,121,94,92,201,198,59,69,134,35,122,136,159,160,128,9,219,138,246,192,227,28,138,195,201,202,203,203,184,108,72,10,105,109,5,94,139,198,18,215,156,246,58,131,76,150,37,97,212,184,228,32,103,145,
193,221,14,203,248,252,155,16,151,160,226,72,16,90,245,146,18,44,138,98,67,142,172,177,43,242,12,50,48,78,197,166,16,175,223,26,202,192,81,80,182,199,21,93,29,222,240,193,254,78,187,221,134,27,72,179,
108,60,25,207,166,19,152,168,70,216,224,52,180,75,42,64,205,147,235,168,189,20,166,166,81,99,162,15,133,153,50,86,19,71,95,107,158,165,141,70,243,90,151,199,147,50,53,126,137,20,174,73,231,209,145,174,
206,165,4,17,39,129,31,81,70,128,246,69,13,147,66,251,149,95,183,177,95,143,44,9,197,50,21,77,59,123,39,156,4,152,77,199,15,31,220,223,217,217,29,14,15,162,48,0,75,135,45,64,112,63,231,225,116,14,57,25,
11,200,44,45,111,225,158,93,107,79,217,101,103,50,204,142,5,169,240,74,224,152,189,99,99,252,52,21,22,238,37,57,82,233,104,227,217,59,210,66,211,56,75,195,227,56,120,124,121,108,17,177,128,251,43,223,
126,227,138,149,203,21,109,188,83,100,232,196,82,236,231,179,38,166,7,115,92,198,227,200,26,101,120,5,50,231,58,18,79,145,41,139,34,8,195,75,14,114,22,25,97,161,73,231,221,132,194,4,71,69,125,234,242,
251,101,247,165,78,69,159,65,134,1,86,53,84,66,155,76,140,96,8,101,141,83,196,211,251,225,131,123,73,154,194,33,7,75,171,221,106,193,237,165,105,58,30,15,203,170,104,180,218,230,132,215,156,168,55,238,
136,54,145,92,58,59,217,156,225,243,156,182,220,226,107,205,178,44,138,162,107,93,30,214,187,208,53,32,195,46,86,199,38,217,104,254,165,56,151,18,228,11,243,182,55,134,164,77,26,74,123,0,152,215,77,50,
148,94,240,48,247,170,77,64,144,115,20,60,57,124,108,176,157,55,60,216,107,52,34,184,183,60,207,70,163,209,100,50,142,194,200,247,209,97,228,72,57,25,137,120,230,213,206,44,111,65,50,244,204,61,211,132,
56,180,20,180,99,146,135,54,215,76,95,28,130,164,179,147,209,215,18,255,166,87,135,214,34,250,189,174,178,113,30,54,157,228,60,89,168,23,198,153,171,42,246,46,221,55,222,250,222,89,20,199,100,12,71,223,
180,209,108,61,85,185,92,213,198,59,205,121,33,15,222,247,248,8,194,216,164,9,167,153,120,228,60,15,112,121,25,70,177,94,222,119,40,242,172,221,234,60,3,31,182,70,250,93,106,19,206,215,32,3,20,205,2,241,
22,149,194,105,50,172,89,208,71,112,253,194,241,75,47,44,220,48,243,162,204,141,50,199,43,92,175,146,110,85,148,249,206,227,29,198,185,21,69,30,39,73,24,224,87,81,20,179,217,172,42,139,40,106,192,62,20,
178,214,195,6,183,129,225,106,250,14,195,210,188,16,217,234,63,252,90,147,36,14,194,232,58,151,135,209,206,96,167,40,227,241,201,57,146,72,202,218,238,115,207,51,255,138,207,99,173,173,237,227,87,85,137,
145,22,188,1,103,33,36,100,113,2,104,73,160,173,170,200,28,227,99,66,137,185,55,106,98,109,174,247,224,193,39,113,60,43,139,18,38,176,213,108,193,135,147,36,25,143,14,64,25,193,226,68,179,206,193,107,
225,91,163,92,1,157,73,236,232,169,58,32,9,3,241,195,113,46,133,236,71,139,188,227,124,52,153,135,20,50,87,244,130,156,121,145,131,48,16,31,146,113,121,191,207,151,49,34,53,148,22,115,245,39,77,220,218,
113,36,199,30,164,7,210,103,9,43,222,253,224,167,7,123,187,63,248,231,191,251,212,208,35,252,121,46,160,233,5,100,106,164,251,51,64,9,176,11,124,5,80,181,107,6,211,46,94,136,211,52,231,205,249,226,139,
163,197,196,102,57,250,91,154,177,5,146,142,107,142,83,169,211,101,8,119,128,107,14,172,4,191,149,121,97,138,88,82,10,96,73,237,130,9,142,120,107,191,144,78,2,242,247,222,219,179,160,109,46,83,113,226,
56,134,93,208,106,181,192,206,218,219,219,155,78,167,119,238,188,234,80,137,133,224,12,35,85,101,193,32,188,220,249,149,25,164,59,69,81,23,95,43,56,60,176,84,174,115,121,144,38,194,60,90,225,129,201,128,
96,114,37,201,37,199,4,60,190,18,147,195,171,195,88,103,200,185,211,171,21,12,17,192,181,87,208,235,150,132,131,125,242,117,179,162,40,41,206,133,35,235,192,193,26,43,216,33,190,75,248,0,56,216,74,184,
65,173,226,108,150,204,102,240,249,172,204,192,170,133,177,59,237,54,252,31,230,124,120,112,0,23,94,94,94,83,136,188,199,139,113,45,129,49,189,209,208,37,83,200,60,4,123,247,38,154,172,231,216,82,89,47,
81,4,144,155,123,86,116,158,185,172,232,22,151,49,203,44,46,99,178,151,93,182,226,249,74,14,131,246,76,245,21,78,200,89,145,238,236,63,131,182,58,35,210,253,127,219,252,228,116,152,226,191,222,184,253,
11,164,251,53,33,221,47,182,9,49,135,201,201,56,54,212,171,146,235,93,184,2,206,248,128,226,233,50,96,58,249,173,196,11,51,116,4,178,160,156,134,186,244,112,237,113,244,156,34,244,48,196,254,254,78,22,
231,28,100,113,234,240,6,122,46,34,75,51,184,79,216,75,224,211,125,244,209,7,175,188,250,58,31,27,165,82,198,174,255,172,145,238,115,20,187,149,65,29,13,10,220,243,192,90,9,8,18,5,42,137,211,121,103,86,
130,92,23,232,176,233,4,115,139,229,136,39,192,36,75,101,138,7,240,157,195,206,21,126,75,54,59,178,237,33,66,149,148,152,212,165,64,192,90,40,3,71,225,237,253,228,211,191,99,64,188,77,152,8,56,21,224,
134,218,237,246,44,142,247,119,119,103,211,201,139,47,189,34,49,102,196,40,85,86,68,24,230,209,244,138,25,248,86,150,213,194,26,96,149,198,115,162,209,145,68,83,255,200,82,119,206,179,140,53,143,131,225,
48,9,135,40,65,103,57,200,69,115,248,20,164,123,18,199,15,31,63,242,208,197,85,124,148,221,253,240,125,240,120,89,231,149,69,222,233,245,150,150,87,193,176,220,222,218,12,163,104,125,227,38,223,205,211,
107,164,47,1,88,253,5,210,253,116,164,251,197,54,33,47,126,6,25,112,254,136,223,145,137,197,26,195,254,116,25,240,87,203,176,59,69,156,77,210,44,147,136,22,20,193,14,185,54,215,106,37,112,250,118,30,111,
83,76,221,21,54,224,101,125,6,114,10,74,147,100,116,93,151,147,80,166,146,142,243,83,63,7,72,119,139,98,71,248,166,50,79,103,172,15,134,68,177,231,113,182,249,159,151,191,176,147,103,28,58,121,252,235,
86,22,52,135,142,170,244,122,178,219,150,109,120,17,137,78,15,100,2,122,170,2,187,74,139,69,152,250,104,111,175,44,115,158,37,48,78,141,239,166,69,89,150,211,217,12,92,218,70,179,145,231,197,167,159,220,
125,249,206,23,40,218,205,158,47,217,53,194,68,218,230,168,122,165,108,16,157,163,66,194,68,242,174,102,25,91,41,11,88,149,11,115,120,26,210,125,54,155,252,151,31,253,71,248,88,163,209,156,140,71,60,220,
71,239,191,7,223,116,123,253,219,183,95,250,244,193,189,242,227,252,59,111,253,211,79,62,122,127,243,193,189,95,250,229,95,53,177,173,99,48,245,79,84,174,253,2,233,126,109,72,119,203,130,112,206,77,136,
158,21,248,89,132,80,183,104,120,73,39,158,221,75,226,116,25,39,204,130,206,84,40,191,24,47,99,221,46,1,180,249,232,169,175,196,75,111,115,243,62,27,101,135,11,216,140,221,196,127,242,42,128,149,198,17,
92,155,180,210,20,177,230,16,231,103,128,116,167,167,174,24,81,73,200,251,138,171,39,57,193,134,80,166,115,42,65,14,54,47,160,216,181,99,96,11,199,191,110,246,127,41,123,232,70,34,88,117,150,224,103,163,
106,52,147,113,9,214,79,97,108,40,154,49,148,113,112,191,228,123,123,59,176,143,124,223,35,12,179,170,139,19,25,105,81,228,88,152,29,248,65,189,199,224,90,210,100,17,236,210,50,24,56,240,111,10,31,43,
189,245,181,46,99,78,56,114,245,168,214,243,57,60,13,233,190,245,104,179,44,138,47,127,237,159,128,221,244,87,255,233,207,199,163,33,175,203,70,179,245,107,111,188,131,94,186,239,253,221,223,252,215,15,
126,246,46,104,171,155,207,61,191,190,126,163,70,186,63,85,97,93,6,176,250,11,164,251,207,33,210,221,109,206,194,22,24,235,97,62,238,106,78,230,106,6,176,27,69,167,193,203,161,29,30,199,113,50,155,41,
205,88,30,229,58,62,229,251,4,135,186,224,11,211,67,228,188,180,59,157,229,229,85,171,207,20,35,221,49,148,241,25,33,221,45,152,131,213,169,242,40,30,95,163,216,193,87,170,168,206,249,220,74,208,9,132,
83,213,40,118,188,241,19,94,183,48,185,50,156,137,168,10,151,228,160,212,213,142,222,41,101,41,108,154,94,88,32,24,200,176,207,244,240,225,253,188,44,16,14,194,119,43,235,20,174,100,234,11,73,38,48,24,
102,43,43,171,228,214,40,139,131,96,108,138,18,135,138,28,37,197,130,196,53,249,218,38,54,198,121,83,130,104,248,110,96,48,165,160,115,78,81,28,30,186,126,98,116,176,239,123,126,28,207,44,253,144,136,
162,70,94,228,32,179,178,190,1,254,32,104,43,248,225,43,175,125,137,45,8,179,195,159,246,85,84,197,47,144,238,255,104,144,238,94,163,240,90,89,158,132,229,180,101,66,73,182,148,35,77,147,201,120,200,148,
3,172,161,210,52,131,127,34,10,93,152,232,15,31,148,20,170,231,204,148,130,91,5,117,208,233,245,25,229,163,132,169,216,32,235,95,210,142,250,172,144,238,194,204,54,237,255,203,160,216,107,25,83,120,200,
152,73,205,68,8,39,152,99,92,142,168,116,79,116,192,19,76,68,186,83,237,26,27,115,206,104,37,108,249,29,26,183,179,24,124,190,41,232,74,134,110,25,198,43,190,109,126,77,142,65,87,180,219,157,165,229,53,
189,128,92,89,52,109,142,220,15,123,238,199,44,63,99,132,90,32,133,41,28,172,17,170,84,80,9,50,30,143,35,143,93,198,148,241,212,46,193,230,29,10,246,215,115,232,157,162,56,110,222,186,157,204,166,159,
126,252,209,222,238,182,239,251,96,109,217,32,151,36,56,31,202,12,150,87,246,247,118,94,121,237,117,63,12,108,166,9,78,12,255,169,10,203,149,206,37,54,167,184,238,68,100,45,195,229,182,87,224,126,130,
181,94,22,207,192,135,165,223,94,68,71,115,28,213,162,216,113,17,115,210,26,148,130,226,179,213,194,77,142,200,72,175,116,91,227,34,243,64,91,41,251,43,176,56,102,211,233,193,222,158,143,145,187,130,95,
35,89,206,110,158,103,92,204,108,54,39,159,252,245,161,79,166,1,56,47,61,80,87,189,165,2,28,64,26,144,253,65,94,244,236,150,50,56,179,174,49,161,69,126,232,181,78,84,117,150,52,209,217,151,7,207,3,103,
229,4,229,36,45,125,129,137,66,159,93,9,114,216,123,254,116,180,215,193,212,178,249,182,99,94,55,35,30,96,227,52,100,212,19,221,169,136,247,170,61,101,236,79,28,68,184,110,28,79,71,195,3,138,47,106,198,
103,197,73,146,101,153,135,129,39,212,152,53,195,31,22,238,73,37,108,221,50,220,88,187,219,197,241,17,66,224,81,173,98,245,148,229,135,254,48,44,191,16,189,7,115,154,161,76,229,26,51,147,113,88,138,101,
104,28,135,206,143,18,141,81,197,208,57,194,208,139,69,25,246,181,177,176,17,77,114,194,109,225,235,86,28,41,243,78,87,28,47,189,250,197,151,95,251,226,98,125,255,59,191,241,219,38,77,75,50,155,247,63,
5,67,236,198,115,183,235,113,138,188,156,115,137,156,252,149,21,249,101,234,224,159,25,74,192,53,5,77,151,117,45,25,146,252,12,124,88,19,116,63,191,142,230,10,27,199,32,27,17,115,136,44,154,82,48,74,136,
11,59,52,103,112,22,101,170,162,49,216,135,145,170,201,128,217,44,57,18,191,183,189,197,56,136,56,137,25,244,92,208,129,7,107,213,35,20,21,19,117,214,224,102,82,70,180,248,170,202,15,130,70,212,184,241,
90,152,28,148,190,235,145,37,165,230,12,74,214,180,113,137,185,176,34,164,187,230,208,207,225,215,202,59,228,10,151,135,201,69,210,188,153,50,15,162,156,100,111,224,236,74,16,236,11,46,133,225,233,98,
223,22,35,89,56,183,199,155,108,134,171,17,51,118,222,178,92,74,101,182,175,14,144,61,203,222,235,100,58,6,211,33,240,3,240,126,72,139,154,252,43,76,59,129,161,106,58,24,19,189,162,90,58,182,146,69,20,
132,237,86,187,215,27,48,168,138,209,231,240,218,159,178,252,16,168,224,148,150,164,140,242,33,110,224,203,26,160,119,202,50,22,150,13,80,25,156,251,33,25,66,249,51,68,203,181,230,158,195,115,232,93,64,
113,88,162,91,253,224,222,39,73,18,223,121,237,245,32,140,8,159,230,144,119,128,37,215,255,122,253,57,14,156,179,94,115,142,176,193,74,29,152,18,39,90,139,132,88,70,44,137,52,60,136,160,34,57,151,193,
1,248,35,50,92,174,15,7,10,191,2,204,197,144,5,90,215,49,25,192,231,97,153,139,161,4,174,202,181,36,220,155,120,6,62,108,141,53,63,239,70,101,248,138,253,184,52,112,27,46,139,49,101,101,56,147,71,100,
194,206,12,126,149,238,119,53,46,56,174,198,80,187,219,143,16,160,88,209,14,213,34,207,243,146,24,132,113,45,34,115,83,73,252,80,154,107,202,168,168,89,59,22,181,237,135,97,20,69,107,55,111,8,119,28,118,
227,108,212,66,104,37,114,117,213,49,52,205,16,98,116,54,152,227,129,252,41,151,236,130,197,215,202,120,248,43,4,145,160,49,66,46,8,185,207,236,173,158,91,9,162,238,46,11,73,15,5,155,144,106,218,100,73,
180,4,8,103,47,171,147,204,49,216,149,48,79,55,156,181,82,84,91,213,54,131,233,217,164,221,222,186,71,140,165,106,154,79,16,106,75,115,14,87,129,105,119,236,151,41,202,227,34,71,5,231,16,234,38,80,19,
96,2,131,154,251,242,250,47,109,233,29,197,181,80,116,45,82,194,242,188,203,207,241,60,167,150,193,241,75,146,145,182,26,92,31,145,129,185,58,126,28,14,96,153,131,202,33,0,45,25,16,103,68,186,47,202,176,
251,202,39,228,202,218,198,250,205,91,23,6,19,59,142,69,238,42,37,22,152,42,205,137,239,80,56,195,113,143,200,112,34,210,165,50,78,3,228,229,210,36,199,53,121,43,155,136,172,101,220,58,158,255,11,164,
251,213,33,221,225,183,65,119,90,198,145,46,162,186,164,109,111,103,11,172,42,56,99,96,191,72,34,50,174,8,77,99,77,5,164,13,145,162,134,74,152,27,48,17,214,170,234,247,122,203,107,27,4,26,151,94,148,169,
188,101,203,211,28,105,159,206,113,62,3,164,187,217,8,122,238,187,194,103,92,162,2,56,47,138,93,91,162,10,38,86,86,226,40,138,253,112,81,161,143,230,6,161,216,151,229,192,23,222,35,253,88,137,26,196,171,
225,120,72,147,52,73,18,222,11,96,97,128,15,136,147,174,12,114,138,235,231,200,2,160,226,196,121,253,161,4,93,213,108,52,110,220,120,161,39,187,129,244,115,183,168,17,243,243,189,121,134,229,119,136,158,
31,17,243,30,150,235,9,83,157,110,237,104,93,163,243,141,12,34,221,171,185,140,33,0,212,53,203,50,123,12,120,40,217,121,246,66,63,58,157,145,218,243,252,35,172,213,96,208,114,10,79,118,100,191,191,116,
225,228,165,182,196,20,90,84,176,44,12,159,134,113,76,24,171,166,216,70,61,86,198,224,28,201,254,114,76,112,174,164,147,68,62,41,67,105,218,227,159,11,62,203,120,232,83,100,184,28,4,101,212,92,198,35,
66,238,250,49,79,151,201,156,132,89,214,142,76,5,23,178,44,142,115,85,50,30,177,74,101,69,182,56,237,140,16,13,188,227,101,234,138,54,203,231,235,195,233,199,78,49,92,139,151,190,205,222,224,129,230,183,
83,60,132,211,6,143,13,199,117,60,153,78,38,19,216,42,113,28,195,185,141,219,166,52,199,102,157,80,163,164,184,1,75,216,114,122,83,202,211,5,109,181,178,166,201,254,42,226,192,109,196,50,156,201,164,197,
69,27,174,244,196,103,132,116,71,188,56,234,95,201,86,60,233,55,131,192,62,15,74,206,100,230,96,135,178,194,37,132,58,26,112,139,136,112,239,24,68,56,39,22,100,67,70,99,49,69,255,151,56,163,224,183,187,
59,143,210,52,45,41,48,228,184,120,105,194,139,44,148,25,155,45,35,140,181,133,126,61,42,79,166,120,93,234,14,150,87,215,65,106,42,103,93,209,217,175,14,56,232,110,243,137,103,246,163,229,156,90,20,223,
157,42,44,157,3,39,28,153,117,166,102,88,182,50,104,253,8,35,195,102,148,52,184,28,109,83,16,248,164,246,116,84,167,7,221,79,202,214,41,235,180,95,50,121,105,208,138,84,118,94,135,243,217,123,174,13,165,
185,254,150,151,146,193,253,252,204,89,189,23,101,158,25,172,225,194,50,117,220,209,210,126,10,88,82,130,81,221,28,134,91,96,178,229,35,209,139,14,116,209,112,164,71,211,142,31,154,76,134,168,221,242,
156,223,66,146,166,20,202,209,86,29,144,133,142,145,93,138,181,33,102,154,162,188,112,216,22,101,175,223,27,244,7,158,23,104,82,73,200,21,151,7,110,24,151,113,147,11,92,108,1,157,124,246,72,119,81,159,
246,88,65,130,40,118,129,196,167,231,68,177,147,213,98,80,236,180,98,41,215,241,20,46,118,71,152,250,176,158,211,129,223,141,213,68,219,164,91,18,79,167,116,60,76,167,51,240,236,16,132,78,65,12,135,211,
47,166,211,135,88,128,144,42,225,80,47,15,210,156,48,219,112,60,112,19,147,137,154,118,100,171,35,59,35,61,230,247,107,138,216,207,224,71,27,52,157,48,68,214,164,167,93,170,217,230,128,166,22,102,159,
46,172,31,124,95,11,50,156,147,169,131,107,54,201,140,197,94,186,228,76,38,247,8,66,123,149,179,28,86,23,179,209,94,49,185,23,217,175,234,136,204,177,63,60,203,7,13,92,118,78,53,85,166,201,244,253,159,
254,67,60,29,11,19,144,86,115,108,50,147,221,107,115,56,113,100,242,194,50,103,188,189,235,147,177,125,77,158,62,78,158,103,224,203,60,41,83,34,130,105,170,203,234,154,238,153,203,34,56,164,84,49,33,12,
253,68,25,235,64,25,58,42,146,193,61,237,196,240,119,30,251,176,77,24,166,153,164,49,104,168,44,203,97,31,130,113,99,180,152,53,175,216,133,225,140,30,227,173,44,117,59,238,46,140,164,4,193,112,56,228,
14,85,124,173,50,9,193,154,119,253,130,25,157,248,196,174,97,208,98,161,134,173,190,193,107,122,179,118,133,153,59,103,230,18,174,16,230,252,189,66,42,228,178,62,254,89,81,122,86,198,226,96,149,13,210,
243,46,192,226,7,222,174,142,172,241,254,11,69,11,178,102,163,192,165,221,145,96,208,102,98,78,155,167,71,195,125,52,144,51,244,126,224,66,160,34,185,200,73,207,35,245,182,37,24,51,210,216,76,43,108,189,
102,179,217,235,245,132,99,34,197,149,84,137,200,186,78,167,110,37,241,228,253,88,19,242,232,61,215,173,70,12,78,157,64,200,108,166,217,122,64,11,229,23,181,239,108,10,197,13,104,222,210,66,104,43,163,
240,85,43,215,210,87,176,190,71,36,240,69,232,101,136,238,235,2,132,86,108,224,177,69,157,165,233,195,7,159,140,14,70,240,195,217,116,10,115,217,104,181,121,89,215,50,220,220,13,237,95,203,92,193,25,162,
11,200,128,69,119,77,132,121,103,148,129,231,61,35,129,223,222,206,227,209,193,193,96,105,229,136,76,146,204,54,31,220,199,176,244,5,136,0,193,183,117,21,38,190,225,4,67,213,87,42,80,74,162,116,29,147,
104,194,140,21,109,173,58,29,165,141,138,168,155,156,224,70,168,101,96,61,5,161,118,195,2,204,159,58,236,176,179,251,24,177,47,216,233,64,193,14,162,122,125,27,39,55,49,106,67,77,105,104,201,45,179,37,
220,45,108,117,80,5,8,190,130,205,71,216,99,178,89,92,39,156,233,210,151,58,88,236,18,166,109,35,56,126,227,92,228,200,75,123,113,6,138,44,107,182,90,87,245,102,57,194,130,33,109,54,0,8,20,117,18,43,28,
27,80,172,26,210,36,150,182,15,163,169,122,65,63,11,85,12,232,53,159,166,20,116,13,39,85,201,32,168,104,143,58,53,205,33,124,23,202,176,161,162,61,117,80,136,146,215,60,172,168,225,240,160,200,75,109,
248,100,4,107,115,38,218,180,250,78,178,17,132,206,151,98,51,25,110,169,226,10,243,56,137,187,221,46,197,226,152,41,70,180,116,35,151,69,37,48,92,143,20,137,204,227,99,105,124,224,86,153,58,2,150,19,140,
8,247,124,68,70,154,2,4,52,35,217,246,52,183,98,83,139,181,57,204,17,73,138,239,73,138,100,169,90,201,218,208,132,97,28,117,22,227,215,66,122,204,100,123,174,84,58,231,232,47,144,131,119,93,174,91,85,
91,91,143,38,163,81,94,228,141,70,83,231,168,147,247,15,246,192,55,222,216,184,197,22,156,99,187,68,57,148,102,170,217,43,56,238,123,49,153,103,207,234,189,40,147,156,7,214,192,49,230,35,50,14,161,86,
46,0,143,240,130,66,70,251,158,109,79,226,28,142,107,170,42,148,73,203,228,113,132,170,3,31,166,82,140,89,63,76,219,63,81,203,160,165,174,114,9,254,84,69,46,15,45,184,2,109,171,74,153,51,211,201,242,56,
12,66,110,32,136,33,15,38,242,118,108,214,71,206,3,64,84,232,19,112,207,169,52,77,163,70,155,116,1,138,123,6,60,96,10,131,62,43,78,119,2,4,73,190,21,171,178,21,134,195,45,2,251,72,62,29,39,140,242,154,
105,28,31,28,236,174,173,223,240,163,38,115,177,243,71,230,126,43,237,249,99,17,234,188,99,217,190,115,232,205,148,162,172,101,246,246,119,216,94,99,134,22,204,195,234,26,243,201,45,88,109,213,147,77,
68,149,84,172,78,58,171,156,78,167,176,251,146,56,14,163,38,95,43,215,88,160,227,42,135,239,199,57,107,33,100,45,163,107,13,197,47,131,206,28,151,213,149,103,2,151,196,16,133,239,86,89,170,123,81,99,59,
16,26,134,179,102,74,41,12,102,24,25,140,93,97,51,0,103,165,151,89,148,49,149,78,23,202,193,195,251,251,135,159,252,205,246,227,173,47,188,254,21,48,74,9,65,86,81,56,3,113,134,101,145,117,186,240,36,101,
224,43,215,133,173,80,208,185,225,195,60,231,37,28,17,65,154,68,170,110,39,68,225,67,236,161,162,77,202,153,93,98,56,250,158,148,121,246,172,222,71,101,158,6,107,192,154,149,217,148,193,144,132,157,195,
131,39,153,205,96,102,48,149,211,106,107,6,31,209,56,241,116,138,6,179,239,130,7,134,133,7,89,6,207,222,235,15,96,156,233,116,2,146,205,118,219,243,66,190,150,239,37,98,78,104,36,234,168,15,239,61,199,
41,210,36,103,0,208,188,140,153,99,239,146,57,72,221,186,160,90,90,25,204,235,120,84,113,192,75,152,130,247,108,219,178,203,3,187,144,192,138,21,61,142,65,177,47,52,123,178,97,24,202,74,51,66,66,16,217,
25,97,226,165,54,148,110,14,42,10,135,185,134,209,74,249,121,224,116,47,41,240,196,186,230,36,164,59,205,149,83,7,64,248,155,67,237,139,136,45,71,60,129,80,159,183,8,196,167,171,24,25,11,50,158,240,132,
161,18,149,44,147,165,25,135,216,57,76,150,231,57,209,135,218,142,106,202,116,83,157,87,17,211,20,19,70,87,50,129,23,60,90,146,128,194,106,241,181,56,115,233,74,111,129,190,234,92,133,22,166,1,165,199,
110,166,13,176,243,243,17,198,165,6,103,9,74,160,89,243,219,20,84,10,158,207,186,96,195,181,228,78,106,222,237,85,94,164,145,42,152,130,23,3,10,103,201,236,63,253,229,159,78,38,147,126,191,63,220,223,
89,93,191,201,39,137,225,24,40,203,173,205,205,23,95,140,162,16,181,88,89,194,98,133,61,33,27,94,236,96,165,149,166,14,43,238,108,214,155,76,186,90,249,204,223,100,104,48,200,66,119,57,115,193,68,209,
82,250,212,59,151,101,92,75,198,115,229,80,248,51,202,232,83,231,57,171,202,173,135,15,224,57,192,36,137,147,25,163,213,183,30,126,90,22,121,187,211,219,222,218,236,246,6,141,102,147,119,194,100,56,218,
219,219,14,194,144,194,41,202,93,94,133,245,186,183,253,24,86,78,179,211,217,121,252,168,217,108,47,45,173,212,215,162,74,82,101,242,211,182,47,48,229,233,93,142,22,121,158,163,4,46,160,198,210,168,170,
123,216,208,196,50,86,8,246,92,68,9,50,254,138,247,91,32,225,249,48,160,91,163,225,75,138,112,83,64,199,224,63,23,169,35,22,58,132,59,38,58,198,166,141,137,221,10,70,77,213,17,217,146,172,17,164,138,171,
192,179,87,210,150,14,57,130,89,119,175,23,233,62,29,13,37,129,176,9,194,218,28,33,197,93,21,6,81,212,108,194,137,91,20,121,212,68,155,116,58,153,192,83,116,122,61,112,132,179,52,129,155,108,181,59,124,
156,160,174,1,125,205,232,51,176,179,178,20,20,10,60,125,171,221,69,85,203,142,20,49,220,215,200,114,70,177,43,211,165,65,106,195,196,110,100,66,55,48,170,135,100,224,211,112,131,89,70,69,78,240,85,58,
118,133,147,231,14,251,90,50,107,149,100,150,46,45,170,218,176,53,197,79,68,166,14,155,110,126,45,71,21,170,240,137,35,239,76,72,247,195,176,77,126,215,21,250,155,140,99,16,220,228,21,167,66,122,92,227,
206,22,19,153,87,252,234,113,154,209,7,214,149,231,248,90,218,88,170,193,127,212,203,70,226,106,34,176,197,69,26,169,90,74,201,243,125,176,213,106,252,191,255,247,255,9,134,232,205,155,55,131,32,120,248,
240,97,167,59,96,103,158,141,44,126,182,247,222,13,251,75,171,85,229,154,186,53,211,138,29,214,110,30,248,101,183,59,237,247,70,131,254,104,50,105,238,31,12,224,94,180,209,190,28,204,170,106,197,68,245,
19,21,129,179,248,249,171,235,34,204,187,10,153,217,100,12,247,8,26,28,180,210,163,7,247,193,98,2,67,41,77,99,223,15,243,28,235,42,226,217,164,221,233,240,57,6,218,42,12,163,91,183,95,128,13,179,253,120,
19,158,190,219,31,76,198,195,201,100,196,235,111,101,109,125,241,90,14,217,62,53,41,248,2,207,159,233,93,142,125,54,16,49,136,193,84,159,146,122,106,238,3,84,210,244,167,51,99,224,26,37,80,5,102,163,93,
89,163,225,57,27,200,102,60,104,19,98,178,115,234,3,73,242,145,207,252,41,100,184,49,219,183,113,79,41,100,225,193,176,164,116,240,176,241,16,118,200,150,148,64,111,69,91,143,214,112,218,92,43,210,29,
102,18,235,243,195,168,45,59,155,123,247,64,239,180,59,93,56,9,186,189,126,212,104,14,15,246,250,248,219,112,60,58,0,171,54,137,103,251,59,219,141,86,11,116,244,120,52,188,113,235,246,44,158,166,73,12,
143,211,0,189,70,97,163,201,104,4,255,4,77,7,67,117,250,3,14,28,174,201,21,212,18,6,217,44,152,245,129,195,59,120,180,184,6,19,177,173,247,8,166,13,135,54,113,215,48,101,48,17,60,184,158,41,181,225,121,
171,107,22,42,173,106,167,155,93,72,189,88,208,224,24,54,62,215,66,75,106,196,60,168,57,199,116,205,57,3,210,253,168,31,45,44,116,75,115,93,4,147,238,112,39,17,107,138,46,202,112,230,151,114,142,210,53,
223,80,132,170,190,22,3,218,120,169,176,137,122,145,70,170,194,48,234,159,15,40,252,127,253,241,31,166,105,186,190,190,14,139,227,238,221,187,160,179,62,120,255,189,47,190,254,85,46,251,230,181,30,39,
177,63,245,154,237,46,227,248,228,188,136,26,246,64,144,84,126,146,54,92,23,212,214,164,219,153,192,105,183,189,189,158,102,225,66,95,88,71,212,209,172,133,14,75,108,103,94,19,97,222,25,101,78,39,240,
115,200,213,7,151,144,176,69,57,6,128,131,16,22,68,163,209,232,117,7,89,158,88,142,23,74,93,161,145,155,131,182,74,241,84,167,98,62,199,93,91,219,120,248,224,222,108,58,105,119,187,8,243,89,188,150,172,
235,94,165,22,115,88,168,193,5,49,70,83,227,169,80,82,121,77,253,37,108,79,96,27,36,146,6,239,206,63,134,5,239,165,53,26,30,193,10,24,73,193,229,139,160,243,10,33,212,146,176,11,188,78,107,214,42,91,48,
40,57,13,132,159,34,134,6,74,246,51,28,161,52,113,87,151,218,217,129,198,118,108,167,169,57,210,93,95,31,210,157,171,101,215,214,111,192,153,129,133,120,190,159,229,25,220,12,76,239,96,105,181,217,104,
129,2,130,5,12,55,15,246,239,238,206,22,119,9,34,188,66,53,157,140,185,201,205,234,250,6,156,43,32,137,37,183,75,203,173,86,103,107,243,193,112,184,15,167,139,113,115,168,132,88,48,35,16,122,142,28,26,
102,53,45,109,227,85,89,163,207,25,188,198,90,190,226,214,126,120,102,96,77,31,67,23,41,234,87,25,223,22,124,105,109,56,67,133,105,9,161,152,207,147,67,1,112,36,148,198,163,172,61,53,42,111,32,128,23,
243,172,95,192,143,102,219,220,48,5,50,3,15,141,163,108,235,238,5,25,240,217,207,80,116,137,38,136,228,114,69,2,106,157,159,151,170,178,93,88,235,31,38,227,209,135,63,123,119,125,227,185,219,207,191,116,
210,7,97,200,30,125,129,182,10,195,144,207,180,57,246,192,106,25,240,204,167,147,97,175,183,170,77,205,13,131,56,240,33,153,132,95,84,222,240,96,41,158,245,87,87,31,109,108,108,238,238,173,77,137,33,96,
81,198,16,187,186,166,12,157,145,41,215,68,152,119,102,153,211,8,252,224,0,199,166,0,195,131,44,77,225,68,42,42,5,251,1,116,208,240,96,127,115,114,15,54,76,119,48,168,209,76,55,159,187,253,232,225,131,
199,91,155,237,118,187,214,232,112,242,243,116,13,150,87,142,222,15,234,241,202,94,109,142,72,54,205,41,81,255,120,182,227,92,157,224,55,247,108,26,37,60,209,122,28,205,225,82,120,129,162,204,47,39,214,
220,192,115,171,2,206,104,220,57,146,185,80,76,111,11,211,238,197,230,137,40,29,110,35,178,84,147,40,27,68,1,66,36,13,62,95,221,163,244,0,12,147,87,142,13,84,155,217,246,144,246,7,95,180,111,111,219,246,
179,63,244,70,120,31,94,224,173,225,33,143,141,243,180,231,5,112,118,194,187,0,95,15,89,131,105,141,130,123,254,248,241,67,56,45,122,131,37,184,19,44,223,203,210,118,187,11,187,11,73,232,145,110,52,129,
17,192,129,196,130,119,2,51,151,121,158,186,9,166,65,41,51,200,49,196,109,177,71,71,75,197,237,97,12,135,14,95,94,205,91,83,144,225,89,229,186,104,57,77,195,161,72,247,136,21,230,224,207,82,76,202,232,
61,41,165,62,212,34,164,142,101,209,104,174,237,111,4,6,172,111,3,112,146,223,47,91,100,129,19,206,170,89,37,42,102,191,186,112,132,196,167,200,184,137,72,104,155,222,37,218,24,120,109,231,141,180,16,
8,206,51,165,93,39,209,203,236,60,222,76,146,228,214,237,23,163,48,252,248,238,7,253,193,210,96,176,252,104,243,193,116,58,190,253,194,29,88,173,91,91,155,240,2,86,215,54,224,72,191,183,189,181,183,187,
3,15,30,68,225,242,202,234,177,56,186,87,191,240,229,251,159,126,244,224,193,3,38,156,228,147,246,221,127,248,59,48,178,44,231,162,12,131,0,190,27,14,135,237,118,7,188,33,198,170,240,239,108,157,129,177,
11,210,76,60,122,116,107,109,253,241,242,210,99,215,237,15,135,75,79,202,84,20,118,229,115,175,160,44,207,117,48,141,157,81,230,169,4,126,235,235,55,55,54,158,91,172,40,8,155,205,13,240,41,22,144,247,
175,125,225,203,124,173,151,239,188,182,56,14,156,81,211,201,8,150,245,210,242,90,20,68,71,238,167,156,122,126,171,112,156,154,116,219,0,25,57,166,91,101,224,117,150,139,72,247,26,53,195,72,119,159,182,
174,69,186,87,115,25,242,18,192,117,35,237,132,183,231,7,65,158,231,190,175,210,180,50,93,157,203,202,198,85,204,22,50,125,175,44,52,137,140,17,217,66,54,228,20,118,20,108,254,118,171,195,85,254,136,208,
145,108,50,152,32,61,183,228,99,10,167,235,69,186,211,152,200,236,230,59,131,165,21,48,154,246,119,183,65,190,211,235,35,229,6,232,175,86,39,203,146,94,15,86,157,232,47,45,195,93,238,237,110,195,61,54,
193,59,232,245,193,127,175,185,216,29,10,234,129,46,158,76,198,112,59,203,171,171,22,69,177,192,197,110,181,134,52,196,97,218,146,125,206,101,42,56,8,148,164,226,86,250,31,54,22,244,42,216,240,132,142,
166,190,103,24,79,204,75,134,164,218,234,155,58,157,42,184,55,26,35,57,225,56,4,255,180,4,19,56,12,34,199,38,233,240,72,169,116,169,203,139,32,221,143,160,243,171,226,73,25,247,162,81,148,69,142,249,19,
145,238,240,86,62,252,219,191,38,202,199,222,251,239,253,228,214,237,23,26,141,230,187,63,249,219,110,183,183,126,227,214,127,253,209,159,129,127,14,63,249,240,253,247,190,242,181,95,78,147,132,40,162,
147,44,77,44,15,206,209,36,232,141,155,207,129,135,191,191,191,95,179,136,213,220,163,28,150,16,152,74,208,24,30,174,4,168,63,48,43,192,231,39,163,17,37,65,45,134,212,171,174,70,177,131,253,184,249,104,
109,101,105,111,169,63,2,135,113,58,237,252,247,140,116,7,95,3,52,93,187,211,57,134,113,80,184,213,44,82,118,28,51,249,114,110,152,184,142,184,0,210,221,17,129,214,51,215,215,84,89,130,193,251,78,111,
16,199,51,88,153,160,39,224,67,204,53,100,115,228,46,223,140,195,249,68,122,47,37,245,197,233,117,187,179,56,134,133,27,69,33,108,33,48,21,117,221,67,204,195,40,164,174,92,97,106,176,108,86,238,154,145,
238,207,61,255,34,135,144,65,160,213,233,130,121,85,195,211,88,166,191,188,66,177,227,146,47,13,222,159,1,128,208,77,174,174,110,212,188,230,224,51,194,180,28,230,44,87,6,67,138,207,97,232,158,121,126,
234,48,51,115,126,177,163,200,72,119,12,38,98,164,201,195,114,98,50,90,162,40,194,140,170,214,105,150,9,238,0,82,150,245,108,48,227,168,137,45,45,36,103,225,7,221,110,23,252,92,56,171,64,89,55,91,45,105,
233,177,25,10,81,49,245,216,121,144,238,207,82,230,196,70,170,141,70,11,60,148,109,176,179,226,24,30,105,127,111,7,206,207,221,237,199,95,248,242,87,247,119,119,247,118,182,97,190,144,244,61,137,225,179,
27,55,159,219,218,124,248,194,75,175,128,69,118,74,7,214,149,213,245,187,119,63,172,184,220,201,90,129,96,145,73,49,111,220,200,160,12,16,0,183,113,54,139,169,208,31,83,221,176,19,146,100,6,75,60,140,
34,174,6,96,20,251,44,105,4,97,222,239,141,226,164,1,206,181,88,104,193,184,136,116,191,134,238,211,231,147,1,167,32,140,26,215,116,173,178,44,195,48,234,81,52,247,194,227,80,44,220,80,110,16,254,88,35,
167,130,170,11,170,13,50,144,101,240,137,74,233,53,82,24,184,72,124,246,21,125,63,152,205,38,152,223,69,215,206,205,179,92,88,4,25,199,81,250,253,30,219,102,62,24,246,65,0,234,21,52,84,28,199,96,7,193,
7,224,251,110,167,231,161,149,109,130,247,94,43,134,35,183,152,182,77,209,7,233,27,41,23,56,221,77,92,89,218,155,60,244,116,96,181,193,180,92,199,155,53,199,62,121,172,180,210,230,69,32,103,170,172,86,
115,250,0,70,123,186,92,255,77,253,7,233,144,208,115,56,158,45,96,238,200,118,38,51,78,255,17,34,201,159,77,39,28,32,103,31,217,154,2,194,246,82,53,45,11,153,20,29,9,209,125,175,215,235,165,105,138,72,
212,16,142,135,160,131,148,50,230,245,135,50,236,56,237,177,158,148,178,170,27,65,94,71,235,188,203,200,156,134,116,135,211,239,225,253,79,210,36,254,210,47,125,3,149,215,214,230,250,141,155,47,190,252,
234,116,58,1,133,117,235,249,23,192,24,238,245,6,237,78,23,150,218,214,230,131,213,149,141,193,242,242,233,96,226,47,191,254,165,135,247,127,156,36,243,215,191,182,118,195,164,90,133,41,117,135,187,205,
249,11,142,14,210,186,156,8,175,202,42,73,210,52,158,70,141,6,55,251,101,20,251,100,218,232,117,226,94,111,60,28,118,168,212,235,243,141,116,191,128,12,252,58,192,158,236,254,101,198,57,47,210,221,199,
142,129,194,107,100,85,26,26,30,13,12,220,68,241,108,10,187,111,50,30,195,14,122,229,213,87,190,243,157,55,222,127,255,195,162,168,54,110,172,194,193,142,41,2,44,158,199,172,16,168,42,44,182,240,60,222,
170,81,35,106,117,251,194,116,22,69,15,34,236,196,101,28,169,210,103,172,246,103,139,116,63,44,131,33,33,48,97,202,162,90,192,187,207,17,225,28,171,58,9,17,126,22,212,56,203,112,31,111,12,81,139,178,169,
26,240,156,51,29,51,210,29,252,185,152,48,119,190,23,194,8,220,204,6,131,45,182,184,6,142,7,174,108,137,144,177,167,1,187,166,17,69,73,146,112,162,16,236,241,78,183,7,231,134,99,145,238,3,103,0,71,193,
72,140,201,159,45,47,124,207,215,42,115,26,189,12,101,112,247,225,55,175,189,254,101,88,80,160,164,190,246,203,223,10,130,176,219,239,131,245,249,224,222,39,143,31,61,132,9,2,111,17,22,208,163,135,247,
7,203,43,160,194,78,111,221,252,165,215,223,253,237,127,225,253,199,63,5,139,41,97,26,182,213,181,13,97,219,19,48,4,67,88,34,30,219,234,14,3,26,152,212,96,182,111,165,242,44,5,115,207,243,188,58,17,56,
157,54,123,189,73,16,20,179,89,75,90,240,127,29,42,174,1,138,215,209,26,254,140,50,89,158,62,155,86,245,23,150,209,198,126,169,25,191,107,42,205,186,126,215,169,101,136,135,85,85,133,227,55,51,228,80,
46,124,198,142,121,20,205,45,139,124,58,77,250,253,193,15,127,248,251,239,189,247,211,173,71,143,214,215,87,51,56,127,136,246,132,75,187,4,29,242,156,37,132,67,5,190,95,94,185,129,116,49,214,40,112,155,
177,244,138,124,220,49,120,74,206,163,83,215,96,54,28,106,188,187,141,192,40,110,69,1,11,157,133,224,112,195,57,191,150,153,52,204,206,115,242,10,105,138,224,234,240,63,187,117,148,107,147,236,11,115,
207,246,186,69,33,65,109,89,70,157,36,195,27,216,164,246,200,200,154,201,68,80,31,105,216,20,160,135,192,200,130,155,24,79,38,224,124,220,185,115,231,205,55,223,252,232,195,187,85,37,110,222,88,131,9,
39,48,148,233,53,141,164,14,68,216,128,166,172,239,183,154,173,238,96,217,114,25,32,138,117,73,246,39,98,150,138,212,240,35,226,28,94,228,158,175,85,230,41,72,247,175,127,243,91,188,88,111,221,126,254,
197,23,239,212,225,180,87,190,248,229,215,94,255,10,242,165,16,120,7,126,248,246,15,126,155,232,199,202,83,146,160,158,87,172,175,61,190,251,241,237,111,191,245,75,255,223,191,255,127,192,157,172,12,218,
80,212,145,94,182,134,168,145,36,134,3,232,176,197,229,56,157,205,224,132,200,49,199,140,55,60,28,238,174,174,222,112,48,62,93,82,178,212,5,243,170,215,27,58,206,178,86,238,231,17,233,254,172,239,231,
24,153,243,33,221,73,91,56,42,11,188,40,85,105,67,85,6,160,188,180,180,242,240,254,61,56,205,127,248,195,223,219,217,222,254,47,255,249,63,247,251,125,74,125,40,219,36,89,17,63,163,231,240,188,208,22,
90,94,94,35,40,99,93,50,84,186,81,92,101,145,214,11,74,99,222,59,84,212,104,248,58,191,118,108,71,175,235,64,186,179,140,180,170,156,32,102,186,78,50,50,34,28,97,144,6,17,174,44,201,219,165,40,252,241,
84,22,179,190,236,118,116,123,168,70,108,68,249,65,216,238,246,176,236,161,18,131,165,149,223,252,141,223,250,209,143,254,18,126,5,199,3,88,175,224,146,75,75,42,7,74,28,182,79,221,2,30,142,255,222,96,
5,237,100,162,252,132,107,183,116,19,46,11,151,16,11,85,83,215,213,58,239,18,50,238,119,222,124,251,188,164,113,37,99,55,206,207,54,247,210,139,15,150,6,227,31,255,228,75,66,70,207,61,255,226,131,123,
31,127,225,139,95,153,19,57,112,187,16,234,233,196,244,99,245,25,207,26,183,200,115,176,240,203,210,68,73,243,60,13,162,38,93,215,33,99,216,239,247,198,160,226,102,73,64,129,0,68,39,49,209,170,99,72,232,
175,133,48,239,140,50,89,150,62,27,2,191,11,203,176,33,85,39,185,25,8,194,128,102,144,177,28,41,142,99,169,220,9,101,174,69,21,249,173,68,248,73,30,135,124,137,79,238,126,8,187,229,173,55,223,28,44,45,
253,155,63,248,63,96,111,52,91,77,77,149,31,210,168,65,166,58,112,185,211,68,179,209,92,94,217,192,70,104,228,206,179,77,231,247,15,96,45,228,163,30,19,176,212,33,127,10,42,25,98,89,14,6,73,211,164,224,
24,207,14,142,55,55,240,174,105,38,25,79,96,239,202,229,152,17,87,147,240,0,148,149,163,198,107,180,219,96,251,73,67,13,133,254,38,89,154,234,44,62,41,230,242,169,14,28,107,57,180,215,117,218,83,49,181,
121,9,5,38,228,189,79,63,6,205,245,63,253,143,255,195,104,52,250,147,63,249,147,78,167,19,6,1,182,201,129,1,253,192,224,72,200,237,99,74,12,248,237,210,242,42,120,148,198,117,68,203,89,46,233,126,172,
83,240,55,93,73,111,86,50,207,250,103,25,69,57,86,230,217,33,221,65,230,246,173,251,143,119,86,242,162,225,185,170,221,106,127,237,107,223,200,114,100,71,68,104,47,71,1,164,1,248,11,49,15,28,50,180,1,
111,26,193,114,220,106,88,128,185,139,107,162,132,21,217,96,148,73,85,249,179,184,57,232,79,71,227,165,207,29,210,253,231,65,198,37,102,75,238,90,76,60,68,136,60,172,209,240,22,240,233,178,12,46,41,230,
116,47,170,106,175,213,88,154,68,253,89,49,238,130,105,156,196,241,243,183,111,127,237,235,95,251,183,127,248,135,240,90,123,189,30,188,177,10,43,1,13,179,168,107,58,127,129,181,229,118,58,253,176,209,
82,22,254,197,167,123,208,155,184,190,147,14,7,96,184,80,122,119,222,182,143,56,178,249,254,231,104,120,178,128,142,195,94,95,53,167,251,137,148,199,156,197,39,132,58,58,89,212,136,204,97,42,42,211,132,
102,206,0,62,39,74,181,57,161,179,213,195,227,197,246,197,16,76,161,13,185,190,229,60,102,234,171,251,31,125,0,58,253,173,183,190,13,3,254,209,31,255,219,118,187,21,53,34,70,180,49,214,4,142,132,154,37,
25,126,20,69,209,96,105,141,8,151,169,232,199,69,117,127,195,221,240,132,187,165,183,229,185,56,221,175,153,47,224,88,153,103,135,116,95,94,30,249,190,218,122,116,11,107,175,73,230,214,115,207,111,111,
111,195,60,130,245,193,45,88,56,208,203,31,225,188,82,29,219,226,195,32,77,146,254,96,48,157,78,124,132,207,232,209,112,184,182,209,170,129,238,211,73,183,221,74,48,176,152,54,62,95,72,247,159,135,156,
177,229,107,215,12,227,153,115,36,215,253,77,231,156,238,181,12,101,172,170,32,27,55,131,246,212,109,201,71,119,167,69,89,252,230,111,254,214,143,255,254,239,239,221,191,247,220,115,183,151,176,177,160,
152,205,38,9,118,138,195,43,186,112,184,195,174,10,91,174,161,46,149,182,50,159,98,255,205,169,240,210,116,220,214,37,106,54,99,205,25,164,146,100,18,21,81,183,100,160,160,150,162,224,166,243,132,247,
199,101,216,207,96,38,185,40,192,84,38,107,67,235,202,245,67,84,186,93,213,222,162,109,163,97,66,75,220,251,154,144,116,134,211,253,88,159,148,39,31,199,209,114,91,238,174,137,213,129,234,239,137,3,226,
32,75,94,124,241,197,175,127,253,107,127,252,71,127,36,16,129,220,198,107,123,46,125,202,70,134,184,129,182,35,123,157,65,179,213,169,232,54,24,49,15,39,193,154,179,2,218,234,145,218,86,146,203,21,168,
246,222,88,127,63,111,81,11,231,120,164,251,7,63,253,219,211,123,222,188,240,234,235,231,133,128,55,34,12,1,78,103,173,90,230,224,0,49,89,112,67,9,157,21,245,14,113,25,161,142,8,20,121,136,49,154,104,
246,77,1,135,109,2,108,227,23,154,72,51,66,202,118,149,134,24,229,243,131,116,255,44,238,231,73,153,243,33,221,13,62,151,6,86,89,163,2,119,165,153,236,237,238,252,254,15,127,63,77,147,191,252,209,143,
214,215,215,151,87,214,9,44,42,187,221,65,187,211,51,17,100,102,197,178,13,190,144,206,140,249,218,133,10,186,19,199,207,203,184,81,166,161,75,146,148,110,51,117,206,198,204,32,163,155,155,227,121,8,73,
210,44,83,137,234,40,102,154,94,255,181,206,36,131,149,72,57,226,77,133,161,143,92,202,168,64,61,215,16,170,40,67,170,39,108,169,144,109,183,131,177,36,215,167,78,95,20,220,180,27,128,177,239,149,94,108,
177,83,217,73,19,185,200,247,245,193,64,244,122,186,243,254,227,159,130,219,251,131,31,252,224,39,63,254,241,199,159,124,124,251,249,231,151,151,215,96,148,120,54,141,227,41,17,51,40,215,195,22,68,81,
163,229,123,88,62,205,101,134,252,16,112,199,75,178,31,233,96,87,237,21,50,39,131,203,87,150,211,29,251,33,156,208,242,7,11,72,23,16,234,164,224,42,174,99,224,120,65,221,22,232,146,156,2,230,217,231,111,
255,4,164,251,211,251,54,159,191,129,187,235,97,27,149,201,20,59,15,49,29,72,74,57,35,132,222,19,198,207,80,232,82,253,145,107,91,230,8,75,249,109,219,238,72,219,22,151,241,47,88,127,23,53,56,146,37,243,
2,15,192,48,208,179,153,252,220,33,221,159,241,253,28,43,115,46,164,59,158,210,68,112,198,42,73,165,237,241,126,122,231,206,157,141,141,245,127,243,7,127,208,237,118,111,220,122,222,18,63,184,236,184,
153,51,70,145,183,73,45,66,28,211,56,19,43,75,188,238,24,4,139,73,183,72,49,98,93,9,166,202,181,172,3,120,224,187,6,159,197,69,255,228,183,210,105,102,100,142,120,109,176,138,174,138,211,253,20,153,138,
110,4,46,153,166,241,189,79,239,22,69,9,63,93,95,191,217,233,244,28,179,153,168,81,77,205,235,71,224,126,197,141,119,144,171,207,112,51,112,142,200,196,155,132,173,208,164,25,179,20,11,172,19,100,44,19,
176,137,58,178,189,191,183,251,123,63,252,97,28,199,127,254,23,127,177,177,177,177,178,114,131,53,94,171,211,237,116,251,92,8,101,169,214,241,30,132,158,143,3,10,112,93,174,134,34,24,139,105,226,164,108,
74,87,152,194,146,150,72,75,219,118,53,238,17,142,121,195,197,110,10,6,23,72,32,109,78,147,120,232,47,231,107,179,254,170,20,119,214,97,3,22,38,233,120,164,251,83,21,214,5,26,184,55,35,132,55,18,37,0,
3,59,41,45,53,79,157,51,28,92,138,197,74,5,91,138,198,39,122,85,105,214,116,140,46,195,23,233,248,113,60,110,54,91,53,167,123,129,28,100,133,65,30,254,99,65,186,99,32,201,148,43,115,175,57,99,57,218,149,
100,224,118,71,100,48,234,87,150,150,137,237,120,153,147,198,225,183,80,98,43,1,147,241,56,34,195,112,4,27,82,212,140,116,31,29,196,191,247,195,223,248,139,31,253,40,43,179,87,191,120,75,231,136,178,226,
142,47,92,232,139,53,122,28,170,231,237,161,184,51,43,152,102,41,97,80,157,124,212,83,133,231,26,167,211,176,51,75,235,35,204,227,3,54,90,108,90,201,105,99,31,30,173,97,38,186,136,235,123,179,202,112,
69,56,89,150,61,222,122,88,18,147,87,171,9,230,76,115,58,25,129,219,203,69,231,124,18,115,227,78,67,88,202,14,53,217,82,108,199,73,75,48,74,219,130,79,217,146,29,115,166,223,146,28,209,103,124,156,163,
71,98,178,55,219,125,249,206,157,27,27,27,127,128,199,67,111,227,198,243,236,84,214,50,60,31,186,110,130,171,29,67,233,137,246,139,183,42,150,3,17,236,139,131,68,38,115,202,252,5,25,57,191,31,131,224,
231,94,12,154,51,99,206,2,200,131,232,20,52,29,48,117,158,87,219,55,98,10,133,108,151,111,246,163,105,61,80,4,160,142,252,136,185,12,89,103,200,153,37,159,160,105,62,190,145,234,83,21,22,183,119,254,198,
215,255,166,102,106,183,158,217,188,22,21,163,21,52,245,127,245,55,95,131,127,7,97,118,247,227,151,133,185,79,234,105,205,52,38,182,88,132,150,175,166,130,114,33,172,146,154,179,154,73,131,84,224,183,
82,115,200,16,227,162,150,134,229,9,52,41,130,126,137,141,219,213,139,72,247,207,58,71,123,153,86,245,53,197,165,100,236,117,77,181,178,16,25,89,148,145,74,102,105,252,104,107,19,252,5,208,43,55,110,220,
106,182,59,71,100,206,50,206,233,50,156,27,225,24,40,211,138,190,243,79,191,191,127,112,112,247,147,143,95,251,202,186,23,37,178,157,22,169,167,146,72,40,31,147,132,38,46,166,45,229,67,233,7,194,141,82,
233,167,8,136,201,194,98,26,193,123,163,237,80,211,156,97,219,33,174,43,36,32,133,100,148,185,182,59,131,13,61,207,115,89,230,137,26,102,125,44,214,225,170,222,44,243,143,239,108,111,29,28,236,35,155,
88,163,17,4,65,81,20,163,209,16,132,202,234,225,205,91,47,72,114,175,180,225,216,49,252,162,6,29,72,22,154,109,11,38,13,205,159,253,182,158,109,110,208,201,246,25,246,188,113,20,63,251,254,116,247,95,
253,238,239,130,235,157,231,229,47,189,252,141,153,152,85,116,48,44,202,44,180,52,230,148,187,0,85,5,166,89,199,105,193,224,143,245,227,76,20,243,154,44,43,35,196,34,178,129,185,141,231,62,178,231,17,
170,30,161,91,210,53,175,146,219,222,207,171,211,93,170,244,100,153,5,122,194,5,4,191,150,140,172,196,173,42,92,139,7,64,59,11,139,64,79,54,105,143,111,164,250,84,133,5,154,24,46,246,112,115,141,9,146,
20,24,135,168,69,92,105,137,89,145,44,201,118,34,162,141,42,55,31,173,120,94,197,41,105,48,122,75,34,30,195,66,95,87,33,89,34,133,214,80,179,202,170,134,47,179,217,133,14,133,52,172,76,220,2,128,218,141,
84,243,190,193,4,196,50,76,251,108,75,227,196,148,204,157,8,215,98,134,176,107,106,13,127,70,153,203,181,170,135,227,221,227,103,47,69,197,228,179,53,237,127,128,109,102,52,81,178,121,212,64,101,188,253,
248,17,19,99,97,134,59,138,198,227,97,187,221,133,185,174,101,206,50,206,233,50,200,245,192,62,139,48,39,58,40,148,143,239,126,250,120,107,243,197,23,238,84,51,183,152,22,96,52,5,205,220,13,38,124,250,
192,206,133,151,73,231,190,130,179,83,27,168,167,172,210,86,22,71,68,13,132,206,157,224,180,154,52,16,8,174,31,228,197,45,116,37,234,76,128,17,192,160,50,245,37,149,199,120,127,22,150,113,229,111,150,
181,79,150,39,59,219,143,199,227,17,92,174,77,144,250,253,253,125,73,29,247,96,71,198,241,204,41,69,195,111,58,218,69,86,60,137,43,28,86,114,41,224,46,113,163,102,26,121,98,77,64,93,213,188,99,138,248,
121,92,131,221,48,169,125,156,183,146,162,183,188,228,97,53,189,253,253,119,224,120,248,248,147,79,190,121,231,155,13,221,232,137,118,44,178,81,53,174,192,177,227,82,81,42,138,50,80,33,237,248,164,170,
154,18,123,30,79,245,12,60,193,82,148,248,186,193,233,49,77,49,136,227,102,206,149,102,137,31,48,223,233,114,247,72,208,135,37,70,9,76,77,133,141,36,40,131,53,161,88,36,131,182,61,98,164,37,25,134,145,
57,54,9,102,107,231,193,232,129,237,79,123,153,101,148,148,79,53,123,143,231,116,127,186,194,162,48,226,163,173,13,235,152,155,134,129,142,77,201,217,227,72,219,102,156,112,205,48,240,103,74,24,158,117,
151,56,82,51,42,190,225,213,32,137,185,213,114,13,106,27,77,227,42,80,172,53,247,253,160,213,238,98,212,189,44,48,75,72,130,30,34,247,231,156,238,174,87,166,121,243,243,206,233,126,68,198,112,227,50,189,
153,9,19,24,167,95,155,146,96,35,179,179,179,117,176,183,11,31,111,54,155,97,24,194,105,63,25,99,27,168,7,15,238,221,126,254,133,179,143,243,84,25,36,186,164,90,2,211,5,147,12,246,60,43,250,131,21,203,
89,37,243,105,163,152,53,156,160,224,180,176,116,42,244,105,48,194,225,231,153,163,43,48,211,156,42,247,133,62,140,7,181,49,2,219,187,80,212,173,158,37,159,135,198,22,81,150,247,189,146,70,70,29,93,226,
220,106,244,26,222,44,6,161,170,234,193,253,79,211,36,65,86,210,70,35,73,17,32,206,136,33,106,209,140,119,254,241,167,31,124,247,149,183,240,160,149,170,212,104,248,135,34,104,200,136,227,244,160,212,
38,122,10,186,163,162,70,170,236,155,192,94,165,102,93,138,181,45,159,220,48,160,239,4,224,123,208,146,198,156,3,168,131,187,31,125,178,181,181,249,210,139,47,31,200,209,80,143,91,186,217,113,58,77,119,
149,139,20,224,114,133,128,19,7,124,46,23,139,183,168,134,164,208,197,88,204,198,122,66,97,117,227,45,18,127,11,241,192,96,136,192,116,120,162,182,13,134,75,22,205,32,102,143,224,139,99,103,141,66,212,
92,236,135,248,218,241,86,145,116,148,126,197,125,131,142,225,116,103,26,123,199,49,248,62,113,14,179,247,120,164,251,83,21,22,143,117,10,135,250,147,60,235,240,20,96,221,147,191,233,146,12,181,75,114,
28,214,166,252,61,35,125,192,56,226,123,48,105,105,214,89,18,14,166,98,185,49,24,141,199,92,204,65,47,19,243,8,100,223,153,107,209,120,174,254,199,133,116,103,123,193,20,208,49,55,27,189,227,202,244,1,
71,167,30,44,214,189,221,237,241,104,8,135,106,183,217,132,169,27,30,28,112,157,48,5,47,167,121,57,13,155,46,134,56,156,18,150,62,178,200,131,57,171,125,152,51,108,37,145,251,60,78,205,58,112,202,181,
184,25,106,69,236,197,182,157,156,171,109,123,5,46,175,226,240,9,110,203,50,68,221,196,196,199,20,154,225,188,173,217,147,78,221,64,194,132,17,116,29,91,230,86,193,38,108,45,234,58,171,207,28,233,206,
188,135,31,126,248,51,88,180,200,118,32,68,28,199,60,15,149,161,99,115,184,72,67,171,244,39,123,63,25,172,172,24,12,4,147,106,10,36,93,8,100,208,214,205,174,232,118,157,110,172,147,145,24,87,136,37,224,
138,200,99,20,101,165,153,209,223,80,191,34,221,99,146,116,123,75,184,188,241,176,119,198,114,58,214,211,72,134,30,40,58,65,85,4,76,185,33,202,89,21,43,7,211,111,169,72,105,99,50,205,169,228,74,6,174,
31,103,139,129,27,233,26,251,149,11,215,109,227,65,211,119,131,16,252,24,177,50,245,219,14,243,181,59,246,60,38,92,176,225,158,125,146,211,157,201,35,234,54,49,152,137,34,139,242,236,102,239,241,156,238,
47,190,250,101,206,47,114,137,41,102,1,28,183,150,225,42,191,211,57,212,159,228,89,71,42,5,33,163,0,12,105,211,95,30,11,101,227,153,42,64,107,162,179,0,78,19,181,54,128,185,246,75,38,81,68,250,106,99,
108,18,82,177,128,115,44,12,130,52,207,145,141,12,159,167,106,52,218,100,136,226,181,2,178,207,176,32,129,49,202,159,31,78,247,179,140,163,25,61,75,117,161,20,134,23,245,233,84,149,249,189,79,239,166,
105,26,4,1,216,86,48,75,220,117,146,81,139,28,55,184,255,201,253,47,252,202,50,173,59,68,146,195,135,131,6,232,5,228,143,247,49,4,225,84,105,163,136,3,108,48,126,234,181,76,155,9,58,33,136,190,216,156,
195,170,14,238,82,116,166,38,32,231,8,46,119,217,192,131,189,254,21,215,33,40,238,158,194,62,224,156,190,134,107,201,200,37,84,102,125,243,65,141,152,242,202,20,239,16,194,85,18,244,145,146,0,71,151,56,
35,179,174,244,205,154,208,47,183,38,132,59,203,210,148,246,8,227,158,196,66,245,56,242,115,193,146,126,188,189,217,234,182,131,32,2,229,199,85,28,232,220,105,88,151,160,228,18,56,62,58,162,221,150,237,
85,189,180,39,15,114,145,179,15,46,45,217,38,147,157,61,169,76,25,19,203,244,179,198,11,225,214,170,42,229,184,173,52,50,146,123,234,44,202,48,102,104,65,198,140,131,118,153,217,47,102,207,202,186,117,
23,187,105,10,238,156,189,72,151,243,248,68,142,74,109,65,152,11,91,24,146,126,180,158,48,47,140,32,100,138,117,114,158,151,73,86,73,134,209,94,74,157,215,236,117,223,120,235,109,246,141,13,226,102,206,
116,104,90,131,73,91,60,89,203,24,206,29,42,25,103,9,75,187,161,109,113,149,120,82,6,206,212,78,103,58,157,133,101,233,179,12,92,37,158,205,132,233,236,20,193,199,13,37,190,54,60,170,204,42,169,77,1,20,
142,23,207,178,193,96,201,113,12,187,174,31,248,221,238,160,190,86,24,38,221,78,60,153,244,202,210,59,114,63,103,121,174,107,149,65,42,81,223,187,216,56,184,19,92,178,209,140,17,174,234,68,12,79,227,221,
143,62,80,85,9,142,9,55,38,224,178,15,161,231,177,103,77,192,30,157,55,3,185,170,179,150,202,27,85,26,21,113,88,198,240,77,163,202,177,71,128,27,101,94,51,117,60,34,182,144,222,177,215,170,169,180,152,
5,152,91,118,91,30,75,219,101,130,146,244,11,89,36,170,96,231,165,41,28,203,56,138,108,13,84,234,44,23,207,225,58,228,192,199,36,239,13,11,22,181,54,148,69,186,147,149,205,52,91,174,169,88,62,92,195,140,
235,42,106,92,225,155,85,182,89,175,75,250,154,250,221,10,163,92,72,161,171,121,45,164,45,162,150,50,207,115,100,254,161,52,159,109,192,103,168,187,224,18,185,83,164,50,109,202,70,91,183,192,101,171,156,
138,189,47,230,123,56,182,108,136,111,64,219,94,56,100,215,184,38,108,181,64,42,123,118,25,255,132,107,49,171,143,245,253,61,211,117,219,178,143,9,75,208,206,75,148,155,34,106,203,231,197,37,77,172,46,
165,29,83,219,66,84,131,163,38,200,17,183,62,99,77,71,47,84,193,103,73,85,149,79,202,184,223,254,238,155,54,79,193,177,74,142,73,56,140,181,180,203,93,29,150,145,11,61,119,197,19,28,234,139,95,115,153,
162,244,122,221,177,235,192,201,210,230,223,5,65,152,34,250,89,80,157,96,17,133,96,60,5,176,200,56,191,32,200,113,192,99,179,50,208,59,80,103,240,79,162,196,10,152,187,114,109,237,166,239,7,245,181,86,
150,135,48,243,187,123,203,199,221,207,89,158,235,26,101,210,52,241,131,240,98,227,96,142,195,46,59,66,72,168,186,210,141,48,211,238,120,120,128,113,37,226,232,102,227,164,158,118,11,245,151,196,114,145,
245,251,75,118,40,51,14,134,82,192,208,206,67,80,103,8,93,138,50,191,145,131,93,162,75,121,236,181,232,126,140,222,50,229,114,214,136,179,128,24,93,19,62,176,105,108,247,9,253,202,152,223,146,15,255,197,
3,79,24,246,109,187,163,216,46,35,0,151,75,241,14,19,37,169,148,233,238,103,183,46,158,243,52,81,71,150,56,204,57,88,241,87,254,102,201,75,114,26,205,86,60,155,192,57,164,173,169,34,12,130,68,204,25,217,
145,42,19,21,93,179,17,249,158,139,232,51,148,164,153,180,38,63,231,224,166,34,142,156,176,231,116,177,236,84,22,148,15,53,70,226,49,202,212,36,37,12,250,167,102,170,224,78,181,228,79,32,232,164,214,86,
166,69,15,97,116,173,140,32,45,111,130,248,200,68,120,178,226,54,141,175,209,210,113,92,230,134,167,148,173,77,241,155,226,236,179,28,6,116,250,8,67,157,124,161,2,79,247,59,111,126,207,246,180,168,235,
88,12,179,200,188,134,73,136,69,25,14,197,226,221,184,206,188,173,192,124,123,48,33,228,49,50,240,176,221,206,132,154,116,57,181,76,154,36,104,76,97,18,13,172,191,10,76,173,186,187,55,183,1,182,197,234,
226,159,253,250,175,191,242,202,171,63,253,233,207,28,164,127,10,225,149,47,45,173,214,227,120,142,90,91,219,63,24,118,146,36,124,242,126,206,242,92,215,42,147,101,105,16,70,23,27,7,45,202,26,130,110,
168,120,234,115,195,97,28,0,56,215,68,26,73,17,13,99,28,105,121,40,169,172,153,21,182,215,235,31,63,14,12,84,248,186,104,56,65,230,53,18,100,95,40,221,39,175,197,222,92,197,173,231,207,188,225,29,67,241,
110,86,116,77,245,91,82,43,5,199,82,179,215,208,135,115,213,39,115,207,5,245,132,76,158,36,65,212,184,66,14,57,105,171,115,173,62,18,105,150,46,226,62,28,251,86,45,221,8,241,232,98,142,184,72,19,112,39,
166,227,209,104,58,25,167,105,12,211,128,244,196,11,102,105,34,18,248,84,91,180,193,237,202,116,102,163,192,250,164,185,85,245,252,219,254,105,124,156,176,75,161,140,193,195,76,211,20,66,119,23,101,206,
171,184,109,79,54,116,207,61,178,40,184,169,165,107,52,85,109,92,159,166,232,13,159,199,101,156,21,247,141,55,223,62,255,107,51,31,215,180,236,132,45,239,34,79,77,215,84,106,79,202,100,153,191,52,152,
128,76,156,68,44,19,133,205,60,75,136,117,140,219,156,40,108,16,69,124,73,108,100,57,84,217,143,216,67,240,31,145,3,224,45,120,235,91,91,91,97,24,222,124,238,5,38,6,226,107,45,45,77,130,48,217,222,89,
199,76,249,49,247,243,25,211,39,82,159,130,206,197,198,169,8,39,173,109,247,26,10,88,26,24,50,7,35,27,205,102,60,155,226,230,225,76,173,48,46,67,221,185,211,50,195,160,225,223,136,34,31,142,123,140,22,
122,76,133,87,143,195,84,213,101,26,74,175,68,247,16,171,210,163,35,215,18,182,135,160,196,140,199,153,102,134,255,133,116,116,117,215,66,97,182,147,92,108,62,198,205,196,164,121,95,103,247,218,164,157,
153,35,50,69,158,181,90,237,43,229,144,83,11,253,82,4,248,155,108,65,177,237,207,206,239,28,255,101,51,221,188,254,61,223,47,177,82,188,98,24,80,94,228,123,123,200,3,30,194,49,102,113,155,137,72,35,25,
116,68,27,163,227,46,115,85,75,247,138,86,47,187,177,117,126,226,124,227,216,85,199,73,100,107,95,155,226,173,154,241,252,148,49,57,207,86,86,213,37,157,21,247,237,239,255,224,216,215,182,232,73,97,223,
74,138,174,113,3,159,67,204,98,180,140,41,253,234,114,76,145,35,112,199,202,192,83,239,29,116,158,187,177,63,157,118,138,130,153,185,20,86,99,150,200,131,108,189,3,89,163,147,21,237,48,184,35,48,187,170,
178,28,79,38,176,205,222,248,206,27,239,127,240,65,146,38,203,75,43,184,8,64,181,225,17,93,172,172,110,207,226,230,4,59,232,32,177,12,5,5,5,71,73,74,242,149,62,91,250,68,240,121,253,192,191,216,56,202,
46,125,108,250,128,69,103,166,220,159,115,82,138,217,193,165,32,130,86,19,36,53,209,31,27,97,53,145,19,67,115,94,22,89,6,199,253,112,184,31,83,247,67,202,242,81,154,207,38,118,84,22,121,174,8,218,5,216,
89,174,14,143,92,107,206,206,174,212,89,158,136,160,39,146,72,44,77,88,196,210,136,219,205,207,183,45,237,210,92,96,151,63,139,17,167,107,28,204,97,25,208,224,190,31,92,45,135,28,243,200,115,110,14,4,
94,106,189,180,61,219,198,62,178,92,84,32,107,35,172,142,156,82,121,77,81,194,113,107,66,218,20,251,203,243,28,254,44,242,116,58,29,69,141,22,121,199,120,211,177,72,250,94,175,239,246,134,106,76,111,16,
251,164,149,87,167,112,85,173,115,207,51,14,214,69,154,54,212,26,85,174,237,232,85,183,185,54,232,188,19,198,36,68,63,218,86,151,63,251,221,95,251,238,91,71,94,9,133,235,29,206,78,43,203,246,88,23,55,
73,243,218,28,131,183,58,191,76,191,191,223,106,78,199,227,30,71,50,64,178,1,199,96,158,130,157,197,175,217,37,72,62,59,56,232,21,162,61,128,127,194,59,222,126,188,125,235,214,173,23,95,122,241,221,119,
223,197,190,246,29,230,8,151,207,223,126,4,7,249,230,230,13,181,64,251,200,153,17,109,242,193,206,103,75,159,136,236,151,141,198,197,198,177,220,9,108,155,144,165,197,97,84,174,175,164,105,111,68,13,76,
11,51,95,190,165,61,209,11,5,43,139,248,111,152,84,112,82,24,29,142,184,159,34,31,29,28,192,12,7,68,1,202,215,170,242,64,122,8,254,172,50,95,87,114,241,90,38,50,194,237,81,245,211,159,136,68,76,49,144,
48,113,113,230,54,241,108,221,143,103,139,55,100,93,67,122,118,35,2,49,125,199,201,96,31,246,107,224,116,215,6,211,41,151,229,0,251,234,116,131,44,79,184,217,181,109,71,166,172,29,134,94,33,67,40,97,215,
107,194,242,164,105,202,241,99,141,105,68,180,185,202,50,111,181,59,198,143,19,98,166,102,77,221,240,165,23,235,152,50,78,210,185,244,202,228,254,131,52,14,78,210,249,199,209,117,231,112,248,188,245,126,
28,219,97,210,248,244,39,142,137,69,157,254,149,156,253,216,132,130,59,11,177,205,95,187,190,154,59,2,146,28,53,59,119,149,169,47,185,172,204,254,176,183,178,116,16,69,57,88,67,117,230,165,221,238,6,33,
70,220,137,7,195,20,86,161,162,242,125,151,27,120,56,178,221,106,79,166,147,15,63,252,224,237,239,125,47,138,162,15,62,252,176,223,31,128,38,219,88,127,28,4,217,253,7,235,69,225,25,132,191,169,185,53,
197,167,243,30,109,159,219,38,20,174,41,47,101,180,158,230,19,158,77,11,182,55,192,201,90,122,78,141,247,10,74,63,43,107,131,136,26,197,100,129,120,232,110,195,105,79,21,77,228,63,106,141,228,98,2,249,
201,227,217,164,217,234,214,215,18,69,195,13,83,183,17,231,179,80,153,76,19,71,91,181,99,104,173,228,133,54,188,246,177,223,159,71,92,29,46,103,217,236,211,112,237,14,46,77,239,60,70,4,179,62,29,145,201,
178,180,174,51,189,42,14,57,243,68,176,111,137,83,120,88,141,193,38,106,182,218,186,42,98,234,253,195,96,90,93,119,190,181,202,85,218,170,52,6,121,179,186,47,169,24,19,244,9,120,175,224,106,240,210,213,
228,20,183,69,107,42,98,50,72,175,96,101,234,195,243,127,222,113,104,15,114,41,17,58,82,76,54,207,133,53,252,156,167,220,91,125,76,94,201,217,239,126,235,59,223,53,57,69,89,7,240,125,91,136,73,103,35,
249,119,87,43,163,148,223,235,129,197,91,129,145,100,170,132,64,157,249,126,183,219,131,93,93,81,170,43,196,174,10,8,17,245,137,131,58,138,26,43,107,55,224,207,241,104,248,104,107,235,141,239,126,119,
107,107,235,241,214,163,215,94,115,218,237,217,193,254,122,146,54,77,234,196,158,8,245,169,206,84,166,159,235,38,20,124,190,209,25,110,106,232,12,154,148,23,147,20,65,119,230,248,85,228,173,164,216,225,
131,192,47,100,130,177,177,233,10,110,249,139,212,221,28,131,64,230,117,52,174,74,139,214,209,220,205,8,236,86,216,126,120,39,116,173,42,11,252,102,230,250,90,231,97,125,45,226,48,40,24,41,74,209,92,151,
45,56,2,94,200,179,60,17,152,26,236,198,26,244,179,249,144,241,168,206,109,68,88,164,251,17,153,52,185,122,78,119,83,91,230,200,158,236,134,84,60,204,49,156,40,10,97,242,200,209,51,71,180,169,119,17,122,
161,118,23,223,33,79,23,1,208,112,228,52,77,66,63,132,185,130,51,56,8,194,138,76,222,84,101,93,217,65,63,218,41,132,176,145,121,199,185,240,202,100,246,43,92,39,36,243,100,195,142,147,198,225,50,187,122,
231,178,47,105,184,82,109,12,135,13,228,147,174,107,219,194,94,205,217,143,89,66,167,174,96,20,82,200,67,220,50,92,12,81,115,241,156,40,35,196,211,101,22,198,201,242,240,224,160,127,99,99,59,8,243,56,
110,155,14,104,244,43,176,28,59,237,110,191,191,212,237,15,186,189,65,183,59,232,15,86,123,253,165,118,167,19,120,65,11,76,231,110,247,227,187,31,129,10,251,238,27,111,188,251,222,123,75,131,188,40,7,
195,81,143,145,170,118,28,19,164,174,211,111,14,49,55,124,126,155,80,204,9,10,248,3,54,4,111,196,29,29,118,102,132,168,10,58,157,14,28,216,179,217,140,131,65,132,144,17,106,30,9,86,186,134,29,8,83,170,
198,131,33,94,25,235,46,193,179,204,225,180,183,232,26,188,50,58,134,73,67,136,186,28,76,56,22,67,47,231,176,35,83,147,108,32,13,142,164,182,58,250,216,39,2,133,229,46,86,185,215,161,224,243,31,254,158,
99,204,106,253,132,12,88,88,173,102,235,88,56,207,89,32,63,199,203,216,68,216,146,24,164,34,141,157,196,226,197,208,198,131,169,139,227,132,75,127,43,34,188,149,182,30,187,174,134,227,132,41,245,109,46,
193,171,96,127,141,28,198,170,213,238,178,199,13,51,29,200,176,41,27,19,49,53,237,156,77,133,229,5,87,166,65,186,217,93,96,104,36,206,50,142,52,64,20,126,63,238,162,233,100,147,239,60,45,199,93,215,36,
72,174,240,236,119,191,243,221,239,49,22,156,151,160,182,173,225,109,175,58,99,243,159,36,51,28,237,191,241,237,111,109,110,109,34,71,192,57,199,217,59,232,173,173,238,52,27,179,36,105,21,120,210,179,
163,225,178,81,45,45,191,135,52,196,254,14,173,0,29,134,97,163,209,124,255,253,159,190,250,234,171,207,221,122,238,79,255,236,39,205,230,237,35,50,139,227,144,101,81,153,34,166,43,89,178,23,146,41,242,
60,8,195,203,140,195,103,26,39,107,184,131,3,82,214,240,146,138,102,194,205,146,97,19,246,41,12,131,187,180,204,202,162,100,19,166,178,225,242,154,108,71,216,234,83,15,195,133,88,206,202,134,64,146,36,
112,254,23,69,17,96,60,43,226,107,57,58,8,90,57,198,125,11,223,100,66,24,162,78,117,36,110,157,227,199,227,129,169,67,13,229,57,5,149,188,99,159,8,115,193,226,234,204,91,220,60,250,217,112,186,179,179,
25,168,160,45,155,123,122,88,9,36,246,4,213,12,247,178,179,243,56,12,163,34,47,40,182,110,77,44,11,88,49,248,148,26,157,200,237,60,40,217,170,120,78,181,10,17,174,229,59,38,205,85,118,157,78,10,135,123,
149,179,47,105,105,30,140,111,206,171,5,245,53,173,132,83,86,84,145,102,219,91,143,162,70,100,200,246,24,149,112,88,6,198,113,158,0,178,213,183,205,134,57,151,249,82,254,141,89,246,57,99,232,16,106,148,
125,250,35,99,186,87,127,246,127,247,173,119,92,211,237,26,141,85,182,80,140,179,109,193,111,108,105,31,43,51,26,30,188,244,242,203,219,143,31,19,67,225,185,199,25,142,6,131,193,176,211,25,74,164,136,
243,249,141,80,209,134,162,46,120,156,210,229,134,116,166,82,31,78,175,141,141,252,133,231,229,127,248,15,255,240,173,111,127,11,44,175,221,157,93,112,21,23,101,12,115,233,161,113,220,207,117,19,10,89,
155,87,28,245,228,30,109,102,158,101,208,153,148,153,175,210,208,166,118,157,192,115,242,34,159,197,51,207,243,69,221,50,106,1,240,197,86,173,113,24,9,89,131,254,8,117,84,99,32,50,18,132,210,181,80,223,
57,69,208,40,85,218,170,239,135,80,230,212,163,144,155,244,57,142,61,140,165,214,214,148,88,64,60,31,121,34,19,28,191,34,243,86,214,37,211,215,140,116,55,179,40,101,211,137,90,78,107,44,39,96,10,209,30,
46,179,36,78,146,116,138,89,215,148,1,253,186,6,64,209,141,89,59,217,96,18,249,141,80,204,195,99,39,29,190,135,87,134,40,57,27,216,111,235,70,162,83,229,206,11,9,48,87,203,116,67,134,183,26,79,104,138,
235,159,186,194,137,41,164,211,233,113,55,79,177,96,176,30,89,117,166,66,215,190,71,246,110,249,53,16,173,224,33,6,154,163,72,119,251,222,165,169,150,119,137,169,245,138,207,126,79,152,162,109,106,78,
173,12,47,181,245,59,68,141,231,91,148,129,57,203,188,6,88,177,160,105,103,217,199,116,228,232,157,74,70,205,182,84,85,0,126,89,145,234,51,140,195,215,122,240,240,198,210,96,127,105,105,188,188,52,158,
37,173,241,184,91,20,112,94,121,76,92,195,221,232,168,207,45,236,168,178,223,157,180,90,9,124,106,58,109,190,242,234,141,127,247,239,254,253,111,253,214,111,13,15,70,22,65,87,87,49,154,4,2,195,44,184,
200,224,243,219,60,2,12,29,142,38,152,170,128,178,16,196,84,206,169,31,47,84,72,151,144,55,136,235,130,221,52,181,127,176,31,6,104,39,149,121,169,12,107,136,92,196,160,155,66,48,134,243,145,91,2,139,26,
142,119,250,187,202,210,44,77,226,168,209,228,107,85,105,228,6,35,237,38,178,106,144,71,99,108,103,101,171,219,44,173,131,52,29,192,72,229,113,4,250,200,19,109,62,120,208,104,54,151,86,86,174,182,242,
252,153,113,186,243,244,249,210,23,182,212,153,213,75,156,196,10,31,208,241,252,0,109,218,138,183,122,205,17,119,136,146,66,113,227,12,42,216,242,218,109,58,192,169,243,107,145,107,203,23,86,42,76,154,
7,194,79,84,90,191,56,78,64,213,50,220,52,200,153,27,107,178,38,8,5,37,53,157,140,57,198,66,85,107,81,89,20,136,203,55,85,4,8,34,243,253,144,187,169,195,167,154,205,54,83,143,213,93,141,45,25,44,193,95,
109,186,185,126,35,84,199,89,217,34,115,227,228,10,167,14,10,9,198,63,94,121,89,174,71,21,0,182,72,208,44,0,110,104,74,197,227,124,242,112,156,4,22,132,150,179,176,29,135,93,37,57,87,162,139,52,41,115,
108,209,49,217,223,79,6,183,184,210,223,141,84,183,140,219,217,204,37,196,226,147,227,44,94,11,110,108,111,111,99,255,0,78,128,113,175,59,109,109,204,120,211,129,1,193,37,129,190,7,111,87,9,234,71,80,
150,206,193,176,55,30,119,202,18,63,219,104,200,63,251,243,191,228,146,113,38,237,97,8,152,13,136,136,58,246,195,224,210,207,111,19,138,138,233,138,108,203,3,115,232,241,22,114,10,34,102,11,43,154,124,
144,201,210,25,76,195,108,54,70,2,63,114,25,76,135,84,225,204,113,51,150,214,128,79,73,110,62,72,224,53,19,195,222,63,216,221,8,111,241,181,240,232,197,238,129,178,170,152,170,1,169,147,93,228,41,83,98,
94,195,39,109,71,9,234,193,3,191,213,6,13,15,63,221,222,124,0,158,252,242,242,90,187,221,70,114,113,242,111,175,170,242,156,145,247,207,140,211,93,18,221,66,133,157,128,140,18,66,78,46,66,57,217,19,218,
48,117,218,173,110,89,219,108,109,3,199,79,52,117,189,54,54,47,37,3,57,189,136,83,72,9,221,82,192,185,237,217,96,95,93,131,163,44,213,159,102,52,252,28,124,91,175,123,41,118,30,63,130,145,91,237,14,165,
82,170,241,112,63,140,34,76,179,228,57,216,128,190,239,245,251,75,7,123,187,163,209,65,167,219,155,78,38,179,201,100,253,230,115,84,64,206,145,65,87,219,84,134,178,117,63,71,222,8,167,14,107,56,113,157,
66,209,166,3,150,75,218,243,138,207,117,132,132,49,49,139,37,240,44,101,77,159,78,184,81,206,226,149,194,221,11,59,51,175,9,66,141,60,110,23,51,56,71,192,76,26,43,21,192,76,68,145,55,253,228,133,233,102,
9,39,161,227,79,131,246,129,219,58,104,181,91,101,218,207,70,46,218,3,102,156,147,174,5,86,237,112,184,116,112,208,111,54,83,240,66,60,175,114,221,210,243,74,80,62,121,30,84,202,47,10,80,115,94,28,55,
152,106,198,182,171,112,107,24,55,167,147,76,86,98,65,134,47,87,17,137,37,113,158,24,218,25,10,125,34,59,151,161,187,37,182,218,235,147,129,183,235,83,7,173,11,140,35,76,191,24,135,75,177,248,160,166,
181,81,17,255,44,218,80,69,161,141,229,238,98,236,134,227,60,46,247,2,176,177,18,185,8,211,20,164,190,106,112,163,192,106,71,240,175,113,215,17,45,175,200,12,171,34,129,178,120,225,22,76,234,137,84,214,
168,103,5,35,179,234,16,77,29,184,52,181,126,116,21,216,240,147,201,56,142,177,105,110,232,135,156,10,128,239,103,163,161,31,248,216,236,83,136,102,187,61,155,78,225,134,122,131,37,88,154,112,255,216,
98,71,74,216,111,202,173,158,186,196,109,249,222,179,224,116,231,176,29,42,35,89,81,113,145,164,179,166,226,210,60,226,178,170,136,135,80,213,220,135,53,69,142,230,202,59,165,229,188,32,217,254,144,158,
129,136,13,76,41,56,168,97,38,240,225,2,205,53,177,140,167,184,172,180,237,128,199,5,13,122,1,110,14,95,59,122,175,98,42,106,207,203,146,36,158,78,186,253,129,178,92,152,253,193,210,100,60,130,23,221,
95,94,1,161,241,104,136,60,19,69,1,250,11,140,187,34,207,100,16,218,130,135,57,199,60,133,41,157,99,20,10,231,1,73,159,74,11,97,208,166,166,218,189,166,179,223,171,202,82,47,84,53,19,125,149,39,231,185,
24,228,129,207,188,96,183,185,2,34,221,124,210,41,102,142,42,200,25,22,196,175,80,101,89,26,199,201,104,52,68,22,106,33,34,173,154,105,94,8,39,137,186,211,160,179,229,133,171,241,110,80,229,104,165,11,
125,250,181,224,97,103,113,100,248,1,37,247,116,170,48,85,100,204,123,138,231,154,202,94,220,221,140,101,68,190,52,193,157,233,204,54,121,82,6,236,188,207,182,235,114,137,129,230,242,98,227,228,85,97,
43,176,108,241,176,49,106,28,106,216,65,29,152,85,93,165,133,221,61,24,214,192,36,106,37,242,139,185,164,187,77,27,2,22,94,160,238,134,117,95,250,190,79,166,48,206,51,195,73,152,104,201,92,11,153,93,112,
135,105,106,5,120,228,126,40,63,162,234,190,58,218,228,9,165,135,29,86,114,105,109,144,56,77,198,195,131,102,179,213,115,7,123,187,219,228,237,98,53,251,112,120,128,223,20,200,121,224,5,254,214,230,131,
102,171,13,91,232,96,127,119,227,214,109,68,171,159,186,196,107,53,252,108,56,221,81,243,160,78,170,74,5,54,144,193,90,83,59,167,18,220,112,69,158,18,158,67,114,206,208,181,216,51,141,181,149,153,52,37,
114,170,215,177,238,152,67,221,26,113,193,151,196,182,196,224,82,140,3,200,146,171,47,153,73,17,14,63,238,201,232,152,198,136,37,123,229,133,40,185,60,187,221,234,246,123,131,157,237,45,238,210,66,61,
165,84,150,101,163,225,1,23,225,43,138,90,194,133,250,131,101,172,118,32,37,77,172,85,6,69,65,185,68,103,161,1,196,33,133,226,46,196,163,77,202,154,235,213,29,215,89,64,8,92,121,155,34,175,54,44,185,198,
31,67,128,100,200,26,86,10,33,226,160,181,27,13,130,170,88,77,247,92,178,137,106,25,162,42,215,117,165,8,23,106,242,56,161,11,206,247,176,153,77,246,90,107,219,237,141,165,100,175,145,77,249,217,78,185,
22,71,76,209,248,34,164,40,29,51,46,147,228,114,159,31,131,95,63,191,204,51,227,189,58,73,70,212,221,92,207,63,14,161,189,231,64,13,83,219,71,62,6,206,33,178,75,138,35,50,38,239,68,107,136,170,85,43,205,
161,67,182,71,172,130,227,28,156,162,169,67,208,123,85,176,33,230,48,75,122,69,218,144,175,165,28,223,151,57,153,3,173,165,217,34,46,146,117,67,77,11,206,65,95,24,39,31,117,185,197,9,24,80,106,75,53,26,
205,213,213,181,233,104,100,251,37,139,229,149,85,48,4,182,54,31,14,150,150,163,176,177,249,240,62,252,16,52,26,81,96,151,156,23,203,209,127,9,78,95,226,112,183,213,113,75,252,154,56,221,81,101,75,21,
200,168,38,161,208,214,152,130,157,134,132,57,200,47,34,45,194,85,115,18,67,216,206,2,12,51,164,247,130,149,200,69,158,83,78,156,40,92,92,198,61,149,53,149,78,73,129,112,248,225,174,216,231,66,121,195,
58,94,205,17,153,172,204,57,140,107,218,29,86,229,120,124,0,166,19,156,58,96,180,34,52,15,87,145,59,30,29,80,164,44,3,135,177,223,95,89,89,221,216,219,123,188,245,232,33,172,129,102,167,227,205,225,160,
226,169,10,133,35,253,115,78,119,65,144,51,10,245,100,101,117,73,147,22,59,245,138,19,56,221,125,215,103,46,11,214,26,32,36,13,197,15,46,232,113,99,105,28,116,219,85,178,154,237,97,75,34,98,237,170,101,
102,179,73,81,208,173,227,225,172,136,182,248,208,56,142,86,43,227,205,221,214,234,94,180,212,117,252,65,54,58,229,90,100,201,195,20,168,69,107,191,230,150,94,176,246,47,34,243,217,7,206,241,232,244,46,
60,14,197,11,28,10,158,43,91,188,138,39,116,89,233,6,189,200,124,81,134,62,30,134,33,43,29,110,199,228,240,122,98,142,110,83,92,98,33,169,244,197,69,230,76,150,111,120,139,60,79,218,107,41,110,187,205,
84,86,68,8,97,122,130,24,247,180,178,124,85,38,38,70,204,51,142,193,241,218,216,179,5,126,99,26,8,140,107,77,165,136,140,72,202,225,9,200,102,225,89,232,245,151,24,4,3,166,222,89,150,56,154,135,180,162,
174,155,211,29,236,125,68,138,136,210,19,212,138,156,42,53,168,42,35,96,248,21,76,59,38,220,22,192,110,53,185,157,88,180,6,5,3,110,57,172,65,84,139,104,196,201,121,235,90,208,26,142,63,19,137,54,156,238,
218,118,225,38,186,33,33,45,199,155,203,81,124,219,25,164,226,180,192,218,141,91,20,71,195,223,194,81,49,24,44,131,157,184,190,222,82,182,123,8,207,210,218,198,77,91,127,234,16,129,95,113,118,31,25,76,
102,155,157,117,106,96,224,49,68,213,103,51,105,177,43,73,45,163,202,121,247,13,105,40,88,233,164,208,30,211,155,240,180,214,179,201,97,212,153,223,158,132,221,110,62,29,100,7,218,78,125,45,147,131,121,
57,58,224,50,46,76,67,58,238,71,31,254,180,221,233,116,59,125,63,12,234,113,224,106,235,201,222,65,52,152,134,221,64,151,205,98,118,236,181,12,84,90,186,63,63,157,144,175,86,134,33,26,23,30,71,27,123,
150,204,35,219,163,132,207,119,236,184,230,149,139,50,140,60,174,168,28,183,164,195,223,56,221,245,177,201,232,54,182,40,20,51,184,227,237,97,103,16,11,91,7,147,141,184,157,28,115,45,167,84,121,64,22,
136,86,147,254,33,100,176,165,73,224,186,13,219,3,9,246,114,81,7,74,29,187,236,184,240,10,81,93,186,162,165,105,248,255,44,68,195,89,90,89,131,229,177,245,232,1,92,162,213,233,172,172,109,60,221,107,19,
166,222,254,25,112,186,27,222,11,202,147,18,6,170,98,183,32,106,52,226,120,138,165,3,101,209,238,180,193,17,67,67,204,54,26,181,229,145,86,139,81,181,33,204,54,156,244,236,66,135,33,204,183,23,69,13,172,
157,162,151,226,57,62,197,194,136,254,155,212,19,215,66,113,136,176,52,92,204,168,147,200,200,228,78,110,138,185,128,234,66,32,38,213,210,218,208,117,113,124,109,113,150,168,113,215,69,125,100,3,124,19,
172,196,105,65,58,76,101,119,138,185,202,11,144,139,73,169,254,178,118,150,201,211,20,220,166,132,122,103,24,45,60,239,190,129,7,198,28,102,76,52,195,72,228,74,213,216,133,19,30,52,6,81,145,244,147,3,
45,15,201,40,85,62,122,244,128,13,92,216,21,129,31,210,138,193,155,3,123,126,54,157,128,232,173,219,47,74,74,52,208,116,138,65,122,80,74,111,47,26,120,85,225,171,244,200,181,88,230,231,175,19,242,207,
151,140,65,39,240,234,215,6,240,130,78,132,114,168,225,136,116,172,140,231,249,204,63,27,132,97,78,221,137,180,45,150,174,187,178,105,19,242,99,14,63,81,91,127,92,228,236,162,214,195,66,101,123,45,244,
253,149,176,245,140,135,239,167,110,28,111,86,173,205,96,34,59,54,165,247,97,136,23,95,121,141,45,178,23,238,188,70,157,22,203,87,94,125,157,129,172,47,221,121,141,159,247,197,59,175,114,112,103,109,253,
166,90,195,72,177,239,250,202,248,98,167,109,3,83,175,170,171,103,192,233,206,137,188,92,228,224,21,250,194,71,98,55,124,158,50,140,154,88,160,31,148,105,154,229,89,218,233,118,199,227,113,69,4,205,202,
66,151,76,141,17,183,203,228,131,164,82,46,205,60,219,47,221,222,192,36,16,92,55,16,216,160,72,145,110,212,182,36,175,238,203,201,117,178,104,235,97,127,138,122,150,24,95,106,194,2,135,102,9,169,174,169,
29,158,73,121,93,129,143,108,200,208,69,205,215,142,5,173,39,153,171,224,68,50,179,16,159,220,148,147,208,168,148,157,138,215,11,119,187,80,210,56,182,28,145,196,195,12,215,184,203,50,48,130,135,172,196,
142,53,1,164,99,152,164,165,123,191,185,234,150,197,242,108,155,194,42,198,5,128,43,237,108,63,138,147,25,167,132,168,208,156,232,7,209,120,43,103,179,89,179,217,82,56,130,183,249,224,211,118,187,187,
186,118,195,132,3,133,92,154,109,109,182,111,60,106,174,222,26,63,240,41,46,200,215,34,248,140,145,81,66,253,92,117,66,190,66,25,19,20,191,196,56,134,211,154,26,8,56,210,181,60,179,112,20,7,142,147,21,
85,134,125,180,72,6,92,0,240,214,43,100,37,41,7,253,254,120,60,154,119,93,102,224,34,229,37,164,195,148,236,212,206,183,40,176,120,211,195,104,23,34,119,168,180,147,19,228,196,72,134,217,71,10,99,249,
24,87,58,124,63,250,48,210,157,26,114,43,27,166,241,78,72,65,92,101,143,53,142,17,63,19,78,119,195,5,22,171,164,114,202,166,110,164,50,133,131,151,101,90,173,22,60,25,206,80,165,96,47,192,63,27,141,6,
238,16,133,51,207,37,177,195,209,136,203,155,185,254,0,126,222,108,54,40,233,81,129,230,106,53,58,149,46,25,99,213,86,77,184,249,137,152,113,23,91,230,41,166,126,160,1,231,55,22,20,1,151,238,158,58,75,
149,97,179,176,61,213,207,52,219,116,96,168,147,100,184,123,158,43,177,167,217,60,47,207,32,153,35,230,170,99,238,191,38,236,102,199,150,91,216,49,47,1,83,72,155,154,89,114,189,57,67,97,70,102,25,120,
41,223,253,222,59,115,60,27,103,26,180,222,9,7,202,245,111,198,219,206,66,139,64,216,63,187,219,143,178,44,197,122,136,202,212,115,193,66,127,237,11,95,220,221,121,252,224,225,3,14,70,48,238,31,116,101,
89,228,73,146,128,143,72,241,72,68,246,181,138,120,26,180,10,199,107,22,113,125,45,165,180,237,78,236,124,134,244,47,215,45,131,140,163,65,120,177,113,204,134,180,200,114,161,45,170,129,33,160,162,114,
131,84,21,1,89,69,40,227,122,110,60,157,114,166,9,94,16,156,246,57,56,240,121,234,26,180,10,123,13,184,103,132,237,249,110,250,17,144,107,134,27,203,243,87,214,111,224,225,207,246,152,155,59,81,86,165,
13,85,74,75,30,43,255,123,70,186,187,4,254,234,58,157,153,76,176,177,149,42,17,182,18,132,69,158,114,218,29,94,15,24,90,25,226,224,92,38,87,225,250,149,193,160,63,26,205,96,195,255,206,191,250,29,56,27,
118,119,119,65,190,217,106,128,212,198,141,231,200,47,119,9,112,34,151,156,193,68,76,83,145,57,53,203,150,153,94,177,56,3,54,154,242,148,89,90,148,113,206,60,219,71,174,117,68,70,152,146,82,147,105,38,
250,118,215,61,165,190,135,146,158,108,130,115,60,206,244,21,71,136,41,51,178,152,194,67,158,106,206,164,145,127,160,180,45,99,116,191,243,230,219,140,41,119,76,150,13,214,164,179,223,88,106,103,227,168,
136,109,215,101,252,224,206,206,38,213,73,97,249,6,156,39,48,16,248,237,96,247,222,191,127,239,209,163,71,220,244,1,158,10,233,67,149,241,158,145,165,0,121,51,218,60,14,166,20,29,119,226,55,187,197,204,
147,124,31,243,84,135,185,214,103,68,255,114,221,50,160,176,66,216,60,23,26,71,144,11,96,105,185,53,119,208,157,67,8,180,239,53,18,236,103,150,71,86,6,119,30,104,40,110,67,11,219,166,217,108,70,97,72,
123,7,173,107,236,240,216,108,102,68,45,192,62,136,227,114,116,182,193,129,9,208,173,253,254,114,125,45,191,29,131,235,89,76,91,243,198,34,139,247,83,135,56,200,77,117,13,175,0,107,177,19,218,106,56,242,
10,11,57,9,31,227,62,99,78,247,66,148,29,209,66,166,51,248,31,69,132,225,177,162,70,51,67,136,128,105,155,194,6,105,69,230,36,215,199,128,124,183,219,137,227,184,221,233,126,255,157,239,191,255,193,135,
89,146,181,90,205,86,167,211,106,119,107,244,124,87,118,34,25,236,201,33,243,29,115,64,237,194,179,36,228,161,217,174,174,168,108,22,179,153,170,134,242,113,199,98,117,228,100,170,129,245,210,144,35,185,
86,67,89,45,108,10,215,197,98,73,246,17,45,108,56,169,73,198,125,227,205,119,88,65,82,29,41,26,102,179,168,151,251,205,149,120,79,112,73,61,169,88,240,4,139,28,191,248,1,224,88,128,227,55,8,252,201,116,
170,236,155,224,87,201,225,207,138,217,39,16,92,83,132,240,229,71,124,4,6,170,154,132,29,248,188,95,196,6,220,232,154,198,194,174,100,203,241,179,161,127,185,110,25,212,26,68,44,121,129,113,168,221,153,
130,249,169,41,26,204,42,49,57,37,196,31,250,141,188,76,3,87,120,44,131,167,125,145,21,69,201,93,178,225,221,129,122,98,243,33,244,67,14,132,45,13,250,195,33,146,1,252,139,223,249,151,212,214,112,183,
194,118,9,13,144,185,121,243,121,206,97,17,8,75,121,173,105,145,68,200,248,78,231,35,150,194,30,190,31,199,126,209,15,13,91,188,58,89,41,96,217,246,213,21,114,62,51,78,119,75,88,231,48,203,179,167,189,
166,108,204,244,204,244,254,33,223,13,252,241,130,166,154,48,165,138,121,80,133,52,188,119,92,16,14,63,187,251,209,135,119,238,220,249,198,215,191,254,238,123,239,206,226,233,203,119,190,96,65,240,232,
243,47,139,126,172,83,100,121,167,114,247,242,132,246,57,23,43,119,197,250,234,171,24,199,244,208,173,251,15,240,82,172,27,107,217,208,52,159,91,181,63,200,70,19,159,49,12,36,20,134,191,91,157,162,61,
109,1,166,170,93,66,109,251,71,235,221,198,74,84,101,157,50,102,254,79,114,103,146,56,158,18,97,6,150,64,192,54,192,122,37,122,115,179,100,86,115,196,97,34,54,240,89,247,49,217,34,175,225,52,75,168,89,
139,225,215,41,92,63,241,91,189,124,106,208,116,114,78,41,123,2,73,197,179,160,127,185,110,153,28,45,172,232,98,227,112,65,37,161,220,172,253,237,88,202,25,142,253,149,30,26,89,194,169,242,160,150,9,163,
86,158,198,76,182,71,120,68,143,78,123,2,209,151,21,39,140,122,253,94,154,196,237,118,231,237,183,191,255,225,7,31,198,113,210,106,53,58,221,65,171,221,171,199,241,90,169,23,148,249,184,109,79,74,83,203,
118,232,126,164,180,204,28,28,204,210,53,210,253,120,165,64,177,213,171,234,177,246,12,57,221,171,186,170,9,233,107,100,54,112,250,45,167,53,82,99,48,166,152,137,16,62,218,104,118,202,34,83,246,204,174,
105,151,106,178,141,32,12,96,140,159,189,255,179,175,124,245,43,237,118,251,238,199,31,39,179,89,111,48,224,80,242,77,103,29,244,254,99,177,195,57,116,46,224,191,240,44,49,205,249,162,76,221,226,232,146,
62,178,141,73,48,189,181,228,182,70,76,183,205,184,25,46,165,166,12,128,237,143,107,139,82,234,78,22,220,35,226,236,218,211,253,214,119,222,92,208,106,78,226,134,105,212,91,206,70,110,85,212,174,202,104,
184,147,101,185,97,165,32,214,164,48,140,176,187,212,100,194,16,161,186,10,148,189,156,8,17,64,21,83,74,18,188,17,228,67,112,228,185,164,206,81,213,44,236,52,84,238,233,146,72,114,21,213,83,51,49,216,
2,23,135,101,161,193,80,156,214,70,230,156,118,44,245,85,205,60,34,150,59,163,173,11,230,77,156,76,25,253,113,133,84,51,9,182,249,10,46,56,142,45,144,228,86,148,194,34,221,169,211,4,65,22,17,87,157,195,
171,171,210,128,106,67,77,205,102,163,217,44,177,158,150,144,189,53,163,22,217,58,220,154,152,168,35,221,187,119,239,222,121,249,165,175,127,253,27,63,251,233,207,224,180,191,253,194,203,245,181,96,233,
134,157,153,42,66,81,52,204,181,132,105,181,176,120,63,92,113,101,25,169,204,65,4,194,190,23,28,171,20,196,149,246,88,251,172,56,221,97,77,206,116,140,238,155,19,77,213,212,177,61,129,224,221,52,91,45,
7,187,171,230,245,219,164,187,114,25,201,206,222,98,146,36,219,219,219,239,124,255,157,205,135,15,135,163,209,250,250,77,16,91,149,203,13,55,218,22,187,37,37,61,77,49,223,37,102,201,102,159,43,131,108,
161,234,173,179,140,195,166,16,223,243,73,50,243,70,127,76,111,189,176,121,249,220,50,17,118,105,56,224,107,173,87,161,214,51,28,59,148,184,60,171,246,116,127,237,141,183,22,181,90,229,55,102,110,216,
205,134,158,69,22,194,208,147,201,136,201,194,145,118,157,232,195,193,9,135,213,160,40,123,200,135,188,1,115,49,114,90,107,144,225,194,40,23,177,169,200,9,209,106,117,52,133,245,97,182,38,65,39,172,210,
166,52,117,146,210,108,64,71,154,38,103,162,14,237,112,126,173,182,58,217,188,60,73,19,103,73,178,245,240,65,167,211,115,92,151,101,210,52,121,188,249,0,78,202,78,187,123,172,173,123,176,183,187,191,191,
219,237,246,234,113,134,163,131,253,157,157,86,187,19,4,193,21,82,205,128,33,131,65,247,11,218,240,158,165,29,149,182,107,139,161,13,112,201,95,192,160,146,106,250,205,212,141,242,42,105,212,50,176,222,
154,173,46,115,137,82,174,220,227,197,39,45,53,59,118,145,8,16,114,249,225,135,31,124,245,171,95,109,181,154,31,127,242,73,158,38,131,165,37,190,86,216,31,10,71,23,163,222,226,181,158,184,31,225,152,72,
174,41,244,215,54,225,125,146,82,224,224,195,85,181,44,250,172,56,221,17,112,14,75,94,170,142,108,59,194,141,117,162,180,13,230,73,4,238,182,90,221,168,217,132,133,196,198,134,239,135,224,130,116,192,
130,93,90,233,118,251,160,185,30,62,184,31,53,26,223,252,230,55,255,250,175,255,26,244,216,173,246,115,77,209,220,211,251,51,157,88,170,69,84,112,151,156,37,166,138,99,25,131,176,63,211,56,204,78,113,
106,3,45,97,57,221,45,75,23,241,62,87,243,238,127,150,221,212,181,253,13,249,108,187,240,89,229,190,249,189,119,22,181,218,68,122,169,23,245,210,3,109,210,80,78,154,204,242,44,33,210,53,108,29,216,106,
181,166,179,25,57,125,178,6,224,80,84,143,244,177,231,49,222,23,52,122,20,70,149,193,37,226,51,245,250,75,212,204,198,67,224,97,99,16,86,133,147,205,22,123,231,25,242,95,195,146,33,236,127,134,182,105,
177,211,224,137,154,152,242,229,228,206,152,102,211,88,100,59,157,52,154,45,47,240,143,181,117,21,2,187,189,102,171,93,143,147,167,105,28,207,64,97,193,242,186,194,46,208,69,150,194,109,92,120,28,215,
240,130,205,35,149,156,98,231,90,57,52,114,97,202,203,200,107,102,142,95,169,44,172,101,48,64,22,54,224,204,32,244,48,69,160,72,109,177,230,192,206,0,174,11,58,107,22,199,187,59,59,239,124,255,251,15,
31,60,24,14,15,214,215,111,193,181,194,222,4,70,203,135,61,85,57,135,174,165,170,195,247,195,92,65,102,111,240,67,16,28,180,46,221,56,170,20,176,127,208,149,182,44,122,246,156,238,4,34,197,139,229,162,
64,231,90,118,26,78,20,139,184,206,103,161,65,202,60,232,110,16,193,187,111,119,97,81,129,247,237,7,161,68,223,208,131,159,40,85,124,124,247,227,215,94,123,245,165,151,94,250,111,127,243,223,190,184,250,
197,177,152,78,196,212,212,84,49,135,186,170,46,60,75,204,164,129,229,4,232,130,145,12,44,197,138,91,72,41,102,162,189,108,223,51,174,185,224,110,35,218,128,30,88,211,144,98,172,203,42,106,75,248,82,173,
243,220,239,189,253,207,22,181,90,226,181,42,215,235,230,83,105,140,91,145,198,83,176,93,137,57,183,104,181,219,19,116,3,13,96,181,6,103,185,214,70,168,53,10,156,233,134,58,131,52,58,211,89,24,90,32,173,
39,126,211,81,101,84,38,182,241,185,81,163,174,233,107,43,23,173,125,3,128,96,28,32,56,74,101,53,157,142,96,224,217,100,140,77,88,93,103,60,28,113,2,187,192,29,238,68,65,232,123,254,116,50,198,78,226,
74,205,176,248,179,17,4,72,183,24,79,167,97,20,21,121,30,79,39,69,150,193,209,87,20,57,242,199,131,110,173,202,209,193,1,140,163,41,163,215,237,13,96,144,120,50,201,72,89,131,103,113,201,46,208,121,158,
194,109,92,56,63,101,107,2,140,121,93,179,140,217,36,13,197,147,20,65,165,26,169,132,191,203,112,81,198,243,125,56,237,27,173,54,184,165,216,43,12,115,240,160,52,2,176,70,7,75,107,157,30,66,79,238,221,
251,180,217,104,254,202,175,254,234,95,253,21,158,246,253,13,233,69,121,49,107,171,60,56,230,90,11,247,35,109,99,46,211,252,198,118,253,96,154,224,227,57,221,9,224,62,55,190,254,127,246,222,180,201,178,
228,60,15,203,204,179,220,125,171,165,171,151,233,25,12,54,138,38,105,41,130,20,37,10,24,16,32,35,72,202,180,69,128,12,235,167,152,225,176,191,248,191,152,244,55,19,144,68,201,212,39,69,88,20,9,80,10,
110,18,77,104,48,3,206,210,75,237,183,238,122,214,76,191,91,230,189,85,93,213,93,85,93,93,221,51,80,207,160,209,115,251,173,115,242,158,229,205,119,121,222,231,161,157,185,145,198,141,180,97,67,88,64,
141,109,185,16,20,178,189,9,156,238,206,115,186,115,81,153,51,157,76,229,165,43,187,186,219,82,112,245,243,160,130,37,144,110,46,57,98,221,142,73,238,108,40,249,245,250,67,120,48,126,244,163,31,253,163,
95,252,69,120,179,78,242,73,145,136,151,20,174,30,122,248,175,141,182,17,4,140,93,9,142,240,181,106,196,196,219,229,175,181,122,137,28,153,135,121,57,236,192,38,180,137,153,237,11,55,233,234,230,165,243,
226,51,232,106,23,167,17,211,158,121,244,57,190,210,20,254,176,43,129,109,39,65,53,64,154,12,144,119,41,144,75,104,158,102,74,147,68,197,49,119,211,145,162,44,198,94,102,137,131,8,49,167,59,145,195,74,
24,124,57,88,198,94,231,142,48,228,43,73,45,67,41,132,41,13,185,62,113,55,59,20,37,151,178,56,216,223,227,114,34,92,145,241,241,81,76,231,98,215,126,124,184,15,217,232,100,2,31,31,36,141,70,73,157,123,
66,141,39,203,108,89,148,5,236,155,143,63,249,168,221,238,130,231,130,3,207,166,211,197,98,214,27,14,119,31,63,66,22,227,102,115,185,88,112,214,254,248,209,199,85,89,246,7,131,253,253,221,193,96,52,220,
220,124,51,145,238,140,9,100,244,121,157,53,74,99,147,246,66,153,58,31,119,188,42,186,216,128,139,106,36,13,219,241,199,113,225,56,209,157,157,123,85,89,252,241,127,248,147,7,15,30,252,246,111,127,231,
15,255,240,95,191,245,211,113,181,104,87,203,198,69,231,122,14,210,221,201,28,137,242,180,54,154,32,163,88,94,173,136,214,25,155,68,10,27,208,204,167,181,152,158,60,125,242,24,220,27,60,90,247,238,221,
79,209,203,104,175,121,33,60,142,94,235,236,53,35,221,169,216,236,121,23,60,235,177,170,97,239,205,247,213,254,166,218,184,167,119,230,106,62,113,83,36,17,17,73,52,229,199,123,72,24,24,39,64,240,218,197,
176,58,167,127,234,193,207,252,213,7,127,254,31,190,255,167,223,252,214,55,191,251,7,223,219,110,223,211,164,35,31,108,174,55,161,109,61,49,41,159,148,113,155,240,213,102,211,147,221,221,39,150,46,245,
246,157,29,164,234,37,228,61,78,116,93,231,92,120,111,9,48,165,60,36,217,158,59,3,116,35,60,25,120,101,126,137,116,9,131,87,155,69,13,240,147,131,58,147,58,186,83,203,197,172,40,114,210,137,132,184,169,
132,11,94,175,152,60,93,24,9,240,245,54,81,36,228,47,5,25,123,150,231,228,119,163,38,35,122,201,42,107,246,99,109,90,197,12,174,233,60,105,179,14,130,31,1,17,38,46,146,96,193,156,142,119,170,86,54,229,
33,128,162,42,32,122,26,109,110,245,135,27,16,49,109,109,239,116,122,189,37,2,139,187,36,96,53,135,224,27,92,76,218,104,60,120,251,11,105,218,88,46,230,221,94,31,162,137,249,100,58,218,216,200,203,98,
62,155,101,217,18,246,1,8,212,33,10,131,159,234,117,122,39,227,113,127,56,188,127,255,33,92,46,8,202,90,157,14,248,188,136,106,97,136,59,43,242,173,173,157,151,217,25,242,108,217,104,181,94,102,135,193,
25,90,173,184,4,197,54,236,26,98,26,81,166,1,122,138,105,170,68,217,56,110,103,113,163,210,85,155,239,197,25,155,115,143,51,28,109,194,215,124,255,253,247,127,225,23,126,225,100,124,50,159,84,177,27,60,
255,92,124,28,231,181,160,125,24,38,12,54,94,237,213,143,251,81,23,73,11,235,172,230,155,27,19,138,234,232,240,160,211,233,36,17,74,79,78,103,147,249,116,10,219,73,28,167,172,86,29,83,179,169,246,227,
138,162,32,243,154,56,221,249,20,252,196,122,234,106,67,131,47,112,57,236,210,228,177,138,58,170,221,83,221,196,37,120,103,21,195,142,52,207,151,48,14,192,88,112,141,209,192,245,71,106,208,210,205,237,
205,59,127,243,225,127,185,255,224,193,151,191,252,149,167,187,187,28,158,56,203,223,206,94,73,26,135,235,147,52,219,107,60,15,159,67,132,186,19,30,254,147,241,97,7,210,100,237,32,250,193,75,61,155,182,
90,29,8,192,197,230,244,185,224,56,23,201,225,120,27,203,57,242,179,210,56,238,213,224,25,99,81,85,242,94,13,146,137,66,33,197,132,71,57,104,78,86,24,157,156,229,21,71,224,252,187,145,242,147,84,94,185,
130,206,143,47,5,77,68,108,134,98,197,17,15,118,242,203,131,186,237,78,199,117,206,73,239,214,124,207,147,95,137,151,13,222,47,44,215,121,56,173,12,34,105,33,107,97,84,30,51,55,5,221,33,19,197,144,235,
33,69,236,4,178,194,185,32,247,124,126,1,137,222,198,230,22,252,241,232,104,31,115,70,102,79,198,77,166,134,255,164,91,56,227,199,5,14,5,73,92,119,48,200,151,75,174,40,189,204,206,112,230,58,95,233,56,
70,240,220,70,148,105,232,154,32,35,128,230,174,72,125,198,166,202,33,225,54,105,127,26,15,14,170,172,229,178,230,179,54,207,30,199,186,242,173,47,142,222,255,219,71,223,255,193,15,190,245,171,191,250,
189,239,126,183,211,86,47,60,23,115,246,199,158,216,39,12,220,178,49,51,246,10,187,38,227,113,124,35,88,212,198,156,125,252,232,147,34,203,51,131,29,189,254,160,15,62,107,49,95,124,250,201,71,195,209,
6,132,0,188,93,11,250,201,248,130,55,161,198,195,124,50,135,227,231,204,48,43,117,227,220,27,156,163,19,13,241,138,102,19,97,137,4,137,44,235,98,223,29,24,21,245,116,183,167,59,221,232,14,63,218,21,94,
194,154,200,238,34,228,246,1,55,98,144,17,117,226,102,11,183,128,63,188,251,238,151,255,227,159,253,199,187,119,31,64,20,204,143,1,124,149,228,133,19,218,216,136,77,152,161,90,5,118,70,28,159,174,188,
154,188,52,55,56,26,130,164,1,50,80,120,67,32,188,234,244,186,16,136,64,62,241,241,199,31,14,71,35,216,143,217,239,172,159,139,56,84,95,48,13,206,72,5,142,184,175,205,129,113,121,155,152,227,253,16,239,
33,177,80,34,26,118,1,104,74,100,137,174,82,88,198,66,218,76,237,86,66,227,126,148,86,30,122,124,207,21,119,83,89,103,28,243,199,186,110,16,89,150,192,16,97,69,112,201,170,213,62,22,168,117,105,51,22,
180,62,145,132,69,196,229,231,172,179,225,162,208,16,150,10,100,76,158,231,64,32,148,124,49,183,182,239,238,239,62,217,219,125,130,101,35,178,153,158,156,244,7,67,146,126,90,30,30,236,195,58,209,25,245,
6,139,57,50,50,195,67,122,231,206,189,195,131,189,189,167,79,120,12,24,92,236,230,246,157,241,241,225,116,58,129,175,12,57,35,141,113,37,215,142,207,61,75,215,117,166,76,121,14,126,157,67,93,0,120,72,
229,192,57,151,35,22,195,149,13,188,206,229,81,175,209,93,38,173,101,220,90,216,178,81,47,26,40,163,67,12,104,235,199,129,23,45,138,109,212,130,136,12,209,191,95,249,217,187,239,255,245,135,95,253,169,
159,250,198,55,127,249,175,255,250,111,120,244,236,249,231,226,177,251,32,248,198,60,115,94,125,4,247,9,184,217,10,131,10,184,237,150,230,240,9,42,111,99,240,0,101,110,179,5,53,215,42,7,121,61,28,176,
219,235,182,218,173,229,114,121,124,116,8,95,3,66,105,236,244,209,113,20,245,111,234,218,122,102,122,30,177,190,85,78,119,202,76,131,246,182,212,25,137,81,160,150,70,15,189,117,51,135,181,243,150,107,
70,200,119,129,148,202,70,17,16,92,209,191,224,82,140,203,85,206,120,105,34,161,180,189,222,112,62,95,248,137,98,65,105,60,39,111,13,242,59,226,89,208,157,235,20,146,72,7,158,46,198,51,58,6,184,194,213,
193,138,225,188,152,65,152,143,175,64,9,91,240,18,206,208,233,118,136,100,98,113,116,112,0,238,120,107,235,14,78,117,81,12,120,165,28,153,120,182,245,203,112,96,92,193,230,127,249,223,254,15,248,29,206,
141,12,135,81,148,53,122,199,237,173,7,243,39,166,198,22,0,92,77,8,82,198,71,7,121,81,192,119,158,205,102,171,202,186,23,188,196,50,155,146,17,112,206,110,72,60,10,175,35,151,120,225,176,221,118,111,243,
206,93,129,212,107,243,113,235,206,102,118,212,195,162,59,134,251,53,149,96,147,40,245,236,201,170,194,209,237,154,171,102,161,51,69,94,182,17,60,113,88,179,16,152,80,147,254,141,181,57,25,31,15,135,27,
215,59,14,94,88,154,58,168,173,93,233,45,58,102,251,20,69,72,44,96,157,103,3,254,8,211,195,102,206,228,125,36,119,144,208,176,185,67,95,68,152,42,34,234,213,117,222,116,89,11,130,113,184,248,139,233,116,
123,231,46,60,202,151,57,23,63,0,161,161,201,188,49,184,65,193,169,155,153,105,44,225,99,176,193,33,93,240,83,228,49,157,171,232,153,87,255,249,251,123,69,94,6,76,4,151,171,224,59,183,218,237,108,185,
132,92,184,221,106,189,253,206,187,198,231,164,134,244,166,208,167,227,53,33,229,116,202,82,121,37,97,134,153,248,11,235,233,248,184,63,218,96,16,134,239,67,89,81,24,96,60,68,132,202,46,204,165,115,45,
27,199,217,133,246,244,237,177,144,243,232,192,96,229,209,149,42,108,77,202,119,198,217,201,98,22,175,184,66,231,7,89,156,160,123,216,71,64,244,122,102,66,155,191,157,207,111,240,232,141,40,109,214,141,
174,238,36,58,177,66,158,109,75,91,34,81,44,4,88,36,18,241,199,31,252,191,139,124,65,34,120,145,224,144,16,34,169,91,205,230,98,185,172,202,18,156,215,151,191,244,85,235,199,218,195,185,104,191,181,60,
65,121,238,122,130,74,0,87,150,113,210,59,74,78,123,180,83,94,239,101,108,226,51,94,205,32,10,222,22,58,110,233,26,47,190,83,173,118,103,58,57,118,57,94,229,52,73,168,189,109,3,104,85,180,201,56,107,213,
65,246,135,149,18,12,239,207,113,156,182,186,93,209,28,113,170,32,166,129,68,96,12,182,178,204,231,19,49,241,46,7,252,145,159,142,101,64,81,69,20,125,136,196,187,89,111,125,203,54,234,154,199,97,2,207,
117,14,117,71,49,47,215,13,2,145,222,249,54,16,168,207,90,213,188,109,210,138,99,28,100,68,49,240,184,171,186,128,61,63,130,51,151,240,116,23,137,199,151,32,28,161,219,31,101,89,230,135,42,158,115,46,
73,207,141,111,123,145,211,130,173,189,138,218,139,164,153,163,191,43,155,213,162,145,23,176,174,152,25,183,249,71,224,76,199,199,251,85,94,9,61,20,233,158,112,158,9,103,130,16,128,70,176,147,60,207,126,
252,225,143,190,252,213,159,230,119,130,133,15,185,146,29,43,189,38,89,118,75,156,238,167,109,12,115,84,193,27,149,210,216,160,103,110,130,75,108,87,35,0,76,135,165,153,158,93,50,13,30,160,243,100,211,
140,5,183,97,232,143,3,216,139,242,86,241,29,172,249,166,227,129,238,183,108,11,27,250,42,59,178,227,18,18,83,150,177,208,43,145,164,241,225,225,34,19,20,145,140,206,16,236,17,254,188,204,50,148,87,74,
83,72,198,255,235,251,127,251,149,175,254,52,250,223,154,251,39,145,31,51,53,23,229,200,220,75,1,231,12,89,220,45,48,247,198,188,123,132,120,175,101,115,120,114,151,141,94,107,158,133,66,87,210,104,104,
140,33,29,60,64,224,137,145,161,135,70,151,195,208,144,13,132,15,126,228,21,177,188,49,62,113,200,165,95,87,157,78,55,112,186,207,26,67,248,126,109,216,0,104,226,223,50,151,155,85,218,247,10,195,120,55,
127,7,30,2,16,155,91,231,98,127,243,57,221,185,111,245,44,207,250,89,155,50,173,188,141,143,152,188,24,5,242,254,93,250,56,222,38,70,36,183,175,59,120,18,18,140,26,210,170,57,152,225,75,154,117,171,101,
179,170,165,159,86,213,34,51,67,243,60,81,93,23,7,123,251,37,81,12,121,181,112,122,165,53,239,134,142,52,169,148,160,210,124,221,213,103,75,158,151,19,157,65,125,203,156,238,207,218,104,95,221,139,132,
132,218,4,30,116,229,65,255,66,254,103,86,186,68,86,121,228,74,192,69,19,240,71,84,181,133,218,234,25,157,49,2,182,48,35,65,234,146,13,55,2,203,19,59,129,12,212,122,47,201,213,119,34,125,197,147,130,211,
223,221,123,92,82,216,238,235,197,202,239,49,36,145,93,32,184,135,92,180,208,186,11,228,211,195,181,47,202,145,69,81,154,138,133,177,142,110,131,221,215,87,160,52,23,81,16,207,86,76,78,210,254,40,74,12,
113,75,195,154,123,253,17,60,61,184,229,146,191,141,137,134,65,68,107,124,253,138,250,38,43,93,120,136,141,27,141,20,155,8,113,186,115,231,158,23,79,3,163,104,145,180,7,249,137,197,73,209,152,104,106,
176,169,225,247,79,43,234,9,62,254,124,237,92,236,111,8,167,251,42,23,240,140,224,124,125,80,113,235,117,216,16,51,240,138,98,52,226,254,175,83,81,51,79,123,51,72,248,202,233,8,162,13,110,144,177,155,
163,252,183,38,112,32,62,227,143,62,253,88,116,177,16,96,25,177,168,125,232,7,81,65,64,164,58,7,131,33,184,218,36,142,195,32,8,203,198,5,181,244,91,230,116,127,46,167,157,165,247,183,214,44,200,64,175,
58,26,40,166,208,136,176,225,72,61,4,74,165,33,0,140,152,125,23,89,165,120,102,0,99,43,249,118,207,162,91,164,83,66,137,121,195,53,54,220,176,210,213,129,61,178,112,67,42,79,70,173,87,54,156,147,62,121,
242,8,153,2,61,65,40,7,75,1,179,205,30,138,243,209,141,209,38,143,212,4,151,70,150,246,66,180,141,102,110,79,188,9,142,180,149,94,53,115,239,57,156,238,173,234,100,156,244,198,113,107,144,141,217,171,
165,177,217,220,220,58,58,196,74,22,239,42,180,245,18,187,13,107,33,40,153,107,171,169,128,101,137,235,82,81,83,47,38,86,7,198,211,38,198,156,52,135,240,179,195,26,33,163,231,113,186,127,38,133,78,111,
129,211,253,141,180,49,33,23,163,71,220,37,221,101,68,5,254,98,210,115,244,180,97,245,173,194,225,21,126,234,232,217,192,249,249,124,145,45,23,75,91,179,44,27,4,207,53,165,47,162,15,202,237,96,110,22,
55,27,141,237,237,187,216,155,175,42,169,161,249,129,15,78,203,34,44,169,220,30,167,251,165,120,239,76,202,32,44,190,112,220,179,195,126,162,178,216,40,196,253,72,176,165,150,100,183,9,49,95,75,204,168,
157,143,218,144,111,12,145,107,107,60,235,1,244,51,84,189,190,238,231,186,56,84,71,46,66,15,71,50,186,150,3,61,4,121,24,198,175,217,229,98,81,100,25,3,4,34,153,160,168,195,16,149,102,168,35,238,33,6,210,
160,225,198,22,243,79,49,211,1,234,140,93,46,71,246,51,75,175,156,149,247,28,78,119,120,82,218,229,114,214,232,247,203,185,241,245,169,180,217,30,109,108,28,31,29,209,241,224,226,198,20,108,199,42,76,
55,82,137,49,33,202,202,118,187,29,9,148,161,185,185,125,215,203,79,170,218,68,147,180,211,46,150,174,42,237,127,227,116,255,204,126,47,167,214,73,26,132,38,65,55,150,141,110,81,44,90,229,172,27,136,144,
56,61,201,178,197,228,100,140,220,182,228,137,40,221,35,100,95,180,154,248,15,21,105,129,115,81,119,15,220,80,127,56,146,44,213,179,15,122,137,63,230,107,23,164,251,173,113,186,95,198,6,223,115,122,162,
253,148,184,102,204,154,246,122,15,68,96,93,35,71,56,186,143,146,2,201,136,39,201,49,86,245,136,116,70,210,104,159,147,178,164,51,124,249,142,110,245,84,127,106,103,199,106,236,239,128,84,245,139,60,155,
76,198,21,246,131,209,151,19,17,91,14,113,134,135,221,59,45,240,116,173,215,136,155,153,204,163,55,24,200,113,60,39,12,31,249,69,57,178,102,250,35,173,204,45,48,247,198,182,202,233,124,145,176,150,210,
247,216,42,78,30,53,123,79,219,219,111,205,119,121,136,12,54,134,36,109,111,108,152,227,241,33,228,122,176,208,241,241,49,124,201,202,83,134,243,70,67,251,42,110,164,41,234,164,39,219,119,238,19,64,166,
102,224,217,163,230,54,88,13,23,135,225,92,60,149,194,139,163,101,212,69,177,90,28,254,69,172,57,124,99,27,6,76,125,38,109,80,169,178,252,28,124,47,102,56,66,9,123,161,136,33,68,94,92,55,186,243,50,143,
203,89,71,121,109,106,139,115,81,211,227,163,67,120,24,144,123,147,210,7,244,83,198,192,127,210,54,238,4,58,71,85,27,207,22,41,35,63,13,240,86,189,254,96,48,18,6,116,21,104,192,130,250,43,254,200,237,
35,221,47,195,251,142,175,180,112,147,75,102,69,217,25,149,213,201,31,36,8,12,174,125,77,64,124,132,165,80,75,194,49,210,209,227,92,219,5,46,33,167,82,149,140,212,48,215,249,145,26,163,215,32,161,83,56,
192,108,62,57,216,223,77,168,202,204,233,171,33,176,71,150,101,254,0,65,129,218,31,205,138,44,53,196,25,253,94,111,56,216,144,234,196,42,255,85,86,210,246,231,228,200,138,195,73,56,28,62,12,55,87,25,60,
215,38,102,29,20,44,184,113,87,142,246,210,200,233,237,217,147,221,206,206,94,107,107,99,190,235,56,118,132,32,173,217,186,119,255,173,241,241,225,120,60,54,36,30,169,136,186,140,121,38,215,198,146,220,
157,237,109,19,55,152,220,155,1,162,123,173,205,90,199,59,179,93,205,77,92,121,174,234,176,56,30,160,189,133,18,233,107,177,193,132,8,119,200,207,240,247,82,126,130,180,178,53,7,74,92,202,132,191,109,
140,78,156,53,197,100,16,96,165,240,108,236,237,62,178,4,215,102,248,30,106,121,149,165,69,206,143,74,135,242,177,243,74,123,226,96,8,235,92,219,56,65,73,135,187,95,105,44,143,73,73,215,48,7,0,226,170,
25,163,103,16,217,133,15,91,94,22,183,201,233,126,57,27,233,74,137,192,154,57,39,191,134,133,241,37,64,27,138,43,156,178,129,154,145,39,219,209,1,32,82,221,69,162,251,137,63,251,32,186,95,169,234,192,
30,210,64,123,77,34,35,245,193,222,99,158,179,130,4,144,217,99,112,123,68,98,205,74,160,18,138,64,188,68,7,203,175,41,59,74,154,147,77,26,105,227,167,54,127,102,183,60,96,110,120,10,171,112,140,49,241,
136,165,231,230,191,9,207,48,112,42,250,42,42,131,235,54,209,123,239,225,104,142,35,125,20,6,118,114,136,139,12,225,182,158,52,122,78,71,173,122,41,151,146,186,202,240,44,77,167,147,2,5,32,77,128,140,
58,183,242,206,240,56,110,110,223,99,98,36,238,155,28,181,70,139,164,179,177,60,106,215,153,8,221,125,78,169,144,47,178,201,242,172,209,104,126,198,191,23,67,81,172,223,156,196,209,164,189,57,36,52,217,
241,128,235,7,220,62,134,87,104,177,92,22,158,133,25,190,62,226,66,169,146,79,153,160,244,194,132,157,130,95,17,35,239,100,146,38,237,118,251,222,131,7,113,103,9,71,174,242,196,243,223,25,143,50,230,154,
177,111,40,223,34,167,251,229,120,223,133,25,32,16,177,122,42,61,125,1,243,148,97,9,6,129,254,112,106,204,95,70,56,52,101,248,127,83,143,34,23,61,113,187,78,100,9,241,227,131,253,39,139,197,162,200,115,
190,91,176,61,100,89,206,34,23,76,221,199,40,124,179,98,65,161,122,33,57,8,200,150,218,157,246,131,7,95,24,154,65,106,210,165,206,125,229,77,19,141,170,186,228,52,56,111,105,52,223,243,106,153,123,99,
206,206,56,157,150,39,82,116,131,235,180,44,122,90,207,154,195,202,36,91,203,189,72,25,185,150,81,204,91,107,37,64,12,35,112,91,106,235,134,235,72,165,15,44,177,30,116,182,139,164,53,44,166,189,106,17,
24,154,69,157,205,41,226,126,40,121,173,36,205,226,152,196,195,131,72,223,68,155,107,148,99,105,230,206,221,102,233,247,26,54,240,92,148,181,192,92,214,109,120,98,89,60,23,201,17,251,132,136,112,91,141,
188,206,186,216,233,210,2,193,63,58,216,205,115,236,148,203,8,42,82,19,113,201,92,48,148,60,43,33,133,113,217,217,196,91,193,158,63,26,13,55,183,118,96,9,54,107,35,76,127,9,187,41,65,67,241,29,59,133,
116,215,196,193,114,187,72,247,75,217,200,4,136,246,72,66,193,49,156,95,81,94,181,53,101,107,240,190,140,169,220,235,90,124,178,115,77,213,152,168,105,237,42,175,84,164,142,14,247,10,202,175,241,245,86,
154,133,239,67,51,145,143,203,60,63,50,194,201,217,18,121,25,8,192,6,195,1,92,106,120,6,102,102,62,208,253,227,122,204,187,87,77,124,153,116,37,37,4,126,46,210,93,202,216,105,146,188,106,60,99,244,181,
175,191,71,55,62,182,76,209,192,131,21,222,211,55,171,12,118,184,89,163,191,132,61,15,133,164,106,82,40,170,102,179,41,49,73,69,214,174,160,83,220,227,228,235,56,28,142,32,164,183,81,178,223,189,147,71,
233,198,226,176,91,76,197,55,34,138,36,200,121,121,216,136,143,209,116,160,175,164,200,255,205,180,49,87,39,39,129,248,162,217,106,191,209,20,207,94,180,208,183,144,168,203,70,8,117,225,14,243,193,131,
91,131,14,197,173,101,220,176,197,164,39,177,130,82,203,197,124,60,62,6,31,53,155,207,185,207,0,238,131,57,146,106,97,146,241,168,35,226,44,21,54,8,35,14,104,48,24,236,220,185,175,52,118,111,32,5,76,218,
57,73,178,38,126,236,33,10,3,140,194,226,192,120,241,219,226,116,191,156,13,239,226,184,163,51,243,148,140,59,94,204,42,229,113,222,154,85,39,214,200,124,20,234,182,211,17,70,209,176,161,26,251,246,208,
242,176,26,177,66,30,31,29,194,143,103,203,165,76,122,90,199,15,49,95,28,97,102,242,131,238,60,99,31,121,86,226,126,191,191,185,181,77,29,97,93,186,170,167,187,81,20,47,221,146,19,67,25,63,80,162,186,
76,212,28,231,79,140,235,213,51,101,110,80,91,228,92,155,216,171,189,87,220,237,83,174,146,19,211,208,31,106,25,213,89,60,127,122,208,218,122,212,222,238,102,211,94,57,43,178,37,114,88,34,176,149,217,
153,4,76,184,154,197,215,58,67,214,128,222,172,57,128,164,241,238,124,183,141,213,174,136,220,182,98,118,89,41,229,121,52,60,118,24,163,196,73,109,82,102,21,223,88,155,107,148,99,45,209,67,61,199,6,245,
211,234,42,73,27,151,47,253,22,69,142,156,19,205,86,81,98,63,69,99,153,236,82,235,169,202,114,145,47,146,180,201,212,218,108,3,47,146,35,44,54,115,239,209,54,139,130,110,140,160,11,196,255,236,105,130,
77,212,92,150,89,74,143,25,92,52,220,147,39,39,199,112,150,60,203,168,253,146,192,254,143,5,172,186,226,68,146,203,58,20,134,56,95,2,150,228,9,114,153,62,253,114,244,182,179,242,93,177,140,227,86,86,47,
59,23,33,221,185,38,241,154,144,238,23,216,136,148,22,11,157,113,221,93,5,217,218,115,11,133,52,36,179,98,148,35,165,47,95,237,194,238,42,30,170,237,90,11,183,100,158,141,136,50,188,233,100,236,112,60,
22,103,18,147,40,130,180,155,48,10,86,114,77,79,85,172,68,238,180,50,66,245,227,32,182,26,14,134,240,111,20,167,92,237,177,26,14,157,53,109,131,159,22,161,208,98,84,189,102,241,201,231,33,221,73,239,6,
135,165,44,122,216,87,136,103,196,8,139,2,208,40,12,76,72,146,136,183,220,79,240,33,208,97,81,155,120,158,118,39,105,55,218,255,116,177,88,42,145,15,18,113,148,40,40,2,144,207,202,182,222,174,186,155,
157,42,219,202,142,90,132,120,96,10,7,47,148,110,86,128,101,39,122,176,204,83,202,196,245,126,190,228,13,181,97,56,229,149,200,73,192,71,180,90,157,139,108,246,247,158,238,238,62,134,80,164,63,24,93,158,
8,101,111,247,201,248,232,176,209,106,61,159,6,250,217,227,156,75,3,109,189,120,23,110,233,152,203,87,38,232,12,10,161,138,20,86,130,141,139,150,105,187,168,102,93,112,107,92,185,95,102,139,147,241,184,
40,48,106,64,158,134,186,166,247,77,75,201,148,89,80,194,196,202,26,104,157,145,68,221,110,119,177,88,244,250,125,79,103,138,122,211,73,171,112,101,66,131,31,1,204,184,66,186,115,217,65,5,68,249,141,114,
186,23,88,187,46,100,74,252,242,199,161,112,86,121,149,109,177,113,23,22,10,57,228,244,115,35,42,8,59,59,230,243,164,95,169,74,33,2,26,171,137,53,142,181,172,242,124,121,124,116,4,78,170,38,214,92,6,78,
25,129,62,136,92,77,232,150,72,65,67,178,68,100,148,239,245,122,217,50,3,167,165,152,51,199,66,204,82,117,93,59,115,121,169,42,47,95,201,155,179,151,12,63,143,123,210,15,52,170,48,75,244,138,42,131,108,
19,7,126,123,10,32,86,248,11,254,1,231,81,54,145,178,219,217,113,233,198,179,70,167,162,6,45,255,32,97,100,120,162,112,53,59,1,87,160,181,28,223,109,168,136,128,191,68,167,175,194,16,19,139,38,122,22,
52,169,213,179,220,136,16,136,40,175,159,248,166,218,112,58,115,37,176,37,3,38,47,178,25,143,143,26,141,230,157,187,247,159,99,115,46,24,149,165,79,245,85,193,159,204,123,129,247,81,157,177,129,159,97,
27,95,142,228,168,89,84,81,249,247,96,147,144,208,42,207,225,114,241,245,120,124,20,152,66,25,244,200,15,83,144,125,21,214,89,79,25,196,239,82,66,43,128,8,107,54,155,166,141,230,108,58,109,182,187,50,
247,174,26,206,77,173,134,0,173,113,46,210,61,146,17,46,60,195,141,35,221,243,5,228,92,7,219,119,239,17,31,255,149,249,243,2,99,148,147,178,212,249,197,68,74,86,66,68,198,170,101,34,126,165,137,208,19,
249,123,29,58,169,210,149,1,197,126,112,116,32,92,96,10,129,68,216,223,208,129,180,196,121,125,35,185,218,124,92,122,243,17,182,10,94,120,50,153,180,90,237,197,124,158,54,219,50,99,72,75,141,235,24,124,
150,248,59,161,182,178,47,192,115,18,221,167,215,167,124,197,72,119,234,226,105,18,80,73,156,182,76,32,239,161,26,210,0,160,17,36,108,211,54,141,105,84,243,199,16,213,195,205,168,42,255,122,187,48,160,
196,35,202,240,127,73,54,83,117,167,190,224,56,156,74,34,216,140,110,61,147,210,227,72,89,160,136,247,212,0,111,166,205,117,46,58,143,202,158,103,195,20,55,176,63,194,235,218,239,15,151,243,57,162,219,
34,211,238,34,2,19,178,239,217,108,2,145,83,146,166,221,110,15,231,227,202,106,49,159,144,240,178,184,42,66,24,148,227,163,35,133,53,160,33,137,50,184,233,201,49,222,224,52,129,204,177,221,238,192,135,
147,201,24,142,211,106,119,188,15,142,170,178,200,22,11,184,255,253,225,136,85,60,105,55,82,76,56,37,220,109,148,92,40,47,15,69,152,59,177,113,138,40,162,32,98,16,64,39,162,126,172,127,132,224,43,20,139,
130,185,247,40,29,214,126,160,29,73,23,60,125,19,2,190,74,2,145,34,14,158,30,41,120,157,58,94,65,12,94,141,6,82,156,233,34,163,237,243,25,164,59,59,138,40,137,94,5,210,157,72,126,45,3,11,174,128,116,71,
133,247,154,17,149,240,102,151,148,14,115,161,240,220,138,50,188,22,97,47,100,220,34,3,29,56,219,97,250,147,134,74,145,72,210,150,202,135,167,20,91,89,255,224,225,68,1,203,85,248,237,138,130,52,79,191,
71,124,18,53,199,10,112,181,17,65,73,157,144,197,2,29,22,23,22,57,227,110,68,105,230,50,56,72,128,13,94,22,233,206,213,2,184,68,175,20,233,206,213,62,77,93,48,199,125,233,32,54,22,201,136,150,176,75,75,
37,207,46,50,36,163,160,131,26,78,157,152,54,151,68,31,172,22,100,86,40,196,157,115,28,46,219,82,193,68,145,162,65,20,71,26,23,71,88,59,140,0,124,67,245,205,180,129,224,249,170,23,93,235,85,145,226,140,
13,71,155,21,242,12,130,211,57,128,56,127,180,177,121,124,124,0,209,202,253,7,15,159,60,254,4,222,155,225,104,180,247,244,73,62,202,54,70,155,143,63,253,8,75,78,73,154,101,75,143,178,81,39,227,227,78,
167,59,155,205,22,179,233,219,95,248,226,163,199,31,195,3,13,126,106,113,48,195,42,192,189,7,203,147,99,176,129,77,85,249,173,165,204,243,253,227,199,198,196,59,247,238,137,130,132,99,89,35,195,81,132,
39,6,151,41,217,208,228,10,54,42,178,88,195,213,129,31,2,95,236,170,40,57,148,198,18,169,136,221,171,213,116,188,212,113,101,58,130,247,118,190,38,108,111,233,69,18,33,50,74,12,137,62,176,210,166,105,
206,67,186,75,88,81,219,27,68,186,195,74,224,50,6,94,54,182,153,207,102,40,202,153,162,40,109,163,217,40,241,107,214,16,23,207,103,19,184,23,16,144,151,200,208,210,134,125,5,226,101,1,163,213,117,179,
221,137,137,143,52,176,74,240,251,77,74,162,177,86,107,153,32,237,228,70,123,238,97,46,41,43,203,113,104,4,233,138,22,153,53,198,5,209,241,17,229,70,188,155,17,107,24,27,239,96,2,216,72,184,202,4,14,105,
157,15,157,12,51,14,242,195,233,229,2,173,182,24,202,177,114,245,21,145,238,94,61,11,151,241,10,145,238,164,237,97,252,232,128,120,18,35,10,142,88,13,225,129,100,218,18,229,58,180,59,221,60,207,99,4,62,
163,11,139,201,103,161,124,72,89,98,153,211,36,112,59,209,247,93,112,156,144,180,43,241,102,204,103,84,99,209,23,101,138,225,162,212,190,103,253,210,54,126,108,136,131,160,155,58,87,138,236,189,87,187,
232,240,100,33,196,241,60,27,221,211,135,251,123,72,40,216,31,126,244,225,251,240,57,236,123,10,25,126,179,201,201,9,132,31,41,248,166,229,50,77,18,120,139,224,225,40,202,226,206,206,253,110,175,15,158,
11,94,30,58,78,132,202,81,195,97,243,248,24,82,152,201,228,4,142,48,24,110,108,110,221,129,255,60,193,247,39,154,77,38,237,118,247,238,253,7,112,47,142,142,14,16,216,185,247,4,214,241,246,23,30,198,196,
90,137,10,55,218,52,134,83,70,9,120,146,41,249,226,184,39,133,87,78,155,197,17,78,95,193,207,213,149,226,190,59,131,69,225,13,66,166,114,74,216,194,236,180,94,253,160,148,14,152,95,91,5,250,70,175,65,
201,52,178,158,103,45,18,176,149,141,145,84,248,2,164,123,108,146,192,198,123,83,72,247,189,167,143,171,162,104,162,34,193,146,194,180,120,58,134,43,123,152,164,13,91,141,225,75,246,71,27,240,87,69,150,
165,168,105,130,248,178,86,179,13,247,2,46,245,189,183,222,129,93,7,243,211,6,24,87,147,147,241,221,251,15,73,33,173,34,162,62,199,197,57,56,239,166,29,113,133,132,169,123,156,23,183,51,38,208,216,99,
49,110,207,29,210,192,156,169,84,237,191,55,233,20,215,150,233,216,35,95,108,81,190,115,234,203,88,218,55,193,28,119,198,156,223,127,88,154,162,182,162,245,105,61,98,158,5,189,201,249,92,25,233,46,160,
22,172,78,155,219,70,186,43,210,34,103,15,237,165,121,168,59,195,20,60,36,230,5,15,86,147,144,144,52,117,73,108,173,248,4,163,86,232,28,222,55,225,247,57,117,28,35,67,131,66,140,173,240,90,24,235,1,35,
24,105,187,85,215,253,70,108,78,38,227,95,253,149,95,254,179,255,244,159,152,154,230,166,206,117,13,186,228,231,35,221,185,100,11,199,73,83,172,212,140,54,183,224,125,128,159,106,119,218,71,7,22,210,186,
222,96,88,44,151,188,61,194,101,204,145,41,31,197,214,2,85,244,20,246,249,102,3,146,71,120,176,26,13,108,53,18,84,51,35,26,104,180,129,187,3,255,57,159,207,18,170,151,99,87,123,48,156,158,76,246,119,159,
222,125,240,22,220,161,10,153,203,146,218,143,193,123,225,77,31,59,106,79,196,203,65,40,35,221,177,56,32,187,55,59,108,166,123,195,221,30,91,250,24,122,59,26,192,145,168,141,25,62,212,74,65,218,249,114,
166,163,182,96,138,18,188,66,185,194,47,179,188,48,171,119,50,164,233,156,101,235,32,91,233,86,204,24,171,95,215,64,186,131,175,135,173,162,7,73,242,198,38,184,155,217,228,4,60,20,120,171,102,179,181,
115,239,45,248,219,131,221,39,94,192,195,221,217,185,119,176,191,11,158,107,107,231,238,254,222,147,2,54,114,226,26,4,215,182,125,247,222,114,62,59,58,220,95,204,167,189,254,40,137,87,35,56,156,189,50,
27,76,237,170,48,15,72,123,6,49,151,35,61,28,225,39,97,223,114,5,62,57,24,19,18,95,59,141,34,213,182,242,122,45,62,74,226,72,202,179,104,120,97,99,205,155,46,23,59,2,0,85,147,108,34,39,143,235,136,249,
202,148,78,139,204,60,188,185,204,51,113,25,164,59,223,198,213,212,167,80,226,221,60,210,61,142,88,90,131,158,43,166,61,162,129,38,203,79,36,139,231,24,33,109,21,27,184,145,7,7,123,120,209,243,2,159,218,
184,34,241,65,69,88,9,217,5,55,54,239,48,238,102,117,28,225,248,9,147,174,20,213,83,55,20,99,25,73,16,172,144,1,249,237,242,37,109,32,105,42,105,255,199,123,102,110,236,92,240,151,87,191,232,234,34,209,
151,224,34,225,40,252,2,60,254,228,35,240,47,253,254,16,114,211,141,237,237,217,201,228,233,163,79,227,36,30,12,70,221,126,31,242,241,241,248,24,94,3,140,8,148,246,84,209,122,255,201,99,56,193,214,246,
14,243,59,31,29,30,60,125,252,105,130,209,19,218,108,239,220,61,220,67,14,104,136,187,248,205,132,72,57,77,155,7,240,209,167,31,67,20,64,72,203,74,77,135,161,86,181,26,127,93,165,117,78,52,93,100,126,
36,210,73,206,78,132,17,85,176,123,149,89,198,240,40,100,82,35,90,59,148,224,101,149,0,238,237,80,196,187,94,247,132,12,28,14,205,93,69,37,84,68,196,114,69,175,52,36,0,174,72,67,142,34,132,127,110,213,
198,81,74,90,138,226,92,185,244,64,252,7,215,224,168,64,119,111,12,196,77,16,49,193,243,195,47,33,236,196,144,10,66,246,7,219,0,209,144,112,199,67,7,214,54,241,14,196,225,237,72,217,184,128,103,175,40,
152,144,137,58,3,142,138,159,54,176,12,236,169,67,6,62,134,73,65,95,31,247,82,6,134,17,155,17,85,33,234,150,74,2,247,3,177,120,71,186,46,185,77,95,179,84,21,253,129,28,135,53,242,0,139,46,140,243,89,57,
79,167,192,146,74,154,2,198,1,105,42,4,17,123,15,210,147,102,42,243,194,221,17,65,240,94,56,233,45,28,65,12,149,10,59,208,171,226,116,63,131,116,231,202,43,108,59,17,117,145,185,15,229,148,17,117,95,14,
59,141,222,216,220,92,46,22,101,89,10,106,131,187,184,218,246,58,189,164,145,108,111,223,177,206,48,93,178,144,189,173,157,152,133,82,16,37,67,83,105,88,74,84,213,105,100,185,122,57,27,221,129,68,220,
150,16,218,126,146,45,232,57,113,173,98,222,106,54,10,124,206,235,165,98,214,229,235,159,235,198,145,238,239,126,233,171,242,134,55,210,119,222,249,242,58,93,114,179,213,233,116,251,235,148,202,195,205,
205,59,119,238,175,219,60,120,251,221,51,180,203,224,215,54,70,219,103,104,151,119,30,188,21,108,32,126,192,53,119,27,3,44,183,43,45,224,102,123,10,197,78,185,138,17,142,254,115,144,238,76,88,130,12,237,
4,138,210,232,121,162,4,190,171,97,34,99,39,28,166,84,164,71,61,114,210,86,240,148,76,202,248,225,26,78,76,32,186,132,108,23,227,119,114,178,248,72,58,22,251,130,101,68,242,82,179,188,144,231,62,229,227,
71,50,178,115,182,221,193,166,87,238,67,53,154,148,74,31,30,236,62,37,109,77,188,8,240,201,225,225,222,209,193,126,171,213,49,162,196,39,104,0,231,249,88,157,12,16,225,139,13,223,98,50,62,70,40,249,96,
216,233,246,100,202,118,13,233,14,7,96,205,52,237,86,178,184,28,255,112,66,125,134,175,221,170,218,16,161,181,151,56,84,36,158,64,225,12,237,134,216,209,66,241,208,130,251,122,181,199,48,24,47,58,79,216,
35,230,143,175,211,180,205,42,238,198,196,116,124,1,51,69,56,161,105,245,117,144,238,106,197,241,224,117,145,95,5,210,61,246,45,80,29,234,139,235,63,224,213,231,69,223,156,32,39,248,243,219,119,238,41,
95,57,246,87,214,48,99,36,177,244,57,161,52,50,44,247,122,250,196,152,79,73,7,23,55,85,143,148,101,250,51,238,123,95,207,38,214,170,175,202,158,42,34,218,88,224,180,179,229,178,204,11,216,246,79,166,147,
135,157,13,7,183,67,67,30,165,39,46,158,212,137,211,209,245,206,117,29,154,99,234,18,190,201,20,207,50,168,224,86,34,219,74,102,146,68,139,59,192,157,86,149,114,107,168,38,128,10,48,108,131,114,223,21,
22,107,178,44,231,8,8,121,172,156,236,183,76,53,47,156,180,146,76,138,160,101,175,215,131,128,6,41,27,211,180,215,29,32,225,1,236,154,144,94,145,128,2,227,159,41,224,197,138,15,209,216,90,134,143,129,
123,147,24,83,233,51,237,14,126,109,174,209,171,106,119,123,212,75,61,197,233,254,224,173,119,214,91,16,237,94,159,189,30,188,11,108,179,185,189,227,121,223,33,96,73,32,37,196,118,170,181,130,216,92,43,
92,82,39,161,4,111,104,112,47,161,235,195,144,78,235,181,135,124,241,149,112,152,8,157,43,29,10,243,36,42,65,166,118,170,85,49,169,113,146,196,121,1,105,47,74,189,144,15,50,235,188,49,1,200,77,27,85,130,
81,167,86,195,193,0,197,247,232,82,55,91,45,105,40,209,35,129,160,226,186,66,124,131,231,116,103,205,17,162,194,112,23,229,209,110,125,4,130,213,179,232,63,172,240,118,220,36,79,198,10,233,190,114,147,
167,127,0,203,25,30,161,126,17,26,94,84,231,206,179,129,39,254,204,137,53,247,120,110,20,125,158,24,125,39,42,187,10,155,208,185,105,28,170,36,171,93,73,3,20,68,13,30,239,206,179,150,109,167,200,37,95,
117,84,177,25,217,45,149,159,88,125,232,210,234,234,235,121,21,72,247,215,79,241,236,69,95,46,143,116,215,150,52,120,52,236,234,13,182,25,140,54,23,203,57,6,16,164,238,197,95,217,114,93,134,234,158,34,
83,136,73,35,30,13,188,91,179,217,236,247,7,115,234,51,52,210,20,153,14,211,148,27,142,216,35,51,200,64,11,171,96,246,81,138,131,98,154,194,137,172,50,200,0,81,49,13,164,113,207,180,59,210,56,126,45,72,
119,248,214,21,22,142,106,172,107,18,148,71,105,143,206,117,54,20,46,41,158,21,72,144,159,145,226,148,213,158,226,117,32,164,187,35,194,222,68,197,214,48,159,138,25,141,182,32,101,45,17,132,69,117,204,
10,131,42,235,249,33,88,125,135,174,161,244,157,242,98,9,219,73,127,48,96,33,187,180,145,178,248,94,8,139,82,133,36,218,149,170,207,32,221,99,106,148,61,47,143,150,57,171,128,175,83,34,129,236,139,149,
55,201,233,206,129,20,1,100,237,69,63,192,58,180,65,221,72,230,41,28,51,233,36,65,59,111,221,134,188,236,133,228,27,88,7,242,204,214,94,189,46,38,156,42,74,176,80,59,234,10,54,13,101,239,186,12,130,230,
35,157,206,117,35,175,45,219,68,244,179,144,101,100,89,54,157,76,225,204,5,108,248,58,202,76,231,168,174,122,170,28,69,117,71,231,79,85,99,105,163,43,173,135,72,87,175,118,209,9,42,17,191,201,20,207,86,
110,52,142,86,80,193,252,44,210,93,251,160,63,216,20,185,110,59,147,182,139,252,36,101,155,36,193,215,0,252,72,138,13,25,132,2,80,138,99,169,243,133,91,253,104,56,68,112,83,85,83,97,7,167,41,224,245,154,
206,166,76,112,8,111,26,36,80,152,125,123,133,183,8,149,44,140,171,82,238,83,176,232,27,21,76,171,192,234,167,214,58,95,235,173,140,154,126,221,62,33,207,206,189,183,144,38,193,203,74,121,196,153,23,79,
92,21,55,61,255,151,91,209,183,82,166,114,42,111,229,3,204,245,114,195,216,158,238,150,122,204,124,237,16,3,162,0,42,41,177,67,160,57,47,231,158,129,157,174,164,210,195,97,31,30,126,194,244,113,75,172,
3,191,207,102,51,184,65,204,216,55,232,15,25,117,204,0,246,182,106,213,170,90,184,165,231,102,20,78,119,210,237,118,23,229,209,76,180,193,229,59,86,216,96,236,5,10,134,146,178,204,205,178,224,154,53,104,
167,40,158,242,51,196,63,224,245,8,100,202,148,39,163,168,36,99,2,12,63,160,216,215,109,206,61,14,129,31,106,2,253,121,214,13,237,117,113,168,239,134,245,69,158,216,188,180,77,223,216,135,38,131,141,248,
19,215,58,114,105,102,235,96,67,8,70,172,158,224,90,226,104,253,56,149,54,99,221,252,212,194,29,82,15,84,222,55,245,149,214,115,238,247,122,209,53,124,177,205,101,142,243,234,108,72,23,30,11,180,96,67,
40,161,200,107,205,51,214,70,134,194,207,216,84,203,166,73,115,26,233,17,160,25,167,72,112,194,217,116,6,175,211,187,95,252,226,119,190,253,29,8,139,224,73,185,115,103,11,188,21,53,209,18,230,225,156,
205,230,240,139,216,205,227,52,73,219,237,118,19,21,188,169,228,134,183,160,78,219,117,185,104,212,72,166,28,113,22,105,188,38,5,119,234,248,255,107,46,89,81,86,72,254,206,132,25,58,223,76,179,60,27,124,
11,54,105,163,129,202,7,162,68,233,120,156,135,43,95,4,232,71,128,11,50,32,58,214,40,67,155,136,71,126,60,36,237,204,100,53,15,0,78,221,172,173,91,134,234,122,252,86,110,109,223,141,169,103,191,92,46,
225,130,125,241,139,95,252,54,92,106,204,166,221,206,157,173,74,46,117,138,189,212,186,6,155,197,98,193,210,182,105,146,64,96,11,153,175,40,179,145,160,95,199,180,151,81,198,231,34,142,135,64,242,172,
78,231,209,9,127,226,201,9,195,119,15,90,141,18,69,146,183,34,114,112,218,173,5,250,111,173,96,87,68,62,206,112,160,122,105,27,10,254,149,121,65,73,18,190,15,15,79,191,16,13,79,36,241,238,57,165,205,115,
145,229,220,131,19,202,234,75,163,207,71,170,24,233,98,174,226,39,182,193,184,184,117,155,44,91,176,84,56,188,9,214,99,133,214,143,83,233,232,177,234,220,213,249,142,42,82,157,28,162,8,229,107,64,186,
191,33,84,200,215,64,186,227,97,151,173,164,147,167,157,162,154,183,21,249,193,52,133,188,99,52,157,140,225,49,217,24,109,253,218,175,253,198,247,255,244,79,33,99,217,217,217,206,243,130,27,53,16,160,
85,22,209,94,224,161,120,212,9,253,102,18,15,134,91,224,14,157,71,84,32,67,60,178,252,118,168,160,236,69,233,41,37,229,4,150,223,237,216,243,204,97,9,117,173,149,113,85,132,250,141,219,24,234,39,160,92,
141,145,150,213,74,173,218,139,13,131,107,3,7,12,129,16,183,241,206,205,55,153,175,125,82,207,122,170,219,118,237,19,61,225,110,34,36,116,195,225,230,108,58,169,74,187,189,181,243,63,252,211,223,252,247,
127,252,239,193,209,111,111,111,205,23,139,44,207,3,59,62,28,173,137,219,86,196,23,13,126,239,13,54,234,181,152,104,160,251,240,142,195,41,2,55,252,149,144,238,30,253,227,107,6,228,130,249,56,36,176,20,
223,48,210,221,168,228,249,63,192,97,171,160,225,165,72,75,37,201,24,109,106,169,164,202,144,221,243,79,28,162,104,143,44,199,162,62,60,166,136,218,197,97,227,203,162,207,123,14,189,213,68,37,7,170,97,
244,89,155,170,44,198,199,7,152,204,215,150,50,29,253,225,143,126,216,237,247,71,195,141,70,179,21,142,3,161,217,19,215,216,66,223,87,194,134,62,213,201,237,35,221,95,233,40,195,85,108,174,140,116,39,
225,186,200,193,3,220,202,108,214,114,150,187,81,106,99,99,251,211,79,62,106,52,27,223,249,206,183,15,15,246,191,255,131,239,15,7,67,154,31,170,57,25,1,27,72,100,184,129,21,83,114,136,80,140,205,29,102,
87,225,96,208,170,50,105,229,85,158,34,152,134,229,198,96,223,116,218,43,179,59,223,125,215,220,15,52,52,13,119,170,189,160,94,115,43,131,157,62,117,57,45,79,49,173,23,19,13,105,86,213,148,163,120,85,
212,243,243,77,249,174,198,101,152,13,116,103,110,70,243,185,152,83,14,71,155,159,124,242,81,171,221,250,246,183,255,217,238,238,238,159,253,224,7,112,169,73,147,205,114,198,237,24,100,105,252,220,41,
124,152,36,155,155,219,164,126,197,196,55,46,118,26,194,171,153,155,51,252,232,138,72,247,176,102,199,44,120,130,206,183,129,27,222,33,189,234,205,34,221,33,215,189,181,146,100,96,68,226,154,28,55,77,
24,13,127,121,244,121,83,23,35,149,77,85,180,167,19,238,12,7,27,184,11,187,79,31,81,249,2,25,248,35,156,80,195,236,7,150,51,159,78,139,44,3,155,135,15,223,141,226,56,156,107,23,246,0,93,110,234,44,135,
75,113,235,72,247,87,74,218,127,5,27,10,115,152,175,157,75,27,117,189,142,116,23,126,209,136,248,8,214,109,150,39,173,214,230,50,238,31,101,71,67,70,35,253,248,131,31,193,231,223,120,239,151,192,193,127,
239,95,124,175,219,233,52,154,169,21,169,46,126,142,53,191,62,92,94,192,72,97,227,142,64,221,252,228,110,107,99,6,143,126,57,239,134,86,87,144,148,162,18,162,225,118,16,122,42,202,98,42,14,178,214,60,
66,68,111,234,107,108,101,8,235,24,250,89,132,122,82,13,11,118,60,244,37,200,233,78,162,103,4,157,177,190,57,120,1,76,79,164,187,220,161,59,122,75,221,223,81,219,79,244,30,3,71,62,250,240,125,216,146,
255,9,94,106,243,189,127,241,221,118,187,5,151,186,228,215,89,197,28,33,192,142,144,196,9,251,172,70,154,14,54,182,249,26,138,246,154,179,119,52,126,50,134,127,156,190,58,167,123,88,179,162,198,157,116,
150,221,26,23,133,242,227,84,55,128,116,55,120,203,235,40,106,223,34,71,184,71,141,243,140,184,103,245,190,60,250,28,110,197,3,157,213,202,236,170,246,186,13,252,121,111,247,49,98,196,185,131,78,15,12,
201,97,52,224,129,153,207,102,237,118,39,203,81,208,248,211,79,126,220,106,119,182,182,239,134,115,61,81,173,183,221,236,190,94,252,216,118,44,119,78,111,17,233,254,38,112,186,67,152,140,45,148,179,124,
237,218,131,221,53,1,115,152,143,188,162,73,52,63,103,171,116,62,30,54,55,78,210,193,52,31,247,224,63,23,139,249,195,135,15,255,193,63,248,251,255,247,31,252,1,24,13,134,195,24,41,7,144,67,13,110,7,19,
32,178,143,4,119,213,235,13,155,237,174,149,126,153,167,93,238,79,148,169,139,147,17,220,4,222,224,24,55,111,124,49,141,49,22,52,102,236,120,56,177,170,207,118,223,167,182,126,77,156,238,126,74,134,201,
55,232,203,6,177,137,85,69,153,9,91,105,0,80,17,178,60,141,144,46,241,220,124,147,107,219,240,85,143,204,120,91,111,109,219,205,35,115,12,55,107,62,159,223,127,240,224,231,254,251,159,253,238,119,191,
11,199,239,247,251,176,73,68,68,34,68,40,57,227,101,10,177,152,52,232,141,218,2,10,83,140,152,183,174,190,103,118,98,151,124,90,60,46,77,181,126,46,68,186,227,229,181,151,207,145,225,106,35,191,81,164,
4,194,185,166,123,102,169,223,112,3,72,247,64,86,124,11,50,147,55,133,116,223,209,5,28,230,145,107,43,181,178,169,170,98,114,124,88,230,5,15,172,240,108,39,92,52,72,230,103,179,9,71,236,139,37,214,119,
121,96,155,127,221,189,247,86,56,215,199,182,249,142,89,110,170,197,145,238,222,50,210,253,213,145,246,95,222,134,24,248,170,128,98,95,67,99,49,138,93,24,218,188,156,186,243,253,114,242,101,117,156,79,
218,105,119,158,116,103,143,62,156,66,96,251,107,191,246,107,127,249,151,127,249,241,199,31,61,124,248,206,104,99,19,172,151,139,25,56,50,42,41,168,40,73,27,141,102,179,209,102,173,70,15,82,23,196,75,
220,158,234,56,207,39,157,186,88,225,236,133,6,86,252,133,229,221,142,89,128,120,111,138,140,57,211,99,10,237,133,215,163,68,169,215,72,186,56,135,213,238,84,239,79,173,248,197,40,37,140,42,123,33,178,
92,70,106,148,91,216,229,161,62,218,208,195,129,235,255,112,239,255,171,171,234,55,126,227,215,255,234,175,254,234,163,143,254,238,225,219,239,64,50,14,230,203,249,124,185,156,203,20,97,140,26,19,141,
102,43,66,93,80,237,93,166,99,196,252,72,15,27,42,61,84,40,197,74,52,125,158,105,140,145,238,214,222,144,238,25,221,244,8,162,35,87,150,229,203,33,221,21,179,77,38,183,86,146,124,73,164,59,236,213,29,
87,29,187,68,65,238,182,102,115,120,176,139,108,32,168,113,196,90,32,152,104,184,227,201,31,253,209,255,83,85,37,108,236,20,89,152,162,40,57,183,183,105,98,23,243,167,79,31,63,184,255,54,159,11,238,209,
137,171,6,54,63,112,165,21,180,213,45,33,221,223,0,78,119,241,253,23,33,221,131,86,21,101,55,30,233,190,102,99,243,22,146,54,181,22,135,7,251,191,243,59,191,147,103,249,159,252,233,159,238,220,221,25,
109,110,113,132,214,238,244,58,221,62,171,156,80,131,41,162,178,135,242,189,127,225,87,72,251,232,173,202,69,203,21,45,67,51,210,28,205,113,255,41,168,67,7,164,59,109,75,204,87,20,9,191,220,203,33,221,
175,97,227,172,19,61,101,179,62,114,20,249,198,162,255,118,210,208,68,108,90,66,4,47,68,29,147,80,31,163,146,80,17,190,35,151,231,233,91,69,20,206,71,88,186,193,144,159,56,2,205,76,207,224,247,158,234,
236,239,237,126,231,183,127,27,47,245,159,252,201,253,123,247,182,183,239,81,232,167,58,221,94,183,219,15,124,229,107,136,121,45,124,237,52,216,187,173,54,27,174,49,86,147,153,155,139,13,142,70,97,19,
22,97,93,181,101,114,122,97,14,162,33,163,115,243,95,8,157,79,231,200,178,230,211,104,120,201,145,95,146,247,61,250,250,215,191,142,15,162,142,111,143,71,220,190,20,207,250,64,23,45,101,119,93,163,14,
236,31,90,29,28,60,161,105,219,138,68,147,80,252,14,162,0,200,5,167,211,121,137,208,194,114,85,131,244,64,42,246,72,85,93,66,194,24,39,49,159,171,210,209,80,151,240,121,174,226,159,28,78,119,229,89,10,
215,57,221,217,144,95,149,231,112,186,175,219,184,58,157,30,101,219,155,59,63,251,115,63,251,175,254,229,191,132,16,234,254,253,183,57,148,195,132,72,51,69,109,164,86,90,11,114,64,230,225,132,183,160,
49,156,68,169,181,243,190,205,59,76,26,65,245,77,27,134,153,185,169,45,205,111,186,143,248,242,136,214,195,41,149,7,240,8,203,229,34,109,52,111,129,211,157,81,102,176,134,70,35,53,164,127,78,242,206,74,
188,172,91,129,215,113,199,197,6,3,114,186,67,2,78,0,145,146,198,30,181,89,163,39,116,130,219,100,162,186,184,68,27,220,233,5,228,8,113,86,189,56,156,30,12,183,134,63,247,179,63,251,175,254,240,15,59,
237,206,206,189,183,152,139,93,38,160,149,146,249,0,143,57,8,220,240,136,98,81,209,29,189,157,170,100,223,30,206,220,44,216,96,14,136,87,219,9,152,203,211,195,7,20,251,69,156,238,62,14,84,158,144,22,227,
3,162,102,76,4,212,225,109,120,86,4,5,37,175,201,233,238,83,194,91,43,73,190,36,210,125,67,101,51,27,85,156,216,144,77,158,45,107,12,31,120,174,1,209,87,40,64,109,107,156,205,230,152,192,147,92,26,240,
97,90,103,121,14,207,76,141,93,91,12,56,246,246,159,60,108,124,129,167,69,193,171,45,77,99,168,170,67,27,255,68,33,221,87,186,84,87,228,116,63,99,51,159,228,191,245,237,223,248,227,63,249,147,172,202,
191,252,247,238,219,194,198,42,102,128,59,77,59,58,14,1,100,128,217,59,62,228,95,111,102,81,107,9,127,149,31,247,108,133,141,20,126,172,157,200,170,250,87,15,75,49,24,228,225,35,77,72,247,82,148,147,207,
105,47,220,14,210,157,36,36,234,136,96,52,31,253,221,7,16,201,194,55,189,123,247,126,175,215,23,62,75,229,251,152,52,86,73,123,54,238,151,252,104,173,21,118,195,144,229,41,164,59,227,63,68,122,131,74,
81,124,35,142,179,241,111,253,198,183,33,140,45,139,234,167,222,253,153,133,90,88,98,253,16,93,47,66,195,235,32,133,230,17,243,177,142,186,182,211,211,93,56,217,174,59,40,116,46,42,86,129,221,88,51,107,
32,147,205,70,154,33,79,55,154,71,19,105,135,0,179,175,142,116,87,171,169,197,91,147,153,188,54,210,61,169,115,167,171,153,238,240,211,207,54,243,217,9,37,198,150,71,115,49,154,136,17,241,52,155,205,153,
36,154,203,204,112,249,137,119,80,117,218,109,240,89,76,230,137,205,166,216,193,163,214,110,119,248,92,227,90,183,141,235,69,122,246,19,131,116,23,128,30,241,219,92,132,116,151,216,202,179,241,243,86,
124,198,6,142,252,222,47,127,227,224,240,240,195,31,127,248,83,63,119,63,109,85,74,77,138,165,81,121,203,85,24,38,248,23,94,243,155,224,116,9,185,105,212,202,136,242,65,85,89,179,156,181,104,91,168,3,
210,157,230,57,153,248,145,186,90,210,138,130,255,171,124,247,93,228,26,184,117,96,111,17,233,110,5,112,131,108,63,187,79,31,49,196,172,219,105,55,155,237,217,244,4,2,234,32,180,204,164,64,36,10,31,121,
153,85,95,76,148,168,86,113,55,137,187,226,28,211,19,14,94,202,141,17,187,109,214,154,87,166,176,197,55,127,229,91,71,71,71,31,126,240,193,207,127,241,31,182,93,171,175,186,153,203,167,240,216,66,238,
168,121,220,167,14,40,118,112,59,169,75,33,139,108,171,22,92,189,165,202,38,122,6,14,142,230,163,180,167,106,95,77,49,82,4,254,10,97,131,60,166,68,148,159,87,243,122,250,119,127,247,119,241,145,141,218,
207,186,118,66,165,175,170,158,231,14,58,93,195,134,50,8,39,47,191,103,192,96,194,63,47,35,233,209,31,207,216,244,181,189,163,243,143,93,187,86,34,247,84,85,197,193,222,19,148,185,133,63,21,72,119,211,
104,52,178,44,67,160,52,78,225,106,183,98,187,92,185,230,70,154,98,109,158,226,252,70,179,213,237,245,238,220,185,43,65,132,115,95,48,139,61,155,206,116,122,209,122,188,68,213,21,190,251,201,248,136,4,
38,162,91,187,206,151,180,225,137,17,185,80,52,224,45,228,255,66,98,175,189,144,170,135,213,80,50,121,218,198,203,43,56,219,233,116,118,119,31,119,123,67,242,125,85,212,202,147,86,174,61,3,48,188,65,44,
154,99,34,156,162,199,26,48,188,85,112,236,178,83,47,154,88,10,115,24,80,48,115,166,112,186,27,86,66,113,107,28,243,34,87,197,156,238,90,162,146,0,197,196,250,46,119,15,225,154,247,250,131,192,91,23,58,
9,235,54,222,61,93,199,134,241,246,71,7,251,199,199,200,100,223,106,181,210,52,45,233,23,44,185,217,106,221,127,240,142,35,105,15,47,156,161,153,194,68,248,97,40,231,98,90,30,134,239,179,163,224,204,72,
173,120,29,34,126,99,153,167,204,163,121,85,163,153,62,121,242,168,215,31,82,154,25,183,234,86,71,181,19,4,229,136,127,199,139,13,254,212,65,100,29,115,255,1,220,220,212,206,23,122,65,84,92,162,31,17,
244,174,248,254,34,170,82,49,242,62,10,16,188,90,36,127,78,77,131,251,73,239,151,178,97,233,54,239,209,60,224,92,166,193,156,199,133,172,113,105,248,210,192,53,93,41,248,8,228,177,79,96,79,134,245,233,
225,112,35,194,250,180,26,143,143,112,199,142,19,136,168,91,237,14,234,166,129,43,105,181,138,44,111,53,91,205,118,251,122,60,235,177,33,129,76,158,183,100,55,156,103,252,70,145,36,122,209,237,246,22,
139,5,181,228,53,79,66,136,176,154,103,227,133,47,1,206,13,28,92,171,217,204,209,193,97,95,185,202,115,166,121,165,206,49,213,113,145,255,247,39,1,233,206,169,150,168,30,56,244,23,103,144,238,220,146,
151,180,154,3,2,30,115,87,43,241,225,21,26,158,52,111,70,44,178,139,199,93,118,33,120,213,73,137,19,208,166,54,200,133,65,35,242,53,42,131,149,224,60,109,84,23,137,47,156,59,162,154,138,140,94,9,40,176,
202,9,113,168,8,243,7,29,225,53,35,221,25,43,150,23,203,253,189,221,201,228,4,22,211,237,96,132,14,33,15,166,93,17,194,176,151,139,69,84,233,70,220,6,151,145,160,94,7,190,107,117,4,25,108,137,44,173,202,
230,46,231,66,56,39,137,126,104,207,9,123,142,204,133,240,244,8,124,65,6,154,176,160,14,154,213,139,122,48,216,228,209,24,88,210,60,90,204,220,44,169,18,136,191,98,56,157,70,178,20,248,249,82,87,86,47,
225,116,165,133,136,165,116,145,101,165,85,229,101,214,116,232,99,82,125,153,145,238,21,130,80,234,219,129,4,210,36,64,68,197,205,75,32,221,37,171,44,103,152,64,39,61,70,108,192,241,16,82,65,82,169,112,
115,98,122,207,145,209,1,111,88,99,221,38,207,242,227,195,125,56,66,167,211,5,175,4,145,240,189,183,30,238,61,126,188,204,150,173,86,59,91,162,202,227,214,157,120,62,155,102,203,69,179,217,2,231,112,84,
213,111,189,243,110,179,209,98,153,1,172,134,224,197,163,240,125,125,219,33,246,219,51,54,112,215,10,188,201,117,176,65,47,85,148,140,211,238,245,250,147,201,196,151,246,132,135,151,88,230,72,183,217,
15,149,51,172,161,34,74,57,26,163,175,43,91,18,21,155,156,11,156,103,172,221,115,214,131,52,143,151,187,62,193,134,218,240,234,249,54,151,57,206,77,219,212,252,194,123,226,98,68,54,82,230,98,84,40,170,
43,38,8,52,68,63,192,189,66,225,71,13,192,40,37,4,47,209,42,228,82,172,161,77,189,221,50,101,231,82,241,16,28,119,94,133,247,137,222,28,163,3,69,32,35,218,67,205,144,201,166,68,222,79,24,180,180,128,78,
214,144,238,162,238,163,220,237,32,221,121,58,239,211,79,62,130,103,62,73,83,136,173,150,89,102,165,78,199,60,60,152,240,125,248,209,251,95,255,202,123,248,224,106,200,42,241,221,107,232,180,165,91,84,
134,67,139,153,154,77,237,172,176,101,20,218,8,171,38,35,75,1,213,196,74,90,7,216,58,43,24,133,39,202,138,134,182,225,57,234,194,20,116,25,51,79,62,26,26,188,58,96,181,215,148,177,4,233,46,156,238,20,
175,18,32,207,153,91,132,4,50,215,32,95,52,90,222,115,145,238,235,124,178,215,184,169,9,246,215,116,127,56,218,220,220,62,62,62,60,57,62,134,124,126,185,92,14,55,54,54,183,182,15,15,246,199,199,135,108,
3,103,188,123,255,173,217,116,114,116,120,128,165,210,36,165,42,134,190,167,150,196,209,236,188,178,153,16,250,16,74,51,15,227,151,143,117,19,206,14,73,26,225,210,180,168,88,56,155,23,57,99,92,24,57,205,
15,13,87,50,156,23,231,10,76,111,220,129,78,104,156,8,98,195,78,187,13,142,181,217,192,87,26,118,203,36,73,185,103,6,223,48,197,210,8,151,66,87,231,162,97,78,110,22,170,43,63,244,234,245,51,94,93,96,227,
24,110,195,89,21,146,192,248,7,60,168,113,177,200,3,123,115,182,177,1,61,164,86,162,82,158,85,25,175,183,63,142,191,242,167,108,132,5,139,185,6,5,33,161,149,16,147,4,169,62,162,63,14,122,18,30,229,174,
47,64,186,139,4,249,45,32,221,185,64,241,163,31,253,16,188,127,187,211,209,200,170,188,224,215,157,211,43,198,16,144,75,94,252,231,131,255,60,218,218,226,150,145,242,10,93,177,75,192,115,181,93,179,171,
58,125,211,159,155,197,137,155,84,40,64,207,155,173,11,103,145,251,165,86,61,116,30,127,97,162,81,158,172,54,62,157,87,158,217,94,9,156,195,56,39,249,151,209,207,218,8,210,157,67,215,55,1,18,232,27,163,
82,184,60,31,233,190,238,176,174,215,43,132,79,32,122,42,193,115,44,151,242,36,33,175,200,52,109,52,230,36,61,162,101,18,93,165,168,106,105,4,43,67,255,224,117,87,54,40,17,224,166,42,208,158,154,227,98,
30,10,23,68,137,39,241,54,52,220,39,72,116,106,118,114,194,60,159,207,227,56,225,221,157,214,46,175,16,251,169,48,92,66,19,167,17,207,178,243,67,22,169,8,2,53,77,174,93,216,30,181,94,85,73,253,185,248,
189,224,198,208,85,31,250,215,62,38,242,28,155,200,136,13,106,133,224,140,148,136,65,9,199,158,200,178,41,214,218,227,43,198,130,81,34,87,129,84,109,181,87,187,87,62,199,89,29,71,83,129,70,178,45,178,
97,168,10,145,169,201,60,41,71,115,86,187,21,215,10,238,181,82,220,180,254,201,228,109,246,12,210,157,158,221,136,31,238,245,246,194,43,64,186,75,206,194,170,101,212,161,206,24,171,193,253,181,80,212,
227,64,18,190,251,238,222,227,78,31,169,168,19,68,177,215,44,85,91,187,106,102,139,153,154,199,42,234,169,110,87,119,154,122,235,64,31,21,170,160,215,65,91,79,90,200,44,101,132,33,64,248,18,149,14,13,
71,175,92,25,67,52,128,100,76,88,230,195,166,4,165,20,138,52,123,34,162,57,46,171,74,230,225,48,70,53,172,74,25,123,190,118,92,234,155,5,9,196,84,0,95,52,41,18,157,210,22,17,28,150,148,101,163,244,146,
154,195,193,166,174,202,217,108,210,72,26,199,227,35,72,179,182,239,220,237,116,122,16,82,205,102,83,240,86,212,5,168,186,189,126,78,114,117,189,193,112,177,156,23,89,54,24,12,99,98,251,134,219,63,177,
102,166,146,185,78,166,248,123,58,115,201,68,69,75,211,128,63,79,85,124,98,205,196,69,96,195,78,173,169,106,200,36,79,92,106,9,78,162,209,87,206,43,28,191,174,192,217,192,133,240,34,189,134,35,154,64,
217,177,86,112,17,84,23,206,181,105,124,2,154,141,38,68,245,131,225,166,243,192,153,13,93,22,42,90,232,132,60,163,14,231,226,107,102,157,187,252,245,9,54,243,197,44,78,211,203,104,68,223,178,141,32,155,
120,87,176,162,24,130,97,20,67,181,185,148,18,200,85,214,98,174,80,219,35,166,240,40,112,184,57,207,81,199,23,156,49,183,126,230,195,120,170,101,23,176,38,44,54,161,189,144,184,4,100,97,208,90,105,175,
99,172,141,175,203,217,53,78,119,183,210,33,62,171,27,92,228,89,171,213,190,65,253,97,159,195,106,102,134,70,129,15,122,162,42,86,30,244,114,194,90,254,145,29,18,98,249,193,112,200,104,3,110,200,218,64,
153,175,93,97,202,165,206,218,186,213,215,189,10,156,12,87,225,69,251,37,144,220,198,12,107,98,133,139,51,247,52,192,53,189,6,68,20,186,44,60,18,32,60,48,116,249,194,216,128,117,33,225,23,81,235,55,1,
18,24,108,66,96,29,110,4,127,247,51,17,150,186,42,164,162,228,166,91,187,181,115,255,129,239,143,214,221,222,16,254,93,239,79,181,59,93,66,199,169,209,104,19,254,229,224,157,74,185,242,228,169,213,61,
208,65,92,64,63,99,83,195,221,177,37,71,140,94,71,58,145,215,192,105,159,15,90,150,48,208,62,50,231,190,9,71,209,126,44,158,119,126,240,84,141,18,217,230,26,17,22,74,29,159,43,209,106,202,238,233,130,
245,4,177,131,203,195,82,94,239,152,200,11,109,2,227,149,120,53,10,136,116,152,203,241,112,4,198,223,50,153,164,199,119,56,205,8,105,37,145,145,127,49,132,125,8,71,64,88,4,236,148,141,34,164,187,36,129,
140,78,226,192,129,11,83,78,238,148,39,252,69,23,104,61,219,244,179,156,238,250,6,57,221,159,99,99,124,215,24,254,217,216,186,51,159,79,225,151,242,242,101,65,31,220,87,52,200,47,212,245,2,34,255,217,
164,221,110,87,148,164,19,218,138,122,127,158,228,23,146,193,167,110,111,75,111,110,170,225,137,157,158,224,211,231,231,140,228,89,45,47,30,253,9,253,95,105,62,218,186,246,194,28,42,120,55,222,63,120,
109,22,235,84,86,7,46,118,105,70,189,73,228,183,167,83,19,180,177,37,60,180,152,77,175,59,172,107,246,10,125,255,230,146,55,94,20,156,68,249,220,151,114,29,79,30,184,211,211,0,103,109,10,122,112,141,67,
141,77,182,105,54,155,203,197,60,77,26,252,248,114,39,69,18,102,186,61,161,211,71,85,97,92,174,241,10,236,60,146,26,39,72,29,231,149,216,193,164,162,182,11,194,88,46,90,207,153,17,144,203,60,244,183,54,
38,114,61,155,64,192,38,136,78,42,220,121,5,73,86,79,132,187,32,79,24,193,226,240,128,188,111,75,135,203,239,149,226,204,57,189,146,97,76,2,70,248,126,107,168,88,41,159,170,179,215,227,216,70,11,72,194,
171,224,104,15,108,81,193,81,225,200,52,246,176,80,92,58,50,18,215,220,36,167,251,197,36,75,188,249,25,158,179,25,12,71,121,81,176,252,34,255,136,223,14,25,88,192,30,73,23,101,177,183,183,11,15,42,187,
21,176,73,146,180,211,235,117,218,61,150,198,226,34,196,158,218,31,233,97,223,244,225,69,88,168,229,42,11,186,194,61,93,129,0,164,196,78,245,32,229,121,214,201,35,80,128,19,153,48,194,33,23,214,10,135,
196,245,240,156,151,130,251,81,249,146,29,5,158,43,78,8,90,244,60,155,103,143,115,54,37,188,234,104,2,100,205,45,8,159,186,61,30,180,191,204,136,131,246,51,172,218,203,72,17,226,19,159,108,102,74,82,23,
219,192,67,51,136,220,194,153,146,199,69,145,179,49,1,135,85,148,185,19,66,107,25,55,245,241,215,106,139,241,192,25,1,233,197,244,11,86,8,79,18,228,170,73,210,224,115,181,148,107,187,98,236,34,75,180,
169,231,174,231,26,227,29,183,54,38,114,37,155,104,69,49,204,215,71,10,159,172,60,235,19,32,194,105,42,145,42,240,8,117,137,149,248,137,39,250,70,205,115,200,126,124,78,210,54,227,227,83,42,249,71,106,
141,251,155,217,72,188,44,187,51,126,0,75,230,169,89,82,85,98,46,153,7,194,89,13,18,43,100,82,1,194,208,87,97,88,143,43,143,9,114,112,226,236,139,173,202,86,187,93,224,96,86,45,192,200,103,108,82,156,
29,209,151,182,177,78,185,0,235,107,54,91,154,126,10,71,193,252,122,120,255,22,8,136,144,218,225,212,13,139,90,115,131,21,60,96,89,20,135,135,251,112,134,70,163,105,60,105,103,166,178,166,110,64,110,184,
84,75,98,188,146,251,114,141,251,46,152,21,173,220,90,31,35,38,250,119,207,12,28,210,68,9,196,24,68,194,255,237,110,46,143,14,54,17,239,123,222,166,22,109,14,207,31,79,32,140,72,12,228,145,168,78,219,
32,151,251,186,195,42,173,186,234,77,133,191,106,54,145,227,229,242,55,222,146,46,155,212,182,125,175,138,238,183,225,156,142,203,177,231,218,212,58,238,219,60,137,177,192,36,54,88,71,43,176,87,40,189,
60,102,143,173,153,184,182,246,95,52,40,112,242,238,68,236,113,186,213,106,129,183,42,203,114,107,107,39,156,107,164,115,72,9,143,77,251,57,235,185,198,67,255,10,94,158,27,176,41,137,242,197,250,247,208,
235,126,27,46,214,50,35,178,80,178,41,63,192,193,8,6,79,106,198,111,35,75,164,240,128,171,188,175,12,251,212,145,21,204,148,102,161,97,255,38,59,126,194,25,128,195,112,86,69,1,178,243,32,83,158,109,240,
78,76,179,92,166,111,110,134,4,71,105,63,206,22,94,51,142,248,145,114,118,177,72,210,6,23,104,184,241,163,252,172,117,176,225,1,137,203,219,8,70,159,34,18,48,120,183,243,238,222,124,175,38,220,82,160,
12,246,79,153,14,181,56,184,206,139,197,2,35,53,110,215,208,108,41,62,159,85,57,159,79,218,157,126,24,208,156,214,179,158,233,246,116,119,162,102,236,8,34,234,132,188,252,125,143,80,209,171,102,26,98,
38,13,118,202,173,207,238,8,100,196,201,206,193,201,189,209,28,197,250,49,110,166,110,247,85,67,122,84,12,211,3,122,155,0,207,80,122,13,243,41,245,199,245,2,148,255,206,70,84,218,216,77,249,65,186,85,
96,189,178,193,211,157,142,176,26,55,114,83,159,111,195,114,3,90,210,52,17,14,80,42,4,63,76,20,171,47,178,129,143,250,174,156,184,88,249,225,204,70,179,85,20,89,141,207,186,149,233,63,31,10,25,185,10,
145,159,214,162,155,68,107,107,183,219,188,237,239,236,220,75,210,148,207,5,9,225,150,203,142,93,146,225,168,253,133,235,57,117,247,46,247,221,95,197,203,115,227,54,58,4,143,172,105,22,202,178,86,96,83,
18,4,113,115,90,175,149,150,169,162,44,151,40,164,204,220,47,103,205,74,43,14,40,16,101,251,178,242,10,116,162,124,25,72,200,89,181,242,245,125,167,130,90,180,86,145,57,237,58,5,168,177,6,184,39,117,50,
248,143,60,207,32,126,9,47,64,208,142,94,183,9,79,197,229,109,156,72,112,233,77,61,74,117,98,250,105,94,44,185,120,196,241,166,228,97,44,40,111,249,10,144,128,13,13,148,66,22,25,102,191,203,34,39,121,
174,37,164,135,66,178,163,163,133,90,116,85,59,118,209,194,45,66,228,120,3,247,157,142,195,156,235,188,91,136,243,229,132,209,3,157,66,177,255,162,80,46,94,11,229,244,202,251,156,178,33,61,199,83,199,
241,52,2,161,151,162,68,98,89,168,117,248,246,154,117,155,51,199,225,72,255,148,195,178,58,186,169,155,250,28,27,143,20,17,108,14,115,30,178,205,250,247,191,200,166,80,102,168,113,222,117,161,76,176,129,
136,169,44,11,95,71,192,82,21,79,191,7,176,156,146,249,117,199,151,169,215,237,50,229,101,163,209,232,245,135,225,56,35,85,181,141,123,98,83,162,148,185,112,61,215,248,238,175,232,229,185,65,27,126,88,
205,74,150,49,120,138,16,196,172,54,98,95,144,226,148,80,7,22,1,217,56,101,75,132,163,209,232,143,22,218,73,170,173,114,105,199,137,204,165,114,33,118,211,50,95,237,7,89,184,110,237,249,200,140,108,93,
44,60,195,117,107,174,39,218,20,101,4,120,139,54,76,238,106,233,189,44,243,188,77,0,116,38,246,241,20,160,167,108,88,84,229,242,54,177,47,251,198,58,218,208,195,113,61,89,168,101,187,211,117,117,9,49,
20,23,236,34,227,139,50,20,136,113,34,168,2,131,152,91,49,234,136,158,144,117,101,153,183,58,221,112,17,192,176,171,58,83,55,183,84,155,91,119,208,55,120,223,153,223,205,139,168,114,74,47,187,59,13,147,
214,78,74,175,92,202,196,88,143,94,31,106,86,226,16,79,101,159,181,193,128,12,177,242,216,101,54,26,73,106,92,237,199,81,173,167,186,49,76,225,24,206,21,156,221,11,109,78,57,172,56,110,221,200,77,125,
190,13,239,171,49,22,35,68,71,132,155,44,21,221,88,86,104,225,187,125,174,13,68,213,169,178,189,168,158,186,216,146,60,36,216,164,73,35,77,162,162,44,136,151,178,22,100,142,137,249,94,19,3,9,190,52,9,
210,122,212,144,9,70,68,200,223,110,181,182,238,220,11,231,74,180,222,49,249,92,197,115,157,62,127,61,156,161,92,233,187,191,138,151,231,102,109,252,69,182,94,48,213,179,200,208,67,30,225,171,104,217,
1,113,111,158,129,105,198,239,210,190,107,232,155,241,244,59,65,82,169,105,168,157,111,156,201,36,48,119,51,42,170,15,248,250,61,245,230,137,137,33,228,122,106,165,182,26,138,46,122,149,42,240,64,137,
180,234,245,153,174,121,1,155,68,179,117,179,221,119,238,62,195,223,12,116,191,161,210,35,117,204,109,207,102,179,129,242,244,69,113,42,254,230,3,42,79,113,206,175,28,101,24,200,8,74,27,224,114,185,140,
145,173,187,110,53,155,113,156,112,182,91,184,98,104,6,240,196,46,109,230,117,142,237,171,123,54,184,232,33,247,130,111,153,231,144,16,246,30,122,6,216,70,133,162,228,121,54,144,245,211,87,227,169,213,
96,67,227,74,190,107,193,235,121,230,92,151,178,57,229,176,110,141,21,75,133,134,148,103,181,212,190,142,27,218,77,207,177,201,84,60,210,85,79,215,39,42,9,54,81,156,130,211,170,171,50,78,98,108,29,102,
153,103,179,148,94,59,151,20,224,15,240,100,36,41,196,100,41,122,171,181,115,61,212,115,120,81,30,169,150,187,196,122,174,250,221,95,197,203,115,227,54,43,54,104,189,22,92,114,88,64,73,34,111,131,164,
95,16,166,45,56,161,51,124,137,93,224,73,225,65,25,82,244,228,176,55,188,240,171,40,45,124,234,79,31,166,112,9,67,84,115,145,202,121,130,108,21,106,85,116,100,79,118,192,218,236,92,182,57,197,166,4,185,
86,171,213,190,42,227,210,11,108,124,249,108,67,141,50,149,45,204,82,179,10,60,234,56,27,8,243,231,243,5,22,91,185,54,232,68,254,135,174,134,176,19,137,124,142,137,72,97,40,229,60,142,203,225,221,94,95,
166,202,140,78,84,218,49,173,153,158,113,59,203,95,150,87,114,223,139,34,199,18,88,154,6,19,248,164,42,43,2,75,186,32,251,40,226,231,190,8,224,145,247,250,140,13,81,15,134,54,151,10,195,246,190,180,239,
180,225,110,143,90,161,68,248,182,94,194,230,108,74,120,51,55,245,5,54,181,243,116,195,122,109,126,138,6,202,232,65,196,24,201,62,199,198,152,120,233,76,95,229,169,179,83,21,5,27,131,218,144,3,248,161,
249,98,238,219,121,150,95,140,21,90,143,100,227,30,60,120,171,211,29,152,181,115,221,85,203,196,213,143,85,171,116,250,133,235,97,81,223,43,125,247,87,242,242,188,26,27,46,111,96,82,28,199,129,215,129,
1,89,12,113,224,252,81,102,60,137,144,79,173,152,22,67,65,84,146,74,237,25,50,4,237,201,13,71,95,149,98,158,56,223,183,226,233,57,230,104,119,12,124,245,220,167,66,216,41,169,0,53,10,125,75,139,11,28,
102,149,118,189,74,176,46,175,35,181,105,87,183,15,221,184,70,34,92,44,105,67,64,176,191,191,11,89,127,89,148,182,94,129,125,172,167,60,100,157,161,144,251,240,120,57,79,170,226,69,162,217,157,6,108,165,
56,170,129,174,4,254,179,163,218,153,202,173,170,37,83,214,1,222,33,205,7,43,25,0,150,230,157,186,236,125,223,123,242,40,47,243,52,109,4,155,195,131,189,147,241,241,96,180,65,123,18,218,28,35,5,197,97,
111,48,12,195,82,124,89,68,56,149,108,168,43,90,139,99,58,109,99,100,102,91,108,156,79,81,125,209,94,138,6,254,57,52,21,182,122,47,101,115,10,135,117,155,172,88,12,33,97,225,0,223,233,244,116,148,132,
44,127,190,205,82,153,67,221,222,214,121,173,138,221,42,14,54,181,50,173,78,47,58,153,212,245,210,121,209,77,226,166,177,158,153,93,149,168,133,155,242,110,207,231,218,116,121,71,217,167,85,58,71,139,
234,50,235,185,234,119,127,189,130,8,151,99,197,170,9,56,187,234,208,121,242,73,207,14,67,113,140,10,12,147,4,255,84,43,194,19,207,239,238,173,57,37,12,232,106,204,208,9,109,135,99,154,1,234,141,200,92,
197,28,50,200,66,137,204,139,50,47,226,132,67,238,44,0,82,243,208,43,211,212,121,106,116,158,112,188,5,176,46,23,162,26,81,194,74,157,156,112,213,85,85,44,23,112,37,78,78,198,57,170,156,196,210,33,48,
43,160,105,205,18,191,50,147,204,149,63,116,208,105,146,230,117,94,213,42,85,233,120,124,220,125,208,167,110,170,203,109,110,181,101,198,133,36,162,235,35,225,43,230,116,100,35,34,23,134,88,164,47,15,
161,138,27,144,139,52,214,217,217,124,10,107,97,253,176,179,142,182,182,121,220,154,171,49,18,42,210,154,35,242,35,254,92,42,156,235,140,141,99,77,248,211,48,43,222,99,56,138,102,155,103,159,195,23,218,
188,44,210,253,26,54,23,161,216,47,131,116,95,183,153,32,33,13,230,134,73,228,158,170,134,243,54,38,138,138,50,103,214,90,159,48,248,206,168,115,126,64,87,243,113,224,61,219,113,139,150,171,143,117,99,
1,55,253,114,235,249,252,33,221,209,134,104,15,8,68,74,21,4,91,73,157,59,212,65,105,204,211,172,184,124,121,146,137,83,66,22,67,85,46,12,243,80,4,145,162,12,79,197,67,136,28,14,16,0,85,200,12,148,159,
36,175,25,250,128,235,169,130,208,185,112,217,105,172,58,59,134,224,171,21,185,141,99,96,176,97,205,78,158,236,185,13,176,46,223,248,68,39,202,143,58,243,139,179,88,46,8,98,110,98,84,237,229,234,149,241,
145,135,91,169,78,248,2,31,115,93,20,69,145,36,49,187,139,162,44,173,4,239,52,19,8,57,145,142,18,149,44,21,118,18,133,142,130,156,56,14,162,139,205,58,89,104,29,158,177,18,50,186,60,111,52,91,105,138,
40,69,140,73,59,93,248,236,100,49,111,53,219,177,159,6,169,107,183,92,204,8,70,106,120,140,97,177,152,193,207,198,105,202,220,84,240,183,101,9,169,34,4,142,141,245,231,7,117,6,149,231,128,191,0,121,127,
46,58,255,229,159,213,155,64,186,95,209,230,101,144,238,103,108,142,84,90,169,104,199,20,239,232,226,81,157,212,196,159,95,86,185,242,242,223,181,245,58,61,82,248,196,249,29,148,8,204,150,17,60,89,90,
221,83,89,170,221,158,106,206,85,202,233,199,101,214,243,249,67,186,243,196,70,172,153,183,215,106,63,112,174,132,148,71,6,95,156,10,146,153,58,92,89,229,253,90,80,201,21,54,24,19,145,215,51,206,184,128,
116,135,207,99,193,236,168,80,153,246,208,6,167,131,242,141,212,107,77,96,23,8,19,236,124,19,124,32,38,69,101,110,35,190,106,164,187,71,86,24,228,125,86,162,188,192,178,178,37,193,74,67,145,110,29,106,
228,103,182,5,86,26,218,249,44,240,197,88,82,248,0,18,112,131,42,205,220,223,166,97,88,109,99,84,35,151,4,90,82,133,80,207,81,38,52,4,213,105,155,36,77,15,247,247,202,44,219,218,185,123,124,116,136,67,
184,173,246,248,232,32,207,242,246,131,222,248,232,168,217,110,183,218,221,253,167,143,208,5,36,113,206,164,114,68,122,233,104,70,146,247,236,9,4,92,84,140,123,240,240,109,214,236,122,237,207,234,41,135,
117,59,154,195,66,79,173,156,175,206,26,106,237,161,107,136,19,195,237,75,33,41,185,132,205,84,197,149,50,119,85,246,182,201,142,234,232,68,197,101,81,202,20,59,49,43,168,85,230,47,110,59,162,204,120,
39,113,93,155,193,37,121,236,90,185,139,212,85,214,115,141,239,254,138,94,158,27,180,193,100,152,202,64,108,31,121,70,132,200,167,99,194,180,225,1,34,92,185,173,121,44,134,135,7,121,102,141,42,40,6,123,
184,86,80,60,190,169,20,10,177,62,242,176,167,166,20,189,56,54,162,31,104,248,70,17,9,4,115,191,113,241,56,166,177,199,218,86,144,60,58,186,203,149,99,14,60,227,110,133,211,221,48,78,82,35,197,21,131,
33,57,51,227,222,49,105,47,214,110,13,91,16,68,24,89,42,56,12,63,107,145,206,244,78,143,244,153,45,73,168,248,97,36,87,169,138,148,198,113,20,105,211,142,120,6,147,51,113,70,144,172,38,191,133,221,204,
238,169,3,14,135,251,131,225,24,124,213,193,30,231,122,147,201,56,95,102,163,205,45,38,83,129,111,154,45,230,176,164,237,237,123,173,78,251,241,227,79,138,44,195,9,181,70,179,200,179,173,59,119,15,246,
158,194,117,216,185,251,96,54,157,192,113,192,29,39,129,169,233,181,62,171,167,28,214,237,232,63,51,55,49,130,115,184,147,164,88,228,81,110,170,232,77,212,87,176,89,24,253,137,107,142,116,190,97,170,45,
83,255,121,94,66,22,146,196,169,243,29,122,223,201,82,50,68,162,205,70,189,232,219,198,210,52,14,93,146,227,240,135,189,210,122,174,241,221,111,71,16,225,101,108,164,29,71,210,82,154,200,182,73,134,67,
106,118,190,69,37,65,85,44,10,20,117,36,16,57,193,9,161,187,71,185,108,120,105,43,166,190,101,82,61,186,134,54,204,0,161,28,177,142,157,180,8,113,61,60,207,8,235,49,210,147,117,254,15,190,253,36,136,123,
81,139,242,243,28,140,58,17,88,225,25,126,184,87,196,233,174,184,32,106,113,124,1,27,85,68,196,86,35,113,109,213,72,83,130,93,209,96,146,32,191,113,208,216,119,45,106,230,195,80,158,32,140,104,142,42,
6,29,9,61,14,49,26,9,19,40,7,21,72,110,89,17,211,14,239,5,56,44,205,208,4,191,145,104,78,162,241,38,74,195,64,165,205,22,252,62,155,77,134,163,77,88,216,236,228,4,242,186,118,167,139,20,79,116,174,10,
23,90,207,22,83,148,17,41,145,106,41,141,177,65,145,59,7,207,6,220,187,172,182,101,93,17,58,191,182,158,7,226,181,63,171,16,217,154,176,21,68,38,230,139,105,189,251,71,158,35,76,35,75,181,2,236,155,151,
180,241,213,125,191,155,10,63,119,196,236,60,164,88,187,178,17,166,17,142,11,153,52,73,244,130,148,192,73,104,39,131,175,178,91,167,7,202,13,93,157,151,57,143,38,132,82,173,83,222,125,211,122,172,171,
247,242,106,217,221,172,137,68,156,241,186,161,174,252,194,115,177,254,243,85,31,250,87,45,136,112,3,54,196,98,110,137,252,139,138,75,92,230,19,165,156,192,73,201,168,104,214,190,94,9,169,162,74,130,9,
212,134,76,92,89,99,136,37,1,6,143,40,48,125,54,175,135,138,208,92,195,182,92,138,90,151,144,113,18,207,202,200,33,87,184,56,147,138,88,9,92,5,33,31,19,74,105,103,21,222,3,243,250,13,243,204,169,90,219,
84,55,101,42,149,227,35,63,67,199,148,74,204,62,232,243,89,23,58,15,18,92,210,195,137,176,27,173,32,38,227,2,31,252,60,77,140,73,35,210,17,171,98,169,75,188,138,198,236,218,253,21,31,169,230,1,22,39,8,
245,160,206,109,157,223,90,224,80,105,127,56,26,31,31,66,50,8,159,76,167,39,157,94,15,156,0,222,119,186,158,131,193,16,94,184,233,228,56,207,151,216,91,68,76,92,197,93,63,166,178,49,164,199,197,163,105,
18,56,191,1,207,106,108,86,10,1,206,235,63,11,188,24,54,16,36,72,99,146,3,158,56,192,191,189,85,27,39,227,26,164,68,64,15,80,152,194,88,19,168,20,27,148,83,117,49,92,118,77,172,123,161,145,112,106,186,
137,254,111,81,235,142,50,234,130,227,188,240,92,215,120,232,95,209,203,115,131,54,176,187,10,80,32,212,139,252,251,184,26,254,118,242,236,50,115,38,183,80,85,80,99,246,112,57,214,65,227,18,62,55,77,56,
100,224,188,207,43,122,42,73,30,81,149,72,202,97,180,66,246,122,134,81,1,196,215,46,253,123,252,128,248,31,68,224,143,84,38,17,64,116,1,63,220,171,224,116,199,245,64,208,164,42,20,83,162,128,136,195,82,
136,232,49,206,42,234,180,209,192,247,157,198,45,73,145,180,38,142,61,235,130,235,199,72,115,133,189,172,61,26,4,190,86,108,180,199,121,225,97,35,29,149,168,207,188,42,139,249,105,244,85,66,205,143,84,
36,98,43,167,232,238,80,78,181,215,231,222,209,131,183,191,32,130,26,90,189,245,206,187,156,114,246,135,195,222,96,16,192,28,240,239,221,187,15,24,19,188,125,231,46,219,192,17,224,56,43,97,142,215,253,
172,70,95,123,239,27,65,13,209,152,148,249,41,8,204,90,215,158,62,134,209,177,28,117,99,20,118,139,54,216,89,189,34,26,126,111,239,105,81,228,90,230,143,112,103,139,9,242,46,54,180,245,165,205,102,163,
213,122,33,170,254,39,20,233,94,203,168,0,249,29,33,29,21,162,5,237,71,100,252,148,82,196,12,189,66,13,30,164,88,5,59,90,139,107,243,51,107,4,146,48,158,78,206,202,11,239,194,192,45,47,0,3,49,158,203,
93,233,212,115,130,180,82,125,23,136,87,104,248,222,46,210,29,94,164,182,110,205,212,92,88,70,201,40,207,51,114,78,117,187,221,42,177,47,172,87,19,76,194,87,235,252,212,156,14,226,117,252,62,54,91,141,
56,78,90,173,86,183,59,96,119,5,167,232,169,222,204,206,11,93,82,94,232,124,152,15,215,39,182,158,224,120,109,4,135,6,15,88,79,140,156,239,27,248,140,189,188,77,244,79,190,246,222,10,237,71,208,146,21,
164,150,7,145,68,61,197,4,38,197,91,181,81,246,170,104,248,162,68,82,121,25,255,32,59,124,50,72,112,1,1,196,73,210,105,183,33,54,238,118,251,151,65,213,255,36,34,221,215,11,241,158,162,213,9,31,185,56,
5,46,144,175,75,31,135,252,59,176,213,112,162,36,3,206,50,84,35,209,194,250,113,252,224,235,138,80,67,120,177,215,80,236,54,160,70,25,148,40,226,23,175,13,233,14,171,111,19,170,179,70,53,32,236,69,196,
113,154,35,1,41,241,54,84,85,183,219,37,104,65,22,153,117,18,48,45,29,88,63,182,205,42,65,81,68,172,108,113,188,181,125,55,66,130,10,140,188,26,186,209,53,237,185,158,87,186,62,131,116,103,29,10,36,81,
240,212,166,76,234,19,56,239,223,228,103,236,37,109,226,144,46,209,69,172,125,227,70,241,108,48,43,208,113,65,84,218,31,218,221,166,13,237,183,38,240,239,107,129,89,159,195,179,30,108,210,180,1,94,73,
17,209,85,77,67,15,210,172,137,12,124,142,146,1,203,101,202,101,221,231,30,231,57,231,250,156,113,186,159,177,9,248,97,132,234,225,31,42,246,66,150,232,195,133,103,92,94,32,27,69,9,237,130,181,104,174,
120,159,175,194,184,180,19,54,244,128,138,182,60,102,22,52,1,86,231,98,165,6,244,101,84,12,138,196,181,17,255,12,69,97,17,7,87,224,65,96,229,22,21,128,226,96,195,213,207,87,13,214,101,128,202,194,46,107,
83,181,93,43,211,153,54,17,219,64,4,141,149,13,162,254,158,47,230,237,118,27,158,64,38,204,129,245,39,113,11,28,211,241,201,88,122,136,52,152,129,128,131,102,131,191,87,132,163,248,77,230,202,128,179,
180,85,179,210,213,82,229,220,52,140,48,74,213,159,137,231,231,213,234,15,124,253,189,247,194,198,165,73,226,84,184,41,232,149,230,50,4,95,98,200,228,99,25,39,94,177,193,70,158,167,6,11,13,216,51,138,
196,255,208,191,66,192,74,133,74,207,120,43,163,225,65,126,136,121,221,152,127,154,227,26,236,205,197,49,247,152,44,115,197,104,33,156,53,140,188,33,208,144,104,14,123,86,204,64,246,218,104,52,14,15,246,
49,176,162,164,14,113,116,37,202,91,65,216,149,103,240,11,135,164,54,183,183,97,79,139,104,217,84,13,137,121,247,163,130,132,243,53,5,230,231,49,204,221,65,180,77,188,66,67,237,51,230,244,96,22,58,205,
98,150,204,94,192,51,80,12,22,71,60,52,109,6,89,134,4,126,24,234,51,222,134,116,216,89,56,128,21,13,98,147,16,211,169,229,171,202,69,16,164,58,130,207,141,48,79,18,76,12,143,15,31,178,126,7,166,186,212,
131,195,163,234,136,196,208,200,197,144,104,114,68,183,140,201,176,89,209,147,95,57,156,153,80,224,61,139,23,142,164,88,26,73,241,190,71,7,56,20,39,57,216,167,39,102,37,206,226,165,85,231,107,14,218,3,
208,121,244,127,237,56,42,112,150,243,185,98,57,151,112,150,27,239,233,60,213,175,230,204,75,121,194,155,154,88,97,163,85,165,210,220,14,167,123,144,105,102,157,209,190,233,205,245,178,198,254,39,110,
72,73,218,40,137,230,136,155,6,37,68,88,69,193,98,78,44,246,7,191,54,70,163,241,120,10,198,255,227,63,251,159,32,24,59,56,56,128,7,28,242,65,184,197,247,238,63,4,239,207,15,134,113,122,68,116,201,57,56,
44,170,214,225,131,124,235,124,255,111,160,13,56,172,95,14,156,70,150,17,165,54,168,188,193,86,22,27,193,239,57,97,201,160,72,163,211,134,188,170,213,235,118,97,127,232,247,224,255,59,205,38,36,224,45,
124,27,163,56,203,51,235,137,13,49,196,165,178,37,237,159,214,143,80,26,225,228,86,171,231,59,198,251,18,115,111,19,187,174,212,197,102,223,39,242,115,94,114,128,11,82,126,155,119,254,168,94,172,84,104,
118,209,3,34,109,89,160,16,51,186,209,108,118,58,157,135,15,223,73,210,38,78,138,8,1,144,229,142,149,167,180,16,85,240,90,186,60,194,29,72,206,197,212,242,100,203,128,2,191,54,53,65,238,24,72,9,135,37,
87,171,105,6,168,98,6,21,108,8,148,37,92,33,56,2,19,87,178,91,76,72,245,3,252,87,89,87,60,43,79,125,144,132,193,62,88,249,194,195,10,93,39,122,46,90,88,81,149,114,88,141,3,25,196,28,18,33,78,154,14,123,
122,97,181,95,152,242,11,195,75,133,210,196,66,108,114,133,151,153,51,228,96,67,151,168,82,50,248,228,148,247,80,70,123,66,26,35,58,119,34,205,178,126,156,211,231,170,159,61,215,122,245,71,175,10,85,193,
21,50,15,253,243,109,138,188,108,52,219,47,127,156,117,27,63,134,164,11,91,246,85,7,190,118,230,50,102,73,131,107,3,89,63,236,76,116,109,233,161,137,240,27,213,84,139,193,59,76,25,197,112,48,128,189,179,
215,237,125,235,91,191,242,254,251,63,154,205,231,157,78,171,223,31,118,58,61,97,7,83,102,104,250,77,211,60,210,199,4,86,150,217,213,107,144,124,126,254,108,98,129,38,115,179,20,129,109,53,167,69,44,213,
13,129,110,168,25,226,59,19,37,189,94,7,28,20,17,107,89,238,63,162,86,141,86,109,114,86,156,159,111,215,155,211,233,108,50,157,21,101,1,239,225,124,118,114,247,238,253,249,124,5,177,17,65,71,196,191,89,
166,22,163,124,176,244,117,43,81,97,17,133,50,214,248,242,113,28,215,29,43,150,57,226,33,53,226,69,178,216,140,103,212,153,29,110,108,141,54,182,2,79,147,9,100,0,30,228,130,251,21,245,220,157,0,47,36,
124,208,178,24,30,145,11,130,160,53,207,208,241,184,34,215,80,112,128,204,9,107,176,166,56,194,115,179,84,214,55,233,193,121,107,145,53,171,89,178,212,81,124,132,47,0,197,115,149,43,229,176,194,156,78,
253,7,45,135,13,74,33,92,8,183,76,255,37,236,192,134,39,251,68,159,198,214,254,176,103,22,182,118,132,103,22,134,153,217,117,81,200,180,15,218,48,110,178,102,163,206,218,88,190,215,175,3,193,111,80,251,
231,102,207,21,38,37,225,171,205,213,178,167,187,83,53,171,25,5,67,58,105,219,219,59,135,7,123,176,37,48,171,39,188,19,220,85,64,229,155,138,32,5,26,101,162,191,255,253,239,127,233,75,95,250,206,183,127,
235,247,126,255,255,26,143,79,222,254,194,151,181,231,54,136,181,233,155,238,2,60,33,167,226,129,180,231,245,77,65,188,57,54,209,215,190,254,141,213,100,41,147,129,120,254,33,78,181,35,106,228,37,113,
180,189,185,185,185,181,9,97,212,98,185,56,60,60,58,58,26,31,192,255,32,192,157,205,192,61,157,156,156,140,79,78,230,243,197,98,177,4,199,214,239,246,250,253,126,154,36,255,229,111,254,234,155,223,252,
230,112,52,124,242,244,41,207,169,113,30,231,133,15,228,145,231,169,11,19,56,102,67,208,199,10,81,164,143,196,216,16,25,226,144,153,126,223,48,194,142,73,196,66,167,70,18,79,29,152,137,188,50,165,19,13,
103,34,129,244,220,149,66,35,103,189,16,139,215,215,181,161,248,44,218,7,210,57,14,212,79,34,111,69,87,201,82,105,70,24,59,97,181,46,80,6,90,153,185,131,4,129,185,164,189,188,21,67,144,84,180,186,230,
20,167,80,238,134,135,245,67,124,225,176,60,56,181,66,237,175,225,48,214,14,251,130,133,133,190,27,135,143,47,201,13,31,211,172,242,11,109,110,159,171,158,109,242,44,227,107,126,179,231,226,36,1,162,213,
165,91,246,117,191,99,218,51,55,23,233,102,138,199,219,157,94,85,21,142,210,127,63,136,38,194,52,8,143,128,236,38,65,50,153,31,254,215,191,253,251,127,255,31,12,250,253,15,62,248,32,91,206,71,27,155,220,
117,189,167,119,224,248,79,236,158,243,131,61,12,170,120,45,215,240,77,179,65,135,21,112,70,21,3,181,132,131,89,20,200,225,135,91,205,198,131,251,247,192,251,156,76,166,123,123,7,39,147,19,72,206,17,228,
194,83,79,212,230,199,160,140,193,145,182,158,205,22,211,41,74,168,254,249,95,252,167,135,111,191,253,149,47,127,249,223,254,209,31,13,6,163,192,182,100,9,243,235,27,37,8,5,12,69,110,142,11,41,190,139,
216,235,132,252,69,194,64,242,53,92,242,96,144,49,179,11,113,1,136,84,115,200,193,225,107,31,243,150,207,133,79,246,68,20,108,98,36,2,193,35,35,57,25,80,27,83,201,12,14,91,82,179,153,171,72,17,199,44,
202,193,17,168,38,69,231,66,240,154,225,241,78,14,254,137,200,95,224,14,140,190,11,165,107,169,196,57,28,43,69,17,10,169,18,74,53,135,191,26,81,205,250,48,152,199,59,104,97,235,71,224,228,142,18,70,19,
142,192,107,224,178,35,211,33,240,30,117,238,194,112,138,69,100,214,229,176,240,0,188,105,28,243,55,107,3,153,87,218,104,220,248,185,248,73,228,241,236,37,4,89,174,155,170,116,90,207,2,66,29,108,80,157,
51,74,138,42,39,88,206,106,64,18,105,158,40,85,132,133,21,121,113,120,120,248,203,223,252,229,167,79,158,194,126,191,181,117,7,238,206,134,29,53,76,99,207,237,87,52,250,67,147,201,136,143,251,172,223,
139,155,178,137,126,233,107,95,119,129,87,219,8,227,29,211,204,243,13,232,117,58,59,59,119,32,194,253,244,201,83,136,158,184,74,98,60,219,22,179,193,234,21,167,72,208,76,86,63,254,240,125,48,251,141,95,
255,245,127,247,239,254,93,167,211,53,136,184,35,239,233,123,210,28,180,115,81,138,135,215,67,76,196,83,210,198,248,108,67,164,52,35,193,172,11,5,146,39,240,88,215,245,228,160,200,112,39,94,25,35,245,
148,85,71,220,243,189,7,38,94,173,87,36,180,98,235,148,22,104,181,98,130,124,63,144,163,73,77,207,143,116,133,133,233,139,22,102,194,194,138,60,107,54,154,235,11,91,99,31,57,187,48,15,48,58,103,97,234,
212,194,212,217,133,241,26,158,187,48,237,23,102,201,177,190,201,28,243,47,105,83,230,69,171,221,190,241,115,173,88,13,21,182,143,107,85,247,77,15,182,162,76,101,130,210,230,116,62,77,59,157,62,22,46,
169,120,24,99,147,186,129,148,220,189,193,104,99,171,215,31,64,178,254,241,199,31,181,90,237,95,248,133,159,255,179,31,252,0,12,222,234,62,236,152,206,177,26,47,224,80,129,70,249,166,56,221,63,23,54,209,
215,223,251,134,87,114,34,182,21,166,70,84,172,177,83,111,109,110,108,109,110,102,89,246,248,233,46,6,47,78,52,123,181,160,248,12,9,154,11,197,143,208,138,80,64,241,228,241,71,144,153,255,230,111,254,
38,228,140,63,248,193,15,126,233,151,190,134,219,209,98,17,248,146,2,75,9,255,70,128,6,189,82,49,160,67,50,153,23,127,13,120,32,144,100,154,208,207,214,163,10,140,168,111,214,60,132,165,165,248,69,210,
225,182,242,64,100,81,190,137,153,116,137,174,2,119,63,169,192,30,113,251,198,31,129,47,28,58,58,105,147,175,177,193,242,97,121,44,46,44,76,228,124,57,231,246,116,174,207,46,172,44,10,42,186,71,44,75,
245,220,133,145,251,57,187,48,81,121,96,240,199,133,11,163,101,132,133,241,17,194,194,34,79,52,203,11,211,90,189,201,28,243,47,111,147,231,203,36,109,220,236,185,248,35,179,6,84,43,84,1,97,108,79,247,
82,151,204,221,194,163,207,197,6,91,189,73,163,137,90,120,131,110,183,143,145,87,154,210,110,105,90,237,174,81,246,253,31,125,240,149,175,126,229,203,95,250,210,159,255,197,95,252,244,157,255,110,170,
102,240,239,58,138,253,243,113,47,110,202,230,44,210,221,170,90,132,192,156,237,117,59,27,163,209,116,54,219,223,59,32,156,119,20,248,106,185,145,55,159,79,22,144,252,77,198,179,233,201,124,62,3,155,70,
218,132,31,60,62,218,127,242,228,241,123,239,189,119,103,123,251,247,127,255,247,239,223,127,208,237,245,134,131,62,44,6,226,58,237,149,199,125,40,98,20,207,4,5,241,2,154,92,247,2,156,53,183,222,120,182,
83,38,173,88,83,47,98,118,61,203,90,44,182,150,121,8,26,230,162,38,186,226,206,130,101,254,252,213,17,156,12,97,81,65,129,95,251,72,206,197,19,21,120,189,106,57,44,189,239,140,33,172,235,50,162,222,42,
123,40,191,176,90,251,244,141,59,98,103,23,70,78,135,119,123,89,152,190,198,194,20,183,59,235,139,22,102,98,150,234,88,45,140,228,148,141,112,176,213,130,59,163,178,32,31,33,138,204,103,23,241,124,25,
27,91,214,176,73,220,236,185,2,172,131,209,231,220,132,89,186,172,214,182,167,187,45,213,202,117,113,174,141,243,234,100,84,142,140,88,91,167,211,27,64,232,253,225,7,31,252,163,127,252,143,39,147,201,
120,57,174,26,118,221,134,214,99,63,7,247,226,21,34,221,25,3,209,108,54,239,221,221,89,102,217,147,221,93,79,45,34,185,219,98,62,59,62,222,7,63,149,101,203,50,207,203,138,128,78,85,149,231,217,108,54,
62,25,31,31,30,28,188,245,240,225,183,190,245,173,127,245,135,127,8,209,217,195,119,190,184,152,47,96,99,1,159,149,45,115,158,72,96,140,149,135,219,8,70,215,79,105,4,142,202,136,177,80,214,213,62,91,12,
82,140,198,107,117,40,43,142,78,180,196,25,213,73,61,126,249,112,253,8,94,45,141,63,116,161,102,191,126,4,154,59,101,216,189,9,2,95,172,157,39,76,155,94,72,129,15,203,37,64,125,102,97,154,170,221,254,
67,184,56,144,35,120,85,209,107,46,204,94,176,48,117,206,194,172,204,194,132,35,72,107,210,133,35,56,97,221,251,220,162,162,179,229,146,28,214,77,158,75,120,205,3,207,186,47,66,20,174,204,116,222,55,221,
190,238,98,205,17,181,195,221,25,27,206,217,101,208,151,142,3,113,244,253,222,131,39,135,143,167,139,249,55,190,241,141,191,248,235,63,111,119,122,103,108,62,31,247,226,166,108,162,175,125,253,189,21,
13,13,143,59,209,166,253,133,183,31,66,226,243,248,201,147,83,10,37,78,29,31,239,205,103,83,158,63,192,58,110,77,80,71,43,147,139,240,46,206,166,179,40,142,127,251,59,191,253,195,191,253,225,95,252,229,
95,116,59,221,209,104,3,222,152,249,98,222,239,245,71,131,193,201,116,194,121,74,16,194,244,232,41,45,210,220,126,38,70,139,18,58,243,223,17,187,5,250,176,72,186,1,12,243,164,216,132,52,133,152,173,73,
230,39,153,158,34,242,17,153,140,155,209,103,145,97,58,1,143,253,240,114,158,158,250,125,117,132,152,214,197,71,168,157,245,64,175,245,35,88,57,2,102,119,220,124,224,153,72,23,22,198,129,207,50,67,93,
194,231,46,204,92,126,97,244,249,106,97,250,114,11,227,35,243,245,142,73,61,233,51,193,49,127,109,27,8,94,98,98,38,185,217,115,157,82,36,243,108,107,84,207,178,144,18,26,167,187,170,221,135,12,81,227,
40,181,39,248,90,233,54,32,136,218,234,68,197,35,51,218,50,163,134,74,239,108,238,252,205,143,255,203,189,251,247,190,240,238,187,79,159,238,121,254,9,150,35,248,156,220,139,155,178,57,7,233,14,127,7,
169,92,26,39,159,60,122,196,227,251,194,102,91,87,71,7,123,57,202,105,148,21,105,216,98,239,76,121,32,34,230,131,141,34,47,39,147,233,63,255,159,255,121,146,164,255,230,95,255,27,167,234,175,254,189,159,
9,52,137,243,249,162,223,239,37,73,50,91,204,131,58,182,241,83,86,181,36,65,134,201,204,2,236,149,167,34,184,175,47,220,152,244,149,188,3,150,22,161,87,136,208,196,208,228,184,245,230,136,126,247,153,
35,176,168,132,229,230,154,204,0,80,248,17,94,126,210,37,148,195,98,237,140,164,98,68,33,93,230,75,234,192,244,100,86,11,171,67,67,51,44,140,201,6,224,229,105,183,59,36,140,200,227,194,47,94,24,35,170,
121,160,50,84,199,158,191,176,213,17,48,45,117,250,212,21,171,133,164,133,128,166,216,76,188,4,210,253,51,141,138,206,243,188,217,108,189,138,115,49,250,220,137,40,14,101,30,12,141,118,245,220,206,167,
110,14,127,110,235,246,48,26,116,85,7,156,87,207,116,219,224,197,76,175,175,251,3,215,131,15,59,186,29,41,51,83,243,177,57,153,217,121,127,48,252,232,199,127,71,76,200,94,73,212,83,51,253,228,160,216,
47,101,243,187,255,235,255,238,185,29,148,213,60,195,225,222,253,194,59,211,201,244,240,248,56,150,170,7,114,124,237,62,253,20,28,147,19,173,14,141,194,165,76,47,69,91,1,164,144,205,70,123,127,127,255,
231,127,254,231,255,225,47,254,226,239,253,159,191,55,30,143,183,182,33,162,26,141,70,200,115,88,19,37,195,230,198,198,104,56,248,232,227,79,137,91,79,248,45,133,230,205,48,196,177,38,245,249,202,51,255,
96,144,194,155,24,117,235,29,71,28,145,76,129,226,244,25,51,10,49,193,49,149,192,107,166,130,227,50,51,78,126,16,37,136,22,66,46,37,9,146,200,189,48,13,16,185,63,254,152,48,168,44,47,238,179,46,57,44,
44,39,47,11,205,213,31,42,150,203,194,234,146,216,77,35,246,250,44,61,82,163,67,95,45,108,54,57,233,13,6,178,176,213,17,86,11,115,196,180,203,229,118,174,50,174,22,230,33,248,87,95,88,69,210,44,103,22,
134,40,13,94,152,167,88,98,26,109,187,206,165,205,41,112,80,205,249,44,218,76,79,38,253,225,232,21,157,203,107,100,172,139,36,154,83,54,78,53,92,10,94,41,134,219,2,247,86,17,242,70,67,2,15,89,73,5,191,
103,186,56,125,28,207,228,115,230,56,171,245,24,63,1,110,206,91,143,112,99,9,147,197,231,244,158,158,131,116,31,13,81,219,231,120,124,2,95,155,145,238,112,153,198,199,251,220,90,42,41,188,66,58,202,4,
113,18,162,100,171,28,184,171,39,143,159,198,113,116,247,222,206,191,253,163,127,51,30,31,49,98,112,124,124,216,238,116,33,224,98,196,249,116,58,5,135,53,232,247,224,248,151,66,186,175,227,182,233,85,
100,167,86,217,21,235,219,58,160,92,144,168,231,1,202,221,25,64,185,59,15,80,206,112,240,43,3,202,127,226,144,238,159,13,155,87,128,116,15,54,94,176,254,98,158,117,165,50,149,123,205,51,21,6,42,60,163,
5,137,107,72,176,160,253,192,172,84,188,152,204,71,244,99,86,235,177,129,128,68,88,161,121,164,156,108,68,179,86,214,108,62,183,247,52,0,152,130,112,78,191,215,155,207,231,152,244,81,118,1,151,117,57,
159,46,151,75,116,85,72,105,102,91,45,156,34,100,25,168,162,200,41,31,137,119,119,15,34,148,113,178,223,251,222,247,62,248,240,3,212,85,110,183,225,24,240,51,251,123,79,92,160,169,174,234,197,98,209,235,
245,180,90,83,100,36,160,128,245,106,215,97,134,150,111,166,168,207,203,17,136,200,210,105,94,152,18,22,19,198,25,8,85,128,94,209,100,7,137,226,245,35,224,187,203,0,119,95,61,13,135,61,117,4,175,52,33,
204,217,132,195,16,99,39,204,165,124,216,179,71,240,11,83,235,11,243,90,4,202,61,179,48,119,221,133,185,171,47,44,240,228,240,5,15,52,234,231,113,105,39,202,79,173,255,55,155,103,109,144,84,158,233,105,
165,255,177,246,128,249,33,233,72,234,29,94,132,81,40,15,45,131,181,124,35,248,172,13,223,182,218,137,86,52,252,72,194,67,111,202,215,224,61,217,230,197,54,218,203,245,124,222,238,69,188,154,95,129,120,
181,170,58,237,38,92,193,217,108,206,53,93,120,221,32,173,152,78,38,204,55,6,215,165,215,237,141,79,198,203,229,34,65,209,25,218,186,43,55,95,44,156,232,88,50,147,17,206,247,129,131,83,164,70,148,101,
25,194,38,155,45,222,148,38,147,217,157,59,173,56,193,25,105,67,10,242,16,54,59,161,205,21,184,16,189,180,196,28,162,12,19,132,75,198,70,123,81,150,47,209,245,198,24,107,24,74,127,68,64,173,182,121,81,
68,56,243,142,160,45,98,74,32,242,188,178,172,141,37,217,2,33,123,128,207,11,28,246,42,18,162,133,224,116,12,247,180,170,206,203,50,38,53,113,44,147,105,68,72,229,217,18,98,79,136,40,99,20,16,67,63,222,
104,52,17,11,74,73,49,173,193,104,210,24,69,76,124,89,229,182,224,15,215,23,134,206,190,174,112,97,74,22,70,202,78,197,139,22,38,71,160,133,97,201,41,134,228,154,22,70,95,13,19,204,40,194,53,88,69,185,
36,221,205,188,204,159,93,88,93,214,103,23,166,205,155,204,49,255,242,54,144,11,160,32,213,77,159,139,254,104,32,33,72,99,228,195,44,41,199,87,94,128,54,200,88,211,232,72,109,188,134,35,241,145,84,92,
45,21,29,39,242,81,200,60,33,200,30,156,33,163,238,182,128,126,61,143,22,246,70,98,26,192,226,185,93,249,71,175,108,152,193,226,140,141,76,220,125,150,239,41,242,35,87,120,157,233,189,160,90,202,25,164,
59,100,118,221,110,247,224,232,136,106,201,136,116,7,95,51,159,79,139,60,135,171,222,104,54,166,216,227,35,177,114,79,251,75,155,191,227,249,3,145,147,54,158,82,22,233,168,12,103,31,157,110,223,74,120,
235,70,131,1,120,171,162,40,159,143,116,103,90,94,66,152,106,134,17,193,41,193,91,61,121,244,9,248,221,102,187,197,176,240,249,124,246,228,211,143,187,189,30,165,168,55,137,116,47,139,242,209,39,63,158,
78,78,26,105,227,233,147,79,193,103,229,121,177,247,244,73,187,211,78,144,204,255,191,33,221,63,207,72,119,134,128,176,13,179,221,7,160,28,99,6,185,122,200,241,149,244,103,165,71,108,125,250,231,199,102,
229,145,64,70,32,198,12,179,13,63,127,8,66,86,204,17,98,216,216,202,129,164,41,73,1,178,240,41,241,122,60,40,218,157,103,67,236,111,124,28,183,250,245,170,239,69,232,22,220,232,185,120,140,198,250,161,
58,115,150,211,157,70,13,137,211,156,10,88,176,33,103,217,178,38,98,140,56,78,78,198,19,117,90,46,209,51,237,59,97,226,148,90,24,141,251,209,252,93,89,84,170,1,191,23,12,229,115,212,82,196,70,85,156,4,
238,36,214,167,144,102,63,203,18,96,68,204,211,63,242,174,70,38,70,48,183,69,42,18,46,243,27,47,221,8,127,104,52,91,53,73,39,73,84,2,177,3,108,173,78,147,228,36,41,229,80,76,65,108,246,210,98,224,97,58,
136,224,132,90,64,201,179,37,44,201,216,68,171,166,211,19,216,175,238,220,189,15,78,60,91,46,33,176,42,202,137,35,72,219,193,254,83,112,103,119,31,60,96,66,30,145,178,231,109,214,47,140,89,83,184,241,
202,89,3,115,248,169,23,44,140,32,40,103,23,166,3,125,115,137,205,89,58,2,183,17,233,8,114,88,130,245,210,180,154,99,70,14,187,182,48,62,66,160,236,240,229,199,55,148,99,254,229,109,120,188,245,218,199,
145,38,160,127,57,120,215,180,140,188,37,21,107,172,182,48,10,135,167,209,5,43,170,56,221,139,116,204,110,202,23,229,149,79,225,153,99,154,193,122,198,219,184,11,109,28,111,93,82,154,80,162,206,32,82,
172,231,218,120,46,86,191,102,42,19,191,190,123,193,195,250,215,57,78,204,186,10,218,147,19,40,119,22,233,222,238,52,33,118,152,76,166,214,39,146,139,249,52,207,115,150,150,101,79,225,101,144,181,98,2,
63,102,140,241,20,214,66,1,72,131,196,162,136,25,39,112,232,225,112,24,49,133,155,82,189,94,239,255,103,239,204,122,36,89,174,251,30,145,91,173,189,205,62,247,242,146,18,100,218,18,96,25,224,139,5,152,
4,252,38,249,77,228,151,177,12,127,41,193,16,248,17,100,45,126,176,4,216,150,44,137,18,105,114,214,59,61,51,221,181,87,102,70,56,206,249,159,19,153,213,221,211,83,61,93,213,211,61,183,134,226,213,101,
79,116,86,100,84,102,196,89,126,231,127,194,69,194,22,112,57,233,174,245,162,100,62,176,57,205,197,64,229,114,124,122,146,119,59,97,227,155,79,103,89,145,227,208,99,69,79,249,243,246,248,77,216,84,194,
46,57,157,76,18,216,123,105,246,254,221,241,98,62,15,159,63,25,141,194,131,76,62,233,108,58,25,143,130,199,71,66,186,117,117,250,254,93,216,157,73,166,138,204,84,74,163,190,127,123,92,150,11,18,5,228,
166,73,8,70,133,105,23,221,238,232,228,100,185,156,7,239,51,47,138,48,165,201,120,76,158,35,11,155,6,139,44,156,237,193,18,12,75,67,151,218,145,238,119,135,116,71,75,202,184,116,136,164,176,116,154,209,
68,173,180,201,168,85,231,11,1,73,41,143,229,179,134,123,202,38,113,12,231,82,96,10,73,226,27,99,160,188,86,213,103,199,40,126,69,99,56,101,76,110,99,36,126,99,60,180,25,147,100,172,152,20,199,248,198,
212,210,57,227,23,81,150,127,157,117,142,235,131,49,216,105,114,214,152,140,106,151,90,79,166,143,223,69,99,206,92,7,159,197,99,108,252,44,47,30,25,107,129,177,206,10,225,74,116,147,73,211,74,51,252,114,
120,253,36,206,157,152,88,16,23,126,78,10,13,156,220,66,72,24,100,16,118,241,68,44,35,17,60,9,119,30,230,144,103,57,94,69,207,21,6,193,74,75,57,124,195,231,18,76,57,186,194,147,71,143,140,74,169,120,113,
100,146,40,98,173,63,51,207,158,63,7,35,14,227,49,108,58,212,177,118,62,15,27,74,150,23,239,142,143,131,177,3,53,133,240,4,188,59,126,19,110,181,211,233,87,213,114,116,250,238,235,111,126,235,221,219,
55,239,223,189,13,38,82,248,103,88,173,123,247,31,4,71,242,219,87,47,247,246,247,177,41,188,124,254,44,124,214,254,254,1,212,175,32,111,80,82,155,188,164,42,203,176,177,29,191,121,125,255,254,67,220,164,
149,204,113,240,70,79,195,100,94,191,122,30,28,222,170,172,78,222,191,13,159,21,70,134,49,225,179,204,126,216,233,250,152,21,43,76,212,232,238,13,33,111,72,217,65,3,79,225,117,108,74,208,14,244,232,225,
78,142,58,171,60,99,231,178,122,5,189,44,203,6,112,11,69,80,14,70,112,255,90,117,148,226,21,44,4,126,227,21,24,44,230,226,68,86,113,192,177,204,2,176,54,182,87,191,211,99,106,215,52,76,188,210,117,164,
227,52,199,255,88,124,173,146,238,27,164,179,68,79,181,19,210,13,16,95,130,214,56,176,122,28,43,56,171,128,106,26,229,162,33,148,12,182,142,198,100,69,197,152,14,42,222,148,72,144,49,137,179,46,73,48,
134,39,150,25,53,211,36,212,206,145,223,11,85,158,209,107,74,234,73,18,170,247,8,239,90,45,242,144,201,70,214,217,138,116,45,172,161,164,98,133,219,132,9,117,98,3,248,179,82,155,136,146,157,142,145,100,
0,103,174,207,93,39,225,80,93,29,73,247,230,58,73,26,117,212,73,74,251,140,166,59,34,83,226,78,107,161,178,229,34,103,86,86,33,20,65,27,220,32,236,149,68,144,18,86,18,143,73,216,78,97,29,97,192,112,16,
171,84,54,12,27,48,231,173,162,0,41,231,104,33,74,106,189,132,91,20,7,133,68,14,170,127,209,108,103,111,255,224,224,232,222,47,127,241,143,97,98,121,209,141,30,147,67,136,128,48,139,254,55,223,255,237,
201,100,244,226,249,175,199,97,211,122,123,28,118,144,175,191,255,91,179,201,244,245,203,103,146,30,78,236,233,201,201,222,30,117,163,232,20,157,233,108,124,122,122,178,127,120,8,250,41,28,14,71,135,247,
142,143,95,223,127,248,8,135,134,211,78,60,253,254,96,62,15,214,219,56,120,139,175,94,60,87,99,211,134,7,112,50,58,13,223,64,88,238,175,190,249,1,57,152,188,65,227,241,117,108,16,65,126,154,67,176,104,
82,238,216,137,78,19,57,124,88,161,71,42,147,18,112,97,158,183,24,220,154,10,88,167,44,151,92,35,85,164,254,166,48,31,192,133,141,209,184,0,229,218,105,11,195,218,164,192,253,41,188,229,190,108,253,111,
180,132,248,180,235,164,218,41,22,34,170,218,231,205,87,174,148,87,67,26,211,171,200,189,242,236,150,175,28,69,50,99,248,59,85,143,193,136,46,208,50,142,1,130,68,231,205,106,188,165,25,35,86,88,202,192,
234,202,152,165,142,169,91,99,112,29,47,73,118,74,75,194,108,33,121,22,86,3,191,206,58,67,131,63,174,15,114,121,164,143,110,27,55,11,159,133,247,58,142,65,62,225,204,24,185,142,171,164,129,169,243,141,
38,2,47,26,159,229,242,3,18,7,151,118,121,136,251,82,75,216,186,215,235,25,35,225,13,164,216,99,107,19,1,112,163,155,237,60,173,13,255,111,180,177,195,59,19,59,163,24,221,117,50,74,188,101,81,151,47,188,
207,144,187,14,191,250,242,229,43,156,94,48,43,96,247,82,248,92,27,22,136,108,150,104,74,136,4,99,83,106,228,125,236,111,238,5,137,162,109,187,174,202,224,238,77,167,19,46,223,33,161,247,112,16,77,199,
163,249,108,14,211,35,24,104,143,30,61,25,143,71,97,216,242,112,62,28,238,7,107,235,197,139,223,4,99,106,255,224,200,55,151,245,42,115,156,160,224,166,149,87,53,232,119,178,176,179,176,125,134,237,160,
55,24,228,5,181,212,166,138,124,10,19,74,82,194,11,18,149,210,86,168,125,170,156,40,229,103,149,52,40,183,34,117,206,62,181,211,126,89,77,34,130,27,165,8,77,22,169,13,190,2,84,225,37,188,129,43,80,223,
115,23,171,216,16,85,73,18,73,153,99,98,27,111,208,112,219,198,192,104,253,132,235,4,19,9,45,51,248,213,133,99,34,157,123,216,28,112,170,119,198,59,145,73,249,133,21,87,200,197,230,158,103,241,34,127,
243,40,147,211,200,53,176,11,54,253,106,115,245,117,6,225,88,123,139,6,200,89,154,187,243,235,35,134,133,236,107,140,61,133,239,192,181,199,224,29,119,210,159,193,180,175,227,27,90,163,185,142,67,134,
129,205,52,62,251,125,6,4,81,182,39,148,160,49,190,200,41,57,186,67,122,213,249,15,127,94,141,54,202,236,181,57,245,192,163,140,183,164,225,73,6,111,89,22,157,130,69,239,10,108,234,44,1,94,35,88,70,254,
96,45,178,217,236,51,139,166,59,12,4,72,65,168,224,148,69,167,223,34,203,195,58,150,62,152,209,144,232,203,34,206,95,66,253,139,74,79,82,144,223,120,225,95,191,126,17,174,115,120,239,222,253,123,143,250,
253,225,235,23,207,95,60,127,214,235,245,81,3,84,46,151,199,223,126,27,214,226,224,240,40,108,221,199,47,95,133,105,23,69,247,209,163,175,16,251,95,132,123,224,150,179,137,77,145,189,200,211,140,100,255,
184,29,0,219,47,100,167,60,126,252,244,165,175,159,61,251,85,88,128,225,222,222,193,225,61,201,118,88,139,77,25,129,45,244,52,76,88,211,29,72,58,107,186,119,168,133,92,150,48,233,94,131,116,207,57,106,
144,50,233,30,230,32,2,50,220,170,3,164,123,248,97,162,245,204,80,176,76,195,166,217,34,221,195,51,71,95,68,198,82,241,220,31,33,12,205,184,32,11,164,187,78,108,229,88,94,231,232,190,91,99,112,16,95,233,
58,120,109,42,95,113,187,19,120,24,20,177,230,144,70,85,228,157,34,203,74,142,245,224,224,138,92,219,42,58,36,99,242,86,199,180,207,50,38,54,151,132,48,44,252,50,99,216,104,98,26,254,210,245,137,99,108,
162,221,202,156,88,39,181,52,37,209,245,137,142,153,124,150,246,154,52,171,99,18,241,221,146,90,14,128,120,29,14,16,155,198,193,11,79,47,52,166,131,123,192,193,41,177,30,236,127,254,47,255,181,233,117,
157,22,131,65,239,193,131,251,191,252,213,175,33,55,28,238,123,49,159,190,125,123,60,155,77,102,179,57,139,52,49,144,21,143,126,165,66,164,163,12,239,49,48,145,130,183,191,44,137,138,234,118,187,69,183,
251,213,211,239,33,178,31,94,170,239,127,243,189,55,111,222,142,198,99,49,8,216,136,83,2,197,74,163,2,133,185,109,244,161,125,84,23,168,65,30,232,15,193,10,184,104,1,253,243,63,254,125,216,152,158,126,
253,3,0,229,77,75,206,120,133,139,47,235,76,180,161,180,67,162,54,13,215,142,199,40,32,96,160,252,178,43,156,155,216,136,156,205,163,214,21,154,203,174,92,225,6,39,118,142,116,111,204,4,61,186,109,162,
94,255,93,28,51,58,121,127,120,120,255,74,215,129,253,206,239,170,184,255,192,130,194,54,159,112,255,119,78,157,83,65,85,216,244,189,134,41,172,182,76,141,120,17,198,156,199,139,174,58,134,3,172,254,58,
215,1,202,36,97,117,17,74,185,194,26,42,85,111,208,100,27,100,70,216,189,219,235,3,132,16,195,43,74,247,83,152,31,65,164,56,159,102,12,41,205,173,140,105,127,22,252,62,92,231,194,251,202,26,210,157,205,
191,146,213,132,139,34,159,78,43,16,216,253,254,224,253,251,183,123,123,251,164,209,91,161,65,141,150,171,75,55,91,86,69,212,82,91,196,155,50,14,187,96,227,14,159,115,239,232,190,102,46,195,197,11,114,
217,248,111,27,210,157,247,219,84,131,92,77,100,13,13,199,217,110,82,43,16,59,189,203,131,185,41,73,91,4,173,89,182,60,106,2,194,123,23,233,116,18,59,174,229,10,94,172,72,105,131,142,97,184,108,115,133,
104,160,194,159,74,225,114,91,212,17,185,136,224,67,108,158,155,177,55,87,208,137,137,129,139,31,138,115,44,4,255,102,38,38,154,238,87,153,152,167,141,187,246,154,150,253,236,38,192,237,51,73,232,15,50,
66,136,77,225,96,64,205,95,201,178,200,204,160,248,76,234,243,19,208,33,168,49,64,165,84,28,35,42,49,215,24,3,101,199,13,92,135,207,248,28,26,252,222,164,31,95,31,147,3,234,83,188,10,253,95,112,29,110,
130,37,200,160,138,14,176,129,244,177,57,127,96,140,244,121,192,117,170,75,239,235,172,166,123,216,68,15,247,247,131,19,55,155,206,162,166,123,150,218,201,100,50,155,78,185,65,169,69,181,71,162,226,1,
137,58,149,162,176,197,134,64,183,211,161,189,150,123,151,246,186,189,163,123,15,162,207,127,255,222,81,248,247,87,223,126,187,174,166,123,213,104,186,131,147,90,149,78,79,219,210,233,216,179,135,131,
189,222,96,16,12,120,21,62,175,62,38,157,110,91,210,233,181,21,200,69,234,177,137,30,174,170,51,210,233,59,77,247,47,82,211,29,22,83,120,45,19,96,77,81,104,148,94,102,143,162,8,197,165,188,182,243,88,
17,201,228,122,3,123,51,130,156,235,127,150,213,22,246,40,68,69,100,227,67,107,152,115,184,25,79,145,71,208,94,59,144,194,5,166,167,75,67,204,242,161,28,231,189,116,206,155,25,115,129,166,123,248,202,
246,134,123,167,163,17,114,141,97,19,120,123,124,28,54,44,60,232,34,219,110,155,238,190,17,176,134,45,71,205,66,184,251,109,88,145,94,143,186,221,62,120,240,56,203,11,172,96,120,249,30,62,124,112,114,
114,58,95,44,182,167,233,158,23,69,70,113,156,157,166,251,142,116,239,175,79,105,59,105,57,36,207,97,182,138,5,81,43,147,184,104,64,135,40,254,216,105,48,37,22,14,129,165,112,51,232,217,154,159,37,161,
131,196,106,143,40,99,47,93,67,175,89,38,33,230,25,21,2,114,161,121,66,170,136,252,44,216,221,5,154,238,243,197,252,232,224,48,12,26,135,77,202,26,38,152,222,73,0,82,160,9,147,232,171,8,220,195,235,54,
70,157,226,243,28,90,122,157,78,39,124,222,112,56,220,63,60,210,234,57,119,120,112,16,126,254,242,245,107,205,248,237,52,221,119,154,238,159,95,211,29,155,58,194,195,2,254,216,88,104,97,69,203,85,91,168,
234,81,141,227,217,52,34,153,118,109,33,77,211,146,122,224,147,211,181,175,179,29,209,78,105,108,107,173,111,9,74,124,104,13,85,6,88,106,178,181,62,251,243,139,145,94,160,233,78,126,108,81,12,134,253,
96,7,189,124,241,235,233,116,138,96,76,44,23,64,92,74,9,45,0,193,14,23,14,191,200,253,86,83,188,93,193,194,122,240,224,73,194,77,213,41,203,150,231,143,30,61,154,240,159,157,166,251,142,116,191,133,164,
187,132,90,26,66,189,198,25,192,233,43,195,169,250,58,227,130,182,170,46,195,35,7,95,27,39,13,210,26,16,246,227,49,201,7,133,52,211,85,33,77,191,117,209,78,213,171,169,172,214,180,93,70,249,243,195,230,
163,48,253,109,18,35,189,88,211,125,58,155,15,7,131,127,248,251,255,51,157,77,151,203,165,4,152,60,123,27,137,40,133,122,237,127,26,46,151,7,151,175,83,132,135,35,56,193,40,83,236,245,123,193,3,122,242,
213,55,81,161,60,124,241,223,124,239,235,44,203,158,191,120,41,133,160,59,77,247,157,166,251,109,210,116,215,67,212,43,220,171,125,151,25,198,165,51,155,206,43,42,5,113,106,136,97,227,115,210,5,221,225,
213,32,77,14,102,95,64,222,200,222,215,22,210,164,184,62,132,52,43,62,105,210,173,138,118,2,119,242,198,201,7,73,132,225,236,26,38,250,87,137,234,208,139,155,120,155,196,72,207,146,238,74,6,248,255,245,
183,127,27,188,152,154,242,151,82,103,27,155,254,57,23,101,199,13,245,89,27,238,241,15,106,236,31,44,131,85,29,28,220,31,12,247,180,106,148,182,142,175,30,63,10,22,214,139,231,47,141,162,46,158,97,22,
209,116,7,233,78,45,232,29,105,202,216,36,74,118,180,184,109,246,137,136,219,54,12,137,211,59,201,222,15,65,222,158,200,145,10,56,248,165,64,121,154,52,56,248,71,128,114,112,234,87,5,202,17,17,16,153,
246,29,233,126,215,72,119,144,220,176,70,17,71,12,78,187,33,58,148,155,242,186,10,186,149,226,83,183,80,47,124,191,20,174,86,210,189,133,122,217,15,224,78,105,155,116,223,18,158,70,196,60,189,35,32,203,
179,152,128,251,208,189,67,7,16,178,154,86,213,186,111,9,118,119,150,116,135,138,192,232,244,228,253,233,137,36,155,172,132,195,237,74,80,156,59,125,213,117,48,163,208,126,185,162,212,186,43,242,98,176,
119,208,239,239,161,60,81,250,21,90,123,255,254,189,126,191,247,230,205,219,197,114,97,76,180,168,160,2,10,116,29,154,238,196,169,211,23,159,74,207,11,184,138,130,131,107,220,75,170,225,81,192,168,220,
118,44,79,207,24,93,19,172,254,2,160,220,156,1,202,99,18,1,229,150,109,160,220,124,0,40,143,88,64,184,241,122,5,40,71,8,105,101,98,59,210,253,110,145,238,166,33,221,13,75,132,39,145,228,86,210,157,82,
66,49,235,77,88,99,155,62,103,113,152,219,38,218,153,132,131,140,220,213,28,134,5,251,173,103,239,189,69,177,19,139,195,98,173,26,72,189,53,98,164,23,104,186,135,27,120,246,235,95,78,198,19,8,159,227,
24,17,225,74,219,136,189,134,97,121,150,61,253,250,235,225,96,159,1,235,36,54,73,229,168,176,193,11,22,222,156,71,15,31,14,250,253,227,183,111,223,188,125,219,82,20,53,59,77,247,157,166,251,45,212,116,
71,232,93,53,212,209,59,85,148,215,197,228,143,233,14,33,18,209,2,154,226,93,56,137,73,65,128,241,154,92,42,204,44,58,137,212,18,35,243,55,60,6,115,182,34,206,12,186,10,96,192,202,189,123,93,36,17,7,36,
106,15,121,175,207,48,231,15,141,185,64,211,253,228,221,241,98,177,128,32,31,197,131,185,255,138,195,177,172,188,56,219,204,73,183,215,219,219,59,98,156,140,62,14,129,123,226,202,18,177,159,195,255,122,
252,232,97,167,219,125,241,242,229,104,60,70,142,88,145,83,179,211,116,223,105,186,223,66,77,119,54,58,28,88,106,84,53,67,185,4,102,41,123,148,41,142,141,51,100,57,101,155,110,147,104,39,71,199,34,89,
142,176,186,139,20,123,210,210,125,247,170,60,67,146,185,76,177,223,90,49,210,179,164,123,120,212,79,78,222,193,103,177,154,194,107,132,197,156,106,200,176,131,243,228,233,215,18,56,87,66,129,194,67,60,
52,44,213,222,222,222,254,254,48,124,228,179,103,207,230,139,101,36,221,69,134,145,45,237,45,145,238,62,54,90,220,145,238,59,210,253,83,198,228,21,170,70,18,213,61,224,180,44,60,2,84,212,98,219,2,176,
183,61,210,253,234,99,26,213,119,103,98,234,69,122,234,4,107,165,226,8,169,222,59,116,7,37,32,141,49,160,216,173,210,231,107,207,199,222,204,189,159,213,116,15,135,55,142,162,94,183,27,254,58,152,90,148,
116,75,224,77,120,43,209,25,250,18,31,60,124,76,141,233,141,100,76,97,69,132,61,189,215,235,238,13,135,193,7,12,31,19,172,170,215,111,222,132,239,94,197,215,37,90,68,131,185,118,122,29,77,119,18,62,135,
66,57,48,152,179,210,233,219,213,116,71,146,232,188,116,58,239,253,59,77,247,47,86,211,157,196,145,188,232,136,91,187,170,161,46,144,93,133,240,238,117,68,77,55,50,198,72,188,24,52,153,20,66,98,31,230,
194,134,84,205,119,218,2,10,189,175,120,239,225,161,83,109,120,163,166,86,162,103,237,149,230,99,110,224,222,51,167,58,176,200,52,133,1,191,243,59,63,252,231,95,252,211,116,58,45,58,69,216,122,194,191,
212,78,220,70,244,33,10,175,115,167,40,126,244,163,31,145,78,144,51,101,89,133,109,71,137,97,54,178,156,127,119,114,50,26,141,196,108,70,2,85,73,52,43,253,67,180,153,27,229,7,197,215,180,90,178,11,225,
7,216,126,5,105,138,74,224,140,77,136,26,122,15,77,55,37,17,3,99,197,97,142,177,213,44,249,200,110,44,5,29,242,44,23,37,64,102,196,201,238,224,176,180,166,81,165,92,60,252,46,21,145,73,209,5,239,224,228,
249,210,186,132,175,25,181,161,28,72,162,203,50,86,150,129,16,102,160,28,185,11,92,193,121,21,75,141,19,163,185,113,205,165,213,43,24,238,188,2,125,111,37,221,69,123,71,229,198,18,212,114,89,16,64,84,
198,197,137,137,56,135,68,174,128,57,56,100,48,168,70,247,130,137,133,13,208,197,72,12,60,202,186,254,28,38,192,205,141,73,91,141,187,175,92,124,199,45,87,226,24,164,100,160,182,40,104,15,105,96,178,218,
103,42,15,53,29,75,212,86,10,190,188,182,53,240,68,132,179,188,135,217,236,24,162,234,189,145,104,26,179,142,124,83,89,120,240,121,71,165,80,44,253,30,11,255,242,227,34,247,213,190,119,99,32,65,87,249,
120,29,246,142,139,180,243,209,249,228,105,46,220,188,206,231,6,238,253,2,210,61,108,45,251,123,7,193,6,10,91,85,48,142,250,84,148,151,47,230,115,21,24,164,77,228,135,255,250,247,194,70,94,46,203,197,
114,193,242,172,245,98,49,159,205,230,147,201,100,116,74,86,213,108,58,227,228,151,21,190,3,49,27,21,150,103,171,193,183,147,20,168,43,140,45,215,193,109,139,239,195,225,54,4,230,85,142,70,88,48,35,125,
71,234,51,56,120,20,222,226,146,2,199,9,29,143,30,63,48,251,69,83,77,190,30,1,17,176,222,146,22,176,13,78,21,171,169,153,177,216,145,238,95,32,233,254,1,218,187,25,163,18,23,40,234,88,161,225,53,154,127,
211,232,89,83,148,38,197,99,50,159,134,99,247,209,204,48,231,238,221,68,41,205,232,25,139,63,185,246,124,216,196,208,6,101,66,159,27,200,222,121,157,18,106,254,36,176,180,37,210,157,176,166,52,235,15,
135,225,177,158,207,169,29,97,56,198,135,195,97,206,13,194,194,44,187,189,254,254,225,209,114,89,134,29,109,62,159,143,39,147,241,104,60,157,206,130,59,70,141,8,75,209,90,138,25,25,217,47,208,90,193,34,
245,94,39,42,123,146,196,46,132,204,224,130,199,77,149,184,211,176,66,162,251,20,189,115,32,149,184,131,3,203,58,203,41,170,187,158,54,160,215,156,136,129,97,236,84,141,11,97,158,84,218,138,56,105,60,
193,122,132,70,54,101,11,202,46,37,88,89,136,65,188,255,128,218,119,164,251,151,74,186,95,56,38,152,18,242,130,104,108,158,107,212,106,43,52,60,100,228,60,72,119,60,39,36,238,102,68,139,221,40,165,45,
249,199,107,211,222,81,7,56,133,198,60,87,219,40,197,110,47,212,161,231,35,202,129,169,86,157,117,151,74,93,180,141,250,241,12,9,92,54,159,230,190,60,244,154,157,54,216,148,49,44,28,144,114,75,135,18,
165,153,78,196,136,183,73,186,99,103,235,15,134,193,188,10,123,214,114,185,12,22,86,150,231,195,225,94,248,22,159,60,249,26,169,67,43,220,182,5,218,131,26,29,4,223,169,22,71,85,202,101,183,20,234,90,246,
16,77,219,37,226,141,234,241,5,150,74,15,174,120,5,47,101,80,124,153,230,245,150,193,224,225,149,83,215,74,122,21,235,209,186,48,173,40,214,163,18,17,125,241,255,148,29,151,227,32,182,162,140,186,11,168,
56,211,194,164,29,233,254,5,146,238,31,54,37,204,57,211,198,55,68,184,66,124,94,187,221,128,140,99,84,48,109,83,236,155,162,198,97,218,224,211,81,229,131,134,79,42,93,101,99,145,35,162,52,109,138,221,
180,250,26,58,97,8,140,204,153,18,217,238,163,243,193,125,201,38,175,216,64,51,134,133,54,49,103,60,120,140,28,110,153,116,143,154,238,195,193,176,248,222,15,150,139,217,171,87,47,167,147,233,114,177,
124,252,244,43,238,65,95,67,119,85,106,235,18,246,145,56,115,143,109,62,86,71,107,115,34,81,85,70,35,110,35,156,183,231,118,181,137,54,35,130,99,37,251,17,200,111,118,36,37,242,146,136,65,107,227,54,35,
242,133,80,64,181,14,56,120,252,121,212,207,139,165,217,177,128,211,81,16,186,42,10,18,137,38,90,74,128,242,166,165,178,218,104,26,85,51,90,221,26,149,112,118,164,251,23,173,233,190,206,24,78,55,137,238,
123,194,76,47,94,164,240,198,226,245,81,77,247,164,77,114,179,66,252,6,136,240,182,94,59,100,126,209,98,7,193,1,204,25,241,247,11,181,234,249,224,183,43,115,94,111,62,20,3,145,120,124,18,81,33,120,124,
24,3,55,243,70,73,247,182,166,59,117,60,206,178,127,243,187,247,44,37,86,200,152,81,71,143,79,39,180,23,145,20,41,17,180,8,230,91,233,127,87,51,240,157,196,142,21,160,25,32,57,8,207,150,237,39,88,20,130,
189,136,247,39,165,76,82,93,88,115,21,52,28,76,254,74,156,144,159,90,75,164,64,185,168,116,193,207,140,150,20,246,130,40,9,63,30,157,190,120,254,140,154,247,228,249,211,167,95,245,122,67,122,175,117,175,
66,50,148,243,118,169,52,203,208,166,79,17,61,223,145,238,95,176,166,251,90,186,239,212,210,166,226,138,232,52,178,38,64,189,248,163,93,20,107,3,13,111,89,59,148,107,18,229,241,217,8,122,6,187,33,252,
127,180,216,17,46,225,35,90,245,38,139,94,179,244,13,187,2,230,6,109,2,88,17,124,157,68,213,213,101,62,156,220,191,89,210,93,222,79,10,212,165,242,184,59,52,37,108,137,98,176,189,84,146,74,95,6,155,37,
22,45,71,210,29,133,126,56,15,32,169,147,104,116,206,2,220,0,164,167,122,175,106,160,74,58,89,25,111,113,230,52,143,227,83,86,152,230,168,179,180,197,208,30,225,9,36,101,165,176,81,141,71,176,227,210,
71,136,63,247,213,203,103,221,78,119,70,127,166,48,58,30,63,249,106,48,24,74,240,82,242,168,30,219,162,111,66,105,210,62,107,71,186,127,193,164,251,250,99,68,247,93,204,157,132,49,69,57,50,209,109,16,
157,122,209,211,128,234,100,153,134,191,14,237,13,242,30,99,98,34,72,125,24,31,123,133,157,159,115,140,195,99,206,146,109,144,200,175,91,127,62,184,47,121,219,140,148,213,57,211,208,240,89,150,46,203,
43,223,23,52,59,63,145,116,231,8,28,99,29,150,170,97,140,190,193,156,152,135,184,168,103,159,14,253,163,211,8,104,58,235,207,144,238,180,205,89,241,75,53,151,1,247,207,121,133,81,145,67,228,123,174,176,
25,42,14,174,17,122,215,206,212,196,51,179,81,17,68,67,135,21,210,189,145,111,111,114,61,130,86,88,243,252,217,111,230,51,74,23,4,243,106,111,111,111,177,88,76,103,179,231,191,249,245,225,209,209,131,
71,79,34,117,10,59,218,169,116,186,229,168,60,227,90,201,142,116,255,130,73,247,245,199,120,235,164,55,40,63,18,20,110,182,162,107,158,135,87,137,251,78,135,211,210,149,75,31,91,98,92,19,61,83,77,46,140,
1,197,78,190,39,161,126,14,117,36,103,230,44,104,21,35,126,36,134,107,220,138,94,59,5,29,178,117,230,35,58,235,244,70,208,73,204,59,134,179,49,140,167,115,14,243,185,234,125,33,160,177,230,250,92,64,186,
107,117,139,4,109,51,138,161,72,180,89,113,119,47,46,91,108,18,113,142,116,143,52,106,18,157,71,254,197,186,114,8,75,147,49,73,93,115,107,47,181,207,166,81,119,134,230,161,246,27,135,130,15,54,163,68,
58,151,89,164,216,98,57,118,132,185,83,222,167,202,124,73,97,181,240,74,242,255,209,195,231,50,27,102,90,155,122,94,79,198,99,180,53,45,151,203,145,115,195,225,32,252,153,78,166,111,143,143,131,233,241,
240,225,227,148,243,161,226,147,74,68,29,125,52,129,231,153,29,233,190,27,131,49,208,71,87,183,221,212,86,78,87,212,174,117,138,194,113,86,69,82,211,155,67,207,56,14,37,137,36,36,148,139,60,111,207,89,
99,83,66,231,227,129,17,58,223,104,131,188,171,127,86,163,233,14,204,95,82,249,244,224,85,98,250,152,43,221,23,111,85,137,164,232,215,152,207,89,77,119,43,158,162,72,3,169,136,151,209,56,20,114,85,53,
111,231,6,100,0,242,32,92,77,88,67,74,188,233,149,152,0,11,80,151,77,92,63,73,201,155,86,115,55,124,16,2,108,169,36,22,19,164,93,35,218,234,181,201,34,114,31,152,24,198,72,38,213,86,147,124,52,217,27,
151,253,69,217,89,186,78,176,103,56,3,29,206,150,172,172,187,85,213,169,190,253,223,47,233,133,53,34,215,157,82,75,49,178,126,134,140,113,156,142,78,71,163,211,195,131,67,47,196,141,44,4,194,213,89,235,
179,118,154,238,95,164,166,251,154,99,24,70,169,161,125,206,36,132,211,92,153,104,159,231,121,6,199,16,143,244,22,208,51,23,187,34,179,90,10,157,232,57,213,65,208,119,170,125,127,155,236,33,30,45,165,
201,174,164,179,110,149,176,73,4,57,64,33,138,32,129,53,98,173,241,58,226,79,173,125,95,170,88,37,162,197,31,189,247,244,39,63,254,15,100,218,241,255,153,180,192,29,250,72,144,197,212,186,36,248,140,254,
215,71,225,115,163,210,233,81,240,61,94,65,33,17,175,2,53,177,87,180,132,166,164,33,149,105,181,20,18,171,33,21,139,68,203,165,97,46,70,223,50,254,46,204,59,151,214,179,225,100,186,63,113,69,157,151,69,
111,50,232,79,7,244,207,69,191,179,232,21,243,78,119,214,235,205,122,211,103,147,241,251,145,111,121,251,112,66,29,197,155,170,240,144,21,57,69,46,79,78,78,30,62,124,20,27,136,155,168,10,175,172,252,78,
211,253,11,211,116,191,250,24,216,194,17,141,78,56,230,203,58,235,168,210,103,37,75,168,224,110,9,61,99,129,80,53,249,121,51,141,5,18,72,178,115,243,61,223,230,155,148,194,91,193,202,62,250,89,146,43,
80,187,94,53,45,156,213,6,93,64,189,62,225,190,64,50,21,188,237,172,57,159,204,180,254,120,62,237,41,7,39,190,5,103,214,153,47,148,154,41,118,3,209,23,30,233,170,96,133,90,40,252,33,200,197,20,123,201,
65,119,72,143,42,150,38,38,141,21,95,63,141,78,13,75,178,90,125,163,132,25,42,235,210,8,56,229,173,148,59,37,162,36,171,113,104,53,122,205,34,153,79,247,198,225,19,122,227,94,119,217,79,92,18,189,87,158,
158,1,32,86,45,171,55,175,94,5,235,3,93,33,129,94,144,171,7,121,253,96,96,206,43,142,26,82,197,158,110,239,178,185,69,155,177,166,66,135,240,79,142,113,208,193,134,12,166,28,177,130,234,105,203,241,48,
56,174,152,146,7,114,107,103,86,140,173,223,102,205,25,177,85,70,177,181,230,216,111,154,53,135,136,184,172,57,95,22,253,183,117,98,78,27,22,99,98,184,2,178,34,218,108,238,38,138,221,62,215,24,54,250,
183,82,232,151,37,57,92,34,180,86,231,78,192,4,151,80,132,152,129,196,178,172,228,144,37,206,160,142,141,34,185,204,43,67,147,114,113,95,206,141,225,166,185,72,231,154,143,141,145,100,49,153,36,104,236,
195,101,200,49,202,30,199,196,168,110,194,146,188,87,250,44,86,31,76,99,174,57,220,187,145,123,151,38,242,200,74,175,61,231,102,12,59,123,225,141,168,214,159,79,250,147,159,252,36,110,88,89,214,43,235,
229,153,10,44,112,219,158,185,109,234,60,205,251,58,182,240,176,215,100,244,110,115,40,74,242,238,196,109,167,13,216,233,182,77,186,47,187,243,217,225,36,169,211,193,219,97,182,44,82,14,225,93,72,186,
255,230,255,253,114,185,92,198,38,104,144,13,105,130,235,200,57,50,90,113,120,116,191,219,235,238,72,247,29,233,190,6,233,158,0,32,68,50,41,44,119,39,47,80,63,124,1,201,173,223,35,82,240,155,208,62,79,
240,138,249,70,175,61,209,189,32,105,143,65,91,245,250,234,159,21,95,31,152,81,120,31,217,118,225,4,165,243,231,41,255,43,220,87,125,117,210,189,189,97,213,100,112,249,171,74,167,43,142,126,49,183,189,
85,210,125,214,155,204,134,211,176,79,237,157,28,100,108,188,159,33,221,19,137,143,249,201,248,244,248,152,116,35,52,135,34,87,139,186,221,81,88,117,48,24,60,122,252,116,71,186,239,72,119,209,19,69,132,
69,153,56,54,207,105,189,57,116,171,85,19,234,38,130,201,10,214,241,197,132,186,107,72,247,34,219,140,246,121,74,97,35,180,95,73,109,91,139,93,43,213,88,99,94,8,245,171,126,150,164,112,36,149,111,148,
48,90,161,252,241,182,57,141,174,20,68,186,111,89,211,189,237,18,130,84,128,116,186,3,151,224,212,211,17,233,244,134,186,62,207,109,215,220,97,145,236,17,165,174,183,71,186,47,58,243,89,127,222,157,247,
134,147,61,218,38,148,116,15,191,176,92,204,38,163,17,109,79,252,88,134,171,206,231,243,146,148,88,82,219,202,39,192,90,78,162,238,32,199,44,15,14,14,119,164,251,142,116,103,136,199,114,112,195,195,34,
110,85,26,163,133,138,211,80,129,164,137,16,127,100,134,165,58,67,105,179,246,119,234,215,208,71,215,106,228,181,136,112,234,141,224,74,60,57,108,214,165,45,45,118,251,201,100,185,168,173,226,191,44,190,
130,74,123,49,127,218,148,63,149,30,175,232,190,131,7,220,162,166,123,123,195,226,188,134,139,210,233,170,172,0,28,180,209,56,191,72,58,93,0,235,92,184,109,161,174,183,71,186,151,201,114,190,63,45,22,
249,96,60,144,126,175,60,114,58,25,191,59,126,147,229,57,36,69,113,74,32,31,167,61,214,68,229,57,86,126,233,42,133,195,33,27,12,168,141,162,209,141,108,71,186,127,55,73,119,165,216,233,121,150,56,145,
211,214,56,177,95,3,211,222,40,85,33,168,25,0,59,31,44,103,48,46,125,255,125,35,106,250,1,221,119,47,144,246,101,99,86,112,48,24,82,92,84,150,134,169,58,226,126,242,240,160,94,67,139,61,81,37,21,214,205,
225,192,177,69,140,150,143,64,89,159,156,247,17,203,233,60,223,38,221,183,141,221,157,177,176,76,240,192,195,30,233,169,251,16,25,19,240,222,17,26,95,44,151,106,249,164,0,172,201,211,41,185,33,7,155,29,
121,218,33,229,154,44,137,210,233,146,173,80,210,189,174,74,144,238,9,31,95,196,13,49,15,5,220,129,2,153,48,159,56,53,219,34,221,19,142,175,229,248,134,194,110,21,166,54,123,48,73,170,100,120,186,79,113,
135,178,134,213,244,237,235,23,184,229,224,11,72,143,19,254,83,51,231,134,68,1,61,118,34,252,147,176,224,17,237,143,68,169,21,69,94,20,197,239,246,146,19,233,70,29,174,19,142,47,102,2,228,23,195,148,112,
107,0,202,41,187,17,30,148,140,2,222,212,76,133,87,44,99,199,27,164,123,123,197,232,231,252,39,146,238,103,86,204,51,178,203,107,78,81,149,148,73,247,176,188,34,32,147,166,145,116,15,63,76,212,203,227,
104,87,157,102,121,155,116,47,178,56,177,234,162,137,121,157,216,231,108,127,114,3,99,76,171,165,205,250,215,161,103,140,100,255,172,24,86,42,211,194,32,144,232,163,203,129,164,53,104,234,129,201,67,210,
198,184,26,198,92,49,46,36,158,206,163,94,48,228,47,31,115,22,7,227,83,182,226,176,50,230,131,64,135,249,100,172,12,30,95,171,85,11,238,61,229,14,21,113,13,53,105,35,250,247,206,220,28,10,183,178,97,165,
100,97,85,40,249,88,91,58,61,197,233,209,72,167,107,91,102,132,87,182,65,186,143,6,39,225,194,7,239,143,34,233,30,230,243,250,213,179,201,120,92,35,58,67,132,42,9,138,225,247,99,249,2,135,207,137,244,
231,9,208,213,56,223,103,251,61,250,207,195,175,190,58,181,239,71,253,147,225,104,111,71,186,127,55,73,119,80,150,208,62,215,124,17,224,68,238,69,199,100,57,81,236,222,157,215,116,15,75,90,164,171,212,
248,114,233,215,211,125,231,3,94,25,23,68,19,146,116,93,113,84,166,234,203,178,186,134,88,43,177,123,69,150,199,251,74,84,213,13,137,60,6,143,47,208,188,87,21,8,115,147,154,238,103,255,92,40,157,14,152,
245,34,233,116,160,94,45,110,91,168,107,9,196,109,156,116,15,110,115,217,89,22,147,46,240,5,156,76,111,94,191,152,205,102,20,230,161,42,185,140,164,113,91,46,33,227,190,50,95,248,114,124,106,8,99,21,12,
191,163,189,225,189,251,143,109,157,228,211,78,57,152,187,49,207,103,71,186,127,87,41,246,60,203,80,226,26,85,238,188,105,84,63,160,182,184,14,201,157,180,198,0,227,98,27,249,44,201,45,4,2,127,127,20,
202,176,28,132,224,97,107,137,163,174,61,159,11,41,118,16,234,104,185,8,138,221,137,2,64,172,94,188,120,125,140,144,238,112,91,92,123,62,78,217,163,141,11,204,174,100,9,75,103,82,101,148,206,112,219,64,
120,34,183,13,190,137,65,135,54,117,93,69,110,59,141,220,246,166,73,247,69,127,94,23,85,255,116,192,14,37,225,221,179,233,248,253,251,119,225,154,99,170,185,177,146,105,213,36,180,236,179,70,154,179,170,
158,104,236,50,109,15,14,14,31,60,124,28,188,51,86,189,182,179,238,140,230,176,204,118,164,251,119,138,116,199,99,145,113,198,169,102,247,60,138,217,74,142,111,133,192,254,184,88,43,226,80,90,241,230,
47,163,216,249,36,133,8,45,176,38,131,182,128,210,86,111,171,98,173,206,52,196,60,153,117,242,64,90,126,157,1,242,157,161,252,19,82,151,130,28,185,120,163,171,159,21,171,121,183,49,231,149,13,203,166,
157,72,186,55,120,180,137,190,156,141,220,182,176,216,45,110,59,130,241,109,110,123,27,164,251,100,127,148,47,139,238,162,27,73,247,227,227,87,203,114,185,88,204,169,162,170,40,150,139,37,233,11,106,243,
53,99,219,96,124,34,93,96,195,22,156,165,97,191,216,219,219,59,58,58,42,58,125,225,77,76,82,103,193,130,11,187,226,32,166,182,119,164,251,23,79,186,123,35,162,47,173,120,46,189,54,54,145,252,184,120,229,
94,127,113,13,132,13,65,210,240,183,69,214,249,56,234,197,1,92,180,55,167,80,76,197,20,251,118,240,180,54,86,198,80,149,211,16,173,60,118,138,95,201,22,118,118,157,141,248,1,177,232,167,253,89,48,2,182,
135,221,221,49,210,189,202,203,224,18,14,102,157,72,186,79,167,147,201,100,186,88,44,194,119,156,5,75,181,118,210,231,213,87,198,201,142,217,104,186,179,5,87,51,125,147,242,238,22,54,145,147,247,239,123,
189,97,237,69,127,186,152,119,170,206,178,42,42,50,178,118,164,251,119,134,116,71,139,19,110,149,148,33,71,93,123,39,42,42,73,82,132,13,133,219,139,32,162,202,7,7,137,151,92,66,114,227,144,165,116,211,
199,40,118,146,252,23,253,110,14,37,147,21,227,141,52,48,190,62,13,127,118,12,39,220,13,66,52,231,40,246,12,126,5,226,125,151,182,234,81,89,27,142,109,92,103,62,87,26,115,199,72,247,186,168,171,78,85,
140,58,148,235,99,210,253,213,155,23,148,78,11,187,114,237,146,84,210,58,70,232,83,9,129,137,9,19,99,231,82,121,206,251,65,77,41,182,34,207,243,162,35,154,238,198,46,250,139,108,153,229,97,91,223,145,
238,223,49,210,93,142,37,166,28,86,181,216,65,105,38,76,96,83,222,166,34,17,52,119,41,165,157,160,225,200,26,36,183,67,70,27,146,153,172,95,154,162,83,193,38,104,248,179,26,243,120,252,196,68,50,81,106,
45,118,60,169,63,86,192,232,47,215,179,223,212,156,111,130,116,127,245,242,89,85,46,59,193,247,217,14,233,94,230,101,85,44,251,179,1,168,40,10,183,127,251,109,73,141,252,232,133,12,251,206,108,62,71,40,
40,6,77,35,237,110,91,185,109,163,122,216,146,149,72,44,137,142,130,192,179,201,188,63,205,234,28,97,172,29,233,254,197,147,238,156,11,129,105,3,153,99,180,116,76,219,132,58,178,70,76,141,103,27,39,185,
99,128,36,142,129,175,117,29,34,252,131,90,236,74,62,199,200,154,16,252,146,167,211,62,56,151,181,234,137,2,228,201,121,210,125,179,115,190,46,233,30,182,223,201,116,20,126,152,145,73,210,93,46,23,97,
179,232,118,123,229,114,14,91,108,54,155,86,101,25,254,142,97,165,172,63,28,140,78,79,194,110,210,31,12,103,211,73,150,229,193,22,234,13,6,228,187,125,18,233,238,211,58,5,122,233,181,95,23,40,77,228,215,
152,96,32,147,135,33,3,245,122,84,160,75,67,113,108,203,184,24,198,227,220,101,77,42,157,170,233,30,118,110,250,143,54,78,220,145,238,95,54,233,78,236,141,70,253,152,203,74,46,212,98,223,30,50,38,123,
148,17,239,204,42,59,190,217,207,130,22,123,116,92,162,96,73,237,252,25,138,125,125,61,123,167,176,247,141,97,119,87,35,221,159,191,124,30,30,130,176,251,132,191,40,23,243,111,95,191,236,20,157,233,120,
68,18,139,157,78,112,121,248,203,14,46,78,61,58,125,223,235,246,139,94,119,50,30,5,227,162,40,58,239,223,29,135,143,239,17,241,52,128,110,47,72,247,201,225,9,218,106,197,67,44,92,28,137,51,233,102,200,
13,120,250,111,135,236,194,250,204,0,62,118,236,10,81,238,43,73,197,168,65,255,62,203,104,95,140,92,163,255,45,53,31,117,78,149,105,36,244,156,72,21,152,178,125,106,253,135,15,97,217,191,29,233,190,38,
89,110,238,58,233,14,167,27,20,187,227,184,173,241,230,230,144,49,254,44,81,136,81,28,102,99,159,37,181,208,6,103,21,42,183,163,14,61,247,224,170,113,154,95,165,18,32,146,238,41,30,219,91,74,186,135,159,
44,23,203,233,100,124,120,120,127,60,62,13,223,236,209,195,199,225,177,120,249,236,87,97,216,209,225,131,147,119,239,122,221,222,96,127,63,108,79,21,163,240,9,91,116,252,14,155,238,160,127,116,255,81,
212,116,23,210,157,181,177,37,208,12,224,209,122,96,19,130,186,219,134,116,119,76,106,115,222,34,5,189,70,82,135,44,66,4,237,211,148,222,127,250,221,170,174,21,97,176,16,122,79,121,35,67,227,104,129,0,
146,164,219,233,132,95,15,223,80,216,209,19,149,247,97,52,157,188,191,29,233,126,249,49,136,86,43,192,62,216,193,188,171,164,59,91,54,210,162,92,148,88,110,16,7,139,179,243,210,11,231,154,159,229,117,
140,212,165,229,124,82,10,21,200,39,35,250,33,240,254,252,41,235,188,66,186,251,91,76,186,15,134,123,123,251,251,111,94,191,26,141,79,120,7,241,243,233,4,66,210,40,104,160,173,77,122,23,7,75,187,14,127,
91,46,23,78,86,202,4,87,17,31,190,152,207,139,78,7,134,233,193,233,161,154,23,62,146,238,77,82,95,55,121,199,45,200,168,161,88,167,110,107,186,135,87,20,53,206,225,19,201,27,45,10,178,19,171,202,40,125,
32,137,72,164,255,77,211,220,22,46,125,89,150,44,183,150,113,127,55,222,149,194,62,101,171,124,153,35,74,189,35,221,207,141,97,245,48,200,140,136,142,184,84,137,162,61,204,29,37,221,99,188,217,51,130,
180,13,74,251,194,49,11,146,60,50,104,187,96,164,79,242,6,62,75,195,191,25,246,23,248,73,56,197,85,211,61,249,180,117,190,49,210,157,200,123,115,13,210,61,60,242,39,239,223,81,61,96,150,29,30,221,203,
130,233,88,46,79,222,29,7,87,176,161,210,85,149,226,232,222,131,209,201,251,215,175,94,134,143,185,255,224,161,133,47,98,60,26,201,188,126,249,236,241,147,175,139,78,247,202,164,123,77,45,90,225,42,98,
19,9,102,82,105,155,237,31,65,42,201,92,107,133,125,184,58,140,44,137,83,0,7,55,174,219,237,46,151,203,112,5,10,174,177,47,140,116,3,239,139,118,71,186,159,45,118,131,15,209,114,162,65,60,147,19,45,14,
41,110,203,221,53,210,221,227,160,133,236,250,138,246,57,158,91,254,155,106,19,90,236,231,199,224,168,67,37,190,71,209,216,69,52,252,154,159,229,77,212,9,230,26,35,167,86,27,223,23,125,95,12,254,108,164,
18,192,180,52,221,29,158,201,77,104,213,55,235,172,228,61,180,18,129,59,172,108,88,203,114,25,206,222,196,8,217,73,251,75,89,45,220,50,67,82,223,250,239,125,243,91,136,125,160,243,245,147,39,95,19,19,
108,51,236,112,193,90,121,242,245,55,225,102,194,7,236,239,31,236,239,31,178,48,67,5,87,229,7,191,253,175,248,197,167,229,123,242,245,247,57,237,136,112,143,129,66,3,182,240,148,99,194,152,50,156,32,238,
244,225,132,116,103,102,203,115,130,11,129,42,10,249,51,151,180,88,44,195,166,82,50,38,206,187,190,87,149,88,68,237,209,245,135,226,219,252,79,211,235,13,103,179,105,48,64,138,162,232,247,7,92,151,79,
149,213,165,169,56,138,159,112,131,76,126,100,217,117,114,84,187,159,115,152,67,224,128,176,92,206,33,163,148,160,19,112,123,197,16,201,2,250,20,246,250,224,61,133,165,8,159,82,155,154,3,222,244,13,135,
43,132,29,152,86,140,141,115,64,91,75,74,122,46,115,250,38,210,120,133,186,170,131,211,71,90,168,196,97,59,92,33,172,202,146,52,115,104,14,97,197,82,158,24,251,140,139,243,19,11,95,218,217,137,217,228,
211,142,110,24,224,220,54,173,202,248,36,160,66,182,166,163,48,45,17,90,188,17,169,84,83,145,26,90,183,221,152,217,130,49,37,149,104,149,87,184,142,246,148,163,2,123,126,50,163,239,83,243,65,117,107,209,
51,43,90,201,252,165,240,156,5,212,230,199,53,230,202,233,9,188,246,119,209,46,168,140,235,227,174,184,62,70,219,103,96,238,2,204,139,182,138,73,13,183,22,229,198,163,142,219,121,196,239,226,142,145,238,
97,215,40,187,139,188,204,51,39,114,101,89,94,76,39,144,105,39,18,4,242,30,154,118,49,26,171,78,155,172,66,85,22,69,126,112,112,48,159,207,195,95,117,186,157,34,43,246,143,238,25,213,1,169,243,240,141,
45,122,139,126,202,41,212,29,233,30,199,192,76,243,82,65,34,65,151,72,60,167,45,29,113,47,106,36,80,254,167,216,2,74,95,228,58,137,86,111,220,38,210,93,122,244,25,31,53,203,83,27,61,117,244,64,117,205,
47,222,50,244,12,207,34,206,161,72,177,203,171,39,13,30,132,80,247,254,218,235,108,90,122,246,210,222,34,133,191,217,170,4,248,48,198,133,116,185,210,66,236,13,228,120,104,161,139,15,30,76,153,56,249,
46,18,213,143,191,99,164,123,81,229,227,154,164,251,138,178,192,54,216,233,116,73,153,104,89,166,89,158,89,83,5,139,35,73,180,0,138,254,28,28,236,83,25,94,85,6,191,143,54,239,108,16,62,228,116,116,26,
142,154,240,229,6,155,101,176,183,39,81,25,126,171,22,221,69,216,224,139,170,227,140,219,145,238,237,163,210,232,215,39,121,79,111,84,230,169,57,30,219,58,226,171,228,52,180,198,133,27,142,133,108,183,
74,211,29,85,242,81,179,188,230,98,64,171,241,135,86,135,231,70,207,118,227,36,247,167,141,137,223,69,164,216,49,85,88,188,28,121,218,240,58,71,61,123,124,163,225,233,202,109,246,145,57,39,105,91,99,222,
199,57,19,138,40,37,155,162,47,166,9,247,248,252,56,45,204,188,123,154,238,225,199,179,98,154,207,10,130,119,249,164,14,14,221,116,50,14,151,57,61,61,13,195,126,248,195,31,254,248,199,63,254,197,63,253,
115,216,4,30,63,121,72,150,84,98,243,188,192,29,45,230,139,154,227,104,84,8,91,20,189,94,119,255,240,62,251,71,44,176,102,235,249,254,164,152,245,178,50,221,105,186,183,143,74,212,163,234,60,29,28,13,
37,167,65,60,123,171,18,139,81,107,92,50,226,188,11,171,228,116,10,173,22,124,150,87,186,90,166,234,165,176,206,38,246,179,144,238,32,185,249,16,141,250,232,14,65,0,61,122,229,180,7,213,182,113,146,251,
19,198,36,172,84,213,214,116,215,242,120,16,158,231,11,33,55,96,214,193,222,145,60,149,197,11,254,113,109,248,248,108,32,220,173,235,172,114,228,252,124,198,103,195,173,60,27,9,148,160,239,158,166,123,
90,165,203,193,156,226,40,92,235,199,139,192,238,116,185,152,78,22,71,247,238,253,236,167,63,251,187,191,251,251,231,207,159,61,122,244,112,185,92,44,151,75,4,200,40,77,27,124,192,162,19,54,217,60,207,
195,87,18,254,121,239,254,99,131,104,39,223,218,114,56,175,138,106,120,186,71,176,229,78,211,189,165,107,238,91,133,99,97,191,163,20,12,111,124,182,165,255,13,219,9,167,104,198,95,10,136,176,216,142,45,
230,236,19,205,240,106,255,93,72,204,26,181,8,124,236,62,121,195,154,238,145,228,182,82,52,47,15,42,60,0,45,78,118,72,49,39,80,109,219,40,201,125,213,49,252,93,80,118,69,215,48,6,194,77,123,13,155,128,
192,38,42,10,108,75,24,64,45,38,25,147,125,64,27,94,85,9,185,135,60,202,84,140,202,239,52,235,140,134,23,182,253,93,196,249,8,222,116,231,52,221,131,119,88,44,138,69,55,152,89,157,196,167,120,149,31,61,
120,250,252,217,111,130,185,244,179,159,254,241,235,215,175,255,234,175,254,242,240,240,8,32,2,25,83,108,176,80,155,73,242,149,8,97,72,88,93,229,240,232,65,211,175,59,24,140,73,189,236,45,242,121,97,40,
228,226,119,154,238,74,60,87,177,15,54,140,123,224,87,103,81,38,187,138,104,213,50,70,186,114,171,67,104,229,88,70,202,200,241,47,66,143,156,18,237,181,175,48,76,51,37,87,38,176,55,165,233,46,99,156,104,
186,3,243,59,163,233,174,213,20,159,13,61,163,200,17,67,61,112,119,240,0,148,144,226,226,251,170,221,182,42,10,216,4,35,19,59,118,168,194,1,91,182,181,225,229,101,7,248,98,163,46,171,70,93,121,206,193,
114,151,132,32,4,53,63,50,231,59,169,233,222,27,15,23,247,222,76,142,70,7,111,143,80,117,249,139,95,252,223,240,205,253,228,63,254,36,252,237,159,253,217,127,235,245,123,189,94,167,170,168,235,4,28,113,
52,143,164,212,27,75,62,230,157,130,118,43,35,17,107,156,3,167,7,239,130,31,183,63,30,154,196,238,52,221,65,60,131,5,51,13,164,33,197,76,87,209,8,23,201,179,156,118,94,209,26,151,32,35,189,15,84,78,197,
102,2,197,27,178,70,67,221,69,13,245,155,215,116,111,17,252,169,23,189,108,163,66,187,34,218,205,212,184,215,254,231,159,1,61,227,224,12,175,33,27,42,172,67,95,154,214,156,183,93,81,0,97,137,230,117,104,
190,83,168,217,165,16,176,139,218,240,146,138,193,119,202,30,67,158,229,85,69,193,138,245,231,124,39,53,221,195,237,29,142,238,159,30,188,31,237,159,14,78,134,85,89,143,39,163,111,190,249,230,71,63,250,
209,159,254,233,159,134,65,135,7,7,116,169,132,34,197,25,119,70,133,133,233,185,77,211,222,254,209,96,184,207,110,38,109,150,97,57,74,95,77,15,199,181,173,246,79,14,211,224,23,91,191,211,116,199,241,14,
190,20,199,153,87,88,183,200,174,128,59,165,50,102,69,107,156,185,54,90,148,74,90,10,227,56,132,192,134,211,19,88,20,122,241,43,120,67,110,64,211,189,53,198,158,167,225,141,118,48,113,209,114,212,220,
217,205,98,101,128,160,146,216,51,181,148,239,203,222,88,69,1,87,56,212,60,47,245,70,37,186,231,36,126,205,11,164,29,63,163,54,252,5,149,18,53,171,153,175,51,159,59,169,233,78,113,184,133,237,141,250,
211,33,245,37,156,252,203,168,42,171,63,250,195,63,252,155,191,249,159,191,252,213,191,124,239,155,239,223,187,247,32,92,122,54,157,76,167,99,73,241,80,139,137,110,167,232,102,89,65,173,88,57,218,199,
249,55,178,92,150,251,51,215,117,253,209,48,41,83,103,234,134,201,220,145,238,198,217,8,160,120,100,184,109,56,201,55,133,77,157,213,71,79,27,85,88,78,114,83,166,53,161,199,195,41,85,191,93,77,247,117,
198,32,30,91,137,238,123,221,32,57,55,164,107,142,143,2,72,201,153,104,238,234,250,25,43,10,180,48,23,240,71,45,84,125,85,71,93,252,85,109,120,206,201,179,170,242,234,117,214,34,239,239,158,166,59,36,
217,195,128,206,188,235,18,55,235,78,190,125,253,234,143,127,250,211,233,108,246,231,255,253,47,158,60,121,252,232,225,83,248,74,193,140,26,12,247,128,77,89,35,177,112,186,183,154,124,79,180,111,11,171,
22,204,180,58,47,59,227,126,49,235,112,186,33,81,38,126,71,186,87,160,162,163,230,109,173,61,69,55,69,123,175,234,145,219,198,217,53,214,71,74,219,183,41,237,219,165,251,222,166,189,153,23,217,10,13,191,
186,62,248,172,240,156,216,27,55,235,46,30,3,73,67,103,4,128,108,168,122,254,151,115,218,240,238,58,159,117,247,52,221,99,238,131,238,161,204,203,147,229,163,123,15,255,221,239,255,254,207,127,254,243,
162,211,121,240,232,169,111,104,175,76,115,20,22,129,161,68,34,69,194,34,5,31,112,122,52,118,69,213,31,237,13,23,123,150,247,47,239,125,196,41,118,154,238,208,62,143,15,144,145,166,9,219,214,26,23,13,
117,154,185,17,139,35,108,235,57,187,213,91,210,116,191,210,24,232,154,179,245,106,72,29,203,107,20,118,51,58,235,23,140,193,215,141,253,61,34,82,183,74,95,223,232,24,46,86,137,235,67,79,227,6,63,107,
213,37,100,251,92,168,107,86,67,15,219,164,139,46,153,181,2,206,179,254,60,239,169,228,118,114,94,143,94,3,26,44,90,22,9,204,32,4,122,89,194,66,82,42,200,24,167,166,201,41,33,29,26,110,17,130,173,70,34,
26,41,194,25,18,105,118,210,34,73,92,81,228,206,209,105,246,253,236,63,253,236,143,254,226,47,254,114,86,205,159,254,222,215,233,44,188,154,120,161,18,158,24,187,117,32,18,162,253,22,174,151,212,101,127,
49,239,205,194,196,247,222,31,166,85,198,34,54,38,85,164,128,205,64,13,15,112,8,201,41,114,130,251,165,51,54,207,224,173,51,80,222,90,49,31,87,44,137,43,134,194,160,246,138,25,62,165,227,138,121,237,235,
147,101,25,162,117,112,138,113,5,10,75,19,47,46,43,33,115,72,228,10,152,3,84,68,104,14,23,77,44,124,249,49,223,138,137,185,186,254,232,241,206,173,27,145,19,167,42,78,201,96,114,170,17,90,37,20,131,75,
11,102,255,12,139,80,83,191,41,60,50,217,245,198,208,70,192,143,145,76,128,152,184,42,158,121,235,152,36,103,136,66,191,233,98,64,70,204,128,179,89,78,218,2,246,94,250,107,223,251,133,99,242,164,48,137,
140,145,23,123,59,247,245,105,99,224,228,121,145,251,117,178,62,250,252,108,234,179,86,44,44,71,157,25,216,67,17,196,192,197,228,34,228,98,163,230,20,14,109,206,42,82,62,18,13,63,120,35,163,168,65,229,
106,245,134,164,70,64,48,98,193,255,81,31,231,219,73,1,176,57,210,82,55,97,218,94,43,55,120,210,40,24,242,77,14,81,29,248,63,248,131,127,63,30,79,254,250,127,252,245,163,127,251,100,209,155,151,131,165,
203,235,132,227,61,137,231,174,30,188,105,162,195,125,21,44,146,180,156,14,39,211,189,73,157,87,221,170,183,55,62,176,149,85,124,209,197,164,33,130,68,154,22,180,49,139,90,243,218,241,107,235,80,181,0,
48,199,107,45,164,202,242,159,93,177,114,185,236,246,122,4,121,242,173,157,89,49,156,156,146,100,4,103,17,155,247,182,214,28,87,142,107,46,88,60,191,153,149,94,214,181,38,38,41,57,157,88,170,109,167,48,
49,33,221,47,111,253,162,73,104,233,157,23,171,133,182,47,34,170,24,142,70,63,21,213,137,205,186,63,106,182,44,22,179,188,232,108,186,205,204,217,245,137,130,165,194,106,89,187,165,245,81,47,169,93,133,
183,173,251,250,132,49,23,206,199,111,250,179,238,30,233,78,33,115,222,48,216,104,73,38,211,233,63,253,195,63,60,124,248,52,155,231,249,188,19,44,166,178,91,45,187,139,101,127,62,235,79,233,95,58,139,
240,207,197,112,62,237,143,151,131,121,217,91,58,235,58,179,238,112,188,215,89,116,201,93,101,255,23,6,33,98,240,16,20,252,162,72,119,40,133,127,128,116,111,183,81,185,144,120,102,78,50,211,250,30,144,
238,9,108,138,155,32,185,109,155,228,78,237,54,73,247,171,143,73,16,221,101,26,222,71,146,27,216,228,166,180,216,43,70,225,34,17,158,37,31,249,190,190,96,157,126,251,39,127,242,39,141,133,149,246,189,
175,99,89,51,121,48,236,6,26,7,45,80,100,105,164,240,21,23,226,125,42,53,234,193,106,183,73,244,11,81,141,225,134,37,98,85,86,142,65,199,58,103,241,125,212,215,51,170,59,138,141,67,247,105,116,66,181,
162,32,170,212,156,52,155,48,202,211,106,147,162,42,47,93,240,12,51,27,254,25,188,63,58,179,28,133,166,131,229,149,184,52,47,139,70,103,75,235,178,117,14,112,101,29,44,184,198,184,210,202,44,223,186,163,
246,253,154,184,56,113,197,180,142,27,43,118,122,242,126,184,127,176,198,138,249,120,107,43,151,213,252,169,109,174,208,252,48,22,102,159,185,130,215,212,190,150,72,199,100,188,49,146,69,128,142,184,100,
164,37,76,213,0,53,82,170,238,180,150,34,158,248,100,105,74,63,59,131,221,179,17,174,100,63,60,163,198,197,43,56,207,167,141,33,227,145,199,88,145,49,70,148,215,199,249,124,104,206,225,127,158,190,123,
127,112,116,116,249,152,117,174,115,225,24,163,85,251,168,0,71,80,25,22,214,230,238,61,65,103,10,97,131,98,241,167,71,104,117,43,247,117,203,199,220,61,210,29,168,150,81,126,21,164,59,227,224,14,19,163,
28,217,34,179,73,145,148,48,164,37,119,214,178,212,41,150,228,165,33,24,110,13,64,185,0,112,177,48,232,110,145,238,136,184,59,31,131,160,218,55,142,118,38,97,43,188,50,51,41,107,39,73,91,23,214,53,111,
78,170,15,105,159,171,190,216,69,180,183,232,145,111,28,249,41,91,122,228,72,126,195,249,189,33,210,253,114,218,155,172,78,110,40,103,90,103,166,247,155,162,216,9,83,210,74,0,118,142,108,229,229,222,137,
183,252,226,52,248,215,25,115,39,73,119,126,100,9,1,67,210,155,21,251,189,2,229,168,230,147,116,32,12,37,126,75,19,8,98,40,183,17,203,68,27,210,61,106,186,163,177,197,221,34,221,109,211,107,3,143,127,
202,43,131,101,68,165,139,211,26,10,143,56,49,242,56,74,150,51,238,97,194,9,243,65,226,25,180,183,104,159,183,104,111,74,200,218,237,106,123,27,213,35,119,134,231,236,253,141,144,238,151,234,154,167,57,
54,121,169,4,48,18,113,52,155,165,216,45,165,216,241,89,254,42,68,248,151,58,230,172,75,24,182,33,38,221,61,240,232,84,163,125,148,86,103,145,3,208,231,32,221,89,243,175,180,138,251,161,222,213,210,233,
33,164,59,176,246,72,186,99,235,137,154,238,64,87,208,143,11,164,156,87,243,105,149,116,23,121,40,205,29,120,176,23,208,165,134,224,79,139,167,75,149,168,244,218,47,71,94,39,22,156,171,35,125,215,38,221,
145,167,19,5,121,209,157,18,93,39,68,145,34,21,34,137,15,6,202,179,4,186,148,180,247,179,237,147,226,126,35,233,222,94,177,241,233,201,222,193,129,172,152,34,233,237,21,243,200,167,112,184,29,91,26,19,
18,0,77,99,243,184,154,15,222,42,101,102,88,107,241,233,166,34,62,162,213,5,28,92,103,17,39,171,186,48,162,99,19,193,228,166,48,85,182,80,221,208,209,114,174,110,116,187,13,122,20,136,200,76,147,62,85,
141,51,152,190,78,52,165,28,4,127,129,131,146,17,13,155,140,35,131,181,151,55,118,253,49,85,141,16,30,171,23,219,184,125,175,204,7,91,251,153,57,143,78,78,247,15,143,46,31,179,206,117,46,188,119,58,194,
185,80,78,162,224,155,188,119,201,229,38,73,211,172,84,123,178,120,16,225,87,157,243,23,51,230,174,146,238,81,211,221,104,153,203,202,196,16,222,226,143,139,121,10,39,77,234,141,49,94,95,99,137,178,103,
124,191,81,211,253,206,144,238,226,194,91,3,197,210,156,69,83,233,53,168,149,23,151,80,61,246,115,88,215,44,20,89,199,186,98,45,150,79,34,89,46,171,126,169,166,251,42,237,173,2,143,162,174,145,109,150,
246,142,52,188,144,211,169,54,144,188,113,210,93,116,223,249,185,169,88,9,55,134,87,180,134,62,219,0,197,158,160,232,83,191,11,214,14,188,190,22,251,151,49,230,14,147,238,237,112,126,132,185,83,80,96,
188,139,52,54,86,184,3,47,85,87,180,19,185,134,116,87,10,79,130,209,119,137,116,103,17,72,11,113,68,169,110,171,197,97,60,143,180,88,219,38,203,117,204,197,100,57,246,202,112,242,87,23,147,229,238,60,
237,45,26,141,88,46,210,186,168,55,78,195,55,228,244,103,32,221,189,82,79,62,146,247,141,238,187,149,29,158,104,228,235,161,76,81,139,61,124,177,171,20,123,126,235,117,241,111,104,204,85,52,221,91,10,
229,139,229,146,117,15,50,214,116,79,163,166,123,84,40,135,87,34,154,238,78,60,160,240,223,52,35,59,129,123,203,87,137,232,139,95,65,211,221,37,40,134,176,181,10,114,165,236,85,1,245,14,19,99,141,243,
20,184,80,170,138,171,193,78,15,255,1,162,237,180,9,82,197,48,65,198,249,1,90,142,68,52,221,161,109,200,235,117,123,53,221,17,10,228,112,126,77,118,4,66,81,230,170,98,146,77,210,144,252,74,139,210,5,49,
151,42,247,17,45,246,182,182,119,163,233,206,155,234,134,197,45,19,164,150,107,68,112,182,168,233,126,233,24,134,1,83,232,131,113,88,16,90,166,98,254,68,118,228,211,180,216,141,145,226,187,150,22,59,243,
54,82,252,80,110,179,56,241,46,141,185,99,154,238,209,183,140,191,219,192,15,122,1,43,178,232,137,28,127,18,26,139,243,22,95,169,37,113,222,150,78,151,215,14,130,121,183,82,211,157,148,23,154,92,129,151,
224,96,125,109,236,5,52,169,244,28,87,228,194,171,16,243,135,180,189,97,110,36,18,188,75,128,203,162,182,97,35,24,142,87,252,88,58,185,35,87,187,105,77,247,181,244,236,25,157,83,78,74,59,167,167,215,66,
162,68,215,220,120,100,213,219,90,236,45,205,123,191,37,205,251,187,56,230,110,147,238,120,175,225,50,180,113,240,24,56,95,37,221,109,116,103,140,181,177,111,2,179,23,119,134,116,103,154,193,53,219,180,
180,178,217,18,89,110,214,33,203,225,219,174,210,222,27,19,183,196,152,68,10,24,109,99,28,222,16,233,174,188,2,136,226,102,125,34,125,110,174,115,95,86,206,75,27,29,247,152,17,190,85,20,251,237,25,115,
183,73,119,212,137,167,50,91,221,245,164,118,218,106,110,5,186,171,41,108,120,43,13,118,125,138,22,47,12,49,221,126,210,93,152,16,214,75,144,238,18,94,60,143,141,147,229,104,23,86,169,174,57,34,137,107,
209,222,73,212,62,23,74,123,35,180,55,81,100,158,73,119,123,53,29,250,235,147,238,8,93,181,238,43,65,226,152,243,197,87,190,47,68,42,207,107,177,107,193,191,87,213,233,239,40,197,190,206,152,109,107,186,
139,52,170,178,171,226,218,112,140,9,249,68,104,186,167,49,89,229,69,58,189,185,66,163,233,46,24,188,61,51,49,142,114,164,43,194,231,114,36,166,234,113,218,216,19,193,42,249,169,56,120,84,164,78,80,194,
141,172,168,21,130,28,89,25,92,54,178,78,246,230,53,221,163,69,137,157,177,209,194,219,130,142,56,171,212,10,78,209,214,8,191,196,148,72,90,186,239,48,110,51,174,13,250,212,249,52,29,204,194,145,128,238,
3,209,232,219,170,166,251,133,247,229,132,69,128,102,57,84,110,220,85,239,75,30,53,19,239,11,233,26,207,197,70,205,125,93,211,100,251,226,199,108,157,116,95,193,193,63,192,109,3,7,231,43,208,232,36,249,
144,66,185,76,204,51,189,69,111,190,55,72,114,243,196,200,95,251,208,196,90,64,121,154,52,151,253,8,80,222,154,216,21,164,211,55,78,186,59,152,202,44,100,149,64,184,145,206,156,237,234,136,11,52,215,144,
229,230,114,10,25,53,64,113,15,45,93,201,182,238,39,10,96,122,85,249,129,97,37,250,223,172,195,115,51,154,238,162,89,14,108,45,177,113,62,23,234,217,95,114,95,86,197,83,129,205,121,205,2,74,225,4,147,
113,100,85,93,229,190,190,203,99,182,75,186,43,183,157,186,166,216,5,212,245,10,183,221,228,203,89,92,37,42,148,71,160,92,112,112,157,24,148,94,210,85,160,252,3,19,59,15,148,155,51,64,121,83,87,113,217,
196,86,164,211,111,146,116,247,154,214,100,245,155,84,244,58,182,143,189,64,147,219,147,10,85,22,211,38,31,37,149,197,87,117,168,1,114,124,208,165,90,18,153,124,84,184,146,217,145,164,209,125,215,134,
241,81,179,252,38,53,221,141,164,77,65,191,125,10,197,46,45,163,36,179,156,196,110,172,81,215,156,210,211,87,191,175,29,233,190,69,210,93,10,104,140,47,201,252,113,45,28,60,137,220,118,164,204,87,46,219,
224,224,10,148,51,146,126,149,137,33,106,246,145,137,53,64,121,34,237,115,62,52,177,48,165,182,116,250,141,145,238,178,3,2,253,103,20,139,173,185,79,161,198,215,31,163,181,129,86,227,157,201,122,164,178,
208,222,208,246,22,1,28,68,38,168,19,145,115,218,139,248,204,103,233,24,227,149,152,71,109,182,213,174,95,112,234,175,68,69,127,50,233,30,81,97,209,201,68,229,215,21,41,118,105,115,43,137,109,127,190,
162,224,59,69,168,111,106,204,255,23,96,0,75,84,73,27,147,219,168,61,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* JuceDemoPluginAudioProcessorEditor::uibg_png = (const char*) resource_JuceDemoPluginAudioProcessorEditor_uibg_png;
const int JuceDemoPluginAudioProcessorEditor::uibg_pngSize = 65211;

// JUCER_RESOURCE: on_orange_png, 492, "../on_orange.png"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_on_orange_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,19,0,0,0,15,8,6,0,0,0,6,68,244,44,0,0,0,4,103,65,77,65,0,
0,175,200,55,5,138,233,0,0,0,25,116,69,88,116,83,111,102,116,119,97,114,101,0,65,100,111,98,101,32,73,109,97,103,101,82,101,97,100,121,113,201,101,60,0,0,1,126,73,68,65,84,120,218,156,84,65,82,194,48,
20,77,67,218,10,50,234,200,66,199,5,7,241,18,94,192,149,247,114,231,13,60,136,119,96,197,40,160,204,84,74,155,148,248,95,121,31,51,236,32,51,143,223,38,253,47,47,255,253,144,197,23,131,145,9,6,2,155,68,
197,241,216,37,232,14,241,53,198,76,200,64,228,4,133,160,20,140,248,92,112,222,30,17,5,65,75,108,4,13,159,131,163,18,36,94,10,174,5,183,140,32,189,224,186,14,40,217,146,100,45,88,49,98,68,221,185,36,193,
189,96,202,56,17,140,185,145,14,40,168,4,75,193,92,48,227,60,212,122,85,54,162,162,233,187,201,222,60,39,176,139,79,164,111,19,230,95,193,147,137,207,220,160,6,84,89,161,202,80,128,7,193,99,158,239,109,
113,206,248,77,109,242,220,153,202,7,145,26,205,135,44,12,247,156,56,193,23,97,109,66,6,49,19,252,92,225,179,161,124,30,65,150,247,103,0,51,54,2,121,205,170,179,20,106,152,117,108,11,171,142,162,226,224,
48,117,45,74,124,95,52,20,232,78,158,81,237,44,116,61,11,93,73,29,207,28,115,15,150,175,248,50,150,100,212,229,70,226,140,54,126,11,126,72,158,255,27,18,152,210,187,185,75,122,102,25,184,186,96,161,45,
19,23,84,179,225,59,155,111,201,41,228,239,82,178,53,237,238,235,241,73,178,1,207,81,177,79,90,170,44,247,203,115,230,245,100,184,1,5,191,155,156,217,103,115,190,87,170,172,73,58,185,165,213,167,220,128,
70,143,217,145,64,59,185,38,217,169,119,179,83,55,3,163,39,217,89,255,26,127,2,12,0,74,21,165,77,47,125,194,188,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* JuceDemoPluginAudioProcessorEditor::on_orange_png = (const char*) resource_JuceDemoPluginAudioProcessorEditor_on_orange_png;
const int JuceDemoPluginAudioProcessorEditor::on_orange_pngSize = 492;

// JUCER_RESOURCE: on_red_png, 134, "../on_red.png"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_on_red_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,11,0,0,0,7,8,2,0,0,0,81,12,32,10,0,0,0,4,103,65,77,65,0,0,175,
200,55,5,138,233,0,0,0,25,116,69,88,116,83,111,102,116,119,97,114,101,0,65,100,111,98,101,32,73,109,97,103,101,82,101,97,100,121,113,201,101,60,0,0,0,24,73,68,65,84,120,218,98,252,31,20,196,128,23,48,
49,16,2,67,71,5,64,128,1,0,138,112,1,177,213,229,246,172,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* JuceDemoPluginAudioProcessorEditor::on_red_png = (const char*) resource_JuceDemoPluginAudioProcessorEditor_on_red_png;
const int JuceDemoPluginAudioProcessorEditor::on_red_pngSize = 134;

// JUCER_RESOURCE: on_yellow_png, 133, "../on_yellow.png"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_on_yellow_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,11,0,0,0,7,8,2,0,0,0,81,12,32,10,0,0,0,4,103,65,77,65,0,0,
175,200,55,5,138,233,0,0,0,25,116,69,88,116,83,111,102,116,119,97,114,101,0,65,100,111,98,101,32,73,109,97,103,101,82,101,97,100,121,113,201,101,60,0,0,0,23,73,68,65,84,120,218,98,250,255,159,1,63,98,
98,32,4,134,142,10,128,0,3,0,255,99,21,249,69,111,163,218,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* JuceDemoPluginAudioProcessorEditor::on_yellow_png = (const char*) resource_JuceDemoPluginAudioProcessorEditor_on_yellow_png;
const int JuceDemoPluginAudioProcessorEditor::on_yellow_pngSize = 133;

// JUCER_RESOURCE: off_png, 133, "../off.png"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_off_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,11,0,0,0,7,8,2,0,0,0,81,12,32,10,0,0,0,4,103,65,77,65,0,0,175,200,
55,5,138,233,0,0,0,25,116,69,88,116,83,111,102,116,119,97,114,101,0,65,100,111,98,101,32,73,109,97,103,101,82,101,97,100,121,113,201,101,60,0,0,0,23,73,68,65,84,120,218,98,12,9,9,97,192,11,152,24,8,129,
161,163,2,32,192,0,239,192,1,10,42,195,246,197,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* JuceDemoPluginAudioProcessorEditor::off_png = (const char*) resource_JuceDemoPluginAudioProcessorEditor_off_png;
const int JuceDemoPluginAudioProcessorEditor::off_pngSize = 133;

// JUCER_RESOURCE: dry_on_png, 776, "../dry_on.png"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_dry_on_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,35,0,0,0,13,8,2,0,0,0,172,29,64,72,0,0,0,4,103,65,77,65,0,0,
175,200,55,5,138,233,0,0,0,25,116,69,88,116,83,111,102,116,119,97,114,101,0,65,100,111,98,101,32,73,109,97,103,101,82,101,97,100,121,113,201,101,60,0,0,2,154,73,68,65,84,120,218,156,84,75,79,83,65,20,
158,59,143,219,22,5,84,192,66,165,36,37,80,42,137,46,52,18,197,104,66,92,184,240,231,152,184,113,229,198,31,230,70,99,92,184,242,1,2,229,85,16,5,83,176,189,241,206,203,239,204,136,24,37,148,120,114,219,
204,156,57,143,111,206,249,206,36,79,158,62,99,140,37,44,209,86,27,99,132,16,216,74,33,56,231,14,226,93,42,10,214,219,19,109,60,132,209,143,39,73,194,57,12,176,101,30,27,134,207,135,141,119,14,198,88,
72,10,65,90,15,127,56,64,117,208,110,91,99,134,70,46,7,239,196,56,123,228,121,108,19,51,224,92,192,192,26,41,40,14,112,132,172,220,90,7,92,144,223,8,8,56,48,18,78,107,144,28,90,248,172,44,125,120,251,
230,149,128,131,51,214,90,160,250,215,6,137,241,239,233,210,62,149,41,142,144,6,26,124,60,8,93,215,57,75,69,129,88,66,3,173,117,22,8,129,28,69,113,216,39,60,2,164,88,158,69,249,203,6,209,181,209,200,138,
163,231,173,38,59,85,30,143,84,80,17,160,3,70,218,103,221,238,214,231,109,169,20,96,132,139,243,149,79,139,74,41,22,10,97,116,222,63,56,120,105,104,36,203,178,221,157,86,161,88,44,143,86,128,151,122,113,
6,209,218,72,201,5,75,120,167,115,248,250,229,11,168,74,165,190,195,131,54,245,208,251,229,197,247,88,12,12,94,168,86,107,107,155,235,102,53,159,191,255,160,185,188,216,218,92,191,126,115,14,117,163,254,
197,134,156,42,177,187,60,6,221,217,110,25,173,103,102,175,221,186,115,15,161,161,116,161,112,165,190,115,183,239,46,140,79,212,234,51,179,90,235,165,143,239,144,166,50,62,81,46,143,225,20,53,76,85,161,
103,166,95,221,69,63,168,189,84,37,214,254,182,175,164,234,118,59,88,43,73,116,42,22,75,185,206,209,187,225,242,40,74,135,52,80,78,213,103,209,229,130,34,34,16,41,123,9,120,129,254,16,35,80,235,202,149,
106,214,249,190,182,186,188,247,117,23,189,193,253,192,186,48,0,137,8,76,131,205,197,161,225,253,189,47,83,245,171,170,144,82,231,172,65,71,21,87,61,51,97,242,16,72,34,34,77,26,75,106,211,141,201,122,
67,9,48,194,199,137,91,120,248,136,134,49,112,25,54,173,141,53,92,125,108,188,138,1,32,155,132,233,220,16,39,206,32,136,33,227,192,35,34,200,15,134,68,79,210,10,113,244,70,164,120,35,182,54,154,89,214,
157,156,110,120,150,252,208,121,180,73,149,2,38,144,184,199,27,17,160,159,240,70,196,249,15,212,58,126,35,64,147,27,115,243,40,96,100,246,127,188,17,18,184,67,241,8,135,148,10,39,218,228,240,196,109,114,
173,227,117,209,203,243,253,3,167,216,228,78,243,56,242,156,108,192,166,63,109,44,137,249,41,192,0,196,103,204,212,168,112,5,244,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* JuceDemoPluginAudioProcessorEditor::dry_on_png = (const char*) resource_JuceDemoPluginAudioProcessorEditor_dry_on_png;
const int JuceDemoPluginAudioProcessorEditor::dry_on_pngSize = 776;

// JUCER_RESOURCE: dry_off_png, 775, "../dry_off.png"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_dry_off_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,35,0,0,0,13,8,2,0,0,0,172,29,64,72,0,0,0,4,103,65,77,65,0,0,
175,200,55,5,138,233,0,0,0,25,116,69,88,116,83,111,102,116,119,97,114,101,0,65,100,111,98,101,32,73,109,97,103,101,82,101,97,100,121,113,201,101,60,0,0,2,153,73,68,65,84,120,218,156,84,75,79,83,65,20,
158,59,143,219,22,133,170,128,133,74,73,74,74,121,36,186,208,72,20,163,9,113,225,194,255,227,198,149,127,205,141,198,176,208,141,104,43,111,40,136,130,41,216,222,120,231,229,119,238,136,24,37,45,241,228,
182,153,57,115,30,223,156,243,157,145,207,158,191,96,140,69,44,210,86,27,99,132,16,216,74,33,56,231,14,226,93,44,114,214,219,115,109,60,132,209,143,71,81,196,57,12,176,101,30,27,134,207,103,27,239,28,
140,177,144,20,130,180,30,254,112,128,234,184,221,182,198,12,143,94,207,188,35,227,236,169,231,153,77,200,128,115,1,3,107,164,160,56,192,145,101,229,214,58,224,130,252,70,64,192,129,145,112,90,131,228,
208,194,103,173,249,225,237,242,107,1,7,103,172,181,64,245,175,13,18,227,223,211,165,125,44,99,28,33,13,52,248,120,38,116,93,231,44,21,5,98,9,13,180,214,89,32,4,114,20,197,97,31,241,0,144,98,121,22,228,
47,27,68,215,70,35,43,142,154,43,239,88,79,153,172,205,161,34,64,7,140,180,79,186,221,221,207,123,82,41,192,200,46,206,215,62,53,148,82,44,43,132,209,233,96,177,120,109,120,52,73,146,131,253,86,46,159,
47,141,149,129,151,122,113,1,209,218,72,201,5,139,120,167,115,242,230,213,75,168,10,133,129,147,227,54,245,208,251,213,198,10,22,67,197,43,149,74,117,115,103,203,172,167,139,143,30,111,172,54,90,59,91,
183,238,44,160,110,212,191,208,144,158,18,186,203,67,208,253,189,150,209,122,102,254,230,221,251,15,17,26,74,151,21,174,48,112,233,222,131,165,137,201,106,125,102,94,107,221,252,248,30,105,202,19,147,
165,210,56,78,81,195,88,229,250,102,250,213,93,244,131,218,75,85,98,237,111,71,74,170,110,183,131,181,146,68,167,124,190,144,234,20,189,27,41,141,161,116,72,3,101,173,62,143,46,231,20,17,129,72,217,79,
192,11,244,135,24,129,90,151,111,84,146,206,247,205,245,213,195,175,7,232,13,238,7,214,101,3,16,137,140,105,176,185,58,60,114,116,248,165,86,159,83,185,152,58,103,13,58,170,184,234,155,9,147,135,64,18,
17,105,210,88,84,157,158,157,170,207,42,1,70,248,48,113,75,79,158,210,48,102,92,134,77,107,123,19,87,31,159,168,96,0,200,38,98,58,53,196,137,11,8,98,200,48,240,136,8,242,131,33,193,147,180,66,156,190,
17,49,222,136,221,237,141,36,233,78,77,207,122,22,253,208,105,176,137,149,2,38,144,184,247,27,17,158,146,115,222,136,48,255,25,181,206,222,8,208,228,246,194,34,10,24,152,253,31,111,132,4,238,172,120,132,
67,74,133,19,109,82,120,226,54,169,214,225,186,232,229,229,193,161,30,54,169,211,60,140,60,39,27,176,233,79,27,75,98,126,10,48,0,126,191,205,159,48,249,28,219,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* JuceDemoPluginAudioProcessorEditor::dry_off_png = (const char*) resource_JuceDemoPluginAudioProcessorEditor_dry_off_png;
const int JuceDemoPluginAudioProcessorEditor::dry_off_pngSize = 775;

// JUCER_RESOURCE: wet_off_png, 705, "../Graphics/wet_off.png"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_wet_off_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,22,0,0,0,23,8,2,0,0,0,128,138,40,201,0,0,0,4,103,65,77,65,0,
0,175,200,55,5,138,233,0,0,0,25,116,69,88,116,83,111,102,116,119,97,114,101,0,65,100,111,98,101,32,73,109,97,103,101,82,101,97,100,121,113,201,101,60,0,0,2,83,73,68,65,84,120,218,212,84,93,111,18,65,20,
157,175,133,22,40,116,97,145,32,150,64,144,90,37,209,63,96,98,226,79,50,38,198,7,227,143,243,65,141,77,181,86,81,75,211,134,104,233,135,84,20,171,208,157,153,29,207,204,146,70,141,89,124,212,251,112,119,
25,206,220,123,238,57,23,232,221,251,15,117,164,137,49,132,82,206,24,101,76,48,46,149,52,196,8,46,112,140,136,162,40,1,35,40,101,130,147,89,80,138,20,170,144,18,10,160,214,218,157,241,100,140,64,61,188,
71,6,157,108,66,97,36,192,24,192,104,232,112,200,9,24,100,16,52,145,113,65,12,176,41,207,179,228,141,97,232,238,122,254,140,25,143,63,111,174,63,61,62,216,63,199,8,169,229,199,163,193,100,50,169,173,52,
22,210,233,189,221,222,178,95,244,253,210,193,224,195,233,233,184,90,171,43,165,134,199,135,168,84,12,202,249,130,63,30,141,62,157,12,209,62,155,205,249,165,32,148,146,223,188,117,251,44,156,118,95,62,
23,66,40,45,95,111,110,160,124,190,176,188,241,236,49,232,6,229,202,250,147,71,50,60,211,81,180,253,230,85,38,155,3,139,175,227,47,152,12,239,185,165,188,101,1,61,124,63,40,150,202,253,189,157,165,124,
97,49,147,221,127,223,71,86,82,214,155,173,163,195,1,94,192,31,25,165,241,177,182,82,7,0,148,107,245,70,172,11,227,28,54,177,102,107,21,160,209,201,176,125,181,179,176,152,217,121,215,173,84,47,150,130,
11,194,19,184,89,169,214,112,161,125,165,3,230,74,105,103,179,245,216,222,133,89,177,77,248,14,68,38,223,191,149,130,50,154,111,119,183,90,171,215,160,230,165,122,115,58,153,246,119,123,82,74,76,183,214,
185,30,134,97,236,109,44,176,85,252,206,189,7,196,169,142,169,172,67,148,42,173,60,110,77,129,210,48,9,125,224,101,2,70,224,36,222,60,141,29,2,67,198,82,34,245,219,118,34,18,48,255,198,118,138,222,219,
23,36,49,46,175,221,248,211,6,11,169,20,78,60,236,5,153,23,161,12,157,130,118,4,198,236,10,224,41,85,152,246,82,160,132,237,156,95,130,115,232,69,208,220,141,96,31,86,14,103,10,56,241,248,103,150,28,184,
3,205,140,189,78,35,59,78,196,103,234,88,93,173,41,115,75,192,127,109,156,53,40,161,35,41,149,99,67,4,183,1,129,231,151,80,145,118,196,173,162,110,163,169,29,202,144,243,237,20,127,55,200,47,219,201,157,
16,88,170,217,118,54,218,157,185,255,157,255,195,118,254,16,96,0,137,38,247,94,11,40,196,1,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* JuceDemoPluginAudioProcessorEditor::wet_off_png = (const char*) resource_JuceDemoPluginAudioProcessorEditor_wet_off_png;
const int JuceDemoPluginAudioProcessorEditor::wet_off_pngSize = 705;

// JUCER_RESOURCE: wet_on_png, 712, "../Graphics/wet_on.png"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_wet_on_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,22,0,0,0,23,8,2,0,0,0,128,138,40,201,0,0,0,4,103,65,77,65,0,
0,175,200,55,5,138,233,0,0,0,25,116,69,88,116,83,111,102,116,119,97,114,101,0,65,100,111,98,101,32,73,109,97,103,101,82,101,97,100,121,113,201,101,60,0,0,2,90,73,68,65,84,120,218,204,84,91,111,18,65,24,
221,185,176,20,208,93,150,139,21,183,208,18,210,122,193,232,131,255,204,104,76,77,26,31,252,107,190,52,177,73,141,13,141,148,180,33,90,122,145,138,65,112,155,157,153,29,207,204,18,162,38,130,143,253,30,
190,189,157,239,178,231,156,93,242,98,251,141,74,148,163,181,67,8,163,148,80,202,41,19,82,104,71,115,198,113,27,145,36,201,2,12,39,132,114,230,204,130,16,164,88,198,196,33,0,42,165,236,61,182,24,195,209,
15,231,137,198,36,147,208,24,9,48,10,48,6,90,28,242,2,12,50,22,212,137,182,225,104,96,221,76,198,44,175,53,197,116,59,243,119,204,120,252,253,195,251,221,203,179,211,57,134,11,37,190,94,12,162,40,10,235,
27,43,217,236,201,241,81,49,40,5,65,249,108,240,101,50,25,215,194,134,148,114,120,121,142,78,165,74,213,243,131,241,104,244,237,106,136,241,133,194,173,160,92,137,133,224,88,132,187,110,111,127,15,19,
60,223,239,30,30,132,245,245,92,46,223,57,216,247,60,255,110,109,109,111,247,93,62,95,88,201,229,123,221,195,199,79,159,77,167,19,204,143,162,233,100,242,195,43,6,96,151,131,143,32,168,148,202,213,254,
73,239,182,231,231,242,133,211,207,125,100,41,68,163,217,186,56,31,224,4,221,145,81,137,203,176,222,0,0,43,135,141,141,148,23,202,24,26,209,102,107,11,160,209,213,112,243,97,219,12,252,212,89,173,221,
43,87,238,240,12,71,229,106,45,68,193,230,253,54,54,151,82,89,153,141,198,166,22,98,165,50,225,25,22,137,126,78,203,149,42,134,119,59,31,91,91,143,192,230,90,163,121,29,93,247,143,143,132,16,158,95,124,
208,126,18,199,113,170,109,74,176,97,252,249,171,29,199,178,14,110,141,66,132,72,37,51,204,136,2,166,33,18,230,64,203,5,24,67,103,234,60,5,15,97,67,74,93,238,254,229,78,196,2,204,205,112,39,153,175,250,
175,216,222,121,139,6,218,73,148,158,213,227,18,90,8,41,241,52,195,57,119,150,69,44,98,203,160,121,5,74,141,5,112,20,50,206,102,92,180,52,238,92,218,130,49,240,229,96,184,93,193,28,12,29,86,20,232,202,
210,207,108,113,160,6,156,105,83,78,18,227,133,132,205,216,49,188,26,81,150,182,128,254,74,91,105,208,66,37,66,72,187,141,195,153,9,16,188,188,133,76,148,93,220,124,239,214,209,196,188,148,118,230,238,
228,255,247,34,127,184,147,89,34,96,170,153,59,95,190,94,242,239,76,233,186,241,238,252,37,192,0,68,64,236,198,105,57,227,219,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* JuceDemoPluginAudioProcessorEditor::wet_on_png = (const char*) resource_JuceDemoPluginAudioProcessorEditor_wet_on_png;
const int JuceDemoPluginAudioProcessorEditor::wet_on_pngSize = 712;


//[EndFile] You can add extra defines here...
//[/EndFile]
