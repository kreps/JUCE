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
	void drawGroupComponentOutline (Graphics& g, int width, int height,
		const String& text, const Justification& position,
		GroupComponent& group)
	{
		const float textH = 10.0f;
		const float indent = 3.0f;
		const float textEdgeGap = 4.0f;
		float cs = 5.0f;

		Font f (textH);

		Path p;
		float x = indent;
		float y = f.getAscent() - 3.0f;
		float w = jmax (0.0f, width - x * 2.0f);
		float h = jmax (0.0f, height - y  - indent);
		cs = jmin (cs, w * 0.5f, h * 0.5f);
		const float cs2 = 2.0f * cs;

		float textW = text.isEmpty() ? 0 : jlimit (0.0f, jmax (0.0f, w - cs2 - textEdgeGap * 2), f.getStringWidth (text) + textEdgeGap * 2.0f);
		float textX = cs + textEdgeGap;

		if (position.testFlags (Justification::horizontallyCentred))
			textX = cs + (w - cs2 - textW) * 0.5f;
		else if (position.testFlags (Justification::right))
			textX = w - cs - textW - textEdgeGap;

		p.startNewSubPath (x + textX + textW, y);
		p.lineTo (x + w - cs, y);

		p.addArc (x + w - cs2, y, cs2, cs2, 0, float_Pi * 0.5f);
		p.lineTo (x + w, y + h - cs);

		p.addArc (x + w - cs2, y + h - cs2, cs2, cs2, float_Pi * 0.5f, float_Pi);
		p.lineTo (x + cs, y + h);

		p.addArc (x, y + h - cs2, cs2, cs2, float_Pi, float_Pi * 1.5f);
		p.lineTo (x, y + cs);

		p.addArc (x, y, cs2, cs2, float_Pi * 1.5f, float_Pi * 2.0f);
		p.lineTo (x + textX, y);

		const float alpha = group.isEnabled() ? 1.0f : 0.5f;

		g.setColour (group.findColour (GroupComponent::outlineColourId)
			.withMultipliedAlpha (alpha));

		g.strokePath (p, PathStrokeType (2.0f));

		g.setColour (group.findColour (GroupComponent::textColourId)
			.withMultipliedAlpha (alpha));
		g.setFont (f);
		g.drawText (text,
			roundToInt (x + textX), 0,
			roundToInt (textW),
			roundToInt (textH),
			Justification::centred, true);
	}

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
    addAndMakeVisible (groupComponent2 = new GroupComponent ("new group",
                                                             TRANS("reverb")));
    groupComponent2->setColour (GroupComponent::textColourId, Colour (0xff434343));

    addAndMakeVisible (groupComponent = new GroupComponent ("new group",
                                                            TRANS("delay")));
    groupComponent->setColour (GroupComponent::textColourId, Colour (0xff363636));

    addAndMakeVisible (delayHeader = new Label ("new label",
                                                TRANS("amount")));
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
    panSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    panSlider->setColour (Slider::backgroundColourId, Colour (0x00c95c5c));
    panSlider->setColour (Slider::textBoxTextColourId, Colours::white);
    panSlider->setColour (Slider::textBoxHighlightColourId, Colour (0xff1111ee));
    panSlider->setColour (Slider::textBoxOutlineColourId, Colours::grey);
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
                                                     TRANS("distortion")));
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
    hpfSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
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


    //[UserPreSize]
	addAndMakeVisible(resizer = new ResizableCornerComponent(this, &resizeLimits));
	resizeLimits.setSizeLimits(150, 150, 800, 300);
    //[/UserPreSize]

    setSize (400, 200);


    //[Constructor] You can add your own custom stuff here..
	// set our component's initial size to be the last one that was stored in the filter's settings
	setSize(ownerFilter->lastUIWidth, ownerFilter->lastUIHeight);
	setSize(800, 300);

	startTimer(500);
	gainSlider->setDoubleClickReturnValue(true,0.0f);
	//cutom rotary start and end position
	//gainSlider->setRotaryParameters(1.0f*3.14f+0.1f,(12.0f/4.0f)*3.14f-0.1f,true);
	panSlider->setDoubleClickReturnValue(true,0.5f);
	midSideSlider->setDoubleClickReturnValue(true,0.5f);
	LookAndFeel *laf = new CustomLookAndFeel();
	//setupCustomLookAndFeelColours(*laf);
	LookAndFeel::setDefaultLookAndFeel(laf);
	laf->setDefaultSansSerifTypefaceName("Aharoni");

    //[/Constructor]
}

JuceDemoPluginAudioProcessorEditor::~JuceDemoPluginAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	//deleteAllChildren ();
    //[/Destructor_pre]

    groupComponent2 = nullptr;
    groupComponent = nullptr;
    delayHeader = nullptr;
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

    groupComponent2->setBounds (472, 53, 200, 100);
    groupComponent->setBounds (200, 53, 240, 100);
    delayHeader->setBounds (200, 67, 80, 20);
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
    distortionHeader->setBounds (116, 213, 80, 10);
    hpfHeader->setBounds (210, 182, 80, 30);
    hpfSlider->setBounds (220, 202, 60, 75);
    reverbSizeSlider->setBounds (488, 88, 50, 50);
    midsideInfoLabel->setBounds (10, 257, 80, 30);
    reverbSizeHeader->setBounds (472, 64, 80, 30);
    delayTimeSlider2->setBounds (360, 87, 80, 50);
    delayTimeValueLabel2->setBounds (360, 67, 80, 20);
    wetOnlyButton->setBounds (32, 16, 150, 24);
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
  <GROUPCOMPONENT name="new group" id="fb7419eb67152218" memberName="groupComponent2"
                  virtualName="" explicitFocusOrder="0" pos="472 53 200 100" textcol="ff434343"
                  title="reverb"/>
  <GROUPCOMPONENT name="new group" id="98be51d9c59fac6f" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="200 53 240 100" textcol="ff363636"
                  title="delay"/>
  <LABEL name="new label" id="b192efc88f0f8308" memberName="delayHeader"
         virtualName="" explicitFocusOrder="0" pos="200 67 80 20" textCol="ff363636"
         edTextCol="ff000000" edBkgCol="0" labelText="amount" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="pan" id="324eec4d274919f3" memberName="panSlider" virtualName=""
          explicitFocusOrder="0" pos="100 87 80 50" tooltip="pan" bkgcol="c95c5c"
          textboxtext="ffffffff" textboxhighlight="ff1111ee" textboxoutline="ff808080"
          min="0" max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
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
         virtualName="" explicitFocusOrder="0" pos="116 213 80 10" textCol="ff363636"
         edTextCol="ff000000" edBkgCol="0" labelText="distortion" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="10" bold="0" italic="0" justification="12"/>
  <LABEL name="new label" id="f53c45ed3e69f449" memberName="hpfHeader"
         virtualName="" explicitFocusOrder="0" pos="210 182 80 30" textCol="ff363636"
         edTextCol="ff000000" edBkgCol="0" labelText="hi pass filter"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Aharoni" fontsize="10" bold="0" italic="0" justification="36"/>
  <SLIDER name="hi pass filter" id="253b421224cbac37" memberName="hpfSlider"
          virtualName="" explicitFocusOrder="0" pos="220 202 60 75" tooltip="hi pass filter (hz)"
          min="20" max="10000" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
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
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
