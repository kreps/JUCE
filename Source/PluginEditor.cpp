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
	laf.setColour (Slider::rotarySliderFillColourId, Colour (0xffdddddd));
	laf.setColour (Slider::rotarySliderOutlineColourId, Colours::white);

	laf.setColour (TextButton::buttonColourId, Colours::white);
	laf.setColour (TextButton::textColourOffId, Colour (0xff00b5f6));
    laf.setColour(GroupComponent::textColourId, Colour(0xff000000));
	laf.setColour (TextButton::buttonOnColourId, laf.findColour (TextButton::textColourOffId));
	laf.setColour (TextButton::textColourOnId, laf.findColour (TextButton::buttonColourId));
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
    addAndMakeVisible (panSlider = new Slider ("panSlider"));
    panSlider->setRange (0, 1, 0);
    panSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    panSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    panSlider->addListener (this);

    addAndMakeVisible (delaySlider = new Slider ("delaySlider"));
    delaySlider->setTooltip (TRANS("delay gain\n"));
    delaySlider->setRange (0, 1, 0);
    delaySlider->setSliderStyle (Slider::RotaryVerticalDrag);
    delaySlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    delaySlider->setColour (Slider::trackColourId, Colours::white);
    delaySlider->setColour (Slider::textBoxHighlightColourId, Colour (0xff1111ee));
    delaySlider->setColour (Slider::textBoxOutlineColourId, Colours::grey);
    delaySlider->addListener (this);

    addAndMakeVisible (delayTimeSlider = new Slider ("delayTimeSlider"));
    delayTimeSlider->setRange (0, 1, 0);
    delayTimeSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    delayTimeSlider->setTextBoxStyle (Slider::TextBoxBelow, true, 80, 20);
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
    panHeader->setColour (Label::textColourId, Colour (0xff7e7e7e));
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
    midsideHeader->setColour (Label::textColourId, Colour (0xff909090));
    midsideHeader->setColour (TextEditor::textColourId, Colours::black);
    midsideHeader->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (saturationSlider = new Slider ("mid/side slider"));
    saturationSlider->setRange (0.001, 1, 0);
    saturationSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    saturationSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    saturationSlider->addListener (this);

    addAndMakeVisible (hpfHeader = new Label ("new label",
                                              TRANS("hi pass")));
    hpfHeader->setFont (Font ("Aharoni", 10.00f, Font::plain));
    hpfHeader->setJustificationType (Justification::centred);
    hpfHeader->setEditable (false, false, false);
    hpfHeader->setColour (Label::textColourId, Colour (0xffababab));
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

    addAndMakeVisible (reverbSizeHeader = new Label ("new label",
                                                     TRANS("room size")));
    reverbSizeHeader->setFont (Font ("Aharoni", 10.00f, Font::plain));
    reverbSizeHeader->setJustificationType (Justification::centred);
    reverbSizeHeader->setEditable (false, false, false);
    reverbSizeHeader->setColour (Label::textColourId, Colour (0xff858585));
    reverbSizeHeader->setColour (TextEditor::textColourId, Colours::black);
    reverbSizeHeader->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

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

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("saturation")));
    label->setFont (Font ("Aharoni", 10.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (Label::textColourId, Colour (0xff818181));
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (wetLabel = new Label ("new label",
                                             TRANS("wet")));
    wetLabel->setFont (Font ("Aharoni", 10.00f, Font::plain));
    wetLabel->setJustificationType (Justification::centred);
    wetLabel->setEditable (false, false, false);
    wetLabel->setColour (Label::textColourId, Colour (0xff929292));
    wetLabel->setColour (TextEditor::textColourId, Colours::black);
    wetLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    cachedImage_uibg_png = ImageCache::getFromMemory (uibg_png, uibg_pngSize);

    //[UserPreSize]
	addAndMakeVisible(resizer = new ResizableCornerComponent(this, &resizeLimits));
	resizeLimits.setSizeLimits(150, 150, 800, 300);
    //[/UserPreSize]

    setSize (450, 120);


    //[Constructor] You can add your own custom stuff here..
	// set our component's initial size to be the last one that was stored in the filter's settings
	setSize(ownerFilter->lastUIWidth, ownerFilter->lastUIHeight);
	startTimer(50);
	gainSlider->setDoubleClickReturnValue(true,0.0f);
	panSlider->setDoubleClickReturnValue(true,0.5f);
	midSideSlider->setDoubleClickReturnValue(true,0.5f);
	LookAndFeel::setDefaultLookAndFeel(&guilaf2);
	setupCustomLookAndFeelColours(guilaf);
	setupCustomLookAndFeelColours(guilaf2);
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
    reverbSizeHeader = nullptr;
    delayAmountHeader = nullptr;
    lnf3Btn = nullptr;
    guilafBtn = nullptr;
    guilaf2Btn = nullptr;
    dryOnBtn = nullptr;
    wetOnBtn = nullptr;
    gainSlider = nullptr;
    label = nullptr;
    wetLabel = nullptr;


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
                       580, 412, 400, 230,
                       RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize,
                       false);

    g.setColour (Colour (0xff373737));
    g.fillRoundedRectangle (0.0f, 0.0f, 450.0f, 120.0f, 10.000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void JuceDemoPluginAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    panSlider->setBounds (186, 39, 60, 55);
    delaySlider->setBounds (112, 151, 80, 50);
    delayTimeSlider->setBounds (192, 151, 80, 80);
    delayTimeValueLabel->setBounds (192, 131, 80, 20);
    panHeader->setBounds (186, 29, 60, 10);
    midSideSlider->setBounds (126, 39, 60, 55);
    midsideHeader->setBounds (126, 29, 60, 10);
    saturationSlider->setBounds (366, 39, 60, 55);
    hpfHeader->setBounds (246, 29, 60, 10);
    hpfSlider->setBounds (246, 39, 60, 55);
    reverbSizeSlider->setBounds (306, 39, 60, 55);
    reverbSizeHeader->setBounds (306, 29, 60, 10);
    delayAmountHeader->setBounds (152, 128, 80, 24);
    lnf3Btn->setBounds (216, 384, 88, 24);
    guilafBtn->setBounds (320, 384, 88, 24);
    guilaf2Btn->setBounds (432, 384, 88, 24);
    dryOnBtn->setBounds (23, 32, 35, 13);
    wetOnBtn->setBounds (28, 50, 36, 23);
    gainSlider->setBounds (66, 39, 60, 55);
    label->setBounds (366, 29, proportionOfWidth (0.0422f), proportionOfHeight (0.0083f));
    wetLabel->setBounds (66, 29, 60, 10);
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
		CParamSmooth paramSmooth(100.0f,44100.0f);
		getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::delayTimeParam,			paramSmooth.process((float)delayTimeSlider->getValue()));
		//CParamSmooth paramSmooth(100.0f,44100.0f);
		getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::delayTimeParam, (float)delayTimeSlider->getValue());
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
		getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::saturationAmountParam,                                                  (float)saturationSlider->getValue());
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
    else if (buttonThatWasClicked == dryOnBtn)
    {
        //[UserButtonCode_dryOnBtn] -- add your button handler code here..
		getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::dryOnParam, (dryOnBtn->getToggleState() == true) ? 1.0f : 0.0f);

        //[/UserButtonCode_dryOnBtn]
    }
    else if (buttonThatWasClicked == wetOnBtn)
    {
        //[UserButtonCode_wetOnBtn] -- add your button handler code here..
        getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::wetOnParam, (wetOnBtn->getToggleState() == true) ? 1.0f : 0.0f);
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
	gainSlider->setValue(ourProcessor->wetGain,dontSendNotification);
	delaySlider->setValue(ourProcessor->delayAmount, dontSendNotification);
	panSlider->setValue(ourProcessor->pan, dontSendNotification);
	midSideSlider->setValue(ourProcessor->midSideAmount, dontSendNotification);
	reverbSizeSlider->setValue(ourProcessor->roomSize, dontSendNotification);
	dryOnBtn->setToggleState(ourProcessor->dryOn==1.0f, dontSendNotification);
    hpfSlider->setValue(ourProcessor->hpfFrequency,dontSendNotification);
    saturationSlider->setValue(ourProcessor->saturationAmount,dontSendNotification);
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
                 initialWidth="450" initialHeight="120">
  <METHODS>
    <METHOD name="mouseEnter (const MouseEvent&amp; e)"/>
    <METHOD name="keyPressed (const KeyPress&amp; key)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ff777777">
    <IMAGE pos="580 412 400 230" resource="uibg_png" opacity="1" mode="2"/>
    <ROUNDRECT pos="0 0 450 120" cornerSize="10" fill="solid: ff373737" hasStroke="0"/>
  </BACKGROUND>
  <SLIDER name="panSlider" id="324eec4d274919f3" memberName="panSlider"
          virtualName="" explicitFocusOrder="0" pos="186 39 60 55" min="0"
          max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="delaySlider" id="37878e5e9fd60a08" memberName="delaySlider"
          virtualName="" explicitFocusOrder="0" pos="112 151 80 50" tooltip="delay gain&#10;"
          trackcol="ffffffff" textboxhighlight="ff1111ee" textboxoutline="ff808080"
          min="0" max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="delayTimeSlider" id="ead45d255e5f5831" memberName="delayTimeSlider"
          virtualName="" explicitFocusOrder="0" pos="192 151 80 80" min="0"
          max="1" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="3b34631ac55e0fe6" memberName="delayTimeValueLabel"
         virtualName="" explicitFocusOrder="0" pos="192 131 80 20" textCol="ff282828"
         edTextCol="ff000000" edBkgCol="0" labelText="time" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="ec32effd76232b82" memberName="panHeader"
         virtualName="" explicitFocusOrder="0" pos="186 29 60 10" textCol="ff7e7e7e"
         edTextCol="ff000000" edBkgCol="0" labelText="pan&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="mid/side slider" id="84706171dc5b90dd" memberName="midSideSlider"
          virtualName="" explicitFocusOrder="0" pos="126 39 60 55" min="0"
          max="1" int="0.0050000000000000001" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="fcf994bed06bf6ab" memberName="midsideHeader"
         virtualName="" explicitFocusOrder="0" pos="126 29 60 10" textCol="ff909090"
         edTextCol="ff000000" edBkgCol="0" labelText="mid/side" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="mid/side slider" id="2a577f0fc0372cc6" memberName="saturationSlider"
          virtualName="" explicitFocusOrder="0" pos="366 39 60 55" min="0.001"
          max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="f53c45ed3e69f449" memberName="hpfHeader"
         virtualName="" explicitFocusOrder="0" pos="246 29 60 10" textCol="ffababab"
         edTextCol="ff000000" edBkgCol="0" labelText="hi pass" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="hpfSlider" id="253b421224cbac37" memberName="hpfSlider"
          virtualName="" explicitFocusOrder="0" pos="246 39 60 55" tooltip="hi pass filter (hz)"
          min="20" max="10000" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.20000000000000001"/>
  <SLIDER name="new slider" id="81b8a5f3e2f90d2e" memberName="reverbSizeSlider"
          virtualName="" explicitFocusOrder="0" pos="306 39 60 55" min="0.01"
          max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="9e5a6f98ed1157ee" memberName="reverbSizeHeader"
         virtualName="" explicitFocusOrder="0" pos="306 29 60 10" textCol="ff858585"
         edTextCol="ff000000" edBkgCol="0" labelText="room size" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="17713b10facdb0a1" memberName="delayAmountHeader"
         virtualName="" explicitFocusOrder="0" pos="152 128 80 24" edTextCol="ff000000"
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
  <IMAGEBUTTON name="new button" id="e6bfce1ed1163934" memberName="dryOnBtn"
               virtualName="" explicitFocusOrder="0" pos="23 32 35 13" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="dry_off_png" opacityNormal="1" colourNormal="0"
               resourceOver="" opacityOver="1" colourOver="0" resourceDown="dry_on_png"
               opacityDown="1" colourDown="0"/>
  <IMAGEBUTTON name="new button" id="d1b3d57fbe1550e7" memberName="wetOnBtn"
               virtualName="" explicitFocusOrder="0" pos="28 50 36 23" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="wet_off_png" opacityNormal="1" colourNormal="0"
               resourceOver="" opacityOver="1" colourOver="0" resourceDown="wet_on_png"
               opacityDown="1" colourDown="0"/>
  <SLIDER name="gainSlider" id="c31acc4ca22491a9" memberName="gainSlider"
          virtualName="" explicitFocusOrder="0" pos="66 39 60 55" tooltip="gain"
          textboxbkgd="ffffff" textboxhighlight="881111ee" textboxoutline="0"
          min="0" max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.29999999999999999"/>
  <LABEL name="new label" id="dce9f23eacc8bf8e" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="366 29 4.222% 0.833%" textCol="ff818181"
         edTextCol="ff000000" edBkgCol="0" labelText="saturation" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="4cc590f60a8a610f" memberName="wetLabel"
         virtualName="" explicitFocusOrder="0" pos="66 29 60 10" textCol="ff929292"
         edTextCol="ff000000" edBkgCol="0" labelText="wet" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

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

// JUCER_RESOURCE: uibg_png, 63194, "../Graphics/uibg.png"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_uibg_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,1,144,0,0,0,230,8,2,0,0,0,116,209,68,243,0,0,0,4,103,65,77,65,0,
0,175,200,55,5,138,233,0,0,0,25,116,69,88,116,83,111,102,116,119,97,114,101,0,65,100,111,98,101,32,73,109,97,103,101,82,101,97,100,121,113,201,101,60,0,0,246,108,73,68,65,84,120,218,236,189,231,147,101,
201,117,39,150,153,215,62,95,174,221,244,12,48,192,96,0,34,232,192,8,44,29,60,184,34,185,17,90,44,9,254,45,218,15,218,15,138,253,123,196,88,130,10,129,95,180,223,36,18,2,68,134,66,4,197,37,57,131,1,102,
166,109,249,170,231,174,205,220,227,50,223,43,239,187,91,90,212,0,221,213,175,78,229,189,55,111,230,201,99,126,231,119,244,191,255,15,255,81,41,101,173,109,109,171,156,83,90,71,198,104,99,98,19,213,77,
237,148,139,163,24,62,62,85,38,50,81,67,50,90,27,13,18,90,107,165,225,159,248,1,124,167,81,22,254,115,214,226,223,10,132,248,83,21,198,129,79,46,121,173,187,150,129,27,73,226,24,238,15,31,3,159,194,182,
206,194,157,227,99,221,198,213,103,147,241,218,218,198,43,120,76,248,103,170,106,117,141,47,147,192,31,252,198,240,109,225,71,26,190,213,52,38,126,166,21,92,254,213,200,180,58,130,215,33,63,65,25,39,95,
176,182,240,133,152,166,109,225,39,203,50,240,187,252,202,88,38,138,162,157,157,237,225,104,229,212,215,26,100,234,166,225,113,238,76,6,158,207,209,50,55,109,219,226,195,186,214,226,139,162,47,120,161,
184,47,12,253,22,141,200,155,5,54,13,62,145,50,74,246,150,225,199,196,73,179,52,29,40,36,227,152,8,22,134,197,181,138,43,196,209,132,157,182,108,12,44,27,248,33,202,200,16,40,136,67,226,36,242,220,227,
47,211,219,144,127,208,15,253,149,223,128,175,216,226,94,141,224,161,227,200,127,70,247,90,53,21,79,101,75,43,227,84,153,26,100,96,182,64,198,182,145,137,225,195,166,109,96,14,232,183,44,207,48,171,36,
88,158,164,20,224,111,109,149,227,15,175,116,173,187,150,129,123,172,234,154,223,28,124,175,105,213,129,78,230,55,118,11,87,127,101,143,9,95,237,117,20,22,174,111,124,95,6,95,19,173,104,120,179,78,203,
50,229,61,192,255,188,27,153,200,105,27,100,224,57,249,117,224,86,195,165,130,219,8,214,24,191,23,219,182,113,20,193,227,31,145,129,189,71,175,12,247,167,134,205,89,165,113,12,26,228,212,215,26,100,178,
36,5,53,113,151,50,184,65,104,107,212,240,61,200,128,22,74,64,193,129,242,114,42,17,85,165,89,55,88,37,138,4,143,207,40,134,221,4,51,18,179,198,18,141,129,26,72,20,183,70,29,132,58,145,166,20,199,209,
240,18,89,1,153,211,150,77,205,119,132,170,205,177,117,129,103,71,208,68,188,212,189,222,146,223,148,15,233,7,116,214,200,231,71,245,87,248,62,124,174,79,172,175,147,50,106,73,242,178,218,48,70,59,137,
103,77,27,81,240,164,227,113,81,209,211,28,57,4,78,200,24,13,255,135,169,73,64,241,193,196,193,50,114,110,105,3,224,81,137,90,10,230,143,100,44,140,9,6,2,156,4,238,234,215,186,83,25,56,124,104,241,105,
186,217,96,24,202,139,188,249,213,45,239,211,187,127,204,107,159,93,154,30,155,85,3,175,90,62,228,229,167,6,222,153,113,139,109,115,19,25,58,6,156,172,83,146,209,184,147,23,50,248,68,145,230,109,130,47,
133,199,99,67,24,111,83,139,73,117,76,134,95,153,35,205,5,255,107,233,235,212,215,26,100,248,136,189,11,25,203,22,58,136,26,187,180,223,98,248,89,221,214,103,43,184,56,162,243,156,20,110,106,149,173,189,
140,22,17,82,207,168,196,116,131,134,2,108,37,7,246,166,246,254,10,44,141,11,150,13,13,36,38,27,26,91,98,6,42,81,133,172,158,130,154,210,222,236,181,244,13,139,144,126,92,86,58,65,237,240,236,168,165,
97,78,202,28,81,82,44,169,79,104,55,125,170,22,139,141,95,38,116,227,11,171,59,77,98,176,114,225,147,132,85,241,105,50,73,28,181,244,218,90,219,144,179,103,108,75,70,242,209,51,159,39,195,58,90,109,138,
159,199,94,245,90,119,45,227,61,20,118,176,220,242,46,186,149,171,195,191,211,36,121,5,143,121,109,133,5,171,28,182,7,157,47,184,217,232,16,86,94,105,43,217,78,104,32,223,72,134,119,192,81,153,150,100,
76,208,182,248,88,70,54,135,108,17,218,82,172,39,216,236,245,33,136,101,25,39,175,76,185,196,36,214,59,200,167,191,86,47,35,191,124,55,50,232,24,162,93,226,76,56,161,193,33,196,95,53,231,42,65,141,211,
3,50,100,4,160,137,134,63,37,53,35,143,9,186,91,209,200,138,163,22,96,72,130,106,182,104,178,157,179,108,192,111,109,229,162,34,163,113,250,189,25,197,39,133,165,11,24,239,155,59,239,35,226,103,226,208,
123,253,162,143,249,140,62,32,180,112,41,245,17,153,160,154,156,58,98,133,157,162,154,244,89,102,90,92,214,213,85,173,220,8,77,81,82,240,45,90,37,32,3,115,21,20,188,89,82,240,142,78,69,131,167,159,107,
154,246,181,90,230,23,200,68,81,196,135,81,26,165,173,147,91,5,253,11,167,220,173,92,61,142,82,24,254,21,60,38,110,23,211,9,225,149,229,216,16,235,223,36,162,13,230,99,139,203,50,198,36,176,145,224,131,
36,206,131,140,165,205,168,148,108,154,171,202,224,145,166,213,49,25,67,107,4,54,36,124,18,69,153,149,141,177,144,137,208,1,113,100,72,104,86,82,240,13,172,165,22,135,195,104,17,186,90,20,139,89,146,49,
252,202,234,186,17,253,8,155,243,140,215,26,100,192,39,184,35,25,156,91,135,247,220,160,149,39,166,250,85,149,160,230,183,134,202,66,163,25,165,130,30,112,70,161,34,35,141,135,246,93,18,39,48,214,181,
150,77,164,208,205,162,65,41,158,3,147,73,33,66,28,153,143,64,14,141,181,104,78,130,190,139,196,10,161,39,247,118,185,34,207,157,239,86,69,116,168,120,25,121,52,26,156,12,97,237,188,140,87,211,122,177,
14,89,134,215,42,71,105,151,215,106,12,19,125,57,43,87,7,131,208,202,193,169,150,21,124,131,10,62,156,249,139,245,23,100,208,91,148,216,158,190,138,213,173,95,129,245,78,241,75,71,246,52,237,34,201,24,
224,114,167,141,119,11,87,7,35,244,174,31,33,248,176,232,43,93,107,19,242,234,132,143,42,87,211,50,141,80,83,208,57,13,167,148,19,79,239,178,50,238,136,140,209,33,86,21,2,85,176,18,172,109,48,116,160,
200,205,137,48,78,141,81,225,8,238,202,104,142,248,136,33,133,47,8,12,21,21,137,179,41,254,199,66,38,188,50,62,32,125,88,250,244,215,186,144,113,119,37,3,223,88,12,146,196,188,147,81,227,216,230,170,74,
16,149,138,165,107,193,228,152,133,25,131,86,2,173,40,199,119,163,81,51,94,123,217,224,97,64,113,126,122,35,117,132,203,39,146,128,153,162,223,34,101,193,134,30,30,25,206,194,177,167,240,254,37,70,73,
1,80,113,3,91,58,156,200,125,131,159,68,108,29,195,152,244,140,162,68,200,30,116,97,253,144,12,174,13,212,44,148,97,112,100,6,129,179,11,194,9,204,33,205,21,6,157,216,35,61,85,193,179,54,167,79,240,42,
24,71,247,134,25,169,246,136,93,102,86,240,224,239,192,80,203,202,27,46,106,240,164,148,184,42,153,90,70,2,132,87,179,186,213,43,176,222,99,140,131,214,240,233,177,140,129,187,37,223,193,136,131,112,135,
143,192,50,244,190,213,53,54,24,167,159,40,209,64,175,158,226,78,20,58,33,119,134,70,166,35,240,178,50,62,72,43,65,16,50,198,93,75,50,154,84,158,242,154,134,54,128,138,226,164,170,53,143,163,73,197,59,
142,13,91,9,17,27,186,178,198,208,50,173,37,244,140,22,50,78,45,146,60,17,173,73,216,12,176,99,78,125,173,65,6,20,10,166,143,110,91,70,158,110,225,4,95,83,9,106,199,78,54,110,31,118,176,156,120,193,248,
11,28,36,187,230,178,209,28,186,66,153,150,38,60,54,49,217,33,134,231,210,120,175,14,140,26,159,205,213,226,210,129,246,129,241,141,242,225,45,74,251,138,129,134,73,75,167,194,3,170,133,117,239,95,20,
110,183,56,118,222,217,39,103,119,177,122,121,30,232,0,51,60,7,118,105,30,240,72,60,166,224,27,116,116,21,175,176,37,5,31,195,131,208,165,225,121,72,135,182,104,153,59,84,76,18,224,92,86,222,228,102,195,
124,52,46,140,67,135,97,26,101,23,30,248,228,179,216,229,251,185,107,235,157,151,90,64,9,44,103,12,216,9,185,133,171,55,77,221,212,119,250,8,44,67,63,189,206,38,36,149,96,216,240,225,52,57,153,6,112,162,
54,150,195,42,108,203,92,90,6,151,144,22,97,114,232,228,160,118,140,104,193,95,199,52,255,108,50,126,254,252,41,12,5,103,222,195,135,143,210,188,139,143,230,108,36,110,160,117,226,8,225,254,50,100,94,
193,67,180,116,236,147,123,34,59,143,54,47,190,178,8,157,98,3,190,252,216,182,103,189,214,32,115,12,32,114,115,25,158,7,58,161,27,31,193,150,104,26,207,204,229,149,96,24,135,211,160,148,82,113,177,73,
40,157,170,47,191,59,112,112,215,80,208,6,29,196,22,175,14,106,40,45,171,90,194,5,78,225,210,138,92,136,232,195,140,194,8,104,209,146,110,139,16,71,210,128,70,131,49,193,78,132,107,160,67,71,50,28,11,
146,243,139,237,96,35,15,203,62,59,201,24,121,239,112,63,244,154,88,8,67,49,24,221,35,25,54,32,57,222,109,173,79,32,72,212,18,103,27,173,45,21,125,253,91,223,245,138,80,176,82,130,150,226,249,101,229,
167,37,147,26,162,232,114,104,112,24,140,30,67,137,242,14,74,215,133,240,159,63,71,113,168,99,215,138,216,139,150,235,137,76,136,236,41,127,63,20,99,138,57,19,228,83,66,60,185,100,181,158,49,206,101,174,
21,100,228,84,146,128,163,102,29,203,129,146,27,142,204,50,101,57,207,242,206,13,7,185,140,12,43,2,88,1,232,140,200,217,197,62,124,72,0,105,56,18,96,253,29,147,193,3,205,114,36,8,173,122,77,176,9,75,177,
33,227,227,147,236,196,93,36,3,227,180,108,10,113,228,155,119,17,189,70,195,171,159,92,185,150,84,128,221,219,221,234,247,251,112,3,69,89,30,142,15,167,147,49,76,84,39,235,176,94,224,247,206,103,190,60,
186,150,4,14,107,52,75,144,26,158,11,126,101,140,152,129,7,172,202,162,211,233,158,250,90,131,12,167,89,111,81,38,224,151,34,10,30,241,198,36,75,194,158,63,255,199,222,17,234,62,252,21,107,252,30,20,240,
26,237,58,212,41,75,187,227,196,146,176,44,211,210,180,179,25,193,199,198,116,114,248,244,201,167,91,91,219,251,251,123,121,150,130,165,195,155,19,67,67,33,156,206,33,39,177,128,100,105,197,75,247,28,
121,123,202,47,59,209,6,70,7,200,5,206,15,199,236,141,143,241,155,0,214,244,239,50,34,51,153,35,109,218,67,211,88,189,243,56,240,124,24,103,160,233,99,129,232,119,191,246,13,92,124,180,236,248,84,36,5,
31,241,10,115,142,51,128,138,67,16,244,26,98,94,220,134,100,200,176,2,37,110,13,71,124,41,3,200,50,188,193,224,167,17,57,134,45,41,230,112,173,112,20,83,94,214,130,214,147,67,88,146,74,188,58,156,114,
34,131,58,139,16,24,13,29,74,148,104,180,173,61,62,14,44,5,178,177,207,187,214,169,50,44,64,19,100,34,198,245,208,172,221,124,100,150,105,234,58,205,178,27,14,114,25,25,37,246,252,149,55,161,146,224,168,
120,49,18,134,215,108,150,219,144,138,190,132,12,3,172,2,84,194,113,148,133,189,25,57,231,104,3,194,63,159,62,249,100,94,20,85,85,131,117,208,239,245,224,246,138,162,56,60,220,135,183,220,233,245,89,134,
34,92,146,211,167,199,227,8,44,45,15,205,168,14,58,207,105,203,121,128,41,62,89,89,150,121,158,159,250,90,131,76,48,124,110,34,227,66,158,148,236,77,45,202,197,45,230,95,171,43,41,193,16,57,97,232,150,
172,124,138,82,105,127,0,200,235,230,68,23,250,146,49,230,94,157,4,4,57,71,193,147,195,199,6,135,148,247,247,118,58,157,28,238,173,170,202,131,131,131,241,248,48,207,242,36,65,135,145,35,229,49,158,16,
120,230,5,103,150,149,33,35,1,140,79,230,194,3,177,109,102,36,121,232,115,205,244,197,33,72,182,10,41,132,173,45,233,23,69,247,108,208,239,141,172,119,200,90,23,204,232,144,77,12,227,44,84,21,123,151,
49,155,166,124,154,57,142,107,58,132,249,37,113,66,86,183,40,120,86,131,236,232,157,244,183,201,222,67,165,204,254,32,103,136,40,117,173,96,156,166,105,8,162,117,177,69,29,113,108,132,94,30,222,15,57,
226,224,137,146,76,82,213,85,176,204,49,144,209,178,141,124,59,22,62,222,234,169,40,1,50,73,111,238,59,192,80,119,225,128,156,148,225,117,118,35,180,151,196,79,196,17,163,216,129,12,203,225,240,139,100,
100,157,113,184,55,74,106,80,104,184,23,76,139,192,9,88,57,176,143,92,12,211,90,22,237,124,62,99,191,175,169,171,137,181,160,179,224,107,54,155,237,108,111,195,97,184,177,241,32,73,51,165,23,113,124,254,
43,198,100,8,46,215,68,235,5,26,254,4,248,131,33,96,119,9,34,17,237,108,18,195,247,179,64,178,121,55,196,111,182,171,64,246,16,16,143,131,147,246,210,73,156,54,136,80,87,199,64,142,168,137,40,248,130,
230,88,140,64,72,130,100,27,246,123,172,132,178,90,81,135,240,94,226,228,147,79,62,42,139,57,44,155,56,73,70,195,81,81,22,211,233,244,147,143,63,90,89,91,187,127,255,17,72,38,81,218,16,234,56,34,181,32,
10,219,159,15,236,197,97,136,138,34,116,49,174,71,121,215,146,18,164,216,19,154,144,184,235,65,229,217,165,123,22,16,63,198,167,104,25,99,166,174,105,150,151,49,105,254,86,108,46,239,153,161,254,101,219,
156,44,182,83,144,238,146,86,176,28,167,192,52,25,152,72,138,206,243,128,98,231,248,251,177,0,39,69,239,240,122,222,28,195,129,106,196,215,94,10,186,141,155,65,226,241,134,163,119,116,212,40,6,250,130,
12,31,47,191,68,186,95,120,33,78,211,92,117,19,34,174,154,194,178,178,74,34,77,80,31,71,147,129,58,5,65,118,30,121,112,150,12,133,252,44,173,1,151,244,202,56,43,240,0,164,44,146,118,240,126,241,232,214,
168,194,230,32,255,201,127,217,225,99,215,151,169,24,80,85,96,76,128,206,2,59,107,103,103,103,50,153,188,247,222,251,38,74,248,33,48,222,97,20,187,129,111,6,210,29,13,46,198,247,196,176,122,81,63,88,77,
46,57,39,224,217,131,101,212,197,229,149,32,153,103,12,17,112,82,79,66,90,239,212,215,205,187,172,33,55,8,71,118,169,193,26,171,56,6,191,147,236,12,216,146,13,220,160,179,179,114,58,159,78,225,247,203,
166,4,171,22,198,30,244,251,240,63,152,243,253,189,61,184,240,250,250,125,139,165,69,120,49,120,145,236,198,137,55,74,223,180,242,16,236,221,43,50,181,156,91,96,75,245,82,13,76,237,239,217,42,15,204,140,
142,215,201,28,215,12,100,47,71,108,197,243,149,140,150,195,55,20,37,157,137,116,103,5,15,127,159,165,224,151,207,124,240,80,184,176,35,230,108,168,146,83,88,93,5,186,13,3,138,242,70,165,139,202,155,199,
9,247,195,249,175,95,34,221,47,68,186,95,111,19,178,129,236,229,97,169,53,92,19,195,21,112,226,3,170,139,101,116,212,38,189,121,156,149,232,8,148,105,51,201,92,19,227,218,99,252,16,122,52,104,8,238,238,
110,149,179,138,131,44,38,132,55,208,115,81,101,81,194,125,194,94,2,159,238,103,63,251,224,11,239,127,153,143,141,38,88,247,175,27,233,190,64,177,123,25,212,209,160,192,227,24,92,167,148,32,81,53,57,22,
87,81,130,92,23,104,216,53,130,185,197,114,68,219,158,250,186,27,43,197,3,142,35,241,42,233,233,238,64,247,99,138,97,147,209,235,26,133,105,177,76,167,224,163,192,253,252,195,199,255,15,3,226,217,16,193,
160,97,81,192,13,245,251,253,233,108,182,187,189,61,157,140,223,253,220,23,180,137,157,243,117,191,2,225,197,99,155,103,18,81,245,77,187,180,6,196,252,225,120,37,58,146,24,63,59,182,212,205,85,150,177,
227,113,208,117,211,138,237,86,195,65,46,154,195,56,64,90,217,162,11,57,29,152,56,254,39,107,171,115,20,60,202,184,134,117,176,128,116,188,1,127,121,171,155,239,204,89,235,209,240,78,74,171,2,170,62,137,
170,250,202,214,187,204,227,127,99,72,247,235,109,66,94,252,12,50,104,173,56,20,156,158,95,164,95,46,144,1,103,160,201,134,19,196,217,204,187,205,60,167,37,67,217,34,174,205,245,90,169,174,235,173,151,
155,20,83,143,148,15,120,41,15,31,197,187,109,4,175,8,2,92,69,207,182,4,86,131,81,182,251,181,35,221,61,138,29,225,155,86,158,78,172,15,142,174,248,130,217,203,131,28,149,143,3,106,118,232,24,78,121,242,
117,91,15,154,195,88,184,142,71,122,216,215,125,120,17,115,87,236,233,57,232,169,86,181,226,177,123,152,250,193,206,78,67,62,138,175,159,147,228,32,56,101,147,233,52,142,227,78,183,83,85,245,199,191,248,
232,243,239,125,201,113,181,175,226,138,40,101,213,17,64,37,162,234,173,245,65,116,14,186,43,137,228,221,206,50,246,82,30,176,170,151,230,208,35,221,57,48,232,15,1,182,114,185,126,162,229,224,223,137,
243,92,160,85,4,99,107,208,190,10,153,72,73,9,82,238,230,98,171,27,95,94,35,22,181,87,222,118,161,224,253,161,212,156,87,126,117,250,193,21,234,102,255,91,67,186,123,22,132,43,110,66,74,122,183,140,80,
247,104,120,77,39,158,223,75,234,124,25,147,149,233,96,162,108,82,31,174,35,232,133,0,218,124,160,134,43,241,210,123,246,236,83,54,202,142,22,176,137,221,196,127,242,170,29,142,86,56,130,235,147,86,142,
34,214,156,127,120,13,72,119,122,234,150,243,216,132,188,111,185,122,146,19,108,8,101,186,162,18,228,96,243,18,138,221,241,218,63,127,85,83,112,57,202,85,122,207,172,193,103,7,237,193,84,207,26,180,46,
196,134,162,25,67,25,216,0,117,93,237,236,108,129,118,72,146,152,48,204,54,20,39,50,194,160,174,106,248,149,52,73,131,230,128,107,105,201,34,248,165,37,24,56,220,137,9,161,55,238,116,25,115,194,145,171,
71,165,94,158,126,118,28,233,78,113,40,169,143,224,228,232,49,187,192,199,166,172,245,112,118,239,45,82,6,147,207,188,203,89,221,203,215,106,41,187,193,227,136,23,207,35,32,148,203,242,9,116,37,195,193,
200,225,230,196,250,252,37,210,253,142,145,238,81,119,154,245,42,88,132,213,225,144,14,240,16,55,22,69,231,48,77,130,59,124,54,155,205,167,83,14,208,98,84,222,36,148,239,83,28,234,130,47,76,15,145,243,
210,31,12,214,215,239,121,125,102,25,233,142,161,140,215,132,116,247,96,14,86,167,22,12,19,159,50,195,8,47,28,183,173,177,215,81,130,38,85,166,13,40,118,169,181,61,237,117,43,31,197,71,109,213,102,107,
122,181,113,237,150,219,106,116,195,37,82,198,3,32,88,134,189,162,167,79,63,173,192,79,210,74,238,86,135,20,174,102,234,11,77,38,48,24,102,27,27,247,56,14,227,113,16,140,77,177,234,72,145,163,166,136,
144,186,35,95,91,98,99,30,149,78,135,68,26,128,153,199,145,238,1,243,202,88,101,142,83,4,20,187,150,135,164,66,231,37,20,187,15,150,59,46,42,12,37,69,231,91,221,112,45,67,177,118,231,189,2,196,200,45,
229,125,249,118,195,56,234,42,7,87,120,46,222,194,191,68,186,223,41,210,61,238,212,113,175,172,230,89,51,233,73,40,201,151,114,20,197,124,124,184,207,148,3,172,161,138,162,132,127,34,10,93,73,244,39,20,
197,11,212,11,180,88,20,129,58,24,140,86,24,229,99,149,84,108,176,31,64,59,234,117,33,221,149,204,54,237,255,155,160,216,131,140,20,30,10,71,0,23,150,156,97,142,113,57,162,117,35,53,0,79,112,174,138,173,
118,91,108,204,5,163,149,242,229,119,104,220,78,103,224,243,77,64,87,50,116,75,24,175,248,182,249,53,25,65,87,244,251,131,181,245,251,110,9,185,178,108,218,28,187,31,246,220,79,89,126,98,132,122,32,133,
20,14,58,143,131,161,130,74,144,137,121,28,125,234,50,102,123,40,34,216,188,161,96,127,152,195,139,144,238,62,120,201,103,41,171,43,210,129,48,98,19,208,240,65,17,106,109,47,111,117,195,35,115,5,162,102,
116,153,207,254,26,21,49,240,138,233,31,174,97,189,179,39,12,50,112,238,253,18,233,126,215,72,119,29,55,81,239,176,46,99,208,86,214,255,8,102,126,58,153,236,237,236,36,104,161,215,188,233,200,31,136,170,
170,228,98,102,217,156,124,242,135,67,159,76,3,112,94,70,160,174,70,107,117,219,240,128,206,7,88,201,110,123,61,72,119,158,7,206,202,41,202,73,122,144,179,68,161,47,175,4,57,236,189,120,58,218,235,96,
106,249,124,219,25,171,218,90,80,193,29,157,143,212,112,162,102,59,237,142,21,251,19,7,129,125,51,155,77,14,246,247,152,52,133,147,102,179,249,188,44,203,24,3,79,168,49,3,195,31,98,45,153,128,76,106,209,
77,127,56,196,241,17,97,25,83,173,98,123,193,242,67,127,152,106,87,104,151,177,162,1,153,54,18,51,83,208,249,75,245,45,134,206,143,6,141,81,203,208,57,2,193,168,99,53,48,4,105,114,140,92,210,82,216,96,
57,82,134,89,194,211,14,1,137,126,33,138,221,43,117,31,131,11,166,135,143,116,134,131,226,52,136,214,57,7,142,224,107,21,199,197,225,90,9,227,214,153,54,139,201,195,174,119,112,113,230,130,86,195,101,
239,231,44,148,64,36,5,77,55,173,146,101,72,242,221,149,218,6,25,9,186,95,29,201,69,136,196,214,91,184,136,57,68,22,77,173,24,42,73,6,14,3,26,143,202,180,117,103,117,23,70,106,199,171,204,102,201,145,
248,157,205,23,140,131,152,205,103,12,122,6,171,10,102,24,214,106,140,149,55,66,212,25,192,205,180,30,232,156,109,219,36,77,59,121,231,209,23,179,249,94,147,68,49,89,82,118,193,160,228,77,27,68,219,48,
26,30,28,2,14,253,28,5,127,240,14,185,69,16,137,228,34,105,222,196,114,39,98,79,246,113,46,175,4,5,156,232,167,43,128,28,27,156,219,211,77,54,231,124,14,214,197,235,122,173,208,229,174,221,67,246,44,127,
175,227,201,225,238,206,86,154,164,8,87,68,45,42,249,87,152,246,56,138,2,236,192,249,232,21,106,72,142,159,105,149,167,89,191,215,31,141,86,73,233,72,169,225,25,154,97,105,249,33,80,193,52,158,164,140,
242,33,81,154,232,144,211,63,103,25,75,97,53,65,201,78,202,16,202,31,177,208,116,231,252,90,13,207,33,210,232,156,83,202,68,216,204,214,131,86,177,114,149,234,33,148,90,62,40,36,186,116,53,171,91,74,128,
248,164,109,107,34,13,105,88,193,19,153,44,170,93,193,217,222,113,157,170,191,31,125,42,74,224,182,174,206,54,227,157,62,194,162,96,245,90,27,149,182,146,81,225,64,98,184,13,151,197,56,225,174,82,124,
110,47,201,100,131,41,252,168,216,29,58,98,148,165,157,101,183,55,159,207,102,83,74,162,99,241,67,85,85,13,49,8,227,90,68,230,166,134,248,161,200,240,151,162,102,103,60,106,59,201,178,60,207,239,191,245,
72,69,135,217,112,86,30,244,12,177,218,90,21,98,104,142,241,253,232,108,48,199,3,249,83,17,217,5,203,89,115,134,195,220,34,136,132,65,140,4,184,177,190,14,237,202,74,208,49,56,209,83,245,82,101,155,110,
156,128,28,17,111,121,134,57,134,5,119,206,60,50,247,27,213,190,104,55,25,76,207,38,237,230,139,79,208,165,111,237,164,26,35,230,147,230,28,174,2,211,110,252,23,83,62,208,11,197,10,244,136,138,211,65,
77,128,9,12,106,238,87,31,252,198,11,183,101,185,22,138,174,197,161,227,171,46,63,19,35,240,64,100,112,124,214,12,218,87,131,187,99,50,48,87,167,143,195,126,155,28,84,134,140,27,34,240,91,70,186,47,31,
2,113,68,72,119,161,34,242,135,0,162,49,90,62,117,97,164,107,195,178,41,115,137,79,16,81,98,152,21,234,34,132,65,30,34,35,221,225,42,60,78,134,71,199,29,194,196,127,137,116,191,6,210,29,215,95,86,214,
211,142,178,145,15,228,170,157,205,151,243,98,142,196,12,224,28,68,18,105,15,198,120,75,180,33,20,142,210,62,150,162,185,214,159,241,92,253,149,149,213,141,251,160,253,154,89,158,116,139,40,30,216,86,
24,129,3,210,29,110,131,161,3,175,18,233,30,51,151,215,18,138,93,16,216,215,67,177,19,85,47,3,24,233,85,158,13,114,140,83,246,127,97,168,53,189,10,223,188,112,155,1,197,14,119,180,181,249,162,152,151,
117,93,113,216,185,42,43,174,45,33,219,147,168,23,48,223,209,38,152,34,192,205,203,209,23,86,183,89,150,117,242,252,209,195,207,68,46,90,215,171,123,241,65,64,204,171,72,95,105,71,115,2,142,195,4,240,
92,53,133,249,217,103,103,69,205,218,7,29,160,32,131,185,100,183,144,33,228,121,0,119,24,242,25,165,252,203,207,243,233,156,238,152,60,182,53,69,167,12,85,36,69,75,92,236,250,250,22,53,111,37,254,63,41,
93,159,97,93,152,81,124,173,86,181,199,120,223,61,252,226,174,96,226,13,193,166,151,115,171,4,86,78,56,255,74,197,10,17,8,84,118,33,19,83,199,129,144,163,61,95,166,52,115,102,89,59,150,199,165,162,83,
189,60,206,109,201,196,164,92,202,186,92,206,25,51,66,52,141,79,151,9,21,109,158,142,22,150,84,205,78,49,158,22,100,2,4,78,33,216,6,73,191,192,67,184,232,240,216,112,92,207,198,147,241,120,12,107,102,
54,155,193,185,141,231,91,35,199,102,72,168,81,82,220,122,232,155,243,116,186,248,193,112,52,90,223,184,239,200,254,170,103,105,212,153,233,108,170,231,61,194,211,131,82,140,213,107,66,186,35,94,188,110,
130,146,37,183,70,16,216,87,42,229,57,2,114,36,230,3,14,72,44,35,194,227,83,16,225,156,88,208,29,157,31,170,9,250,191,196,25,5,63,221,222,122,94,20,69,67,129,33,19,225,165,9,47,178,84,102,44,238,182,18,
107,75,25,118,24,153,226,117,109,184,186,126,239,1,72,77,244,116,168,6,187,237,30,7,221,125,62,241,210,59,72,47,168,69,241,221,217,154,109,186,86,18,142,204,58,19,24,150,189,12,154,228,74,100,216,140,
210,130,203,241,52,197,214,40,227,23,137,59,27,233,78,243,139,229,141,84,84,9,255,48,152,170,139,220,13,184,216,217,116,199,109,224,75,144,180,84,68,82,183,15,239,219,211,44,104,178,147,221,50,210,253,
174,97,226,158,150,243,174,152,191,95,25,172,225,218,50,161,126,213,211,126,42,88,82,138,81,221,28,134,91,98,178,101,54,180,56,223,115,117,199,232,152,223,26,124,62,30,239,163,118,171,42,222,48,243,162,
160,115,216,121,117,160,137,203,193,178,143,67,176,59,138,242,154,24,212,193,104,101,180,186,178,26,199,169,35,149,132,92,113,85,26,101,179,102,214,229,2,23,142,250,59,159,108,125,149,72,119,62,141,72,
57,194,193,128,40,118,133,196,167,87,68,177,51,115,11,163,216,105,91,46,83,245,158,133,8,55,74,234,195,70,102,0,63,59,180,227,208,45,98,62,155,76,232,120,152,76,166,224,217,57,226,154,225,51,9,237,36,
38,225,208,106,9,66,138,182,45,146,17,144,230,132,217,134,227,129,44,39,53,182,147,129,238,13,244,224,192,29,42,217,173,234,146,59,72,208,116,74,136,172,73,79,51,65,16,7,52,29,251,236,158,223,37,4,193,
151,100,56,39,19,130,107,62,201,140,197,94,174,225,76,38,247,8,50,167,115,186,35,138,44,9,149,74,70,138,15,132,240,102,233,48,73,196,198,211,250,108,110,120,63,14,147,22,74,174,212,202,73,133,166,65,204,
204,138,28,45,14,52,0,238,186,215,186,158,140,111,36,197,169,15,198,76,99,42,32,146,119,166,253,89,117,77,25,19,240,32,23,141,83,85,229,124,62,59,41,211,32,130,105,226,154,246,86,238,231,164,12,231,109,
57,164,228,105,48,180,19,239,93,138,153,131,12,190,68,51,131,191,171,25,150,185,242,251,157,23,51,208,80,101,89,193,62,140,253,217,163,22,212,61,214,122,102,3,198,91,121,234,118,220,93,24,73,73,211,253,
253,125,238,80,197,215,106,230,89,156,68,224,58,240,130,225,19,59,192,160,213,82,13,91,184,193,219,125,107,65,70,86,145,191,115,67,72,183,136,217,68,217,219,65,42,228,6,12,82,86,112,172,40,99,47,227,151,
180,245,65,122,206,10,170,243,87,172,210,129,141,2,119,208,64,131,65,91,170,5,109,158,59,216,223,69,3,185,172,144,242,37,66,91,210,8,135,84,136,212,251,150,96,129,112,133,20,61,88,91,221,110,119,52,26,
41,195,41,117,240,248,236,92,149,67,51,8,173,36,46,191,131,66,171,17,193,169,19,8,153,205,52,95,15,232,161,252,42,80,92,56,126,46,1,205,123,90,8,231,101,152,116,47,242,244,21,218,147,73,157,199,233,142,
166,59,54,237,104,110,96,81,107,48,104,83,242,95,184,113,27,91,239,71,75,144,172,231,160,240,168,60,229,56,34,79,254,246,43,226,116,247,252,130,119,197,252,125,121,88,195,238,246,86,49,159,191,251,222,
251,199,100,64,91,61,123,242,233,250,198,189,33,152,33,87,189,31,120,5,216,172,16,23,92,13,91,14,84,140,110,164,137,11,241,46,241,89,103,164,189,157,34,232,166,165,10,15,127,204,40,134,71,37,146,171,182,
109,70,36,84,202,198,1,5,181,183,183,35,45,164,104,123,52,181,213,158,101,204,163,217,29,209,146,4,34,63,132,9,70,20,217,133,173,126,120,112,144,119,186,211,233,56,239,244,189,57,146,59,59,1,183,21,206,
52,30,134,240,52,246,181,112,186,147,142,177,145,143,183,74,47,149,11,184,216,177,138,163,42,139,52,203,153,145,70,179,217,194,156,209,84,227,145,122,46,118,95,79,237,17,234,82,120,79,143,6,6,132,78,225,
150,246,221,65,171,153,109,213,150,69,49,47,74,154,100,246,94,132,26,192,235,150,208,7,84,244,5,238,127,50,18,171,178,6,45,26,199,241,238,254,238,91,189,158,34,52,60,252,194,76,207,187,174,211,49,121,
225,138,235,237,178,16,45,32,88,105,36,7,128,143,54,248,216,159,145,179,198,17,101,59,118,123,104,196,154,9,63,242,21,51,124,210,59,194,28,159,142,116,63,98,81,223,128,37,154,18,31,98,148,34,104,133,80,
236,180,172,245,137,18,164,229,54,60,92,166,228,233,132,104,137,44,223,143,224,68,238,192,87,226,250,164,187,99,254,158,95,5,214,192,49,230,99,50,134,80,43,215,128,71,196,105,173,243,221,216,183,39,49,
42,228,157,105,95,181,153,158,247,36,143,163,108,8,124,200,107,146,243,131,75,156,84,144,65,75,221,86,26,102,178,213,194,80,233,92,141,182,85,43,42,79,155,178,154,101,68,14,35,153,104,38,242,54,62,235,
163,23,1,32,42,244,73,153,165,163,40,10,80,88,228,122,160,120,44,224,1,41,12,122,93,156,238,173,245,120,78,130,158,9,232,231,40,53,238,178,130,195,9,163,188,102,49,155,237,237,109,223,127,240,40,201,187,
204,197,206,191,114,108,85,159,138,80,231,170,73,182,239,12,189,153,70,53,65,102,103,119,139,237,53,186,19,164,106,81,46,96,62,181,79,107,56,239,174,105,246,96,88,173,99,9,225,100,210,233,116,231,179,
89,150,119,249,90,149,195,2,157,200,26,43,244,118,230,138,187,204,5,38,59,126,25,134,96,119,188,189,99,9,92,18,125,27,190,91,235,169,238,85,192,118,32,52,76,89,229,75,41,4,51,140,128,167,72,201,181,212,
121,156,238,55,129,92,31,65,204,147,217,216,218,134,43,111,56,182,173,4,44,170,142,21,48,178,76,67,128,58,10,91,44,53,26,81,238,238,106,89,45,213,139,222,33,243,247,69,176,6,172,89,153,78,24,12,201,92,
134,240,211,249,116,10,107,43,73,147,110,175,207,149,225,60,206,108,50,65,221,157,68,224,129,229,121,167,42,75,120,192,209,202,42,140,51,153,140,65,178,219,239,199,113,198,215,74,226,185,242,122,33,240,
118,26,45,123,207,152,186,152,87,12,0,90,148,49,123,86,107,226,23,141,66,65,181,246,50,104,0,196,212,55,128,151,48,5,239,25,33,197,231,28,236,66,2,43,182,145,100,153,3,30,34,208,6,139,154,97,231,130,107,
188,96,18,8,19,175,157,80,186,25,84,20,166,229,125,103,36,118,246,154,57,221,27,62,237,73,215,156,133,116,167,185,98,216,65,224,138,178,71,218,23,17,91,142,58,129,80,95,180,8,84,156,230,19,153,88,197,
74,168,68,53,203,148,69,201,33,118,182,113,170,170,34,250,80,223,81,77,184,178,212,162,138,152,166,152,48,186,72,169,110,105,151,205,231,160,176,122,124,45,174,95,143,116,188,232,209,125,181,93,38,13,
40,99,118,51,125,128,157,159,143,48,46,1,156,133,21,212,139,240,187,20,84,114,175,229,69,193,70,228,201,157,172,175,125,71,11,235,36,210,253,102,117,161,54,160,216,201,58,109,2,98,94,51,41,146,164,177,
244,57,102,29,54,237,8,168,122,127,45,14,120,221,33,76,156,18,22,119,199,252,125,62,172,161,108,155,23,79,159,96,154,57,205,102,243,41,163,213,95,60,253,24,252,137,254,96,180,249,226,217,112,180,218,233,
118,121,39,140,247,15,118,118,54,211,44,163,112,138,141,214,239,193,122,221,217,124,9,43,167,59,24,108,189,124,222,237,246,215,214,54,194,181,168,146,212,134,226,80,167,164,219,47,17,144,161,197,30,199,
198,210,209,213,89,59,104,67,15,27,122,29,140,21,130,61,151,147,101,206,95,179,221,30,72,196,137,178,84,181,201,167,81,211,50,228,133,183,19,226,63,151,169,35,22,61,192,197,38,242,70,162,55,185,25,53,
21,34,178,13,89,35,96,253,187,214,40,182,46,8,251,244,106,56,221,39,7,251,154,64,216,4,97,237,30,28,236,193,135,89,154,231,221,46,88,76,117,93,229,93,180,73,39,227,49,60,197,96,52,106,234,186,44,230,112,
147,189,254,128,143,19,92,198,160,175,25,125,6,118,86,89,128,66,129,167,239,245,135,168,106,153,52,140,218,145,6,100,57,163,216,173,116,105,208,78,8,154,68,38,139,210,64,147,207,165,125,112,131,101,73,
69,78,240,213,152,72,232,166,52,17,135,197,86,219,69,93,10,162,26,219,96,216,74,241,19,241,3,195,113,184,184,150,177,181,173,19,34,245,188,20,210,253,232,14,226,119,13,255,25,193,3,179,87,72,106,87,199,
28,1,96,139,137,204,43,126,245,154,125,109,100,94,70,174,122,31,75,149,214,113,97,217,104,234,147,141,245,88,241,197,120,214,203,151,68,249,198,30,246,20,20,123,204,232,89,78,52,156,99,254,80,74,194,55,
130,162,212,204,43,232,200,68,252,165,119,73,170,119,145,204,116,124,8,55,117,239,193,91,160,149,158,63,249,20,44,38,48,148,138,98,150,36,89,85,97,93,197,108,58,238,15,6,124,142,129,182,202,178,252,241,
59,159,133,13,179,249,242,25,76,230,112,101,117,124,184,63,30,31,240,250,219,184,255,96,249,90,134,108,159,64,10,190,220,155,158,157,169,6,189,138,54,34,158,188,132,146,122,118,113,140,180,210,153,77,
122,220,24,137,136,49,47,118,164,3,26,158,179,129,78,152,136,26,98,178,147,39,229,35,217,146,203,199,200,102,30,158,176,8,74,170,19,97,4,164,205,180,92,233,6,39,48,162,135,200,146,82,232,173,56,239,209,
10,167,205,157,34,221,97,38,177,236,63,203,251,122,240,108,231,19,208,59,253,193,16,78,130,225,104,37,239,116,247,247,118,86,240,167,217,225,193,30,88,181,243,217,116,119,107,179,211,235,129,142,62,60,
216,127,244,248,157,233,108,82,204,103,240,56,29,208,107,84,50,57,62,56,128,127,130,166,131,161,6,43,171,140,80,191,175,55,80,75,176,189,137,100,195,46,208,178,227,209,18,9,38,98,211,237,80,127,122,211,
146,51,222,50,101,48,17,60,68,177,148,218,240,188,133,154,133,214,217,224,116,27,189,224,125,146,76,133,17,54,190,200,67,75,2,98,30,201,125,165,107,142,190,186,102,144,2,59,225,56,86,28,15,213,129,70,
248,132,140,119,161,168,48,89,190,33,56,107,184,22,67,158,120,169,176,137,122,30,210,253,242,37,81,28,165,130,207,184,136,137,157,26,45,65,208,58,244,23,59,199,252,241,5,140,140,244,49,214,247,95,124,
101,72,119,74,219,223,21,169,158,187,136,192,207,144,35,12,46,33,97,139,144,9,58,77,51,184,227,78,167,51,26,174,150,213,220,115,188,80,234,10,243,65,21,104,171,2,79,117,42,230,51,209,253,251,15,159,62,
249,100,58,25,247,135,67,132,249,44,95,75,135,186,87,237,66,6,73,73,19,1,77,249,26,237,208,10,108,168,188,38,124,41,223,19,216,7,137,36,44,42,31,195,130,143,139,128,134,71,176,2,70,82,90,238,24,130,21,
54,73,162,9,187,192,235,52,176,86,249,130,65,205,17,73,252,45,98,104,160,100,63,195,17,26,65,1,68,212,206,14,52,182,241,157,166,22,72,119,119,119,72,119,66,90,197,247,31,60,130,51,3,11,241,146,164,172,
74,184,25,152,222,213,181,123,221,78,15,20,80,154,166,112,243,96,255,110,111,189,208,158,98,23,94,223,100,124,200,181,177,247,30,60,132,115,5,36,225,66,171,107,235,189,222,224,197,179,39,251,251,187,112,
186,136,155,67,37,196,138,25,129,208,115,212,92,241,198,189,135,125,227,85,29,208,231,12,94,99,45,223,114,107,63,60,51,176,166,143,234,165,34,138,250,249,200,6,248,210,78,56,67,149,180,132,176,204,231,
201,161,0,102,40,38,143,50,120,106,84,222,64,0,47,230,89,191,198,46,99,219,92,152,2,153,129,135,198,177,190,117,247,146,76,195,205,31,46,208,48,81,196,38,60,43,219,51,145,238,87,242,131,150,184,216,125,
69,139,111,164,129,230,165,110,67,90,232,124,243,39,24,173,39,145,238,119,13,19,55,119,73,170,199,49,207,115,8,252,224,0,199,166,0,251,123,101,81,192,100,214,173,133,253,0,58,104,127,111,247,217,248,19,
216,48,195,213,213,128,102,122,235,237,119,158,63,125,242,242,197,179,126,191,31,154,121,195,201,207,121,223,213,245,141,227,247,131,129,238,246,8,126,131,145,196,220,156,18,245,79,236,59,206,133,4,191,
220,179,52,74,56,209,122,28,77,253,70,197,169,37,104,31,243,47,69,105,28,181,53,156,209,184,115,52,115,161,72,111,11,105,247,34,164,90,156,14,247,17,89,170,73,212,157,188,3,90,152,72,26,18,190,122,76,
233,1,24,166,106,141,15,84,203,108,223,53,167,59,30,242,216,56,207,197,113,10,107,19,222,5,248,122,200,26,76,11,6,220,243,151,47,159,194,105,49,90,93,131,59,193,242,189,178,232,247,135,176,187,242,188,
19,97,214,111,14,35,128,3,137,153,97,34,32,105,170,170,136,230,48,2,60,31,59,206,240,200,155,106,135,142,150,214,121,46,118,237,193,1,28,182,225,125,203,124,237,149,171,123,166,43,28,138,116,143,88,97,
14,43,153,98,82,162,247,180,214,238,72,139,144,16,203,162,209,34,223,223,8,57,215,125,0,78,243,251,229,141,151,154,108,218,78,9,182,205,21,46,215,220,101,9,30,66,82,208,202,116,97,150,9,19,20,114,137,
93,117,183,46,115,204,159,142,116,191,146,143,195,92,236,158,193,42,240,72,184,118,169,221,200,229,205,159,5,170,158,105,115,95,149,95,118,167,108,100,228,49,93,64,224,247,224,193,91,15,31,190,141,232,
115,178,20,64,38,235,118,31,130,79,177,132,188,255,226,151,126,149,175,245,249,247,190,184,60,14,76,233,100,140,69,21,107,235,247,243,52,63,118,63,205,36,78,122,181,49,129,116,91,98,138,28,211,109,75,
240,58,155,101,164,123,64,205,48,210,61,161,173,235,145,238,237,66,134,14,26,112,221,72,59,225,237,37,105,90,85,85,146,216,162,104,165,171,115,211,250,184,138,172,10,233,123,229,161,73,12,128,232,33,27,
114,1,175,30,54,127,191,55,96,228,4,230,139,53,155,12,18,164,143,24,80,77,20,78,119,139,116,167,49,145,187,49,49,171,107,27,96,52,237,110,111,130,252,96,180,130,216,20,208,95,189,65,89,206,71,163,53,16,
94,89,91,135,187,220,217,222,132,123,236,118,251,224,54,130,255,30,184,216,153,146,13,116,241,120,124,8,183,179,126,239,158,52,85,94,230,98,247,90,67,11,113,216,18,209,128,151,105,225,32,176,154,138,91,
233,191,8,181,109,11,27,158,138,111,168,239,25,198,19,171,134,33,169,190,251,87,72,167,42,238,141,198,72,78,56,14,193,63,109,192,4,206,210,220,248,36,29,30,41,216,252,175,185,14,210,253,24,58,191,61,165,
147,67,116,221,221,186,204,49,127,38,167,251,197,126,144,240,34,224,97,192,142,158,48,240,249,102,27,172,44,175,90,197,238,145,238,220,178,201,254,18,233,126,73,25,240,53,96,98,251,131,193,41,140,131,
42,106,167,185,93,32,78,132,6,46,152,19,17,167,192,175,136,116,55,42,117,110,26,37,142,42,75,48,120,63,24,173,206,102,83,88,153,160,39,136,59,168,225,153,231,22,112,158,88,49,242,13,248,144,31,19,76,146,
209,112,56,157,205,224,69,228,121,6,91,8,76,69,23,122,136,197,184,24,92,27,177,41,190,200,202,221,49,210,253,237,207,188,43,48,102,173,123,131,33,152,87,225,36,102,153,149,245,13,138,29,55,124,105,240,
254,4,0,66,55,121,239,222,195,192,107,14,62,35,76,203,81,206,114,143,40,99,84,26,91,178,38,10,128,88,118,226,56,44,101,61,210,29,131,137,24,105,138,177,156,152,140,150,60,207,49,163,234,92,81,150,138,
59,128,52,77,152,13,198,106,73,108,105,41,57,11,31,12,135,67,240,115,225,172,2,101,221,237,245,180,167,199,102,40,68,43,48,183,43,32,221,95,165,76,124,54,158,245,164,181,28,172,110,197,1,166,4,78,57,214,
92,86,136,141,8,69,229,164,108,251,234,10,53,240,246,73,213,177,186,117,191,236,108,47,224,46,73,245,116,32,201,190,27,2,63,48,100,214,55,30,192,110,231,204,247,245,198,225,208,33,91,64,236,176,99,178,
73,194,69,148,87,166,37,229,129,72,182,42,77,222,7,47,98,214,204,251,236,43,118,242,110,146,164,109,51,79,8,12,93,79,106,65,162,11,235,168,25,173,12,145,68,160,169,8,82,22,37,233,8,147,158,147,9,56,203,
228,32,70,125,240,188,124,25,9,6,44,58,37,198,110,235,68,138,62,164,20,61,122,35,56,221,41,59,20,25,114,120,153,49,79,93,122,53,114,136,22,9,118,144,195,167,197,86,47,134,124,20,102,82,39,58,40,15,199,
35,91,213,53,148,253,200,76,234,164,228,196,13,71,107,211,233,148,125,70,77,164,198,118,73,55,177,114,103,116,187,242,177,48,176,13,65,91,205,231,8,10,76,179,20,221,239,52,15,212,53,169,74,13,117,120,
166,13,172,238,56,66,114,77,153,243,144,238,167,90,203,190,189,110,204,250,69,26,105,180,237,133,37,81,23,42,212,87,134,116,39,216,247,155,139,116,191,134,12,198,80,49,194,141,190,225,181,199,185,42,210,
29,81,44,69,55,238,206,234,137,229,208,45,8,108,220,123,240,226,217,19,248,126,127,127,31,28,165,247,191,248,254,151,190,244,43,63,252,225,95,213,117,251,248,237,7,216,197,203,232,44,203,153,107,120,60,
30,131,170,146,230,195,70,35,203,73,183,75,140,2,20,18,139,92,154,183,245,52,39,242,159,136,85,5,209,41,54,175,5,233,126,84,134,140,35,236,166,216,160,173,233,212,169,157,10,110,190,98,185,240,16,62,42,
85,89,181,85,71,101,83,53,99,235,41,207,187,48,97,216,151,1,163,13,24,64,87,145,2,211,137,11,22,225,247,87,70,67,2,106,53,9,194,195,99,152,83,248,107,62,155,41,111,95,119,17,230,142,21,215,140,116,31,
234,33,120,132,181,174,89,253,221,105,132,228,218,50,231,33,221,143,86,198,234,229,254,58,45,181,245,56,210,72,131,40,172,110,168,80,143,34,221,149,239,230,118,11,126,217,2,121,79,13,22,3,127,60,71,83,
222,52,164,251,107,145,185,42,210,29,129,209,147,36,234,168,164,87,171,73,206,188,239,48,248,96,180,50,29,31,130,25,189,178,178,246,71,127,244,111,126,244,163,31,193,64,143,30,221,47,176,195,179,112,90,
56,74,111,117,58,29,246,134,224,90,105,150,173,174,61,128,91,243,158,157,211,249,12,43,186,230,185,148,60,208,74,38,254,12,233,224,194,174,171,245,237,75,185,89,49,166,29,49,138,183,48,121,238,102,38,
189,138,140,165,168,151,83,76,228,88,29,91,141,183,192,125,206,78,204,68,79,71,122,24,171,49,97,56,48,132,183,142,199,195,167,240,150,14,199,83,240,7,191,240,254,251,95,254,242,151,127,248,191,254,21,
236,179,199,143,238,129,163,205,16,77,106,42,81,49,147,31,115,79,195,87,183,219,237,13,71,198,243,9,199,38,6,109,120,160,198,129,211,253,234,72,247,87,33,115,1,210,61,148,68,105,239,175,133,92,17,115,
186,115,252,149,137,83,56,52,123,109,133,202,72,119,230,30,57,149,211,253,50,214,187,242,237,51,248,222,125,187,60,246,97,225,4,162,92,12,65,230,152,57,19,57,204,36,155,238,94,47,210,253,213,160,55,206,
149,185,26,210,157,194,185,198,150,105,156,23,182,232,192,70,102,181,178,182,182,241,244,211,79,58,157,252,251,223,255,211,173,205,205,159,252,248,199,43,43,43,100,41,16,240,15,49,214,54,74,240,204,55,
60,47,136,65,77,214,215,239,19,148,49,148,12,53,81,62,107,203,220,57,9,83,249,70,157,33,144,38,104,248,144,95,59,213,251,187,11,164,59,203,4,204,13,65,204,92,56,131,121,53,34,12,82,86,172,245,205,160,
111,228,147,194,135,19,53,93,209,195,129,235,239,219,3,246,251,146,52,235,15,71,88,246,208,170,213,181,141,63,198,227,225,111,224,71,15,30,220,3,99,182,42,43,198,143,56,170,34,130,227,33,180,128,7,45,
54,90,221,192,88,61,81,126,194,181,123,174,11,151,133,75,168,165,170,169,187,139,144,92,91,230,2,164,59,225,20,20,115,21,50,210,159,27,123,88,31,69,118,190,190,242,38,133,135,71,100,44,182,56,12,50,174,
197,218,200,11,173,119,140,3,144,76,20,202,184,144,58,39,193,246,232,154,249,85,27,34,136,118,11,228,189,57,202,31,191,132,228,126,245,72,247,219,189,214,245,100,200,172,96,122,101,21,49,224,152,40,170,
209,118,86,82,64,135,42,128,100,216,46,66,31,109,54,76,58,187,241,112,119,190,179,194,12,48,31,255,252,103,96,74,127,227,27,223,132,173,242,151,255,203,15,186,221,78,150,167,22,1,53,134,250,96,26,62,171,
248,77,193,159,157,188,179,178,122,79,133,56,49,105,159,120,229,0,6,175,198,93,142,154,47,74,210,48,102,223,138,74,163,138,18,208,73,173,224,185,142,175,13,102,112,190,163,153,116,76,228,66,155,44,38,
66,65,1,73,82,210,14,25,68,241,183,35,130,71,33,125,46,110,63,101,79,93,177,231,251,164,20,44,142,25,13,63,117,243,145,25,140,237,152,27,208,194,61,140,86,214,159,124,250,9,216,167,223,255,211,63,217,
222,222,254,241,143,127,178,178,130,118,147,197,190,220,134,225,11,190,227,143,74,200,1,135,125,4,218,205,23,247,113,52,78,131,194,26,187,105,163,154,43,112,186,223,101,107,130,179,100,46,64,186,107,199,
116,123,46,160,216,157,132,57,53,199,119,237,109,43,84,197,24,51,190,22,89,221,9,213,15,157,103,189,155,104,153,99,222,133,123,166,88,3,131,81,24,126,193,7,224,50,242,94,218,31,56,117,195,60,238,255,15,
100,162,8,241,62,76,30,64,60,68,136,60,12,104,120,15,248,140,88,134,172,96,226,116,175,219,118,167,215,89,27,231,43,211,250,112,8,135,205,124,54,251,204,59,239,252,230,87,126,243,47,254,211,127,130,89,
29,141,70,112,130,180,88,9,104,184,101,73,228,99,240,176,117,6,131,149,172,211,179,30,254,197,167,123,58,26,71,137,41,246,87,193,112,161,144,197,162,109,31,230,248,153,90,73,45,208,240,100,1,157,182,54,
110,155,211,253,76,202,99,206,226,19,66,157,200,120,9,217,196,84,84,210,132,198,208,157,7,112,98,36,104,239,75,251,164,204,167,179,171,246,65,179,60,212,15,94,152,151,76,125,245,233,207,62,128,3,229,155,
223,252,61,24,240,7,127,249,23,253,126,47,239,228,140,104,227,152,51,40,168,192,146,12,31,229,121,190,186,118,159,8,151,105,83,144,186,127,20,61,140,85,244,194,109,234,43,113,186,191,142,200,198,5,156,
238,148,166,109,60,167,59,53,197,198,146,31,43,176,122,58,40,110,87,161,242,68,19,37,146,0,115,47,199,13,47,50,156,93,108,189,19,206,52,74,12,168,13,197,137,1,121,31,73,99,15,226,132,53,175,19,233,254,
38,228,140,61,95,187,99,24,79,40,230,112,161,191,233,130,211,61,200,80,204,171,77,203,195,110,218,159,68,61,253,252,163,9,216,35,127,252,199,255,230,167,127,255,247,159,124,250,201,219,111,191,179,134,
141,5,213,116,58,158,207,166,220,23,44,74,146,12,118,85,214,19,83,151,234,51,148,116,5,115,81,119,162,226,162,56,236,59,60,236,21,39,37,35,65,42,105,142,214,171,208,146,129,140,52,75,64,121,115,194,251,
99,171,255,21,204,36,23,5,72,101,178,19,90,87,174,31,162,210,237,118,137,71,88,45,83,20,112,239,107,202,150,8,167,251,233,59,145,155,224,33,125,176,222,212,219,247,213,189,85,187,178,163,246,136,131,108,
254,238,187,239,126,229,43,191,249,151,63,248,129,66,4,114,31,175,29,71,244,91,162,164,184,89,17,220,248,104,176,218,237,13,90,186,13,70,204,195,73,112,223,108,128,182,122,110,55,173,230,114,5,170,189,
23,60,202,155,22,181,48,103,34,221,165,177,7,53,221,245,60,235,17,87,144,17,74,249,78,20,170,183,223,136,151,210,89,159,177,66,75,58,137,211,230,52,38,105,129,210,17,162,55,142,56,246,47,185,249,208,140,
132,215,220,9,84,61,183,238,113,252,92,175,23,233,254,102,228,140,175,134,116,95,230,125,183,101,167,141,92,220,157,239,108,111,253,217,247,255,172,40,230,127,243,163,31,61,120,240,96,125,227,1,37,242,
244,112,184,218,31,140,56,56,205,199,140,242,13,190,168,219,8,191,47,155,14,199,38,169,154,89,167,41,178,136,36,9,26,222,132,106,10,57,225,132,113,208,197,8,73,114,44,211,170,246,184,103,71,129,249,59,
157,73,118,60,5,208,227,92,150,37,200,165,140,10,52,142,196,231,10,171,209,151,10,249,118,59,198,243,154,75,112,211,31,17,140,125,111,221,242,78,108,253,164,169,74,85,187,110,111,85,141,70,110,240,47,
47,255,169,42,203,63,252,195,63,252,135,159,254,244,231,191,248,249,59,159,249,204,250,250,125,24,101,54,157,204,102,19,242,30,108,20,99,11,162,188,211,131,29,228,136,83,223,35,153,80,111,173,233,149,
220,165,219,118,167,214,4,2,39,254,2,75,101,198,156,0,57,85,51,16,183,221,98,39,46,115,177,11,95,187,111,11,116,67,127,92,158,125,241,246,221,217,156,238,84,70,203,156,238,17,197,215,151,15,1,106,127,
119,39,10,245,88,233,144,48,187,98,163,145,35,221,150,24,228,198,157,53,133,83,41,180,49,225,123,54,177,79,8,162,138,188,240,158,197,224,127,125,72,247,55,33,103,124,37,164,59,158,210,145,38,182,117,84,
73,182,232,31,238,22,239,189,247,222,195,135,15,254,231,63,255,243,225,112,248,232,241,103,60,241,67,196,142,27,19,7,161,41,162,5,133,100,164,113,38,86,150,196,195,67,16,172,199,195,186,192,136,117,171,
152,11,208,179,14,224,129,31,9,62,139,195,17,100,134,51,145,158,84,174,29,245,218,96,45,221,22,167,251,57,50,220,89,10,46,89,20,179,79,62,254,8,124,5,248,244,193,131,183,6,131,145,80,246,41,106,84,163,
66,76,69,145,243,200,85,56,173,84,13,48,41,0,47,207,200,248,140,147,91,80,45,105,237,107,155,244,76,207,193,38,26,232,254,238,206,246,159,126,255,251,179,217,236,255,248,235,191,126,248,240,225,198,198,
35,214,120,189,193,112,48,92,225,66,40,79,181,142,247,192,229,185,60,14,236,160,7,250,94,166,210,67,53,153,155,130,77,233,214,53,94,198,133,251,137,3,68,221,115,204,11,23,187,223,137,82,59,237,225,124,
240,29,241,208,223,204,215,102,253,213,90,238,172,195,6,44,76,210,41,72,247,69,99,15,41,59,66,211,198,247,163,127,21,97,224,229,210,161,101,171,219,240,42,33,62,10,184,223,192,13,239,152,24,158,222,15,
67,96,130,98,190,252,61,91,225,226,121,19,145,238,24,72,146,114,101,43,5,155,132,247,240,43,73,75,254,254,168,12,170,254,166,241,249,233,211,101,206,26,135,79,11,108,68,226,121,117,143,201,112,209,114,
219,114,167,110,199,72,247,131,189,217,159,126,255,143,254,250,71,63,42,155,242,253,95,121,236,42,4,66,145,199,205,93,48,45,229,248,133,218,223,49,236,142,40,60,226,110,17,119,96,207,152,234,96,100,235,
88,112,65,74,216,153,181,63,102,228,188,9,228,125,126,95,113,7,41,125,178,134,153,232,34,238,46,251,110,133,43,194,148,101,249,242,197,211,134,152,188,122,93,48,103,186,147,241,1,184,189,92,116,206,225,
173,136,129,166,20,110,19,135,154,108,41,182,227,132,187,79,104,120,163,0,191,34,133,37,234,24,173,12,2,145,130,89,121,160,198,59,211,237,207,191,247,222,163,135,15,255,28,143,135,209,195,71,159,97,123,
34,200,240,124,184,208,4,215,25,225,194,198,45,16,223,83,235,169,74,119,213,222,92,207,23,148,249,75,50,122,113,63,130,224,87,66,168,169,196,137,209,194,181,192,254,151,83,140,117,10,101,246,242,70,164,
80,200,119,249,22,208,165,102,230,102,23,41,255,102,213,66,134,172,51,4,100,232,19,176,246,147,72,119,6,65,153,144,62,174,125,57,207,43,11,3,47,151,14,113,17,137,81,66,136,193,37,174,108,0,112,45,37,19,
87,68,129,56,101,209,104,68,75,87,181,51,154,145,28,187,159,55,25,233,30,40,46,41,95,30,171,64,181,178,20,25,89,150,209,86,151,197,236,249,139,103,224,47,128,94,121,244,232,113,183,63,56,38,115,153,113,
206,151,97,2,126,170,249,115,76,43,250,157,63,248,238,238,222,222,71,191,248,249,23,127,237,65,156,207,117,191,168,139,216,206,115,101,19,66,131,122,212,181,80,62,52,73,170,162,188,208,73,129,172,120,
101,86,79,114,103,35,218,14,210,70,0,211,133,216,156,202,114,30,144,11,86,180,144,69,44,226,94,68,160,140,50,39,106,152,221,157,190,89,78,65,109,109,190,216,219,219,69,54,177,78,39,77,211,186,174,15,14,
246,65,168,105,159,190,245,248,179,154,220,171,144,170,98,126,81,169,242,35,11,205,74,201,173,160,203,156,255,54,204,182,0,6,25,71,173,140,51,188,236,213,238,100,251,223,253,201,159,128,235,93,85,205,
111,124,254,183,166,106,218,210,193,176,44,35,0,90,239,205,99,236,76,197,96,154,13,76,15,6,127,233,94,150,170,94,212,100,169,0,111,95,70,54,144,102,88,170,57,137,49,64,134,97,224,40,236,59,105,123,191,
168,78,151,228,50,201,44,209,19,170,133,175,237,48,103,66,227,216,8,27,138,9,189,62,12,137,208,238,179,77,218,101,164,187,102,115,84,56,46,192,16,197,181,211,190,198,48,240,210,129,227,248,168,36,95,85,
152,43,78,112,195,99,117,23,31,2,71,199,185,20,242,158,78,213,55,22,233,142,121,3,110,127,208,168,150,201,103,3,237,127,138,109,102,28,81,178,197,212,64,229,112,243,229,115,246,232,7,131,65,150,231,135,
135,251,253,254,16,20,118,144,185,204,56,231,203,32,215,3,251,44,74,78,116,120,59,63,255,232,227,151,47,158,189,251,217,247,218,105,84,79,106,48,154,210,110,21,165,99,62,162,97,231,194,193,204,185,89,
56,59,157,180,52,209,109,209,43,103,185,114,124,70,242,1,35,54,7,188,25,46,49,225,197,173,92,171,66,38,64,4,112,193,82,95,82,125,138,247,71,57,156,187,200,190,179,246,41,171,249,214,230,203,195,195,3,
184,92,191,215,67,62,254,221,93,244,161,136,159,107,54,155,154,70,117,146,174,113,17,178,226,33,198,84,181,26,102,21,238,18,55,106,233,144,39,86,2,234,54,240,142,89,226,231,137,156,143,136,112,240,219,
45,21,174,81,207,174,250,219,223,253,14,28,15,63,255,197,47,190,250,222,87,59,174,51,82,253,153,42,15,218,67,172,79,240,237,94,176,224,152,13,34,103,18,82,85,93,157,195,164,79,220,20,60,193,70,53,92,189,
32,208,92,230,184,89,112,165,121,242,1,67,160,75,86,13,202,32,88,146,211,196,77,168,153,183,129,175,93,95,138,175,93,158,148,186,70,56,178,24,200,12,244,24,169,115,204,94,253,63,252,143,255,211,146,66,
13,44,133,203,229,78,17,247,143,72,168,197,222,145,114,167,59,150,161,220,11,252,103,67,79,83,37,61,86,45,47,35,230,134,231,23,123,195,107,217,69,137,164,84,140,250,57,98,111,84,232,189,174,45,115,112,
176,55,24,174,92,111,28,21,50,224,18,233,208,193,0,241,129,59,193,91,111,110,62,223,219,217,134,103,233,118,187,89,150,213,164,41,145,45,51,235,188,243,153,207,178,204,101,198,185,80,6,137,46,233,96,99,
110,88,182,206,145,72,207,119,166,99,111,7,23,120,90,99,37,187,177,96,203,98,21,32,154,17,164,185,90,56,126,76,91,37,139,138,106,97,128,242,193,203,128,20,245,129,76,110,5,24,144,238,199,196,142,213,39,
195,80,7,123,59,163,213,245,155,188,181,115,100,64,165,127,244,209,7,197,124,142,172,164,157,78,81,20,190,77,113,136,172,171,52,206,190,254,133,111,162,97,165,109,227,176,20,28,180,6,183,251,164,231,113,
99,55,1,221,65,204,124,2,140,13,29,119,2,168,80,232,124,77,106,81,205,57,67,219,83,161,65,151,191,120,241,108,101,101,13,67,178,4,164,26,152,129,55,120,176,149,116,237,168,77,169,138,64,201,114,198,191,
118,245,76,23,135,118,76,97,117,225,49,231,226,77,12,21,73,223,61,102,94,145,217,110,109,35,148,243,76,184,232,43,165,67,179,156,163,124,237,154,152,251,91,62,228,162,69,187,160,19,156,238,148,115,224,
227,208,247,181,199,73,32,214,98,231,150,244,15,133,56,23,212,210,156,34,92,224,92,148,118,190,98,240,141,8,3,47,100,56,84,206,10,30,31,222,221,238,181,152,234,240,205,68,186,243,205,51,192,44,98,110,
54,122,145,173,244,1,199,224,72,83,215,59,219,155,135,7,251,240,124,195,110,23,148,212,254,222,158,102,174,18,180,151,39,85,51,201,186,17,134,56,76,163,35,98,145,111,96,203,36,176,62,177,149,68,149,240,
56,129,117,224,156,107,113,51,212,150,216,139,125,59,185,200,249,246,10,92,51,192,225,19,60,80,154,12,117,19,19,31,147,229,206,80,3,222,222,145,9,13,36,164,223,167,11,177,101,226,232,243,97,107,239,201,
191,1,72,119,14,67,124,248,225,63,195,206,68,182,3,165,102,179,25,207,3,3,41,56,237,67,90,181,248,135,157,127,88,221,216,8,237,178,201,168,71,210,133,84,167,125,215,29,170,225,208,12,103,110,126,160,14,
91,84,32,142,3,199,167,208,249,58,102,244,23,234,87,164,123,156,207,135,163,53,10,191,98,154,245,80,79,14,221,36,215,89,12,138,142,213,34,135,116,84,51,109,103,214,96,4,183,80,5,213,176,51,205,169,230,
74,6,214,69,158,195,206,112,159,65,166,44,147,214,185,38,180,222,178,140,224,199,136,149,40,20,195,124,237,198,87,158,145,59,35,220,179,39,57,221,249,48,224,64,62,133,143,83,214,83,151,55,123,99,86,222,
202,180,1,197,206,237,139,222,144,210,33,238,3,230,239,135,140,63,230,98,190,141,18,173,101,153,160,233,223,88,164,59,19,70,195,50,67,101,129,97,120,101,4,63,5,170,167,250,228,227,143,224,144,79,211,20,
108,171,121,81,112,215,73,182,7,56,110,240,233,47,62,253,210,191,90,167,117,135,197,78,240,203,105,7,38,2,249,227,19,12,65,152,182,232,212,179,180,105,236,249,215,146,54,19,20,76,37,250,98,127,14,135,
224,46,121,217,129,128,92,90,141,83,12,116,9,49,47,140,242,114,210,74,7,190,133,177,197,169,20,114,9,173,172,239,55,2,233,46,161,95,110,77,8,119,86,22,133,162,206,32,148,203,83,225,233,136,194,1,91,219,
189,220,124,214,27,246,211,52,71,51,200,121,231,206,181,141,5,37,55,135,227,99,160,250,125,221,191,231,214,118,244,94,165,42,54,58,180,207,152,115,65,251,73,101,202,152,88,166,159,229,151,34,173,85,109,
193,214,161,64,145,184,235,204,81,25,43,52,229,65,70,198,65,187,12,25,129,156,4,118,181,232,154,5,200,209,42,68,240,163,112,196,181,7,220,22,62,48,140,179,129,204,244,8,148,23,70,16,50,197,58,57,207,235,
4,74,68,5,19,164,223,237,85,241,79,209,215,191,245,221,0,186,89,170,194,211,98,40,50,215,115,8,58,170,69,207,241,179,100,66,220,211,122,183,92,144,229,87,28,39,200,156,122,63,238,234,227,156,47,227,99,
180,38,180,107,231,14,142,129,244,70,16,73,215,149,65,42,209,36,190,222,56,184,19,34,178,209,140,212,132,135,68,12,47,193,143,126,246,129,109,27,112,76,184,49,1,181,255,16,140,226,2,85,5,159,85,221,84,
223,115,101,207,86,157,182,200,235,89,214,204,224,155,78,91,97,143,128,40,47,227,110,97,176,23,101,138,173,83,78,187,86,160,210,98,22,96,69,72,2,207,99,233,187,76,80,146,126,41,139,68,84,77,188,52,149,
241,140,163,200,225,77,181,95,122,249,28,14,209,95,134,59,242,222,240,96,81,111,67,121,164,123,68,115,194,165,14,140,32,103,198,16,73,93,105,133,29,195,242,206,77,222,218,49,25,203,139,133,184,242,224,
27,234,119,171,68,185,48,87,196,162,22,82,249,91,210,85,85,141,86,86,133,234,82,50,91,66,221,5,151,168,76,93,232,162,171,59,125,215,3,151,173,53,173,19,158,9,4,21,98,119,6,42,186,12,62,145,112,204,17,
145,3,71,117,201,174,137,60,169,198,130,84,246,242,50,201,25,215,98,86,31,239,251,199,210,117,219,3,51,61,71,133,132,213,132,34,207,243,121,129,115,199,132,104,228,108,26,207,186,37,133,168,130,163,38,
82,105,46,62,17,166,79,50,213,225,119,73,85,53,39,101,162,223,251,250,55,37,117,77,40,118,207,183,109,56,168,102,37,230,167,61,77,34,22,30,242,226,58,41,227,137,22,66,147,91,201,48,113,245,44,193,55,46,
53,206,107,145,97,120,7,30,212,76,95,169,195,86,95,60,8,215,3,95,79,166,40,230,73,154,93,111,28,244,211,253,178,99,28,127,96,99,35,204,116,116,184,191,135,113,37,226,232,102,227,36,196,127,56,40,201,231,
106,85,150,20,242,48,203,227,96,40,5,12,237,42,3,117,134,208,165,188,76,58,21,216,37,174,209,167,94,139,238,71,244,22,145,88,134,55,238,164,177,148,242,176,120,29,202,215,125,103,2,79,28,36,156,238,94,
211,5,101,200,151,147,29,197,118,25,1,184,16,238,228,67,221,196,48,99,151,183,110,75,117,236,112,99,199,150,56,204,121,158,231,55,121,107,167,202,144,151,100,58,221,222,108,58,134,115,200,121,83,69,9,
130,68,45,24,217,49,223,141,138,174,219,201,147,56,66,244,25,17,159,104,223,248,62,228,224,38,106,150,155,108,100,134,240,163,82,215,148,15,21,35,241,20,101,42,73,9,225,41,245,29,217,217,141,54,180,170,
17,116,18,180,149,180,232,33,140,174,151,145,224,163,18,238,217,243,20,183,167,139,104,57,39,135,80,88,74,217,90,129,118,75,113,246,101,14,3,58,125,148,80,39,31,213,194,97,153,177,166,59,85,83,227,19,
125,253,155,223,86,30,37,97,125,49,23,199,90,5,214,167,124,59,234,163,199,87,144,241,252,51,210,211,64,123,242,252,132,18,210,92,57,101,60,239,194,57,227,92,230,90,119,39,19,144,147,28,53,89,212,111,5,
232,132,28,36,215,148,41,169,253,239,245,198,65,156,97,128,160,43,231,73,129,229,112,97,28,192,108,54,101,110,19,130,254,11,93,181,62,146,84,198,95,68,38,242,209,202,233,227,192,64,117,226,234,142,73,
203,184,51,71,246,133,38,58,121,45,246,230,90,110,61,127,233,13,111,132,226,93,86,116,160,250,109,168,149,130,241,212,236,1,250,112,201,229,235,249,70,9,189,121,66,166,154,207,211,188,195,203,207,39,94,
142,211,25,45,47,209,11,101,180,63,246,2,255,71,81,22,203,184,15,227,223,42,1,131,28,177,60,43,76,15,55,117,49,159,77,167,147,195,131,131,201,248,176,40,102,48,13,72,79,188,100,150,206,213,28,126,171,
175,250,224,118,149,174,36,143,27,195,210,103,205,173,13,243,239,251,167,241,113,194,212,226,86,12,30,102,154,166,206,46,209,178,204,85,21,183,239,201,134,238,121,76,136,5,110,106,25,137,166,10,198,245,
121,138,94,248,60,110,226,172,68,223,248,230,119,185,220,201,249,86,215,151,180,208,224,67,38,171,61,246,106,53,5,62,216,197,5,25,184,209,170,174,57,75,154,196,103,90,122,151,177,6,239,84,230,22,151,245,
169,50,212,167,96,112,189,113,90,194,73,59,223,189,70,120,168,253,73,14,2,157,110,119,54,157,224,230,161,22,56,236,82,133,50,167,160,188,44,129,21,58,121,158,192,113,111,34,238,166,25,152,206,216,147,
135,229,221,20,153,142,27,116,15,177,225,84,126,236,90,202,247,16,196,23,125,185,153,225,127,37,168,77,124,215,66,37,219,73,47,55,31,227,102,98,90,2,207,151,247,218,180,159,153,99,50,117,85,246,122,125,
94,126,28,184,113,30,15,1,55,19,71,73,219,54,41,172,73,163,47,45,195,153,83,57,93,192,223,100,11,10,76,219,136,234,153,61,84,208,45,178,150,74,152,18,226,36,105,176,82,156,214,33,245,70,218,217,217,130,
15,137,206,80,112,155,115,85,228,58,29,168,62,70,199,35,166,250,210,81,72,24,221,108,101,178,27,27,242,19,87,27,199,175,58,166,60,240,246,181,20,111,133,140,225,57,99,18,220,20,51,160,55,116,86,162,223,
255,198,183,96,245,196,190,9,250,133,22,26,170,30,179,88,100,1,188,101,136,97,131,35,112,140,7,11,81,76,202,206,226,31,103,249,228,87,58,78,239,72,6,206,192,219,91,214,167,200,212,85,141,140,154,215,26,
199,250,165,143,77,31,176,232,76,202,253,57,39,197,69,233,240,136,224,241,133,32,169,68,127,124,132,213,99,130,153,230,188,169,203,18,142,251,253,253,221,25,117,63,148,250,1,238,68,202,68,195,101,30,71,
42,237,215,240,182,35,151,29,187,214,130,157,221,218,203,60,81,76,50,53,23,202,187,80,153,40,41,144,16,25,195,213,201,75,115,137,93,254,50,70,156,143,11,29,151,1,13,158,36,169,225,246,12,134,163,76,202,
121,157,66,173,170,53,119,115,185,188,12,243,200,115,110,14,4,62,215,251,220,230,116,19,73,0,184,168,64,7,35,108,193,118,137,224,193,186,153,205,102,18,210,166,216,31,113,25,130,74,45,38,147,131,188,211,
35,239,24,111,122,166,230,43,241,104,37,26,237,219,67,122,131,216,39,173,185,61,133,107,131,206,189,202,56,88,23,41,109,168,29,49,117,74,71,175,208,230,90,208,121,103,140,73,24,23,97,250,188,225,217,31,
125,237,27,223,166,134,224,130,6,60,199,66,11,20,198,12,11,208,82,5,198,213,92,206,103,196,197,175,60,85,102,225,120,223,101,120,251,122,50,183,187,172,79,202,128,94,200,58,157,235,141,227,185,19,216,
54,241,101,219,142,91,188,9,82,175,147,119,48,45,76,157,230,156,47,8,117,75,5,43,203,248,111,176,173,64,65,51,58,188,133,223,169,171,131,189,61,56,237,211,44,139,36,207,229,218,42,213,49,130,63,219,50,
113,173,94,190,150,68,70,132,240,243,226,39,226,138,47,118,92,148,56,233,204,109,18,251,186,159,216,135,37,150,43,67,47,107,68,96,75,174,211,100,176,15,123,150,223,110,114,38,184,237,240,233,186,94,197,
190,58,195,180,172,230,220,236,218,183,35,243,132,188,228,21,50,132,18,118,61,183,67,71,196,150,19,98,82,60,38,97,103,55,85,175,63,16,63,78,169,169,157,118,93,39,209,241,204,205,168,232,69,155,27,175,
76,238,63,200,228,230,81,100,174,62,142,11,157,195,225,247,249,5,249,72,1,239,116,117,222,152,88,212,153,220,202,217,31,253,238,215,190,121,161,133,134,191,175,35,43,245,37,11,247,152,161,156,60,22,53,
68,191,148,12,123,145,24,73,189,155,240,246,245,100,172,175,20,189,173,101,125,76,166,169,170,44,239,92,123,156,72,202,75,153,150,196,241,9,207,166,5,63,24,152,201,107,111,219,195,157,154,210,207,214,
63,172,10,40,38,95,91,130,224,99,56,237,177,229,45,251,143,206,149,85,137,65,217,166,158,77,199,221,222,48,92,75,213,157,40,43,162,206,172,154,102,86,50,77,28,109,117,70,104,173,244,181,54,188,75,176,
223,31,106,34,54,21,209,134,176,139,4,26,155,40,241,85,140,8,102,125,58,38,83,150,69,183,219,187,221,228,140,60,145,194,82,214,53,189,178,223,30,130,77,212,237,245,93,91,207,102,204,182,174,132,198,47,
116,55,177,158,124,212,3,79,153,251,155,89,124,153,224,8,188,215,110,111,32,168,93,114,138,251,170,55,81,51,50,72,111,65,225,186,163,243,127,213,113,200,182,98,12,99,68,225,160,152,218,85,4,71,202,157,
115,111,225,152,188,149,179,63,250,189,175,127,235,252,227,203,119,244,178,58,96,91,49,200,159,248,98,77,58,63,169,171,229,229,101,184,127,247,29,69,139,174,43,115,183,121,201,178,40,226,52,189,246,56,
194,165,67,209,78,33,165,48,2,46,139,168,37,90,58,156,154,164,205,227,141,98,62,151,66,63,50,193,216,102,143,20,183,252,117,17,117,211,100,23,175,65,227,170,241,104,29,215,146,117,6,238,34,108,63,188,
19,186,86,91,166,73,183,140,18,231,170,44,92,139,96,183,53,35,69,41,154,27,177,5,71,192,139,75,101,153,45,117,5,208,190,135,152,79,77,139,71,117,101,35,194,215,201,31,147,41,192,194,202,59,183,156,156,
145,134,193,122,164,135,25,21,15,115,12,39,207,51,152,60,38,173,23,107,88,238,205,45,21,234,90,38,179,247,205,135,112,228,162,152,103,73,6,115,149,231,121,154,102,45,153,188,133,45,135,122,128,126,180,
169,57,243,46,233,138,235,174,76,102,191,194,117,66,50,198,31,210,23,142,67,96,171,133,6,96,95,210,121,168,58,211,4,177,129,124,214,117,125,91,216,219,57,251,163,111,127,231,191,59,231,248,226,205,17,
184,120,132,205,104,9,48,35,24,57,165,46,150,89,30,71,73,253,247,93,68,139,174,39,19,113,105,194,157,229,37,203,170,192,205,115,221,113,22,4,5,252,11,62,4,47,226,198,101,131,41,33,170,210,193,96,0,7,246,
116,58,229,96,16,33,100,148,93,68,130,173,11,176,3,233,243,33,94,38,226,149,35,68,48,215,117,5,167,189,71,215,224,149,209,49,156,119,148,10,229,96,202,120,12,189,94,192,142,164,38,89,32,13,6,209,240,92,
94,117,242,137,64,97,69,212,8,71,16,129,71,203,107,174,106,68,72,149,255,9,25,176,176,122,221,222,45,39,112,124,34,108,77,173,22,170,152,153,185,199,139,161,141,7,83,55,155,205,185,244,151,73,147,181,
199,37,6,220,50,39,76,169,111,115,147,102,41,251,107,228,48,182,189,254,144,61,110,152,233,84,103,93,221,25,171,137,180,115,14,101,67,215,90,153,130,116,163,174,171,140,107,184,236,56,90,128,40,252,126,
162,101,211,73,156,120,237,251,158,157,188,174,68,98,110,241,236,71,28,214,57,199,87,176,249,45,71,76,180,241,57,120,225,252,222,63,216,253,218,239,253,206,179,23,207,144,35,224,12,25,31,84,61,62,142,
184,45,183,29,45,186,158,140,148,121,223,89,94,178,174,170,52,203,110,50,14,159,105,156,172,137,36,1,34,172,97,38,159,170,168,156,239,119,97,159,194,48,184,75,155,178,169,27,54,97,90,31,46,183,1,33,236,
171,79,99,100,240,192,106,39,54,4,176,99,93,20,213,117,157,98,60,43,231,107,25,151,166,189,10,227,190,117,194,81,124,6,130,50,141,68,20,114,252,74,75,172,131,237,38,177,94,227,83,159,8,172,59,171,110,
15,82,135,155,199,157,148,169,202,50,74,227,219,77,206,240,201,151,218,180,175,187,59,110,191,85,13,167,197,225,94,182,182,94,102,89,94,87,53,197,214,189,137,229,115,79,130,79,241,64,19,105,231,65,201,
86,203,115,234,108,134,112,173,196,72,10,171,25,154,65,65,221,189,216,151,244,52,15,226,155,243,106,65,125,77,43,225,156,21,85,23,229,230,139,231,121,39,23,178,61,70,37,28,149,137,177,69,233,113,32,91,
184,109,54,204,185,83,17,229,214,52,163,240,201,90,167,114,20,137,80,28,27,51,186,245,179,63,246,71,220,41,244,26,198,131,223,216,22,37,67,165,137,240,44,224,67,12,127,11,28,144,154,155,210,17,36,227,
84,25,233,197,116,98,156,182,105,223,156,134,28,119,221,244,225,134,165,57,122,41,115,204,93,218,145,91,42,98,250,23,149,116,202,186,76,149,149,45,7,46,247,218,234,26,44,185,131,131,125,240,50,144,153,
221,183,216,12,128,47,130,195,68,92,70,206,160,106,112,73,192,41,44,203,50,207,178,195,195,253,110,127,24,174,85,206,163,172,87,187,34,10,181,29,232,70,43,193,223,113,110,155,81,156,18,184,228,60,58,173,
182,83,159,136,78,248,219,37,170,85,175,134,211,157,125,142,44,74,34,124,88,203,122,19,195,230,243,25,92,31,38,28,204,58,106,254,197,168,110,41,215,86,158,18,71,216,23,152,137,140,246,32,76,75,237,106,
126,55,59,59,219,239,188,253,89,166,36,107,233,104,0,227,138,41,45,189,83,130,29,234,34,10,123,107,60,251,35,110,26,18,123,153,83,87,84,99,234,36,195,51,72,123,255,134,137,107,168,215,179,93,94,117,220,
247,128,181,5,229,133,241,25,34,154,100,4,193,16,83,30,215,81,51,232,159,99,91,252,66,25,207,27,174,11,26,16,201,5,110,187,44,55,62,167,217,100,64,184,176,189,45,152,117,36,79,180,101,220,1,43,22,52,237,
180,252,57,29,57,110,171,213,121,183,15,191,150,106,103,234,66,112,183,226,191,156,62,14,31,137,111,72,67,142,55,185,121,4,24,58,28,77,224,85,139,28,135,196,84,206,169,159,56,179,240,158,93,213,137,227,
216,99,127,236,238,222,110,150,226,26,109,170,198,10,107,136,94,198,160,75,33,24,195,249,200,45,1,139,12,155,172,224,223,109,89,148,197,124,150,119,186,124,173,182,200,163,244,192,69,115,221,118,200,46,
22,219,217,250,149,36,76,147,100,143,147,71,99,66,221,220,177,39,122,246,228,73,167,219,93,219,216,184,93,162,218,87,198,233,206,211,151,232,68,249,82,103,214,98,179,249,12,73,220,148,137,147,20,55,118,
203,201,233,208,36,222,45,23,110,91,110,156,65,5,91,113,191,79,12,9,120,73,240,40,157,231,11,107,108,13,183,147,170,100,110,139,240,226,88,161,4,25,199,185,215,133,177,166,3,65,40,216,158,147,241,33,225,
191,208,101,6,211,175,169,107,196,229,75,21,1,130,200,146,36,155,207,167,13,145,243,116,187,253,88,112,148,76,15,227,60,25,172,227,83,77,76,39,255,70,168,142,179,245,118,128,56,185,202,132,160,16,87,143,
152,91,63,251,227,179,142,47,42,199,183,236,67,177,178,193,5,225,244,52,235,207,178,161,213,66,243,80,23,243,166,194,22,29,227,221,221,249,234,99,174,244,143,114,59,108,102,253,114,26,17,98,241,228,56,
150,209,183,158,24,224,77,104,200,33,164,14,111,106,19,138,150,233,138,150,8,79,24,62,206,17,112,34,102,203,90,122,66,144,41,139,41,108,153,233,244,16,9,252,200,101,240,196,65,102,129,155,241,150,39,215,
131,113,249,20,193,125,37,134,189,187,183,253,48,123,204,215,114,200,119,2,91,17,84,36,83,53,32,117,50,152,24,45,19,33,73,13,159,246,29,37,168,7,15,252,212,9,26,30,62,221,124,246,36,235,116,214,215,239,
247,251,125,36,23,183,246,22,137,106,25,121,255,202,56,221,53,209,45,180,170,13,202,26,57,185,8,229,228,79,104,33,105,243,91,221,23,128,248,218,6,142,159,224,106,244,103,140,178,98,176,144,77,195,197,
201,170,81,54,6,253,35,193,190,80,131,99,61,213,159,83,210,8,216,227,34,117,128,93,168,173,151,207,97,228,94,127,64,169,148,246,112,127,55,3,11,26,77,193,170,40,138,36,137,87,86,214,246,118,182,137,245,
104,52,25,143,167,227,241,131,183,222,166,243,155,35,131,145,243,169,12,235,235,126,142,189,145,96,94,105,95,59,41,137,94,14,50,18,175,250,173,159,235,241,89,199,151,68,254,201,11,69,98,3,21,237,100,131,
105,220,133,167,232,84,179,126,61,133,115,4,204,164,67,107,83,152,137,60,143,39,191,248,236,228,89,3,67,153,100,146,246,247,162,222,94,175,223,107,138,149,242,32,66,123,32,10,92,75,2,32,32,251,150,171,
10,184,197,219,235,109,200,193,104,64,193,107,57,54,224,133,255,199,25,111,202,19,199,211,245,100,224,237,114,175,217,107,140,163,164,95,140,225,82,44,37,61,183,137,247,28,101,208,134,170,107,142,118,
163,12,232,41,142,243,68,220,11,192,199,74,244,50,76,83,145,250,10,224,70,133,213,142,253,193,128,154,55,34,45,175,42,43,158,31,199,100,99,184,112,107,38,245,180,72,218,107,108,232,14,237,67,52,33,112,
41,181,126,116,21,216,240,227,241,225,108,54,131,245,151,37,25,167,2,224,251,233,193,126,146,38,216,236,83,169,110,191,63,157,76,224,134,70,171,107,176,52,225,254,177,197,142,214,176,223,108,212,94,184,
196,125,249,222,171,224,116,231,176,29,42,35,221,18,128,90,179,39,196,165,121,136,131,35,42,17,75,173,49,37,239,225,119,180,227,202,59,235,244,162,32,217,127,72,207,64,196,6,18,57,6,53,204,4,62,92,160,
121,95,173,99,64,67,183,28,8,151,104,81,100,220,18,220,28,190,182,220,78,203,84,212,113,92,206,231,179,201,120,184,178,106,61,219,221,202,234,218,248,240,0,94,244,202,250,6,8,29,30,236,35,207,68,93,131,
254,2,227,174,174,74,157,102,190,224,97,193,49,79,97,74,115,138,66,225,60,160,142,84,8,117,251,160,67,116,130,120,253,182,206,254,152,124,224,227,199,23,190,33,207,70,6,91,189,140,211,237,238,6,140,48,
172,198,131,122,106,108,29,225,185,141,33,42,138,122,20,179,217,28,188,119,100,161,86,42,119,182,91,84,181,50,243,124,56,73,7,47,226,236,222,108,59,109,43,102,43,118,11,232,19,55,113,139,53,117,13,116,
196,8,125,234,113,138,56,55,135,13,233,28,44,199,40,186,163,54,162,4,208,191,67,117,217,96,160,185,185,222,56,85,91,251,10,44,95,60,44,70,13,181,219,136,168,3,179,13,85,90,174,40,75,134,53,48,137,90,227,
26,94,85,161,13,1,11,47,81,119,195,186,111,146,36,33,83,88,162,99,176,215,185,208,74,174,133,204,46,184,195,28,181,2,60,118,63,132,149,180,161,175,142,147,60,161,142,177,195,74,165,189,13,50,43,230,135,
251,123,221,110,111,20,173,238,108,111,146,183,27,129,75,178,191,191,135,223,212,200,121,16,167,201,139,103,79,186,189,62,108,161,189,221,237,135,143,223,65,180,250,185,75,60,168,225,87,195,233,142,154,
7,117,82,139,45,78,172,230,50,14,228,104,109,26,112,195,45,121,74,68,60,185,96,232,90,238,153,198,218,74,38,205,170,138,234,117,188,59,102,12,55,178,66,128,123,195,149,198,132,32,113,181,110,184,194,36,
34,119,30,14,63,238,201,104,164,49,98,195,94,121,77,157,80,65,172,223,27,174,140,86,183,54,95,204,166,19,112,237,145,58,166,177,101,89,30,236,239,113,17,62,220,101,10,223,104,181,178,186,142,213,14,164,
164,137,181,74,123,194,194,64,213,235,78,42,148,72,82,85,78,122,151,73,222,144,2,238,75,8,129,91,111,83,20,171,211,2,147,76,48,196,202,114,150,246,182,243,213,180,173,239,21,59,17,217,68,72,30,200,204,
12,232,232,186,80,41,194,133,154,12,153,207,34,112,190,247,187,229,120,167,119,127,179,255,112,109,190,211,41,39,252,108,65,38,140,19,174,197,20,160,225,126,148,112,227,134,46,79,120,173,99,50,183,22,
45,186,227,174,203,202,23,188,95,99,28,130,140,73,53,161,247,230,216,92,162,119,129,236,146,234,152,140,228,157,104,13,113,247,51,231,105,51,112,246,188,130,227,28,156,37,70,39,4,189,183,53,27,98,134,
89,210,91,210,134,124,45,107,146,68,87,100,14,244,214,166,203,184,200,80,8,193,10,139,179,108,48,78,117,48,4,117,12,55,0,6,148,125,97,59,157,238,189,123,247,39,7,7,158,40,84,173,111,220,3,67,224,197,179,
167,171,107,235,121,214,121,246,244,83,248,16,52,26,49,98,55,156,23,171,208,127,73,207,95,226,112,183,237,105,75,252,142,56,221,81,101,107,155,234,60,144,80,56,111,76,193,226,68,194,28,228,92,212,30,74,
227,152,77,69,249,142,245,45,49,106,208,123,193,74,228,186,170,34,34,126,161,228,47,227,158,154,64,165,211,160,55,142,43,127,91,237,114,161,60,243,66,168,118,129,200,100,101,46,109,61,197,128,109,14,15,
247,192,116,130,83,7,140,86,132,230,225,42,138,14,15,246,40,82,86,130,195,184,178,178,177,113,239,225,206,206,203,23,207,159,194,26,232,14,6,241,2,14,170,46,84,40,132,224,143,22,156,238,138,32,103,20,
234,41,155,155,54,160,194,78,189,234,12,78,119,130,2,98,89,172,239,44,32,9,169,134,130,238,135,157,181,195,116,216,111,231,247,202,29,108,73,68,37,205,48,16,203,76,167,227,186,166,91,199,195,217,226,194,
178,194,188,206,50,224,236,109,28,62,219,238,221,219,201,215,134,38,89,45,15,248,90,203,50,225,90,172,86,148,178,11,214,165,229,182,20,66,63,38,64,250,37,25,103,23,124,216,76,75,22,81,154,230,170,50,119,
28,56,199,163,51,190,246,56,20,47,48,20,60,183,190,120,21,79,232,166,117,29,122,145,213,178,12,253,122,150,101,172,116,184,29,147,241,204,182,74,40,37,245,162,102,149,190,48,126,209,178,146,146,190,68,
17,146,71,203,181,48,159,221,114,185,92,196,132,16,11,186,71,20,104,61,95,149,196,196,136,121,134,237,104,33,12,118,11,224,183,165,170,120,172,167,129,165,201,136,164,10,158,128,108,22,158,133,209,202,
26,131,96,96,133,94,102,137,163,121,120,146,132,246,14,56,221,99,67,109,220,85,19,171,72,9,168,82,17,163,124,202,240,43,152,118,68,65,44,129,221,150,187,156,184,229,218,73,242,240,57,9,72,248,118,23,133,
40,61,41,72,80,151,83,53,119,194,233,238,124,178,152,232,134,148,224,215,196,118,62,186,127,65,234,254,163,199,20,71,195,159,194,81,177,186,186,14,7,255,131,7,61,235,187,135,240,44,221,127,248,150,10,
29,18,144,192,175,190,188,143,12,38,179,135,98,153,0,12,180,100,235,92,195,164,197,174,36,65,134,146,161,210,125,67,11,5,43,157,20,46,102,122,19,158,214,48,155,172,25,166,73,127,156,13,135,213,100,181,
220,115,126,234,131,76,5,230,229,193,30,151,113,33,208,198,68,63,251,240,159,250,131,193,112,176,146,100,105,24,7,174,246,96,190,179,151,175,78,178,97,234,154,110,61,61,245,90,2,149,214,209,155,211,9,
249,118,101,2,63,247,245,198,113,98,207,146,121,228,123,148,240,249,14,203,79,199,205,178,12,199,31,91,42,199,109,232,240,23,7,63,28,155,94,235,135,158,75,4,85,51,112,38,7,216,58,152,108,196,237,100,228,
90,166,177,85,74,22,136,179,227,149,35,200,96,95,31,202,117,27,60,60,57,70,181,4,74,169,180,158,151,29,5,128,12,162,186,92,75,75,83,248,255,34,41,191,55,107,27,247,97,121,188,120,254,4,46,209,27,12,54,
238,63,188,216,107,227,21,117,82,134,43,96,110,53,57,35,188,23,148,39,37,12,84,203,88,161,188,211,153,205,38,88,58,208,212,253,65,31,28,49,52,196,124,163,81,95,30,233,181,24,85,27,194,108,195,73,207,46,
116,150,193,124,199,121,222,193,218,41,122,41,177,73,40,22,214,106,46,129,162,167,83,158,215,161,17,46,102,212,73,100,100,114,39,55,203,92,64,161,16,136,73,181,16,2,33,116,99,199,169,122,151,232,124,175,
238,35,11,240,77,177,18,167,5,105,90,123,129,185,42,236,158,66,20,106,185,242,53,208,245,68,138,219,148,80,239,12,209,194,139,238,27,120,96,44,96,198,212,133,10,137,92,169,26,187,54,217,94,103,53,175,
231,43,243,61,167,143,200,88,219,60,127,254,132,13,92,216,21,105,146,209,138,193,155,3,123,126,58,25,131,232,227,119,222,213,148,104,160,233,84,171,197,94,163,227,157,124,53,110,235,196,22,199,174,197,
50,111,94,39,228,55,75,70,208,9,188,250,157,240,234,161,19,97,13,53,28,209,198,203,196,113,194,252,179,105,150,193,81,25,200,255,132,166,219,133,174,127,2,152,162,78,89,98,253,113,145,115,132,90,15,11,
149,253,181,208,247,183,202,215,51,30,189,159,208,56,94,86,173,207,96,34,37,60,165,247,97,136,119,191,240,69,182,200,62,251,222,23,169,211,98,243,133,247,191,204,64,214,207,189,247,69,126,222,119,223,
123,159,131,59,247,31,188,101,239,31,105,73,112,190,215,38,245,170,174,125,5,156,238,156,200,171,84,5,94,97,162,18,107,232,66,109,147,229,221,24,203,199,155,162,40,171,178,24,12,135,135,135,135,45,17,
52,91,21,56,120,5,253,27,10,51,97,253,71,52,243,108,191,12,71,171,146,64,136,162,84,97,131,34,75,186,209,249,146,60,238,14,69,175,195,176,247,13,51,44,126,171,183,224,152,114,209,43,71,63,75,72,117,77,
205,178,37,229,117,11,62,50,131,192,137,71,128,21,61,22,180,158,101,174,130,19,201,204,66,124,114,83,78,2,25,67,65,197,241,122,161,48,47,6,255,66,247,10,205,224,24,92,227,17,203,192,8,49,246,131,50,222,
4,64,208,51,51,251,68,159,118,239,69,77,189,62,221,164,176,138,184,0,112,165,173,205,231,179,249,148,83,66,84,104,78,244,131,104,188,53,211,233,180,219,237,89,28,33,126,246,228,227,126,127,120,239,254,
35,9,7,42,189,54,125,241,172,255,232,121,247,222,227,195,39,9,197,5,249,90,4,159,17,25,203,237,67,222,192,22,24,55,150,145,160,248,13,198,17,78,107,106,32,96,168,107,178,228,77,76,106,76,89,183,37,246,
209,34,25,112,1,192,91,111,145,149,164,89,93,89,57,60,60,88,116,93,118,92,136,75,237,164,12,83,178,83,39,199,186,206,210,20,212,22,6,128,19,52,208,240,240,167,243,208,16,116,145,250,215,26,240,188,48,
174,116,244,126,220,81,164,59,122,156,158,14,20,174,123,70,10,226,54,33,117,28,35,126,37,156,238,194,5,54,179,243,214,52,93,215,41,116,1,7,47,203,244,122,61,120,50,156,161,214,194,94,128,127,118,58,29,
220,33,22,103,62,129,9,77,146,253,131,3,46,111,230,250,3,248,188,219,237,80,210,163,5,205,213,235,12,90,215,48,198,170,111,187,112,243,99,53,229,46,182,204,83,236,219,231,216,163,138,128,75,119,207,157,
165,86,202,102,153,168,238,146,179,77,7,134,61,75,6,3,1,88,98,133,61,205,8,168,228,49,193,39,205,85,35,247,31,8,187,217,177,229,22,118,204,4,193,20,210,82,51,203,164,234,220,18,142,71,102,25,120,41,95,
255,214,119,22,120,54,37,233,253,173,108,213,70,201,91,179,77,35,33,9,238,78,90,109,111,62,47,203,2,235,33,90,169,231,130,133,254,197,47,253,202,246,214,203,39,79,159,112,48,130,113,255,160,43,155,186,
154,207,231,224,35,82,60,18,145,125,189,122,54,73,123,181,137,187,245,44,92,203,90,231,187,19,155,87,86,136,243,234,101,144,113,52,205,174,55,142,108,72,131,49,81,231,211,199,214,119,59,0,51,55,74,11,
91,167,100,21,161,76,20,71,179,201,132,51,77,240,130,224,180,175,192,129,175,138,72,186,61,178,215,224,168,91,173,16,221,74,63,2,114,205,112,99,197,201,198,131,71,120,248,179,61,22,85,38,47,219,162,99,
27,57,186,151,239,135,155,47,248,178,51,205,72,156,99,220,222,199,202,95,124,189,249,237,144,199,106,21,202,218,238,150,211,221,199,184,153,104,55,26,154,193,84,207,177,177,149,109,16,182,146,102,117,
85,180,84,79,14,175,7,12,173,18,113,112,17,147,171,112,253,202,234,234,202,193,193,20,54,252,247,254,221,247,224,108,216,222,222,6,249,110,175,3,82,15,31,189,77,126,121,68,128,19,189,102,86,199,106,82,
168,210,4,150,45,153,94,181,60,3,62,154,114,193,44,45,203,152,75,207,246,177,107,29,147,81,82,82,42,153,102,162,111,143,162,115,234,123,40,233,201,38,56,199,227,2,57,59,167,131,66,73,54,79,53,183,164,
36,255,192,58,95,198,24,253,254,55,190,77,33,82,222,57,136,27,4,139,107,183,179,214,47,15,243,122,198,76,87,252,0,91,91,207,168,78,10,75,107,144,160,221,24,240,219,193,238,253,244,211,79,158,63,127,206,
133,56,240,84,176,67,156,21,239,25,89,10,144,55,163,207,227,96,74,209,68,227,164,59,172,167,177,230,251,88,164,58,228,90,119,64,237,242,38,200,128,194,202,96,243,92,107,28,69,46,128,167,229,118,78,122,
201,121,8,129,75,226,206,28,214,184,171,114,47,131,59,15,52,20,213,142,96,91,138,110,183,155,103,25,237,29,180,174,193,117,233,117,187,37,81,11,176,15,98,34,142,206,118,56,48,1,186,117,101,101,61,92,43,
233,207,192,245,172,39,61,70,57,56,223,205,216,3,89,125,136,131,220,212,72,120,5,88,139,157,209,86,195,232,91,36,143,37,124,76,244,138,57,221,107,213,12,84,15,153,206,224,63,41,12,210,121,167,91,34,68,
128,153,167,52,27,164,45,153,147,13,117,210,5,249,225,112,48,155,205,250,131,225,119,191,243,221,127,249,224,195,114,94,246,122,221,222,96,208,235,15,3,122,126,168,7,185,78,119,244,62,243,29,115,64,237,
218,179,164,244,145,217,110,111,169,26,28,179,153,54,64,249,52,87,206,31,59,153,2,176,94,11,57,82,228,53,148,215,194,82,184,174,150,75,178,143,105,97,225,164,38,153,232,107,223,248,14,43,72,170,35,69,
195,108,154,143,170,164,187,49,219,81,92,82,79,42,22,60,193,186,194,47,126,0,56,22,224,248,77,211,100,60,153,88,255,38,248,85,114,248,179,101,246,9,4,215,212,25,124,37,57,31,129,169,109,199,217,0,126,
63,169,103,2,110,140,164,177,112,164,217,114,124,83,218,82,220,174,12,106,13,34,150,188,198,56,248,161,178,88,188,230,41,26,100,149,72,78,9,241,135,73,167,106,138,52,82,49,203,224,105,95,151,96,195,115,
211,108,120,119,160,158,216,124,200,146,140,3,97,107,171,43,251,251,72,6,240,223,127,239,223,82,91,195,237,22,219,37,116,64,230,173,183,62,195,57,44,2,97,217,184,55,169,231,57,50,190,211,249,136,165,176,
71,239,199,248,47,250,80,216,226,237,217,74,1,107,226,110,143,60,246,149,113,186,123,194,58,195,44,207,177,139,187,186,51,117,83,233,253,67,190,27,248,227,53,77,53,97,74,45,35,102,148,22,222,59,46,8,135,
207,62,250,217,135,239,189,247,222,111,125,229,43,255,248,95,254,113,58,155,124,254,189,47,121,16,60,250,252,235,106,101,230,10,100,121,167,114,247,230,86,169,122,137,169,252,22,198,137,248,101,134,254,
3,188,20,181,68,63,180,15,77,243,185,21,252,65,54,154,248,140,97,32,161,18,254,110,123,142,246,148,78,31,240,91,222,37,116,190,127,180,219,238,108,228,109,57,104,102,76,243,74,238,204,124,54,155,16,97,
6,150,64,192,54,192,122,37,122,115,211,249,52,112,196,97,34,54,77,88,247,49,217,34,175,225,162,156,83,179,22,225,215,169,163,100,158,244,70,213,68,208,116,122,65,41,123,141,22,24,255,95,145,169,208,194,
202,175,55,14,189,45,67,40,55,111,127,27,79,57,195,177,191,38,70,35,75,153,182,74,131,76,150,247,170,98,198,100,123,132,71,140,233,180,39,16,125,211,114,194,104,180,50,42,230,179,126,127,240,237,111,127,
247,195,15,62,156,205,230,189,94,103,48,92,237,245,71,97,156,184,87,196,105,83,29,246,253,73,41,181,108,71,238,71,107,207,204,17,138,99,5,233,126,186,82,160,216,234,109,145,199,190,66,78,247,54,84,53,
33,125,141,46,87,205,74,207,244,14,236,33,24,83,204,68,8,191,218,233,14,154,186,180,254,204,14,180,75,129,108,35,205,82,24,227,159,255,229,159,127,237,215,127,173,223,239,127,244,243,159,207,167,211,209,
234,42,135,146,223,50,15,64,239,191,84,91,156,67,231,206,52,215,158,37,166,48,95,150,185,173,142,118,161,213,54,253,83,115,95,8,166,219,102,220,12,105,52,74,95,250,108,43,219,161,106,169,147,5,65,56,175,
160,61,163,223,249,253,111,44,105,53,51,143,178,34,31,173,151,7,81,91,7,87,229,96,127,171,44,43,97,165,32,214,164,44,203,177,187,212,120,204,16,161,80,5,202,94,78,142,8,160,150,41,37,9,222,8,242,25,56,
242,92,82,103,108,59,205,6,29,91,197,196,217,64,254,68,43,141,63,151,185,56,60,11,13,134,226,156,19,153,43,218,177,240,7,248,164,49,17,203,93,210,214,5,243,102,54,159,48,250,227,22,169,102,230,216,230,
43,189,230,56,45,119,184,82,220,138,82,121,164,59,117,154,32,200,34,226,170,43,120,117,109,145,18,11,147,212,108,118,186,221,6,235,105,9,217,27,24,181,200,214,225,214,196,68,29,25,125,244,209,71,239,125,
254,115,95,249,202,111,253,243,63,253,51,156,246,239,124,246,243,225,90,176,116,179,193,212,214,153,170,59,114,45,37,173,22,150,239,135,43,174,60,35,149,28,68,32,156,196,233,169,74,65,221,42,121,236,235,
226,116,135,53,57,117,51,116,223,76,62,177,19,227,123,2,193,187,233,246,122,6,187,171,86,225,109,210,93,69,140,100,103,111,113,62,159,111,110,110,126,231,187,223,121,246,244,233,254,193,193,131,7,111,
129,216,61,189,222,137,242,77,181,221,80,210,83,138,249,110,48,75,62,251,220,10,178,133,170,183,46,51,14,155,66,124,207,103,201,4,138,8,230,71,119,75,155,151,207,45,137,176,107,225,128,15,90,175,69,173,
39,28,59,23,146,179,31,105,20,246,187,95,251,230,178,86,107,147,206,52,202,134,229,126,236,145,133,48,244,120,124,192,100,225,117,93,51,125,56,56,225,176,26,44,101,15,249,144,23,48,23,35,167,157,3,25,
46,140,2,149,68,68,110,186,215,27,80,249,13,248,177,122,156,14,178,182,232,106,169,147,212,178,1,141,150,38,103,42,132,118,56,191,22,172,78,54,47,207,210,196,229,124,254,226,233,147,193,96,100,162,136,
101,138,98,254,242,217,19,56,41,7,253,225,169,182,238,222,206,246,238,238,246,112,56,10,227,236,31,236,237,110,109,245,250,131,52,77,111,177,5,6,24,50,24,116,191,166,13,31,123,218,81,207,82,226,105,3,
34,242,23,48,168,100,187,73,183,136,242,170,157,119,130,12,172,183,110,111,200,92,162,148,43,143,121,241,105,79,205,142,93,36,82,132,92,126,248,225,7,191,254,235,191,222,235,117,127,254,139,95,84,197,
124,117,109,141,175,149,173,236,43,227,234,131,209,242,181,78,220,143,50,18,201,213,190,225,155,36,188,207,82,10,28,124,184,45,242,216,215,197,233,142,128,115,88,242,218,14,116,223,168,104,230,230,214,
249,96,158,70,224,110,175,55,204,187,93,88,72,108,108,36,73,6,46,200,0,44,216,181,141,225,112,5,52,215,211,39,159,230,157,206,87,191,250,213,191,251,187,191,3,61,246,184,255,118,87,117,119,220,238,212,
205,61,213,34,42,184,27,206,18,205,182,180,56,18,132,253,165,198,49,23,210,2,139,93,193,76,219,28,20,34,148,67,240,254,180,103,55,141,124,127,67,62,219,174,125,86,197,177,111,232,200,91,96,78,218,76,183,
117,35,159,69,224,203,248,198,64,8,131,30,12,6,147,201,132,156,62,189,220,11,56,150,99,29,191,40,214,94,228,89,94,86,21,108,150,218,152,170,40,144,231,140,110,154,240,96,145,51,73,85,78,116,200,66,46,
88,44,22,40,108,169,37,52,194,234,27,218,107,158,133,8,135,97,179,78,135,202,173,68,134,59,199,156,131,44,207,243,156,50,27,102,33,35,29,34,219,243,175,245,230,32,221,41,12,28,129,102,171,14,86,210,149,
131,108,101,82,29,244,23,50,202,245,71,107,105,154,143,167,7,240,86,9,186,133,11,46,226,52,13,129,98,6,195,254,254,254,193,127,254,207,255,219,247,255,236,207,126,246,179,15,95,190,124,201,244,252,217,
240,192,196,174,220,27,17,41,105,187,184,214,137,251,193,252,180,224,123,28,59,2,45,213,3,47,144,238,71,161,61,41,113,51,221,34,142,228,21,35,221,57,83,209,146,221,114,224,198,112,15,171,102,148,154,228,
165,221,228,10,89,222,228,70,17,2,222,36,121,167,239,27,77,74,194,4,214,220,253,7,143,235,186,250,201,143,127,242,246,227,199,223,251,222,247,126,248,195,31,254,198,198,87,246,245,193,68,79,165,166,74,
115,148,167,185,246,44,49,147,70,22,35,25,14,203,80,113,98,227,195,47,62,170,125,147,106,112,237,145,238,154,11,185,17,114,220,10,136,71,11,179,142,86,75,150,240,141,176,138,209,183,190,253,175,151,181,
218,60,238,181,81,60,172,38,90,140,91,85,204,38,96,187,18,115,110,221,235,247,199,232,6,10,96,53,128,179,34,111,35,132,26,84,56,211,133,58,131,52,58,211,89,8,45,144,115,227,164,107,108,147,55,115,223,
248,92,212,104,36,125,109,245,178,181,47,0,8,198,1,130,166,107,218,201,228,0,6,158,142,15,11,100,200,52,135,251,7,156,192,174,209,134,52,121,154,37,113,50,25,31,98,39,113,107,167,88,252,217,129,29,11,
87,158,77,38,89,158,215,85,53,155,140,235,178,132,163,15,86,12,220,15,156,195,96,72,30,236,237,193,56,142,50,122,195,209,42,12,50,27,143,203,114,14,251,51,193,55,125,35,47,166,2,13,222,233,92,59,63,229,
107,2,196,188,14,44,99,62,73,67,241,36,75,80,169,78,161,225,239,38,91,150,137,147,4,78,251,78,175,15,110,41,246,10,195,28,60,40,141,20,172,209,213,181,251,131,17,66,79,62,249,228,227,110,167,251,175,126,
251,183,255,246,111,241,180,95,121,168,227,188,170,167,125,91,165,167,92,107,233,126,180,111,204,37,205,111,124,63,84,166,9,62,157,211,157,0,238,11,227,139,150,118,150,198,89,154,217,96,22,48,137,54,79,
196,249,109,141,94,33,167,187,243,156,238,28,84,102,79,167,80,101,237,234,190,238,119,20,204,126,25,186,96,9,164,155,67,142,24,183,179,124,159,33,228,55,24,174,192,194,248,240,195,15,127,231,183,127,27,
118,214,65,121,88,37,146,111,17,174,30,90,252,215,70,219,8,2,198,46,26,142,240,92,101,49,241,118,249,185,86,55,240,145,41,61,40,161,119,212,235,38,102,182,47,141,173,200,111,159,232,60,62,166,213,28,28,
8,76,123,230,209,231,184,165,41,139,199,170,4,172,39,56,205,16,174,134,7,136,210,129,64,131,44,101,174,102,74,147,68,197,49,103,211,145,162,44,198,92,102,141,133,8,49,219,101,145,195,72,24,60,28,220,198,
102,239,190,48,228,43,113,45,67,40,4,51,38,190,46,250,97,177,35,157,92,234,106,123,107,147,53,63,204,200,254,222,110,76,215,226,147,112,111,103,11,188,209,195,67,248,120,59,201,178,154,50,247,164,173,
147,121,49,175,234,202,54,205,179,79,63,238,118,251,160,185,96,224,201,120,60,155,77,6,43,43,47,159,61,69,22,227,60,159,207,102,236,181,63,123,250,73,83,215,195,209,104,107,235,229,104,180,186,178,190,
254,102,34,221,25,19,200,232,243,182,200,106,99,147,238,76,153,182,220,239,249,174,232,34,3,42,42,75,50,219,243,227,184,48,78,116,255,193,163,166,174,254,250,111,126,244,248,241,227,239,127,255,79,127,
248,195,191,122,251,203,113,51,235,54,243,236,172,107,157,131,116,119,82,71,162,60,173,141,38,200,40,218,11,13,209,58,163,25,162,48,1,205,124,90,179,241,193,139,231,207,64,189,193,210,122,244,232,173,
20,181,140,246,61,47,140,52,7,146,16,231,107,70,186,51,183,170,242,110,185,52,206,104,225,236,45,183,212,214,186,90,123,164,31,76,213,244,208,141,91,4,159,114,75,52,229,203,123,156,97,60,7,150,10,59,52,
160,156,254,210,227,95,253,251,159,253,223,127,243,227,255,243,219,223,249,246,15,254,226,47,239,117,31,105,234,35,31,100,174,77,177,107,124,51,93,233,20,71,59,97,50,62,120,249,242,185,165,169,190,119,
255,1,28,243,196,182,72,21,93,215,185,22,190,91,2,76,41,15,73,182,167,214,0,221,10,79,6,206,204,239,125,253,155,203,90,109,18,101,160,39,71,109,33,113,116,167,230,179,73,85,149,212,39,210,160,123,71,188,
186,108,124,121,245,172,164,116,64,169,208,145,144,31,10,60,246,162,44,73,239,70,57,35,122,73,170,200,135,177,54,157,106,2,115,58,77,186,220,7,193,151,128,72,135,118,106,193,130,222,16,159,84,157,98,204,
69,0,224,40,129,245,180,186,190,49,92,89,3,139,105,227,222,131,222,96,48,71,96,113,159,26,88,77,187,189,62,168,152,52,203,30,127,230,221,52,205,230,179,105,127,48,4,107,98,122,56,94,93,91,43,235,106,58,
153,20,5,248,190,109,222,233,130,21,6,191,53,232,13,14,246,247,135,43,43,111,189,245,14,76,23,24,101,157,94,15,116,30,113,209,226,97,82,87,229,198,198,131,155,156,12,101,49,7,119,245,38,39,12,58,143,90,
113,8,138,101,88,53,196,84,162,76,5,244,100,211,52,137,178,113,220,45,226,172,209,77,151,223,197,49,153,83,199,89,89,93,135,199,252,224,131,15,190,250,213,175,30,236,31,76,15,155,216,141,206,191,22,143,
227,124,47,104,111,134,73,177,186,239,246,234,203,253,124,119,113,94,215,252,114,99,242,247,119,119,182,123,189,94,18,37,85,85,141,39,135,211,241,24,142,147,56,78,185,91,117,44,62,166,148,43,74,7,153,
215,196,233,206,151,224,21,235,219,68,25,42,124,129,233,176,115,83,198,42,234,169,238,64,245,19,151,224,155,85,12,59,210,92,95,194,56,0,99,65,53,70,35,55,92,85,163,142,206,239,173,223,255,199,143,254,
223,183,30,63,254,194,23,222,127,241,242,37,155,39,206,242,211,217,43,181,198,225,248,36,213,246,26,207,195,231,208,183,117,194,195,127,176,191,211,235,246,96,186,192,250,193,169,158,140,59,157,30,24,
224,34,115,244,90,212,221,253,252,54,72,150,195,124,39,91,227,184,187,193,51,198,210,85,201,107,53,112,38,42,133,20,19,30,229,160,217,89,97,116,114,81,54,108,129,7,55,126,137,175,90,200,0,120,249,146,
209,68,196,102,216,172,56,226,194,78,222,60,216,183,221,233,184,45,57,8,183,49,221,244,132,229,162,101,131,246,11,183,235,60,156,86,10,145,180,144,181,48,42,143,153,155,66,223,33,19,197,224,235,33,69,
236,33,120,133,83,65,238,121,255,2,28,189,181,245,13,248,118,119,119,11,125,70,98,83,164,170,165,22,254,73,175,112,194,203,5,134,2,39,174,63,26,149,243,57,231,44,110,114,50,28,155,231,43,141,99,4,207,
45,28,234,60,39,200,8,160,57,43,210,30,147,105,74,112,184,77,58,28,199,163,237,166,232,184,34,63,41,115,114,28,235,234,183,63,191,250,193,63,61,253,241,79,126,242,157,63,248,131,191,252,193,15,122,93,
117,225,181,152,211,157,184,178,60,25,131,21,106,32,102,137,16,252,145,183,185,66,34,88,186,141,57,251,236,233,167,85,81,22,6,51,122,195,209,16,116,214,108,58,123,242,233,199,43,171,107,96,2,240,113,45,
232,39,227,3,222,132,26,127,45,156,238,236,163,7,14,117,105,243,129,220,85,228,70,180,213,150,219,54,42,26,232,254,64,247,250,209,125,94,218,13,78,97,75,100,119,17,114,251,128,26,49,200,136,122,232,38,
51,55,131,111,62,247,185,47,252,237,255,245,183,15,31,62,6,43,152,151,1,60,74,114,97,133,54,38,98,19,102,168,86,129,157,17,203,167,27,223,77,94,146,27,108,13,129,211,0,30,40,236,16,48,175,122,131,62,24,
34,224,79,124,242,201,71,43,171,171,112,30,179,222,89,190,22,113,168,94,80,13,206,72,5,182,184,95,1,209,121,204,246,126,176,247,144,88,40,145,30,118,1,104,74,100,137,174,81,24,198,66,218,76,237,22,141,
198,125,41,173,44,122,220,231,138,179,169,220,103,28,253,199,182,205,136,44,75,96,136,112,71,48,101,205,226,28,11,212,186,116,24,11,90,159,72,194,208,35,32,31,200,134,73,161,34,172,208,80,193,121,158,
3,137,248,242,100,110,220,123,184,245,242,249,230,203,231,24,54,34,153,241,193,193,112,180,66,173,159,230,59,219,91,112,159,168,140,6,163,217,116,138,118,126,28,221,191,255,104,103,123,115,243,197,115,
14,141,131,138,93,191,119,127,127,111,103,60,62,132,71,6,159,145,202,184,174,223,2,67,90,192,95,171,202,148,235,224,151,57,212,5,128,135,84,14,236,115,97,89,214,178,12,108,231,122,119,144,245,231,73,103,
30,119,102,182,206,218,89,134,109,116,92,124,108,28,216,104,81,108,163,14,88,100,136,254,125,255,215,30,126,240,211,143,190,248,165,47,125,243,219,223,250,233,79,255,145,75,207,206,191,22,151,221,135,
134,111,204,51,199,238,2,229,82,90,120,217,10,141,10,120,237,150,234,240,9,42,111,99,208,0,117,105,139,25,37,215,26,7,126,61,12,216,31,244,59,221,206,124,62,223,219,221,129,199,0,83,26,51,125,52,142,34,
98,237,182,181,158,153,158,75,172,95,41,167,59,121,166,161,247,182,196,25,137,81,160,229,227,146,187,203,78,220,100,172,38,29,151,71,200,119,129,148,202,70,17,16,92,209,255,64,165,24,87,170,146,241,210,
8,106,113,118,48,88,153,78,103,190,162,88,80,26,231,248,173,139,144,57,107,22,84,231,58,5,39,210,129,166,139,241,138,142,1,174,48,59,24,49,156,86,19,48,243,113,11,212,112,4,207,225,10,189,126,143,72,38,
102,187,219,219,160,142,55,54,238,51,223,20,134,159,174,226,35,19,207,182,126,69,68,231,255,254,63,252,71,248,19,174,141,12,135,81,84,100,131,189,238,198,227,233,115,211,34,71,53,204,38,24,41,251,187,
219,101,85,193,51,79,38,147,69,100,221,55,188,196,48,155,79,17,177,119,67,205,163,112,30,57,196,11,195,246,187,131,245,251,15,5,82,175,205,39,157,251,235,197,238,0,131,238,104,238,183,20,130,77,162,212,
179,39,35,191,40,59,131,218,215,109,177,76,26,101,65,19,135,123,22,2,19,74,210,191,177,50,7,251,123,43,43,107,215,27,7,39,150,170,14,90,107,3,69,31,135,81,181,239,8,137,1,172,211,100,64,31,161,123,152,
151,76,222,71,237,14,18,42,54,119,168,139,8,83,69,68,189,186,45,115,87,116,192,24,135,201,159,141,199,247,30,60,132,165,124,153,107,241,2,8,144,25,230,141,193,3,10,46,157,23,38,155,195,199,32,131,69,186,
160,167,72,99,58,215,208,154,87,255,240,227,205,170,172,3,38,130,195,85,240,204,157,110,183,152,207,193,23,238,118,58,159,249,236,231,140,247,73,13,245,155,66,157,142,115,66,157,211,201,75,229,59,9,53,
204,196,95,216,142,247,247,134,171,107,12,194,240,89,124,43,29,6,24,15,17,69,156,50,187,174,140,99,239,66,123,250,246,88,200,121,116,96,176,242,232,74,21,142,38,229,137,94,89,201,162,23,175,56,66,231,
11,89,156,160,123,88,71,128,245,122,172,66,155,159,206,251,55,220,197,39,205,219,172,175,123,137,78,172,144,103,219,218,214,72,20,11,6,22,53,137,248,235,159,253,239,179,114,166,168,112,79,112,72,8,145,
212,157,60,159,205,231,77,93,131,242,250,194,123,95,180,190,172,61,92,139,206,91,203,21,148,167,222,79,232,18,192,145,101,172,244,142,146,163,26,237,136,214,187,137,76,124,76,171,25,68,193,219,74,199,
29,221,226,228,59,213,233,246,198,135,123,174,196,89,78,147,132,26,204,216,0,90,149,222,100,236,181,106,193,40,72,231,48,170,251,164,192,71,218,233,247,165,231,136,83,21,49,13,36,204,147,161,108,99,255,
43,123,111,218,100,89,114,158,135,101,230,217,238,94,183,246,94,103,6,27,41,154,164,201,8,201,97,145,192,128,4,21,65,194,166,45,2,228,87,254,14,135,195,191,199,164,191,89,132,68,134,77,125,210,7,73,32,
192,160,9,210,146,76,8,152,1,6,51,189,84,117,45,183,238,122,214,76,191,91,230,189,85,93,85,93,213,93,93,221,211,68,99,208,51,125,251,173,60,121,207,201,147,249,46,207,251,60,204,231,19,49,241,46,59,252,
209,82,141,25,255,169,137,126,15,145,120,183,40,75,113,243,54,234,37,199,97,2,207,85,14,117,71,62,47,231,13,2,145,222,249,54,224,168,79,219,245,172,99,210,154,125,28,100,68,49,176,220,85,83,194,153,143,
240,134,10,86,119,153,248,50,55,170,58,244,6,235,121,158,251,166,138,75,174,37,225,185,241,101,47,218,180,224,104,175,163,206,60,105,21,184,223,85,173,122,158,21,165,97,241,43,62,177,217,119,60,62,126,
86,23,181,208,67,41,205,62,56,71,25,224,2,80,11,118,82,20,249,79,62,254,241,151,127,225,151,248,157,96,225,67,206,100,199,74,175,72,150,221,18,167,251,105,27,195,28,85,240,70,165,212,54,232,153,155,224,
22,219,101,11,0,211,97,105,166,103,151,72,131,27,232,60,217,52,99,193,109,104,250,99,7,246,162,184,85,246,14,250,219,88,199,107,122,208,182,109,44,232,171,252,200,142,42,8,76,89,198,66,47,69,146,70,135,
135,243,124,230,124,19,140,120,102,180,31,45,242,28,229,149,210,20,130,241,255,250,163,127,248,202,47,252,18,238,191,13,215,79,34,223,102,106,46,138,145,185,150,2,155,51,68,113,55,40,139,119,145,77,236,
25,135,197,223,107,219,2,86,238,34,235,183,103,121,72,116,37,89,166,209,135,116,176,128,96,39,70,134,30,106,93,14,77,67,54,16,62,248,150,87,196,242,198,184,226,144,75,191,169,187,221,94,224,116,159,102,
67,248,126,29,56,0,168,227,223,50,151,155,85,218,215,10,67,123,55,127,7,110,2,16,155,91,148,165,248,188,112,186,115,221,234,121,158,245,179,54,85,90,123,27,239,49,121,49,10,228,253,187,242,56,222,38,70,
36,183,207,59,120,18,18,244,26,210,186,181,54,197,151,52,239,213,139,86,221,72,61,173,110,68,102,134,250,121,162,166,41,15,246,159,85,68,49,228,213,194,233,149,214,124,26,58,210,164,82,130,123,246,121,
87,31,45,121,94,78,220,12,154,91,230,116,127,222,70,251,236,158,215,245,51,129,7,93,121,208,191,144,255,153,165,46,145,85,30,185,18,112,209,4,252,17,85,109,161,182,122,78,103,140,128,45,204,72,144,186,
100,195,173,131,229,137,29,67,4,106,253,46,201,217,119,34,125,197,139,194,166,191,183,255,184,34,183,61,8,92,250,51,134,36,178,75,4,247,48,40,143,105,221,5,242,233,225,218,23,197,200,162,40,77,201,194,
88,71,183,33,139,231,51,80,154,147,40,240,134,116,203,241,73,58,88,143,18,67,220,210,48,231,254,96,29,86,15,30,185,180,223,198,68,195,192,168,188,144,191,162,186,137,11,240,116,240,141,179,44,197,34,66,
156,238,238,220,245,226,105,96,20,205,147,206,90,113,66,34,157,49,209,212,96,81,195,159,159,86,212,19,188,255,249,90,119,235,219,180,121,69,78,247,101,44,224,25,193,249,254,160,226,214,155,176,97,137,
220,64,49,26,113,253,215,169,168,85,164,253,41,4,124,213,100,29,188,13,46,144,241,54,71,241,111,67,136,74,92,227,143,62,251,153,232,98,161,84,80,196,162,246,161,30,68,9,1,205,184,150,181,181,33,108,181,
73,28,7,172,50,203,198,5,181,244,91,230,116,191,148,211,206,210,251,219,104,22,100,160,87,29,13,20,83,104,160,238,41,215,16,40,148,6,7,48,98,246,93,100,149,226,158,1,244,173,228,219,61,143,110,145,74,
9,5,230,153,203,54,220,176,214,245,129,61,178,240,64,106,79,70,173,151,54,28,147,62,121,242,8,153,2,61,65,40,59,75,65,130,132,119,40,142,71,55,214,55,185,165,38,108,105,100,105,47,68,219,104,45,234,240,
68,233,117,11,204,189,49,70,137,167,121,214,219,245,201,40,233,143,226,246,90,62,226,93,45,141,205,230,230,214,209,33,102,178,248,84,161,163,151,216,109,88,11,65,73,95,91,67,9,44,75,92,151,138,138,122,
49,177,58,48,106,60,49,230,164,53,132,159,29,54,8,25,61,151,211,253,109,19,49,125,75,144,238,111,165,141,9,177,24,45,113,151,244,22,17,37,248,203,113,223,209,106,99,128,188,69,23,28,87,29,173,13,236,159,
47,230,249,98,190,176,212,30,79,9,151,134,194,23,209,7,229,114,48,23,139,91,89,182,189,125,7,107,243,140,207,246,165,105,198,154,210,141,141,110,19,233,126,37,222,59,147,50,8,139,111,28,215,236,176,158,
168,44,22,10,73,8,156,177,165,152,116,167,118,90,114,90,105,123,165,206,113,118,23,99,138,73,87,121,214,3,232,103,168,250,3,61,40,116,121,168,142,92,132,59,28,201,232,90,118,244,16,228,97,24,191,102,23,
243,121,153,231,12,16,136,164,71,175,9,77,84,154,161,142,120,134,24,8,131,134,27,91,204,63,197,76,7,168,51,118,181,24,217,247,44,189,118,86,222,115,56,221,97,165,116,170,197,52,27,12,170,153,241,249,169,
180,213,89,223,216,56,62,58,162,241,224,230,198,228,108,199,42,116,55,82,138,49,33,202,202,78,167,19,9,148,161,181,185,125,199,203,79,170,198,68,227,180,219,41,23,174,174,236,207,57,221,63,183,223,203,
169,85,146,6,161,73,208,217,34,235,149,229,188,93,77,123,129,8,137,195,147,60,159,143,79,70,200,109,75,59,17,133,123,132,236,139,150,29,255,33,35,45,112,46,170,238,193,54,52,24,174,75,148,234,217,7,189,
196,31,243,181,11,210,253,214,56,221,175,98,131,239,57,173,104,223,37,174,25,179,166,189,222,3,17,88,55,216,67,134,219,71,69,142,100,196,157,228,232,171,122,68,58,35,105,180,143,73,125,23,157,238,234,
118,95,13,38,118,122,172,70,254,9,72,86,191,44,242,241,120,84,99,61,24,247,114,34,98,43,192,207,240,176,123,167,5,158,174,245,10,113,51,147,121,244,215,214,100,28,207,9,195,35,191,40,70,214,76,127,4,75,
227,22,152,123,99,91,23,116,189,72,88,75,233,123,108,149,39,143,90,253,167,157,237,7,179,61,150,113,135,131,33,73,59,27,27,230,120,116,8,177,30,76,116,116,124,12,95,178,246,148,225,124,208,208,185,138,
7,105,138,58,233,201,246,206,61,2,200,52,12,60,123,212,218,6,171,225,252,48,92,139,187,82,120,114,52,141,166,44,151,147,195,191,192,170,128,14,54,12,152,250,92,218,160,82,101,245,14,124,47,110,255,68,
9,123,161,136,33,68,94,220,100,189,89,85,196,213,180,171,188,54,181,197,190,168,201,241,209,33,44,6,228,222,164,240,1,247,41,99,224,143,116,140,59,129,206,81,214,198,179,69,74,203,79,6,187,85,127,176,
182,182,46,12,232,42,208,128,5,245,87,252,145,219,71,186,95,133,247,157,180,233,24,234,45,145,21,69,103,148,86,167,253,32,65,96,112,227,115,2,178,71,88,114,181,196,29,35,29,61,142,181,93,224,18,114,42,
85,201,186,26,22,186,56,82,35,220,53,72,232,20,6,152,206,198,7,207,246,18,202,50,115,248,106,8,236,145,231,185,31,32,40,80,251,209,172,200,82,131,159,49,232,247,135,107,27,146,157,88,198,191,202,74,216,
126,73,140,172,216,157,132,225,112,49,220,92,102,240,92,155,152,117,80,48,225,198,85,57,58,75,35,167,183,167,79,246,186,187,251,237,173,141,217,158,99,223,17,156,180,86,251,238,189,7,163,227,195,209,104,
100,72,60,82,17,117,25,243,76,174,180,37,185,157,237,109,19,103,76,238,205,0,209,253,246,102,163,227,221,233,158,230,34,174,172,171,38,76,142,250,6,221,45,164,72,223,136,13,6,68,120,66,126,142,191,151,
242,29,164,181,109,216,81,170,165,141,86,101,235,39,206,154,114,188,22,96,165,176,54,246,247,30,89,130,107,51,124,15,181,188,170,202,34,231,71,173,67,250,216,121,165,61,217,96,8,235,220,216,56,65,73,135,
59,95,201,22,199,13,130,158,13,115,0,32,174,154,49,122,6,145,93,184,216,138,170,188,77,78,247,171,217,72,85,74,4,214,204,57,241,53,76,140,111,1,218,144,95,225,148,13,212,140,76,30,143,27,0,34,213,157,
244,240,147,103,123,63,186,87,171,250,192,30,38,81,12,15,130,68,70,154,131,253,199,220,103,5,1,32,179,199,224,241,136,196,154,181,64,37,20,129,120,137,14,150,95,83,222,40,169,79,54,201,210,236,23,55,127,
121,175,58,96,110,120,114,171,176,141,49,241,136,165,75,227,223,132,123,24,56,20,125,29,153,193,85,155,232,195,15,177,53,199,145,62,10,3,59,217,197,69,134,112,219,140,179,190,211,81,187,89,200,173,164,
170,50,172,165,201,100,92,162,0,164,9,144,81,231,150,187,51,44,199,205,237,187,76,140,196,117,147,163,246,250,60,233,110,44,142,58,77,46,52,2,239,40,21,242,69,54,121,145,103,89,235,115,254,189,24,138,
226,69,118,125,52,151,246,103,16,208,228,199,107,156,63,224,242,49,188,66,243,197,162,244,44,204,240,245,17,23,74,153,124,138,4,165,22,38,252,71,252,138,24,121,39,147,52,233,116,58,119,239,223,143,187,
11,24,185,46,18,207,127,103,60,202,152,115,198,190,160,124,139,156,238,87,227,125,23,102,128,64,196,234,169,244,244,5,204,83,134,37,24,4,250,195,161,49,127,25,225,208,148,230,255,77,189,30,185,232,137,
219,115,34,75,136,31,31,60,123,50,159,207,203,162,224,167,5,199,67,158,23,44,114,193,212,125,140,194,55,58,16,70,80,190,144,54,8,136,150,58,221,206,253,251,31,12,145,109,34,93,232,194,103,222,52,209,168,
170,43,118,131,243,145,70,253,61,175,151,185,55,230,232,140,195,105,89,145,162,27,220,164,85,217,215,122,218,26,214,38,217,90,236,71,202,200,189,140,98,62,90,107,1,98,24,129,219,58,175,207,204,45,11,86,
244,135,15,186,219,101,210,30,150,147,126,61,15,12,205,162,206,230,20,113,63,84,60,87,146,102,161,237,223,147,120,188,157,54,47,145,142,165,158,59,119,155,169,223,151,176,65,97,237,70,96,46,171,54,220,
177,44,59,23,201,17,251,128,136,112,91,89,209,228,61,172,116,105,129,224,31,29,236,21,5,86,202,165,5,21,213,149,56,101,46,24,74,238,149,144,196,184,156,108,178,91,193,153,191,190,62,220,220,218,133,41,
216,188,131,48,253,5,156,166,4,13,197,119,236,20,210,29,189,6,138,191,110,17,233,126,37,27,233,0,209,30,73,40,56,134,243,51,202,203,178,166,28,13,126,47,99,42,119,114,193,184,248,215,82,217,88,77,26,87,
123,165,34,117,116,184,95,82,124,141,175,183,210,44,124,31,138,137,60,174,33,194,123,105,225,228,104,137,118,25,112,192,214,134,107,112,171,97,13,76,205,108,77,15,142,155,17,159,94,13,241,101,210,157,
20,23,248,82,164,187,164,177,211,36,121,221,120,198,152,49,124,2,165,161,50,13,75,55,241,206,53,88,140,226,166,62,238,108,237,117,239,238,44,14,13,42,143,59,43,242,92,184,168,153,182,33,48,192,50,64,14,
155,247,170,42,78,83,176,123,214,217,44,116,188,57,59,232,214,11,34,155,82,140,147,54,194,148,26,89,15,216,229,162,48,235,113,83,186,81,189,181,54,47,3,254,36,152,225,91,13,124,53,226,32,248,30,96,218,
221,76,82,251,172,74,227,253,172,165,32,168,210,113,27,123,211,202,69,139,239,15,44,162,249,124,58,155,205,96,9,192,191,48,203,73,122,115,49,38,16,68,86,218,211,5,81,161,6,161,13,86,75,42,19,63,30,14,
135,219,91,119,28,50,124,213,106,145,197,157,133,78,167,118,209,101,183,142,96,138,90,144,238,86,26,90,169,17,2,130,180,230,108,212,70,223,231,77,168,76,178,104,136,173,40,178,22,130,195,23,102,148,35,
38,107,210,188,215,89,150,18,5,7,54,78,56,66,223,136,134,198,153,113,51,177,212,172,6,163,44,22,243,233,100,2,215,205,23,185,97,122,69,203,12,180,184,98,25,63,162,117,192,205,99,121,87,99,173,54,98,151,
20,110,245,250,198,38,159,35,19,59,29,152,254,122,188,126,212,28,113,130,63,136,192,18,217,25,196,191,238,162,24,57,208,245,113,117,249,181,226,25,99,233,164,39,154,119,110,156,212,242,3,134,176,14,209,
160,201,227,217,211,131,246,214,163,206,118,47,159,244,171,105,153,47,144,195,18,129,173,204,206,36,96,194,101,47,190,214,57,178,6,244,167,173,53,184,121,119,102,123,29,204,118,69,180,109,43,102,151,149,
84,158,71,195,99,133,49,74,156,228,38,165,87,241,173,181,121,137,155,110,137,30,234,18,27,212,79,107,234,36,205,174,254,240,202,178,64,206,137,86,187,172,112,245,227,90,188,218,124,224,56,153,23,243,36,
109,49,181,54,219,36,176,254,8,139,77,189,235,17,29,179,40,232,198,8,186,64,252,207,112,134,96,19,181,22,85,158,82,48,8,55,13,95,212,241,201,49,92,165,64,202,70,148,116,133,243,63,161,87,142,119,28,78,
235,144,27,226,124,10,88,130,39,136,101,6,244,203,209,193,198,202,119,229,34,134,61,177,89,116,47,66,186,115,78,226,13,33,221,47,176,17,41,45,62,225,56,239,174,130,108,237,185,137,66,106,146,89,101,196,
100,5,100,150,215,171,121,168,142,107,207,221,130,121,54,34,138,240,38,227,145,195,246,88,236,73,76,162,8,194,110,194,40,88,137,53,61,85,177,18,185,211,218,8,213,143,131,29,103,184,54,132,127,162,56,229,
93,24,78,128,133,202,91,54,227,213,226,143,46,66,213,107,22,159,188,12,233,78,122,55,216,44,5,215,126,189,72,247,101,40,236,27,38,112,5,57,174,29,200,214,222,166,77,103,212,26,78,90,131,113,214,239,63,
123,138,245,29,170,95,240,225,134,106,22,158,124,39,162,179,116,47,234,38,233,160,87,45,134,229,56,133,93,80,200,128,36,65,102,86,240,190,190,167,63,166,194,10,169,143,69,188,63,232,183,214,134,160,104,
215,187,233,17,246,149,198,23,217,236,239,61,25,141,142,186,221,222,29,228,183,185,234,195,59,58,124,150,207,231,187,247,238,239,63,125,188,185,181,179,185,185,125,197,249,140,198,199,39,71,71,119,238,
63,76,147,52,216,84,170,34,26,38,92,112,184,185,186,218,4,157,65,222,174,125,185,59,216,184,120,1,187,86,53,105,75,185,197,218,69,49,91,44,242,170,4,119,67,241,206,72,0,119,175,38,79,89,9,225,23,246,156,
31,168,87,14,209,94,137,8,190,44,205,70,163,81,167,219,135,253,138,115,35,77,158,37,173,138,32,171,201,185,72,119,73,214,120,136,247,205,34,221,177,163,181,174,44,242,163,234,107,143,35,210,145,75,71,
236,162,140,50,99,208,56,212,149,14,57,22,118,22,21,53,252,158,45,157,33,23,147,154,7,20,123,158,207,23,139,5,108,82,228,183,198,20,242,91,238,163,33,184,188,16,129,74,2,159,179,214,228,45,96,245,12,14,
171,86,107,50,158,244,7,107,150,161,95,214,158,168,241,142,218,74,92,82,232,82,240,242,162,62,40,121,201,243,145,247,193,235,244,162,223,175,23,27,24,248,237,201,129,88,226,47,120,75,118,30,101,19,41,
187,157,31,87,110,52,205,186,53,21,104,249,7,9,35,195,29,133,203,222,9,184,81,237,197,232,78,6,139,14,11,31,68,167,175,66,19,19,139,38,122,22,52,9,40,89,110,68,8,68,148,215,79,124,91,109,24,223,120,173,
155,206,128,201,139,108,96,183,202,178,214,206,157,123,151,216,156,11,70,101,233,211,107,47,148,139,105,160,225,103,216,198,167,35,217,107,150,112,216,120,183,159,109,18,18,90,229,62,92,78,190,30,143,
142,2,83,40,131,30,121,49,217,213,115,209,87,206,181,188,214,54,161,25,128,135,53,157,78,210,172,5,97,78,171,211,147,190,119,149,57,55,177,26,28,180,236,92,164,123,36,45,92,120,133,27,71,186,23,243,249,
241,209,193,246,157,187,196,199,127,109,254,188,192,24,229,36,45,117,126,50,145,130,149,224,145,177,106,153,136,95,113,168,136,252,189,14,249,14,43,87,5,20,251,193,209,129,112,129,41,4,18,97,125,67,7,
210,18,231,245,141,228,110,243,184,228,55,33,108,181,170,202,241,120,220,110,119,230,179,89,218,234,72,143,33,77,53,110,226,220,21,194,93,46,65,161,125,65,140,76,116,159,94,159,242,53,35,221,169,138,167,
73,64,37,113,218,50,129,188,135,106,72,1,128,90,144,176,76,219,50,38,171,103,143,49,18,54,170,174,253,235,237,66,131,18,183,40,195,191,146,124,170,154,110,115,193,56,28,74,34,216,204,49,203,53,21,44,35,
143,21,9,204,25,111,171,205,203,220,116,110,149,61,207,134,41,110,192,83,128,215,117,48,24,46,102,51,68,183,69,166,211,67,4,38,68,223,211,233,184,169,155,36,77,123,189,62,122,13,85,61,159,141,73,120,57,
242,233,54,8,222,170,209,209,17,92,102,13,253,124,100,13,154,156,28,227,3,78,19,136,28,59,157,46,124,56,30,143,96,156,118,167,235,247,224,168,174,74,240,209,224,249,15,134,235,172,226,73,167,145,226,227,
93,184,219,40,184,80,94,30,138,48,119,98,227,20,81,68,185,216,8,160,19,81,63,214,47,33,248,10,229,188,100,238,61,10,135,181,111,104,199,84,148,167,111,66,192,87,69,32,82,196,193,211,146,130,215,169,235,
21,196,224,213,200,144,226,76,151,57,29,159,207,33,221,121,163,136,146,232,117,32,221,137,228,215,50,176,224,26,72,119,84,120,111,24,81,9,111,118,69,225,48,215,218,206,77,38,194,107,17,206,66,198,45,50,
208,129,51,195,76,127,146,169,20,137,36,109,165,124,67,53,249,86,214,47,60,236,40,96,185,10,127,92,113,194,216,139,232,17,173,24,251,10,112,183,49,183,72,149,144,249,28,55,44,246,218,56,226,206,162,52,
119,57,12,18,96,131,87,69,186,115,182,0,110,209,107,69,186,51,171,131,166,42,152,227,186,116,16,27,139,164,69,75,216,165,133,253,195,206,115,36,163,160,65,241,120,39,252,155,162,64,150,42,56,130,204,10,
181,207,115,198,17,114,124,37,237,205,20,46,105,156,28,97,237,208,3,240,5,213,183,211,166,118,245,117,111,186,214,203,36,197,25,27,246,54,107,42,85,140,142,14,142,143,142,214,55,54,143,143,15,192,91,185,
119,255,225,147,199,159,194,123,51,92,95,223,127,250,164,88,207,55,214,55,31,127,246,9,166,156,146,52,207,23,30,101,163,78,70,199,16,81,78,167,211,249,116,242,222,7,95,124,244,248,103,176,160,97,159,154,
31,76,49,72,188,123,127,113,114,12,54,112,168,42,127,180,84,69,241,236,248,177,49,241,238,221,187,86,104,212,89,214,200,176,23,225,137,193,165,75,54,20,185,130,141,66,169,10,70,240,201,78,132,202,58,101,
197,174,52,18,138,138,216,189,90,118,199,75,207,109,200,6,187,176,231,178,189,165,23,73,132,200,136,139,141,232,3,107,109,90,230,60,164,187,184,21,141,189,65,164,59,204,4,110,99,224,101,99,155,217,116,
138,162,156,41,138,210,102,173,172,194,175,217,128,95,60,155,142,225,89,128,67,94,33,67,75,7,206,21,240,151,5,140,214,52,173,78,55,38,62,210,192,42,193,239,55,107,85,104,15,25,209,82,70,148,183,135,75,
121,244,45,68,126,37,130,112,69,139,204,26,227,130,104,124,68,185,17,239,102,196,26,198,198,111,48,1,108,36,92,101,2,135,180,206,187,78,134,25,7,121,113,250,148,185,213,22,93,57,86,174,190,38,210,221,
171,103,225,52,94,35,210,29,143,59,101,124,235,128,236,36,70,20,28,177,236,194,13,201,116,36,202,125,232,116,123,69,81,196,8,124,198,45,44,166,61,11,14,34,24,23,211,156,38,129,199,137,123,223,5,227,56,
229,139,23,178,155,49,159,81,131,73,95,42,27,193,87,246,53,235,87,182,241,109,67,236,4,221,212,181,210,248,218,162,47,168,36,84,149,231,218,232,190,62,124,182,143,132,130,131,225,39,31,255,8,62,135,115,
79,33,195,111,62,62,65,169,155,20,246,166,197,34,77,18,120,139,96,113,148,85,185,179,123,175,215,31,192,206,5,47,15,141,19,161,114,212,112,216,58,62,134,16,102,60,62,129,17,214,134,27,155,91,59,240,199,
19,124,127,162,233,120,220,233,244,238,220,187,15,207,226,232,232,0,129,157,251,79,96,30,239,125,240,48,38,214,202,8,143,100,147,13,39,140,18,240,36,83,242,197,241,76,10,175,156,54,243,35,236,190,130,
159,107,106,197,117,119,6,139,194,27,132,76,229,20,176,133,222,105,189,252,65,73,29,4,241,24,237,187,124,4,236,78,241,145,231,89,139,4,108,101,99,36,21,190,0,233,30,155,36,176,241,222,20,210,125,255,233,
227,186,44,91,168,72,176,32,55,45,158,140,224,206,30,38,105,102,235,17,124,201,193,250,6,252,85,153,231,41,106,154,32,190,172,221,234,192,179,128,91,125,247,193,251,112,234,96,124,154,129,113,61,62,25,
221,185,247,144,20,210,106,34,234,115,140,37,131,235,110,218,117,206,144,48,117,143,243,226,118,198,4,26,123,172,125,237,187,67,106,152,51,181,106,252,247,86,92,96,101,58,246,200,39,91,56,88,94,138,123,
42,237,139,96,142,43,99,206,159,63,44,77,209,88,209,250,180,30,49,207,130,222,180,249,92,27,233,46,160,22,204,155,153,219,70,186,43,210,34,231,29,218,75,243,80,117,134,41,120,144,113,28,51,235,45,66,66,
82,215,37,177,181,226,10,70,173,208,25,188,111,194,239,115,106,28,35,77,131,66,140,173,240,94,8,18,66,164,162,220,18,148,118,35,54,39,227,209,191,248,157,223,250,235,191,249,27,166,166,185,169,107,189,
4,93,242,229,72,119,166,73,131,113,210,20,51,53,235,155,91,240,62,192,79,117,186,157,163,3,11,97,93,127,109,88,46,22,124,60,194,109,44,144,41,127,6,155,96,160,138,158,192,57,223,202,32,120,132,133,149,
101,88,106,36,168,102,78,52,208,104,3,79,7,254,56,155,77,147,56,225,85,56,88,27,78,78,198,207,246,158,222,185,255,0,158,80,141,204,101,73,227,219,224,189,240,166,247,29,181,39,226,101,39,148,145,238,152,
28,144,211,155,55,108,166,123,195,211,190,110,216,245,118,212,128,35,94,27,51,124,168,165,130,180,243,233,76,71,101,193,20,37,120,133,114,133,95,102,121,97,150,239,100,8,211,57,202,214,65,182,210,45,153,
49,150,191,94,2,233,14,123,61,28,21,253,1,150,252,97,187,153,142,79,96,135,130,221,170,213,106,239,222,125,0,127,123,176,247,196,11,120,184,157,221,187,7,207,246,96,231,218,218,189,243,108,255,73,9,7,
57,113,13,194,214,182,125,231,238,98,54,61,58,124,54,159,77,250,131,245,36,94,182,224,112,244,202,108,48,13,213,229,121,141,69,62,215,30,83,45,11,241,147,112,110,185,18,87,14,250,132,196,215,78,173,72,
141,173,189,94,139,247,146,216,147,242,44,26,94,216,88,59,193,142,120,31,223,159,186,176,72,56,120,92,69,204,215,166,114,90,100,230,225,205,101,158,137,171,32,221,249,49,46,187,62,133,18,239,230,145,238,
177,84,247,104,93,49,237,17,53,52,89,94,145,44,158,99,132,180,85,108,224,65,30,28,236,227,77,47,74,92,181,113,237,44,211,242,186,208,91,176,177,185,67,152,128,149,113,132,227,39,116,186,146,87,79,213,
80,244,101,36,64,176,66,6,228,143,203,87,180,129,160,169,162,243,31,159,153,185,177,107,193,95,94,255,166,171,139,68,95,194,22,9,163,240,11,240,248,211,79,96,127,25,12,134,16,155,110,108,111,79,79,198,
79,31,125,22,39,241,218,218,122,111,48,128,120,124,52,58,134,215,0,61,2,165,61,85,180,126,246,228,49,92,96,107,123,151,249,157,143,14,15,158,62,254,44,65,239,9,109,182,119,239,28,238,35,7,52,248,93,252,
102,130,167,156,166,173,3,248,232,179,159,97,117,18,93,164,90,77,134,33,87,181,108,127,93,134,117,78,52,93,164,127,36,210,73,33,37,63,34,11,132,211,171,202,115,174,8,35,147,26,209,218,161,4,47,171,4,112,
109,135,60,222,213,188,39,68,224,10,171,138,145,165,146,34,149,213,137,229,138,94,105,8,0,92,153,134,24,69,8,255,220,178,140,163,148,32,224,101,115,229,212,3,241,31,188,68,29,10,183,123,99,192,111,2,143,
9,214,15,191,132,112,18,67,40,8,209,31,28,3,68,67,194,21,15,29,88,219,100,119,32,14,111,71,202,198,37,172,189,178,100,66,38,170,12,56,74,126,218,192,50,176,175,14,9,248,168,67,167,160,207,143,251,82,180,
97,12,87,68,89,136,166,173,146,192,253,64,44,222,145,110,42,98,101,64,103,22,165,170,232,63,104,227,176,70,22,176,232,194,56,31,149,115,119,10,85,21,43,214,241,98,2,78,98,239,65,122,210,92,229,94,184,
59,106,156,189,66,167,183,112,4,177,128,121,56,129,94,23,167,251,25,164,59,103,94,225,216,137,144,62,80,113,29,202,41,35,224,55,118,59,141,222,216,220,92,204,231,149,87,82,180,20,65,192,166,220,239,246,
147,44,217,222,222,177,206,48,93,178,144,189,157,146,162,140,88,229,41,162,174,52,76,37,170,250,52,178,92,189,154,141,238,66,32,110,43,112,109,63,205,231,180,78,92,187,156,181,91,89,73,130,160,11,197,
172,203,47,127,173,27,71,186,127,225,75,191,32,111,120,150,190,255,254,151,87,233,146,91,237,110,183,55,88,165,84,30,110,110,238,236,220,91,181,185,255,222,23,206,208,46,195,190,182,177,190,125,134,118,
121,247,254,131,96,3,254,3,206,185,151,173,97,186,93,208,188,216,190,182,138,98,167,88,197,8,71,255,57,72,119,38,44,65,134,118,2,69,105,220,121,162,4,190,171,97,34,99,39,28,166,148,164,71,61,114,210,86,
240,148,76,202,248,230,26,14,76,192,187,132,104,23,253,119,218,100,113,73,58,22,251,130,105,68,242,82,251,74,191,16,156,210,248,145,180,236,156,45,119,176,233,181,235,80,89,139,66,233,195,131,189,167,
164,173,137,55,1,62,57,60,220,63,58,120,214,110,119,141,40,241,25,137,72,60,31,171,243,162,164,134,34,190,241,232,24,161,228,107,195,110,175,47,176,143,21,136,3,12,192,154,105,218,167,49,153,75,203,243,
147,186,51,124,237,86,53,134,8,173,189,196,161,34,241,4,114,103,232,52,196,138,22,138,135,150,92,215,107,196,25,21,127,135,73,99,34,195,252,241,77,154,118,88,197,221,152,184,97,192,10,237,3,17,118,104,
90,253,50,72,119,181,228,120,240,192,227,215,139,116,15,249,197,213,31,240,234,243,130,80,15,104,248,237,157,187,202,103,142,253,157,53,204,24,73,44,125,78,40,141,12,203,189,158,190,240,107,67,168,199,
90,13,84,213,87,37,99,120,224,178,211,197,162,42,74,56,246,79,38,227,135,221,13,7,143,67,67,28,165,199,46,30,55,137,211,209,207,145,238,193,134,201,216,86,81,236,74,122,146,220,69,72,119,112,64,41,39,
128,10,48,108,211,202,90,152,198,82,42,207,11,246,128,144,199,202,201,121,203,84,243,194,73,43,193,164,8,90,246,251,125,212,24,199,160,56,237,247,214,144,240,0,78,77,8,175,72,64,129,245,180,200,225,197,
140,15,209,216,90,214,227,130,237,77,124,76,194,214,172,150,59,248,181,121,137,90,85,167,215,167,90,234,41,78,247,251,15,222,95,45,65,116,250,3,222,245,224,93,96,155,205,237,93,207,251,14,14,75,2,33,33,
150,83,173,21,196,230,74,226,146,42,9,21,236,134,6,207,18,186,63,12,233,180,94,123,200,39,95,9,135,137,112,200,202,161,48,79,162,18,100,106,167,92,21,147,26,39,73,92,148,16,246,162,212,11,237,65,102,149,
55,38,0,185,233,160,74,208,235,212,106,184,182,134,226,123,116,171,91,237,182,20,148,104,73,48,252,16,241,13,103,144,238,72,133,241,34,164,123,224,129,176,66,147,103,133,183,227,245,32,221,151,219,228,
233,31,192,116,134,71,168,95,132,134,23,213,185,243,108,96,197,159,185,176,230,26,207,141,162,207,19,163,119,162,170,167,176,8,93,152,236,80,37,121,227,42,98,183,36,106,240,120,111,150,183,109,39,69,46,
249,186,171,202,205,200,110,169,226,196,234,67,151,214,215,159,207,235,64,186,191,121,138,103,47,250,114,117,164,187,182,164,193,163,225,84,207,216,102,109,125,115,190,152,41,106,240,226,80,197,80,194,
156,101,10,27,202,183,201,6,105,112,52,216,221,90,173,214,96,176,54,163,58,67,150,166,200,116,152,166,92,112,196,26,153,65,6,90,152,5,179,143,146,31,4,123,104,131,71,139,50,200,0,81,51,13,164,113,207,
149,59,210,56,126,35,72,119,68,155,98,226,168,193,188,38,65,121,148,22,185,67,174,179,115,226,146,252,89,129,4,249,134,109,14,89,237,41,94,7,66,186,59,34,236,77,84,108,13,243,169,152,245,245,45,8,89,43,
4,97,81,30,179,110,8,131,43,252,16,172,190,67,247,80,234,78,69,185,128,227,100,176,182,198,66,118,105,150,178,248,94,112,139,82,133,36,218,181,106,206,32,221,99,42,148,93,22,71,11,153,99,192,215,41,145,
64,246,201,202,155,71,186,19,64,214,94,130,210,118,94,147,235,34,52,124,64,177,43,15,33,83,23,147,111,220,44,250,60,83,246,142,203,193,105,62,210,233,76,103,69,99,217,38,162,159,133,40,35,207,243,201,
120,2,87,46,225,192,215,81,110,186,71,77,221,87,213,122,212,116,117,241,84,101,11,27,189,89,164,251,219,64,241,108,229,65,95,3,233,94,22,186,227,76,218,41,139,147,148,109,146,4,95,3,216,71,82,44,200,32,
20,64,113,227,27,165,90,96,180,245,225,16,193,77,117,67,137,29,164,210,134,215,107,50,157,48,193,33,188,105,16,64,97,244,237,21,222,34,84,178,48,174,78,185,78,193,162,111,148,48,173,3,171,159,90,169,124,
173,150,50,26,250,117,251,132,60,187,119,31,32,77,130,151,149,242,136,51,47,158,184,76,110,122,254,47,183,164,111,165,72,229,84,220,202,3,204,244,98,195,216,190,238,85,122,196,72,119,240,1,81,0,149,148,
216,193,209,156,85,51,207,192,78,119,18,187,50,7,176,248,9,211,199,37,177,46,252,62,157,78,225,1,49,99,223,218,96,200,168,99,70,186,119,84,187,81,245,220,45,60,55,163,112,186,147,110,183,187,16,233,174,
185,26,224,120,71,246,176,44,141,130,161,164,44,115,179,72,119,179,2,237,20,197,83,94,67,252,3,94,143,64,26,107,184,51,138,82,50,38,52,40,5,20,251,170,205,185,227,16,248,161,33,208,159,103,221,208,94,
23,135,234,110,152,95,100,253,227,43,219,12,140,125,104,114,56,136,63,117,237,35,151,230,182,9,54,132,96,196,236,9,206,37,142,86,199,169,181,25,233,214,103,22,158,144,186,175,138,129,105,174,53,159,115,
191,215,139,238,225,139,109,174,50,206,235,179,33,93,120,76,208,130,13,161,132,34,175,53,207,88,27,17,95,58,99,83,47,90,38,45,168,77,75,128,102,28,34,193,5,167,147,41,188,78,95,248,226,23,191,253,173,
111,131,91,4,43,101,103,103,11,118,43,42,162,37,204,195,57,197,70,233,25,177,155,199,105,146,118,58,157,22,42,120,83,202,13,31,65,147,118,154,106,158,53,72,166,28,113,20,105,188,38,5,87,234,248,223,13,
167,172,40,42,164,253,206,132,30,58,95,76,163,108,247,173,216,164,89,134,202,7,162,68,233,88,92,135,51,95,4,232,71,128,11,50,32,58,214,40,67,27,202,170,154,0,73,91,141,91,57,204,132,63,77,220,180,163,
219,198,73,239,14,188,113,91,219,119,98,170,217,47,22,11,184,97,95,252,226,23,191,5,183,26,163,105,183,187,179,85,203,173,78,177,150,218,52,96,51,159,207,89,218,54,77,18,112,108,33,242,21,101,54,18,244,
235,154,206,34,202,249,90,196,241,16,72,158,213,233,56,58,225,79,60,57,97,248,238,65,171,81,188,72,218,173,136,28,156,78,107,129,254,91,43,216,21,145,143,51,236,168,94,217,134,156,127,101,94,144,146,132,
239,227,8,194,251,66,52,60,145,196,187,75,82,155,231,34,203,185,6,39,148,213,87,70,159,175,171,114,93,151,51,21,63,177,25,227,226,86,109,242,124,206,82,225,240,38,88,143,21,90,29,167,214,209,99,213,189,
163,139,93,85,166,58,57,68,17,202,55,128,116,127,75,168,144,95,2,233,142,195,46,218,73,183,72,187,101,61,235,40,218,7,211,20,226,142,245,201,120,4,203,100,99,125,235,119,127,247,155,223,251,171,191,130,
136,101,119,119,187,40,74,46,212,128,131,86,91,68,123,193,14,197,173,78,184,111,38,241,218,112,11,182,67,231,17,21,200,16,143,44,191,93,74,40,123,81,122,10,73,57,128,229,119,59,246,60,115,152,66,93,41,
101,92,23,161,126,227,54,68,95,129,176,3,82,241,208,106,5,233,238,187,41,145,211,29,54,96,112,132,164,7,240,188,120,147,249,218,199,205,180,175,122,29,215,57,209,99,174,38,66,64,55,28,110,78,39,227,186,
178,219,91,187,255,227,255,240,251,255,254,63,252,123,216,232,183,183,183,102,243,121,94,20,129,29,31,70,107,225,177,21,241,77,131,223,251,107,27,205,138,79,180,166,7,240,142,195,37,2,55,252,181,144,238,
30,253,227,115,6,180,5,243,56,196,249,17,223,48,210,221,168,228,242,31,96,183,85,208,240,146,164,165,148,100,140,54,141,100,82,165,201,238,242,11,7,47,218,35,203,49,169,15,203,20,81,187,174,185,58,250,
188,239,112,183,26,171,228,64,101,70,159,181,169,171,114,116,124,128,193,124,99,41,210,209,31,255,248,135,189,193,96,125,184,145,181,218,97,28,112,205,158,184,108,11,247,190,10,14,244,137,78,110,31,233,
254,90,91,25,174,99,115,109,164,59,9,215,69,14,22,112,59,183,121,219,89,174,70,169,141,141,237,207,62,253,36,107,101,223,254,246,183,14,15,158,125,239,251,223,27,174,13,169,127,168,225,96,4,108,32,144,
225,2,86,76,193,33,66,49,54,119,53,55,220,48,1,185,170,146,118,81,23,41,130,105,184,203,22,206,77,167,189,50,187,243,213,119,205,245,64,67,221,112,167,202,11,234,13,151,50,120,211,167,42,167,229,46,166,
213,100,162,33,205,170,134,98,20,223,19,126,126,188,41,223,213,184,28,163,129,222,212,77,169,63,23,99,202,225,250,230,167,159,126,210,238,180,191,245,173,127,185,183,183,247,215,223,255,62,220,106,210,
100,179,28,113,59,6,89,26,223,119,10,31,38,201,230,230,54,169,95,209,141,83,46,118,26,220,171,169,155,49,252,232,154,72,247,48,103,199,44,120,130,206,183,129,27,222,33,189,234,205,34,221,33,214,189,181,
148,164,87,19,16,77,51,46,154,48,26,254,234,232,243,150,46,215,85,62,81,209,190,78,184,50,28,108,224,41,236,61,125,68,233,11,100,224,143,176,67,13,163,31,152,206,108,50,41,243,28,108,30,62,252,66,20,199,
225,90,123,112,6,232,106,83,231,5,220,138,91,71,186,191,86,210,254,107,216,144,155,195,124,237,156,218,104,154,85,164,187,240,139,70,248,196,78,217,44,78,218,237,205,69,60,56,202,143,134,140,70,250,201,
71,63,134,207,191,254,225,111,192,6,255,157,127,253,157,94,183,155,181,82,43,82,93,188,142,53,191,62,156,94,64,79,97,99,71,160,110,190,115,183,189,49,69,74,169,89,47,148,186,130,164,20,165,16,13,151,131,
112,167,162,40,166,86,246,204,142,16,209,155,250,6,75,25,66,202,137,251,44,66,61,41,135,5,39,30,238,37,200,233,78,162,103,4,157,177,190,56,120,1,76,79,164,187,220,161,59,122,160,238,237,170,237,39,122,
159,129,35,159,124,252,35,56,146,127,19,111,181,249,206,191,254,179,78,167,13,183,186,226,215,89,197,236,33,192,137,144,196,9,239,89,89,154,174,109,108,243,61,20,237,53,103,119,52,126,50,130,255,57,125,
125,78,247,48,103,69,133,59,169,44,47,185,40,36,243,174,111,6,233,110,240,145,55,81,212,185,69,142,112,143,26,231,30,113,207,234,125,117,244,57,60,138,251,58,111,148,217,83,157,85,27,248,239,253,189,199,
136,17,231,10,58,45,24,146,195,200,96,193,204,166,211,78,167,155,23,40,104,252,217,167,63,105,119,186,91,219,119,194,181,158,168,246,123,110,122,79,207,127,98,187,150,43,167,183,136,116,127,27,56,221,
193,77,198,18,202,89,190,246,192,32,162,9,152,195,124,228,53,19,4,53,94,72,181,24,13,91,27,39,233,218,164,24,245,225,143,243,249,236,225,195,135,191,254,235,191,246,127,254,171,127,5,70,107,195,97,140,
148,3,200,161,6,143,131,249,130,121,143,132,237,170,223,31,182,58,61,43,245,50,79,187,60,24,43,211,148,39,235,240,16,248,128,99,220,188,241,201,52,198,88,80,155,177,227,230,196,186,57,91,125,159,216,230,
13,113,186,251,46,25,38,223,160,47,27,196,38,150,25,101,38,108,165,6,64,69,200,242,52,138,27,119,62,178,156,115,219,240,85,143,204,104,91,111,109,219,205,35,115,12,15,107,54,155,221,187,127,255,87,255,
219,95,249,179,63,251,51,100,220,28,12,224,144,136,16,229,80,19,74,206,120,153,66,76,38,173,245,215,59,2,10,83,140,152,183,174,185,107,118,99,151,124,86,62,174,76,189,122,45,68,186,227,237,181,87,143,
145,225,110,55,16,110,81,242,147,243,252,65,247,204,82,189,225,6,144,238,129,172,248,22,100,38,111,10,233,190,171,75,24,230,145,235,40,181,180,169,235,114,124,124,88,21,37,55,172,112,111,39,82,8,205,231,
211,233,152,61,246,249,2,243,187,220,176,205,191,238,220,125,16,174,245,51,219,122,223,44,54,213,252,72,247,110,25,233,254,250,72,251,175,110,67,12,124,117,64,177,175,160,177,24,197,46,12,109,94,78,221,
249,122,57,237,101,77,92,140,59,105,111,150,244,166,143,62,158,128,99,251,187,191,251,187,127,247,119,127,247,179,159,125,242,240,225,251,235,27,155,96,189,152,79,97,35,163,148,130,138,146,52,203,90,173,
172,195,90,141,30,164,46,136,151,184,51,209,113,81,140,187,77,185,196,217,27,33,186,19,108,32,159,118,204,2,196,103,83,100,204,153,26,83,40,47,188,25,37,74,79,36,224,75,153,130,116,95,214,254,60,113,187,
15,9,163,218,94,136,44,151,150,26,229,230,118,113,168,143,54,244,112,205,13,126,184,255,255,53,117,253,205,111,254,222,223,255,253,223,127,242,201,79,31,190,247,62,4,227,96,190,152,205,22,139,153,116,
17,198,168,49,145,181,218,17,234,130,106,191,101,58,70,204,175,235,97,166,210,67,133,82,172,68,211,167,85,160,209,160,246,160,27,210,61,163,135,30,129,119,228,170,170,122,53,164,187,98,182,201,228,214,
82,146,175,136,116,135,179,186,235,234,99,151,40,136,221,86,108,14,15,246,144,13,4,53,142,88,11,4,3,13,119,60,254,203,191,252,191,235,186,130,131,157,60,11,83,150,21,199,246,54,77,236,124,246,244,233,
227,251,247,222,227,107,193,51,58,113,245,154,45,14,92,101,5,109,117,75,72,247,183,128,211,93,246,254,139,144,238,65,171,138,162,27,143,116,95,177,177,69,27,73,155,218,243,195,131,103,127,244,71,127,84,
228,197,119,255,234,175,118,239,236,174,111,110,177,135,214,233,246,187,189,1,171,156,80,129,41,162,180,135,242,181,127,225,87,72,7,184,91,85,243,182,43,219,134,122,164,217,155,227,250,83,80,135,14,72,
119,58,150,152,175,40,18,117,135,87,67,186,191,132,141,179,78,244,148,205,106,203,81,228,11,139,254,219,73,65,19,177,105,9,17,188,16,117,76,66,117,140,90,92,69,248,142,156,158,167,111,21,145,59,31,17,
111,93,131,181,80,60,65,167,122,10,191,247,85,247,217,254,222,183,255,240,15,241,86,127,247,187,247,238,222,221,222,190,75,174,159,234,246,250,189,222,32,240,190,175,32,230,181,240,181,83,99,239,182,218,
204,92,54,82,227,169,155,137,13,182,70,97,17,182,33,98,107,38,167,23,230,32,102,79,63,47,254,5,215,249,116,140,44,115,62,141,134,151,24,249,21,121,223,163,175,125,237,107,184,16,117,252,66,121,140,32,
70,242,170,54,244,140,125,110,69,251,114,185,232,238,48,178,156,23,219,185,54,107,186,108,43,187,231,178,38,176,127,104,117,112,240,132,186,109,107,18,77,66,241,59,240,2,32,22,156,76,102,21,66,11,171,
101,14,210,3,169,120,71,170,155,10,2,198,56,137,249,90,181,142,134,186,130,207,11,21,95,50,31,115,253,239,14,78,71,171,221,185,177,123,120,163,54,202,179,20,6,191,73,34,65,124,109,98,79,158,165,237,42,
160,249,60,27,215,164,147,163,124,123,115,247,87,126,245,87,254,252,223,252,27,112,161,238,221,123,143,93,57,12,136,232,238,97,85,122,169,181,32,3,178,96,15,188,5,217,112,28,165,214,206,6,182,232,50,105,
4,229,55,109,104,102,230,162,182,20,191,233,57,226,203,35,90,15,167,84,30,96,71,88,44,230,105,214,226,206,4,95,58,56,139,24,96,252,253,43,218,136,154,129,83,89,150,26,210,63,39,121,103,37,187,172,91,130,
215,241,196,197,2,67,2,107,21,2,112,2,136,84,212,246,168,205,10,61,161,243,228,250,68,84,23,87,104,131,39,189,128,28,193,207,106,230,135,147,131,225,214,240,87,127,229,87,254,252,47,254,162,219,233,238,
222,125,192,34,93,129,143,95,250,3,60,230,32,141,19,94,198,136,98,81,209,142,222,78,85,242,204,30,78,221,52,216,96,12,136,119,219,9,152,203,24,97,208,247,40,118,236,190,166,120,19,157,157,40,230,8,93,
188,96,175,41,196,48,61,68,204,35,53,99,34,160,14,111,195,189,34,40,40,25,37,180,13,213,220,132,136,41,103,58,101,4,191,109,4,150,112,198,102,25,18,222,90,74,242,21,145,238,27,42,159,218,168,230,192,134,
108,138,124,209,16,63,44,35,58,155,198,161,0,181,109,176,55,155,125,2,79,114,105,96,15,211,58,47,10,88,51,13,86,109,209,225,216,127,246,228,97,246,1,119,139,194,174,182,48,217,80,213,135,54,254,71,133,
116,95,234,82,93,147,211,253,140,205,108,92,252,193,183,190,249,31,190,251,221,188,46,190,252,79,238,33,241,177,138,25,224,78,221,142,142,93,0,105,96,246,27,31,242,175,183,242,168,189,128,191,42,142,251,
182,198,66,10,47,107,167,130,98,133,220,253,8,155,231,144,139,206,16,210,189,18,229,228,115,202,11,183,131,116,111,8,52,20,17,140,230,147,159,126,4,158,44,124,211,59,119,238,245,251,3,225,179,84,190,142,
169,88,86,66,19,161,133,225,165,181,146,216,13,77,150,167,144,238,140,255,16,101,121,74,69,241,131,56,206,71,127,240,205,111,129,27,91,149,245,47,126,225,151,231,106,110,137,245,67,116,189,8,13,175,131,
20,154,71,204,199,58,234,217,110,95,247,224,98,123,238,160,212,133,168,88,121,88,37,63,97,78,123,82,108,171,132,121,244,230,226,104,34,237,16,96,246,245,145,238,106,217,181,120,107,50,147,47,141,116,79,
154,194,233,122,170,187,188,250,217,102,54,61,161,192,216,114,107,46,122,19,49,34,158,166,211,25,171,27,112,154,25,110,63,241,14,170,110,167,3,123,22,147,121,98,177,41,118,176,212,58,157,46,95,107,212,
232,142,113,253,72,79,255,209,32,221,5,160,103,133,152,255,92,164,187,248,86,204,19,238,143,226,51,54,48,242,135,191,245,245,131,195,195,143,127,242,241,47,254,234,189,180,93,43,53,46,23,70,21,109,87,
163,155,224,95,120,205,111,130,211,21,196,166,81,59,39,202,7,85,231,173,106,218,166,99,161,9,72,119,234,231,100,226,71,170,106,73,41,10,254,85,251,234,187,200,53,112,233,192,222,34,210,221,10,224,6,217,
126,246,158,62,98,136,89,175,219,105,181,58,211,201,9,56,212,65,104,153,73,129,72,20,62,242,50,171,62,153,40,94,45,19,177,75,85,156,125,122,194,193,75,186,49,226,109,155,181,230,149,41,109,249,219,191,
243,141,163,163,163,143,63,250,232,159,126,241,191,235,184,246,64,245,114,87,76,96,217,66,236,168,185,221,167,9,40,118,216,118,82,151,66,20,217,81,109,184,123,11,149,143,245,20,54,56,234,143,210,94,40,
113,217,197,72,30,248,107,132,13,114,155,18,81,126,94,115,215,243,30,150,186,181,148,36,113,251,190,36,207,122,135,182,255,210,7,230,96,131,156,65,141,60,24,78,183,103,89,150,231,57,2,165,241,72,17,168,
49,79,167,166,138,12,236,86,89,154,162,49,213,104,96,109,204,231,179,94,175,207,215,42,28,117,78,161,160,89,122,107,156,238,175,145,180,255,69,54,158,164,140,235,115,234,57,78,119,37,162,155,129,95,129,
198,101,225,226,51,188,239,16,188,252,244,167,159,238,237,61,254,224,253,47,213,83,83,77,235,168,93,36,237,34,206,176,47,42,163,141,147,69,115,76,132,93,244,152,3,134,183,10,22,111,209,107,230,45,74,70,
129,119,65,229,68,227,152,23,133,233,58,27,199,96,58,71,209,138,80,107,177,64,189,13,45,108,74,26,164,237,146,180,71,191,34,167,251,11,203,20,240,207,179,253,167,199,199,200,100,223,110,183,211,52,133,
109,235,100,60,162,222,190,207,238,221,127,31,91,181,133,230,196,49,141,170,247,212,137,51,4,147,137,92,219,145,112,157,67,48,105,130,38,178,244,24,241,55,13,115,236,137,111,138,218,95,233,79,127,242,
179,39,79,30,125,240,133,47,29,171,209,36,154,182,155,118,87,117,118,205,54,151,117,45,82,237,99,63,99,132,106,170,49,215,31,96,155,27,217,241,92,207,137,146,129,19,149,38,232,93,5,254,120,231,81,236,
175,21,18,24,147,13,61,229,107,236,140,177,79,13,188,228,86,90,150,37,242,216,39,112,38,195,137,167,135,195,141,8,243,211,106,52,58,194,19,59,78,192,163,110,119,186,249,2,188,125,151,181,219,101,94,180,
91,237,86,167,243,114,60,235,177,33,129,76,238,183,228,55,176,200,121,17,145,36,122,9,251,206,124,62,167,146,188,230,78,8,45,105,90,169,124,193,151,0,167,29,220,251,118,171,85,148,37,147,169,215,69,193,
52,175,84,57,166,60,46,242,255,254,99,64,186,115,168,37,170,7,112,55,158,67,186,115,73,94,194,106,94,111,220,230,174,150,226,195,75,52,60,220,252,254,96,157,207,6,28,119,209,3,231,85,39,21,118,64,155,
198,32,23,6,181,200,55,168,12,86,53,112,153,168,41,19,159,56,119,68,53,21,25,189,20,80,96,149,19,226,80,17,230,15,26,225,13,35,221,25,43,86,148,139,103,251,123,227,241,9,76,166,215,69,15,29,92,30,12,187,
34,132,97,47,230,243,168,214,89,220,129,45,35,65,189,14,124,215,154,8,78,194,10,89,90,149,45,92,193,137,112,14,18,125,211,158,19,246,28,233,11,225,238,17,248,130,12,52,97,65,29,52,107,230,205,218,218,
166,246,66,159,179,104,62,117,211,164,78,192,255,138,225,114,26,201,82,224,231,43,93,91,189,128,203,85,22,14,162,202,69,150,149,86,149,151,89,211,161,142,73,249,101,70,186,215,120,106,52,183,3,9,164,78,
128,136,146,155,87,64,186,203,230,87,77,49,128,78,250,236,106,25,58,66,89,246,18,30,78,76,239,57,50,58,224,3,203,86,109,138,188,56,62,124,6,35,116,187,61,216,149,192,19,190,251,224,225,254,227,199,139,
124,209,110,119,242,197,33,60,146,173,157,120,54,157,228,139,121,171,213,134,205,225,168,110,30,188,255,133,86,214,102,153,1,204,134,224,205,35,247,221,51,112,89,209,91,78,206,216,192,83,43,241,33,55,
193,6,119,169,178,98,156,118,191,63,24,143,199,62,181,39,60,188,196,50,71,186,205,190,169,156,97,13,117,195,98,174,152,93,170,109,69,254,157,246,231,27,22,32,47,153,15,210,60,94,237,254,4,27,58,23,213,
229,54,87,25,231,166,109,26,126,225,61,113,49,34,27,41,114,49,42,36,213,21,19,4,26,162,31,224,90,161,240,163,6,96,148,18,130,151,40,248,161,68,90,0,99,83,109,183,74,121,115,169,185,9,142,43,175,194,251,
68,111,142,209,129,34,144,15,250,144,51,100,178,41,145,247,19,6,45,45,160,147,21,164,187,120,121,202,221,14,210,157,187,243,62,251,244,19,88,243,73,154,130,111,181,200,115,43,121,58,230,225,65,183,236,
227,79,126,244,181,175,124,136,11,87,67,84,137,239,94,166,211,182,110,83,26,14,45,166,106,58,177,211,210,86,81,40,35,44,139,140,44,5,212,16,43,105,19,96,235,172,96,20,86,148,21,13,109,195,125,212,165,
41,233,54,230,158,124,52,20,120,117,192,106,175,40,99,9,210,93,56,221,41,151,73,128,60,103,110,17,18,200,92,131,124,211,104,122,151,34,221,87,249,100,95,226,161,38,88,95,211,131,225,250,230,230,246,241,
241,225,201,241,49,196,243,139,197,98,184,177,177,185,181,125,120,240,108,116,124,200,54,112,197,59,247,30,76,39,227,163,195,3,76,149,162,214,27,174,178,187,106,65,28,205,92,132,85,129,208,135,80,154,
69,104,191,124,172,91,112,245,20,222,121,39,50,63,44,209,81,148,5,99,92,140,56,216,150,126,23,210,38,14,228,2,211,27,87,160,19,106,39,2,223,176,219,233,192,198,218,202,240,149,134,211,50,73,82,174,153,
161,220,46,166,70,180,68,25,254,90,212,204,201,197,66,117,237,69,175,222,2,109,231,243,109,28,195,109,56,219,130,36,48,126,129,7,53,46,22,121,224,221,156,109,108,64,15,169,165,168,148,103,85,198,251,237,
199,241,119,254,148,141,196,115,28,220,249,72,83,9,49,137,63,96,89,150,42,232,73,120,148,187,190,0,233,206,62,213,109,32,221,185,125,246,199,63,254,33,236,254,157,110,87,35,171,242,156,95,119,14,175,24,
67,64,91,242,252,63,29,252,167,245,173,45,46,25,41,175,208,21,187,4,118,174,142,107,245,84,119,96,6,51,51,63,113,227,26,5,232,249,176,117,225,42,242,188,212,178,134,206,237,47,76,52,202,233,14,227,195,
121,229,153,237,149,192,57,140,227,234,182,18,180,215,105,27,65,186,179,235,250,54,64,2,125,97,84,18,151,231,35,221,87,55,172,151,171,21,194,39,224,61,85,176,115,44,22,178,146,144,87,100,146,102,217,140,
164,71,180,116,162,43,136,28,233,73,144,111,77,255,195,251,174,108,80,34,192,67,85,160,61,13,251,197,220,20,238,188,76,35,147,120,27,106,238,19,36,58,21,59,153,98,109,134,218,232,9,159,238,52,119,121,
133,120,159,10,205,37,212,113,26,113,47,59,47,178,72,69,224,168,105,218,218,133,237,81,235,101,150,212,95,139,223,11,46,12,93,119,209,191,241,54,145,75,108,34,35,54,168,21,130,61,82,34,6,37,28,123,34,
203,166,88,107,143,239,24,11,70,137,92,5,82,181,241,253,209,254,72,215,171,227,104,226,87,144,104,139,108,24,170,66,100,106,210,79,202,222,156,213,110,201,181,130,103,173,102,53,19,235,87,38,31,179,103,
144,238,180,118,35,94,220,171,229,133,215,128,116,151,152,133,85,203,168,66,157,51,86,131,235,107,33,211,201,142,36,124,247,189,253,199,221,1,82,81,39,136,98,111,88,126,184,113,245,212,150,83,53,139,85,
212,87,189,158,238,182,244,214,129,62,42,85,73,175,131,182,158,180,144,89,202,8,67,128,240,37,82,178,48,236,189,114,102,172,97,253,85,218,138,48,25,132,73,64,12,41,20,105,246,68,68,115,92,213,181,244,
195,161,143,106,88,149,50,246,124,237,56,213,183,11,18,136,161,0,190,104,146,36,82,231,32,221,95,186,86,200,153,17,136,41,30,63,254,84,17,37,57,196,122,59,187,119,14,158,33,125,56,235,83,112,14,145,31,
42,214,104,137,207,132,183,39,136,203,62,115,9,47,65,57,212,45,181,176,210,198,97,125,243,7,57,80,136,229,172,157,238,33,154,16,201,12,153,20,145,50,67,17,170,22,71,6,110,4,31,46,17,83,244,210,230,34,
192,43,163,252,25,172,216,227,205,210,12,130,38,71,228,138,48,79,88,82,172,170,64,137,143,166,84,201,18,52,228,175,197,201,32,105,1,185,230,162,127,179,109,34,151,216,48,227,59,242,131,227,221,174,185,
184,6,75,59,137,4,137,102,164,8,104,201,77,16,239,139,245,108,36,144,17,213,3,229,153,179,26,206,241,115,109,55,241,34,87,124,15,217,38,236,161,190,61,56,226,112,136,67,74,177,177,94,109,130,78,16,196,
222,122,62,56,198,70,48,210,93,36,248,136,26,244,117,35,221,197,55,33,36,209,250,250,230,193,225,51,38,99,197,206,74,110,216,246,58,67,68,40,128,101,5,184,107,79,159,60,126,239,253,47,16,252,56,102,23,
76,16,109,152,141,109,198,102,50,87,139,109,189,185,171,182,15,213,241,194,228,13,11,21,243,13,33,59,108,153,170,79,129,0,124,77,92,30,16,209,104,81,204,78,71,146,232,66,26,244,175,85,240,80,216,95,243,
109,3,140,62,87,34,56,102,204,171,225,57,111,220,6,219,120,168,103,156,195,67,199,153,74,216,103,79,123,88,215,174,21,86,244,156,178,78,123,247,222,125,95,31,109,122,253,33,252,179,10,39,233,116,123,188,
142,225,49,195,63,188,61,82,42,87,212,4,60,237,14,179,43,107,255,224,207,218,52,240,116,108,197,30,163,215,145,78,132,238,208,105,31,15,90,235,23,244,82,168,138,186,172,173,215,52,247,39,127,146,166,89,
133,108,115,89,132,137,82,199,215,74,180,154,208,152,23,205,39,136,29,92,125,209,191,217,54,145,23,218,4,198,43,169,182,145,67,164,67,95,142,135,35,48,254,150,201,36,61,190,195,105,70,72,43,241,140,40,
219,31,198,161,22,16,22,1,59,101,163,8,233,46,65,32,163,147,216,113,224,196,148,87,159,247,132,191,232,230,89,207,54,253,60,167,187,190,65,78,247,75,108,132,4,142,166,180,177,181,51,155,77,224,151,242,
242,101,161,150,236,51,26,20,243,54,205,28,60,255,233,184,211,233,212,244,102,18,218,10,189,249,198,147,252,66,48,248,212,237,111,233,205,77,53,60,177,147,19,92,125,190,176,45,107,181,186,184,245,199,
83,86,249,226,163,229,51,94,153,0,115,83,254,140,225,185,89,204,83,89,29,184,216,165,24,245,54,145,223,158,14,77,208,198,86,176,104,141,62,157,195,122,201,90,161,175,223,92,241,193,139,130,147,236,248,
62,149,235,184,243,192,157,238,6,56,107,83,210,194,53,14,53,54,217,166,213,106,45,230,179,52,201,120,249,114,37,69,2,102,122,60,161,210,71,89,97,156,174,241,149,120,110,73,141,19,164,142,243,39,16,152,
212,84,118,65,24,203,69,243,57,211,2,114,149,69,127,107,109,34,47,103,19,8,216,4,209,73,137,59,175,32,201,234,137,240,20,100,133,177,11,102,29,199,197,190,194,229,225,243,178,153,179,103,39,205,152,228,
122,248,122,107,200,88,41,31,170,243,174,199,200,85,254,105,235,188,10,142,94,2,91,252,70,133,45,211,88,195,66,113,233,136,169,220,213,141,114,186,95,76,178,196,135,159,225,62,155,181,225,122,81,150,44,
191,200,63,226,143,67,6,22,240,142,164,203,170,220,223,223,131,133,202,219,10,216,36,73,218,237,247,187,157,62,75,99,113,18,98,95,61,91,215,195,129,25,192,139,0,62,215,50,10,186,198,51,149,83,71,135,20,
59,229,131,148,231,89,167,29,129,122,30,34,19,90,56,228,198,90,225,144,120,57,60,231,149,224,126,148,190,228,141,2,175,245,156,219,248,188,205,243,227,196,207,75,185,93,235,161,130,111,114,231,222,131,
86,214,114,87,94,28,2,218,85,158,106,89,156,109,220,26,226,196,80,105,201,73,234,246,57,27,171,35,240,12,33,150,155,83,75,56,216,96,87,103,20,113,206,149,51,101,140,144,224,179,200,152,229,124,130,248,
48,191,147,68,195,73,234,138,113,194,45,236,124,173,54,125,145,210,93,54,159,151,88,244,55,254,242,220,136,77,236,53,135,249,53,115,33,241,73,91,171,165,36,135,161,111,222,168,70,164,131,101,113,81,125,
221,191,15,28,59,139,200,27,75,91,42,159,50,212,218,10,254,206,248,87,93,82,235,204,70,194,141,203,172,58,110,124,163,16,140,141,161,55,165,198,2,19,44,131,135,89,68,139,101,254,136,61,157,145,1,183,196,
233,110,168,87,142,221,150,181,181,141,166,44,39,211,233,34,95,196,210,140,17,84,150,117,40,249,97,202,162,170,144,200,152,213,170,201,187,135,247,112,127,239,233,230,214,78,175,55,240,64,67,119,236,70,
137,78,54,245,70,229,246,10,88,131,62,229,247,82,207,221,111,89,194,235,130,128,29,152,3,226,22,41,16,225,195,32,98,144,170,127,38,224,200,208,99,213,175,199,205,215,171,220,240,112,7,120,231,149,87,213,
219,40,95,125,83,200,107,88,174,218,160,44,211,234,86,245,18,172,88,176,77,182,179,14,146,34,146,182,243,21,153,161,88,57,211,5,238,69,234,183,96,86,44,233,194,105,206,183,41,48,227,155,175,199,174,176,
145,216,40,164,211,159,231,152,134,71,197,112,188,11,10,126,143,13,143,179,236,255,144,176,129,188,9,110,30,108,65,36,8,11,186,44,219,237,174,37,111,10,174,213,213,5,188,173,149,201,204,197,243,121,137,
69,255,166,4,17,174,101,19,116,191,49,93,136,29,33,154,143,94,184,19,134,133,159,3,130,1,235,30,178,226,165,130,66,45,130,190,50,37,114,120,168,41,104,107,146,66,32,201,60,20,56,224,70,16,103,136,106,
155,221,168,154,96,168,72,186,95,85,28,9,210,134,168,25,211,39,169,22,75,66,57,158,225,86,84,18,36,158,149,100,215,237,112,186,179,186,13,147,220,255,147,173,95,254,219,226,255,137,16,216,87,17,205,177,
246,205,68,244,13,136,155,23,126,229,121,190,88,44,98,250,149,38,9,60,135,249,124,14,223,110,114,114,60,157,140,118,118,31,132,6,205,167,245,254,195,248,254,174,222,249,84,61,22,87,13,95,251,250,213,159,
59,75,245,192,11,75,61,9,16,70,88,142,97,195,99,229,200,71,92,10,74,14,248,212,215,153,78,111,122,15,46,116,247,4,157,47,5,98,170,183,4,110,120,17,166,246,146,151,194,179,236,19,17,1,87,164,66,199,47,
229,104,130,13,46,9,110,126,150,205,49,202,56,40,148,64,143,66,189,160,75,76,11,136,249,169,95,201,134,229,6,180,132,105,178,200,194,129,236,137,98,245,69,54,240,209,192,85,99,112,14,124,115,38,56,89,
101,153,55,8,115,183,210,253,231,67,18,6,236,114,197,48,232,83,242,29,238,116,58,140,78,216,221,189,155,164,169,32,125,149,221,114,249,177,75,114,108,181,191,112,62,190,9,255,26,223,61,159,207,147,52,
187,169,123,248,154,108,116,112,30,89,211,44,224,176,172,192,166,120,233,176,224,219,74,196,38,109,201,114,139,66,200,204,245,114,214,172,164,128,133,115,252,28,178,248,180,242,18,116,162,124,26,72,80,
214,90,45,193,234,65,45,218,103,250,87,182,78,237,97,15,242,14,176,58,25,252,161,40,242,12,125,127,183,18,110,156,181,9,171,226,234,54,78,36,184,244,166,94,79,117,98,6,105,81,46,56,121,196,254,166,248,
157,44,40,111,249,14,144,128,13,53,148,66,20,25,122,191,171,178,32,121,174,5,132,135,66,178,163,163,185,154,247,84,39,118,209,220,205,131,187,113,3,207,157,198,97,206,117,110,89,147,6,41,14,24,253,30,
23,42,45,23,117,122,199,43,221,224,122,25,187,156,178,137,226,248,204,56,158,70,192,147,214,210,171,23,108,252,82,50,171,54,103,198,225,83,224,212,134,5,1,215,77,61,212,75,108,60,82,68,176,57,204,121,
200,54,171,223,255,34,155,82,153,161,198,126,215,185,50,193,6,124,221,170,42,125,30,1,83,85,220,253,30,192,114,74,250,215,29,223,166,126,175,199,148,151,89,150,245,7,195,48,206,186,170,59,198,61,177,41,
215,116,46,154,207,75,124,247,215,244,242,220,160,13,47,86,179,148,101,12,59,133,246,61,249,75,186,7,159,144,226,36,136,14,44,2,2,80,151,163,27,221,40,42,242,9,237,36,29,146,156,218,113,34,115,137,255,
225,201,120,165,191,218,232,21,196,80,224,35,51,114,116,177,240,12,231,173,57,159,104,83,148,17,224,236,152,97,23,158,61,160,170,40,58,4,64,103,98,31,79,1,122,202,134,69,85,174,110,19,251,180,111,172,
163,13,61,28,53,227,185,90,116,186,61,215,84,224,52,113,194,46,50,62,41,67,254,41,233,125,72,69,79,200,224,60,163,142,232,9,89,87,85,69,187,219,11,55,1,12,123,170,59,113,51,75,185,185,213,13,250,6,159,
59,243,187,121,17,85,174,182,202,233,78,205,164,141,147,212,43,167,50,145,212,151,211,47,49,234,69,26,186,63,207,217,160,55,135,88,249,152,66,103,36,169,161,198,0,46,9,122,170,27,195,20,142,225,90,97,
179,123,161,205,169,13,43,142,219,55,242,80,47,183,225,115,53,142,18,70,36,4,108,84,77,15,150,21,90,248,105,159,107,3,33,120,170,108,63,106,38,46,182,36,15,9,54,105,146,165,73,4,33,45,199,29,130,204,49,
49,63,107,98,32,193,151,38,65,90,143,166,221,110,71,148,192,234,180,219,91,59,119,195,181,32,248,223,53,197,76,197,51,157,94,62,31,118,92,175,245,221,95,199,203,115,179,54,254,38,91,47,152,234,89,100,
104,145,71,248,42,90,222,128,188,99,47,145,157,207,149,184,160,2,106,164,174,66,28,76,116,105,167,157,47,156,73,39,48,87,51,106,78,77,186,128,107,51,132,234,142,4,9,231,61,92,222,63,165,126,239,211,67,
202,75,182,88,41,213,235,51,68,58,37,28,18,173,246,205,18,242,112,126,10,254,102,77,15,50,149,30,169,99,46,123,182,90,25,202,211,151,229,41,255,155,7,84,158,226,156,95,57,138,48,8,144,129,247,139,67,69,
92,150,173,86,28,39,156,252,42,93,57,52,107,176,98,23,54,247,58,199,246,245,173,13,198,196,201,179,176,54,176,57,113,85,42,84,81,216,70,249,162,121,116,158,77,227,44,125,53,226,165,88,218,80,187,146,175,
90,248,188,208,153,107,93,201,230,212,134,117,107,172,88,42,20,164,60,171,101,8,215,67,185,233,18,155,92,197,235,186,238,235,230,68,37,193,38,138,83,216,180,154,186,138,147,24,75,135,121,238,217,44,165,
214,206,92,254,240,31,176,50,146,20,124,178,20,119,171,149,107,61,212,51,120,81,30,169,182,187,194,124,174,251,221,95,199,203,115,227,54,75,54,104,189,226,92,178,91,160,3,32,203,145,126,65,200,247,112,
64,103,248,22,187,192,147,194,141,50,164,232,201,110,111,120,225,151,94,90,248,212,95,62,48,157,18,232,183,225,36,149,243,4,217,202,91,242,200,158,236,128,181,217,169,171,248,52,155,18,196,90,237,118,
231,186,140,75,47,176,241,248,128,13,181,158,171,124,110,22,154,85,224,81,199,217,128,155,63,155,205,177,152,83,55,156,209,81,222,97,16,105,6,37,213,109,132,116,162,194,80,202,113,92,76,106,168,189,254,
64,186,202,140,78,84,218,53,237,169,158,42,201,154,6,38,190,155,127,238,101,89,192,110,11,147,9,38,240,73,93,213,113,146,112,50,70,158,155,86,102,25,162,43,143,188,215,103,108,136,122,48,144,66,138,141,
172,19,38,201,49,92,129,81,75,148,8,63,214,43,216,156,13,9,111,230,161,190,192,166,113,158,110,88,175,244,79,81,67,25,45,68,244,145,236,37,54,198,196,11,103,6,170,72,157,157,168,40,216,24,212,134,92,131,
31,154,205,103,218,19,167,240,139,17,74,42,138,42,155,247,239,63,232,246,214,204,202,181,238,168,69,226,154,199,170,93,57,253,194,249,176,168,239,181,190,251,107,121,121,94,143,13,167,55,48,40,142,227,
80,237,98,64,22,167,228,57,126,148,30,79,170,15,170,37,211,98,72,136,74,80,169,61,32,153,147,169,36,191,238,66,86,138,121,226,188,162,37,119,207,49,71,187,99,126,56,207,125,42,132,157,18,10,152,136,132,
235,40,133,207,180,3,204,105,233,73,27,152,103,110,54,159,198,105,26,120,230,252,28,220,37,92,116,47,180,225,121,164,54,237,233,206,161,27,53,72,132,75,32,91,91,63,123,182,7,81,127,85,86,182,89,130,125,
172,175,62,179,206,80,136,125,184,189,156,59,85,241,38,81,239,78,6,71,41,182,106,224,86,2,127,236,170,78,174,10,171,164,134,174,117,128,119,88,209,56,146,8,0,113,10,78,93,245,185,239,63,121,84,84,69,154,
102,193,230,240,96,255,100,116,188,182,190,65,103,18,218,28,31,60,59,62,62,236,175,13,67,179,20,223,22,17,78,37,27,194,57,54,178,49,157,182,49,210,179,45,54,206,135,168,146,110,147,238,86,227,215,33,86,
120,2,32,246,114,155,87,69,186,191,180,205,42,106,156,67,4,225,87,184,0,89,126,198,102,161,204,161,238,108,235,162,81,229,94,29,7,155,70,153,118,183,31,157,140,155,102,225,188,232,38,51,164,120,102,118,
85,161,22,110,202,167,61,95,107,211,21,93,101,159,214,233,12,45,234,171,204,231,157,65,186,175,176,98,53,84,148,145,228,55,181,233,48,249,164,14,188,58,150,116,106,253,46,166,153,126,39,200,23,10,191,
187,183,230,144,144,67,63,166,21,98,180,29,182,105,122,226,96,188,185,90,177,68,48,178,80,34,243,162,244,139,56,225,144,59,11,128,212,220,244,202,52,117,158,26,157,59,28,111,1,172,203,137,168,44,74,88,
169,147,3,174,166,174,203,197,28,238,196,201,201,168,64,149,147,88,42,4,102,9,52,109,88,226,87,122,146,57,243,135,27,116,154,164,69,83,212,141,74,85,58,26,29,247,238,15,240,86,88,87,216,194,106,203,140,
11,73,68,247,71,220,87,29,241,31,173,136,92,24,98,145,190,58,132,42,206,32,22,201,86,217,217,124,8,107,97,254,112,178,174,111,109,115,187,53,103,99,196,85,164,57,71,180,143,248,107,169,83,200,251,21,155,
139,208,249,66,10,162,53,219,60,191,14,95,104,243,170,72,247,151,176,185,8,197,126,21,164,251,170,205,24,225,86,24,27,38,145,123,170,50,231,109,76,20,149,85,193,172,181,62,96,16,70,43,21,144,50,82,61,
197,247,108,215,205,219,174,57,214,217,28,30,250,213,230,243,238,33,221,209,134,104,15,24,134,131,25,4,91,75,158,59,228,65,169,205,211,44,185,124,153,2,152,67,66,22,67,13,192,8,33,168,73,81,134,167,230,
38,68,118,7,8,128,42,100,6,202,119,146,55,76,23,67,245,251,32,116,46,92,118,88,65,199,30,151,0,223,98,114,27,199,149,120,195,154,157,17,111,15,183,0,214,229,7,159,232,68,249,86,103,126,113,230,139,57,
193,205,76,140,170,189,156,189,50,222,243,112,75,213,9,159,224,227,166,177,178,44,147,36,230,237,162,172,42,43,206,59,245,4,26,132,140,36,42,89,168,130,32,105,142,185,43,168,242,232,188,205,42,89,104,
19,214,88,5,17,93,81,100,173,118,154,38,139,57,158,194,113,183,7,159,157,204,103,237,86,39,246,221,32,77,227,22,243,41,193,72,13,183,49,204,231,83,248,217,24,99,67,188,22,252,109,85,65,168,8,142,99,182,
186,126,152,13,205,104,125,9,242,254,92,116,254,171,175,213,155,64,186,95,211,230,85,144,238,103,108,142,84,90,171,104,215,148,239,235,242,81,147,52,196,159,95,213,133,242,242,223,141,245,58,61,146,248,
196,254,29,148,8,204,23,17,172,44,173,238,170,60,213,110,95,181,102,42,229,240,227,42,243,121,247,144,238,220,177,17,11,157,155,213,190,225,92,9,41,143,52,190,56,21,36,51,117,184,179,202,239,107,65,37,
87,216,96,76,68,187,158,113,198,5,164,59,124,30,139,246,148,10,153,105,15,109,112,58,40,223,72,190,214,4,118,129,208,193,206,15,193,59,98,146,84,230,50,226,237,128,117,241,220,82,49,33,105,37,151,19,97,
246,170,226,10,67,64,39,7,74,47,223,179,173,57,82,12,229,124,22,248,106,26,137,20,33,0,55,17,225,111,41,204,37,152,180,141,81,141,220,227,63,57,84,8,249,28,101,220,18,10,125,202,38,73,211,195,103,251,
85,158,111,237,222,57,62,58,132,79,90,237,206,232,232,160,200,139,206,253,254,232,232,168,213,233,180,59,189,103,79,31,49,38,177,96,82,57,34,189,68,125,163,197,156,207,236,49,56,92,148,140,187,255,240,
61,214,236,122,227,107,245,85,145,238,47,97,243,42,72,247,231,109,38,42,174,149,185,163,242,247,76,126,212,68,39,42,174,202,74,186,216,169,249,89,45,35,127,217,182,35,138,140,119,19,215,179,57,220,146,
199,174,93,184,72,93,103,62,239,12,210,125,213,6,131,97,74,3,249,6,114,97,68,136,124,56,38,76,27,30,32,194,153,219,134,219,98,184,121,144,123,214,40,131,98,176,134,107,5,197,227,139,74,33,17,235,61,15,
123,170,75,209,179,92,34,250,129,154,111,206,34,221,141,142,169,237,177,177,132,116,167,167,252,70,144,238,248,197,117,67,77,147,154,35,51,174,29,19,89,106,227,86,176,5,65,132,145,165,130,173,79,63,105,
145,206,244,155,30,233,51,91,146,80,241,205,72,174,86,53,41,141,99,43,210,166,93,231,30,76,142,196,25,65,194,207,66,251,148,43,220,195,125,117,192,238,240,96,109,56,130,189,234,96,159,99,189,241,120,84,
44,242,245,205,45,38,83,129,111,154,207,103,48,165,237,237,187,237,110,231,241,227,79,203,60,199,14,181,172,85,22,249,214,206,157,131,253,167,112,31,118,239,220,159,78,198,48,14,34,245,3,83,211,27,93,
171,175,138,116,127,9,155,87,65,186,159,107,51,55,250,83,215,90,215,197,134,169,183,76,243,183,69,5,81,72,18,167,206,87,232,125,37,75,49,92,13,134,218,104,230,3,155,45,76,118,232,146,2,209,240,246,90,
243,121,39,145,238,82,142,35,105,41,77,100,219,36,195,33,57,59,95,162,18,167,42,22,5,138,38,18,136,156,224,132,112,187,103,80,187,171,153,250,150,73,245,86,187,14,216,21,136,116,236,164,68,136,243,97,
4,252,25,164,187,79,96,73,91,29,81,249,137,90,84,64,186,19,234,68,223,54,210,157,88,83,193,127,196,66,21,17,177,33,143,115,93,103,105,74,176,43,220,165,5,155,134,139,208,203,225,80,226,105,89,15,37,52,
105,141,52,62,58,40,15,80,123,121,36,76,160,236,84,32,185,101,77,76,59,124,22,96,179,52,67,19,252,65,162,57,136,198,135,40,5,3,149,182,218,240,251,116,58,30,174,111,194,196,166,39,39,16,215,117,186,61,
164,120,162,107,33,179,120,211,76,231,19,148,17,169,144,106,41,141,177,64,81,56,7,107,3,158,93,222,216,170,169,113,179,32,118,111,218,172,223,252,90,5,207,214,132,163,32,50,177,150,110,48,217,254,145,
231,8,195,200,74,121,148,115,232,247,122,105,27,159,221,247,167,41,183,158,185,136,217,121,72,177,118,105,195,72,104,241,11,153,52,73,244,130,148,192,73,232,36,131,175,178,215,164,7,202,13,93,83,84,5,
51,103,135,84,173,239,114,99,1,3,204,46,239,23,245,162,183,217,56,67,227,4,156,164,186,202,181,88,255,249,186,139,254,117,11,34,220,128,13,241,141,88,34,255,162,228,18,167,249,68,41,39,112,82,50,42,154,
181,175,151,66,170,168,146,96,2,181,33,19,87,54,232,98,137,131,193,45,10,161,213,198,177,124,14,87,18,181,229,84,212,170,132,140,19,127,86,90,14,141,231,24,113,132,8,99,36,164,23,242,49,33,149,118,86,
225,253,245,112,186,99,199,178,182,169,110,137,116,132,39,44,10,4,97,176,119,48,251,160,143,103,93,168,60,136,115,73,139,19,97,55,216,70,198,244,185,22,126,62,73,18,246,128,248,121,193,240,149,174,240,
46,26,179,103,159,45,249,72,53,247,119,58,65,168,7,117,110,235,252,209,2,67,165,131,225,250,232,248,16,130,65,248,100,50,57,233,246,251,176,9,224,115,167,251,185,182,54,132,23,110,50,62,46,138,5,214,22,
17,19,87,115,213,143,21,186,12,177,232,112,251,148,56,206,111,193,90,141,169,144,233,239,163,232,63,11,188,24,14,16,36,72,99,146,3,165,60,11,194,173,218,56,105,215,192,19,140,197,5,66,23,198,138,64,165,
216,160,156,170,139,225,182,107,226,87,10,133,132,64,62,27,206,247,121,163,187,126,167,126,126,156,23,94,235,37,22,253,235,22,68,184,1,17,112,34,174,226,150,102,201,23,249,247,145,145,52,204,225,195,107,
151,153,51,185,132,170,130,26,179,135,203,177,14,26,167,240,185,104,194,46,3,199,125,94,209,83,73,240,136,93,138,146,14,163,25,242,174,103,24,21,64,124,237,82,191,199,15,136,255,65,4,254,72,101,18,1,68,
23,240,195,189,14,78,119,102,101,106,84,141,98,74,228,16,177,91,10,30,61,250,89,101,147,102,25,190,239,36,57,65,138,164,13,113,236,89,23,182,126,34,250,10,97,114,227,209,32,240,181,98,163,61,206,139,40,
228,116,84,161,62,243,50,45,230,60,77,98,8,168,121,73,69,74,159,178,161,103,138,114,170,253,1,215,142,238,191,247,1,147,29,194,13,127,128,228,92,120,141,193,112,216,95,91,11,96,14,248,231,206,157,251,
140,9,222,222,185,195,54,48,2,140,19,108,222,248,90,141,213,138,60,134,66,69,76,33,177,226,134,2,231,74,170,238,11,159,52,73,119,220,170,13,119,243,19,199,24,238,35,69,85,42,207,179,206,239,18,51,49,174,
218,76,231,179,178,44,196,215,163,162,36,139,20,4,249,89,44,163,52,40,175,122,249,56,151,92,139,29,253,107,45,250,215,39,136,112,99,194,10,65,214,165,105,184,208,135,40,246,72,228,213,13,62,47,98,248,
69,134,114,237,89,55,13,115,198,74,225,206,105,223,135,232,179,129,200,77,138,184,197,229,138,195,144,83,196,65,16,221,132,47,51,243,243,81,43,162,195,210,27,109,10,130,150,104,56,161,78,40,118,84,231,
54,206,239,166,136,131,224,176,169,22,201,47,125,11,180,212,124,98,209,156,53,54,111,233,134,17,152,173,118,123,62,159,162,118,67,93,245,250,221,233,108,138,247,195,67,133,24,198,224,251,138,185,127,79,
5,88,60,124,253,172,157,69,8,125,206,66,18,7,222,85,116,118,32,34,55,150,248,186,151,235,39,50,9,245,205,40,118,199,216,87,229,62,215,128,76,122,139,53,198,95,237,192,64,95,218,232,213,132,187,215,171,
100,252,190,87,79,113,171,52,223,183,106,227,60,150,197,80,123,205,37,60,235,108,211,237,245,138,162,240,189,110,146,29,160,36,110,77,196,138,73,175,219,213,66,197,127,217,56,151,95,235,29,226,116,95,
181,81,62,130,147,144,67,9,231,85,196,123,61,3,29,24,32,194,17,182,103,185,52,114,72,250,234,189,246,153,123,162,30,111,152,74,219,249,62,126,158,6,53,3,134,107,73,135,59,92,139,242,56,76,101,163,66,102,
74,251,216,7,247,65,100,39,54,218,243,105,121,164,251,109,208,82,35,248,203,194,209,90,194,28,18,149,176,28,153,106,234,172,213,193,198,175,180,206,243,34,207,243,65,127,48,158,140,139,34,79,8,124,75,
160,34,116,26,40,208,243,189,68,90,175,112,1,224,59,57,92,223,226,110,158,216,68,169,74,141,87,181,97,21,251,240,188,44,119,14,196,28,80,211,46,46,28,82,210,180,201,209,198,219,186,198,94,201,38,14,225,
18,69,61,141,47,220,40,238,13,54,244,192,56,33,42,229,15,6,141,223,150,13,243,183,6,254,125,45,48,235,115,120,214,131,77,154,102,176,43,129,65,171,213,106,168,233,65,138,53,17,238,86,40,25,176,88,164,
156,214,189,116,156,75,174,245,142,113,186,159,177,9,167,180,144,79,129,255,226,132,202,146,89,117,77,192,180,107,120,223,18,202,36,52,162,185,226,59,169,84,104,151,118,194,134,30,80,209,150,219,204,130,
38,192,242,90,172,212,128,123,34,157,46,17,219,56,196,181,179,184,67,196,59,34,68,55,48,115,139,10,64,113,176,225,236,231,235,6,235,50,64,101,110,23,141,169,59,174,157,235,28,206,91,182,233,116,187,152,
217,64,133,89,236,181,232,116,58,176,2,89,43,19,230,159,196,72,220,118,124,50,146,26,34,53,102,32,224,160,149,241,247,138,176,21,191,197,92,25,112,149,142,106,213,186,94,168,130,207,15,244,117,73,247,
232,237,95,63,175,87,127,224,107,31,126,168,2,46,16,67,66,39,220,20,158,158,205,72,178,19,209,222,177,180,19,47,217,96,185,86,77,162,126,120,144,18,52,150,21,248,140,180,20,209,10,182,75,198,91,105,13,
15,242,67,180,149,138,96,4,119,240,97,109,46,142,185,198,100,153,43,70,11,225,172,97,228,13,129,134,68,115,216,179,98,6,178,215,44,203,14,15,158,97,79,0,181,47,99,0,88,161,188,213,98,177,192,179,47,199,
38,169,205,237,237,56,78,34,154,54,101,67,98,198,16,81,66,194,249,156,130,97,18,76,230,238,136,140,244,0,81,43,70,34,141,8,154,89,232,232,222,81,201,130,119,88,237,217,230,136,32,77,17,35,210,60,205,90,
232,234,51,222,38,18,89,80,238,41,35,116,82,66,76,167,150,239,42,7,104,9,118,168,37,68,63,97,89,192,181,161,126,14,248,144,99,49,60,96,41,130,198,81,117,196,103,44,110,49,36,154,28,209,35,195,111,71,189,
108,12,62,176,220,51,161,96,247,44,95,216,146,98,169,37,197,239,61,58,192,161,56,187,133,117,122,162,124,18,102,43,161,18,117,43,50,57,36,159,67,173,255,43,227,168,192,89,206,215,138,229,90,150,109,140,
223,233,60,213,175,22,143,216,19,222,52,196,10,27,45,51,149,2,211,97,250,102,237,243,223,101,145,183,219,29,43,212,8,198,115,154,158,178,9,96,230,43,218,48,210,157,150,119,52,48,253,153,94,96,92,107,241,
64,74,210,172,34,154,35,46,26,84,101,81,148,37,139,57,177,216,31,252,218,88,95,31,141,38,96,252,63,253,203,255,217,214,245,193,193,1,44,240,86,59,131,71,124,247,222,67,216,253,121,97,128,223,182,78,116,
201,5,108,88,148,173,35,53,217,230,102,219,140,62,143,54,176,97,253,86,224,52,178,140,40,181,65,229,13,181,124,141,224,247,156,176,100,144,167,209,237,116,59,157,118,191,215,131,243,97,208,135,127,119,
91,16,196,183,219,248,54,70,49,56,197,252,116,233,105,33,73,75,204,20,110,210,37,169,24,33,38,176,38,191,190,99,124,46,49,123,180,88,117,165,60,5,239,125,34,63,103,5,4,68,13,150,145,63,230,157,31,213,
139,149,10,205,46,238,128,168,89,239,49,105,240,239,172,213,234,118,187,15,31,190,159,164,45,146,195,149,102,37,206,2,120,74,11,81,5,111,164,202,227,8,60,79,103,32,249,86,65,207,155,94,123,77,9,175,154,
187,34,104,41,243,86,171,169,7,168,102,6,21,116,209,171,10,238,16,140,80,18,194,144,183,197,4,28,127,130,8,84,77,205,189,242,84,7,73,24,236,131,28,15,56,172,229,109,29,119,46,154,88,89,87,50,172,198,134,
12,98,14,137,16,39,77,195,158,158,88,227,39,166,252,196,240,86,193,14,238,137,77,174,241,50,115,223,110,176,161,91,84,7,105,104,229,119,40,163,61,33,141,17,157,59,145,102,89,29,231,244,181,154,231,175,
21,248,107,164,241,70,11,120,194,111,133,204,67,127,185,77,89,84,16,169,189,250,56,171,54,190,13,73,151,182,26,168,46,124,237,220,229,204,146,6,247,38,107,181,225,100,162,123,75,139,38,194,111,212,16,
140,8,159,48,69,20,195,181,53,56,59,251,189,254,55,190,241,59,63,250,209,143,167,179,89,183,219,30,12,134,221,110,95,216,193,148,25,154,65,203,180,142,244,49,129,149,165,119,245,90,27,235,187,106,19,11,
52,89,132,170,99,242,146,228,28,198,170,106,93,249,39,73,239,76,148,244,251,93,216,160,136,88,203,114,253,17,181,106,180,234,208,102,197,53,142,237,102,115,50,153,142,39,211,178,42,225,61,156,77,79,238,
220,185,55,155,45,33,54,34,232,136,177,183,101,106,49,138,7,43,229,53,211,9,134,103,68,161,140,53,190,188,31,199,41,204,154,101,142,184,73,141,120,145,48,81,34,73,47,59,220,216,90,223,216,10,60,77,38,
144,1,120,144,75,67,18,245,120,9,201,143,136,251,160,101,50,198,19,48,42,143,65,109,56,182,230,27,73,160,61,172,181,42,207,28,47,58,64,184,247,213,214,23,233,97,243,214,34,107,214,176,100,169,35,255,8,
95,0,242,231,106,87,201,176,194,156,142,200,175,70,203,176,76,140,35,195,54,168,222,206,95,129,174,101,184,179,143,31,159,179,141,31,246,204,196,86,70,120,110,98,24,153,189,44,10,153,206,65,27,218,77,
86,108,212,89,27,203,207,250,77,32,248,141,70,188,216,141,94,43,116,74,194,87,155,169,69,95,247,38,106,218,48,10,134,116,210,182,183,119,15,15,246,225,72,168,201,247,132,119,130,81,144,240,87,24,30,82,
239,68,175,219,253,222,247,190,247,165,47,125,233,219,223,250,131,63,249,211,255,99,52,58,121,239,131,47,107,207,109,16,107,51,48,189,57,236,132,28,138,7,210,158,55,215,5,241,246,216,68,95,253,218,215,
151,157,165,76,6,226,249,135,56,212,142,168,49,35,137,163,237,205,205,205,173,77,112,163,230,139,249,225,225,209,209,209,232,0,254,15,14,238,116,10,219,211,201,201,201,232,228,100,54,155,207,231,11,216,
216,6,189,254,96,48,72,147,228,63,255,151,191,255,237,223,254,237,225,250,240,201,211,167,220,167,198,113,156,23,62,144,37,207,93,23,226,22,122,244,84,160,91,136,89,182,203,177,172,166,103,171,240,228,
159,94,149,51,226,164,184,145,192,83,7,102,34,175,76,233,68,195,153,72,32,61,119,165,208,200,89,47,196,226,245,117,173,231,56,244,218,7,82,57,14,212,79,220,130,79,210,85,228,4,81,86,90,145,144,114,228,
2,101,160,149,158,59,8,16,90,173,142,220,212,64,9,40,208,36,79,46,69,209,37,50,31,153,40,52,241,133,97,185,113,106,137,218,95,193,97,172,12,251,130,137,41,207,190,192,238,99,44,186,240,231,16,75,38,43,
196,146,151,144,79,54,87,176,121,225,56,201,235,177,41,242,156,239,249,205,94,139,131,4,240,86,23,110,49,208,131,174,233,76,221,44,40,158,193,3,233,116,251,117,93,58,10,255,125,35,154,8,211,96,181,11,
162,155,4,201,100,126,248,95,255,225,215,126,237,215,215,6,131,143,62,250,40,95,204,214,55,54,89,219,233,174,222,133,241,159,216,125,231,27,123,184,70,246,70,238,225,219,102,131,27,86,192,25,213,12,212,
226,0,74,210,8,248,195,237,86,118,255,222,93,216,125,78,198,147,253,253,131,147,241,9,4,231,88,167,231,174,39,106,74,160,58,51,253,178,205,116,58,159,76,80,66,245,111,127,240,55,15,223,123,239,43,95,254,
242,191,253,203,191,92,91,91,15,108,75,150,48,191,204,111,75,188,224,38,36,185,217,47,36,255,46,226,93,39,196,47,218,87,253,16,110,71,41,15,6,25,51,187,16,39,128,72,53,135,54,56,124,237,99,62,242,57,241,
201,59,17,57,155,232,137,128,243,200,72,78,6,212,198,148,50,131,97,43,82,211,227,44,82,196,62,139,114,48,2,229,164,232,90,8,94,51,220,222,201,206,63,171,194,73,115,6,161,239,66,234,90,50,113,14,219,74,
211,172,21,75,150,80,178,57,252,213,136,106,214,187,193,220,222,65,19,91,29,129,131,59,10,24,77,24,129,231,192,105,71,166,67,224,51,234,220,137,97,23,139,200,172,203,176,176,0,40,62,109,56,65,230,117,
183,41,113,22,37,136,111,138,33,56,213,159,95,27,136,188,210,44,187,241,107,241,74,228,246,236,5,56,89,174,151,170,116,210,76,3,66,29,108,32,190,131,192,188,172,11,124,124,209,178,65,18,105,158,40,84,
132,137,149,69,121,120,120,248,91,191,253,91,79,159,60,133,243,126,107,107,7,158,206,134,93,207,76,182,239,158,213,212,250,67,157,201,136,143,251,188,63,139,155,178,137,126,227,171,95,115,129,87,219,8,
227,157,229,206,45,122,0,253,110,119,119,119,7,60,220,207,158,60,5,239,137,179,36,1,144,194,108,176,122,201,41,18,52,147,213,79,62,254,17,152,125,243,247,126,239,223,253,187,127,215,237,246,12,129,107,
88,206,212,136,212,147,102,124,13,195,175,150,16,77,39,180,185,198,248,104,131,18,10,228,74,112,158,68,133,50,85,8,247,124,138,65,249,19,141,88,235,141,228,83,66,97,193,103,243,84,96,226,213,122,73,66,
43,182,78,105,129,86,43,22,120,245,13,57,154,212,244,124,75,87,152,152,190,104,98,38,76,172,44,242,86,214,90,157,216,10,251,200,217,137,121,186,186,115,38,166,78,77,76,157,157,24,207,225,210,137,105,63,
49,75,27,235,219,204,49,255,138,54,85,81,182,59,157,27,191,214,146,213,80,97,249,184,81,205,192,244,225,40,202,85,46,40,109,14,231,211,180,219,29,96,226,146,146,135,49,22,169,51,164,228,238,175,173,111,
108,245,7,107,16,172,255,236,103,159,180,219,157,127,246,207,254,233,95,127,255,251,96,240,160,247,176,107,186,199,106,52,135,161,2,141,242,77,113,186,191,19,54,209,215,62,252,186,87,249,32,182,21,166,
70,164,158,24,56,232,183,54,55,182,54,55,243,60,127,252,116,15,157,23,199,29,93,82,37,132,95,36,104,46,20,63,66,43,66,14,197,147,199,159,64,100,254,251,191,255,251,16,51,126,255,251,223,255,141,223,248,
42,30,71,243,121,224,75,10,44,37,252,27,1,26,244,82,197,128,134,100,50,47,254,26,168,154,139,48,103,103,133,69,95,251,190,35,69,157,107,142,139,140,236,77,68,196,19,224,129,200,150,107,88,49,147,46,209,
93,224,234,39,37,216,35,46,223,248,17,248,198,225,70,39,101,242,21,54,88,30,150,219,226,194,196,88,101,90,216,27,60,157,235,243,19,171,202,146,146,238,152,161,119,47,152,24,109,63,103,39,38,42,15,12,254,
184,112,98,12,242,244,19,227,17,194,196,34,79,52,203,19,19,12,212,219,202,49,255,234,54,69,177,72,210,236,102,175,197,31,153,21,237,184,82,149,224,198,246,117,63,117,201,204,205,61,250,92,108,8,250,151,
181,218,157,110,111,173,215,27,160,231,149,166,116,90,154,118,167,103,148,253,209,143,63,250,202,47,124,229,203,95,250,210,223,254,224,7,191,180,243,223,76,212,20,254,89,69,177,191,27,207,226,166,108,
162,175,126,248,117,227,35,50,99,82,75,66,76,156,166,237,247,186,27,235,235,147,233,244,217,254,1,225,188,163,192,87,203,133,188,217,108,60,135,224,111,60,154,78,78,102,179,41,216,100,105,11,126,240,248,
232,217,147,39,143,63,252,240,195,157,237,237,63,253,211,63,189,119,239,126,175,223,31,174,13,96,50,224,215,105,113,151,130,43,98,20,247,4,5,241,2,234,92,247,2,156,13,151,222,184,183,83,58,173,40,114,
140,34,102,215,179,172,197,98,27,233,135,160,102,46,42,162,43,174,44,88,230,207,95,142,224,164,9,139,18,10,34,171,39,215,226,142,10,188,95,141,12,75,239,59,19,54,54,77,21,81,109,149,119,40,63,177,70,251,
240,141,43,98,103,39,70,155,14,159,246,50,49,253,18,19,99,72,167,110,46,154,152,137,89,170,99,57,49,47,92,174,150,95,45,226,180,32,143,64,226,239,111,47,199,252,171,219,216,170,129,67,226,102,175,21,96,
29,212,149,44,69,152,133,203,27,109,251,186,215,86,237,66,151,231,218,120,193,71,106,225,160,7,1,255,213,237,175,129,235,253,241,71,31,253,247,255,252,159,143,199,227,209,98,84,103,118,213,134,230,99,
223,129,103,113,83,54,209,111,126,245,195,37,175,45,227,113,41,56,105,181,90,119,239,236,46,242,252,201,222,158,167,22,145,216,109,62,155,30,31,63,131,125,42,207,23,85,81,84,53,1,157,234,186,40,242,233,
116,116,50,58,62,60,56,120,240,240,225,55,190,241,141,63,255,139,191,0,239,236,225,251,95,156,207,230,112,176,192,158,149,47,10,210,13,230,176,177,241,112,27,97,78,119,158,255,219,115,84,70,140,133,178,
174,241,209,162,36,17,100,231,18,144,23,111,116,162,37,206,168,78,170,241,203,135,171,35,8,21,135,124,24,100,61,79,141,32,112,100,107,195,135,92,191,243,57,111,29,132,20,120,88,78,1,234,51,19,211,148,
237,246,31,194,205,129,24,65,38,166,94,114,98,246,130,137,169,115,38,198,226,110,43,35,72,105,210,133,17,156,176,238,189,189,28,243,175,104,147,47,22,180,97,221,228,181,132,215,60,240,172,251,36,68,233,
170,92,23,3,211,27,232,30,97,241,27,167,221,25,27,142,217,165,209,151,198,1,63,250,94,255,254,147,195,199,147,249,236,235,95,255,250,15,254,223,191,237,116,251,103,108,222,141,103,113,83,54,209,87,191,
246,225,178,43,135,214,61,31,218,31,188,247,16,2,159,199,79,158,156,82,40,113,234,248,120,127,54,157,80,207,20,230,134,177,118,107,197,129,165,82,54,120,180,211,40,142,255,240,219,127,248,195,127,248,
225,15,254,238,7,189,110,111,125,125,3,222,152,217,124,54,232,15,214,215,214,78,38,99,81,92,116,158,194,72,208,83,90,164,185,189,250,131,22,37,116,230,191,35,118,11,220,195,34,169,6,48,204,147,124,19,
210,20,98,182,38,233,159,100,122,138,200,123,100,194,241,70,159,69,134,233,4,60,246,131,190,47,111,142,18,151,249,17,98,154,23,143,208,56,235,129,94,171,35,88,25,1,163,59,46,62,88,142,192,195,196,216,
241,89,228,168,75,120,233,196,204,213,39,70,159,47,39,166,175,54,49,30,153,239,119,76,234,73,159,11,142,249,151,182,1,231,37,38,102,146,155,189,214,41,69,50,207,182,70,249,44,11,33,161,113,186,167,58,
3,136,16,53,118,198,121,130,175,165,110,3,130,168,173,78,84,188,110,214,183,204,122,166,210,157,205,221,255,242,147,255,124,247,222,221,15,190,240,133,167,79,247,61,255,4,203,17,188,35,207,226,166,108,
132,79,70,242,190,68,209,9,31,108,111,109,194,130,127,244,248,177,239,140,17,224,17,248,78,37,118,13,87,44,19,198,16,109,24,24,60,44,216,15,219,89,59,207,139,217,108,241,199,127,252,199,48,244,127,252,
143,223,133,23,232,131,47,126,57,208,36,62,126,252,228,189,135,15,182,54,55,159,238,239,7,45,13,105,93,211,68,125,139,128,38,226,210,141,100,127,228,80,17,49,44,77,227,213,22,21,237,144,126,98,88,248,
211,43,217,122,28,1,59,114,4,81,205,58,220,126,4,207,152,207,31,114,167,219,178,113,145,37,3,208,255,20,133,62,223,205,40,115,144,239,171,252,118,73,237,20,212,76,160,253,196,56,133,116,106,98,86,38,166,
8,175,108,35,173,46,152,152,62,51,49,183,20,50,117,238,244,196,244,5,19,91,142,128,108,112,171,19,115,82,105,117,204,133,34,68,183,111,51,199,252,171,219,240,89,120,227,215,162,36,99,116,46,207,122,101,
171,103,246,224,72,35,8,190,111,250,247,226,59,212,144,132,52,94,181,35,94,6,120,122,75,214,25,119,162,38,115,179,128,159,122,239,253,47,252,205,95,255,205,238,157,123,89,154,49,167,187,132,246,239,202,
179,184,41,155,152,67,3,229,37,97,56,74,111,119,218,163,241,73,77,20,110,188,220,235,186,218,219,123,12,27,147,19,173,14,221,212,21,183,144,113,158,172,149,194,19,140,231,243,227,223,252,205,223,220,220,
218,250,147,255,253,79,102,243,249,214,246,250,248,228,120,125,125,139,215,13,108,117,199,39,39,235,195,53,106,233,176,196,72,73,18,158,90,144,238,228,22,54,156,32,243,204,63,6,34,91,248,219,52,54,48,
239,138,104,225,80,4,41,18,5,55,164,85,160,6,8,138,132,34,74,129,35,193,80,81,149,162,150,142,200,239,12,123,193,99,67,132,92,13,7,72,73,156,34,209,21,214,22,234,162,42,34,250,48,150,20,21,230,164,97,
4,227,131,41,134,207,68,113,130,195,114,246,71,107,158,88,20,71,240,230,215,86,38,22,211,105,192,220,129,171,19,99,77,67,67,72,119,30,225,204,196,28,65,118,233,171,97,36,31,57,158,88,41,105,117,106,96,
186,234,196,226,48,177,250,188,137,57,63,177,183,155,99,254,149,109,212,235,212,40,184,156,103,125,162,103,19,55,203,234,52,82,176,172,163,8,206,32,21,33,23,133,182,13,140,10,207,86,53,185,46,217,49,99,
202,214,94,127,56,155,205,184,13,233,12,95,187,159,79,36,29,222,148,40,57,51,31,196,120,43,223,142,135,19,123,55,159,233,57,72,247,245,33,106,251,28,143,78,224,107,51,210,29,182,147,209,241,51,46,45,33,
132,151,130,193,36,65,156,132,246,237,246,173,86,246,228,241,211,56,142,238,220,221,253,183,127,249,127,141,70,71,140,24,28,29,31,118,186,189,36,73,217,53,152,76,38,176,97,173,13,250,48,254,149,144,238,
171,184,109,42,168,241,166,86,219,37,235,219,42,160,92,206,174,243,0,229,238,12,160,220,157,7,40,103,56,248,181,1,229,255,232,144,238,159,15,155,215,128,116,15,54,94,176,254,98,158,117,165,114,85,120,
205,51,21,26,42,180,40,112,16,185,130,112,92,104,223,48,43,25,47,106,135,22,95,99,101,62,162,122,47,234,140,148,234,13,54,162,89,43,115,54,239,236,51,13,0,166,32,156,51,232,247,97,167,199,20,125,35,156,
21,139,217,100,177,88,224,86,133,12,53,182,221,198,46,66,150,129,42,203,2,9,167,162,120,111,239,32,66,25,39,251,157,239,124,231,163,143,63,66,93,229,78,7,198,128,159,121,182,255,196,5,154,234,186,153,
207,231,253,126,95,171,21,69,70,2,10,88,175,118,29,122,104,61,97,201,18,22,143,14,2,146,235,105,158,152,146,216,136,113,6,66,21,160,151,52,217,65,162,120,117,4,103,153,65,141,113,243,66,97,193,195,158,
26,193,43,77,56,187,196,97,136,177,19,230,82,30,246,236,8,126,98,106,117,98,94,139,64,185,231,38,230,94,118,98,238,250,19,11,138,176,124,195,205,10,27,218,115,92,218,226,92,255,220,230,92,27,36,149,103,
122,90,169,127,172,44,48,223,36,205,105,227,32,4,236,41,15,45,131,181,124,33,248,172,13,63,182,198,137,86,52,252,8,115,212,72,175,157,94,146,109,94,108,163,189,92,207,187,246,44,226,101,255,10,70,121,
117,183,211,130,59,56,157,206,34,225,6,115,16,86,76,198,99,38,108,131,251,210,239,245,71,39,163,197,98,158,160,232,12,29,221,181,131,232,207,137,142,165,99,10,83,136,77,96,131,83,228,221,230,121,142,176,
201,86,155,15,165,241,120,186,179,211,142,19,236,145,102,218,41,36,244,17,218,92,129,11,49,99,28,181,225,27,38,8,55,70,251,150,105,149,23,11,220,122,99,244,53,12,137,211,137,128,90,131,81,88,132,61,239,
8,218,34,166,4,146,137,175,170,198,88,146,45,16,178,7,248,188,196,102,175,50,33,90,8,226,57,162,46,220,186,41,170,42,38,142,34,76,147,105,98,242,203,23,224,123,130,71,25,163,128,24,238,227,89,214,66,44,
104,85,210,102,45,204,115,154,238,24,236,233,133,45,249,195,213,137,225,102,223,212,56,49,37,19,35,101,167,242,69,19,147,17,104,98,72,174,16,27,228,180,243,95,13,97,34,16,20,162,112,147,18,98,60,138,25,
139,231,39,214,84,205,217,137,105,243,54,115,204,191,186,13,196,2,40,72,117,211,215,162,255,52,16,16,164,49,242,97,86,20,227,43,47,64,27,100,172,169,117,164,49,94,195,145,248,72,106,2,99,75,167,53,35,
16,145,121,66,144,61,216,67,198,188,99,194,158,232,65,207,16,215,199,212,128,197,125,187,242,63,189,180,97,6,139,51,54,210,113,247,121,126,166,200,143,92,227,125,166,247,2,239,115,44,106,218,34,239,97,
48,202,51,38,47,75,174,202,161,91,187,152,19,83,7,58,183,89,43,59,57,25,193,157,77,211,150,16,226,43,45,176,198,56,242,213,45,25,138,181,103,50,228,75,130,136,242,112,247,206,3,75,12,87,57,209,129,166,
105,76,44,123,130,196,139,232,61,212,158,202,146,177,163,190,193,81,83,87,178,163,189,9,118,171,249,147,71,159,110,108,108,102,195,140,29,180,217,108,122,184,191,247,224,189,15,40,68,229,198,84,140,225,
113,87,54,132,220,139,99,58,208,188,184,11,161,235,165,199,141,245,227,52,163,97,137,47,197,53,30,101,16,149,101,249,248,209,79,97,62,155,91,59,79,30,253,108,103,231,14,120,136,71,7,207,238,61,120,216,
106,119,96,7,99,68,46,1,202,69,208,147,174,101,157,111,196,224,97,35,230,198,86,167,38,166,184,79,234,188,137,185,229,196,212,153,137,89,154,24,143,64,153,184,216,107,193,211,135,244,30,156,59,49,216,
0,189,78,151,76,204,190,229,28,243,175,108,19,173,20,121,95,98,28,214,239,18,225,137,32,107,44,135,50,154,177,136,25,227,19,249,176,105,168,221,59,80,134,49,23,8,231,133,153,155,80,64,188,94,183,152,145,
44,104,67,202,208,92,189,183,84,230,181,170,22,255,139,241,119,36,204,67,72,99,252,81,43,204,203,238,60,27,179,210,148,23,100,144,94,251,179,160,86,247,215,242,76,185,112,193,247,249,44,167,59,181,26,
18,167,57,37,176,192,40,207,23,13,17,99,196,113,114,50,26,171,211,114,137,158,105,159,217,69,124,162,60,162,118,63,234,191,171,202,90,101,240,123,201,80,62,71,220,38,152,243,143,147,192,157,196,250,20,
82,236,103,89,2,124,244,220,253,35,93,41,145,137,17,204,109,145,138,132,211,252,198,75,55,194,127,100,173,118,67,210,73,226,149,128,239,0,71,43,242,237,10,253,174,38,159,130,238,142,212,104,248,209,194,
130,19,106,1,37,45,217,236,209,96,71,30,184,150,147,19,56,175,118,238,220,235,245,122,249,98,1,142,85,89,141,29,65,218,14,158,61,173,202,234,206,253,251,76,200,35,82,246,124,204,250,137,49,107,10,183,
76,202,121,64,28,126,234,5,19,35,8,202,217,137,105,153,24,220,210,186,166,213,233,164,170,64,35,200,176,4,235,165,237,209,49,35,135,93,153,24,143,16,40,59,2,219,231,219,201,49,255,234,54,220,222,250,210,
227,56,127,150,43,65,252,17,151,17,35,111,73,197,154,8,184,157,212,119,3,5,152,246,85,108,29,51,48,218,227,130,148,63,206,89,198,145,43,191,198,219,184,11,109,28,55,105,73,106,194,239,62,34,197,122,174,
141,214,203,162,57,19,11,216,55,249,44,184,89,255,101,198,137,89,87,65,123,114,2,248,228,12,167,187,65,84,129,176,65,97,202,9,181,139,42,206,170,160,235,203,128,32,43,76,6,142,26,119,173,83,214,75,224,
122,30,5,21,120,5,16,97,224,224,229,111,168,19,133,69,110,145,62,138,8,231,4,246,229,164,1,165,97,60,22,102,166,57,31,198,46,27,190,91,17,19,28,179,72,30,124,67,216,77,78,70,199,176,52,122,107,3,131,180,
141,237,134,246,71,70,63,29,30,62,67,162,81,135,17,83,167,219,129,141,6,6,60,62,62,132,209,96,107,91,204,33,158,77,58,221,46,196,122,236,57,174,13,55,96,119,158,156,140,224,74,240,121,187,221,133,136,
18,246,110,48,128,219,57,159,77,90,240,171,221,33,65,105,4,124,129,241,116,50,129,123,51,30,157,244,7,131,170,42,23,243,5,124,175,86,187,157,164,217,116,50,38,106,64,155,165,45,184,28,209,143,57,214,215,
99,250,68,248,19,35,152,25,233,94,47,229,142,27,102,250,101,239,143,147,238,13,167,236,69,126,6,79,27,58,84,28,201,159,88,233,203,33,164,59,239,68,252,120,232,7,107,46,47,210,0,53,86,54,136,60,203,202,
177,228,60,197,152,125,103,249,191,209,251,137,174,53,78,205,207,138,41,122,137,233,148,198,73,72,0,72,147,13,30,12,164,168,110,61,254,25,15,109,42,19,249,182,80,60,15,36,35,238,109,156,19,202,73,62,105,
53,181,178,75,3,220,25,27,129,95,157,34,224,173,121,253,136,12,149,112,69,123,27,58,32,235,165,141,99,194,15,237,241,140,72,188,138,185,212,138,41,0,94,229,62,135,251,195,54,164,104,102,113,235,65,89,
44,190,63,156,51,173,236,242,30,158,99,115,102,28,190,22,217,216,112,45,216,84,106,85,59,233,162,35,197,89,216,176,206,112,186,195,15,195,235,39,121,110,163,66,67,28,124,142,12,13,180,73,113,74,152,183,
45,222,197,5,121,228,21,0,225,109,132,117,130,20,215,244,42,58,234,48,0,47,45,162,244,13,11,67,48,107,4,24,223,217,217,241,44,253,194,5,206,121,104,95,7,144,158,96,4,133,17,70,156,91,226,102,147,9,42,
214,230,121,85,21,113,146,30,31,30,130,179,195,108,10,176,2,142,15,15,48,26,205,58,117,93,78,198,199,247,31,126,112,124,116,48,58,62,130,157,11,126,135,59,186,177,185,5,129,228,179,189,167,176,221,112,
251,203,211,199,143,224,90,131,193,26,239,26,76,111,80,161,76,158,169,171,106,14,81,231,193,254,230,230,54,127,73,230,181,1,155,217,108,12,147,217,223,123,220,237,13,234,10,246,208,35,184,22,88,130,13,
92,75,13,116,70,202,224,156,80,173,9,45,69,103,126,68,47,18,227,242,107,37,100,246,194,215,160,132,59,208,177,134,59,22,122,137,229,153,123,116,180,31,193,15,75,180,1,36,161,168,217,61,20,184,127,227,
121,148,194,8,154,9,126,195,8,159,107,110,239,171,216,52,118,41,152,120,173,113,68,113,154,242,127,68,190,86,11,159,61,242,44,225,170,182,212,7,202,90,63,12,217,193,12,175,150,184,46,89,18,168,70,129,
46,154,137,146,153,173,20,109,226,148,92,1,233,120,11,135,61,219,24,171,45,166,50,208,134,38,22,43,239,166,73,170,157,50,191,231,66,153,88,107,74,250,73,12,246,123,192,187,214,8,61,164,185,145,251,172,
133,186,150,189,33,18,1,241,202,35,120,214,210,181,34,237,17,150,222,70,138,1,116,12,63,55,142,161,61,183,9,72,247,229,56,38,10,60,234,72,165,125,134,211,157,219,7,100,3,247,94,18,249,20,20,81,147,232,
172,84,28,89,215,132,219,171,233,93,18,44,37,218,16,200,40,73,56,81,226,129,169,42,176,160,242,225,67,117,171,64,64,74,39,18,147,146,106,39,5,99,175,27,204,20,57,156,146,136,105,144,254,96,109,109,125,
227,167,31,253,8,38,150,164,173,16,49,209,52,28,193,44,58,15,223,251,194,108,54,121,242,248,83,112,121,142,143,14,97,7,185,255,222,7,139,217,124,255,233,35,41,15,27,61,62,57,233,247,7,240,223,89,154,205,
23,211,241,248,100,48,28,50,13,49,28,14,235,195,141,195,195,253,205,237,29,246,245,172,148,96,76,167,211,205,243,57,108,121,16,45,238,61,121,204,49,1,60,76,88,128,179,201,24,158,0,220,238,123,15,223,199,
0,147,54,104,94,190,150,160,24,76,63,77,41,88,22,41,183,20,68,71,70,232,152,27,6,229,138,96,143,166,158,74,237,157,47,27,8,172,35,162,75,110,184,84,228,227,77,193,124,48,92,88,41,223,1,143,181,118,77,
114,56,54,156,123,148,182,183,239,54,255,55,170,192,214,245,203,141,19,121,165,88,38,81,245,58,111,174,182,149,188,26,34,76,239,73,238,61,158,93,211,200,129,36,51,164,191,35,109,78,195,166,202,96,19,32,
72,145,86,231,219,92,19,202,20,9,136,88,73,38,136,27,36,104,193,16,3,240,43,113,195,51,7,127,184,63,162,35,133,248,201,165,12,181,8,38,209,123,29,108,184,158,112,198,70,198,177,181,8,152,90,183,228,68,
160,155,70,103,185,124,128,228,224,103,144,238,224,5,180,219,109,165,36,189,193,193,160,48,81,209,254,229,150,153,117,156,37,101,196,29,151,210,137,217,42,210,94,71,205,115,167,224,174,19,163,231,23,7,
94,62,120,159,25,187,8,63,250,244,233,30,159,94,236,86,112,167,27,166,207,189,96,129,208,102,9,167,132,80,48,46,91,141,150,144,116,21,144,238,184,245,214,213,108,58,153,207,103,212,190,131,68,239,112,
16,205,167,147,124,145,179,235,1,14,218,206,206,157,233,116,2,102,229,48,239,245,6,224,109,61,121,242,25,56,83,131,181,245,51,72,119,110,138,230,0,118,165,174,74,44,172,113,82,232,5,108,159,176,29,180,
187,221,36,69,68,43,118,228,255,28,233,254,185,69,186,131,139,196,146,25,244,234,50,18,138,207,65,118,61,172,231,59,163,157,72,69,244,194,74,75,149,13,226,158,103,225,69,238,246,161,76,214,75,28,50,236,
130,92,191,70,93,255,62,51,194,177,113,154,5,144,227,40,177,207,223,31,113,44,100,95,35,216,19,60,3,187,106,195,239,184,21,125,6,181,58,142,91,162,53,150,227,88,102,175,35,55,141,206,126,119,22,233,206,
164,151,150,210,73,44,79,130,175,58,253,162,235,53,44,163,108,124,21,143,190,127,160,241,150,50,60,210,224,149,85,154,165,68,122,151,242,166,78,121,177,134,107,173,24,15,54,66,155,125,9,210,157,233,106,
88,233,55,141,19,70,186,87,150,41,250,226,64,92,95,49,251,23,66,216,5,233,206,47,252,254,254,19,24,103,184,177,177,185,177,211,233,244,246,159,60,126,242,248,81,187,221,97,169,187,170,44,15,159,61,131,
123,177,54,92,135,173,251,240,233,30,76,59,77,91,59,59,247,56,247,95,192,119,160,18,6,2,202,105,53,36,81,140,180,127,36,7,64,254,11,250,41,187,187,119,159,186,230,209,163,79,52,130,149,251,107,195,13,
225,245,209,250,231,72,247,207,29,210,157,95,155,218,213,36,119,162,165,41,141,24,28,193,11,72,147,44,141,227,138,88,4,248,224,10,184,182,211,208,33,177,73,116,128,88,189,25,27,198,208,27,106,86,35,152,
69,205,1,218,213,208,240,193,70,147,24,128,230,254,100,214,78,247,89,108,185,63,33,48,147,107,73,229,90,171,211,54,70,98,55,211,200,1,16,198,33,164,160,90,6,120,176,122,153,99,26,194,3,74,78,137,247,160,
255,151,255,245,127,91,106,93,71,105,183,219,222,218,218,252,233,39,159,138,6,31,44,238,124,126,116,116,184,88,204,22,139,156,72,154,8,144,21,142,126,143,10,17,69,25,218,99,216,69,130,104,191,172,16,21,
213,106,181,210,86,235,222,221,7,220,205,12,47,213,123,15,31,28,28,28,77,166,83,113,8,200,137,243,8,20,45,66,5,30,204,173,67,12,237,2,187,64,195,28,123,254,67,70,253,218,224,1,125,252,163,127,128,141,
233,238,253,247,25,80,174,151,162,243,126,132,243,135,181,42,248,80,92,88,16,58,17,27,212,186,121,137,51,160,252,178,17,158,155,216,4,131,205,245,149,17,150,195,158,26,225,22,39,246,28,210,125,233,38,
248,163,91,27,31,245,127,30,109,38,39,163,225,112,243,90,227,176,255,78,239,170,132,255,156,74,135,109,222,144,254,59,149,206,17,185,2,155,190,243,105,10,237,69,19,3,188,136,109,158,135,23,93,215,134,
18,172,238,85,198,97,40,147,16,182,72,130,255,26,247,208,163,234,21,139,108,147,174,2,166,204,87,239,15,167,246,217,188,198,114,63,162,55,56,137,20,230,179,180,65,166,185,83,54,171,215,226,184,143,199,
57,247,123,197,75,164,59,185,127,21,177,9,167,105,50,159,215,140,192,238,116,186,163,209,81,191,63,64,142,222,218,58,79,90,233,123,10,152,225,69,9,63,129,40,71,160,231,38,167,28,77,104,99,125,211,87,46,
97,240,20,67,54,250,219,37,210,157,246,219,200,39,185,150,153,53,214,76,38,191,201,123,129,188,211,219,4,220,77,41,218,114,210,154,104,203,3,39,32,71,239,66,157,142,100,199,141,140,224,196,139,20,25,116,
54,227,97,151,35,4,7,149,227,169,72,244,59,185,143,200,6,8,62,147,205,19,240,107,57,130,159,152,243,21,213,37,210,221,9,130,255,102,38,38,156,238,215,153,152,195,141,187,9,205,219,111,220,5,120,251,92,
18,252,149,72,149,214,199,208,86,88,255,43,162,69,102,232,16,55,99,189,110,88,25,51,59,222,192,56,116,198,39,204,193,239,168,216,254,130,251,163,18,6,183,58,15,223,87,92,5,194,113,72,4,75,122,26,229,157,
36,150,167,23,206,249,2,27,209,121,224,113,234,75,191,215,89,164,59,102,191,172,93,27,12,138,188,240,72,119,59,24,12,142,143,143,193,43,134,19,166,33,82,45,56,130,152,153,147,169,59,177,232,235,164,21,
153,97,226,105,146,20,69,17,33,45,108,12,59,20,248,59,92,33,128,223,7,253,62,236,86,227,233,84,123,129,229,203,145,238,8,7,103,220,54,135,158,103,1,229,231,32,221,239,63,120,159,245,29,94,29,233,206,121,
139,231,1,229,180,247,255,28,233,254,174,33,221,57,21,136,136,80,58,122,9,79,194,234,223,184,66,13,51,97,10,92,74,84,201,207,66,135,52,165,99,110,5,238,116,245,107,97,34,30,117,146,27,82,54,80,151,223,
67,70,240,99,238,66,114,215,138,49,131,78,16,252,68,73,162,76,120,97,165,156,13,27,253,101,115,86,246,66,27,145,124,191,202,56,103,145,238,96,2,91,201,218,96,205,68,2,120,131,151,231,228,228,100,62,159,
199,84,245,35,21,131,72,121,30,88,46,76,82,191,166,160,221,224,59,36,73,194,56,163,118,214,134,49,135,232,94,41,110,103,139,141,238,116,218,199,199,35,99,184,215,243,50,164,59,59,144,75,220,54,237,44,
231,1,202,117,0,148,243,29,205,168,110,240,234,72,247,51,35,44,1,229,212,46,248,115,164,251,59,131,116,103,148,182,232,113,50,222,138,224,87,112,83,151,48,37,142,47,78,65,135,144,206,100,9,83,130,80,7,
193,59,183,8,61,187,218,181,120,187,33,170,127,67,18,135,250,234,200,114,190,21,84,230,70,67,58,202,13,245,67,194,181,178,219,135,221,157,69,186,195,215,56,30,141,134,3,240,177,250,7,135,71,112,226,140,
142,143,38,227,177,22,142,167,255,159,189,51,91,146,228,184,206,180,187,199,146,107,173,189,163,1,82,34,1,45,23,186,192,237,16,99,51,186,145,230,78,228,211,240,169,104,180,49,61,195,12,165,171,145,204,
198,76,26,51,66,16,13,232,70,119,163,183,90,114,141,8,247,241,115,254,227,30,145,85,89,85,153,85,153,213,149,221,217,160,68,162,202,59,194,99,115,63,203,119,254,3,104,66,161,13,50,227,236,85,132,176,224,
44,162,181,145,181,148,109,244,191,234,247,251,237,110,55,65,255,100,103,119,119,246,252,95,124,119,116,4,245,216,203,73,119,132,20,208,38,217,155,15,32,221,35,14,222,0,202,43,221,192,193,87,72,186,95,
8,148,87,188,112,7,160,124,75,186,127,28,164,59,251,126,208,17,167,231,6,249,61,108,162,216,111,56,145,171,109,12,134,26,117,22,83,18,189,217,171,80,38,118,254,235,49,74,221,2,158,166,165,89,157,17,28,
254,82,250,220,53,8,126,218,237,18,180,146,211,31,28,187,59,75,186,87,206,127,231,102,48,28,250,5,235,237,219,119,63,62,255,222,123,118,64,108,185,128,74,118,104,166,196,52,155,3,12,4,177,111,143,116,
62,74,64,121,209,32,157,229,195,195,135,90,120,22,237,125,195,253,253,253,193,224,148,27,154,74,151,189,75,72,119,64,222,220,202,60,141,164,59,243,68,20,0,35,24,146,119,70,33,191,253,218,169,69,231,19,
206,151,255,29,0,168,101,128,114,111,185,164,0,76,230,3,229,60,177,18,229,65,0,202,171,18,114,159,1,40,63,55,177,45,233,190,57,164,59,65,216,170,226,157,219,32,147,232,84,196,130,232,113,20,180,179,6,
148,201,58,150,228,111,224,69,172,49,11,140,139,182,150,11,113,167,228,28,238,164,214,138,167,5,45,154,146,55,206,4,218,188,23,82,254,136,246,112,253,202,25,242,254,131,99,119,103,73,119,182,161,236,171,
159,94,63,253,236,241,139,231,223,15,71,195,162,40,96,64,242,154,107,216,38,112,160,174,132,250,161,79,136,255,201,40,78,71,235,134,49,157,118,203,63,179,71,79,62,119,82,111,72,38,211,23,159,63,245,55,
226,245,155,119,192,72,241,69,113,68,83,135,38,14,22,246,17,126,72,145,99,118,176,35,14,206,205,43,240,194,132,204,23,25,50,128,185,163,249,112,83,160,220,93,0,148,243,115,61,3,148,151,200,220,129,121,
78,97,93,98,98,58,76,108,75,186,111,8,233,78,161,64,116,249,101,77,133,58,201,107,157,52,139,39,161,209,108,58,157,176,183,153,88,105,89,34,40,19,37,103,20,149,159,128,116,143,40,19,186,97,206,224,78,
140,158,48,238,100,19,24,116,235,196,211,132,152,151,235,146,110,175,151,80,236,162,240,69,184,127,213,36,239,239,2,118,119,150,116,15,100,128,251,191,255,250,175,197,116,90,81,254,82,188,143,216,244,
207,218,40,59,174,168,207,90,127,135,127,80,193,193,99,25,172,114,111,239,94,175,191,19,170,70,105,65,250,236,209,67,191,162,253,248,252,133,10,168,139,99,152,69,52,221,165,246,170,164,151,204,40,73,184,
178,35,211,224,182,121,233,167,104,31,27,95,92,119,205,200,19,109,89,142,13,61,224,224,151,2,229,137,169,113,240,43,128,114,112,234,203,2,229,48,24,69,166,125,75,186,111,26,233,14,146,91,2,181,28,71,244,
59,167,34,58,84,226,241,208,173,148,62,105,13,212,11,207,23,134,213,57,212,75,95,128,59,37,77,210,125,77,120,26,17,243,244,141,128,44,79,99,20,239,162,107,135,14,32,100,53,245,28,225,211,15,137,221,205,
215,116,63,57,62,122,127,124,36,13,132,181,169,173,226,90,58,157,59,125,85,85,187,213,70,251,101,242,199,188,145,153,229,189,157,189,110,119,7,70,91,240,246,245,189,123,135,221,110,231,245,235,183,147,
233,68,169,216,37,103,171,233,190,37,221,239,28,233,174,106,210,157,90,136,43,101,34,201,29,72,119,197,10,198,66,186,19,214,216,164,207,37,111,120,183,68,59,189,247,79,193,14,38,203,67,23,244,115,90,245,
53,197,78,44,14,139,181,134,230,152,119,70,140,116,142,166,187,191,128,183,111,95,143,70,35,13,239,75,163,234,133,105,49,45,53,62,24,214,202,243,131,123,135,253,222,46,3,214,38,54,73,229,168,141,194,7,
230,157,145,135,15,30,244,186,221,55,111,223,250,69,80,236,236,32,189,184,213,116,223,146,238,119,77,211,29,230,191,128,221,150,59,73,129,192,230,223,114,239,9,27,183,112,225,17,93,208,126,225,175,234,
174,161,103,89,42,115,166,32,12,11,255,161,137,231,28,202,191,65,177,35,62,116,215,112,185,57,154,238,71,239,222,80,160,157,187,108,18,219,74,85,233,156,122,55,53,47,206,54,179,105,119,58,59,59,7,28,106,
161,132,12,214,34,226,202,140,216,207,254,223,30,61,124,208,106,183,127,124,241,226,228,244,20,104,108,0,34,212,86,211,125,171,233,126,7,53,221,161,137,4,150,26,85,205,80,46,129,89,202,30,37,101,162,207,
144,220,138,243,39,119,10,79,227,222,186,145,44,55,252,22,217,72,177,155,134,238,187,164,188,56,134,5,138,253,206,98,119,103,73,119,255,170,31,29,189,211,97,75,193,162,80,11,139,217,160,33,195,14,206,
227,39,79,165,148,36,164,73,144,73,164,110,60,198,236,236,236,236,238,246,253,41,159,61,123,54,158,76,35,233,14,170,21,224,217,154,72,119,23,27,45,110,73,247,45,233,126,157,49,4,18,178,119,24,116,15,88,
108,0,169,16,36,52,176,108,241,178,167,239,18,158,86,171,190,51,44,37,118,19,22,226,44,165,248,67,227,218,97,60,74,64,218,73,98,58,9,61,53,150,186,46,125,59,215,126,150,116,247,155,55,182,162,78,187,237,
127,237,77,173,138,17,132,90,108,47,52,133,188,255,224,17,53,166,39,201,49,232,186,208,250,237,215,244,78,167,189,211,239,123,31,208,159,198,91,85,175,94,191,246,207,62,32,233,18,45,226,254,96,118,125,
164,251,10,53,221,183,164,251,167,169,233,78,226,72,78,116,196,133,247,142,26,234,96,178,43,208,240,234,38,162,166,43,25,163,36,94,108,177,6,161,16,18,235,48,48,239,96,190,211,18,144,135,235,138,215,174,
168,87,98,34,222,145,152,90,38,234,116,46,51,31,117,11,215,126,150,116,247,3,126,249,203,175,254,227,219,63,14,135,195,188,149,251,165,199,255,143,202,138,219,136,62,68,254,115,110,229,249,215,95,127,
77,58,65,86,21,69,73,253,33,57,93,135,166,29,254,208,239,142,142,78,78,78,196,108,70,19,106,21,35,96,232,31,18,250,73,43,176,242,161,111,82,224,182,131,62,178,206,243,12,27,133,86,232,65,89,1,79,173,187,
41,157,35,221,25,240,55,13,78,61,19,37,64,6,202,201,238,224,176,180,16,237,74,71,210,29,224,184,138,43,56,121,190,116,95,252,99,70,109,232,150,116,255,68,52,221,209,114,229,140,166,59,24,148,168,197,78,
69,254,212,117,80,69,33,205,219,68,207,128,77,69,77,119,99,129,80,165,254,197,23,221,119,199,154,8,21,147,55,12,187,224,186,154,215,206,29,21,253,153,74,23,143,195,222,241,34,20,123,150,100,88,61,226,
124,62,12,233,238,191,143,159,253,252,207,127,250,233,37,245,155,168,170,110,175,231,127,231,87,31,39,153,17,90,68,126,241,203,191,120,251,246,29,99,71,164,44,74,171,72,57,170,136,74,160,12,254,96,52,
84,161,135,21,132,171,68,14,39,180,186,66,7,234,168,228,135,31,74,199,17,190,101,224,182,101,151,144,77,192,96,213,171,36,12,164,163,90,52,142,208,196,193,163,71,233,141,21,224,51,236,49,73,9,104,236,
40,34,40,166,116,84,194,170,23,255,152,70,61,172,142,170,99,128,158,182,164,251,39,162,233,30,199,192,251,134,195,94,107,186,179,25,46,145,122,126,154,183,142,158,157,215,116,175,231,172,24,218,16,77,
119,8,16,55,116,214,99,254,89,122,100,200,113,150,194,220,36,11,215,188,118,188,252,245,24,132,240,137,182,92,27,233,78,159,86,222,122,244,228,169,255,239,163,247,239,6,131,65,183,211,57,60,60,244,223,
201,116,58,245,254,93,171,221,241,79,233,228,116,128,0,86,244,126,241,173,90,14,0,139,207,239,45,20,198,137,84,232,1,137,192,51,244,37,160,144,21,239,187,229,88,59,171,92,23,81,211,157,251,183,73,238,
146,119,54,147,38,154,225,26,13,160,156,243,211,156,4,161,123,35,34,168,136,208,203,195,128,42,144,73,104,249,8,58,51,36,48,15,87,203,177,46,98,66,19,227,205,199,178,3,69,133,162,108,75,115,129,62,101,
220,82,174,70,170,8,96,162,40,230,150,116,255,56,73,247,69,76,9,214,44,175,130,70,59,116,214,157,180,212,154,17,44,21,157,117,29,112,39,29,18,223,55,68,207,100,195,101,122,145,54,42,160,145,252,38,115,
161,136,227,2,163,25,29,122,50,199,44,228,137,69,103,61,106,213,179,238,166,129,126,60,189,219,182,188,74,136,149,175,139,165,26,56,219,56,163,49,207,10,92,9,178,177,210,188,39,68,145,86,130,221,37,255,
229,87,255,53,198,185,129,93,132,54,106,186,219,235,123,243,106,60,30,249,117,106,50,30,167,89,214,239,239,248,167,248,248,241,83,164,14,37,239,171,208,131,75,155,96,55,145,59,198,55,11,185,115,73,40,
59,81,231,18,123,37,44,40,226,141,234,16,228,227,164,91,108,105,17,142,0,221,45,13,197,27,252,48,130,87,20,91,67,37,5,219,189,177,133,100,16,235,145,115,73,175,74,45,150,156,56,71,193,255,19,211,206,204,
172,119,98,28,5,10,31,174,99,116,159,201,41,112,85,216,168,226,17,76,56,187,226,53,77,126,56,153,140,211,60,23,217,47,101,130,245,45,71,136,247,60,252,208,133,238,76,245,17,162,142,126,192,226,17,124,
209,208,108,196,17,26,19,147,112,107,125,4,73,77,186,120,132,136,53,91,241,190,209,8,38,72,185,170,208,215,120,99,199,140,71,163,118,167,115,243,227,56,233,200,44,99,248,173,146,157,95,133,144,22,150,
3,236,190,32,227,24,21,76,16,66,66,140,201,193,146,23,60,34,227,157,172,138,58,148,24,83,155,63,23,143,65,103,22,156,157,108,105,103,197,155,9,175,187,10,115,70,148,38,204,89,129,8,141,125,13,101,169,
229,15,129,119,56,238,184,113,213,124,112,93,34,217,25,176,129,122,12,11,109,98,206,120,241,24,57,92,232,186,22,25,51,159,116,143,154,238,253,94,63,255,252,231,211,201,232,229,203,23,195,193,112,58,153,
62,122,242,25,239,255,21,116,87,19,128,75,4,156,58,110,49,226,216,5,147,32,21,36,0,37,140,162,84,88,63,40,52,3,236,154,219,213,154,208,140,8,234,178,178,30,129,252,70,209,19,22,23,35,61,191,117,92,102,
68,190,16,10,168,218,194,66,137,63,143,158,157,138,34,94,225,93,164,45,178,40,243,156,68,162,169,126,91,128,242,186,165,114,136,175,133,168,154,132,192,116,18,214,187,45,233,254,113,107,186,47,50,134,
77,9,209,125,103,117,19,249,144,252,23,139,207,39,104,186,155,38,238,196,10,241,43,64,207,154,122,237,136,42,240,203,6,19,73,40,118,196,223,231,106,213,243,198,175,103,230,188,216,124,32,124,16,162,207,
66,228,64,136,28,99,224,62,223,42,233,222,212,116,167,142,199,105,250,151,127,117,168,41,177,66,198,140,229,152,17,57,20,180,186,41,100,130,33,219,76,233,42,43,230,49,202,250,24,248,54,177,99,5,104,6,
184,132,64,38,216,126,130,69,33,216,11,10,173,197,152,148,136,50,243,202,98,80,27,126,36,236,211,241,67,67,45,81,0,202,97,227,8,56,30,45,41,172,5,81,18,254,244,228,248,199,231,207,44,43,225,60,121,242,
89,167,211,167,239,58,172,85,72,134,114,224,41,145,102,25,26,246,163,139,232,249,150,116,255,136,53,221,23,46,208,43,131,146,129,132,128,129,122,241,169,161,251,46,97,71,46,54,75,88,96,171,66,253,237,
170,208,51,216,13,254,191,81,48,40,92,194,21,90,245,144,142,81,181,86,253,50,152,155,226,205,24,86,4,31,199,4,117,117,153,15,39,247,111,151,116,55,156,245,131,166,59,94,119,246,237,57,67,101,131,173,204,
62,6,21,175,147,100,59,91,31,220,245,208,255,28,93,115,33,5,29,242,129,212,127,173,98,169,86,250,135,35,65,138,251,65,242,231,74,182,0,53,77,132,249,20,112,240,208,61,215,112,238,44,131,229,66,232,54,
41,76,39,92,218,74,175,137,183,64,67,222,38,9,162,125,21,130,98,28,35,87,128,0,168,97,23,194,243,206,158,28,31,221,191,119,127,68,127,134,63,252,240,189,255,188,31,61,254,172,215,235,195,179,84,18,140,
165,22,41,28,107,75,240,50,250,191,203,172,188,218,146,238,31,49,233,190,120,129,30,45,67,10,37,214,78,154,174,240,218,196,193,74,150,121,208,196,27,162,167,1,101,164,66,135,133,107,35,99,194,75,69,157,
107,214,80,199,191,98,181,186,200,180,153,167,85,175,108,112,174,22,159,15,116,214,93,232,76,26,169,194,154,170,207,146,105,177,244,117,105,233,62,123,45,210,29,73,61,14,9,251,167,82,168,208,235,134,19,
243,146,80,96,159,206,6,81,61,225,32,173,118,103,72,119,242,98,180,248,165,210,101,82,220,63,235,2,140,138,231,204,101,90,37,230,30,112,112,35,130,16,54,54,188,117,141,61,51,54,46,148,143,127,134,116,
175,229,219,85,140,249,9,90,161,213,243,103,63,140,71,195,241,120,236,205,171,157,157,157,201,100,50,28,141,158,255,240,253,254,193,193,253,135,143,35,117,138,21,208,6,233,116,78,117,56,206,39,152,45,
233,254,17,147,238,139,143,113,222,140,66,240,129,95,9,202,126,107,209,53,207,252,167,196,57,74,191,91,218,98,234,226,242,121,67,244,76,235,0,35,38,72,109,121,103,133,124,79,21,26,187,158,155,179,160,
85,156,107,46,233,203,177,51,122,237,82,126,119,245,124,68,103,157,190,8,34,24,120,197,176,58,134,241,194,156,253,124,150,189,174,40,29,122,77,210,61,84,183,72,208,54,165,24,138,68,155,3,238,238,196,101,
139,77,34,206,145,238,145,70,53,209,121,228,191,88,149,22,97,105,50,38,73,70,166,114,82,251,172,106,117,103,94,125,194,84,16,20,75,176,24,25,233,92,166,65,96,196,114,236,8,115,39,188,78,21,217,148,194,
106,254,147,228,255,112,245,84,170,253,76,43,85,141,171,193,233,41,44,187,98,58,61,177,182,223,239,249,63,195,193,240,237,155,55,222,200,127,240,224,81,146,101,42,52,175,22,141,22,233,163,41,50,175,91,
210,125,59,6,99,160,143,30,220,118,85,105,217,93,145,212,110,229,185,229,172,10,62,175,21,162,103,28,135,146,68,18,50,152,121,150,53,231,28,98,83,66,231,227,133,17,58,95,133,6,121,203,159,171,214,116,
7,230,47,77,131,232,197,43,197,244,81,75,93,23,47,85,104,25,168,174,67,186,3,137,140,197,143,21,185,69,21,50,101,46,54,53,178,182,40,29,231,63,88,39,39,146,238,126,1,215,54,36,146,37,226,68,200,143,21,
87,197,80,247,30,110,4,93,81,43,104,35,212,181,52,251,194,246,149,128,50,23,188,148,252,29,222,21,172,168,41,24,139,124,106,197,106,71,76,39,165,80,110,160,144,153,43,7,217,73,217,43,25,146,231,244,170,
63,80,73,47,81,145,141,117,135,22,154,55,255,254,83,12,66,129,99,26,143,198,254,82,188,169,53,28,14,223,188,121,125,122,122,242,139,95,124,169,200,181,172,52,218,16,64,226,70,59,74,111,211,157,219,146,
238,31,63,233,190,136,185,1,237,243,162,40,131,238,185,96,213,254,141,134,58,27,37,91,40,238,173,87,142,158,65,251,220,111,108,82,28,196,132,96,126,9,157,111,84,3,94,143,90,245,106,17,66,157,178,58,28,
107,231,21,138,41,127,11,16,39,2,125,51,164,187,90,230,186,92,16,62,133,183,116,53,233,174,93,25,137,113,147,100,160,75,66,30,151,99,117,182,150,78,23,216,223,47,73,80,191,50,8,182,40,0,229,1,81,115,241,
8,8,244,162,129,98,188,133,20,127,82,117,143,91,236,62,9,187,226,179,164,187,98,241,57,142,52,91,41,46,21,235,15,107,178,228,11,40,16,86,37,229,184,59,26,183,198,254,153,100,147,188,53,104,167,85,106,
108,34,89,85,72,14,25,245,246,237,235,114,76,202,106,42,72,223,34,29,232,239,251,96,48,200,178,180,223,235,79,166,227,239,190,251,246,171,191,248,235,64,92,226,212,9,226,214,90,155,45,233,254,41,144,238,
11,141,177,37,135,168,160,51,67,130,148,100,227,240,166,75,207,8,143,86,185,219,32,221,35,157,47,194,1,140,95,1,100,84,101,164,225,165,8,55,201,37,20,189,216,185,28,65,127,17,0,144,228,59,247,161,72,248,
92,10,242,15,215,184,46,132,134,253,24,6,187,22,35,221,85,227,143,35,10,227,156,116,58,63,16,55,79,58,221,52,169,235,6,183,205,176,165,8,45,222,2,233,62,49,227,225,206,169,63,67,231,180,211,158,118,141,
53,13,210,189,140,164,123,57,45,95,191,124,233,45,29,116,133,4,122,65,174,30,111,61,254,102,248,181,140,162,81,212,161,21,34,144,110,75,186,127,202,164,251,101,237,106,56,191,68,81,45,232,240,114,130,
215,223,112,194,116,56,199,226,191,58,148,130,157,33,185,185,204,43,21,141,245,21,145,238,145,188,15,90,236,46,54,208,107,210,240,170,33,196,186,212,185,88,125,48,137,185,102,127,237,74,174,93,154,200,
35,43,125,13,138,157,23,90,67,205,19,150,32,221,27,127,72,254,181,154,208,107,61,43,157,14,65,4,110,106,230,191,251,162,10,203,138,255,61,51,211,254,203,44,130,244,93,202,172,71,205,109,175,155,116,159,
180,199,163,157,129,41,146,206,219,174,161,136,144,188,62,231,73,247,239,159,125,103,27,90,242,193,150,20,220,156,175,21,249,14,179,187,187,143,62,210,91,210,125,75,186,95,64,186,151,77,210,189,228,255,
141,205,181,149,101,83,206,134,207,193,184,36,147,35,117,45,43,211,107,231,76,165,181,66,186,115,209,7,216,78,165,154,248,149,68,151,150,59,151,48,167,76,138,90,255,153,251,23,79,177,21,41,89,102,235,
132,167,191,37,221,247,153,5,11,89,255,171,164,211,211,56,184,161,80,158,34,200,127,70,161,28,19,128,93,16,214,75,44,40,82,208,131,5,133,77,29,23,105,215,32,157,174,241,189,129,79,210,33,222,44,117,203,
204,233,142,59,131,113,111,156,78,242,254,241,78,44,167,70,187,38,201,57,240,169,252,95,31,156,30,15,71,67,4,206,34,194,106,35,168,5,215,149,207,222,238,116,14,14,239,133,251,32,42,14,44,1,86,74,44,147,
45,196,173,166,251,199,167,233,62,119,140,102,156,48,146,238,180,151,84,156,255,209,162,251,142,180,53,234,13,50,191,155,18,106,151,204,197,184,28,111,114,232,233,176,42,28,44,77,178,138,150,33,27,244,
218,69,139,157,219,179,43,14,7,171,107,159,43,208,249,58,209,40,235,73,37,247,101,68,247,29,215,14,231,9,199,105,101,249,180,88,179,166,123,211,37,4,169,0,233,116,11,46,193,6,79,71,164,211,107,234,250,
60,183,141,248,28,249,74,129,186,94,31,233,62,105,141,71,221,113,123,220,233,15,118,40,84,17,72,119,255,23,166,147,209,224,228,196,47,79,72,220,210,210,54,30,83,55,13,6,2,140,110,240,235,176,75,65,99,
80,68,219,236,237,237,111,73,247,45,233,206,49,71,13,251,26,102,148,172,53,136,87,201,79,36,92,32,187,26,231,131,96,207,158,193,184,88,251,59,113,11,232,163,199,42,235,69,197,81,109,129,55,135,157,149,
164,161,197,174,175,141,158,161,236,70,244,236,89,124,69,150,254,134,25,37,148,191,170,206,232,190,131,7,92,163,166,123,115,193,98,159,197,70,233,116,108,50,161,87,96,173,113,62,79,58,93,0,235,76,184,
109,161,174,215,71,186,23,102,58,222,29,230,147,172,119,218,227,103,35,41,231,225,224,244,221,155,215,105,150,65,82,84,73,143,16,93,112,186,167,33,107,171,98,229,87,236,168,152,167,105,175,215,239,239,
238,171,176,144,109,73,247,79,147,116,15,20,59,189,207,18,175,16,53,60,103,99,191,6,166,189,81,170,34,50,9,14,188,220,89,138,61,124,255,174,22,53,189,64,247,221,225,73,93,58,102,6,7,67,88,159,139,202,
40,37,101,137,251,201,252,139,122,3,45,118,166,243,217,41,166,155,129,84,24,98,180,188,5,202,253,201,120,29,209,220,195,209,53,73,247,181,107,186,207,90,88,202,91,116,126,141,116,203,73,167,115,135,239,
179,210,233,42,26,74,43,39,221,253,212,70,247,7,166,52,253,227,93,68,213,96,53,253,244,234,71,92,242,120,52,146,30,39,252,167,98,206,13,137,2,122,237,68,248,199,176,224,17,173,143,148,198,206,243,44,207,
243,191,234,152,35,163,165,125,246,150,116,255,84,53,221,171,66,114,97,224,105,66,25,52,7,169,12,144,105,193,125,117,141,104,169,240,146,52,49,46,229,212,25,140,235,34,221,119,201,240,95,58,230,44,14,
198,187,172,80,245,104,155,130,61,248,218,88,153,18,240,189,62,6,95,123,194,29,42,226,61,140,52,131,144,247,234,22,53,221,155,11,86,98,160,50,193,61,129,22,149,78,79,164,213,123,148,78,183,182,201,109,
175,131,116,63,233,29,249,3,239,189,63,136,164,187,159,207,171,151,207,6,167,167,21,116,8,136,80,37,65,49,252,125,19,186,227,208,255,230,58,9,158,128,99,221,15,122,234,221,14,253,243,224,179,207,142,245,
251,147,238,81,255,100,103,75,186,127,154,164,59,40,75,96,74,58,180,203,68,230,158,77,15,34,203,137,98,119,246,188,166,187,191,165,121,50,75,141,79,167,110,49,221,119,222,224,197,137,3,234,69,169,198,
5,197,81,153,170,39,28,236,250,8,27,213,216,49,86,38,215,37,178,31,200,221,243,55,58,87,243,62,168,64,168,219,212,116,63,251,103,174,116,58,96,214,121,210,233,168,157,108,112,219,66,93,35,104,185,122,
210,221,187,205,69,107,154,15,218,192,23,176,51,189,126,245,227,104,52,162,48,15,177,175,41,1,131,13,151,144,113,95,153,47,124,57,222,53,84,160,87,202,131,157,254,225,189,71,186,50,217,176,85,244,198,
246,84,250,122,111,73,247,79,147,98,231,132,184,21,252,82,108,159,90,245,163,178,213,130,24,151,105,140,225,189,132,51,120,231,80,47,21,122,169,91,134,227,156,230,32,4,15,91,72,28,117,225,249,204,165,
216,65,168,71,245,174,148,145,67,89,207,21,36,117,230,223,31,37,164,59,220,22,219,156,143,13,236,209,90,52,221,227,159,105,49,165,244,189,154,35,157,158,156,147,78,79,105,179,184,80,58,221,160,235,23,
55,209,90,45,233,62,233,142,253,5,180,198,173,72,186,15,6,199,195,225,208,255,221,193,96,144,166,41,60,110,152,115,72,150,1,158,0,161,30,44,127,52,48,34,195,100,127,255,224,240,222,3,239,136,249,217,182,
40,136,63,26,181,135,237,65,103,75,186,127,82,164,59,10,226,76,236,150,202,111,230,12,201,173,21,243,13,78,178,62,202,94,33,88,202,113,168,224,231,169,171,80,47,38,4,120,121,96,239,210,27,10,44,2,177,
102,132,109,134,152,103,7,199,91,226,168,188,65,236,34,72,66,171,51,5,140,24,83,178,40,38,112,165,250,92,65,104,110,45,154,238,51,46,33,219,186,66,93,71,110,187,65,186,159,145,78,111,114,219,44,157,94,
115,219,40,248,91,7,233,62,233,140,178,73,158,186,212,129,55,80,246,248,248,157,63,209,100,50,166,246,19,89,54,30,141,137,252,140,82,23,204,146,136,177,6,78,221,31,214,81,84,201,91,236,253,253,253,189,
189,61,147,64,158,81,101,46,109,121,251,173,51,238,141,122,53,126,183,37,221,63,118,210,61,250,131,78,114,200,148,236,75,77,214,212,107,159,213,44,55,8,195,95,137,113,121,91,253,106,212,75,217,76,103,
133,18,29,171,146,183,126,188,188,235,192,211,154,88,153,179,16,218,45,35,49,143,236,51,194,202,151,155,117,137,78,106,170,62,156,11,48,243,26,53,221,55,139,116,47,179,194,91,40,189,81,43,146,238,195,
161,183,171,134,147,201,196,191,79,254,83,199,62,197,74,237,165,178,208,156,208,81,179,212,114,156,181,98,2,203,191,138,121,158,183,91,237,163,247,239,59,157,126,229,68,211,61,31,183,202,214,180,204,203,
100,154,110,73,247,79,135,116,71,139,19,110,149,148,34,71,205,16,28,135,112,140,201,141,223,203,82,112,55,82,28,70,79,217,92,130,113,9,18,165,220,34,168,87,33,109,61,197,110,160,168,172,52,48,94,7,158,
38,90,236,118,14,197,158,66,86,21,241,190,75,91,245,72,92,24,189,194,110,13,187,219,48,210,221,37,92,210,60,245,155,81,5,160,252,237,251,215,33,163,143,212,30,108,186,202,160,197,78,128,2,140,84,18,232,
168,51,67,102,95,81,29,31,31,181,59,221,201,120,212,242,107,22,107,186,155,146,123,55,233,50,51,249,150,116,255,212,72,119,108,180,188,137,214,90,236,254,133,18,61,98,218,104,225,49,45,133,140,169,203,
199,112,127,123,77,154,45,236,149,25,136,181,172,148,134,111,106,204,83,68,152,59,63,139,210,49,62,204,170,96,254,175,68,35,251,171,10,24,221,37,122,246,155,68,186,191,248,241,7,111,182,236,237,31,174,
137,116,175,168,104,211,165,126,15,100,79,147,240,209,209,164,20,91,148,94,196,211,241,152,194,88,116,193,149,14,98,214,42,84,147,35,75,27,93,61,134,51,104,23,30,142,134,173,206,14,191,220,97,211,72,188,
147,185,37,221,63,9,210,157,115,33,116,123,105,75,166,175,182,226,123,171,35,162,85,177,254,19,57,10,44,218,185,114,100,204,134,6,3,113,12,125,47,73,178,114,60,45,9,189,65,81,215,33,153,53,45,154,238,
86,87,136,169,95,121,159,85,195,29,58,67,186,175,27,187,91,142,116,247,95,237,96,120,226,127,152,102,89,150,183,167,211,137,223,181,218,237,78,49,29,195,44,28,141,134,101,81,248,223,113,88,42,237,246,
123,39,199,71,21,245,10,235,143,134,131,52,205,252,179,239,244,122,228,187,93,139,116,119,73,149,0,189,148,148,133,200,25,43,228,215,216,188,162,175,49,17,215,90,116,136,192,180,7,172,130,163,206,22,203,
132,146,220,101,149,18,110,39,208,158,95,23,233,159,208,56,113,75,186,127,220,164,59,177,55,38,64,235,252,136,231,106,177,175,15,25,19,188,71,137,119,166,3,59,190,218,115,65,139,61,40,88,185,104,70,112,
16,69,45,107,34,213,84,189,224,24,183,132,221,45,71,186,63,127,241,220,191,4,126,245,241,191,40,38,227,159,94,189,104,229,173,225,233,9,73,44,182,90,157,110,151,31,182,223,145,170,147,227,247,157,118,
55,239,180,7,167,39,147,201,56,207,91,239,223,189,241,167,239,16,241,212,227,172,167,144,238,131,253,35,108,254,86,210,47,180,116,165,32,75,65,43,113,232,189,251,182,207,106,67,46,85,128,143,233,8,244,
105,250,123,151,72,163,26,78,69,211,125,71,2,49,144,237,104,139,194,202,249,42,232,148,106,193,75,162,32,131,170,27,146,208,73,88,246,111,75,186,47,184,13,170,77,39,221,185,18,80,129,98,183,28,183,69,
83,191,91,66,198,156,228,133,40,79,21,112,152,149,157,75,178,58,10,123,21,251,37,181,14,61,39,196,42,236,230,203,84,2,68,210,93,28,160,59,74,186,251,159,76,39,211,225,224,116,127,255,222,233,233,177,127,
178,7,15,30,249,215,226,197,179,63,249,97,7,251,247,143,222,189,235,180,59,189,221,93,191,60,149,140,194,27,110,171,3,124,161,221,235,30,220,123,40,54,74,36,221,41,222,100,36,208,12,224,81,59,200,194,
8,234,174,107,210,221,50,169,77,145,102,214,116,135,5,85,146,240,163,104,159,34,36,20,10,86,229,15,132,222,19,94,200,208,56,154,237,23,170,28,108,183,90,254,175,251,39,228,87,116,1,235,241,31,46,247,220,
146,238,87,233,154,139,86,28,98,34,155,75,186,7,247,90,219,168,196,114,139,56,88,35,91,46,14,193,205,206,229,194,24,169,75,203,208,184,19,84,32,239,140,13,29,250,235,220,231,25,210,221,221,97,210,189,
215,223,217,217,221,125,253,234,229,201,233,17,175,32,110,60,28,64,72,26,5,13,180,180,57,33,221,189,165,229,127,91,76,39,86,238,148,242,174,34,78,62,25,143,243,86,11,134,233,222,241,126,48,47,92,36,221,
65,252,138,41,130,61,144,91,144,81,67,177,86,213,212,116,247,159,40,106,156,253,25,201,27,205,115,178,19,203,18,146,61,117,34,146,67,251,161,217,28,247,128,100,27,173,40,168,8,131,52,176,130,156,152,31,
87,234,50,155,102,16,165,217,146,238,231,198,176,122,24,191,88,65,71,92,170,68,209,30,102,67,73,119,209,62,39,110,89,157,167,216,215,135,140,249,205,3,99,16,66,213,43,58,87,8,137,74,42,6,126,18,118,241,
160,233,110,174,119,159,111,141,116,39,242,94,221,128,116,247,175,252,209,251,119,84,15,152,166,251,7,135,169,55,29,139,233,209,187,55,222,21,172,169,116,9,105,187,131,195,251,39,71,239,95,189,124,225,
79,115,239,254,3,13,95,68,57,106,2,104,204,171,23,207,30,61,126,154,183,218,75,147,238,21,181,104,133,171,136,69,196,155,73,133,174,151,127,4,169,36,115,29,42,236,253,209,97,100,73,156,2,56,184,178,237,
118,123,58,157,250,35,80,112,141,125,97,110,203,168,121,93,212,91,210,253,108,177,27,124,136,134,19,13,226,153,156,232,144,168,229,203,178,155,70,186,59,108,180,177,135,121,173,125,142,247,150,127,83,
174,7,25,195,86,135,74,124,135,162,177,121,52,252,130,231,138,42,198,8,227,84,54,88,109,124,93,33,171,160,86,82,9,160,26,154,238,22,239,228,42,180,234,203,134,160,107,212,143,135,183,181,36,233,174,221,
231,95,252,25,98,31,32,0,30,63,126,202,164,123,26,73,247,199,79,191,32,110,219,185,221,221,189,221,221,125,33,221,217,85,249,249,159,127,41,114,207,74,61,126,250,51,198,64,236,178,164,187,98,102,203,49,
143,137,64,21,133,252,153,75,154,76,166,126,81,161,158,220,144,139,208,72,62,42,43,81,123,116,253,129,20,25,217,94,157,78,127,52,26,122,3,36,207,243,110,183,199,117,249,84,89,13,126,207,123,234,220,32,
115,75,186,207,217,186,181,224,130,148,38,79,121,39,168,117,205,163,142,184,65,19,101,106,163,226,183,74,190,174,59,175,233,174,37,130,92,178,102,121,147,116,175,22,208,62,255,128,232,153,22,117,118,126,
40,60,103,196,111,121,49,72,130,249,78,203,68,118,227,103,209,44,168,156,171,233,190,200,156,85,104,159,129,185,163,124,59,104,171,168,68,113,107,81,110,60,106,193,51,133,103,177,97,164,59,124,239,42,
45,51,155,33,0,190,187,127,111,56,26,82,156,158,72,110,227,23,205,32,128,19,91,198,163,157,183,3,200,90,22,83,111,88,237,238,238,158,14,78,9,8,108,229,180,102,181,59,32,221,41,206,149,114,55,74,151,66,
36,107,75,186,199,49,200,228,42,230,48,36,139,203,201,199,132,9,90,40,254,67,71,220,177,142,56,123,186,22,91,37,97,182,6,118,152,9,130,175,119,139,116,71,206,216,73,216,211,48,65,234,63,28,153,179,16,
225,118,138,157,239,174,161,103,204,41,40,217,135,140,44,86,104,132,76,220,12,26,32,220,184,240,112,142,158,125,24,227,141,66,66,11,23,209,161,15,214,3,69,17,44,188,129,76,177,71,227,143,67,221,27,105,
177,112,53,121,111,102,244,227,55,140,116,207,203,236,180,34,233,190,188,200,225,152,180,90,109,82,38,154,22,73,154,165,90,149,222,226,48,194,179,97,213,216,219,219,173,168,118,177,240,126,31,173,29,105,
207,159,228,248,228,216,111,53,254,14,248,133,160,183,179,35,81,25,126,93,39,237,137,127,230,121,217,178,202,110,73,247,230,86,169,194,227,147,188,167,83,65,230,169,222,30,155,58,226,179,228,52,180,198,
161,191,177,104,139,148,91,214,116,71,149,124,212,44,175,184,24,80,135,248,67,163,195,179,115,119,12,61,139,207,34,82,236,152,42,76,4,142,60,173,248,62,71,61,123,29,4,123,51,157,94,49,103,147,52,53,230,
93,156,51,173,104,210,65,80,244,197,66,194,61,190,63,34,151,232,45,155,111,190,249,38,46,88,105,218,41,170,233,153,125,41,225,20,175,127,246,148,230,100,164,211,5,44,139,56,46,34,18,89,116,33,144,238,
21,71,248,224,119,0,248,148,202,24,124,134,242,198,86,204,34,105,54,232,66,7,89,17,15,163,38,66,9,231,22,85,157,49,49,162,234,199,94,243,40,31,102,163,220,95,12,244,23,188,67,55,28,156,250,195,28,31,31,
251,97,95,125,245,213,175,126,245,171,111,255,248,31,126,17,120,244,248,193,120,60,38,75,36,203,113,69,147,241,164,226,56,154,183,56,178,60,239,116,218,222,70,99,255,136,13,66,93,141,119,7,249,168,147,
22,128,149,168,246,130,69,105,80,254,13,144,202,0,25,99,244,153,130,2,90,218,171,73,118,28,119,204,242,29,99,164,147,222,129,98,50,237,116,187,126,48,71,193,13,18,158,241,142,153,120,199,160,203,76,6,
29,176,213,196,133,195,10,233,238,170,250,176,156,18,97,188,163,64,210,115,102,98,22,37,9,73,152,152,51,225,85,192,17,120,39,82,104,235,130,54,66,188,43,88,166,240,209,6,28,145,96,174,146,231,240,109,
152,167,133,163,81,209,222,230,56,87,0,42,69,52,89,120,139,130,181,175,208,27,29,65,95,40,11,67,171,5,231,130,45,89,79,149,191,18,255,73,232,240,176,47,154,207,34,115,182,69,213,238,116,150,58,78,197,
242,199,32,221,241,68,248,21,77,160,38,138,235,66,122,1,84,27,3,213,21,190,46,65,153,248,61,201,56,39,235,247,254,91,24,99,216,166,98,176,89,230,204,57,241,84,66,239,225,186,176,255,45,123,15,47,26,3,
55,211,5,183,3,134,197,37,115,150,154,204,240,110,32,220,29,238,179,4,139,241,126,198,119,195,206,188,27,134,55,58,55,179,96,85,58,141,208,143,36,206,77,112,172,20,216,76,249,161,10,109,1,27,136,182,97,
227,173,10,1,63,177,150,162,162,144,116,140,14,189,169,85,104,18,33,226,59,72,195,201,185,116,4,219,194,17,100,175,160,5,180,76,166,189,49,197,81,184,214,143,111,2,187,211,197,100,56,152,28,28,30,254,
230,215,191,249,183,127,251,247,231,207,159,61,124,248,96,58,157,76,167,83,88,167,172,114,173,91,121,203,47,178,89,150,161,82,250,240,222,35,133,104,39,95,218,180,63,46,243,178,127,188,67,176,165,124,
96,58,44,70,54,244,147,13,106,65,225,122,85,216,46,102,238,24,133,207,234,31,78,38,227,52,207,141,14,133,4,225,254,158,191,99,26,234,93,161,39,80,243,158,227,69,9,247,28,193,5,13,53,113,28,161,49,177,
208,8,55,30,65,82,147,46,30,1,213,224,90,180,237,37,173,142,207,82,202,19,2,197,24,81,67,100,109,161,237,141,133,15,71,136,33,249,168,227,154,26,184,198,14,90,195,98,194,132,29,200,132,12,111,172,78,151,
128,129,88,4,216,189,244,69,243,89,100,206,254,255,198,163,17,47,88,106,241,227,152,58,110,33,203,47,94,84,120,0,10,248,37,47,25,216,215,113,115,80,219,16,211,208,254,139,229,122,44,218,90,76,184,63,107,
26,195,207,194,134,142,24,18,98,84,33,187,30,239,97,208,26,92,250,30,206,29,163,227,152,58,11,20,52,239,231,205,57,102,174,164,135,188,73,194,10,101,2,223,173,195,103,56,51,103,213,152,143,224,77,27,167,
233,238,189,195,124,146,79,218,222,204,106,81,155,28,254,148,31,222,127,242,252,217,15,222,92,250,205,175,255,225,213,171,87,255,252,207,255,180,191,127,0,16,129,140,41,54,88,252,185,216,137,35,132,193,
112,220,101,255,224,126,221,175,219,27,140,166,154,118,38,217,56,87,149,98,121,191,173,166,59,136,231,50,246,193,134,113,15,252,234,44,202,164,103,17,173,74,198,72,87,238,224,16,106,217,150,17,15,177,
252,23,161,71,78,137,246,202,149,24,22,50,37,234,38,69,106,55,209,116,151,49,86,52,221,129,249,157,209,116,15,213,20,31,12,61,35,82,129,161,30,184,59,120,1,138,74,84,31,24,165,89,87,69,1,155,96,82,88,
38,32,51,175,32,69,83,27,94,62,118,128,47,58,234,178,186,112,15,57,0,154,134,132,32,4,53,175,152,243,70,106,186,119,78,251,147,195,215,131,131,147,189,183,7,116,157,198,124,251,237,255,243,79,238,155,
255,246,141,255,237,63,254,227,255,236,116,59,157,78,171,44,11,110,195,139,64,32,101,105,41,245,198,146,143,89,43,167,213,10,95,81,40,147,63,222,123,231,253,184,221,211,190,50,122,171,233,14,226,25,44,
152,170,33,13,41,102,90,70,35,28,125,70,117,70,43,175,104,141,75,144,145,190,7,203,173,95,82,14,136,32,236,32,183,55,106,168,223,190,166,123,131,224,79,156,20,213,171,32,180,43,85,178,28,87,230,140,138,
254,48,232,25,154,247,56,104,145,211,187,157,151,242,188,146,219,169,40,64,154,174,254,28,234,103,202,6,17,107,222,83,182,39,104,195,59,8,195,139,204,1,45,98,89,154,149,37,5,43,22,159,243,70,106,186,251,
203,219,63,185,119,188,247,254,100,247,184,119,212,47,139,234,116,112,242,197,23,95,124,253,245,215,191,255,253,239,253,160,253,189,61,58,20,137,68,80,210,141,60,23,182,106,200,76,75,204,206,238,65,175,
191,203,110,38,45,150,254,118,20,174,28,238,159,86,186,220,61,218,79,188,95,140,74,236,173,166,187,130,174,121,133,237,44,168,208,169,60,93,2,119,74,100,204,140,214,56,115,109,116,83,74,174,164,195,42,
204,142,173,226,186,80,37,14,137,50,145,62,199,23,114,11,154,238,141,49,250,60,13,175,66,7,19,27,45,71,225,226,110,25,43,3,4,101,98,37,127,33,207,75,223,90,69,1,87,56,84,74,4,38,216,27,149,232,158,149,
248,53,223,32,100,95,27,218,240,115,42,37,170,10,25,218,171,231,179,145,154,238,20,135,155,232,206,73,119,216,31,140,250,195,193,119,39,101,81,254,253,223,253,221,191,252,203,255,249,207,63,125,247,249,
23,63,59,60,188,239,15,61,26,14,134,195,83,73,241,80,139,137,118,43,111,167,105,238,143,141,104,31,231,223,200,114,153,238,142,108,219,118,79,250,166,72,172,170,106,38,115,75,186,139,46,16,124,227,4,98,
18,126,39,95,21,54,117,86,31,157,155,114,135,116,113,194,185,233,146,149,130,108,160,234,215,171,233,190,200,24,196,99,75,209,125,151,123,8,193,210,91,17,89,21,109,84,108,192,148,137,166,53,190,250,128,
21,5,161,48,151,188,153,138,89,25,246,85,171,168,139,63,171,13,207,57,121,1,73,154,199,89,136,188,223,60,77,119,72,185,248,1,173,113,219,26,59,106,15,126,122,245,242,31,126,253,235,225,104,244,191,254,
247,31,30,63,126,244,240,193,19,248,74,222,140,234,245,119,80,162,19,177,44,230,143,28,176,21,198,132,172,55,211,170,172,104,157,118,243,81,139,211,13,38,48,241,91,210,189,4,21,173,66,154,91,34,154,171,
195,166,102,177,32,93,59,187,74,187,72,105,187,38,165,125,183,116,223,155,180,55,243,34,107,21,89,141,26,243,150,33,3,125,235,102,221,252,49,160,54,45,42,28,154,84,61,255,143,115,218,240,246,38,231,218,
60,77,119,5,91,157,45,207,246,160,51,125,55,249,229,151,95,126,246,228,201,239,126,247,187,221,189,189,195,251,79,10,50,18,141,208,94,10,10,180,126,10,22,144,174,13,165,161,126,14,42,117,227,131,161,77,
203,238,241,78,119,218,115,198,113,46,86,164,184,183,154,238,113,123,215,49,135,71,238,112,226,220,154,180,198,85,67,100,177,2,46,27,68,129,136,62,95,150,210,94,154,116,191,30,237,205,97,239,224,197,172,
11,43,131,103,82,7,136,181,11,21,131,119,76,95,31,161,114,174,112,224,251,179,226,10,135,205,211,116,87,177,7,42,58,205,190,31,253,143,223,252,253,31,254,240,79,163,114,252,228,175,159,38,35,191,146,33,
130,13,36,157,221,58,43,250,127,98,191,249,227,153,170,232,78,198,157,145,159,248,206,251,253,164,76,35,233,110,37,94,110,182,154,238,37,3,192,2,28,83,214,216,74,6,147,83,141,235,38,185,133,138,214,58,
106,141,51,49,175,215,65,186,95,219,60,12,56,27,164,208,75,78,207,78,221,154,180,216,77,174,76,21,41,118,254,62,238,144,190,62,156,60,30,195,114,211,65,69,114,181,231,218,48,210,93,115,165,184,212,121,
250,191,91,149,255,253,111,255,246,245,235,55,127,252,246,143,15,255,230,241,168,61,156,244,198,217,36,107,141,218,186,242,207,217,47,207,22,30,37,92,218,66,21,54,161,190,59,69,171,240,87,210,46,58,221,
97,143,170,90,129,50,197,194,12,158,71,12,16,127,202,164,59,208,42,29,154,160,160,134,60,128,236,183,72,114,139,194,158,17,74,198,185,117,144,238,215,24,3,231,21,177,214,72,195,139,211,190,114,1,85,87,
137,105,91,87,225,221,117,125,125,208,158,43,60,215,134,105,186,115,18,65,51,92,67,154,48,70,101,255,249,167,239,95,254,248,252,207,126,254,165,59,114,173,211,78,213,43,166,221,105,145,159,136,94,77,197,
222,163,127,209,83,191,127,149,66,210,84,170,53,104,119,38,157,196,37,176,40,189,55,69,241,53,174,232,102,7,202,79,169,130,105,251,145,104,186,51,29,166,88,201,250,188,166,123,179,141,202,197,250,232,
104,44,68,175,83,108,238,68,164,251,250,69,68,67,158,186,228,69,63,1,154,183,38,77,247,229,199,208,156,253,157,73,24,186,86,13,76,201,15,94,149,22,123,193,55,129,54,126,102,61,184,219,128,254,248,52,248,
23,25,163,127,251,219,223,198,5,203,38,93,231,36,135,141,140,36,220,64,101,177,174,35,75,99,225,37,129,150,226,221,47,145,84,175,4,203,69,232,37,56,124,181,130,7,114,155,46,182,105,227,53,78,124,159,224,
235,169,160,59,138,133,22,236,160,28,86,126,18,100,179,130,208,90,200,182,203,137,105,81,205,10,235,61,195,84,251,255,239,189,63,242,157,44,133,166,141,247,80,109,146,21,121,173,179,229,130,215,39,115,
128,43,107,161,159,165,162,178,119,168,204,114,141,43,106,94,175,138,55,39,222,49,185,62,185,99,199,71,239,251,187,123,11,220,49,23,47,109,230,176,33,127,170,235,35,212,63,140,226,58,103,142,224,66,106,
95,135,137,199,32,145,146,44,2,20,232,37,35,141,93,172,1,212,132,14,5,161,150,34,66,208,126,105,134,70,184,84,5,54,133,43,217,15,79,169,113,241,12,206,115,189,49,180,28,243,152,96,100,33,202,235,226,124,
46,154,179,255,215,227,119,239,247,14,14,46,31,179,200,113,230,142,145,215,145,85,39,165,174,64,11,26,189,186,107,39,101,55,182,175,77,12,158,96,62,112,161,214,113,93,119,124,204,230,145,238,98,20,7,126,
21,164,59,227,224,22,19,163,28,217,36,213,38,55,5,60,71,241,111,107,213,110,205,85,226,210,16,12,151,6,160,92,0,184,88,24,180,89,164,59,178,194,156,225,150,47,74,56,54,90,153,132,173,112,129,153,73,88,
59,137,77,36,110,215,88,217,122,167,186,72,251,60,232,139,205,163,189,69,143,124,229,200,79,209,208,35,71,242,187,180,53,201,189,118,210,253,10,243,39,85,104,40,167,26,123,166,115,171,162,216,9,83,10,
149,0,92,203,169,75,23,122,23,150,213,199,167,193,191,200,152,141,36,221,249,149,37,4,12,73,111,86,236,119,1,40,71,53,159,128,227,48,148,248,43,165,181,32,10,209,193,65,115,177,132,79,235,166,166,59,26,
91,108,22,233,174,235,94,27,120,253,19,190,51,184,141,168,116,177,161,134,194,33,78,108,185,139,84,32,203,25,247,80,126,135,185,144,120,6,237,45,218,231,13,218,155,162,102,122,189,218,222,42,232,145,91,
197,115,14,246,241,154,73,247,75,117,205,147,12,139,188,84,2,40,169,214,85,171,165,216,181,117,225,92,110,25,34,252,99,29,179,145,164,59,153,35,172,233,142,111,185,44,170,160,156,147,32,42,12,59,203,114,
216,155,76,21,134,0,184,167,110,133,21,45,20,84,215,164,123,40,37,198,132,239,58,233,158,48,51,204,193,121,90,136,105,159,32,75,11,89,81,4,215,25,106,36,238,13,136,44,45,217,18,221,151,66,110,39,61,56,
84,216,77,18,19,22,116,117,185,246,249,12,237,173,116,8,137,74,85,238,202,145,31,208,240,34,80,167,149,21,105,144,91,32,221,231,143,193,18,239,141,29,214,131,150,66,125,27,60,240,213,80,236,216,155,19,
217,183,144,30,165,90,203,133,137,240,143,117,204,166,146,238,81,211,93,133,143,127,102,98,8,111,241,233,68,140,63,244,79,133,153,136,254,58,145,116,79,249,122,163,166,251,198,144,238,226,194,107,5,142,
43,99,209,84,162,198,171,192,139,139,40,13,252,88,88,215,44,20,89,197,186,226,80,44,111,34,89,46,119,253,82,77,247,89,218,91,30,108,80,215,72,87,139,252,68,26,62,126,198,112,159,111,159,116,23,221,119,
1,12,137,15,140,225,149,80,67,159,174,128,98,55,40,250,12,207,130,240,113,123,115,45,246,143,99,204,6,147,238,205,112,126,132,185,19,80,96,202,9,83,46,181,225,126,25,50,113,111,100,43,91,72,247,208,91,
68,130,209,155,68,186,211,162,201,57,77,23,237,157,74,28,198,243,72,203,172,224,100,24,51,159,44,199,90,153,165,105,57,159,44,183,231,105,111,33,87,112,187,72,235,162,90,57,13,95,147,211,31,128,116,119,
129,122,114,145,188,175,117,223,181,172,240,148,165,189,25,202,20,181,216,253,131,157,165,216,179,59,175,139,127,75,99,54,155,116,103,58,41,101,113,34,131,137,49,249,157,44,72,186,67,121,38,97,228,50,
51,162,233,190,17,164,59,66,129,28,206,39,119,88,66,81,106,133,100,185,246,238,240,229,90,236,77,218,187,214,116,95,3,237,13,133,45,52,100,246,255,246,161,72,119,134,1,19,232,131,113,88,16,132,151,152,
63,65,161,92,93,79,139,93,41,41,190,107,104,177,179,19,207,203,217,10,139,55,55,125,204,198,147,238,52,139,128,131,199,137,93,73,186,43,142,151,171,48,91,206,27,110,10,233,238,7,167,18,118,98,75,19,68,
184,91,3,89,190,8,169,44,130,162,160,189,249,131,44,89,251,124,85,180,183,224,181,236,10,129,49,254,32,164,59,194,8,78,149,14,100,175,17,189,220,44,201,169,32,245,186,120,145,232,154,43,50,180,85,50,163,
197,110,133,172,190,19,20,251,221,25,179,217,164,59,220,23,28,161,137,131,71,133,76,111,172,52,72,119,98,133,101,57,139,167,98,209,97,224,220,27,65,186,43,70,28,76,192,196,252,28,50,144,95,107,32,203,
93,64,58,46,39,203,107,218,155,111,83,10,13,178,149,206,39,244,85,48,114,159,215,163,233,62,111,140,138,121,90,195,219,143,240,52,145,62,103,151,255,218,215,21,33,196,74,58,96,132,156,114,109,178,221,
93,138,253,131,140,217,60,77,119,18,135,225,216,10,127,237,52,36,145,217,138,246,174,22,81,102,45,194,202,10,186,171,9,108,120,45,13,118,93,130,38,96,108,81,70,77,119,229,66,63,2,202,168,222,33,77,119,
97,66,88,47,65,106,110,156,60,202,149,107,132,163,136,186,12,186,230,248,246,47,213,255,54,136,112,226,241,241,131,166,227,164,38,229,204,236,77,231,67,20,153,83,1,220,95,66,135,254,26,154,238,103,198,
192,204,111,92,151,1,79,3,202,127,217,235,194,122,119,94,139,29,187,20,98,30,72,179,220,92,207,254,99,29,179,110,77,119,145,70,13,236,170,4,72,56,198,132,124,34,52,221,147,152,172,114,34,157,94,31,161,
214,116,23,12,94,159,153,24,71,57,146,25,225,115,73,243,37,2,103,35,72,175,130,54,180,150,212,150,172,218,181,34,187,104,173,11,192,5,241,117,142,99,241,97,35,235,164,111,95,211,61,146,247,88,25,107,45,
188,53,232,136,179,74,173,152,177,77,141,240,75,244,191,77,67,247,29,166,86,202,93,48,174,59,31,161,198,217,255,74,81,143,22,116,214,213,90,53,221,231,94,23,152,59,185,174,4,42,55,118,217,235,146,87,77,
197,235,66,186,198,177,61,94,95,215,229,247,249,134,90,236,31,193,152,181,147,238,51,56,248,5,220,54,112,112,62,2,141,54,230,34,133,114,153,152,99,199,144,190,124,135,214,104,152,152,161,82,190,11,38,
214,0,202,19,83,31,246,10,160,188,49,177,37,164,211,87,78,186,91,200,54,178,144,149,129,112,35,237,57,235,197,94,224,4,53,200,114,117,57,133,12,232,41,174,161,133,45,216,214,189,166,0,102,116,69,97,88,
137,254,247,146,5,122,55,33,221,69,179,156,177,181,208,214,69,93,164,103,127,201,117,233,32,158,106,144,200,10,89,64,41,156,224,104,0,89,85,171,40,60,220,146,238,55,37,221,3,183,157,216,186,216,5,212,
245,12,183,93,231,203,57,228,28,21,202,35,80,46,56,120,152,24,226,223,201,44,80,126,193,196,206,3,229,234,12,80,94,215,85,92,54,177,25,233,244,219,36,221,157,138,165,255,10,112,63,116,63,215,141,189,64,
147,219,49,149,26,155,211,95,73,42,139,175,106,81,3,100,121,163,75,66,73,164,185,82,184,146,217,17,83,235,190,135,134,241,81,179,252,54,53,221,149,164,77,65,191,93,135,98,151,150,81,146,89,54,32,170,176,
247,64,215,156,210,211,203,95,215,167,60,230,108,241,179,255,218,153,116,119,224,182,19,109,34,233,94,114,59,63,224,224,32,221,153,132,40,2,35,173,209,217,73,211,14,35,164,59,194,25,200,236,21,172,112,
128,195,70,107,130,11,166,106,202,124,230,176,65,161,60,53,73,136,160,23,118,185,137,33,106,118,197,196,200,122,71,32,223,72,251,156,139,38,230,167,212,148,78,175,39,86,21,108,148,197,75,19,210,189,57,
177,211,227,163,157,189,189,115,151,86,79,204,97,37,50,26,101,46,92,216,36,19,147,21,16,232,63,167,18,217,154,99,182,93,188,21,114,242,33,52,76,229,153,200,16,112,36,238,218,99,66,109,160,144,99,40,229,
148,138,235,96,74,176,155,172,99,2,4,69,221,78,89,17,234,70,60,206,132,150,89,212,137,200,130,158,61,127,174,48,70,129,82,11,129,124,192,128,34,7,127,238,92,87,204,231,228,232,120,119,255,96,129,57,159,
61,78,68,133,69,39,19,149,95,104,243,185,240,61,20,241,31,129,166,37,153,17,239,207,82,243,217,142,137,99,254,191,0,3,0,151,107,177,162,244,118,198,38,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* JuceDemoPluginAudioProcessorEditor::uibg_png = (const char*) resource_JuceDemoPluginAudioProcessorEditor_uibg_png;
const int JuceDemoPluginAudioProcessorEditor::uibg_pngSize = 63194;

// JUCER_RESOURCE: dry_on_png, 780, "../Graphics/dry_on.png"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_dry_on_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,35,0,0,0,13,8,2,0,0,0,172,29,64,72,0,0,0,4,103,65,77,65,0,0,
175,200,55,5,138,233,0,0,0,25,116,69,88,116,83,111,102,116,119,97,114,101,0,65,100,111,98,101,32,73,109,97,103,101,82,101,97,100,121,113,201,101,60,0,0,2,158,73,68,65,84,120,218,156,84,91,79,19,65,24,
157,235,246,66,0,165,5,202,61,160,85,212,7,163,38,36,18,141,198,196,152,248,131,244,193,39,127,128,127,202,152,72,12,137,134,7,69,144,146,66,91,170,2,90,176,91,219,157,139,103,102,104,213,96,128,56,217,
157,236,204,158,239,114,190,239,204,208,39,207,158,19,66,40,161,137,78,148,82,156,115,44,5,231,140,49,131,97,77,196,83,218,234,127,98,44,6,113,47,163,148,50,6,0,150,196,98,65,240,88,191,176,240,225,49,
194,185,112,187,22,246,48,8,187,120,141,181,222,154,42,163,187,150,191,49,7,141,134,86,42,55,60,194,1,208,74,112,231,7,121,248,168,76,107,131,188,48,66,6,1,195,144,163,203,83,43,4,199,46,108,224,20,51,
135,129,81,90,107,4,61,142,41,173,175,190,91,94,178,142,180,141,68,132,95,8,131,125,60,204,15,71,215,24,237,138,114,132,17,47,118,107,228,196,241,180,48,141,89,27,13,82,96,135,194,25,120,162,204,21,131,
185,185,163,58,224,236,169,248,34,83,112,64,54,93,123,74,3,70,144,211,6,10,210,179,108,197,113,245,243,142,144,18,169,186,95,198,148,55,63,113,148,14,8,148,72,169,129,193,115,249,252,232,207,56,174,215,
43,233,76,118,120,180,16,250,132,233,244,72,220,183,26,73,55,155,135,111,94,191,196,78,38,147,61,60,104,184,72,196,110,172,173,226,163,127,96,112,108,114,186,186,93,46,151,214,239,220,127,84,42,173,85,
182,54,111,44,220,14,146,129,113,36,197,233,145,186,204,108,125,167,166,146,228,218,245,155,163,133,241,229,165,87,7,141,239,168,190,11,156,205,46,222,125,0,150,66,136,247,43,111,63,126,88,169,85,182,
38,166,102,134,114,195,136,225,18,165,44,57,75,245,58,73,199,245,5,50,145,18,203,198,183,125,41,100,28,55,241,13,33,120,138,125,78,44,214,22,198,38,234,213,10,194,96,115,102,174,232,235,230,100,78,188,
118,207,80,61,175,70,20,97,124,98,170,213,252,81,222,220,216,219,253,34,165,4,191,208,45,210,59,40,196,158,207,229,247,247,190,94,40,94,73,167,51,216,6,0,63,36,67,95,237,89,20,225,116,234,78,35,161,179,
197,249,185,75,243,146,59,75,248,109,183,219,247,30,62,14,32,28,53,224,106,219,101,36,49,57,51,203,124,119,33,243,36,81,158,27,17,65,196,39,222,17,178,119,71,252,101,201,121,42,138,66,207,113,238,168,
49,245,234,118,171,21,95,188,124,53,21,165,188,136,172,164,130,135,179,69,236,127,222,17,71,183,144,151,95,144,22,210,236,235,31,184,181,176,152,203,143,244,68,228,168,119,229,39,144,183,47,140,243,38,
132,60,210,9,23,96,211,73,146,64,37,40,226,56,6,87,64,79,90,41,25,201,161,28,76,218,73,231,79,19,92,70,192,128,244,47,1,6,0,217,231,220,140,64,5,128,152,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* JuceDemoPluginAudioProcessorEditor::dry_on_png = (const char*) resource_JuceDemoPluginAudioProcessorEditor_dry_on_png;
const int JuceDemoPluginAudioProcessorEditor::dry_on_pngSize = 780;

// JUCER_RESOURCE: dry_off_png, 779, "../Graphics/dry_off.png"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_dry_off_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,35,0,0,0,13,8,2,0,0,0,172,29,64,72,0,0,0,4,103,65,77,65,0,0,
175,200,55,5,138,233,0,0,0,25,116,69,88,116,83,111,102,116,119,97,114,101,0,65,100,111,98,101,32,73,109,97,103,101,82,101,97,100,121,113,201,101,60,0,0,2,157,73,68,65,84,120,218,156,84,91,79,19,65,24,
157,235,150,150,0,74,91,90,110,18,80,4,53,198,168,9,137,68,163,49,49,38,254,32,95,124,242,175,25,19,137,33,209,240,32,8,82,82,104,161,94,64,11,118,107,187,115,241,204,76,91,53,24,32,76,118,39,59,179,231,
187,156,239,59,51,244,249,139,151,132,16,74,104,162,19,165,20,231,28,75,193,57,99,204,96,88,19,241,148,182,250,191,24,139,65,220,203,40,165,140,1,128,37,177,88,16,60,214,47,44,124,120,140,112,46,220,174,
133,61,12,194,46,94,99,173,183,166,202,232,174,229,31,204,97,189,174,149,202,230,71,56,0,90,9,238,252,32,15,31,149,105,109,144,23,70,200,32,96,24,114,116,121,106,133,224,216,133,13,156,98,230,48,48,74,
107,141,160,199,49,165,141,181,247,203,75,214,145,182,145,136,240,11,97,176,143,135,249,225,232,26,163,93,81,58,24,177,189,185,74,78,28,51,115,55,49,107,163,65,10,236,80,56,3,79,148,185,98,48,55,183,85,
27,156,61,21,95,100,10,14,200,166,107,79,105,192,8,114,218,64,65,122,150,205,56,174,126,222,19,82,34,85,247,203,152,242,214,39,142,210,1,129,18,41,53,56,116,33,151,43,252,138,227,90,173,210,151,206,228,
11,197,208,39,76,167,71,226,190,213,72,186,209,56,122,251,230,21,118,210,233,204,209,97,221,69,34,118,115,125,13,31,3,131,67,163,19,151,170,59,229,114,105,227,254,163,167,165,210,122,101,123,235,246,194,
189,32,25,24,71,82,156,30,169,203,204,214,246,118,85,146,220,184,117,167,80,28,91,94,122,125,88,255,129,234,187,192,153,204,226,131,199,96,41,132,248,176,242,238,227,234,202,110,101,123,124,114,106,56,
155,71,12,151,40,101,201,89,170,215,78,218,174,47,144,137,148,88,214,191,31,72,33,227,184,129,111,8,193,83,236,119,98,177,182,56,58,94,171,86,16,6,155,83,51,179,190,110,78,230,196,107,247,12,213,243,106,
68,17,198,198,39,155,141,159,229,173,205,253,111,95,164,148,224,23,186,69,122,7,133,216,139,217,220,193,254,215,203,179,215,250,250,210,216,6,0,63,36,67,95,237,89,20,225,116,234,78,35,161,211,179,243,
51,87,231,37,119,150,240,219,106,181,30,62,121,22,64,56,106,192,237,238,148,145,196,196,212,52,243,221,133,204,147,68,121,110,68,4,17,159,112,71,192,111,239,142,248,199,146,243,84,20,133,158,227,220,81,
99,106,213,157,102,51,190,50,119,61,21,165,188,136,172,164,130,135,179,69,236,57,239,136,206,45,228,229,23,164,133,52,251,7,6,239,46,44,102,115,35,61,17,57,234,93,249,9,228,237,11,227,188,9,33,59,58,225,
2,108,218,73,18,168,4,69,28,199,224,10,232,73,43,37,35,57,156,133,73,43,105,255,109,130,203,8,24,144,254,45,192,0,155,154,220,84,5,101,5,56,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* JuceDemoPluginAudioProcessorEditor::dry_off_png = (const char*) resource_JuceDemoPluginAudioProcessorEditor_dry_off_png;
const int JuceDemoPluginAudioProcessorEditor::dry_off_pngSize = 779;

// JUCER_RESOURCE: wet_off_png, 874, "../Graphics/wet_off.png"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_wet_off_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,36,0,0,0,23,8,2,0,0,0,236,140,122,204,0,0,0,4,103,65,77,65,
0,0,175,200,55,5,138,233,0,0,0,25,116,69,88,116,83,111,102,116,119,97,114,101,0,65,100,111,98,101,32,73,109,97,103,101,82,101,97,100,121,113,201,101,60,0,0,2,252,73,68,65,84,120,218,188,86,91,79,19,65,
24,157,219,86,187,80,122,217,34,165,23,81,40,148,88,197,132,223,194,79,241,197,39,127,155,47,190,248,166,17,149,187,134,52,64,173,183,216,2,59,59,51,158,153,45,21,155,194,182,129,240,165,153,238,204,158,
51,243,205,249,46,89,250,226,229,43,165,21,49,134,80,202,25,163,140,9,198,101,36,13,49,130,11,44,195,180,214,35,49,74,235,49,41,140,113,74,169,160,148,9,78,250,70,41,134,48,10,41,161,216,67,41,229,214,
248,85,24,193,249,152,20,109,52,49,68,192,41,192,48,129,97,128,119,24,176,3,3,6,94,187,45,48,142,196,96,203,241,41,12,55,196,193,198,24,109,156,17,3,72,202,243,172,14,6,175,65,162,177,115,35,49,19,81,
32,166,144,74,218,183,0,49,110,3,64,153,140,194,123,94,10,254,132,82,90,13,172,187,108,36,166,31,179,177,41,2,171,56,217,221,212,254,217,24,80,26,169,8,14,57,16,24,150,118,21,102,34,138,13,169,177,43,
136,33,254,53,239,203,109,165,48,36,86,65,95,133,153,148,130,132,226,241,197,145,170,82,70,206,21,98,87,57,143,131,155,226,41,101,212,72,12,198,107,40,191,127,253,220,249,188,89,156,43,61,40,149,251,152,
56,153,173,2,208,22,217,69,92,64,93,108,173,224,208,71,43,167,129,93,236,180,143,123,221,110,185,90,227,194,59,216,219,9,138,179,211,153,153,227,163,214,105,175,87,173,45,68,74,157,28,181,176,97,33,152,
157,201,230,126,116,218,223,59,109,76,125,127,42,31,4,216,86,68,81,68,92,250,88,177,93,237,65,125,212,166,245,90,73,32,92,245,232,24,195,185,216,221,250,8,228,84,38,131,135,211,94,119,121,181,185,181,
249,126,122,38,91,169,212,222,190,121,125,63,237,227,135,11,53,215,214,187,221,63,160,0,115,118,118,138,13,237,182,72,144,184,212,225,63,116,209,140,165,68,106,168,29,192,98,76,54,95,40,4,197,253,189,
237,108,54,159,78,251,173,195,175,105,127,74,74,185,84,111,180,90,135,120,72,251,84,193,123,66,218,39,71,165,74,21,128,249,106,173,92,169,65,39,193,61,230,74,157,11,24,71,20,89,220,14,220,69,109,238,160,
233,184,142,243,15,179,176,180,28,73,217,249,118,210,104,174,165,125,31,247,67,72,50,185,156,231,74,109,118,110,190,92,125,88,95,121,2,37,185,219,205,22,184,123,128,187,19,119,144,124,62,200,7,69,4,41,
87,8,22,30,215,63,125,120,183,184,210,0,165,84,169,65,177,47,251,59,112,5,1,107,62,93,151,209,121,191,186,181,166,212,197,125,99,99,131,92,107,245,213,231,192,25,162,109,46,59,111,108,59,224,232,188,81,
156,80,131,41,192,158,16,214,51,87,86,151,41,156,33,251,152,32,73,22,202,240,86,58,200,121,120,158,124,24,130,117,43,29,4,119,75,62,204,50,108,20,233,193,246,38,185,153,37,31,230,113,47,238,32,55,183,
228,195,6,29,100,177,241,236,66,25,227,138,221,6,100,104,234,242,194,38,205,69,211,33,151,41,99,201,56,232,32,67,93,6,99,98,211,249,143,242,104,185,153,248,13,50,232,32,67,93,198,102,99,82,211,185,76,
185,163,111,144,24,115,119,223,32,24,254,10,48,0,46,189,42,57,133,13,247,230,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* JuceDemoPluginAudioProcessorEditor::wet_off_png = (const char*) resource_JuceDemoPluginAudioProcessorEditor_wet_off_png;
const int JuceDemoPluginAudioProcessorEditor::wet_off_pngSize = 874;

// JUCER_RESOURCE: wet_on_png, 884, "../Graphics/wet_on.png"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_wet_on_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,36,0,0,0,23,8,2,0,0,0,236,140,122,204,0,0,0,4,103,65,77,65,0,
0,175,200,55,5,138,233,0,0,0,25,116,69,88,116,83,111,102,116,119,97,114,101,0,65,100,111,98,101,32,73,109,97,103,101,82,101,97,100,121,113,201,101,60,0,0,3,6,73,68,65,84,120,218,188,86,219,78,19,65,24,
158,211,86,187,80,122,216,34,165,7,27,229,100,168,33,145,11,223,196,24,223,195,27,175,124,31,226,75,120,227,133,26,141,16,81,17,65,13,105,128,90,79,177,5,118,118,102,252,102,182,32,146,194,182,129,240,
167,153,238,204,126,223,204,63,223,127,200,138,135,143,30,43,173,136,49,132,82,206,24,101,76,48,46,35,105,136,17,92,96,25,166,181,238,139,81,90,15,72,97,140,83,74,5,165,76,112,210,51,74,49,132,81,72,9,
197,30,74,41,183,198,79,195,8,206,7,164,104,163,137,33,2,78,1,134,9,12,3,188,195,128,29,24,48,240,218,109,129,177,47,6,91,14,78,97,184,33,14,54,198,104,227,140,24,64,82,158,103,117,48,120,13,18,141,157,
235,139,25,138,2,49,133,84,210,190,5,136,113,27,0,202,100,20,94,241,82,240,39,148,210,106,96,221,101,125,49,189,152,13,76,17,88,197,201,238,166,246,207,198,128,210,72,69,112,200,129,192,176,180,211,48,
67,81,108,72,141,93,65,12,241,175,121,79,110,43,133,33,177,10,250,52,204,176,20,36,20,143,47,142,84,149,50,114,174,16,187,202,121,28,220,20,79,41,163,250,98,48,158,65,249,253,235,231,250,135,213,226,68,
233,90,169,220,195,196,201,108,21,128,182,200,46,226,2,234,98,107,5,135,62,90,57,13,236,98,187,181,211,237,116,202,213,26,23,222,231,141,245,160,56,62,154,25,219,217,110,238,117,187,213,90,61,82,106,119,
187,137,13,11,193,248,88,54,247,163,221,250,222,110,97,234,251,35,249,32,192,182,34,138,34,226,210,199,138,237,106,15,234,163,54,173,215,74,2,225,170,71,199,24,206,197,167,181,119,64,142,100,50,120,216,
235,118,102,110,53,214,86,87,70,199,178,149,74,237,197,179,167,87,211,62,126,184,80,99,97,177,211,249,3,10,48,251,251,123,216,208,110,139,4,137,75,29,254,67,23,205,88,74,164,78,180,3,88,140,201,230,11,
133,160,184,185,241,49,155,205,167,211,126,115,235,107,218,31,145,82,78,77,207,53,155,91,120,72,251,84,193,123,66,90,187,219,165,74,21,128,201,106,173,92,169,65,39,193,61,230,74,157,11,24,71,20,89,220,
14,220,69,109,238,160,233,184,142,243,15,83,159,154,137,164,108,127,219,157,107,44,164,125,31,247,67,72,50,185,156,231,74,109,124,98,178,92,189,62,61,59,15,37,185,219,205,22,184,123,128,187,67,119,144,
124,62,200,7,69,4,41,87,8,234,55,166,223,191,93,190,57,59,7,74,169,82,131,98,95,54,215,225,10,2,214,184,189,40,163,131,94,117,107,77,169,139,251,210,210,60,57,211,94,45,63,0,206,16,109,115,217,121,99,
219,1,71,231,141,226,132,58,154,2,236,9,97,61,115,101,117,156,194,25,178,143,9,146,100,161,12,47,164,131,28,132,7,201,135,33,88,23,210,65,112,183,228,195,44,195,70,145,222,189,243,132,156,207,146,15,243,
184,23,119,144,243,91,242,97,71,29,228,229,155,251,135,202,24,87,236,54,32,39,166,46,47,108,210,28,54,29,114,156,50,144,140,71,29,228,68,151,193,152,216,116,254,163,60,127,125,239,236,111,16,87,145,164,
111,151,177,217,152,212,116,142,83,46,233,27,36,198,92,222,55,8,134,191,2,12,0,65,35,45,190,13,108,226,164,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* JuceDemoPluginAudioProcessorEditor::wet_on_png = (const char*) resource_JuceDemoPluginAudioProcessorEditor_wet_on_png;
const int JuceDemoPluginAudioProcessorEditor::wet_on_pngSize = 884;

// JUCER_RESOURCE: off_png, 133, "../Graphics/off.png"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_off_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,11,0,0,0,7,8,2,0,0,0,81,12,32,10,0,0,0,4,103,65,77,65,0,0,175,200,
55,5,138,233,0,0,0,25,116,69,88,116,83,111,102,116,119,97,114,101,0,65,100,111,98,101,32,73,109,97,103,101,82,101,97,100,121,113,201,101,60,0,0,0,23,73,68,65,84,120,218,98,12,9,9,97,192,11,152,24,8,129,
161,163,2,32,192,0,239,192,1,10,42,195,246,197,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* JuceDemoPluginAudioProcessorEditor::off_png = (const char*) resource_JuceDemoPluginAudioProcessorEditor_off_png;
const int JuceDemoPluginAudioProcessorEditor::off_pngSize = 133;

// JUCER_RESOURCE: on_red_png, 134, "../Graphics/on_red.png"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_on_red_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,11,0,0,0,7,8,2,0,0,0,81,12,32,10,0,0,0,4,103,65,77,65,0,0,175,
200,55,5,138,233,0,0,0,25,116,69,88,116,83,111,102,116,119,97,114,101,0,65,100,111,98,101,32,73,109,97,103,101,82,101,97,100,121,113,201,101,60,0,0,0,24,73,68,65,84,120,218,98,252,159,156,204,128,23,48,
49,16,2,67,71,5,64,128,1,0,169,183,1,211,191,46,93,56,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* JuceDemoPluginAudioProcessorEditor::on_red_png = (const char*) resource_JuceDemoPluginAudioProcessorEditor_on_red_png;
const int JuceDemoPluginAudioProcessorEditor::on_red_pngSize = 134;


//[EndFile] You can add extra defines here...
//[/EndFile]
