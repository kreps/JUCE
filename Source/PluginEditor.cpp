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
    laf.setColour(GroupComponent::textColourId, Colour(0xff434343));
	laf.setColour (TextButton::buttonOnColourId, laf.findColour (TextButton::textColourOffId));
	laf.setColour (TextButton::textColourOnId, laf.findColour (TextButton::buttonColourId));
};

//[/MiscUserDefs]

//==============================================================================
JuceDemoPluginAudioProcessorEditor::JuceDemoPluginAudioProcessorEditor (JuceDemoPluginAudioProcessor* ownerFilter)
    : AudioProcessorEditor (ownerFilter)
{
    addAndMakeVisible (reverGroupComponent = new GroupComponent ("new group",
                                                                 TRANS("reverb")));

    addAndMakeVisible (delayGroupComponent = new GroupComponent ("new group",
                                                                 TRANS("delay")));
    delayGroupComponent->setTextLabelPosition (Justification::centredLeft);

    addAndMakeVisible (panSlider = new Slider ("pan"));
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

    addAndMakeVisible (delaySlider = new Slider ("delay"));
    delaySlider->setTooltip (TRANS("delay gain\n"));
    delaySlider->setRange (0, 1, 0);
    delaySlider->setSliderStyle (Slider::RotaryVerticalDrag);
    delaySlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    delaySlider->setColour (Slider::trackColourId, Colours::white);
    delaySlider->setColour (Slider::textBoxHighlightColourId, Colour (0xff1111ee));
    delaySlider->setColour (Slider::textBoxOutlineColourId, Colours::grey);
    delaySlider->addListener (this);

    addAndMakeVisible (bypassButton = new ToggleButton ("new toggle button"));
    bypassButton->setButtonText (TRANS("bypass"));
    bypassButton->addListener (this);

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

    addAndMakeVisible (inputHeaderLabel = new Label ("input label for header",
                                                     TRANS("wet amount")));
    inputHeaderLabel->setFont (Font ("Aharoni", 10.00f, Font::plain));
    inputHeaderLabel->setJustificationType (Justification::centred);
    inputHeaderLabel->setEditable (false, false, false);
    inputHeaderLabel->setColour (Label::textColourId, Colour (0xff363636));
    inputHeaderLabel->setColour (TextEditor::textColourId, Colours::black);
    inputHeaderLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

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

    addAndMakeVisible (slider = new Slider ("new slider"));
    slider->setRange (0, 10, 0);
    slider->setSliderStyle (Slider::RotaryVerticalDrag);
    slider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    slider->addListener (this);

    addAndMakeVisible (textButton = new TextButton ("new button"));
    textButton->setButtonText (TRANS("change lf1"));
    textButton->addListener (this);

    addAndMakeVisible (textButton2 = new TextButton ("new button"));
    textButton2->setButtonText (TRANS("change lf2"));
    textButton2->addListener (this);

    addAndMakeVisible (textButton3 = new TextButton ("new button"));
    textButton3->setButtonText (TRANS("dry"));
    textButton3->addListener (this);

    addAndMakeVisible (toggleButton = new ToggleButton ("new toggle button"));
    toggleButton->setButtonText (String::empty);
    toggleButton->addListener (this);

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
    guilaf.setDefaultSansSerifTypefaceName("Aharoni");
    guilaf.setImage(ImageCache::getFromMemory(kreps_logo_jpeg, kreps_logo_jpegSize));
    guilaf.setChickKnobImage(ImageCache::getFromMemory(chickknob_png,chickknob_pngSize));
    //[/Constructor]
}

JuceDemoPluginAudioProcessorEditor::~JuceDemoPluginAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	//deleteAllChildren ();
    //[/Destructor_pre]

    reverGroupComponent = nullptr;
    delayGroupComponent = nullptr;
    panSlider = nullptr;
    infoLabel = nullptr;
    gainSlider = nullptr;
    delaySlider = nullptr;
    bypassButton = nullptr;
    gainInfoLabel = nullptr;
    panInfoLabel = nullptr;
    delayTimeSlider = nullptr;
    delayTimeValueLabel = nullptr;
    panHeader = nullptr;
    inputHeaderLabel = nullptr;
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
    slider = nullptr;
    textButton = nullptr;
    textButton2 = nullptr;
    textButton3 = nullptr;
    toggleButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..

    //[/Destructor]
}

//==============================================================================
void JuceDemoPluginAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff777777));

    g.setColour (Colours::black.withAlpha (0.500f));
    g.drawImageWithin (cachedImage_uibg_png,
                       0, 0, 1920, 1040,
                       RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize,
                       false);

    //[UserPaint] Add your own custom painting code here..

    //[/UserPaint]
}

void JuceDemoPluginAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    reverGroupComponent->setBounds (472, 53, 200, 100);
    delayGroupComponent->setBounds (200, 53, 240, 100);
    panSlider->setBounds (100, 87, 80, 50);
    infoLabel->setBounds (96, 304, 400, 25);
    gainSlider->setBounds (0, 87, 80, 50);
    delaySlider->setBounds (200, 87, 80, 50);
    bypassButton->setBounds (8, 301, 64, 24);
    gainInfoLabel->setBounds (0, 137, 80, 20);
    panInfoLabel->setBounds (100, 137, 80, 20);
    delayTimeSlider->setBounds (280, 87, 80, 50);
    delayTimeValueLabel->setBounds (280, 67, 80, 20);
    panHeader->setBounds (100, 67, 80, 20);
    inputHeaderLabel->setBounds (0, 67, 80, 20);
    midSideSlider->setBounds (20, 202, 80, 50);
    midsideHeader->setBounds (10, 182, 80, 20);
    saturationSlider->setBounds (104, 221, 100, 50);
    distortionHeader->setBounds (116, 208, 80, 10);
    hpfHeader->setBounds (210, 182, 80, 30);
    hpfSlider->setBounds (220, 202, 60, 50);
    reverbSizeSlider->setBounds (488, 88, 50, 50);
    midsideInfoLabel->setBounds (10, 257, 80, 30);
    reverbSizeHeader->setBounds (472, 64, 80, 30);
    delayTimeSlider2->setBounds (360, 87, 80, 50);
    delayTimeValueLabel2->setBounds (360, 67, 80, 20);
    delayAmountHeader->setBounds (200, 64, 80, 24);
    slider->setBounds (296, 160, 112, 88);
    textButton->setBounds (200, 296, 88, 24);
    textButton2->setBounds (304, 296, 88, 24);
    textButton3->setBounds (4, 5, 44, 24);
    toggleButton->setBounds (49, 6, 150, 24);
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

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void JuceDemoPluginAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == bypassButton)
    {
        //[UserButtonCode_bypassButton] -- add your button handler code here..
		getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::bypassParam, (float)bypassButton->getToggleState());
        //[/UserButtonCode_bypassButton]
    }
    else if (buttonThatWasClicked == textButton)
    {
        //[UserButtonCode_textButton] -- add your button handler code here..
		LookAndFeel::setDefaultLookAndFeel(&lookAndFeelV1);
        //[/UserButtonCode_textButton]
    }
    else if (buttonThatWasClicked == textButton2)
    {
        //[UserButtonCode_textButton2] -- add your button handler code here..
        //[/UserButtonCode_textButton2]
    }
    else if (buttonThatWasClicked == textButton3)
    {
        //[UserButtonCode_textButton3] -- add your button handler code here..
        //[/UserButtonCode_textButton3]
    }
    else if (buttonThatWasClicked == toggleButton)
    {
        //[UserButtonCode_toggleButton] -- add your button handler code here..
        //[/UserButtonCode_toggleButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void JuceDemoPluginAudioProcessorEditor::mouseEnter (const MouseEvent& e)
{
    //[UserCode_mouseEnter] -- Add your code here...
	DBG(e.getPosition().toString());
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
	//rightGainInfoLabel->setText(String(rightGain*50)+ "\nRight",dontSendNotification);
	bypassButton->setToggleState((ourProcessor->m_fBypass != 0), sendNotification);
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
    <IMAGE pos="0 0 1920 1040" resource="uibg_png" opacity="0.5" mode="2"/>
  </BACKGROUND>
  <GROUPCOMPONENT name="new group" id="fb7419eb67152218" memberName="reverGroupComponent"
                  virtualName="" explicitFocusOrder="0" pos="472 53 200 100" title="reverb"/>
  <GROUPCOMPONENT name="new group" id="98be51d9c59fac6f" memberName="delayGroupComponent"
                  virtualName="" explicitFocusOrder="0" pos="200 53 240 100" title="delay"
                  textpos="33"/>
  <SLIDER name="pan" id="324eec4d274919f3" memberName="panSlider" virtualName=""
          explicitFocusOrder="0" pos="100 87 80 50" min="0" max="1" int="0"
          style="RotaryVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="" id="3084384ee25f6d12" memberName="infoLabel" virtualName=""
         explicitFocusOrder="0" pos="96 304 400 25" textCol="ff414141"
         edTextCol="ff000000" edBkgCol="0" labelText="aaa" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <SLIDER name="gainSlider" id="c31acc4ca22491a9" memberName="gainSlider"
          virtualName="" explicitFocusOrder="0" pos="0 87 80 50" tooltip="gain"
          min="0" max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.29999999999999999"/>
  <SLIDER name="delay" id="37878e5e9fd60a08" memberName="delaySlider" virtualName=""
          explicitFocusOrder="0" pos="200 87 80 50" tooltip="delay gain&#10;"
          trackcol="ffffffff" textboxhighlight="ff1111ee" textboxoutline="ff808080"
          min="0" max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <TOGGLEBUTTON name="new toggle button" id="d59c4ede9f259185" memberName="bypassButton"
                virtualName="" explicitFocusOrder="0" pos="8 301 64 24" buttonText="bypass"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="gainInfoLabel" id="dde6ff72637f37e7" memberName="gainInfoLabel"
         virtualName="" explicitFocusOrder="0" pos="0 137 80 20" textCol="ff323232"
         edTextCol="ff000000" edBkgCol="0" labelText="0.0 dB&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="64ddab567eb77e3c" memberName="panInfoLabel"
         virtualName="" explicitFocusOrder="0" pos="100 137 80 20" textCol="ff282828"
         edTextCol="ff000000" edBkgCol="0" labelText="C" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="ead45d255e5f5831" memberName="delayTimeSlider"
          virtualName="" explicitFocusOrder="0" pos="280 87 80 50" min="0"
          max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="3b34631ac55e0fe6" memberName="delayTimeValueLabel"
         virtualName="" explicitFocusOrder="0" pos="280 67 80 20" textCol="ff282828"
         edTextCol="ff000000" edBkgCol="0" labelText="time" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="ec32effd76232b82" memberName="panHeader"
         virtualName="" explicitFocusOrder="0" pos="100 67 80 20" textCol="ff363636"
         edTextCol="ff000000" edBkgCol="0" labelText="pan&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <LABEL name="input label for header" id="2a92c25f1cf628c8" memberName="inputHeaderLabel"
         virtualName="" explicitFocusOrder="0" pos="0 67 80 20" textCol="ff363636"
         edTextCol="ff000000" edBkgCol="0" labelText="wet amount" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="mid/side slider" id="84706171dc5b90dd" memberName="midSideSlider"
          virtualName="" explicitFocusOrder="0" pos="20 202 80 50" min="0"
          max="1" int="0.0050000000000000001" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="fcf994bed06bf6ab" memberName="midsideHeader"
         virtualName="" explicitFocusOrder="0" pos="10 182 80 20" textCol="ff363636"
         edTextCol="ff000000" edBkgCol="0" labelText="mid/side" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="mid/side slider" id="2a577f0fc0372cc6" memberName="saturationSlider"
          virtualName="" explicitFocusOrder="0" pos="104 221 100 50" min="0.001"
          max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="saturation fx" id="eda4710f044030be" memberName="distortionHeader"
         virtualName="" explicitFocusOrder="0" pos="116 208 80 10" textCol="ff363636"
         edTextCol="ff000000" edBkgCol="0" labelText="saturation" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="12"/>
  <LABEL name="new label" id="f53c45ed3e69f449" memberName="hpfHeader"
         virtualName="" explicitFocusOrder="0" pos="210 182 80 30" textCol="ff363636"
         edTextCol="ff000000" edBkgCol="0" labelText="hi pass filter"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Aharoni" fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="hi pass filter" id="253b421224cbac37" memberName="hpfSlider"
          virtualName="" explicitFocusOrder="0" pos="220 202 60 50" tooltip="hi pass filter (hz)"
          min="20" max="10000" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.20000000000000001"/>
  <SLIDER name="new slider" id="81b8a5f3e2f90d2e" memberName="reverbSizeSlider"
          virtualName="" explicitFocusOrder="0" pos="488 88 50 50" min="0.01"
          max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="63580ead55c45fe" memberName="midsideInfoLabel"
         virtualName="" explicitFocusOrder="0" pos="10 257 80 30" textCol="ff363636"
         edTextCol="ff000000" edBkgCol="0" labelText="80%" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="9e5a6f98ed1157ee" memberName="reverbSizeHeader"
         virtualName="" explicitFocusOrder="0" pos="472 64 80 30" textCol="ff363636"
         edTextCol="ff000000" edBkgCol="0" labelText="room size" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="f86ed4bd47474957" memberName="delayTimeSlider2"
          virtualName="" explicitFocusOrder="0" pos="360 87 80 50" min="0"
          max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="b702d23a464e1ffe" memberName="delayTimeValueLabel2"
         virtualName="" explicitFocusOrder="0" pos="360 67 80 20" textCol="ff282828"
         edTextCol="ff000000" edBkgCol="0" labelText="feedback" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="17713b10facdb0a1" memberName="delayAmountHeader"
         virtualName="" explicitFocusOrder="0" pos="200 64 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="amount" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Aharoni" fontsize="10" bold="0"
         italic="0" justification="36"/>
  <SLIDER name="new slider" id="501ed27d1d7aee12" memberName="slider" virtualName=""
          explicitFocusOrder="0" pos="296 160 112 88" min="0" max="10"
          int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <TEXTBUTTON name="new button" id="877f25c71c1bc232" memberName="textButton"
              virtualName="" explicitFocusOrder="0" pos="200 296 88 24" buttonText="change lf1"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="bcef889c607949af" memberName="textButton2"
              virtualName="" explicitFocusOrder="0" pos="304 296 88 24" buttonText="change lf2"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="c04eb8bb913886bc" memberName="textButton3"
              virtualName="" explicitFocusOrder="0" pos="4 5 44 24" buttonText="dry"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="new toggle button" id="98e5eb6eca28c006" memberName="toggleButton"
                virtualName="" explicitFocusOrder="0" pos="49 6 150 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
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

// JUCER_RESOURCE: uibg_png, 14573, "../uibg.png"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_uibg_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,7,128,0,0,4,16,8,6,0,0,0,3,44,70,24,0,0,0,4,103,65,77,65,0,0,175,
200,55,5,138,233,0,0,0,25,116,69,88,116,83,111,102,116,119,97,114,101,0,65,100,111,98,101,32,73,109,97,103,101,82,101,97,100,121,113,201,101,60,0,0,56,127,73,68,65,84,120,218,236,221,125,144,93,117,121,
192,241,147,23,19,48,169,25,129,8,37,38,133,52,146,146,152,30,16,68,99,147,102,136,133,202,132,73,133,1,82,104,147,138,58,161,113,68,108,82,145,1,43,106,100,124,1,197,12,145,88,141,224,232,24,121,53,29,
40,83,235,11,99,0,147,66,131,201,169,18,12,50,128,169,137,32,152,109,144,152,49,148,108,127,191,222,187,54,164,155,221,187,175,217,251,220,207,103,230,153,3,187,231,222,123,94,118,243,207,119,207,57,195,
218,219,219,11,0,0,0,0,0,0,0,154,223,112,135,0,0,0,0,0,0,0,32,6,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,
0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,
0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,
0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,
0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,
0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,
0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,
32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,
8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,1,24,0,0,0,0,0,0,32,8,
1,24,0,0,0,0,0,0,32,136,145,141,174,56,108,216,176,150,57,40,237,237,237,126,50,0,0,0,0,0,0,128,166,51,114,8,110,211,184,52,83,58,249,250,214,52,47,56,101,0,0,0,0,0,0,0,157,59,212,1,120,68,154,51,234,
51,167,168,133,223,113,93,172,191,51,205,147,105,238,77,243,157,250,0,0,0,0,0,0,0,144,12,107,244,118,199,253,120,11,232,28,120,115,240,93,80,95,142,235,195,123,229,32,252,173,52,119,20,181,24,220,47,87,
8,187,5,52,0,0,0,0,0,0,208,140,6,51,0,143,77,243,129,52,75,235,255,221,223,118,165,249,100,154,21,105,246,244,229,141,4,96,0,0,0,0,0,0,160,25,13,70,0,206,183,121,94,156,230,163,105,198,15,194,62,109,79,
115,117,154,175,164,121,169,55,111,208,140,1,184,31,175,208,62,228,4,120,0,0,0,0,0,0,232,157,129,14,192,111,75,115,67,81,123,182,239,96,219,146,230,210,162,246,188,224,30,17,128,127,103,106,81,187,90,
187,99,57,41,205,182,162,118,181,245,227,251,45,251,85,164,0,220,95,231,165,170,170,25,105,49,51,205,180,252,251,180,115,231,206,215,222,119,223,125,191,247,246,183,191,189,173,190,202,211,245,115,145,
127,238,55,148,101,249,35,231,2,0,0,0,0,0,160,245,12,84,0,30,149,230,227,69,237,150,207,135,218,199,234,211,240,213,192,45,28,128,143,40,106,209,254,188,162,246,124,230,70,110,213,157,35,112,126,254,242,
173,69,237,121,204,125,126,14,179,0,92,83,85,213,156,180,184,40,205,57,69,45,240,110,40,106,129,247,241,245,235,215,255,102,229,202,149,243,214,172,89,243,141,250,234,199,20,181,63,180,200,129,120,102,
253,255,215,166,89,83,150,229,58,231,2,0,0,0,0,0,160,53,12,68,0,206,17,241,155,105,230,12,161,253,204,129,242,220,162,193,56,217,130,1,120,86,154,171,138,90,252,237,139,189,69,45,2,95,147,230,161,222,
190,73,43,7,224,170,170,242,45,211,23,164,185,34,205,206,52,107,210,172,45,203,242,217,3,86,29,151,230,157,105,174,63,200,251,228,219,173,231,112,124,81,253,119,50,63,31,251,214,244,62,47,181,234,185,
0,0,0,0,0,0,104,5,253,29,128,39,164,249,151,52,51,134,224,190,62,156,230,236,162,118,37,101,151,90,40,0,231,171,69,63,157,102,222,0,108,82,190,34,248,67,69,47,110,17,221,170,1,184,170,170,28,226,255,49,
205,230,52,171,202,178,124,160,139,213,15,75,243,254,162,22,118,27,121,223,37,105,78,74,115,73,55,239,27,246,92,0,0,0,0,0,0,180,130,254,12,192,249,138,195,245,197,161,121,222,111,163,242,115,81,103,23,
181,219,22,31,84,11,4,224,195,211,124,46,205,226,1,222,172,124,181,233,202,52,151,23,181,171,131,27,210,106,1,184,126,213,239,103,210,156,82,212,194,239,154,6,222,250,21,245,227,122,77,163,219,146,62,
39,95,13,156,67,112,254,99,136,101,141,92,13,44,0,3,0,0,0,0,0,52,151,225,253,244,62,249,118,180,249,202,223,41,67,124,127,243,149,201,223,46,106,1,180,85,77,74,243,96,49,240,241,55,203,97,243,178,52,247,
23,181,103,210,114,128,170,170,242,237,153,191,87,63,86,111,109,48,254,102,47,22,181,8,220,176,250,123,191,181,254,89,223,171,127,54,0,0,0,0,0,0,129,244,87,0,254,106,81,187,122,177,25,156,150,102,117,
139,158,239,124,43,224,28,127,103,28,130,99,254,96,19,253,140,12,138,170,170,166,213,143,203,3,101,89,94,154,102,111,15,223,34,175,63,170,39,47,200,159,145,63,43,127,102,91,91,219,198,107,175,189,246,
52,103,2,0,0,0,0,0,32,142,254,8,192,75,211,204,111,178,253,206,183,194,93,220,98,231,58,159,163,124,165,233,161,186,18,55,95,121,156,175,4,158,235,215,174,40,174,187,238,186,217,207,61,247,220,134,244,
159,43,202,178,252,80,47,223,102,95,81,187,154,183,199,210,103,174,248,212,167,62,85,77,158,60,249,187,85,85,205,112,70,0,0,0,0,0,0,98,232,235,51,128,79,42,106,87,48,142,106,194,125,223,147,230,143,211,
60,126,224,55,2,62,3,120,70,253,60,13,133,91,95,239,76,243,166,206,142,123,51,31,255,158,156,151,170,170,38,60,241,196,19,15,223,120,227,141,63,248,206,119,190,243,254,244,165,255,236,229,219,255,93,154,
155,138,110,158,105,221,137,163,210,44,42,106,183,129,126,75,90,94,149,230,45,101,89,110,139,124,46,0,0,0,0,0,0,90,65,95,3,112,190,162,115,86,19,239,255,61,105,206,62,240,139,193,2,240,248,52,27,139,218,
21,184,67,197,150,52,57,60,118,26,46,35,7,224,170,170,114,132,95,159,230,142,250,51,121,47,72,115,91,154,39,27,121,191,244,250,215,22,181,120,123,220,13,55,220,48,243,194,11,47,252,249,81,71,29,149,111,
5,189,35,205,83,105,110,78,239,251,203,46,222,34,63,247,247,29,105,238,77,179,185,254,158,87,164,197,130,162,22,129,247,68,61,23,0,0,0,0,0,0,173,160,47,1,56,223,70,249,235,1,142,65,14,192,247,236,255,
133,64,1,56,95,153,253,237,52,115,134,224,38,231,99,254,23,105,94,58,240,27,193,3,240,231,242,62,151,101,185,172,254,165,137,69,45,190,230,227,241,232,193,222,39,189,110,73,90,44,124,254,249,231,255,224,
150,91,110,249,183,71,30,121,164,120,226,137,39,142,26,57,114,228,111,211,103,236,59,254,248,227,119,79,159,62,125,216,130,5,11,102,141,25,51,230,177,180,238,170,244,25,7,254,126,190,58,205,197,197,126,
241,119,191,247,255,76,90,140,72,175,121,127,212,115,1,0,0,0,0,0,208,10,122,27,128,243,115,71,31,73,51,53,192,49,200,33,236,228,253,191,16,40,0,231,43,59,63,49,132,55,251,61,105,86,29,248,197,168,1,184,
170,170,124,203,244,124,53,246,43,203,178,220,187,223,106,249,185,204,249,15,42,242,51,154,171,253,95,159,94,179,48,45,150,172,93,187,246,185,21,43,86,140,111,107,107,123,99,209,245,115,127,247,30,113,
196,17,27,63,252,225,15,255,250,244,211,79,31,93,212,66,112,190,194,184,35,254,126,63,205,15,15,124,81,250,156,252,199,2,191,73,243,166,180,254,195,17,207,5,0,0,0,0,0,64,43,232,109,0,142,114,245,111,135,
151,93,5,28,36,0,79,72,243,147,52,99,135,240,102,231,231,1,191,174,190,44,154,249,248,55,114,94,170,170,218,84,212,130,236,23,59,89,53,223,154,249,111,210,252,32,205,67,105,221,145,105,249,137,199,30,
123,236,79,23,47,94,188,175,173,173,237,205,61,253,236,241,227,199,223,127,211,77,55,189,234,176,195,14,251,238,25,103,156,177,61,125,233,129,52,255,126,176,245,211,103,190,43,45,222,155,182,239,228,136,
231,2,0,0,0,0,0,160,21,12,239,229,235,222,27,236,56,92,22,240,220,126,180,24,218,241,55,203,209,243,170,86,248,69,171,170,106,94,90,108,63,72,252,205,114,4,191,41,205,105,175,127,253,235,223,158,150,215,
223,126,251,237,39,92,112,193,5,211,123,19,127,179,103,159,125,118,246,252,249,243,39,221,124,243,205,179,175,191,254,250,211,210,54,60,210,213,250,105,219,190,156,183,177,190,173,0,0,0,0,0,0,52,161,222,
4,224,41,105,102,6,59,14,103,164,153,20,104,127,242,213,191,11,155,100,91,23,23,181,16,28,93,14,221,171,186,89,103,87,154,155,223,240,134,55,92,250,145,143,124,228,117,31,255,248,199,231,181,183,183,143,
233,203,135,166,215,191,122,205,154,53,39,109,223,190,253,176,244,191,203,27,120,201,170,162,69,162,60,0,0,0,0,0,64,68,189,9,192,11,131,30,139,139,2,237,75,190,149,239,168,38,217,214,177,129,127,166,254,
87,85,85,211,210,98,92,89,150,247,52,176,238,21,211,166,77,123,113,237,218,181,167,23,93,63,235,183,39,70,93,119,221,117,127,190,121,243,230,83,211,251,119,25,119,235,219,56,174,190,205,0,0,0,0,0,0,52,
153,222,4,224,51,130,30,139,57,129,246,101,161,237,29,114,251,247,181,238,86,170,170,106,86,91,91,219,95,95,121,229,149,167,22,253,31,240,15,191,248,226,139,255,112,247,238,221,151,165,207,57,185,155,
117,215,20,177,254,32,2,0,0,0,0,0,160,101,244,52,0,231,91,245,158,22,244,88,228,0,60,42,192,126,204,40,106,183,233,110,38,167,20,177,110,193,125,160,252,76,221,123,26,88,111,201,210,165,75,255,99,223,
190,125,71,14,196,70,164,247,157,112,229,149,87,222,159,63,167,155,85,239,74,51,223,63,143,0,0,0,0,0,0,205,167,167,1,56,135,186,17,65,143,197,225,105,78,10,176,31,115,155,116,187,231,68,252,161,170,170,
42,255,209,196,132,178,44,127,212,205,122,111,220,177,99,71,249,195,31,254,240,109,3,185,61,235,214,173,251,179,231,159,127,126,94,250,188,169,7,91,167,190,173,19,234,219,14,0,0,0,0,0,64,19,233,105,0,
142,254,92,208,169,1,246,97,102,147,110,247,172,160,63,83,249,124,108,104,96,189,37,203,151,47,255,105,49,192,87,161,183,183,183,191,234,218,107,175,205,219,211,221,85,192,27,154,248,103,9,0,0,0,0,0,160,
101,9,192,47,55,195,62,28,50,81,127,182,242,126,109,105,96,189,211,54,109,218,116,194,96,108,208,125,247,221,55,49,45,222,220,205,106,91,90,224,247,29,0,0,0,0,0,32,156,158,6,224,9,193,143,71,132,253,155,
210,164,219,61,53,232,207,84,126,182,241,182,174,86,168,170,234,53,187,119,239,126,205,158,61,123,6,229,24,236,218,181,107,250,190,125,251,78,78,159,219,213,213,198,219,138,216,207,101,6,0,0,0,0,0,8,169,
167,1,120,92,240,227,209,236,251,55,182,24,224,91,8,15,160,168,207,155,205,251,181,179,155,117,222,242,232,163,143,254,184,24,164,231,107,183,183,183,143,121,234,169,167,242,231,157,218,197,106,59,95,
124,241,197,35,253,19,9,0,0,0,0,0,208,92,70,246,112,253,232,1,120,172,237,63,100,114,252,60,60,205,158,72,63,80,91,183,110,61,118,195,134,13,227,211,127,158,114,176,117,238,188,243,206,147,127,253,235,
95,15,234,118,165,207,60,108,203,150,45,239,75,255,121,102,103,223,95,180,104,209,235,206,58,235,172,63,58,229,148,83,252,43,9,0,0,0,0,0,208,68,70,58,4,47,51,194,246,219,254,254,180,115,231,206,225,219,
183,111,63,42,253,231,177,7,91,103,199,142,29,71,14,246,190,207,154,53,235,23,31,248,192,7,238,40,203,242,142,206,190,255,213,175,126,117,126,90,188,203,63,9,0,0,0,0,0,0,205,165,167,1,248,165,224,199,
99,111,147,111,255,11,182,127,104,153,57,115,230,207,210,60,118,219,109,183,221,125,176,117,46,189,244,210,17,27,55,110,156,182,122,245,234,65,219,174,163,143,62,250,213,105,177,163,139,85,242,213,254,
187,252,19,9,0,0,0,0,0,208,92,122,250,12,224,103,131,31,143,157,77,190,253,57,216,53,107,196,126,54,240,207,84,119,207,55,94,127,226,137,39,190,126,16,183,105,239,113,199,29,151,63,111,99,23,235,28,17,
224,247,1,0,0,0,0,0,160,229,244,52,0,63,29,252,120,68,216,191,199,109,247,144,219,175,41,93,173,80,150,229,47,199,140,25,211,54,122,244,232,199,6,99,131,198,142,29,187,101,248,240,225,143,164,207,237,
234,143,5,166,4,62,39,0,0,0,0,0,0,97,245,52,0,111,13,126,60,34,236,159,0,60,244,126,166,166,54,176,222,198,233,211,167,255,100,48,54,232,212,83,79,125,162,232,250,234,223,162,190,205,209,127,223,1,0,0,
0,0,0,194,233,105,0,222,18,252,120,68,216,191,13,182,123,200,237,215,220,170,170,70,116,179,222,77,151,95,126,249,248,65,216,158,189,31,252,224,7,115,220,93,117,176,21,234,219,58,55,205,3,254,137,4,0,
0,0,0,0,104,46,61,13,192,15,5,62,22,47,165,121,56,192,126,172,107,210,237,190,55,226,15,85,89,150,47,20,181,8,60,179,155,245,190,119,226,137,39,254,118,252,248,241,247,15,228,246,76,154,52,105,221,177,
199,30,187,45,125,222,166,46,86,203,219,186,33,173,179,199,63,145,0,0,0,0,0,0,205,165,167,1,120,123,17,247,86,189,63,74,179,43,192,126,228,72,223,108,207,50,222,90,196,190,221,240,93,105,230,55,176,222,
170,27,111,188,113,244,176,97,195,118,15,196,70,164,247,109,91,189,122,245,196,162,139,171,127,235,230,215,183,25,0,0,0,0,0,128,38,51,188,23,175,185,39,232,177,136,18,188,242,149,204,107,154,108,155,215,
4,255,61,203,251,183,180,187,219,64,151,101,121,219,9,39,156,112,223,251,222,247,190,111,15,196,207,197,213,87,95,253,192,209,71,31,253,205,244,57,119,31,108,165,250,54,46,109,129,115,2,0,0,0,0,0,16,82,
111,2,240,215,130,30,139,72,251,245,229,162,22,130,155,193,222,52,95,137,252,75,86,150,101,190,114,62,255,129,193,59,26,88,125,249,59,223,249,206,157,179,103,207,94,219,159,219,48,127,254,252,127,58,231,
156,115,126,150,182,229,170,110,86,205,219,120,87,125,155,1,0,0,0,0,0,104,50,189,9,192,249,57,185,91,130,29,135,252,140,214,72,183,182,206,231,103,109,147,108,107,14,239,219,90,224,119,237,154,52,75,186,
91,169,44,203,231,211,98,213,202,149,43,119,206,154,53,235,238,126,248,220,151,230,207,159,127,231,242,229,203,127,153,254,123,101,3,235,47,169,111,43,0,0,0,0,0,0,77,104,120,47,95,183,42,216,113,88,21,
240,220,126,172,24,250,87,1,231,171,127,91,34,54,150,101,153,255,112,98,123,85,85,87,53,178,238,214,173,91,111,154,56,113,226,248,101,203,150,253,235,168,81,163,122,245,199,9,163,71,143,254,201,69,23,
93,180,233,146,75,46,249,175,244,191,43,210,251,118,249,156,229,250,182,61,93,223,86,0,0,0,0,0,0,154,80,111,3,112,190,197,240,211,65,142,193,147,69,204,231,157,254,40,205,138,33,190,141,215,212,143,127,
171,120,79,154,43,170,170,154,218,221,138,23,92,112,193,228,111,124,227,27,87,45,90,180,232,219,15,62,248,224,164,243,207,63,255,206,87,188,226,21,63,107,228,67,114,48,94,184,112,225,157,15,61,244,80,
123,89,150,223,155,55,111,222,166,180,124,162,171,215,212,183,233,138,52,151,248,103,17,0,0,0,0,0,160,121,13,107,111,111,111,108,197,97,195,14,252,210,210,52,159,9,112,12,222,93,212,130,246,239,52,122,
76,134,212,137,252,255,231,39,27,155,102,83,154,41,67,112,147,115,160,62,181,168,93,5,92,52,251,241,111,244,188,84,85,117,89,90,76,45,203,242,61,93,188,236,79,242,58,69,237,217,200,251,210,107,38,23,181,
91,51,159,247,232,163,143,254,226,243,159,255,252,211,59,118,236,120,229,115,207,61,119,228,222,189,123,95,57,122,244,232,23,142,60,242,200,182,137,19,39,238,190,236,178,203,142,155,60,121,242,171,210,
186,183,165,89,149,62,231,231,105,121,78,154,255,78,115,208,91,74,167,207,184,49,45,182,166,245,87,68,61,23,0,0,0,0,0,0,173,160,47,1,120,84,81,139,139,211,154,120,255,55,23,181,8,249,178,91,37,7,10,192,
217,73,105,30,172,159,175,161,226,133,250,113,239,244,150,196,145,3,112,86,85,213,55,211,226,201,178,44,151,117,242,146,9,105,46,76,243,165,52,187,58,121,237,91,235,223,31,159,230,247,211,188,178,126,
60,159,169,207,87,210,251,174,239,228,119,117,113,154,239,167,249,113,39,239,249,233,180,152,146,94,119,110,228,115,1,0,0,0,0,0,208,10,250,18,128,179,89,105,238,111,210,125,207,209,55,71,200,205,7,126,
35,88,0,206,46,74,243,245,33,116,220,115,104,188,235,96,43,180,64,0,62,188,168,197,216,111,149,101,121,245,126,223,58,172,168,221,130,249,91,197,65,226,120,31,28,147,102,97,154,213,105,218,246,219,150,
143,166,197,219,210,188,53,109,203,11,145,207,5,0,0,0,0,0,64,43,24,222,199,215,63,144,230,179,77,186,239,159,44,58,137,191,65,229,103,28,191,127,136,108,203,197,69,23,241,183,21,148,101,185,39,45,206,
78,179,160,170,170,79,236,247,173,252,181,159,22,253,31,127,179,252,204,238,117,105,206,79,51,34,127,161,126,229,239,130,252,185,157,197,95,0,0,0,0,0,0,154,79,95,175,0,206,242,237,101,243,85,192,167,53,
209,126,223,155,230,204,226,128,91,63,119,8,120,5,112,135,124,27,224,252,172,215,17,135,96,19,243,179,126,23,165,185,181,187,21,163,95,1,220,161,170,170,113,105,113,75,154,199,231,206,157,251,245,95,253,
234,87,249,118,221,95,58,216,207,101,63,185,112,204,152,49,187,215,175,95,127,70,81,123,54,244,249,93,197,95,87,0,3,0,0,0,0,0,52,151,225,253,240,30,57,236,229,91,250,110,111,146,125,126,60,205,95,22,3,
27,217,134,170,47,22,181,171,76,119,14,242,231,230,171,79,115,112,191,213,175,220,255,41,203,50,63,227,247,236,182,182,182,225,103,158,121,230,231,191,240,133,47,252,108,160,127,46,239,190,251,238,95,
156,123,238,185,255,176,109,219,182,209,133,43,127,1,0,0,0,0,0,194,233,143,43,128,59,76,43,106,207,53,29,63,132,247,55,135,200,217,69,45,2,31,84,224,43,128,59,76,74,115,115,154,185,131,176,105,247,164,
121,119,253,216,55,164,85,174,0,222,223,218,181,107,255,118,242,228,201,249,182,228,159,45,203,242,99,3,177,45,85,85,125,56,45,150,62,243,204,51,127,127,230,153,103,174,110,181,115,1,0,0,0,0,0,208,10,
250,51,0,103,51,210,252,115,81,11,140,67,77,142,190,103,21,221,196,223,172,5,2,112,135,121,105,242,115,96,167,13,192,38,61,156,230,242,162,118,187,237,30,105,197,0,156,85,85,117,76,90,124,38,205,41,105,
86,229,41,203,114,111,95,62,63,189,103,190,69,251,146,250,228,115,178,44,189,103,75,198,120,0,0,0,0,0,128,86,208,223,1,56,203,87,0,223,158,102,206,16,218,207,111,165,249,171,162,193,91,31,183,80,0,238,
240,174,52,87,165,57,190,31,54,101,107,154,124,5,235,154,222,190,65,171,6,224,14,85,85,77,77,139,43,210,92,148,230,43,105,238,74,179,174,209,219,53,167,215,143,173,255,254,205,79,243,142,250,185,248,100,
122,253,214,86,62,23,0,0,0,0,0,0,173,96,32,2,112,150,175,58,188,33,205,226,33,176,143,43,210,44,43,122,240,108,213,22,12,192,29,242,45,161,23,164,121,91,209,179,171,184,159,44,106,183,122,206,207,248,
125,160,175,27,209,234,1,184,67,85,85,71,164,197,121,69,45,228,230,160,155,175,94,223,82,95,30,248,204,237,9,105,166,20,181,171,185,243,114,93,81,11,199,119,148,101,185,211,185,0,0,0,0,0,0,104,13,3,21,
128,59,228,219,206,230,91,12,143,61,4,251,182,43,205,165,105,190,214,211,23,182,112,0,222,95,14,192,39,21,181,152,56,181,147,239,119,132,200,205,197,255,143,145,125,34,0,119,174,170,170,124,62,58,2,239,
132,3,190,189,189,126,62,182,148,101,185,217,185,0,0,0,0,0,0,104,77,3,29,128,179,28,18,243,115,77,207,27,196,253,202,183,188,205,87,253,62,221,155,23,11,192,135,150,232,8,0,0,0,0,0,0,189,51,24,1,184,195,
204,162,246,92,211,249,3,184,63,107,211,92,147,230,225,190,188,137,0,9,0,0,0,0,0,0,52,163,193,12,192,29,242,45,108,23,166,121,71,154,99,250,225,253,242,173,111,191,92,212,110,245,252,120,127,108,160,0,
12,0,0,0,0,0,0,52,163,67,17,128,247,151,175,10,158,155,102,78,154,227,139,218,179,77,187,179,53,205,147,105,214,165,185,55,205,67,253,189,81,2,48,0,0,0,0,0,0,208,140,14,117,0,238,204,184,162,22,130,143,
40,106,81,56,95,213,187,171,168,133,223,23,6,99,3,4,96,0,0,0,0,0,0,160,25,13,197,0,124,200,9,192,0,0,0,0,0,0,64,51,26,217,232,138,162,40,0,0,0,0,0,0,192,208,54,220,33,0,0,0,0,0,0,0,136,65,0,6,0,0,0,0,
0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,
6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,
0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,
0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,
8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,
0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,
66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,
0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,
0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,
0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,
6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,
0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,
0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,
8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,
0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,
66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,
0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,
0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,
0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,
6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,
0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,
0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,
8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,
0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,
66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,
0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,
0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,
0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,
6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,
0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,
0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,
8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,
0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,
66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,0,0,8,66,0,6,0,0,0,0,254,135,61,59,144,1,0,0,0,24,228,111,125,143,175,52,2,0,96,
66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,
8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,
1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,
128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,
48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,
0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,
192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,
24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,
3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,
0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,
0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,
1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,
0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,
6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,
0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,
0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,
0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,
0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,
0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,
0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,
0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,
0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,
0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,
0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,
0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,
0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,
0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,
0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,
0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,
0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,
0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,
0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,
0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,
0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,
0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,
0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,
0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,
0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,
0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,
0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,
0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,
0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,
0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,
0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,
0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,
0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,
0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,
0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,
0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,
0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,
0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,
0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,
0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,
0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,
0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,
0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,
0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,
0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,
0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,
0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,
0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,136,61,59,144,1,0,0,0,24,228,111,125,143,175,52,2,128,9,1,12,0,0,0,0,0,0,48,33,128,
1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,
0,0,0,0,0,0,192,132,0,6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,132,0,
6,0,0,0,0,0,0,152,16,192,0,0,0,0,0,0,0,19,2,24,0,0,0,0,0,0,96,66,0,3,0,0,0,0,0,0,76,8,96,0,0,0,0,0,0,128,9,1,12,0,0,0,0,0,0,48,33,128,1,0,0,0,0,0,0,38,4,48,0,0,0,0,0,0,192,68,2,12,0,188,93,83,253,98,185,
130,182,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* JuceDemoPluginAudioProcessorEditor::uibg_png = (const char*) resource_JuceDemoPluginAudioProcessorEditor_uibg_png;
const int JuceDemoPluginAudioProcessorEditor::uibg_pngSize = 14573;


//[EndFile] You can add extra defines here...
//[/EndFile]
