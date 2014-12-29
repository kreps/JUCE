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
            const float lineThickness = jmin (15.0f, jmin (width, height) * 0.45f) * 0.1f;
            Path outlineArc;
			outlineArc.addEllipse(rx, ry, rw, rw);
            g.strokePath (outlineArc, PathStrokeType (lineThickness));
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
            LookAndFeel_V2::drawLinearSliderThumb (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
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
    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("delay")));
    label->setFont (Font ("Aharoni", 10.00f, Font::plain));
    label->setJustificationType (Justification::centred);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

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
    gainSlider->setTooltip (TRANS("gain"));
    gainSlider->setRange (0, 1, 0);
    gainSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    gainSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    gainSlider->addListener (this);
    gainSlider->setSkewFactor (0.3);

    addAndMakeVisible (delaySlider = new Slider ("delay"));
    delaySlider->setTooltip (TRANS("delay gain\n"));
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
    panInfoLabel->setFont (Font ("Aharoni", 10.00f, Font::plain));
    panInfoLabel->setJustificationType (Justification::centred);
    panInfoLabel->setEditable (false, false, false);
    panInfoLabel->setColour (Label::textColourId, Colour (0xff282828));
    panInfoLabel->setColour (TextEditor::textColourId, Colours::black);
    panInfoLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (delayAmountInfoLabel = new Label ("new label",
                                                         TRANS("amount")));
    delayAmountInfoLabel->setFont (Font ("Aharoni", 10.00f, Font::plain));
    delayAmountInfoLabel->setJustificationType (Justification::centred);
    delayAmountInfoLabel->setEditable (false, false, false);
    delayAmountInfoLabel->setColour (Label::textColourId, Colour (0xff282828));
    delayAmountInfoLabel->setColour (TextEditor::textColourId, Colours::black);
    delayAmountInfoLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (textButton = new TextButton ("new button"));
    textButton->addListener (this);

    addAndMakeVisible (delayTimeSlider = new Slider ("new slider"));
    delayTimeSlider->setRange (0, 10000, 0);
    delayTimeSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    delayTimeSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    delayTimeSlider->addListener (this);

    addAndMakeVisible (delayAmountInfoLabel2 = new Label ("new label",
                                                          TRANS("time")));
    delayAmountInfoLabel2->setFont (Font ("Aharoni", 10.00f, Font::plain));
    delayAmountInfoLabel2->setJustificationType (Justification::centred);
    delayAmountInfoLabel2->setEditable (false, false, false);
    delayAmountInfoLabel2->setColour (Label::textColourId, Colour (0xff282828));
    delayAmountInfoLabel2->setColour (TextEditor::textColourId, Colours::black);
    delayAmountInfoLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


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

    label = nullptr;
    panSlider = nullptr;
    infoLabel = nullptr;
    gainSlider = nullptr;
    delaySlider = nullptr;
    bypassButton = nullptr;
    gainInfoLabel = nullptr;
    panInfoLabel = nullptr;
    delayAmountInfoLabel = nullptr;
    textButton = nullptr;
    delayTimeSlider = nullptr;
    delayAmountInfoLabel2 = nullptr;


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
    g.fillRoundedRectangle (210.0f, 40.0f, 160.0f, 100.0f, 10.000f);

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

    label->setBounds (210, 33, 160, 30);
    panSlider->setBounds (120, 50, 60, 60);
    infoLabel->setBounds (10, 4, 400, 25);
    gainSlider->setBounds (20, 50, 60, 60);
    delaySlider->setBounds (220, 50, 60, 60);
    bypassButton->setBounds (192, 184, 64, 24);
    gainInfoLabel->setBounds (10, 110, 80, 30);
    panInfoLabel->setBounds (110, 110, 80, 30);
    delayAmountInfoLabel->setBounds (210, 110, 80, 30);
    textButton->setBounds (16, 184, 150, 24);
    delayTimeSlider->setBounds (300, 50, 60, 60);
    delayAmountInfoLabel2->setBounds (290, 110, 80, 30);
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
        //[/UserSliderCode_delayTimeSlider]
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
  <BACKGROUND backgroundColour="ff777777">
    <ROUNDRECT pos="10 40 80 100" cornerSize="10" fill="solid: ff878787" hasStroke="0"/>
    <ROUNDRECT pos="110 40 80 100" cornerSize="10" fill="solid: ff878787" hasStroke="0"/>
    <ROUNDRECT pos="210 40 160 100" cornerSize="10" fill="solid: ff878787" hasStroke="0"/>
  </BACKGROUND>
  <LABEL name="new label" id="b192efc88f0f8308" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="210 33 160 30" edTextCol="ff000000"
         edBkgCol="0" labelText="delay" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Aharoni" fontsize="10" bold="0"
         italic="0" justification="36"/>
  <SLIDER name="pan" id="324eec4d274919f3" memberName="panSlider" virtualName=""
          explicitFocusOrder="0" pos="120 50 60 60" tooltip="pan" bkgcol="c95c5c"
          textboxtext="ffffffff" textboxhighlight="ff1111ee" textboxoutline="ff808080"
          min="0" max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="" id="3084384ee25f6d12" memberName="infoLabel" virtualName=""
         explicitFocusOrder="0" pos="10 4 400 25" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="aaa" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <SLIDER name="gainSlider" id="c31acc4ca22491a9" memberName="gainSlider"
          virtualName="" explicitFocusOrder="0" pos="20 50 60 60" tooltip="gain"
          min="0" max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.29999999999999999"/>
  <SLIDER name="delay" id="37878e5e9fd60a08" memberName="delaySlider" virtualName=""
          explicitFocusOrder="0" pos="220 50 60 60" tooltip="delay gain&#10;"
          trackcol="ffffffff" textboxhighlight="ff1111ee" textboxoutline="ff808080"
          min="0" max="1" int="0.10000000000000001" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <TOGGLEBUTTON name="new toggle button" id="d59c4ede9f259185" memberName="bypassButton"
                virtualName="" explicitFocusOrder="0" pos="192 184 64 24" buttonText="bypass"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="new label" id="dde6ff72637f37e7" memberName="gainInfoLabel"
         virtualName="" explicitFocusOrder="0" pos="10 110 80 30" textCol="ff323232"
         edTextCol="ff000000" edBkgCol="0" labelText="0.0 dB&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="64ddab567eb77e3c" memberName="panInfoLabel"
         virtualName="" explicitFocusOrder="0" pos="110 110 80 30" textCol="ff282828"
         edTextCol="ff000000" edBkgCol="0" labelText="pan" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="c1aa620aa8c0a7b0" memberName="delayAmountInfoLabel"
         virtualName="" explicitFocusOrder="0" pos="210 110 80 30" textCol="ff282828"
         edTextCol="ff000000" edBkgCol="0" labelText="amount" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="new button" id="f224485d1aa5be5d" memberName="textButton"
              virtualName="" explicitFocusOrder="0" pos="16 184 150 24" buttonText="new button"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="new slider" id="ead45d255e5f5831" memberName="delayTimeSlider"
          virtualName="" explicitFocusOrder="0" pos="300 50 60 60" min="0"
          max="10000" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="3b34631ac55e0fe6" memberName="delayAmountInfoLabel2"
         virtualName="" explicitFocusOrder="0" pos="290 110 80 30" textCol="ff282828"
         edTextCol="ff000000" edBkgCol="0" labelText="time" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
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


//[EndFile] You can add extra defines here...
//[/EndFile]
