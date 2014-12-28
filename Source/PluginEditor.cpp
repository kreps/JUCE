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
struct CustomLookAndFeel    : public LookAndFeel_V3
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
            LookAndFeel_V3::drawLinearSliderThumb (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
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
			/*Rotary knob fill*/
            Path filledArc;
            //filledArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, angle, 0.0);
			filledArc.addEllipse (rx, ry, rw, rw);
			g.fillPath (filledArc);
        }

        {
            /*const float lineThickness = jmin (15.0f, jmin (width, height) * 0.45f) * 0.1f;
            Path outlineArc;
			outlineArc.addEllipse(rx, ry, rw, rw);
            g.strokePath (outlineArc, PathStrokeType (lineThickness));*/
        }
		Path needle;
		Rectangle<float> r (rx, ry, rw, rw);
		Rectangle<float> r2 (0.0f,0.0f, rw*0.1f,rw * 0.5f);
        needle.addRectangle (r2.withPosition (Point<float> (r.getCentreX() - (r2.getWidth() / 2.0f), r.getY())));

        g.setColour (slider.findColour (Slider::rotarySliderOutlineColourId));
        g.fillPath (needle, AffineTransform::rotation (angle, r.getCentreX(), r.getCentreY()));
    }

};

//==============================================================================
/** Another really simple look and feel that is very flat and square.
    This inherits from CustomLookAndFeel above for the linear bar and slider backgrounds.
 */


