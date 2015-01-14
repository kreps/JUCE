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
    gainSlider = nullptr;
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
    gainSlider->setBounds (41, 8, 70, 50);
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
    wetOnBtn->setBounds (7, 27, 35, 13);
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
    else if (sliderThatWasMoved == gainSlider)
    {
        //[UserSliderCode_gainSlider] -- add your slider handling code here..
		// It's vital to use setParameterNotifyingHost to change any parameters that are automatable
		// by the host, rather than just modifying them directly, otherwise the host won't know
		// that they've changed.
		getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::gainParam,                                                  (float)gainSlider->getValue());
        //[/UserSliderCode_gainSlider]
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
  <SLIDER name="gainSlider" id="c31acc4ca22491a9" memberName="gainSlider"
          virtualName="" explicitFocusOrder="0" pos="41 8 70 50" tooltip="gain"
          textboxbkgd="ffffff" textboxhighlight="881111ee" textboxoutline="0"
          min="0" max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.29999999999999999"/>
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
               virtualName="" explicitFocusOrder="0" pos="7 27 35 13" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="wet_off_png" opacityNormal="1" colourNormal="0"
               resourceOver="" opacityOver="1" colourOver="0" resourceDown="wet_on_png"
               opacityDown="1" colourDown="0"/>
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

// JUCER_RESOURCE: uibg_png, 65015, "../uibg.png"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_uibg_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,1,144,0,0,0,230,8,2,0,0,0,116,209,68,243,0,0,0,4,103,65,77,65,0,
0,175,200,55,5,138,233,0,0,0,25,116,69,88,116,83,111,102,116,119,97,114,101,0,65,100,111,98,101,32,73,109,97,103,101,82,101,97,100,121,113,201,101,60,0,0,253,137,73,68,65,84,120,218,236,189,89,147,100,
201,117,30,232,238,119,143,61,50,179,42,107,109,244,130,110,0,36,64,64,34,134,216,27,13,104,72,2,154,17,36,2,54,54,63,100,158,230,97,126,206,60,208,70,38,145,99,132,108,100,163,39,138,20,8,128,176,17,
183,70,163,55,244,82,107,86,110,177,222,184,155,251,156,197,221,35,50,43,43,43,215,170,6,140,9,90,51,43,242,132,223,123,253,186,31,63,203,119,190,35,255,229,255,249,59,127,248,247,255,70,92,220,143,14,
51,37,101,221,212,81,16,193,63,171,166,50,70,40,169,180,214,66,162,0,252,85,42,117,30,25,169,64,74,6,65,80,213,53,252,41,10,67,137,95,147,240,95,35,116,99,180,209,218,8,115,33,50,240,57,220,73,168,64,
166,2,249,48,8,225,54,240,49,181,110,116,35,224,31,82,6,112,167,79,147,153,79,39,107,107,27,231,28,228,36,50,240,207,88,84,103,121,115,10,231,217,224,255,112,84,122,15,18,126,149,52,38,126,38,113,254,
159,141,76,35,3,120,29,246,47,40,99,236,15,189,50,88,26,117,211,240,43,243,50,240,221,67,175,117,103,103,187,215,31,92,234,242,56,129,12,60,159,225,229,220,52,13,62,172,105,52,190,40,250,129,23,10,143,
35,21,125,139,70,164,49,225,113,52,62,145,128,149,142,127,20,248,11,191,37,24,150,166,3,133,236,56,42,128,133,129,123,71,224,10,49,52,97,71,45,27,5,203,6,254,136,50,118,8,20,196,33,113,18,121,238,241,
203,244,54,236,63,232,143,238,202,159,128,159,240,15,127,249,191,214,234,34,149,139,105,106,173,84,28,198,135,54,21,252,240,12,54,48,131,176,199,206,33,131,203,66,194,236,151,73,20,195,59,46,171,138,103,
156,238,2,231,90,209,43,188,16,25,126,99,101,93,242,194,106,104,159,192,221,193,31,195,192,205,34,189,221,167,200,92,200,32,39,187,144,104,206,162,176,112,230,241,109,226,156,176,142,8,164,50,210,78,58,
239,1,254,231,229,200,4,70,106,47,3,207,201,175,3,183,154,82,188,141,2,21,242,123,209,77,19,6,1,60,254,1,25,216,123,7,95,107,28,134,176,84,46,117,121,156,64,70,5,120,192,194,238,168,224,119,144,1,45,20,
129,130,3,229,101,68,100,85,149,100,221,160,133,85,36,176,165,162,32,132,13,5,51,18,178,198,178,26,3,53,144,85,220,18,117,16,234,68,154,82,28,71,194,75,100,5,164,142,90,54,21,223,17,238,92,210,116,244,
13,229,53,17,47,117,167,183,236,55,237,135,244,7,58,107,236,231,7,245,151,255,221,127,46,31,91,95,143,203,136,21,201,147,106,195,16,30,247,98,149,139,196,229,117,185,155,19,94,36,157,97,168,34,225,109,
209,162,145,244,146,248,108,162,67,141,150,239,249,101,236,74,210,124,220,137,3,71,162,84,246,72,164,83,241,120,25,205,251,244,124,131,156,68,230,204,103,151,164,199,102,213,192,171,150,15,121,251,87,
5,26,69,153,229,182,57,143,12,29,3,198,174,83,146,145,184,147,151,50,248,68,129,228,109,130,47,133,199,131,245,70,102,9,90,53,108,82,29,146,57,244,90,27,250,185,212,229,113,140,140,102,11,29,68,213,242,
165,132,160,100,164,132,83,255,201,10,46,12,200,4,32,133,27,107,161,43,39,35,173,8,169,103,84,98,178,214,240,116,1,92,23,236,77,201,179,128,127,80,79,89,54,52,144,53,217,208,216,178,102,160,176,170,144,
213,147,87,83,210,153,189,154,126,97,17,210,143,171,74,199,171,29,158,29,177,50,204,227,50,7,148,20,75,202,199,180,155,60,82,139,133,23,174,92,46,106,227,29,35,83,130,41,167,34,205,7,177,49,110,245,179,
70,112,171,95,152,139,145,161,123,138,163,16,108,126,144,140,248,96,242,198,194,138,159,114,188,12,252,59,142,162,115,14,114,18,153,51,43,44,180,154,97,33,146,179,166,13,31,194,194,41,109,97,183,19,204,
201,249,100,120,7,28,148,105,72,70,121,109,139,143,165,236,230,176,91,132,182,20,235,9,54,123,165,51,6,86,100,204,161,215,202,203,242,114,151,199,177,50,184,29,208,46,49,168,165,121,85,131,67,136,95,85,
199,42,65,137,211,3,50,224,83,26,131,38,26,254,149,212,140,125,76,208,221,130,70,22,28,181,0,67,18,54,166,70,147,237,152,101,3,126,107,99,47,106,101,36,78,191,51,163,120,147,105,186,128,114,190,185,113,
62,34,126,102,29,122,167,95,228,33,159,81,242,72,43,46,165,60,32,227,85,147,17,7,172,176,35,84,147,124,146,153,22,162,171,123,161,202,229,162,118,248,49,50,85,85,243,6,0,191,0,126,248,14,226,32,110,76,
195,147,4,207,116,81,50,112,202,93,136,239,16,6,49,12,255,12,124,88,220,46,42,243,225,149,213,216,16,235,95,112,219,53,199,48,30,147,81,42,34,235,21,54,64,234,101,52,109,70,188,14,109,154,211,202,208,
242,18,135,100,20,25,1,176,33,225,147,32,72,180,221,24,75,153,0,29,16,67,134,132,100,37,5,191,128,133,213,224,112,24,45,66,87,139,98,49,43,50,234,208,107,133,17,47,123,121,28,35,131,115,107,240,158,107,
180,242,172,169,126,90,37,40,249,173,161,178,144,104,70,9,175,7,140,18,168,200,72,227,81,52,38,140,96,172,51,45,155,64,40,180,234,4,41,36,120,49,48,153,20,34,196,145,249,8,228,208,88,131,230,36,232,187,
128,149,15,171,87,103,151,11,242,220,249,110,69,64,135,138,147,177,143,70,131,147,33,44,141,147,113,106,90,46,215,33,203,240,90,101,127,110,117,173,134,23,174,92,46,106,135,31,35,3,166,138,113,145,88,
114,55,40,130,134,254,130,224,67,8,150,14,61,246,5,200,92,148,251,217,232,250,153,249,176,232,43,157,105,19,242,234,132,143,74,83,209,50,13,80,83,208,75,14,84,104,172,167,119,82,25,115,64,70,73,31,171,
242,129,42,137,246,120,141,129,5,65,110,78,128,113,106,140,10,7,112,87,74,114,196,199,26,82,248,130,192,80,17,129,117,54,173,255,177,148,57,226,181,138,75,95,30,199,200,192,47,240,9,108,57,222,201,168,
113,116,125,90,37,136,203,93,211,181,96,114,212,210,140,129,111,241,138,114,54,2,106,198,51,47,27,60,12,40,206,79,111,164,10,112,249,4,54,96,38,232,91,180,193,217,208,195,35,195,104,140,104,227,253,219,
24,37,5,64,173,27,216,208,225,68,254,47,252,37,96,235,24,198,164,103,180,70,49,217,131,198,175,31,146,193,181,129,38,57,101,24,224,19,18,193,27,142,96,14,105,174,224,247,48,142,146,139,85,46,207,38,192,
20,208,231,176,26,86,243,0,240,132,171,121,128,11,145,49,23,228,59,40,235,32,92,186,15,75,239,91,156,97,131,113,250,137,18,13,20,92,165,184,19,133,78,200,157,161,145,233,8,60,169,140,11,210,218,32,8,102,
178,96,165,146,140,36,149,39,156,166,161,13,32,130,48,42,43,201,227,72,82,241,134,99,195,218,134,136,149,224,55,134,193,83,52,4,208,51,90,202,24,113,248,181,194,102,128,29,115,169,203,227,73,50,246,233,
150,78,240,25,149,160,52,236,100,99,252,142,29,44,99,189,96,252,2,7,201,206,184,108,36,135,174,80,166,161,9,15,85,168,41,96,207,115,169,156,87,23,134,129,203,230,74,235,210,129,246,129,241,149,112,225,
45,74,251,90,3,13,147,150,70,248,7,20,75,235,222,189,40,248,127,97,24,26,231,236,147,179,187,92,189,60,15,116,128,41,158,3,189,50,15,33,76,241,197,42,23,184,234,229,71,7,196,101,39,34,189,12,59,33,23,
224,59,212,53,92,229,25,248,176,244,215,179,108,66,82,9,138,13,31,78,147,147,105,0,39,106,173,57,172,194,182,204,137,101,80,73,73,43,76,14,157,61,168,73,159,145,233,128,246,148,152,79,39,247,239,223,133,
161,192,112,190,118,237,122,156,182,240,209,140,14,172,27,168,141,53,233,113,127,41,50,175,224,33,26,58,246,201,61,177,59,143,54,239,129,215,58,209,13,60,224,165,46,143,199,101,120,30,208,136,32,101,106,
131,56,210,70,160,79,165,4,253,56,156,6,165,148,138,9,85,68,233,84,201,175,187,174,159,190,62,113,112,83,83,84,30,173,139,6,175,14,106,40,46,202,202,134,11,12,133,89,2,227,35,250,48,163,48,2,90,180,164,
219,2,196,145,212,160,209,96,76,176,19,225,26,232,208,145,12,7,251,237,249,197,118,176,178,15,203,62,59,201,40,251,222,225,126,232,53,177,16,92,25,45,110,150,97,3,146,174,135,235,202,38,16,108,212,18,
103,27,173,45,120,76,52,170,47,82,185,84,229,137,54,30,185,202,238,140,165,65,105,65,24,54,112,65,24,230,153,22,129,160,208,196,1,25,30,199,230,140,132,228,60,0,47,138,48,8,86,78,181,11,144,137,104,97,
25,187,97,206,238,59,208,41,34,159,129,15,139,75,138,54,243,105,55,33,220,30,104,16,246,95,234,6,77,24,196,22,73,17,112,98,30,13,55,74,41,61,93,6,22,71,77,209,52,216,108,154,35,44,118,43,210,162,12,156,
142,11,41,115,63,157,140,214,214,214,230,244,243,241,157,143,227,56,222,188,118,179,211,238,208,94,109,2,122,227,12,185,144,12,63,194,197,215,80,138,48,224,71,67,87,84,26,181,204,50,218,20,16,103,18,46,
23,68,242,152,140,205,87,210,220,90,100,34,229,11,81,159,158,70,9,70,97,84,215,181,33,215,152,199,84,228,41,211,148,10,165,142,95,18,28,230,195,181,205,193,62,31,195,158,78,198,15,31,62,128,251,140,162,
104,115,115,51,73,51,118,199,147,56,230,12,9,251,234,180,158,36,167,65,224,219,24,206,15,227,218,221,115,192,198,138,83,118,188,105,13,231,109,56,16,201,26,150,14,18,82,55,130,239,199,208,197,40,81,128,
155,63,64,107,78,179,26,247,113,119,27,198,194,231,193,28,104,24,68,228,12,90,3,45,248,31,190,246,13,214,103,214,107,21,6,148,11,195,200,248,242,53,133,174,78,33,195,174,162,61,83,108,178,85,251,73,224,
196,182,82,46,6,41,201,240,99,183,97,249,189,37,54,197,185,159,7,100,56,156,103,140,207,72,208,26,10,108,126,73,41,15,90,185,0,25,154,123,142,233,42,76,220,212,116,228,11,114,194,181,55,40,40,187,140,
142,61,47,151,199,101,234,170,138,147,228,24,129,147,12,114,18,25,97,237,121,197,62,191,59,179,249,228,84,210,234,154,154,55,216,170,140,176,193,81,59,19,54,12,47,217,44,215,62,21,125,2,25,6,88,121,168,
132,61,132,216,155,177,49,90,114,35,225,159,119,239,124,148,47,22,101,89,193,210,234,180,219,112,123,139,197,98,60,222,175,155,42,107,119,88,134,34,92,54,167,79,143,199,17,88,122,107,146,243,63,116,158,
195,139,147,30,96,138,79,86,20,69,154,166,20,188,224,72,27,193,181,14,202,120,195,231,60,50,198,231,73,73,23,243,156,184,36,27,205,191,20,79,157,255,213,119,100,161,85,108,135,146,177,169,92,210,144,206,
21,189,124,221,36,67,233,133,16,115,175,198,6,4,249,36,230,201,225,132,41,105,18,179,191,183,147,101,41,220,91,89,22,163,209,104,50,25,167,73,10,202,75,83,152,140,245,17,101,108,27,127,164,243,158,131,
3,198,223,51,77,136,98,117,165,108,242,208,229,154,149,85,85,222,42,36,245,36,73,107,227,171,67,239,12,21,109,160,157,187,214,24,111,70,251,108,162,31,199,56,85,197,155,95,134,172,246,158,122,170,143,
71,163,166,174,215,175,92,125,186,215,125,50,163,87,10,86,109,240,57,88,91,56,167,136,3,182,89,83,142,88,40,60,57,105,30,73,21,46,101,248,214,17,58,76,78,56,198,246,232,45,210,140,235,10,206,115,99,33,
112,23,33,35,217,159,230,88,227,153,125,7,115,209,120,183,39,201,216,135,58,79,206,215,190,73,235,136,81,236,192,14,203,225,240,167,201,216,117,198,177,130,32,170,64,161,225,140,170,6,129,19,176,102,96,
31,153,16,150,116,177,104,242,124,206,126,95,93,149,83,173,65,103,193,15,152,90,59,219,219,224,201,108,108,108,70,113,34,228,50,142,207,255,47,196,100,8,174,132,72,202,37,26,254,177,20,16,67,192,46,19,
68,98,181,179,138,20,223,207,18,201,38,204,202,46,147,242,84,144,61,4,196,27,54,70,96,135,176,105,195,79,189,250,186,81,19,81,188,82,96,72,40,194,116,191,160,28,31,123,3,206,20,181,234,16,222,75,24,125,
244,209,251,197,34,135,101,19,70,81,191,215,95,20,139,217,108,246,209,135,239,15,214,214,174,94,189,14,146,81,16,215,132,58,14,216,177,96,133,237,206,7,246,226,48,68,69,17,186,16,215,163,125,215,222,134,
32,85,46,201,60,108,176,236,101,121,207,22,196,143,6,148,53,33,67,52,33,87,150,49,105,254,198,88,52,151,245,190,80,255,178,109,142,106,220,132,108,150,63,213,163,126,255,157,183,246,118,182,255,232,95,
255,187,167,70,70,234,147,33,221,151,145,47,107,78,225,49,228,208,52,206,233,36,109,130,138,131,222,132,151,65,15,11,163,75,224,84,227,153,192,104,85,90,46,154,179,51,164,84,213,33,25,119,173,211,201,
152,229,157,139,223,20,164,59,167,105,78,187,9,41,254,104,150,171,4,237,126,198,22,176,227,140,59,194,35,15,158,36,67,33,63,92,151,48,115,81,187,8,147,5,98,73,41,139,36,13,28,60,120,116,75,84,97,57,200,
127,244,203,29,62,118,93,153,138,2,85,5,199,20,232,44,176,179,118,118,118,166,211,233,43,175,188,170,168,196,66,112,134,145,170,178,96,144,79,6,210,157,189,45,68,177,195,18,210,168,31,180,164,216,28,38,
224,195,128,35,77,140,186,56,185,18,36,243,140,33,2,184,250,42,122,221,180,80,143,120,221,172,32,107,52,127,8,78,100,98,133,53,86,97,40,163,128,28,73,176,95,106,184,65,163,231,197,44,159,205,224,251,69,
93,128,85,11,99,119,59,29,248,63,152,243,253,189,61,184,240,250,250,85,141,165,69,20,28,104,26,186,47,206,21,225,253,224,13,216,135,208,108,120,105,231,217,57,108,169,244,75,20,183,164,189,103,77,231,
89,64,138,238,192,50,102,153,213,101,76,251,59,96,43,158,175,164,164,61,124,125,81,210,73,145,238,92,252,117,146,16,38,27,189,239,252,242,239,142,135,41,190,240,233,207,249,200,151,102,13,109,203,171,
124,73,28,90,109,152,235,193,68,184,180,5,84,36,193,231,6,135,120,65,73,215,85,113,231,206,199,55,110,220,106,119,122,126,99,82,28,208,202,104,11,50,82,214,233,62,141,140,133,43,90,188,156,249,141,64,
186,159,109,19,98,14,211,154,182,86,143,115,77,12,87,192,9,23,108,124,170,140,12,154,168,157,135,73,129,142,64,17,215,211,196,212,33,174,61,97,173,103,138,64,137,221,221,71,197,188,108,140,117,124,60,
170,26,214,66,177,40,224,62,97,47,129,79,247,222,123,239,124,250,213,207,177,207,94,83,248,230,147,128,116,95,162,216,157,12,234,104,80,224,97,8,174,83,76,144,168,10,35,80,230,52,74,144,235,2,21,187,70,
48,183,88,142,248,4,152,100,173,109,241,128,225,72,188,136,218,178,213,149,157,144,98,216,100,244,154,90,96,36,43,145,177,210,120,123,255,248,225,223,49,32,158,45,101,248,19,156,10,112,67,157,78,103,54,
159,239,110,111,207,166,147,23,95,250,180,68,183,134,81,170,188,29,49,204,99,232,21,115,16,29,76,167,149,53,96,205,31,78,255,161,35,137,155,249,208,82,87,167,89,198,134,199,65,167,77,10,182,91,169,160,
210,206,225,83,144,238,249,124,126,247,225,253,16,93,92,205,71,217,251,239,190,13,30,47,235,60,48,227,187,253,254,218,250,149,60,207,183,30,220,75,210,116,243,218,13,190,155,147,64,171,151,57,47,170,13,
228,247,228,156,14,62,57,8,139,65,69,4,152,161,118,50,236,165,195,147,192,140,223,187,251,17,120,227,48,197,119,239,124,60,28,174,109,92,189,198,57,212,144,78,93,91,105,64,33,124,159,152,245,32,236,19,
201,144,241,5,203,136,178,133,250,55,2,233,126,182,77,200,139,159,65,6,228,35,219,221,98,161,205,54,247,124,188,12,56,3,117,210,155,162,239,158,183,234,60,165,5,69,217,34,174,205,117,90,169,170,170,71,
15,183,40,166,30,8,23,240,18,14,62,138,119,91,91,188,34,89,211,236,112,240,29,26,206,118,63,119,164,187,67,177,35,124,83,219,167,179,214,7,47,36,182,208,79,54,255,203,242,23,246,55,216,161,99,56,229,227,
175,91,59,208,156,193,74,195,176,47,123,29,217,129,23,145,155,197,158,204,65,79,53,162,177,30,187,131,169,143,118,118,234,186,228,89,34,55,205,198,203,225,184,159,206,102,176,1,179,86,86,150,213,135,31,
188,255,242,43,159,33,104,62,215,111,147,93,35,108,164,109,137,170,183,193,120,201,48,96,251,228,214,64,60,255,50,94,218,10,12,88,149,43,115,120,28,210,125,54,155,252,236,39,127,9,95,203,178,214,100,60,
226,225,222,123,251,151,240,75,175,63,184,125,251,165,15,239,124,84,255,186,252,250,235,255,234,131,247,222,190,119,231,163,223,251,253,63,176,193,245,35,48,245,135,127,86,35,95,82,44,227,237,218,231,
42,104,147,196,17,69,43,196,1,153,178,174,97,7,108,61,188,63,157,140,97,198,211,52,133,163,24,254,182,63,218,171,117,115,227,250,109,120,228,170,105,148,133,20,42,190,22,6,47,233,172,176,113,226,147,201,
240,57,194,62,8,232,201,223,8,164,187,99,65,56,229,38,164,164,119,195,8,117,135,134,151,116,226,185,189,36,142,151,81,73,17,119,167,66,71,213,120,29,253,120,2,104,243,129,234,175,196,75,239,222,189,143,
217,40,59,88,192,102,237,38,254,47,175,90,88,105,28,193,117,176,29,67,17,107,14,113,62,7,164,59,61,117,195,22,55,33,239,27,174,158,228,184,6,66,153,78,169,4,217,114,95,65,177,27,54,110,158,244,186,217,
255,5,53,2,222,83,42,226,43,106,13,62,27,53,163,153,156,215,96,253,84,214,134,162,25,67,25,133,150,65,185,179,243,8,180,67,20,133,132,97,214,190,56,145,17,6,85,89,193,87,226,40,246,154,3,174,37,109,22,
193,45,45,139,129,83,224,255,70,132,222,184,212,101,204,137,66,206,224,219,122,121,250,219,113,72,247,7,247,239,213,85,245,187,95,252,151,96,55,253,237,223,252,213,120,180,207,235,50,107,181,191,250,141,
239,160,151,30,133,127,247,255,253,252,157,95,189,9,218,234,198,173,23,54,55,175,123,164,251,83,21,22,226,107,93,228,139,207,30,205,222,129,243,211,216,125,5,77,1,134,73,195,199,184,147,209,77,253,224,
254,253,217,116,10,79,222,106,181,64,103,89,167,183,106,242,249,180,42,231,237,174,14,131,90,5,117,0,238,73,216,192,160,77,19,129,73,91,85,160,131,226,124,145,218,188,184,242,201,45,173,232,226,129,213,
89,104,212,177,12,186,159,116,63,154,82,197,255,140,116,127,146,76,208,154,37,109,48,214,147,114,220,227,196,136,139,27,91,69,103,68,195,59,124,62,159,231,179,25,7,104,49,42,175,34,202,247,9,14,117,193,
15,166,135,200,121,233,116,187,235,235,87,156,62,211,140,116,199,80,198,115,66,186,19,156,85,75,7,80,1,195,196,165,204,48,99,91,35,208,67,159,69,9,170,88,168,198,163,216,241,198,159,240,186,133,139,226,
163,182,106,146,53,57,172,77,243,200,60,170,101,45,92,154,222,102,78,73,134,125,166,187,119,63,46,49,62,43,236,221,74,159,194,149,76,125,33,201,4,6,195,108,99,227,10,57,107,218,58,168,228,115,179,147,
183,82,228,40,57,164,123,73,190,182,141,141,217,40,179,164,67,34,182,152,82,208,57,199,32,221,67,116,253,196,104,111,55,10,163,249,124,230,232,135,68,154,102,101,85,130,204,198,230,53,240,7,65,91,193,
135,159,126,237,119,216,130,176,72,247,167,147,153,232,213,200,23,159,78,206,58,160,108,1,222,10,78,156,195,182,104,150,105,234,234,238,157,15,203,178,140,227,56,77,82,248,5,14,16,86,192,6,181,126,125,
239,222,221,175,126,45,77,146,154,188,78,120,124,124,138,56,6,119,157,170,61,208,203,12,38,147,222,100,210,109,192,225,99,60,145,45,41,168,9,35,23,16,142,137,115,195,130,127,97,31,85,158,195,191,248,237,
70,186,135,89,21,182,139,50,79,234,105,219,134,146,92,41,199,98,145,79,198,251,76,57,192,26,106,177,40,224,159,232,227,11,27,253,225,131,146,66,245,138,79,84,184,85,80,7,221,254,128,93,116,45,108,197,
6,167,94,104,71,61,47,164,187,176,179,45,57,45,36,207,143,164,179,133,135,140,153,52,76,132,240,4,115,140,203,17,181,233,139,46,120,130,185,88,60,106,182,173,141,185,100,180,18,174,252,14,141,219,217,
28,124,190,41,232,74,196,3,56,99,132,149,21,39,251,164,178,232,138,78,167,187,182,126,213,172,32,87,86,77,155,67,247,195,158,251,17,203,207,26,161,14,72,97,11,7,141,195,193,16,152,9,100,66,30,71,30,185,
140,13,5,8,3,130,205,43,10,246,251,57,60,14,233,126,227,230,237,124,54,253,240,215,239,237,108,111,69,81,4,214,150,11,114,193,1,30,178,204,112,125,99,119,231,209,167,95,251,92,148,196,46,211,132,72,247,
167,243,218,96,240,194,38,11,248,169,216,119,37,235,12,1,37,171,229,145,218,61,121,20,7,239,189,251,22,40,169,110,183,11,207,188,63,218,231,88,32,216,186,24,83,81,166,193,24,124,253,230,63,197,107,27,
155,168,143,92,110,5,83,20,120,164,87,81,84,117,187,227,126,111,111,208,223,155,205,186,123,251,67,41,35,148,49,148,202,53,76,163,129,41,39,74,148,72,187,76,132,173,21,248,103,164,251,227,50,50,172,131,
246,184,42,66,208,86,218,253,9,44,14,48,129,247,118,118,34,140,220,85,188,233,200,31,8,202,178,224,98,102,187,57,249,228,247,135,62,153,6,240,66,251,160,174,250,107,85,83,243,128,46,79,194,224,195,231,
131,116,231,121,224,172,156,160,156,228,97,32,206,137,149,32,135,189,151,79,71,123,29,76,45,151,111,59,226,117,51,200,0,84,112,38,211,190,232,77,197,124,167,217,209,214,254,36,108,99,16,204,231,211,209,
254,30,197,23,13,227,179,230,121,94,20,69,136,129,39,212,152,158,225,15,11,247,152,128,204,214,162,171,78,175,71,152,30,152,254,144,16,170,205,83,150,31,250,195,176,252,18,58,233,249,52,67,153,38,176,
102,230,202,126,73,120,28,69,231,7,38,202,26,205,208,57,2,193,136,85,25,246,181,49,26,131,38,57,225,182,240,117,107,142,148,61,5,233,254,210,171,159,125,249,181,207,174,214,247,127,231,143,255,39,155,
166,37,153,123,31,127,8,134,216,245,91,183,253,56,30,233,126,18,175,144,121,200,142,66,186,227,186,49,214,210,89,34,221,223,123,251,109,152,184,78,7,97,208,219,59,219,161,123,1,13,133,0,16,87,22,4,69,
89,128,203,209,175,215,248,60,183,165,76,164,182,64,133,213,117,184,88,100,240,250,122,221,73,191,63,109,183,31,60,120,120,101,177,136,189,12,135,106,149,3,7,175,48,247,252,51,210,253,40,164,123,83,101,
195,93,24,169,153,12,153,205,146,35,241,59,91,15,24,7,49,207,231,156,217,168,232,192,131,181,26,98,229,141,37,234,116,137,97,198,87,27,126,11,81,28,103,105,118,253,181,36,223,171,163,32,36,75,74,47,223,
131,51,109,158,61,210,253,49,20,187,100,98,79,246,113,78,141,98,119,211,197,190,45,70,178,112,110,143,54,217,28,106,80,6,38,92,151,107,11,89,236,234,61,100,207,114,247,58,153,142,193,116,136,163,24,188,
31,210,162,54,255,10,211,30,6,129,135,29,24,23,189,66,13,105,51,223,34,141,147,78,187,211,239,15,73,233,216,82,67,120,237,79,89,126,104,5,168,218,145,148,81,62,36,136,35,43,35,142,53,243,109,97,53,65,
201,30,151,193,179,1,23,143,166,59,231,215,170,120,14,195,162,42,207,124,170,223,253,248,131,60,159,191,252,234,103,225,218,126,28,166,82,120,225,211,159,243,0,81,54,3,221,221,56,87,214,211,221,74,170,
140,98,134,19,91,127,225,17,6,28,127,71,157,165,29,254,32,1,111,47,73,246,246,118,3,187,238,133,119,236,57,45,10,195,130,211,177,191,183,61,88,219,116,87,177,50,161,226,170,84,184,126,4,182,21,120,133,
155,155,15,175,95,187,183,245,104,99,10,190,204,65,25,199,173,33,201,40,109,216,240,62,179,127,17,80,196,242,25,84,107,123,172,249,105,55,42,195,87,220,215,165,133,219,72,105,1,202,54,46,105,14,201,36,
221,25,252,105,177,219,51,184,224,200,14,18,122,123,235,254,124,62,163,36,58,150,92,128,69,92,19,131,48,1,255,66,130,10,7,12,35,23,182,168,217,40,135,218,142,146,36,77,211,171,55,174,139,96,156,244,230,
197,168,141,248,114,132,156,250,24,154,97,124,63,154,220,204,241,64,175,56,32,187,96,53,107,174,29,146,249,162,64,36,12,98,68,214,59,161,93,66,249,212,74,16,117,119,93,81,192,20,55,33,69,66,100,77,180,
4,8,103,175,155,39,153,99,88,112,103,212,117,117,181,22,205,131,102,139,193,244,108,210,110,61,248,8,93,250,70,79,203,9,59,10,24,42,169,209,150,81,238,135,49,216,244,66,177,2,61,32,196,56,168,9,48,129,
65,205,253,238,230,239,61,48,143,52,213,66,73,186,22,41,97,121,218,229,167,194,80,121,25,28,191,38,25,233,170,193,205,33,153,39,237,41,14,14,56,138,52,69,182,8,37,235,190,241,250,183,159,90,70,115,76,
169,205,230,245,155,104,94,173,200,156,176,196,4,238,15,14,207,128,106,136,248,90,116,88,49,130,223,48,226,137,42,18,36,63,57,203,192,108,46,22,57,6,212,156,10,247,64,94,71,164,141,220,62,112,157,178,
170,218,237,12,94,134,164,80,101,72,185,9,247,206,8,223,129,62,31,156,75,221,44,171,122,189,17,126,88,118,30,151,225,195,130,145,238,184,188,130,80,217,4,63,179,211,121,134,70,9,207,11,239,0,222,244,145,
50,85,89,116,218,221,99,4,78,50,200,73,100,92,173,229,249,202,77,150,213,22,198,1,26,4,27,176,171,50,240,215,184,55,173,231,169,169,82,39,35,118,30,61,0,171,138,192,235,53,50,43,208,207,114,84,130,170,
56,28,51,7,41,20,147,142,51,94,113,208,239,175,95,189,70,92,50,50,76,11,93,182,61,35,176,116,79,71,85,117,148,212,231,19,216,169,233,213,172,121,20,134,112,154,198,73,26,218,35,93,58,98,150,3,50,60,23,
39,145,177,139,220,44,125,87,248,78,128,251,227,20,115,203,101,113,190,136,54,100,37,75,136,240,39,189,110,42,166,131,173,140,97,187,117,57,140,68,120,223,60,212,194,131,120,13,28,15,139,124,145,231,185,
38,44,5,88,24,224,3,226,164,107,139,156,226,250,57,66,51,160,251,197,144,47,126,8,208,85,173,44,187,126,253,83,125,217,139,101,84,6,21,29,35,182,176,230,228,203,239,0,61,63,110,55,68,177,195,56,54,39,
227,66,125,210,115,208,176,12,234,132,102,41,99,141,27,227,89,150,217,99,32,154,105,59,207,97,18,165,85,93,242,196,61,158,95,36,192,110,196,57,200,199,101,58,221,222,49,50,165,174,184,50,138,78,37,233,
137,216,89,134,150,113,237,81,178,246,5,19,18,141,205,25,244,135,235,122,153,151,33,153,110,175,95,85,96,243,130,201,173,217,249,39,61,162,125,248,67,114,54,9,211,76,122,111,119,7,108,49,56,106,92,1,137,
232,245,251,105,218,90,205,209,194,181,30,62,188,190,190,246,104,208,223,175,170,0,244,23,39,38,108,254,216,201,176,157,85,53,6,30,106,153,148,160,142,3,62,71,203,88,13,74,1,28,33,83,168,156,89,214,14,
205,33,199,242,86,199,185,40,153,144,16,109,69,85,172,190,83,70,136,198,225,209,50,190,162,205,241,249,70,112,250,145,211,141,57,108,94,250,46,123,131,7,72,212,89,224,33,188,200,120,108,56,174,231,147,
233,100,50,129,25,155,207,231,112,110,211,75,182,199,166,79,168,81,82,92,175,96,114,141,43,18,196,23,180,190,113,213,144,253,85,205,227,32,155,203,100,38,243,54,225,233,117,32,67,241,156,144,238,24,158,
64,253,43,57,96,77,250,205,34,176,79,85,202,99,33,151,129,98,133,75,8,117,90,99,43,136,240,240,8,68,56,39,22,100,38,211,177,152,162,255,75,156,81,240,215,237,71,247,23,139,69,77,129,33,21,224,165,9,47,
34,151,236,236,214,221,22,214,218,162,234,116,73,7,0,188,145,181,222,112,253,202,38,22,69,203,89,79,116,119,155,61,246,134,92,62,241,196,126,180,92,82,139,226,187,163,189,79,184,4,78,56,50,235,140,103,
88,118,50,104,146,11,43,195,102,148,180,184,28,227,82,16,74,40,183,72,112,14,47,158,94,230,132,50,108,190,41,127,127,148,202,164,16,27,87,183,218,58,79,122,142,3,50,107,235,27,224,15,10,50,217,188,182,
102,133,226,122,171,88,146,195,217,124,14,250,2,118,14,26,156,148,147,218,222,126,4,54,23,248,28,253,193,218,234,181,182,30,13,55,85,117,245,202,110,211,100,69,145,60,233,126,206,243,236,207,12,214,112,
102,25,31,119,116,180,159,2,150,148,96,84,55,135,225,86,152,108,249,72,12,211,61,83,101,74,134,180,118,241,75,147,201,62,106,183,178,228,13,147,47,22,171,4,27,116,29,180,127,217,199,33,204,52,69,121,225,
176,173,234,254,160,63,28,12,195,48,54,130,139,25,100,83,198,65,50,175,231,45,142,108,178,121,110,92,178,245,89,34,221,133,63,237,177,130,4,81,236,2,137,79,79,137,98,103,230,22,70,177,211,146,166,92,199,
83,184,216,149,176,157,80,250,170,11,127,27,235,137,239,22,145,207,167,83,58,30,166,211,25,44,108,67,92,51,124,38,161,77,38,185,184,70,172,64,72,181,64,162,210,128,15,39,152,109,56,30,40,176,38,38,26,
206,234,118,87,118,71,102,204,239,215,22,177,159,192,143,182,104,58,97,137,172,73,79,51,65,16,7,52,13,219,165,182,238,221,199,19,86,101,56,39,227,131,107,46,201,140,230,136,169,57,147,201,61,130,130,215,
191,253,93,71,171,108,60,66,221,185,142,20,191,64,10,158,240,194,101,92,204,221,51,123,41,70,160,132,92,56,198,225,40,161,143,148,217,188,186,57,30,109,97,84,196,85,223,74,199,253,224,250,124,160,45,80,
44,224,127,248,67,17,72,205,149,80,85,85,225,71,249,44,205,90,81,24,251,107,77,166,89,183,51,233,245,198,187,187,29,241,228,251,57,243,179,215,101,153,164,217,73,230,167,44,23,101,89,132,81,120,72,6,142,
206,98,49,199,46,6,42,184,140,247,69,170,196,214,108,114,243,21,140,52,105,239,102,90,22,61,150,33,80,230,2,92,182,114,218,106,42,139,21,6,191,100,180,191,199,254,8,50,180,81,224,84,5,202,230,113,92,233,
40,231,203,13,175,123,110,156,3,214,92,20,182,59,237,124,158,119,187,61,159,249,130,187,72,58,141,46,67,198,138,186,149,45,151,113,73,187,39,165,187,201,3,79,87,20,11,56,156,46,100,150,124,212,219,23,
211,49,69,42,211,163,251,74,65,138,100,19,240,221,49,151,176,140,139,135,26,246,176,78,232,147,242,14,182,197,24,82,92,85,27,11,89,204,101,238,27,114,237,108,63,4,119,163,40,74,84,249,97,84,148,37,89,
244,98,233,210,123,202,19,201,140,138,164,229,195,0,172,173,110,183,59,28,14,195,36,101,187,8,172,182,88,196,29,213,30,155,137,144,75,122,140,19,249,209,142,18,214,184,196,29,191,116,227,136,0,151,157,
44,196,50,214,32,93,230,119,41,192,44,128,54,199,160,25,234,229,236,126,27,2,191,4,122,153,19,203,160,30,14,66,225,201,35,88,63,25,38,237,183,52,96,71,202,108,108,108,189,250,170,252,232,67,100,47,227,
117,192,7,2,135,240,209,16,197,147,70,187,2,106,58,105,225,23,131,72,87,78,220,194,205,228,249,60,140,98,94,78,124,173,233,172,53,28,228,113,92,205,231,157,39,221,207,153,159,189,0,91,35,142,79,50,63,
59,143,30,142,246,246,134,107,27,135,100,242,124,118,239,206,199,24,150,62,217,56,7,100,192,103,15,52,38,190,225,4,67,213,87,107,80,74,162,14,148,77,52,97,198,138,200,124,125,58,138,203,146,125,68,140,
119,182,151,209,166,137,19,19,36,21,152,63,62,236,240,104,251,33,98,95,240,165,104,216,21,68,113,235,226,228,54,70,109,169,41,45,45,185,91,208,112,183,96,233,107,176,134,96,195,33,153,64,204,149,197,24,
221,72,102,166,142,112,55,45,75,254,181,113,237,246,56,192,193,57,100,142,63,172,206,0,28,77,173,118,251,162,86,44,111,93,162,49,32,85,66,160,168,39,41,56,123,130,130,117,86,215,139,124,46,93,31,70,91,
245,130,126,22,236,119,180,76,35,154,82,48,199,56,169,74,218,161,161,144,30,111,100,162,54,146,50,145,73,166,211,29,189,87,137,154,207,78,88,81,251,251,123,85,89,27,203,39,35,248,72,102,117,233,244,157,
100,35,136,203,54,248,41,96,215,112,133,249,60,159,247,122,61,138,197,49,83,140,104,155,172,148,85,35,48,92,223,104,91,199,238,105,124,224,86,225,252,134,197,3,203,9,70,132,123,62,36,99,57,86,200,140,
100,219,211,49,123,24,71,64,100,205,97,142,72,82,124,79,82,36,203,243,127,24,23,154,176,140,163,28,29,247,243,124,82,122,153,11,151,177,172,93,180,15,136,82,135,208,237,202,42,102,23,183,58,66,6,78,238,
110,103,182,187,215,191,245,194,181,15,63,120,191,38,140,15,227,53,96,85,52,102,217,91,205,239,22,222,108,112,63,77,158,103,89,6,14,11,44,18,184,187,209,254,246,218,250,85,129,1,56,246,56,226,253,113,
119,208,199,218,117,174,148,56,116,63,234,28,207,158,159,6,214,192,49,230,67,50,138,80,43,103,128,71,132,113,37,211,221,208,25,162,234,96,92,83,55,137,204,219,54,143,35,180,15,124,216,74,49,238,170,197,
37,206,214,188,231,98,3,152,207,82,130,63,213,72,203,80,9,214,107,81,50,91,3,123,19,69,57,79,136,28,166,33,0,68,195,68,222,74,136,101,158,196,45,6,44,244,137,185,231,212,98,177,72,179,14,187,225,32,30,
90,240,128,45,12,122,94,156,238,141,118,120,78,130,158,177,49,133,225,112,135,192,62,148,79,199,9,163,188,230,98,62,223,219,219,190,186,121,61,74,91,12,137,230,175,44,253,86,218,243,71,34,212,121,199,
178,89,71,149,24,162,22,181,151,217,217,125,196,160,10,186,19,12,114,11,227,49,159,220,130,213,85,61,185,84,121,77,197,234,164,179,234,233,116,154,101,173,124,62,79,210,22,95,171,52,88,160,19,104,197,
247,163,78,90,8,233,101,140,215,80,252,50,232,204,9,88,93,133,54,112,73,249,55,178,189,29,213,189,240,216,14,132,134,9,45,92,41,133,197,12,83,61,175,112,25,128,147,210,203,92,184,76,217,84,210,185,193,
132,73,17,156,42,162,124,103,195,115,208,216,150,72,7,100,134,131,25,140,52,153,244,146,36,124,249,149,87,9,71,90,177,54,227,238,106,222,61,180,120,104,156,102,38,105,53,20,100,153,128,211,81,81,152,25,
174,182,191,183,189,113,229,186,116,215,26,141,58,253,222,126,171,189,7,10,241,168,251,169,207,254,236,79,131,53,96,205,202,108,202,96,72,38,20,134,191,230,179,25,60,56,166,114,218,29,195,224,35,26,103,
62,157,162,169,24,5,139,69,129,133,7,69,1,239,181,63,24,194,56,211,233,4,36,91,157,78,24,38,124,173,40,204,133,79,77,185,168,31,219,53,116,140,85,139,188,100,0,208,178,140,217,62,59,198,155,248,204,224,
53,42,157,12,230,117,66,226,214,231,37,76,193,123,70,72,113,233,47,236,66,2,43,54,244,56,22,197,190,210,236,201,57,42,148,113,102,132,4,199,37,9,19,47,141,165,116,83,168,40,148,45,74,87,54,118,246,156,
57,221,107,10,60,177,174,121,18,210,221,65,160,29,19,137,48,14,23,237,9,206,13,225,200,14,35,212,151,45,2,133,225,217,99,153,16,254,103,211,65,146,101,138,69,193,33,118,14,147,149,228,15,10,223,81,205,
114,101,137,101,21,49,77,49,97,116,145,82,93,83,85,38,248,25,73,218,230,107,113,230,50,144,225,202,121,127,170,66,11,219,128,50,164,86,137,218,5,216,249,249,8,227,226,193,89,88,51,179,12,191,219,96,142,
224,249,244,5,27,129,107,99,172,157,55,141,22,150,126,86,196,114,135,100,216,21,243,28,99,108,208,226,158,193,132,23,66,117,44,26,158,35,23,43,50,189,238,8,124,55,33,18,152,112,88,37,215,175,223,124,248,
240,65,81,20,172,212,220,97,43,121,231,83,96,158,183,138,100,13,165,17,140,91,216,60,5,230,77,130,178,200,227,36,227,107,193,219,156,205,178,126,111,188,183,215,63,234,126,206,254,236,199,19,248,21,77,
253,224,238,29,184,109,48,73,230,249,140,175,245,224,238,135,117,85,118,186,253,173,7,247,122,253,97,214,106,241,78,152,236,143,118,118,182,226,36,161,84,171,14,214,175,192,115,237,108,61,132,105,106,
117,187,143,30,222,111,181,58,107,107,27,254,90,4,14,209,54,63,205,197,70,158,24,131,38,54,4,123,83,224,2,202,214,70,141,239,97,67,123,146,177,66,176,231,82,174,241,164,159,249,110,27,36,194,72,32,181,
183,67,195,215,20,225,166,130,12,139,255,92,165,142,88,233,16,206,54,145,51,18,237,129,36,24,53,229,35,178,53,89,35,88,158,208,40,193,214,5,97,159,158,13,167,251,116,180,47,9,147,76,16,214,214,104,180,
7,31,38,113,154,182,90,96,49,85,85,153,182,208,38,157,78,38,240,20,221,126,31,28,225,98,129,161,165,118,167,203,199,9,234,26,208,215,140,62,3,59,171,88,128,66,129,167,111,119,122,168,106,217,145,162,118,
164,30,89,206,40,118,109,187,52,72,99,123,207,88,153,36,136,61,77,62,151,246,193,13,194,178,199,34,39,248,169,85,224,72,189,137,56,44,212,210,250,40,204,210,5,167,237,106,56,137,74,56,3,102,107,88,94,
75,233,74,87,17,18,121,157,12,233,126,16,182,201,239,186,65,127,147,113,12,130,155,188,226,84,200,144,107,220,217,98,34,243,138,95,61,78,51,115,195,19,87,189,117,9,29,254,195,47,27,73,125,178,209,254,
184,248,70,170,39,148,97,53,68,165,100,92,31,230,41,117,165,177,69,33,206,113,93,145,201,178,5,188,151,233,164,235,101,90,96,215,102,25,8,97,144,40,8,188,175,99,44,171,153,61,195,109,30,151,166,12,236,
145,225,112,56,157,205,184,139,215,120,180,127,245,90,219,95,107,60,233,130,119,223,106,193,120,217,161,251,185,188,249,153,77,198,240,142,174,108,222,0,173,116,255,206,199,112,135,96,40,45,22,243,40,
74,48,0,31,134,243,217,164,211,237,242,44,129,182,74,146,244,230,237,79,193,134,217,122,120,15,225,26,131,225,100,188,63,153,140,120,253,109,92,221,92,189,150,34,219,71,88,222,222,3,189,233,89,191,215,
232,85,52,1,165,23,34,74,234,233,165,15,96,75,8,28,116,8,213,77,76,160,10,84,232,129,244,104,120,206,6,178,25,223,96,16,145,168,92,155,198,183,158,215,228,242,105,27,221,103,182,111,231,158,82,200,130,
104,51,45,51,26,86,173,26,107,73,9,244,86,140,79,173,60,3,78,119,152,73,172,63,77,210,142,236,222,219,249,8,244,78,167,219,131,147,160,215,31,164,89,107,127,111,103,128,127,77,198,163,61,176,106,243,249,
108,247,209,86,214,110,131,142,134,181,116,253,230,237,217,124,186,200,231,240,56,25,232,53,10,27,77,70,35,248,39,104,58,24,170,59,24,114,224,240,170,220,64,45,193,246,38,134,144,140,71,58,226,209,18,
88,76,196,150,217,161,254,244,170,33,103,188,225,4,20,17,60,4,161,173,244,224,121,243,53,11,141,209,106,153,145,80,190,189,160,240,225,119,42,208,11,28,180,196,35,230,65,205,41,219,53,231,4,72,247,195,
126,180,112,208,45,195,117,17,76,186,19,112,225,169,163,186,91,145,225,56,12,231,94,2,251,11,69,168,252,181,132,77,163,89,83,3,129,199,23,222,72,245,132,50,54,208,75,137,20,226,235,112,132,246,30,204,
225,66,81,142,208,190,33,156,52,182,63,43,202,208,56,153,221,189,93,131,12,249,97,193,120,66,198,40,10,199,13,37,141,111,54,225,171,180,26,162,90,198,138,176,26,79,39,162,139,208,254,90,186,201,104,243,
52,71,220,207,57,158,253,120,2,63,69,170,22,92,66,194,22,149,24,0,142,19,184,153,44,3,115,111,88,148,185,227,120,65,85,18,4,33,200,128,182,90,224,169,78,197,124,42,184,122,245,218,221,59,31,205,166,147,
78,175,135,48,159,213,107,73,95,247,42,93,136,204,229,254,104,45,83,170,2,173,192,154,202,107,252,143,75,185,250,118,92,210,226,221,249,99,88,240,225,194,163,225,17,172,128,145,20,92,190,8,58,167,54,7,
146,176,11,188,78,61,107,149,43,24,100,54,106,133,223,34,134,6,74,246,51,28,161,182,113,215,128,218,217,129,198,86,174,211,212,18,233,110,46,15,233,206,213,178,87,55,175,195,153,129,133,120,81,84,148,
5,220,12,76,239,112,237,74,43,107,131,2,138,227,56,64,40,98,127,251,209,3,75,150,75,71,218,116,50,230,210,174,43,155,215,224,92,1,73,44,185,93,91,111,183,187,15,238,221,217,223,223,133,211,197,186,57,
84,66,44,152,17,8,61,71,134,230,176,154,150,98,25,217,176,232,115,6,175,177,150,231,53,140,78,61,213,244,81,189,84,64,81,191,198,250,182,148,101,178,197,15,190,47,1,217,250,28,10,96,134,98,242,40,189,
167,70,229,13,4,240,98,158,245,51,248,209,202,69,81,124,135,151,134,198,209,174,117,247,138,12,248,236,39,40,186,36,215,135,203,21,9,168,117,17,164,113,227,241,254,251,111,191,181,121,253,230,230,141,
91,44,243,222,91,255,112,124,33,225,203,159,249,2,211,203,114,164,73,11,237,112,85,136,202,99,114,56,78,106,48,194,205,53,82,47,225,247,178,4,25,209,144,231,204,86,55,191,131,198,33,188,56,7,31,40,105,
139,39,157,79,238,24,223,240,116,2,95,32,13,51,206,33,194,186,132,245,196,215,34,139,65,70,209,81,247,179,236,241,125,6,226,189,227,8,252,224,0,199,166,0,251,123,96,215,193,137,84,53,26,246,3,232,160,
253,189,221,123,147,143,96,195,244,134,67,143,102,186,113,235,246,253,187,119,30,62,184,215,233,116,60,45,6,156,252,84,59,130,229,232,135,239,7,3,221,141,187,218,18,145,108,155,83,162,254,9,29,50,215,
37,149,221,61,219,70,9,143,181,30,167,84,172,8,99,77,208,62,78,72,4,113,24,52,21,156,209,184,115,164,77,72,75,203,248,110,115,237,22,226,75,0,97,27,145,229,16,97,70,20,32,68,210,16,241,213,67,74,15,192,
48,101,163,92,160,218,206,246,101,115,186,227,33,143,141,243,224,128,140,225,237,195,187,0,95,79,83,133,60,145,193,13,31,62,188,11,167,69,127,184,70,181,104,113,89,44,58,157,30,236,174,52,205,2,164,27,
205,97,4,112,32,177,224,29,27,8,169,186,44,23,65,142,105,80,202,12,114,12,113,75,236,208,209,66,81,11,169,44,135,142,113,7,174,219,183,204,215,94,154,170,173,90,22,64,64,247,72,201,238,138,203,155,172,
222,147,82,154,3,45,66,124,44,139,70,163,246,180,150,39,62,114,1,56,201,239,151,45,178,88,37,179,102,214,136,134,81,211,103,142,252,68,20,25,183,17,9,227,210,187,132,149,129,215,118,218,8,210,42,199,252,
19,233,101,30,61,188,151,231,249,205,219,47,166,73,242,235,247,223,25,12,215,134,195,245,251,247,238,76,167,227,235,55,95,0,221,188,189,245,0,30,104,109,227,10,188,191,241,222,222,238,206,54,124,181,221,
238,192,134,225,113,142,255,209,174,100,148,187,69,50,86,205,35,221,233,25,44,210,221,7,165,208,74,7,63,23,254,19,198,44,131,161,18,228,241,169,153,37,98,37,200,199,133,72,13,119,235,106,28,131,156,69,
162,82,36,133,11,11,96,245,192,3,230,243,105,156,100,75,62,204,26,116,83,253,248,253,156,7,51,253,84,2,191,205,205,27,215,174,221,90,173,22,72,90,173,107,224,83,172,84,29,188,246,153,223,229,107,189,252,
202,107,171,227,192,25,53,157,140,224,121,215,214,175,166,113,122,232,126,234,105,24,181,43,23,199,19,14,169,46,57,166,219,20,224,117,214,171,72,119,143,154,97,164,123,68,91,215,33,221,155,165,12,121,
9,224,186,145,118,162,98,134,56,46,203,18,116,253,98,209,216,174,206,117,227,97,114,114,217,125,222,66,72,217,85,132,95,219,200,134,188,128,29,5,155,191,211,238,114,149,63,98,193,36,155,12,54,72,31,48,
160,154,42,120,46,23,233,78,99,34,179,91,164,134,107,27,96,52,237,110,111,129,124,183,63,64,202,13,208,95,237,110,81,228,253,254,26,8,15,214,214,225,46,119,182,183,224,30,91,173,14,184,141,224,191,123,
46,118,69,65,61,208,197,147,201,24,110,103,253,202,21,135,162,88,225,98,119,90,67,90,226,48,227,200,62,151,50,141,68,202,54,116,5,20,3,174,81,219,54,176,225,169,229,135,166,61,142,161,247,154,33,169,174,
250,198,167,83,137,167,212,69,141,225,56,4,255,180,70,16,117,156,42,151,164,195,35,5,243,74,245,89,144,238,135,208,249,77,245,184,76,112,214,40,202,42,199,252,19,145,238,240,86,222,253,239,191,32,202,
199,254,219,191,252,199,155,183,63,149,101,173,55,255,241,191,247,122,253,107,215,111,253,226,167,127,213,106,181,225,84,127,247,237,95,126,254,139,191,63,155,77,145,79,57,159,77,167,19,176,120,93,31,
180,99,21,22,197,149,34,21,109,94,187,239,240,62,182,159,237,74,231,17,227,221,144,123,15,54,49,150,20,84,101,133,26,196,161,207,181,115,88,200,109,228,88,47,241,193,240,9,239,202,65,132,213,120,82,184,
148,169,230,112,32,18,108,145,202,91,69,213,215,77,20,112,81,213,111,14,210,29,124,13,208,116,157,110,247,136,206,219,34,104,102,169,150,190,90,64,44,235,239,12,159,213,226,12,72,119,37,98,99,102,1,30,
33,138,173,209,110,127,56,159,207,96,101,130,158,128,47,241,41,226,114,228,1,223,12,55,215,227,72,8,24,8,96,146,244,123,189,217,124,14,11,55,77,19,216,66,176,168,140,239,33,134,17,0,105,154,128,99,36,
203,172,220,37,35,221,111,189,240,34,135,144,65,160,221,237,129,121,101,150,112,25,148,25,172,111,80,236,184,230,75,131,247,103,1,32,116,147,87,174,92,243,188,230,224,51,194,180,28,228,44,215,182,232,
16,159,195,210,61,243,252,248,48,179,93,186,228,40,50,210,29,131,137,24,105,10,177,156,152,140,150,52,77,49,163,106,204,2,233,118,169,3,72,93,251,217,96,198,81,27,91,90,73,206,194,7,189,94,15,252,92,56,
171,64,89,183,218,109,233,232,177,25,10,209,48,245,216,105,144,238,207,82,230,137,244,50,195,225,198,218,250,149,15,127,253,110,183,215,207,90,237,187,31,127,8,255,173,171,234,133,151,94,1,103,164,166,
243,182,166,115,9,254,121,243,246,11,32,0,230,216,205,23,94,60,45,167,59,49,76,114,103,17,180,181,66,25,18,91,27,251,247,134,114,249,22,78,231,121,214,153,247,29,63,171,241,196,214,244,138,40,61,129,255,
99,117,166,132,88,86,169,9,99,233,233,140,37,170,33,114,12,41,204,202,22,196,58,9,238,211,196,136,18,110,183,109,217,14,109,52,193,52,103,38,222,187,84,2,63,48,100,214,55,54,145,107,159,25,26,207,52,142,
117,189,201,2,226,72,42,38,155,108,184,136,1,35,74,46,129,72,186,44,84,218,1,47,98,94,231,29,246,21,179,180,21,69,113,83,231,196,250,47,170,105,101,35,131,150,117,84,245,7,61,36,17,168,75,130,148,5,81,
220,199,164,231,116,10,206,50,57,136,65,7,60,47,227,9,178,101,152,21,24,187,173,34,91,244,97,108,31,224,79,4,167,59,109,156,64,209,178,52,22,20,122,210,40,129,182,43,10,102,161,34,244,115,20,114,159,23,
70,150,19,29,148,47,249,38,27,173,166,236,71,162,98,246,71,200,146,88,155,205,102,236,51,74,34,53,214,43,186,137,149,59,163,219,133,139,133,129,21,2,218,10,60,39,24,52,78,98,116,191,227,212,131,248,99,
17,115,72,151,60,68,113,121,109,7,206,35,115,28,189,204,75,175,188,246,139,159,253,245,222,206,246,239,253,254,31,188,253,230,63,190,251,171,55,55,175,223,88,223,184,154,231,115,248,235,230,245,155,160,
194,176,22,41,80,108,249,107,242,63,121,156,147,115,186,63,216,186,110,173,62,130,240,48,18,58,112,228,18,164,158,66,237,168,78,154,58,140,162,5,51,148,162,159,133,39,185,198,216,7,34,75,86,196,16,51,
108,243,184,220,184,150,195,4,48,62,120,239,173,86,6,111,133,16,76,82,52,34,212,48,102,68,217,40,171,10,163,168,153,207,83,174,80,169,140,189,22,238,86,173,206,76,188,119,169,4,126,24,67,197,8,55,250,
134,103,30,39,112,12,133,22,255,129,225,132,198,49,148,145,151,130,241,254,200,178,178,193,76,6,224,251,181,194,214,188,154,106,14,221,130,192,198,149,205,7,247,238,32,191,254,254,62,188,133,87,95,123,
245,51,159,249,236,143,127,252,159,170,170,185,121,107,19,187,120,41,153,36,41,35,84,38,147,9,168,42,66,15,225,198,68,150,147,86,139,115,199,138,218,223,197,105,83,205,82,225,44,95,106,217,167,113,243,
114,5,255,243,224,116,119,50,100,28,97,55,197,26,109,77,7,236,246,254,38,218,110,117,117,126,10,127,46,60,132,143,10,81,148,77,153,137,100,38,230,108,61,165,105,11,38,12,251,50,96,180,1,3,232,34,16,96,
58,113,193,34,124,127,208,239,17,80,171,134,41,198,176,189,194,216,95,62,159,11,103,95,99,25,0,210,40,5,220,174,182,39,123,224,17,86,178,98,245,119,121,124,237,231,145,57,14,233,62,92,71,35,43,159,207,
214,55,174,128,97,245,246,155,255,240,202,107,191,3,50,183,94,120,105,145,47,62,124,255,29,216,28,224,177,127,246,119,127,143,139,93,133,88,34,176,79,206,233,78,39,246,73,145,238,141,14,226,72,51,81,47,
203,48,231,12,245,131,147,224,127,251,158,81,182,209,172,107,245,97,92,65,34,24,116,173,86,107,127,180,79,111,209,194,103,193,151,95,69,222,35,125,105,19,62,71,164,251,115,145,57,45,210,29,129,209,211,
40,200,68,212,174,196,52,101,222,119,24,188,219,31,204,38,227,166,17,131,193,218,31,255,241,247,127,242,147,159,192,64,215,175,95,93,96,135,103,203,105,65,222,125,144,101,153,116,177,203,56,73,134,107,
155,112,107,190,202,84,166,115,4,205,229,41,87,30,178,179,67,188,32,182,18,149,93,87,237,218,151,114,179,98,76,59,98,20,111,105,242,92,206,76,58,21,25,218,162,94,142,100,184,114,249,85,127,243,2,184,207,
217,131,156,202,89,95,246,66,49,33,12,7,134,240,214,241,120,248,24,222,210,120,50,3,127,240,211,175,190,250,185,207,125,238,199,127,241,159,192,40,185,121,253,10,56,218,12,209,164,166,18,37,51,249,49,
247,52,252,192,46,104,247,250,158,146,55,84,33,104,195,145,152,120,78,247,211,35,221,159,133,204,83,144,238,95,250,242,87,88,239,129,211,247,226,139,175,120,153,87,94,253,44,216,95,171,57,200,63,252,215,
255,118,117,156,147,115,186,139,211,32,221,225,10,112,32,36,49,28,55,146,101,224,132,46,203,130,106,14,36,151,110,97,229,23,66,33,201,68,48,150,172,157,43,171,44,186,119,145,39,113,188,176,52,143,168,
149,192,151,177,160,36,76,112,128,115,217,44,74,227,40,141,158,17,210,253,146,42,10,78,35,115,58,164,59,57,219,74,23,113,152,46,244,34,131,249,99,181,178,182,182,113,247,227,143,178,44,253,225,15,255,
228,209,214,214,207,126,250,211,193,96,64,150,2,1,255,200,16,14,34,60,243,149,229,60,3,75,57,90,95,191,74,80,70,95,50,84,7,233,188,41,82,99,86,216,216,150,189,67,133,71,195,251,252,218,145,222,223,101,
32,221,89,198,82,30,241,233,232,176,218,30,197,142,48,72,235,75,106,23,146,61,151,79,10,31,78,197,108,32,123,93,211,217,215,35,246,251,162,56,233,244,250,88,246,208,136,225,218,198,247,240,120,248,111,
240,167,205,205,43,96,204,150,176,73,36,247,30,198,42,162,12,225,138,182,5,60,104,177,254,112,131,58,39,104,70,169,180,77,11,46,11,151,16,43,85,83,151,212,118,224,60,50,151,133,116,127,249,51,95,176,54,
60,201,112,169,42,250,219,42,96,25,114,253,24,57,118,10,164,123,81,42,234,86,82,54,77,155,101,122,189,33,152,123,58,208,240,134,210,52,229,204,81,76,43,9,11,53,49,16,89,73,7,115,231,212,247,163,173,221,
27,55,174,11,10,217,48,123,172,162,2,84,190,86,24,161,195,219,84,225,179,68,186,95,94,69,193,201,101,200,172,96,122,101,17,56,82,132,128,146,113,90,104,223,192,145,101,216,46,194,247,59,239,69,217,110,
216,219,205,119,6,204,0,243,225,175,223,3,79,228,91,223,122,29,182,202,159,255,223,127,6,14,120,146,198,26,1,53,72,201,199,177,85,174,50,227,255,102,105,54,24,94,17,62,78,76,175,33,28,140,16,191,50,105,
113,212,124,89,146,134,62,123,99,85,26,85,148,128,78,106,44,158,235,176,103,199,12,206,151,52,147,236,34,48,224,45,164,200,169,5,73,82,70,7,25,68,241,219,1,193,163,144,54,15,183,159,88,22,30,98,228,202,
97,119,142,247,73,145,102,15,28,58,202,29,207,76,222,87,221,137,158,112,3,90,184,135,254,96,253,206,199,31,129,125,250,195,63,249,119,219,219,219,63,253,233,207,6,131,62,53,172,67,202,4,134,47,184,142,
63,112,186,71,84,93,30,128,118,115,197,125,28,141,147,160,176,38,102,86,99,61,252,137,57,221,47,179,53,193,147,100,158,39,210,157,115,0,167,66,186,151,101,203,152,176,223,155,62,124,152,177,12,178,196,
80,183,181,8,225,48,37,162,222,179,108,58,155,9,238,21,228,28,61,204,15,112,67,103,100,62,137,199,227,113,183,215,225,242,142,245,141,77,31,187,1,153,94,119,6,59,23,70,10,148,120,102,72,247,79,130,76,
64,204,150,220,181,152,120,136,16,121,232,209,240,14,240,25,176,12,146,25,48,167,123,213,52,59,237,108,109,146,14,102,213,184,167,132,202,231,243,23,110,223,254,226,151,190,248,31,255,195,127,128,89,237,
247,251,48,121,13,86,2,90,102,209,192,197,224,97,235,116,187,131,36,107,107,7,255,226,211,61,238,79,130,72,45,246,135,240,2,233,208,90,182,237,195,28,191,109,81,185,68,195,147,5,116,148,103,119,209,156,
238,79,164,60,230,44,62,33,212,81,143,83,85,171,98,42,42,219,132,70,209,157,51,24,217,17,165,58,158,206,147,213,195,227,197,118,197,62,104,150,107,114,243,129,122,200,212,87,31,191,247,14,28,40,175,191,
254,53,24,240,207,254,252,63,118,58,237,52,75,25,209,198,185,44,80,80,158,37,25,62,130,67,125,184,118,149,8,151,169,232,135,212,253,245,224,90,40,130,7,102,75,158,138,211,253,121,68,54,158,39,210,221,
147,154,157,28,233,14,159,128,170,25,12,246,149,26,54,58,96,153,222,96,184,183,179,147,165,105,158,231,5,69,73,90,24,187,197,56,36,7,101,109,217,45,37,194,254,240,251,127,8,111,226,63,255,231,255,7,140,
42,112,91,16,44,151,164,218,85,165,134,129,238,117,139,221,189,190,85,158,207,10,233,254,73,200,25,59,190,118,195,48,158,37,71,178,239,111,186,228,116,247,50,20,243,106,226,98,220,138,59,211,160,45,239,
191,63,5,123,228,123,223,251,254,63,252,253,223,127,244,241,71,183,110,221,94,195,198,130,98,54,155,228,216,41,14,175,24,68,81,2,187,42,105,91,166,40,203,205,98,231,59,104,77,69,184,88,140,59,6,15,123,
11,9,14,44,82,73,178,37,46,124,75,6,50,210,52,1,229,213,99,222,31,151,97,63,131,153,228,162,0,91,153,108,44,173,43,215,15,81,233,118,227,189,69,215,70,195,82,20,112,239,107,202,150,88,78,247,35,125,82,
158,124,28,199,200,45,185,125,85,92,25,234,193,142,216,131,249,204,23,249,139,47,190,248,165,47,125,241,207,255,236,207,4,34,144,59,120,237,48,160,111,57,58,46,110,160,173,100,191,59,108,181,187,13,221,
6,35,230,225,36,184,170,54,64,91,221,215,91,90,114,185,2,213,222,91,60,202,39,45,106,161,194,231,149,167,36,220,230,1,20,251,73,144,238,32,179,179,215,234,247,118,251,131,201,246,78,159,101,250,189,181,
5,56,132,51,228,23,229,250,245,197,98,193,123,12,45,133,166,137,225,39,138,74,106,111,251,230,155,255,244,163,31,253,47,119,238,220,249,229,91,111,130,133,252,226,75,159,230,100,48,95,107,56,156,194,45,
79,167,3,38,35,127,102,72,247,79,70,206,248,116,72,119,223,181,27,173,155,34,107,2,19,182,242,157,237,71,63,250,225,143,22,139,252,191,253,228,39,155,155,155,96,189,210,153,33,193,115,239,116,251,182,
37,17,179,98,185,6,95,196,118,205,198,136,142,123,19,21,149,245,60,171,23,73,32,45,27,154,175,115,118,156,116,82,91,226,36,19,34,36,201,176,76,35,154,195,158,29,5,230,47,117,38,217,241,36,229,136,55,149,
36,17,114,41,163,2,13,3,235,115,105,215,224,210,149,10,185,118,59,24,75,10,34,234,244,69,193,77,119,68,48,246,189,49,171,45,118,26,55,105,162,20,229,174,217,27,138,126,223,116,223,126,248,86,89,20,127,
244,71,127,244,143,255,240,15,191,254,224,215,183,95,120,97,125,253,42,140,50,159,77,231,243,41,17,51,232,32,196,22,68,105,214,142,66,44,159,230,50,67,155,247,18,102,77,14,82,19,111,235,157,74,150,180,
212,35,237,56,221,57,1,114,100,203,159,138,200,51,253,108,147,130,107,184,142,129,161,49,190,45,208,57,253,113,251,236,203,183,111,142,107,164,122,169,121,202,199,81,236,39,65,186,147,12,156,191,131,126,
111,60,153,244,235,90,177,204,218,198,53,33,31,54,99,4,215,97,57,4,153,141,13,183,27,145,130,147,83,220,209,254,238,221,187,63,255,249,207,223,120,227,141,123,247,238,86,85,137,185,231,36,227,107,133,
65,211,106,237,140,39,109,164,140,63,234,126,46,21,233,254,73,200,25,159,10,233,78,196,146,146,216,214,81,37,233,69,103,188,187,120,229,149,87,174,93,219,252,191,254,253,191,239,245,122,215,111,190,224,
136,31,2,55,135,152,244,160,254,221,22,133,164,108,227,76,172,44,9,123,99,16,172,38,189,106,129,17,235,70,48,85,174,99,29,192,67,203,218,212,33,23,253,147,223,202,24,59,91,185,118,208,107,131,67,232,162,
56,221,143,145,105,232,70,224,146,139,197,252,163,15,223,175,42,140,214,109,110,222,232,118,251,202,106,120,31,168,117,133,193,232,60,114,21,78,99,171,6,44,122,145,108,139,64,249,162,125,158,49,71,177,
192,58,65,206,101,14,54,81,87,118,118,119,182,255,228,135,63,132,195,250,175,254,250,175,175,93,187,182,177,113,157,53,94,187,219,235,246,6,12,171,118,84,235,140,34,92,142,3,11,123,83,94,73,68,60,22,211,
92,45,216,148,110,76,237,100,140,191,159,208,67,212,29,199,188,229,98,183,5,131,43,36,144,246,68,162,182,64,231,244,181,89,127,53,154,59,235,176,1,11,147,20,124,245,155,175,31,73,234,122,18,226,215,243,
200,48,244,134,251,14,9,15,77,116,245,98,246,8,127,130,204,108,158,14,134,163,118,107,186,191,223,245,50,237,118,183,172,138,18,217,54,152,160,9,243,79,12,41,70,128,28,70,27,17,232,3,83,249,240,225,214,
173,91,55,95,122,249,197,127,250,167,127,106,154,170,219,235,243,181,62,117,251,94,20,138,123,247,175,27,33,143,188,159,243,60,59,172,230,36,203,206,54,135,22,26,238,250,178,40,207,45,171,44,49,163,157,
156,131,50,136,111,194,30,168,130,195,219,71,202,28,51,14,173,64,139,56,97,153,96,69,134,92,177,144,115,136,74,17,166,220,232,221,237,221,239,125,255,123,96,91,109,239,109,191,252,218,53,169,35,196,223,
218,150,209,54,239,100,179,143,12,230,166,107,193,86,2,211,44,234,78,48,70,57,238,233,50,86,92,125,34,151,140,186,94,149,186,63,201,149,226,147,21,38,130,131,141,106,22,197,34,138,226,203,91,213,218,53,
89,0,139,254,238,221,143,70,251,123,240,133,86,43,235,116,123,11,228,153,202,200,80,178,52,88,1,101,51,125,104,201,69,71,151,5,101,174,42,152,18,202,202,178,232,241,166,101,40,45,170,9,201,8,106,89,128,
157,53,219,25,172,247,191,240,249,207,255,197,95,252,69,146,164,215,111,188,192,230,158,151,225,249,176,117,133,130,58,87,184,80,12,40,243,171,114,35,145,201,174,216,159,201,217,145,50,114,121,63,142,
239,193,88,180,144,112,145,22,75,45,224,90,26,45,65,75,126,16,231,71,43,71,109,239,32,190,78,35,186,82,177,85,25,98,122,52,220,73,232,16,77,243,111,36,167,123,168,226,121,158,245,251,147,52,41,39,211,
150,151,233,180,123,73,146,228,200,97,96,119,41,129,229,64,91,5,92,134,6,67,116,218,237,233,108,250,206,187,239,124,235,91,175,183,91,173,119,222,121,167,63,28,130,46,219,220,124,16,199,197,157,187,215,
136,13,240,121,114,186,63,46,163,28,81,63,219,198,194,83,173,184,74,26,27,146,240,84,103,90,44,230,179,15,62,120,239,193,253,251,251,251,187,73,156,132,113,124,72,230,36,227,28,43,99,177,81,104,192,115,
192,168,105,190,250,181,175,204,243,252,231,127,251,243,215,62,191,25,182,138,176,181,48,170,228,54,227,182,88,159,185,186,173,123,89,71,177,137,58,121,216,153,132,113,211,148,73,57,106,235,58,88,242,
14,211,158,11,9,70,228,154,175,248,109,227,2,71,150,133,210,214,57,31,98,70,71,118,186,11,226,116,63,82,198,18,171,63,218,122,248,240,62,120,64,96,194,103,173,12,137,24,231,243,2,92,181,69,14,142,176,
100,8,136,163,133,230,126,81,228,80,106,199,242,188,52,105,221,241,168,125,79,33,230,53,151,203,6,123,30,39,39,118,246,30,126,239,251,223,255,201,223,252,205,206,246,238,231,63,245,197,70,214,70,174,244,
142,18,203,10,183,21,21,36,66,25,246,101,111,67,173,129,236,150,121,148,139,197,227,50,43,173,172,156,255,43,150,62,50,147,255,177,245,165,56,251,200,28,255,254,246,25,106,183,148,113,111,68,30,232,195,
22,50,135,31,235,62,75,95,47,153,233,44,122,2,5,51,106,207,223,68,78,119,226,222,83,224,100,12,6,147,48,208,160,188,188,12,118,196,233,15,226,36,229,54,98,73,76,153,92,132,249,42,216,183,73,154,110,92,
189,214,106,117,198,227,209,253,251,247,191,241,205,111,222,189,119,239,225,131,251,159,253,76,208,237,204,31,109,175,23,69,247,248,251,121,6,156,238,71,201,8,38,226,208,220,212,212,53,118,231,146,200,
56,140,89,131,176,204,108,54,189,123,231,195,61,56,237,141,233,116,58,221,110,119,62,159,245,186,131,0,119,181,57,249,56,199,203,144,227,162,124,80,139,205,207,217,116,254,246,91,111,129,55,36,234,86,
53,143,225,251,113,90,7,41,104,174,60,108,205,195,116,17,38,37,253,115,158,118,23,81,171,84,201,66,192,107,92,180,202,113,87,23,9,53,40,165,58,18,203,63,163,136,98,144,120,86,131,160,113,86,143,107,140,
196,198,26,58,125,236,155,112,143,181,213,37,14,58,163,213,106,95,198,170,182,152,137,170,128,197,195,61,156,58,84,148,183,63,26,85,85,197,116,239,240,203,70,255,74,43,200,18,147,180,101,171,35,59,45,
153,165,42,73,68,132,133,25,34,180,133,4,210,182,135,113,173,54,181,107,160,45,125,137,56,99,128,56,135,192,90,186,174,43,60,30,230,249,223,254,237,223,126,249,229,47,119,68,187,39,58,145,136,75,93,185,
154,30,11,244,103,221,173,140,138,69,52,144,253,53,217,143,76,56,51,243,29,177,95,137,154,170,23,194,149,134,128,102,137,219,112,54,38,225,84,169,255,41,85,187,163,119,79,172,226,7,185,216,61,95,187,226,
152,221,10,95,123,99,108,248,206,243,181,7,92,59,25,146,45,233,187,145,158,196,236,149,255,219,255,254,127,48,104,240,184,46,205,214,152,191,72,25,219,51,219,21,85,16,44,115,217,179,192,183,209,56,94,
102,109,109,127,109,48,6,133,181,181,181,73,157,178,15,203,56,11,213,4,212,31,208,143,51,157,79,223,121,235,205,175,126,237,107,95,248,194,23,254,244,79,255,244,119,63,31,166,201,112,119,127,120,252,253,
216,74,250,51,61,251,104,180,215,237,13,206,54,135,190,30,210,69,58,172,75,229,26,56,185,54,178,70,108,109,221,223,219,217,134,251,110,181,90,96,108,86,84,19,132,108,153,73,118,251,133,79,9,151,247,124,
234,56,79,149,65,162,75,46,51,32,135,157,99,208,72,164,231,252,104,42,23,167,174,19,113,133,129,68,165,165,106,176,10,16,109,51,133,255,215,128,67,170,154,50,90,45,60,61,80,36,232,143,120,87,10,207,173,
0,61,210,253,144,216,161,250,100,24,106,180,183,211,31,174,95,210,170,6,75,233,253,247,223,89,228,57,178,146,102,25,120,133,190,34,205,69,214,69,28,38,223,252,244,235,24,92,147,186,54,88,10,30,137,144,
125,31,122,30,51,49,211,169,153,17,51,159,53,217,144,178,147,160,103,182,124,141,11,161,176,62,52,214,200,168,100,20,229,28,224,26,89,150,62,120,112,111,48,88,67,213,64,64,170,174,234,42,27,34,194,86,
210,21,214,48,25,240,254,64,201,114,173,110,101,170,185,92,140,245,132,194,234,204,5,104,173,105,60,212,9,21,140,20,52,82,249,217,110,176,17,178,117,78,201,18,178,149,210,43,157,19,86,249,218,37,49,247,
55,108,167,123,95,242,8,78,119,246,27,200,188,114,125,237,113,18,176,222,139,53,160,43,183,228,250,25,79,45,29,188,254,198,191,122,106,151,230,147,116,114,62,181,76,83,115,147,46,142,149,90,142,68,95,
32,70,46,117,195,124,216,79,150,89,228,89,81,170,126,111,212,110,195,97,211,170,42,115,72,134,131,55,214,54,94,25,39,137,227,52,203,222,123,231,237,151,95,126,249,246,173,219,255,245,175,126,153,182,110,
61,245,126,52,177,154,157,237,217,171,178,4,11,239,108,115,184,164,178,162,51,199,55,52,165,6,4,92,149,109,96,252,173,135,247,246,247,118,85,0,214,34,54,113,152,140,39,212,252,164,38,132,71,213,27,180,
194,180,81,81,25,196,121,152,149,113,86,171,176,12,34,131,72,76,234,78,96,225,5,230,233,215,18,4,224,100,244,175,109,147,73,129,25,135,22,98,14,81,219,176,69,232,80,234,216,212,177,172,83,93,166,85,30,
214,69,168,235,184,174,148,182,229,9,92,77,229,1,237,174,126,87,58,254,14,207,200,33,150,121,58,219,43,140,140,223,3,72,247,21,175,13,44,172,118,171,125,225,171,154,31,243,221,119,223,2,19,12,84,21,216,
29,54,43,45,172,105,192,149,198,100,157,53,115,149,87,109,61,54,147,137,70,221,52,17,147,137,152,206,196,188,144,101,32,84,91,116,64,203,68,34,42,69,101,28,137,176,173,34,56,216,107,221,70,116,109,189,
20,222,4,156,69,220,63,130,117,20,12,8,234,175,148,85,41,202,18,94,168,36,82,117,105,42,89,207,117,62,147,243,169,152,239,139,81,33,10,7,217,118,28,160,228,141,57,164,136,239,242,173,124,94,152,143,40,
46,206,12,172,143,236,190,40,184,230,215,120,94,114,169,172,15,235,42,207,133,171,20,182,45,11,57,198,192,207,72,157,71,78,103,246,6,95,255,214,27,231,111,143,126,38,25,219,159,154,205,123,233,89,77,168,
207,2,47,184,224,4,50,77,3,135,91,171,215,155,246,122,35,236,112,89,69,141,61,174,142,27,71,169,250,218,181,242,246,109,243,95,255,242,237,63,248,234,87,178,86,182,179,189,147,101,173,227,175,117,158,
103,135,205,115,230,86,245,236,230,48,88,12,161,40,84,161,109,41,177,41,147,101,154,250,131,15,222,35,198,165,176,221,110,99,43,224,170,241,237,54,121,73,79,39,147,43,47,130,47,82,8,202,244,193,194,138,
98,35,163,66,197,101,148,149,232,160,97,49,102,64,52,150,199,93,139,177,154,182,1,143,75,137,240,254,244,143,35,45,73,128,240,157,184,2,107,41,52,202,53,74,167,6,156,75,2,82,193,113,91,7,31,102,181,137,
9,7,59,243,150,220,134,130,74,220,118,66,48,237,1,131,87,228,81,75,188,44,138,32,14,47,116,85,19,137,13,181,108,24,147,211,93,131,13,219,52,129,69,186,27,203,255,107,85,44,226,93,243,197,172,215,239,135,
20,148,97,154,115,116,121,4,22,213,207,68,62,49,200,10,223,18,89,203,164,133,40,193,73,180,205,102,72,81,242,93,29,169,76,217,35,54,214,50,90,54,103,171,116,85,152,114,161,243,133,88,192,248,11,185,152,
155,188,9,154,90,54,88,198,111,185,183,44,99,132,56,56,14,179,3,176,194,109,156,187,39,168,146,148,142,46,59,49,154,8,81,217,217,100,142,45,110,150,99,156,132,39,56,133,169,227,163,206,181,246,230,234,
78,94,33,94,11,91,45,230,22,216,97,77,205,212,201,75,153,111,188,254,70,77,212,180,22,113,179,100,58,180,153,35,230,6,185,112,25,207,194,203,40,118,38,66,180,8,70,38,237,101,172,224,9,100,234,58,152,78,
219,97,208,244,251,211,225,96,146,166,240,130,67,108,184,210,136,67,227,192,186,74,211,242,202,250,254,213,171,123,89,86,106,221,77,146,43,191,252,229,175,190,249,205,111,110,109,109,49,224,232,169,247,
115,182,103,71,42,209,40,60,219,28,82,241,144,77,30,89,58,93,75,84,108,183,247,251,239,189,163,27,60,237,185,49,1,135,117,133,17,203,158,128,148,175,50,101,43,150,87,76,209,214,101,214,44,210,106,158,
212,115,248,37,107,74,236,17,64,209,165,133,66,118,159,24,91,167,28,117,45,79,165,197,44,192,194,173,108,101,83,127,54,205,195,181,1,110,181,17,26,142,99,239,66,185,19,53,224,24,185,39,23,94,233,29,35,
132,176,133,92,20,97,9,28,88,212,217,80,14,233,78,121,96,166,217,10,236,130,62,184,196,177,99,88,154,93,224,170,182,22,40,27,65,70,228,249,220,88,82,252,154,3,45,122,89,11,233,246,24,150,103,148,253,193,
144,122,73,4,62,43,200,37,190,112,137,82,85,160,86,90,50,235,152,54,232,148,70,53,198,242,76,132,100,233,31,161,76,173,241,235,122,225,80,220,58,112,164,26,75,82,217,147,203,68,79,184,150,139,21,178,239,
31,218,174,219,142,125,204,113,84,216,19,199,170,44,199,231,197,138,158,91,144,121,195,205,184,66,84,139,163,62,189,217,251,220,144,238,71,162,216,79,130,116,63,82,70,235,120,119,247,250,222,94,217,237,
141,251,221,105,251,218,3,203,178,208,4,117,141,241,248,40,132,151,161,41,247,7,10,78,237,239,15,198,99,176,119,48,11,150,182,212,95,254,229,95,249,254,142,199,93,235,57,33,221,27,91,117,188,42,99,67,
75,28,253,141,136,243,155,161,82,150,45,64,44,169,114,249,196,135,247,188,187,189,211,239,175,51,89,194,114,28,76,222,196,186,138,117,46,163,180,136,210,89,148,78,22,163,142,46,131,199,175,197,214,126,
99,117,135,109,6,177,74,80,185,130,134,247,205,196,108,85,141,109,5,226,66,245,180,106,27,182,38,44,33,172,237,56,109,227,81,172,54,26,226,177,9,60,214,89,60,134,135,166,78,34,168,187,46,31,233,174,86,
240,179,107,27,87,103,179,9,252,248,102,101,210,90,22,92,134,73,61,126,144,182,91,231,243,249,124,58,198,234,11,206,235,83,57,79,192,253,147,233,167,146,230,190,120,116,69,173,93,17,27,99,51,30,201,41,
185,14,245,241,77,52,20,151,11,115,29,110,227,168,251,132,98,10,18,110,23,18,172,160,136,52,54,40,241,50,194,134,228,104,255,28,73,16,122,168,252,168,214,21,102,90,200,10,35,158,45,201,188,239,108,46,
227,119,176,150,77,61,5,102,21,90,206,168,51,3,74,67,241,188,126,28,242,130,58,17,4,92,155,102,131,171,194,247,172,61,157,140,148,241,104,180,182,179,219,203,210,60,12,155,32,104,224,191,81,132,254,66,
158,103,176,242,171,10,22,86,52,3,203,194,142,211,48,52,70,156,240,90,207,233,7,61,142,21,82,115,177,242,236,108,150,247,250,131,157,157,71,130,233,86,168,196,204,183,123,88,153,112,68,244,220,187,251,
241,237,23,94,60,122,156,198,148,179,84,21,73,216,221,79,250,163,98,220,170,23,241,227,215,98,75,129,74,73,78,161,130,109,253,160,87,193,154,84,149,228,113,108,82,140,227,101,204,252,205,152,105,113,50,
60,52,121,100,250,25,32,221,237,108,8,11,121,1,187,169,40,75,110,104,162,87,186,174,115,33,33,187,132,240,5,176,121,31,110,61,72,147,68,18,203,24,21,216,135,221,110,191,213,234,48,83,130,109,134,100,118,
251,162,215,21,221,74,215,200,154,96,108,51,247,39,30,129,238,56,89,133,59,173,96,44,81,89,215,254,200,33,171,245,208,56,100,66,157,76,113,211,3,34,34,144,208,249,248,92,66,171,21,184,134,179,40,205,49,
135,1,243,166,136,243,21,120,6,223,248,214,27,17,43,123,238,88,187,2,99,89,125,109,23,46,19,40,7,53,147,182,25,140,175,46,12,195,128,129,54,234,172,50,117,29,149,101,90,215,237,233,44,157,78,90,243,121,
55,159,183,242,34,45,171,164,42,131,51,95,43,56,199,179,83,159,130,238,217,230,176,33,156,180,113,92,207,216,205,204,70,31,236,114,201,90,173,249,108,186,40,22,236,189,178,75,101,150,125,55,132,99,134,
65,195,63,75,211,40,10,97,147,59,64,141,244,227,144,173,42,234,69,34,195,26,221,67,108,56,149,30,186,150,112,61,4,97,102,78,248,198,249,95,17,199,128,184,107,161,176,33,15,185,218,124,204,6,53,140,247,
199,79,232,181,73,55,51,135,100,170,178,104,183,59,71,194,121,158,218,117,253,9,50,156,57,181,74,17,252,77,73,223,170,107,108,238,194,206,175,103,58,246,77,67,24,171,20,70,81,141,149,226,228,221,80,111,
36,56,99,224,67,162,51,228,195,64,231,98,145,202,184,43,58,11,177,16,1,219,164,148,218,191,160,29,231,80,117,236,156,157,102,28,183,234,152,210,86,58,220,175,141,69,122,71,231,201,99,18,33,93,83,55,150,
105,227,16,196,151,55,157,177,212,209,230,24,153,224,141,239,254,209,145,175,205,183,117,98,40,4,113,129,6,202,130,47,140,71,12,156,65,134,176,60,146,78,45,45,237,251,183,33,67,34,71,66,43,154,0,26,159,
68,153,51,47,253,170,172,16,104,127,186,237,97,101,180,91,250,8,131,193,162,51,91,238,207,46,143,102,118,112,41,202,162,16,142,245,208,70,127,108,205,176,53,0,28,205,121,93,21,197,124,54,219,223,223,157,
83,247,67,46,12,48,220,137,148,137,134,139,20,206,180,184,83,129,249,31,152,228,208,181,150,236,236,90,159,228,137,56,228,76,179,103,195,34,46,57,238,54,191,205,40,186,165,185,194,46,127,252,242,245,80,
33,171,29,46,31,233,206,60,242,198,97,244,94,106,191,180,53,219,66,182,24,34,98,179,222,152,3,84,58,72,183,169,171,26,252,66,138,233,216,182,190,84,46,6,42,117,49,157,142,210,172,77,113,64,188,233,185,
200,7,97,127,16,244,247,245,152,222,160,160,68,239,133,41,92,237,117,238,105,198,193,186,72,219,134,218,48,242,94,89,255,87,248,24,41,67,97,143,28,211,183,95,56,191,221,115,68,105,78,224,16,241,140,112,
21,182,67,239,210,81,231,108,145,180,85,96,167,150,89,105,76,160,92,246,91,172,114,3,120,252,254,39,80,230,185,148,230,56,238,4,182,77,140,112,155,213,193,89,113,218,179,52,67,14,33,170,253,54,46,238,
96,220,86,63,216,195,202,80,149,120,197,157,105,26,248,78,85,142,246,246,224,180,143,147,36,176,188,87,166,41,99,25,86,97,182,104,138,8,188,175,213,107,217,190,231,150,240,243,233,79,100,56,217,191,50,
195,218,114,155,88,227,139,65,64,194,50,121,26,7,100,63,169,17,129,45,185,142,146,185,36,164,187,177,145,31,185,46,135,216,87,167,23,23,101,206,205,174,93,59,50,237,236,48,12,243,160,163,42,12,236,122,
67,29,12,16,177,101,44,49,105,133,133,210,240,6,202,118,167,43,92,76,106,166,103,45,147,69,50,156,155,57,245,16,149,234,220,10,151,251,15,210,56,56,73,167,31,199,248,206,225,240,253,165,83,98,115,121,
60,235,79,30,19,139,58,163,51,105,216,199,144,238,175,127,251,187,156,215,84,54,122,109,109,117,195,88,123,146,163,102,231,129,182,157,20,206,43,115,8,83,251,12,202,128,62,9,50,231,41,205,17,54,71,35,
172,97,79,127,214,14,31,204,246,6,56,89,107,183,244,120,167,162,234,98,237,108,16,23,100,88,178,54,26,80,80,112,218,19,14,129,59,113,152,162,44,48,72,92,87,243,217,164,213,238,249,107,137,42,11,146,69,
144,205,203,89,162,87,170,40,180,77,189,43,143,9,58,229,134,55,17,246,251,11,29,129,162,100,176,152,79,160,89,68,197,105,140,8,102,125,122,6,72,119,251,68,176,111,101,176,38,7,251,205,24,108,162,86,187,
99,154,106,62,103,182,117,97,105,252,196,50,147,239,146,33,22,120,74,134,35,126,66,76,185,72,142,11,222,107,171,221,181,113,32,114,138,59,162,61,21,115,198,154,157,127,101,154,131,243,127,218,113,200,
182,226,98,111,106,122,64,132,151,14,233,206,198,242,49,69,120,226,2,75,146,131,175,124,253,155,54,167,232,90,140,192,10,112,85,75,116,54,82,199,202,139,149,121,246,101,64,207,93,230,124,165,57,54,114,
164,217,215,182,253,198,45,158,155,25,41,226,222,76,69,77,26,110,44,242,156,75,252,133,49,142,5,13,225,206,236,130,5,212,77,147,93,60,236,231,88,115,139,20,92,103,13,89,103,224,46,194,246,211,196,116,
136,31,22,113,212,42,130,200,152,50,241,215,34,14,3,106,131,70,240,90,238,198,206,201,1,233,128,164,199,63,17,66,112,201,141,213,174,54,216,161,79,37,91,100,167,91,226,22,91,127,88,134,43,144,143,134,
243,156,4,242,115,148,140,112,0,206,190,236,37,34,222,21,123,28,195,73,211,4,38,143,121,65,172,53,108,239,205,172,4,242,53,147,217,187,230,67,56,242,98,145,39,81,194,165,136,113,156,16,71,110,189,208,
69,79,118,209,143,86,21,23,27,176,149,117,230,149,169,92,109,9,203,112,252,239,36,227,112,67,3,191,115,217,151,52,14,170,206,174,24,27,200,79,186,174,107,11,123,49,103,127,240,245,111,125,219,70,61,165,
109,58,112,40,149,199,168,155,167,200,8,241,116,153,149,113,140,107,232,121,81,203,232,147,47,83,148,11,220,60,103,29,71,58,231,84,186,190,141,54,214,108,251,104,153,164,59,35,68,85,220,237,118,225,192,
158,205,102,190,82,223,134,184,237,89,167,125,90,202,162,197,181,245,50,145,65,52,64,18,247,170,42,225,180,119,232,26,188,50,58,134,121,38,28,138,74,90,38,117,31,194,149,190,220,159,41,250,232,150,144,
216,151,242,251,71,60,17,40,172,128,49,16,14,32,47,207,122,248,135,138,233,71,164,121,76,230,82,144,238,46,62,176,38,134,11,177,152,171,220,225,197,208,198,131,169,155,207,115,230,149,102,210,100,15,43,
241,237,21,24,29,65,125,155,235,56,137,217,95,35,135,177,105,119,122,22,233,174,68,44,147,150,204,38,98,106,219,57,251,178,161,51,173,76,155,233,118,59,14,97,9,39,28,103,5,212,178,130,116,95,150,142,172,
32,221,31,191,174,77,144,92,224,217,31,124,253,155,223,214,28,13,97,126,2,215,197,108,137,147,102,111,251,9,50,251,163,221,111,124,237,43,247,30,220,131,15,78,59,14,91,147,207,162,12,232,19,32,115,158,
210,28,150,225,51,141,147,53,129,197,37,215,22,135,153,206,68,80,228,251,45,66,2,4,184,75,235,162,174,106,54,97,26,23,46,215,142,150,79,88,230,3,13,158,20,124,187,198,166,33,134,90,225,230,112,254,87,
85,21,99,60,43,229,107,41,19,199,237,18,227,190,85,228,186,177,89,232,61,65,19,148,171,1,148,54,214,193,118,147,13,42,133,71,62,17,88,119,90,92,156,121,139,155,199,60,19,164,187,5,52,196,58,238,200,214,
142,217,111,4,18,123,70,200,180,83,63,122,244,48,73,210,170,172,40,182,238,76,172,101,234,73,120,178,49,143,56,231,146,61,205,115,106,116,146,165,68,84,192,233,169,186,167,186,11,234,238,197,190,36,247,
245,181,165,230,30,13,143,52,36,170,57,118,69,85,139,98,235,193,253,52,75,45,217,30,217,206,135,100,96,156,199,81,245,254,182,217,48,119,140,58,171,72,119,237,145,238,92,135,120,112,204,224,194,207,254,
144,237,76,242,251,235,0,245,188,240,149,250,182,60,197,193,151,143,148,1,7,164,226,166,116,84,252,114,134,113,62,81,141,24,46,79,230,156,77,40,228,74,230,152,187,180,99,255,40,202,24,98,242,37,43,170,
34,166,130,86,134,84,6,107,195,53,88,114,163,209,62,120,25,200,204,238,90,108,46,11,194,209,19,12,26,91,186,132,64,103,112,73,192,41,44,138,34,77,146,241,120,191,213,233,249,107,21,121,144,180,43,179,
8,220,78,211,24,221,22,202,150,143,113,121,7,1,176,109,224,146,243,232,180,218,142,124,34,58,225,47,140,249,155,35,220,207,134,211,157,29,242,36,136,2,162,250,98,189,137,97,243,124,14,215,135,9,7,179,
142,154,127,49,170,91,58,140,180,207,63,27,62,120,92,182,14,253,41,46,154,129,39,218,217,217,190,125,235,83,248,32,184,36,80,141,129,113,21,184,86,44,228,157,213,130,8,206,88,6,222,32,55,13,241,237,90,
142,92,81,181,170,34,228,45,137,125,255,61,38,107,166,94,207,122,117,213,81,172,202,106,11,202,11,227,51,4,52,201,8,130,225,182,234,194,39,70,4,199,182,248,133,146,202,213,254,186,160,1,145,152,244,162,
169,147,67,182,165,153,14,130,79,70,139,142,118,228,211,210,165,156,188,76,99,116,17,102,96,197,130,166,157,21,191,166,35,199,60,106,100,218,234,72,221,196,210,168,106,97,78,48,142,187,214,111,97,67,135,
139,149,1,67,71,185,122,49,162,214,169,8,49,46,57,245,19,38,26,222,179,41,51,38,24,162,217,214,187,123,187,9,242,66,199,117,89,211,234,180,156,15,190,217,7,55,85,231,184,8,157,240,13,88,100,216,100,5,
255,127,83,44,138,69,62,79,179,22,95,171,89,164,65,60,50,65,46,155,140,203,201,109,170,206,173,36,203,52,233,32,236,130,106,47,56,2,125,232,137,238,221,185,147,181,90,107,27,27,23,203,252,253,204,56,221,
121,250,34,25,113,119,101,247,82,196,60,159,107,124,64,21,70,49,110,236,134,241,96,190,73,188,89,101,182,211,220,56,131,10,182,194,78,135,24,18,240,146,224,81,26,75,147,32,16,89,174,100,44,162,92,47,252,
139,99,133,226,101,140,109,151,233,141,53,233,9,66,193,246,156,78,198,12,82,197,150,209,73,90,87,21,92,206,122,63,18,65,100,81,148,228,249,12,219,74,73,217,106,117,66,74,200,250,50,102,71,6,107,248,84,
179,166,147,123,35,92,80,121,0,233,78,239,93,44,203,158,13,23,42,92,236,217,31,82,251,73,11,204,19,118,1,112,227,120,100,159,224,208,38,43,27,92,16,70,206,146,206,60,233,105,11,145,55,213,34,175,75,108,
209,49,217,221,205,135,55,185,254,59,72,117,175,158,119,138,89,64,136,197,199,199,121,236,90,194,210,123,63,239,70,12,151,39,115,206,38,20,76,92,161,87,8,79,184,168,152,35,224,152,199,16,73,195,109,129,
180,46,22,51,216,50,179,217,184,196,62,192,92,28,203,36,194,106,137,155,113,173,224,184,30,140,123,11,17,239,154,141,97,239,238,109,95,75,110,242,181,12,242,157,192,86,4,21,73,80,3,100,34,175,192,196,
96,74,0,87,195,39,93,71,9,234,193,35,131,134,145,212,244,68,91,247,238,36,89,182,190,126,181,211,233,32,185,184,214,23,104,222,62,51,164,187,43,107,86,204,102,229,149,117,128,209,171,138,107,176,125,8,
68,73,233,182,186,180,68,56,142,49,137,227,39,134,10,116,140,99,87,97,131,133,108,26,205,102,99,141,76,23,161,11,246,121,134,10,142,221,89,25,79,215,185,42,3,191,60,122,120,31,70,110,119,186,148,74,105,
198,251,187,9,88,208,104,10,150,139,197,34,138,194,193,96,109,111,103,155,88,143,250,211,201,100,54,153,108,222,184,69,13,181,56,50,24,24,151,202,96,68,60,162,145,15,190,17,111,94,121,164,187,77,244,90,
254,197,128,180,231,5,159,235,33,187,21,75,246,72,110,70,164,44,171,180,36,47,20,251,175,138,96,39,233,206,194,22,8,101,229,188,83,205,224,28,1,51,105,172,117,12,51,145,166,225,244,131,79,77,239,213,112,
18,170,104,26,119,246,130,246,94,187,211,174,23,131,98,20,160,61,16,120,174,165,35,175,101,108,173,30,101,190,148,51,157,137,83,201,194,150,13,27,213,182,160,235,55,78,38,64,170,185,232,108,227,8,219,
47,134,242,75,238,160,166,181,209,80,247,26,180,161,170,138,163,221,40,3,122,138,227,60,1,247,2,112,177,18,185,10,211,20,164,190,60,184,17,188,251,69,222,233,118,113,215,97,146,81,139,162,100,211,134,
64,89,188,112,43,173,41,140,133,132,24,74,251,238,208,46,68,227,3,151,28,70,225,160,44,108,248,201,100,60,159,207,97,253,37,81,226,27,166,205,70,251,81,28,97,179,79,33,90,157,206,108,58,133,27,234,15,
215,96,105,194,253,99,139,29,41,97,191,233,160,121,234,18,23,22,136,255,44,56,221,57,108,135,202,72,54,76,215,204,158,16,179,86,212,4,45,38,206,87,45,44,70,84,120,138,28,218,201,168,114,228,10,57,181,
253,144,158,1,115,187,22,139,130,248,87,176,211,20,23,249,8,113,85,172,99,158,65,54,28,8,183,209,162,64,153,21,184,57,252,60,50,59,116,78,8,80,133,69,158,207,167,147,222,96,168,109,181,131,30,12,215,38,
227,17,188,232,193,250,6,8,141,71,251,112,219,96,121,129,254,2,227,174,42,11,25,39,174,224,97,201,49,79,97,202,163,138,4,57,15,40,3,225,225,45,46,232,192,165,157,151,113,246,135,13,37,182,125,151,99,106,
172,22,202,101,46,6,11,208,138,48,222,110,109,128,72,175,156,116,171,153,210,21,51,14,99,44,10,163,30,139,249,60,7,239,29,188,9,184,76,106,116,107,81,86,66,229,105,111,26,119,31,132,201,149,249,118,220,
148,104,165,11,115,252,181,234,75,112,122,63,33,50,53,6,154,235,179,141,83,82,39,109,178,76,141,203,217,176,81,163,168,79,20,117,96,166,57,100,153,69,81,88,186,49,194,109,213,166,230,85,229,219,16,176,
240,146,40,17,77,176,58,138,34,50,133,109,116,12,246,58,57,8,202,94,139,40,176,12,101,169,41,255,117,224,126,8,43,169,125,95,29,99,243,132,50,196,14,43,165,116,54,200,124,145,143,247,247,90,173,118,63,
24,238,108,111,145,183,27,128,75,178,191,191,135,191,84,200,121,16,198,209,131,123,119,90,237,14,108,161,189,221,237,107,55,111,35,90,253,216,37,238,213,240,33,25,100,179,36,50,188,139,237,150,142,154,
7,117,82,83,107,176,129,44,214,186,65,167,186,6,55,92,147,167,132,231,144,92,246,162,62,128,67,118,5,210,116,29,44,89,111,176,87,166,157,109,234,214,136,229,250,88,238,67,249,71,66,144,32,173,21,61,24,
46,12,2,178,69,204,243,163,108,99,196,154,189,242,138,58,161,130,88,167,221,27,244,135,143,182,30,204,103,83,112,237,169,119,186,46,138,98,180,191,23,197,9,23,195,199,240,139,20,131,225,58,86,59,144,146,
174,137,187,213,241,148,168,131,197,137,7,139,67,201,7,212,150,82,198,231,13,41,224,46,87,57,203,46,184,77,81,232,13,75,102,57,69,98,64,50,100,45,43,133,16,243,184,189,157,14,227,166,186,178,216,9,200,
38,242,50,104,16,144,125,96,27,67,26,227,199,73,2,112,190,247,91,197,100,167,125,117,171,115,109,45,223,201,138,41,63,219,49,215,186,12,167,247,19,34,99,153,132,206,52,14,161,189,109,53,161,243,230,216,
92,162,119,129,236,146,226,144,140,205,59,209,26,162,206,213,141,225,208,33,219,35,78,193,113,14,78,91,206,47,80,169,21,27,98,96,159,216,116,123,32,236,181,180,138,34,89,146,57,208,94,155,173,226,34,125,
105,43,43,44,75,120,36,85,57,234,129,58,134,27,0,3,74,63,208,89,214,186,114,229,234,116,52,114,68,161,98,125,227,10,24,2,15,238,221,29,174,173,167,73,118,239,238,199,240,33,242,76,97,253,71,205,121,177,
18,253,151,248,248,37,14,119,219,28,181,196,205,10,51,250,5,118,75,71,149,45,117,44,83,7,24,176,93,57,168,163,12,170,21,240,29,184,47,14,127,135,217,84,60,231,7,23,75,211,123,9,48,39,91,150,129,98,34,
99,17,4,140,123,170,61,149,78,141,222,56,166,50,182,197,46,233,56,38,250,145,162,89,34,50,89,153,107,189,36,32,131,217,27,143,247,192,116,130,83,7,140,86,132,230,225,42,10,198,163,61,138,148,21,224,48,
14,6,27,27,87,174,237,236,60,124,112,255,46,172,129,86,183,27,46,225,160,226,169,10,133,16,252,65,176,68,50,17,228,140,66,61,69,221,156,211,164,197,78,189,226,104,153,48,10,34,194,230,53,172,53,64,72,
90,138,31,92,208,227,108,109,28,247,58,77,126,165,216,193,150,68,196,45,239,101,102,179,9,242,151,193,173,227,225,172,113,97,29,28,71,25,189,49,190,183,221,190,178,147,174,245,84,52,44,70,199,92,235,183,
60,112,206,109,108,206,58,14,197,11,20,5,207,181,43,94,197,19,186,110,76,70,47,178,92,149,161,175,39,73,194,74,135,41,207,149,99,182,21,68,194,231,147,235,188,77,41,241,23,160,117,128,74,42,176,188,69,
200,43,109,175,133,249,236,134,203,229,2,38,132,224,184,187,177,238,105,227,248,170,108,76,140,169,221,24,146,106,92,236,217,83,184,33,99,140,194,122,26,88,154,140,72,42,225,9,200,102,225,89,232,15,214,
24,4,3,166,222,73,150,56,154,135,180,162,14,200,80,84,238,98,187,165,135,138,218,184,139,58,20,129,176,160,74,156,70,194,238,99,70,21,166,29,81,16,43,96,55,155,94,92,225,42,178,181,147,228,225,115,18,
144,240,237,38,80,43,221,35,64,107,168,104,38,114,163,57,125,97,92,178,24,77,60,215,224,72,88,219,153,242,39,4,24,110,56,45,112,245,250,77,138,163,225,95,225,168,24,14,215,193,78,220,220,108,107,6,21,
187,89,186,122,237,134,171,63,197,23,10,39,214,41,58,245,97,55,117,11,50,241,192,64,34,59,57,139,73,139,93,73,188,12,37,67,67,210,54,28,165,243,173,71,66,33,237,36,210,33,108,60,242,19,22,230,44,234,76,
146,94,175,156,14,139,61,227,166,222,203,148,96,94,142,246,184,140,11,129,54,42,120,239,221,183,58,221,110,175,59,136,146,216,143,3,87,219,204,119,246,210,225,52,233,197,166,110,85,179,35,175,101,161,
210,50,248,77,15,174,63,73,198,243,115,159,109,28,99,237,89,50,143,168,143,19,69,139,168,151,28,184,209,97,189,42,195,200,227,134,202,113,107,58,252,87,250,208,72,223,144,70,11,155,232,32,232,51,222,30,
156,201,30,182,14,38,27,179,133,218,107,169,90,151,49,89,32,70,79,6,7,144,193,142,38,129,235,54,120,120,114,140,42,31,40,85,110,217,81,0,72,33,170,11,84,3,65,16,152,255,143,43,88,97,41,172,109,92,133,
229,241,224,254,29,184,68,187,219,221,184,122,237,233,94,27,175,168,199,101,184,2,230,66,187,165,91,222,11,202,147,18,6,170,97,172,80,154,101,243,249,20,75,7,234,170,211,237,128,35,134,134,152,107,52,
234,202,35,141,239,142,3,231,10,204,54,156,244,236,66,39,9,246,161,75,169,51,88,77,47,37,84,17,197,194,26,203,32,230,72,120,56,68,88,83,130,146,218,102,210,173,48,63,15,53,64,197,184,152,43,4,162,148,
26,49,37,211,91,225,248,218,234,44,225,251,58,179,143,108,129,111,130,149,56,45,72,213,232,167,152,171,174,167,137,166,101,166,185,242,213,165,62,225,16,160,101,76,237,154,156,22,182,140,29,28,185,11,
151,48,99,106,196,131,124,246,84,141,93,169,100,47,27,166,85,62,200,247,140,60,32,163,117,125,255,254,29,54,112,97,87,196,81,66,43,134,250,200,239,239,205,166,19,16,189,121,251,69,73,137,6,154,78,49,92,
236,213,50,220,73,135,97,83,69,122,113,232,90,44,243,201,235,132,252,201,146,177,232,4,94,253,142,199,25,157,8,141,229,125,116,204,89,25,108,106,66,100,120,113,146,80,163,70,229,139,183,29,164,151,27,
17,91,192,20,158,102,206,250,227,34,231,0,181,30,22,42,187,107,161,239,175,133,171,103,60,120,63,190,113,188,93,181,46,131,137,100,111,148,222,135,33,94,252,244,107,108,145,125,234,149,215,168,73,76,253,
233,87,63,199,64,214,151,94,121,141,159,247,197,87,94,229,224,206,213,205,27,250,234,129,150,4,199,123,109,182,94,213,52,143,203,4,143,97,29,206,25,145,228,68,94,41,74,240,10,35,17,105,69,23,106,234,36,
109,97,247,203,184,94,44,138,178,88,116,123,189,241,120,220,52,21,250,236,54,232,110,45,89,98,136,180,224,79,88,255,212,205,72,176,253,210,235,15,109,2,33,8,98,17,227,59,34,221,104,92,73,158,228,78,89,
130,251,232,16,42,216,52,214,111,117,22,28,147,250,57,229,232,102,41,8,153,147,223,82,200,94,132,143,204,32,112,162,0,98,69,143,5,173,79,50,87,193,137,52,174,157,59,186,207,4,206,69,165,172,26,94,47,20,
230,197,224,159,239,94,33,25,28,131,107,60,96,25,24,33,172,209,235,118,38,0,130,158,153,217,39,248,184,117,37,168,171,245,217,22,133,85,172,11,0,87,122,180,117,127,158,207,56,37,68,133,230,154,232,60,
192,120,171,103,179,89,171,213,214,56,66,120,239,206,135,157,78,239,202,213,235,54,28,40,228,218,236,193,189,206,245,251,173,43,55,199,119,34,138,11,242,181,8,62,99,101,52,183,15,249,196,116,66,190,64,
25,27,20,63,199,56,124,166,5,24,244,69,83,223,241,204,194,81,28,43,85,84,77,1,231,43,203,128,11,0,222,122,131,172,36,245,112,48,24,143,71,203,174,203,198,118,91,66,160,3,1,103,184,225,1,152,247,73,28,
135,212,50,11,145,59,82,226,225,79,231,161,34,232,34,190,98,12,99,69,24,87,58,120,63,230,32,210,157,184,218,181,11,211,132,79,72,65,156,209,35,59,82,134,99,196,143,203,48,50,235,98,35,146,92,207,63,215,
121,163,234,150,201,22,114,1,7,47,203,180,219,109,120,50,156,161,70,195,94,128,127,102,89,134,59,68,227,204,71,48,161,81,180,63,26,113,121,51,215,31,192,231,173,86,70,73,143,6,52,87,59,235,54,166,102,
140,85,71,183,224,230,39,98,102,92,191,69,98,49,229,246,57,250,160,34,224,210,221,99,103,169,177,108,22,220,49,240,132,179,77,7,134,126,146,12,6,2,176,196,42,52,114,217,14,78,48,72,230,144,185,170,236,
253,123,194,110,118,108,233,6,56,210,168,153,24,210,214,204,146,235,205,25,10,59,50,203,192,75,249,230,183,191,179,196,179,113,166,193,152,71,201,80,7,209,141,249,150,178,33,9,110,81,93,110,111,221,47,
138,5,214,67,52,182,158,11,22,250,107,159,249,236,246,163,135,119,238,222,225,96,4,227,254,65,87,214,85,153,231,57,248,136,20,143,68,100,95,187,154,79,227,118,165,194,86,53,247,215,194,10,15,46,206,180,
184,162,203,237,56,253,188,100,96,222,16,116,126,166,113,236,134,84,24,19,53,190,13,173,107,60,0,102,110,16,47,116,21,147,85,132,50,65,24,204,167,83,206,52,193,11,130,211,190,4,7,190,92,4,22,173,194,94,
3,238,25,225,122,190,91,158,76,114,205,112,99,133,209,198,230,117,60,252,217,30,11,74,149,22,205,34,211,181,61,186,87,239,135,106,211,148,43,59,147,140,196,57,196,237,125,168,252,197,210,192,92,80,33,
167,237,36,243,152,204,133,115,186,187,24,55,101,6,85,208,83,221,153,204,177,177,149,70,142,230,40,78,170,114,193,105,119,120,61,216,75,21,113,112,1,147,171,112,253,202,112,56,24,141,102,176,225,127,240,
111,127,0,103,195,246,246,54,200,183,218,25,72,93,187,126,139,252,242,128,0,39,114,77,13,39,98,186,16,133,242,44,91,242,136,198,13,46,154,242,148,89,90,149,81,39,158,237,227,155,68,8,91,82,106,51,205,
68,124,140,97,248,39,214,247,80,210,147,77,112,142,199,41,203,232,111,56,29,228,75,178,121,170,27,34,224,230,126,22,198,149,49,98,215,28,166,127,166,157,131,184,65,176,184,118,179,181,78,49,78,171,57,
179,88,241,3,60,122,116,143,234,164,176,180,6,206,19,24,8,252,118,176,123,63,254,248,163,251,247,239,115,33,14,178,220,85,149,209,214,123,70,150,2,228,205,232,240,56,152,82,84,193,36,106,245,170,89,40,
249,62,150,169,14,123,173,223,82,170,25,80,88,9,108,158,179,118,201,102,212,184,35,78,17,158,210,143,166,45,10,179,28,214,184,41,83,39,131,59,15,52,20,213,142,96,91,138,86,171,149,38,9,237,29,180,174,
193,117,105,183,90,5,81,11,176,15,162,2,142,206,102,28,152,0,221,58,24,172,251,107,69,157,57,184,158,213,180,205,40,7,142,149,44,239,199,135,56,140,237,224,196,214,162,58,166,173,134,146,23,88,200,73,
248,152,35,182,202,98,145,167,105,122,102,114,203,39,201,16,186,64,85,162,238,138,54,50,157,193,255,108,97,144,76,179,86,129,16,1,102,158,146,108,144,54,100,78,226,225,65,0,133,94,175,59,159,207,59,221,
222,119,191,243,221,183,223,121,183,200,139,118,187,213,238,118,219,157,158,71,207,247,100,55,149,241,142,220,231,142,89,28,80,59,243,44,9,121,96,182,155,11,42,155,197,108,166,246,80,62,201,149,243,135,
78,38,15,172,151,150,28,41,112,26,74,121,222,109,199,52,187,44,201,62,164,133,45,99,2,201,4,223,248,214,119,88,65,214,76,185,41,228,44,237,151,81,107,99,190,35,184,164,158,84,44,120,130,85,137,63,252,
0,112,44,192,241,27,199,209,100,58,213,238,77,240,171,228,240,103,195,236,19,8,174,169,18,248,137,82,62,2,99,221,76,146,46,124,63,170,230,22,220,24,216,222,232,129,100,203,241,183,147,106,6,181,6,17,75,
158,97,28,252,80,104,44,94,115,20,13,174,79,131,112,53,16,50,202,202,122,17,7,34,100,25,60,237,171,2,108,120,130,8,52,240,238,64,61,177,249,144,68,9,7,194,214,134,131,253,125,36,3,248,159,127,240,111,
224,53,237,192,105,175,117,43,203,64,230,198,141,23,56,135,197,221,12,194,246,180,202,83,93,69,156,252,194,82,216,131,247,163,220,79,192,124,103,140,210,122,178,82,192,154,184,139,235,29,199,32,70,253,
152,12,88,248,113,154,93,44,241,183,135,149,195,12,132,38,108,201,108,102,102,182,247,15,249,110,224,143,87,52,213,210,245,40,147,164,1,153,247,142,11,194,225,179,247,223,123,247,149,87,94,249,23,95,250,
210,155,191,124,115,54,159,190,252,202,103,28,8,30,125,254,117,49,152,155,69,46,114,46,119,175,159,208,62,231,108,85,220,88,95,125,17,227,4,202,118,207,179,156,255,188,20,45,43,63,135,169,125,119,37,225,
253,65,54,154,248,140,97,32,161,112,61,86,142,209,158,252,69,100,197,112,46,161,227,207,55,102,59,219,72,155,162,91,207,153,230,149,220,153,124,62,159,18,97,6,150,64,192,54,8,169,113,3,220,220,44,159,
121,142,56,76,196,198,17,235,62,38,91,228,53,188,40,114,234,79,107,249,117,170,32,202,163,118,191,156,186,190,155,75,74,217,39,144,84,252,54,80,205,148,104,97,165,103,27,135,222,150,34,148,155,179,191,
149,163,156,225,216,95,29,162,145,37,84,83,198,94,38,73,219,229,98,206,100,123,132,71,12,233,180,39,16,125,221,112,194,168,63,232,47,242,121,167,211,125,227,141,239,190,251,206,187,243,121,222,110,103,
221,222,176,221,233,251,113,194,246,34,140,235,114,220,113,39,165,173,101,59,112,63,82,58,102,14,95,28,107,145,238,71,43,5,138,173,94,84,239,184,103,200,233,222,248,170,38,164,175,145,197,80,13,218,170,
61,210,99,48,166,152,137,16,190,154,181,186,117,85,104,119,102,123,218,37,79,182,17,39,49,140,241,171,183,127,245,249,47,124,190,211,233,188,255,235,95,231,179,89,127,56,228,80,242,13,181,9,122,255,161,
120,196,57,116,238,202,113,230,89,98,122,242,199,59,236,93,72,167,62,223,150,137,250,72,55,54,58,21,4,140,155,97,134,113,202,0,216,108,43,219,161,14,27,168,169,247,98,32,79,163,61,131,175,124,253,91,43,
90,77,229,65,178,72,251,235,197,40,104,42,239,170,140,246,31,21,69,105,89,41,136,53,41,73,82,184,155,241,100,210,184,46,146,174,236,22,175,152,34,2,168,97,74,73,110,244,7,54,22,56,242,92,82,167,116,51,
75,186,153,46,67,226,108,32,127,162,97,199,211,172,114,113,56,22,26,12,197,25,99,101,78,105,199,194,127,192,39,101,70,246,19,218,186,96,222,204,243,41,163,63,46,144,106,38,95,96,79,243,179,118,201,110,
140,237,136,99,132,103,26,82,220,105,130,32,139,136,171,46,225,213,53,139,152,106,67,109,205,102,214,106,213,88,79,187,108,68,42,29,232,134,219,91,18,117,100,240,254,251,239,191,242,242,75,95,250,210,
191,248,213,91,191,130,211,254,246,167,94,246,215,130,165,155,116,103,186,74,68,149,217,107,9,219,106,97,245,126,184,226,202,49,82,217,131,8,132,163,48,62,82,41,136,115,120,100,159,28,78,119,88,147,51,
51,71,247,77,165,83,61,181,251,154,18,173,173,118,27,70,171,155,210,191,77,186,171,128,145,236,236,45,230,121,190,181,181,245,157,239,126,231,222,221,187,251,163,209,230,230,13,16,187,34,215,179,32,221,
18,219,53,37,61,109,49,223,57,102,201,101,159,109,7,53,174,240,58,201,56,108,10,241,61,63,73,198,83,68,48,63,186,89,217,188,124,110,217,8,187,180,28,240,94,235,53,168,245,44,199,14,37,46,79,170,61,131,
175,126,227,245,85,173,214,68,217,44,72,122,197,126,232,144,133,48,244,100,50,98,178,240,170,170,152,62,28,156,112,88,13,154,178,135,124,200,91,48,23,35,167,141,1,25,46,140,10,16,155,138,156,16,237,118,
215,80,88,31,102,107,18,119,147,102,209,146,182,78,210,119,235,98,125,231,200,100,57,231,160,124,5,185,176,177,249,39,106,226,34,207,31,220,189,211,237,246,85,16,176,204,98,145,63,188,119,7,78,202,110,
167,119,164,173,187,183,179,189,187,187,221,235,245,253,56,251,163,189,221,71,143,218,157,110,28,199,23,216,1,27,12,25,12,186,159,209,134,15,29,237,168,99,41,113,180,1,212,149,175,193,160,146,110,69,173,
69,144,150,77,158,121,25,88,111,173,118,143,185,68,41,87,30,242,226,147,142,154,29,187,72,196,8,185,124,247,221,119,190,240,133,47,180,219,173,95,127,240,65,185,200,135,107,107,124,173,100,176,47,148,
169,70,253,213,107,61,118,63,66,217,72,174,45,244,55,46,225,253,36,165,192,193,135,139,106,197,244,188,56,221,17,112,14,75,94,234,174,236,40,17,204,77,174,141,11,230,73,4,238,182,219,189,180,213,130,133,
196,198,70,20,37,224,130,116,193,130,93,219,232,245,6,160,185,238,222,249,56,205,178,47,127,249,203,191,248,197,47,64,143,221,236,220,106,137,214,142,217,157,153,220,81,45,82,211,166,243,205,18,205,182,
109,113,100,17,246,39,26,135,217,41,142,147,177,118,5,51,109,187,214,83,124,190,186,194,47,27,74,167,192,191,228,89,212,231,56,171,66,38,163,240,232,234,156,219,148,55,85,109,63,11,192,151,113,141,129,
16,6,221,237,118,167,211,41,57,125,114,181,23,112,104,143,117,252,161,88,251,34,77,82,236,218,86,99,124,190,92,44,144,231,140,110,154,240,96,129,81,81,89,76,165,207,66,46,89,44,150,40,108,223,149,207,
118,22,114,9,209,39,33,194,97,216,36,203,168,220,202,202,112,231,152,99,144,229,105,154,82,102,67,45,101,108,155,140,230,248,107,125,114,144,238,20,6,14,64,179,149,163,65,60,24,37,131,105,57,234,44,101,
132,233,244,215,226,56,157,204,70,240,86,9,186,133,11,46,224,52,13,129,98,186,189,206,254,254,232,191,252,151,255,247,135,63,250,209,123,239,189,251,240,225,67,166,231,79,122,35,21,154,98,175,79,164,164,
205,242,90,143,221,15,230,167,45,190,199,216,86,67,84,15,188,68,186,31,132,246,196,196,205,116,129,56,146,103,140,116,231,76,69,67,118,203,200,76,224,30,134,170,31,171,232,161,222,226,10,89,222,228,74,
16,2,94,69,105,214,241,205,29,57,97,2,107,238,234,230,205,170,42,127,246,211,159,221,186,121,243,7,63,248,193,143,127,252,227,223,219,248,210,190,28,77,229,204,214,84,73,142,242,212,103,158,37,102,210,
72,66,36,195,97,25,42,78,172,93,248,197,119,42,62,71,53,184,116,72,119,201,133,220,8,57,110,44,136,71,90,102,29,215,58,239,252,88,197,224,219,111,252,143,171,90,45,15,219,77,16,246,202,169,180,198,173,
88,204,167,96,187,18,115,110,213,238,116,38,232,6,90,192,170,7,103,5,206,70,240,53,168,112,166,91,234,12,210,232,76,103,97,105,129,140,153,68,45,165,235,180,206,93,227,115,171,70,89,203,122,22,90,75,6,
39,140,151,65,71,169,110,166,211,17,12,60,155,140,23,200,144,169,198,251,35,78,96,87,104,67,170,52,78,162,48,154,78,198,216,73,92,235,25,22,127,102,176,99,225,202,243,233,52,73,255,127,246,222,180,203,
182,228,44,19,139,136,61,157,57,207,201,249,78,53,104,108,140,48,172,213,52,221,32,149,6,88,11,212,198,110,36,241,149,223,225,47,254,228,255,98,240,55,35,117,35,219,244,39,214,114,131,144,0,75,12,141,
161,75,85,82,13,119,200,249,228,25,247,28,126,167,136,115,50,111,102,222,204,188,153,121,175,10,149,74,53,100,69,238,29,59,118,236,55,222,225,121,159,167,81,228,249,108,50,46,178,12,142,62,216,49,48,31,
56,135,193,145,60,62,58,130,235,88,170,232,245,86,6,112,145,217,120,156,101,115,248,62,35,124,211,47,21,197,228,96,193,155,205,107,215,167,92,79,128,184,215,158,101,204,21,105,40,159,84,19,84,170,153,
106,248,123,153,44,143,9,163,8,78,251,102,187,3,97,41,106,133,97,13,30,140,70,12,222,232,96,117,179,187,130,208,147,15,63,252,160,213,108,253,155,95,251,181,191,254,107,60,237,251,219,58,108,228,197,180,
83,231,241,25,247,90,154,143,118,194,92,34,126,227,116,134,152,38,248,108,78,119,2,184,47,156,47,218,218,73,28,38,113,82,123,183,128,10,219,178,16,23,75,22,221,33,167,187,117,156,238,156,84,230,72,39,
85,89,97,139,142,238,52,21,172,126,230,85,176,4,210,205,41,71,204,219,213,60,79,159,242,235,246,250,176,49,126,252,227,31,255,219,95,251,53,248,178,142,179,81,30,73,189,69,184,122,104,243,95,27,109,35,
8,152,122,33,56,194,107,149,132,196,219,229,214,90,189,68,140,76,229,65,73,189,163,93,55,33,179,125,193,191,162,38,208,205,101,15,121,76,120,202,170,89,56,16,152,246,204,161,207,241,147,118,186,219,156,
80,135,211,12,225,106,120,128,40,237,9,52,200,83,230,110,166,56,138,84,24,114,53,29,41,202,66,172,101,22,216,136,16,178,95,22,88,204,132,193,195,193,52,118,219,155,194,144,175,36,180,244,169,16,172,152,
184,190,232,237,244,64,148,92,138,124,127,111,151,45,63,172,200,240,232,48,164,123,241,73,120,116,176,7,209,232,104,4,63,222,143,146,164,160,202,61,89,235,104,158,206,243,34,175,203,242,201,71,31,180,
90,29,176,92,112,225,201,120,60,155,77,186,253,254,206,147,199,200,98,220,104,204,103,51,142,218,159,60,254,176,44,138,222,202,202,222,222,206,202,202,160,191,182,246,122,34,221,25,19,200,232,243,42,77,
10,83,71,173,153,50,85,54,108,51,43,141,31,3,38,42,137,146,186,237,174,99,253,117,130,205,173,123,101,145,255,249,95,124,239,193,131,7,223,250,214,55,191,251,221,255,243,225,47,132,229,172,85,206,147,
243,238,117,1,210,221,137,57,43,71,107,163,9,50,138,254,66,73,180,206,232,134,40,44,64,51,159,214,108,124,252,236,233,19,48,111,176,181,238,221,187,31,163,149,209,78,243,194,136,56,144,164,56,95,49,210,
157,185,85,157,254,155,228,122,192,251,156,235,108,79,237,173,169,213,123,122,107,170,166,35,59,174,16,124,202,146,104,202,181,247,88,195,120,14,108,21,182,232,64,89,253,249,7,191,248,119,239,253,240,
47,190,255,151,95,253,218,87,191,253,199,223,217,104,221,35,161,236,197,152,235,117,104,51,129,181,149,198,108,205,184,77,120,180,201,248,120,103,231,105,77,75,189,177,185,5,199,60,177,45,82,71,215,117,
238,133,239,150,0,83,202,65,146,235,51,123,128,110,132,39,3,87,230,215,73,151,208,91,181,73,144,128,157,92,169,82,201,163,91,53,159,77,242,60,35,157,72,131,225,29,241,234,178,243,229,204,179,146,214,1,
17,31,53,84,66,178,84,92,143,210,44,35,187,27,52,24,209,75,163,210,70,47,212,166,153,79,96,77,167,81,139,117,16,92,11,136,48,113,145,4,11,70,67,124,82,53,211,49,55,1,64,160,4,222,211,96,109,189,215,95,
5,143,105,125,99,171,221,237,206,17,88,220,33,1,171,105,171,221,1,19,19,39,201,131,55,222,138,227,100,62,155,118,186,61,240,38,166,163,241,96,117,53,43,242,233,100,146,166,16,251,86,141,102,11,188,48,
248,173,110,187,123,60,28,246,250,253,251,247,31,193,114,129,83,214,108,183,193,230,17,23,45,30,38,69,158,173,175,111,189,204,201,144,165,115,8,87,95,230,132,169,72,247,156,83,80,60,134,77,67,72,45,202,
44,242,138,62,77,25,169,58,12,91,105,152,148,186,108,241,187,56,53,230,204,235,244,7,107,240,152,239,190,251,238,175,254,234,175,30,15,143,167,163,50,180,43,23,223,139,175,99,157,22,180,115,195,132,193,
198,169,189,186,118,63,170,34,105,97,157,213,252,114,67,138,247,15,15,246,219,237,118,20,68,121,158,143,39,163,233,120,12,199,73,24,198,172,86,29,74,140,41,237,138,162,32,243,138,56,221,249,22,188,99,
157,76,148,161,198,23,88,142,122,110,178,80,5,109,213,234,170,78,100,35,124,179,138,97,71,154,251,75,24,7,96,106,48,141,193,138,237,13,212,74,83,55,54,214,54,255,241,253,255,122,255,193,131,207,124,230,
179,207,118,118,216,61,177,53,63,93,125,37,105,28,206,79,82,111,175,113,60,124,22,99,91,43,60,252,199,195,131,118,171,13,203,5,222,15,46,245,100,220,108,182,193,1,151,49,39,239,5,215,57,79,14,199,141,
169,57,205,247,188,52,142,189,29,60,99,40,170,74,206,170,65,48,145,43,164,152,112,40,7,205,193,10,163,147,211,172,100,15,220,135,241,75,124,213,66,6,192,219,151,156,38,34,54,67,177,226,128,27,59,249,227,
65,221,118,171,195,42,227,36,220,250,116,215,17,150,139,149,245,214,207,79,215,58,56,173,52,34,105,33,107,97,84,30,51,55,121,221,33,19,132,16,235,33,69,236,8,162,194,169,32,247,92,124,1,129,222,234,218,
58,252,227,225,225,30,198,140,196,166,72,93,75,21,252,43,189,194,9,111,23,184,20,4,113,157,149,149,108,62,231,154,197,203,156,12,167,214,249,74,215,49,130,231,22,14,117,94,19,100,4,208,92,21,169,78,141,
41,51,8,184,77,220,27,135,43,251,101,218,180,105,227,249,49,207,95,167,182,197,195,79,13,222,253,167,199,223,255,193,15,190,246,91,191,245,157,111,127,187,221,82,47,188,23,115,186,19,87,150,35,99,160,
134,91,30,204,140,189,194,174,201,120,28,87,8,22,181,49,91,63,121,252,81,158,102,169,193,138,94,111,165,7,54,107,54,157,125,252,209,7,253,193,42,184,0,124,92,11,250,201,184,132,55,161,198,95,9,167,59,
199,232,158,67,93,100,62,144,187,138,194,136,42,223,179,251,70,5,93,221,233,234,118,39,216,228,173,93,226,18,86,68,118,23,32,183,15,152,17,131,140,168,35,59,153,217,25,252,195,219,111,127,230,175,255,
234,175,183,183,31,128,23,204,219,0,30,37,122,97,135,54,22,98,35,102,168,94,136,81,97,251,116,233,212,228,165,184,193,222,16,4,13,16,129,194,23,2,238,85,187,219,1,71,4,226,137,15,63,124,191,63,24,192,
121,204,118,103,249,94,196,161,250,130,110,112,70,42,176,199,125,237,204,224,229,199,132,236,239,123,127,15,137,133,34,209,176,243,64,83,34,75,180,165,194,52,22,210,102,106,187,16,26,119,173,180,178,233,
241,59,87,92,77,101,157,113,140,31,171,42,33,178,44,129,33,194,140,96,201,202,197,57,230,169,117,233,48,22,180,62,145,132,97,68,64,49,80,237,23,133,154,176,188,160,130,117,60,7,146,241,229,197,92,223,
216,222,219,121,186,187,243,20,211,70,52,102,124,124,220,91,233,147,244,211,252,96,127,15,230,137,198,168,187,50,155,78,209,207,15,131,205,205,123,7,251,187,187,207,158,114,106,28,76,236,218,198,230,240,
232,96,60,30,193,35,67,204,72,109,92,209,181,253,115,145,128,191,86,151,41,247,193,47,115,168,11,0,15,169,28,56,230,194,182,172,229,49,240,57,23,135,221,164,51,143,154,243,176,57,171,139,164,154,37,40,
163,67,12,104,203,215,129,15,45,8,235,160,9,30,25,162,127,63,251,133,237,119,255,254,253,207,125,254,243,95,254,234,87,254,254,239,255,145,91,207,46,190,23,183,221,123,193,55,230,153,227,112,129,106,41,
21,188,108,133,78,5,188,246,154,250,240,9,42,95,135,96,1,138,172,78,103,84,92,43,45,196,245,112,193,78,183,211,108,53,231,243,249,209,225,1,60,6,184,210,88,233,163,235,40,34,214,174,170,218,49,211,115,
139,245,157,114,186,83,100,234,181,183,37,207,72,140,2,21,31,151,172,46,59,177,147,177,154,52,109,35,64,190,11,164,84,54,138,128,224,138,254,4,147,98,108,166,50,198,75,35,168,197,214,221,110,127,58,157,
185,142,98,65,105,92,16,183,46,82,230,108,89,208,156,235,24,130,72,11,150,46,196,59,90,6,184,194,234,96,198,112,154,79,192,205,199,79,160,128,35,120,14,119,104,119,218,68,50,49,59,220,223,7,115,188,190,
190,137,93,93,228,3,94,41,70,38,158,109,253,50,28,24,87,24,243,63,255,47,255,43,252,21,238,141,12,135,65,144,38,221,163,214,250,131,233,83,83,33,71,53,172,38,56,41,195,195,253,44,207,225,153,39,147,201,
34,179,238,4,47,49,205,230,74,68,28,221,144,120,20,174,35,167,120,225,178,157,86,119,109,115,91,32,245,218,124,216,220,92,75,15,187,152,116,71,119,191,162,20,108,20,196,142,61,89,149,216,186,93,113,214,
44,16,210,238,138,172,108,226,45,177,159,179,16,152,80,145,254,181,29,115,60,60,234,247,87,175,119,29,92,88,234,58,168,234,218,83,244,113,26,85,59,69,72,76,96,157,53,6,236,17,134,135,141,140,201,251,72,
238,32,162,102,115,139,182,136,48,85,68,212,171,171,172,97,211,38,56,227,176,248,179,241,120,99,107,27,182,242,101,238,197,27,192,67,102,152,55,6,15,40,184,117,35,53,201,28,126,12,99,176,73,23,236,20,
89,76,107,75,218,243,234,31,190,191,155,103,133,199,68,112,186,10,158,185,217,106,165,243,57,196,194,173,102,243,141,55,223,54,46,38,53,164,55,133,54,29,215,132,148,211,41,74,229,153,248,30,102,226,47,
172,198,195,163,222,96,149,65,24,174,138,95,139,194,0,227,33,130,128,75,102,215,29,99,57,186,208,142,190,61,20,114,30,237,25,172,28,186,82,249,163,73,57,162,87,54,178,24,197,43,206,208,185,70,22,43,232,
30,182,17,224,189,158,234,208,230,167,115,241,13,171,248,196,141,42,233,232,118,164,163,90,200,179,235,162,46,144,40,22,28,44,18,137,248,243,247,254,159,89,54,83,212,184,39,56,36,132,72,234,102,163,49,
155,207,203,162,0,227,245,153,79,127,174,118,109,237,254,94,116,222,214,220,65,121,230,124,188,74,0,103,150,177,211,59,136,78,90,180,19,86,239,101,198,132,167,172,154,65,20,124,157,235,176,169,43,92,124,
171,154,173,246,120,116,100,51,92,229,56,138,72,231,174,246,160,85,209,38,227,168,85,11,70,65,196,49,169,239,147,18,31,113,179,211,17,205,17,171,114,98,26,136,152,39,67,213,101,205,124,62,1,19,239,178,
195,31,184,238,88,6,20,161,113,165,49,55,108,173,239,120,140,186,230,117,152,192,115,153,67,221,146,207,203,121,3,79,164,119,246,24,112,212,39,205,114,218,50,113,201,62,14,50,162,24,216,238,170,202,225,
204,71,120,67,1,187,59,143,92,153,27,85,29,58,189,65,154,166,174,169,226,130,123,73,120,110,92,217,139,140,22,28,237,101,208,154,69,141,12,237,93,209,40,103,73,150,27,22,191,226,19,155,125,199,163,163,
189,50,43,133,30,138,116,79,56,206,132,59,129,11,64,45,216,81,150,165,63,121,255,199,159,249,220,47,240,55,193,194,135,156,201,14,149,94,146,44,187,35,78,247,147,99,12,115,84,193,23,21,83,219,160,99,110,
130,37,174,23,45,0,76,135,165,153,158,93,34,13,110,160,115,100,211,140,5,175,125,211,31,59,176,231,197,173,98,59,232,191,134,58,92,209,189,102,221,196,130,190,74,15,235,97,1,129,41,203,88,232,133,72,210,
240,224,96,150,78,173,107,130,17,207,140,236,209,60,77,81,94,41,142,33,24,255,111,239,254,211,103,63,247,11,104,127,43,174,159,4,174,205,212,156,23,35,115,45,5,140,51,68,113,119,192,220,27,242,233,225,
253,189,102,157,193,206,157,39,221,230,52,245,137,174,40,73,52,250,144,22,54,16,88,98,100,232,161,214,101,223,52,84,123,194,7,215,242,138,88,222,16,119,28,114,233,87,101,187,221,241,156,238,147,164,15,
207,215,130,3,128,58,254,107,230,114,171,149,118,181,66,223,222,205,207,192,77,0,50,230,231,156,238,207,113,186,115,221,234,121,158,245,211,99,138,184,116,99,156,199,228,196,40,144,247,239,210,215,113,
99,66,68,114,187,188,131,35,33,65,175,33,46,27,43,19,252,72,211,78,57,111,148,149,212,211,202,74,100,102,168,159,39,168,170,124,127,119,175,32,138,33,167,22,78,159,180,230,211,208,146,38,149,18,220,179,
203,187,186,104,201,241,114,162,49,168,238,152,211,253,249,49,218,101,247,156,174,159,241,60,232,202,129,254,133,252,207,44,116,137,106,229,144,43,30,23,77,192,31,81,213,22,106,171,231,116,198,8,216,194,
140,4,177,141,86,237,0,70,30,215,35,136,64,107,103,37,57,251,78,164,175,120,83,48,250,59,187,79,10,114,219,189,192,165,59,99,72,34,59,71,112,15,131,242,152,214,93,32,159,14,174,125,94,140,44,138,210,148,
44,12,117,112,23,236,190,46,3,165,57,137,2,95,72,59,31,29,199,189,65,16,25,226,150,134,57,119,123,3,216,61,120,228,146,189,13,89,45,130,217,93,93,254,138,234,38,214,195,211,193,55,78,146,24,139,8,97,188,
181,121,207,137,167,193,160,96,22,181,86,178,99,18,233,12,137,166,6,139,26,238,252,172,69,61,193,249,159,63,231,116,103,78,247,69,44,224,24,193,121,125,80,113,235,85,140,97,137,92,79,49,26,112,253,215,
170,160,145,197,221,9,4,124,197,120,0,222,6,23,200,216,204,81,252,91,17,162,18,247,248,227,143,63,20,93,44,148,10,10,88,212,222,215,131,40,33,160,25,215,178,178,210,7,83,27,133,161,199,42,179,108,156,
87,75,191,99,78,247,11,57,237,106,250,126,43,205,130,12,244,169,227,0,197,20,26,168,123,202,53,4,10,165,193,1,12,152,125,23,89,165,184,103,0,125,43,121,186,231,209,45,82,41,161,192,60,177,201,170,237,
151,186,220,175,15,107,120,33,165,35,163,214,139,49,28,147,62,125,250,24,153,2,29,65,40,59,75,94,130,132,45,20,199,163,171,131,53,110,169,241,38,141,70,214,231,162,109,52,115,123,226,75,176,164,173,116,
219,204,189,103,112,186,55,203,227,97,212,29,134,205,149,116,200,86,45,14,205,218,218,250,225,1,102,178,248,84,161,163,151,216,109,88,11,65,73,95,91,69,9,172,154,184,46,21,21,245,66,98,117,96,212,120,
100,204,113,163,15,191,219,175,16,50,250,115,78,247,159,241,231,50,62,22,163,45,110,163,206,60,160,4,127,62,234,90,218,109,12,144,175,209,5,199,93,71,123,3,251,231,179,89,58,159,205,107,106,143,167,132,
75,69,225,139,232,131,114,57,152,139,197,141,36,217,216,216,198,218,60,227,179,93,105,154,177,166,180,176,193,93,34,221,47,197,123,103,98,6,97,241,194,113,205,14,235,137,170,198,66,33,9,129,51,182,20,
147,238,212,78,75,78,43,153,87,234,28,103,119,49,164,152,116,153,103,221,131,126,250,170,219,211,189,76,231,7,234,208,6,104,225,72,70,183,102,71,15,65,30,134,241,107,245,124,54,203,211,148,1,2,129,244,
232,85,190,137,74,51,212,17,207,16,3,97,80,127,117,157,249,167,152,233,0,117,198,46,23,35,187,158,165,91,103,229,61,131,211,29,118,74,171,152,79,146,94,175,152,26,151,159,138,27,173,193,234,234,209,225,
33,93,15,22,55,36,103,59,84,190,187,145,82,140,17,81,86,182,90,173,64,160,12,141,181,141,109,39,63,169,42,19,140,226,118,43,159,219,178,168,127,206,233,254,51,251,92,86,45,147,52,8,77,130,78,230,73,39,
207,103,205,98,210,241,68,72,28,158,164,233,108,116,60,68,110,91,178,68,20,238,17,178,47,88,116,252,251,140,180,192,185,168,186,7,102,168,215,31,72,148,234,216,7,157,196,31,243,181,11,210,253,206,56,221,
47,51,6,191,115,218,209,174,75,92,51,102,77,59,189,7,34,176,174,176,135,12,205,71,65,142,100,192,157,228,232,171,58,68,58,35,105,180,139,73,93,23,157,110,235,102,87,245,198,245,228,72,13,221,27,144,172,
126,158,165,163,209,176,196,122,48,218,114,34,98,203,192,207,112,176,123,171,5,158,174,245,18,113,51,147,121,116,87,86,228,58,142,19,134,175,252,162,24,89,51,253,17,108,141,59,96,238,13,235,50,163,251,
5,194,90,74,207,177,158,31,63,110,116,159,181,54,30,78,119,40,203,14,47,32,136,226,214,234,170,57,26,30,64,172,7,19,29,30,29,193,67,150,142,50,156,15,26,58,87,241,32,141,81,39,61,218,216,188,79,0,153,
138,129,103,143,27,27,48,170,63,59,240,247,226,174,20,158,28,77,163,202,243,197,228,240,63,96,85,64,251,49,12,152,250,153,28,131,74,149,197,39,224,185,184,253,19,37,236,133,34,134,16,121,97,149,116,166,
69,22,22,147,182,114,218,212,53,246,69,141,143,14,15,96,51,32,247,38,133,15,104,167,140,129,127,165,99,220,10,116,142,178,54,142,45,82,90,126,18,176,86,221,222,202,202,64,24,208,149,167,1,243,234,175,
248,43,119,143,116,191,12,239,59,126,210,194,77,46,145,21,69,103,148,86,39,123,16,33,48,184,114,57,1,177,17,53,185,90,226,142,145,142,30,199,218,214,115,9,89,21,171,104,160,250,153,206,14,213,16,173,6,
9,157,194,5,38,211,209,254,222,78,68,89,102,14,95,13,129,61,210,52,117,23,240,10,212,238,106,181,200,82,131,159,209,235,118,251,43,171,146,157,88,196,191,170,150,176,253,130,24,89,177,59,9,151,195,205,
112,115,153,193,51,199,132,172,131,130,9,55,174,202,209,89,26,88,189,49,121,186,211,222,218,109,174,175,78,119,44,251,142,224,164,53,154,247,238,63,28,30,29,12,135,67,67,226,145,138,168,203,152,103,114,
169,45,201,110,110,108,152,48,97,114,111,6,136,238,54,215,42,29,110,77,118,52,23,113,101,95,85,126,114,212,55,104,239,32,69,250,74,198,96,64,132,39,228,207,240,115,41,215,65,90,214,21,59,74,165,180,209,
170,100,112,108,107,147,143,86,60,172,20,246,198,238,206,227,154,224,218,12,223,67,45,175,162,168,145,243,163,212,62,125,108,157,210,158,24,24,194,58,87,117,24,161,164,195,246,103,147,249,81,133,160,103,
195,28,0,136,171,102,140,158,65,100,23,110,182,172,200,239,146,211,253,114,99,164,42,37,2,107,230,140,248,26,38,198,75,128,99,200,175,176,170,246,212,140,76,30,143,6,0,145,234,86,122,248,201,179,125,16,
220,47,85,185,95,31,68,65,8,47,130,68,70,170,253,221,39,220,103,5,1,32,179,199,224,241,136,196,154,165,64,37,20,129,120,137,14,150,63,83,54,148,212,39,27,37,113,242,249,181,95,220,41,246,153,27,158,220,
42,108,99,140,28,98,233,194,248,55,226,30,6,14,69,111,35,51,184,60,38,120,231,29,108,205,177,164,143,194,192,78,118,113,145,33,188,174,70,73,215,234,160,89,205,101,41,169,170,12,123,105,60,30,229,40,0,
105,60,100,212,218,133,117,134,237,184,182,113,143,137,145,184,110,114,216,28,204,162,246,234,252,176,85,165,66,35,240,9,165,66,62,111,76,154,165,73,210,248,25,127,46,134,162,212,238,112,18,67,19,119,
167,16,208,164,71,43,156,63,224,242,49,124,66,179,249,60,119,44,204,240,248,136,11,165,76,62,69,130,82,11,19,254,35,254,68,140,124,147,81,28,181,90,173,123,15,30,132,237,57,92,185,204,34,199,127,103,28,
202,152,115,198,174,160,124,135,156,238,151,227,125,23,102,0,79,196,234,168,244,244,57,204,83,134,37,24,4,250,195,161,49,63,140,112,104,74,243,255,154,30,4,54,120,106,119,172,200,18,226,143,247,247,158,
206,102,179,60,203,248,109,193,241,144,166,25,139,92,48,117,31,163,240,141,246,132,17,148,47,36,3,1,209,82,171,221,122,240,224,173,62,178,77,196,115,157,185,204,155,38,26,85,117,201,110,112,62,210,168,
191,231,118,153,123,67,142,206,56,156,150,29,41,186,193,85,92,228,93,173,39,141,126,105,162,245,249,110,160,140,172,101,16,242,209,90,10,16,195,8,220,150,202,186,126,29,235,90,244,135,247,219,27,121,212,
236,231,227,110,57,243,12,205,162,206,102,21,113,63,20,60,87,146,102,33,243,239,72,60,94,207,49,215,72,199,82,207,157,189,203,212,239,53,198,192,190,40,42,129,185,44,143,225,142,101,177,92,36,71,236,2,
34,194,109,37,89,149,118,176,210,165,5,130,127,184,191,147,101,88,41,151,22,84,84,87,226,148,185,96,40,185,87,66,18,227,114,178,137,181,130,51,127,48,232,175,173,111,193,20,234,180,133,48,253,57,156,166,
4,13,197,111,236,4,210,29,189,6,138,191,238,16,233,126,169,49,210,1,162,29,146,80,112,12,103,103,148,23,101,77,57,26,156,45,99,42,119,114,193,184,248,215,80,201,72,141,43,91,58,165,34,117,120,176,155,
83,124,141,159,183,210,44,124,239,139,137,124,93,67,132,247,210,194,201,209,18,89,25,112,192,86,250,43,176,212,176,7,38,102,186,162,123,71,213,144,79,175,138,248,50,105,37,197,5,190,16,233,46,105,236,
56,138,110,27,207,24,50,134,79,160,52,84,166,97,233,38,182,92,189,249,48,172,202,163,214,250,78,251,222,230,252,192,160,242,184,173,69,158,11,55,53,211,54,120,6,88,6,200,97,243,94,81,132,113,12,227,246,
90,107,153,14,215,166,251,237,114,78,100,83,138,113,210,70,152,82,131,218,1,118,185,40,204,122,220,148,110,84,175,237,152,235,128,63,9,102,248,90,3,95,141,56,8,174,7,152,172,155,137,74,151,85,169,156,
159,181,16,4,85,58,108,98,111,90,62,111,240,250,192,38,154,205,38,211,233,20,182,0,252,13,179,156,164,55,23,98,2,65,100,165,29,93,16,21,106,16,218,80,107,73,101,226,143,251,253,254,198,250,182,69,134,
175,82,205,147,176,53,215,241,164,158,183,217,173,35,152,162,22,164,123,45,13,173,212,8,1,65,90,117,58,106,163,231,121,21,42,147,44,26,82,23,20,89,11,193,225,11,51,202,1,147,53,105,182,117,53,75,137,130,
3,27,70,28,161,175,6,125,99,205,168,26,215,212,172,6,87,153,207,103,147,241,24,238,155,206,83,195,244,138,53,51,208,226,142,101,252,136,214,30,55,143,229,93,141,181,218,128,93,82,88,234,193,234,26,159,
35,227,122,210,51,221,65,56,56,172,14,57,193,239,69,96,137,236,12,226,95,123,94,140,236,233,250,184,186,124,171,120,198,80,58,233,137,230,157,27,39,181,252,130,33,172,67,208,171,210,112,250,108,191,185,
254,184,181,209,73,199,221,98,146,167,115,228,176,68,96,43,179,51,9,152,112,209,139,175,117,138,172,1,221,73,99,5,22,111,123,186,211,194,108,87,64,102,91,49,187,172,164,242,28,26,30,43,140,65,100,37,55,
41,189,138,175,237,152,107,44,122,77,244,80,23,140,65,253,180,170,140,226,228,242,47,47,207,51,228,156,104,52,243,2,119,63,238,197,203,205,7,142,147,89,54,139,226,6,83,107,243,152,8,246,31,97,177,169,
119,61,160,99,22,5,221,24,65,231,137,255,25,206,224,199,4,141,121,145,198,20,12,194,162,225,135,58,58,62,130,187,100,72,217,136,146,174,112,254,71,244,201,177,197,225,180,14,185,33,214,165,128,37,120,
130,88,166,71,127,88,58,216,88,249,46,159,135,96,19,171,121,251,60,164,59,231,36,94,17,210,253,156,49,34,165,197,39,28,231,221,149,151,173,61,51,81,72,77,50,203,140,152,172,128,204,242,122,37,95,170,101,
155,51,59,103,158,141,128,34,188,241,104,104,177,61,22,123,18,163,32,128,176,155,48,10,181,196,154,142,170,88,137,220,105,105,132,234,199,130,197,233,175,244,225,207,32,140,217,10,195,9,48,87,105,163,
78,120,183,184,163,139,80,245,154,197,39,47,66,186,147,222,13,54,75,193,189,111,23,233,190,8,133,93,195,4,238,32,203,181,3,49,237,77,50,58,195,70,127,220,232,141,146,110,119,239,25,214,119,168,126,193,
135,27,170,89,56,242,157,128,206,210,157,160,29,197,189,78,49,239,231,163,24,172,160,144,1,73,130,204,44,225,125,93,79,127,72,133,21,82,31,11,216,62,232,215,118,12,65,209,174,182,232,1,246,149,134,231,
141,217,221,121,58,28,30,182,219,157,109,228,183,185,236,203,59,60,216,75,103,179,173,251,15,118,159,61,89,91,223,92,91,219,184,228,124,134,163,163,227,195,195,237,7,143,226,40,246,99,10,85,16,13,19,110,
56,52,174,182,52,94,103,144,205,181,43,119,251,49,54,156,131,213,42,198,77,41,183,212,245,60,155,206,231,105,145,131,187,161,216,50,18,192,221,169,201,83,86,66,248,133,29,231,7,234,149,67,180,151,35,130,
47,137,147,225,112,216,106,119,193,94,113,110,164,74,147,168,81,16,100,53,58,19,233,46,201,26,7,241,190,89,164,59,118,180,150,69,141,252,168,250,202,215,17,233,200,133,35,118,94,70,153,49,104,28,234,74,
135,28,11,59,139,138,26,62,103,67,39,200,197,164,102,30,197,158,166,179,249,124,14,70,138,252,214,144,66,254,154,251,104,8,46,47,68,160,146,192,231,172,53,121,11,88,61,131,195,170,209,24,143,198,221,222,
74,205,208,175,186,62,86,163,77,181,30,217,40,211,185,224,229,69,125,80,242,146,103,35,239,189,215,233,68,191,111,23,27,232,249,237,201,129,88,224,47,216,36,91,135,178,9,84,189,145,30,21,118,56,73,218,
37,21,104,249,23,9,35,195,29,133,139,222,9,88,168,230,124,184,157,192,166,195,194,7,209,233,43,223,196,196,162,137,142,5,77,2,74,150,27,17,2,17,229,244,19,95,215,49,140,111,188,210,162,51,96,242,188,49,
96,173,146,164,177,185,125,255,130,49,103,130,81,89,250,244,202,27,229,124,26,104,248,29,30,227,210,145,236,53,75,56,108,156,219,207,99,34,18,90,229,62,92,78,190,30,13,15,61,83,40,131,30,121,51,213,203,
231,162,171,156,107,249,172,235,136,102,0,30,214,100,50,142,147,6,132,57,141,86,71,250,222,85,98,237,184,214,224,160,37,103,34,221,3,105,225,194,59,220,56,210,61,155,205,142,14,247,55,182,239,17,31,255,
149,249,243,60,99,148,149,180,212,217,201,68,10,86,188,71,198,170,101,34,126,197,161,34,242,247,90,228,59,44,108,225,81,236,251,135,251,194,5,166,16,72,132,245,13,237,73,75,172,211,55,146,213,230,235,
146,223,132,176,213,162,200,71,163,81,179,217,154,77,167,113,163,37,61,134,52,213,176,10,83,155,9,119,185,4,133,245,11,98,100,162,251,116,250,148,183,140,116,167,42,158,38,1,149,200,234,154,9,228,29,84,
67,10,0,212,130,132,101,218,134,49,73,57,125,130,145,176,81,101,233,62,111,235,27,148,184,69,25,254,22,165,19,85,181,171,115,174,195,161,36,130,205,44,179,92,83,193,50,112,88,17,207,156,241,186,142,185,
206,162,115,171,236,89,99,152,226,6,60,5,248,92,123,189,254,124,58,69,116,91,96,90,29,68,96,66,244,61,153,140,170,178,138,226,184,211,233,162,215,80,148,179,233,136,132,151,3,151,110,131,224,173,24,30,
30,194,109,86,208,207,71,214,160,241,241,17,190,224,56,130,200,177,213,106,195,15,71,163,33,92,167,217,106,59,27,28,148,69,14,62,26,188,255,94,127,192,42,158,116,26,41,62,222,133,187,141,130,11,229,228,
161,8,115,39,99,172,34,138,40,27,26,1,116,34,234,167,118,91,8,30,33,159,229,204,189,71,225,176,118,13,237,152,138,114,244,77,8,248,42,8,68,138,56,120,218,82,240,57,181,157,130,24,124,26,9,82,156,233,60,
165,227,243,57,164,59,27,138,32,10,110,3,233,78,36,191,53,3,11,174,128,116,71,133,247,138,17,149,240,101,23,20,14,115,173,237,204,100,34,124,22,254,44,100,220,34,3,29,56,51,204,244,39,137,138,145,72,178,
46,148,107,168,38,223,170,118,27,15,59,10,88,174,194,29,87,156,48,118,34,122,68,43,198,190,2,172,54,230,22,169,18,50,155,161,193,98,175,141,35,238,36,136,83,155,194,69,60,108,240,178,72,119,206,22,192,
18,221,42,210,157,89,29,52,85,193,44,215,165,189,216,88,32,45,90,194,46,45,236,31,245,44,69,50,10,186,40,30,239,132,127,83,20,200,82,5,71,144,89,190,246,121,198,117,132,28,95,73,123,51,133,75,26,39,71,
88,59,244,0,92,65,245,245,28,83,218,242,170,139,174,245,34,73,113,106,12,123,155,37,149,42,134,135,251,71,135,135,131,213,181,163,163,125,240,86,238,63,120,244,244,201,71,240,221,244,7,131,221,103,79,
179,65,186,58,88,123,242,241,7,152,114,138,226,52,157,59,148,141,58,30,30,65,68,57,153,76,102,147,241,27,111,125,234,241,147,15,97,67,131,157,154,237,79,48,72,188,247,96,126,124,4,99,224,80,85,238,104,
41,178,108,239,232,137,49,225,214,189,123,181,208,168,179,172,145,97,47,194,17,131,75,151,172,47,114,249,49,10,165,42,24,193,39,150,8,149,117,242,130,93,105,36,20,21,177,123,181,232,142,151,158,91,159,
13,182,222,230,242,248,154,62,36,17,34,35,46,54,162,15,44,181,105,152,179,144,238,226,86,84,245,13,34,221,97,38,176,140,158,151,141,199,76,39,19,20,229,140,81,148,54,105,36,5,62,102,5,126,241,116,50,130,
119,1,14,121,129,12,45,45,56,87,192,95,22,48,90,85,53,90,237,144,248,72,61,171,4,127,223,172,85,161,29,100,68,75,25,81,190,30,46,229,209,83,136,252,74,0,225,138,22,153,53,198,5,209,245,17,229,70,188,155,
1,107,24,27,103,96,60,216,72,184,202,4,14,89,91,231,58,25,102,28,228,205,233,82,230,181,174,209,149,99,229,234,43,34,221,157,122,22,78,227,22,145,238,120,220,41,227,90,7,196,146,24,81,112,196,178,11,55,
36,211,145,40,235,208,106,119,178,44,11,17,248,140,38,44,36,155,5,7,17,92,23,211,156,38,130,215,137,182,239,156,235,88,229,138,23,98,205,152,207,168,194,164,47,149,141,224,145,93,205,250,165,199,184,182,
33,118,130,110,234,94,113,120,101,209,23,84,18,42,242,51,199,232,174,62,216,219,69,66,193,94,255,131,247,223,133,159,195,185,167,144,225,55,29,29,163,212,77,12,182,105,62,143,163,8,190,34,216,28,121,145,
111,110,221,239,116,123,96,185,224,227,161,235,4,168,28,213,239,55,142,142,32,132,25,141,142,225,10,43,253,213,181,245,77,248,215,99,252,126,130,201,104,212,106,117,182,239,63,128,119,113,120,184,143,
192,206,221,167,48,143,55,222,122,20,18,107,101,128,71,178,73,250,99,70,9,56,146,41,121,112,60,147,252,39,167,205,236,16,187,175,224,247,170,82,113,221,157,193,162,240,5,33,83,57,5,108,190,119,90,47,126,
81,82,7,94,60,70,187,46,31,1,187,83,124,228,120,214,2,1,91,213,33,146,10,159,131,116,15,77,228,217,120,111,10,233,190,251,236,73,153,231,13,84,36,152,147,155,22,142,135,176,178,7,81,156,212,229,16,30,
178,55,88,133,255,148,167,105,140,154,38,136,47,107,54,90,240,46,96,169,239,61,124,19,78,29,140,79,19,24,92,142,142,135,219,247,31,145,66,90,73,68,125,150,177,100,112,223,181,122,192,25,18,166,238,177,
78,220,206,24,79,99,143,181,175,93,123,64,13,115,166,84,149,123,110,197,5,86,166,99,15,92,178,133,131,229,133,184,167,210,174,8,102,185,50,102,221,249,195,210,20,85,45,90,159,181,67,204,179,160,55,25,
159,43,35,221,5,212,130,121,51,115,215,72,119,69,90,228,108,161,157,52,15,85,103,152,130,7,25,199,49,179,222,32,36,36,117,93,18,91,43,238,96,212,10,157,194,247,38,252,62,39,174,99,164,105,80,136,177,21,
174,133,32,33,68,42,202,46,64,105,55,50,230,120,52,252,173,223,252,202,95,253,205,223,48,53,205,77,221,235,26,116,201,23,35,221,153,38,13,174,19,199,152,169,25,172,173,195,247,0,191,213,106,183,14,247,
107,8,235,186,43,253,124,62,231,227,17,150,49,67,166,252,41,24,65,79,21,61,134,115,190,145,64,240,8,27,43,73,176,212,72,80,205,148,104,160,113,12,188,29,248,215,233,116,18,133,17,239,194,222,74,127,124,
60,218,219,121,182,253,224,33,188,161,18,153,203,162,202,181,193,59,225,77,231,59,106,71,196,203,78,40,35,221,49,57,32,167,55,27,108,166,123,195,211,190,172,216,245,182,212,128,35,94,27,51,124,168,133,
130,180,117,233,76,75,101,193,24,37,120,133,114,133,63,102,249,96,22,223,164,15,211,57,202,214,94,182,210,46,152,49,22,127,92,3,233,14,182,30,142,138,110,15,75,254,96,110,38,163,99,176,80,96,173,26,141,
230,214,189,135,240,95,247,119,158,58,1,15,187,185,117,111,127,111,7,44,215,250,214,246,222,238,211,28,14,114,226,26,4,211,182,177,125,111,62,157,28,30,236,205,166,227,110,111,16,133,139,22,28,142,94,
153,13,166,162,186,60,239,177,192,229,218,67,170,101,33,126,18,206,45,155,227,206,65,159,144,248,218,169,21,169,170,75,167,215,226,188,36,246,164,28,139,134,19,54,214,86,176,35,206,199,119,167,46,108,
18,14,30,151,17,243,165,41,172,22,153,121,248,114,153,103,226,50,72,119,126,141,139,174,79,161,196,187,121,164,123,40,213,61,218,87,76,123,68,13,77,53,239,72,22,207,49,66,218,42,99,224,69,238,239,239,
226,162,103,57,238,218,176,180,53,211,242,90,223,91,176,186,182,73,152,128,165,235,8,199,143,239,116,37,175,158,170,161,232,203,72,128,80,11,25,144,59,46,95,114,12,4,77,5,157,255,248,206,204,141,221,11,
254,227,213,23,93,157,39,250,226,77,36,92,133,63,128,39,31,125,0,246,165,215,235,67,108,186,186,177,49,57,30,61,123,252,113,24,133,43,43,131,78,175,7,241,248,112,120,4,159,1,122,4,74,59,170,104,189,247,
244,9,220,96,125,99,139,249,157,15,15,246,159,61,249,56,66,239,9,199,108,108,109,31,236,34,7,52,248,93,252,101,130,167,28,199,141,125,248,209,199,31,98,117,18,93,164,82,141,251,62,87,181,104,127,93,132,
117,86,52,93,164,127,36,208,81,38,37,63,34,11,132,211,171,72,83,174,8,35,147,26,209,218,161,4,47,171,4,112,109,135,60,222,229,188,39,68,224,10,171,138,65,77,37,69,42,171,19,203,21,125,210,16,0,216,60,
246,49,138,16,254,217,69,25,71,41,65,192,139,113,229,212,3,241,31,92,163,14,133,230,222,24,240,155,192,99,130,253,195,31,33,156,196,16,10,66,244,7,199,0,209,144,112,197,67,123,214,54,177,14,196,225,109,
73,217,56,135,189,151,231,76,200,68,149,1,75,201,207,218,179,12,236,170,3,2,62,106,223,41,232,242,227,174,20,109,24,195,21,80,22,162,106,170,200,115,63,16,139,119,160,171,130,88,25,208,153,69,169,42,250,
7,50,28,181,145,13,44,186,48,214,69,229,220,157,66,85,197,130,117,188,152,128,147,216,123,144,158,52,85,169,19,238,14,42,91,95,162,211,91,56,130,88,192,220,159,64,183,197,233,126,10,233,206,153,87,56,
118,2,164,15,84,92,135,178,202,8,248,141,221,78,163,87,215,214,230,179,89,225,148,20,107,138,32,192,40,119,219,221,40,137,54,54,54,107,107,152,46,89,200,222,78,72,81,6,172,242,20,80,87,26,166,18,85,121,
18,89,174,94,110,140,110,67,32,94,23,224,218,126,148,206,104,159,216,102,62,109,54,146,156,4,65,231,138,89,151,175,127,175,27,71,186,191,253,233,207,201,23,158,196,111,190,249,153,101,186,228,70,179,221,
238,244,150,41,149,251,107,107,155,155,247,151,199,60,120,227,237,83,180,203,96,215,86,7,27,167,104,151,183,30,60,244,99,192,127,192,57,119,146,21,76,183,11,154,23,219,215,150,81,236,20,171,24,225,232,
63,3,233,206,132,37,200,208,78,160,40,141,150,39,136,224,89,13,19,25,91,225,48,165,36,61,234,145,147,182,130,163,100,82,198,53,215,112,96,2,222,37,68,187,232,191,147,145,197,45,105,89,236,11,166,17,200,
71,237,42,253,66,112,74,215,15,164,101,231,116,185,131,135,94,185,14,149,52,40,148,62,216,223,121,70,218,154,184,8,240,147,131,131,221,195,253,189,102,179,109,68,137,207,72,68,226,248,88,173,19,37,53,
20,241,141,134,71,8,37,95,233,183,59,93,129,125,44,65,28,224,2,172,153,166,93,26,147,185,180,28,63,169,61,197,215,94,171,202,16,161,181,147,56,84,36,158,64,238,12,157,134,88,209,66,241,208,156,235,122,
149,56,163,226,239,48,105,76,96,152,63,190,138,227,22,171,184,27,19,86,12,88,33,59,16,96,135,102,173,175,131,116,87,11,142,7,7,60,190,93,164,187,207,47,46,255,130,83,159,23,132,186,71,195,111,108,222,
83,46,115,236,86,214,48,99,36,177,244,89,161,52,50,44,247,122,242,198,183,134,80,15,181,234,169,162,171,114,198,240,192,109,39,243,121,145,229,112,236,31,143,71,143,218,171,22,94,135,134,56,74,143,108,
56,170,34,171,131,159,35,221,253,24,38,99,91,70,177,43,233,73,178,231,33,221,193,1,165,156,0,42,192,240,152,70,210,192,52,150,82,105,154,177,7,132,60,86,86,206,91,166,154,23,78,90,9,38,69,208,178,219,
237,162,198,56,6,197,113,183,179,130,132,7,112,106,66,120,69,2,10,172,167,69,14,47,102,124,136,198,182,102,61,46,48,111,226,99,18,182,102,185,220,193,159,205,53,106,85,173,78,151,106,169,39,56,221,31,
60,124,115,185,4,209,234,246,216,234,193,183,192,99,214,54,182,28,239,59,56,44,17,132,132,88,78,173,107,65,108,46,37,46,169,146,80,128,53,52,120,150,208,250,48,164,179,118,218,67,46,249,74,56,76,132,67,
22,22,133,121,34,21,33,83,59,229,170,152,212,56,138,194,44,135,176,23,165,94,200,6,153,101,222,24,15,228,166,131,42,66,175,83,171,254,202,10,138,239,209,82,55,154,77,41,40,209,150,96,248,33,226,27,78,
33,221,145,10,227,69,72,119,207,3,81,11,77,94,45,188,29,183,131,116,95,152,201,147,191,128,233,12,135,80,63,15,13,47,170,115,103,141,129,29,127,234,198,154,107,60,55,138,62,143,140,222,12,138,142,194,
34,116,102,146,3,21,165,149,45,136,221,146,168,193,195,157,105,218,172,91,49,114,201,151,109,149,175,5,245,186,202,142,107,125,96,227,242,234,243,185,13,164,251,171,167,120,118,162,47,151,71,186,235,154,
52,120,52,156,234,9,143,89,25,172,205,230,83,69,13,94,28,170,24,74,152,179,76,97,69,249,54,49,144,6,175,6,214,173,209,104,244,122,43,83,170,51,36,113,140,76,135,113,204,5,71,172,145,25,100,160,133,89,
48,251,40,249,65,96,67,43,60,90,148,65,6,136,146,105,32,141,125,174,220,17,135,225,43,65,186,35,218,20,19,71,21,230,53,9,202,163,180,200,29,114,157,157,19,151,228,207,10,36,200,53,108,115,200,90,159,224,
117,32,164,187,37,194,222,72,133,181,97,62,21,51,24,172,67,200,90,32,8,139,242,152,101,69,24,92,225,135,96,245,29,90,67,169,59,101,249,28,142,147,222,202,10,11,217,197,73,204,226,123,222,45,138,21,146,
104,151,170,58,133,116,15,169,80,118,81,28,45,100,142,30,95,167,68,2,217,37,43,111,30,233,78,0,217,250,2,148,182,117,154,92,231,161,225,61,138,93,57,8,153,58,159,124,227,102,209,231,137,170,183,109,10,
78,243,161,142,167,58,201,170,154,199,4,244,187,16,101,164,105,58,30,141,225,206,57,28,248,58,72,77,251,176,42,187,170,24,4,85,91,103,207,84,50,175,131,87,139,116,127,29,40,158,107,121,209,87,64,186,231,
153,110,89,19,183,242,236,56,230,49,81,132,159,1,216,145,24,11,50,8,5,80,220,248,70,169,22,184,218,160,223,71,112,83,89,81,98,7,169,180,225,243,26,79,198,76,112,8,95,26,4,80,24,125,59,133,183,0,149,44,
140,45,99,174,83,176,232,27,37,76,75,207,234,167,150,42,95,203,165,140,138,254,184,123,66,158,173,123,15,145,38,193,201,74,57,196,153,19,79,92,36,55,29,255,151,93,208,183,82,164,114,34,110,229,11,76,245,
124,213,212,93,221,41,244,144,145,238,224,3,162,0,42,41,177,131,163,57,45,166,142,129,157,86,18,187,50,123,176,249,9,211,199,37,177,54,252,117,50,153,192,11,98,198,190,149,94,159,81,199,140,116,111,169,
102,165,202,153,157,59,110,70,225,116,39,221,110,123,46,210,93,115,53,192,178,69,118,176,44,141,130,161,164,44,115,179,72,119,179,4,237,20,197,83,222,67,252,11,78,143,64,26,107,184,51,138,82,50,198,55,
40,121,20,251,242,152,51,175,67,224,135,138,64,127,142,117,67,59,93,28,170,187,97,126,145,245,143,47,61,166,103,234,71,38,133,131,248,35,219,60,180,113,90,87,126,12,33,24,49,123,130,115,9,131,229,235,
148,218,12,117,227,227,26,222,144,122,160,178,158,169,174,52,159,51,159,235,69,107,248,226,49,151,185,206,237,141,33,93,120,76,208,194,24,66,9,5,78,107,158,177,54,34,190,116,106,76,57,111,152,56,163,54,
45,1,154,113,136,4,55,156,140,39,240,57,189,253,169,79,125,243,27,223,4,183,8,118,202,230,230,58,88,43,42,162,69,204,195,57,193,70,233,41,177,155,135,113,20,183,90,173,6,42,120,83,202,13,95,65,21,183,
170,98,150,84,72,166,28,112,20,105,156,38,5,87,234,248,239,21,167,172,40,42,36,123,103,124,15,157,43,166,81,182,251,78,198,196,73,130,202,7,162,68,105,89,92,135,51,95,4,232,71,128,11,50,32,90,214,40,195,
49,148,85,53,30,146,182,28,183,114,152,9,255,54,182,147,150,110,26,43,189,59,240,197,173,111,108,135,84,179,159,207,231,176,96,159,250,212,167,190,1,75,141,209,180,221,218,92,47,101,169,99,172,165,86,
21,140,153,205,102,44,109,27,71,17,56,182,16,249,138,50,27,9,250,181,77,107,30,164,124,47,226,120,240,36,207,234,100,28,29,241,79,28,57,161,127,118,175,213,40,94,36,89,43,34,7,167,211,90,160,255,117,45,
216,21,145,143,51,236,168,94,122,12,57,255,202,188,32,37,9,207,99,9,194,251,66,52,60,145,196,219,11,82,155,103,34,203,185,6,39,148,213,151,70,159,15,84,62,208,249,84,133,79,235,132,113,113,203,99,210,
116,198,82,225,240,37,212,14,43,180,124,157,82,7,79,84,123,91,103,91,42,143,117,116,128,34,148,175,0,233,254,154,80,33,95,3,233,142,151,157,55,163,118,22,183,243,114,218,82,100,7,227,24,226,142,193,120,
52,132,109,178,58,88,255,237,223,254,250,247,255,242,47,33,98,217,218,218,200,178,156,11,53,224,160,149,53,162,189,192,66,113,171,19,218,205,40,92,233,175,131,57,180,14,81,129,12,241,200,242,219,166,132,
178,19,165,167,144,148,3,88,254,182,67,199,51,135,41,212,165,82,198,85,17,234,55,62,134,232,43,16,118,64,42,30,90,45,33,221,93,55,37,114,186,131,1,6,71,72,122,0,207,138,55,153,175,125,84,77,186,170,211,
178,173,99,61,226,106,34,4,116,253,254,218,100,60,42,139,122,99,125,235,127,248,247,191,251,95,254,252,191,128,161,223,216,88,159,206,102,105,150,121,118,124,184,90,3,143,173,128,23,13,254,218,93,89,173,
150,124,162,21,221,131,111,28,110,225,185,225,175,132,116,119,232,31,151,51,32,19,204,215,33,206,143,240,134,145,238,70,69,23,255,2,187,173,130,134,151,36,45,165,36,67,28,83,73,38,85,154,236,46,190,177,
247,162,29,178,28,147,250,176,77,17,181,107,171,203,163,207,187,22,173,213,72,69,251,42,49,250,244,152,178,200,135,71,251,24,204,87,53,69,58,250,253,31,255,115,167,215,27,244,87,147,70,211,95,7,92,179,
167,54,89,71,219,87,192,129,62,214,209,221,35,221,111,181,149,225,42,99,174,140,116,39,225,186,192,194,6,110,166,117,218,180,53,87,163,212,234,234,198,199,31,125,144,52,146,111,126,243,27,7,251,123,223,
255,193,247,251,43,125,234,31,170,56,24,129,49,16,200,112,1,43,164,224,16,161,24,107,91,154,27,110,152,128,92,21,81,51,43,179,24,193,52,220,101,11,231,166,213,78,153,221,186,234,187,230,122,160,161,110,
184,19,229,5,245,138,75,25,108,244,169,202,89,115,23,211,114,50,209,144,102,85,69,49,138,235,9,63,59,222,148,103,53,54,197,104,160,51,177,19,234,207,197,152,178,63,88,251,232,163,15,154,173,230,55,190,
241,31,118,118,118,254,234,7,63,128,165,38,77,182,154,35,110,203,32,75,227,250,78,225,135,81,180,182,182,65,234,87,180,112,202,134,86,131,123,53,177,83,134,31,93,17,233,238,231,108,153,5,79,208,249,181,
231,134,183,72,175,122,179,72,119,136,117,239,44,37,233,212,4,68,211,140,139,38,140,134,191,60,250,188,161,243,129,74,199,42,216,213,17,87,134,253,24,120,11,59,207,30,83,250,2,25,248,3,236,80,195,232,
7,166,51,29,143,243,52,133,49,143,30,189,29,132,161,191,215,14,156,1,186,88,211,105,6,75,113,231,72,247,91,37,237,191,194,24,114,115,152,175,157,83,27,85,181,140,116,23,126,209,0,223,216,137,49,243,227,
102,115,109,30,246,14,211,195,62,163,145,126,242,222,143,225,231,95,126,231,215,193,192,127,231,63,126,167,211,110,39,141,184,22,169,46,222,199,154,63,31,78,47,160,167,176,186,41,80,55,215,185,219,92,
157,32,165,212,180,227,75,93,94,82,138,82,136,134,203,65,104,169,40,138,41,85,125,202,34,4,244,165,190,194,82,134,144,114,162,157,69,168,39,229,176,224,196,67,91,130,156,238,36,122,70,208,153,218,21,7,
207,129,233,137,116,151,61,176,135,15,213,253,45,181,241,84,239,50,112,228,131,247,223,133,35,249,55,112,169,205,119,254,227,183,91,173,38,44,117,193,159,179,10,217,67,128,19,33,10,35,182,89,73,28,175,
172,110,240,26,138,246,154,173,55,53,254,100,8,255,179,250,234,156,238,126,206,138,10,119,82,89,94,112,81,72,230,93,223,12,210,221,224,43,175,130,160,117,135,28,225,14,53,206,61,226,142,213,251,242,232,
115,120,21,15,116,90,41,179,163,90,203,99,224,159,119,119,158,32,70,156,43,232,180,97,72,14,35,129,13,51,157,76,90,173,118,154,161,160,241,199,31,253,164,217,106,175,111,108,251,123,61,85,205,55,236,228,
190,158,253,164,110,215,92,57,189,67,164,251,235,192,233,14,110,50,150,80,78,243,181,123,6,17,77,192,28,230,35,47,153,32,168,114,66,170,217,176,223,88,61,142,87,198,217,176,11,255,58,155,77,31,61,122,
244,43,191,242,203,255,199,31,255,49,12,90,233,247,67,164,28,64,14,53,120,29,204,23,204,54,18,204,85,183,219,111,180,58,181,212,203,28,237,114,111,164,76,149,31,15,224,37,240,1,199,184,121,227,146,105,
140,177,160,54,99,203,205,137,101,117,186,250,62,174,171,87,196,233,238,186,100,152,124,131,30,214,139,77,44,50,202,76,216,74,13,128,138,144,229,113,16,86,246,108,100,57,231,182,225,81,15,205,112,67,175,
111,212,107,135,230,8,94,214,116,58,189,255,224,193,47,253,247,95,248,246,183,191,141,140,155,189,30,28,18,1,162,28,74,66,201,25,39,83,136,201,164,149,238,160,37,160,48,197,136,249,218,86,247,204,86,104,
163,143,243,39,133,41,151,239,133,72,119,92,222,250,242,49,50,172,118,5,225,22,37,63,57,207,239,117,207,106,170,55,220,0,210,221,147,21,223,129,204,228,77,33,221,183,116,14,151,121,108,91,74,45,198,148,
101,62,58,58,40,178,156,27,86,184,183,19,41,132,102,179,201,100,196,30,251,108,142,249,93,110,216,230,63,182,239,61,244,247,250,176,110,188,105,230,107,106,118,168,59,119,140,116,191,61,210,254,203,143,
33,6,190,210,163,216,151,208,88,140,98,23,134,54,39,167,110,93,189,156,108,89,21,102,163,86,220,153,70,157,201,227,247,199,224,216,254,246,111,255,246,223,254,237,223,126,248,225,7,143,30,189,57,88,93,
131,209,243,217,4,12,25,165,20,84,16,197,73,210,104,36,45,214,106,116,32,117,65,188,132,173,177,14,179,108,212,174,242,5,206,222,8,209,157,96,3,249,180,99,22,32,62,155,2,99,78,213,152,124,121,225,213,
40,81,58,34,1,87,202,20,164,251,162,246,231,136,219,93,72,24,148,245,185,200,114,105,169,81,118,86,207,15,244,225,170,238,175,216,222,63,239,254,127,85,89,126,253,235,191,243,119,127,247,119,31,124,240,
211,71,111,188,9,193,56,12,159,79,167,243,249,84,186,8,67,212,152,72,26,205,0,117,65,181,51,153,150,17,243,3,221,79,84,124,160,80,138,149,104,250,180,242,52,26,212,30,116,67,186,103,244,210,3,240,142,
108,81,20,47,135,116,87,204,54,25,221,89,74,242,37,145,238,112,86,183,109,121,100,35,5,177,219,210,152,131,253,29,100,3,65,141,35,214,2,193,64,195,30,141,254,244,79,255,239,178,44,224,96,39,207,194,228,
121,193,177,125,29,71,245,108,250,236,217,147,7,247,223,224,123,193,59,58,182,229,74,157,237,219,162,22,180,213,29,33,221,95,3,78,119,177,253,231,33,221,189,86,21,69,55,14,233,190,52,166,206,154,72,218,
212,156,29,236,239,253,254,239,255,126,150,102,223,251,203,191,220,218,222,26,172,173,179,135,214,106,119,219,157,30,171,156,80,129,41,160,180,135,114,181,127,225,87,136,123,104,173,138,89,211,230,77,
67,61,210,236,205,113,253,201,171,67,123,164,59,29,75,204,87,20,136,186,195,203,33,221,175,49,198,214,86,244,148,205,114,203,81,224,10,139,238,233,164,160,137,216,180,136,8,94,136,58,38,162,58,70,41,174,
34,60,35,167,231,233,169,2,114,231,3,226,173,171,176,22,138,39,232,68,79,224,175,93,213,222,219,221,249,230,183,190,133,75,253,189,239,221,191,119,111,99,227,30,185,126,170,221,233,118,58,61,207,251,190,
132,152,215,194,215,78,141,189,27,106,45,177,201,80,141,38,118,42,99,176,53,10,139,176,21,17,91,51,57,189,48,7,49,123,250,89,241,47,184,206,39,99,100,153,243,73,52,188,196,200,47,201,251,30,124,233,75,
95,194,141,168,195,23,202,99,120,49,146,151,29,67,239,216,229,86,180,43,151,139,238,14,35,203,121,179,157,57,102,69,231,77,85,239,216,164,242,236,31,90,237,239,63,165,110,219,146,68,147,80,252,14,188,
0,136,5,199,227,105,129,208,194,98,145,131,116,64,42,182,72,101,85,64,192,24,70,33,223,171,212,65,95,23,240,243,76,133,23,204,199,92,253,217,193,233,104,52,91,55,182,134,55,58,70,57,150,66,239,55,73,36,
136,159,77,232,200,179,116,189,12,104,62,107,140,173,226,241,97,186,177,182,245,133,95,250,194,159,252,167,255,4,46,212,253,251,111,176,43,135,1,17,173,30,86,165,23,90,11,114,65,22,236,129,175,32,233,
143,130,184,174,167,189,58,107,51,105,4,229,55,107,223,204,204,69,109,41,126,211,123,196,143,71,180,30,78,168,60,128,69,152,207,103,113,210,224,206,4,87,58,56,141,24,96,252,253,75,142,17,53,3,171,146,
36,54,164,127,78,242,206,74,172,172,93,128,215,241,196,197,2,67,4,123,21,2,112,2,136,20,212,246,168,205,18,61,161,117,228,250,68,84,23,22,56,6,79,122,1,57,130,159,85,205,14,198,251,253,245,254,47,125,
225,11,127,242,221,239,182,91,237,173,123,15,89,164,203,243,241,75,127,128,195,28,196,97,196,219,24,81,44,42,216,212,27,177,138,246,234,131,137,157,248,49,24,3,226,106,91,1,115,25,35,12,250,14,197,142,
221,215,20,111,162,179,19,132,28,161,139,23,236,52,133,24,166,135,136,121,164,102,140,4,212,225,198,112,175,8,10,74,6,17,153,161,146,155,16,49,229,76,167,140,224,183,141,192,18,78,141,89,132,132,119,150,
146,124,73,164,251,170,74,39,117,80,114,96,67,99,178,116,94,17,63,44,35,58,171,202,162,0,117,93,97,111,54,251,4,142,228,210,128,13,211,58,205,50,216,51,21,86,109,209,225,216,221,123,250,40,121,139,187,
69,193,170,205,77,210,87,229,65,29,254,139,66,186,47,116,169,174,200,233,126,106,204,116,148,253,222,55,190,254,231,223,251,94,90,102,159,249,87,247,145,248,88,133,12,112,167,110,71,203,46,128,52,48,59,
195,135,252,235,141,52,104,206,225,63,101,71,221,186,196,66,10,111,107,171,188,98,133,172,126,128,205,115,200,69,103,8,233,94,136,114,242,25,229,133,187,65,186,87,4,26,10,8,70,243,193,79,223,3,79,22,158,
116,123,251,126,183,219,19,62,75,229,234,152,138,101,37,52,17,90,24,222,90,75,137,93,223,100,121,2,233,206,248,15,81,150,167,84,20,191,136,163,116,248,123,95,255,6,184,177,69,94,126,254,237,95,156,169,
89,77,172,31,162,235,69,104,120,237,165,208,28,98,62,212,65,167,110,119,117,7,110,182,99,247,115,157,137,138,149,131,85,242,27,230,180,39,197,182,74,152,71,111,46,142,38,210,14,1,102,95,29,233,174,22,
93,139,119,38,51,121,109,164,123,84,101,86,151,19,221,230,221,207,99,166,147,99,10,140,107,110,205,69,111,34,68,196,211,100,50,101,117,3,78,51,195,242,19,239,160,106,183,90,96,179,152,204,19,139,77,161,
133,173,214,106,181,249,94,195,74,183,140,237,6,122,242,47,6,233,46,0,189,90,136,249,207,68,186,139,111,197,60,225,238,40,62,53,6,174,252,206,87,190,188,127,112,240,254,79,222,255,252,47,221,143,155,165,
82,163,124,110,84,214,180,37,186,9,238,131,215,252,37,88,93,64,108,26,52,83,162,124,80,101,218,40,38,77,58,22,42,143,116,167,126,78,38,126,164,170,150,148,162,224,111,165,171,190,139,92,3,151,14,234,59,
68,186,215,2,184,65,182,159,157,103,143,25,98,214,105,183,26,141,214,100,124,12,14,181,23,90,102,82,32,18,133,15,156,204,170,75,38,138,87,203,68,236,82,21,103,159,158,112,240,146,110,12,216,108,179,214,
188,50,121,157,127,245,55,191,118,120,120,248,254,123,239,253,235,79,253,155,150,109,246,84,39,181,217,24,182,45,196,142,154,219,125,42,143,98,7,179,19,219,24,162,200,150,106,194,234,205,85,58,210,19,
48,112,212,31,165,157,80,226,162,139,145,60,240,91,132,13,114,155,18,81,126,94,209,234,57,15,75,221,89,74,146,184,125,175,201,179,222,34,243,159,187,192,28,198,32,103,80,37,47,134,211,237,73,146,164,105,
138,64,105,60,82,4,106,204,211,41,169,34,3,214,42,137,99,28,76,53,26,216,27,179,217,180,211,233,242,189,50,75,157,83,40,104,22,223,25,167,251,45,146,246,191,104,140,35,41,227,250,156,122,142,211,93,137,
232,166,231,87,160,235,178,112,241,41,222,119,8,94,126,250,211,143,118,118,158,188,245,230,167,203,137,41,38,101,208,204,162,102,22,38,216,23,149,144,225,100,209,28,19,96,23,61,230,128,225,171,130,205,
155,117,170,89,131,146,81,224,93,80,57,209,88,230,69,97,186,206,202,50,152,206,82,180,34,212,90,44,80,95,251,22,54,37,13,210,245,130,180,71,191,36,167,251,11,203,20,240,231,222,238,179,163,35,100,178,
111,54,155,113,28,131,217,58,30,13,169,183,239,227,251,15,222,196,86,109,161,57,177,76,163,234,60,117,226,12,193,100,34,215,118,36,92,231,16,76,154,160,137,44,61,68,252,77,197,28,123,226,155,162,246,87,
252,211,159,124,248,244,233,227,183,222,254,244,145,26,142,131,73,179,106,182,85,107,203,108,112,89,183,70,170,125,236,103,12,80,77,53,228,250,3,152,185,97,61,154,233,25,81,50,112,162,210,120,189,43,207,
31,111,29,138,253,86,33,129,33,141,161,183,124,5,203,24,186,212,192,53,77,105,158,231,200,99,31,193,153,12,39,158,238,247,87,3,204,79,171,225,240,16,79,236,48,2,143,186,217,106,167,115,240,246,109,210,
108,230,105,214,108,52,27,173,214,245,120,214,67,67,2,153,220,111,201,95,96,150,242,38,34,73,244,28,236,206,108,54,163,146,188,230,78,8,45,105,90,169,124,193,67,128,211,14,238,125,179,209,200,242,156,
201,212,203,44,99,154,87,170,28,83,30,23,249,127,255,37,32,221,57,212,18,213,3,88,141,231,144,238,92,146,151,176,154,247,27,183,185,171,133,248,240,2,13,15,139,223,237,13,248,108,192,235,206,59,224,188,
234,168,192,14,104,83,25,228,194,160,22,249,10,149,193,138,10,110,19,84,121,228,18,231,150,168,166,2,163,23,2,10,172,114,66,28,42,194,252,65,87,120,197,72,119,198,138,101,249,124,111,119,103,52,58,134,
201,116,218,232,161,131,203,131,97,87,128,48,236,249,108,22,148,58,9,91,96,50,34,212,235,192,111,173,10,224,36,44,144,165,85,213,153,205,56,17,206,65,162,107,218,179,194,158,35,125,33,220,61,2,15,200,
64,19,22,212,193,97,213,172,90,89,89,211,78,232,115,26,204,38,118,18,149,17,248,95,33,220,78,35,89,10,252,126,161,203,90,207,225,118,69,13,7,81,97,131,154,149,86,149,147,89,211,190,142,73,249,101,70,186,
151,120,106,84,119,3,9,164,78,128,128,146,155,151,64,186,139,241,43,38,24,64,71,93,118,181,12,29,161,44,123,9,47,39,164,239,28,25,29,240,133,37,203,99,178,52,59,58,216,131,43,180,219,29,176,74,224,9,223,
123,248,104,247,201,147,121,58,111,54,91,233,252,0,94,201,250,102,56,157,140,211,249,172,209,104,130,113,56,44,171,135,111,190,221,72,154,44,51,128,217,16,92,60,114,223,29,3,87,45,122,203,209,169,49,240,
214,114,124,201,149,31,131,86,42,47,24,167,221,237,246,70,163,145,75,237,9,15,47,177,204,145,110,179,107,42,103,88,67,89,177,152,43,102,151,202,186,32,255,78,187,243,13,11,144,23,204,7,105,30,47,183,62,
126,12,157,139,234,226,49,151,185,206,77,143,169,248,131,119,196,197,136,108,164,200,197,40,159,84,87,76,16,104,136,126,128,107,133,194,143,234,129,81,74,8,94,2,239,135,18,105,1,92,155,106,187,69,204,
198,165,228,38,56,174,188,10,239,19,125,57,70,123,138,64,62,232,125,206,144,201,166,68,222,79,24,180,180,128,78,150,144,238,226,229,41,123,55,72,119,238,206,251,248,163,15,96,207,71,113,12,190,213,60,
77,107,201,211,49,15,15,186,101,239,127,240,238,151,62,251,14,110,92,13,81,37,126,123,137,142,155,186,73,105,56,28,49,81,147,113,61,201,235,34,240,101,132,69,145,145,165,128,42,98,37,173,60,108,157,21,
140,252,142,170,69,67,219,112,31,117,110,114,90,198,212,145,143,250,2,175,246,88,237,37,101,44,65,186,11,167,59,229,50,9,144,103,205,29,66,2,153,107,144,23,141,166,119,33,210,125,153,79,246,26,47,53,194,
250,154,238,245,7,107,107,27,71,71,7,199,71,71,16,207,207,231,243,254,234,234,218,250,198,193,254,222,240,232,128,199,192,29,183,239,63,156,140,71,135,7,251,152,42,69,173,55,220,101,247,212,156,56,154,
185,8,171,60,161,15,161,52,51,223,126,249,68,55,224,238,49,124,243,86,100,126,88,162,35,203,51,198,184,24,113,176,107,250,171,144,54,113,32,231,153,222,184,2,29,81,59,17,248,134,237,86,11,12,107,35,193,
79,26,78,203,40,138,185,102,134,114,187,152,26,209,18,101,184,123,81,51,39,23,11,213,149,55,189,122,13,180,157,207,30,99,25,110,195,217,22,36,129,113,27,220,171,113,177,200,3,91,115,30,83,123,244,144,
90,136,74,57,86,101,92,111,119,29,183,242,39,198,72,60,199,193,157,139,52,149,16,147,184,3,150,101,169,188,158,132,67,185,235,115,144,238,236,83,221,5,210,157,219,103,127,252,227,127,6,235,223,106,183,
53,178,42,207,248,115,231,240,138,49,4,100,146,103,255,176,255,15,131,245,117,46,25,41,167,208,21,218,8,44,87,203,54,58,170,221,51,189,169,153,29,219,81,137,2,244,124,216,90,127,23,121,95,106,81,67,231,
246,23,38,26,229,116,135,113,225,188,114,204,246,74,224,28,198,114,117,91,9,218,235,228,24,65,186,179,235,250,58,64,2,93,97,84,18,151,103,35,221,151,13,214,245,106,133,240,19,240,158,10,176,28,243,185,
236,36,228,21,25,199,73,50,37,233,17,45,157,232,10,34,71,122,19,228,91,211,255,112,221,85,237,149,8,240,80,21,104,79,197,126,49,55,133,91,39,211,200,36,222,134,154,251,4,137,78,197,78,166,88,155,162,54,
122,196,167,59,205,93,62,33,182,83,190,185,132,58,78,3,238,101,231,77,22,168,0,28,53,77,166,93,216,30,181,94,100,73,221,189,248,187,224,194,208,85,55,253,43,111,19,185,96,76,96,100,12,106,133,96,143,148,
136,65,9,199,158,200,178,41,214,218,227,21,99,193,40,145,171,64,170,54,94,31,237,142,116,189,124,29,77,252,10,18,109,209,24,134,170,16,153,154,244,147,178,55,87,107,187,224,90,193,179,86,179,154,73,237,
118,38,31,179,167,144,238,180,119,3,222,220,203,229,133,91,64,186,75,204,194,170,101,84,161,78,25,171,193,245,53,159,233,100,71,18,158,125,103,247,73,187,135,84,212,17,162,216,43,150,31,174,108,57,169,
243,137,154,134,42,232,170,78,71,183,27,122,125,95,31,230,42,167,207,65,215,142,180,144,89,202,8,67,128,240,37,82,178,48,236,189,114,102,172,98,253,85,50,69,152,12,194,36,32,134,20,138,52,123,2,162,57,
46,202,82,250,225,208,71,53,172,74,25,58,190,118,156,234,235,5,9,196,80,0,63,52,73,18,169,51,144,238,215,174,21,114,102,4,98,138,39,79,62,82,68,73,14,177,222,230,214,246,254,30,210,135,179,62,5,231,16,
249,165,98,141,150,248,76,216,60,65,92,246,177,141,120,11,202,161,94,83,11,43,25,142,218,53,127,144,3,133,88,206,210,234,14,162,9,145,204,144,73,17,41,51,20,160,106,113,96,96,33,248,112,9,152,162,151,
140,139,0,175,140,114,103,176,98,143,55,137,19,8,154,44,145,43,194,60,97,75,177,170,2,37,62,170,92,69,11,208,144,187,23,39,131,164,5,228,138,155,254,213,182,137,92,48,134,25,223,145,31,28,87,187,228,226,
26,108,237,40,16,36,154,145,34,96,77,110,130,120,95,172,103,35,129,140,168,30,40,199,156,85,113,142,159,107,187,145,19,185,226,53,228,49,222,134,186,246,224,128,195,33,14,41,101,76,237,212,38,232,4,65,
236,173,227,131,99,108,4,35,221,69,130,143,168,65,111,27,233,46,190,9,33,137,6,131,181,253,131,61,38,99,197,206,74,110,216,118,58,67,68,40,128,101,5,88,181,103,79,159,188,241,230,219,4,63,14,217,5,19,
68,27,102,99,171,145,25,207,212,124,67,175,109,169,141,3,117,52,55,105,197,66,197,188,32,52,14,91,166,202,19,32,0,87,19,151,23,68,52,90,20,179,211,145,36,186,144,6,253,107,229,61,20,246,215,92,219,0,163,
207,149,8,142,25,243,114,120,206,27,31,131,109,60,212,51,206,225,161,229,76,37,216,217,147,30,214,149,107,133,5,189,167,164,213,220,186,255,192,213,71,171,78,183,15,127,46,195,73,90,237,14,239,99,120,
205,240,39,155,71,74,229,138,154,128,163,221,97,118,101,237,94,252,233,49,21,188,157,186,96,143,209,233,72,71,66,119,104,181,139,7,235,218,109,232,133,80,21,117,89,215,78,211,220,157,252,81,28,39,5,178,
205,37,1,38,74,45,223,43,210,106,76,215,60,111,62,94,236,224,242,155,254,213,182,137,188,112,140,103,188,146,106,27,57,68,218,247,229,56,56,2,227,111,153,76,210,225,59,172,102,132,180,18,207,136,178,253,
254,58,212,2,194,34,96,39,198,40,66,186,75,16,200,232,36,118,28,56,49,229,212,231,29,225,47,186,121,181,99,155,126,158,211,93,223,32,167,251,5,99,132,4,142,166,180,186,190,57,157,142,225,15,229,228,203,
124,45,217,101,52,40,230,173,170,25,120,254,147,81,171,213,42,233,203,36,180,21,122,243,149,35,249,133,96,240,153,221,93,215,107,107,170,127,92,143,143,113,247,185,194,182,236,213,226,252,214,31,71,89,
229,138,143,53,159,241,202,120,152,155,114,103,12,207,173,198,60,85,173,61,23,187,20,163,94,39,242,219,147,161,9,142,169,11,216,180,70,159,204,97,93,179,86,232,234,55,151,124,241,162,224,36,22,223,165,
114,45,119,30,216,147,221,0,167,199,228,180,113,141,69,141,77,30,211,104,52,230,179,105,28,37,188,125,185,146,34,1,51,189,30,95,233,163,172,48,78,215,184,74,60,183,164,134,17,82,199,185,19,8,134,148,84,
118,65,24,203,121,243,57,213,2,114,153,77,127,103,109,34,215,27,227,9,216,4,209,73,137,59,167,32,201,234,137,240,22,100,135,177,11,86,91,142,139,93,133,203,193,231,197,152,179,103,39,205,152,228,122,184,
122,171,207,88,41,23,170,179,213,99,228,42,255,118,109,157,10,142,94,0,91,156,161,194,150,105,172,97,161,184,116,192,84,238,234,70,57,221,207,39,89,226,195,207,112,159,205,74,127,144,229,57,203,47,242,
175,184,227,144,129,5,108,145,116,94,228,187,187,59,176,81,217,172,192,152,40,138,219,221,110,187,213,101,105,44,78,66,236,170,189,129,238,247,76,15,62,4,240,185,22,81,208,21,222,169,156,58,218,167,216,
41,31,164,28,207,58,89,4,234,121,8,140,111,225,144,133,173,133,67,226,122,120,206,75,193,253,40,125,201,134,2,239,245,156,219,248,252,152,231,175,19,62,47,229,118,165,151,10,190,201,246,253,135,141,164,
97,47,189,57,4,180,171,28,213,178,56,219,104,26,194,200,80,105,201,74,234,246,185,49,181,14,192,51,132,88,110,70,45,225,48,6,187,58,131,128,115,174,156,41,99,132,4,159,69,198,44,230,227,197,135,249,155,
36,26,78,82,87,12,35,110,97,231,123,53,233,65,114,123,209,124,174,177,233,111,252,227,185,145,49,161,211,28,230,207,204,250,196,39,153,214,154,146,28,134,158,188,82,149,72,7,203,230,162,250,186,251,30,
56,118,22,145,55,150,182,84,46,101,168,117,45,248,59,227,62,117,73,173,51,27,9,55,46,179,234,184,113,141,66,112,109,12,189,41,53,230,153,96,25,60,204,34,90,44,243,71,236,233,140,12,184,35,78,119,67,189,
114,236,182,172,172,172,86,121,62,158,76,230,233,60,148,102,12,175,178,172,125,201,15,83,22,69,129,68,198,172,86,77,222,61,124,135,187,59,207,214,214,55,59,157,158,3,26,218,35,59,140,116,180,166,87,11,
187,147,193,30,116,41,191,107,189,119,103,178,132,215,5,1,59,48,7,196,45,82,32,194,135,65,192,32,85,247,78,192,145,161,215,170,111,199,205,215,203,220,240,176,2,108,121,229,83,117,99,148,171,190,41,228,
53,204,151,199,160,44,211,178,169,186,6,43,22,152,201,102,210,66,82,68,210,118,190,36,51,20,43,103,90,207,189,72,253,22,204,138,37,93,56,213,217,99,50,204,248,166,131,208,102,117,32,99,20,210,233,207,
82,76,195,163,98,56,174,130,130,191,134,134,175,179,232,255,144,176,129,188,9,110,30,108,64,36,8,27,58,207,155,205,118,77,222,20,220,171,173,51,248,90,11,147,152,243,231,115,141,77,255,170,4,17,174,52,
198,235,126,99,186,16,59,66,52,31,189,176,18,134,133,159,61,130,1,235,30,178,227,165,130,66,45,130,174,50,37,114,120,168,41,88,151,36,133,64,146,121,40,112,192,141,32,214,16,213,54,187,81,37,193,80,145,
116,191,40,56,18,36,131,168,25,211,39,169,150,154,132,114,28,195,173,168,36,72,60,43,201,174,187,225,116,103,117,27,38,185,255,87,235,191,248,195,236,255,13,16,216,87,16,205,177,118,205,68,244,4,196,205,
11,127,164,105,58,159,207,67,250,35,142,34,120,15,179,217,12,158,110,124,124,52,25,15,55,183,30,250,6,205,103,229,238,163,240,193,150,222,252,72,61,17,87,13,63,251,242,229,223,59,75,245,192,7,75,61,9,
16,70,212,28,195,250,215,202,145,143,184,20,148,28,112,169,175,83,157,222,244,29,156,235,238,9,58,95,10,196,84,111,241,220,240,34,76,237,36,47,133,103,217,37,34,60,174,72,249,142,95,202,209,248,49,184,
37,184,249,89,140,99,144,112,80,40,129,30,133,122,94,151,152,54,16,243,83,191,212,24,150,27,208,18,166,201,38,243,7,178,35,138,213,231,141,129,31,245,108,49,2,231,192,53,103,130,147,149,231,105,133,48,
247,90,186,255,92,72,194,128,93,174,24,122,125,74,94,225,86,171,197,232,132,173,173,123,81,28,11,210,87,213,235,54,61,178,81,138,173,246,231,206,199,53,225,95,225,217,211,217,44,138,147,155,90,195,91,
26,163,189,243,200,154,102,30,135,85,11,108,138,183,14,11,190,45,69,108,210,150,44,75,228,67,102,174,151,179,102,37,5,44,156,227,231,144,197,165,149,23,160,19,229,210,64,130,178,214,106,1,86,247,106,209,
46,211,191,100,58,181,131,61,200,55,192,234,100,240,47,89,150,38,232,251,219,165,112,227,244,24,191,43,46,63,198,138,4,151,94,211,131,88,71,166,23,103,249,156,147,71,236,111,138,223,201,130,242,53,175,
0,9,216,80,67,41,68,145,190,247,187,200,51,146,231,154,67,120,40,36,59,58,152,169,89,71,181,66,27,204,236,204,187,27,55,240,222,233,58,204,185,206,45,107,210,32,197,1,163,179,113,190,210,114,94,167,119,
184,212,13,174,23,177,203,137,49,65,24,158,186,142,163,17,112,164,181,244,233,249,49,110,43,153,229,49,167,174,195,167,192,9,131,5,1,215,77,189,212,11,198,56,164,136,96,115,152,243,144,199,44,63,255,121,
99,114,101,250,26,251,93,103,202,248,49,224,235,22,69,238,242,8,152,170,226,238,119,15,150,83,210,191,110,121,153,186,157,14,83,94,38,73,210,237,245,253,117,6,170,108,25,251,180,142,185,166,115,222,124,
174,241,236,183,244,241,220,224,24,222,172,102,33,203,232,45,133,118,61,249,11,186,7,151,144,226,36,136,246,44,2,2,80,151,163,27,221,40,42,242,9,237,36,29,146,156,218,177,34,115,137,255,224,200,120,165,
191,218,232,37,196,144,231,35,51,114,116,177,240,12,231,173,57,159,88,199,40,35,192,217,49,195,46,60,123,64,69,150,181,8,128,206,196,62,142,2,244,196,24,22,85,185,252,152,208,165,125,67,29,172,234,254,
176,26,205,212,188,213,238,216,170,0,167,137,19,118,129,113,73,25,242,79,73,239,67,42,122,66,6,231,24,117,68,79,168,182,69,145,53,219,29,191,8,48,176,163,218,99,59,173,41,55,183,108,160,111,240,189,51,
191,155,19,81,229,106,171,156,238,212,76,90,89,73,189,114,42,19,73,125,57,253,18,162,94,164,161,245,121,110,12,122,115,136,149,15,41,116,70,146,26,106,12,224,146,160,163,186,49,76,225,232,239,229,141,
221,11,199,156,48,88,97,216,188,145,151,122,241,24,62,87,195,32,98,68,130,199,70,149,244,98,89,161,133,223,246,153,99,32,4,143,85,221,13,170,177,13,107,146,135,132,49,113,148,196,81,0,33,45,199,29,130,
204,49,33,191,107,98,32,193,143,38,66,90,143,170,217,108,6,148,192,106,53,155,235,155,247,252,189,32,248,223,50,217,84,133,83,29,95,60,31,118,92,175,244,236,183,241,241,220,236,24,183,200,181,19,76,117,
44,50,180,201,3,252,20,107,54,64,206,177,151,200,206,229,74,172,87,1,53,82,87,33,14,38,186,181,213,214,21,206,164,19,152,171,25,37,167,38,173,199,181,25,66,117,7,130,132,115,30,46,219,79,169,223,187,244,
144,114,146,45,181,148,234,245,41,34,157,28,14,137,70,243,102,9,121,56,63,5,255,101,69,247,18,21,31,170,35,46,123,54,26,9,202,211,231,249,9,255,155,47,168,28,197,57,127,114,20,97,16,32,3,215,139,67,69,
220,150,141,70,24,70,156,252,202,109,222,55,43,176,99,231,117,234,116,142,235,219,219,27,140,137,147,119,81,215,158,205,137,171,82,190,138,194,99,148,43,154,7,103,141,169,108,77,143,70,188,20,139,49,212,
174,228,170,22,46,47,116,234,94,151,26,115,194,96,221,25,43,150,242,5,41,199,106,233,195,117,95,110,186,96,76,170,194,129,46,187,186,58,86,145,31,19,132,49,24,173,170,44,194,40,196,210,97,154,58,54,75,
169,181,51,151,63,252,3,236,140,40,6,159,44,70,107,181,116,175,71,122,10,31,202,99,213,180,151,152,207,85,159,253,54,62,158,27,31,179,96,131,214,75,206,37,187,5,218,3,178,44,233,23,248,124,15,7,116,134,
151,216,122,158,20,110,148,33,69,79,118,123,253,7,191,240,210,252,79,221,237,61,211,41,129,126,43,78,82,89,71,144,173,220,72,190,178,35,59,96,109,118,234,42,62,201,166,4,177,86,179,217,186,42,227,210,
11,198,56,124,192,170,26,164,42,157,153,185,102,21,120,212,113,54,224,230,79,167,51,44,230,148,21,103,116,148,115,24,68,154,65,73,117,27,33,157,168,48,20,115,28,23,146,26,106,167,219,147,174,50,163,35,
21,183,77,115,162,39,74,178,166,158,137,239,230,223,123,158,103,96,109,97,50,126,8,252,164,44,202,48,138,56,25,35,239,77,43,179,8,209,149,67,222,235,83,99,136,122,208,147,66,202,24,217,39,76,146,99,184,
2,163,22,40,17,126,173,151,24,115,58,36,188,153,151,250,130,49,149,117,116,195,122,169,127,138,26,202,104,35,162,143,84,95,48,198,152,112,110,77,79,101,177,173,199,42,240,99,12,106,67,174,192,47,77,103,
83,237,136,83,248,195,240,37,21,69,149,205,7,15,30,182,59,43,102,233,94,219,106,30,217,234,137,106,22,86,191,112,62,44,234,123,165,103,191,149,143,231,118,198,112,122,3,131,226,48,244,213,46,6,100,113,
74,158,227,71,233,241,164,250,160,90,48,45,250,132,168,4,149,218,1,146,57,153,74,242,235,214,103,165,152,39,206,41,90,114,247,28,115,180,91,230,135,115,220,167,66,216,41,161,128,9,72,184,142,82,248,76,
59,192,156,150,142,180,129,121,230,166,179,73,24,199,158,103,206,205,193,94,192,69,247,194,49,60,143,184,142,59,186,117,96,135,21,18,225,18,200,182,46,247,246,118,32,234,47,242,162,174,22,96,159,218,85,
159,89,103,200,199,62,220,94,206,157,170,184,72,212,187,147,192,81,138,173,26,104,74,224,95,219,170,149,170,172,86,82,67,215,218,195,59,106,209,56,146,8,0,113,10,86,93,246,189,239,62,125,156,21,89,28,
39,126,204,193,254,238,241,240,104,101,176,74,103,18,142,57,218,223,59,58,58,232,174,244,125,179,20,47,139,8,167,210,24,194,57,86,98,152,78,142,49,210,179,45,99,172,11,81,37,221,38,221,173,198,237,67,
172,240,120,64,236,197,99,94,22,233,126,237,49,203,168,113,14,17,132,95,225,28,100,249,169,49,115,101,14,116,107,67,103,149,202,119,202,208,143,169,148,105,182,187,193,241,168,170,230,214,137,110,50,67,
138,99,102,87,5,106,225,198,124,218,243,189,214,108,214,86,245,179,50,158,226,136,242,50,243,249,196,32,221,151,88,177,42,42,202,72,242,155,218,116,152,124,82,123,94,157,154,116,106,157,21,211,76,191,
227,229,11,133,223,221,141,230,144,144,67,63,166,21,98,180,29,182,105,58,226,96,92,92,173,88,34,24,89,40,145,121,81,250,69,172,112,200,157,6,64,106,110,122,101,154,58,71,141,206,29,142,119,0,214,229,68,
84,18,68,172,212,201,1,87,85,150,249,124,6,43,113,124,60,204,80,229,36,148,10,129,89,0,77,43,150,248,149,158,100,206,252,161,129,142,163,56,171,178,178,82,177,138,135,195,163,206,131,30,46,69,109,179,
58,171,117,205,140,11,81,64,235,35,238,171,14,248,95,107,17,185,48,196,34,125,121,8,85,152,64,44,146,44,179,179,185,16,182,134,249,195,201,58,88,223,224,118,107,206,198,136,171,72,115,14,200,142,184,123,
169,19,200,251,165,49,231,161,243,133,20,68,107,30,243,252,62,124,225,152,151,69,186,95,99,204,121,40,246,203,32,221,151,199,140,16,110,133,177,97,20,216,103,42,177,110,140,9,130,188,200,152,181,214,5,
12,194,104,165,60,82,70,170,167,248,157,109,217,89,211,86,71,58,153,193,75,191,220,124,62,121,72,119,28,67,180,7,12,195,193,12,66,93,74,158,219,231,65,169,205,211,44,184,124,153,2,152,67,66,22,67,245,
192,8,33,168,137,81,134,167,228,38,68,118,7,8,128,42,100,6,202,117,146,87,76,23,67,245,123,47,116,46,92,118,88,65,199,30,23,15,223,98,114,27,203,149,120,195,154,157,1,155,135,59,0,235,242,139,143,116,
164,92,171,51,127,56,179,249,140,224,102,38,68,213,94,206,94,25,231,121,216,133,234,132,75,240,113,211,88,158,231,81,20,178,185,200,139,162,22,231,157,122,2,13,66,70,34,21,205,85,70,144,52,203,220,21,
84,121,180,110,204,50,89,104,229,247,88,1,17,93,150,37,141,102,28,71,243,25,158,194,97,187,3,63,59,158,77,155,141,86,232,186,65,170,202,206,103,19,130,145,26,110,99,152,205,38,240,187,33,198,134,120,47,
248,175,69,1,161,34,56,142,201,242,254,97,54,52,163,245,5,200,251,51,209,249,47,191,87,111,2,233,126,197,49,47,131,116,63,53,230,80,197,165,10,182,76,254,166,206,31,87,81,69,252,249,69,153,41,39,255,93,
213,78,167,71,18,159,216,191,131,18,129,233,60,128,157,165,213,61,149,198,218,238,170,198,84,197,28,126,92,102,62,159,60,164,59,119,108,132,66,231,86,107,215,112,174,132,148,71,26,95,172,242,146,153,218,
175,172,114,118,205,171,228,10,27,140,9,200,234,25,107,172,71,186,195,207,67,209,158,82,62,51,237,160,13,86,123,229,27,201,215,26,207,46,224,59,216,249,37,56,71,76,146,202,92,70,188,27,176,46,158,91,42,
36,36,173,228,114,2,204,94,21,92,97,240,232,100,79,233,229,122,182,53,71,138,190,156,207,2,95,85,37,145,34,4,224,38,32,252,45,133,185,4,147,174,67,84,35,119,248,79,14,21,124,62,71,25,187,128,66,159,24,
19,197,241,193,222,110,145,166,235,91,219,71,135,7,240,147,70,179,53,60,220,207,210,172,245,160,59,60,60,108,180,90,205,86,103,239,217,99,198,36,102,76,42,71,164,151,168,111,52,159,241,153,61,2,135,139,
146,113,15,30,189,193,154,93,175,124,175,190,44,210,253,26,99,94,6,233,254,252,152,177,10,75,101,182,85,250,134,73,15,171,224,88,133,69,94,72,23,59,53,63,171,69,228,47,102,59,160,200,120,43,178,157,58,
133,37,121,98,155,153,13,212,85,230,243,137,65,186,47,143,193,96,152,210,64,174,129,92,24,17,2,23,142,9,211,134,3,136,112,230,182,226,182,24,110,30,228,158,53,202,160,24,172,225,214,130,226,113,69,37,
159,136,117,158,71,125,162,75,209,177,92,34,250,129,154,111,78,35,221,141,14,169,237,177,170,9,233,78,111,249,149,32,221,241,193,117,69,77,147,154,35,51,174,29,19,89,106,101,151,176,5,94,132,145,165,130,
107,151,126,210,34,157,233,140,30,233,51,215,36,161,226,154,145,108,169,74,82,26,199,86,164,181,122,192,61,152,28,137,51,130,132,223,133,118,41,87,88,195,93,181,207,238,112,111,165,63,4,91,181,191,203,
177,222,104,52,204,230,233,96,109,157,201,84,224,73,211,217,20,166,180,177,113,175,217,110,61,121,242,81,158,166,216,161,150,52,242,44,93,223,220,222,223,125,6,235,176,181,253,96,50,30,193,117,16,169,
239,153,154,94,233,94,125,89,164,251,53,198,188,12,210,253,204,49,51,163,63,178,141,129,206,86,77,185,110,170,31,102,5,68,33,81,24,91,87,161,119,149,44,197,112,53,184,212,106,53,235,213,201,220,36,7,54,
202,16,13,95,95,105,62,159,72,164,187,148,227,72,90,74,19,217,54,201,112,72,206,206,149,168,196,169,10,69,129,162,10,4,34,39,56,33,52,247,12,106,183,37,83,223,50,169,222,114,215,1,187,2,129,14,173,148,
8,113,62,140,128,63,133,116,119,9,44,105,171,35,42,63,81,139,242,72,119,66,157,232,187,70,186,19,107,42,248,143,88,168,34,34,54,228,113,46,203,36,142,9,118,133,86,90,176,105,184,9,157,28,14,37,158,22,
245,80,66,147,150,72,227,163,189,242,0,181,151,7,194,4,202,78,5,146,91,150,196,180,195,103,1,54,75,51,52,193,29,36,154,131,104,124,137,82,48,80,113,163,9,127,157,76,70,253,193,26,76,108,114,124,12,113,
93,171,221,65,138,39,186,23,50,139,87,213,100,54,70,25,145,2,169,150,226,16,11,20,153,181,176,55,224,221,165,85,93,84,37,26,11,98,247,38,99,253,234,247,42,120,182,198,31,5,129,9,181,116,131,137,249,71,
158,35,12,35,11,229,80,206,190,223,235,218,99,92,118,223,157,166,220,122,102,3,102,231,33,197,218,197,24,70,66,139,95,200,164,73,162,23,164,4,78,66,39,25,60,202,78,21,239,43,219,183,85,86,100,204,156,
237,83,181,174,203,141,5,12,48,187,188,155,149,243,206,90,101,13,93,199,227,36,213,101,238,197,250,207,87,221,244,183,45,136,112,3,99,136,111,164,38,242,47,74,46,113,154,79,148,114,60,39,37,163,162,89,
251,122,33,164,138,42,9,198,83,27,50,113,101,133,46,150,56,24,220,162,224,91,109,44,203,231,112,37,81,215,156,138,90,150,144,177,226,207,74,203,161,113,28,35,150,16,97,140,132,116,66,62,198,167,210,78,
43,188,223,14,167,59,118,44,235,58,214,13,145,142,112,132,69,158,32,12,108,7,179,15,186,120,214,250,202,131,56,151,180,57,17,118,131,109,100,76,159,91,195,239,71,81,196,30,16,191,47,184,124,161,11,92,
69,99,118,234,189,5,31,169,230,254,78,43,8,117,175,206,93,91,119,180,192,165,226,94,127,48,60,58,128,96,16,126,50,30,31,183,187,93,48,2,248,222,105,61,87,86,250,240,193,141,71,71,89,54,199,218,34,98,226,
74,174,250,177,66,151,33,22,29,110,159,18,199,249,53,216,171,33,21,50,221,58,138,254,179,192,139,225,0,65,130,52,38,57,80,202,177,32,220,233,24,43,237,26,120,130,177,184,128,239,194,88,18,168,148,49,40,
167,106,67,88,118,77,252,74,190,144,224,201,103,253,249,62,171,116,219,89,234,231,175,243,194,123,93,99,211,223,182,32,194,13,136,128,19,113,21,183,52,75,190,200,125,143,140,164,97,14,31,222,187,204,156,
201,37,84,229,213,152,29,92,142,117,208,56,133,207,69,19,118,25,56,238,115,138,158,74,130,71,236,82,148,116,24,205,144,173,158,97,84,0,241,181,75,253,30,127,64,252,15,34,240,71,42,147,8,32,58,135,31,238,
54,56,221,153,149,169,82,37,138,41,145,67,196,110,41,120,244,232,103,229,85,156,36,248,189,147,228,4,41,146,86,196,177,87,91,111,250,137,232,203,135,201,149,67,131,192,99,133,70,59,156,23,81,200,233,160,
64,125,230,69,90,204,58,154,68,31,80,243,150,10,148,62,49,134,222,41,202,169,118,123,92,59,122,240,198,91,76,118,8,11,254,16,201,185,240,30,189,126,191,187,178,226,193,28,240,231,246,246,3,198,4,111,108,
110,243,24,184,2,92,199,143,121,229,123,53,84,75,242,24,10,21,49,133,196,138,27,10,172,205,169,186,47,124,210,36,221,113,167,99,184,155,159,56,198,208,142,100,69,174,28,207,58,127,75,204,196,184,60,102,
50,155,230,121,38,190,30,21,37,89,164,192,203,207,98,25,165,66,121,213,139,175,115,193,189,216,209,191,210,166,191,61,65,132,27,19,86,240,178,46,85,197,133,62,68,177,7,34,175,110,240,125,17,195,47,50,
148,107,199,186,105,152,51,86,10,119,86,187,62,68,151,13,68,110,82,196,45,46,118,28,134,156,34,14,130,232,38,252,152,153,159,143,90,17,45,150,222,200,40,8,90,162,226,132,58,161,216,81,157,219,88,103,77,
17,7,193,97,83,41,146,95,250,14,104,169,249,196,162,57,107,108,222,210,21,35,48,27,205,230,108,54,65,237,134,178,232,116,219,147,233,4,215,195,65,133,24,198,224,250,138,185,127,79,121,88,60,60,126,210,
76,2,132,62,39,62,137,3,223,42,58,59,16,145,155,154,248,186,23,251,39,48,17,245,205,40,118,199,216,87,229,62,87,143,76,122,141,53,198,95,238,192,64,95,218,232,229,132,187,211,171,100,252,190,83,79,177,
203,52,223,119,58,198,58,44,139,161,246,154,11,120,214,121,76,187,211,201,178,204,245,186,73,118,128,146,184,37,17,43,70,157,118,91,11,21,255,69,215,185,248,94,159,32,78,247,229,49,202,69,112,18,114,40,
225,188,10,216,214,51,208,129,1,34,28,97,59,150,75,35,135,164,171,222,107,151,185,39,234,241,138,169,180,173,235,227,231,105,80,51,160,191,151,116,184,195,189,40,143,195,84,54,202,103,166,180,139,125,
208,14,34,59,177,209,142,79,203,33,221,239,130,150,26,193,95,53,28,173,57,204,33,82,17,203,145,169,170,76,26,45,108,252,138,203,52,205,210,52,237,117,123,163,241,40,203,210,136,192,183,4,42,66,167,129,
2,61,215,75,164,245,18,23,0,126,147,253,193,58,119,243,132,38,136,85,108,156,170,13,171,216,251,247,85,115,231,64,200,1,53,89,113,225,144,146,166,77,142,54,94,215,61,246,82,99,66,31,46,81,212,83,185,194,
141,226,222,96,67,47,140,19,162,82,254,96,208,248,93,141,97,254,86,207,191,175,5,102,125,6,207,186,31,19,199,9,88,37,24,208,104,52,42,106,122,144,98,77,128,214,10,37,3,230,243,152,211,186,23,94,231,130,
123,125,194,56,221,79,141,241,167,180,144,79,129,255,98,133,202,146,89,117,141,199,180,107,248,222,34,202,36,84,162,185,226,58,169,148,111,151,182,194,134,238,81,209,53,183,153,121,77,128,197,189,88,169,
1,109,34,157,46,1,143,177,136,107,103,113,135,128,45,34,68,55,48,243,26,21,128,66,63,134,179,159,183,13,214,101,128,202,172,158,87,166,108,217,102,170,83,56,111,121,76,171,221,198,204,6,42,204,98,175,
69,171,213,130,29,200,90,153,48,255,40,68,226,182,163,227,161,212,16,169,49,3,1,7,141,132,159,43,192,86,252,6,115,101,192,93,90,170,81,234,114,174,50,62,63,208,215,37,221,163,215,127,255,220,174,254,192,
151,222,121,71,121,92,32,134,132,86,184,41,28,61,155,145,100,39,162,189,67,105,39,94,176,193,114,173,154,68,253,240,32,37,104,44,43,240,25,105,41,162,29,92,47,24,111,165,53,220,203,15,145,41,21,193,8,
238,224,195,218,92,24,114,141,169,102,174,24,45,132,179,134,145,55,4,26,18,205,97,199,138,233,201,94,147,36,57,216,223,195,158,0,106,95,198,0,176,64,121,171,249,124,142,103,95,138,77,82,107,27,27,97,24,
5,52,109,202,134,132,140,33,162,132,132,117,57,5,195,36,152,204,221,17,24,233,1,162,86,140,72,26,17,52,179,208,209,218,81,201,130,45,172,118,108,115,68,144,166,136,17,105,22,39,13,116,245,25,111,19,136,
44,40,247,148,17,58,41,34,166,211,154,87,149,3,180,8,59,212,34,162,159,168,89,192,181,162,126,14,248,33,199,98,120,192,82,4,141,87,213,1,159,177,104,98,72,52,57,160,87,134,79,71,189,108,12,62,168,185,
103,66,129,245,204,95,216,146,82,83,75,138,179,61,218,195,161,56,187,133,117,122,162,124,18,102,43,161,18,181,75,50,57,36,159,67,173,255,75,215,81,158,179,156,239,21,202,189,106,30,99,156,165,115,84,191,
90,60,98,71,120,83,17,43,108,176,200,84,10,76,135,233,155,181,203,127,231,89,218,108,182,106,161,70,48,142,211,244,196,24,15,102,190,228,24,70,186,211,246,14,122,166,59,213,115,140,107,107,60,144,162,
56,41,136,230,136,139,6,69,158,101,121,206,98,78,44,246,7,127,172,14,6,195,225,24,6,255,143,255,225,127,170,203,114,127,127,31,54,120,163,153,192,43,190,119,255,17,88,127,222,24,224,183,13,136,46,57,3,
131,69,217,58,82,147,173,110,182,205,232,103,113,12,24,172,175,120,78,163,154,17,165,181,87,121,67,45,95,35,248,61,43,44,25,228,105,180,91,237,86,171,217,237,116,224,124,232,117,225,239,237,6,4,241,205,
38,126,141,65,8,78,49,191,93,122,91,72,210,18,50,133,155,116,73,42,70,136,9,172,201,237,239,16,223,75,200,30,45,86,93,41,79,193,182,79,228,231,106,1,1,81,131,101,224,142,121,235,174,234,196,74,133,102,
23,45,32,106,214,59,76,26,252,61,105,52,218,237,246,163,71,111,70,113,131,228,112,165,89,137,179,0,142,210,66,84,193,43,169,242,88,2,207,211,25,72,190,149,215,243,166,207,94,83,194,171,228,174,8,218,202,
108,106,53,245,0,149,204,160,130,46,122,81,192,10,193,21,114,66,24,178,89,140,192,241,39,136,64,81,149,220,43,79,117,144,136,193,62,200,241,128,151,173,217,172,163,229,162,137,229,101,33,151,213,216,144,
65,204,33,1,226,164,233,178,39,39,86,185,137,41,55,49,92,42,176,224,142,216,228,10,31,51,247,237,250,49,180,68,165,151,134,86,206,66,25,237,8,105,140,232,220,137,52,203,242,117,78,222,171,122,254,94,158,
191,70,26,111,180,128,39,156,41,100,30,250,139,199,228,89,1,145,218,203,95,103,121,140,107,67,210,121,93,244,84,27,30,59,181,41,179,164,193,218,36,141,38,156,76,180,182,180,105,2,124,162,138,96,68,248,
134,41,162,232,175,172,192,217,217,237,116,191,246,181,223,124,247,221,31,79,166,211,118,187,217,235,245,219,237,174,176,131,41,211,55,189,134,105,28,234,35,2,43,75,239,234,149,12,235,39,117,76,40,208,
100,17,170,14,201,75,146,115,24,171,170,101,225,222,36,125,51,65,212,237,182,193,64,17,177,86,205,245,71,212,170,209,170,69,198,138,107,28,27,213,218,120,60,25,141,39,121,145,195,119,56,157,28,111,111,
223,159,78,23,16,27,17,116,196,216,187,102,106,49,138,7,11,229,52,211,9,134,103,68,161,140,53,190,156,31,199,41,204,146,101,142,184,73,141,120,145,48,81,34,73,175,186,191,186,62,88,93,247,60,77,198,147,
1,56,144,75,69,18,245,120,11,201,143,136,251,160,101,50,198,17,48,42,135,65,173,56,182,230,133,36,208,30,214,90,149,99,142,23,29,32,180,125,101,237,138,244,96,188,181,200,154,85,44,89,106,201,63,194,15,
128,252,185,210,22,114,89,97,78,71,228,87,165,229,178,76,140,35,151,173,80,189,157,31,129,238,101,184,179,143,95,159,173,43,119,217,83,19,91,186,194,115,19,195,200,236,186,40,100,58,7,107,223,110,178,
52,70,157,30,83,243,187,126,21,8,126,163,17,47,118,163,247,242,157,146,240,104,83,53,239,234,206,88,77,42,70,193,144,78,218,198,198,214,193,254,46,28,9,37,249,158,240,77,48,10,18,254,19,134,135,212,59,
209,105,183,191,255,253,239,127,250,211,159,254,230,55,126,239,15,255,232,127,31,14,143,223,120,235,51,218,113,27,132,218,244,76,103,6,150,144,67,113,79,218,243,234,186,32,94,159,49,193,23,191,244,229,
69,103,41,147,129,56,254,33,14,181,3,106,204,136,194,96,99,109,109,109,125,13,220,168,217,124,118,112,112,120,120,56,220,135,255,131,131,59,153,128,121,58,62,62,30,30,31,79,167,179,217,108,14,134,173,
215,233,246,122,189,56,138,254,235,63,254,221,87,191,250,213,254,160,255,244,217,51,238,83,227,56,206,9,31,200,150,231,174,11,113,11,29,122,202,211,45,132,44,219,101,89,86,211,177,85,56,242,79,167,202,
25,112,82,220,72,224,169,61,51,145,83,166,180,162,225,76,36,144,142,187,82,104,228,106,39,196,226,244,117,107,199,113,232,180,15,164,114,236,169,159,184,5,159,164,171,200,9,162,172,180,34,33,229,192,122,
202,192,90,122,238,32,64,104,52,90,178,168,158,18,80,160,73,142,92,138,162,75,100,62,50,129,111,226,243,151,229,198,169,5,106,127,9,135,177,116,217,23,76,76,57,246,5,118,31,67,209,133,63,131,88,50,90,
34,150,188,128,124,178,186,196,152,23,94,39,186,157,49,89,154,242,154,223,236,189,56,72,0,111,117,110,231,61,221,107,155,214,196,78,189,226,25,188,144,86,187,91,150,185,165,240,223,53,162,137,48,13,86,
187,32,186,137,144,76,230,159,255,219,63,253,242,47,255,202,74,175,247,222,123,239,165,243,233,96,117,141,181,157,238,233,45,184,254,211,122,215,186,198,30,174,145,189,146,53,124,221,198,160,193,242,56,
163,146,129,90,28,64,73,26,1,127,185,217,72,30,220,191,7,214,231,120,52,222,221,221,63,30,29,67,112,142,117,122,238,122,162,166,4,170,51,211,31,117,53,153,204,198,99,148,80,253,225,143,254,230,209,27,
111,124,246,51,159,249,207,127,250,167,43,43,3,207,182,84,19,230,151,249,109,137,23,220,248,36,55,251,133,228,223,5,108,117,124,252,162,93,213,15,225,118,148,242,96,144,49,179,11,113,2,136,84,115,200,
192,225,103,31,242,145,207,137,79,182,68,228,108,162,39,2,206,35,35,57,25,80,27,82,202,12,46,91,144,154,30,103,145,2,246,89,148,133,43,80,78,138,238,133,224,53,195,237,157,236,252,179,42,156,52,103,16,
250,206,167,174,37,19,103,177,173,52,78,26,161,100,9,37,155,195,143,70,84,179,206,13,230,246,14,154,216,242,21,56,184,163,128,209,248,43,240,28,56,237,200,116,8,124,70,157,57,49,236,98,17,153,117,185,
44,108,0,138,79,43,78,144,57,221,109,74,156,5,17,226,155,66,8,78,245,207,238,24,136,188,226,36,185,241,123,241,78,228,246,236,57,56,89,182,19,171,120,92,77,60,66,29,198,64,124,7,129,121,94,102,248,250,
130,69,131,36,210,60,81,168,8,19,203,179,252,224,224,224,43,95,253,202,179,167,207,224,188,95,95,223,132,183,179,90,15,18,147,236,218,189,146,90,127,168,51,25,241,113,63,235,239,226,166,198,4,191,254,
197,47,89,207,171,109,132,241,174,230,206,45,122,1,221,118,123,107,107,19,60,220,143,159,62,3,239,137,179,36,30,144,194,108,176,122,193,41,226,53,147,213,79,222,127,23,134,125,253,119,126,231,207,254,
236,207,218,237,142,33,112,13,203,153,26,145,122,210,140,175,97,248,213,2,162,105,133,54,215,24,23,109,80,66,129,92,9,206,147,40,95,166,242,225,158,75,49,40,119,162,17,107,189,145,124,138,47,44,184,108,
158,242,76,188,90,47,72,104,101,172,85,90,160,213,138,5,94,93,67,142,38,53,61,215,210,229,39,166,207,155,152,241,19,203,179,180,145,52,150,39,182,196,62,114,122,98,142,174,238,140,137,169,19,19,83,167,
39,198,115,184,112,98,218,77,172,38,195,250,58,115,204,191,228,152,34,203,155,173,214,141,223,107,193,106,168,176,124,92,169,170,103,186,112,20,165,42,21,148,54,135,243,113,220,110,247,48,113,73,201,195,
16,139,212,9,82,114,119,87,6,171,235,221,222,10,4,235,31,126,248,65,179,217,250,213,95,253,215,127,245,131,31,192,128,135,157,71,109,211,62,82,195,25,92,202,211,40,223,20,167,251,39,98,76,240,165,119,
190,236,84,62,136,109,133,169,17,169,39,6,14,250,245,181,213,245,181,181,52,77,159,60,219,65,231,197,114,71,151,84,9,225,15,18,52,23,138,31,161,21,33,135,226,233,147,15,32,50,255,221,223,253,93,136,25,
127,240,131,31,252,250,175,127,17,143,163,217,204,243,37,121,150,18,254,11,1,26,244,66,197,128,46,201,100,94,252,24,168,154,139,48,103,91,11,139,190,118,125,71,138,58,215,44,23,25,217,155,8,136,39,192,
1,145,107,174,97,133,76,186,68,171,192,213,79,74,176,7,92,190,113,87,224,133,67,67,39,101,242,37,54,88,190,44,183,197,249,137,177,202,180,176,55,56,58,215,231,39,86,228,57,37,221,49,67,111,95,48,49,50,
63,167,39,38,42,15,12,254,56,119,98,12,242,116,19,227,43,248,137,5,142,104,150,39,38,24,168,215,149,99,254,229,199,100,217,60,138,147,155,189,23,255,200,44,105,199,229,42,7,55,182,171,187,177,141,166,
118,230,208,231,50,134,160,127,73,163,217,106,119,86,58,157,30,122,94,113,76,167,165,105,182,58,70,213,239,254,248,189,207,126,238,179,159,249,244,167,127,248,163,31,253,194,230,127,55,86,19,248,115,25,
197,254,201,120,23,55,53,38,248,226,59,95,54,46,34,51,38,174,73,136,137,211,180,221,78,123,117,48,24,79,38,123,187,251,132,243,14,60,95,45,23,242,166,211,209,12,130,191,209,112,50,62,158,78,39,48,38,137,
27,240,139,71,135,123,79,159,62,121,231,157,119,54,55,54,254,232,143,254,232,254,253,7,157,110,183,191,210,131,201,128,95,167,197,93,242,174,136,81,220,19,228,197,11,168,115,221,9,112,86,92,122,227,222,
78,233,180,162,200,49,8,152,93,175,102,45,150,186,146,126,8,106,230,162,34,186,226,202,66,205,252,249,139,43,88,105,194,162,132,130,200,234,201,189,184,163,2,215,171,146,203,210,247,206,132,141,85,85,
4,84,91,101,11,229,38,86,105,23,190,113,69,236,244,196,200,232,240,105,47,19,211,215,152,24,67,58,117,117,222,196,76,200,82,29,139,137,57,225,114,181,120,180,128,211,130,124,5,18,127,127,125,57,230,95,
126,76,93,84,112,72,220,236,189,60,172,131,186,146,165,8,51,183,105,165,235,174,238,52,85,51,211,249,153,99,156,224,35,181,112,208,139,128,127,106,119,87,192,245,126,255,189,247,254,237,191,251,119,163,
209,104,56,31,150,73,189,60,134,230,83,127,2,222,197,77,141,9,126,227,139,239,44,120,109,25,143,75,193,73,163,209,184,183,189,53,79,211,167,59,59,142,90,68,98,183,217,116,114,116,180,7,118,42,77,231,69,
150,21,37,1,157,202,50,203,210,201,100,120,60,60,58,216,223,127,248,232,209,215,190,246,181,63,249,238,119,193,59,123,244,230,167,102,211,25,28,44,96,179,210,121,70,186,193,28,54,86,14,110,35,204,233,
214,241,127,59,142,202,128,177,80,181,173,92,180,40,73,4,177,92,2,242,98,67,39,90,226,140,234,164,26,191,252,112,249,10,66,197,33,63,244,178,158,39,174,32,112,228,186,246,63,228,250,157,203,121,107,47,
164,192,151,229,20,160,62,53,49,77,217,110,247,67,88,28,136,17,100,98,234,154,19,171,207,153,152,58,99,98,44,238,182,116,5,41,77,90,127,5,43,172,123,175,47,199,252,75,142,73,231,115,50,88,55,121,47,225,
53,247,60,235,46,9,145,219,34,213,89,207,116,122,186,67,88,252,202,106,123,106,12,199,236,210,232,75,215,1,63,250,126,247,193,211,131,39,227,217,244,203,95,254,242,143,254,254,135,173,118,247,212,152,
79,198,187,184,169,49,193,23,191,244,206,162,43,135,246,61,31,218,111,189,241,8,2,159,39,79,159,158,80,40,177,234,232,104,119,58,25,83,207,20,230,134,177,118,91,139,3,75,165,108,240,104,39,65,24,126,235,
155,223,250,231,127,250,231,31,253,237,143,58,237,206,96,176,10,95,204,116,54,237,117,123,131,149,149,227,241,72,20,23,173,163,48,18,244,148,22,105,110,167,254,160,69,9,157,249,239,136,221,2,109,88,32,
213,0,134,121,146,111,66,154,66,204,214,36,253,147,76,79,17,56,143,76,56,222,232,103,129,97,58,1,135,253,160,231,101,227,40,113,153,187,66,72,243,226,43,84,182,118,64,175,229,43,212,114,5,140,238,184,
248,80,115,4,238,39,198,142,207,60,69,93,194,11,39,102,46,63,49,250,249,98,98,250,114,19,227,43,243,122,135,164,158,244,51,193,49,127,237,49,224,188,132,196,76,114,179,247,58,161,72,230,216,214,40,159,
85,67,72,104,172,238,168,86,15,34,68,141,157,113,142,224,107,161,219,128,32,234,90,71,42,28,152,193,186,25,36,42,222,92,219,250,199,159,252,215,123,247,239,189,245,246,219,207,158,237,58,254,9,150,35,
248,132,188,139,155,26,35,124,50,146,247,37,138,78,248,193,198,250,26,108,248,199,79,158,184,206,24,1,30,129,239,148,99,215,112,193,50,97,12,209,134,11,131,135,5,246,176,153,52,211,52,155,78,231,127,240,
7,127,0,151,254,139,191,248,30,124,64,111,125,234,51,158,38,241,201,147,167,111,60,122,184,190,182,246,108,119,215,107,105,72,235,154,38,234,91,4,52,17,151,110,32,246,145,67,69,196,176,84,149,83,91,84,
100,33,221,196,176,240,167,151,178,245,120,5,236,200,17,68,53,235,112,187,43,56,198,124,254,33,119,186,45,26,23,89,50,0,253,79,81,232,115,221,140,50,7,121,94,229,204,37,181,83,80,51,129,118,19,227,20,
210,137,137,213,50,49,69,120,229,58,208,234,156,137,233,83,19,179,11,33,83,107,79,78,76,159,51,177,197,21,144,13,110,121,98,86,42,173,150,185,80,132,232,246,117,230,152,127,249,49,124,22,222,248,189,40,
201,24,156,201,179,94,212,197,94,189,127,168,17,4,223,53,221,251,225,54,53,36,33,141,87,105,137,151,1,222,222,130,117,198,30,171,241,204,204,225,183,222,120,243,237,191,249,171,191,217,218,190,159,196,
9,115,186,75,104,255,73,121,23,55,53,38,228,208,64,57,73,24,142,210,155,173,230,112,116,92,18,133,27,111,247,178,44,118,118,158,128,97,178,162,213,161,171,178,224,22,50,206,147,53,98,120,131,225,108,118,
244,27,191,241,27,107,235,235,127,248,191,253,225,116,54,91,223,24,140,142,143,6,131,117,222,55,96,234,142,142,143,7,253,21,106,233,168,137,145,146,36,60,181,32,221,201,45,172,56,65,230,152,127,12,68,
182,240,95,227,208,192,188,11,162,133,67,17,164,64,20,220,144,86,129,26,32,40,18,10,40,5,142,4,67,89,145,139,90,58,34,191,19,236,5,15,13,17,114,85,28,32,69,97,140,68,87,88,91,40,179,34,11,232,135,161,
164,168,48,39,13,87,48,46,152,98,248,76,16,70,120,89,206,254,104,205,19,11,194,0,190,252,178,150,137,133,116,26,48,119,224,242,196,88,211,208,16,210,157,175,112,106,98,150,32,187,244,104,24,201,7,150,
39,150,75,90,157,26,152,46,59,177,208,79,172,60,107,98,214,77,236,245,230,152,127,233,49,234,54,53,10,46,230,89,31,235,233,216,78,147,50,14,20,108,235,32,128,51,72,5,200,69,161,235,10,174,10,239,86,85,
169,206,217,49,99,202,214,78,183,63,157,78,185,13,233,20,95,187,155,79,32,29,222,148,40,57,53,31,196,120,43,215,142,135,19,251,100,190,211,51,144,238,131,62,106,251,28,13,143,225,177,25,233,14,230,100,
120,180,199,165,37,132,240,82,48,24,69,136,147,208,174,221,190,209,72,158,62,121,22,134,193,246,189,173,255,252,167,255,215,112,120,200,136,193,225,209,65,171,221,137,162,152,93,131,241,120,12,6,107,165,
215,133,235,95,10,233,190,140,219,166,130,26,27,181,178,94,176,190,45,3,202,229,236,58,11,80,110,79,1,202,237,89,128,114,134,131,95,25,80,254,47,14,233,254,179,49,230,22,144,238,126,140,19,172,63,159,
103,93,169,84,101,78,243,76,249,134,10,45,10,28,68,174,32,28,23,218,53,204,74,198,139,218,161,197,215,88,154,143,168,222,139,58,35,165,122,253,24,209,172,149,57,155,79,236,59,245,0,38,47,156,211,235,118,
193,210,99,138,190,18,206,138,249,116,60,159,207,209,84,33,67,77,221,108,98,23,33,203,64,229,121,134,132,83,65,184,179,179,31,160,140,83,253,157,239,124,231,189,247,223,67,93,229,86,11,174,1,191,179,183,
251,212,122,154,234,178,154,205,102,221,110,87,171,37,69,70,2,10,212,78,237,218,247,208,58,194,146,5,44,30,29,4,36,215,211,60,49,37,177,17,227,12,132,42,64,47,104,178,189,68,241,242,21,108,205,12,106,
140,155,23,10,11,190,236,137,43,56,165,9,91,47,112,24,50,216,10,115,41,95,246,244,21,220,196,212,242,196,156,22,129,178,207,77,204,94,119,98,246,234,19,243,138,176,188,224,102,137,13,237,57,46,109,113,
174,127,62,230,204,49,72,42,207,244,180,82,255,88,218,96,174,73,154,211,198,94,8,216,81,30,214,12,214,114,133,224,211,99,248,181,85,86,180,162,225,87,152,163,70,122,237,244,130,108,243,252,49,218,201,
245,124,210,222,69,184,232,95,193,40,175,108,183,26,176,130,147,201,52,16,110,48,11,97,197,120,52,98,194,54,88,151,110,167,59,60,30,206,231,179,8,69,103,232,232,46,45,68,127,86,116,44,45,83,152,66,108,
2,6,78,145,119,155,166,41,194,38,27,77,62,148,70,163,201,230,102,51,140,176,71,154,105,167,144,208,71,104,115,5,46,196,140,113,212,134,111,152,32,220,24,237,90,166,85,154,205,209,244,134,232,107,24,18,
167,19,1,181,10,163,176,0,123,222,17,180,69,76,9,36,19,95,20,149,169,73,182,64,200,30,224,231,57,54,123,229,17,209,66,16,207,17,117,225,150,85,86,20,33,113,20,97,154,76,19,147,95,58,7,223,19,60,202,16,
5,196,208,142,39,73,3,177,160,69,78,198,90,152,231,52,173,24,216,244,172,206,249,135,203,19,67,99,95,149,56,49,37,19,35,101,167,252,69,19,147,43,208,196,144,92,33,52,200,105,231,30,13,97,34,16,20,162,
112,147,18,98,60,138,25,179,231,39,86,21,213,233,137,105,243,58,115,204,191,252,24,136,5,80,144,234,166,239,69,255,104,32,32,136,67,228,195,44,40,198,87,78,128,214,203,88,83,235,72,101,156,134,35,241,
145,148,4,198,150,78,107,70,32,34,243,132,32,123,176,135,140,121,199,132,61,209,129,158,33,174,15,169,1,139,251,118,229,127,122,49,134,25,44,78,141,145,142,187,159,229,119,138,252,200,37,174,51,125,23,
184,206,161,168,105,139,188,135,193,40,207,152,52,207,185,42,135,110,237,124,70,76,29,232,220,38,141,228,248,120,8,43,27,199,13,33,196,87,90,96,141,97,224,170,91,114,41,214,158,73,144,47,9,34,202,131,
173,237,135,53,49,92,165,68,7,26,199,33,177,236,9,18,47,160,239,80,59,42,75,198,142,186,6,71,77,93,201,150,108,19,88,171,217,211,199,31,173,174,174,37,253,132,29,180,233,116,114,176,187,243,240,141,183,
40,68,229,198,84,140,225,209,42,27,66,238,133,33,29,104,78,220,133,208,245,210,227,198,250,113,154,209,176,196,151,98,43,135,50,8,242,60,127,242,248,167,48,159,181,245,205,167,143,63,220,220,220,6,15,
241,112,127,239,254,195,71,141,102,11,44,24,35,114,9,80,46,130,158,116,175,218,186,70,12,190,108,192,220,216,234,196,196,20,247,73,157,53,49,187,152,152,58,53,177,154,38,198,87,160,76,92,232,180,224,233,
135,244,29,156,57,49,48,128,78,167,75,38,86,191,230,28,243,47,61,38,88,42,242,94,227,58,172,223,37,194,19,94,214,88,14,101,28,198,34,102,140,79,228,195,166,162,118,111,79,25,198,92,32,156,23,102,110,66,
1,241,58,221,98,70,178,224,24,82,134,230,234,125,77,101,222,90,149,226,127,49,254,142,132,121,8,105,140,191,90,11,243,178,61,107,140,89,106,202,243,50,72,183,254,46,168,213,253,86,222,41,23,46,120,157,
79,115,186,83,171,33,113,154,83,2,11,6,165,233,188,34,98,140,48,140,142,135,35,117,82,46,209,49,237,51,187,136,75,148,7,212,238,71,253,119,69,94,170,4,254,154,51,148,207,18,183,9,230,252,195,200,115,39,
177,62,133,20,251,89,150,0,95,61,119,255,72,87,74,96,66,4,115,215,72,69,194,105,126,227,164,27,225,31,146,70,179,34,233,36,241,74,192,119,128,163,21,249,118,133,126,87,147,79,65,171,243,255,179,119,102,
75,146,36,215,121,118,247,88,114,173,172,165,247,233,25,12,72,0,20,121,161,11,220,10,144,73,188,33,117,39,224,101,68,153,222,137,70,147,241,25,36,146,87,34,205,100,70,202,136,33,0,27,244,58,221,181,101,
229,26,17,238,242,115,254,227,30,145,89,91,214,146,213,85,221,217,32,129,153,106,175,8,143,205,253,44,223,249,143,228,104,240,104,253,11,39,210,2,74,74,178,97,209,80,69,158,55,45,135,71,126,191,122,250,
252,171,126,191,63,157,76,188,97,53,47,142,29,35,109,31,126,120,91,204,139,231,47,95,66,144,71,90,217,99,155,13,19,131,106,10,74,38,101,63,96,13,63,117,201,196,24,65,89,158,152,150,137,249,91,90,150,252,
118,58,201,42,240,17,228,176,140,245,242,242,232,160,200,97,27,19,195,17,162,100,71,84,251,188,159,26,243,55,31,131,242,214,107,31,199,133,189,92,9,241,199,90,70,32,111,185,139,53,11,112,59,201,239,70,
9,48,29,178,216,58,5,24,29,184,32,21,182,115,180,113,68,230,215,132,49,238,220,49,14,69,90,18,154,8,171,143,180,98,61,115,140,214,117,210,28,194,2,246,83,62,11,20,235,95,231,56,41,250,42,232,32,78,224,
127,178,164,233,110,136,42,16,53,40,10,57,81,239,162,2,81,21,50,125,1,4,89,81,50,112,92,184,107,157,178,161,5,110,208,81,80,81,87,128,8,3,231,63,254,138,43,81,208,228,150,228,163,88,112,78,176,47,39,5,
40,21,120,44,138,76,35,30,6,147,141,190,173,4,2,199,104,146,231,175,208,175,38,71,135,7,254,213,232,111,15,12,201,54,118,42,94,31,65,63,125,252,248,3,9,141,58,242,152,186,189,174,95,104,252,1,15,14,62,
250,163,249,165,109,50,246,254,108,214,237,245,188,175,7,203,113,123,103,207,175,206,195,163,67,127,38,255,243,78,167,231,61,74,191,118,251,1,254,118,142,71,195,182,255,211,233,114,67,105,2,190,252,224,
147,225,208,223,155,227,195,163,173,193,160,40,230,147,241,196,95,87,187,211,201,242,214,201,240,152,165,1,109,43,111,251,211,177,252,152,67,127,61,200,39,250,127,3,193,12,210,189,172,219,29,87,80,250,
133,245,135,160,123,133,144,189,180,159,161,221,134,55,21,199,237,79,172,212,229,48,233,142,149,8,143,135,127,177,68,122,145,15,80,82,102,131,197,179,172,108,75,46,72,140,217,207,86,255,155,172,159,228,
74,199,41,241,172,32,209,203,74,167,124,156,140,27,0,105,30,67,27,3,119,84,183,129,127,166,77,155,211,68,161,44,148,246,3,137,136,135,49,206,137,228,36,118,90,205,165,236,82,0,183,52,70,240,171,5,1,222,
18,239,143,180,161,18,173,232,48,134,55,200,178,30,227,32,248,161,3,207,72,194,171,20,75,45,32,1,112,147,251,28,239,15,198,112,71,51,75,75,15,181,197,194,253,65,204,180,176,245,61,60,99,204,210,113,112,
46,30,99,227,185,252,162,82,170,210,73,21,29,119,156,245,11,214,146,166,187,255,101,255,249,73,156,219,168,88,16,231,127,78,10,13,188,72,33,36,140,101,11,171,184,144,71,161,3,160,255,26,253,123,66,18,
215,252,41,58,174,48,240,86,90,194,225,27,52,134,128,106,132,31,252,252,233,211,160,210,47,90,224,136,67,135,60,128,212,4,19,20,198,140,56,74,226,70,195,33,117,172,157,78,139,98,150,102,249,193,199,143,
222,216,129,154,130,127,3,14,62,126,32,111,180,213,45,203,249,240,248,224,229,55,63,62,216,255,112,120,176,239,87,46,255,223,254,142,238,61,122,236,29,201,31,222,189,245,203,13,202,95,222,190,126,229,
207,53,24,108,99,213,128,188,65,65,109,242,76,89,20,99,239,117,126,120,255,232,209,19,92,36,116,109,252,152,209,232,216,79,230,253,187,215,189,254,160,44,252,26,186,239,207,229,71,250,49,254,92,106,160,
91,220,25,28,1,213,146,105,41,222,243,19,254,144,192,229,151,74,196,236,69,175,65,137,118,160,67,15,119,74,244,178,202,51,106,116,116,56,66,56,44,203,6,112,11,69,13,243,80,112,255,42,232,40,197,35,104,
8,252,198,35,60,104,109,239,85,198,84,182,110,152,120,165,227,72,199,105,142,255,177,248,90,41,122,246,164,179,68,111,181,229,58,80,244,250,1,178,67,17,94,45,126,93,86,11,168,38,81,46,26,66,201,80,43,
165,49,105,206,166,128,84,188,197,205,30,99,140,213,150,66,25,52,134,39,150,170,96,166,73,168,157,35,191,103,162,76,232,53,37,245,36,134,234,61,252,183,86,137,60,164,185,149,251,172,69,186,22,214,16,55,
1,9,157,71,104,175,229,115,37,58,16,150,97,140,36,3,120,27,62,117,28,195,107,110,21,73,247,250,56,38,137,58,234,36,165,189,164,233,142,242,1,89,192,131,149,196,54,5,123,212,220,116,86,50,142,232,107,130,
242,106,254,150,132,165,164,49,12,25,101,25,2,37,1,76,85,81,5,21,155,15,231,173,162,0,41,239,72,16,37,213,78,18,198,161,111,48,36,114,16,146,72,249,32,91,131,237,237,221,189,223,125,247,175,126,98,89,
222,142,30,19,79,195,49,102,209,253,230,71,127,52,26,13,223,188,254,222,155,60,7,251,31,253,10,242,242,71,63,158,140,198,239,223,190,146,244,176,209,199,71,71,91,91,3,255,207,173,188,53,158,156,28,31,
31,13,118,118,32,67,236,55,135,221,157,189,143,31,223,63,122,242,20,182,158,149,20,140,233,118,123,211,233,216,47,121,222,91,124,247,230,53,124,2,255,48,253,11,56,26,30,251,39,224,111,247,87,223,124,75,
14,38,47,208,120,125,45,163,24,144,159,230,16,44,154,148,91,118,162,19,35,114,204,21,160,92,105,216,163,185,166,82,7,227,203,70,1,235,132,229,146,43,164,138,130,191,41,204,7,112,97,165,66,5,60,229,218,
53,183,195,177,113,223,227,176,189,253,188,245,191,169,11,108,89,94,239,56,73,232,20,11,17,213,208,231,205,149,182,144,79,67,26,211,7,145,251,192,179,107,62,114,20,201,140,225,239,68,155,69,108,106,30,
199,68,4,41,209,234,236,49,87,68,153,18,129,136,149,68,130,80,32,193,47,12,43,0,223,72,27,30,26,252,241,254,72,31,41,226,39,235,54,212,210,48,137,191,235,56,6,249,132,165,49,114,28,91,74,3,83,235,106,
77,4,190,105,188,151,203,15,72,28,124,137,116,247,86,64,167,211,81,74,194,27,112,6,69,137,138,215,47,87,71,214,105,150,28,17,119,72,165,179,178,85,162,67,31,181,160,157,66,171,78,74,150,95,26,117,249,
252,247,12,118,209,255,234,219,183,239,176,123,193,172,64,165,27,133,207,67,195,2,145,205,18,77,9,145,96,172,75,141,106,36,93,69,210,157,150,222,178,24,157,12,199,227,17,151,239,144,208,187,223,136,198,
39,195,233,100,10,211,195,27,104,79,159,62,63,57,25,250,97,243,157,105,191,63,240,214,214,155,55,127,240,198,212,96,123,119,137,116,71,81,52,28,216,70,94,149,85,88,211,108,166,39,126,249,244,203,65,167,
215,203,114,34,90,169,34,127,67,186,63,88,210,221,155,72,104,153,193,159,46,72,40,236,131,48,61,108,208,59,227,149,72,37,252,193,74,73,149,141,205,61,151,241,34,119,247,40,147,13,45,14,129,93,176,233,
87,169,171,223,103,16,142,149,211,104,128,156,38,153,61,125,127,196,176,144,117,141,177,39,255,12,108,115,12,190,113,43,253,25,84,243,56,174,166,53,234,227,88,168,215,177,153,198,123,191,91,38,221,33,
122,105,57,156,132,246,36,244,169,243,31,62,95,133,54,202,38,100,241,248,250,163,140,183,164,225,73,6,111,94,228,173,156,69,239,114,44,234,28,23,171,144,107,37,127,176,18,217,236,11,72,119,200,213,160,
211,111,158,102,32,221,11,11,137,190,52,10,215,23,80,255,34,132,93,72,119,124,240,239,223,191,241,199,217,217,219,123,180,247,180,219,237,191,127,243,250,205,235,87,157,78,23,173,238,138,249,252,227,15,
63,248,123,177,189,179,235,151,238,143,111,223,249,105,231,121,251,233,211,175,16,251,159,249,107,224,20,6,1,229,252,54,100,73,74,178,127,220,14,128,237,23,178,83,158,61,123,241,214,85,175,94,253,94,19,
172,188,181,189,179,39,186,62,90,111,72,247,7,71,186,227,179,41,93,201,237,78,180,20,165,177,130,163,183,2,242,172,149,167,105,193,42,2,216,184,34,215,182,136,14,201,152,76,71,196,234,211,140,1,67,111,
184,88,141,49,139,18,14,218,106,52,124,28,163,185,25,128,70,125,50,122,167,135,40,182,220,159,232,152,201,185,36,115,173,213,226,24,35,190,155,169,100,3,136,199,97,82,80,213,14,158,127,123,161,49,237,
221,3,14,78,137,245,160,255,219,127,255,31,117,175,235,36,239,245,58,143,31,63,250,221,239,191,151,30,124,254,229,158,142,247,247,63,78,38,163,201,100,202,34,77,12,100,197,173,63,80,33,210,81,134,215,
24,152,72,222,219,159,23,68,69,181,219,237,188,221,254,234,197,215,168,102,246,31,213,143,190,249,250,195,135,253,225,201,137,24,4,108,196,5,2,69,75,163,130,0,115,235,232,67,187,168,46,80,65,99,47,252,
16,212,175,141,22,208,191,253,235,191,248,133,233,197,203,111,1,148,235,186,233,124,56,194,217,135,181,42,218,80,72,44,136,156,136,141,221,186,241,138,3,40,191,232,8,167,38,54,36,103,115,183,113,132,250,
176,11,71,184,195,137,157,34,221,107,51,33,108,221,218,4,175,255,33,142,25,30,29,238,236,60,186,210,113,96,191,243,183,42,238,63,66,233,126,153,55,220,255,157,83,231,68,174,248,69,223,133,48,133,14,77,
19,35,94,132,49,167,241,162,171,142,225,0,171,187,201,113,128,50,137,96,139,4,248,175,112,15,3,85,175,208,100,155,251,42,80,200,188,121,127,16,218,199,240,146,210,253,68,111,32,136,20,231,83,143,33,165,
185,133,49,205,115,193,239,195,113,206,188,174,180,38,221,217,252,43,88,77,56,207,179,241,184,4,129,221,237,246,14,15,247,183,182,6,164,209,91,90,23,68,43,67,77,1,20,94,148,232,19,72,231,8,178,220,100,
151,227,9,237,237,62,10,153,75,127,240,156,92,54,254,219,154,116,231,245,54,9,65,174,58,178,134,158,201,108,55,5,43,16,43,189,205,188,185,41,73,91,4,173,89,182,60,106,2,194,123,23,233,116,18,59,174,228,
8,78,172,72,105,131,142,97,56,108,125,132,104,160,194,159,74,164,127,39,234,136,108,68,240,33,54,207,224,87,125,132,48,49,23,50,170,53,233,238,132,224,191,157,137,137,166,251,85,38,230,104,225,174,98,
241,246,39,55,1,238,159,73,66,127,50,201,210,6,31,218,138,234,127,193,178,200,64,135,80,140,181,110,172,12,202,142,183,112,28,222,227,51,104,240,59,78,182,95,114,127,84,6,184,213,5,124,95,33,11,68,199,
225,38,88,82,211,40,223,36,171,60,93,58,231,115,198,72,159,7,28,167,188,240,186,150,73,119,138,126,89,187,61,24,204,166,179,64,186,219,193,96,112,112,112,224,173,98,191,195,84,44,170,229,183,32,40,115,
66,186,147,146,190,78,74,145,129,137,231,89,54,155,205,18,146,133,77,253,10,229,237,29,100,8,252,127,15,182,182,252,106,117,124,114,162,67,131,229,139,73,119,194,193,193,109,195,245,92,6,202,207,32,221,
95,126,253,45,250,59,220,156,116,71,220,226,52,80,206,107,255,134,116,255,220,72,119,132,2,137,8,229,173,151,121,18,116,255,166,55,212,64,9,83,112,41,233,74,190,140,14,105,14,199,220,9,238,180,250,185,
40,16,79,125,146,43,238,108,160,46,190,135,32,248,41,118,33,177,107,5,102,208,9,193,207,146,36,202,196,15,86,210,217,126,161,191,104,206,202,158,59,70,90,190,175,114,156,101,210,221,15,241,75,201,246,
96,219,36,2,188,249,143,231,232,232,104,60,30,167,156,245,227,46,6,137,10,58,176,72,76,114,189,166,208,110,254,26,178,44,3,103,212,105,117,252,49,119,200,188,82,40,103,75,141,238,118,59,7,7,135,198,160,
214,243,34,210,29,6,100,205,109,243,202,114,22,80,174,35,80,142,59,218,226,188,193,205,73,247,165,35,212,64,57,151,11,110,72,247,207,134,116,7,165,45,253,56,193,91,49,126,229,111,106,141,41,193,191,88,
64,135,72,206,164,198,148,188,171,67,240,206,29,162,103,171,157,11,203,13,75,253,27,110,113,168,87,39,203,113,43,56,205,77,3,121,43,55,92,15,233,207,213,186,123,236,110,153,116,247,151,113,112,120,184,
51,240,54,214,214,135,143,251,126,199,57,60,216,31,30,31,107,209,120,2,52,161,208,6,153,113,246,42,66,88,112,22,209,218,200,90,202,54,250,191,234,247,251,237,110,55,65,255,100,103,7,91,219,254,23,15,142,
142,160,30,123,49,233,142,144,2,218,36,123,243,1,164,123,196,193,27,64,121,165,27,56,248,45,146,238,231,2,229,21,47,220,1,40,223,144,238,159,7,233,206,190,31,116,196,233,185,65,126,15,155,40,246,27,78,
228,106,27,131,161,70,45,99,74,162,55,123,25,202,196,206,127,61,70,169,59,192,211,180,52,171,51,130,195,95,72,159,187,6,193,79,187,93,130,86,114,250,147,99,119,203,164,123,229,252,119,110,70,227,177,95,
176,246,247,15,222,188,254,222,123,118,64,108,185,128,74,118,104,166,196,52,155,3,12,4,177,111,143,116,62,74,64,121,209,32,157,229,189,189,167,90,120,22,237,125,195,157,157,157,209,232,132,27,154,74,151,
189,11,72,119,64,222,220,202,60,141,164,59,243,68,20,0,35,24,146,119,70,33,191,253,218,169,69,231,19,206,151,255,59,0,80,87,1,202,189,229,146,2,48,57,27,40,231,137,149,40,15,2,80,94,149,144,251,12,64,
249,169,137,109,72,247,135,67,186,19,132,173,42,222,185,13,50,137,78,69,44,136,30,71,65,59,107,64,153,172,99,73,254,6,94,196,26,179,192,184,104,107,57,23,119,74,78,225,78,106,173,120,90,208,162,41,121,
227,76,160,205,123,46,229,143,104,15,215,175,44,145,247,159,28,187,91,38,221,217,134,178,239,127,248,240,242,171,231,111,95,127,63,158,140,139,162,128,1,201,107,174,97,155,192,129,186,18,234,135,62,33,
254,79,70,113,58,90,55,140,233,180,91,254,153,61,123,241,181,147,122,67,50,153,190,249,250,165,191,17,31,62,30,0,35,197,23,197,17,77,29,154,56,88,216,71,248,33,69,142,217,193,142,56,56,55,175,192,11,19,
50,95,100,200,0,230,142,230,195,77,129,114,119,14,80,206,207,117,9,40,47,145,185,3,243,156,194,186,196,196,116,152,216,134,116,127,32,164,59,133,2,209,229,151,53,21,234,36,175,117,210,44,158,132,70,179,
249,124,198,222,102,98,165,101,137,160,76,148,156,81,84,126,2,210,61,162,76,232,134,185,128,59,49,122,194,184,147,77,96,208,173,19,79,19,98,94,174,75,186,189,94,64,177,139,194,23,225,254,85,147,188,191,
15,216,221,50,233,30,200,0,247,127,255,233,159,138,249,188,162,252,165,120,31,177,233,159,181,81,118,92,81,159,181,254,22,255,160,130,131,199,50,88,229,246,246,163,94,127,43,84,141,210,130,244,213,179,
167,126,69,123,243,250,173,10,168,139,99,152,69,52,221,165,246,170,164,151,204,40,73,184,178,35,211,224,182,121,233,167,104,31,27,95,92,119,205,200,19,109,89,142,13,61,224,224,23,2,229,137,169,113,240,
75,128,114,112,234,87,5,202,97,48,138,76,251,134,116,127,104,164,59,72,110,9,212,114,28,209,239,156,138,232,80,137,199,67,183,82,250,164,53,80,47,60,95,24,86,167,80,47,125,14,238,148,52,73,247,53,225,
105,68,204,211,55,2,178,60,141,81,188,243,174,29,58,128,144,213,212,103,8,159,126,74,236,238,108,77,247,225,241,209,225,241,145,52,16,214,166,182,138,107,233,116,238,244,85,85,237,86,27,237,151,201,31,
243,70,102,150,247,182,182,187,221,45,24,109,193,219,215,143,30,237,117,187,157,15,31,246,103,243,153,82,177,75,206,70,211,125,67,186,223,59,210,93,213,164,59,181,16,87,202,68,146,59,144,238,138,21,140,
133,116,39,172,177,73,159,75,222,240,126,137,118,122,239,159,130,29,76,150,135,46,232,167,180,234,107,138,157,88,28,22,107,13,205,49,239,141,24,233,25,154,238,254,2,246,247,63,76,38,19,13,239,75,163,234,
133,105,49,45,53,62,24,214,202,243,221,71,123,253,222,128,1,107,19,155,164,114,212,70,225,3,243,206,200,211,39,79,122,221,238,199,253,125,191,8,138,157,29,164,23,55,154,238,27,210,253,190,105,186,195,
252,23,176,219,114,39,41,16,216,252,183,220,123,194,198,45,92,120,68,23,180,95,248,171,186,111,232,89,150,202,156,41,8,195,194,127,104,226,121,6,229,223,160,216,17,31,186,111,184,220,25,154,238,71,7,31,
41,208,206,93,54,137,109,165,170,116,78,189,155,154,23,103,155,217,180,59,157,173,173,93,14,181,80,66,6,107,17,113,101,70,236,103,255,111,207,158,62,105,181,219,111,222,190,29,158,156,0,141,13,64,132,
218,104,186,111,52,221,239,161,166,59,52,145,192,82,163,170,25,202,37,48,75,217,163,164,76,244,18,201,173,56,127,114,175,240,52,238,173,27,201,114,195,111,145,141,20,187,105,232,190,75,202,139,99,88,160,
216,239,45,118,183,76,186,251,87,253,232,232,64,135,45,5,139,66,45,44,102,131,134,12,59,56,207,95,188,148,82,146,144,38,65,38,145,186,241,24,179,181,181,53,24,244,253,41,95,189,122,53,157,205,35,233,14,
170,21,224,217,154,72,119,23,27,45,110,72,247,13,233,126,157,49,4,18,178,119,24,116,15,88,108,0,169,16,36,52,176,108,241,178,167,239,19,158,86,171,190,51,44,37,118,19,22,226,44,165,248,67,227,218,97,60,
74,64,218,73,98,58,9,61,53,174,116,93,250,110,174,125,153,116,247,155,55,182,162,78,187,237,255,218,155,90,21,35,8,181,216,94,104,10,249,248,201,51,106,76,79,146,99,208,117,161,245,219,175,233,157,78,
123,171,223,247,62,160,63,141,183,170,222,127,248,224,159,125,64,210,37,90,196,253,193,236,250,72,247,91,212,116,223,144,238,95,166,166,59,137,35,57,209,17,23,222,59,106,168,131,201,174,64,195,171,155,
136,154,222,202,24,37,241,98,139,53,8,133,144,88,135,129,121,7,243,157,150,128,60,92,87,188,118,69,189,18,19,241,142,196,212,50,81,167,243,42,243,81,119,112,237,203,164,187,31,240,147,159,252,236,223,
190,251,205,120,60,206,91,185,95,122,252,63,84,86,220,70,244,33,242,159,115,43,207,127,254,243,159,147,78,144,85,69,81,82,127,72,78,215,161,105,135,63,244,193,209,209,112,56,20,179,25,77,168,85,140,128,
161,127,72,232,39,173,192,202,135,190,73,129,219,14,250,200,58,207,51,108,20,90,161,7,101,5,60,181,238,166,116,138,116,103,192,223,52,56,245,76,148,0,25,40,39,187,131,195,210,66,180,43,29,73,119,128,227,
42,174,224,228,249,210,125,241,143,25,181,161,27,210,253,11,209,116,71,203,149,37,77,119,48,40,81,139,157,138,252,169,235,160,138,66,154,119,137,158,1,155,138,154,238,198,2,161,74,253,139,47,186,239,142,
53,17,42,38,111,24,118,193,117,53,175,157,59,42,250,51,149,46,30,135,189,227,85,40,246,44,201,176,122,196,249,124,26,210,221,127,31,63,250,246,143,126,248,225,29,245,155,168,170,110,175,231,255,206,175,
62,78,50,35,180,136,252,241,79,254,100,127,255,128,177,35,82,22,165,85,164,156,84,68,37,80,6,127,52,25,171,208,195,10,194,85,34,135,19,90,93,161,3,117,84,242,195,15,165,227,8,223,50,112,219,178,75,200,
38,96,176,234,85,18,6,210,81,45,26,71,104,226,224,209,163,244,198,10,240,25,246,152,164,4,52,118,20,17,20,83,58,42,97,213,139,127,76,163,30,86,71,213,49,64,79,27,210,253,11,209,116,143,99,224,125,195,
97,175,53,221,217,12,151,72,61,63,205,59,71,207,78,107,186,215,115,86,12,109,136,166,59,4,136,27,58,235,49,255,44,61,50,228,56,87,194,220,36,11,215,188,118,188,252,245,24,132,240,137,182,92,27,233,78,
159,86,222,122,246,226,165,255,223,163,195,131,209,104,212,237,116,246,246,246,252,119,50,159,207,189,127,215,106,119,252,83,26,158,140,16,192,138,222,47,190,85,203,1,96,241,249,189,133,194,56,145,10,
61,32,17,120,134,190,4,20,178,226,125,183,28,107,103,149,235,34,106,186,115,255,54,201,93,242,206,102,210,68,51,92,163,1,148,115,126,154,147,32,116,111,68,4,21,17,122,121,24,80,5,50,9,45,31,65,103,134,
4,230,225,106,57,214,69,76,104,98,188,249,88,118,160,168,80,148,109,105,46,208,167,140,91,202,213,72,21,1,76,20,197,220,144,238,159,39,233,190,138,41,193,154,229,85,208,104,135,206,186,147,150,90,11,130,
165,162,179,174,3,238,164,67,226,251,134,232,153,108,184,76,47,210,70,5,52,146,223,100,46,20,113,92,96,180,160,67,79,230,152,133,60,177,232,172,71,173,122,214,221,52,208,143,167,119,219,150,151,9,177,
242,117,177,84,3,103,27,23,52,230,89,129,43,65,54,86,154,247,132,40,210,173,96,119,201,127,248,197,127,140,113,110,96,23,161,141,154,238,246,250,222,188,154,78,39,126,157,154,77,167,105,150,245,251,91,
254,41,62,127,254,18,169,67,201,251,42,244,224,210,38,216,77,228,142,241,205,66,238,92,18,202,78,212,185,196,94,9,11,138,120,163,58,4,249,56,233,22,91,90,132,35,64,119,75,67,241,6,63,140,224,21,197,214,
80,73,193,118,111,108,33,25,196,122,228,92,210,171,82,139,37,39,206,81,240,255,196,180,51,11,235,157,24,71,129,194,135,235,24,221,103,114,10,92,21,54,170,120,4,19,206,174,120,77,147,31,206,102,211,52,
207,69,246,75,153,96,125,203,17,226,61,15,63,116,161,59,83,125,132,168,163,31,176,120,4,95,52,52,27,113,132,198,196,36,220,90,31,65,82,147,46,30,33,98,205,86,188,111,52,130,9,82,174,42,244,53,126,176,
99,166,147,73,187,211,185,249,113,156,116,100,150,49,252,86,201,206,175,66,72,11,203,1,118,95,144,113,140,10,38,8,33,33,198,228,96,201,11,30,145,241,78,86,69,29,74,140,169,205,159,243,199,160,51,11,206,
78,182,180,179,226,205,132,215,93,133,57,35,74,19,230,172,64,132,198,190,134,178,212,242,135,192,59,28,119,220,184,108,62,184,46,145,236,12,216,64,61,134,133,54,49,103,188,120,140,28,174,116,93,171,140,
57,155,116,143,154,238,253,94,63,255,250,219,249,108,242,238,221,219,241,104,60,159,205,159,189,248,138,247,255,10,186,171,9,192,37,2,78,29,183,24,113,236,130,73,144,10,18,128,18,70,81,42,172,31,20,154,
1,118,205,237,106,77,104,70,4,117,89,89,143,64,126,163,232,9,139,139,145,158,223,58,46,51,34,95,8,5,84,109,97,161,196,159,71,207,78,69,17,175,240,46,210,22,89,148,121,78,34,209,84,191,45,64,121,221,82,
57,196,215,66,84,77,66,96,58,9,235,221,134,116,255,188,53,221,87,25,195,166,132,232,190,179,186,137,124,72,254,139,197,231,19,52,221,77,19,119,98,133,248,91,64,207,154,122,237,136,42,240,203,6,19,73,40,
118,196,223,207,212,170,231,141,95,47,204,121,181,249,64,248,32,68,159,133,200,129,16,57,198,192,125,190,83,210,189,169,233,78,29,143,211,244,223,253,233,158,166,196,10,25,51,150,99,70,228,80,208,234,
166,144,9,134,108,51,165,171,172,152,199,40,235,99,224,219,196,142,21,160,25,224,18,2,153,96,251,9,22,133,96,47,40,180,22,99,82,34,202,204,43,139,65,109,248,145,176,79,199,15,13,181,68,1,40,135,141,35,
224,120,180,164,176,22,68,73,248,147,225,241,155,215,175,44,43,225,188,120,241,85,167,211,167,239,58,172,85,72,134,114,224,41,145,102,25,26,246,163,139,232,249,134,116,255,140,53,221,87,46,208,43,131,
146,129,132,128,129,122,241,169,161,251,46,97,71,46,54,75,88,96,171,66,253,237,109,161,103,176,27,252,255,162,96,80,184,132,75,180,234,33,29,163,106,173,250,171,96,110,138,55,99,88,17,124,28,19,212,213,
101,62,156,220,191,91,210,221,112,214,15,154,238,120,221,217,183,231,12,149,13,182,50,251,24,84,188,78,146,237,108,125,112,215,67,255,115,116,205,133,20,116,200,7,82,255,181,138,165,90,233,63,28,9,82,
220,15,146,63,87,178,5,168,105,34,204,167,128,131,135,238,185,134,115,103,25,44,23,66,183,73,97,58,225,210,86,122,77,188,5,26,242,54,73,16,237,171,16,20,227,24,185,2,4,64,13,187,16,158,119,118,120,124,
244,248,209,227,9,253,25,255,225,15,223,251,207,251,217,243,175,122,189,62,60,75,37,193,88,106,145,194,177,182,4,47,163,255,93,102,229,213,134,116,255,140,73,247,213,11,244,104,25,82,40,177,118,210,116,
133,215,38,14,86,178,204,131,38,222,16,61,13,40,35,21,58,44,92,27,25,19,94,42,234,92,179,134,58,254,21,171,213,121,166,205,89,90,245,202,6,231,106,245,249,64,103,221,133,206,164,145,42,172,169,250,44,
153,23,87,190,46,45,221,103,175,69,186,35,169,199,33,97,255,84,10,21,122,221,112,98,94,18,10,236,211,217,32,170,39,28,164,213,110,137,116,39,47,70,139,95,42,93,38,197,253,179,46,192,168,120,206,92,166,
85,98,238,1,7,55,34,8,97,99,195,91,215,216,51,99,227,66,249,248,23,72,247,90,190,93,197,152,159,160,21,90,189,126,245,135,233,100,60,157,78,189,121,181,181,181,53,155,205,198,147,201,235,63,124,191,179,
187,251,248,233,243,72,157,98,5,180,65,58,157,83,29,142,243,9,102,67,186,127,198,164,251,234,99,156,55,163,16,124,224,87,130,178,223,90,116,205,51,255,41,113,142,210,239,150,182,152,187,184,124,222,16,
61,211,58,192,136,9,82,91,222,89,33,223,83,133,198,174,167,230,44,104,21,231,154,75,250,114,236,130,94,187,148,223,93,62,31,209,89,167,47,130,8,6,94,49,172,142,97,188,48,103,63,159,171,94,87,148,14,189,
38,233,30,170,91,36,104,155,82,12,69,162,205,1,119,119,226,178,197,38,17,167,72,247,72,163,154,232,60,242,47,86,165,69,88,154,140,73,146,145,169,156,212,62,171,90,221,153,87,159,48,21,4,197,18,44,70,70,
58,151,105,16,24,177,28,59,194,220,9,175,83,69,54,167,176,154,255,36,249,255,184,122,42,213,126,166,149,170,166,213,232,228,4,150,93,49,159,15,173,237,247,123,254,207,120,52,222,255,248,209,27,249,79,
158,60,75,178,76,133,230,213,162,209,34,125,52,69,230,117,67,186,111,198,96,12,244,209,131,219,174,42,45,187,43,146,218,173,60,183,156,85,193,231,117,139,232,25,199,161,36,145,132,12,102,158,101,205,57,
135,216,148,208,249,120,97,132,206,87,161,65,222,213,207,85,107,186,3,243,151,166,65,244,226,149,98,250,168,43,93,23,47,85,104,25,168,174,67,186,3,137,140,197,143,21,185,69,21,50,101,46,54,53,178,182,
40,29,231,63,88,39,39,146,238,126,1,215,54,36,146,37,226,68,200,143,21,87,197,80,247,30,110,4,93,81,43,104,35,212,181,52,251,194,246,149,128,50,23,188,148,252,29,222,21,172,168,41,24,139,124,106,197,106,
71,76,39,165,80,110,160,144,153,43,71,217,176,236,149,12,201,115,122,213,31,168,164,151,168,200,166,186,67,11,205,199,127,249,33,6,161,192,49,77,39,83,127,41,222,212,26,143,199,31,63,126,56,57,25,254,
241,31,255,84,145,107,89,105,180,33,128,196,141,118,148,222,166,59,183,33,221,63,127,210,125,21,115,3,218,231,69,81,6,221,115,193,170,253,27,13,117,54,74,182,80,220,91,223,58,122,6,237,115,191,177,73,
113,16,19,130,249,5,116,190,81,13,120,61,106,213,171,85,8,117,202,234,112,172,157,87,40,166,252,45,64,156,8,244,45,144,238,234,42,215,229,130,240,41,188,165,203,73,119,237,202,72,140,155,36,3,93,18,242,
184,28,171,179,181,116,186,192,254,126,73,130,250,149,65,176,69,1,40,15,136,154,139,71,64,160,23,13,20,227,45,164,248,147,170,123,220,98,247,73,216,21,95,36,221,21,139,207,113,164,217,74,113,169,88,127,
88,147,37,95,64,129,176,42,41,167,221,201,180,53,245,207,36,155,229,173,81,59,173,82,99,19,201,170,66,114,200,168,253,253,15,229,148,148,213,84,144,190,69,58,208,223,247,209,104,148,101,105,191,215,159,
205,167,191,253,237,119,63,251,147,63,11,196,37,78,157,32,110,173,181,217,144,238,95,2,233,190,210,24,91,114,136,10,58,51,36,72,73,54,14,111,186,244,140,240,104,149,187,11,210,61,210,249,34,28,192,248,
21,64,70,85,70,26,94,138,112,147,92,66,209,171,157,203,17,244,23,1,0,73,190,115,31,138,132,207,165,32,255,112,141,235,66,104,216,143,97,176,107,53,210,93,53,254,56,162,48,78,73,167,243,3,113,103,73,167,
155,38,117,221,224,182,25,182,20,161,197,59,32,221,103,102,58,222,58,241,103,232,156,116,218,243,174,177,166,65,186,151,145,116,47,231,229,135,119,239,188,165,131,174,144,64,47,200,213,227,173,199,223,
12,191,150,81,52,138,58,180,66,4,210,109,72,247,47,153,116,191,168,93,13,231,151,40,170,5,29,94,78,240,250,27,78,152,14,231,88,252,87,135,82,176,37,146,155,203,188,82,209,88,191,37,210,61,146,247,65,139,
221,197,6,122,77,26,94,53,132,88,175,116,46,86,31,76,98,174,217,95,187,146,107,151,38,242,200,74,95,131,98,231,133,214,80,243,132,43,144,238,141,63,36,255,90,205,232,181,94,148,78,135,32,2,55,53,243,223,
125,81,133,101,197,255,61,51,211,254,203,44,130,244,93,202,172,71,205,109,175,155,116,159,181,167,147,173,145,41,146,206,126,215,80,68,72,94,159,211,164,251,247,175,126,107,27,90,242,193,150,20,220,156,
175,21,249,14,51,24,236,160,143,244,134,116,223,144,238,231,144,238,101,147,116,47,249,159,177,185,182,178,108,206,217,240,51,48,46,201,228,72,93,203,173,233,181,115,166,210,90,33,221,185,232,3,108,167,
82,77,252,74,162,75,87,59,151,48,167,76,138,90,255,153,251,23,79,177,21,41,89,102,235,132,167,191,35,221,247,133,5,11,89,255,203,164,211,211,56,184,161,80,158,34,200,191,164,80,142,9,192,46,8,235,37,22,
20,41,232,193,130,194,166,142,139,180,107,144,78,215,248,222,192,39,233,16,111,150,186,101,230,116,167,157,209,180,55,77,103,121,255,120,43,150,83,163,93,147,228,28,248,84,254,215,71,39,199,227,201,24,
129,179,136,176,218,8,106,193,117,229,179,183,59,157,221,189,71,225,62,136,138,3,75,128,149,18,203,100,11,113,163,233,254,249,105,186,159,57,70,51,78,24,73,119,218,75,42,206,255,104,209,125,71,218,26,
245,6,153,223,77,9,181,75,206,196,184,28,111,114,232,233,112,91,56,88,154,100,21,45,67,54,232,181,139,22,59,183,103,87,28,14,86,215,62,87,160,243,117,162,81,214,147,74,238,203,136,238,59,174,29,206,19,
142,211,202,242,121,177,102,77,247,166,75,8,82,1,210,233,22,92,130,13,158,142,72,167,215,212,245,105,110,27,241,57,242,149,2,117,189,62,210,125,214,154,78,186,211,246,180,211,31,109,81,168,34,144,238,
254,23,230,179,201,104,56,244,203,19,18,183,180,180,77,167,212,77,131,129,0,163,27,252,58,236,82,208,24,20,209,54,219,219,59,27,210,125,67,186,115,204,81,195,190,134,25,37,107,13,226,85,242,19,9,23,200,
174,198,249,32,216,179,75,24,23,107,127,39,110,5,125,244,88,101,189,170,56,170,45,240,230,176,179,146,52,180,216,245,181,209,51,148,221,136,158,61,139,175,200,210,223,48,163,132,242,87,213,146,238,59,
120,192,53,106,186,55,23,44,246,89,108,148,78,199,38,19,122,5,214,26,231,103,73,167,11,96,157,9,183,45,212,245,250,72,247,194,204,167,131,113,62,203,122,39,61,126,54,146,114,30,143,78,14,62,126,72,179,
12,146,162,74,122,132,232,130,211,61,13,89,91,21,43,191,98,71,197,60,77,123,189,126,127,176,163,194,66,182,33,221,191,76,210,61,80,236,244,62,75,188,66,212,240,156,141,253,26,152,246,70,169,138,200,36,
56,240,114,203,20,123,248,254,93,45,106,122,142,238,187,195,147,186,112,204,2,14,134,176,62,23,149,81,74,202,18,247,147,249,23,245,6,90,236,76,231,179,83,76,55,3,169,48,196,104,121,11,148,251,147,241,
58,162,185,135,163,107,146,238,107,215,116,95,180,176,148,183,232,252,26,233,174,38,157,206,29,190,151,165,211,85,52,148,110,157,116,247,83,155,60,30,153,210,244,143,7,136,170,193,106,250,225,253,27,92,
242,116,50,145,30,39,252,167,98,206,13,137,2,122,237,68,248,199,176,224,17,173,143,148,198,206,243,44,207,243,63,237,152,35,163,165,125,246,134,116,255,82,53,221,171,66,114,97,224,105,66,25,52,7,169,12,
144,105,193,125,117,141,104,169,240,146,52,49,46,229,212,18,198,117,158,238,187,100,248,47,28,179,140,131,241,46,43,84,61,218,166,96,15,190,54,86,166,4,124,175,143,193,215,158,112,135,138,120,15,35,205,
32,228,189,186,67,77,247,230,130,149,24,168,76,112,79,160,85,165,211,19,105,245,30,165,211,173,109,114,219,235,32,221,135,189,35,127,224,237,195,221,72,186,251,249,188,127,247,106,116,114,82,65,135,128,
8,85,18,20,195,239,155,208,29,135,254,153,235,36,120,2,142,117,63,232,169,119,59,244,159,39,95,125,117,172,15,135,221,163,254,112,107,67,186,127,153,164,59,40,75,96,74,58,180,203,68,230,158,77,15,34,203,
137,98,119,246,180,166,187,191,165,121,178,72,141,207,231,110,53,221,119,222,224,197,137,3,234,69,169,198,21,197,81,153,170,39,28,236,250,8,27,213,216,49,86,38,215,37,178,31,200,221,243,55,122,166,230,
125,80,129,80,119,169,233,190,252,231,76,233,116,192,172,103,73,167,163,118,178,193,109,11,117,141,160,229,237,147,238,222,109,46,90,243,124,212,6,190,128,157,233,195,251,55,147,201,132,194,60,196,190,
166,4,12,54,92,66,198,125,101,190,240,229,120,215,80,129,94,41,119,183,250,123,143,158,233,202,100,227,86,209,155,218,19,233,235,189,33,221,191,76,138,157,19,226,86,240,75,177,125,106,213,143,202,86,43,
98,92,166,49,134,247,18,206,224,157,66,189,84,232,165,110,25,142,115,154,131,16,60,108,37,113,212,149,231,115,38,197,14,66,61,170,119,165,140,28,202,122,174,32,169,115,246,253,81,66,186,195,109,177,205,
249,216,192,30,173,69,211,61,254,153,23,115,74,223,171,51,164,211,147,83,210,233,41,109,22,231,74,167,27,116,253,226,38,90,183,75,186,207,186,83,127,1,173,105,43,146,238,163,209,241,120,60,246,191,59,
26,141,210,52,133,199,13,115,14,201,50,192,19,32,212,131,229,143,6,70,100,152,236,236,236,238,61,122,226,29,49,63,219,22,5,241,39,147,246,184,61,234,108,72,247,47,138,116,71,65,156,137,221,82,249,205,
92,32,185,181,98,190,193,73,214,71,217,75,4,75,57,14,21,252,60,117,25,234,197,132,0,47,15,236,93,122,67,129,69,32,214,140,176,45,16,243,236,224,120,75,28,149,55,136,93,4,73,104,181,84,192,136,49,37,139,
98,2,87,170,207,21,132,230,214,162,233,190,224,18,178,173,43,212,117,228,182,27,164,251,146,116,122,147,219,102,233,244,154,219,70,193,223,58,72,247,89,103,146,205,242,212,165,14,188,129,178,199,199,7,
254,68,179,217,148,218,79,100,217,116,50,37,242,51,74,93,48,75,34,198,26,56,117,127,88,71,81,37,111,177,247,119,118,182,183,183,77,2,121,70,149,185,180,229,237,183,206,180,55,233,213,248,221,134,116,255,
220,73,247,232,15,58,201,33,83,178,47,53,89,83,175,125,81,179,220,32,12,127,41,198,229,109,245,203,81,47,101,51,157,21,74,116,172,74,222,250,241,242,174,3,79,107,98,101,206,66,104,183,140,196,60,178,207,
8,43,95,108,214,37,58,169,169,250,112,46,192,204,107,212,116,127,88,164,123,153,21,222,66,233,77,90,145,116,31,143,189,93,53,158,205,102,254,125,242,159,58,246,41,86,106,47,149,133,230,132,142,154,165,
150,227,172,21,19,88,254,85,204,243,188,221,106,31,29,30,118,58,253,202,137,166,123,62,109,149,173,121,153,151,201,60,221,144,238,95,14,233,142,22,39,220,42,41,69,142,154,33,56,14,225,24,147,27,191,151,
165,224,110,164,56,140,158,178,185,0,227,18,36,74,185,85,80,175,66,218,122,138,221,64,81,89,105,96,188,14,60,77,180,216,237,25,20,123,10,89,85,196,251,46,108,213,35,113,97,244,10,187,51,236,238,129,145,
238,46,225,146,230,185,223,140,42,0,229,251,135,31,66,70,31,169,61,216,116,149,65,139,157,0,5,24,169,36,208,81,103,134,204,190,162,58,62,62,106,119,186,179,233,164,229,215,44,214,116,55,37,247,110,210,
101,102,242,13,233,254,165,145,238,216,104,121,19,173,181,216,253,11,37,122,196,180,209,194,99,186,18,50,166,46,30,195,253,237,53,105,182,176,87,102,32,214,114,171,52,124,83,99,158,34,194,220,249,89,148,
142,241,97,86,5,243,127,37,26,217,95,86,192,232,46,208,179,127,72,164,251,219,55,127,240,102,203,246,206,222,154,72,247,138,138,54,93,234,247,64,246,52,9,31,157,204,74,177,69,233,69,60,153,78,41,140,69,
23,92,233,32,102,173,66,53,57,178,180,209,213,99,56,131,118,225,241,100,220,234,108,241,203,29,54,141,196,59,153,27,210,253,139,32,221,57,23,66,183,151,182,100,250,106,43,190,183,58,34,90,21,235,63,145,
163,192,162,157,183,142,140,217,208,96,32,142,161,239,37,73,110,29,79,75,66,111,80,212,117,72,102,77,139,166,187,213,21,98,234,151,222,103,213,112,135,150,72,247,117,99,119,87,35,221,253,87,59,26,15,253,
15,211,44,203,242,246,124,62,243,187,86,187,221,41,230,83,152,133,147,201,184,44,10,255,119,28,150,74,187,253,222,240,248,168,162,94,97,253,201,120,148,166,153,127,246,157,94,143,124,183,107,145,238,46,
169,18,160,151,146,178,16,57,99,133,252,26,155,87,244,53,38,226,90,139,14,17,152,246,128,85,112,212,217,98,153,80,146,187,172,82,194,237,4,218,243,235,34,253,39,52,78,220,144,238,159,55,233,78,236,141,
9,208,58,63,226,51,181,216,215,135,140,9,222,163,196,59,211,129,29,191,221,115,65,139,61,40,88,185,104,70,112,16,69,93,213,68,170,169,122,193,49,238,8,187,187,26,233,254,250,237,107,255,18,248,213,199,
255,69,49,155,254,240,254,109,43,111,141,79,134,36,177,216,106,117,186,93,126,216,126,71,170,134,199,135,157,118,55,239,180,71,39,195,217,108,154,231,173,195,131,143,254,244,29,34,158,122,156,245,20,210,
125,180,115,132,205,223,74,250,133,150,174,20,100,41,104,37,14,189,119,247,251,172,54,228,82,5,248,152,142,64,159,166,191,119,137,52,170,225,84,52,221,119,36,16,3,217,142,182,40,172,156,175,130,78,169,
22,188,36,10,50,168,186,33,9,157,132,101,255,54,164,251,138,219,160,122,232,164,59,87,2,42,80,236,150,227,182,104,234,119,71,200,152,147,188,16,229,169,2,14,115,107,231,146,172,142,194,94,197,126,73,173,
67,207,9,177,10,187,249,85,42,1,34,233,46,14,208,61,37,221,253,79,230,179,249,120,116,178,179,243,232,228,228,216,63,217,221,39,207,252,107,241,246,213,239,253,176,221,157,199,71,7,7,157,118,167,55,24,
248,229,169,100,20,222,112,91,29,224,11,237,94,119,247,209,83,177,81,34,233,78,241,38,35,129,102,0,143,218,65,22,70,80,119,93,147,238,150,73,109,138,52,179,166,59,44,168,146,132,31,69,251,20,33,161,80,
176,42,127,32,244,158,240,66,134,198,209,108,191,80,229,96,187,213,242,191,238,159,144,95,209,5,172,199,255,113,185,231,134,116,191,76,215,92,180,226,16,19,121,184,164,123,112,175,181,141,74,44,119,136,
131,53,178,229,226,16,220,236,92,46,140,145,186,180,12,141,59,65,5,242,206,216,208,161,191,206,125,94,32,221,221,61,38,221,123,253,173,173,193,224,195,251,119,195,147,35,94,65,220,116,60,130,144,52,10,
26,104,105,115,66,186,123,75,203,255,109,49,159,89,185,83,202,187,138,56,249,108,58,205,91,45,24,166,219,199,59,193,188,112,145,116,7,241,43,166,8,246,64,110,65,70,13,197,90,85,83,211,221,127,162,168,
113,246,103,36,111,52,207,201,78,44,75,72,246,212,137,72,14,237,135,102,115,220,3,146,109,180,162,160,34,12,210,192,10,114,98,126,92,169,203,108,158,65,148,102,67,186,159,26,195,234,97,252,98,5,29,113,
169,18,69,123,152,7,74,186,139,246,57,113,203,234,52,197,190,62,100,204,111,30,24,131,16,170,190,165,115,133,144,168,164,98,224,39,97,23,15,154,238,230,122,247,249,206,72,119,34,239,213,13,72,119,255,
202,31,29,30,80,61,96,154,238,236,238,165,222,116,44,230,71,7,31,189,43,88,83,233,18,210,118,187,123,143,135,71,135,239,223,189,245,167,121,244,248,137,134,47,162,28,53,1,52,230,253,219,87,207,158,191,
204,91,237,43,147,238,21,181,104,133,171,136,69,196,155,73,133,174,151,127,4,169,36,115,29,42,236,253,209,97,100,73,156,2,56,184,178,237,118,123,62,159,251,35,80,112,141,125,97,110,203,168,121,93,212,
27,210,125,185,216,13,62,68,195,137,6,241,76,78,116,72,212,242,101,217,135,70,186,59,108,180,177,135,121,173,125,142,247,150,255,166,92,15,50,134,173,14,149,248,14,69,99,103,209,240,43,158,43,170,24,35,
140,83,217,96,181,241,117,133,172,130,186,149,74,0,213,208,116,183,120,39,111,67,171,190,108,8,186,70,253,120,120,91,87,36,221,181,251,250,155,31,35,246,1,2,224,249,243,151,76,186,167,145,116,127,254,
242,27,226,182,157,27,12,182,7,131,29,33,221,217,85,249,246,143,126,42,114,207,74,61,127,249,35,198,64,236,85,73,119,197,204,150,99,30,19,129,42,10,249,51,151,52,155,205,253,162,66,61,185,33,23,161,145,
124,84,86,162,246,232,250,3,41,50,178,189,58,157,254,100,50,246,6,72,158,231,221,110,143,235,242,169,178,26,252,158,247,212,185,65,230,134,116,63,99,235,214,130,11,82,154,60,229,157,160,214,53,143,58,
226,6,77,148,169,141,138,223,42,249,186,238,189,166,187,150,8,114,201,154,229,77,210,189,90,65,251,252,19,162,103,90,212,217,249,161,240,156,17,191,229,197,32,9,230,59,45,19,217,141,159,69,179,160,242,
76,77,247,85,230,172,66,251,12,204,29,229,219,65,91,69,37,138,91,139,114,227,81,11,158,41,60,139,7,70,186,195,247,174,210,50,179,25,2,224,131,157,71,227,201,152,226,244,68,114,27,191,104,6,1,156,216,50,
30,237,188,29,64,214,178,152,123,195,106,48,24,156,140,78,8,8,108,229,180,102,181,59,32,221,41,206,149,114,55,74,151,66,36,107,67,186,199,49,200,228,42,230,48,36,139,203,201,199,132,9,90,40,254,67,71,
220,177,142,56,123,186,22,91,37,97,182,6,118,152,9,130,175,247,139,116,71,206,216,73,216,211,48,65,234,63,28,153,179,16,225,118,142,157,239,190,161,103,204,41,40,217,135,140,44,86,104,132,76,220,12,26,
32,220,184,240,240,12,61,251,48,198,27,133,132,22,174,162,67,31,172,7,138,34,88,120,3,153,98,143,198,31,135,186,55,210,98,225,106,242,222,44,232,199,63,48,210,61,47,179,147,138,164,251,242,34,135,99,210,
106,181,73,153,104,94,36,105,150,106,85,122,139,195,8,207,134,85,99,123,123,80,81,237,98,225,253,62,90,59,210,158,63,201,241,240,216,111,53,254,14,248,133,160,183,181,37,81,25,126,93,103,237,153,127,230,
121,217,178,202,110,72,247,230,86,169,194,227,147,188,167,83,65,230,169,222,30,155,58,226,139,228,52,180,198,161,191,177,106,139,148,59,214,116,71,149,124,212,44,175,184,24,80,135,248,67,163,195,179,115,
247,12,61,139,207,34,82,236,152,42,76,4,142,60,221,242,125,142,122,246,58,8,246,102,58,189,100,206,38,105,106,204,187,56,103,90,209,164,131,160,232,139,133,132,123,124,127,68,46,209,91,54,191,252,229,
47,227,130,149,166,157,162,154,47,237,75,9,167,120,253,179,167,52,39,35,157,46,96,89,196,113,17,145,200,162,11,129,116,175,56,194,7,191,3,192,167,84,198,224,51,148,55,182,98,22,73,179,65,23,58,200,138,
120,24,53,17,74,56,183,168,234,140,137,17,85,63,246,154,39,249,56,155,228,254,98,160,191,224,29,186,241,232,196,31,230,248,248,216,15,251,217,207,126,246,139,95,252,226,187,223,252,155,95,4,158,61,127,
50,157,78,201,18,201,114,92,209,108,58,171,56,142,230,45,142,44,207,59,157,182,183,209,216,63,98,131,80,87,211,193,40,159,116,210,2,176,18,213,94,176,40,13,202,191,1,82,25,32,99,140,62,83,80,64,75,123,
53,201,142,227,142,89,190,99,140,116,210,59,80,204,230,157,110,215,15,230,40,184,65,194,51,222,49,19,239,24,116,153,201,160,3,182,154,184,112,88,33,221,93,85,31,150,83,34,140,119,20,72,122,46,76,204,162,
36,33,9,19,115,38,188,10,56,2,239,68,10,109,93,208,70,136,119,5,203,20,62,218,128,35,18,204,85,242,28,190,13,243,180,112,52,42,218,219,28,231,10,64,165,136,38,11,111,81,176,246,21,122,163,35,232,11,101,
97,104,181,224,92,176,37,235,169,242,87,226,63,9,29,30,246,121,243,89,101,206,182,168,218,157,206,149,142,83,177,252,49,72,119,60,17,126,69,19,168,137,226,186,144,94,0,213,198,64,117,133,175,75,80,38,
126,79,50,206,201,250,189,255,14,198,24,182,169,24,108,150,57,115,78,60,149,208,123,184,46,236,127,87,189,135,231,141,129,155,233,130,219,1,195,226,130,57,75,77,102,120,55,16,238,14,247,89,130,197,120,
63,227,187,97,23,222,13,195,27,157,91,88,176,42,157,70,232,71,18,231,38,56,86,10,108,166,252,80,133,182,128,13,68,219,176,241,86,133,128,159,88,75,81,81,72,58,70,135,222,212,42,52,137,16,241,29,164,225,
228,92,58,130,109,225,8,178,87,208,2,90,38,243,222,148,226,40,92,235,199,55,129,221,233,98,54,30,205,118,247,246,126,253,171,95,255,243,63,255,203,235,215,175,158,62,125,50,159,207,230,243,57,172,83,86,
185,214,173,188,229,23,217,44,203,80,41,189,247,232,153,66,180,147,47,109,222,159,150,121,217,63,222,34,216,82,62,48,29,22,35,27,250,201,6,181,160,112,189,42,108,23,11,119,140,194,103,245,15,103,179,105,
154,231,70,135,66,130,112,127,79,223,49,13,245,174,208,19,168,121,207,241,162,132,123,142,224,130,134,154,56,142,208,152,88,104,132,27,143,32,169,73,23,143,128,106,112,45,218,246,146,86,199,103,41,229,
9,129,98,140,168,33,178,182,208,246,198,194,135,35,196,144,124,212,113,77,13,92,99,7,173,97,49,97,194,14,100,66,134,55,86,167,75,192,64,44,2,236,94,250,188,249,172,50,103,255,255,211,201,132,23,44,181,
250,113,76,29,183,144,229,23,47,42,60,0,5,252,146,151,12,236,235,184,57,168,109,136,105,104,255,197,114,61,22,109,45,38,220,159,53,141,225,103,97,67,71,12,9,49,170,144,93,143,247,48,104,13,94,249,30,158,
57,70,199,49,117,22,40,104,222,159,53,231,152,185,146,30,242,38,9,43,148,9,124,183,14,159,225,194,156,85,99,62,130,55,61,56,77,119,239,29,230,179,124,214,246,102,86,139,218,228,240,167,252,244,241,139,
215,175,254,224,205,165,95,255,234,191,190,127,255,254,31,254,225,239,119,118,118,1,34,144,49,197,6,139,63,23,59,113,132,48,24,142,187,236,236,62,174,251,117,123,131,209,84,243,206,44,155,230,170,82,44,
239,183,209,116,7,241,92,198,62,216,48,238,129,95,45,163,76,122,17,209,170,100,140,116,229,14,14,161,150,109,25,241,16,203,191,8,61,114,74,180,87,174,196,176,144,41,81,55,41,82,187,137,166,187,140,177,
162,233,14,204,111,73,211,61,84,83,124,50,244,140,72,5,134,122,224,238,224,5,40,42,81,125,96,148,102,93,21,5,108,130,73,97,153,128,204,188,130,20,77,109,120,249,216,1,190,232,168,203,234,194,61,228,0,
104,26,18,130,16,212,188,100,206,15,82,211,189,115,210,159,237,125,24,237,14,183,247,119,233,58,141,249,238,187,255,231,159,220,47,255,211,47,253,223,254,237,223,254,207,78,183,211,233,180,202,178,224,
54,188,8,4,82,150,150,82,111,44,249,152,181,114,90,173,240,21,133,50,249,227,237,3,239,199,13,78,250,202,232,141,166,59,136,103,176,96,170,134,52,164,152,233,42,26,225,232,51,170,51,90,121,69,107,92,130,
140,244,61,88,110,253,146,114,64,4,97,7,185,189,81,67,253,238,53,221,27,4,127,226,164,168,94,5,161,93,169,146,229,184,50,103,84,244,167,65,207,208,188,199,65,139,156,222,237,188,148,231,149,220,77,69,
1,210,116,245,231,80,63,83,54,136,88,243,158,178,61,65,27,222,65,24,94,100,14,104,17,203,210,172,44,41,88,177,250,156,31,164,166,187,191,188,157,225,163,227,237,195,225,224,184,119,212,47,139,234,100,
52,252,230,155,111,126,254,243,159,255,205,223,252,141,31,180,179,189,77,135,34,145,8,74,186,145,231,194,86,13,153,105,137,217,26,236,246,250,3,118,51,105,177,244,183,163,112,229,120,231,164,210,229,224,
104,39,241,126,49,42,177,55,154,238,10,186,230,21,182,179,160,66,167,242,244,10,184,83,34,99,22,180,198,153,107,163,155,82,114,37,29,86,97,118,108,21,215,133,42,113,72,148,137,244,57,190,144,59,208,116,
111,140,209,167,105,120,21,58,152,216,104,57,10,23,119,199,88,25,32,40,19,43,249,11,121,94,250,206,42,10,184,194,161,82,34,48,193,222,168,68,247,172,196,175,249,6,33,251,218,208,134,63,163,82,162,170,
144,161,189,124,62,15,82,211,157,226,112,51,221,25,118,199,253,209,164,63,30,253,118,88,22,229,95,254,197,95,252,227,63,254,159,223,253,254,183,95,127,243,163,189,189,199,254,208,147,241,104,60,62,145,
20,15,181,152,104,183,242,118,154,230,254,216,136,246,113,254,141,44,151,249,96,98,219,182,59,236,155,34,177,170,170,153,204,13,233,46,186,64,240,141,19,136,73,248,157,252,182,176,169,101,125,116,110,
202,29,210,197,9,231,166,75,86,10,178,129,170,95,175,166,251,42,99,16,143,45,69,247,93,238,33,4,75,239,68,100,85,180,81,177,1,83,38,154,214,248,234,19,86,20,132,194,92,242,102,42,102,101,216,87,173,162,
46,254,162,54,60,231,228,5,36,105,30,103,37,242,254,225,105,186,67,202,197,15,104,77,219,214,216,73,123,244,195,251,119,255,245,87,191,26,79,38,255,235,127,255,221,243,231,207,158,62,121,1,95,201,155,
81,189,254,22,74,116,34,150,197,252,145,3,182,194,152,144,245,102,90,149,21,173,147,110,62,105,113,186,193,4,38,126,67,186,151,160,162,85,72,115,75,68,243,246,176,169,69,44,72,215,206,174,210,46,82,218,
174,73,105,223,47,221,247,38,237,205,188,200,90,69,86,163,198,188,101,200,64,223,185,89,119,246,24,80,155,22,21,14,77,170,158,255,225,148,54,188,189,201,185,30,158,166,187,130,173,206,150,103,123,212,
153,31,204,126,242,211,159,126,245,226,197,95,255,245,95,15,182,183,247,30,191,40,200,72,52,66,123,41,40,208,250,41,88,64,186,54,148,134,250,57,168,212,77,119,199,54,45,187,199,91,221,121,207,25,199,185,
88,145,226,222,104,186,199,237,93,199,28,30,185,195,137,115,107,210,26,87,13,145,197,10,184,108,16,5,34,250,252,170,148,246,149,73,247,235,209,222,28,246,14,94,204,186,176,50,120,38,117,128,88,187,80,
49,120,207,244,245,17,42,231,10,7,190,63,183,92,225,240,240,52,221,85,236,129,138,78,179,135,147,255,242,235,191,252,187,191,251,251,73,57,125,241,103,47,147,137,95,201,16,193,6,146,206,110,157,21,253,
63,177,223,252,241,76,85,116,103,211,206,196,79,124,235,112,39,41,211,72,186,91,137,151,155,141,166,123,201,0,176,0,199,148,53,182,146,193,228,84,227,186,73,110,161,162,181,142,90,227,76,204,235,117,144,
238,215,54,15,3,206,6,41,244,146,211,179,115,183,38,45,118,147,43,83,69,138,157,191,143,123,164,175,15,39,143,199,176,220,116,80,145,188,221,115,61,48,210,93,115,165,184,212,121,250,223,173,202,255,252,
231,127,254,225,195,199,223,124,247,155,167,255,254,249,164,61,158,245,166,217,44,107,77,218,186,242,207,217,47,207,22,30,37,92,218,66,21,54,161,190,59,69,171,240,87,210,46,58,221,113,143,170,90,129,50,
197,194,12,158,71,12,16,127,201,164,59,208,42,29,154,160,160,134,60,128,236,119,72,114,139,194,158,17,74,198,185,117,144,238,215,24,3,231,21,177,214,72,195,139,211,126,235,2,170,174,18,211,182,174,194,
187,239,250,250,160,61,111,241,92,15,76,211,157,147,8,154,225,26,210,132,49,42,251,221,239,191,127,247,230,245,143,191,253,169,59,114,173,147,78,213,43,230,221,121,145,15,69,175,166,98,239,209,191,232,
169,223,191,74,33,105,42,213,26,181,59,179,78,226,18,88,148,222,155,162,248,26,87,116,179,3,229,167,84,193,180,253,76,52,221,153,14,83,172,100,125,90,211,189,217,70,229,124,125,116,52,22,162,215,41,54,
119,34,210,125,253,34,162,33,79,93,242,162,159,0,205,91,147,166,251,213,199,208,156,253,157,73,24,186,86,13,76,201,15,190,45,45,246,130,111,2,109,252,204,122,112,183,1,253,249,105,240,175,50,70,255,213,
95,253,85,92,176,108,210,117,78,114,216,200,72,194,13,84,22,235,58,178,52,22,94,18,104,41,222,253,18,73,245,74,176,92,132,94,130,195,87,43,120,32,183,233,98,155,54,94,227,196,247,9,190,158,10,186,163,
88,104,193,14,202,97,229,39,65,54,43,8,173,133,108,187,156,152,22,213,172,176,222,51,76,181,255,111,239,253,145,239,100,41,52,109,188,135,106,147,172,200,107,157,45,23,188,62,153,3,92,89,11,253,44,21,
149,189,67,101,150,107,92,81,243,122,85,188,57,241,142,201,245,201,29,59,62,58,236,15,182,87,184,99,46,94,218,194,97,67,254,84,215,71,168,127,24,197,117,150,142,224,66,106,95,135,137,199,32,145,146,44,
2,20,232,37,35,141,93,172,1,212,132,14,5,161,150,34,66,208,126,105,134,70,184,84,5,54,133,43,217,15,79,169,113,241,2,206,115,189,49,180,28,243,152,96,100,33,202,235,226,124,206,155,179,255,215,227,131,
195,237,221,221,139,199,172,114,156,51,199,200,235,200,170,147,82,87,160,5,141,190,189,107,39,101,55,182,175,77,12,158,96,62,112,161,214,113,93,247,124,204,195,35,221,197,40,14,252,42,72,119,198,193,45,
38,70,57,178,89,170,77,110,10,120,142,226,223,214,170,221,154,171,196,165,33,24,46,13,64,185,0,112,177,48,232,97,145,238,200,10,115,134,91,190,40,225,216,104,101,18,182,194,5,102,38,97,237,36,54,145,184,
93,99,101,235,157,234,60,237,243,160,47,118,22,237,45,122,228,183,142,252,20,13,61,114,36,191,75,91,147,220,107,39,221,47,49,127,82,133,134,114,170,177,103,58,119,91,20,59,97,74,161,18,128,107,57,117,
233,66,239,194,178,250,252,52,248,87,25,243,32,73,119,126,101,9,1,67,210,155,21,251,93,0,202,81,205,39,224,56,12,37,254,74,105,45,136,66,116,112,208,92,44,225,211,186,169,233,142,198,22,15,139,116,215,
117,175,13,188,254,9,223,25,220,70,84,186,216,80,67,225,16,39,182,220,69,42,144,229,140,123,40,191,195,156,75,60,131,246,22,237,243,6,237,77,81,51,189,94,109,111,21,244,200,173,226,57,7,251,120,205,164,
251,133,186,230,73,134,69,94,42,1,148,84,235,170,219,165,216,181,117,225,92,238,42,68,248,231,58,230,65,146,238,100,142,176,166,59,190,229,178,168,130,114,78,130,168,48,236,44,203,97,111,50,85,24,2,224,
158,186,21,86,180,80,80,93,147,238,161,148,24,19,190,239,164,123,194,204,48,7,231,105,33,166,125,130,44,45,100,69,17,92,103,168,145,184,55,32,178,180,100,75,116,95,10,185,157,244,224,80,97,55,73,76,88,
208,213,197,218,231,11,180,183,210,33,36,42,85,185,183,142,252,128,134,23,129,58,173,172,72,131,220,1,233,126,246,24,44,241,222,216,97,61,104,41,212,183,193,3,191,29,138,29,123,115,34,251,22,210,163,84,
107,185,50,17,254,185,142,121,168,164,123,212,116,87,225,227,95,152,24,194,91,124,58,17,227,15,253,83,97,38,162,191,78,36,221,83,190,222,168,233,254,96,72,119,113,225,181,2,199,149,177,104,42,81,227,85,
224,197,69,148,6,126,44,172,107,22,138,172,98,93,113,40,150,55,145,44,151,187,126,161,166,251,34,237,45,15,54,168,107,164,183,139,252,68,26,62,126,198,112,159,239,158,116,23,221,119,1,12,137,15,140,225,
149,80,67,159,222,2,197,110,80,244,25,158,5,225,227,246,230,90,236,159,199,152,7,76,186,55,195,249,17,230,78,64,129,41,39,76,185,212,134,251,101,200,196,189,145,173,108,33,221,67,111,17,9,70,63,36,210,
157,22,77,206,105,186,104,239,84,226,48,158,70,90,22,5,39,195,152,179,201,114,172,149,89,154,150,103,147,229,246,52,237,45,228,10,110,23,105,93,84,183,78,195,215,228,244,39,32,221,93,160,158,92,36,239,
107,221,119,45,43,60,101,105,111,134,50,69,45,118,255,96,23,41,246,236,222,235,226,223,209,152,135,77,186,51,157,148,178,56,145,193,196,152,252,78,86,36,221,161,60,147,48,114,153,25,209,116,127,16,164,
59,66,129,28,206,39,119,88,66,81,234,22,201,114,237,221,225,139,181,216,155,180,119,173,233,190,6,218,27,10,91,104,200,236,255,237,83,145,238,12,3,38,208,7,227,176,32,8,47,49,127,130,66,185,186,158,22,
187,82,82,124,215,208,98,103,39,158,151,179,91,44,222,124,232,99,30,60,233,78,179,8,56,120,156,216,165,164,187,226,120,185,10,179,229,188,225,67,33,221,253,224,84,194,78,108,105,130,8,119,107,32,203,87,
33,149,69,80,20,180,55,127,144,37,107,159,223,22,237,45,120,45,187,66,96,140,63,9,233,142,48,130,83,165,3,217,107,68,47,55,75,114,42,72,189,46,94,36,186,230,138,12,109,149,44,104,177,91,33,171,239,5,197,
126,127,198,60,108,210,29,238,11,142,208,196,193,163,66,166,55,86,26,164,59,177,194,178,156,197,83,177,232,48,112,238,7,65,186,43,70,28,76,192,196,252,28,50,144,95,107,32,203,93,64,58,46,38,203,107,218,
155,111,83,10,13,178,91,157,79,232,171,96,228,62,175,71,211,253,172,49,42,230,105,13,111,63,194,211,68,250,156,93,254,107,95,87,132,16,43,233,128,17,114,202,181,201,118,127,41,246,79,50,230,225,105,186,
147,56,12,199,86,248,107,167,33,137,204,86,180,119,181,136,50,107,17,86,86,208,93,77,96,195,107,105,176,235,18,52,1,99,139,50,106,186,43,23,250,17,80,70,245,30,105,186,11,19,194,122,9,82,115,227,228,81,
222,186,70,56,138,168,203,160,107,142,111,255,66,253,111,131,8,39,30,31,63,104,58,78,106,82,206,204,222,116,62,68,145,57,21,192,253,43,232,208,95,67,211,125,105,12,204,252,198,117,25,240,52,160,252,175,
122,93,88,239,78,107,177,99,151,66,204,3,105,150,155,235,217,127,174,99,214,173,233,46,210,168,129,93,149,0,9,199,152,144,79,132,166,123,18,147,85,78,164,211,235,35,212,154,238,130,193,235,165,137,113,
148,35,89,16,62,151,52,95,34,112,54,130,244,42,104,67,107,73,109,201,170,93,43,178,139,214,186,0,92,16,95,231,56,22,31,54,178,78,250,238,53,221,35,121,143,149,177,214,194,91,131,142,56,171,212,138,25,
219,212,8,191,64,255,219,52,116,223,97,106,165,220,5,227,186,243,17,106,156,253,175,20,245,104,65,103,93,173,85,211,253,204,235,2,115,39,215,149,64,229,198,94,245,186,228,85,83,241,186,144,174,113,108,
143,215,215,117,241,125,190,161,22,251,103,48,102,237,164,251,2,14,126,14,183,13,28,156,143,64,163,141,57,79,161,92,38,230,216,49,164,47,223,161,53,26,38,102,168,148,239,156,137,53,128,242,196,212,135,
189,4,40,111,76,236,10,210,233,183,78,186,91,200,54,178,144,149,129,112,35,237,57,235,197,94,224,4,53,200,114,117,49,133,12,232,41,174,161,133,45,216,214,189,166,0,102,116,69,97,88,137,254,247,21,11,244,
110,66,186,139,102,57,99,107,161,173,139,58,79,207,254,130,235,210,65,60,213,32,145,21,178,128,82,56,193,209,0,178,170,110,163,240,112,67,186,223,148,116,15,220,118,98,235,98,23,80,215,11,220,118,157,
47,231,144,115,84,40,143,64,185,224,224,97,98,136,127,39,139,64,249,57,19,59,13,148,171,37,160,188,174,171,184,104,98,11,210,233,119,73,186,59,21,75,255,21,224,126,232,126,174,27,123,129,38,183,99,42,
53,54,167,191,148,84,22,95,213,162,6,200,242,70,151,132,146,72,115,169,112,37,179,35,166,214,125,15,13,227,163,102,249,93,106,186,43,73,155,130,126,187,14,197,46,45,163,36,179,108,64,84,97,239,129,174,
57,165,167,175,126,93,95,242,152,229,226,103,255,181,51,233,238,192,109,39,218,68,210,189,228,118,126,192,193,65,186,51,9,81,4,70,90,163,179,147,166,29,70,72,119,132,51,144,217,43,88,225,0,135,141,214,
4,23,76,213,148,249,194,97,131,66,121,106,146,16,65,47,236,213,38,134,168,217,37,19,35,235,29,129,124,35,237,115,206,155,152,159,82,83,58,189,158,88,85,176,81,22,47,77,72,247,230,196,78,142,143,182,182,
183,79,93,90,61,49,135,149,200,104,148,185,112,97,147,76,76,86,64,160,255,156,74,100,107,142,217,118,241,86,200,201,135,208,48,149,103,34,67,192,145,184,107,143,9,181,129,66,142,161,148,83,42,174,131,
41,193,110,178,142,9,16,20,117,59,101,69,168,27,241,56,19,90,102,81,39,34,11,122,246,244,185,194,24,5,74,45,4,242,1,3,138,28,252,169,115,93,50,159,225,209,241,96,103,119,133,57,47,31,39,162,194,162,147,
137,202,47,180,249,92,249,30,138,248,143,64,211,146,204,136,247,231,74,243,217,140,137,99,254,191,0,3,0,88,210,46,40,57,66,7,130,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* JuceDemoPluginAudioProcessorEditor::uibg_png = (const char*) resource_JuceDemoPluginAudioProcessorEditor_uibg_png;
const int JuceDemoPluginAudioProcessorEditor::uibg_pngSize = 65015;

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

// JUCER_RESOURCE: wet_off_png, 643, "../wet_off.png"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_wet_off_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,35,0,0,0,13,8,2,0,0,0,172,29,64,72,0,0,0,4,103,65,77,65,0,0,
175,200,55,5,138,233,0,0,0,25,116,69,88,116,83,111,102,116,119,97,114,101,0,65,100,111,98,101,32,73,109,97,103,101,82,101,97,100,121,113,201,101,60,0,0,2,21,73,68,65,84,120,218,188,84,93,111,211,48,20,
141,29,39,91,91,72,154,166,165,116,105,203,74,181,15,40,31,15,252,51,132,132,120,64,252,57,94,120,152,52,105,83,187,181,165,83,197,86,54,232,40,42,41,153,98,59,230,56,129,23,30,218,73,149,118,165,220,
196,206,177,239,185,231,94,155,188,121,247,65,38,210,80,202,32,196,164,148,80,202,168,201,5,87,134,98,38,195,52,44,73,146,117,48,24,16,66,153,126,76,227,175,17,2,23,139,152,24,248,73,165,148,233,156,185,
38,38,229,33,25,34,99,152,40,112,210,14,20,224,128,196,127,240,202,160,240,235,96,96,58,123,253,82,42,81,169,25,10,112,219,98,92,8,204,88,132,232,245,25,244,31,102,62,255,57,234,159,84,107,65,117,171,
158,97,62,159,28,25,75,237,241,222,115,232,201,184,228,223,175,38,81,20,5,141,237,205,141,141,179,209,160,232,149,60,207,255,58,57,15,195,121,45,104,10,33,166,223,46,17,176,84,174,56,174,55,159,205,126,
92,79,145,76,161,112,207,243,203,49,231,198,42,131,116,224,201,40,162,217,246,240,240,0,124,29,215,237,247,142,131,198,163,92,46,223,61,62,116,28,247,97,173,126,240,233,99,62,95,216,204,229,135,253,222,
179,151,175,22,139,16,139,163,104,17,134,191,156,162,7,178,171,35,41,72,165,24,74,234,121,229,146,95,25,159,13,239,59,110,46,95,184,248,50,134,23,156,55,91,237,171,203,9,62,64,66,164,220,49,12,26,77,0,
32,64,208,220,206,234,97,220,194,56,23,212,52,65,139,182,218,187,216,107,118,61,221,121,210,209,244,79,187,213,218,150,95,126,192,44,93,72,84,5,251,238,236,117,32,151,16,50,19,4,165,211,107,201,234,156,
0,179,173,116,35,212,29,91,32,173,232,247,194,47,87,144,74,191,123,212,222,125,138,198,173,55,91,55,209,205,120,52,224,156,59,110,113,191,243,34,142,227,172,145,179,30,33,183,136,132,212,117,139,190,126,
251,62,235,47,156,46,140,225,133,20,150,105,233,148,37,116,195,60,69,227,46,193,140,7,189,229,145,26,237,125,221,123,88,152,157,109,137,227,7,89,40,181,153,253,223,249,135,45,193,160,137,87,222,17,152,
188,163,59,2,2,222,209,29,1,213,255,8,48,0,253,48,161,89,87,214,229,35,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* JuceDemoPluginAudioProcessorEditor::wet_off_png = (const char*) resource_JuceDemoPluginAudioProcessorEditor_wet_off_png;
const int JuceDemoPluginAudioProcessorEditor::wet_off_pngSize = 643;

// JUCER_RESOURCE: wet_on_png, 641, "../wet_on.png"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_wet_on_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,35,0,0,0,13,8,2,0,0,0,172,29,64,72,0,0,0,4,103,65,77,65,0,0,
175,200,55,5,138,233,0,0,0,25,116,69,88,116,83,111,102,116,119,97,114,101,0,65,100,111,98,101,32,73,109,97,103,101,82,101,97,100,121,113,201,101,60,0,0,2,19,73,68,65,84,120,218,188,84,209,110,211,48,20,
141,157,180,91,83,72,154,38,165,116,105,67,171,168,219,160,8,144,64,226,11,120,225,133,159,65,66,72,72,19,226,133,15,227,133,135,73,147,152,58,232,170,78,213,160,108,208,81,84,82,50,197,118,204,113,2,
175,116,82,165,94,169,55,181,125,236,123,238,185,215,38,207,95,238,137,84,104,82,106,132,232,148,18,74,13,170,51,206,164,38,13,221,192,52,44,77,211,85,48,24,16,66,13,245,211,181,191,70,8,92,194,19,162,
97,145,10,33,178,57,125,69,76,198,67,24,136,140,97,42,193,73,57,80,128,3,18,235,224,149,67,225,87,193,192,84,246,234,35,101,42,51,211,36,224,197,130,193,56,199,76,129,16,181,63,135,254,195,204,231,63,
71,131,143,245,134,95,223,106,230,152,183,111,246,180,255,218,139,87,175,161,167,193,4,251,126,62,137,227,216,111,181,55,55,54,78,70,199,21,167,234,56,238,215,201,231,40,154,55,252,128,115,62,253,118,
134,128,85,175,102,217,206,124,54,251,113,49,69,50,229,242,53,199,245,18,198,180,101,6,233,192,211,160,136,86,44,14,15,246,193,215,178,237,193,209,161,223,186,85,42,153,253,195,3,203,178,111,54,154,251,
239,223,153,102,121,179,100,14,7,71,119,239,63,92,44,34,108,142,227,69,20,253,178,42,14,200,46,143,36,33,149,52,80,82,199,241,170,110,109,124,50,188,110,217,37,179,252,229,116,12,207,25,11,58,225,249,
217,4,127,64,130,103,220,49,244,91,1,0,16,192,15,218,121,61,180,43,24,99,156,234,58,104,209,78,184,141,179,102,23,211,238,237,158,162,255,169,95,111,108,185,222,13,163,160,10,137,170,224,220,238,78,15,
114,113,46,114,65,80,58,181,151,44,207,9,176,98,33,59,8,117,199,17,72,43,254,189,112,189,26,82,25,244,63,132,219,119,208,184,205,160,115,25,95,142,71,199,140,49,203,174,236,246,238,37,73,146,55,114,222,
35,228,10,145,144,186,186,94,40,120,222,95,15,30,61,198,24,119,12,250,180,219,161,74,89,64,55,45,236,238,34,227,28,131,85,96,158,60,125,198,5,199,157,205,49,75,35,137,52,197,77,35,235,121,35,48,185,166,
55,2,2,174,233,141,128,234,127,4,24,0,109,94,161,208,252,42,126,109,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* JuceDemoPluginAudioProcessorEditor::wet_on_png = (const char*) resource_JuceDemoPluginAudioProcessorEditor_wet_on_png;
const int JuceDemoPluginAudioProcessorEditor::wet_on_pngSize = 641;


//[EndFile] You can add extra defines here...
//[/EndFile]
