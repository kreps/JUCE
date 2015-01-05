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
/** Custom Look And Feel subclasss.

    Simply override the methods you need to, anything else will be inherited from the base class.
    It's a good idea not to hard code your colours, use the findColour method along with appropriate
    ColourIds so you can set these on a per-component basis.
 */
struct CustomLookAndFeel    : public LookAndFeel_V2
{
	void drawRoundThumb (Graphics& g, const float x, const float y,
                         const float diameter, const Colour& colour, float outlineThickness)
    {
        const Rectangle<float> a (x, y, diameter, diameter);
        const float halfThickness = outlineThickness * 0.5f;

        Path p;
        p.addEllipse (x + halfThickness, y + halfThickness, diameter - outlineThickness, diameter - outlineThickness);

        const DropShadow ds (Colours::black, 1, Point<int> (0, 0));
        ds.drawForPath (g, p);

        g.setColour (colour);
        g.fillPath (p);

        g.setColour (colour.brighter());
        g.strokePath (p, PathStrokeType (outlineThickness));
    }

    void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
                               bool isMouseOverButton, bool isButtonDown) override
    {
        Colour baseColour (backgroundColour.withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f)
                           .withMultipliedAlpha (button.isEnabled() ? 0.9f : 0.5f));

        if (isButtonDown || isMouseOverButton)
            baseColour = baseColour.contrasting (isButtonDown ? 0.2f : 0.1f);

        const bool flatOnLeft   = button.isConnectedOnLeft();
        const bool flatOnRight  = button.isConnectedOnRight();
        const bool flatOnTop    = button.isConnectedOnTop();
        const bool flatOnBottom = button.isConnectedOnBottom();

        const float width  = button.getWidth() - 1.0f;
        const float height = button.getHeight() - 1.0f;

        if (width > 0 && height > 0)
        {
            const float cornerSize = jmin (15.0f, jmin (width, height) * 0.45f);
            const float lineThickness = cornerSize * 0.1f;
            const float halfThickness = lineThickness * 0.5f;

            Path outline;
            outline.addRoundedRectangle (0.5f + halfThickness, 0.5f + halfThickness, width - lineThickness, height - lineThickness,
                                         cornerSize, cornerSize,
                                         ! (flatOnLeft  || flatOnTop),
                                         ! (flatOnRight || flatOnTop),
                                         ! (flatOnLeft  || flatOnBottom),
                                         ! (flatOnRight || flatOnBottom));

            const Colour outlineColour (button.findColour (button.getToggleState() ? TextButton::textColourOnId
                                                                                   : TextButton::textColourOffId));

            g.setColour (baseColour);
            g.fillPath (outline);

            if (! button.getToggleState())
            {
                g.setColour (outlineColour);
                g.strokePath (outline, PathStrokeType (lineThickness));
            }
        }
    }

	void drawToggleButton (Graphics& g, ToggleButton& button,
                                       bool isMouseOverButton, bool isButtonDown)
	{
		if (button.hasKeyboardFocus (true))
		{
			//g.setColour (button.findColour (TextEditor::focusedOutlineColourId));
			//g.drawRect (0, 0, button.getWidth(), button.getHeight());
		}

		float fontSize = jmin (15.0f, button.getHeight() * 0.75f);
		const float tickWidth = fontSize * 1.1f;

		drawTickBox (g, button, 4.0f, (button.getHeight() - tickWidth) * 0.5f,
			tickWidth, tickWidth,
			button.getToggleState(),
			button.isEnabled(),
			isMouseOverButton,
			isButtonDown);

		g.setColour (button.findColour (ToggleButton::textColourId));
		g.setFont (fontSize);

		if (! button.isEnabled())
			g.setOpacity (0.5f);

		const int textX = (int) tickWidth + 5;

		g.drawFittedText (button.getButtonText(),
			textX, 0,
			button.getWidth() - textX - 2, button.getHeight(),
			Justification::centredLeft, 10);
	}

    void drawTickBox (Graphics& g, Component& component,
                      float x, float y, float w, float h,
                      bool ticked,
                      bool isEnabled,
                      bool /*isMouseOverButton*/,
                      bool /*isButtonDown*/) override
    {
        const float boxSize = w * 0.7f;

        bool isDownOrDragging = component.isEnabled() && (component.isMouseOverOrDragging() || component.isMouseButtonDown());
        const Colour colour (component.findColour (TextButton::buttonOnColourId).withMultipliedSaturation ((component.hasKeyboardFocus (false) || isDownOrDragging) ? 1.3f : 0.9f)
                             .withMultipliedAlpha (component.isEnabled() ? 1.0f : 0.7f));
        g.setColour (colour);

        Rectangle<float> r (x, y + (h - boxSize) * 0.5f, boxSize, boxSize);
		//g.drawRoundedRectangle(r,1.0f,0);
		//g.fillRect (r);
		g.fillRoundedRectangle(r,3.0f);

        if (ticked)
        {
            //const Path tick (LookAndFeel_V3::getTickShape (6.0f));
            g.setColour (isEnabled ? findColour (TextButton::buttonColourId) : Colours::grey);
			g.setColour (Colours::white);
            /*const AffineTransform trans (RectanglePlacement (RectanglePlacement::centred)
                                         .getTransformToFit (tick.getBounds(), r.reduced (r.getHeight() * 0.05f)));*/
			//g.drawRoundedRectangle (r*0.1f,1.0f,0);
			float boxsize2 = boxSize*0.5f;
			 Rectangle<float> r2 (x+boxsize2/2.0f, y + (h - boxsize2) * 0.5f, boxsize2, boxsize2);
			g.fillRoundedRectangle(r2,1.0f);
        }
    }

    void drawLinearSliderThumb (Graphics& g, int x, int y, int width, int height,
                                float sliderPos, float minSliderPos, float maxSliderPos,
                                const Slider::SliderStyle style, Slider& slider) override
    {
        const float sliderRadius = (float) (getSliderThumbRadius (slider) - 2);

        bool isDownOrDragging = slider.isEnabled() && (slider.isMouseOverOrDragging() || slider.isMouseButtonDown());
        Colour knobColour (slider.findColour (Slider::thumbColourId).withMultipliedSaturation ((slider.hasKeyboardFocus (false) || isDownOrDragging) ? 1.3f : 0.9f)
                           .withMultipliedAlpha (slider.isEnabled() ? 1.0f : 0.7f));

        if (style == Slider::LinearHorizontal || style == Slider::LinearVertical)
        {
            float kx, ky;

            if (style == Slider::LinearVertical)
            {
                kx = x + width * 0.5f;
                ky = sliderPos;
            }
            else
            {
                kx = sliderPos;
                ky = y + height * 0.5f;
            }

            const float outlineThickness = slider.isEnabled() ? 0.8f : 0.3f;

            drawRoundThumb (g,
                            kx - sliderRadius,
                            ky - sliderRadius,
                            sliderRadius * 2.0f,
                            knobColour, outlineThickness);
        }
        else
        {
            // Just call the base class for the demo
            LookAndFeel_V2::drawLinearSliderThumb (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
        }
    }

    void drawLinearSlider (Graphics& g, int x, int y, int width, int height,
                           float sliderPos, float minSliderPos, float maxSliderPos,
                           const Slider::SliderStyle style, Slider& slider) override
    {
        g.fillAll (slider.findColour (Slider::backgroundColourId));

        if (style == Slider::LinearBar || style == Slider::LinearBarVertical)
        {
            const float fx = (float) x, fy = (float) y, fw = (float) width, fh = (float) height;

            Path p;

            if (style == Slider::LinearBarVertical)
                p.addRectangle (fx, sliderPos, fw, 1.0f + fh - sliderPos);
            else
                p.addRectangle (fx, fy, sliderPos - fx, fh);


            Colour baseColour (slider.findColour (Slider::rotarySliderFillColourId)
                               .withMultipliedSaturation (slider.isEnabled() ? 1.0f : 0.5f)
                               .withMultipliedAlpha (0.8f));

            g.setColour (baseColour);
            g.fillPath (p);

            const float lineThickness = jmin (15.0f, jmin (width, height) * 0.45f) * 0.1f;
            g.drawRect (slider.getLocalBounds().toFloat(), lineThickness);
        }
        else
        {
            drawLinearSliderBackground (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
            drawLinearSliderThumb (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
        }
    }

    void drawLinearSliderBackground (Graphics& g, int x, int y, int width, int height,
                                     float /*sliderPos*/,
                                     float /*minSliderPos*/,
                                     float /*maxSliderPos*/,
                                     const Slider::SliderStyle /*style*/, Slider& slider) override
    {
        const float sliderRadius = getSliderThumbRadius (slider) - 5.0f;
        Path on, off;

        if (slider.isHorizontal())
        {
            const float iy = x + width * 0.5f - sliderRadius * 0.5f;
            Rectangle<float> r (x - sliderRadius * 0.5f, iy, width + sliderRadius, sliderRadius);
            const float onW = r.getWidth() * ((float) slider.valueToProportionOfLength (slider.getValue()));

            on.addRectangle (r.removeFromLeft (onW));
            off.addRectangle (r);
        }
        else
        {
            const float ix = x + width * 0.5f - sliderRadius * 0.5f;
            Rectangle<float> r (ix, y - sliderRadius * 0.5f, sliderRadius, height + sliderRadius);
            const float onH = r.getHeight() * ((float) slider.valueToProportionOfLength (slider.getValue()));

            on.addRectangle (r.removeFromBottom (onH));
            off.addRectangle (r);
        }

        g.setColour (slider.findColour (Slider::rotarySliderFillColourId));
        g.fillPath (on);

        g.setColour (slider.findColour (Slider::trackColourId));
        g.fillPath (off);
    }

    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                           float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override
    {
        const float radius = jmin (width / 2, height / 2) - 2.0f;
        const float centreX = x + width * 0.5f;
        const float centreY = y + height * 0.5f;
        const float rx = centreX - radius;
        const float ry = centreY - radius;
        const float rw = radius * 2.0f;
        const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();

        if (slider.isEnabled())
            g.setColour (slider.findColour (Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 1.0f : 0.7f));
        else
            g.setColour (Colour (0x80808080));

        {
			Path filledArc2;
            //filledArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, angle, 0.0);
			filledArc2.addEllipse (rx, ry, rw, rw);

			g.setGradientFill(ColourGradient(Colours::white,0,0,Colours::black,100,100,true));
			g.fillPath (filledArc2);
        }

        {
            /*const float lineThickness = jmin (15.0f, jmin (width, height) * 0.45f) * 0.1f;
            Path outlineArc;
			outlineArc.addEllipse(rx, ry, rw, rw);
            g.strokePath (outlineArc, PathStrokeType (lineThickness));*/
        }
		Path needle;
		Rectangle<float> r (rx, ry, rw, rw);
		Rectangle<float> r2 (0.0f,0.0f, rw*0.05f,rw * 0.3f);
        needle.addRectangle (r2.withPosition (Point<float> (r.getCentreX() - (r2.getWidth() / 2.0f), r.getY())));

        //g.setColour (slider.findColour (Slider::rotarySliderOutlineColourId));
		g.setGradientFill(ColourGradient(Colours::grey,0,0,Colours::black,50,50,true));
		//g.setColour(Colours::black);
        g.fillPath (needle, AffineTransform::rotation (angle, r.getCentreX(), r.getCentreY()));
    }

//	void drawTooltip (Graphics& g, const String& text, int width, int height)
//	{
//		g.fillAll (findColour (TooltipWindow::backgroundColourId));
//
//#if ! JUCE_MAC // The mac windows already have a non-optional 1 pix outline, so don't double it here..
//		g.setColour (findColour (TooltipWindow::outlineColourId));
//		g.drawRect (0, 0, width, height, 1);
//#endif
//
//		LookAndFeelHelpers::layoutTooltipText (text, findColour (TooltipWindow::textColourId))
//			.draw (g, Rectangle<float> ((float) width, (float) height));
//	}

};

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

	laf.setColour (TextButton::buttonOnColourId, laf.findColour (TextButton::textColourOffId));
	laf.setColour (TextButton::textColourOnId, laf.findColour (TextButton::buttonColourId));
};
//[/MiscUserDefs]

//==============================================================================
JuceDemoPluginAudioProcessorEditor::JuceDemoPluginAudioProcessorEditor (JuceDemoPluginAudioProcessor* ownerFilter)
    : AudioProcessorEditor (ownerFilter)
{
    addAndMakeVisible (delayHeader = new Label ("new label",
                                                TRANS("delay")));
    delayHeader->setFont (Font ("Aharoni", 10.00f, Font::plain));
    delayHeader->setJustificationType (Justification::centred);
    delayHeader->setEditable (false, false, false);
    delayHeader->setColour (Label::textColourId, Colour (0xff363636));
    delayHeader->setColour (TextEditor::textColourId, Colours::black);
    delayHeader->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (panSlider = new Slider ("pan"));
    panSlider->setTooltip (TRANS("pan"));
    panSlider->setRange (0, 1, 0);
    panSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    panSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    panSlider->setColour (Slider::backgroundColourId, Colour (0x00c95c5c));
    panSlider->setColour (Slider::textBoxTextColourId, Colours::white);
    panSlider->setColour (Slider::textBoxHighlightColourId, Colour (0xff1111ee));
    panSlider->setColour (Slider::textBoxOutlineColourId, Colours::grey);
    panSlider->addListener (this);

    addAndMakeVisible (infoLabel = new Label (String::empty,
                                              TRANS("aaa")));
    infoLabel->setFont (Font (15.00f, Font::plain));
    infoLabel->setJustificationType (Justification::centredLeft);
    infoLabel->setEditable (false, false, false);
    infoLabel->setColour (Label::textColourId, Colours::white);
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
    delaySlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
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
                                                 TRANS("pan")));
    panInfoLabel->setFont (Font ("Aharoni", 10.00f, Font::plain));
    panInfoLabel->setJustificationType (Justification::centred);
    panInfoLabel->setEditable (false, false, false);
    panInfoLabel->setColour (Label::textColourId, Colour (0xff282828));
    panInfoLabel->setColour (TextEditor::textColourId, Colours::black);
    panInfoLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (delayAmountValueLabel = new Label ("new label",
                                                          TRANS("amount")));
    delayAmountValueLabel->setFont (Font ("Aharoni", 10.00f, Font::plain));
    delayAmountValueLabel->setJustificationType (Justification::centred);
    delayAmountValueLabel->setEditable (false, false, false);
    delayAmountValueLabel->setColour (Label::textColourId, Colour (0xff282828));
    delayAmountValueLabel->setColour (TextEditor::textColourId, Colours::black);
    delayAmountValueLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (delayTimeSlider = new Slider ("new slider"));
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
    panHeader->setColour (Label::textColourId, Colour (0xff363636));
    panHeader->setColour (TextEditor::textColourId, Colours::black);
    panHeader->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (inputHeaderLabel = new Label ("input label for header",
                                                     TRANS("input")));
    inputHeaderLabel->setFont (Font ("Aharoni", 10.00f, Font::plain));
    inputHeaderLabel->setJustificationType (Justification::centred);
    inputHeaderLabel->setEditable (false, false, false);
    inputHeaderLabel->setColour (Label::textColourId, Colour (0xff363636));
    inputHeaderLabel->setColour (TextEditor::textColourId, Colours::black);
    inputHeaderLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (midSideSlider = new Slider ("mid/side slider"));
    midSideSlider->setRange (0, 1, 0);
    midSideSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    midSideSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
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
    saturationSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    saturationSlider->addListener (this);

    addAndMakeVisible (distortionHeader = new Label ("new label",
                                                     TRANS("distortion")));
    distortionHeader->setFont (Font ("Aharoni", 10.00f, Font::plain));
    distortionHeader->setJustificationType (Justification::centred);
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
    hpfSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    hpfSlider->addListener (this);

    addAndMakeVisible (imageButton = new ImageButton ("new button"));
    imageButton->addListener (this);

    imageButton->setImages (false, true, true,
                            ImageCache::getFromMemory (btn_jpeg, btn_jpegSize), 1.000f, Colour (0x00000000),
                            Image(), 1.000f, Colour (0x00000000),
                            Image(), 1.000f, Colour (0x00000000));
    addAndMakeVisible (imageSlider = new Slider ("new slider"));
    imageSlider->setRange (0, 10, 0);
    imageSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    imageSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    imageSlider->addListener (this);


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
	gainSlider->setRotaryParameters(1.0f*3.14f+0.1f,(12.0f/4.0f)*3.14f-0.1f,true);
	panSlider->setDoubleClickReturnValue(true,0.5f);
    midSideSlider->setDoubleClickReturnValue(true,0.5f);
	LookAndFeel *laf = new CustomLookAndFeel();
	//SquareLookAndFeel* laf = new SquareLookAndFeel();
	setupCustomLookAndFeelColours(*laf);
	LookAndFeel::setDefaultLookAndFeel(laf);
	laf->setDefaultSansSerifTypefaceName("Aharoni");
    //addAndMakeVisible(tooltipWindow = new TooltipWindow());
    //[/Constructor]
}

