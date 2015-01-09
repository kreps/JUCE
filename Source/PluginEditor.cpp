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

    addAndMakeVisible (wetOnlyButton = new ToggleButton ("new toggle button"));
    wetOnlyButton->setButtonText (TRANS("dry off"));
    wetOnlyButton->addListener (this);

    addAndMakeVisible (delayAmountHeader = new Label ("new label",
                                                      TRANS("amount")));
    delayAmountHeader->setFont (Font (15.00f, Font::plain));
    delayAmountHeader->setJustificationType (Justification::centredLeft);
    delayAmountHeader->setEditable (false, false, false);
    delayAmountHeader->setColour (TextEditor::textColourId, Colours::black);
    delayAmountHeader->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (imageButton = new ImageButton ("new button"));
    imageButton->addListener (this);

    imageButton->setImages (false, true, true,
                            ImageCache::getFromMemory (kreps_logo_jpeg, kreps_logo_jpegSize), 1.000f, Colour (0x00000000),
                            Image(), 1.000f, Colour (0x00000000),
                            Image(), 1.000f, Colour (0x00000000));

    //[UserPreSize]
	addAndMakeVisible(resizer = new ResizableCornerComponent(this, &resizeLimits));
	resizeLimits.setSizeLimits(150, 150, 800, 300);
    //[/UserPreSize]

    setSize (400, 200);


    //[Constructor] You can add your own custom stuff here..
	// set our component's initial size to be the last one that was stored in the filter's settings
	setSize(ownerFilter->lastUIWidth, ownerFilter->lastUIHeight);
	setSize(800, 300);
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
    wetOnlyButton = nullptr;
    delayAmountHeader = nullptr;
    imageButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..

    //[/Destructor]
}

//==============================================================================
void JuceDemoPluginAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff777777));

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
    wetOnlyButton->setBounds (32, 16, 150, 24);
    delayAmountHeader->setBounds (205, 64, 80, 24);
    imageButton->setBounds (224, 280, 39, 48);
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
    else if (buttonThatWasClicked == wetOnlyButton)
    {
        //[UserButtonCode_wetOnlyButton] -- add your button handler code here..
        //[/UserButtonCode_wetOnlyButton]
    }
    else if (buttonThatWasClicked == imageButton)
    {
        //[UserButtonCode_imageButton] -- add your button handler code here..
        //[/UserButtonCode_imageButton]
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
  <BACKGROUND backgroundColour="ff777777"/>
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
  <TOGGLEBUTTON name="new toggle button" id="56ad375f8324d8aa" memberName="wetOnlyButton"
                virtualName="" explicitFocusOrder="0" pos="32 16 150 24" buttonText="dry off"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="new label" id="17713b10facdb0a1" memberName="delayAmountHeader"
         virtualName="" explicitFocusOrder="0" pos="205 64 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="amount" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <IMAGEBUTTON name="new button" id="24d8f7096728b683" memberName="imageButton"
               virtualName="" explicitFocusOrder="0" pos="224 280 39 48" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="kreps_logo_jpeg" opacityNormal="1" colourNormal="0"
               resourceOver="" opacityOver="1" colourOver="0" resourceDown=""
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


//[EndFile] You can add extra defines here...
//[/EndFile]
