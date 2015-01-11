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
	laf.setColour (Slider::rotarySliderFillColourId, Colour (0xff00b5f6));
	laf.setColour (Slider::rotarySliderOutlineColourId, Colours::white);

	laf.setColour (TextButton::buttonColourId, Colours::white);
	laf.setColour (TextButton::textColourOffId, Colour (0xff00b5f6));
    laf.setColour(GroupComponent::textColourId, Colour(0xff000000));
	laf.setColour (TextButton::buttonOnColourId, laf.findColour (TextButton::textColourOffId));
	laf.setColour (TextButton::textColourOnId, laf.findColour (TextButton::buttonColourId));
};

//[/MiscUserDefs]

//==============================================================================
JuceDemoPluginAudioProcessorEditor::JuceDemoPluginAudioProcessorEditor (JuceDemoPluginAudioProcessor* ownerFilter)
    : AudioProcessorEditor (ownerFilter)
{
    addAndMakeVisible (groupComponent = new GroupComponent ("new group",
                                                            TRANS("output")));

    addAndMakeVisible (reverGroupComponent = new GroupComponent ("new group",
                                                                 TRANS("reverb")));

    addAndMakeVisible (delayGroupComponent = new GroupComponent ("new group",
                                                                 TRANS("delay")));
    delayGroupComponent->setTextLabelPosition (Justification::centredLeft);

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

    addAndMakeVisible (delayTimeSlider = new Slider ("new slider"));
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

    addAndMakeVisible (hpfSlider = new Slider ("hi pass filter"));
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

    addAndMakeVisible (delayTimeSlider2 = new Slider ("new slider"));
    delayTimeSlider2->setRange (0, 1, 0);
    delayTimeSlider2->setSliderStyle (Slider::RotaryVerticalDrag);
    delayTimeSlider2->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    delayTimeSlider2->addListener (this);

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

    addAndMakeVisible (dry = new ToggleButton ("new toggle button"));
    dry->setButtonText (TRANS("dry"));
    dry->addListener (this);
    dry->setToggleState (true, dontSendNotification);

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

    addAndMakeVisible (donateBtn = new ImageButton ("new button"));
    donateBtn->addListener (this);

    donateBtn->setImages (false, true, true,
                          ImageCache::getFromMemory (images1_jpg, images1_jpgSize), 1.000f, Colour (0x00000000),
                          Image(), 1.000f, Colour (0x00000000),
                          Image(), 1.000f, Colour (0x00000000));
    addAndMakeVisible (bypassBtn = new ToggleButton ("new toggle button"));
    bypassBtn->setButtonText (TRANS("bypass"));
    bypassBtn->addListener (this);

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("+")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    cachedImage_uibg_png = ImageCache::getFromMemory (uibg_png, uibg_pngSize);

    //[UserPreSize]
	addAndMakeVisible(resizer = new ResizableCornerComponent(this, &resizeLimits));
	resizeLimits.setSizeLimits(150, 150, 800, 300);
    //[/UserPreSize]

    setSize (400, 200);


    //[Constructor] You can add your own custom stuff here..
	// set our component's initial size to be the last one that was stored in the filter's settings
	setSize(ownerFilter->lastUIWidth, ownerFilter->lastUIHeight);
	setSize(800, 400);
    startTimer(50);
	gainSlider->setDoubleClickReturnValue(true,0.0f);
	//cutom rotary start and end position
	//gainSlider->setRotaryParameters(1.0f*3.14f+0.1f,(12.0f/4.0f)*3.14f-0.1f,true);
	panSlider->setDoubleClickReturnValue(true,0.5f);
	midSideSlider->setDoubleClickReturnValue(true,0.5f);
	setupCustomLookAndFeelColours(guilaf);
	LookAndFeel::setDefaultLookAndFeel(&guilaf);
    //guilaf.setDefaultSansSerifTypefaceName("Aharoni");
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
    //[/Constructor]
}

JuceDemoPluginAudioProcessorEditor::~JuceDemoPluginAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	//deleteAllChildren ();
    //[/Destructor_pre]

    groupComponent = nullptr;
    reverGroupComponent = nullptr;
    delayGroupComponent = nullptr;
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
    delayTimeSlider2 = nullptr;
    delayTimeValueLabel2 = nullptr;
    delayAmountHeader = nullptr;
    lnf3Btn = nullptr;
    guilafBtn = nullptr;
    guilaf2Btn = nullptr;
    dry = nullptr;
    slider = nullptr;
    reverbSizeHeader2 = nullptr;
    slider2 = nullptr;
    reverbSizeHeader3 = nullptr;
    slider3 = nullptr;
    reverbSizeHeader4 = nullptr;
    donateBtn = nullptr;
    bypassBtn = nullptr;
    label = nullptr;


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
    g.drawImage (cachedImage_uibg_png,
                 4, 4, 1920, 1040,
                 0, 0, cachedImage_uibg_png.getWidth(), cachedImage_uibg_png.getHeight());

    //[UserPaint] Add your own custom painting code here..

    //[/UserPaint]
}

void JuceDemoPluginAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    groupComponent->setBounds (8, 8, 144, 112);
    reverGroupComponent->setBounds (456, 13, 408, 100);
    delayGroupComponent->setBounds (208, 13, 240, 100);
    panSlider->setBounds (100, 159, 80, 50);
    infoLabel->setBounds (40, 432, 400, 25);
    gainSlider->setBounds (73, 24, 80, 50);
    delaySlider->setBounds (208, 47, 80, 50);
    gainInfoLabel->setBounds (73, 72, 80, 20);
    panInfoLabel->setBounds (100, 209, 80, 20);
    delayTimeSlider->setBounds (288, 47, 80, 50);
    delayTimeValueLabel->setBounds (288, 27, 80, 20);
    panHeader->setBounds (100, 139, 80, 20);
    midSideSlider->setBounds (20, 154, 80, 50);
    midsideHeader->setBounds (10, 134, 80, 20);
    saturationSlider->setBounds (120, 309, 100, 50);
    distortionHeader->setBounds (132, 296, 80, 10);
    hpfHeader->setBounds (258, 150, 80, 30);
    hpfSlider->setBounds (268, 170, 60, 50);
    reverbSizeSlider->setBounds (472, 48, 50, 50);
    midsideInfoLabel->setBounds (10, 209, 80, 30);
    reverbSizeHeader->setBounds (456, 24, 80, 30);
    delayTimeSlider2->setBounds (368, 47, 80, 50);
    delayTimeValueLabel2->setBounds (368, 27, 80, 20);
    delayAmountHeader->setBounds (208, 24, 80, 24);
    lnf3Btn->setBounds (216, 384, 88, 24);
    guilafBtn->setBounds (320, 384, 88, 24);
    guilaf2Btn->setBounds (432, 384, 88, 24);
    dry->setBounds (24, 32, 48, 24);
    slider->setBounds (536, 48, 50, 50);
    reverbSizeHeader2->setBounds (520, 24, 80, 30);
    slider2->setBounds (608, 48, 50, 50);
    reverbSizeHeader3->setBounds (600, 24, 80, 30);
    slider3->setBounds (688, 48, 50, 50);
    reverbSizeHeader4->setBounds (680, 24, 80, 30);
    donateBtn->setBounds (368, 136, 128, 48);
    bypassBtn->setBounds (40, 88, 80, 24);
    label->setBounds (65, 33, 24, 24);
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
    else if (sliderThatWasMoved == delayTimeSlider2)
    {
        //[UserSliderCode_delayTimeSlider2] -- add your slider handling code here..
        //[/UserSliderCode_delayTimeSlider2]
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
    else if (buttonThatWasClicked == dry)
    {
        //[UserButtonCode_dry] -- add your button handler code here..
        //[/UserButtonCode_dry]
    }
    else if (buttonThatWasClicked == donateBtn)
    {
        //[UserButtonCode_donateBtn] -- add your button handler code here..
        //[/UserButtonCode_donateBtn]
    }
    else if (buttonThatWasClicked == bypassBtn)
    {
        //[UserButtonCode_bypassBtn] -- add your button handler code here..
		getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::bypassParam, (float)(bypassBtn->getToggleState() == true)?1.0f:0.0f);
        //[/UserButtonCode_bypassBtn]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void JuceDemoPluginAudioProcessorEditor::mouseEnter (const MouseEvent& e)
{
    //[UserCode_mouseEnter] -- Add your code here...
    //[/UserCode_mouseEnter]
}

void JuceDemoPluginAudioProcessorEditor::mouseExit (const MouseEvent& e)
{
    //[UserCode_mouseExit] -- Add your code here...
	DBG(e.getPosition().toString());
    //[/UserCode_mouseExit]
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
                 initialWidth="400" initialHeight="200">
  <METHODS>
    <METHOD name="mouseEnter (const MouseEvent&amp; e)"/>
    <METHOD name="mouseExit (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ff777777">
    <IMAGE pos="4 4 1920 1040" resource="uibg_png" opacity="1" mode="0"/>
  </BACKGROUND>
  <GROUPCOMPONENT name="new group" id="7c8c0a2a1419927a" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="8 8 144 112" title="output"/>
  <GROUPCOMPONENT name="new group" id="fb7419eb67152218" memberName="reverGroupComponent"
                  virtualName="" explicitFocusOrder="0" pos="456 13 408 100" title="reverb"/>
  <GROUPCOMPONENT name="new group" id="98be51d9c59fac6f" memberName="delayGroupComponent"
                  virtualName="" explicitFocusOrder="0" pos="208 13 240 100" title="delay"
                  textpos="33"/>
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
          virtualName="" explicitFocusOrder="0" pos="73 24 80 50" tooltip="gain"
          min="0" max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.29999999999999999"/>
  <SLIDER name="delaySlider" id="37878e5e9fd60a08" memberName="delaySlider"
          virtualName="" explicitFocusOrder="0" pos="208 47 80 50" tooltip="delay gain&#10;"
          trackcol="ffffffff" textboxhighlight="ff1111ee" textboxoutline="ff808080"
          min="0" max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="gainInfoLabel" id="dde6ff72637f37e7" memberName="gainInfoLabel"
         virtualName="" explicitFocusOrder="0" pos="73 72 80 20" textCol="ff323232"
         edTextCol="ff000000" edBkgCol="0" labelText="0.0 dB&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="64ddab567eb77e3c" memberName="panInfoLabel"
         virtualName="" explicitFocusOrder="0" pos="100 209 80 20" textCol="ff282828"
         edTextCol="ff000000" edBkgCol="0" labelText="C" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="ead45d255e5f5831" memberName="delayTimeSlider"
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
          virtualName="" explicitFocusOrder="0" pos="20 154 80 50" min="0"
          max="1" int="0.0050000000000000001" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="fcf994bed06bf6ab" memberName="midsideHeader"
         virtualName="" explicitFocusOrder="0" pos="10 134 80 20" textCol="ff363636"
         edTextCol="ff000000" edBkgCol="0" labelText="mid/side" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="mid/side slider" id="2a577f0fc0372cc6" memberName="saturationSlider"
          virtualName="" explicitFocusOrder="0" pos="120 309 100 50" min="0.001"
          max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="saturation fx" id="eda4710f044030be" memberName="distortionHeader"
         virtualName="" explicitFocusOrder="0" pos="132 296 80 10" textCol="ff363636"
         edTextCol="ff000000" edBkgCol="0" labelText="saturation" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="12"/>
  <LABEL name="new label" id="f53c45ed3e69f449" memberName="hpfHeader"
         virtualName="" explicitFocusOrder="0" pos="258 150 80 30" textCol="ff363636"
         edTextCol="ff000000" edBkgCol="0" labelText="hi pass filter"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Aharoni" fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="hi pass filter" id="253b421224cbac37" memberName="hpfSlider"
          virtualName="" explicitFocusOrder="0" pos="268 170 60 50" tooltip="hi pass filter (hz)"
          min="20" max="10000" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.20000000000000001"/>
  <SLIDER name="new slider" id="81b8a5f3e2f90d2e" memberName="reverbSizeSlider"
          virtualName="" explicitFocusOrder="0" pos="472 48 50 50" min="0.01"
          max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="63580ead55c45fe" memberName="midsideInfoLabel"
         virtualName="" explicitFocusOrder="0" pos="10 209 80 30" textCol="ff363636"
         edTextCol="ff000000" edBkgCol="0" labelText="80%" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="9e5a6f98ed1157ee" memberName="reverbSizeHeader"
         virtualName="" explicitFocusOrder="0" pos="456 24 80 30" textCol="ff363636"
         edTextCol="ff000000" edBkgCol="0" labelText="room size" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="f86ed4bd47474957" memberName="delayTimeSlider2"
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
  <TOGGLEBUTTON name="new toggle button" id="9fec732da680abce" memberName="dry"
                virtualName="" explicitFocusOrder="0" pos="24 32 48 24" buttonText="dry"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="1"/>
  <SLIDER name="new slider" id="64dc86b4ed912be" memberName="slider" virtualName=""
          explicitFocusOrder="0" pos="536 48 50 50" min="0" max="10" int="0"
          style="RotaryVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="cf93cb9c05f6ea83" memberName="reverbSizeHeader2"
         virtualName="" explicitFocusOrder="0" pos="520 24 80 30" textCol="ff363636"
         edTextCol="ff000000" edBkgCol="0" labelText="damp todo" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="19c54baf5cf03b32" memberName="slider2"
          virtualName="" explicitFocusOrder="0" pos="608 48 50 50" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="629d011e42cdcd54" memberName="reverbSizeHeader3"
         virtualName="" explicitFocusOrder="0" pos="600 24 80 30" textCol="ff363636"
         edTextCol="ff000000" edBkgCol="0" labelText="freeze todo" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="935f633b2a015b36" memberName="slider3"
          virtualName="" explicitFocusOrder="0" pos="688 48 50 50" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="7c566ba924521d30" memberName="reverbSizeHeader4"
         virtualName="" explicitFocusOrder="0" pos="680 24 80 30" textCol="ff363636"
         edTextCol="ff000000" edBkgCol="0" labelText="width todo" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <IMAGEBUTTON name="new button" id="d21f807ed0a4cb1b" memberName="donateBtn"
               virtualName="" explicitFocusOrder="0" pos="368 136 128 48" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="images1_jpg" opacityNormal="1" colourNormal="0"
               resourceOver="" opacityOver="1" colourOver="0" resourceDown=""
               opacityDown="1" colourDown="0"/>
  <TOGGLEBUTTON name="new toggle button" id="4ce3978395a4d72f" memberName="bypassBtn"
                virtualName="" explicitFocusOrder="0" pos="40 88 80 24" buttonText="bypass"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="new label" id="66302a18014fd815" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="65 33 24 24" edTextCol="ff000000"
         edBkgCol="0" labelText="+" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
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

// JUCER_RESOURCE: uibg_png, 42225, "../uibg.png"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_uibg_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,7,128,0,0,4,16,8,2,0,0,0,140,78,209,79,0,0,0,4,103,65,77,65,0,0,
175,200,55,5,138,233,0,0,0,25,116,69,88,116,83,111,102,116,119,97,114,101,0,65,100,111,98,101,32,73,109,97,103,101,82,101,97,100,121,113,201,101,60,0,0,164,131,73,68,65,84,120,218,236,221,93,106,28,177,
18,6,208,150,212,51,123,114,24,24,19,200,134,194,53,225,26,194,197,219,118,119,171,174,126,38,11,208,251,209,131,236,41,157,222,64,81,124,149,254,243,223,255,69,68,74,105,219,182,26,181,253,189,149,91,
109,165,45,162,214,118,167,173,61,37,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,229,249,254,171,201,134,114,202,13,157,231,89,251,107,205,41,149,82,218,151,205,221,203,157,97,24,134,97,
24,134,97,24,134,97,24,134,97,24,134,97,150,76,121,123,60,83,71,237,199,214,96,201,121,52,172,95,87,255,54,165,218,219,216,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,96,246,136,122,93,181,
143,75,111,91,47,228,92,82,58,175,115,47,123,171,28,215,17,209,234,153,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,121,60,127,206,132,142,173,103,115,108,179,57,125,43,183,230,174,184,
26,205,163,81,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,107,230,227,243,171,55,168,183,186,205,51,191,169,215,200,238,72,227,195,246,95,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,
97,152,37,179,247,96,142,158,20,221,83,162,219,153,219,9,219,213,112,238,201,29,253,181,55,170,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,204,222,116,68,212,24,103,139,86,189,223,110,
99,118,58,242,72,138,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,85,147,126,255,249,155,231,118,194,158,216,49,55,21,230,227,252,222,203,94,163,126,31,71,31,157,238,221,106,134,97,24,134,
97,24,134,97,24,134,97,24,134,97,24,134,89,49,31,159,95,237,49,182,136,90,183,151,76,175,198,245,43,200,35,141,29,134,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,96,202,143,199,179,214,153,
18,157,106,175,198,158,247,241,107,184,45,230,28,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,242,124,255,181,141,173,132,121,100,69,159,231,89,123,195,186,230,148,74,233,75,12,155,
187,151,59,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,242,246,120,206,201,232,232,123,9,103,78,199,24,142,158,19,210,35,39,186,125,198,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,
48,75,102,143,168,215,85,183,17,205,209,11,57,151,148,206,235,220,75,31,150,62,174,35,162,213,51,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,242,120,254,236,81,29,81,71,42,199,54,155,
211,183,114,107,238,138,171,209,60,26,213,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,102,62,62,191,102,90,244,12,141,158,243,209,181,94,35,187,35,253,91,86,88,24,134,97,24,134,97,24,134,
97,24,134,97,24,134,97,24,102,201,236,61,152,163,39,69,247,148,232,118,218,21,91,191,26,206,61,185,163,191,246,70,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,217,155,142,136,26,227,
108,209,170,247,219,109,204,78,71,30,73,209,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,106,210,239,63,127,243,220,78,216,19,59,230,166,194,124,156,223,123,217,107,212,239,227,232,163,211,
189,91,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,43,230,227,243,171,61,198,22,81,235,246,146,233,213,184,126,5,121,164,177,195,144,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,22,
76,249,241,120,214,58,83,162,83,237,213,216,243,62,126,13,183,197,156,163,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,83,158,239,191,182,177,149,48,143,172,232,243,60,107,111,88,215,156,
82,41,125,137,97,115,247,114,103,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,83,222,30,207,57,25,29,125,47,225,204,233,24,195,209,115,66,122,228,68,183,207,24,134,97,24,134,97,24,134,97,24,
134,97,24,134,97,24,102,201,236,17,245,186,234,54,162,57,122,33,231,146,210,121,157,123,233,195,210,199,117,68,180,122,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,83,30,207,159,61,170,
35,234,72,229,216,102,115,250,86,110,205,93,113,53,154,71,163,154,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,214,204,199,231,215,76,139,158,161,209,115,62,186,214,107,100,119,164,127,203,10,
11,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,189,7,115,244,164,232,158,18,221,78,187,98,235,87,195,185,39,119,244,215,222,168,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,
37,51,123,211,17,81,99,156,45,90,245,126,187,141,217,233,200,35,41,154,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,86,77,250,253,231,111,158,219,9,123,98,199,220,84,152,143,243,123,47,123,141,
250,125,28,125,116,186,119,171,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,197,124,124,126,181,199,216,34,106,221,94,50,189,26,215,175,32,143,52,118,24,50,12,195,48,12,195,48,12,195,48,12,
195,48,12,195,48,204,130,41,63,30,207,90,103,74,116,170,189,26,123,222,199,175,225,182,152,115,212,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,202,243,253,215,54,182,18,230,145,21,125,
158,103,237,13,235,154,83,42,165,47,49,108,238,94,238,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,202,219,227,57,39,163,163,239,37,156,57,29,99,56,122,78,72,143,156,232,246,25,195,48,
12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,61,162,94,87,221,70,52,71,47,228,92,82,58,175,115,47,125,88,250,184,142,136,86,207,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,202,
227,249,179,71,117,68,29,169,28,219,108,78,223,202,173,185,43,174,70,243,104,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,154,249,248,252,154,105,209,51,52,122,206,71,215,122,141,236,142,
244,111,89,97,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,179,247,96,142,158,20,221,83,162,219,105,87,108,253,106,56,247,228,142,254,218,27,213,12,195,48,12,195,48,12,195,48,12,195,48,
12,195,48,12,179,100,102,111,58,34,106,140,179,69,171,222,111,183,49,59,29,121,36,69,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,170,73,191,255,252,205,115,59,97,79,236,152,155,10,243,113,
126,239,101,175,81,191,143,163,143,78,247,110,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,172,152,143,207,175,246,24,91,68,173,219,75,166,87,227,250,21,228,145,198,14,67,134,97,24,134,97,
24,134,97,24,134,97,24,134,97,24,134,89,48,229,199,227,89,235,76,137,78,181,87,99,207,251,248,53,220,22,115,142,154,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,121,190,255,218,198,86,194,
60,178,162,207,243,172,189,97,93,115,74,165,244,37,134,205,221,203,157,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,121,123,60,231,100,116,244,189,132,51,167,99,12,71,207,9,233,145,19,221,
62,99,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,179,71,212,235,170,219,136,230,232,133,156,75,74,231,117,238,165,15,75,31,215,17,209,234,153,97,24,134,97,24,134,97,24,134,97,24,134,97,24,
134,97,150,76,121,60,127,246,168,142,168,35,149,99,155,205,233,91,185,53,119,197,213,104,30,141,106,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,51,31,159,95,51,45,122,134,70,207,249,232,90,
175,145,221,145,254,45,43,44,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,246,30,204,209,147,162,123,74,116,59,237,138,173,95,13,231,158,220,209,95,123,163,154,97,24,134,97,24,134,97,24,
134,97,24,134,97,24,134,97,150,204,236,77,71,68,141,113,182,104,213,251,237,54,102,167,35,143,164,104,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,53,233,247,159,191,121,110,39,236,137,29,
115,83,97,62,206,239,189,236,53,234,247,113,244,209,233,222,173,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,21,243,241,249,213,30,99,139,168,117,123,201,244,106,92,191,130,60,210,216,97,
200,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,11,166,252,120,60,107,157,41,209,169,246,106,236,121,31,191,134,219,98,206,81,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,207,
247,95,219,216,74,152,71,86,244,121,158,181,55,172,107,78,169,148,190,196,176,185,123,185,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,111,143,231,156,140,142,190,151,112,230,116,140,
225,232,57,33,61,114,162,219,103,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,246,136,122,93,117,27,209,28,189,144,115,73,233,188,206,189,244,97,233,227,58,34,90,61,51,12,195,48,12,195,
48,12,195,48,12,195,48,12,195,48,204,146,41,143,231,207,30,213,17,117,164,114,108,179,57,125,43,183,230,174,184,26,205,163,81,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,107,230,227,243,107,
166,69,207,208,232,57,31,93,235,53,178,59,210,191,101,133,133,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,222,131,57,122,82,116,79,137,110,167,93,177,245,171,225,220,147,59,250,107,111,
84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,153,189,233,136,168,49,206,22,173,122,191,221,198,236,116,228,145,20,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,171,38,253,
254,243,55,207,237,132,61,177,99,110,42,204,199,249,189,151,189,70,253,62,142,62,58,221,187,213,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,98,62,62,191,218,99,108,17,181,110,47,153,94,141,
235,87,144,71,26,59,12,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,193,148,31,143,103,173,51,37,58,213,94,141,61,239,227,215,112,91,204,57,106,134,97,24,134,97,24,134,97,24,134,97,24,134,
97,24,134,89,50,229,249,254,107,27,91,9,243,200,138,62,207,179,246,134,117,205,41,149,210,151,24,54,119,47,119,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,229,237,241,156,147,209,209,247,
18,206,156,142,49,28,61,39,164,71,78,116,251,140,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,30,81,175,171,110,35,154,163,23,114,46,41,157,215,185,151,62,44,125,92,71,68,171,103,134,97,
24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,229,241,252,217,163,58,162,142,84,142,109,54,167,111,229,214,220,21,87,163,121,52,170,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,205,
124,124,126,205,180,232,25,26,61,231,163,107,189,70,118,71,250,183,172,176,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,217,123,48,71,79,138,238,41,209,237,180,43,182,126,53,156,123,114,
71,127,237,141,106,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,179,55,29,17,53,198,217,162,85,239,183,219,152,157,142,60,146,162,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,
213,164,223,127,254,230,185,157,176,39,118,204,77,133,249,56,191,247,178,215,168,223,199,209,71,167,123,183,154,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,86,204,199,231,87,123,140,45,162,214,
237,37,211,171,113,253,10,242,72,99,135,33,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,152,242,227,241,172,117,166,68,167,218,171,177,231,125,252,26,110,139,57,71,205,48,12,195,48,12,195,
48,12,195,48,12,195,48,12,195,48,75,166,60,223,127,109,99,43,97,30,89,209,231,121,214,222,176,174,57,165,82,250,18,195,230,238,229,206,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,166,188,61,
158,115,50,58,250,94,194,153,211,49,134,163,231,132,244,200,137,110,159,49,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,217,35,234,117,213,109,68,115,244,66,206,37,165,243,58,247,210,135,
165,143,235,136,104,245,204,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,166,60,158,63,123,84,71,212,145,202,177,205,230,244,173,220,154,187,226,106,52,143,70,53,195,48,12,195,48,12,195,48,
12,195,48,12,195,48,12,195,172,153,143,207,175,153,22,61,67,163,231,124,116,173,215,200,238,72,255,150,21,22,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,123,15,230,232,73,209,61,37,186,
157,118,197,214,175,134,115,79,238,232,175,189,81,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,246,166,35,162,198,56,91,180,234,253,118,27,179,211,145,71,82,52,195,48,12,195,48,12,195,
48,12,195,48,12,195,48,12,195,172,154,244,251,207,223,60,183,19,246,196,142,185,169,48,31,231,247,94,246,26,245,251,56,250,232,116,239,86,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,138,249,
248,252,106,143,177,69,212,186,189,100,122,53,174,95,65,30,105,236,48,100,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,5,83,126,60,158,181,206,148,232,84,123,53,246,188,143,95,195,109,49,231,
168,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,148,231,251,175,109,108,37,204,35,43,250,60,207,218,27,214,53,167,84,74,95,98,216,220,189,220,25,134,97,24,134,97,24,134,97,24,134,97,24,
134,97,24,102,201,148,183,199,115,78,70,71,223,75,56,115,58,198,112,244,156,144,30,57,209,237,51,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,123,68,189,174,186,141,104,142,94,200,185,164,
116,94,231,94,250,176,244,113,29,17,173,158,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,148,199,243,103,143,234,136,58,82,57,182,217,156,190,149,91,115,87,92,141,230,209,168,102,24,134,
97,24,134,97,24,134,97,24,134,97,24,134,97,152,53,243,241,249,53,211,162,103,104,244,156,143,174,245,26,217,29,233,223,178,194,194,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,239,193,28,
61,41,186,167,68,183,211,174,216,250,213,112,238,201,29,253,181,55,170,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,204,222,116,68,212,24,103,139,86,189,223,110,99,118,58,242,72,138,102,
24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,85,147,126,255,249,155,231,118,194,158,216,49,55,21,230,227,252,222,203,94,163,126,31,71,31,157,238,221,106,134,97,24,134,97,24,134,97,24,134,97,24,
134,97,24,134,89,49,31,159,95,237,49,182,136,90,183,151,76,175,198,245,43,200,35,141,29,134,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,96,202,143,199,179,214,153,18,157,106,175,198,158,247,
241,107,184,45,230,28,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,242,124,255,181,141,173,132,121,100,69,159,231,89,123,195,186,230,148,74,233,75,12,155,187,151,59,195,48,12,195,48,
12,195,48,12,195,48,12,195,48,12,195,44,153,242,246,120,206,201,232,232,123,9,103,78,199,24,142,158,19,210,35,39,186,125,198,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,143,168,215,85,
183,17,205,209,11,57,151,148,206,235,220,75,31,150,62,174,35,162,213,51,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,242,120,254,236,81,29,81,71,42,199,54,155,211,183,114,107,238,138,171,
209,60,26,213,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,102,62,62,191,102,90,244,12,141,158,243,209,181,94,35,187,35,253,91,86,88,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,
201,236,61,152,163,39,69,247,148,232,118,218,21,91,191,26,206,61,185,163,191,246,70,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,217,155,142,136,26,227,108,209,170,247,219,109,204,78,
71,30,73,209,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,106,210,239,63,127,243,220,78,216,19,59,230,166,194,124,156,223,123,217,107,212,239,227,232,163,211,189,91,205,48,12,195,48,12,195,
48,12,195,48,12,195,48,12,195,48,43,230,227,243,171,61,198,22,81,235,246,146,233,213,184,126,5,121,164,177,195,144,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,22,76,249,241,120,214,58,83,162,
83,237,213,216,243,62,126,13,183,197,156,163,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,83,158,239,191,182,177,149,48,143,172,232,243,60,107,111,88,215,156,82,41,125,137,97,115,247,114,
103,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,83,222,30,207,57,25,29,125,47,225,204,233,24,195,209,115,66,122,228,68,183,207,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,
236,17,245,186,234,54,162,57,122,33,231,146,210,121,157,123,233,195,210,199,117,68,180,122,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,83,30,207,159,61,170,35,234,72,229,216,102,115,250,
86,110,205,93,113,53,154,71,163,154,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,214,204,199,231,215,76,139,158,161,209,115,62,186,214,107,100,119,164,127,203,10,11,195,48,12,195,48,12,195,48,
12,195,48,12,195,48,12,195,44,153,189,7,115,244,164,232,158,18,221,78,187,98,235,87,195,185,39,119,244,215,222,168,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,51,123,211,17,81,99,156,
45,90,245,126,187,141,217,233,200,35,41,154,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,86,77,250,253,231,111,158,219,9,123,98,199,220,84,152,143,243,123,47,123,141,250,125,28,125,116,186,119,
171,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,197,124,124,126,181,199,216,34,106,221,94,50,189,26,215,175,32,143,52,118,24,50,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,130,41,
63,30,207,90,103,74,116,170,189,26,123,222,199,175,225,182,152,115,212,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,202,243,253,215,54,182,18,230,145,21,125,158,103,237,13,235,154,83,42,
165,47,49,108,238,94,238,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,202,219,227,57,39,163,163,239,37,156,57,29,99,56,122,78,72,143,156,232,246,25,195,48,12,195,48,12,195,48,12,195,48,
12,195,48,12,195,44,153,61,162,94,87,221,70,52,71,47,228,92,82,58,175,115,47,125,88,250,184,142,136,86,207,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,202,227,249,179,71,117,68,29,169,
28,219,108,78,223,202,173,185,43,174,70,243,104,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,154,249,248,252,154,105,209,51,52,122,206,71,215,122,141,236,142,244,111,89,97,97,24,134,97,
24,134,97,24,134,97,24,134,97,24,134,97,152,37,179,247,96,142,158,20,221,83,162,219,105,87,108,253,106,56,247,228,142,254,218,27,213,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,102,111,
58,34,106,140,179,69,171,222,111,183,49,59,29,121,36,69,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,170,73,191,255,252,205,115,59,97,79,236,152,155,10,243,113,126,239,101,175,81,191,143,163,
143,78,247,110,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,172,152,143,207,175,246,24,91,68,173,219,75,166,87,227,250,21,228,145,198,14,67,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,
134,89,48,229,199,227,89,235,76,137,78,181,87,99,207,251,248,53,220,22,115,142,154,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,121,190,255,218,198,86,194,60,178,162,207,243,172,189,97,
93,115,74,165,244,37,134,205,221,203,157,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,121,123,60,231,100,116,244,189,132,51,167,99,12,71,207,9,233,145,19,221,62,99,24,134,97,24,134,97,24,
134,97,24,134,97,24,134,97,152,37,179,71,212,235,170,219,136,230,232,133,156,75,74,231,117,238,165,15,75,31,215,17,209,234,153,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,121,60,127,246,
168,142,168,35,149,99,155,205,233,91,185,53,119,197,213,104,30,141,106,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,51,31,159,95,51,45,122,134,70,207,249,232,90,175,145,221,145,254,45,43,44,
12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,246,30,204,209,147,162,123,74,116,59,237,138,173,95,13,231,158,220,209,95,123,163,154,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,
150,204,236,77,71,68,141,113,182,104,213,251,237,54,102,167,35,143,164,104,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,53,233,247,159,191,121,110,39,236,137,29,115,83,97,62,206,239,189,236,
53,234,247,113,244,209,233,222,173,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,21,243,241,249,213,30,99,139,168,117,123,201,244,106,92,191,130,60,210,216,97,200,48,12,195,48,12,195,48,12,
195,48,12,195,48,12,195,48,11,166,252,120,60,107,157,41,209,169,246,106,236,121,31,191,134,219,98,206,81,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,207,247,95,219,216,74,152,71,86,
244,121,158,181,55,172,107,78,169,148,190,196,176,185,123,185,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,111,143,231,156,140,142,190,151,112,230,116,140,225,232,57,33,61,114,162,219,
103,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,246,136,122,93,117,27,209,28,189,144,115,73,233,188,206,189,244,97,233,227,58,34,90,61,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,
48,204,146,41,143,231,207,30,213,17,117,164,114,108,179,57,125,43,183,230,174,184,26,205,163,81,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,107,230,227,243,107,166,69,207,208,232,57,31,93,
235,53,178,59,210,191,101,133,133,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,222,131,57,122,82,116,79,137,110,167,93,177,245,171,225,220,147,59,250,107,111,84,51,12,195,48,12,195,48,
12,195,48,12,195,48,12,195,48,204,146,153,189,233,136,168,49,206,22,173,122,191,221,198,236,116,228,145,20,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,171,38,253,254,243,55,207,237,132,61,
177,99,110,42,204,199,249,189,151,189,70,253,62,142,62,58,221,187,213,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,98,62,62,191,218,99,108,17,181,110,47,153,94,141,235,87,144,71,26,59,12,25,
134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,193,148,31,143,103,173,51,37,58,213,94,141,61,239,227,215,112,91,204,57,106,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,229,249,254,
107,27,91,9,243,200,138,62,207,179,246,134,117,205,41,149,210,151,24,54,119,47,119,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,229,237,241,156,147,209,209,247,18,206,156,142,49,28,61,39,
164,71,78,116,251,140,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,30,81,175,171,110,35,154,163,23,114,46,41,157,215,185,151,62,44,125,92,71,68,171,103,134,97,24,134,97,24,134,97,24,134,
97,24,134,97,24,134,89,50,229,241,252,217,163,58,162,142,84,142,109,54,167,111,229,214,220,21,87,163,121,52,170,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,205,124,124,126,205,180,232,25,
26,61,231,163,107,189,70,118,71,250,183,172,176,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,217,123,48,71,79,138,238,41,209,237,180,43,182,126,53,156,123,114,71,127,237,141,106,134,97,
24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,179,55,29,17,53,198,217,162,85,239,183,219,152,157,142,60,146,162,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,213,164,223,127,254,230,
185,157,176,39,118,204,77,133,249,56,191,247,178,215,168,223,199,209,71,167,123,183,154,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,86,204,199,231,87,123,140,45,162,214,237,37,211,171,113,253,
10,242,72,99,135,33,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,152,242,227,241,172,117,166,68,167,218,171,177,231,125,252,26,110,139,57,71,205,48,12,195,48,12,195,48,12,195,48,12,195,48,
12,195,48,75,166,60,223,127,109,99,43,97,30,89,209,231,121,214,222,176,174,57,165,82,250,18,195,230,238,229,206,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,166,188,61,158,115,50,58,250,94,
194,153,211,49,134,163,231,132,244,200,137,110,159,49,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,217,35,234,117,213,109,68,115,244,66,206,37,165,243,58,247,210,135,165,143,235,136,104,245,
204,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,166,60,158,63,123,84,71,212,145,202,177,205,230,244,173,220,154,187,226,106,52,143,70,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,
172,153,143,207,175,153,22,61,67,163,231,124,116,173,215,200,238,72,255,150,21,22,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,123,15,230,232,73,209,61,37,186,157,118,197,214,175,134,115,
79,238,232,175,189,81,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,246,166,35,162,198,56,91,180,234,253,118,27,179,211,145,71,82,52,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,
195,172,154,244,251,207,223,60,183,19,246,196,142,185,169,48,31,231,247,94,246,26,245,251,56,250,232,116,239,86,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,138,249,248,252,106,143,177,69,
212,186,189,100,122,53,174,95,65,30,105,236,48,100,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,5,83,126,60,158,181,206,148,232,84,123,53,246,188,143,95,195,109,49,231,168,25,134,97,24,134,97,
24,134,97,24,134,97,24,134,97,24,102,201,148,231,251,175,109,108,37,204,35,43,250,60,207,218,27,214,53,167,84,74,95,98,216,220,189,220,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,148,
183,199,115,78,70,71,223,75,56,115,58,198,112,244,156,144,30,57,209,237,51,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,123,68,189,174,186,141,104,142,94,200,185,164,116,94,231,94,250,176,
244,113,29,17,173,158,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,148,199,243,103,143,234,136,58,82,57,182,217,156,190,149,91,115,87,92,141,230,209,168,102,24,134,97,24,134,97,24,134,
97,24,134,97,24,134,97,152,53,243,241,249,53,211,162,103,104,244,156,143,174,245,26,217,29,233,223,178,194,194,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,239,193,28,61,41,186,167,68,183,
211,174,216,250,213,112,238,201,29,253,181,55,170,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,204,222,116,68,212,24,103,139,86,189,223,110,99,118,58,242,72,138,102,24,134,97,24,134,97,
24,134,97,24,134,97,24,134,97,152,85,147,126,255,249,155,231,118,194,158,216,49,55,21,230,227,252,222,203,94,163,126,31,71,31,157,238,221,106,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,49,
31,159,95,237,49,182,136,90,183,151,76,175,198,245,43,200,35,141,29,134,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,96,202,143,199,179,214,153,18,157,106,175,198,158,247,241,107,184,45,230,
28,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,242,124,255,181,141,173,132,121,100,69,159,231,89,123,195,186,230,148,74,233,75,12,155,187,151,59,195,48,12,195,48,12,195,48,12,195,48,
12,195,48,12,195,44,153,242,246,120,206,201,232,232,123,9,103,78,199,24,142,158,19,210,35,39,186,125,198,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,143,168,215,85,183,17,205,209,11,57,
151,148,206,235,220,75,31,150,62,174,35,162,213,51,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,242,120,254,236,81,29,81,71,42,199,54,155,211,183,114,107,238,138,171,209,60,26,213,12,195,
48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,102,62,62,191,102,90,244,12,141,158,243,209,181,94,35,187,35,253,91,86,88,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,236,61,152,163,
39,69,247,148,232,118,218,21,91,191,26,206,61,185,163,191,246,70,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,217,155,142,136,26,227,108,209,170,247,219,109,204,78,71,30,73,209,12,195,
48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,106,210,239,63,127,243,220,78,216,19,59,230,166,194,124,156,223,123,217,107,212,239,227,232,163,211,189,91,205,48,12,195,48,12,195,48,12,195,48,12,195,
48,12,195,48,43,230,227,243,171,61,198,22,81,235,246,146,233,213,184,126,5,121,164,177,195,144,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,22,76,249,241,120,214,58,83,162,83,237,213,216,243,62,
126,13,183,197,156,163,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,83,158,239,191,182,177,149,48,143,172,232,243,60,107,111,88,215,156,82,41,125,137,97,115,247,114,103,24,134,97,24,134,
97,24,134,97,24,134,97,24,134,97,152,37,83,222,30,207,57,25,29,125,47,225,204,233,24,195,209,115,66,122,228,68,183,207,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,236,17,245,186,234,54,
162,57,122,33,231,146,210,121,157,123,233,195,210,199,117,68,180,122,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,83,30,207,159,61,170,35,234,72,229,216,102,115,250,86,110,205,93,113,53,
154,71,163,154,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,214,204,199,231,215,76,139,158,161,209,115,62,186,214,107,100,119,164,127,203,10,11,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,
195,44,153,189,7,115,244,164,232,158,18,221,78,187,98,235,87,195,185,39,119,244,215,222,168,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,51,123,211,17,81,99,156,45,90,245,126,187,141,217,
233,200,35,41,154,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,86,77,250,253,231,111,158,219,9,123,98,199,220,84,152,143,243,123,47,123,141,250,125,28,125,116,186,119,171,25,134,97,24,134,97,24,
134,97,24,134,97,24,134,97,24,102,197,124,124,126,181,199,216,34,106,221,94,50,189,26,215,175,32,143,52,118,24,50,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,130,41,63,30,207,90,103,74,116,170,
189,26,123,222,199,175,225,182,152,115,212,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,202,243,253,215,54,182,18,230,145,21,125,158,103,237,13,235,154,83,42,165,47,49,108,238,94,238,12,
195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,202,219,227,57,39,163,163,239,37,156,57,29,99,56,122,78,72,143,156,232,246,25,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,61,
162,94,87,221,70,52,71,47,228,92,82,58,175,115,47,125,88,250,184,142,136,86,207,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,202,227,249,179,71,117,68,29,169,28,219,108,78,223,202,173,
185,43,174,70,243,104,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,154,249,248,252,154,105,209,51,52,122,206,71,215,122,141,236,142,244,111,89,97,97,24,134,97,24,134,97,24,134,97,24,134,
97,24,134,97,152,37,179,247,96,142,158,20,221,83,162,219,105,87,108,253,106,56,247,228,142,254,218,27,213,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,102,111,58,34,106,140,179,69,171,
222,111,183,49,59,29,121,36,69,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,170,73,191,255,252,205,115,59,97,79,236,152,155,10,243,113,126,239,101,175,81,191,143,163,143,78,247,110,53,195,
48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,172,152,143,207,175,246,24,91,68,173,219,75,166,87,227,250,21,228,145,198,14,67,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,48,229,199,227,
89,235,76,137,78,181,87,99,207,251,248,53,220,22,115,142,154,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,121,190,255,218,198,86,194,60,178,162,207,243,172,189,97,93,115,74,165,244,37,134,
205,221,203,157,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,121,123,60,231,100,116,244,189,132,51,167,99,12,71,207,9,233,145,19,221,62,99,24,134,97,24,134,97,24,134,97,24,134,97,24,134,
97,152,37,179,71,212,235,170,219,136,230,232,133,156,75,74,231,117,238,165,15,75,31,215,17,209,234,153,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,121,60,127,246,168,142,168,35,149,99,
155,205,233,91,185,53,119,197,213,104,30,141,106,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,51,31,159,95,51,45,122,134,70,207,249,232,90,175,145,221,145,254,45,43,44,12,195,48,12,195,48,
12,195,48,12,195,48,12,195,48,12,179,100,246,30,204,209,147,162,123,74,116,59,237,138,173,95,13,231,158,220,209,95,123,163,154,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,236,77,71,68,
141,113,182,104,213,251,237,54,102,167,35,143,164,104,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,53,233,247,159,191,121,110,39,236,137,29,115,83,97,62,206,239,189,236,53,234,247,113,244,
209,233,222,173,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,21,243,241,249,213,30,99,139,168,117,123,201,244,106,92,191,130,60,210,216,97,200,48,12,195,48,12,195,48,12,195,48,12,195,48,12,
195,48,11,166,252,120,60,107,157,41,209,169,246,106,236,121,31,191,134,219,98,206,81,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,207,247,95,219,216,74,152,71,86,244,121,158,181,55,
172,107,78,169,148,190,196,176,185,123,185,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,111,143,231,156,140,142,190,151,112,230,116,140,225,232,57,33,61,114,162,219,103,12,195,48,12,
195,48,12,195,48,12,195,48,12,195,48,12,179,100,246,136,122,93,117,27,209,28,189,144,115,73,233,188,206,189,244,97,233,227,58,34,90,61,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,143,
231,207,30,213,17,117,164,114,108,179,57,125,43,183,230,174,184,26,205,163,81,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,107,230,227,243,107,166,69,207,208,232,57,31,93,235,53,178,59,210,
191,101,133,133,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,222,131,57,122,82,116,79,137,110,167,93,177,245,171,225,220,147,59,250,107,111,84,51,12,195,48,12,195,48,12,195,48,12,195,48,
12,195,48,204,146,153,189,233,136,168,49,206,22,173,122,191,221,198,236,116,228,145,20,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,171,38,253,254,243,55,207,237,132,61,177,99,110,42,204,199,
249,189,151,189,70,253,62,142,62,58,221,187,213,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,98,62,62,191,218,99,108,17,181,110,47,153,94,141,235,87,144,71,26,59,12,25,134,97,24,134,97,24,
134,97,24,134,97,24,134,97,24,102,193,148,31,143,103,173,51,37,58,213,94,141,61,239,227,215,112,91,204,57,106,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,229,249,254,107,27,91,9,243,200,
138,62,207,179,246,134,117,205,41,149,210,151,24,54,119,47,119,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,229,237,241,156,147,209,209,247,18,206,156,142,49,28,61,39,164,71,78,116,251,
140,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,30,81,175,171,110,35,154,163,23,114,46,41,157,215,185,151,62,44,125,92,71,68,171,103,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,
134,89,50,229,241,252,217,163,58,162,142,84,142,109,54,167,111,229,214,220,21,87,163,121,52,170,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,205,124,124,126,205,180,232,25,26,61,231,163,107,
189,70,118,71,250,183,172,176,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,217,123,48,71,79,138,238,41,209,237,180,43,182,126,53,156,123,114,71,127,237,141,106,134,97,24,134,97,24,134,
97,24,134,97,24,134,97,24,134,89,50,179,55,29,17,53,198,217,162,85,239,183,219,152,157,142,60,146,162,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,213,164,223,127,254,230,185,157,176,39,118,
204,77,133,249,56,191,247,178,215,168,223,199,209,71,167,123,183,154,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,86,204,199,231,87,123,140,45,162,214,237,37,211,171,113,253,10,242,72,99,135,33,
195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,152,242,227,241,172,117,166,68,167,218,171,177,231,125,252,26,110,139,57,71,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,166,60,
223,127,109,99,43,97,30,89,209,231,121,214,222,176,174,57,165,82,250,18,195,230,238,229,206,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,166,188,61,158,115,50,58,250,94,194,153,211,49,134,163,
231,132,244,200,137,110,159,49,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,217,35,234,117,213,109,68,115,244,66,206,37,165,243,58,247,210,135,165,143,235,136,104,245,204,48,12,195,48,12,
195,48,12,195,48,12,195,48,12,195,48,75,166,60,158,63,123,84,71,212,145,202,177,205,230,244,173,220,154,187,226,106,52,143,70,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,172,153,143,207,175,
153,22,61,67,163,231,124,116,173,215,200,238,72,255,150,21,22,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,123,15,230,232,73,209,61,37,186,157,118,197,214,175,134,115,79,238,232,175,189,
81,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,246,166,35,162,198,56,91,180,234,253,118,27,179,211,145,71,82,52,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,172,154,244,251,
207,223,60,183,19,246,196,142,185,169,48,31,231,247,94,246,26,245,251,56,250,232,116,239,86,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,138,249,248,252,106,143,177,69,212,186,189,100,122,
53,174,95,65,30,105,236,48,100,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,5,83,126,60,158,181,206,148,232,84,123,53,246,188,143,95,195,109,49,231,168,25,134,97,24,134,97,24,134,97,24,134,97,
24,134,97,24,102,201,148,231,251,175,109,108,37,204,35,43,250,60,207,218,27,214,53,167,84,74,95,98,216,220,189,220,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,148,183,199,115,78,70,71,
223,75,56,115,58,198,112,244,156,144,30,57,209,237,51,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,123,68,189,174,186,141,104,142,94,200,185,164,116,94,231,94,250,176,244,113,29,17,173,
158,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,148,199,243,103,143,234,136,58,82,57,182,217,156,190,149,91,115,87,92,141,230,209,168,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,
97,152,53,243,241,249,53,211,162,103,104,244,156,143,174,245,26,217,29,233,223,178,194,194,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,239,193,28,61,41,186,167,68,183,211,174,216,250,213,
112,238,201,29,253,181,55,170,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,204,222,116,68,212,24,103,139,86,189,223,110,99,118,58,242,72,138,102,24,134,97,24,134,97,24,134,97,24,134,97,
24,134,97,152,85,147,126,255,249,155,231,118,194,158,216,49,55,21,230,227,252,222,203,94,163,126,31,71,31,157,238,221,106,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,49,31,159,95,237,49,182,
136,90,183,151,76,175,198,245,43,200,35,141,29,134,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,96,202,143,199,179,214,153,18,157,106,175,198,158,247,241,107,184,45,230,28,53,195,48,12,195,
48,12,195,48,12,195,48,12,195,48,12,195,44,153,242,124,255,181,141,173,132,121,100,69,159,231,89,123,195,186,230,148,74,233,75,12,155,187,151,59,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,
153,242,246,120,206,201,232,232,123,9,103,78,199,24,142,158,19,210,35,39,186,125,198,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,143,168,215,85,183,17,205,209,11,57,151,148,206,235,220,
75,31,150,62,174,35,162,213,51,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,242,120,254,236,81,29,81,71,42,199,54,155,211,183,114,107,238,138,171,209,60,26,213,12,195,48,12,195,48,12,195,
48,12,195,48,12,195,48,12,179,102,62,62,191,102,90,244,12,141,158,243,209,181,94,35,187,35,253,91,86,88,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,236,61,152,163,39,69,247,148,232,118,
218,21,91,191,26,206,61,185,163,191,246,70,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,217,155,142,136,26,227,108,209,170,247,219,109,204,78,71,30,73,209,12,195,48,12,195,48,12,195,
48,12,195,48,12,195,48,12,179,106,210,239,63,127,243,220,78,216,19,59,230,166,194,124,156,223,123,217,107,212,239,227,232,163,211,189,91,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,43,230,
227,243,171,61,198,22,81,235,246,146,233,213,184,126,5,121,164,177,195,144,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,22,76,249,241,120,214,58,83,162,83,237,213,216,243,62,126,13,183,197,156,
163,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,83,158,239,191,182,177,149,48,143,172,232,243,60,107,111,88,215,156,82,41,125,137,97,115,247,114,103,24,134,97,24,134,97,24,134,97,24,134,
97,24,134,97,152,37,83,222,30,207,57,25,29,125,47,225,204,233,24,195,209,115,66,122,228,68,183,207,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,236,17,245,186,234,54,162,57,122,33,231,
146,210,121,157,123,233,195,210,199,117,68,180,122,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,83,30,207,159,61,170,35,234,72,229,216,102,115,250,86,110,205,93,113,53,154,71,163,154,97,
24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,214,204,199,231,215,76,139,158,161,209,115,62,186,214,107,100,119,164,127,203,10,11,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,189,7,
115,244,164,232,158,18,221,78,187,98,235,87,195,185,39,119,244,215,222,168,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,51,123,211,17,81,99,156,45,90,245,126,187,141,217,233,200,35,41,
154,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,86,77,250,253,231,111,158,219,9,123,98,199,220,84,152,143,243,123,47,123,141,250,125,28,125,116,186,119,171,25,134,97,24,134,97,24,134,97,24,134,
97,24,134,97,24,102,197,124,124,126,181,199,216,34,106,221,94,50,189,26,215,175,32,143,52,118,24,50,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,130,41,63,30,207,90,103,74,116,170,189,26,123,
222,199,175,225,182,152,115,212,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,202,243,253,215,54,182,18,230,145,21,125,158,103,237,13,235,154,83,42,165,47,49,108,238,94,238,12,195,48,12,
195,48,12,195,48,12,195,48,12,195,48,12,179,100,202,219,227,57,39,163,163,239,37,156,57,29,99,56,122,78,72,143,156,232,246,25,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,61,162,94,87,
221,70,52,71,47,228,92,82,58,175,115,47,125,88,250,184,142,136,86,207,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,202,227,249,179,71,117,68,29,169,28,219,108,78,223,202,173,185,43,174,
70,243,104,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,154,249,248,252,154,105,209,51,52,122,206,71,215,122,141,236,142,244,111,89,97,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,
97,152,37,179,247,96,142,158,20,221,83,162,219,105,87,108,253,106,56,247,228,142,254,218,27,213,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,102,111,58,34,106,140,179,69,171,222,111,183,
49,59,29,121,36,69,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,170,73,191,255,252,205,115,59,97,79,236,152,155,10,243,113,126,239,101,175,81,191,143,163,143,78,247,110,53,195,48,12,195,48,
12,195,48,12,195,48,12,195,48,12,195,172,152,143,207,175,246,24,91,68,173,219,75,166,87,227,250,21,228,145,198,14,67,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,48,229,199,227,89,235,76,137,
78,181,87,99,207,251,248,53,220,22,115,142,154,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,121,190,255,218,198,86,194,60,178,162,207,243,172,189,97,93,115,74,165,244,37,134,205,221,203,
157,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,121,123,60,231,100,116,244,189,132,51,167,99,12,71,207,9,233,145,19,221,62,99,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,179,
71,212,235,170,219,136,230,232,133,156,75,74,231,117,238,165,15,75,31,215,17,209,234,153,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,121,60,127,246,168,142,168,35,149,99,155,205,233,91,
185,53,119,197,213,104,30,141,106,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,51,31,159,95,51,45,122,134,70,207,249,232,90,175,145,221,145,254,45,43,44,12,195,48,12,195,48,12,195,48,12,195,
48,12,195,48,12,179,100,246,30,204,209,147,162,123,74,116,59,237,138,173,95,13,231,158,220,209,95,123,163,154,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,236,77,71,68,141,113,182,104,
213,251,237,54,102,167,35,143,164,104,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,53,233,247,159,191,121,110,39,236,137,29,115,83,97,62,206,239,189,236,53,234,247,113,244,209,233,222,173,
102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,21,243,241,249,213,30,99,139,168,117,123,201,244,106,92,191,130,60,210,216,97,200,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,11,166,
252,120,60,107,157,41,209,169,246,106,236,121,31,191,134,219,98,206,81,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,207,247,95,219,216,74,152,71,86,244,121,158,181,55,172,107,78,169,
148,190,196,176,185,123,185,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,111,143,231,156,140,142,190,151,112,230,116,140,225,232,57,33,61,114,162,219,103,12,195,48,12,195,48,12,195,
48,12,195,48,12,195,48,12,179,100,246,136,122,93,117,27,209,28,189,144,115,73,233,188,206,189,244,97,233,227,58,34,90,61,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,143,231,207,30,
213,17,117,164,114,108,179,57,125,43,183,230,174,184,26,205,163,81,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,107,230,227,243,107,166,69,207,208,232,57,31,93,235,53,178,59,210,191,101,133,
133,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,222,131,57,122,82,116,79,137,110,167,93,177,245,171,225,220,147,59,250,107,111,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,
204,146,153,189,233,136,168,49,206,22,173,122,191,221,198,236,116,228,145,20,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,171,38,253,254,243,55,207,237,132,61,177,99,110,42,204,199,249,189,
151,189,70,253,62,142,62,58,221,187,213,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,98,62,62,191,218,99,108,17,181,110,47,153,94,141,235,87,144,71,26,59,12,25,134,97,24,134,97,24,134,97,24,
134,97,24,134,97,24,102,193,148,31,143,103,173,51,37,58,213,94,141,61,239,227,215,112,91,204,57,106,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,229,249,254,107,27,91,9,243,200,138,62,207,
179,246,134,117,205,41,149,210,151,24,54,119,47,119,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,229,237,241,156,147,209,209,247,18,206,156,142,49,28,61,39,164,71,78,116,251,140,97,24,134,
97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,30,81,175,171,110,35,154,163,23,114,46,41,157,215,185,151,62,44,125,92,71,68,171,103,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,229,
241,252,217,163,58,162,142,84,142,109,54,167,111,229,214,220,21,87,163,121,52,170,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,205,124,124,126,205,180,232,25,26,61,231,163,107,189,70,118,71,
250,183,172,176,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,217,123,48,71,79,138,238,41,209,237,180,43,182,126,53,156,123,114,71,127,237,141,106,134,97,24,134,97,24,134,97,24,134,97,24,
134,97,24,134,89,50,179,55,29,17,53,198,217,162,85,239,183,219,152,157,142,60,146,162,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,213,164,223,127,254,230,185,157,176,39,118,204,77,133,249,
56,191,247,178,215,168,223,199,209,71,167,123,183,154,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,86,204,199,231,87,123,140,45,162,214,237,37,211,171,113,253,10,242,72,99,135,33,195,48,12,195,
48,12,195,48,12,195,48,12,195,48,12,195,44,152,242,227,241,172,117,166,68,167,218,171,177,231,125,252,26,110,139,57,71,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,166,60,223,127,109,99,
43,97,30,89,209,231,121,214,222,176,174,57,165,82,250,18,195,230,238,229,206,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,166,188,61,158,115,50,58,250,94,194,153,211,49,134,163,231,132,244,
200,137,110,159,49,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,217,35,234,117,213,109,68,115,244,66,206,37,165,243,58,247,210,135,165,143,235,136,104,245,204,48,12,195,48,12,195,48,12,195,
48,12,195,48,12,195,48,75,166,60,158,63,123,84,71,212,145,202,177,205,230,244,173,220,154,187,226,106,52,143,70,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,172,153,143,207,175,153,22,61,67,
163,231,124,116,173,215,200,238,72,255,150,21,22,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,123,15,230,232,73,209,61,37,186,157,118,197,214,175,134,115,79,238,232,175,189,81,205,48,12,
195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,246,166,35,162,198,56,91,180,234,253,118,27,179,211,145,71,82,52,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,172,154,244,251,207,223,60,
183,19,246,196,142,185,169,48,31,231,247,94,246,26,245,251,56,250,232,116,239,86,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,138,249,248,252,106,143,177,69,212,186,189,100,122,53,174,95,65,
30,105,236,48,100,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,5,83,126,60,158,181,206,148,232,84,123,53,246,188,143,95,195,109,49,231,168,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,
102,201,148,231,251,175,109,108,37,204,35,43,250,60,207,218,27,214,53,167,84,74,95,98,216,220,189,220,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,148,183,199,115,78,70,71,223,75,56,115,
58,198,112,244,156,144,30,57,209,237,51,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,123,68,189,174,186,141,104,142,94,200,185,164,116,94,231,94,250,176,244,113,29,17,173,158,25,134,97,
24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,148,199,243,103,143,234,136,58,82,57,182,217,156,190,149,91,115,87,92,141,230,209,168,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,53,243,
241,249,53,211,162,103,104,244,156,143,174,245,26,217,29,233,223,178,194,194,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,239,193,28,61,41,186,167,68,183,211,174,216,250,213,112,238,201,
29,253,181,55,170,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,204,222,116,68,212,24,103,139,86,189,223,110,99,118,58,242,72,138,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,
85,147,126,255,249,155,231,118,194,158,216,49,55,21,230,227,252,222,203,94,163,126,31,71,31,157,238,221,106,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,49,31,159,95,237,49,182,136,90,183,
151,76,175,198,245,43,200,35,141,29,134,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,96,202,143,199,179,214,153,18,157,106,175,198,158,247,241,107,184,45,230,28,53,195,48,12,195,48,12,195,
48,12,195,48,12,195,48,12,195,44,153,242,124,255,181,141,173,132,121,100,69,159,231,89,123,195,186,230,148,74,233,75,12,155,187,151,59,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,242,
246,120,206,201,232,232,123,9,103,78,199,24,142,158,19,210,35,39,186,125,198,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,143,168,215,85,183,17,205,209,11,57,151,148,206,235,220,75,31,150,
62,174,35,162,213,51,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,242,120,254,236,81,29,81,71,42,199,54,155,211,183,114,107,238,138,171,209,60,26,213,12,195,48,12,195,48,12,195,48,12,195,
48,12,195,48,12,179,102,62,62,191,102,90,244,12,141,158,243,209,181,94,35,187,35,253,91,86,88,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,236,61,152,163,39,69,247,148,232,118,218,21,91,
191,26,206,61,185,163,191,246,70,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,217,155,142,136,26,227,108,209,170,247,219,109,204,78,71,30,73,209,12,195,48,12,195,48,12,195,48,12,195,
48,12,195,48,12,179,106,210,239,63,127,243,220,78,216,19,59,230,166,194,124,156,223,123,217,107,212,239,227,232,163,211,189,91,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,43,230,227,243,171,
61,198,22,81,235,246,146,233,213,184,126,5,121,164,177,195,144,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,22,76,249,241,120,214,58,83,162,83,237,213,216,243,62,126,13,183,197,156,163,102,24,
134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,83,158,239,191,182,177,149,48,143,172,232,243,60,107,111,88,215,156,82,41,125,137,97,115,247,114,103,24,134,97,24,134,97,24,134,97,24,134,97,24,134,
97,152,37,83,222,30,207,57,25,29,125,47,225,204,233,24,195,209,115,66,122,228,68,183,207,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,236,17,245,186,234,54,162,57,122,33,231,146,210,121,
157,123,233,195,210,199,117,68,180,122,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,83,30,207,159,61,170,35,234,72,229,216,102,115,250,86,110,205,93,113,53,154,71,163,154,97,24,134,97,
24,134,97,24,134,97,24,134,97,24,134,97,214,204,199,231,215,76,139,158,161,209,115,62,186,214,107,100,119,164,127,203,10,11,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,189,7,115,244,164,
232,158,18,221,78,187,98,235,87,195,185,39,119,244,215,222,168,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,51,123,211,17,81,99,156,45,90,245,126,187,141,217,233,200,35,41,154,97,24,134,
97,24,134,97,24,134,97,24,134,97,24,134,97,86,77,250,253,231,111,158,219,9,123,98,199,220,84,152,143,243,123,47,123,141,250,125,28,125,116,186,119,171,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,
24,102,197,124,124,126,181,199,216,34,106,221,94,50,189,26,215,175,32,143,52,118,24,50,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,130,41,63,30,207,90,103,74,116,170,189,26,123,222,199,175,225,
182,152,115,212,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,202,243,253,215,54,182,18,230,145,21,125,158,103,237,13,235,154,83,42,165,47,49,108,238,94,238,12,195,48,12,195,48,12,195,48,
12,195,48,12,195,48,12,179,100,202,219,227,57,39,163,163,239,37,156,57,29,99,56,122,78,72,143,156,232,246,25,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,61,162,94,87,221,70,52,71,47,228,
92,82,58,175,115,47,125,88,250,184,142,136,86,207,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,202,227,249,179,71,117,68,29,169,28,219,108,78,223,202,173,185,43,174,70,243,104,84,51,12,
195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,154,249,248,252,154,105,209,51,52,122,206,71,215,122,141,236,142,244,111,89,97,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,179,247,96,
142,158,20,221,83,162,219,105,87,108,253,106,56,247,228,142,254,218,27,213,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,102,111,58,34,106,140,179,69,171,222,111,183,49,59,29,121,36,69,
51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,170,73,191,255,252,205,115,59,97,79,236,152,155,10,243,113,126,239,101,175,81,191,143,163,143,78,247,110,53,195,48,12,195,48,12,195,48,12,195,48,
12,195,48,12,195,172,152,143,207,175,246,24,91,68,173,219,75,166,87,227,250,21,228,145,198,14,67,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,48,229,199,227,89,235,76,137,78,181,87,99,207,
251,248,53,220,22,115,142,154,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,121,190,255,218,198,86,194,60,178,162,207,243,172,189,97,93,115,74,165,244,37,134,205,221,203,157,97,24,134,97,
24,134,97,24,134,97,24,134,97,24,134,97,150,76,121,123,60,231,100,116,244,189,132,51,167,99,12,71,207,9,233,145,19,221,62,99,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,179,71,212,235,170,
219,136,230,232,133,156,75,74,231,117,238,165,15,75,31,215,17,209,234,153,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,121,60,127,246,168,142,168,35,149,99,155,205,233,91,185,53,119,197,
213,104,30,141,106,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,51,31,159,95,51,45,122,134,70,207,249,232,90,175,145,221,145,254,45,43,44,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,
12,179,100,246,30,204,209,147,162,123,74,116,59,237,138,173,95,13,231,158,220,209,95,123,163,154,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,236,77,71,68,141,113,182,104,213,251,237,54,
102,167,35,143,164,104,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,53,233,247,159,191,121,110,39,236,137,29,115,83,97,62,206,239,189,236,53,234,247,113,244,209,233,222,173,102,24,134,97,24,
134,97,24,134,97,24,134,97,24,134,97,152,21,243,241,249,213,30,99,139,168,117,123,201,244,106,92,191,130,60,210,216,97,200,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,11,166,252,120,60,107,157,
41,209,169,246,106,236,121,31,191,134,219,98,206,81,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,207,247,95,219,216,74,152,71,86,244,121,158,181,55,172,107,78,169,148,190,196,176,185,
123,185,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,111,143,231,156,140,142,190,151,112,230,116,140,225,232,57,33,61,114,162,219,103,12,195,48,12,195,48,12,195,48,12,195,48,12,195,
48,12,179,100,246,136,122,93,117,27,209,28,189,144,115,73,233,188,206,189,244,97,233,227,58,34,90,61,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,143,231,207,30,213,17,117,164,114,108,
179,57,125,43,183,230,174,184,26,205,163,81,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,107,230,227,243,107,166,69,207,208,232,57,31,93,235,53,178,59,210,191,101,133,133,97,24,134,97,24,134,
97,24,134,97,24,134,97,24,134,97,150,204,222,131,57,122,82,116,79,137,110,167,93,177,245,171,225,220,147,59,250,107,111,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,153,189,233,136,
168,49,206,22,173,122,191,221,198,236,116,228,145,20,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,171,38,253,254,243,55,207,237,132,61,177,99,110,42,204,199,249,189,151,189,70,253,62,142,62,
58,221,187,213,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,98,62,62,191,218,99,108,17,181,110,47,153,94,141,235,87,144,71,26,59,12,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,
193,148,31,143,103,173,51,37,58,213,94,141,61,239,227,215,112,91,204,57,106,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,229,249,254,107,27,91,9,243,200,138,62,207,179,246,134,117,205,41,
149,210,151,24,54,119,47,119,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,229,237,241,156,147,209,209,247,18,206,156,142,49,28,61,39,164,71,78,116,251,140,97,24,134,97,24,134,97,24,134,
97,24,134,97,24,134,97,150,204,30,81,175,171,110,35,154,163,23,114,46,41,157,215,185,151,62,44,125,92,71,68,171,103,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,229,241,252,217,163,58,162,
142,84,142,109,54,167,111,229,214,220,21,87,163,121,52,170,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,205,124,124,126,205,180,232,25,26,61,231,163,107,189,70,118,71,250,183,172,176,48,12,
195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,217,123,48,71,79,138,238,41,209,237,180,43,182,126,53,156,123,114,71,127,237,141,106,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,
179,55,29,17,53,198,217,162,85,239,183,219,152,157,142,60,146,162,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,213,164,223,127,254,230,185,157,176,39,118,204,77,133,249,56,191,247,178,215,
168,223,199,209,71,167,123,183,154,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,86,204,199,231,87,123,140,45,162,214,237,37,211,171,113,253,10,242,72,99,135,33,195,48,12,195,48,12,195,48,12,195,
48,12,195,48,12,195,44,152,242,227,241,172,117,166,68,167,218,171,177,231,125,252,26,110,139,57,71,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,166,60,223,127,109,99,43,97,30,89,209,231,
121,214,222,176,174,57,165,82,250,18,195,230,238,229,206,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,166,188,61,158,115,50,58,254,207,222,189,165,184,13,4,81,0,85,119,203,222,83,130,193,97,
32,27,10,12,129,129,124,204,182,71,82,87,250,225,89,64,255,31,125,8,92,58,222,64,113,185,213,239,18,206,158,142,17,142,158,9,233,209,19,221,254,198,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,
75,102,143,168,215,85,183,81,205,209,7,57,151,148,206,235,220,75,15,75,31,215,17,209,230,153,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,121,60,223,122,85,71,212,209,202,177,205,229,244,
173,220,154,187,226,106,52,143,69,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,172,153,247,143,207,217,22,61,75,163,103,62,186,214,107,116,119,164,239,99,133,133,97,24,134,97,24,134,97,24,
134,97,24,134,97,24,134,97,150,204,222,139,57,122,83,116,111,137,110,79,123,197,214,95,13,231,222,220,209,191,246,69,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,185,155,142,136,26,
227,217,162,77,239,183,219,200,78,71,30,77,209,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,106,210,159,191,255,242,188,78,216,27,59,230,165,194,124,156,95,123,217,107,212,175,227,232,209,
233,190,173,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,21,243,254,241,217,62,198,22,81,235,246,146,233,181,184,126,21,121,164,113,195,144,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,
97,22,76,249,249,120,214,58,91,162,83,237,211,216,243,62,126,13,183,197,204,81,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,207,95,191,183,113,149,48,143,174,232,243,60,107,95,88,215,
156,82,41,253,136,97,115,247,114,103,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,83,126,60,158,51,25,29,253,46,225,236,233,24,225,232,153,144,30,61,209,237,111,12,195,48,12,195,48,12,195,
48,12,195,48,12,195,48,12,179,100,246,136,122,93,117,27,213,28,125,144,115,73,233,188,206,189,244,176,244,113,29,17,109,158,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,148,199,243,173,
87,117,68,29,173,28,219,92,78,223,202,173,185,43,174,70,243,88,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,154,121,255,248,156,109,209,179,52,122,230,163,107,189,70,119,71,250,62,86,88,
24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,236,189,152,163,55,69,247,150,232,246,180,87,108,253,213,112,238,205,29,253,107,95,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,
204,146,153,187,233,136,168,49,158,45,218,244,126,187,141,236,116,228,209,20,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,171,38,253,249,251,47,207,235,132,189,177,99,94,42,204,199,249,181,
151,189,70,253,58,142,30,157,238,219,106,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,49,239,31,159,237,99,108,17,181,110,47,153,94,139,235,87,145,71,26,55,12,25,134,97,24,134,97,24,134,97,
24,134,97,24,134,97,24,102,193,148,159,143,103,173,179,37,58,213,62,141,61,239,227,215,112,91,204,28,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,242,252,245,123,27,87,9,243,232,138,
62,207,179,246,133,117,205,41,149,210,143,24,54,119,47,119,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,229,199,227,57,147,209,209,239,18,206,158,142,17,142,158,9,233,209,19,221,254,198,
48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,143,168,215,85,183,81,205,209,7,57,151,148,206,235,220,75,15,75,31,215,17,209,230,153,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,
76,121,60,223,122,85,71,212,209,202,177,205,229,244,173,220,154,187,226,106,52,143,69,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,172,153,247,143,207,217,22,61,75,163,103,62,186,214,107,116,
119,164,239,99,133,133,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,222,139,57,122,83,116,111,137,110,79,123,197,214,95,13,231,222,220,209,191,246,69,53,195,48,12,195,48,12,195,48,12,195,
48,12,195,48,12,195,44,153,185,155,142,136,26,227,217,162,77,239,183,219,200,78,71,30,77,209,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,106,210,159,191,255,242,188,78,216,27,59,230,165,194,
124,156,95,123,217,107,212,175,227,232,209,233,190,173,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,21,243,254,241,217,62,198,22,81,235,246,146,233,181,184,126,21,121,164,113,195,144,97,24,
134,97,24,134,97,24,134,97,24,134,97,24,134,97,22,76,249,249,120,214,58,91,162,83,237,211,216,243,62,126,13,183,197,204,81,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,207,95,191,183,
113,149,48,143,174,232,243,60,107,95,88,215,156,82,41,253,136,97,115,247,114,103,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,83,126,60,158,51,25,29,253,46,225,236,233,24,225,232,153,144,30,
61,209,237,111,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,246,136,122,93,117,27,213,28,125,144,115,73,233,188,206,189,244,176,244,113,29,17,109,158,25,134,97,24,134,97,24,134,97,24,134,
97,24,134,97,24,102,201,148,199,243,173,87,117,68,29,173,28,219,92,78,223,202,173,185,43,174,70,243,88,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,154,121,255,248,156,109,209,179,52,122,
230,163,107,189,70,119,71,250,62,86,88,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,236,189,152,163,55,69,247,150,232,246,180,87,108,253,213,112,238,205,29,253,107,95,84,51,12,195,48,12,
195,48,12,195,48,12,195,48,12,195,48,204,146,153,187,233,136,168,49,158,45,218,244,126,187,141,236,116,228,209,20,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,171,38,253,249,251,47,207,235,
132,189,177,99,94,42,204,199,249,181,151,189,70,253,58,142,30,157,238,219,106,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,49,239,31,159,237,99,108,17,181,110,47,153,94,139,235,87,145,71,26,
55,12,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,193,148,159,143,103,173,179,37,58,213,62,141,61,239,227,215,112,91,204,28,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,
242,252,245,123,27,87,9,243,232,138,62,207,179,246,133,117,205,41,149,210,143,24,54,119,47,119,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,229,199,227,57,147,209,209,239,18,206,158,142,
17,142,158,9,233,209,19,221,254,198,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,143,168,215,85,183,81,205,209,7,57,151,148,206,235,220,75,15,75,31,215,17,209,230,153,97,24,134,97,24,134,
97,24,134,97,24,134,97,24,134,97,150,76,121,60,223,122,85,71,212,209,202,177,205,229,244,173,220,154,187,226,106,52,143,69,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,172,153,247,143,207,
217,22,61,75,163,103,62,186,214,107,116,119,164,239,99,133,133,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,222,139,57,122,83,116,111,137,110,79,123,197,214,95,13,231,222,220,209,191,246,
69,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,185,155,142,136,26,227,217,162,77,239,183,219,200,78,71,30,77,209,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,106,210,159,
191,255,242,188,78,216,27,59,230,165,194,124,156,95,123,217,107,212,175,227,232,209,233,190,173,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,21,243,254,241,217,62,198,22,81,235,246,146,233,
181,184,126,21,121,164,113,195,144,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,22,76,249,249,120,214,58,91,162,83,237,211,216,243,62,126,13,183,197,204,81,51,12,195,48,12,195,48,12,195,48,12,
195,48,12,195,48,204,146,41,207,95,191,183,113,149,48,143,174,232,243,60,107,95,88,215,156,82,41,253,136,97,115,247,114,103,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,83,126,60,158,51,25,
29,253,46,225,236,233,24,225,232,153,144,30,61,209,237,111,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,246,136,122,93,117,27,213,28,125,144,115,73,233,188,206,189,244,176,244,113,29,17,
109,158,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,148,199,243,173,87,117,68,29,173,28,219,92,78,223,202,173,185,43,174,70,243,88,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,
48,204,154,121,255,248,156,109,209,179,52,122,230,163,107,189,70,119,71,250,62,86,88,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,236,189,152,163,55,69,247,150,232,246,180,87,108,253,213,
112,238,205,29,253,107,95,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,153,187,233,136,168,49,158,45,218,244,126,187,141,236,116,228,209,20,205,48,12,195,48,12,195,48,12,195,48,12,195,
48,12,195,48,171,38,253,249,251,47,207,235,132,189,177,99,94,42,204,199,249,181,151,189,70,253,58,142,30,157,238,219,106,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,49,239,31,159,237,99,108,
17,181,110,47,153,94,139,235,87,145,71,26,55,12,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,193,148,159,143,103,173,179,37,58,213,62,141,61,239,227,215,112,91,204,28,53,195,48,12,195,48,12,
195,48,12,195,48,12,195,48,12,195,44,153,242,252,245,123,27,87,9,243,232,138,62,207,179,246,133,117,205,41,149,210,143,24,54,119,47,119,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,229,
199,227,57,147,209,209,239,18,206,158,142,17,142,158,9,233,209,19,221,254,198,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,143,168,215,85,183,81,205,209,7,57,151,148,206,235,220,75,15,75,
31,215,17,209,230,153,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,121,60,223,122,85,71,212,209,202,177,205,229,244,173,220,154,187,226,106,52,143,69,53,195,48,12,195,48,12,195,48,12,195,
48,12,195,48,12,195,172,153,247,143,207,217,22,61,75,163,103,62,186,214,107,116,119,164,239,99,133,133,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,222,139,57,122,83,116,111,137,110,79,
123,197,214,95,13,231,222,220,209,191,246,69,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,185,155,142,136,26,227,217,162,77,239,183,219,200,78,71,30,77,209,12,195,48,12,195,48,12,195,
48,12,195,48,12,195,48,12,179,106,210,159,191,255,242,188,78,216,27,59,230,165,194,124,156,95,123,217,107,212,175,227,232,209,233,190,173,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,21,243,
254,241,217,62,198,22,81,235,246,146,233,181,184,126,21,121,164,113,195,144,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,22,76,249,249,120,214,58,91,162,83,237,211,216,243,62,126,13,183,197,204,
81,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,207,95,191,183,113,149,48,143,174,232,243,60,107,95,88,215,156,82,41,253,136,97,115,247,114,103,24,134,97,24,134,97,24,134,97,24,134,
97,24,134,97,152,37,83,126,60,158,51,25,29,253,46,225,236,233,24,225,232,153,144,30,61,209,237,111,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,246,136,122,93,117,27,213,28,125,144,115,
73,233,188,206,189,244,176,244,113,29,17,109,158,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,148,199,243,173,87,117,68,29,173,28,219,92,78,223,202,173,185,43,174,70,243,88,84,51,12,195,
48,12,195,48,12,195,48,12,195,48,12,195,48,204,154,121,255,248,156,109,209,179,52,122,230,163,107,189,70,119,71,250,62,86,88,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,236,189,152,163,
55,69,247,150,232,246,180,87,108,253,213,112,238,205,29,253,107,95,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,153,187,233,136,168,49,158,45,218,244,126,187,141,236,116,228,209,20,
205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,171,38,253,249,251,47,207,235,132,189,177,99,94,42,204,199,249,181,151,189,70,253,58,142,30,157,238,219,106,134,97,24,134,97,24,134,97,24,134,97,
24,134,97,24,134,89,49,239,31,159,237,99,108,17,181,110,47,153,94,139,235,87,145,71,26,55,12,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,193,148,159,143,103,173,179,37,58,213,62,141,61,239,
227,215,112,91,204,28,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,242,252,245,123,27,87,9,243,232,138,62,207,179,246,133,117,205,41,149,210,143,24,54,119,47,119,134,97,24,134,97,24,
134,97,24,134,97,24,134,97,24,134,89,50,229,199,227,57,147,209,209,239,18,206,158,142,17,142,158,9,233,209,19,221,254,198,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,143,168,215,85,183,
81,205,209,7,57,151,148,206,235,220,75,15,75,31,215,17,209,230,153,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,121,60,223,122,85,71,212,209,202,177,205,229,244,173,220,154,187,226,106,
52,143,69,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,172,153,247,143,207,217,22,61,75,163,103,62,186,214,107,116,119,164,239,99,133,133,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,
97,150,204,222,139,57,122,83,116,111,137,110,79,123,197,214,95,13,231,222,220,209,191,246,69,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,185,155,142,136,26,227,217,162,77,239,183,219,
200,78,71,30,77,209,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,106,210,159,191,255,242,188,78,216,27,59,230,165,194,124,156,95,123,217,107,212,175,227,232,209,233,190,173,102,24,134,97,24,
134,97,24,134,97,24,134,97,24,134,97,152,21,243,254,241,217,62,198,22,81,235,246,146,233,181,184,126,21,121,164,113,195,144,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,22,76,249,249,120,214,58,
91,162,83,237,211,216,243,62,126,13,183,197,204,81,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,207,95,191,183,113,149,48,143,174,232,243,60,107,95,88,215,156,82,41,253,136,97,115,247,
114,103,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,83,126,60,158,51,25,29,253,46,225,236,233,24,225,232,153,144,30,61,209,237,111,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,
100,246,136,122,93,117,27,213,28,125,144,115,73,233,188,206,189,244,176,244,113,29,17,109,158,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,148,199,243,173,87,117,68,29,173,28,219,92,78,
223,202,173,185,43,174,70,243,88,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,154,121,255,248,156,109,209,179,52,122,230,163,107,189,70,119,71,250,62,86,88,24,134,97,24,134,97,24,134,97,
24,134,97,24,134,97,24,102,201,236,189,152,163,55,69,247,150,232,246,180,87,108,253,213,112,238,205,29,253,107,95,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,153,187,233,136,168,49,
158,45,218,244,126,187,141,236,116,228,209,20,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,171,38,253,249,251,47,207,235,132,189,177,99,94,42,204,199,249,181,151,189,70,253,58,142,30,157,238,
219,106,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,49,239,31,159,237,99,108,17,181,110,47,153,94,139,235,87,145,71,26,55,12,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,193,148,
159,143,103,173,179,37,58,213,62,141,61,239,227,215,112,91,204,28,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,242,252,245,123,27,87,9,243,232,138,62,207,179,246,133,117,205,41,149,
210,143,24,54,119,47,119,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,229,199,227,57,147,209,209,239,18,206,158,142,17,142,158,9,233,209,19,221,254,198,48,12,195,48,12,195,48,12,195,48,
12,195,48,12,195,48,75,102,143,168,215,85,183,81,205,209,7,57,151,148,206,235,220,75,15,75,31,215,17,209,230,153,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,121,60,223,122,85,71,212,209,
202,177,205,229,244,173,220,154,187,226,106,52,143,69,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,172,153,247,143,207,217,22,61,75,163,103,62,186,214,107,116,119,164,239,99,133,133,97,24,
134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,222,139,57,122,83,116,111,137,110,79,123,197,214,95,13,231,222,220,209,191,246,69,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,
185,155,142,136,26,227,217,162,77,239,183,219,200,78,71,30,77,209,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,106,210,159,191,255,242,188,78,216,27,59,230,165,194,124,156,95,123,217,107,212,
175,227,232,209,233,190,173,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,21,243,254,241,217,62,198,22,81,235,246,146,233,181,184,126,21,121,164,113,195,144,97,24,134,97,24,134,97,24,134,97,
24,134,97,24,134,97,22,76,249,249,120,214,58,91,162,83,237,211,216,243,62,126,13,183,197,204,81,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,207,95,191,183,113,149,48,143,174,232,243,
60,107,95,88,215,156,82,41,253,136,97,115,247,114,103,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,83,126,60,158,51,25,29,253,46,225,236,233,24,225,232,153,144,30,61,209,237,111,12,195,48,
12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,246,136,122,93,117,27,213,28,125,144,115,73,233,188,206,189,244,176,244,113,29,17,109,158,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,
148,199,243,173,87,117,68,29,173,28,219,92,78,223,202,173,185,43,174,70,243,88,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,154,121,255,248,156,109,209,179,52,122,230,163,107,189,70,119,
71,250,62,86,88,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,236,189,152,163,55,69,247,150,232,246,180,87,108,253,213,112,238,205,29,253,107,95,84,51,12,195,48,12,195,48,12,195,48,12,195,
48,12,195,48,204,146,153,187,233,136,168,49,158,45,218,244,126,187,141,236,116,228,209,20,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,171,38,253,249,251,47,207,235,132,189,177,99,94,42,204,
199,249,181,151,189,70,253,58,142,30,157,238,219,106,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,49,239,31,159,237,99,108,17,181,110,47,153,94,139,235,87,145,71,26,55,12,25,134,97,24,134,
97,24,134,97,24,134,97,24,134,97,24,102,193,148,159,143,103,173,179,37,58,213,62,141,61,239,227,215,112,91,204,28,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,242,252,245,123,27,87,
9,243,232,138,62,207,179,246,133,117,205,41,149,210,143,24,54,119,47,119,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,229,199,227,57,147,209,209,239,18,206,158,142,17,142,158,9,233,209,
19,221,254,198,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,143,168,215,85,183,81,205,209,7,57,151,148,206,235,220,75,15,75,31,215,17,209,230,153,97,24,134,97,24,134,97,24,134,97,24,134,
97,24,134,97,150,76,121,60,223,122,85,71,212,209,202,177,205,229,244,173,220,154,187,226,106,52,143,69,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,172,153,247,143,207,217,22,61,75,163,103,
62,186,214,107,116,119,164,239,99,133,133,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,222,139,57,122,83,116,111,137,110,79,123,197,214,95,13,231,222,220,209,191,246,69,53,195,48,12,195,
48,12,195,48,12,195,48,12,195,48,12,195,44,153,185,155,142,136,26,227,217,162,77,239,183,219,200,78,71,30,77,209,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,106,210,159,191,255,242,188,78,
216,27,59,230,165,194,124,156,95,123,217,107,212,175,227,232,209,233,190,173,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,21,243,254,241,217,62,198,22,81,235,246,146,233,181,184,126,21,121,
164,113,195,144,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,22,76,249,249,120,214,58,91,162,83,237,211,216,243,62,126,13,183,197,204,81,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,
146,41,207,95,191,183,113,149,48,143,174,232,243,60,107,95,88,215,156,82,41,253,136,97,115,247,114,103,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,83,126,60,158,51,25,29,253,46,225,236,233,
24,225,232,153,144,30,61,209,237,111,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,246,136,122,93,117,27,213,28,125,144,115,73,233,188,206,189,244,176,244,113,29,17,109,158,25,134,97,24,
134,97,24,134,97,24,134,97,24,134,97,24,102,201,148,199,243,173,87,117,68,29,173,28,219,92,78,223,202,173,185,43,174,70,243,88,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,154,121,255,248,
156,109,209,179,52,122,230,163,107,189,70,119,71,250,62,86,88,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,236,189,152,163,55,69,247,150,232,246,180,87,108,253,213,112,238,205,29,253,107,
95,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,153,187,233,136,168,49,158,45,218,244,126,187,141,236,116,228,209,20,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,171,38,
253,249,251,47,207,235,132,189,177,99,94,42,204,199,249,181,151,189,70,253,58,142,30,157,238,219,106,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,49,239,31,159,237,99,108,17,181,110,47,153,
94,139,235,87,145,71,26,55,12,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,193,148,159,143,103,173,179,37,58,213,62,141,61,239,227,215,112,91,204,28,53,195,48,12,195,48,12,195,48,12,195,48,
12,195,48,12,195,44,153,242,252,245,123,27,87,9,243,232,138,62,207,179,246,133,117,205,41,149,210,143,24,54,119,47,119,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,229,199,227,57,147,209,
209,239,18,206,158,142,17,142,158,9,233,209,19,221,254,198,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,143,168,215,85,183,81,205,209,7,57,151,148,206,235,220,75,15,75,31,215,17,209,230,
153,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,121,60,223,122,85,71,212,209,202,177,205,229,244,173,220,154,187,226,106,52,143,69,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,
195,172,153,247,143,207,217,22,61,75,163,103,62,186,214,107,116,119,164,239,99,133,133,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,222,139,57,122,83,116,111,137,110,79,123,197,214,95,
13,231,222,220,209,191,246,69,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,185,155,142,136,26,227,217,162,77,239,183,219,200,78,71,30,77,209,12,195,48,12,195,48,12,195,48,12,195,48,
12,195,48,12,179,106,210,159,191,255,242,188,78,216,27,59,230,165,194,124,156,95,123,217,107,212,175,227,232,209,233,190,173,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,21,243,254,241,217,
62,198,22,81,235,246,146,233,181,184,126,21,121,164,113,195,144,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,22,76,249,249,120,214,58,91,162,83,237,211,216,243,62,126,13,183,197,204,81,51,12,195,
48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,207,95,191,183,113,149,48,143,174,232,243,60,107,95,88,215,156,82,41,253,136,97,115,247,114,103,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,
152,37,83,126,60,158,51,25,29,253,46,225,236,233,24,225,232,153,144,30,61,209,237,111,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,246,136,122,93,117,27,213,28,125,144,115,73,233,188,206,
189,244,176,244,113,29,17,109,158,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,148,199,243,173,87,117,68,29,173,28,219,92,78,223,202,173,185,43,174,70,243,88,84,51,12,195,48,12,195,48,
12,195,48,12,195,48,12,195,48,204,154,121,255,248,156,109,209,179,52,122,230,163,107,189,70,119,71,250,62,86,88,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,236,189,152,163,55,69,247,150,
232,246,180,87,108,253,213,112,238,205,29,253,107,95,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,153,187,233,136,168,49,158,45,218,244,126,187,141,236,116,228,209,20,205,48,12,195,
48,12,195,48,12,195,48,12,195,48,12,195,48,171,38,253,249,251,47,207,235,132,189,177,99,94,42,204,199,249,181,151,189,70,253,58,142,30,157,238,219,106,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,
134,89,49,239,31,159,237,99,108,17,181,110,47,153,94,139,235,87,145,71,26,55,12,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,193,148,159,143,103,173,179,37,58,213,62,141,61,239,227,215,112,
91,204,28,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,242,252,245,123,27,87,9,243,232,138,62,207,179,246,133,117,205,41,149,210,143,24,54,119,47,119,134,97,24,134,97,24,134,97,24,134,
97,24,134,97,24,134,89,50,229,199,227,57,147,209,209,239,18,206,158,142,17,142,158,9,233,209,19,221,254,198,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,143,168,215,85,183,81,205,209,7,
57,151,148,206,235,220,75,15,75,31,215,17,209,230,153,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,121,60,223,122,85,71,212,209,202,177,205,229,244,173,220,154,187,226,106,52,143,69,53,
195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,172,153,247,143,207,217,22,61,75,163,103,62,186,214,107,116,119,164,239,99,133,133,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,222,
139,57,122,83,116,111,137,110,79,123,197,214,95,13,231,222,220,209,191,246,69,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,185,155,142,136,26,227,217,162,77,239,183,219,200,78,71,30,
77,209,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,106,210,159,191,255,242,188,78,216,27,59,230,165,194,124,156,95,123,217,107,212,175,227,232,209,233,190,173,102,24,134,97,24,134,97,24,134,
97,24,134,97,24,134,97,152,21,243,254,241,217,62,198,22,81,235,246,146,233,181,184,126,21,121,164,113,195,144,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,22,76,249,249,120,214,58,91,162,83,237,
211,216,243,62,126,13,183,197,204,81,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,207,95,191,183,113,149,48,143,174,232,243,60,107,95,88,215,156,82,41,253,136,97,115,247,114,103,24,
134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,83,126,60,158,51,25,29,253,46,225,236,233,24,225,232,153,144,30,61,209,237,111,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,246,136,
122,93,117,27,213,28,125,144,115,73,233,188,206,189,244,176,244,113,29,17,109,158,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,148,199,243,173,87,117,68,29,173,28,219,92,78,223,202,173,
185,43,174,70,243,88,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,154,121,255,248,156,109,209,179,52,122,230,163,107,189,70,119,71,250,62,86,88,24,134,97,24,134,97,24,134,97,24,134,97,24,
134,97,24,102,201,236,189,152,163,55,69,247,150,232,246,180,87,108,253,213,112,238,205,29,253,107,95,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,153,187,233,136,168,49,158,45,218,244,
126,187,141,236,116,228,209,20,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,171,38,253,249,251,47,207,235,132,189,177,99,94,42,204,199,249,181,151,189,70,253,58,142,30,157,238,219,106,134,
97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,49,239,31,159,237,99,108,17,181,110,47,153,94,139,235,87,145,71,26,55,12,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,193,148,159,143,103,
173,179,37,58,213,62,141,61,239,227,215,112,91,204,28,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,242,252,245,123,27,87,9,243,232,138,62,207,179,246,133,117,205,41,149,210,143,24,54,
119,47,119,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,229,199,227,57,147,209,209,239,18,206,158,142,17,142,158,9,233,209,19,221,254,198,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,
48,75,102,143,168,215,85,183,81,205,209,7,57,151,148,206,235,220,75,15,75,31,215,17,209,230,153,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,121,60,223,122,85,71,212,209,202,177,205,229,
244,173,220,154,187,226,106,52,143,69,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,172,153,247,143,207,217,22,61,75,163,103,62,186,214,107,116,119,164,239,99,133,133,97,24,134,97,24,134,97,
24,134,97,24,134,97,24,134,97,150,204,222,139,57,122,83,116,111,137,110,79,123,197,214,95,13,231,222,220,209,191,246,69,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,185,155,142,136,
26,227,217,162,77,239,183,219,200,78,71,30,77,209,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,106,210,159,191,255,242,188,78,216,27,59,230,165,194,124,156,95,123,217,107,212,175,227,232,209,
233,190,173,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,21,243,254,241,217,62,198,22,81,235,246,146,233,181,184,126,21,121,164,113,195,144,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,
97,22,76,249,249,120,214,58,91,162,83,237,211,216,243,62,126,13,183,197,204,81,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,207,95,191,183,113,149,48,143,174,232,243,60,107,95,88,215,
156,82,41,253,136,97,115,247,114,103,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,83,126,60,158,51,25,29,253,46,225,236,233,24,225,232,153,144,30,61,209,237,111,12,195,48,12,195,48,12,195,
48,12,195,48,12,195,48,12,179,100,246,136,122,93,117,27,213,28,125,144,115,73,233,188,206,189,244,176,244,113,29,17,109,158,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,148,199,243,173,
87,117,68,29,173,28,219,92,78,223,202,173,185,43,174,70,243,88,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,154,121,255,248,156,109,209,179,52,122,230,163,107,189,70,119,71,250,62,86,88,
24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,236,189,152,163,55,69,247,150,232,246,180,87,108,253,213,112,238,205,29,253,107,95,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,
204,146,153,187,233,136,168,49,158,45,218,244,126,187,141,236,116,228,209,20,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,171,38,253,249,251,47,207,235,132,189,177,99,94,42,204,199,249,181,
151,189,70,253,58,142,30,157,238,219,106,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,49,239,31,159,237,99,108,17,181,110,47,153,94,139,235,87,145,71,26,55,12,25,134,97,24,134,97,24,134,97,
24,134,97,24,134,97,24,102,193,148,159,143,103,173,179,37,58,213,62,141,61,239,227,215,112,91,204,28,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,242,252,245,123,27,87,9,243,232,138,
62,207,179,246,133,117,205,41,149,210,143,24,54,119,47,119,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,229,199,227,57,147,209,209,239,18,206,158,142,17,142,158,9,233,209,19,221,254,198,
48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,143,168,215,85,183,81,205,209,7,57,151,148,206,235,220,75,15,75,31,215,17,209,230,153,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,
76,121,60,223,122,85,71,212,209,202,177,205,229,244,173,220,154,187,226,106,52,143,69,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,172,153,247,143,207,217,22,61,75,163,103,62,186,214,107,116,
119,164,239,99,133,133,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,222,139,57,122,83,116,111,137,110,79,123,197,214,95,13,231,222,220,209,191,246,69,53,195,48,12,195,48,12,195,48,12,195,
48,12,195,48,12,195,44,153,185,155,142,136,26,227,217,162,77,239,183,219,200,78,71,30,77,209,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,106,210,159,191,255,242,188,78,216,27,59,230,165,194,
124,156,95,123,217,107,212,175,227,232,209,233,190,173,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,21,243,254,241,217,62,198,22,81,235,246,146,233,181,184,126,21,121,164,113,195,144,97,24,
134,97,24,134,97,24,134,97,24,134,97,24,134,97,22,76,249,249,120,214,58,91,162,83,237,211,216,243,62,126,13,183,197,204,81,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,207,95,191,183,
113,149,48,143,174,232,243,60,107,95,88,215,156,82,41,253,136,97,115,247,114,103,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,83,126,60,158,51,25,29,253,46,225,236,233,24,225,232,153,144,30,
61,209,237,111,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,246,136,122,93,117,27,213,28,125,144,115,73,233,188,206,189,244,176,244,113,29,17,109,158,25,134,97,24,134,97,24,134,97,24,134,
97,24,134,97,24,102,201,148,199,243,173,87,117,68,29,173,28,219,92,78,223,202,173,185,43,174,70,243,88,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,154,121,255,248,156,109,209,179,52,122,
230,163,107,189,70,119,71,250,62,86,88,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,236,189,152,163,55,69,247,150,232,246,180,87,108,253,213,112,238,205,29,253,107,95,84,51,12,195,48,12,
195,48,12,195,48,12,195,48,12,195,48,204,146,153,187,233,136,168,49,158,45,218,244,126,187,141,236,116,228,209,20,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,171,38,253,249,251,47,207,235,
132,189,177,99,94,42,204,199,249,181,151,189,70,253,58,142,30,157,238,219,106,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,49,239,31,159,237,99,108,17,181,110,47,153,94,139,235,87,145,71,26,
55,12,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,193,148,159,143,103,173,179,37,58,213,62,141,61,239,227,215,112,91,204,28,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,
242,252,245,123,27,87,9,243,232,138,62,207,179,246,133,117,205,41,149,210,143,24,54,119,47,119,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,229,199,227,57,147,209,209,239,18,206,158,142,
17,142,158,9,233,209,19,221,254,198,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,143,168,215,85,183,81,205,209,7,57,151,148,206,235,220,75,15,75,31,215,17,209,230,153,97,24,134,97,24,134,
97,24,134,97,24,134,97,24,134,97,150,76,121,60,223,122,85,71,212,209,202,177,205,229,244,173,220,154,187,226,106,52,143,69,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,172,153,247,143,207,
217,22,61,75,163,103,62,186,214,107,116,119,164,239,99,133,133,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,222,139,57,122,83,116,111,137,110,79,123,197,214,95,13,231,222,220,209,191,246,
69,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,185,155,142,136,26,227,217,162,77,239,183,219,200,78,71,30,77,209,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,106,210,159,
191,255,242,188,78,216,27,59,230,165,194,124,156,95,123,217,107,212,175,227,232,209,233,190,173,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,21,243,254,241,217,62,198,22,81,235,246,146,233,
181,184,126,21,121,164,113,195,144,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,22,76,249,249,120,214,58,91,162,83,237,211,216,243,62,126,13,183,197,204,81,51,12,195,48,12,195,48,12,195,48,12,
195,48,12,195,48,204,146,41,207,95,191,183,113,149,48,143,174,232,243,60,107,95,88,215,156,82,41,253,136,97,115,247,114,103,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,83,126,60,158,51,25,
29,253,46,225,236,233,24,225,232,153,144,30,61,209,237,111,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,246,136,122,93,117,27,213,28,125,144,115,73,233,188,206,189,244,176,244,113,29,17,
109,158,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,148,199,243,173,87,117,68,29,173,28,219,92,78,223,202,173,185,43,174,70,243,88,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,
48,204,154,121,255,248,156,109,209,179,52,122,230,163,107,189,70,119,71,250,62,86,88,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,236,189,152,163,55,69,247,150,232,246,180,87,108,253,213,
112,238,205,29,253,107,95,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,153,187,233,136,168,49,158,45,218,244,126,187,141,236,116,228,209,20,205,48,12,195,48,12,195,48,12,195,48,12,195,
48,12,195,48,171,38,253,249,251,47,207,235,132,189,177,99,94,42,204,199,249,181,151,189,70,253,58,142,30,157,238,219,106,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,49,239,31,159,237,99,108,
17,181,110,47,153,94,139,235,87,145,71,26,55,12,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,193,148,159,143,103,173,179,37,58,213,62,141,61,239,227,215,112,91,204,28,53,195,48,12,195,48,12,
195,48,12,195,48,12,195,48,12,195,44,153,242,252,245,123,27,87,9,243,232,138,62,207,179,246,133,117,205,41,149,210,143,24,54,119,47,119,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,229,
199,227,57,147,209,209,239,18,206,158,142,17,142,158,9,233,209,19,221,254,198,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,143,168,215,85,183,81,205,209,7,57,151,148,206,235,220,75,15,75,
31,215,17,209,230,153,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,121,60,223,122,85,71,212,209,202,177,205,229,244,173,220,154,187,226,106,52,143,69,53,195,48,12,195,48,12,195,48,12,195,
48,12,195,48,12,195,172,153,247,143,207,217,22,61,75,163,103,62,186,214,107,116,119,164,239,99,133,133,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,222,139,57,122,83,116,111,137,110,79,
123,197,214,95,13,231,222,220,209,191,246,69,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,185,155,142,136,26,227,217,162,77,239,183,219,200,78,71,30,77,209,12,195,48,12,195,48,12,195,
48,12,195,48,12,195,48,12,179,106,210,159,191,255,242,188,78,216,27,59,230,165,194,124,156,95,123,217,107,212,175,227,232,209,233,190,173,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,21,243,
254,241,217,62,198,22,81,235,246,146,233,181,184,126,21,121,164,113,195,144,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,22,76,249,249,120,214,58,91,162,83,237,211,216,243,62,126,13,183,197,204,
81,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,207,95,191,183,113,149,48,143,174,232,243,60,107,95,88,215,156,82,41,253,136,97,115,247,114,103,24,134,97,24,134,97,24,134,97,24,134,
97,24,134,97,152,37,83,126,60,158,51,25,29,253,46,225,236,233,24,225,232,153,144,30,61,209,237,111,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,246,136,122,93,117,27,213,28,125,144,115,
73,233,188,206,189,244,176,244,113,29,17,109,158,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,148,199,243,173,87,117,68,29,173,28,219,92,78,223,202,173,185,43,174,70,243,88,84,51,12,195,
48,12,195,48,12,195,48,12,195,48,12,195,48,204,154,121,255,248,156,109,209,179,52,122,230,163,107,189,70,119,71,250,62,86,88,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,236,189,152,163,
55,69,247,150,232,246,180,87,108,253,213,112,238,205,29,253,107,95,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,153,187,233,136,168,49,158,45,218,244,126,187,141,236,116,228,209,20,
205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,171,38,253,249,251,47,207,235,132,189,177,99,94,42,204,199,249,181,151,189,70,253,58,142,30,157,238,219,106,134,97,24,134,97,24,134,97,24,134,97,
24,134,97,24,134,89,49,239,31,159,237,99,108,17,181,110,47,153,94,139,235,87,145,71,26,55,12,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,193,148,159,143,103,173,179,37,58,213,62,141,61,239,
227,215,112,91,204,28,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,242,252,245,123,27,87,9,243,232,138,62,207,179,246,133,117,205,41,149,210,143,24,54,119,47,119,134,97,24,134,97,24,
134,97,24,134,97,24,134,97,24,134,89,50,229,199,227,57,147,209,209,239,18,206,158,142,17,142,158,9,233,209,19,221,254,198,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,143,168,215,85,183,
81,205,209,7,57,151,148,206,235,220,75,15,75,31,215,17,209,230,153,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,121,60,223,122,85,71,212,209,202,177,205,229,244,173,220,154,187,226,106,
52,143,69,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,172,153,247,143,207,217,22,61,75,163,103,62,186,214,107,116,119,164,239,99,133,133,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,
97,150,204,222,139,57,122,83,116,111,137,110,79,123,197,214,95,13,231,222,220,209,191,246,69,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,185,155,142,136,26,227,217,162,77,239,183,219,
200,78,71,30,77,209,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,106,210,159,191,255,242,188,78,216,27,59,230,165,194,124,156,95,123,217,107,212,175,227,232,209,233,190,173,102,24,134,97,24,
134,97,24,134,97,24,134,97,24,134,97,152,21,243,254,241,217,62,198,22,81,235,246,146,233,181,184,126,21,121,164,113,195,144,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,22,76,249,249,120,214,58,
91,162,83,237,211,216,243,62,126,13,183,197,204,81,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,207,95,191,183,113,149,48,143,174,232,243,60,107,95,88,215,156,82,41,253,136,97,115,247,
114,103,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,83,126,60,158,51,25,29,253,46,225,236,233,24,225,232,153,144,30,61,209,237,111,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,
100,246,136,122,93,117,27,213,28,125,144,115,73,233,188,206,189,244,176,244,113,29,17,109,158,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,148,199,243,173,87,117,68,29,173,28,219,92,78,
223,202,173,185,43,174,70,243,88,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,154,121,255,248,156,109,209,179,52,122,230,163,107,189,70,119,71,250,62,86,88,24,134,97,24,134,97,24,134,97,
24,134,97,24,134,97,24,102,201,236,189,152,163,55,69,247,150,232,246,180,87,108,253,213,112,238,205,29,253,107,95,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,153,187,233,136,168,49,
158,45,218,244,126,187,141,236,116,228,209,20,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,171,38,253,249,251,47,207,235,132,189,177,99,94,42,204,199,249,181,151,189,70,253,58,142,30,157,238,
219,106,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,49,239,31,159,237,99,108,17,181,110,47,153,94,139,235,87,145,71,26,55,12,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,193,148,
159,143,103,173,179,37,58,213,62,141,61,239,227,215,112,91,204,28,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,242,252,245,123,27,87,9,243,232,138,62,207,179,246,133,117,205,41,149,
210,143,24,54,119,47,119,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,229,199,227,57,147,209,209,239,18,206,158,142,17,142,158,9,233,209,19,221,254,198,48,12,195,48,12,195,48,12,195,48,
12,195,48,12,195,48,75,102,143,168,215,85,183,81,205,209,7,57,151,148,206,235,220,75,15,75,31,215,17,209,230,153,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,121,60,223,122,85,71,212,209,
202,177,205,229,244,173,220,154,187,226,106,52,143,69,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,172,153,247,143,207,217,22,61,75,163,103,62,186,214,107,116,119,164,239,99,133,133,97,24,
134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,222,139,57,122,83,116,111,137,110,79,123,197,214,95,13,231,222,220,209,191,246,69,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,
185,155,142,136,26,227,217,162,77,239,183,219,200,78,71,30,77,209,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,106,210,159,191,255,242,188,78,216,27,59,230,165,194,124,156,95,123,217,107,212,
175,227,232,209,233,190,173,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,21,243,254,241,217,62,198,22,81,235,246,146,233,181,184,126,21,121,164,113,195,144,97,24,134,97,24,134,97,24,134,97,
24,134,97,24,134,97,22,76,249,249,120,214,58,91,162,83,237,211,216,243,62,126,13,183,197,204,81,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,207,95,191,183,113,149,48,143,174,232,243,
60,107,95,88,215,156,82,41,253,136,97,115,247,114,103,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,83,126,60,158,51,25,29,253,46,225,236,233,24,225,232,153,144,30,61,209,237,111,12,195,48,
12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,246,136,122,93,117,27,213,28,125,144,115,73,233,188,206,189,244,176,244,113,29,17,109,158,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,
148,199,243,173,87,117,68,29,173,28,219,92,78,223,202,173,185,43,174,70,243,88,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,154,121,255,248,156,109,209,179,52,122,230,163,107,189,70,119,
71,250,62,86,88,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,236,189,152,163,55,69,247,150,232,246,180,87,108,253,213,112,238,205,29,253,107,95,84,51,12,195,48,12,195,48,12,195,48,12,195,
48,12,195,48,204,146,153,187,233,136,168,49,158,45,218,244,126,187,141,236,116,228,209,20,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,171,38,253,249,251,47,207,235,132,189,177,99,94,42,204,
199,249,181,151,189,70,253,58,142,30,157,238,219,106,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,49,239,31,159,237,99,108,17,181,110,47,153,94,139,235,87,145,71,26,55,12,25,134,97,24,134,
97,24,134,97,24,134,97,24,134,97,24,102,193,148,159,143,103,173,179,37,58,213,62,141,61,239,227,215,112,91,204,28,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,242,252,245,123,27,87,
9,243,232,138,62,207,179,246,133,117,205,41,149,210,143,24,54,119,47,119,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,229,199,227,57,147,209,209,239,18,206,158,142,17,142,158,9,233,209,
19,221,254,198,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,143,168,215,85,183,81,205,209,7,57,151,148,206,235,220,75,15,75,31,215,17,209,230,153,97,24,134,97,24,134,97,24,134,97,24,134,
97,24,134,97,150,76,121,60,223,122,85,71,212,209,202,177,205,229,244,173,220,154,187,226,106,52,143,69,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,172,153,247,143,207,217,22,61,75,163,103,
62,186,214,107,116,119,164,239,99,133,133,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,222,139,57,122,83,116,111,137,110,79,123,197,214,95,13,231,222,220,209,191,246,69,53,195,48,12,195,
48,12,195,48,12,195,48,12,195,48,12,195,44,153,185,155,142,136,26,227,217,162,77,239,183,219,200,78,71,30,77,209,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,106,210,159,191,255,242,188,78,
216,27,59,230,165,194,124,156,95,123,217,107,212,175,227,232,209,233,190,173,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,21,243,254,241,217,62,198,22,81,235,246,146,233,181,184,126,21,121,
164,113,195,144,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,22,76,249,249,120,214,58,91,162,83,237,211,216,243,62,126,13,183,197,204,81,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,
146,41,207,95,191,183,113,149,48,143,174,232,243,60,107,95,88,215,156,82,41,253,136,97,115,247,114,103,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,83,126,60,158,51,25,29,253,46,225,236,233,
24,225,232,153,144,30,61,209,237,111,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,246,136,122,93,117,27,213,28,125,144,115,73,233,188,206,189,244,176,244,113,29,17,109,158,25,134,97,24,
134,97,24,134,97,24,134,97,24,134,97,24,102,201,148,199,243,173,87,117,68,29,173,28,219,92,78,223,202,173,185,43,174,70,243,88,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,154,121,255,248,
156,109,209,179,52,122,230,163,107,189,70,119,71,250,62,86,88,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,236,189,152,163,55,69,247,150,232,246,180,87,108,253,213,112,238,205,29,253,107,
95,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,153,187,233,136,168,49,158,45,218,244,126,187,141,236,116,228,209,20,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,171,38,
253,249,251,47,207,235,132,189,177,99,94,42,204,199,249,181,151,189,70,253,58,142,30,157,238,219,106,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,49,239,31,159,237,99,108,17,181,110,47,153,
94,139,235,87,145,71,26,55,12,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,193,148,159,143,103,173,179,37,58,213,62,141,61,239,227,215,112,91,204,28,53,195,48,12,195,48,12,195,48,12,195,48,
12,195,48,12,195,44,153,242,252,245,123,27,87,9,243,232,138,62,207,179,246,133,117,205,41,149,210,143,24,54,119,47,119,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,229,199,227,57,147,209,
209,239,18,206,158,142,17,142,158,9,233,209,19,221,254,198,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,143,168,215,85,183,81,205,209,7,57,151,148,206,235,220,75,15,75,31,215,17,209,230,
153,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,121,60,223,122,85,71,212,209,202,177,205,229,244,173,220,154,187,226,106,52,143,69,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,
195,172,153,247,143,207,217,22,61,75,163,103,62,186,214,107,116,119,164,239,99,133,133,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,222,139,57,122,83,116,111,137,110,79,123,197,214,95,
13,231,222,220,209,191,246,69,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,185,155,142,136,26,227,217,162,77,239,183,219,200,78,71,30,77,209,12,195,48,12,195,48,12,195,48,12,195,48,
12,195,48,12,179,106,210,159,191,255,242,188,78,216,27,59,230,165,194,124,156,95,123,217,107,212,175,227,232,209,233,190,173,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,21,243,254,241,217,
62,198,22,81,235,246,146,233,181,184,126,21,121,164,113,195,144,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,22,76,249,249,120,214,58,91,162,83,237,211,216,243,62,126,13,183,197,204,81,51,12,195,
48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,207,95,191,183,113,149,48,143,174,232,243,60,107,95,88,215,156,82,41,253,136,97,115,247,114,103,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,
152,37,83,126,60,158,51,25,29,253,46,225,236,233,24,225,232,153,144,30,61,209,237,111,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,246,136,122,93,117,27,213,28,125,144,115,73,233,188,206,
189,244,176,244,113,29,17,109,158,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,148,199,243,173,87,117,68,29,173,28,219,92,78,223,202,173,185,43,174,70,243,88,84,51,12,195,48,12,195,48,
12,195,48,12,195,48,12,195,48,204,154,121,255,248,156,109,209,179,52,122,230,163,107,189,70,119,71,250,62,86,88,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,236,189,152,163,55,69,247,150,
232,246,180,87,108,253,213,112,238,205,29,253,107,95,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,153,187,233,136,168,49,158,45,218,244,126,187,141,236,116,228,209,20,205,48,12,195,
48,12,195,48,12,195,48,12,195,48,12,195,48,171,38,253,249,251,47,207,235,132,189,177,99,94,42,204,199,249,181,151,189,70,253,58,142,30,157,238,219,106,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,
134,89,49,239,31,159,237,99,108,17,181,110,47,153,94,139,235,87,145,71,26,55,12,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,193,148,159,143,103,173,179,37,58,213,62,141,61,239,227,215,112,
91,204,28,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,242,252,245,123,27,87,9,243,232,138,62,207,179,246,133,117,205,41,149,210,143,24,54,119,47,119,134,97,24,134,97,24,134,97,24,134,
97,24,134,97,24,134,89,50,229,199,227,57,147,209,209,239,18,206,158,142,17,142,158,9,233,209,19,221,254,198,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,143,168,215,85,183,81,205,209,7,
57,151,148,206,235,220,75,15,75,31,215,17,209,230,153,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,121,60,223,122,85,71,212,209,202,177,205,229,244,173,220,154,187,226,106,52,143,69,53,
195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,172,153,247,143,207,217,22,61,75,163,103,62,186,214,107,116,119,164,239,99,133,133,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,222,
139,57,122,83,116,111,137,110,79,123,197,214,95,13,231,222,220,209,191,246,69,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,185,155,142,136,26,227,217,162,77,239,183,219,200,78,71,30,
77,209,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,106,210,159,191,255,242,188,78,216,27,59,230,165,194,124,156,95,123,217,107,212,175,227,232,209,233,190,173,102,24,134,97,24,134,97,24,134,
97,24,134,97,24,134,97,152,21,243,254,241,217,62,198,22,81,235,246,146,233,181,184,126,21,121,164,113,195,144,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,22,76,249,249,120,214,58,91,162,83,237,
211,216,243,62,126,13,183,197,204,81,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,207,95,191,183,113,149,48,143,174,232,243,60,107,95,88,215,156,82,41,253,136,97,115,247,114,103,24,
134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,83,126,60,158,51,25,29,253,46,225,236,233,24,225,232,153,144,30,61,209,237,111,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,246,136,
122,93,117,27,213,28,125,144,115,73,233,188,206,189,244,176,244,113,29,17,109,158,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,148,199,243,173,87,117,68,29,173,28,219,92,78,223,202,173,
185,43,174,70,243,88,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,154,121,255,248,156,109,209,179,52,122,230,163,107,189,70,119,71,250,62,86,88,24,134,97,24,134,97,24,134,97,24,134,97,24,
134,97,24,102,201,236,189,152,163,55,69,247,150,232,246,180,87,108,253,213,112,238,205,29,253,107,95,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,153,187,233,136,168,49,158,45,218,244,
126,187,141,236,116,228,209,20,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,171,38,253,249,251,47,207,235,132,189,177,99,94,42,204,199,249,181,151,189,70,253,58,142,30,157,238,219,106,134,
97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,49,239,31,159,237,99,108,17,181,110,47,153,94,139,235,87,145,71,26,55,12,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,193,148,159,143,103,
173,179,37,58,213,62,141,61,239,227,215,112,91,204,28,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,242,252,245,123,27,87,9,243,232,138,62,207,179,246,133,117,205,41,149,210,143,24,54,
119,47,119,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,229,199,227,57,147,209,209,239,18,206,158,142,17,142,158,9,233,209,19,221,254,198,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,
48,75,102,143,168,215,85,183,81,205,209,7,57,151,148,206,235,220,75,15,75,31,215,17,209,230,153,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,121,60,223,122,85,71,212,209,202,177,205,229,
244,173,220,154,187,226,106,52,143,69,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,172,153,247,143,207,217,22,61,75,163,103,62,186,214,107,116,119,164,239,99,133,133,97,24,134,97,24,134,97,
24,134,97,24,134,97,24,134,97,150,204,222,139,57,122,83,116,111,137,110,79,123,197,214,95,13,231,222,220,209,191,246,69,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,185,155,142,136,
26,227,217,162,77,239,183,219,200,78,71,30,77,209,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,106,210,159,191,255,242,188,78,216,27,59,230,165,194,124,156,95,123,217,107,212,175,227,232,209,
233,190,173,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,21,243,254,241,217,62,198,22,81,235,246,146,233,181,184,126,21,121,164,113,195,144,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,
97,22,76,249,249,120,214,58,91,162,83,237,211,216,243,62,126,13,183,197,204,81,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,207,95,191,183,113,149,48,143,174,232,243,60,107,95,88,215,
156,82,41,253,136,97,115,247,114,103,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,83,126,60,158,51,25,29,253,46,225,236,233,24,225,232,153,144,30,61,209,237,111,12,195,48,12,195,48,12,195,
48,12,195,48,12,195,48,12,179,100,246,136,122,93,117,27,213,28,125,144,115,73,233,188,206,189,244,176,244,113,29,17,109,158,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,148,199,243,173,
87,117,68,29,173,28,219,92,78,223,202,173,185,43,174,70,243,88,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,154,121,255,248,156,109,209,179,52,122,230,163,107,189,70,119,71,250,62,86,88,
24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,236,189,152,163,55,69,247,150,232,246,180,87,108,253,213,112,238,205,29,253,107,95,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,
204,146,153,187,233,136,168,49,158,45,218,244,126,187,141,236,116,228,209,20,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,171,38,253,249,251,47,207,235,132,189,177,99,94,42,204,199,249,181,
151,189,70,253,58,142,30,157,238,219,106,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,49,239,31,159,237,99,108,17,181,110,47,153,94,139,235,87,145,71,26,55,12,25,134,97,24,134,97,24,134,97,
24,134,97,24,134,97,24,102,193,148,159,143,103,173,179,37,58,213,62,141,61,239,227,215,112,91,204,28,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,242,252,245,123,27,87,9,243,232,138,
62,207,179,246,133,117,205,41,149,210,143,24,54,119,47,119,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,50,229,199,227,57,147,209,209,239,18,206,158,142,17,142,158,9,233,209,19,221,254,198,
48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,143,168,215,85,183,81,205,209,7,57,151,148,206,235,220,75,15,75,31,215,17,209,230,153,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,
76,121,60,223,122,85,71,212,209,202,177,205,229,244,173,220,154,187,226,106,52,143,69,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,172,153,247,143,207,217,22,61,75,163,103,62,186,214,107,116,
119,164,239,99,133,133,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,222,139,57,122,83,116,111,137,110,79,123,197,214,95,13,231,222,220,209,191,246,69,53,195,48,12,195,48,12,195,48,12,195,
48,12,195,48,12,195,44,153,185,155,142,136,26,227,217,162,77,239,183,219,200,78,71,30,77,209,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,106,210,159,191,255,242,188,78,216,27,59,230,165,194,
124,156,95,123,217,107,212,175,227,232,209,233,190,173,102,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,21,243,254,241,217,62,198,22,81,235,246,146,233,181,184,126,21,121,164,113,195,144,97,24,
134,97,24,134,97,24,134,97,24,134,97,24,134,97,22,76,249,249,120,214,58,91,162,83,237,211,216,243,62,126,13,183,197,204,81,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,207,95,191,183,
113,149,48,143,174,232,243,60,107,95,88,215,156,82,41,253,136,97,115,247,114,103,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,37,83,126,60,158,51,25,29,253,46,225,236,233,24,225,232,153,144,30,
61,209,237,111,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,246,136,122,93,117,27,213,28,125,144,115,73,233,188,206,189,244,176,244,113,29,17,109,158,25,134,97,24,134,97,24,134,97,24,134,
97,24,134,97,24,102,201,148,199,243,173,87,117,68,29,173,28,219,92,78,223,202,173,185,43,174,70,243,88,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,252,103,239,110,82,228,134,129,48,128,90,146,
187,239,148,208,208,33,144,11,13,12,129,129,89,204,181,199,182,42,250,233,28,64,251,167,133,192,165,231,11,20,197,87,12,179,102,222,63,190,102,90,244,12,141,158,243,209,181,94,35,187,35,253,95,86,88,24,
134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,236,61,152,163,39,69,247,148,232,118,218,21,91,191,26,206,61,185,163,191,246,70,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,
217,155,142,136,26,227,108,209,170,247,219,109,204,78,71,30,73,209,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,106,210,219,223,207,60,183,19,246,196,142,185,169,48,31,231,247,94,246,26,245,
251,56,250,232,116,239,86,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,138,121,255,248,106,143,177,69,212,186,189,100,122,53,174,95,65,30,105,236,48,100,24,134,97,24,134,97,24,134,97,24,134,
97,24,134,97,152,5,83,126,62,158,181,206,148,232,84,123,53,246,188,143,175,225,182,152,115,212,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,202,243,215,159,109,108,37,204,35,43,250,60,
207,218,27,214,53,167,84,74,95,98,216,220,189,220,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,148,31,143,231,156,140,142,190,151,112,230,116,140,225,232,57,33,61,114,162,219,111,12,195,
48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,246,136,122,93,117,27,209,28,189,144,115,73,233,188,206,189,244,97,233,227,58,34,90,61,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,
41,143,231,239,30,213,17,117,164,114,108,179,57,125,43,183,230,174,184,26,205,163,81,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,107,230,253,227,107,166,69,207,208,232,57,31,93,235,53,178,
59,210,255,101,133,133,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,222,131,57,122,82,116,79,137,110,167,93,177,245,171,225,220,147,59,250,107,111,84,51,12,195,48,12,195,48,12,195,48,12,
195,48,12,195,48,204,146,153,189,233,136,168,49,206,22,173,122,191,221,198,236,116,228,145,20,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,171,38,189,253,253,204,115,59,97,79,236,152,155,10,
243,113,126,239,101,175,81,191,143,163,143,78,247,110,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,172,152,247,143,175,246,24,91,68,173,219,75,166,87,227,250,21,228,145,198,14,67,134,97,24,
134,97,24,134,97,24,134,97,24,134,97,24,134,89,48,229,231,227,89,235,76,137,78,181,87,99,207,251,248,26,110,139,57,71,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,166,60,127,253,217,198,
86,194,60,178,162,207,243,172,189,97,93,115,74,165,244,37,134,205,221,203,157,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,249,241,120,206,201,232,232,123,9,103,78,199,24,142,158,19,210,
35,39,186,253,198,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,143,168,215,85,183,17,205,209,11,57,151,148,206,235,220,75,31,150,62,174,35,162,213,51,195,48,12,195,48,12,195,48,12,195,48,
12,195,48,12,195,44,153,242,120,254,238,81,29,81,71,42,199,54,155,211,183,114,107,238,138,171,209,60,26,213,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,102,222,63,190,102,90,244,12,141,158,
243,209,181,94,35,187,35,253,95,86,88,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,236,61,152,163,39,69,247,148,232,118,218,21,91,191,26,206,61,185,163,191,246,70,53,195,48,12,195,48,12,
195,48,12,195,48,12,195,48,12,195,44,153,217,155,142,136,26,227,108,209,170,247,219,109,204,78,71,30,73,209,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,106,210,219,223,207,60,183,19,246,196,
142,185,169,48,31,231,247,94,246,26,245,251,56,250,232,116,239,86,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,138,121,255,248,106,143,177,69,212,186,189,100,122,53,174,95,65,30,105,236,48,
100,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,5,83,126,62,158,181,206,148,232,84,123,53,246,188,143,175,225,182,152,115,212,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,202,
243,215,159,109,108,37,204,35,43,250,60,207,218,27,214,53,167,84,74,95,98,216,220,189,220,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,148,31,143,231,156,140,142,190,151,112,230,116,140,
225,232,57,33,61,114,162,219,111,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,246,136,122,93,117,27,209,28,189,144,115,73,233,188,206,189,244,97,233,227,58,34,90,61,51,12,195,48,12,195,
48,12,195,48,12,195,48,12,195,48,204,146,41,143,231,239,30,213,17,117,164,114,108,179,57,125,43,183,230,174,184,26,205,163,81,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,107,230,253,227,107,
166,69,207,208,232,57,31,93,235,53,178,59,210,255,101,133,133,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,222,131,57,122,82,116,79,137,110,167,93,177,245,171,225,220,147,59,250,107,111,
84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,153,189,233,136,168,49,206,22,173,122,191,221,198,236,116,228,145,20,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,171,38,189,
253,253,204,115,59,97,79,236,152,155,10,243,113,126,239,101,175,81,191,143,163,143,78,247,110,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,172,152,247,143,175,246,24,91,68,173,219,75,166,87,
227,250,21,228,145,198,14,67,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,48,229,231,227,89,235,76,137,78,181,87,99,207,251,248,26,110,139,57,71,205,48,12,195,48,12,195,48,12,195,48,12,195,
48,12,195,48,75,166,60,127,253,217,198,86,194,60,178,162,207,243,172,189,97,93,115,74,165,244,37,134,205,221,203,157,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,249,241,120,206,201,232,
232,123,9,103,78,199,24,142,158,19,210,35,39,186,253,198,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,143,168,215,85,183,17,205,209,11,57,151,148,206,235,220,75,31,150,62,174,35,162,213,
51,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,242,120,254,238,81,29,81,71,42,199,54,155,211,183,114,107,238,138,171,209,60,26,213,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,
179,102,222,63,190,102,90,244,12,141,158,243,209,181,94,35,187,35,253,95,86,88,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,236,61,152,163,39,69,247,148,232,118,218,21,91,191,26,206,61,
185,163,191,246,70,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,217,155,142,136,26,227,108,209,170,247,219,109,204,78,71,30,73,209,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,
12,179,106,210,219,223,207,60,183,19,246,196,142,185,169,48,31,231,247,94,246,26,245,251,56,250,232,116,239,86,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,138,121,255,248,106,143,177,69,212,
186,189,100,122,53,174,95,65,30,105,236,48,100,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,5,83,126,62,158,181,206,148,232,84,123,53,246,188,143,175,225,182,152,115,212,12,195,48,12,195,48,12,
195,48,12,195,48,12,195,48,12,179,100,202,243,215,159,109,108,37,204,35,43,250,60,207,218,27,214,53,167,84,74,95,98,216,220,189,220,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,148,31,
143,231,156,140,142,190,151,112,230,116,140,225,232,57,33,61,114,162,219,111,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,246,136,122,93,117,27,209,28,189,144,115,73,233,188,206,189,244,
97,233,227,58,34,90,61,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,143,231,239,30,213,17,117,164,114,108,179,57,125,43,183,230,174,184,26,205,163,81,205,48,12,195,48,12,195,48,12,195,
48,12,195,48,12,195,48,107,230,253,227,107,166,69,207,208,232,57,31,93,235,53,178,59,210,255,101,133,133,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,222,131,57,122,82,116,79,137,110,167,
93,177,245,171,225,220,147,59,250,107,111,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,153,189,233,136,168,49,206,22,173,122,191,221,198,236,116,228,145,20,205,48,12,195,48,12,195,48,
12,195,48,12,195,48,12,195,48,171,38,189,253,253,204,115,59,97,79,236,152,155,10,243,113,126,239,101,175,81,191,143,163,143,78,247,110,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,172,152,
247,143,175,246,24,91,68,173,219,75,166,87,227,250,21,228,145,198,14,67,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,48,229,231,227,89,235,76,137,78,181,87,99,207,251,248,26,110,139,57,71,
205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,166,60,127,253,217,198,86,194,60,178,162,207,243,172,189,97,93,115,74,165,244,37,134,205,221,203,157,97,24,134,97,24,134,97,24,134,97,24,134,
97,24,134,97,150,76,249,241,120,206,201,232,232,123,9,103,78,199,24,142,158,19,210,35,39,186,253,198,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,143,168,215,85,183,17,205,209,11,57,151,
148,206,235,220,75,31,150,62,174,35,162,213,51,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,242,120,254,238,81,29,81,71,42,199,54,155,211,183,114,107,238,138,171,209,60,26,213,12,195,48,
12,195,48,12,195,48,12,195,48,12,195,48,12,179,102,222,63,190,102,90,244,12,141,158,243,209,181,94,35,187,35,253,95,86,88,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,236,61,152,163,39,
69,247,148,232,118,218,21,91,191,26,206,61,185,163,191,246,70,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,217,155,142,136,26,227,108,209,170,247,219,109,204,78,71,30,73,209,12,195,
48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,106,210,219,223,207,60,183,19,246,196,142,185,169,48,31,231,247,94,246,26,245,251,56,250,232,116,239,86,51,12,195,48,12,195,48,12,195,48,12,195,48,12,
195,48,204,138,121,255,248,106,143,177,69,212,186,189,100,122,53,174,95,65,30,105,236,48,100,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,5,83,126,62,158,181,206,148,232,84,123,53,246,188,143,
175,225,182,152,115,212,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,202,243,215,159,109,108,37,204,35,43,250,60,207,218,27,214,53,167,84,74,95,98,216,220,189,220,25,134,97,24,134,97,24,
134,97,24,134,97,24,134,97,24,102,201,148,31,143,231,156,140,142,190,151,112,230,116,140,225,232,57,33,61,114,162,219,111,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,246,136,122,93,117,
27,209,28,189,144,115,73,233,188,206,189,244,97,233,227,58,34,90,61,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,143,231,239,30,213,17,117,164,114,108,179,57,125,43,183,230,174,184,
26,205,163,81,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,107,230,253,227,107,166,69,207,208,232,57,31,93,235,53,178,59,210,255,101,133,133,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,
97,150,204,222,131,57,122,82,116,79,137,110,167,93,177,245,171,225,220,147,59,250,107,111,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,153,189,233,136,168,49,206,22,173,122,191,221,
198,236,116,228,145,20,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,171,38,189,253,253,204,115,59,97,79,236,152,155,10,243,113,126,239,101,175,81,191,143,163,143,78,247,110,53,195,48,12,195,
48,12,195,48,12,195,48,12,195,48,12,195,172,152,247,143,175,246,24,91,68,173,219,75,166,87,227,250,21,228,145,198,14,67,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,48,229,231,227,89,235,76,
137,78,181,87,99,207,251,248,26,110,139,57,71,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,166,60,127,253,217,198,86,194,60,178,162,207,243,172,189,97,93,115,74,165,244,37,134,205,221,203,
157,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,249,241,120,206,201,232,232,123,9,103,78,199,24,142,158,19,210,35,39,186,253,198,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,
102,143,168,215,85,183,17,205,209,11,57,151,148,206,235,220,75,31,150,62,174,35,162,213,51,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,242,120,254,238,81,29,81,71,42,199,54,155,211,183,
114,107,238,138,171,209,60,26,213,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,102,222,63,190,102,90,244,12,141,158,243,209,181,94,35,187,35,253,95,86,88,24,134,97,24,134,97,24,134,97,24,134,
97,24,134,97,24,102,201,236,61,152,163,39,69,247,148,232,118,218,21,91,191,26,206,61,185,163,191,246,70,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,217,155,142,136,26,227,108,209,170,
247,219,109,204,78,71,30,73,209,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,106,210,219,223,207,60,183,19,246,196,142,185,169,48,31,231,247,94,246,26,245,251,56,250,232,116,239,86,51,12,195,
48,12,195,48,12,195,48,12,195,48,12,195,48,204,138,121,255,248,106,143,177,69,212,186,189,100,122,53,174,95,65,30,105,236,48,100,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,5,83,126,62,158,181,
206,148,232,84,123,53,246,188,143,175,225,182,152,115,212,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,202,243,215,159,109,108,37,204,35,43,250,60,207,218,27,214,53,167,84,74,95,98,216,
220,189,220,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,148,31,143,231,156,140,142,190,151,112,230,116,140,225,232,57,33,61,114,162,219,111,12,195,48,12,195,48,12,195,48,12,195,48,12,
195,48,12,179,100,246,136,122,93,117,27,209,28,189,144,115,73,233,188,206,189,244,97,233,227,58,34,90,61,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,143,231,239,30,213,17,117,164,114,
108,179,57,125,43,183,230,174,184,26,205,163,81,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,107,230,253,227,107,166,69,207,208,232,57,31,93,235,53,178,59,210,255,101,133,133,97,24,134,97,
24,134,97,24,134,97,24,134,97,24,134,97,150,204,222,131,57,122,82,116,79,137,110,167,93,177,245,171,225,220,147,59,250,107,111,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,153,189,233,
136,168,49,206,22,173,122,191,221,198,236,116,228,145,20,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,171,38,189,253,253,204,115,59,97,79,236,152,155,10,243,113,126,239,101,175,81,191,143,
163,143,78,247,110,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,172,152,247,143,175,246,24,91,68,173,219,75,166,87,227,250,21,228,145,198,14,67,134,97,24,134,97,24,134,97,24,134,97,24,134,
97,24,134,89,48,229,231,227,89,235,76,137,78,181,87,99,207,251,248,26,110,139,57,71,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,166,60,127,253,217,198,86,194,60,178,162,207,243,172,189,
97,93,115,74,165,244,37,134,205,221,203,157,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,249,241,120,206,201,232,232,123,9,103,78,199,24,142,158,19,210,35,39,186,253,198,48,12,195,48,12,
195,48,12,195,48,12,195,48,12,195,48,75,102,143,168,215,85,183,17,205,209,11,57,151,148,206,235,220,75,31,150,62,174,35,162,213,51,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,242,120,
254,238,81,29,81,71,42,199,54,155,211,183,114,107,238,138,171,209,60,26,213,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,102,222,63,190,102,90,244,12,141,158,243,209,181,94,35,187,35,253,95,
86,88,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,236,61,152,163,39,69,247,148,232,118,218,21,91,191,26,206,61,185,163,191,246,70,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,
195,44,153,217,155,142,136,26,227,108,209,170,247,219,109,204,78,71,30,73,209,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,106,210,219,223,207,60,183,19,246,196,142,185,169,48,31,231,247,94,
246,26,245,251,56,250,232,116,239,86,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,138,121,255,248,106,143,177,69,212,186,189,100,122,53,174,95,65,30,105,236,48,100,24,134,97,24,134,97,24,134,
97,24,134,97,24,134,97,152,5,83,126,62,158,181,206,148,232,84,123,53,246,188,143,175,225,182,152,115,212,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,202,243,215,159,109,108,37,204,35,
43,250,60,207,218,27,214,53,167,84,74,95,98,216,220,189,220,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,148,31,143,231,156,140,142,190,151,112,230,116,140,225,232,57,33,61,114,162,219,
111,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,246,136,122,93,117,27,209,28,189,144,115,73,233,188,206,189,244,97,233,227,58,34,90,61,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,
48,204,146,41,143,231,239,30,213,17,117,164,114,108,179,57,125,43,183,230,174,184,26,205,163,81,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,107,230,253,227,107,166,69,207,208,232,57,31,93,
235,53,178,59,210,255,101,133,133,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,222,131,57,122,82,116,79,137,110,167,93,177,245,171,225,220,147,59,250,107,111,84,51,12,195,48,12,195,48,
12,195,48,12,195,48,12,195,48,204,146,153,189,233,136,168,49,206,22,173,122,191,221,198,236,116,228,145,20,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,171,38,189,253,253,204,115,59,97,79,
236,152,155,10,243,113,126,239,101,175,81,191,143,163,143,78,247,110,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,172,152,247,143,175,246,24,91,68,173,219,75,166,87,227,250,21,228,145,198,
14,67,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,48,229,231,227,89,235,76,137,78,181,87,99,207,251,248,26,110,139,57,71,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,166,60,
127,253,217,198,86,194,60,178,162,207,243,172,189,97,93,115,74,165,244,37,134,205,221,203,157,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,249,241,120,206,201,232,232,123,9,103,78,199,24,
142,158,19,210,35,39,186,253,198,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,143,168,215,85,183,17,205,209,11,57,151,148,206,235,220,75,31,150,62,174,35,162,213,51,195,48,12,195,48,12,
195,48,12,195,48,12,195,48,12,195,44,153,242,120,254,238,81,29,81,71,42,199,54,155,211,183,114,107,238,138,171,209,60,26,213,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,102,222,63,190,102,
90,244,12,141,158,243,209,181,94,35,187,35,253,95,86,88,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,236,61,152,163,39,69,247,148,232,118,218,21,91,191,26,206,61,185,163,191,246,70,53,
195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,217,155,142,136,26,227,108,209,170,247,219,109,204,78,71,30,73,209,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,106,210,219,223,
207,60,183,19,246,196,142,185,169,48,31,231,247,94,246,26,245,251,56,250,232,116,239,86,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,138,121,255,248,106,143,177,69,212,186,189,100,122,53,174,
95,65,30,105,236,48,100,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,5,83,126,62,158,181,206,148,232,84,123,53,246,188,143,175,225,182,152,115,212,12,195,48,12,195,48,12,195,48,12,195,48,12,195,
48,12,179,100,202,243,215,159,109,108,37,204,35,43,250,60,207,218,27,214,53,167,84,74,95,98,216,220,189,220,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,148,31,143,231,156,140,142,190,
151,112,230,116,140,225,232,57,33,61,114,162,219,111,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,246,136,122,93,117,27,209,28,189,144,115,73,233,188,206,189,244,97,233,227,58,34,90,61,
51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,143,231,239,30,213,17,117,164,114,108,179,57,125,43,183,230,174,184,26,205,163,81,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,
48,107,230,253,227,107,166,69,207,208,232,57,31,93,235,53,178,59,210,255,101,133,133,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,222,131,57,122,82,116,79,137,110,167,93,177,245,171,225,
220,147,59,250,107,111,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,153,189,233,136,168,49,206,22,173,122,191,221,198,236,116,228,145,20,205,48,12,195,48,12,195,48,12,195,48,12,195,
48,12,195,48,171,38,189,253,253,204,115,59,97,79,236,152,155,10,243,113,126,239,101,175,81,191,143,163,143,78,247,110,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,172,152,247,143,175,246,24,
91,68,173,219,75,166,87,227,250,21,228,145,198,14,67,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,48,229,231,227,89,235,76,137,78,181,87,99,207,251,248,26,110,139,57,71,205,48,12,195,48,12,
195,48,12,195,48,12,195,48,12,195,48,75,166,60,127,253,217,198,86,194,60,178,162,207,243,172,189,97,93,115,74,165,244,37,134,205,221,203,157,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,
249,241,120,206,201,232,232,123,9,103,78,199,24,142,158,19,210,35,39,186,253,198,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,143,168,215,85,183,17,205,209,11,57,151,148,206,235,220,75,
31,150,62,174,35,162,213,51,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,242,120,254,238,81,29,81,71,42,199,54,155,211,183,114,107,238,138,171,209,60,26,213,12,195,48,12,195,48,12,195,
48,12,195,48,12,195,48,12,179,102,222,63,190,102,90,244,12,141,158,243,209,181,94,35,187,35,253,95,86,88,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,236,61,152,163,39,69,247,148,232,118,
218,21,91,191,26,206,61,185,163,191,246,70,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,217,155,142,136,26,227,108,209,170,247,219,109,204,78,71,30,73,209,12,195,48,12,195,48,12,195,
48,12,195,48,12,195,48,12,179,106,210,219,223,207,60,183,19,246,196,142,185,169,48,31,231,247,94,246,26,245,251,56,250,232,116,239,86,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,138,121,255,
248,106,143,177,69,212,186,189,100,122,53,174,95,65,30,105,236,48,100,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,5,83,126,62,158,181,206,148,232,84,123,53,246,188,143,175,225,182,152,115,212,
12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,202,243,215,159,109,108,37,204,35,43,250,60,207,218,27,214,53,167,84,74,95,98,216,220,189,220,25,134,97,24,134,97,24,134,97,24,134,97,24,134,
97,24,102,201,148,31,143,231,156,140,142,190,151,112,230,116,140,225,232,57,33,61,114,162,219,111,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,246,136,122,93,117,27,209,28,189,144,115,
73,233,188,206,189,244,97,233,227,58,34,90,61,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,143,231,239,30,213,17,117,164,114,108,179,57,125,43,183,230,174,184,26,205,163,81,205,48,12,
195,48,12,195,48,12,195,48,12,195,48,12,195,48,107,230,253,227,107,166,69,207,208,232,57,31,93,235,53,178,59,210,255,101,133,133,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,222,131,57,
122,82,116,79,137,110,167,93,177,245,171,225,220,147,59,250,107,111,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,153,189,233,136,168,49,206,22,173,122,191,221,198,236,116,228,145,20,
205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,171,38,189,253,253,204,115,59,97,79,236,152,155,10,243,113,126,239,101,175,81,191,143,163,143,78,247,110,53,195,48,12,195,48,12,195,48,12,195,48,
12,195,48,12,195,172,152,247,143,175,246,24,91,68,173,219,75,166,87,227,250,21,228,145,198,14,67,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,48,229,231,227,89,235,76,137,78,181,87,99,207,
251,248,26,110,139,57,71,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,166,60,127,253,217,198,86,194,60,178,162,207,243,172,189,97,93,115,74,165,244,37,134,205,221,203,157,97,24,134,97,24,
134,97,24,134,97,24,134,97,24,134,97,150,76,249,241,120,206,201,232,232,123,9,103,78,199,24,142,158,19,210,35,39,186,253,198,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,143,168,215,85,
183,17,205,209,11,57,151,148,206,235,220,75,31,150,62,174,35,162,213,51,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,242,120,254,238,81,29,81,71,42,199,54,155,211,183,114,107,238,138,171,
209,60,26,213,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,102,222,63,190,102,90,244,12,141,158,243,209,181,94,35,187,35,253,95,86,88,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,
201,236,61,152,163,39,69,247,148,232,118,218,21,91,191,26,206,61,185,163,191,246,70,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,217,155,142,136,26,227,108,209,170,247,219,109,204,78,
71,30,73,209,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,106,210,219,223,207,60,183,19,246,196,142,185,169,48,31,231,247,94,246,26,245,251,56,250,232,116,239,86,51,12,195,48,12,195,48,12,
195,48,12,195,48,12,195,48,204,138,121,255,248,106,143,177,69,212,186,189,100,122,53,174,95,65,30,105,236,48,100,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,5,83,126,62,158,181,206,148,232,84,
123,53,246,188,143,175,225,182,152,115,212,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,202,243,215,159,109,108,37,204,35,43,250,60,207,218,27,214,53,167,84,74,95,98,216,220,189,220,25,
134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,148,31,143,231,156,140,142,190,151,112,230,116,140,225,232,57,33,61,114,162,219,111,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,
246,136,122,93,117,27,209,28,189,144,115,73,233,188,206,189,244,97,233,227,58,34,90,61,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,143,231,239,30,213,17,117,164,114,108,179,57,125,
43,183,230,174,184,26,205,163,81,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,107,230,253,227,107,166,69,207,208,232,57,31,93,235,53,178,59,210,255,101,133,133,97,24,134,97,24,134,97,24,134,
97,24,134,97,24,134,97,150,204,222,131,57,122,82,116,79,137,110,167,93,177,245,171,225,220,147,59,250,107,111,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,153,189,233,136,168,49,206,
22,173,122,191,221,198,236,116,228,145,20,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,171,38,189,253,253,204,115,59,97,79,236,152,155,10,243,113,126,239,101,175,81,191,143,163,143,78,247,
110,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,172,152,247,143,175,246,24,91,68,173,219,75,166,87,227,250,21,228,145,198,14,67,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,48,
229,231,227,89,235,76,137,78,181,87,99,207,251,248,26,110,139,57,71,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,166,60,127,253,217,198,86,194,60,178,162,207,243,172,189,97,93,115,74,165,
244,37,134,205,221,203,157,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,249,241,120,206,201,232,232,123,9,103,78,199,24,142,158,19,210,35,39,186,253,198,48,12,195,48,12,195,48,12,195,48,
12,195,48,12,195,48,75,102,143,168,215,85,183,17,205,209,11,57,151,148,206,235,220,75,31,150,62,174,35,162,213,51,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,242,120,254,238,81,29,81,
71,42,199,54,155,211,183,114,107,238,138,171,209,60,26,213,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,102,222,63,190,102,90,244,12,141,158,243,209,181,94,35,187,35,253,95,86,88,24,134,97,
24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,236,61,152,163,39,69,247,148,232,118,218,21,91,191,26,206,61,185,163,191,246,70,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,217,155,
142,136,26,227,108,209,170,247,219,109,204,78,71,30,73,209,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,106,210,219,223,207,60,183,19,246,196,142,185,169,48,31,231,247,94,246,26,245,251,56,
250,232,116,239,86,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,138,121,255,248,106,143,177,69,212,186,189,100,122,53,174,95,65,30,105,236,48,100,24,134,97,24,134,97,24,134,97,24,134,97,24,
134,97,152,5,83,126,62,158,181,206,148,232,84,123,53,246,188,143,175,225,182,152,115,212,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,202,243,215,159,109,108,37,204,35,43,250,60,207,218,
27,214,53,167,84,74,95,98,216,220,189,220,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,148,31,143,231,156,140,142,190,151,112,230,116,140,225,232,57,33,61,114,162,219,111,12,195,48,12,
195,48,12,195,48,12,195,48,12,195,48,12,179,100,246,136,122,93,117,27,209,28,189,144,115,73,233,188,206,189,244,97,233,227,58,34,90,61,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,143,
231,239,30,213,17,117,164,114,108,179,57,125,43,183,230,174,184,26,205,163,81,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,107,230,253,227,107,166,69,207,208,232,57,31,93,235,53,178,59,210,
255,101,133,133,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,222,131,57,122,82,116,79,137,110,167,93,177,245,171,225,220,147,59,250,107,111,84,51,12,195,48,12,195,48,12,195,48,12,195,48,
12,195,48,204,146,153,189,233,136,168,49,206,22,173,122,191,221,198,236,116,228,145,20,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,171,38,189,253,253,204,115,59,97,79,236,152,155,10,243,113,
126,239,101,175,81,191,143,163,143,78,247,110,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,172,152,247,143,175,246,24,91,68,173,219,75,166,87,227,250,21,228,145,198,14,67,134,97,24,134,97,
24,134,97,24,134,97,24,134,97,24,134,89,48,229,231,227,89,235,76,137,78,181,87,99,207,251,248,26,110,139,57,71,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,166,60,127,253,217,198,86,194,
60,178,162,207,243,172,189,97,93,115,74,165,244,37,134,205,221,203,157,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,249,241,120,206,201,232,232,123,9,103,78,199,24,142,158,19,210,35,39,
186,253,198,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,143,168,215,85,183,17,205,209,11,57,151,148,206,235,220,75,31,150,62,174,35,162,213,51,195,48,12,195,48,12,195,48,12,195,48,12,195,
48,12,195,44,153,242,120,254,238,81,29,81,71,42,199,54,155,211,183,114,107,238,138,171,209,60,26,213,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,102,222,63,190,102,90,244,12,141,158,243,209,
181,94,35,187,35,253,95,86,88,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,236,61,152,163,39,69,247,148,232,118,218,21,91,191,26,206,61,185,163,191,246,70,53,195,48,12,195,48,12,195,48,
12,195,48,12,195,48,12,195,44,153,217,155,142,136,26,227,108,209,170,247,219,109,204,78,71,30,73,209,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,106,210,219,223,207,60,183,19,246,196,142,
185,169,48,31,231,247,94,246,26,245,251,56,250,232,116,239,86,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,138,121,255,248,106,143,177,69,212,186,189,100,122,53,174,95,65,30,105,236,48,100,
24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,5,83,126,62,158,181,206,148,232,84,123,53,246,188,143,175,225,182,152,115,212,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,202,243,
215,159,109,108,37,204,35,43,250,60,207,218,27,214,53,167,84,74,95,98,216,220,189,220,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,148,31,143,231,156,140,142,190,151,112,230,116,140,225,
232,57,33,61,114,162,219,111,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,246,136,122,93,117,27,209,28,189,144,115,73,233,188,206,189,244,97,233,227,58,34,90,61,51,12,195,48,12,195,48,
12,195,48,12,195,48,12,195,48,204,146,41,143,231,239,30,213,17,117,164,114,108,179,57,125,43,183,230,174,184,26,205,163,81,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,107,230,253,227,107,
166,69,207,208,232,57,31,93,235,53,178,59,210,255,101,133,133,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,222,131,57,122,82,116,79,137,110,167,93,177,245,171,225,220,147,59,250,107,111,
84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,153,189,233,136,168,49,206,22,173,122,191,221,198,236,116,228,145,20,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,171,38,189,
253,253,204,115,59,97,79,236,152,155,10,243,113,126,239,101,175,81,191,143,163,143,78,247,110,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,172,152,247,143,175,246,24,91,68,173,219,75,166,87,
227,250,21,228,145,198,14,67,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,48,229,231,227,89,235,76,137,78,181,87,99,207,251,248,26,110,139,57,71,205,48,12,195,48,12,195,48,12,195,48,12,195,
48,12,195,48,75,166,60,127,253,217,198,86,194,60,178,162,207,243,172,189,97,93,115,74,165,244,37,134,205,221,203,157,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,76,249,241,120,206,201,232,
232,123,9,103,78,199,24,142,158,19,210,35,39,186,253,198,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,143,168,215,85,183,17,205,209,11,57,151,148,206,235,220,75,31,150,62,174,35,162,213,
51,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,242,120,254,238,81,29,81,71,42,199,54,155,211,183,114,107,238,138,171,209,60,26,213,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,
179,102,222,63,190,102,90,244,12,141,158,243,209,181,94,35,187,35,253,95,86,88,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,236,61,152,163,39,69,247,148,232,118,218,21,91,191,26,206,61,
185,163,191,246,70,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,217,155,142,136,26,227,108,209,170,247,219,109,204,78,71,30,73,209,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,
12,179,106,210,219,223,207,60,183,19,246,196,142,185,169,48,31,231,247,94,246,26,245,251,56,250,232,116,239,86,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,138,121,255,248,106,143,177,69,212,
186,189,100,122,53,174,95,65,30,105,236,48,100,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,5,83,126,62,158,181,206,148,232,84,123,53,246,188,143,175,225,182,152,115,212,12,195,48,12,195,48,12,
195,48,12,195,48,12,195,48,12,179,100,202,243,215,159,109,108,37,204,35,43,250,60,207,218,27,214,53,167,84,74,95,98,216,220,189,220,25,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,148,31,
143,231,156,140,142,190,151,112,230,116,140,225,232,57,33,61,114,162,219,111,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,246,136,122,93,117,27,209,28,189,144,115,73,233,188,206,189,244,
97,233,227,58,34,90,61,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,143,231,239,30,213,17,117,164,114,108,179,57,125,43,183,230,174,184,26,205,163,81,205,48,12,195,48,12,195,48,12,195,
48,12,195,48,12,195,48,107,230,253,227,107,166,69,207,208,232,57,31,93,235,53,178,59,210,255,101,133,133,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,150,204,222,131,57,122,82,116,79,137,110,167,
93,177,245,171,225,220,147,59,250,107,111,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,153,189,233,136,168,49,206,22,173,122,191,221,198,236,116,228,145,20,205,48,12,195,48,12,195,48,
12,195,48,12,195,48,12,195,48,171,38,189,253,253,204,115,59,97,79,236,152,155,10,243,113,126,239,101,175,81,191,143,163,143,78,247,110,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,172,152,
247,143,175,246,24,91,68,173,219,75,166,87,227,250,21,228,145,198,14,67,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,48,229,231,227,89,235,76,137,78,181,87,99,207,251,248,26,110,139,57,71,
205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,166,60,127,253,217,198,86,194,60,178,162,207,243,172,189,97,93,115,74,165,244,37,134,205,221,203,157,97,24,134,97,24,134,97,24,134,97,24,134,
97,24,134,97,150,76,249,241,120,206,201,232,232,123,9,103,78,199,24,142,158,19,210,35,39,186,253,198,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,75,102,143,168,215,85,183,17,205,209,11,57,151,
148,206,235,220,75,31,150,62,174,35,162,213,51,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,242,120,254,238,81,29,81,71,42,199,54,155,211,183,114,107,238,138,171,209,60,26,213,12,195,48,
12,195,48,12,195,48,12,195,48,12,195,48,12,179,102,222,63,190,102,90,244,12,141,158,243,209,181,94,35,187,35,253,95,86,88,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,102,201,236,61,152,163,39,
69,247,148,232,118,218,21,91,191,26,206,61,185,163,191,246,70,53,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,44,153,217,155,142,136,26,227,108,209,170,247,219,109,204,78,71,30,73,209,12,195,
48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,106,210,219,223,207,60,183,19,246,196,142,185,169,48,31,231,247,94,246,26,245,251,56,250,232,116,239,86,51,12,195,48,12,195,48,12,195,48,12,195,48,12,
195,48,204,138,121,255,248,106,143,177,69,212,186,189,100,122,53,174,95,65,30,105,236,48,100,24,134,97,24,134,97,24,134,97,24,134,97,24,134,97,152,5,83,126,62,158,181,206,148,232,84,123,53,246,188,143,
175,225,182,152,115,212,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,202,243,215,159,109,108,37,204,35,43,250,60,207,218,27,214,53,167,84,74,95,98,216,220,189,220,25,134,97,24,134,97,24,
134,97,24,134,97,24,134,97,24,102,201,148,31,143,231,156,140,142,190,151,112,230,116,140,225,232,57,33,61,114,162,219,111,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,12,179,100,246,136,122,93,117,
27,209,28,189,144,115,73,233,188,206,189,244,97,233,227,58,34,90,61,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,41,143,231,239,30,213,17,117,164,114,108,179,57,125,43,183,230,174,184,
26,205,163,81,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,107,230,253,227,107,166,69,207,208,232,57,31,93,235,53,178,59,210,255,101,133,133,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,
97,150,204,222,131,57,122,82,116,79,137,110,167,93,177,245,171,225,220,147,59,250,107,111,84,51,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,204,146,153,189,233,136,168,49,206,22,173,122,191,221,
198,236,116,228,145,20,205,48,12,195,48,12,195,48,12,195,48,12,195,48,12,195,48,171,38,189,253,253,204,115,59,97,79,236,152,155,10,243,113,126,239,101,175,81,191,143,163,143,78,247,110,53,195,48,12,195,
48,12,195,48,12,195,48,12,195,48,12,195,172,152,247,143,175,246,24,91,68,173,219,75,166,87,227,250,21,228,145,198,14,67,134,97,24,134,97,24,134,97,24,134,97,24,134,97,24,134,89,48,255,4,24,0,148,71,74,
209,81,42,143,156,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* JuceDemoPluginAudioProcessorEditor::uibg_png = (const char*) resource_JuceDemoPluginAudioProcessorEditor_uibg_png;
const int JuceDemoPluginAudioProcessorEditor::uibg_pngSize = 42225;

// JUCER_RESOURCE: off_png, 3044, "../off.png"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_off_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,19,0,0,0,15,8,6,0,0,0,6,68,244,44,0,0,0,9,112,72,89,115,0,0,11,
19,0,0,11,19,1,0,154,156,24,0,0,10,79,105,67,67,80,80,104,111,116,111,115,104,111,112,32,73,67,67,32,112,114,111,102,105,108,101,0,0,120,218,157,83,103,84,83,233,22,61,247,222,244,66,75,136,128,148,75,
111,82,21,8,32,82,66,139,128,20,145,38,42,33,9,16,74,136,33,161,217,21,81,193,17,69,69,4,27,200,160,136,3,142,142,128,140,21,81,44,12,138,10,216,7,228,33,162,142,131,163,136,138,202,251,225,123,163,107,
214,188,247,230,205,254,181,215,62,231,172,243,157,179,207,7,192,8,12,150,72,51,81,53,128,12,169,66,30,17,224,131,199,196,198,225,228,46,64,129,10,36,112,0,16,8,179,100,33,115,253,35,1,0,248,126,60,60,
43,34,192,7,190,0,1,120,211,11,8,0,192,77,155,192,48,28,135,255,15,234,66,153,92,1,128,132,1,192,116,145,56,75,8,128,20,0,64,122,142,66,166,0,64,70,1,128,157,152,38,83,0,160,4,0,96,203,99,98,227,0,80,
45,0,96,39,127,230,211,0,128,157,248,153,123,1,0,91,148,33,21,1,160,145,0,32,19,101,136,68,0,104,59,0,172,207,86,138,69,0,88,48,0,20,102,75,196,57,0,216,45,0,48,73,87,102,72,0,176,183,0,192,206,16,11,
178,0,8,12,0,48,81,136,133,41,0,4,123,0,96,200,35,35,120,0,132,153,0,20,70,242,87,60,241,43,174,16,231,42,0,0,120,153,178,60,185,36,57,69,129,91,8,45,113,7,87,87,46,30,40,206,73,23,43,20,54,97,2,97,154,
64,46,194,121,153,25,50,129,52,15,224,243,204,0,0,160,145,21,17,224,131,243,253,120,206,14,174,206,206,54,142,182,14,95,45,234,191,6,255,34,98,98,227,254,229,207,171,112,64,0,0,225,116,126,209,254,44,
47,179,26,128,59,6,128,109,254,162,37,238,4,104,94,11,160,117,247,139,102,178,15,64,181,0,160,233,218,87,243,112,248,126,60,60,69,161,144,185,217,217,229,228,228,216,74,196,66,91,97,202,87,125,254,103,
194,95,192,87,253,108,249,126,60,252,247,245,224,190,226,36,129,50,93,129,71,4,248,224,194,204,244,76,165,28,207,146,9,132,98,220,230,143,71,252,183,11,255,252,29,211,34,196,73,98,185,88,42,20,227,81,
18,113,142,68,154,140,243,50,165,34,137,66,146,41,197,37,210,255,100,226,223,44,251,3,62,223,53,0,176,106,62,1,123,145,45,168,93,99,3,246,75,39,16,88,116,192,226,247,0,0,242,187,111,193,212,40,8,3,128,
104,131,225,207,119,255,239,63,253,71,160,37,0,128,102,73,146,113,0,0,94,68,36,46,84,202,179,63,199,8,0,0,68,160,129,42,176,65,27,244,193,24,44,192,6,28,193,5,220,193,11,252,96,54,132,66,36,196,194,66,
16,66,10,100,128,28,114,96,41,172,130,66,40,134,205,176,29,42,96,47,212,64,29,52,192,81,104,134,147,112,14,46,194,85,184,14,61,112,15,250,97,8,158,193,40,188,129,9,4,65,200,8,19,97,33,218,136,1,98,138,
88,35,142,8,23,153,133,248,33,193,72,4,18,139,36,32,201,136,20,81,34,75,145,53,72,49,82,138,84,32,85,72,29,242,61,114,2,57,135,92,70,186,145,59,200,0,50,130,252,134,188,71,49,148,129,178,81,61,212,12,
181,67,185,168,55,26,132,70,162,11,208,100,116,49,154,143,22,160,155,208,114,180,26,61,140,54,161,231,208,171,104,15,218,143,62,67,199,48,192,232,24,7,51,196,108,48,46,198,195,66,177,56,44,9,147,99,203,
177,34,172,12,171,198,26,176,86,172,3,187,137,245,99,207,177,119,4,18,129,69,192,9,54,4,119,66,32,97,30,65,72,88,76,88,78,216,72,168,32,28,36,52,17,218,9,55,9,3,132,81,194,39,34,147,168,75,180,38,186,
17,249,196,24,98,50,49,135,88,72,44,35,214,18,143,19,47,16,123,136,67,196,55,36,18,137,67,50,39,185,144,2,73,177,164,84,210,18,210,70,210,110,82,35,233,44,169,155,52,72,26,35,147,201,218,100,107,178,7,
57,148,44,32,43,200,133,228,157,228,195,228,51,228,27,228,33,242,91,10,157,98,64,113,164,248,83,226,40,82,202,106,74,25,229,16,229,52,229,6,101,152,50,65,85,163,154,82,221,168,161,84,17,53,143,90,66,173,
161,182,82,175,81,135,168,19,52,117,154,57,205,131,22,73,75,165,173,162,149,211,26,104,23,104,247,105,175,232,116,186,17,221,149,30,78,151,208,87,210,203,233,71,232,151,232,3,244,119,12,13,134,21,131,
199,136,103,40,25,155,24,7,24,103,25,119,24,175,152,76,166,25,211,139,25,199,84,48,55,49,235,152,231,153,15,153,111,85,88,42,182,42,124,21,145,202,10,149,74,149,38,149,27,42,47,84,169,170,166,170,222,
170,11,85,243,85,203,84,143,169,94,83,125,174,70,85,51,83,227,169,9,212,150,171,85,170,157,80,235,83,27,83,103,169,59,168,135,170,103,168,111,84,63,164,126,89,253,137,6,89,195,76,195,79,67,164,81,160,
177,95,227,188,198,32,11,99,25,179,120,44,33,107,13,171,134,117,129,53,196,38,177,205,217,124,118,42,187,152,253,29,187,139,61,170,169,161,57,67,51,74,51,87,179,82,243,148,102,63,7,227,152,113,248,156,
116,78,9,231,40,167,151,243,126,138,222,20,239,41,226,41,27,166,52,76,185,49,101,92,107,170,150,151,150,88,171,72,171,81,171,71,235,189,54,174,237,167,157,166,189,69,187,89,251,129,14,65,199,74,39,92,
39,71,103,143,206,5,157,231,83,217,83,221,167,10,167,22,77,61,58,245,174,46,170,107,165,27,161,187,68,119,191,110,167,238,152,158,190,94,128,158,76,111,167,222,121,189,231,250,28,125,47,253,84,253,109,
250,167,245,71,12,88,6,179,12,36,6,219,12,206,24,60,197,53,113,111,60,29,47,199,219,241,81,67,93,195,64,67,165,97,149,97,151,225,132,145,185,209,60,163,213,70,141,70,15,140,105,198,92,227,36,227,109,198,
109,198,163,38,6,38,33,38,75,77,234,77,238,154,82,77,185,166,41,166,59,76,59,76,199,205,204,205,162,205,214,153,53,155,61,49,215,50,231,155,231,155,215,155,223,183,96,90,120,90,44,182,168,182,184,101,
73,178,228,90,166,89,238,182,188,110,133,90,57,89,165,88,85,90,93,179,70,173,157,173,37,214,187,173,187,167,17,167,185,78,147,78,171,158,214,103,195,176,241,182,201,182,169,183,25,176,229,216,6,219,174,
182,109,182,125,97,103,98,23,103,183,197,174,195,238,147,189,147,125,186,125,141,253,61,7,13,135,217,14,171,29,90,29,126,115,180,114,20,58,86,58,222,154,206,156,238,63,125,197,244,150,233,47,103,88,207,
16,207,216,51,227,182,19,203,41,196,105,157,83,155,211,71,103,23,103,185,115,131,243,136,139,137,75,130,203,46,151,62,46,155,27,198,221,200,189,228,74,116,245,113,93,225,122,210,245,157,155,179,155,194,
237,168,219,175,238,54,238,105,238,135,220,159,204,52,159,41,158,89,51,115,208,195,200,67,224,81,229,209,63,11,159,149,48,107,223,172,126,79,67,79,129,103,181,231,35,47,99,47,145,87,173,215,176,183,165,
119,170,247,97,239,23,62,246,62,114,159,227,62,227,60,55,222,50,222,89,95,204,55,192,183,200,183,203,79,195,111,158,95,133,223,67,127,35,255,100,255,122,255,209,0,167,128,37,1,103,3,137,129,65,129,91,
2,251,248,122,124,33,191,142,63,58,219,101,246,178,217,237,65,140,160,185,65,21,65,143,130,173,130,229,193,173,33,104,200,236,144,173,33,247,231,152,206,145,206,105,14,133,80,126,232,214,208,7,97,230,
97,139,195,126,12,39,133,135,133,87,134,63,142,112,136,88,26,209,49,151,53,119,209,220,67,115,223,68,250,68,150,68,222,155,103,49,79,57,175,45,74,53,42,62,170,46,106,60,218,55,186,52,186,63,198,46,102,
89,204,213,88,157,88,73,108,75,28,57,46,42,174,54,110,108,190,223,252,237,243,135,226,157,226,11,227,123,23,152,47,200,93,112,121,161,206,194,244,133,167,22,169,46,18,44,58,150,64,76,136,78,56,148,240,
65,16,42,168,22,140,37,242,19,119,37,142,10,121,194,29,194,103,34,47,209,54,209,136,216,67,92,42,30,78,242,72,42,77,122,146,236,145,188,53,121,36,197,51,165,44,229,185,132,39,169,144,188,76,13,76,221,
155,58,158,22,154,118,32,109,50,61,58,189,49,131,146,145,144,113,66,170,33,77,147,182,103,234,103,230,102,118,203,172,101,133,178,254,197,110,139,183,47,30,149,7,201,107,179,144,172,5,89,45,10,182,66,
166,232,84,90,40,215,42,7,178,103,101,87,102,191,205,137,202,57,150,171,158,43,205,237,204,179,202,219,144,55,156,239,159,255,237,18,194,18,225,146,182,165,134,75,87,45,29,88,230,189,172,106,57,178,60,
113,121,219,10,227,21,5,43,134,86,6,172,60,184,138,182,42,109,213,79,171,237,87,151,174,126,189,38,122,77,107,129,94,193,202,130,193,181,1,107,235,11,85,10,229,133,125,235,220,215,237,93,79,88,47,89,223,
181,97,250,134,157,27,62,21,137,138,174,20,219,23,151,21,127,216,40,220,120,229,27,135,111,202,191,153,220,148,180,169,171,196,185,100,207,102,210,102,233,230,222,45,158,91,14,150,170,151,230,151,14,110,
13,217,218,180,13,223,86,180,237,245,246,69,219,47,151,205,40,219,187,131,182,67,185,163,191,60,184,188,101,167,201,206,205,59,63,84,164,84,244,84,250,84,54,238,210,221,181,97,215,248,110,209,238,27,123,
188,246,52,236,213,219,91,188,247,253,62,201,190,219,85,1,85,77,213,102,213,101,251,73,251,179,247,63,174,137,170,233,248,150,251,109,93,173,78,109,113,237,199,3,210,3,253,7,35,14,182,215,185,212,213,
29,210,61,84,82,143,214,43,235,71,14,199,31,190,254,157,239,119,45,13,54,13,85,141,156,198,226,35,112,68,121,228,233,247,9,223,247,30,13,58,218,118,140,123,172,225,7,211,31,118,29,103,29,47,106,66,154,
242,154,70,155,83,154,251,91,98,91,186,79,204,62,209,214,234,222,122,252,71,219,31,15,156,52,60,89,121,74,243,84,201,105,218,233,130,211,147,103,242,207,140,157,149,157,125,126,46,249,220,96,219,162,182,
123,231,99,206,223,106,15,111,239,186,16,116,225,210,69,255,139,231,59,188,59,206,92,242,184,116,242,178,219,229,19,87,184,87,154,175,58,95,109,234,116,234,60,254,147,211,79,199,187,156,187,154,174,185,
92,107,185,238,122,189,181,123,102,247,233,27,158,55,206,221,244,189,121,241,22,255,214,213,158,57,61,221,189,243,122,111,247,197,247,245,223,22,221,126,114,39,253,206,203,187,217,119,39,238,173,188,79,
188,95,244,64,237,65,217,67,221,135,213,63,91,254,220,216,239,220,127,106,192,119,160,243,209,220,71,247,6,133,131,207,254,145,245,143,15,67,5,143,153,143,203,134,13,134,235,158,56,62,57,57,226,63,114,
253,233,252,167,67,207,100,207,38,158,23,254,162,254,203,174,23,22,47,126,248,213,235,215,206,209,152,209,161,151,242,151,147,191,109,124,165,253,234,192,235,25,175,219,198,194,198,30,190,201,120,51,49,
94,244,86,251,237,193,119,220,119,29,239,163,223,15,79,228,124,32,127,40,255,104,249,177,245,83,208,167,251,147,25,147,147,255,4,3,152,243,252,99,51,45,219,0,0,0,4,103,65,77,65,0,0,177,142,124,251,81,
147,0,0,0,32,99,72,82,77,0,0,122,37,0,0,128,131,0,0,249,255,0,0,128,233,0,0,117,48,0,0,234,96,0,0,58,152,0,0,23,111,146,95,197,70,0,0,0,255,73,68,65,84,120,218,236,147,187,74,3,81,20,69,215,185,143,185,
51,68,34,248,3,146,66,108,252,255,223,81,2,73,97,33,67,50,115,231,113,31,199,94,196,65,72,97,225,42,119,177,96,21,91,84,149,91,97,184,33,127,87,230,190,14,135,195,163,214,82,232,188,195,34,212,178,98,
196,97,157,144,83,197,90,75,49,194,148,50,175,111,71,249,81,102,214,149,135,253,61,47,207,79,56,21,26,47,244,253,5,191,235,232,135,145,16,58,142,167,19,46,229,237,204,224,91,186,208,114,183,219,163,170,
180,190,161,214,138,69,200,57,227,189,39,165,196,90,242,118,166,245,134,138,50,140,23,226,165,199,178,99,28,175,84,7,49,14,88,4,81,197,137,217,150,197,24,145,162,156,207,103,202,50,51,205,3,31,125,207,
158,74,26,34,239,211,194,16,71,112,205,182,108,1,156,192,199,60,97,20,166,146,200,33,208,199,5,99,27,166,178,130,115,168,145,109,25,84,114,94,185,94,19,70,193,68,48,226,88,231,133,16,90,214,170,20,85,
204,55,153,242,127,167,95,243,57,0,141,185,128,141,137,17,228,67,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* JuceDemoPluginAudioProcessorEditor::off_png = (const char*) resource_JuceDemoPluginAudioProcessorEditor_off_png;
const int JuceDemoPluginAudioProcessorEditor::off_pngSize = 3044;

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

// JUCER_RESOURCE: on_red_png, 488, "../on_red.png"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_on_red_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,19,0,0,0,15,8,6,0,0,0,6,68,244,44,0,0,0,4,103,65,77,65,0,0,175,
200,55,5,138,233,0,0,0,25,116,69,88,116,83,111,102,116,119,97,114,101,0,65,100,111,98,101,32,73,109,97,103,101,82,101,97,100,121,113,201,101,60,0,0,1,122,73,68,65,84,120,218,172,84,75,74,3,65,20,236,110,
135,56,25,67,36,70,136,32,228,4,174,60,143,71,16,60,142,123,241,46,158,32,171,1,69,87,19,204,24,98,194,196,137,113,218,122,61,245,72,147,157,146,134,202,235,223,171,174,126,213,19,235,77,104,22,56,2,92,
20,21,251,173,137,240,19,69,159,144,72,98,7,56,6,50,246,59,156,119,123,68,91,96,67,84,64,205,254,54,161,18,73,60,1,78,129,51,70,33,77,185,174,77,20,124,145,100,1,124,48,26,85,230,168,72,8,46,128,49,227,
16,232,241,32,109,162,96,5,148,64,1,188,113,94,212,126,171,178,140,138,198,183,214,62,202,177,231,188,99,21,201,254,228,70,105,51,224,222,251,27,30,176,22,168,178,142,42,91,226,231,26,184,203,144,102,
81,206,52,53,85,89,154,172,219,53,211,245,218,140,188,55,15,152,31,180,156,114,131,119,194,185,136,76,14,29,138,162,75,217,54,192,118,36,10,89,29,252,182,65,153,140,231,8,203,150,108,24,25,230,212,77,
167,142,246,89,101,51,159,155,105,85,153,17,186,57,112,133,254,139,212,164,14,212,90,200,216,113,43,29,31,91,254,204,206,8,201,82,151,49,226,19,11,35,107,175,36,207,118,134,108,153,31,220,108,162,55,83,
214,124,56,57,11,173,238,228,180,124,198,113,210,46,151,204,147,252,38,38,91,208,238,80,143,137,217,221,67,72,166,162,54,122,165,253,118,185,96,94,32,179,190,221,223,99,49,255,243,206,10,142,87,170,172,
142,94,242,134,86,255,229,11,168,85,217,193,190,77,123,200,127,141,95,1,6,0,68,36,154,206,118,63,98,167,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* JuceDemoPluginAudioProcessorEditor::on_red_png = (const char*) resource_JuceDemoPluginAudioProcessorEditor_on_red_png;
const int JuceDemoPluginAudioProcessorEditor::on_red_pngSize = 488;

// JUCER_RESOURCE: on_yellow_png, 549, "../on_yellow.png"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_on_yellow_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,19,0,0,0,15,8,6,0,0,0,6,68,244,44,0,0,0,4,103,65,77,65,0,
0,175,200,55,5,138,233,0,0,0,25,116,69,88,116,83,111,102,116,119,97,114,101,0,65,100,111,98,101,32,73,109,97,103,101,82,101,97,100,121,113,201,101,60,0,0,1,183,73,68,65,84,120,218,148,84,75,82,194,64,
16,205,103,18,32,1,65,96,225,138,171,120,0,175,192,218,173,231,209,181,7,209,171,176,162,164,136,98,197,132,252,102,124,221,211,3,129,29,83,245,232,153,100,250,245,235,79,240,63,94,125,15,139,126,66,32,
232,89,135,235,165,123,232,156,125,124,214,70,9,17,217,24,24,0,137,236,99,121,30,92,17,181,64,45,40,128,138,246,159,111,65,171,68,9,57,166,192,20,152,139,37,210,161,188,119,139,148,28,133,228,0,100,98,
105,25,23,121,32,4,15,192,74,236,2,24,75,32,183,72,77,14,236,129,45,176,145,231,164,182,81,105,194,145,19,81,180,202,14,222,187,49,136,32,201,209,222,71,33,2,64,27,107,89,34,18,158,79,189,181,4,40,9,106,
57,101,101,113,79,153,55,136,112,24,91,167,16,111,171,6,197,67,200,166,181,231,188,180,100,211,148,239,239,4,129,90,204,78,100,164,110,65,42,98,144,45,103,214,57,66,33,254,80,165,24,246,8,13,67,220,140,
126,45,217,253,29,151,194,53,44,80,147,196,248,82,55,238,104,219,249,76,16,197,35,164,87,122,42,26,121,67,93,242,51,10,68,10,39,169,77,25,190,253,142,251,202,24,223,244,91,222,52,182,78,69,81,114,116,
213,150,156,38,61,35,165,132,170,182,181,131,111,45,126,154,187,249,147,243,198,205,204,30,103,142,78,105,241,52,251,150,40,247,206,133,39,208,10,66,238,106,33,254,90,125,101,39,50,154,151,237,238,219,
22,217,45,238,36,206,29,38,44,68,16,173,207,29,134,202,173,248,89,50,56,119,194,158,201,220,172,17,249,114,206,186,147,170,139,57,131,239,70,252,200,191,83,7,155,102,213,155,228,90,90,125,203,23,80,177,
50,185,80,247,38,185,20,178,155,190,77,86,70,93,144,11,100,27,33,187,249,95,227,233,69,155,127,1,6,0,63,195,209,69,145,104,234,249,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* JuceDemoPluginAudioProcessorEditor::on_yellow_png = (const char*) resource_JuceDemoPluginAudioProcessorEditor_on_yellow_png;
const int JuceDemoPluginAudioProcessorEditor::on_yellow_pngSize = 549;

// JUCER_RESOURCE: images1_jpg, 9168, "../../../Desktop/images (1).jpg"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_images1_jpg[] = { 255,216,255,224,0,16,74,70,73,70,0,1,1,0,0,1,0,1,0,0,255,219,0,132,0,9,6,7,16,18,18,17,16,16,16,16,18,16,18,18,
16,17,16,16,15,23,23,16,19,16,16,24,21,22,22,20,18,20,19,24,40,40,32,24,26,37,28,20,20,33,49,33,37,41,43,46,46,46,23,31,63,56,51,44,55,40,45,46,43,1,10,10,10,14,13,14,27,16,16,26,47,37,32,36,44,44,44,
44,44,44,46,52,44,44,44,44,44,44,44,44,44,44,44,44,44,52,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,55,44,44,44,255,192,0,17,8,0,145,1,63,3,1,17,0,2,17,1,3,17,1,255,196,0,
27,0,1,0,2,3,1,1,0,0,0,0,0,0,0,0,0,0,0,5,6,1,3,7,4,2,255,196,0,56,16,0,1,3,2,1,8,8,4,6,3,1,0,0,0,0,0,1,0,2,3,4,18,17,5,6,19,20,33,49,83,97,21,22,65,81,98,113,145,146,34,114,129,177,7,35,50,52,82,193,51,
66,161,36,255,196,0,27,1,1,0,2,3,1,1,0,0,0,0,0,0,0,0,0,0,0,4,5,1,3,6,2,7,255,196,0,51,17,0,1,3,3,2,5,3,4,2,2,2,2,3,0,0,0,0,1,2,3,4,17,18,5,20,19,49,81,82,145,33,65,97,21,34,51,113,6,52,35,50,22,129,36,
177,83,161,193,255,218,0,12,3,1,0,2,17,3,17,0,63,0,238,40,13,114,206,198,254,167,52,121,156,23,135,72,214,255,0,178,216,244,141,115,185,33,175,94,139,136,207,80,188,110,34,238,79,39,174,19,250,40,215,
162,226,51,212,38,226,46,228,242,56,79,232,163,94,139,136,207,80,155,136,187,147,200,225,63,162,141,122,46,35,61,66,110,34,238,79,35,132,254,138,53,232,184,140,245,9,184,139,185,60,142,19,250,40,215,162,
226,51,212,38,226,46,228,242,56,79,232,163,94,139,136,207,80,155,136,187,147,200,225,63,162,141,122,46,35,61,66,110,34,238,79,35,132,254,138,53,232,184,140,245,9,184,139,185,60,142,19,250,40,215,162,226,
51,212,38,226,46,228,242,56,79,232,163,94,139,136,207,80,155,136,187,147,200,225,63,162,141,122,46,35,61,66,110,34,238,79,35,132,254,138,53,232,184,140,245,9,184,139,185,60,142,19,250,40,215,162,226,51,
212,38,226,46,228,242,56,79,232,163,94,139,136,207,80,155,136,187,147,200,225,63,162,141,122,46,35,61,66,110,34,238,79,35,132,254,138,53,232,184,140,245,9,184,139,185,60,142,19,250,40,215,162,226,51,212,
38,226,46,228,242,56,79,232,163,94,139,136,207,80,155,136,187,147,200,225,63,162,141,122,46,35,61,66,110,34,238,79,35,132,254,138,53,232,184,140,245,9,184,139,185,60,142,19,250,40,215,162,226,51,212,38,
226,46,228,242,56,79,232,163,94,139,136,207,80,155,136,187,147,200,225,63,162,141,122,46,35,61,66,110,34,238,79,35,132,254,138,53,232,184,140,245,9,184,139,185,60,142,19,250,40,215,162,226,51,212,38,226,
46,228,242,56,79,232,163,94,139,136,207,80,155,136,187,147,200,225,63,162,141,122,46,35,61,66,110,34,238,79,35,132,254,138,53,232,184,140,245,9,184,139,185,60,142,19,250,40,215,162,226,51,212,38,226,46,
228,242,56,79,232,163,94,139,136,207,80,155,136,187,147,200,225,63,162,141,122,46,35,61,66,110,34,238,79,35,132,254,138,53,232,184,140,245,9,184,139,185,60,142,19,250,40,215,162,226,51,212,38,226,46,228,
242,56,79,232,163,94,139,136,207,80,155,136,187,147,200,225,63,162,141,122,46,35,61,66,110,34,238,79,35,132,254,138,111,107,129,218,8,35,188,45,168,168,169,116,60,42,91,153,149,147,4,102,94,202,122,8,
241,27,94,237,141,28,251,212,26,250,189,180,119,78,107,200,147,75,7,25,246,246,43,176,100,153,38,252,202,135,157,187,67,85,51,40,164,159,239,157,220,253,139,23,84,54,47,182,52,61,93,94,167,241,45,255,
0,75,167,249,53,239,101,29,94,167,241,39,210,233,254,70,246,81,213,234,127,18,125,46,159,228,111,101,29,94,167,241,39,210,233,254,70,246,81,213,234,127,18,125,46,159,228,111,101,29,94,167,241,39,210,233,
254,70,246,81,213,234,127,18,125,46,159,228,111,101,29,94,167,241,39,210,233,254,70,246,81,213,234,127,18,125,46,159,228,111,101,29,94,167,241,39,210,233,254,70,246,81,213,234,127,18,125,46,159,228,111,
101,29,94,167,241,39,210,233,254,70,246,81,213,234,127,18,125,46,159,228,111,101,29,94,167,241,39,210,233,254,70,246,81,213,234,127,18,125,46,159,228,111,101,29,94,167,241,39,210,233,254,70,246,81,213,
234,127,18,125,46,159,228,111,101,29,94,167,241,39,210,233,254,70,246,81,213,234,127,18,125,46,159,228,111,101,29,94,167,241,39,210,233,254,70,246,81,213,234,127,18,125,46,159,228,111,101,29,94,167,241,
39,210,233,254,70,246,81,213,234,127,18,125,46,159,228,111,101,29,94,167,241,39,210,233,254,70,246,81,213,234,127,18,125,46,159,228,111,101,29,94,167,241,39,210,233,254,70,246,81,213,234,127,18,125,46,
159,228,111,101,29,94,167,241,39,210,233,254,70,246,81,213,234,127,18,125,46,159,228,111,101,29,94,167,241,39,210,233,254,70,246,81,213,234,127,18,125,46,159,228,111,101,29,94,167,241,39,210,233,254,70,
246,81,213,234,127,18,125,46,159,228,111,101,29,94,167,241,39,210,233,254,70,246,81,213,234,127,18,125,46,159,228,111,101,62,95,155,176,97,178,224,86,23,75,130,222,151,9,91,47,185,231,142,89,168,222,13,
197,240,146,49,199,176,45,40,249,168,30,139,123,176,216,173,142,169,188,172,226,229,12,161,205,14,27,136,4,46,149,143,71,181,28,158,229,59,154,173,91,41,87,206,102,221,83,3,14,236,49,195,234,168,117,52,
202,170,54,175,34,206,143,210,7,185,9,27,212,219,145,236,98,244,184,176,189,46,44,47,75,139,11,210,226,194,244,184,176,189,46,44,47,75,139,11,210,226,194,244,184,176,189,46,44,47,75,139,11,210,226,194,
244,184,176,189,46,44,47,75,139,11,210,226,194,244,184,176,189,46,44,47,75,139,11,210,226,194,244,184,176,189,46,44,47,75,139,11,210,226,194,244,184,176,189,46,44,47,75,139,11,210,226,194,244,184,176,
189,46,44,47,75,139,11,210,226,194,244,184,176,189,46,44,47,75,139,11,210,226,199,147,43,52,58,23,131,216,9,250,168,213,136,142,133,200,189,13,176,46,50,33,239,205,87,19,77,30,60,199,253,82,244,183,42,
211,54,230,138,228,180,202,70,103,17,255,0,215,7,203,253,168,58,143,246,227,37,82,127,93,231,160,189,111,200,213,97,122,198,66,194,244,200,88,94,153,11,11,211,33,97,122,100,44,107,146,169,141,253,78,107,
124,206,11,210,93,121,33,133,178,115,62,117,248,184,140,245,11,54,119,65,116,234,5,124,92,70,122,132,179,186,11,167,83,112,144,118,16,124,142,43,198,70,108,47,76,133,133,233,144,176,189,50,22,23,166,66,
194,244,200,88,94,153,11,11,211,33,97,122,100,44,47,76,133,133,233,144,176,210,38,66,198,173,114,63,230,223,80,189,226,238,135,155,183,168,215,35,254,109,245,9,139,186,11,183,169,244,202,150,29,206,105,
250,133,133,201,57,161,148,178,242,83,238,245,231,35,54,23,166,66,194,244,200,88,94,153,11,11,211,33,97,122,100,44,124,77,56,107,75,142,224,49,43,211,110,229,178,24,91,34,93,72,78,185,82,127,34,167,125,
58,126,132,77,236,68,189,21,115,101,96,145,159,164,238,80,228,106,198,236,93,204,148,199,35,219,146,27,239,90,242,61,88,94,153,11,11,211,33,97,122,100,44,104,174,127,229,73,242,149,170,161,223,226,119,
232,217,18,125,233,251,36,115,79,246,204,243,119,221,76,210,127,170,210,61,127,231,82,47,57,143,254,168,126,95,237,64,212,255,0,183,31,232,149,69,248,30,125,25,23,188,143,54,49,122,198,66,194,244,200,
88,94,153,11,11,211,33,97,122,100,44,114,47,196,188,160,231,214,22,181,206,13,99,70,227,134,222,213,210,105,145,162,67,117,247,42,43,29,121,44,133,85,142,144,238,116,135,200,146,172,44,212,34,250,152,
116,146,3,129,116,128,243,36,37,154,190,200,46,164,142,73,206,26,170,103,7,71,43,136,199,107,92,113,4,119,45,50,211,71,42,89,200,108,100,207,103,37,59,54,64,203,76,170,133,179,51,180,96,225,220,238,213,
204,84,68,232,94,172,82,230,39,164,141,201,9,27,214,140,141,150,51,122,100,103,17,122,100,49,49,122,100,98,194,244,200,88,94,153,11,11,211,33,97,122,100,44,47,76,133,143,38,86,170,178,25,93,225,112,30,
120,45,244,201,156,173,111,201,170,117,198,53,83,147,233,92,118,151,59,111,50,187,60,90,158,199,49,146,245,51,249,152,99,140,152,119,237,88,251,126,7,220,97,179,60,109,15,120,250,149,149,107,87,154,32,
71,47,82,211,154,249,207,35,94,33,152,220,215,16,26,227,189,165,84,87,233,237,86,44,145,250,42,22,84,117,142,71,96,254,74,94,175,92,230,69,213,133,233,145,156,76,222,153,12,76,94,153,11,11,211,35,22,34,
115,174,174,202,89,118,237,35,0,167,105,205,206,161,168,69,173,118,48,169,204,26,204,72,29,228,15,85,214,170,219,212,231,17,47,232,117,250,8,196,112,197,24,24,90,193,143,154,227,42,164,202,85,83,167,167,
102,49,162,27,175,81,242,55,88,94,153,11,11,211,33,97,122,100,44,105,172,127,229,191,229,43,92,238,255,0,27,191,71,184,211,239,66,103,52,255,0,108,207,55,125,213,142,147,253,86,145,43,255,0,58,145,57,
210,127,244,195,242,255,0,106,191,85,254,211,63,68,186,31,192,227,73,145,120,200,245,97,164,88,200,88,105,19,33,97,164,76,133,134,145,50,22,48,102,3,105,220,54,149,155,170,250,11,88,225,121,114,160,201,
81,51,241,199,23,187,15,37,218,211,179,8,154,159,7,57,43,178,122,169,119,252,39,163,110,21,19,61,173,112,248,67,46,24,249,170,205,94,101,102,40,132,202,24,242,186,169,109,203,244,52,210,193,40,124,44,
4,48,144,230,128,11,79,126,42,170,158,178,70,200,150,95,114,116,180,237,86,41,195,136,192,145,188,3,134,61,235,174,40,78,159,248,85,118,175,57,59,180,141,183,203,13,171,158,214,149,51,109,139,109,58,248,
169,27,157,121,235,83,21,68,144,192,90,214,179,1,113,24,226,183,81,105,209,73,18,62,78,106,107,169,171,123,94,173,105,90,151,59,171,93,190,111,65,130,177,74,8,19,147,72,139,85,34,251,155,105,243,198,189,
152,91,48,250,140,87,151,105,244,238,230,211,41,85,42,114,82,249,153,185,218,106,238,142,64,27,43,70,56,143,246,10,143,80,161,219,253,205,228,165,149,45,79,23,237,94,102,220,248,203,83,210,197,28,144,
17,137,113,14,199,110,197,227,77,130,57,222,173,121,234,174,71,68,212,86,149,58,12,253,172,116,177,181,229,182,185,205,105,217,222,112,86,210,105,80,163,21,83,153,5,149,178,43,145,20,234,37,223,210,230,
50,46,108,83,115,219,59,159,76,230,69,1,26,76,49,121,59,112,29,138,227,78,161,73,218,175,147,151,177,2,174,165,99,84,107,121,145,89,191,157,89,70,170,118,66,194,221,167,23,28,55,55,181,75,168,160,167,
134,53,114,145,226,170,150,71,35,75,70,122,84,91,79,102,63,19,136,219,223,222,161,104,236,202,162,253,13,218,147,241,134,221,74,19,24,73,13,27,201,0,46,173,86,201,115,158,68,191,161,214,41,99,141,145,
198,205,27,14,12,110,56,129,191,5,197,207,84,254,34,217,125,206,162,24,27,130,122,20,252,250,165,137,174,141,241,180,49,206,6,224,55,31,162,187,209,234,95,43,92,142,246,42,245,40,27,26,162,167,185,90,
166,253,108,195,125,195,238,174,31,254,170,86,183,253,144,233,153,82,176,195,9,120,253,65,131,12,123,240,92,92,17,113,106,48,246,185,211,203,39,14,28,254,10,60,217,211,86,239,247,0,119,0,186,102,105,84,
205,246,40,157,168,78,190,231,156,101,218,140,113,210,28,86,221,132,22,182,38,189,220,189,79,117,22,118,84,48,139,200,123,123,70,237,138,52,218,68,15,79,179,209,77,241,106,50,181,126,239,84,47,20,117,
141,145,141,145,187,156,49,92,180,204,116,79,86,59,154,29,4,111,73,24,142,79,114,185,159,117,63,4,113,142,211,137,242,87,58,27,46,247,60,171,213,157,102,181,165,107,33,211,105,42,34,103,136,31,67,138,
189,169,147,135,19,156,84,192,204,228,68,58,140,210,109,62,139,134,115,174,167,88,214,217,15,141,34,243,145,155,13,34,100,44,52,137,144,176,210,38,66,198,170,167,252,15,249,74,241,43,191,198,239,209,233,
137,247,33,97,205,79,219,51,205,223,117,111,164,255,0,85,164,10,255,0,206,164,62,118,159,253,17,124,191,218,173,213,151,255,0,37,159,162,101,7,225,113,225,210,40,249,27,108,52,137,144,176,210,38,66,195,
72,153,11,13,34,100,44,120,178,221,102,142,9,93,224,32,121,144,183,210,183,137,51,91,242,106,157,113,141,84,226,96,147,180,239,59,215,120,115,37,227,53,115,178,10,90,97,11,154,76,151,18,227,223,220,169,
107,232,37,168,147,38,175,161,97,75,84,200,155,101,230,121,115,135,61,228,157,134,40,153,163,97,253,71,121,112,94,168,244,150,194,236,222,183,81,81,92,178,38,45,75,21,90,120,29,35,155,28,109,46,123,142,
0,5,108,231,35,83,39,114,32,34,42,173,144,236,249,191,147,53,74,104,225,63,172,252,79,60,215,27,168,85,113,165,85,246,58,10,72,120,108,177,26,51,111,39,177,239,158,165,224,200,227,142,14,112,3,209,73,
143,81,157,209,163,35,79,67,75,233,35,71,43,156,167,212,217,95,35,176,90,89,17,29,224,2,87,166,178,185,203,116,69,60,170,211,53,61,84,231,25,198,105,76,197,212,142,38,39,109,192,236,180,247,46,130,151,
141,195,180,201,101,42,230,195,47,177,125,9,175,195,72,11,170,94,70,230,51,18,161,107,14,70,193,101,247,36,80,37,229,45,89,249,29,244,146,31,225,180,42,77,38,75,84,181,58,150,117,204,188,42,189,14,85,
78,112,115,15,115,216,125,8,93,131,185,41,64,156,208,237,85,153,81,177,192,103,113,24,6,2,57,156,54,46,25,33,116,149,28,36,234,116,139,34,50,44,215,161,198,171,234,223,52,142,149,251,92,243,142,31,96,
23,109,20,109,137,136,196,228,135,58,247,171,220,174,83,170,102,38,70,20,180,250,87,143,206,155,110,221,237,111,98,230,117,74,222,35,241,111,36,45,232,169,241,109,215,154,145,249,237,81,115,163,103,241,
196,159,170,159,160,51,236,115,250,144,181,119,253,205,103,66,6,134,70,182,70,61,223,165,174,14,63,69,121,43,85,204,86,167,53,66,170,53,68,122,42,150,202,172,240,143,105,99,9,238,228,185,182,232,114,185,
126,231,88,187,93,86,54,167,218,133,95,41,229,23,206,251,223,217,184,119,5,127,73,72,202,102,96,194,162,162,161,211,187,39,18,25,169,146,221,52,173,121,4,71,25,184,158,194,123,148,125,74,173,176,196,173,
191,170,155,168,169,214,89,17,125,144,184,101,90,102,206,44,113,181,152,237,59,182,46,74,154,173,208,203,155,125,84,232,167,167,73,99,197,121,30,86,83,228,218,125,159,11,190,98,28,172,86,170,182,126,72,
191,250,32,164,20,209,115,84,35,242,205,118,78,146,55,53,160,53,248,124,37,163,181,76,163,101,123,94,138,228,244,247,185,30,165,212,142,98,162,47,169,77,43,161,41,142,139,144,91,109,52,56,246,183,21,196,
106,207,77,203,172,117,58,123,87,128,133,91,59,234,47,156,14,198,183,15,170,191,209,35,198,158,253,84,168,213,31,148,214,232,134,252,199,135,25,220,254,27,113,245,94,181,153,112,130,221,76,105,145,229,
45,250,23,3,34,227,114,58,91,13,34,100,44,52,137,144,176,210,38,66,194,244,200,88,215,81,39,194,239,34,188,72,239,177,79,76,79,185,11,86,106,126,217,158,110,251,171,221,39,250,173,43,43,255,0,58,144,89,
240,127,53,159,39,246,170,117,207,204,223,209,59,76,252,110,253,149,232,234,156,57,170,150,204,228,39,172,104,167,161,149,131,183,98,220,147,162,243,53,172,106,110,19,3,218,182,35,209,79,24,153,189,103,
33,97,122,100,44,86,179,254,174,218,107,49,218,242,63,226,185,208,217,157,70,93,10,253,73,216,197,110,167,54,141,152,144,209,188,144,7,154,236,21,108,151,40,17,47,232,90,89,152,53,100,3,240,237,24,170,
165,214,32,69,177,49,40,100,83,217,73,248,115,49,219,36,204,104,237,29,171,76,154,228,73,254,169,115,219,116,231,175,53,45,217,27,33,210,209,143,203,109,242,127,55,109,32,242,84,149,122,156,147,115,95,
78,133,140,20,109,143,145,19,158,89,200,232,26,26,204,52,178,99,180,255,0,168,91,116,170,29,211,149,239,255,0,84,49,91,83,192,106,53,188,212,231,101,211,212,60,52,151,201,35,142,0,46,177,27,20,12,186,
34,34,33,70,170,249,29,235,234,165,158,147,240,234,165,195,23,200,216,246,99,131,182,170,201,53,184,90,191,106,92,150,221,62,69,230,182,42,149,208,8,228,124,96,135,90,112,184,118,171,88,223,155,17,221,
72,78,110,46,84,47,127,134,80,91,20,243,118,147,96,60,151,61,175,205,101,107,63,236,181,211,25,123,184,176,229,152,244,144,74,206,246,149,69,73,46,19,181,223,37,164,236,202,53,67,142,127,88,175,161,28,
161,100,206,76,185,165,134,154,6,31,133,177,131,38,31,203,185,85,209,81,112,230,124,174,230,171,232,76,168,168,206,54,177,63,236,251,204,76,135,172,77,164,120,252,152,176,115,185,158,192,179,169,214,36,
17,89,57,169,138,56,56,143,186,242,67,166,205,61,199,150,224,57,46,37,242,93,110,116,109,101,144,161,231,4,247,206,227,221,240,250,46,243,73,139,135,74,212,235,234,114,154,139,243,168,95,143,67,227,37,
228,185,42,11,132,127,235,188,169,21,85,145,211,34,43,253,205,16,83,190,101,84,111,177,36,220,209,159,188,5,5,117,186,114,82,105,147,18,52,121,161,27,118,207,37,220,155,177,64,159,95,91,90,52,183,236,
151,22,147,222,183,39,12,172,99,108,140,6,176,14,197,207,203,80,249,157,234,183,85,46,35,133,177,183,162,20,156,177,150,228,145,197,172,37,172,27,54,111,62,107,175,211,180,168,225,98,57,233,119,41,206,
214,215,190,87,43,88,182,67,70,77,200,243,84,98,88,13,189,174,42,101,77,116,52,222,142,95,94,132,104,105,100,155,213,167,175,42,230,227,160,143,72,233,90,123,45,27,241,81,169,53,86,84,201,195,107,77,211,
208,58,22,102,229,33,163,110,37,163,188,129,255,0,85,163,150,205,85,32,162,93,81,14,146,236,24,214,180,110,99,71,219,21,243,138,137,86,73,85,122,169,218,64,204,35,68,232,115,204,165,53,242,200,238,247,
46,254,142,62,28,12,111,68,57,26,151,231,51,157,242,90,51,54,59,97,146,79,228,235,125,23,61,252,134,111,189,177,252,92,184,209,227,251,85,196,205,235,154,200,188,176,189,50,22,26,68,200,88,214,234,144,
59,87,133,149,16,244,140,85,52,73,90,123,22,167,78,190,199,180,137,61,207,59,164,39,121,90,92,245,94,102,196,106,33,208,179,83,246,204,243,119,221,117,250,79,245,90,80,87,254,117,32,115,231,252,140,249,
63,181,83,174,254,102,254,137,250,103,227,95,217,88,84,133,136,64,100,20,184,62,219,51,130,246,146,42,30,85,168,108,21,29,235,218,75,212,243,129,74,252,65,171,185,241,71,252,65,62,171,175,254,56,207,241,
186,78,165,6,174,239,189,172,232,67,102,213,46,146,166,22,247,56,56,249,5,117,93,42,69,78,231,124,21,212,236,206,68,67,172,207,80,110,56,29,152,236,95,59,87,169,214,35,82,198,179,41,59,201,88,200,206,
40,124,222,153,25,177,206,243,235,29,103,110,236,62,21,218,232,42,139,75,233,255,0,103,57,169,162,164,222,167,131,54,242,168,165,157,179,22,220,6,194,59,126,138,125,109,50,212,66,172,106,217,72,180,242,
164,79,71,41,104,202,89,252,28,210,34,99,174,32,254,173,193,80,193,252,126,76,175,43,189,62,11,73,53,70,99,104,211,212,162,61,196,146,78,242,73,250,174,165,17,17,17,16,165,85,191,169,213,115,90,13,29,
28,67,113,127,198,66,225,117,137,243,169,84,232,116,154,116,120,196,139,212,144,123,177,14,29,224,143,248,170,218,235,42,41,57,83,209,78,65,91,21,146,61,187,176,113,216,190,147,3,243,137,174,234,135,31,
35,113,122,180,249,166,129,210,61,177,176,98,231,16,0,31,117,237,239,108,109,87,59,146,24,107,85,203,100,58,246,77,162,109,44,12,129,159,171,12,100,61,238,92,5,117,98,212,74,174,240,116,244,148,233,27,
44,125,73,46,0,158,224,74,135,26,102,244,111,85,177,37,235,139,85,221,10,36,207,185,206,119,121,37,125,62,38,97,27,91,209,14,22,71,102,245,119,82,213,154,108,178,23,188,111,123,128,244,92,159,242,57,239,
43,99,232,95,232,177,125,138,238,164,174,157,221,229,115,89,169,121,138,24,50,38,70,108,104,173,113,209,191,13,246,149,34,145,201,199,101,250,154,106,17,120,78,183,66,138,123,87,211,83,145,195,22,28,145,
156,77,138,33,17,105,196,118,183,181,115,186,158,143,53,76,188,72,220,158,189,75,138,29,70,56,99,197,232,120,114,198,87,51,224,48,193,128,226,49,223,138,151,166,105,73,71,119,57,110,229,52,87,87,173,77,
154,137,102,161,241,144,33,190,162,49,216,14,37,73,212,165,225,82,189,223,6,138,38,103,59,80,182,101,58,155,91,35,187,129,92,21,35,56,213,13,111,85,58,218,135,112,225,115,186,33,66,61,191,85,244,180,56,
133,47,89,48,8,233,226,111,242,23,21,243,221,98,165,36,170,119,199,161,215,233,176,227,2,124,155,13,64,85,43,34,22,88,26,221,80,87,133,149,76,163,16,214,231,147,218,188,43,149,79,86,67,229,96,200,64,101,
1,209,51,83,246,204,243,119,221,118,58,79,245,90,115,245,255,0,157,72,28,249,255,0,35,62,79,237,84,235,191,153,191,162,126,153,248,215,246,86,21,33,98,16,4,1,1,148,4,77,118,107,197,81,33,150,73,158,211,
128,0,5,117,71,174,203,73,18,68,198,34,161,87,85,167,54,103,230,170,166,252,143,155,48,82,201,166,100,206,123,131,72,1,220,215,154,237,118,106,200,184,78,98,34,124,30,105,244,230,194,252,209,85,73,11,
202,168,201,75,91,33,157,33,89,205,76,98,103,72,179,152,196,240,229,108,149,13,72,13,147,22,184,126,151,141,227,146,177,160,212,228,163,117,219,234,139,205,8,117,116,109,157,190,188,208,130,110,97,63,
31,243,54,206,254,213,127,255,0,38,138,223,235,234,84,253,41,247,230,75,69,153,244,140,141,204,47,46,123,198,23,246,183,201,87,73,252,134,103,72,142,68,75,39,177,41,154,91,17,170,159,253,158,113,152,52,
187,63,244,201,216,183,255,0,201,230,236,67,95,210,27,213,75,11,131,90,26,198,156,90,193,104,92,252,179,44,143,87,175,185,109,12,120,55,19,77,77,75,99,107,158,227,128,104,196,164,81,186,87,163,27,205,
79,79,122,49,170,231,123,28,175,40,84,105,36,146,76,48,14,113,56,47,165,83,68,177,68,216,250,33,199,205,39,18,69,127,82,229,152,25,34,208,106,228,28,162,7,238,185,205,127,80,183,254,59,23,246,90,105,180,
183,255,0,34,255,0,209,104,124,132,156,74,229,50,47,145,44,106,153,183,52,183,28,49,217,136,91,96,155,133,34,62,215,177,226,88,248,140,86,222,215,60,77,205,120,48,255,0,59,151,69,255,0,41,155,255,0,141,
10,63,161,179,185,73,38,66,200,152,216,152,235,154,49,56,170,42,218,199,85,74,178,187,209,75,106,74,100,129,152,33,243,114,139,114,85,133,201,113,97,114,100,44,70,84,100,8,222,75,152,251,73,222,211,187,
21,211,81,255,0,36,116,108,70,76,151,183,185,67,85,163,35,156,174,141,69,62,108,52,109,150,77,157,205,237,91,103,254,82,150,180,77,242,105,139,69,91,253,234,111,168,200,84,207,35,7,185,128,12,48,27,148,
40,127,147,79,18,42,43,81,202,190,228,169,116,88,223,101,69,177,183,39,228,168,160,113,145,178,23,59,12,0,42,61,118,191,53,92,124,53,98,34,27,41,116,166,192,252,145,85,76,85,197,165,105,97,36,3,188,133,
2,142,181,212,178,164,168,151,84,44,42,105,146,120,214,53,91,92,243,55,54,160,217,249,206,236,87,75,252,178,161,81,83,134,133,58,104,108,238,83,223,54,27,0,220,209,128,92,219,222,175,114,189,121,169,123,
19,48,98,52,214,188,155,2,0,128,32,8,12,160,58,38,106,126,217,158,110,251,174,199,73,254,171,78,126,191,243,169,3,159,63,228,103,201,253,170,157,119,243,55,244,79,211,63,26,254,202,194,164,44,66,0,128,
32,8,2,0,128,32,8,2,0,128,206,40,2,3,8,12,165,193,84,206,234,153,158,68,49,70,242,209,181,228,13,231,185,117,154,4,16,198,139,60,174,75,175,34,139,84,150,71,47,13,136,182,247,33,114,70,66,154,105,89,27,
163,123,90,79,196,231,12,0,10,242,183,83,134,8,92,246,185,21,125,144,171,130,153,242,61,26,169,99,164,201,107,67,99,102,198,48,96,2,249,203,228,124,142,87,191,154,157,100,81,163,27,100,53,226,188,220,
218,49,75,128,151,1,46,6,40,2,0,128,32,24,160,48,128,32,8,2,0,128,32,8,2,0,128,32,50,128,232,153,169,251,102,121,187,238,187,29,39,250,173,57,250,255,0,206,164,14,124,255,0,145,159,39,246,170,117,223,
204,223,209,63,76,252,107,251,43,10,144,177,8,2,0,128,32,8,2,0,128,32,8,5,195,188,44,217,76,92,200,228,176,100,194,0,128,32,54,69,37,187,128,250,162,223,169,229,88,138,125,235,71,184,15,37,139,24,225,
180,210,178,123,48,128,32,50,2,197,192,89,6,16,4,1,0,64,16,4,1,0,64,16,4,1,0,64,16,4,1,1,148,7,68,205,79,219,51,205,223,117,216,233,63,213,105,207,215,254,117,32,179,227,252,172,249,63,181,83,174,126,
102,254,137,218,111,227,119,236,172,218,169,108,88,220,90,150,23,22,165,133,197,169,97,113,106,88,92,90,150,23,22,165,133,197,169,97,113,106,88,92,248,153,214,181,206,59,154,9,94,153,26,189,200,222,166,
28,236,81,84,229,212,38,170,170,103,178,41,95,142,46,118,253,128,98,187,217,210,150,146,4,123,216,158,200,114,241,44,211,200,173,107,141,245,207,175,162,123,111,145,196,29,163,19,139,92,181,66,202,26,
246,46,45,79,255,0,79,114,58,166,149,201,117,47,217,19,40,10,136,91,54,236,71,196,15,97,92,133,109,34,211,204,177,243,232,95,211,206,146,198,143,60,117,153,211,71,27,139,12,152,184,111,192,99,255,0,84,
152,116,106,185,27,146,55,208,212,253,66,6,45,174,123,178,102,83,134,160,19,11,238,195,120,220,66,139,83,69,53,50,218,68,177,186,26,152,230,75,177,77,53,185,126,150,23,232,229,150,215,247,96,74,217,14,
153,85,51,51,141,183,67,196,149,144,198,236,92,190,166,137,51,166,137,174,176,203,183,113,32,28,2,218,221,26,177,205,203,3,194,234,20,232,182,200,148,146,161,141,102,148,187,8,240,198,238,74,11,96,123,
159,195,68,251,186,18,86,86,163,115,85,244,33,93,158,52,88,236,144,158,120,21,102,154,13,101,189,90,67,93,78,4,247,37,40,50,156,51,48,201,19,241,99,113,46,59,173,195,126,197,2,122,41,160,122,49,237,178,
175,34,76,117,17,200,220,154,190,133,23,47,231,43,159,80,52,19,17,7,194,9,27,60,202,234,244,253,37,172,166,255,0,51,46,255,0,82,146,170,185,93,55,248,221,246,151,92,145,149,96,157,135,69,37,218,48,52,
142,59,48,245,92,197,93,12,240,63,252,141,182,92,139,152,42,99,145,191,106,242,230,121,42,115,174,137,134,221,46,36,108,56,2,183,199,162,214,61,47,143,161,169,250,140,13,91,92,144,201,153,74,26,134,221,
11,238,3,120,220,71,209,68,169,163,154,157,216,200,150,55,195,81,28,169,118,41,236,181,70,177,186,226,212,176,184,181,44,46,45,75,11,139,82,194,226,212,176,184,181,44,46,45,75,11,139,82,194,226,212,176,
184,181,44,46,45,75,11,139,82,194,226,212,176,185,208,243,83,246,204,243,119,221,118,26,79,245,90,80,87,254,117,32,243,212,126,116,127,39,246,170,181,175,206,207,209,59,78,252,78,253,144,54,42,188,73,
183,49,98,98,46,44,76,69,197,137,136,184,177,49,23,22,38,34,226,196,196,92,88,152,139,139,19,17,114,35,59,39,209,210,202,127,144,45,30,101,79,211,97,226,84,181,58,122,145,171,36,198,21,42,255,0,133,244,
100,186,89,112,253,56,51,213,93,127,34,147,237,108,125,125,74,221,37,158,174,113,183,241,54,169,150,199,16,32,191,27,143,32,181,255,0,31,129,200,231,73,236,123,213,100,106,162,55,220,141,154,170,74,124,
157,27,65,180,204,73,231,106,150,216,89,62,160,231,47,174,63,251,35,172,142,138,149,26,158,228,166,107,102,172,47,165,51,76,46,116,141,115,154,79,250,128,20,77,71,83,153,149,60,56,253,17,9,20,148,113,
186,28,223,238,67,230,5,194,172,134,159,132,99,112,239,104,42,118,182,141,117,47,221,207,216,139,167,42,164,254,156,141,82,211,138,204,162,230,18,109,123,200,196,118,0,182,49,235,73,64,142,78,104,135,
151,53,42,42,149,23,221,79,172,249,201,16,211,72,200,226,199,18,220,72,43,26,61,92,181,17,171,164,234,102,190,8,226,114,53,133,166,162,162,8,104,34,142,169,206,248,216,62,17,250,143,32,169,25,12,210,215,
57,240,39,37,231,236,89,58,72,217,76,141,145,121,161,84,173,169,167,116,110,49,81,185,172,3,252,132,110,250,171,184,162,157,178,38,114,221,122,21,178,62,37,106,226,203,39,82,87,240,218,18,69,75,157,254,
59,112,35,176,142,213,11,95,95,88,209,191,237,114,70,150,158,143,85,228,67,100,12,156,201,235,76,65,191,149,115,141,189,150,142,197,97,91,80,248,104,243,191,221,100,34,211,196,217,42,49,183,161,59,159,
13,142,146,54,193,78,208,193,54,38,75,118,28,2,173,210,51,170,145,101,153,111,143,34,101,126,48,49,25,31,165,249,144,153,57,240,182,18,199,81,190,73,28,14,18,96,78,29,196,43,9,219,43,166,71,54,84,68,79,
98,36,74,198,199,101,101,215,169,43,248,117,73,43,103,125,204,115,89,105,223,179,111,98,135,174,189,143,133,44,183,82,70,152,215,54,69,186,122,29,10,197,202,98,94,92,88,152,139,139,19,17,113,98,98,46,
44,76,69,197,137,136,184,177,49,23,22,38,34,226,196,196,92,88,152,139,139,19,17,113,98,98,46,44,76,69,195,153,176,172,57,190,134,81,125,75,222,106,126,217,158,110,251,174,171,73,254,171,74,58,255,0,206,
164,54,120,143,207,143,228,254,213,102,176,151,168,103,232,155,167,254,39,126,200,141,26,131,137,39,33,163,76,70,67,70,152,140,134,141,49,25,13,26,98,50,26,52,196,100,52,105,136,200,104,211,17,144,209,
166,35,34,169,248,137,73,60,176,178,40,34,116,152,186,231,91,217,130,183,209,221,20,82,171,228,91,16,53,4,123,216,141,106,92,170,228,168,178,181,51,29,28,52,210,52,59,105,56,12,113,86,213,27,25,222,142,
145,232,182,32,197,185,137,182,107,79,94,71,204,154,153,228,211,86,18,6,56,184,31,212,121,45,85,26,164,80,179,135,2,30,226,162,124,142,202,82,111,63,115,113,243,69,25,167,110,38,33,104,96,237,111,46,106,
6,149,88,145,72,188,69,231,238,73,174,167,89,24,152,123,21,138,108,161,148,132,26,147,32,118,205,128,225,241,0,123,21,155,233,232,214,109,195,156,67,108,181,9,31,9,16,179,102,174,108,201,73,12,179,61,
183,84,61,132,53,163,120,4,110,243,85,181,245,173,169,145,172,111,163,81,73,148,180,235,11,21,203,205,72,204,192,200,21,12,169,124,181,17,58,48,6,45,47,237,36,169,90,181,84,79,129,25,27,174,104,161,129,
237,145,92,244,177,167,58,178,53,93,69,104,115,96,121,141,174,107,111,236,180,29,165,123,160,168,130,10,91,43,146,253,12,85,69,36,147,94,222,134,255,0,196,92,131,59,159,20,144,177,207,141,172,13,45,111,
250,158,245,175,71,170,141,141,115,94,182,85,91,158,181,8,30,229,69,106,93,44,120,171,78,82,158,149,176,10,59,99,0,52,150,129,115,176,237,43,116,76,163,138,117,149,100,186,154,222,234,135,196,140,70,122,
22,92,204,200,210,69,69,43,30,194,201,158,30,48,59,246,141,138,179,82,157,146,213,53,205,91,181,44,76,163,137,89,2,162,243,82,153,145,169,178,133,28,165,236,166,115,223,181,187,119,30,106,238,165,212,
181,81,163,92,251,33,93,2,77,3,238,141,45,57,229,155,243,213,65,12,205,111,231,49,184,190,49,219,143,96,85,90,109,92,116,210,185,139,254,170,190,138,77,172,129,243,49,29,239,208,131,201,153,87,41,194,
193,8,165,187,13,215,52,98,20,217,233,40,229,119,17,95,98,60,83,212,49,184,226,92,179,66,42,162,199,190,172,90,247,145,107,72,2,209,244,84,218,131,96,201,27,15,36,44,41,22,76,85,100,230,79,104,213,126,
36,188,134,141,49,25,13,26,98,50,26,52,196,100,52,105,136,200,104,211,17,144,209,166,35,33,163,76,70,67,70,152,140,134,141,49,25,13,26,98,50,26,52,196,100,52,105,136,200,249,150,61,135,201,121,123,126,
213,50,213,245,66,229,154,159,182,103,155,190,235,163,210,127,170,210,162,191,243,169,15,158,27,39,136,157,214,239,250,170,221,99,210,118,42,244,38,105,254,177,57,15,21,138,62,38,219,152,177,49,23,22,
38,34,226,196,196,92,88,152,139,139,19,17,113,98,98,46,44,76,69,197,137,136,185,144,212,196,205,204,224,123,214,48,65,145,130,213,156,69,197,137,137,139,152,17,13,248,12,123,240,218,150,81,116,51,98,98,
46,11,83,19,55,22,148,196,100,44,76,76,92,6,247,108,242,76,76,220,90,152,139,152,177,49,49,115,54,38,38,110,99,70,55,224,49,239,75,24,185,146,212,196,205,204,88,152,152,184,177,49,23,22,38,34,226,196,
196,92,88,152,139,139,19,17,113,98,98,46,44,76,69,197,137,136,184,177,49,23,22,38,34,226,196,196,92,88,152,139,154,170,134,13,62,75,92,222,140,83,219,61,92,133,179,53,90,69,51,49,241,31,250,175,244,164,
84,165,109,202,170,229,188,202,125,231,6,75,211,199,128,216,246,237,105,254,151,173,66,143,115,29,147,154,114,49,73,81,193,125,215,145,79,211,190,51,100,173,32,141,152,174,115,138,248,151,25,80,183,193,
178,122,177,79,189,126,62,107,214,238,35,28,7,141,126,62,105,187,136,112,30,53,248,249,166,238,33,192,120,215,227,230,155,184,135,1,227,95,143,154,110,226,28,7,141,126,62,105,187,136,112,30,53,248,249,
166,238,33,192,120,215,227,230,155,184,135,1,227,95,143,154,110,226,28,7,141,126,62,105,187,136,112,30,53,248,249,166,238,33,192,120,215,227,230,155,184,135,1,227,95,143,154,110,226,28,7,141,126,62,105,
187,136,112,30,53,248,249,166,238,33,192,120,215,227,230,155,184,135,1,227,95,143,154,110,226,28,7,141,126,62,105,187,136,112,30,53,248,249,166,238,33,192,120,215,227,230,155,184,135,1,227,95,143,154,
110,226,28,7,141,126,62,105,187,136,112,30,53,248,249,166,238,33,192,120,215,227,230,155,184,135,1,227,95,143,154,110,226,28,7,141,126,62,105,187,136,112,30,53,248,249,166,238,33,192,120,215,227,230,155,
184,135,1,227,95,143,154,110,226,28,7,141,126,62,105,187,136,112,30,53,248,249,166,238,33,192,120,215,227,230,155,184,135,1,227,95,143,154,110,226,28,7,141,126,62,105,187,136,112,30,53,248,249,166,238,
33,192,121,131,95,31,53,133,171,140,112,30,108,163,161,150,165,192,6,150,198,8,196,157,155,57,47,113,83,203,86,228,75,89,167,153,37,100,13,231,117,47,80,68,24,208,209,184,0,2,234,216,196,99,81,169,236,
81,185,202,229,186,155,23,179,201,170,106,102,63,245,177,174,249,134,43,91,226,99,255,0,217,17,79,77,123,155,201,77,61,25,7,6,63,104,90,246,176,246,39,131,223,30,78,229,29,25,7,6,63,104,77,172,61,137,
224,113,228,238,81,209,144,112,99,246,132,218,195,216,158,7,30,78,229,29,25,7,6,63,104,77,172,61,137,224,113,228,238,81,209,144,112,99,246,132,218,195,216,158,7,30,78,229,29,25,7,6,63,104,77,172,61,137,
224,113,228,238,81,209,144,112,99,246,132,218,195,216,158,7,30,78,229,29,25,7,6,63,104,77,172,61,137,224,113,228,238,81,209,144,112,99,246,132,218,195,216,158,7,30,78,229,29,25,7,6,63,104,77,172,61,137,
224,113,228,238,81,209,144,112,99,246,132,218,195,216,158,7,30,78,229,29,25,7,6,63,104,77,172,61,137,224,113,228,238,81,209,144,112,99,246,132,218,195,216,158,7,30,78,229,29,25,7,6,63,104,77,172,61,137,
224,113,228,238,81,209,144,112,99,246,132,218,195,216,158,7,30,78,229,29,25,7,6,63,104,77,172,61,137,224,113,228,238,81,209,144,112,99,246,132,218,195,216,158,7,30,78,229,29,25,7,6,63,104,77,172,61,137,
224,113,228,238,81,209,144,112,99,246,132,218,195,216,158,7,30,78,229,29,25,7,6,63,104,77,172,61,137,224,113,228,238,81,209,144,112,99,246,132,218,195,216,158,7,30,78,229,29,25,7,6,63,104,77,172,61,137,
224,113,228,238,81,209,144,112,99,246,132,218,195,216,158,7,30,78,229,29,25,7,6,63,104,77,172,61,137,224,113,228,238,81,209,144,112,99,246,132,218,195,216,158,7,30,78,229,29,25,7,6,63,104,77,172,61,137,
224,113,228,238,81,209,144,112,99,246,132,218,195,216,158,7,30,78,229,29,25,7,6,63,104,77,172,61,137,224,113,228,238,81,209,144,112,99,246,132,218,195,216,158,7,30,78,229,29,25,7,6,63,104,77,172,61,137,
224,113,228,238,81,209,144,112,99,246,132,218,195,216,158,7,30,78,229,29,25,7,6,63,104,77,172,61,137,224,113,228,238,81,209,144,112,99,246,132,218,195,216,158,7,30,78,229,29,25,7,6,63,104,77,172,61,137,
224,113,228,238,81,209,144,112,99,246,132,218,195,216,158,7,30,78,229,29,27,7,10,63,104,77,172,61,137,224,113,228,238,83,210,198,6,140,26,0,29,195,98,222,214,163,82,200,107,85,85,245,83,233,100,192,64,
16,4,1,0,64,16,4,1,0,64,16,4,1,0,64,16,4,1,0,64,16,4,1,0,64,16,4,1,0,64,16,4,1,0,64,16,4,1,0,64,16,4,1,0,64,16,4,1,1,255,217,0,0};

const char* JuceDemoPluginAudioProcessorEditor::images1_jpg = (const char*) resource_JuceDemoPluginAudioProcessorEditor_images1_jpg;
const int JuceDemoPluginAudioProcessorEditor::images1_jpgSize = 9168;


//[EndFile] You can add extra defines here...
//[/EndFile]