struct SquareLookAndFeel    : public CustomLookAndFeel
{
    void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
                               bool isMouseOverButton, bool isButtonDown) override
    {
        Colour baseColour (backgroundColour.withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f)
                           .withMultipliedAlpha (button.isEnabled() ? 0.9f : 0.5f));

        if (isButtonDown || isMouseOverButton)
            baseColour = baseColour.contrasting (isButtonDown ? 0.2f : 0.1f);

        const float width  = button.getWidth() - 1.0f;
        const float height = button.getHeight() - 1.0f;

        if (width > 0 && height > 0)
        {
            g.setGradientFill (ColourGradient (baseColour, 0.0f, 0.0f,
                                               baseColour.darker (0.1f), 0.0f, height,
                                               false));

            g.fillRect (button.getLocalBounds());
        }
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
        g.fillRect (r);

        if (ticked)
        {
            //const Path tick (LookAndFeel_V3::getTickShape (6.0f));
            g.setColour (isEnabled ? findColour (TextButton::buttonColourId) : Colours::grey);

            /*const AffineTransform trans (RectanglePlacement (RectanglePlacement::centred)
                                         .getTransformToFit (tick.getBounds(), r.reduced (r.getHeight() * 0.05f)));*/
			g.drawRoundedRectangle (r*0.1f,1.0f,0);
        }
    }

	void drawToggleButton (Graphics& g, ToggleButton& button,
                                       bool isMouseOverButton, bool isButtonDown)
	{
		if (button.hasKeyboardFocus (true))
		{
			g.setColour (button.findColour (TextEditor::focusedOutlineColourId));
			g.drawRect (0, 0, button.getWidth(), button.getHeight());
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

    void drawLinearSliderThumb (Graphics& g, int x, int y, int width, int height,
                                float sliderPos, float minSliderPos, float maxSliderPos,
                                const Slider::SliderStyle style, Slider& slider) override
    {
        const float sliderRadius = (float) getSliderThumbRadius (slider);

        bool isDownOrDragging = slider.isEnabled() && (slider.isMouseOverOrDragging() || slider.isMouseButtonDown());
        Colour knobColour (slider.findColour (Slider::rotarySliderFillColourId).withMultipliedSaturation ((slider.hasKeyboardFocus (false) || isDownOrDragging) ? 1.3f : 0.9f)
                           .withMultipliedAlpha (slider.isEnabled() ? 1.0f : 0.7f));
        g.setColour (knobColour);

        if (style == Slider::LinearHorizontal || style == Slider::LinearVertical)
        {
            float kx, ky;

            if (style == Slider::LinearVertical)
            {
                kx = x + width * 0.5f;
                ky = sliderPos;
                g.fillRect (Rectangle<float> (kx - sliderRadius, ky - 2.5f, sliderRadius * 2.0f, 5.0f));
            }
            else
            {
                kx = sliderPos;
                ky = y + height * 0.5f;
                g.fillRect (Rectangle<float> (kx - 2.5f, ky - sliderRadius, 5.0f, sliderRadius * 2.0f));
            }
        }
        else
        {
            // Just call the base class for the demo
            LookAndFeel_V3::drawLinearSliderThumb (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
        }
    }

    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                           float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override
    {
        const float diameter = jmin (width, height) - 4.0f;
        const float radius = (diameter / 2.0f) * std::cos (float_Pi / 4.0f);
        const float centreX = x + width * 0.5f;
        const float centreY = y + height * 0.5f;
        const float rx = centreX - radius;
        const float ry = centreY - radius;
        const float rw = radius * 2.0f;
        const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();

        const Colour baseColour (slider.isEnabled() ? slider.findColour (Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 0.8f : 1.0f)
                                                    : Colour (0x80808080));

        Rectangle<float> r (rx, ry, rw, rw);
        AffineTransform t (AffineTransform::rotation (angle, r.getCentreX(), r.getCentreY()));

        float x1 = r.getTopLeft().getX(), y1 = r.getTopLeft().getY(), x2 = r.getBottomLeft().getX(), y2 = r.getBottomLeft().getY();
        t.transformPoints (x1, y1, x2, y2);

        g.setGradientFill (ColourGradient (baseColour, x1, y1,
                                           baseColour.darker (0.1f), x2, y2,
                                           false));

        Path knob;
        knob.addRectangle (r);
        g.fillPath (knob, t);

        Path needle;
        Rectangle<float> r2 (r * 0.1f);
        needle.addRectangle (r2.withPosition (Point<float> (r.getCentreX() - (r2.getWidth() / 2.0f), r.getY())));

        g.setColour (slider.findColour (Slider::rotarySliderOutlineColourId));
        g.fillPath (needle, AffineTransform::rotation (angle, r.getCentreX(), r.getCentreY()));
    }
};

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
    addAndMakeVisible (panSlider = new Slider ("pan"));
    panSlider->setTooltip (TRANS("pan"));
    panSlider->setRange (0, 1, 0);
    panSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    panSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
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
    gainSlider->setTooltip (TRANS("Gain"));
    gainSlider->setRange (0, 1, 0);
    gainSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    gainSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    gainSlider->addListener (this);
    gainSlider->setSkewFactor (0.3);

    addAndMakeVisible (delaySlider = new Slider ("delay"));
    delaySlider->setTooltip (TRANS("Delay gain\n"));
    delaySlider->setRange (0, 1, 0.1);
    delaySlider->setSliderStyle (Slider::RotaryVerticalDrag);
    delaySlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    delaySlider->setColour (Slider::trackColourId, Colours::white);
    delaySlider->setColour (Slider::textBoxHighlightColourId, Colour (0xff1111ee));
    delaySlider->setColour (Slider::textBoxOutlineColourId, Colours::grey);
    delaySlider->addListener (this);

    addAndMakeVisible (bypassButton = new ToggleButton ("new toggle button"));
    bypassButton->setButtonText (TRANS("bypass"));
    bypassButton->addListener (this);

    addAndMakeVisible (gainInfoLabel = new Label ("new label",
                                                  TRANS("0.0 dB\n")));
    gainInfoLabel->setFont (Font ("Aharoni", 12.00f, Font::plain));
    gainInfoLabel->setJustificationType (Justification::centred);
    gainInfoLabel->setEditable (false, false, false);
    gainInfoLabel->setColour (Label::textColourId, Colour (0xff323232));
    gainInfoLabel->setColour (TextEditor::textColourId, Colours::black);
    gainInfoLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (panInfoLabel = new Label ("new label",
                                                 TRANS("pan")));
    panInfoLabel->setFont (Font ("Aharoni", 12.00f, Font::plain));
    panInfoLabel->setJustificationType (Justification::centred);
    panInfoLabel->setEditable (false, false, false);
    panInfoLabel->setColour (Label::textColourId, Colour (0xff282828));
    panInfoLabel->setColour (TextEditor::textColourId, Colours::black);
    panInfoLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (delayAmountInfoLabel = new Label ("new label",
                                                         TRANS("delay")));
    delayAmountInfoLabel->setFont (Font ("Aharoni", 12.00f, Font::plain));
    delayAmountInfoLabel->setJustificationType (Justification::centred);
    delayAmountInfoLabel->setEditable (false, false, false);
    delayAmountInfoLabel->setColour (Label::textColourId, Colour (0xff282828));
    delayAmountInfoLabel->setColour (TextEditor::textColourId, Colours::black);
    delayAmountInfoLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (textButton = new TextButton ("new button"));
    textButton->addListener (this);


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
	CustomLookAndFeel* laf = new CustomLookAndFeel();
	setupCustomLookAndFeelColours(*laf);
	LookAndFeel::setDefaultLookAndFeel(laf);
	laf->setDefaultSansSerifTypefaceName("Aharoni");
    addAndMakeVisible(tooltipWindow = new TooltipWindow());
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
    bypassButton = nullptr;
    gainInfoLabel = nullptr;
    panInfoLabel = nullptr;
    delayAmountInfoLabel = nullptr;
    textButton = nullptr;


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

    g.fillAll (Colour (0xff848484));

    g.setColour (Colour (0xff2a9fa5));
    g.fillRoundedRectangle (10.0f, 30.0f, 80.0f, 100.0f, 10.000f);

    g.setColour (Colour (0xff2a9fa5));
    g.fillRoundedRectangle (110.0f, 30.0f, 80.0f, 100.0f, 10.000f);

    g.setColour (Colour (0xff2a9fa5));
    g.fillRoundedRectangle (210.0f, 30.0f, 80.0f, 100.0f, 10.000f);

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

    panSlider->setBounds (120, 40, 60, 60);
    infoLabel->setBounds (10, 4, 400, 25);
    gainSlider->setBounds (20, 40, 60, 60);
    delaySlider->setBounds (220, 40, 60, 60);
    bypassButton->setBounds (312, 104, 64, 24);
    gainInfoLabel->setBounds (10, 100, 80, 30);
    panInfoLabel->setBounds (110, 100, 80, 30);
    delayAmountInfoLabel->setBounds (210, 100, 80, 30);
    textButton->setBounds (16, 144, 150, 24);
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
        //[/UserButtonCode_textButton]
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
  <BACKGROUND backgroundColour="ff848484">
    <ROUNDRECT pos="10 30 80 100" cornerSize="10" fill="solid: ff2a9fa5" hasStroke="0"/>
    <ROUNDRECT pos="110 30 80 100" cornerSize="10" fill="solid: ff2a9fa5" hasStroke="0"/>
    <ROUNDRECT pos="210 30 80 100" cornerSize="10" fill="solid: ff2a9fa5" hasStroke="0"/>
  </BACKGROUND>
  <SLIDER name="pan" id="324eec4d274919f3" memberName="panSlider" virtualName=""
          explicitFocusOrder="0" pos="120 40 60 60" tooltip="pan" bkgcol="c95c5c"
          textboxtext="ffffffff" textboxhighlight="ff1111ee" textboxoutline="ff808080"
          min="0" max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="" id="3084384ee25f6d12" memberName="infoLabel" virtualName=""
         explicitFocusOrder="0" pos="10 4 400 25" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="aaa" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <SLIDER name="gainSlider" id="c31acc4ca22491a9" memberName="gainSlider"
          virtualName="" explicitFocusOrder="0" pos="20 40 60 60" tooltip="Gain"
          min="0" max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.29999999999999999"/>
  <SLIDER name="delay" id="37878e5e9fd60a08" memberName="delaySlider" virtualName=""
          explicitFocusOrder="0" pos="220 40 60 60" tooltip="Delay gain&#10;"
          trackcol="ffffffff" textboxhighlight="ff1111ee" textboxoutline="ff808080"
          min="0" max="1" int="0.10000000000000001" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <TOGGLEBUTTON name="new toggle button" id="d59c4ede9f259185" memberName="bypassButton"
                virtualName="" explicitFocusOrder="0" pos="312 104 64 24" buttonText="bypass"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="new label" id="dde6ff72637f37e7" memberName="gainInfoLabel"
         virtualName="" explicitFocusOrder="0" pos="10 100 80 30" textCol="ff323232"
         edTextCol="ff000000" edBkgCol="0" labelText="0.0 dB&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="64ddab567eb77e3c" memberName="panInfoLabel"
         virtualName="" explicitFocusOrder="0" pos="110 100 80 30" textCol="ff282828"
         edTextCol="ff000000" edBkgCol="0" labelText="pan" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="c1aa620aa8c0a7b0" memberName="delayAmountInfoLabel"
         virtualName="" explicitFocusOrder="0" pos="210 100 80 30" textCol="ff282828"
         edTextCol="ff000000" edBkgCol="0" labelText="delay" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="new button" id="f224485d1aa5be5d" memberName="textButton"
              virtualName="" explicitFocusOrder="0" pos="16 144 150 24" buttonText="new button"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