JuceDemoPluginAudioProcessorEditor::~JuceDemoPluginAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	//deleteAllChildren ();
    //[/Destructor_pre]

    delayHeader = nullptr;
    panSlider = nullptr;
    infoLabel = nullptr;
    gainSlider = nullptr;
    delaySlider = nullptr;
    bypassButton = nullptr;
    gainInfoLabel = nullptr;
    panInfoLabel = nullptr;
    delayAmountValueLabel = nullptr;
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
    imageButton = nullptr;
    imageSlider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..

    //[/Destructor]
}

//==============================================================================
void JuceDemoPluginAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    g.setGradientFill(ColourGradient(Colours::white, 0, 0, Colours::grey, 0, (float)getHeight(), false));
    g.fillAll();
    //[/UserPrePaint]

    g.fillAll (Colour (0xff777777));

    g.setColour (Colour (0xff878787));
    g.fillRoundedRectangle (10.0f, 40.0f, 80.0f, 100.0f, 10.000f);

    g.setColour (Colour (0xff878787));
    g.fillRoundedRectangle (110.0f, 40.0f, 80.0f, 100.0f, 10.000f);

    g.setColour (Colour (0xff878787));
    g.fillRoundedRectangle (210.0f, 40.0f, 240.0f, 100.0f, 10.000f);

    g.setColour (Colour (0xff878787));
    g.fillRoundedRectangle (10.0f, 150.0f, 80.0f, 100.0f, 10.000f);

    g.setColour (Colour (0xff878787));
    g.fillRoundedRectangle (110.0f, 150.0f, 80.0f, 100.0f, 10.000f);

    g.setColour (Colour (0xff878787));
    g.fillRoundedRectangle (210.0f, 150.0f, 80.0f, 100.0f, 10.000f);

    //[UserPaint] Add your own custom painting code here..
    /*JuceDemoPluginAudioProcessor* p = getProcessor();

    float* tt = p->test;
    for (int i = 0; i < 500; i){
    g.drawVerticalLine(i,100,100+100*tt[i]);
    }*/

    //[/UserPaint]
}

void JuceDemoPluginAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    delayHeader->setBounds (210, 35, 80, 30);
    panSlider->setBounds (120, 55, 60, 60);
    infoLabel->setBounds (10, 4, 400, 25);
    gainSlider->setBounds (20, 55, 60, 60);
    delaySlider->setBounds (220, 55, 60, 60);
    bypassButton->setBounds (8, 264, 64, 24);
    gainInfoLabel->setBounds (10, 110, 80, 30);
    panInfoLabel->setBounds (110, 110, 80, 30);
    delayAmountValueLabel->setBounds (210, 110, 80, 30);
    delayTimeSlider->setBounds (300, 55, 60, 60);
    delayTimeValueLabel->setBounds (290, 110, 80, 30);
    panHeader->setBounds (110, 35, 80, 30);
    inputHeaderLabel->setBounds (10, 35, 80, 30);
    midSideSlider->setBounds (20, 165, 60, 75);
    midsideHeader->setBounds (10, 145, 80, 30);
    saturationSlider->setBounds (120, 165, 60, 75);
    distortionHeader->setBounds (110, 144, 80, 30);
    hpfHeader->setBounds (210, 145, 80, 30);
    hpfSlider->setBounds (220, 165, 60, 75);
    imageButton->setBounds (304, 152, 72, 80);
    imageSlider->setBounds (312, 264, 150, 64);
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
        getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::panParam,
                                                  (float)panSlider->getValue());
        //[/UserSliderCode_panSlider]
    }
    else if (sliderThatWasMoved == gainSlider)
    {
        //[UserSliderCode_gainSlider] -- add your slider handling code here..
        // It's vital to use setParameterNotifyingHost to change any parameters that are automatable
        // by the host, rather than just modifying them directly, otherwise the host won't know
        // that they've changed.
        getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::gainParam,
                                                  (float)gainSlider->getValue());
        //[/UserSliderCode_gainSlider]
    }
    else if (sliderThatWasMoved == delaySlider)
    {
        //[UserSliderCode_delaySlider] -- add your slider handling code here..
        getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::delayParam,
                                                  (float)delaySlider->getValue());
        //[/UserSliderCode_delaySlider]
    }
    else if (sliderThatWasMoved == delayTimeSlider)
    {
        //[UserSliderCode_delayTimeSlider] -- add your slider handling code here..
		getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::delayTimeParam,
			(float)delayTimeSlider->getValue());
		getProcessor()->reset();
        //[/UserSliderCode_delayTimeSlider]
    }
    else if (sliderThatWasMoved == midSideSlider)
    {
        //[UserSliderCode_midSideSlider] -- add your slider handling code here..
        getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::midSideParam,
                                                  (float)midSideSlider->getValue());
        //[/UserSliderCode_midSideSlider]
    }
    else if (sliderThatWasMoved == saturationSlider)
    {
        //[UserSliderCode_saturationSlider] -- add your slider handling code here..
		getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::thresholdParam,
                                                  (float)saturationSlider->getValue());
        //[/UserSliderCode_saturationSlider]
    }
    else if (sliderThatWasMoved == hpfSlider)
    {
        //[UserSliderCode_hpfSlider] -- add your slider handling code here..
		getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::hpfParam,
			(float)hpfSlider->getValue());
        //[/UserSliderCode_hpfSlider]
    }
    else if (sliderThatWasMoved == imageSlider)
    {
        //[UserSliderCode_imageSlider] -- add your slider handling code here..
        //[/UserSliderCode_imageSlider]
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
    else if (buttonThatWasClicked == imageButton)
    {
        //[UserButtonCode_imageButton] -- add your button handler code here..
        //[/UserButtonCode_imageButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
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
  <BACKGROUND backgroundColour="ff777777">
    <ROUNDRECT pos="10 40 80 100" cornerSize="10" fill="solid: ff878787" hasStroke="0"/>
    <ROUNDRECT pos="110 40 80 100" cornerSize="10" fill="solid: ff878787" hasStroke="0"/>
    <ROUNDRECT pos="210 40 240 100" cornerSize="10" fill="solid: ff878787" hasStroke="0"/>
    <ROUNDRECT pos="10 150 80 100" cornerSize="10" fill="solid: ff878787" hasStroke="0"/>
    <ROUNDRECT pos="110 150 80 100" cornerSize="10" fill="solid: ff878787" hasStroke="0"/>
    <ROUNDRECT pos="210 150 80 100" cornerSize="10" fill="solid: ff878787" hasStroke="0"/>
  </BACKGROUND>
  <LABEL name="new label" id="b192efc88f0f8308" memberName="delayHeader"
         virtualName="" explicitFocusOrder="0" pos="210 35 80 30" textCol="ff363636"
         edTextCol="ff000000" edBkgCol="0" labelText="delay" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="pan" id="324eec4d274919f3" memberName="panSlider" virtualName=""
          explicitFocusOrder="0" pos="120 55 60 60" tooltip="pan" bkgcol="c95c5c"
          textboxtext="ffffffff" textboxhighlight="ff1111ee" textboxoutline="ff808080"
          min="0" max="1" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="" id="3084384ee25f6d12" memberName="infoLabel" virtualName=""
         explicitFocusOrder="0" pos="10 4 400 25" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="aaa" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <SLIDER name="gainSlider" id="c31acc4ca22491a9" memberName="gainSlider"
          virtualName="" explicitFocusOrder="0" pos="20 55 60 60" tooltip="gain"
          min="0" max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.29999999999999999"/>
  <SLIDER name="delay" id="37878e5e9fd60a08" memberName="delaySlider" virtualName=""
          explicitFocusOrder="0" pos="220 55 60 60" tooltip="delay gain&#10;"
          trackcol="ffffffff" textboxhighlight="ff1111ee" textboxoutline="ff808080"
          min="0" max="1" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <TOGGLEBUTTON name="new toggle button" id="d59c4ede9f259185" memberName="bypassButton"
                virtualName="" explicitFocusOrder="0" pos="8 264 64 24" buttonText="bypass"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="gainInfoLabel" id="dde6ff72637f37e7" memberName="gainInfoLabel"
         virtualName="" explicitFocusOrder="0" pos="10 110 80 30" textCol="ff323232"
         edTextCol="ff000000" edBkgCol="0" labelText="0.0 dB&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="64ddab567eb77e3c" memberName="panInfoLabel"
         virtualName="" explicitFocusOrder="0" pos="110 110 80 30" textCol="ff282828"
         edTextCol="ff000000" edBkgCol="0" labelText="pan" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="c1aa620aa8c0a7b0" memberName="delayAmountValueLabel"
         virtualName="" explicitFocusOrder="0" pos="210 110 80 30" textCol="ff282828"
         edTextCol="ff000000" edBkgCol="0" labelText="amount" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="ead45d255e5f5831" memberName="delayTimeSlider"
          virtualName="" explicitFocusOrder="0" pos="300 55 60 60" min="0"
          max="1" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="3b34631ac55e0fe6" memberName="delayTimeValueLabel"
         virtualName="" explicitFocusOrder="0" pos="290 110 80 30" textCol="ff282828"
         edTextCol="ff000000" edBkgCol="0" labelText="time" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="ec32effd76232b82" memberName="panHeader"
         virtualName="" explicitFocusOrder="0" pos="110 35 80 30" textCol="ff363636"
         edTextCol="ff000000" edBkgCol="0" labelText="pan&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <LABEL name="input label for header" id="2a92c25f1cf628c8" memberName="inputHeaderLabel"
         virtualName="" explicitFocusOrder="0" pos="10 35 80 30" textCol="ff363636"
         edTextCol="ff000000" edBkgCol="0" labelText="input" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="mid/side slider" id="84706171dc5b90dd" memberName="midSideSlider"
          virtualName="" explicitFocusOrder="0" pos="20 165 60 75" min="0"
          max="1" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="fcf994bed06bf6ab" memberName="midsideHeader"
         virtualName="" explicitFocusOrder="0" pos="10 145 80 30" textCol="ff363636"
         edTextCol="ff000000" edBkgCol="0" labelText="mid/side" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="mid/side slider" id="2a577f0fc0372cc6" memberName="saturationSlider"
          virtualName="" explicitFocusOrder="0" pos="120 165 60 75" min="0.001"
          max="1" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="eda4710f044030be" memberName="distortionHeader"
         virtualName="" explicitFocusOrder="0" pos="110 144 80 30" textCol="ff363636"
         edTextCol="ff000000" edBkgCol="0" labelText="distortion" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="f53c45ed3e69f449" memberName="hpfHeader"
         virtualName="" explicitFocusOrder="0" pos="210 145 80 30" textCol="ff363636"
         edTextCol="ff000000" edBkgCol="0" labelText="hi pass filter"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Aharoni" fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="hi pass filter" id="253b421224cbac37" memberName="hpfSlider"
          virtualName="" explicitFocusOrder="0" pos="220 165 60 75" tooltip="hi pass filter (hz)"
          min="20" max="10000" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <IMAGEBUTTON name="new button" id="ed493b0fd3b704f3" memberName="imageButton"
               virtualName="" explicitFocusOrder="0" pos="304 152 72 80" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="btn_jpeg" opacityNormal="1" colourNormal="0"
               resourceOver="" opacityOver="1" colourOver="0" resourceDown=""
               opacityDown="1" colourDown="0"/>
  <SLIDER name="new slider" id="81b8a5f3e2f90d2e" memberName="imageSlider"
          virtualName="" explicitFocusOrder="0" pos="312 264 150 64" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

// JUCER_RESOURCE: images_jpg, 1141, "../../../Desktop/images.jpg"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_images_jpg[] = { 255,216,255,224,0,16,74,70,73,70,0,1,1,0,0,1,0,1,0,0,255,219,0,132,0,9,6,7,8,7,6,9,8,7,8,10,10,9,11,13,22,15,13,
12,12,13,27,20,21,16,22,32,29,34,34,32,29,31,31,36,40,52,44,36,38,49,39,31,31,45,61,45,49,53,55,58,58,58,35,43,63,68,63,56,67,52,57,58,55,1,10,10,10,13,12,13,26,15,15,26,55,37,31,37,55,55,55,55,55,55,
55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,255,192,0,17,8,0,95,0,95,3,1,34,0,2,17,1,3,17,1,255,196,0,27,0,1,0,3,
1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,4,5,6,3,2,7,255,196,0,52,16,0,1,3,2,4,2,8,5,3,5,0,0,0,0,0,0,1,0,2,3,4,17,5,18,33,49,65,97,6,19,50,66,81,113,129,145,34,98,177,193,240,20,146,161,35,51,82,83,162,255,196,0,
20,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,196,0,22,17,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,17,1,255,218,0,12,3,1,0,2,17,3,17,0,63,0,233,209,20,32,148,68,64,54,68,80,130,81,20,32,148,65,178,112,65,8,121,
41,66,128,136,161,4,175,151,189,172,26,163,220,26,46,179,234,170,217,1,103,88,225,158,71,101,141,190,39,127,178,11,78,153,220,14,80,188,29,51,91,218,115,189,137,83,73,12,147,222,66,64,107,117,115,222,
108,214,250,173,106,108,23,245,86,202,217,158,15,121,173,107,7,253,27,255,0,8,49,133,92,96,255,0,118,222,119,10,203,39,58,95,226,10,253,111,69,178,180,150,190,70,31,153,161,195,220,109,236,185,234,154,
106,172,50,64,30,44,215,106,8,213,175,252,247,66,182,90,224,237,70,161,21,10,90,129,32,206,221,8,237,3,193,95,107,131,133,198,200,37,17,60,208,17,62,136,57,32,173,80,255,0,139,93,154,177,233,98,21,248,
128,154,92,183,15,45,140,184,95,171,104,7,51,185,119,189,0,94,242,226,49,73,52,148,237,6,249,178,146,79,29,254,139,215,162,12,21,24,132,48,187,126,166,32,121,230,57,157,238,24,71,170,14,137,180,226,8,
24,247,51,40,104,188,113,158,231,51,243,120,159,65,206,206,7,136,135,212,152,28,117,26,133,163,93,68,101,105,0,110,185,211,134,86,81,98,49,85,196,199,57,140,119,245,0,255,0,30,40,58,28,66,184,68,235,23,
44,170,129,13,100,47,99,219,120,221,218,3,135,204,57,170,117,145,87,215,86,58,70,67,35,33,205,240,151,11,92,45,76,58,130,70,0,30,16,113,50,177,248,117,123,227,121,184,107,172,72,239,55,199,238,181,233,
221,169,111,142,161,120,244,182,17,28,165,195,118,49,205,253,164,217,82,162,196,99,53,17,211,155,231,4,48,155,241,181,254,136,99,101,17,66,9,78,8,136,50,170,168,225,235,36,156,68,209,48,7,226,3,95,127,
69,71,163,213,205,195,122,75,15,89,163,36,136,101,62,38,51,114,7,60,133,231,209,109,206,219,58,252,10,230,177,170,41,70,87,211,56,199,52,78,18,193,32,238,144,131,246,89,158,208,220,194,196,110,185,78,
147,87,202,105,223,20,68,128,225,99,101,155,209,62,150,195,89,72,40,234,135,85,44,34,206,143,140,92,173,197,158,4,108,52,54,181,214,149,108,12,170,110,120,220,215,180,236,224,110,10,8,232,198,37,47,80,
200,102,36,134,139,11,174,178,39,199,144,189,197,173,104,23,36,236,2,228,105,32,101,40,47,145,205,99,27,187,156,108,2,243,198,113,246,152,141,29,45,206,97,241,95,75,142,126,13,243,237,109,181,202,12,126,
147,212,137,250,226,52,50,102,181,251,165,238,54,7,203,48,10,41,40,160,18,197,43,162,111,92,209,219,35,95,117,66,35,250,250,195,218,49,192,243,214,60,139,102,127,223,243,193,110,64,221,75,143,162,15,85,
54,69,30,104,38,200,137,230,131,229,205,14,105,5,83,168,132,57,165,146,13,56,21,123,117,14,104,112,177,23,65,203,98,24,43,100,120,150,206,108,141,213,179,196,108,230,251,108,166,157,216,180,71,224,172,
130,111,154,88,172,255,0,87,54,196,174,137,240,145,171,79,186,243,116,36,155,186,48,124,197,208,103,69,21,125,67,129,158,177,140,35,253,17,217,223,184,220,143,69,236,202,70,196,50,70,220,160,155,146,117,
46,62,39,197,92,17,56,13,27,111,225,122,54,30,47,55,242,65,227,4,32,12,172,22,111,18,173,139,1,110,8,0,110,131,78,73,116,19,232,155,162,126,108,129,193,19,154,108,16,16,162,112,65,28,84,165,145,1,20,41,
64,68,58,4,221,1,2,40,65,255,217,0,0};

const char* JuceDemoPluginAudioProcessorEditor::images_jpg = (const char*) resource_JuceDemoPluginAudioProcessorEditor_images_jpg;
const int JuceDemoPluginAudioProcessorEditor::images_jpgSize = 1141;

// JUCER_RESOURCE: btn_jpeg, 7538, "../../../Desktop/btn.jpeg"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_btn_jpeg[] = { 255,216,255,224,0,16,74,70,73,70,0,1,1,1,0,72,0,72,0,0,255,219,0,67,0,8,6,6,7,6,5,8,7,7,7,9,9,8,10,12,20,13,12,11,
11,12,25,18,19,15,20,29,26,31,30,29,26,28,28,32,36,46,39,32,34,44,35,28,28,40,55,41,44,48,49,52,52,52,31,39,57,61,56,50,60,46,51,52,50,255,219,0,67,1,9,9,9,12,11,12,24,13,13,24,50,33,28,33,50,50,50,50,
50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,255,192,0,17,8,0,240,0,240,3,1,34,0,2,17,1,3,17,1,255,196,0,28,
0,1,0,1,5,1,1,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,255,196,0,56,16,0,1,3,3,3,3,3,2,3,7,3,5,1,0,0,0,1,0,2,3,4,5,17,18,33,49,6,65,81,19,34,97,50,113,20,35,66,7,21,51,82,129,146,161,145,193,225,36,83,114,
177,209,162,255,196,0,23,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,255,196,0,23,17,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,49,255,218,0,12,3,1,0,2,17,3,17,0,63,0,247,245,78,229,57,63,10,164,17,167,206,
233,129,225,74,32,141,35,192,77,35,192,82,136,35,72,240,19,72,240,20,162,8,210,60,4,210,60,5,40,130,52,143,1,52,143,1,74,32,141,35,192,77,35,192,82,136,35,72,240,19,72,240,20,162,8,210,60,4,210,60,5,40,
130,52,143,1,52,143,1,74,32,141,35,192,77,35,192,78,232,78,55,40,26,71,128,154,71,128,173,58,170,22,28,58,86,143,234,161,181,112,56,224,72,50,130,246,145,224,38,145,224,40,7,35,32,170,144,70,7,133,4,5,
82,32,167,113,242,164,21,42,158,55,8,42,194,34,32,34,34,2,34,32,34,34,2,34,32,34,34,2,34,32,34,34,2,34,198,172,172,134,138,157,211,76,237,45,31,229,6,65,56,90,138,254,165,183,91,220,88,249,131,228,31,
161,155,149,204,93,122,134,178,224,93,28,14,48,66,127,148,251,138,212,65,111,50,201,193,36,242,74,154,178,58,9,250,210,162,119,104,161,165,3,195,159,186,170,157,183,123,155,131,234,106,30,214,159,210,
223,104,255,0,11,38,213,103,142,54,7,189,128,120,24,91,160,208,209,128,48,21,91,140,40,109,209,66,221,242,227,242,174,122,76,104,216,44,146,54,86,93,193,70,80,202,137,33,62,211,145,224,173,132,21,108,
155,110,29,225,106,157,202,177,44,198,50,11,78,28,56,65,210,34,194,183,214,138,168,176,126,177,200,89,168,8,136,128,136,136,8,136,128,136,136,8,136,128,136,136,8,136,128,136,136,8,160,173,77,222,253,77,
107,97,105,247,204,120,96,65,177,158,118,83,194,233,100,112,13,104,206,235,130,187,93,219,93,80,93,44,184,141,167,216,192,176,110,87,138,219,163,207,173,41,108,125,163,102,193,69,190,210,234,153,7,176,
225,70,164,76,83,122,206,13,130,18,239,146,186,59,85,190,81,135,76,208,7,43,58,134,213,21,44,96,150,130,252,120,89,227,199,9,133,170,128,195,112,6,0,66,128,169,85,149,42,211,249,85,75,43,33,110,169,28,
26,213,134,250,192,227,237,110,222,74,3,221,128,73,90,249,31,169,196,171,245,18,23,51,3,97,221,106,42,235,163,139,219,168,101,6,100,85,198,150,161,175,105,224,239,242,186,248,37,108,240,182,70,157,156,
50,184,26,120,31,81,249,178,101,177,246,30,87,71,103,175,12,112,166,118,205,253,40,55,232,161,74,2,34,32,34,34,2,34,32,34,34,2,34,32,34,40,64,66,113,202,165,242,54,54,23,189,192,52,12,146,87,27,124,234,
135,202,93,79,66,237,44,225,210,119,63,100,36,108,47,157,72,218,64,234,122,66,29,47,5,217,217,171,137,146,71,212,74,95,35,203,228,113,201,60,229,80,214,58,87,224,101,206,61,202,232,109,54,66,242,30,240,
163,121,140,91,93,165,213,15,5,205,60,247,93,133,37,28,116,177,128,208,51,220,171,144,192,200,24,26,192,174,163,54,138,156,42,148,21,81,73,225,65,144,53,133,196,236,6,74,166,73,89,19,114,247,97,97,79,
56,124,18,53,153,201,105,194,13,75,102,150,229,94,249,229,39,209,102,209,179,183,221,81,114,190,219,237,50,195,21,92,225,143,148,225,173,193,63,215,236,174,91,222,209,174,46,28,14,225,90,184,216,168,46,
149,17,207,85,25,115,227,24,4,30,222,20,85,202,201,103,169,131,210,161,103,168,233,7,214,15,180,15,57,88,180,61,60,218,83,235,86,73,234,203,216,118,11,109,12,109,167,137,177,68,52,177,163,0,4,168,46,49,
19,157,194,168,197,154,81,192,192,104,88,110,169,44,144,57,135,4,28,133,98,106,140,242,112,60,44,57,42,218,56,65,233,54,234,145,87,69,28,163,146,55,251,172,181,201,244,117,105,149,179,211,184,253,36,56,
46,177,1,17,16,17,17,1,17,16,17,19,40,8,138,50,130,86,61,93,100,52,80,58,105,222,24,193,229,91,184,87,197,65,76,101,147,115,250,90,57,37,112,87,42,218,139,156,218,234,37,13,96,250,89,157,128,69,147,87,
47,125,67,53,205,230,56,201,142,156,112,209,201,251,173,76,48,62,103,134,180,44,136,32,134,71,134,234,213,159,1,117,118,187,84,113,180,60,180,99,178,141,113,139,105,178,6,1,36,129,116,76,99,88,208,214,
140,5,32,0,49,140,5,42,179,104,163,130,165,66,34,86,29,101,115,105,253,140,247,76,120,111,143,149,110,186,188,197,11,217,78,67,230,0,224,120,92,245,162,224,106,101,149,147,140,79,156,228,242,81,91,64,
215,185,230,73,92,92,243,207,128,170,84,78,36,48,72,33,112,108,186,78,130,225,176,43,159,233,248,110,20,213,115,54,190,177,211,200,252,146,210,115,167,236,130,158,168,171,117,140,71,118,143,248,109,58,
100,9,109,235,187,5,198,16,230,214,198,201,59,198,227,130,10,219,222,40,162,184,90,230,166,150,48,246,188,99,4,45,37,7,75,90,45,147,182,158,134,158,35,48,0,201,41,0,233,62,2,10,238,29,99,21,60,241,193,
73,69,81,84,247,158,67,72,111,250,174,138,9,12,244,236,144,183,73,115,114,71,133,110,90,56,228,132,71,141,37,188,56,13,213,192,25,75,79,185,246,176,110,73,65,197,92,42,125,42,217,163,220,233,113,11,9,
213,142,35,96,2,166,178,95,196,86,77,40,225,207,36,43,40,142,171,162,42,228,55,237,5,219,57,135,33,122,106,242,158,139,4,245,20,88,236,211,149,234,200,8,136,128,136,136,8,136,128,153,69,73,32,110,120,
8,37,105,111,29,67,77,107,105,96,252,217,251,48,30,62,235,95,125,234,113,8,125,53,11,131,164,225,207,236,62,203,141,115,159,44,133,206,37,207,113,220,158,234,53,35,34,225,117,173,185,77,234,77,38,7,102,
183,128,170,162,181,75,87,32,213,146,62,86,101,178,208,249,222,28,224,186,250,74,40,233,88,3,64,213,229,23,113,135,65,102,134,153,128,185,163,82,218,55,0,99,128,165,66,172,90,169,21,58,188,163,156,214,
52,185,199,13,27,146,130,73,192,201,90,186,186,247,76,227,13,49,192,225,210,120,251,43,85,53,175,173,37,144,157,48,119,112,229,223,240,169,107,67,26,26,209,128,60,32,134,70,216,198,7,245,39,186,230,238,
122,104,46,173,168,129,220,159,112,29,138,220,77,81,37,67,223,5,41,3,79,241,37,60,48,127,245,99,212,91,161,154,218,232,160,107,137,105,47,245,30,119,113,69,141,149,60,205,168,129,146,176,251,92,50,165,
176,198,217,93,32,104,214,238,74,231,236,53,134,41,77,36,164,140,157,179,216,174,140,228,180,140,224,227,148,43,85,118,186,50,149,209,192,199,126,99,220,1,248,11,141,190,215,87,116,213,207,241,64,185,
241,19,168,59,177,30,10,222,213,89,93,248,211,41,157,197,193,217,247,119,87,174,97,147,82,72,38,99,94,11,120,112,200,68,89,179,117,245,154,235,8,252,199,69,48,250,152,71,254,138,177,120,191,154,198,152,
41,178,216,143,36,242,229,207,50,150,10,103,187,209,134,54,111,250,90,2,184,128,136,152,201,0,114,80,117,253,1,76,95,113,154,114,54,99,112,10,244,133,206,244,133,179,247,125,165,174,112,196,146,251,138,
232,144,17,17,1,17,16,17,22,45,109,116,20,16,25,103,120,107,64,254,165,5,217,101,100,49,153,36,120,107,6,228,147,140,46,38,251,212,206,170,46,167,164,115,155,15,5,227,109,75,6,241,125,168,186,72,90,9,
100,0,236,193,223,238,181,208,192,249,158,26,1,221,70,164,80,198,186,71,97,173,201,251,174,130,213,102,123,220,28,246,140,125,150,93,166,200,26,3,228,27,46,137,145,182,54,134,180,96,4,91,84,65,3,32,96,
107,0,31,42,234,34,172,10,10,43,53,53,49,210,197,174,67,246,29,202,10,207,11,83,122,142,90,139,116,172,130,66,28,55,219,191,194,147,83,52,254,231,251,90,120,104,80,9,29,208,115,182,26,226,201,29,75,41,
239,182,124,174,135,28,130,185,203,205,17,165,153,181,176,108,9,247,124,21,185,183,213,182,178,145,146,3,238,198,28,62,81,106,161,76,63,134,0,108,13,220,52,126,163,242,175,61,236,134,34,247,144,214,52,
111,240,170,39,3,63,11,85,233,201,113,145,211,214,102,26,8,142,3,63,84,133,17,167,175,25,145,183,10,102,185,177,61,199,7,28,145,221,116,118,250,182,214,82,182,65,245,112,71,202,169,172,53,76,2,72,218,
202,113,244,68,7,3,201,90,70,78,219,29,205,209,202,252,65,39,8,173,197,192,49,144,25,156,112,25,201,43,151,174,186,67,51,12,108,201,30,85,55,171,211,235,158,97,132,150,192,63,253,45,50,34,92,114,226,84,
34,170,56,159,43,195,35,105,115,143,0,32,165,116,157,45,97,125,125,83,42,37,103,229,52,229,160,142,85,118,126,149,150,121,154,234,145,147,207,166,63,220,175,69,162,161,142,138,17,27,64,227,115,132,25,
17,176,70,198,181,187,0,48,171,68,64,68,76,160,34,140,173,5,239,168,226,183,131,12,4,73,63,223,102,160,216,92,110,180,182,216,75,166,144,7,99,218,222,229,121,253,198,236,110,53,6,89,75,156,51,237,104,
224,5,137,81,81,45,92,206,150,103,151,189,199,114,86,93,13,182,74,151,140,180,227,194,141,72,183,78,199,206,224,35,135,111,37,117,118,171,102,150,135,72,192,49,217,100,208,90,227,165,96,46,104,46,91,14,
14,200,90,144,0,0,1,128,165,57,69,89,20,118,82,176,106,171,217,11,253,40,253,242,158,195,183,221,5,202,202,230,82,180,15,170,71,125,45,11,85,165,242,203,235,78,237,82,30,7,96,180,207,184,201,79,124,115,
103,126,166,187,98,79,101,189,27,128,65,229,21,98,178,178,10,10,87,212,84,200,25,27,6,73,88,214,155,189,61,226,3,44,13,123,90,15,235,24,202,201,170,166,130,118,235,157,154,218,198,159,111,149,139,105,
167,124,81,185,238,96,141,174,250,90,60,32,202,174,137,147,81,200,199,240,66,231,45,149,46,183,87,152,37,217,142,56,63,236,87,77,81,15,175,11,162,213,167,86,196,248,90,139,253,176,54,154,58,136,125,198,
54,134,184,249,3,186,17,187,7,184,86,159,15,171,51,94,247,23,53,163,218,206,192,172,11,45,119,226,169,189,55,187,222,205,190,225,108,164,145,177,48,189,238,13,104,220,146,81,9,36,108,81,185,239,112,107,
90,50,73,236,184,139,237,205,151,42,134,181,141,30,156,124,18,55,42,229,234,244,234,231,152,97,37,176,52,255,0,114,211,32,34,34,0,220,224,114,189,43,167,58,125,177,219,161,145,248,99,156,50,252,15,113,
254,171,152,233,155,3,235,170,153,60,204,34,32,114,208,71,63,43,212,99,140,71,27,88,221,128,24,65,76,48,71,3,3,35,96,104,30,21,220,34,32,34,34,2,130,165,97,220,170,127,11,70,249,7,213,140,4,26,123,245,
225,241,230,150,149,216,119,15,127,133,201,254,20,189,197,206,36,147,201,43,96,224,94,226,231,28,146,114,74,170,40,189,73,26,193,201,56,81,185,49,106,138,216,36,120,58,115,158,23,87,71,69,29,44,99,0,106,
86,104,105,219,25,46,199,27,5,176,72,150,138,8,217,74,42,202,140,225,85,144,66,135,14,231,133,132,250,134,229,204,107,178,72,56,194,11,117,151,2,92,96,166,250,255,0,83,251,53,98,71,16,140,19,185,113,220,
147,221,99,208,243,41,249,89,133,21,205,220,224,252,95,175,52,99,243,32,126,29,242,22,117,142,191,241,52,254,139,207,230,51,252,133,137,106,168,7,168,107,105,221,244,201,157,138,197,171,134,75,61,212,
72,204,250,100,229,191,35,194,14,175,144,168,124,145,196,221,82,57,172,111,146,112,162,9,153,60,45,145,135,45,112,202,214,117,29,152,95,45,18,82,135,185,146,3,174,50,14,61,193,17,182,4,56,2,210,8,71,0,
230,57,174,25,105,24,35,202,242,251,127,81,93,186,90,164,81,92,227,116,148,224,224,23,110,71,216,174,254,130,247,65,114,164,252,76,19,180,180,12,184,19,187,80,96,212,209,58,209,55,227,96,36,194,62,182,
119,194,212,94,47,143,184,17,28,57,100,3,183,114,84,222,175,78,174,121,138,18,91,0,63,220,180,200,104,136,136,11,160,233,254,158,146,227,43,101,149,167,210,206,205,254,111,248,84,88,44,18,220,166,108,
146,52,136,115,182,223,82,244,250,42,54,81,192,216,216,7,202,9,162,163,101,28,33,140,3,56,220,172,164,68,4,68,64,68,68,16,185,254,164,155,6,40,179,229,197,116,11,148,234,119,233,174,143,255,0,5,42,206,
181,122,150,117,168,7,214,130,127,72,39,252,45,71,173,242,179,237,21,1,181,100,19,203,72,81,183,73,14,209,131,231,117,112,57,88,99,189,131,236,170,214,180,231,89,1,192,170,100,145,177,48,189,238,1,163,
185,86,12,184,90,46,164,146,165,212,141,124,46,58,26,125,192,32,203,158,170,74,231,22,179,83,41,199,250,187,254,20,181,173,104,192,27,96,225,107,173,21,226,174,148,53,223,196,102,196,121,91,36,90,196,
162,4,122,128,140,28,172,181,1,173,4,184,13,207,42,80,172,122,43,77,53,52,239,168,111,190,103,156,151,30,66,93,232,5,109,27,153,140,61,187,180,252,172,128,72,59,43,141,151,179,191,213,17,203,216,235,76,
19,58,146,99,129,156,12,246,43,164,92,255,0,80,80,24,103,109,109,63,7,234,199,98,182,22,251,140,115,208,250,178,56,52,176,123,242,139,88,247,234,10,74,170,55,58,170,54,185,152,193,212,184,10,106,40,104,
95,32,128,187,4,158,253,151,65,123,189,58,190,67,12,68,136,26,127,185,105,209,4,68,64,91,187,13,134,91,156,237,123,218,68,57,254,229,22,27,20,151,73,195,158,211,232,131,253,203,212,45,246,248,168,97,107,
24,208,14,48,112,130,104,40,99,162,133,172,96,25,198,231,11,49,48,136,8,136,128,136,136,8,136,128,185,14,180,97,140,211,212,126,157,218,87,94,181,61,65,111,253,229,104,154,22,255,0,16,13,76,251,132,88,
243,115,85,242,175,209,87,8,234,152,115,221,115,115,85,58,25,95,20,128,181,236,37,174,7,177,86,255,0,30,90,114,14,227,133,26,215,175,195,32,124,13,35,194,168,185,115,189,51,120,101,117,32,140,184,107,
110,216,91,252,170,205,9,202,166,70,54,70,57,143,25,105,24,33,84,136,142,58,104,228,178,93,117,12,250,110,57,31,33,116,209,74,217,162,108,140,57,107,134,66,181,118,160,21,212,133,160,126,99,119,105,90,
107,37,107,161,148,209,204,116,239,237,207,99,225,21,209,42,37,144,67,19,228,119,210,192,73,85,171,53,44,50,82,200,192,221,69,204,35,30,81,24,214,203,205,21,218,45,116,179,53,196,114,222,225,103,175,49,
173,233,170,251,92,191,141,180,202,246,184,28,186,48,112,66,219,216,186,227,213,144,82,93,34,116,83,141,181,227,159,186,14,210,87,70,200,156,233,72,17,129,151,103,140,46,6,231,83,28,213,178,186,151,83,
33,118,218,65,216,172,187,213,233,213,239,49,66,75,96,105,254,229,166,64,68,68,16,183,22,75,28,215,57,218,231,53,194,28,243,252,223,101,85,130,203,37,206,173,142,115,79,162,14,231,249,190,23,168,81,91,
226,163,96,210,6,172,99,56,224,120,8,22,235,116,84,48,53,172,104,14,3,27,118,89,216,80,20,160,34,34,2,34,32,34,34,2,34,32,40,82,136,60,199,246,135,211,126,140,159,189,169,89,134,59,248,205,3,131,229,121,
234,250,38,170,154,42,186,105,41,230,104,116,114,52,181,192,248,94,29,212,150,73,44,87,105,41,220,15,164,119,141,222,66,44,88,179,220,95,109,174,100,141,62,210,112,224,189,90,142,169,149,148,204,149,132,
28,133,227,43,174,233,11,217,130,81,73,51,189,167,233,37,70,158,128,138,1,200,4,112,84,170,192,185,158,160,160,116,51,10,216,70,6,125,216,236,87,76,168,154,38,77,19,163,120,5,174,24,40,186,214,218,235,
69,101,40,113,250,219,179,150,106,229,153,234,89,46,165,142,207,166,127,200,93,41,158,54,193,235,23,1,30,51,147,198,16,177,137,94,25,0,245,156,67,88,118,63,117,195,220,12,82,215,190,88,218,221,251,129,
202,216,222,239,46,175,147,210,139,104,26,118,249,90,116,65,17,16,22,210,205,102,150,231,56,246,145,14,119,62,126,2,139,61,158,107,164,227,13,34,32,119,62,126,2,245,43,101,178,42,8,24,214,176,7,1,141,
187,32,170,217,108,138,223,78,214,181,128,56,12,109,217,108,7,8,136,8,136,128,136,136,8,136,128,136,136,8,136,128,136,136,32,174,119,171,122,125,151,219,75,131,91,255,0,83,16,213,25,239,159,11,163,80,
80,124,231,36,111,134,71,71,35,75,94,211,130,8,225,35,145,209,72,215,180,225,205,57,5,119,255,0,180,46,154,244,159,251,218,149,158,199,109,51,64,224,249,94,122,163,81,234,61,53,120,109,198,137,173,115,
191,49,187,21,190,94,69,102,185,190,219,92,201,1,246,29,156,23,171,82,84,178,170,153,146,176,228,17,148,44,95,68,86,229,144,49,164,247,85,150,155,169,217,25,161,15,219,214,111,210,184,247,220,106,229,
164,20,242,73,249,96,240,22,250,251,80,100,105,25,217,115,8,104,136,136,5,109,45,86,74,139,140,173,37,174,100,57,250,177,245,125,149,54,91,76,151,74,182,180,3,233,2,53,31,246,94,173,69,110,130,145,173,
45,103,184,12,111,219,236,130,221,166,215,21,190,6,52,48,7,1,176,29,150,205,48,136,8,136,128,136,136,8,136,128,136,136,8,136,128,136,136,8,153,68,4,68,65,98,170,154,58,186,105,32,149,161,204,120,193,5,
120,119,82,217,36,176,221,164,167,112,252,162,117,68,239,45,94,238,180,125,75,211,148,253,69,110,117,60,152,100,205,25,138,92,110,210,138,240,204,133,216,116,133,239,210,147,240,115,59,99,244,229,112,
157,67,65,116,233,138,199,83,220,32,123,89,159,108,160,101,142,31,5,106,161,191,152,165,108,140,126,28,211,145,186,139,175,162,221,32,13,207,149,174,171,155,99,186,229,250,87,173,168,238,240,54,150,162,
86,178,161,163,27,158,87,65,87,28,154,117,52,23,183,203,119,68,198,130,230,252,181,219,173,42,218,215,159,107,178,181,177,195,44,206,12,138,55,61,199,179,70,85,69,11,62,213,107,154,231,80,24,208,68,96,
251,157,133,176,183,244,189,68,239,105,169,62,152,60,70,55,113,254,157,191,170,244,43,61,158,43,124,13,195,3,72,225,163,178,8,179,217,226,183,83,176,6,128,224,54,30,63,229,109,177,132,10,80,17,17,1,17,
16,17,17,1,17,16,17,17,1,17,16,17,17,5,60,31,133,82,42,119,8,42,69,26,188,166,71,148,18,161,53,15,33,53,15,33,6,45,117,186,142,229,78,232,43,105,163,158,51,203,94,50,184,75,143,236,103,165,171,220,231,
197,28,244,174,63,246,164,219,253,8,94,139,168,121,9,168,121,8,60,140,254,194,104,35,126,186,91,197,84,78,28,18,208,112,183,214,238,137,191,90,154,25,23,80,54,118,14,4,176,111,255,0,181,223,106,30,66,
106,30,66,14,95,247,29,209,251,76,104,100,249,49,31,254,172,186,107,11,153,252,105,88,7,118,195,30,159,243,186,222,234,30,66,106,30,66,11,16,82,67,76,220,69,24,30,79,114,178,7,10,53,15,33,53,15,33,4,162,
141,67,200,77,67,200,65,40,163,80,242,19,80,242,16,74,40,212,60,132,212,60,132,18,138,53,15,33,53,15,33,4,162,141,67,200,77,67,200,65,40,163,80,242,19,80,242,16,74,40,200,242,132,132,18,169,59,236,19,
115,240,20,128,131,255,217,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,0,0};

const char* JuceDemoPluginAudioProcessorEditor::btn_jpeg = (const char*) resource_JuceDemoPluginAudioProcessorEditor_btn_jpeg;
const int JuceDemoPluginAudioProcessorEditor::btn_jpegSize = 7538;


//[EndFile] You can add extra defines here...
//[/EndFile]
