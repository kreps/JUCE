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

    void drawTickBox (Graphics& g, Component& component,
                      float x, float y, float w, float h,
                      bool ticked,
                      bool isEnabled,
                      bool isMouseOverButton,
                      bool isButtonDown) override
    {
        const float boxSize = w * 0.7f;

        bool isDownOrDragging = component.isEnabled() && (component.isMouseOverOrDragging() || component.isMouseButtonDown());
        const Colour colour (component.findColour (TextButton::buttonColourId).withMultipliedSaturation ((component.hasKeyboardFocus (false) || isDownOrDragging) ? 1.3f : 0.9f)
                             .withMultipliedAlpha (component.isEnabled() ? 1.0f : 0.7f));

        drawRoundThumb (g, x, y + (h - boxSize) * 0.5f, boxSize, colour,
                        isEnabled ? ((isButtonDown || isMouseOverButton) ? 1.1f : 0.5f) : 0.3f);

        if (ticked)
        {
            const Path tick (LookAndFeel_V2::getTickShape (6.0f));
            g.setColour (isEnabled ? findColour (TextButton::buttonOnColourId) : Colours::grey);

            const float scale = 9.0f;
            const AffineTransform trans (AffineTransform::scale (w / scale, h / scale)
                                             .translated (x - 2.5f, y + 1.0f));
            g.fillPath (tick, trans);
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
            const Path tick (LookAndFeel_V3::getTickShape (6.0f));
            g.setColour (isEnabled ? findColour (TextButton::buttonColourId) : Colours::grey);

            const AffineTransform trans (RectanglePlacement (RectanglePlacement::centred)
                                         .getTransformToFit (tick.getBounds(), r.reduced (r.getHeight() * 0.05f)));
            g.fillPath (tick, trans);
        }
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
        laf.setColour (Slider::textBoxOutlineColourId, Colours::transparentWhite);
        laf.setColour (Slider::rotarySliderFillColourId, Colour (0xff00b5f6));
        laf.setColour (Slider::rotarySliderOutlineColourId, Colours::white);

        laf.setColour (TextButton::buttonColourId, Colours::white);
        laf.setColour (TextButton::textColourOffId, Colour (0xff00b5f6));

        laf.setColour (TextButton::buttonOnColourId, laf.findColour (TextButton::textColourOffId));
        laf.setColour (TextButton::textColourOnId, laf.findColour (TextButton::buttonColourId));
    }
//[/MiscUserDefs]

//==============================================================================
JuceDemoPluginAudioProcessorEditor::JuceDemoPluginAudioProcessorEditor (JuceDemoPluginAudioProcessor* ownerFilter)
    : AudioProcessorEditor (ownerFilter)
{
	//[Customlaf]
	CustomLookAndFeel* laf = new CustomLookAndFeel();
	setupCustomLookAndFeelColours(*laf);
	this->setLookAndFeel(laf);
	
	//[/Customlaf]
    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("pan")));
    label->setFont (Font ("Aharoni", 12.00f, Font::plain));
    label->setJustificationType (Justification::centred);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (infoLabel = new Label (String::empty,
                                              TRANS("aaa")));
    infoLabel->setFont (Font (15.00f, Font::plain));
    infoLabel->setJustificationType (Justification::centredLeft);
    infoLabel->setEditable (false, false, false);
    infoLabel->setColour (Label::textColourId, Colours::blue);
    infoLabel->setColour (TextEditor::textColourId, Colours::black);
    infoLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (gainSlider = new Slider ("gainSlider"));
    gainSlider->setTooltip (TRANS("Gain"));
    gainSlider->setRange (0, 1, 0);
    gainSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    gainSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    gainSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66000000));
    gainSlider->addListener (this);

    addAndMakeVisible (delaySlider = new Slider ("delay"));
    delaySlider->setTooltip (TRANS("Delay gain\n"));
    delaySlider->setRange (0, 1, 0.1);
    delaySlider->setSliderStyle (Slider::RotaryVerticalDrag);
    delaySlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    delaySlider->addListener (this);

    addAndMakeVisible (panSlider = new Slider ("pan"));
    panSlider->setTooltip (TRANS("pan"));
    panSlider->setRange (0, 1, 0);
    panSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    panSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    panSlider->addListener (this);

    addAndMakeVisible (bypassButtonImg = new ImageButton ("new button"));
    bypassButtonImg->addListener (this);

    bypassButtonImg->setImages (false, true, true,
                                ImageCache::getFromMemory (onMaya_png, onMaya_pngSize), 1.000f, Colour (0x00ac4b4b),
                                Image(), 1.000f, Colour (0x00953434),
                                ImageCache::getFromMemory (offMaya_png, offMaya_pngSize), 1.000f, Colour (0x008b3a3a));
    addAndMakeVisible (bypassButton = new ToggleButton ("new toggle button"));
    bypassButton->setButtonText (TRANS("bypass"));
    bypassButton->addListener (this);

    addAndMakeVisible (gainInfoLabel = new Label ("new label",
                                                  TRANS("0.0\n"
                                                  "dB\n")));
    gainInfoLabel->setFont (Font ("Aharoni", 12.00f, Font::plain));
    gainInfoLabel->setJustificationType (Justification::centred);
    gainInfoLabel->setEditable (false, false, false);
    gainInfoLabel->setColour (TextEditor::textColourId, Colours::black);
    gainInfoLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (leftGainInfoLabel = new Label ("new label",
                                                      TRANS("10.0 dB\n")));
    leftGainInfoLabel->setFont (Font ("Aharoni", 12.00f, Font::plain));
    leftGainInfoLabel->setJustificationType (Justification::centred);
    leftGainInfoLabel->setEditable (false, false, false);
    leftGainInfoLabel->setColour (TextEditor::textColourId, Colours::black);
    leftGainInfoLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (rightGainInfoLabel = new Label ("new label",
                                                       TRANS("10.0 dB\n")));
    rightGainInfoLabel->setFont (Font ("Aharoni", 12.00f, Font::plain));
    rightGainInfoLabel->setJustificationType (Justification::centred);
    rightGainInfoLabel->setEditable (false, false, false);
    rightGainInfoLabel->setColour (TextEditor::textColourId, Colours::black);
    rightGainInfoLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lafBox = new ComboBox ("new combo box"));
    lafBox->setEditableText (false);
    lafBox->setJustificationType (Justification::centredLeft);
    lafBox->setTextWhenNothingSelected (String::empty);
    lafBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    lafBox->addListener (this);

    addAndMakeVisible (textButton = new TextButton ("new button"));
    textButton->addListener (this);

    cachedImage_untitled1_png = ImageCache::getFromMemory (untitled1_png, untitled1_pngSize);

    //[UserPreSize]
    addAndMakeVisible(resizer = new ResizableCornerComponent(this, &resizeLimits));
    resizeLimits.setSizeLimits(150, 150, 800, 300);
    bypassButtonImg->setClickingTogglesState(true);
    //[/UserPreSize]

    setSize (400, 200);


    //[Constructor] You can add your own custom stuff here..
    // set our component's initial size to be the last one that was stored in the filter's settings
    setSize(ownerFilter->lastUIWidth, ownerFilter->lastUIHeight);
    setSize(800, 300);

    startTimer(50);
	gainSlider->setDoubleClickReturnValue(true,1.0f);
	panSlider->setDoubleClickReturnValue(true,0.5f);

    //addAndMakeVisible(tooltipWindow = new TooltipWindow());
    //[/Constructor]
}

JuceDemoPluginAudioProcessorEditor::~JuceDemoPluginAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    label = nullptr;
    infoLabel = nullptr;
    gainSlider = nullptr;
    delaySlider = nullptr;
    panSlider = nullptr;
    bypassButtonImg = nullptr;
    bypassButton = nullptr;
    gainInfoLabel = nullptr;
    leftGainInfoLabel = nullptr;
    rightGainInfoLabel = nullptr;
    lafBox = nullptr;
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

    g.fillAll (Colours::grey);

    g.setColour (Colours::black);
    g.drawImage (cachedImage_untitled1_png,
                 316, 84, 51, 13,
                 0, 0, cachedImage_untitled1_png.getWidth(), cachedImage_untitled1_png.getHeight());

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

    label->setBounds (60, 76, 150, 24);
    infoLabel->setBounds (10, 4, 400, 25);
    gainSlider->setBounds (10, 30, 70, 70);
    delaySlider->setBounds (200, 30, 90, 90);
    panSlider->setBounds (100, 30, 70, 70);
    bypassButtonImg->setBounds (312, 24, 60, 60);
    bypassButton->setBounds (312, 104, 64, 24);
    gainInfoLabel->setBounds (10, 100, 70, 30);
    leftGainInfoLabel->setBounds (100, 100, 35, 30);
    rightGainInfoLabel->setBounds (133, 100, 35, 30);
    lafBox->setBounds (40, 160, 150, 24);
    textButton->setBounds (224, 152, 150, 104);
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

    if (sliderThatWasMoved == gainSlider)
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
    else if (sliderThatWasMoved == panSlider)
    {
        //[UserSliderCode_panSlider] -- add your slider handling code here..
        getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::panParam,
                                                  (float)panSlider->getValue());
        //[/UserSliderCode_panSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void JuceDemoPluginAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == bypassButtonImg)
    {
        //[UserButtonCode_bypassButtonImg] -- add your button handler code here..
        getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::bypassParam, (float)bypassButtonImg->getToggleState());
        //[/UserButtonCode_bypassButtonImg]
    }
    else if (buttonThatWasClicked == bypassButton)
    {
        //[UserButtonCode_bypassButton] -- add your button handler code here..
        getProcessor()->setParameterNotifyingHost(JuceDemoPluginAudioProcessor::bypassParam, (float)bypassButton->getToggleState());
        //[/UserButtonCode_bypassButton]
    }
    else if (buttonThatWasClicked == textButton)
    {
        //[UserButtonCode_textButton] -- add your button handler code here..
		/*textButton->setLookAndFeel(this->getLookAndFeel());
		gainSlider->setLookAndFeel(new 11CustomLookAndFeel());
		panSlider->setLookAndFeel(new SquareLookAndFeel());*/
        //[/UserButtonCode_textButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void JuceDemoPluginAudioProcessorEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == lafBox)
    {
        //[UserComboBoxCode_lafBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_lafBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
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
	if (pan > 0.5f){
		leftGain = 1 - ((pan-0.5f)*2);
	}
	if (pan < 0.5f){
		rightGain -= (0.5f-pan)*2;
	}
	//0 - 0.5 = left 100
	//0.5 - 1 = right 100
	dbString = amountToDb(leftGain);
	leftGainInfoLabel->setText(dbString,dontSendNotification);
	dbString = amountToDb(rightGain);
	rightGainInfoLabel->setText(dbString,dontSendNotification);
	bypassButton->setToggleState((bool)ourProcessor->m_fBypass, juce::sendNotification);
    bypassButtonImg->setToggleState((bool)ourProcessor->m_fBypass, juce::sendNotification);
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
  <BACKGROUND backgroundColour="ff808080">
    <IMAGE pos="316 84 51 13" resource="untitled1_png" opacity="1" mode="0"/>
  </BACKGROUND>
  <LABEL name="new label" id="8b8d009f45dc12c7" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="60 76 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="pan" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Aharoni" fontsize="12" bold="0"
         italic="0" justification="36"/>
  <LABEL name="" id="3084384ee25f6d12" memberName="infoLabel" virtualName=""
         explicitFocusOrder="0" pos="10 4 400 25" textCol="ff0000ff" edTextCol="ff000000"
         edBkgCol="0" labelText="aaa" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <SLIDER name="gainSlider" id="c31acc4ca22491a9" memberName="gainSlider"
          virtualName="" explicitFocusOrder="0" pos="10 30 70 70" tooltip="Gain"
          rotaryslideroutline="66000000" min="0" max="1" int="0" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="delay" id="37878e5e9fd60a08" memberName="delaySlider" virtualName=""
          explicitFocusOrder="0" pos="200 30 90 90" tooltip="Delay gain&#10;"
          min="0" max="1" int="0.10000000000000001" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="pan" id="324eec4d274919f3" memberName="panSlider" virtualName=""
          explicitFocusOrder="0" pos="100 30 70 70" tooltip="pan" min="0"
          max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <IMAGEBUTTON name="new button" id="b5ee6118cc15876e" memberName="bypassButtonImg"
               virtualName="" explicitFocusOrder="0" pos="312 24 60 60" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="onMaya_png" opacityNormal="1" colourNormal="ac4b4b"
               resourceOver="" opacityOver="1" colourOver="953434" resourceDown="offMaya_png"
               opacityDown="1" colourDown="8b3a3a"/>
  <TOGGLEBUTTON name="new toggle button" id="d59c4ede9f259185" memberName="bypassButton"
                virtualName="" explicitFocusOrder="0" pos="312 104 64 24" buttonText="bypass"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="new label" id="dde6ff72637f37e7" memberName="gainInfoLabel"
         virtualName="" explicitFocusOrder="0" pos="10 100 70 30" edTextCol="ff000000"
         edBkgCol="0" labelText="0.0&#10;dB&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="64ddab567eb77e3c" memberName="leftGainInfoLabel"
         virtualName="" explicitFocusOrder="0" pos="100 100 35 30" edTextCol="ff000000"
         edBkgCol="0" labelText="10.0 dB&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="b95fe3ac1ed884d0" memberName="rightGainInfoLabel"
         virtualName="" explicitFocusOrder="0" pos="133 100 35 30" edTextCol="ff000000"
         edBkgCol="0" labelText="10.0 dB&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Aharoni"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <COMBOBOX name="new combo box" id="43c60f5227b763f7" memberName="lafBox"
            virtualName="" explicitFocusOrder="0" pos="40 160 150 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TEXTBUTTON name="new button" id="8970f44e7a7ca0b" memberName="textButton"
              virtualName="" explicitFocusOrder="0" pos="224 152 150 104" buttonText="new button"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

// JUCER_RESOURCE: offMaya_png, 8150, "../../../Desktop/offMaya.png"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_offMaya_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,60,0,0,0,60,8,6,0,0,0,58,252,217,114,0,0,0,9,112,72,89,115,
0,0,11,19,0,0,11,19,1,0,154,156,24,0,0,0,4,103,65,77,65,0,0,177,142,124,251,81,147,0,0,0,32,99,72,82,77,0,0,122,37,0,0,128,131,0,0,249,255,0,0,128,233,0,0,117,48,0,0,234,96,0,0,58,152,0,0,23,111,146,95,
197,70,0,0,31,76,73,68,65,84,120,218,204,155,123,108,92,231,121,230,127,103,206,153,219,153,59,135,28,114,56,188,137,20,73,81,164,108,75,178,168,88,180,100,93,28,217,142,221,216,110,182,54,96,36,217,164,
216,110,11,20,69,129,110,235,100,219,205,110,22,216,117,83,167,13,208,46,186,40,10,108,119,219,34,192,54,23,196,80,236,166,150,47,178,117,151,69,137,34,41,241,38,138,28,94,70,195,33,103,134,115,191,159,
115,246,15,250,124,181,210,205,246,154,110,5,16,20,7,156,225,247,94,190,247,125,158,231,125,143,100,24,6,63,141,127,209,243,223,220,163,89,221,143,107,22,199,19,117,28,7,176,6,194,146,226,86,37,217,174,
40,138,221,34,73,96,232,186,174,233,85,205,104,84,203,122,45,157,80,180,226,164,181,94,248,208,106,169,92,232,60,242,171,83,63,141,115,73,255,148,6,47,126,240,218,145,138,228,249,183,117,165,249,116,67,
110,109,117,184,90,44,86,171,21,195,48,168,86,171,24,134,129,249,247,12,195,64,150,101,44,22,11,178,44,99,179,217,144,101,153,90,173,70,169,144,50,164,218,70,202,90,75,190,239,208,42,255,99,247,169,95,
61,251,47,202,224,185,247,126,251,151,138,52,253,74,197,218,51,228,246,181,73,22,139,133,74,165,66,185,92,166,90,173,82,175,215,197,151,166,105,232,186,14,32,140,85,20,5,187,221,142,162,40,56,28,14,156,
78,39,78,167,19,89,150,73,167,18,88,75,247,150,188,70,242,143,7,79,191,250,59,255,95,13,158,249,209,107,191,144,145,252,95,111,168,35,237,30,143,135,90,173,70,177,88,20,198,22,10,5,114,185,28,249,124,
158,114,185,76,163,209,216,249,163,146,36,162,12,32,203,50,170,170,226,118,187,241,122,189,120,60,30,156,78,39,14,135,3,151,203,133,170,170,148,74,37,234,217,59,41,57,19,251,214,99,47,125,237,181,127,
86,131,23,207,126,115,96,179,98,59,83,243,140,12,186,61,62,74,165,146,48,50,151,203,177,177,177,65,50,153,164,82,169,32,73,146,56,184,205,102,195,48,12,44,22,139,72,111,73,146,118,210,184,84,162,90,173,
162,235,58,118,187,157,166,166,38,218,218,218,240,249,124,168,170,42,28,146,78,167,105,108,78,172,245,4,75,63,55,240,233,175,93,251,169,27,60,245,151,223,122,45,161,183,254,186,59,216,107,109,52,26,226,
160,27,27,27,36,18,9,210,233,52,22,139,5,175,215,139,207,231,195,227,241,224,118,187,209,117,157,124,62,79,32,16,160,185,185,25,73,146,72,165,82,164,82,41,92,46,23,138,162,80,40,20,40,20,10,100,179,89,
178,217,44,154,166,9,195,67,161,16,78,167,19,183,219,141,205,102,35,157,184,167,135,228,149,63,217,255,204,87,126,225,167,98,240,242,185,111,88,54,114,214,115,25,219,222,99,129,64,128,66,161,64,173,86,
35,153,76,178,178,178,130,221,110,231,145,71,30,65,211,52,86,86,86,8,6,131,168,170,138,213,106,21,14,233,234,234,34,20,10,225,112,56,176,88,44,84,171,85,54,55,55,89,89,89,161,185,185,25,85,85,197,181,
216,222,222,38,18,137,96,179,217,184,125,251,54,165,82,137,174,174,46,154,154,154,112,56,28,120,189,94,178,217,44,246,226,212,116,167,95,58,182,235,248,175,101,254,201,12,94,185,240,122,104,57,229,188,
174,123,135,187,204,130,84,169,84,88,92,92,36,147,201,208,215,215,135,166,105,148,203,101,58,59,59,177,219,237,20,139,69,90,90,90,118,222,255,177,3,130,193,32,14,135,3,187,221,142,44,203,226,115,82,169,
20,155,155,155,236,218,181,11,93,215,73,165,82,216,237,118,52,77,99,109,109,13,155,205,134,211,233,100,113,113,17,85,85,25,24,24,16,215,4,160,154,156,78,119,121,75,99,131,79,254,198,220,63,218,224,232,
249,255,210,189,152,14,220,84,252,195,77,154,166,81,169,84,40,20,10,76,79,79,83,169,84,216,191,127,63,31,125,244,17,185,92,14,85,85,217,222,222,230,212,169,83,248,253,126,90,91,91,145,101,153,249,249,
121,236,118,59,86,171,85,84,100,128,122,189,78,173,86,163,86,171,81,175,215,25,24,24,64,215,117,54,54,54,200,231,243,188,243,206,59,248,124,62,42,149,10,14,135,131,163,71,143,50,49,49,129,162,40,140,140,
140,224,247,251,113,56,28,59,215,97,115,166,212,227,205,158,220,123,250,43,215,254,193,6,175,94,120,61,180,152,242,204,226,29,108,106,52,26,104,154,70,34,145,224,246,237,219,104,154,198,240,240,48,149,
74,133,107,215,174,241,249,207,127,30,159,207,199,15,127,248,67,242,249,60,39,79,158,20,233,59,57,57,9,64,54,155,165,80,40,80,169,84,144,101,25,187,221,142,203,229,194,227,241,96,177,88,216,183,111,31,
181,90,141,68,34,193,229,203,151,1,120,225,133,23,40,149,74,252,217,159,253,25,7,15,30,196,231,243,49,53,53,133,36,73,12,15,15,211,214,214,134,205,102,195,102,179,145,219,152,41,239,109,206,62,218,123,
242,43,51,63,201,38,229,39,166,241,7,175,91,150,183,157,55,12,239,64,83,227,227,254,25,139,197,152,158,158,198,225,112,208,209,209,33,238,167,97,24,84,42,21,12,195,160,209,104,96,177,88,196,231,56,28,
14,0,84,85,165,185,185,25,69,81,68,15,54,12,3,77,211,40,149,74,20,139,69,84,85,165,94,175,139,118,165,105,26,185,92,142,122,189,46,218,153,44,203,116,117,117,17,143,199,153,152,152,96,120,120,152,206,
206,78,116,93,199,213,50,232,92,76,207,94,178,188,247,123,125,61,167,254,93,250,239,101,240,253,172,114,174,226,236,239,176,124,12,20,98,177,24,19,19,19,168,170,74,36,18,161,173,173,141,205,205,77,34,
145,8,129,64,128,239,125,239,123,88,173,86,26,141,6,79,63,253,52,165,82,9,139,197,130,195,225,64,150,101,54,54,54,40,149,74,162,216,1,88,173,86,188,94,47,170,170,226,245,122,113,56,28,100,179,89,138,197,
34,135,14,29,226,173,183,222,226,59,223,249,14,181,90,13,183,219,77,87,87,23,107,107,107,132,195,97,100,89,102,117,117,149,169,169,29,4,218,221,221,189,227,20,111,191,127,97,115,226,114,15,236,249,59,
27,60,245,163,223,249,207,9,99,240,152,106,177,160,105,26,91,91,91,220,184,113,3,187,221,78,91,91,27,45,45,45,4,2,1,242,249,60,241,120,156,159,253,217,159,37,145,72,0,16,10,133,40,149,74,44,44,44,240,
208,67,15,1,16,8,4,72,36,18,28,56,112,0,155,205,38,192,134,89,0,39,39,39,241,122,189,0,120,189,94,82,169,20,61,61,61,124,241,139,95,100,99,99,3,139,197,66,56,28,102,102,102,6,155,205,70,83,83,19,186,174,
83,175,215,89,93,93,229,214,173,91,216,108,54,218,219,219,119,138,161,107,207,224,213,31,188,254,167,159,122,241,213,127,253,227,182,89,126,252,133,165,247,190,185,107,165,24,250,205,79,246,206,241,241,
113,97,76,48,24,196,227,241,32,73,18,125,125,125,100,179,89,110,222,188,73,75,75,11,29,29,29,108,109,109,113,253,250,117,122,123,123,113,56,28,232,186,78,111,111,47,245,122,157,139,23,47,18,139,197,168,
86,171,84,42,21,214,214,214,56,127,254,60,229,114,153,254,254,126,26,141,6,118,187,157,221,187,119,51,62,62,78,34,145,160,179,179,147,80,40,196,205,155,55,73,167,211,244,247,247,35,73,18,30,143,135,166,
166,38,66,161,16,146,36,113,243,230,77,50,153,12,141,70,3,151,203,197,134,30,249,194,221,119,126,231,241,191,181,104,93,248,193,31,204,23,157,3,3,230,125,188,124,249,50,241,120,156,174,174,46,58,58,58,
104,111,111,199,237,118,99,181,90,69,180,38,38,38,88,95,95,7,192,102,179,177,127,255,126,70,70,70,208,117,93,160,169,106,181,202,248,248,56,139,139,139,84,171,85,36,73,194,102,179,209,219,219,203,161,
67,135,80,85,149,70,163,33,238,233,220,220,28,227,227,227,84,42,21,0,218,219,219,57,112,224,128,232,223,141,70,131,66,161,192,198,198,6,107,107,107,172,174,174,18,10,133,24,27,27,195,106,181,238,100,80,
118,126,235,201,159,251,149,208,79,52,120,246,237,111,126,121,190,212,251,39,14,167,11,195,48,152,155,155,227,189,247,222,195,98,177,224,118,187,31,168,168,22,139,5,187,221,46,64,68,62,159,167,209,104,
136,94,107,22,31,73,146,4,156,180,90,173,148,203,101,1,57,205,247,155,24,219,98,177,80,171,213,48,12,3,171,213,74,165,82,33,155,205,162,40,10,110,183,91,20,71,179,80,106,154,70,161,80,160,88,44,146,207,
231,209,117,157,39,158,120,130,125,251,246,1,80,169,84,216,235,91,248,175,3,39,94,253,15,255,87,131,207,253,224,191,111,84,157,189,173,134,97,144,203,229,56,115,230,12,91,91,91,34,162,149,74,69,20,166,
67,135,14,113,237,218,53,98,177,24,187,119,239,166,187,187,27,155,205,134,162,40,200,178,140,36,73,34,194,230,151,201,146,204,191,105,146,136,31,255,125,93,215,31,32,24,230,93,189,119,239,30,161,80,136,
35,71,142,112,253,250,117,113,110,171,213,138,174,235,228,114,57,154,155,155,121,238,185,231,8,4,2,59,129,41,71,139,35,225,100,115,248,240,111,85,30,40,90,179,103,95,255,249,12,187,91,157,128,174,235,
76,77,77,81,44,22,9,133,66,28,60,120,144,133,133,5,6,7,7,185,125,251,54,63,243,51,63,67,40,20,98,126,126,158,225,225,97,78,156,56,129,207,231,163,94,175,139,202,108,30,248,147,7,255,228,107,159,116,180,
249,115,181,90,125,160,149,153,84,210,140,228,135,31,126,200,189,123,247,120,226,137,39,216,191,127,63,223,255,254,247,217,183,111,31,243,243,243,244,247,247,51,49,49,65,62,159,103,114,114,146,99,199,
142,33,73,18,5,35,228,202,20,51,191,21,134,175,61,16,225,203,103,126,127,54,107,29,216,35,73,18,155,155,155,156,57,115,134,166,166,38,34,145,8,170,170,138,52,84,20,133,167,158,122,138,111,127,251,219,
184,221,110,142,31,63,78,163,209,32,149,74,17,139,197,68,223,52,141,51,83,245,147,198,253,184,161,230,151,162,40,226,181,90,173,38,138,83,103,103,39,173,173,173,216,237,118,62,252,240,67,54,55,55,249,
210,151,190,196,123,239,189,71,161,80,192,106,181,34,73,18,146,36,177,188,188,204,246,246,54,159,249,204,103,8,135,195,24,134,129,179,190,180,117,252,179,191,28,18,17,94,122,231,119,15,37,106,237,131,
14,43,226,238,58,157,78,154,155,155,233,238,238,102,126,126,158,129,129,1,238,220,185,195,51,207,60,195,229,203,151,169,215,235,140,141,141,81,44,22,185,115,231,14,51,51,51,20,139,69,202,229,178,40,72,
186,174,211,104,52,168,84,42,104,154,38,12,210,52,77,68,93,211,52,81,168,188,94,47,94,175,23,77,211,168,86,171,228,114,57,170,213,42,62,159,143,3,7,14,240,232,163,143,114,228,200,17,206,156,57,195,197,
139,23,57,120,240,32,111,190,249,38,35,35,35,44,46,46,50,56,56,72,62,159,167,94,175,51,51,51,67,107,107,235,14,43,171,181,180,220,123,255,27,47,247,157,252,234,95,40,0,249,186,244,203,138,221,35,73,146,
68,54,155,37,26,141,50,52,52,132,44,203,200,178,140,203,229,66,146,36,130,193,32,146,36,49,61,61,205,216,216,24,0,183,110,221,98,122,122,154,182,182,54,246,237,219,135,207,231,19,119,222,98,177,136,187,
149,76,38,217,216,216,96,115,115,83,20,30,128,112,56,76,111,111,47,225,112,24,143,199,35,100,158,122,189,78,169,84,98,115,115,147,165,165,37,174,94,189,74,181,90,229,248,241,227,28,62,124,152,15,62,248,
128,161,161,33,66,161,16,186,174,11,10,106,242,231,169,169,41,178,217,44,126,191,31,187,67,37,91,113,253,27,96,199,224,108,195,249,148,172,200,24,134,193,218,218,26,146,36,209,222,222,46,250,101,115,115,
51,213,106,149,142,142,14,193,88,218,218,218,88,93,93,101,117,117,149,227,199,143,211,222,222,78,46,151,35,145,72,176,180,180,68,177,88,196,233,116,18,14,135,105,107,107,99,108,108,12,69,81,136,197,98,
220,190,125,27,128,253,251,247,179,103,207,30,106,181,26,139,139,139,220,189,123,87,56,196,227,241,208,220,220,76,79,79,15,195,195,195,196,98,49,46,92,184,64,123,123,59,67,67,67,168,170,202,252,252,60,
29,29,29,100,179,89,154,155,155,41,151,203,248,253,126,36,73,194,233,116,18,141,70,57,112,224,0,0,91,101,199,99,171,231,127,215,166,172,125,248,122,127,182,209,209,170,88,119,82,109,105,105,137,142,142,
14,20,69,193,102,179,81,46,151,241,122,189,108,111,111,227,245,122,153,153,153,161,179,179,19,128,187,119,239,10,230,115,238,220,57,238,223,191,143,195,225,16,45,164,92,46,179,186,186,138,174,235,236,
222,189,155,209,209,81,122,122,122,24,28,28,68,150,101,116,93,39,26,141,242,254,251,239,115,235,214,45,12,195,160,165,165,69,112,221,108,54,203,228,228,36,30,143,135,161,161,33,60,30,15,115,115,115,12,
12,12,208,221,221,205,218,218,26,157,157,157,100,179,89,92,46,23,153,76,6,143,199,67,165,82,161,179,179,147,229,229,101,246,237,219,135,44,203,148,12,159,171,209,72,62,166,212,235,210,81,205,162,74,86,
73,162,88,44,146,74,165,68,31,115,58,157,84,171,85,28,14,7,54,155,13,77,211,200,102,179,140,140,140,136,30,153,76,38,137,70,163,12,12,12,240,236,179,207,210,104,52,68,116,131,193,32,229,114,153,91,183,
110,49,59,59,43,122,174,89,133,171,213,42,179,179,179,92,187,118,141,190,190,62,78,159,62,141,219,237,102,107,107,139,124,62,143,199,227,193,102,179,49,53,53,197,219,111,191,77,165,82,33,20,10,81,46,151,
105,109,109,101,126,126,158,106,181,138,205,102,195,110,183,99,179,217,112,56,28,84,171,85,122,123,123,153,157,157,21,42,139,98,115,82,173,41,159,86,106,186,245,164,201,96,50,153,12,154,166,17,14,135,
41,22,139,88,173,86,193,97,29,14,7,229,114,153,90,173,134,170,170,104,154,70,189,94,71,215,117,70,71,71,57,112,224,128,224,197,187,119,239,230,242,229,203,56,28,14,250,250,250,8,6,131,172,173,173,177,
188,188,76,95,95,159,104,73,141,70,131,165,165,37,100,89,38,20,10,177,182,182,198,237,219,183,169,213,106,28,62,124,88,56,233,137,39,158,160,169,169,137,179,103,207,10,229,211,229,114,9,166,229,112,56,
196,89,77,21,52,16,8,0,144,74,165,8,4,2,59,81,214,172,167,148,92,85,62,32,43,242,78,158,111,109,225,116,58,241,251,253,148,203,101,100,89,22,197,199,102,179,145,203,229,118,24,135,162,8,93,217,108,99,
223,251,222,247,88,94,94,230,244,233,211,28,58,116,72,220,213,68,34,129,213,106,69,211,52,172,86,43,219,219,219,180,180,180,96,24,6,233,116,26,155,205,134,197,98,97,98,98,2,83,35,27,29,29,229,240,225,
195,92,186,116,137,119,223,125,151,133,133,5,130,193,32,138,162,160,40,138,144,119,1,202,229,178,0,25,230,89,101,89,22,10,104,42,149,98,247,238,221,236,20,103,251,110,75,85,114,133,77,148,147,205,102,
241,120,60,34,245,204,215,249,24,140,84,42,21,241,179,205,102,195,227,241,136,247,153,14,90,95,95,103,97,97,129,88,44,70,40,20,226,228,201,147,120,60,30,26,141,6,30,143,135,98,177,136,166,105,24,134,65,
177,88,196,227,241,8,70,245,185,207,125,142,129,129,1,226,241,56,115,115,115,196,227,113,44,31,51,182,92,46,135,166,105,34,205,205,222,109,158,233,147,42,168,166,105,56,28,14,252,126,63,219,219,219,127,
253,186,228,112,41,21,77,118,162,32,14,224,118,187,81,20,133,70,163,33,96,157,217,47,77,213,67,215,117,100,89,166,173,173,141,181,181,53,142,31,63,78,111,111,47,75,75,75,44,46,46,114,251,246,109,65,32,
22,22,22,72,167,211,184,92,46,33,233,152,61,184,209,104,80,171,213,240,249,124,108,111,111,163,235,58,95,248,194,23,184,125,251,54,115,115,115,216,237,118,158,127,254,121,6,6,6,88,93,93,229,187,223,253,
46,145,72,4,89,150,105,52,26,212,235,117,113,38,243,138,152,223,21,69,193,229,114,145,72,36,4,6,208,80,20,165,97,88,21,233,19,17,52,83,231,199,241,175,9,16,42,149,138,184,187,189,189,189,44,44,44,240,
195,31,254,144,131,7,15,50,52,52,196,201,147,39,69,170,125,244,209,71,140,143,143,11,32,146,203,229,104,109,109,197,48,12,236,118,59,170,170,146,201,100,112,187,221,148,74,37,222,122,235,45,81,52,247,
238,221,75,169,84,162,84,42,113,233,210,37,174,95,191,78,48,24,100,223,190,125,2,110,214,106,53,241,127,211,129,38,216,49,187,140,121,231,21,69,65,51,100,89,209,13,139,197,242,177,97,102,106,124,210,131,
181,90,77,20,40,211,144,98,177,40,20,138,163,71,143,242,206,59,239,240,206,59,239,112,245,234,85,124,62,31,138,162,144,207,231,201,231,243,40,138,130,215,235,21,34,123,115,115,51,30,143,71,20,22,147,234,
57,157,78,74,165,18,231,207,159,231,198,141,27,248,124,62,100,89,38,155,205,146,74,165,104,111,111,231,153,103,158,193,237,118,11,106,88,40,20,176,88,44,34,210,181,90,77,68,220,132,179,102,212,1,12,44,
146,2,127,205,92,204,8,154,17,49,223,104,126,55,85,138,233,233,105,156,78,39,118,187,157,150,150,22,190,252,229,47,51,62,62,206,236,236,44,169,84,74,120,88,85,85,225,36,77,211,216,187,119,47,221,221,221,
226,128,161,80,136,238,238,110,166,166,166,30,248,252,70,163,33,88,90,32,16,224,208,161,67,28,60,120,16,85,85,201,229,114,20,10,5,102,103,103,69,166,200,178,44,210,218,172,47,178,44,11,222,253,73,2,163,
128,102,0,146,73,235,50,153,12,146,36,17,137,68,72,167,211,180,180,180,96,179,217,112,187,221,15,180,172,143,62,250,72,40,14,125,125,125,60,249,228,147,140,141,141,145,201,100,200,102,179,228,114,57,166,
166,166,136,199,227,200,178,204,238,221,187,121,250,233,167,197,33,76,17,239,169,167,158,194,98,177,112,235,214,45,74,165,18,29,29,29,124,234,83,159,194,231,243,97,181,90,105,110,110,166,169,169,137,76,
38,195,202,202,10,177,88,140,68,34,65,185,92,166,163,163,3,135,195,129,170,170,216,237,118,194,225,48,245,122,157,246,246,118,44,22,11,185,92,78,208,213,29,139,117,67,177,89,180,70,221,48,108,102,68,226,
241,56,11,11,11,216,237,118,33,211,152,28,120,109,109,141,120,60,46,14,188,186,186,202,236,236,44,151,46,93,66,85,85,92,46,151,200,136,237,237,109,146,201,36,46,151,139,158,158,30,198,198,198,208,117,
157,100,50,73,36,18,193,98,177,176,190,190,78,91,91,27,39,78,156,64,81,20,81,153,47,93,186,36,38,12,22,139,133,82,169,68,185,92,166,94,175,11,195,76,17,190,173,173,141,72,36,34,34,109,78,57,230,230,230,
216,218,218,34,24,12,34,203,59,176,89,150,116,93,177,75,90,185,102,24,54,139,197,130,207,231,35,26,141,82,173,86,113,187,221,92,186,116,137,116,122,71,237,108,110,110,102,120,120,152,3,7,14,48,55,55,135,
215,235,101,239,222,189,76,79,79,179,176,176,192,242,242,178,96,69,38,105,48,163,211,209,209,65,165,82,33,153,76,34,73,18,91,91,91,226,126,173,174,174,226,245,122,233,232,232,160,88,44,162,235,58,43,43,
43,172,175,175,11,199,154,145,30,26,26,98,100,100,132,205,205,77,182,183,183,25,24,24,192,233,116,114,249,242,101,146,201,36,154,166,17,12,6,25,30,30,22,44,205,156,91,213,106,53,20,234,13,249,23,95,57,
253,243,101,201,31,180,217,108,164,211,105,84,85,101,104,104,136,11,23,46,112,255,254,125,188,94,47,54,155,141,245,245,117,162,209,168,184,131,178,44,243,240,195,15,115,240,224,65,81,181,77,25,200,108,
252,61,61,61,200,178,76,107,107,43,154,166,113,243,230,77,12,195,16,250,243,221,187,119,137,197,98,248,253,126,12,195,32,153,76,18,8,4,208,117,29,135,195,65,40,20,34,16,8,208,214,214,198,129,3,7,248,220,
231,62,71,56,28,102,125,125,29,139,197,66,32,16,224,252,249,243,108,108,108,224,245,122,145,101,153,181,181,53,214,215,215,217,179,103,143,32,33,157,157,157,59,2,161,150,206,42,30,91,125,114,171,166,247,
155,17,177,90,173,20,139,69,18,137,4,131,131,131,12,14,14,98,24,6,137,68,130,43,87,174,176,189,189,141,211,233,36,30,143,115,237,218,53,34,145,8,161,80,136,84,42,197,198,198,134,200,142,135,30,122,136,
90,173,198,246,246,54,241,120,156,90,173,198,194,194,2,249,124,158,190,190,62,28,14,135,184,34,138,162,224,116,58,145,36,137,64,32,64,56,28,230,206,157,59,130,11,55,53,53,17,12,6,153,153,153,33,145,72,
144,72,36,136,68,34,100,179,89,54,55,55,57,116,232,16,161,80,8,171,213,202,252,252,60,119,238,220,33,151,203,17,14,135,133,114,170,235,58,30,135,30,85,172,232,231,116,93,255,87,154,166,225,247,251,201,
231,243,88,173,86,220,110,183,24,92,229,243,121,102,102,102,196,193,138,197,34,146,36,17,143,199,137,70,163,24,134,65,42,149,226,254,253,251,168,170,42,148,195,100,50,137,213,106,101,110,110,142,116,58,
45,70,164,119,238,220,193,110,183,139,145,232,244,244,52,77,77,77,236,218,181,75,136,123,7,14,28,224,202,149,43,196,98,49,26,141,6,213,106,85,108,9,152,53,197,204,38,179,119,7,131,65,238,223,191,47,102,
209,128,208,176,13,195,192,162,21,63,80,236,74,227,60,141,146,161,235,54,201,231,243,49,55,55,71,173,86,99,116,116,20,187,221,46,128,135,195,225,224,200,145,35,56,28,14,54,55,55,177,219,237,84,171,85,
238,223,191,79,62,159,71,211,52,58,59,59,217,179,103,143,152,13,183,182,182,82,44,22,25,30,30,166,90,173,146,205,102,25,31,31,231,226,197,139,152,14,126,242,201,39,197,12,216,196,218,38,144,24,27,27,35,
26,141,178,177,177,65,52,26,165,165,165,69,20,168,124,62,79,48,24,100,108,108,140,173,173,45,1,131,91,91,91,113,185,118,84,215,108,54,203,208,208,208,206,218,69,173,130,203,43,159,85,186,79,189,122,123,
249,204,31,165,139,186,55,104,181,90,241,120,60,220,184,113,131,145,145,17,92,46,151,240,78,36,18,193,235,245,178,190,190,46,122,116,185,92,102,125,125,157,225,225,97,70,71,71,145,101,153,205,205,77,238,
221,187,71,163,209,16,94,118,187,221,116,118,118,226,247,251,105,106,106,226,238,221,187,212,235,117,14,29,58,68,91,91,27,139,139,139,204,206,206,10,80,227,114,185,176,219,237,184,221,110,14,31,62,76,
173,86,227,198,141,27,204,204,204,160,170,42,29,29,29,216,108,54,182,182,182,132,3,76,84,232,118,187,41,20,10,220,184,113,131,64,32,32,212,86,39,217,138,211,166,95,84,0,130,214,202,123,249,134,254,82,
173,86,163,175,175,143,107,215,118,38,142,159,249,204,103,4,242,170,213,106,188,249,230,155,180,180,180,176,103,207,30,10,133,2,165,82,137,112,56,204,227,143,63,206,202,202,10,87,174,92,161,88,44,82,173,
86,133,118,109,194,82,175,215,75,48,24,100,104,104,136,238,238,110,33,252,221,184,113,131,133,133,5,138,197,162,192,236,166,168,96,238,126,60,242,200,35,156,60,121,82,140,106,109,54,27,94,175,151,187,
119,239,50,49,49,33,156,109,102,226,220,220,28,139,139,139,188,242,202,43,2,126,182,90,139,55,186,158,248,245,146,2,224,146,107,127,92,47,22,95,170,41,10,193,96,144,158,158,30,209,18,4,44,251,184,112,
1,12,15,15,139,234,107,138,102,247,238,221,35,30,143,11,4,102,194,83,147,105,229,114,57,82,169,20,209,104,84,224,93,51,123,172,86,171,224,216,38,38,54,191,87,42,21,86,86,86,24,25,25,17,132,197,188,199,
166,78,102,226,124,211,73,86,171,149,238,238,110,218,218,218,196,174,137,215,93,255,83,161,90,246,158,126,245,189,251,103,254,48,154,213,61,61,213,106,149,135,31,126,152,213,213,213,7,118,170,76,145,96,
126,126,158,253,251,247,163,170,42,221,221,221,220,187,119,143,165,165,37,134,134,134,216,218,218,34,155,205,10,153,213,36,32,35,35,35,12,12,12,144,76,38,197,26,68,163,209,192,231,243,145,74,165,40,151,
203,100,50,25,38,39,39,31,112,116,163,209,160,173,173,141,83,167,78,177,188,188,12,64,95,95,31,141,70,131,76,38,195,252,252,60,110,183,91,164,180,121,86,191,223,79,127,127,191,136,174,223,146,204,216,
237,198,255,124,64,136,111,114,148,255,96,179,80,253,86,169,84,162,189,189,93,128,128,79,174,22,21,139,69,210,233,52,51,51,51,28,61,122,148,90,173,70,127,127,63,147,147,147,236,221,187,151,231,158,123,
142,241,241,113,214,214,214,4,227,170,213,106,120,60,30,124,62,31,78,167,147,206,206,78,129,198,90,90,90,72,38,147,44,46,46,210,104,52,80,85,21,195,48,68,43,233,233,233,225,244,233,211,36,18,9,174,95,
191,206,167,63,253,105,17,193,201,201,73,177,64,99,177,88,30,208,184,3,129,0,93,93,93,228,243,121,106,181,26,29,142,194,159,247,156,248,141,198,3,6,187,109,141,223,247,147,248,90,69,235,14,20,139,69,108,
54,155,240,182,249,129,186,174,99,177,88,152,156,156,100,100,100,4,85,85,233,234,234,66,211,52,174,94,189,74,169,84,226,240,225,195,140,142,142,138,195,199,98,49,54,55,55,73,36,18,120,189,94,65,5,77,146,
80,40,20,168,215,235,56,157,78,158,127,254,121,108,54,27,173,173,173,130,76,76,79,79,115,225,194,5,30,123,236,49,34,145,8,91,91,91,228,114,57,38,39,39,133,227,76,177,223,204,12,135,195,65,161,80,216,33,
23,141,205,138,207,163,253,199,191,49,31,238,58,254,85,189,240,163,215,94,155,175,180,125,179,209,104,60,80,49,235,245,58,219,219,219,226,67,82,169,20,31,126,248,33,159,253,236,103,177,219,237,28,61,122,
20,93,215,185,114,229,10,203,203,203,132,195,97,113,247,77,13,204,36,35,153,76,70,24,148,72,36,136,197,98,180,180,180,16,143,199,137,197,98,216,237,118,17,173,205,205,77,146,201,36,71,142,28,225,200,145,
35,108,108,108,32,203,50,231,207,159,39,153,76,162,40,10,165,82,137,116,58,77,173,86,19,89,104,6,12,160,75,45,252,175,158,39,191,146,249,137,227,210,243,63,248,195,245,130,125,87,164,90,173,162,40,10,
11,11,11,44,45,45,177,180,180,68,48,24,228,225,135,31,102,113,113,145,169,169,41,30,123,236,49,142,29,59,38,128,254,133,11,23,184,114,229,10,201,100,82,104,95,186,174,211,217,217,201,11,47,188,32,36,27,
19,74,230,114,57,26,141,6,145,72,132,55,223,124,83,8,122,102,209,106,106,106,98,108,108,140,99,199,142,145,203,229,216,222,222,230,226,197,139,92,189,122,149,125,251,246,137,89,87,60,30,103,215,174,93,
244,245,245,49,56,56,40,148,81,185,24,205,237,105,46,5,187,79,252,186,32,197,242,215,191,254,245,7,12,214,98,31,158,139,231,228,95,112,184,124,82,123,123,59,118,187,157,139,23,47,146,74,165,56,125,250,
52,163,163,163,60,252,240,195,88,173,86,222,125,247,93,49,112,115,187,221,12,12,12,16,12,6,209,117,93,16,123,147,107,155,128,196,212,178,235,245,58,107,107,107,98,229,105,98,98,66,232,98,46,151,139,129,
129,1,241,247,10,133,2,91,91,91,188,255,254,251,92,189,122,149,103,158,121,134,23,95,124,145,158,158,30,20,69,225,198,141,27,232,186,206,147,79,62,73,119,119,55,149,74,133,82,97,155,161,166,173,87,122,
79,189,122,231,147,246,253,13,131,3,189,99,27,229,232,217,246,173,138,231,81,179,40,53,53,53,9,13,184,187,187,27,171,213,74,127,127,63,165,82,137,11,23,46,176,177,177,129,221,110,199,235,245,210,221,221,
45,164,89,151,203,37,118,60,218,219,219,137,68,34,104,154,198,248,248,56,177,88,140,189,123,247,210,217,217,201,230,230,38,27,27,27,180,180,180,208,223,223,47,50,167,163,163,131,84,42,197,236,236,44,239,
190,251,46,19,19,19,28,59,118,140,23,94,120,1,195,48,200,100,50,92,188,120,145,114,185,204,75,47,189,196,35,143,60,194,218,218,218,14,87,182,175,252,229,67,207,124,229,107,127,231,181,165,203,103,254,
219,244,150,209,53,226,118,187,217,181,107,23,231,206,157,227,187,223,253,46,35,35,35,28,63,126,28,191,223,143,213,106,229,141,55,222,224,236,217,179,56,28,14,134,135,135,121,244,209,71,25,28,28,36,24,
12,82,173,86,73,167,211,68,163,81,52,77,19,27,4,102,117,109,106,106,226,254,253,251,172,172,172,32,203,50,61,61,61,52,53,53,137,30,187,184,184,40,102,87,229,114,153,19,39,78,240,242,203,47,83,175,215,
201,100,50,156,63,127,158,91,183,110,241,194,11,47,112,250,244,105,162,209,40,249,124,30,175,182,18,223,221,82,232,232,60,250,155,250,223,121,139,167,205,93,29,43,102,238,71,203,229,206,128,169,76,2,188,
241,198,27,104,154,38,230,73,175,188,242,10,29,29,29,188,253,246,219,92,191,126,157,219,183,111,19,137,68,232,235,235,163,167,167,135,64,32,128,221,110,103,123,123,155,98,177,40,20,9,83,247,50,183,108,
85,85,37,157,78,179,184,184,200,202,202,10,203,203,203,196,98,49,202,229,50,145,72,132,151,94,122,137,147,39,79,82,171,213,136,199,227,92,184,112,129,217,217,89,158,127,254,121,158,122,234,41,214,215,
215,119,134,7,213,120,121,176,163,56,214,126,228,111,26,251,183,46,166,45,190,243,219,123,22,210,129,27,154,26,81,253,126,63,157,157,157,92,189,122,149,239,127,255,251,120,189,94,142,31,63,206,192,192,
0,77,77,77,108,109,109,113,245,234,85,110,222,188,73,52,26,21,147,11,19,121,245,246,246,114,236,216,49,58,59,59,133,112,110,78,42,47,95,190,44,72,139,233,0,167,211,73,119,119,55,251,247,239,231,177,199,
30,163,181,181,149,108,54,203,194,194,2,31,124,240,1,169,84,138,23,95,124,145,199,31,127,156,245,245,117,210,233,52,70,101,179,49,210,150,56,221,119,236,183,206,253,131,87,15,231,255,242,183,15,47,22,
252,231,234,182,176,211,239,247,179,107,215,46,238,222,189,203,119,190,243,29,82,169,20,143,62,250,40,7,15,30,36,28,14,227,116,58,41,20,10,220,187,119,143,133,133,5,214,214,214,72,165,82,100,50,25,156,
78,39,207,61,247,28,145,72,132,174,174,46,20,69,33,26,141,178,186,186,202,217,179,103,197,104,51,24,12,210,217,217,73,127,127,63,125,125,125,120,189,94,42,149,10,27,27,27,220,188,121,147,235,215,175,227,
241,120,120,249,229,151,25,26,26,34,26,141,146,201,100,160,146,168,15,182,220,127,105,240,196,127,122,227,31,189,92,186,244,254,55,70,238,87,90,207,39,107,129,128,169,100,84,42,21,126,244,163,31,113,229,
202,21,188,94,47,7,15,30,100,112,112,144,150,150,22,193,83,63,185,25,155,72,36,200,102,179,56,157,78,30,122,232,33,100,89,102,114,114,146,82,169,132,203,229,34,28,14,227,243,249,240,122,189,98,52,83,42,
149,72,38,147,44,44,44,112,243,230,77,182,183,183,25,29,29,229,217,103,159,69,85,85,113,103,29,90,162,220,223,146,124,246,255,21,217,191,247,250,112,250,206,31,55,205,220,45,94,138,215,59,246,184,221,
110,194,225,48,193,96,144,249,249,121,222,126,251,109,238,222,189,139,215,235,101,112,112,144,190,190,62,66,161,16,170,170,138,177,72,189,94,231,206,157,59,66,211,6,196,66,234,158,61,123,112,58,157,226,
247,76,67,151,150,150,152,155,155,19,27,187,79,63,253,52,123,247,238,101,123,123,155,245,245,117,74,165,18,65,75,236,254,64,107,229,120,251,145,87,239,254,84,22,196,111,190,245,123,127,30,45,4,95,81,156,
77,22,175,215,43,176,241,157,59,119,184,124,249,50,11,11,11,59,128,221,239,167,163,163,67,8,239,110,183,91,76,39,147,201,36,134,97,208,220,220,140,44,203,248,253,126,74,165,146,96,84,235,235,235,66,46,
238,239,239,231,200,145,35,140,140,140,96,24,6,235,235,235,228,114,57,202,249,180,177,219,187,245,87,237,254,250,115,173,99,95,213,127,170,143,0,44,188,253,205,83,107,121,231,183,183,105,107,85,85,85,
8,109,118,187,157,149,149,21,166,166,166,152,153,153,33,22,139,81,42,149,196,168,67,215,117,118,237,218,197,232,232,40,146,36,137,69,53,19,19,75,146,132,203,229,18,83,254,135,30,122,136,93,187,118,81,
175,215,137,199,227,164,211,233,157,43,96,108,100,118,249,106,191,180,231,244,175,253,197,63,235,67,30,83,111,253,222,235,27,101,245,23,179,70,179,87,85,85,124,62,31,45,45,45,184,221,110,234,245,186,16,
246,204,199,3,178,217,44,213,106,149,150,150,22,49,102,181,219,237,226,125,225,112,152,246,246,118,49,223,202,231,243,162,232,149,74,37,84,35,85,14,171,249,111,251,92,141,95,236,59,241,239,245,127,200,
153,255,209,143,241,172,189,255,13,75,190,194,107,91,85,215,151,226,149,96,171,195,249,215,15,100,120,60,30,33,215,152,132,192,124,156,199,48,12,177,200,102,146,119,179,200,229,243,121,161,168,20,139,
69,90,237,153,237,86,87,241,127,171,54,227,171,189,39,95,205,253,203,121,80,235,157,111,125,62,215,144,191,24,207,42,71,138,248,92,178,213,249,192,58,130,57,208,54,247,59,76,85,195,92,83,50,159,113,170,
85,75,184,200,86,34,30,109,220,175,86,191,221,123,242,55,254,232,95,228,147,105,15,60,188,245,87,223,56,85,110,200,39,170,85,229,68,166,70,127,67,178,187,117,201,174,232,200,50,146,69,210,117,3,139,5,
67,166,161,91,180,122,93,166,90,242,90,27,75,30,171,113,222,106,227,125,155,92,123,191,247,244,111,86,254,169,207,245,127,6,0,251,138,198,114,9,5,28,203,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* JuceDemoPluginAudioProcessorEditor::offMaya_png = (const char*) resource_JuceDemoPluginAudioProcessorEditor_offMaya_png;
const int JuceDemoPluginAudioProcessorEditor::offMaya_pngSize = 8150;

// JUCER_RESOURCE: onMaya_png, 9515, "../../../Desktop/onMaya.png"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_onMaya_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,60,0,0,0,60,8,6,0,0,0,58,252,217,114,0,0,0,9,112,72,89,115,0,
0,11,19,0,0,11,19,1,0,154,156,24,0,0,0,4,103,65,77,65,0,0,177,142,124,251,81,147,0,0,0,32,99,72,82,77,0,0,122,37,0,0,128,131,0,0,249,255,0,0,128,233,0,0,117,48,0,0,234,96,0,0,58,152,0,0,23,111,146,95,
197,70,0,0,36,161,73,68,65,84,120,218,196,187,121,172,159,87,122,223,247,57,231,188,219,111,223,238,190,240,242,242,146,151,187,68,81,18,41,137,212,230,161,52,146,53,154,145,103,60,182,51,181,221,241,
116,98,4,8,144,4,65,250,71,209,36,104,129,166,109,10,164,64,139,2,45,80,163,65,82,167,169,99,119,102,60,139,103,36,141,22,107,180,144,18,119,82,228,37,121,47,121,121,247,237,183,47,239,239,221,206,233,
31,84,166,25,215,51,182,147,52,61,47,190,255,191,159,115,158,247,193,243,188,207,247,136,143,254,113,145,159,191,4,82,6,36,137,67,208,7,17,89,40,145,2,98,36,62,113,20,227,102,4,177,173,177,140,77,172,
98,18,35,113,18,192,74,13,170,194,224,76,166,144,125,200,205,168,227,78,113,114,214,202,228,135,61,149,43,88,169,216,211,74,160,35,47,240,163,176,21,245,216,10,26,247,230,163,122,231,82,92,221,186,18,
135,205,59,221,168,181,33,34,133,109,210,24,29,225,136,30,125,165,89,190,27,99,197,9,131,147,6,203,77,17,105,129,20,105,98,109,136,227,62,121,207,194,82,2,243,115,136,44,254,61,44,99,12,73,172,49,194,
76,165,43,197,51,3,195,67,95,200,13,101,79,165,202,197,65,203,17,216,113,136,238,111,1,75,104,45,49,65,140,33,66,74,143,188,149,26,139,43,217,3,140,21,159,49,214,8,198,159,164,83,239,214,219,155,181,115,
237,251,155,223,239,85,219,111,38,113,114,219,88,230,223,199,171,254,187,1,27,3,58,210,72,87,157,42,143,86,126,171,50,93,252,245,220,112,185,40,132,5,221,54,114,227,22,116,251,248,161,196,143,36,73,24,
65,228,96,34,133,145,26,33,187,40,165,176,237,8,47,21,18,167,37,38,147,35,151,78,151,138,179,197,151,244,193,195,47,53,214,91,189,230,173,149,255,171,179,190,252,191,39,113,248,166,209,230,255,31,96,157,
24,148,205,147,3,123,188,255,116,120,182,252,43,169,82,138,196,15,144,203,75,152,142,160,237,91,248,205,152,102,93,208,236,68,180,250,9,113,20,163,76,15,37,67,140,136,73,140,133,22,2,71,10,178,94,154,
98,214,38,95,236,144,45,196,216,217,54,42,55,79,177,228,165,203,167,202,191,213,235,20,127,107,125,110,245,205,237,245,141,127,18,183,227,215,49,226,63,12,176,209,160,13,3,3,131,233,255,102,244,120,238,
235,222,128,178,236,29,131,185,219,37,110,103,168,53,97,109,163,198,214,78,143,158,111,64,74,178,46,20,50,10,39,227,18,227,144,88,30,194,196,200,68,162,176,233,198,33,27,253,46,43,141,8,121,79,147,114,
45,6,202,89,70,199,50,20,203,33,86,126,19,183,96,179,239,120,234,133,193,241,169,23,22,222,175,255,171,78,111,243,239,41,109,150,225,175,6,46,254,42,73,203,4,10,199,78,125,105,228,96,234,159,76,204,168,
25,187,39,232,117,36,161,47,216,90,237,178,190,106,216,170,119,145,86,68,37,231,80,42,120,228,242,22,153,92,154,68,11,186,173,54,233,17,69,122,210,160,132,166,187,26,209,94,19,228,50,25,132,3,237,78,159,
86,91,210,172,119,105,52,3,162,68,81,41,103,152,28,113,25,27,118,177,243,49,106,208,7,55,199,250,124,119,125,109,174,254,159,245,67,254,153,101,101,254,210,73,75,125,243,5,239,23,2,11,145,96,140,34,12,
180,72,167,82,255,229,254,199,179,255,243,224,164,91,54,85,131,110,42,170,107,9,183,230,54,105,105,139,233,211,207,48,53,59,66,78,214,217,189,39,195,208,88,145,202,0,40,25,81,173,119,24,158,77,51,180,
79,226,141,118,112,6,18,242,229,20,158,227,82,219,110,82,204,187,12,15,65,177,144,167,84,200,144,206,194,254,19,7,41,239,155,97,125,105,155,213,229,22,150,76,147,74,44,136,34,42,99,153,92,102,208,123,
173,85,11,7,227,64,188,109,132,136,181,142,113,45,137,148,63,255,212,255,66,96,68,66,28,137,76,177,88,248,231,7,31,25,250,155,25,183,3,59,49,65,51,199,213,185,54,75,171,109,246,76,141,147,179,179,84,215,
239,147,47,52,24,30,80,196,81,151,236,144,70,58,49,155,107,29,6,70,74,228,70,52,194,139,49,174,4,37,49,33,120,18,28,178,212,118,122,20,199,4,150,27,16,250,49,165,74,154,196,52,89,189,189,78,197,202,49,
86,73,113,103,190,74,181,38,25,76,123,200,174,196,201,42,134,38,178,39,186,237,248,137,78,59,254,17,36,189,191,8,216,250,139,147,147,46,150,202,238,31,238,155,29,56,99,146,30,122,39,67,171,105,113,246,
230,61,162,110,159,199,142,31,228,157,115,155,84,219,1,110,206,163,251,126,131,87,95,152,166,52,160,48,233,42,90,186,196,90,210,110,250,116,2,3,174,133,201,216,24,21,33,124,3,93,131,232,72,52,14,73,166,
131,72,18,140,116,216,89,207,242,173,55,86,200,21,11,244,131,53,114,46,188,248,204,46,46,159,191,205,7,103,225,225,135,7,41,227,98,229,3,14,29,45,156,153,179,90,63,90,93,10,94,3,150,127,17,143,250,230,
11,169,7,39,249,103,101,32,73,116,166,84,44,125,107,102,111,249,12,81,11,225,43,54,214,37,31,92,93,161,27,192,163,7,199,105,182,67,174,207,55,248,198,215,143,114,234,137,9,106,235,1,139,139,77,246,205,
230,176,6,235,168,172,100,123,73,162,3,143,165,29,205,226,253,144,249,249,14,75,43,49,181,77,69,220,85,120,50,36,177,122,148,102,123,36,137,69,84,43,114,246,147,58,217,66,153,223,250,205,67,60,124,160,
204,71,231,86,201,151,97,118,116,144,59,235,125,22,183,106,148,172,18,89,39,131,82,59,12,140,230,71,131,190,243,92,191,219,251,182,165,100,87,240,231,63,86,220,183,126,222,201,138,66,49,251,79,103,166,
7,206,16,116,208,65,129,165,229,62,231,175,45,227,166,225,208,120,5,229,216,152,64,99,37,22,73,39,34,142,54,33,208,72,165,193,8,98,161,240,114,49,177,148,20,210,41,14,142,56,72,219,16,171,16,99,107,172,
200,69,132,18,211,110,80,13,12,170,0,97,24,130,49,40,18,226,40,68,239,212,32,138,177,180,65,1,202,138,216,55,149,101,113,35,230,163,203,43,60,164,43,236,153,202,99,69,154,131,7,156,71,238,124,154,249,
131,157,13,255,151,133,212,254,159,23,216,86,28,255,57,176,218,144,74,59,255,197,238,189,67,95,149,113,7,21,40,230,151,34,62,188,178,66,38,157,102,122,44,205,174,17,143,213,173,22,35,187,6,40,87,4,191,
255,7,87,113,29,65,16,9,190,248,197,221,248,221,30,182,45,144,185,8,227,90,108,45,213,104,222,77,104,180,20,97,20,0,96,219,14,197,188,100,192,75,16,35,18,114,22,81,45,164,223,109,241,228,19,3,252,159,
223,95,230,247,254,160,77,220,215,100,10,176,103,114,144,205,197,13,118,141,89,40,149,229,222,253,46,151,47,45,35,204,46,102,118,103,80,162,205,212,190,193,231,170,213,165,255,113,101,165,246,215,165,
252,115,128,165,21,255,191,170,39,203,226,11,251,246,142,254,195,148,232,147,68,54,43,219,240,193,165,5,108,207,101,124,36,207,208,96,154,220,96,140,219,177,217,94,110,243,149,175,205,114,99,59,71,68,
158,125,67,85,236,198,14,215,230,155,156,40,26,16,9,217,161,152,245,5,151,199,30,43,17,229,35,124,39,196,178,124,82,218,131,70,154,235,31,215,25,24,232,34,68,135,76,41,195,245,134,225,192,68,138,223,249,
235,71,184,181,49,138,148,112,96,116,155,133,203,171,56,158,162,48,36,9,117,129,32,180,89,92,130,143,46,111,96,185,99,76,79,56,184,86,200,225,163,187,190,25,132,242,92,24,68,191,39,254,76,2,83,223,120,
166,128,48,234,167,50,137,40,77,238,202,124,119,96,208,42,218,125,65,163,45,120,251,236,38,58,78,152,26,115,25,29,206,80,25,140,81,169,46,229,17,139,91,183,58,84,55,186,236,223,51,204,120,33,77,107,121,
155,11,87,22,153,60,105,51,180,183,141,49,17,217,98,154,235,151,125,54,62,237,226,166,34,92,47,68,70,154,218,162,226,226,135,117,218,78,192,241,87,250,216,170,143,114,19,98,237,113,229,109,159,178,39,
153,216,237,146,77,73,110,124,178,64,179,221,228,225,39,44,164,137,81,210,67,16,18,107,77,163,21,177,190,209,98,108,168,68,218,74,112,51,26,199,115,159,238,118,122,127,224,185,178,225,56,2,247,51,169,
111,62,155,65,2,18,32,49,20,114,217,255,105,247,84,254,249,36,137,137,130,12,31,158,91,97,99,11,166,71,203,140,143,165,24,25,29,36,83,0,203,45,160,10,17,19,135,211,172,215,20,183,46,222,231,254,237,37,
54,58,61,246,255,82,154,125,167,1,161,17,194,66,185,14,51,135,243,212,53,220,185,1,203,215,19,150,238,8,182,26,154,137,35,46,167,127,213,198,173,132,16,103,64,218,148,166,67,156,76,145,171,151,99,150,
174,221,103,121,97,155,236,144,226,244,153,52,118,70,162,226,17,44,167,143,173,82,136,196,33,78,66,214,183,99,234,45,195,174,137,2,130,152,108,198,75,5,157,104,127,20,38,255,194,145,18,75,8,44,33,16,239,
253,131,202,79,67,89,74,78,28,56,48,248,97,62,45,21,137,199,133,185,38,223,127,115,17,69,134,76,46,77,46,107,147,203,217,88,202,160,149,192,206,36,168,12,72,153,162,87,143,137,35,40,140,184,88,217,132,
56,140,208,70,96,84,130,72,108,132,21,34,93,155,176,153,33,238,74,132,72,176,82,18,55,19,161,147,22,24,137,82,16,5,125,180,145,56,118,138,176,237,208,174,71,40,229,146,47,6,104,122,132,93,69,220,117,16,
166,79,28,187,180,58,17,189,78,143,122,39,192,232,128,87,158,221,205,227,199,210,8,209,195,239,217,44,109,174,126,201,118,213,119,255,117,229,101,37,198,254,105,51,48,50,144,249,251,249,180,84,50,129,
122,51,224,79,47,174,209,11,61,6,83,154,88,71,108,110,250,84,107,130,40,233,243,248,233,97,62,248,96,131,141,197,128,67,179,14,83,51,41,28,103,128,176,99,136,66,31,75,196,232,4,180,208,24,227,67,98,16,
113,68,34,123,36,70,34,8,33,82,36,13,7,105,107,180,18,68,218,65,234,4,43,233,144,24,31,133,32,149,50,68,129,228,198,249,136,91,183,125,70,70,21,79,61,63,192,133,247,171,8,157,66,139,24,79,165,72,91,22,
205,86,159,143,207,111,179,103,124,134,202,160,194,206,184,164,50,206,127,222,233,181,254,68,74,25,63,72,90,50,196,0,182,37,79,14,15,57,175,40,109,136,180,199,185,43,155,116,155,146,201,129,52,207,28,
159,224,230,157,101,102,159,216,203,181,107,243,188,248,181,125,12,141,100,153,191,90,231,196,47,87,120,225,165,50,185,178,162,231,143,34,164,34,149,219,6,21,127,86,169,9,192,60,144,208,32,12,8,249,32,
164,204,103,251,46,19,76,146,39,232,230,17,104,156,108,7,33,2,136,0,173,33,84,180,219,49,239,188,177,206,221,155,33,159,123,97,132,199,158,176,248,193,239,181,56,118,116,63,183,111,46,177,247,192,94,62,
185,184,64,173,157,240,201,229,53,94,126,110,0,233,132,84,114,165,19,173,86,239,229,68,154,239,33,192,18,194,160,19,67,177,228,253,39,217,148,144,24,201,122,53,225,242,173,22,51,229,28,83,147,41,250,166,
195,196,120,158,94,167,206,190,131,14,187,102,36,255,236,127,157,231,192,158,1,94,254,220,8,73,108,88,184,5,119,214,182,8,234,109,84,208,66,75,131,192,32,141,64,10,9,168,207,106,154,228,1,180,1,241,217,
102,24,19,67,178,131,177,75,132,150,64,37,33,34,104,35,100,76,49,147,102,215,84,158,145,9,195,23,95,25,228,109,187,195,31,253,211,123,252,230,223,30,102,255,177,14,141,218,6,187,38,51,196,189,26,199,14,
149,152,187,219,227,211,187,13,30,222,63,204,228,132,193,120,46,169,116,234,111,180,253,230,247,164,144,88,50,177,81,136,137,129,98,246,215,37,49,177,201,114,245,198,54,169,148,205,248,128,96,223,110,
151,43,183,54,57,180,111,31,215,175,207,241,252,87,167,249,232,173,38,244,13,207,191,148,161,215,237,115,254,90,143,143,63,13,168,246,35,116,111,135,180,142,176,28,27,163,13,81,28,209,11,52,65,34,112,
84,10,33,36,58,137,62,3,77,72,18,131,133,198,150,144,46,246,112,202,101,146,88,147,4,33,157,102,139,184,87,167,92,216,225,196,163,19,156,122,162,200,179,207,100,249,195,63,242,57,251,122,135,227,79,14,
243,230,191,92,98,239,145,105,238,222,90,99,246,208,24,205,86,31,63,201,115,249,122,149,137,209,1,164,136,168,100,6,62,239,215,194,99,2,121,217,10,146,30,185,108,230,243,185,76,58,47,8,168,55,53,119,22,
155,60,124,104,128,172,232,33,45,73,49,35,177,68,135,193,33,65,98,9,174,94,232,240,210,211,3,72,2,126,124,5,206,95,173,49,53,48,194,241,135,210,12,149,202,148,179,49,202,145,160,44,162,196,99,187,229,
176,186,163,89,221,104,81,221,104,17,117,52,113,216,70,8,159,241,209,10,51,123,70,25,217,101,83,200,131,84,22,189,72,17,134,130,160,19,82,221,168,177,116,103,157,15,63,92,32,10,70,249,252,153,33,158,62,
53,204,235,111,173,112,248,72,153,161,49,27,97,122,20,242,32,116,196,96,49,38,157,41,240,209,245,117,78,180,10,140,20,4,153,148,163,44,107,224,149,78,39,185,108,73,5,249,188,243,170,84,10,163,21,119,87,
26,8,44,246,140,102,8,194,136,192,15,25,26,180,137,162,58,227,187,42,204,205,245,200,167,108,118,13,12,50,119,167,207,253,123,59,124,225,217,89,166,39,52,157,102,147,181,141,14,243,243,1,157,94,128,147,
118,40,79,78,80,28,31,224,145,135,199,57,110,101,89,91,234,112,251,242,61,164,86,28,121,252,16,187,30,154,194,10,182,88,155,187,200,220,237,121,234,107,13,124,95,146,206,21,25,30,200,49,51,61,196,137,
67,3,44,174,238,240,206,187,139,76,221,204,114,248,112,153,188,155,98,238,122,151,137,169,20,254,78,143,202,144,67,175,223,165,82,146,12,24,184,148,242,184,179,88,103,236,216,32,142,48,100,178,246,107,
237,160,243,223,90,57,215,174,148,179,153,167,145,33,113,4,183,22,154,236,158,40,144,150,62,94,1,116,179,75,186,100,211,172,181,169,20,243,124,116,182,195,222,201,28,70,69,92,93,168,145,179,36,150,142,
120,253,199,247,89,95,174,145,114,51,100,179,105,98,165,104,250,17,183,238,111,18,235,42,179,179,43,28,127,242,40,147,51,7,152,56,124,12,219,148,145,186,199,246,221,247,57,255,195,183,249,244,227,101,
34,161,25,25,74,81,204,219,244,235,59,220,106,246,185,116,81,51,152,237,115,224,161,1,242,217,34,151,111,86,217,127,56,197,158,233,18,11,139,85,14,78,228,233,239,108,147,205,101,168,213,125,10,185,60,
161,239,179,127,60,203,252,124,141,19,15,85,112,133,160,144,19,15,213,234,253,41,203,70,237,245,92,85,150,194,208,236,26,182,182,35,142,29,243,144,178,74,42,237,226,119,66,82,41,139,192,73,48,145,160,
93,141,25,62,100,227,247,187,212,27,17,155,91,176,112,255,42,135,14,185,188,246,218,1,116,63,77,167,219,198,202,185,100,71,50,180,125,139,75,31,55,153,187,182,131,147,185,198,163,241,50,142,91,161,43,
29,146,160,198,157,171,171,124,244,193,125,14,206,148,248,194,203,123,201,22,19,182,215,35,252,102,31,10,83,216,41,195,205,75,215,248,193,15,238,226,119,109,70,71,21,190,223,99,100,204,227,242,237,132,
208,183,73,219,18,207,51,164,156,144,84,10,146,160,203,204,190,49,174,221,216,160,217,210,84,202,144,242,92,71,25,231,136,149,113,157,99,202,6,144,212,106,33,113,98,24,222,5,118,53,196,181,29,98,71,99,
217,154,140,39,240,187,134,40,72,200,102,5,58,54,132,33,4,70,112,234,244,8,79,31,47,241,241,79,182,169,118,86,152,57,228,241,209,79,154,152,212,4,123,14,148,40,15,230,16,247,67,230,231,251,28,218,27,227,
70,155,120,70,209,16,138,79,239,117,112,68,138,241,193,44,247,239,119,184,252,131,53,252,168,199,233,83,99,220,189,185,66,38,237,243,210,179,211,12,22,187,124,231,245,155,4,81,138,56,244,200,101,65,39,
9,253,142,38,227,10,148,99,72,217,26,203,138,177,236,136,193,97,77,34,4,155,59,17,229,138,133,37,37,233,148,122,210,146,82,28,183,148,193,32,216,218,236,227,230,12,133,138,34,110,72,164,165,177,28,129,
80,6,219,177,168,55,52,8,141,165,4,202,72,44,59,198,65,80,91,53,252,139,185,123,220,88,108,240,133,87,38,121,236,212,48,75,203,49,103,47,194,218,198,10,142,99,17,26,40,43,151,237,170,133,59,96,227,36,
49,237,122,143,188,244,168,73,120,255,202,50,81,172,73,90,112,250,137,81,78,158,30,166,243,142,230,141,31,110,178,120,109,155,252,112,26,203,214,216,182,198,18,14,74,26,52,134,110,79,82,46,9,80,18,215,
6,161,64,90,224,150,34,210,101,155,205,29,159,67,251,11,128,198,182,115,199,164,147,203,205,34,99,76,34,168,55,98,178,69,131,155,82,132,145,64,75,139,216,60,216,140,196,8,122,65,76,98,98,132,113,112,28,
155,66,78,16,202,62,91,173,62,237,126,140,165,96,109,177,199,210,165,144,181,69,159,209,137,6,47,188,184,151,98,186,128,142,34,202,89,11,106,62,86,220,32,150,1,126,203,48,144,17,36,42,96,168,48,192,215,
191,252,56,123,142,100,184,183,217,98,254,74,139,213,213,30,198,142,8,180,164,221,48,152,208,33,159,151,184,110,12,218,70,163,241,253,24,173,65,35,49,70,160,165,36,210,224,166,21,249,138,71,189,222,67,
36,18,37,123,56,105,123,196,194,98,88,124,214,3,183,187,33,249,65,15,225,38,132,58,193,24,73,18,133,8,147,34,210,9,65,2,58,2,157,128,73,7,76,142,20,185,187,180,193,139,103,38,153,62,104,177,112,167,202,
237,91,13,206,221,92,226,248,19,105,246,31,223,205,141,235,93,182,155,155,20,210,30,58,72,232,37,29,34,145,71,38,138,36,105,146,68,117,134,115,14,141,106,139,80,118,249,198,55,15,115,249,234,6,23,110,
239,96,165,75,124,249,215,39,121,100,111,158,245,219,49,191,255,47,175,51,57,89,192,82,22,113,210,37,142,244,131,168,136,5,10,65,63,1,207,104,162,216,96,60,67,33,173,105,85,3,162,68,99,217,54,174,36,111,
217,194,45,96,98,180,54,248,65,64,217,245,144,110,68,36,34,98,12,161,182,136,241,8,146,0,35,4,126,16,17,198,6,207,132,236,155,25,226,218,173,42,223,255,195,57,30,123,98,136,67,199,60,246,124,126,28,140,
69,175,23,113,225,189,85,206,157,109,96,155,60,41,219,102,167,219,103,92,100,144,73,10,43,237,83,78,251,44,87,27,100,179,14,173,94,196,247,190,115,155,214,214,24,71,143,87,56,118,216,165,217,77,209,238,
38,188,247,238,50,23,63,88,97,120,48,197,241,135,139,72,221,38,137,21,253,192,16,137,152,72,71,40,99,19,198,134,88,91,196,161,66,57,33,41,87,179,29,66,148,8,108,219,70,201,48,99,73,145,184,198,8,180,209,
36,38,65,27,137,176,53,58,4,211,115,72,252,52,73,228,64,0,202,72,122,189,152,78,91,83,42,58,164,210,61,78,159,25,227,157,31,52,121,253,79,150,249,232,39,30,165,124,22,203,137,104,182,66,154,45,141,116,
4,133,124,132,233,70,8,154,140,14,11,6,243,117,108,39,128,146,69,43,50,152,110,64,197,182,169,247,53,63,122,103,157,15,62,174,83,40,41,164,204,211,168,135,84,235,27,76,76,120,188,240,149,17,114,5,31,186,
89,234,109,67,171,19,162,72,17,134,29,156,192,165,31,10,162,24,66,163,17,86,130,48,134,32,81,24,20,194,196,40,97,44,11,17,128,241,30,212,181,194,224,251,9,72,16,41,143,208,68,36,118,64,79,134,104,233,
96,11,23,11,197,245,75,107,100,83,19,200,140,98,104,68,240,31,255,205,99,156,63,183,192,220,229,14,181,141,128,36,233,98,43,27,47,93,192,200,132,110,208,198,68,117,30,58,58,204,216,190,18,166,223,71,135,
49,249,73,143,177,189,67,204,157,219,70,91,16,57,14,174,149,144,196,134,245,157,14,94,214,161,52,44,56,241,220,48,143,158,28,38,151,245,137,183,28,154,173,60,215,111,220,65,38,224,185,130,216,181,232,
25,11,223,18,36,82,67,198,128,101,227,247,21,137,138,30,100,50,66,140,22,88,177,49,33,8,44,101,161,44,73,179,30,96,68,142,236,172,162,190,169,177,198,142,209,204,90,120,201,26,78,18,48,49,150,165,219,
9,56,247,254,22,217,161,34,153,41,139,125,7,53,103,94,153,228,244,179,22,205,106,64,171,42,105,52,60,46,93,220,98,109,217,160,84,158,221,71,42,60,246,197,23,104,199,215,16,206,22,202,78,3,240,196,171,
79,19,243,9,115,23,46,209,111,193,204,120,158,231,158,26,197,29,112,136,82,41,10,99,22,67,3,17,253,237,46,59,55,44,214,239,197,172,109,205,209,243,219,204,142,103,113,178,17,113,41,79,152,158,64,101,199,
105,251,155,148,166,138,32,210,52,26,109,148,3,150,37,49,194,96,180,136,45,147,136,150,38,26,197,241,112,51,105,54,215,219,220,191,28,99,103,60,70,102,15,99,201,135,8,83,101,156,120,145,214,226,135,76,
173,9,178,177,139,17,46,115,247,119,216,153,51,124,252,118,72,206,179,113,11,30,137,101,136,163,12,91,141,38,181,173,54,229,116,150,169,189,25,30,122,97,23,130,29,122,27,85,50,51,99,104,145,161,55,191,
64,102,220,231,177,87,142,147,181,26,44,94,93,101,109,173,205,91,63,209,228,134,178,200,180,139,35,12,81,167,75,208,235,34,250,134,130,82,140,76,102,40,165,115,104,20,149,93,54,249,233,9,18,235,97,164,
44,34,131,121,154,91,239,179,112,185,203,230,150,207,200,128,13,182,38,209,134,68,43,223,210,97,122,203,152,120,191,84,130,66,49,67,114,111,7,217,246,40,91,37,174,253,232,22,205,173,75,68,74,81,30,242,
56,248,104,154,71,78,142,177,116,121,7,103,160,199,179,79,142,114,253,19,195,189,235,91,220,94,245,105,196,61,76,164,176,104,19,161,24,169,164,25,45,57,204,140,103,145,254,38,141,141,101,188,68,210,90,
111,1,45,116,98,8,239,93,39,91,76,49,57,149,131,218,40,125,221,229,246,98,29,179,2,137,10,200,24,159,130,234,49,89,74,49,245,240,62,166,159,240,208,247,215,105,236,104,118,31,25,32,237,10,62,125,227,38,
219,91,215,32,178,40,13,73,14,30,207,19,248,49,186,215,39,151,42,35,109,160,175,9,99,211,178,122,253,230,124,133,236,211,66,10,138,5,155,163,7,134,25,204,21,120,235,237,5,106,53,201,196,136,139,101,9,
150,111,6,180,111,215,57,241,210,44,78,37,77,134,22,19,135,246,80,57,241,56,153,63,126,131,202,249,21,252,150,164,145,116,104,248,125,108,41,217,59,149,194,209,109,28,123,128,168,42,184,124,126,141,177,
145,33,118,11,144,38,224,234,157,30,237,94,159,71,31,26,2,37,209,40,246,238,30,36,112,33,9,45,134,83,138,172,209,228,243,146,61,15,141,49,251,181,215,16,206,42,27,155,91,100,75,30,174,35,121,235,79,86,
233,181,5,149,209,52,137,13,119,110,119,216,90,171,113,230,197,25,30,57,58,130,155,201,161,164,1,109,227,71,193,166,165,117,116,41,209,252,142,208,17,131,131,46,105,5,126,167,207,214,122,139,253,7,167,
153,62,158,224,68,9,181,129,60,31,254,164,69,181,214,33,159,178,168,223,87,220,123,243,14,153,153,14,135,75,1,197,114,155,213,64,19,181,53,118,90,115,242,200,48,162,223,161,214,232,81,91,94,39,8,37,183,
110,86,105,181,251,60,178,103,26,55,149,98,235,238,61,22,215,35,114,198,33,151,78,72,137,30,149,66,138,201,137,2,151,174,111,147,248,9,217,172,197,72,209,99,104,200,176,126,249,35,146,123,53,250,75,93,
50,251,42,212,107,154,205,141,144,39,159,28,162,50,153,32,60,184,119,161,200,167,151,235,248,85,195,228,152,135,201,73,100,2,137,78,8,13,215,172,118,219,92,74,146,7,189,100,161,226,210,107,181,177,236,
44,197,76,154,84,161,193,216,163,25,146,45,143,155,151,215,137,82,9,185,148,68,55,124,18,5,213,165,6,27,119,86,137,77,138,149,70,192,252,118,64,38,101,243,185,39,167,200,58,29,26,155,29,98,207,225,252,
157,13,106,181,30,90,58,236,84,91,92,188,214,36,206,165,88,235,68,68,177,224,194,181,101,38,138,146,233,125,5,66,39,161,236,134,60,114,114,140,119,63,92,225,198,86,135,14,89,26,231,106,228,172,38,89,17,
99,210,18,29,106,242,5,143,148,212,84,183,123,76,159,206,226,141,75,150,151,27,120,165,62,174,3,210,64,118,192,67,235,144,216,88,108,214,234,31,89,198,248,119,252,32,106,21,93,55,159,41,101,240,175,223,
35,12,139,156,60,53,134,41,52,208,166,15,164,113,210,138,231,79,143,145,242,44,214,59,154,148,151,208,10,50,92,221,180,104,116,250,36,90,49,52,61,202,193,35,105,100,169,143,93,44,50,184,39,139,229,135,
84,204,8,253,32,162,91,213,92,253,201,22,63,126,183,70,219,10,201,15,192,211,175,141,146,30,73,51,61,100,227,186,9,181,106,68,16,10,108,35,56,253,236,110,238,223,233,177,186,222,103,105,73,51,61,160,217,
59,33,201,218,146,176,222,199,26,204,240,248,153,81,182,54,219,24,169,209,162,197,240,4,20,83,67,104,98,118,90,125,198,74,89,76,103,29,63,176,99,137,117,213,10,149,222,236,116,251,103,43,41,239,69,199,
17,184,249,50,231,207,174,115,224,209,34,133,156,130,196,96,68,143,177,169,12,249,236,0,171,75,155,184,158,131,8,179,180,250,1,139,171,85,30,122,184,196,233,39,39,48,110,204,242,86,196,220,156,196,196,
53,60,87,35,76,66,54,111,49,62,93,66,231,109,6,6,20,183,230,26,68,161,199,147,79,12,177,123,56,205,149,133,14,243,151,27,248,189,132,90,63,33,151,246,72,59,138,98,206,112,242,153,10,97,160,248,248,220,
50,55,175,238,80,72,231,25,24,83,136,148,102,99,103,147,145,93,131,120,94,128,74,32,73,60,178,89,139,104,219,227,147,115,85,196,104,246,65,67,161,13,173,110,48,103,201,254,61,75,68,10,191,25,127,215,148,
244,139,166,223,102,248,224,30,46,254,233,79,136,173,128,51,251,203,24,173,81,42,34,10,13,223,251,214,28,163,67,105,30,221,111,225,215,29,218,253,54,35,227,101,158,127,102,138,229,251,119,121,231,39,61,
106,61,232,247,53,74,25,148,144,72,109,147,36,17,133,82,131,242,160,195,190,135,43,140,207,148,72,98,168,111,69,92,125,127,141,171,183,59,132,205,62,161,112,240,17,100,237,14,202,24,148,18,20,211,43,60,
113,188,204,171,103,118,243,221,110,68,163,219,65,167,210,228,139,105,62,189,189,195,39,159,220,230,228,211,121,44,229,16,27,129,155,209,220,250,116,133,219,183,37,175,254,210,44,244,91,232,68,226,215,
251,127,108,66,43,178,100,34,232,117,130,215,219,126,236,123,253,126,170,56,57,200,200,254,10,182,246,81,202,96,140,2,17,99,180,96,109,163,15,38,133,56,162,112,172,144,209,145,52,91,221,30,65,44,185,113,
219,176,184,6,86,86,226,121,30,142,212,196,186,139,70,19,71,130,157,54,172,87,123,44,46,116,209,90,211,79,36,218,132,36,218,69,185,138,178,103,136,141,192,138,36,73,28,18,138,4,161,29,194,170,100,233,
110,131,227,71,123,120,50,98,100,168,130,109,27,148,237,176,182,45,89,94,143,121,52,177,30,252,13,6,148,210,216,110,204,208,190,49,70,198,93,204,234,54,189,158,67,215,111,252,64,201,4,43,114,12,90,39,
243,27,29,255,219,251,114,169,175,209,169,179,255,228,46,218,183,231,225,51,139,80,162,109,44,75,17,74,139,203,183,154,60,246,216,0,67,217,128,153,92,133,27,243,29,230,239,52,153,61,50,205,114,245,22,
245,102,15,149,24,76,32,144,2,132,233,242,232,67,19,204,30,172,176,220,168,147,206,61,232,92,194,88,81,44,105,154,27,154,176,237,224,111,69,124,120,181,138,37,20,174,50,196,38,69,18,71,140,143,39,156,
249,252,67,44,204,55,48,24,102,103,243,152,184,197,70,187,195,197,249,29,242,89,133,237,100,16,58,65,26,141,78,60,74,197,20,165,163,67,72,191,139,142,96,187,233,255,105,207,68,231,148,148,88,72,133,16,
138,70,187,255,123,65,41,243,53,209,232,51,52,57,137,106,184,104,163,17,72,164,0,75,216,180,122,49,203,205,136,11,55,58,124,233,25,135,40,234,49,115,112,144,43,23,23,57,124,116,140,87,191,50,195,185,143,
239,178,122,183,143,178,129,196,65,247,21,185,92,154,114,81,226,228,179,12,239,149,68,110,76,162,125,166,42,138,230,114,145,133,79,13,107,125,67,42,23,18,73,67,198,11,145,145,207,158,153,12,47,126,97,
31,141,165,30,231,63,90,226,115,95,152,70,186,85,148,151,226,194,185,54,235,53,141,192,69,9,7,173,26,24,17,145,8,73,118,32,75,105,119,137,120,103,17,29,24,26,141,230,255,34,165,209,8,141,101,153,7,227,
210,36,12,223,221,106,180,222,25,201,86,158,143,219,155,216,174,194,210,6,173,98,148,2,41,52,161,17,36,150,205,199,151,183,120,234,208,94,82,249,62,187,103,28,180,174,240,209,251,11,236,239,143,112,242,
212,20,230,84,64,54,109,35,19,155,213,197,152,157,141,6,235,155,9,133,162,160,144,115,217,142,125,132,140,72,98,77,208,106,66,96,147,206,8,126,237,43,135,17,233,132,161,113,11,105,5,216,50,226,230,39,
77,62,122,115,131,167,158,45,50,49,101,209,91,177,216,244,29,206,94,106,147,88,146,208,24,20,17,70,121,72,161,17,132,216,25,137,108,108,98,76,200,118,61,184,30,118,186,223,177,148,252,108,32,30,244,254,
181,125,208,108,109,39,255,168,82,46,63,239,37,29,154,221,62,126,71,225,180,211,36,93,143,237,90,159,78,59,194,142,97,107,39,224,219,239,109,243,155,95,154,102,32,183,198,228,153,18,110,212,231,157,247,
87,89,154,223,97,120,34,131,52,9,150,145,68,190,77,62,5,251,135,7,169,215,234,248,219,138,202,204,131,129,92,103,222,99,251,94,147,209,225,50,27,107,117,174,126,210,64,165,44,44,17,18,139,144,141,173,
30,221,149,132,167,158,29,229,216,11,35,180,22,183,112,69,153,31,188,187,201,206,166,1,207,208,8,124,214,234,49,35,237,1,140,147,208,111,247,9,91,17,22,29,18,99,177,190,211,254,199,177,116,250,201,103,
126,46,245,141,231,10,8,233,32,164,67,172,229,61,18,113,116,36,159,59,36,93,155,154,93,224,234,123,125,222,124,163,202,59,239,111,51,51,84,225,139,103,198,72,103,18,46,124,186,131,73,4,7,71,179,200,124,
196,216,177,2,133,24,214,111,183,185,62,223,97,109,57,100,107,45,96,99,221,199,82,154,163,71,6,168,181,250,180,106,93,244,142,166,115,79,179,189,220,38,142,211,20,202,89,62,254,120,141,27,115,53,54,54,
187,220,91,233,179,179,216,39,159,192,51,47,149,120,242,181,33,194,70,27,93,45,240,189,15,107,156,187,178,206,211,143,164,121,249,185,49,76,144,226,253,243,171,108,222,233,208,216,81,88,229,81,10,210,
162,40,60,86,214,26,31,52,123,193,223,181,109,101,148,146,40,37,81,191,251,124,17,41,173,207,164,232,245,163,247,93,71,253,118,177,24,103,114,123,70,73,82,19,156,125,231,83,182,118,124,190,244,249,105,
78,157,78,243,200,163,37,148,149,231,135,175,47,208,109,185,140,13,165,113,7,235,236,58,90,100,160,146,199,10,33,238,247,209,145,70,99,35,101,194,145,131,3,164,202,30,115,55,98,10,42,141,241,45,238,222,
23,236,217,95,196,68,46,231,207,111,208,239,10,108,233,82,78,75,14,30,150,156,250,213,97,14,63,63,138,174,119,9,239,89,124,255,205,58,63,62,187,206,23,191,52,198,215,126,99,140,61,123,60,92,225,242,193,
133,53,100,108,56,241,234,73,246,204,216,164,90,219,236,52,131,222,122,181,246,43,182,74,54,149,140,249,169,126,243,105,135,216,36,196,38,33,49,9,145,78,218,237,32,220,40,165,115,191,34,252,58,133,99,
211,140,228,199,88,185,118,143,78,28,48,179,59,143,155,106,176,239,96,150,86,207,226,251,31,172,176,177,146,48,18,23,40,150,4,131,7,211,236,62,152,102,100,64,145,203,88,100,156,20,182,74,216,61,238,49,
62,165,232,26,139,159,156,223,226,222,90,135,217,71,178,236,217,29,179,179,2,235,107,53,6,71,20,179,135,178,156,124,190,192,201,151,43,140,237,206,224,175,5,220,190,96,248,206,235,53,222,187,178,197,231,
126,105,136,175,254,181,50,34,17,4,155,240,198,251,75,196,157,144,87,191,254,44,179,79,13,16,207,221,33,105,90,220,94,223,254,251,126,172,191,157,0,241,191,33,245,141,231,211,8,41,126,42,169,4,177,214,
87,195,80,14,149,188,236,227,81,176,204,216,99,135,200,219,37,206,191,123,155,86,79,176,123,164,128,151,110,115,240,241,50,58,144,156,61,187,195,197,155,109,54,215,52,118,40,41,15,90,76,62,84,102,246,
96,154,3,211,105,42,57,143,40,146,184,153,152,221,199,35,198,14,85,56,112,34,203,236,33,104,111,105,106,27,134,153,221,46,167,158,47,113,232,169,50,35,123,178,116,27,48,119,54,230,199,63,108,240,189,55,
54,89,222,232,240,194,203,35,252,198,239,142,146,234,7,4,91,22,175,191,83,231,198,245,29,206,252,181,83,156,120,101,47,201,237,139,152,70,194,242,102,227,59,126,212,249,219,142,2,75,154,159,145,250,250,
51,25,48,226,103,36,16,116,253,224,173,24,245,84,217,182,167,149,191,194,208,169,35,120,185,20,151,127,124,147,122,93,49,49,88,36,87,241,57,122,58,205,80,197,102,121,57,226,202,167,61,174,94,173,114,235,
114,192,250,66,76,191,29,35,140,133,76,178,248,205,4,43,157,144,26,236,80,24,149,228,7,35,146,94,76,107,53,161,81,179,72,101,51,68,97,196,252,92,155,247,223,236,241,250,15,170,188,241,222,58,119,238,117,
25,26,115,248,242,127,52,197,107,191,93,193,77,170,116,23,28,126,248,86,131,171,55,214,121,225,87,159,226,177,95,123,4,189,112,14,182,35,118,182,90,87,122,52,190,236,102,149,111,187,2,219,251,89,137,119,
255,65,225,23,56,103,205,224,68,121,244,71,19,19,234,120,60,97,227,204,60,193,245,31,175,241,230,239,191,69,62,159,225,133,23,7,153,126,164,143,154,80,108,175,89,92,125,195,231,226,217,29,110,45,70,180,
186,1,150,35,201,121,22,57,219,230,208,116,145,207,157,201,49,188,63,66,141,9,18,39,132,117,201,246,213,20,111,191,215,226,226,237,26,65,223,166,211,239,19,39,33,185,148,96,106,79,158,99,39,134,57,121,
198,98,112,87,155,120,221,101,241,98,158,183,223,92,164,190,25,241,185,223,126,140,163,47,79,35,231,46,194,178,207,66,183,119,175,222,220,122,193,182,228,194,255,51,136,255,51,78,188,111,60,231,33,62,
27,212,255,140,36,104,109,122,141,90,235,135,198,182,158,203,135,114,84,247,235,140,159,60,196,248,190,73,230,175,45,112,254,227,45,100,43,67,201,246,40,143,72,246,156,116,57,254,116,158,163,135,28,166,
71,60,242,25,11,97,107,58,81,64,47,140,153,157,46,146,74,119,72,143,246,144,14,116,238,217,212,215,12,31,95,174,18,4,1,195,131,138,217,253,25,78,63,91,228,229,175,14,243,210,111,12,112,228,9,135,140,52,
180,111,25,46,188,17,243,206,247,215,208,105,193,47,255,173,87,56,124,122,148,232,214,89,204,90,143,245,122,239,238,90,107,229,75,202,178,111,9,35,126,106,48,248,179,18,239,253,195,194,207,245,149,38,
177,33,238,199,164,178,214,240,216,174,241,255,163,146,78,126,201,46,199,216,135,78,208,238,85,56,247,175,206,113,233,221,27,148,10,22,199,159,44,112,224,104,142,220,184,130,161,38,194,82,208,201,17,53,
52,157,173,136,218,178,166,93,75,240,178,62,211,167,60,180,43,88,122,55,36,110,218,136,146,67,101,74,145,171,8,210,21,13,153,62,244,179,152,134,161,177,225,115,247,10,92,254,176,193,102,179,203,161,103,
14,114,250,215,158,162,152,223,164,127,253,22,102,39,102,179,209,185,180,221,219,250,170,54,225,130,84,46,234,23,152,199,213,239,60,235,253,92,96,163,65,199,154,84,218,233,166,70,202,127,184,181,82,27,
202,38,153,71,77,115,5,187,24,179,239,217,227,236,218,187,143,205,213,42,103,63,94,225,206,181,46,157,13,11,217,204,34,123,14,36,9,142,149,144,202,40,202,133,20,173,173,144,110,203,162,187,163,104,46,
197,248,59,30,94,90,49,123,216,37,87,233,163,176,233,183,192,95,50,108,93,19,92,126,55,224,173,31,110,113,229,218,54,67,19,101,62,255,205,87,121,228,87,30,38,219,185,138,185,122,157,126,77,176,182,213,
248,86,63,233,253,154,150,122,85,235,4,33,21,18,241,239,238,136,23,8,191,222,13,126,183,215,111,157,159,10,50,255,168,216,191,59,16,236,44,51,126,228,32,95,57,242,18,119,47,236,112,237,173,171,156,187,
112,143,115,159,104,202,5,143,201,93,5,6,135,45,242,121,155,92,22,34,227,224,216,138,205,5,31,163,29,42,163,6,29,59,108,47,40,122,190,164,222,208,108,84,3,86,151,183,217,110,246,137,165,197,236,236,46,
158,255,250,81,118,63,54,141,171,55,209,215,254,152,104,43,160,177,83,232,108,183,214,255,43,77,255,191,147,41,219,144,252,37,57,254,50,33,157,43,122,12,238,219,197,234,237,165,7,115,156,88,238,173,20,
11,255,253,208,80,225,213,84,161,141,53,150,197,218,181,31,237,78,177,125,187,201,226,185,219,204,125,122,155,245,165,45,250,157,16,19,11,164,45,136,13,28,152,46,115,234,228,46,144,146,179,31,47,114,109,
161,134,80,32,66,131,144,224,230,92,70,38,70,152,61,178,151,61,143,239,99,244,64,25,43,90,34,90,188,74,188,214,38,108,43,238,214,194,63,237,212,226,191,83,116,187,151,133,163,193,85,248,137,79,20,7,72,
229,252,194,144,254,43,3,235,68,98,197,146,196,8,148,178,190,60,82,242,254,110,169,236,157,162,28,98,15,58,120,163,123,144,133,41,250,161,67,107,35,160,181,84,167,190,188,195,230,70,131,78,221,71,247,
27,140,14,89,32,44,214,55,98,100,218,38,91,204,48,56,92,161,180,171,66,105,170,66,113,40,135,229,116,73,90,119,49,107,247,137,182,2,250,109,65,181,150,92,170,85,91,255,67,91,247,255,121,202,42,152,146,
227,131,157,252,149,128,255,173,111,181,72,41,72,116,242,173,141,157,157,111,55,91,230,181,82,53,253,59,233,205,212,43,122,233,138,116,115,215,112,10,101,6,42,101,6,30,27,194,122,106,31,224,98,208,132,
145,32,8,53,16,227,218,22,142,109,30,140,66,68,140,14,119,72,90,119,48,247,171,244,155,13,130,150,33,104,10,186,173,228,237,118,175,243,191,213,123,241,31,73,67,32,45,129,248,15,125,141,7,30,248,172,164,
148,70,235,224,219,173,70,239,219,213,182,124,212,106,200,207,59,150,121,173,148,173,30,181,50,109,207,241,22,176,82,10,229,89,8,91,32,156,20,105,75,67,162,62,179,53,245,48,145,38,236,27,180,31,17,7,10,
191,23,133,126,51,156,211,129,243,221,72,244,126,20,250,225,7,194,18,40,37,248,203,126,171,255,159,0,255,155,224,66,8,132,18,23,194,40,184,80,221,12,254,235,117,75,236,149,86,250,80,73,56,39,165,27,28,
243,210,246,168,167,114,5,227,246,210,150,213,183,77,228,9,173,162,72,68,73,47,233,185,173,86,24,109,10,63,188,218,143,204,185,158,49,215,163,184,57,95,206,167,99,47,175,144,129,192,252,91,159,233,207,
174,255,123,0,177,110,166,126,249,239,99,150,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* JuceDemoPluginAudioProcessorEditor::onMaya_png = (const char*) resource_JuceDemoPluginAudioProcessorEditor_onMaya_png;
const int JuceDemoPluginAudioProcessorEditor::onMaya_pngSize = 9515;

// JUCER_RESOURCE: downMaya_png, 9290, "../../../Desktop/downMaya.png"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_downMaya_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,60,0,0,0,60,8,6,0,0,0,58,252,217,114,0,0,0,9,112,72,89,115,
0,0,11,19,0,0,11,19,1,0,154,156,24,0,0,0,4,103,65,77,65,0,0,177,142,124,251,81,147,0,0,0,32,99,72,82,77,0,0,122,37,0,0,128,131,0,0,249,255,0,0,128,233,0,0,117,48,0,0,234,96,0,0,58,152,0,0,23,111,146,95,
197,70,0,0,35,192,73,68,65,84,120,218,204,187,103,180,103,89,121,159,249,236,125,210,63,199,155,83,221,92,183,114,117,229,212,153,238,6,53,88,192,2,148,144,177,180,132,16,99,107,6,201,178,36,100,203,131,
150,102,24,75,24,20,70,178,89,66,128,49,97,192,18,8,58,208,161,170,187,58,84,117,119,85,119,85,87,232,74,183,234,230,28,254,57,157,188,231,67,123,102,13,30,163,145,44,225,209,89,107,127,57,251,203,251,
236,115,118,122,127,191,87,40,165,248,81,60,119,94,252,131,137,186,74,159,216,104,68,239,157,94,139,236,155,156,247,186,151,150,237,216,82,161,166,87,75,82,74,165,136,39,188,176,167,45,26,244,245,24,173,
145,45,201,181,225,238,240,114,87,172,249,98,218,108,188,60,124,247,63,189,242,163,136,75,252,125,2,223,56,253,217,99,139,141,206,95,60,55,149,125,248,177,151,172,206,107,111,213,165,239,42,60,221,68,
70,162,64,4,41,67,132,210,17,24,132,161,77,24,182,208,189,58,56,101,132,223,66,68,45,38,182,38,212,163,247,153,133,99,19,173,231,183,196,202,95,220,254,142,143,63,251,15,10,248,194,201,63,253,165,55,150,
250,127,249,223,63,222,177,237,214,245,134,80,202,135,120,146,48,145,133,120,4,195,12,137,26,33,154,105,128,225,34,140,0,17,74,84,168,8,130,0,207,51,176,91,38,70,51,68,52,106,120,205,38,65,189,140,12,
202,12,141,39,249,165,15,132,211,199,122,87,254,236,224,187,62,246,123,255,191,2,95,120,234,79,62,250,204,204,182,79,253,222,215,7,122,90,165,22,90,84,39,204,27,136,132,34,25,245,137,166,13,210,89,141,
116,66,39,21,209,208,13,157,64,8,130,208,68,40,29,77,248,72,165,112,67,69,221,110,82,174,123,84,203,33,245,138,141,87,87,4,53,139,176,100,19,214,139,196,18,240,207,126,198,43,60,52,124,231,115,247,190,
247,151,62,253,223,21,120,242,217,63,28,127,110,117,236,177,223,253,234,200,214,202,138,194,107,19,136,132,129,153,108,144,75,235,244,116,229,232,104,139,17,139,10,8,67,234,14,84,26,1,174,231,160,227,
162,249,2,37,116,66,45,36,192,35,174,155,100,34,49,244,136,65,104,72,90,142,207,102,177,206,202,114,131,114,49,196,175,42,130,138,135,87,132,76,167,228,95,126,100,105,225,145,190,75,31,220,254,208,175,
159,251,145,3,159,125,242,203,159,254,195,151,118,252,218,227,167,83,134,23,83,196,18,33,102,84,209,209,27,167,187,87,208,145,141,19,250,6,133,154,75,169,98,83,171,250,52,106,77,52,169,136,167,146,52,
87,3,154,11,130,64,73,226,189,6,201,30,69,173,209,64,185,144,76,68,72,37,67,210,217,56,153,180,133,161,5,20,138,13,22,86,29,150,215,28,188,170,78,176,17,5,167,198,61,39,130,240,55,30,121,243,75,15,190,
231,35,31,253,145,0,207,156,254,55,242,141,205,209,211,31,255,242,238,123,106,27,46,178,77,67,197,3,58,58,116,134,7,218,209,154,13,102,94,127,17,95,79,144,30,221,199,198,134,75,171,89,199,118,35,88,81,
157,222,174,8,107,119,26,148,23,4,162,148,70,248,138,48,213,36,49,24,208,61,150,102,189,80,161,81,215,137,68,106,196,19,146,182,108,154,242,236,20,154,93,98,96,255,78,244,100,130,185,217,50,235,27,146,
176,174,99,23,90,100,211,22,191,255,243,55,175,222,215,59,125,207,240,125,159,40,255,189,1,207,188,252,217,142,191,154,220,241,250,191,254,102,231,128,227,231,16,169,144,104,162,196,142,177,12,153,76,
140,91,83,171,104,122,64,214,136,177,60,229,83,241,116,162,137,36,229,101,155,16,73,223,88,156,242,230,38,245,69,157,176,174,35,170,58,120,2,82,33,65,58,32,217,231,210,214,149,96,254,102,128,208,32,211,
21,226,217,54,49,116,6,134,52,202,84,169,217,26,219,70,218,177,27,45,174,222,108,97,219,1,98,83,160,41,193,63,255,208,70,241,39,39,46,29,223,254,142,95,185,249,119,6,158,126,233,223,108,249,210,229,227,
23,63,243,189,68,78,104,49,84,42,32,149,246,57,178,173,31,35,30,225,141,139,55,184,255,112,39,249,164,133,83,179,137,183,103,120,252,228,12,165,205,20,229,169,20,42,116,24,216,175,112,156,22,202,22,224,
248,136,134,64,4,6,42,10,196,3,84,162,133,165,71,88,184,144,64,105,26,153,33,151,84,126,147,247,63,60,72,173,92,33,98,153,212,28,120,246,165,121,246,30,24,199,247,225,242,229,13,138,37,135,176,106,129,
215,226,163,239,170,53,63,118,215,249,7,118,61,252,137,191,118,94,107,159,250,212,167,126,104,231,236,203,159,237,248,226,229,67,87,255,237,227,237,57,97,164,81,177,128,174,158,144,227,123,250,136,91,
130,11,55,151,73,39,45,118,141,101,249,210,87,174,114,246,181,37,242,61,17,6,7,211,220,158,172,17,108,100,9,26,33,29,3,10,45,98,51,208,38,25,218,98,50,54,154,100,160,223,32,223,25,96,36,66,108,101,161,
249,113,74,183,99,104,90,128,153,43,115,244,96,142,70,181,196,215,190,118,157,203,183,138,28,61,210,75,173,36,152,92,217,96,172,39,202,96,71,142,178,95,162,238,53,8,195,54,46,222,196,80,169,220,207,140,
59,127,241,87,249,161,99,27,63,140,73,255,97,29,115,47,124,70,126,123,106,207,133,207,124,63,147,195,50,145,86,133,129,254,8,7,118,245,227,52,225,250,82,129,192,245,16,150,196,215,124,180,132,129,110,
116,130,37,9,3,9,66,161,171,0,187,166,163,135,33,149,102,139,27,171,46,161,39,208,3,19,225,73,124,195,65,153,33,34,153,33,111,9,130,10,152,166,9,66,16,160,161,27,38,178,45,7,134,142,47,5,1,16,248,6,183,
231,234,12,118,233,28,221,219,199,21,89,96,122,174,138,111,72,190,240,76,62,154,140,28,60,251,49,245,7,35,67,15,254,74,241,111,5,124,126,99,232,244,239,126,175,173,47,212,99,4,86,192,232,128,193,177,61,
125,52,154,77,102,150,155,204,175,218,244,118,164,88,157,223,164,88,80,124,248,39,118,227,184,10,203,80,60,246,216,44,209,120,12,207,83,132,53,3,225,248,116,12,228,72,15,107,100,82,1,166,97,1,224,121,
46,229,106,200,166,173,161,86,67,168,249,24,57,147,72,60,197,171,175,109,242,147,239,238,231,23,126,34,137,30,145,52,42,48,189,176,65,231,96,23,243,203,62,65,80,103,104,75,156,189,119,245,163,196,60,83,
179,13,2,149,228,79,158,74,100,134,115,227,175,252,34,76,252,141,129,207,62,249,133,223,249,31,254,242,200,61,45,165,161,25,30,125,237,112,252,174,17,60,219,97,105,181,202,250,70,147,218,134,142,147,240,
104,239,79,242,237,111,76,178,189,189,134,65,149,219,235,121,188,76,27,187,70,211,156,47,11,80,26,245,117,157,238,17,135,55,222,40,97,84,13,162,174,137,239,71,105,73,27,50,77,118,30,202,178,185,25,71,
169,4,141,82,131,157,25,193,205,197,22,95,254,194,91,108,237,90,33,12,225,230,74,59,35,123,123,113,237,128,202,122,136,41,43,88,166,199,224,0,28,221,219,133,239,44,51,179,232,226,248,38,159,252,110,247,
214,45,241,175,126,229,145,247,254,236,71,254,75,54,249,95,190,184,253,220,31,12,253,254,43,7,127,171,86,213,241,77,72,165,224,238,3,157,8,17,176,184,225,177,94,240,169,148,44,240,146,76,95,131,124,50,
201,238,35,253,220,46,135,92,90,243,137,246,199,56,118,168,151,245,43,62,110,61,130,208,76,22,174,5,100,195,44,71,31,236,35,63,152,37,140,39,80,73,157,142,113,141,187,31,234,162,67,198,89,184,24,65,153,
58,94,35,206,242,37,193,161,35,93,36,250,147,220,88,72,48,183,174,179,231,112,47,237,217,52,51,151,117,84,16,161,90,129,245,13,193,218,154,135,82,138,195,251,123,201,229,66,176,116,170,117,139,79,157,
222,245,179,215,79,254,225,137,255,207,85,250,243,95,125,226,214,175,254,229,150,113,137,137,136,214,185,247,248,32,67,189,48,57,95,101,126,46,100,121,105,157,122,57,70,232,122,80,75,161,135,1,251,143,
104,228,71,146,40,25,34,155,30,55,95,244,153,122,213,4,145,2,52,160,133,158,172,179,239,30,131,190,221,64,66,131,48,68,181,66,230,110,120,92,125,78,226,21,51,16,9,32,208,192,213,217,114,116,141,157,247,
131,74,164,208,148,195,198,172,199,249,87,67,194,64,64,102,3,77,79,17,75,123,116,247,153,12,247,181,49,186,37,202,202,122,149,147,47,175,227,58,22,42,112,248,228,187,139,27,255,243,47,62,208,241,67,129,
47,62,243,239,126,238,61,95,187,239,75,155,53,64,179,217,63,145,230,221,15,13,18,208,160,81,107,82,171,123,212,106,30,126,32,144,129,194,107,104,4,13,8,195,22,177,172,142,110,64,101,213,193,175,107,232,
166,129,20,10,17,104,40,205,67,249,38,161,227,97,166,27,232,241,16,165,52,252,86,136,211,48,144,90,10,68,72,16,128,97,69,144,34,196,245,90,152,73,151,100,214,32,8,28,170,101,11,73,12,51,30,160,199,93,
148,136,160,235,14,169,132,65,44,17,35,155,176,16,210,226,201,23,103,121,253,82,19,165,98,68,99,30,223,255,200,217,255,245,232,59,63,250,175,254,171,115,248,251,179,99,255,219,102,13,66,13,178,105,139,
123,247,245,16,51,109,54,90,18,93,26,116,118,70,201,231,20,134,22,225,245,51,107,28,63,222,69,215,160,197,245,73,151,185,169,22,174,187,137,153,16,24,102,20,95,233,72,13,164,146,8,17,5,77,160,116,3,45,
140,161,137,16,133,9,70,128,150,113,9,61,137,12,20,134,116,9,165,134,175,37,208,68,148,0,69,171,37,48,172,144,237,7,12,182,142,71,89,93,9,120,229,244,38,251,79,228,81,178,133,84,58,118,208,162,233,251,
164,83,17,14,29,104,103,122,105,138,194,70,128,215,112,248,250,149,61,159,24,204,126,250,127,233,62,252,91,246,15,0,95,124,230,223,253,252,159,188,124,127,103,32,193,144,54,135,247,116,18,79,135,44,108,
54,121,233,226,34,219,198,250,153,124,237,14,187,118,141,242,236,55,110,179,190,90,103,116,119,150,243,223,47,112,242,233,34,181,98,64,44,186,130,10,3,90,181,118,8,116,64,129,82,128,120,187,41,9,74,128,
10,65,136,183,27,64,168,33,180,42,86,188,138,66,226,214,19,40,101,129,1,72,9,102,64,50,169,115,255,195,221,12,111,51,121,238,228,42,111,188,230,243,232,47,164,184,116,245,22,227,219,6,184,115,243,14,7,
247,141,144,75,106,28,220,219,195,83,47,108,18,186,38,255,199,197,120,252,103,118,183,253,203,110,248,237,31,0,62,191,54,240,47,202,13,64,132,116,231,53,246,110,77,49,85,172,49,183,208,34,34,18,44,46,
85,137,37,178,220,190,225,50,63,21,242,145,143,142,114,115,122,147,167,158,91,69,211,5,35,91,97,172,167,3,43,155,36,176,82,200,80,160,16,132,66,17,170,16,8,64,1,74,123,27,90,128,250,207,131,33,132,14,
90,27,194,43,97,250,138,64,51,81,86,18,21,234,148,27,77,230,231,170,172,46,10,30,123,114,131,7,188,4,31,248,185,33,190,246,71,107,220,186,148,32,147,235,98,126,161,129,30,203,113,233,122,137,137,225,24,
59,134,51,92,190,181,198,194,162,64,216,14,39,167,183,126,236,232,255,19,248,214,201,63,58,248,249,243,247,111,13,209,209,69,157,221,219,219,105,181,60,150,54,21,183,103,29,246,108,237,228,250,237,219,
236,220,57,193,233,191,152,225,232,131,105,136,8,78,63,221,32,22,143,112,96,87,140,67,59,44,242,17,3,25,107,163,41,13,124,215,67,72,129,161,27,196,44,137,165,41,220,160,133,82,33,82,51,254,51,168,134,
166,9,124,36,94,8,205,114,12,183,88,68,211,37,154,101,146,72,167,208,99,89,138,149,54,206,95,88,228,236,107,101,94,124,169,206,7,63,16,229,200,35,9,46,190,186,198,67,63,53,192,157,183,102,24,222,218,195,
228,245,101,210,169,8,81,173,202,222,157,121,22,87,54,9,149,193,23,94,111,111,127,255,201,255,253,39,118,62,244,203,223,210,1,230,91,217,127,58,181,30,10,133,79,54,45,25,27,76,115,249,250,38,117,21,35,
244,67,202,141,16,95,37,216,88,87,104,190,98,247,254,4,79,191,188,73,136,197,59,246,192,129,221,57,230,54,87,185,120,165,201,122,169,72,177,174,19,184,33,4,62,134,102,211,158,114,233,109,147,244,118,165,
200,119,165,48,18,18,221,76,162,84,148,165,149,2,83,211,43,172,206,123,84,170,16,6,62,49,35,192,52,21,86,194,36,223,149,99,96,172,155,99,199,70,48,172,21,158,57,181,206,203,103,215,120,228,193,62,174,
189,85,100,125,217,67,137,24,149,42,40,105,176,81,214,105,54,42,28,221,217,205,249,84,133,213,138,162,92,247,153,172,116,254,194,78,120,27,248,245,149,158,71,194,32,64,200,128,225,190,12,10,159,233,149,
6,150,105,96,69,77,214,55,60,12,35,203,210,124,129,137,137,24,213,150,199,252,230,6,19,99,17,182,12,181,241,196,139,147,204,44,74,18,233,52,61,93,9,70,71,45,18,49,11,183,233,82,92,88,164,188,180,201,155,
151,151,184,232,215,233,25,72,48,190,119,136,80,6,188,245,250,117,230,175,204,225,91,29,244,76,236,99,98,124,148,108,79,134,104,52,164,89,43,179,182,89,99,106,102,157,243,215,55,25,236,109,227,254,251,
6,153,219,86,231,218,181,34,85,167,197,196,206,56,139,115,45,162,109,49,10,235,46,177,72,156,66,41,100,83,192,93,45,155,177,193,44,203,151,54,112,149,224,228,108,215,209,253,47,125,214,212,103,95,248,
220,216,119,174,223,223,73,248,246,182,178,117,36,205,236,98,133,102,24,197,174,128,76,199,105,150,60,210,185,36,133,114,149,163,71,18,220,89,168,33,2,131,221,35,57,106,126,136,47,13,30,121,199,22,186,
251,115,180,156,6,245,122,19,61,8,72,71,13,182,110,233,68,151,121,38,39,251,184,248,234,85,22,166,110,178,120,237,18,158,40,18,202,24,237,195,39,56,240,174,7,216,113,168,31,67,73,86,215,91,148,171,30,
145,108,27,91,211,17,238,218,39,217,168,71,184,121,101,147,106,189,204,222,109,121,110,93,107,49,61,83,98,100,48,207,141,197,42,145,182,118,234,181,6,185,108,148,74,173,138,25,141,114,107,169,206,232,
104,142,243,87,10,56,74,241,212,205,124,252,127,186,75,28,213,107,78,228,238,201,13,83,132,74,145,142,11,58,218,13,46,93,178,9,195,60,173,166,67,52,97,210,106,249,88,174,134,48,20,201,188,206,218,117,
143,104,36,78,54,99,208,217,1,35,91,118,115,253,186,195,119,191,123,19,25,105,146,136,39,241,107,14,245,213,6,201,168,207,93,135,210,76,236,106,195,109,236,226,130,222,143,235,20,136,135,46,154,149,99,
108,119,47,71,143,111,225,198,84,137,39,158,186,67,189,172,209,222,109,16,77,71,160,50,135,215,18,108,187,107,23,143,62,58,76,52,238,177,178,18,16,141,198,88,93,182,217,59,174,97,70,61,154,94,136,109,
11,90,174,73,171,5,154,21,103,234,246,50,187,182,119,145,78,73,10,69,40,84,125,138,118,234,33,125,213,73,61,16,120,0,33,185,156,137,174,9,214,230,193,203,155,56,158,139,238,74,124,79,210,176,21,209,184,
192,176,52,234,117,133,212,5,166,9,150,80,156,61,179,202,203,23,75,28,186,187,157,124,162,143,169,235,54,71,239,78,35,90,139,76,223,44,81,220,168,161,182,152,140,142,70,184,126,71,199,49,58,177,69,64,
70,5,236,24,74,224,170,22,75,27,117,182,108,73,176,247,209,30,162,70,140,51,103,151,25,222,214,71,163,25,229,233,23,103,216,40,199,121,239,35,219,176,140,22,186,105,83,171,131,212,52,34,9,73,195,81,4,
174,160,229,73,124,95,199,247,12,54,214,36,154,82,116,182,25,20,11,62,126,24,50,91,207,61,168,79,85,50,251,252,64,32,80,116,116,70,112,106,130,74,33,64,207,132,132,190,196,119,21,42,16,120,174,79,54,35,
65,73,252,64,17,136,16,223,211,113,81,228,122,5,63,51,49,196,246,193,12,79,60,185,192,27,103,215,24,232,215,57,178,15,122,186,250,112,93,31,83,64,49,112,104,207,251,56,155,30,174,166,147,204,198,168,134,
54,185,16,78,236,233,199,208,37,90,10,206,188,182,194,185,51,107,36,238,151,60,252,174,78,6,119,181,83,93,107,226,123,18,207,147,248,202,37,8,5,18,65,60,22,82,44,41,8,66,28,15,84,0,161,15,78,201,160,89,
244,232,108,139,114,253,86,5,144,220,44,38,71,229,100,33,218,77,168,35,52,69,54,163,83,47,11,156,86,128,105,40,100,232,163,139,183,7,67,19,138,152,165,163,9,29,37,92,92,215,163,82,83,152,97,132,142,84,
132,100,68,199,15,160,103,48,198,192,93,38,61,131,81,86,22,51,156,124,246,14,229,102,5,105,24,20,235,62,228,162,248,122,6,61,180,136,166,4,155,13,133,22,88,172,87,54,249,15,223,121,157,233,183,26,12,117,
166,24,221,147,162,183,55,134,240,12,44,25,146,204,8,132,233,82,173,134,56,142,14,210,67,34,137,70,117,164,4,73,136,16,10,25,134,24,18,156,102,64,181,96,147,205,198,80,90,72,16,198,88,40,89,113,125,169,
28,137,42,64,74,65,50,110,82,221,176,81,142,134,41,53,132,8,209,12,19,37,90,24,82,195,210,64,26,32,53,16,77,139,133,213,50,195,3,93,60,123,106,129,153,27,62,35,99,121,198,183,102,56,188,109,128,139,175,
53,185,117,113,150,237,59,227,180,167,59,169,52,109,164,165,17,211,18,24,170,74,168,5,104,90,26,205,200,178,86,115,201,228,83,152,97,156,47,253,249,53,246,238,238,98,255,120,27,126,179,196,119,190,181,
192,155,119,170,116,143,235,124,248,167,118,178,176,80,193,15,124,116,45,142,110,200,183,255,10,93,17,160,136,104,96,11,137,161,11,132,45,168,52,37,169,188,133,161,73,124,207,99,163,101,232,250,90,83,
234,8,15,41,5,81,203,162,232,216,132,142,129,161,12,116,4,166,244,209,177,177,52,11,161,20,81,203,192,212,5,182,48,185,61,181,206,174,173,121,222,253,193,9,222,120,109,157,235,151,108,166,159,89,2,225,
19,139,25,236,191,167,151,195,71,50,120,162,74,203,243,104,139,71,88,82,13,66,173,133,223,140,82,108,70,233,207,103,168,215,93,82,49,131,247,188,119,156,84,199,50,87,47,22,184,116,205,33,29,111,145,140,
107,220,115,95,63,251,142,247,177,182,209,226,226,229,50,161,76,162,233,1,17,75,96,40,29,67,26,4,194,195,212,5,186,244,209,205,128,192,53,105,57,146,118,19,12,77,225,121,30,197,150,161,233,117,207,144,
66,40,164,144,104,66,67,138,16,229,73,164,9,34,230,162,69,155,104,134,11,22,4,34,36,22,211,73,36,37,165,178,75,171,25,227,204,169,101,238,127,52,205,35,63,214,207,209,187,109,74,213,58,190,107,144,78,
153,164,83,146,208,85,84,170,6,34,110,160,72,179,178,166,216,168,102,241,92,11,74,62,41,67,32,226,22,5,207,35,27,145,188,243,254,110,142,31,202,82,41,5,132,97,149,76,214,36,159,237,98,113,209,230,228,
183,87,169,85,162,16,175,147,77,10,82,9,147,128,22,166,153,192,181,28,34,166,194,208,193,20,18,229,107,40,33,176,180,0,65,128,18,58,182,175,9,29,101,130,80,111,159,107,149,32,26,213,32,4,213,178,49,133,
129,230,89,196,66,19,25,186,120,202,193,39,96,231,93,61,212,91,139,132,141,128,245,85,197,87,254,244,18,7,14,143,48,177,55,65,174,203,66,211,226,120,129,135,221,172,32,66,141,184,149,68,24,89,174,92,93,
99,249,118,9,17,137,32,77,157,234,130,205,242,157,117,38,14,183,35,125,48,92,23,199,215,208,116,65,119,91,2,187,238,82,90,83,156,127,97,141,11,231,214,168,213,163,232,29,46,233,84,149,157,219,199,8,53,
176,29,133,238,248,196,132,79,212,87,104,161,132,134,0,223,35,26,9,208,2,227,237,149,12,19,33,21,122,194,8,20,104,194,15,124,2,63,36,157,181,16,170,70,125,50,32,219,41,241,151,47,145,174,251,216,90,15,
174,102,177,184,92,39,158,176,56,124,162,131,250,122,153,198,156,207,237,27,146,83,79,46,112,230,69,159,116,222,34,149,15,201,100,108,238,218,215,65,79,191,32,8,170,204,190,85,224,141,199,78,146,212,119,
161,220,14,2,175,9,192,107,143,191,140,206,65,38,246,223,69,36,5,83,75,85,94,120,101,5,103,211,197,104,181,168,44,251,172,111,26,68,218,227,180,109,247,233,30,210,233,233,152,32,22,77,50,185,84,199,173,
27,232,165,42,102,115,145,160,190,68,50,218,73,105,174,12,170,73,38,147,36,112,193,247,67,132,18,88,90,168,244,182,132,227,75,210,38,174,141,211,104,210,217,157,100,203,94,29,175,97,179,58,121,13,63,188,
130,217,42,226,234,131,164,6,143,49,215,163,168,235,14,66,57,76,108,105,163,109,66,112,232,1,147,154,237,225,84,108,52,95,160,27,13,58,50,105,114,29,73,138,205,58,115,119,26,92,57,57,143,162,141,88,87,
158,198,212,50,82,53,136,141,142,208,88,138,242,198,147,23,169,251,25,6,119,247,210,211,147,228,193,187,37,181,245,58,97,211,193,85,2,35,17,199,138,197,81,17,65,37,8,88,93,104,80,106,214,144,4,20,230,
61,170,51,139,104,254,101,194,176,76,104,141,146,238,56,193,200,222,56,157,29,81,86,55,61,240,36,154,20,164,34,110,168,247,166,107,45,33,146,102,24,40,42,229,6,218,80,27,97,210,166,232,151,216,245,206,
173,164,59,238,194,8,2,138,235,54,55,46,52,121,243,220,50,3,123,219,112,55,99,188,248,234,10,59,15,10,134,118,118,48,222,27,37,163,199,16,70,128,79,18,131,128,213,66,147,149,146,203,212,82,157,48,218,
73,166,171,31,91,11,73,117,167,128,20,82,19,152,67,59,169,151,91,44,204,213,32,183,66,68,198,25,31,204,34,250,64,11,44,26,34,74,37,136,177,80,106,49,119,249,54,51,175,217,200,45,221,100,218,36,179,111,
109,210,116,20,59,30,222,70,123,199,46,48,124,74,235,33,55,46,86,177,162,58,50,22,161,214,42,18,122,64,68,210,17,15,124,125,44,235,172,43,84,90,133,138,114,197,227,234,205,53,54,106,21,30,124,96,132,92,
46,100,113,213,193,247,21,253,219,44,146,227,89,206,63,61,137,91,104,210,32,197,226,245,105,10,231,95,167,241,227,15,83,56,208,71,52,21,146,209,18,100,162,17,188,48,228,206,92,11,87,38,113,189,77,140,
188,98,239,129,30,150,87,215,153,85,16,10,139,221,99,49,146,177,8,23,174,172,67,16,34,9,184,51,187,129,229,128,102,250,172,181,2,234,66,82,173,134,76,95,89,102,242,27,223,69,185,189,116,117,118,80,47,
217,56,110,200,131,63,214,75,44,169,40,172,52,209,60,24,27,79,208,209,147,227,212,179,83,188,121,117,21,167,81,35,8,5,72,143,254,164,211,208,135,83,149,203,154,100,76,73,131,141,13,135,102,0,209,68,132,
142,238,20,183,110,204,48,115,81,195,53,52,114,155,85,142,221,157,34,159,75,80,109,249,100,183,4,12,61,52,70,99,42,193,181,146,69,185,152,164,215,146,24,73,137,215,148,156,123,107,13,21,73,144,203,196,
200,245,119,99,153,33,91,183,229,73,37,35,188,57,61,131,211,106,209,49,60,196,96,183,65,77,184,212,154,26,45,21,163,80,105,177,176,88,225,174,157,237,104,81,141,122,221,103,181,108,179,190,46,232,222,
123,20,109,40,71,100,32,78,227,118,129,108,78,210,217,101,242,234,171,235,20,22,52,148,13,67,251,203,236,216,155,37,154,23,44,44,219,136,90,72,168,129,38,53,182,230,106,179,122,87,180,113,90,211,248,128,
146,6,149,130,67,44,149,196,247,234,148,27,77,90,149,12,203,23,26,104,29,54,219,246,118,99,180,52,106,173,16,153,137,162,5,144,31,200,208,53,214,139,46,90,244,101,44,70,219,45,26,45,143,231,94,157,163,
238,38,200,116,38,208,109,151,3,99,93,228,114,49,100,232,210,150,79,177,111,87,26,189,214,162,39,97,96,232,138,253,187,250,89,44,135,204,220,174,96,186,26,69,199,228,205,115,203,220,119,172,143,237,29,
9,18,212,201,28,206,81,243,211,212,149,142,104,134,72,83,82,173,216,180,66,73,190,61,198,204,153,58,246,82,72,127,127,6,187,20,193,113,33,20,80,223,180,145,210,68,23,62,3,137,210,11,122,198,168,191,180,
37,31,168,73,71,136,70,169,65,116,231,16,166,89,230,220,217,101,68,37,131,20,17,160,137,219,12,56,125,102,153,150,237,211,157,144,180,108,141,148,213,96,119,167,79,38,17,65,147,1,235,51,43,220,120,171,
73,88,138,224,149,203,108,76,215,241,163,38,5,177,74,196,50,136,231,37,187,239,238,224,29,247,229,72,250,38,213,77,120,249,187,43,52,87,155,204,172,123,56,142,70,46,111,96,153,10,79,40,206,188,56,203,
150,177,24,189,221,17,6,6,36,51,155,146,59,139,33,117,47,196,204,70,240,55,26,188,126,106,133,142,206,36,34,148,72,149,98,109,17,202,173,117,36,58,109,169,8,203,165,58,34,209,77,38,238,144,183,90,207,
234,195,15,254,234,91,239,185,249,124,241,247,55,242,121,215,85,56,213,34,7,142,116,115,243,66,153,74,45,0,77,32,84,140,229,185,6,213,250,38,189,3,157,56,182,139,50,235,164,34,22,131,189,121,174,92,46,
113,230,213,69,132,163,211,223,97,48,49,17,34,244,28,182,35,81,66,163,94,245,89,154,41,33,171,30,155,155,1,91,39,50,24,166,205,171,175,173,51,187,214,100,207,72,130,209,189,25,162,49,141,92,68,163,214,
180,105,186,1,229,154,224,220,75,5,76,43,224,208,225,126,182,237,110,163,210,172,178,185,28,160,90,146,174,182,78,86,231,55,176,109,139,64,3,77,179,169,215,125,140,118,155,131,135,243,168,149,250,219,
23,10,41,120,96,180,110,167,44,251,140,14,112,119,239,202,115,159,209,218,63,36,34,73,214,110,76,179,239,222,187,209,125,139,83,183,138,8,41,9,2,3,195,20,188,231,253,19,172,172,55,185,112,203,39,154,117,
73,70,146,172,46,21,57,253,210,28,253,91,134,185,255,238,24,185,24,68,34,146,32,16,4,42,36,148,30,154,102,80,41,101,40,110,184,220,190,92,96,105,170,132,166,67,182,195,96,247,137,30,118,143,39,48,211,
17,76,229,18,69,81,247,18,111,123,65,2,69,185,217,199,107,23,139,60,126,106,150,127,20,55,200,196,19,200,86,147,106,185,201,142,241,54,14,30,28,231,220,203,85,252,192,69,23,10,167,33,217,186,163,143,241,
241,144,199,159,159,132,72,10,169,133,188,107,116,229,194,150,123,255,121,83,7,24,140,21,254,172,63,195,135,86,27,105,202,11,27,172,222,42,224,201,40,65,32,16,34,0,165,35,164,162,167,43,2,162,133,122,
43,192,245,77,86,86,155,116,196,99,88,122,200,246,113,193,96,15,248,245,16,219,182,113,67,137,46,227,72,36,186,161,104,75,66,119,62,198,224,72,28,41,37,17,45,68,10,19,77,58,4,78,64,209,22,232,66,225,27,
33,154,110,98,42,13,37,93,204,124,200,192,112,134,139,87,99,216,161,193,234,122,1,207,19,4,158,75,79,123,72,127,183,206,5,205,231,255,210,19,130,64,226,57,58,235,183,151,89,93,114,16,189,237,196,98,46,
91,147,155,95,249,191,179,150,19,15,255,143,207,253,179,133,167,102,127,99,115,112,144,68,150,91,231,230,73,142,143,130,124,59,111,172,73,15,223,15,48,67,159,189,91,211,188,241,198,38,235,117,139,169,
90,129,237,163,9,70,199,210,76,190,53,67,127,126,43,217,116,140,64,19,8,75,17,42,80,34,206,133,43,139,76,222,40,208,159,201,210,172,189,125,115,49,245,128,114,73,146,238,146,152,73,151,104,135,193,177,
221,121,124,21,224,4,2,93,180,208,116,131,165,37,141,83,207,92,97,100,52,131,64,48,57,89,69,232,41,186,146,9,246,141,182,81,173,7,120,110,3,37,53,66,33,145,154,77,169,220,162,116,117,157,48,26,71,26,240,
243,251,11,229,76,164,254,229,31,200,75,31,239,157,255,99,43,50,240,57,149,137,176,190,176,64,144,113,144,66,162,8,9,21,248,202,35,21,211,233,79,27,236,223,158,224,123,47,185,24,70,140,169,27,27,236,217,
55,200,181,171,203,60,254,237,41,14,31,26,166,119,56,66,224,1,154,139,140,4,212,106,77,138,229,16,183,90,103,237,78,136,225,232,104,50,202,92,33,32,221,95,102,100,135,160,39,34,104,213,76,140,80,208,176,
77,66,35,202,244,84,131,103,159,184,77,102,32,198,129,163,3,60,247,196,12,161,147,39,176,91,236,63,156,164,59,39,81,56,4,202,69,6,25,132,50,208,84,72,125,179,78,105,182,132,222,54,136,180,4,143,14,205,
125,117,232,254,95,243,127,0,184,43,82,254,163,143,31,216,252,237,63,125,33,157,213,147,157,120,78,128,47,5,50,208,9,2,8,149,196,20,10,205,247,56,180,183,131,87,174,223,161,85,141,48,59,229,34,101,129,
163,39,70,184,21,89,229,220,217,57,196,89,139,122,211,35,212,60,122,7,117,218,186,50,116,119,106,84,202,138,74,205,161,93,143,162,66,3,77,151,88,169,52,88,30,205,134,226,63,125,251,26,170,169,177,190,
228,19,250,22,94,104,176,237,96,154,163,15,117,241,202,139,101,22,231,124,98,125,62,157,81,151,35,119,37,209,252,16,83,8,2,12,68,96,19,42,137,194,196,107,132,132,153,78,132,48,121,223,206,146,61,16,221,
248,215,255,47,109,105,224,190,223,8,63,208,252,247,159,254,179,243,199,62,99,107,9,210,241,8,209,68,128,155,108,162,197,109,218,115,17,18,73,3,79,135,142,54,139,247,221,211,206,215,190,55,195,102,173,
135,133,83,37,28,35,194,253,39,122,25,24,109,99,109,177,65,40,52,124,17,98,68,61,170,45,184,181,182,65,54,151,37,218,30,80,152,122,91,144,75,140,218,180,15,165,89,89,43,210,213,147,101,247,193,12,65,203,
199,87,38,186,50,233,234,136,17,239,211,120,229,197,21,46,157,92,37,53,216,129,163,138,60,122,95,39,109,157,2,108,65,198,138,210,147,213,89,77,110,34,92,141,72,50,130,153,50,240,73,160,9,159,127,178,253,
214,127,24,122,199,175,151,255,171,98,218,161,31,251,248,191,253,228,202,211,159,248,87,207,118,244,234,229,18,29,154,205,224,143,167,24,31,237,98,116,52,201,181,165,117,46,92,172,176,99,184,147,35,123,
186,216,184,199,227,123,47,214,16,229,8,175,127,123,157,150,35,56,122,111,59,7,142,198,80,34,192,13,21,66,83,76,207,217,40,127,149,168,22,210,191,61,67,185,203,7,41,72,165,243,232,90,157,192,117,232,235,
77,177,117,36,1,126,128,37,21,142,33,89,46,135,156,122,178,196,27,223,47,18,201,101,32,86,228,125,71,114,236,26,239,228,244,235,85,110,222,88,97,223,158,8,63,253,254,65,118,28,200,49,127,189,193,194,149,
101,42,213,56,13,229,240,203,199,26,213,225,228,198,47,255,181,166,150,142,226,19,167,95,47,108,249,232,236,90,76,212,102,86,208,237,69,142,60,176,131,142,182,24,143,61,51,203,217,51,45,46,93,44,19,250,
85,126,236,157,35,196,83,46,43,27,45,220,205,44,243,111,149,217,44,214,240,77,129,30,137,162,25,18,41,60,66,165,115,237,198,38,118,209,97,98,187,78,53,108,33,163,62,195,91,96,122,178,130,52,92,14,28,236,
38,26,7,79,57,20,91,138,27,215,21,103,255,114,157,107,167,87,208,114,9,172,33,159,247,60,156,229,29,71,122,120,236,177,21,190,241,173,101,166,167,109,28,229,112,124,127,15,202,16,156,127,226,28,211,211,
62,118,170,157,241,46,141,79,223,125,246,167,199,31,252,149,107,127,45,112,126,248,200,234,96,235,217,158,239,220,233,58,160,162,57,42,151,103,89,173,173,208,191,107,136,164,97,49,61,91,197,177,51,220,
190,81,39,29,15,120,207,241,62,186,250,53,86,245,10,149,178,98,243,70,139,217,27,45,86,11,33,181,166,79,195,181,241,67,141,217,37,135,165,185,128,132,8,184,231,96,7,195,189,73,110,191,89,103,102,86,167,
173,15,186,123,242,108,172,5,76,94,111,112,254,133,42,231,159,46,178,60,215,36,218,107,49,190,95,242,190,119,230,184,119,111,39,207,159,94,231,47,190,89,4,77,17,233,20,60,124,247,0,122,194,226,137,175,
188,196,228,171,5,140,109,99,104,105,159,63,125,215,229,239,223,243,238,95,248,237,191,177,79,235,207,191,254,216,213,79,60,185,101,167,177,102,209,184,117,134,189,63,190,133,127,244,225,251,184,126,105,
141,239,63,87,164,182,150,192,106,86,248,224,79,117,242,206,247,116,209,116,60,46,94,169,240,218,107,21,238,92,113,168,174,216,16,143,16,237,145,244,143,69,208,244,128,149,105,168,222,214,232,205,53,8,
67,141,149,130,78,122,68,163,111,194,199,241,35,44,76,186,56,171,77,66,59,32,215,101,49,180,83,103,223,129,12,7,246,100,137,71,13,158,127,122,149,111,125,113,149,70,34,70,172,203,230,145,7,178,28,216,
215,203,169,175,191,194,153,239,222,194,152,56,140,108,215,249,228,3,75,43,63,59,113,190,175,255,238,223,10,255,198,192,211,207,127,54,245,197,27,119,205,254,241,11,157,89,183,0,114,242,85,14,189,107,
43,247,252,236,49,110,79,174,242,236,169,2,165,219,17,100,197,231,196,59,211,188,251,189,105,182,108,49,168,181,116,102,151,107,220,158,172,50,117,39,96,189,100,35,19,54,169,182,40,133,89,131,141,171,
73,130,98,141,208,149,232,121,73,219,78,65,207,144,77,165,236,96,183,162,116,230,34,140,12,43,198,70,18,12,247,164,136,198,4,139,243,54,39,159,88,230,244,227,53,130,104,158,248,142,38,239,188,63,201,174,
109,93,60,247,87,175,112,241,155,111,162,198,78,64,119,132,15,30,168,183,126,231,248,11,59,6,142,255,250,204,223,218,137,119,235,228,103,38,62,119,245,240,133,255,120,174,45,166,47,122,184,83,175,177,
243,29,61,60,244,225,7,169,86,27,156,124,118,131,153,55,35,4,139,1,237,61,62,187,31,142,178,239,72,27,91,7,13,82,113,11,223,13,169,217,62,53,207,227,250,76,153,231,78,213,88,187,101,16,44,43,52,215,132,
238,144,246,221,45,30,184,39,197,190,241,28,86,196,35,17,137,160,107,38,181,150,98,110,186,202,165,243,107,156,59,229,179,49,159,68,239,118,24,220,87,229,129,135,6,201,118,26,60,247,31,223,224,234,83,
51,132,19,251,160,63,202,123,71,90,254,239,60,112,234,225,109,247,253,218,233,255,102,235,225,181,167,62,119,248,143,223,58,122,250,27,151,50,81,181,82,197,185,254,58,91,118,180,241,200,207,61,68,182,
35,206,75,175,175,114,249,76,147,234,29,5,85,69,52,45,233,223,145,96,104,151,197,240,160,69,103,206,34,151,53,169,58,54,223,124,124,158,165,169,52,229,171,6,210,241,73,239,181,233,156,8,120,223,187,186,
200,167,163,148,74,54,197,117,155,133,105,151,233,107,13,230,174,183,168,151,67,72,232,36,7,35,236,57,161,115,240,238,44,193,70,192,201,47,62,197,237,203,117,172,173,199,8,123,35,60,178,189,238,125,234,
196,169,15,237,121,224,215,190,251,119,54,151,222,126,238,179,59,255,252,234,158,151,62,127,110,32,235,21,117,188,235,231,73,198,10,28,254,208,97,238,186,111,59,165,138,207,197,87,43,220,188,90,163,182,
20,192,122,26,229,7,144,168,97,100,36,137,14,131,92,191,36,153,211,176,235,81,102,206,218,72,71,49,112,159,137,158,246,80,37,151,194,92,64,173,160,104,22,36,52,34,16,169,35,50,130,76,87,148,225,61,176,
247,88,134,206,116,156,235,47,221,224,204,127,122,133,114,181,147,200,206,173,136,54,157,159,220,91,105,253,202,225,51,143,110,187,247,135,127,217,191,181,125,120,227,234,23,114,223,185,212,125,246,55,
159,31,157,240,10,58,225,212,28,222,250,117,250,247,38,57,254,222,19,140,141,15,178,89,183,185,126,99,147,169,155,13,138,75,10,167,34,113,92,9,34,132,184,203,248,254,36,137,132,160,89,12,33,52,136,182,
187,52,234,138,59,151,28,194,74,12,41,91,88,134,196,72,154,164,123,60,134,39,76,118,110,235,32,159,137,49,117,103,153,115,223,126,158,165,215,87,113,59,15,32,183,142,146,72,218,252,250,61,243,203,63,189,
253,234,125,3,199,127,245,246,143,196,32,254,204,119,191,250,213,223,121,101,247,79,95,158,77,73,177,230,225,77,222,64,99,129,225,253,109,236,122,112,55,195,219,135,64,74,138,21,155,133,249,10,27,107,
62,213,170,71,173,222,34,147,181,16,102,64,190,35,138,144,33,133,21,129,167,28,74,37,143,88,52,78,54,227,209,149,183,232,237,111,167,61,29,65,15,125,38,39,231,185,242,220,85,102,223,152,193,145,157,200,
145,195,104,29,22,163,125,5,245,187,39,238,60,125,164,107,246,221,93,199,127,51,252,145,150,0,92,123,246,143,31,252,171,185,137,175,255,209,217,124,103,171,146,196,95,174,227,207,223,66,58,115,180,143,
167,25,60,60,206,196,142,113,186,7,58,136,36,76,132,174,8,61,133,46,224,230,76,145,179,231,230,33,12,57,114,104,144,93,35,57,84,0,202,20,168,16,156,154,195,234,226,42,147,111,221,97,250,245,219,172,220,
44,226,27,3,24,131,187,209,123,146,152,201,128,143,31,92,46,127,104,252,198,47,237,125,228,227,223,250,239,90,228,241,242,19,95,254,253,111,79,15,127,236,171,23,219,82,20,77,188,13,23,123,101,154,176,
50,71,196,116,73,117,89,164,6,178,100,251,219,232,236,202,144,200,70,145,145,12,43,235,62,40,159,238,46,157,176,233,81,47,55,216,88,43,80,154,47,80,154,43,80,94,175,225,187,113,180,212,48,162,103,11,70,
135,69,36,169,120,255,158,245,214,7,199,239,124,125,48,185,252,177,145,251,63,25,254,183,196,252,119,46,227,153,127,254,247,228,66,51,247,233,83,203,195,255,228,11,111,12,117,214,43,58,78,45,36,168,20,
161,80,132,202,58,190,91,2,28,4,18,211,80,88,166,4,116,28,207,199,245,196,219,82,136,210,145,102,27,90,170,13,145,205,163,167,51,88,41,129,149,86,252,227,125,243,165,71,6,102,190,217,31,223,252,205,145,
7,254,69,245,31,76,161,214,213,103,63,255,225,59,181,220,63,62,61,223,119,236,153,169,142,120,169,168,112,109,29,191,21,16,216,62,202,83,224,182,8,125,9,90,128,144,2,161,199,16,134,196,140,8,100,212,64,
183,2,242,105,193,241,177,162,253,240,192,236,27,19,217,141,175,239,121,232,227,159,255,7,89,153,246,3,240,207,252,225,131,101,47,121,255,82,51,115,255,237,106,118,108,161,26,77,172,55,149,94,111,90,90,
211,137,8,165,185,68,133,80,137,88,16,230,147,77,111,32,225,54,71,211,213,233,193,104,249,165,140,209,120,62,166,213,158,31,121,248,147,246,223,119,92,255,231,0,155,145,123,157,217,123,91,182,0,0,0,0,
73,69,78,68,174,66,96,130,0,0};

const char* JuceDemoPluginAudioProcessorEditor::downMaya_png = (const char*) resource_JuceDemoPluginAudioProcessorEditor_downMaya_png;
const int JuceDemoPluginAudioProcessorEditor::downMaya_pngSize = 9290;

// JUCER_RESOURCE: mayaKnobtest_png, 8092, "../../../Desktop/mayaKnobtest.png"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_mayaKnobtest_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,60,0,0,0,60,8,6,0,0,0,58,252,217,114,0,0,0,9,112,72,89,
115,0,0,11,19,0,0,11,19,1,0,154,156,24,0,0,0,4,103,65,77,65,0,0,177,142,124,251,81,147,0,0,0,32,99,72,82,77,0,0,122,37,0,0,128,131,0,0,249,255,0,0,128,233,0,0,117,48,0,0,234,96,0,0,58,152,0,0,23,111,146,
95,197,70,0,0,31,18,73,68,65,84,120,218,204,155,121,108,156,249,121,223,63,243,190,115,207,112,14,14,103,56,228,12,57,188,73,241,144,68,138,90,105,47,29,222,213,106,237,172,183,27,196,94,163,72,234,254,
209,166,104,128,34,45,16,4,233,31,117,224,20,72,139,54,61,208,20,8,144,52,112,141,26,246,218,94,108,118,237,93,173,165,174,180,171,93,173,184,58,168,155,20,205,251,154,225,112,134,28,114,238,243,61,250,
135,242,254,34,217,73,27,39,118,154,1,8,104,142,247,213,239,249,253,158,227,251,253,62,207,107,210,117,157,159,247,235,226,111,57,205,193,47,189,243,95,43,170,245,203,133,114,45,88,44,149,37,77,211,208,
117,93,252,73,146,132,174,235,152,76,38,76,38,19,146,36,225,245,120,116,183,203,150,113,152,213,31,140,77,158,252,167,252,2,94,166,159,167,193,247,174,127,112,33,87,179,190,152,74,165,37,69,81,176,217,
108,88,44,22,108,54,27,54,155,13,89,150,49,155,205,194,64,85,85,81,20,5,69,81,168,215,235,212,106,53,234,245,58,141,70,3,139,197,66,91,91,88,115,219,76,55,14,30,121,230,233,191,55,6,95,250,55,62,155,251,
243,239,196,211,123,133,150,66,161,128,203,229,194,233,116,226,118,187,105,106,106,194,229,114,97,181,90,1,208,117,93,24,103,50,153,176,88,44,88,44,22,76,38,19,186,174,83,171,213,40,149,74,20,10,5,138,
197,34,229,114,153,74,165,130,207,231,35,212,226,207,87,223,121,217,247,236,239,103,245,255,47,6,95,248,90,147,201,253,226,159,165,82,153,66,80,85,85,156,78,39,62,159,143,64,32,64,83,83,19,138,162,144,
201,100,216,218,218,34,153,76,178,179,179,67,46,151,163,86,171,241,74,211,251,160,43,188,87,124,21,155,205,134,215,235,165,181,181,149,112,56,76,56,28,38,16,8,96,177,88,40,22,139,226,186,114,185,140,205,
102,163,45,28,44,28,125,234,105,207,223,169,193,183,175,252,240,191,111,100,180,127,161,40,10,78,167,147,230,230,102,218,218,218,176,88,44,172,174,174,114,255,254,125,230,230,230,216,218,218,162,84,42,
161,235,58,178,44,163,105,26,125,125,125,252,171,225,235,160,105,252,231,217,167,88,93,93,69,146,36,20,69,65,150,101,156,78,39,145,72,132,225,225,97,14,30,60,72,44,22,163,86,171,177,189,189,205,254,254,
62,229,114,25,135,195,65,172,189,249,173,209,241,167,191,244,11,53,248,222,127,244,152,242,199,127,80,73,108,165,108,110,183,27,143,199,67,52,26,197,100,50,49,51,51,195,212,212,20,139,139,139,232,186,
142,207,231,35,26,141,18,8,4,240,120,60,56,157,78,178,217,44,79,23,255,128,76,210,132,73,210,8,132,28,124,230,249,77,124,62,31,197,98,145,66,161,192,238,238,46,241,120,156,108,54,139,36,73,12,12,12,240,
204,51,207,48,50,50,130,166,105,108,110,110,146,207,231,169,86,171,116,118,70,149,227,199,159,177,252,44,6,155,255,186,63,156,249,206,43,237,91,99,223,75,148,119,246,240,122,189,68,163,81,252,126,63,15,
31,62,228,252,249,243,44,47,47,227,243,249,56,114,228,8,61,61,61,180,180,180,224,116,58,69,140,86,42,21,242,249,60,74,205,68,120,176,14,154,133,242,94,25,73,146,232,232,232,16,191,171,215,235,148,203,
101,210,233,52,203,203,203,204,207,207,243,167,127,250,167,244,247,247,115,246,236,89,6,7,7,201,100,50,36,147,73,54,55,19,230,82,233,146,222,19,245,158,234,30,156,252,248,231,118,194,15,174,126,251,215,
151,119,92,127,2,208,212,212,68,87,87,23,229,114,153,115,231,206,113,227,198,13,252,126,63,19,19,19,12,12,12,8,67,101,89,166,209,104,144,207,231,201,229,114,68,55,127,19,125,191,142,217,219,160,243,148,
21,169,166,179,122,181,74,181,232,96,166,245,247,104,109,109,197,239,247,139,36,167,170,42,165,82,137,157,157,29,230,231,231,185,117,235,22,249,124,158,167,159,126,154,207,127,254,243,216,237,118,214,
214,214,40,22,139,184,221,110,162,173,77,255,105,104,236,216,111,255,173,13,190,251,233,119,127,111,105,219,252,187,86,171,21,159,207,71,87,87,23,115,115,115,124,239,123,223,163,80,40,112,244,232,81,38,
38,38,8,135,195,216,237,118,242,249,60,203,203,203,44,46,46,178,185,185,73,38,147,33,155,205,114,202,252,25,191,252,249,48,173,67,42,222,195,85,164,154,66,246,129,133,196,178,151,239,190,187,193,77,158,
21,73,175,163,163,131,129,129,1,122,123,123,113,187,221,84,42,21,146,201,36,183,110,221,98,122,122,154,64,32,192,235,175,191,78,127,127,63,171,171,171,100,179,89,52,77,99,168,55,250,253,225,67,79,125,
229,111,108,240,131,171,223,254,245,249,164,237,79,172,86,43,205,205,205,68,163,81,62,253,244,83,222,126,251,109,2,129,0,167,78,157,98,96,96,0,175,215,75,42,149,226,179,207,62,227,206,157,59,172,175,175,
83,169,84,48,155,205,56,28,14,172,86,43,191,22,157,227,115,39,60,4,15,86,160,77,67,174,91,81,183,116,82,243,22,46,93,44,240,221,157,97,106,181,26,149,74,133,70,163,129,203,229,162,171,171,139,137,137,
9,142,31,63,78,48,24,100,111,111,143,133,133,5,46,95,190,76,62,159,231,87,126,229,87,56,126,252,56,155,155,155,100,179,89,26,141,6,195,253,29,255,101,104,236,232,111,253,204,6,207,188,241,74,120,209,254,
79,146,102,179,89,36,160,243,231,207,115,238,220,57,14,28,56,192,243,207,63,79,52,26,197,106,181,242,225,135,31,242,193,7,31,144,72,36,112,56,28,68,34,17,186,187,187,137,197,98,52,55,55,51,153,251,119,
228,178,53,218,187,171,180,140,154,48,7,36,180,186,132,186,87,96,231,65,19,153,53,11,158,22,7,215,253,191,195,254,254,62,107,107,107,44,47,47,147,72,36,168,84,42,116,116,116,112,246,236,89,78,156,56,65,
181,90,101,107,107,139,203,151,47,179,180,180,196,107,175,189,198,169,83,167,136,199,227,20,10,5,0,134,122,35,103,250,14,140,95,252,107,39,173,169,223,119,153,246,15,127,63,41,41,10,46,151,139,72,36,194,
133,11,23,248,193,15,126,192,225,195,135,57,113,226,4,62,159,15,85,85,249,230,55,191,201,71,31,125,132,195,225,224,216,177,99,28,62,124,152,190,190,62,90,90,90,104,52,26,236,237,237,161,165,242,88,205,
118,236,46,11,178,36,179,181,100,70,211,100,34,205,58,46,183,68,222,169,82,175,231,104,110,110,166,175,175,143,231,158,123,142,76,38,195,252,252,60,211,211,211,204,206,206,242,141,111,124,131,120,60,206,
107,175,189,70,32,16,224,133,23,94,64,150,101,222,124,243,77,0,78,159,62,205,234,234,42,197,98,145,120,42,247,65,223,1,76,127,153,109,242,215,191,254,245,159,250,112,89,125,170,82,44,150,205,14,135,131,
88,44,198,103,159,125,198,91,111,189,69,119,119,55,47,190,248,34,94,175,23,73,146,120,227,141,55,248,232,163,143,56,112,224,0,95,248,194,23,120,254,249,231,25,24,24,64,85,85,102,102,102,248,236,179,207,
152,158,158,166,49,255,25,253,125,33,130,237,42,119,111,105,124,244,103,105,126,124,167,132,172,249,232,108,183,82,218,87,248,224,242,54,31,173,91,216,216,216,160,84,42,209,210,210,66,111,111,47,253,253,
253,132,195,97,242,249,60,55,110,220,160,82,169,48,50,50,130,217,108,166,189,189,157,84,42,197,245,235,215,9,6,131,12,13,13,145,207,231,201,231,243,148,74,197,175,181,183,71,254,237,255,243,132,239,93,
121,235,223,167,119,84,123,83,83,19,225,112,152,185,185,57,222,122,235,45,242,249,60,99,99,99,52,55,55,163,40,10,231,207,159,231,211,79,63,229,248,241,227,156,62,125,154,214,214,86,60,30,15,179,179,179,
92,187,118,141,141,141,13,170,213,42,138,162,208,111,5,167,199,193,78,210,68,122,97,159,51,71,66,168,186,196,194,82,153,176,223,139,205,229,98,191,160,176,148,91,98,101,101,133,217,217,89,98,177,24,147,
147,147,140,140,140,48,62,62,78,40,20,226,210,165,75,124,242,201,39,120,189,94,78,159,62,141,207,231,99,120,120,152,153,153,25,222,124,243,77,220,110,183,216,132,181,181,117,185,201,97,121,103,112,228,
240,107,127,229,9,127,252,181,144,148,244,253,131,15,28,14,7,213,106,149,66,161,192,194,194,2,141,70,131,82,169,36,160,225,135,31,126,200,212,212,20,207,60,243,12,167,78,157,162,185,185,25,183,219,205,
229,203,151,185,112,225,2,235,235,235,2,47,107,154,198,145,64,146,225,49,63,169,68,14,127,75,25,167,95,199,226,110,96,183,53,168,100,27,52,251,156,44,46,231,120,88,105,3,160,92,46,179,189,189,205,198,
198,6,138,162,208,221,221,141,221,110,39,18,137,160,235,58,31,125,244,17,169,84,138,114,185,204,237,219,183,209,52,141,142,142,14,84,85,197,98,177,80,175,215,113,56,28,20,74,149,161,222,222,222,223,251,
43,147,214,213,143,63,72,238,102,203,97,128,253,253,125,34,145,8,45,45,45,84,42,21,238,222,189,203,119,190,243,29,234,245,58,138,162,48,54,54,198,43,175,188,130,197,98,33,28,14,115,241,226,69,166,166,
166,104,105,105,33,20,10,61,65,8,62,111,253,51,198,199,253,236,237,238,17,61,232,197,209,87,69,81,173,212,150,101,118,103,138,248,155,253,92,185,185,195,71,166,47,9,162,1,144,76,38,69,237,61,121,242,164,
216,240,31,254,240,135,220,187,119,15,89,150,177,219,237,124,245,171,95,229,224,193,131,88,44,22,210,233,52,91,91,91,180,180,180,160,170,42,189,61,93,229,131,135,198,93,63,229,210,159,252,78,147,61,115,
252,127,133,237,118,59,146,36,225,114,185,112,185,92,216,108,54,84,85,165,185,185,25,167,211,73,163,209,160,165,165,133,19,39,78,136,207,167,166,166,184,119,239,30,47,191,252,50,99,99,99,168,170,138,166,
105,164,82,41,234,245,58,246,141,139,36,83,42,209,62,39,238,246,10,137,29,21,19,38,130,65,27,53,151,131,249,84,5,213,233,96,160,99,128,72,36,130,201,100,162,92,46,99,50,153,152,157,157,229,198,141,27,
72,146,68,119,119,55,38,147,137,147,39,79,18,143,199,201,229,114,184,221,110,252,126,63,86,171,21,171,213,138,203,229,194,225,112,224,112,56,104,52,26,196,19,73,167,167,201,221,213,213,211,191,246,132,
193,214,87,127,184,74,58,139,201,100,194,237,118,147,78,167,1,208,52,13,77,211,30,249,255,159,19,128,67,135,14,225,243,249,208,52,141,68,34,193,157,59,119,248,226,23,191,72,107,107,43,239,189,247,30,107,
107,107,72,146,68,181,90,197,100,50,241,207,6,116,124,65,39,54,143,19,217,156,71,87,36,36,201,65,174,96,66,179,88,105,107,181,177,183,83,226,226,197,139,88,173,86,76,38,19,138,162,208,209,209,193,228,
228,36,78,167,147,153,153,25,100,89,166,171,171,11,191,223,207,161,67,135,184,124,249,178,16,18,140,117,234,186,78,189,94,199,229,114,81,40,20,40,149,74,20,75,149,25,192,45,12,254,232,107,65,169,116,236,
127,134,173,86,43,77,77,77,108,108,108,176,191,191,47,212,8,227,134,6,51,26,28,28,20,192,226,246,237,219,28,61,122,20,135,195,193,183,190,245,45,182,183,183,49,155,31,237,163,170,170,232,186,78,41,175,
16,223,174,144,46,213,241,110,72,100,247,45,88,205,53,148,70,145,114,65,162,195,103,161,80,120,196,125,141,77,146,36,137,249,249,121,182,183,183,57,113,226,4,163,163,163,44,46,46,210,209,209,65,165,82,
97,120,120,152,251,247,239,227,114,185,80,85,245,81,124,254,249,117,153,76,6,151,203,69,107,107,43,138,162,144,222,217,125,210,165,189,47,127,235,237,76,178,40,112,236,189,123,247,112,58,157,152,76,38,
113,163,90,173,134,201,100,98,112,112,16,159,207,71,46,151,99,125,125,29,128,238,238,110,206,157,59,71,42,149,18,74,134,113,173,213,106,229,238,82,138,189,89,25,181,166,178,232,154,96,184,122,11,187,172,
33,73,18,183,45,71,255,156,56,4,197,70,153,205,102,17,22,91,91,91,204,205,205,241,252,243,207,179,188,188,204,250,250,58,225,112,24,175,215,203,224,224,32,169,84,10,69,81,158,88,107,54,155,101,127,127,
159,47,126,241,139,72,146,196,222,222,30,243,15,31,204,13,14,143,29,48,3,20,26,182,87,236,118,5,171,213,202,246,246,54,235,235,235,244,245,245,137,157,51,248,108,56,28,22,128,66,81,20,182,182,182,144,
36,9,179,217,76,44,22,19,124,213,184,174,86,171,161,40,10,183,45,207,224,242,185,24,24,24,96,178,171,11,77,251,10,102,179,153,114,185,76,113,110,142,76,38,67,62,159,23,161,83,173,86,209,52,13,155,205,
134,207,231,163,183,183,23,139,197,130,162,40,164,82,41,130,193,32,170,170,18,12,6,133,145,198,75,211,180,71,177,27,143,147,201,100,176,90,173,40,138,66,177,82,31,4,48,93,249,122,139,101,247,208,255,168,
27,238,124,243,230,77,246,247,247,25,26,26,18,10,68,46,151,99,115,115,19,175,215,75,34,145,16,50,77,60,30,103,102,102,134,225,225,97,142,28,57,130,213,106,101,107,107,139,98,177,40,228,26,35,137,4,131,
65,250,250,250,216,222,222,230,230,205,155,88,44,22,250,251,251,105,106,106,18,60,183,88,44,2,80,175,215,49,155,205,132,66,33,66,161,16,170,170,114,227,198,13,102,103,103,153,156,156,164,163,163,3,89,
150,49,153,76,68,163,81,242,249,60,93,93,93,56,157,78,226,241,56,187,187,187,204,204,204,16,137,68,56,116,232,16,249,124,30,179,217,204,208,208,80,216,236,57,251,237,223,79,37,10,152,76,38,26,141,6,213,
106,149,35,71,142,60,10,246,98,17,73,146,48,153,76,196,227,113,106,181,26,193,96,144,181,181,53,84,85,197,239,247,211,211,211,195,230,230,38,233,116,154,112,56,76,87,87,151,200,180,178,44,227,247,251,
105,52,26,108,111,111,51,53,53,197,181,107,215,200,102,179,200,178,204,234,234,42,147,147,147,120,189,94,66,161,16,225,112,24,151,203,133,201,100,34,151,203,145,207,231,249,248,227,143,73,38,147,200,178,
76,52,26,197,225,112,80,175,215,145,101,153,206,206,78,146,201,36,217,108,150,238,238,110,36,73,162,84,42,33,73,18,71,142,28,97,113,113,145,70,163,33,62,175,87,10,223,48,151,21,203,63,178,90,173,200,178,
76,46,151,195,235,245,98,50,153,184,118,237,26,99,99,99,12,13,13,137,122,122,245,234,85,206,158,61,75,83,83,19,169,84,138,70,163,65,115,115,51,46,151,139,253,253,125,230,231,231,73,36,18,60,253,244,35,
145,49,159,207,51,55,55,199,234,234,42,123,123,123,212,235,117,154,154,154,120,233,165,151,168,213,106,220,189,123,151,139,23,47,162,235,58,205,205,205,116,118,118,210,212,212,36,194,230,234,213,171,148,
203,101,218,219,219,9,4,2,194,117,141,141,175,86,171,76,77,77,209,211,211,3,128,36,73,108,111,111,179,184,184,200,233,211,167,113,185,92,228,114,185,191,224,231,42,39,205,117,213,20,50,178,219,222,222,
158,112,41,67,61,52,118,41,16,8,176,178,178,66,181,90,21,201,37,26,141,210,218,218,74,161,80,224,225,195,135,152,205,102,114,185,28,183,111,223,102,100,100,4,93,215,169,84,42,244,245,245,9,240,226,245,
122,25,29,29,165,90,173,178,185,185,73,50,153,100,114,114,18,171,213,74,46,151,67,215,117,114,185,28,247,239,223,71,150,101,58,58,58,8,135,195,28,56,112,0,151,203,69,34,145,32,147,201,32,203,50,149,74,
5,69,81,8,4,2,108,109,109,137,250,93,44,22,105,52,26,104,154,70,54,155,165,169,169,9,73,146,168,55,20,167,185,88,42,75,146,36,33,73,146,128,107,125,125,125,132,66,33,214,214,214,168,84,42,152,76,38,210,
233,52,161,80,8,175,215,203,230,230,38,237,237,237,156,60,121,18,93,215,121,255,253,247,217,219,219,19,165,42,155,205,114,253,250,117,58,59,59,209,117,157,104,52,138,217,108,198,16,253,178,217,71,245,
222,136,225,254,254,126,234,245,58,217,108,150,189,189,61,214,215,215,81,85,21,151,203,69,165,82,33,157,78,19,8,4,120,233,165,151,136,70,163,92,187,118,141,74,165,66,91,91,27,45,45,45,204,206,206,178,
179,179,131,170,170,164,82,41,90,91,91,113,185,92,108,109,109,209,104,52,136,197,98,72,146,68,54,155,53,153,85,85,21,128,34,155,205,178,176,176,192,161,67,135,120,225,133,23,152,157,157,21,187,217,223,
223,207,208,208,16,197,98,145,124,62,143,44,203,220,189,123,151,153,153,25,230,230,230,216,221,221,21,187,170,235,186,40,43,177,88,12,77,211,240,120,60,140,141,141,33,73,18,14,135,3,128,72,36,66,123,123,
59,110,183,91,160,178,173,173,45,118,119,119,133,199,25,240,49,147,201,144,78,167,5,146,203,231,243,180,181,181,113,246,236,89,102,103,103,217,221,221,5,160,175,175,143,145,145,17,50,153,12,63,254,241,
143,177,217,108,34,251,215,106,53,204,70,187,67,81,20,74,165,18,118,187,29,179,217,140,166,105,156,62,125,90,64,203,90,173,70,34,145,224,222,189,123,2,224,79,79,79,83,171,213,112,56,28,12,12,12,224,116,
58,209,52,141,106,181,202,222,222,30,233,116,154,205,205,77,92,46,23,221,221,221,248,124,62,182,183,183,105,109,109,21,40,173,173,173,141,74,165,66,60,30,103,111,111,15,85,85,233,239,239,199,239,247,139,
131,40,149,74,148,203,101,22,23,23,217,218,218,162,163,163,3,77,211,4,232,249,220,231,62,135,217,108,22,73,119,103,103,71,116,59,114,185,28,154,166,137,164,108,54,222,168,170,74,185,92,22,188,114,125,
125,157,133,133,5,44,22,11,146,36,9,213,49,149,74,33,203,178,48,50,18,137,208,214,214,134,207,231,99,111,111,79,156,116,46,151,227,218,181,107,196,227,113,166,167,167,81,20,133,51,103,206,224,247,251,
41,22,139,232,186,78,75,75,11,146,36,113,229,202,21,150,150,150,80,85,149,72,36,194,193,131,7,241,120,60,120,189,94,124,62,31,14,135,131,108,54,203,242,242,50,233,116,154,189,189,61,74,165,18,128,80,58,
156,78,167,104,211,52,55,55,19,139,197,240,122,189,148,203,101,1,76,84,85,253,11,44,109,244,121,60,30,143,64,56,62,159,143,100,50,73,75,75,11,229,114,153,106,181,74,60,30,103,108,108,140,137,137,9,12,
109,186,92,46,115,225,194,5,150,150,150,200,231,243,162,156,1,184,221,110,52,77,227,238,221,187,104,154,198,169,83,167,158,64,70,231,206,157,227,225,195,135,162,174,38,18,9,226,241,56,138,162,96,54,155,
9,4,2,28,56,112,128,201,201,73,162,209,40,193,96,144,90,173,198,141,27,55,88,90,90,162,90,173,34,203,50,178,44,179,187,187,75,115,115,179,240,28,159,207,71,38,147,65,81,20,44,22,11,186,174,99,54,254,99,
163,171,103,184,112,189,94,255,11,210,44,203,194,173,77,38,19,7,14,28,160,169,169,9,179,217,76,34,145,224,157,119,222,97,107,107,139,64,32,128,215,235,197,225,112,144,203,229,40,149,74,88,44,22,156,78,
39,0,235,235,235,164,211,105,130,193,32,138,162,176,190,190,46,0,141,17,151,138,162,208,212,212,132,223,239,71,81,20,118,118,118,88,89,89,225,193,131,7,156,57,115,134,64,32,128,195,225,96,108,108,140,
133,133,5,145,43,12,247,151,101,153,122,189,142,174,235,216,237,118,97,151,192,210,143,195,50,163,220,24,23,154,205,102,172,86,43,102,179,25,139,197,130,166,105,184,221,110,113,106,197,98,145,31,253,232,
71,84,42,21,94,122,233,37,122,122,122,112,58,157,56,157,78,138,197,34,15,30,60,16,25,53,20,10,161,105,26,251,251,251,184,92,46,106,181,26,187,187,187,34,129,229,243,121,28,14,7,147,147,147,140,141,141,
137,207,115,185,28,115,115,115,220,186,117,139,43,87,174,240,242,203,47,11,234,106,252,198,98,177,32,203,50,86,171,21,139,197,34,176,184,81,110,13,240,36,73,18,102,195,245,100,89,22,106,129,225,78,6,78,
54,80,147,36,73,24,32,69,146,36,30,60,120,64,38,147,225,203,95,254,50,157,157,157,44,44,44,48,51,51,131,170,170,180,181,181,241,236,179,207,18,8,4,120,247,221,119,41,22,139,180,183,183,83,46,151,159,80,
67,60,30,15,187,187,187,232,186,206,139,47,190,200,192,192,0,51,51,51,108,111,111,35,73,146,16,245,218,219,219,57,127,254,60,43,43,43,28,58,116,8,139,197,34,78,80,150,101,1,60,12,134,167,40,10,181,90,
13,131,223,27,223,155,13,250,39,203,50,46,151,139,82,169,36,12,126,252,212,141,19,55,146,152,170,170,36,18,9,170,213,42,23,47,94,164,90,173,82,42,149,56,112,224,0,163,163,163,252,232,71,63,226,206,157,
59,28,59,118,12,191,223,207,238,238,46,93,93,93,98,3,117,93,23,39,98,136,118,154,166,241,221,239,126,151,70,163,193,153,51,103,152,154,154,226,219,223,254,54,193,96,16,171,213,42,32,234,232,232,40,146,
36,137,53,25,241,111,180,107,140,154,95,44,22,5,84,5,176,217,108,72,143,119,226,253,126,63,217,108,86,36,130,159,236,208,219,237,118,241,190,94,175,83,40,20,144,101,25,143,199,35,98,168,173,173,141,161,
161,33,218,218,218,88,88,88,224,173,183,222,98,127,127,31,0,163,127,108,120,140,65,210,205,102,51,133,66,129,15,63,252,144,116,58,77,36,18,97,96,96,128,104,52,138,170,170,56,28,14,161,148,22,10,5,145,
95,140,53,61,126,130,186,174,99,54,155,133,38,103,92,103,228,39,201,237,114,137,136,14,4,2,34,203,26,201,192,0,19,141,70,67,196,140,241,157,209,189,239,236,236,228,171,95,253,42,79,61,245,20,233,116,154,
235,215,175,147,78,167,25,24,24,224,229,151,95,102,124,124,28,77,211,168,215,235,52,55,55,139,144,48,136,133,217,108,102,124,124,156,103,158,121,134,72,36,66,50,153,228,230,205,155,236,236,236,112,242,
228,73,190,244,165,47,17,10,133,158,0,52,138,162,0,136,114,100,172,209,248,62,155,205,82,169,84,4,133,84,85,21,159,207,135,217,105,55,239,102,115,106,80,146,36,2,129,0,0,233,116,90,212,173,70,163,33,10,
186,215,235,69,150,101,74,165,210,19,157,193,43,87,174,176,183,183,199,193,131,7,197,201,191,244,210,75,4,131,65,138,197,34,115,115,115,168,170,74,79,79,15,86,171,21,155,205,38,120,108,119,119,55,119,
238,220,33,147,201,112,248,240,97,122,122,122,200,100,50,84,42,21,70,71,71,49,155,205,124,248,225,135,44,44,44,136,17,10,89,150,201,231,243,88,173,86,28,14,135,80,56,140,181,42,138,34,24,150,207,231,3,
224,209,8,134,181,98,182,155,149,183,234,245,250,63,55,155,205,52,53,53,9,146,208,211,211,67,181,90,125,98,246,194,102,179,225,241,120,72,165,82,12,15,15,139,18,116,248,240,97,230,230,230,56,127,254,60,
110,183,91,148,185,124,62,207,206,206,14,38,147,137,99,199,142,241,212,83,79,17,137,68,68,14,168,213,106,194,253,150,150,150,136,199,227,184,221,110,17,231,197,98,145,106,181,74,123,123,59,95,248,194,
23,120,248,240,33,78,167,19,187,221,206,210,210,146,56,128,122,189,46,68,131,74,165,2,192,218,218,26,129,64,0,151,203,37,74,147,89,226,154,252,15,163,239,159,111,68,126,249,119,141,140,92,173,86,89,89,
89,33,26,141,82,171,213,158,112,97,147,201,132,205,102,99,117,117,149,161,161,33,0,150,150,150,136,197,98,28,62,124,152,206,206,78,172,86,171,112,47,191,223,207,216,216,24,103,207,158,229,212,169,83,4,
2,1,22,23,23,185,116,233,18,115,115,115,88,173,86,218,219,219,233,237,237,165,189,189,93,180,111,52,77,163,169,169,137,238,238,110,38,38,38,24,26,26,162,80,40,16,143,199,57,120,240,32,94,175,151,91,183,
110,209,223,223,143,166,105,98,243,12,68,40,73,18,247,238,221,99,120,120,152,214,214,86,116,93,199,225,112,16,106,109,123,217,252,220,215,82,234,212,213,171,218,222,254,190,4,208,213,213,197,157,59,119,
72,167,211,88,44,22,90,91,91,73,38,147,132,66,33,226,241,56,71,142,28,225,193,131,7,34,70,183,182,182,120,247,221,119,137,68,34,244,244,244,16,10,133,104,109,109,197,98,177,136,62,111,54,155,229,221,119,
223,101,101,101,133,100,50,41,50,230,194,194,130,32,254,45,45,45,68,163,81,58,59,59,197,134,21,139,69,82,169,20,211,211,211,108,111,111,51,54,54,70,103,103,39,219,219,219,130,213,93,191,126,157,182,182,
54,226,241,56,177,88,76,176,38,93,215,233,232,232,16,37,170,189,189,93,239,236,236,92,48,3,120,156,166,171,91,201,234,243,46,151,11,175,215,75,44,22,99,121,121,153,182,182,54,218,218,218,40,22,139,132,
195,97,210,233,52,178,44,51,50,50,194,245,235,215,121,245,213,87,121,246,217,103,177,217,108,220,190,125,155,165,165,37,225,246,198,152,146,209,235,49,22,97,148,144,114,185,140,44,203,164,82,41,238,220,
185,35,88,145,81,255,13,180,228,112,56,112,185,92,76,76,76,48,50,50,2,192,244,244,52,99,99,99,232,186,78,38,147,33,28,14,83,42,149,80,85,149,98,177,200,230,230,38,93,93,93,120,60,30,33,219,54,185,157,
155,79,116,30,206,159,63,175,27,101,40,153,76,242,254,251,239,227,247,251,233,238,238,22,49,208,104,52,112,187,221,188,240,194,11,124,243,155,223,36,20,10,113,242,228,73,106,181,26,169,84,138,205,205,
77,10,133,130,168,177,70,189,53,176,243,227,178,175,241,122,252,223,6,141,51,62,183,88,44,120,60,30,34,145,8,129,64,0,179,217,204,229,203,151,41,22,139,252,234,175,254,42,23,46,92,64,81,20,1,35,203,229,
50,137,68,130,189,189,61,94,125,245,85,145,217,29,14,7,93,93,93,254,174,174,174,172,32,15,225,80,243,254,234,122,194,239,112,56,8,133,66,244,244,244,176,176,176,64,181,90,101,124,124,156,197,197,69,6,
7,7,121,240,224,1,35,35,35,188,254,250,235,252,209,31,253,17,181,90,141,147,39,79,210,219,219,203,192,192,128,0,4,134,250,104,184,239,79,26,250,248,123,99,163,31,223,0,93,215,69,34,178,88,44,228,114,57,
46,92,184,64,34,145,224,55,126,227,55,216,216,216,96,105,105,137,209,209,81,230,231,231,25,24,24,96,113,113,145,98,177,200,200,200,136,168,56,213,106,149,222,158,158,122,87,87,87,246,137,19,94,152,250,
99,247,194,94,164,96,96,230,253,253,125,222,123,239,61,118,119,119,241,120,60,72,146,68,163,209,16,11,62,122,244,40,83,83,83,164,211,105,122,123,123,233,236,236,20,101,202,88,240,227,24,214,168,161,143,
27,101,252,246,113,72,248,147,191,55,20,210,245,245,117,150,150,150,136,68,34,28,59,118,140,155,55,111,10,14,108,183,219,69,204,7,131,65,94,125,245,85,60,30,143,184,223,208,208,208,211,177,88,236,218,
79,53,211,238,222,185,153,93,91,79,120,237,118,251,163,145,135,7,15,248,248,227,143,145,36,73,76,213,185,221,110,17,135,54,155,77,160,175,98,177,136,162,40,120,189,94,177,0,147,201,36,178,182,1,83,171,
213,42,181,90,77,184,161,209,3,50,170,128,113,218,22,139,133,106,181,74,38,147,193,40,153,134,184,80,171,213,68,107,69,180,83,138,69,52,77,227,133,23,94,96,104,104,72,76,14,141,140,12,215,7,6,6,109,127,
105,127,248,240,248,81,95,60,145,210,141,58,57,56,56,200,238,238,46,233,116,154,206,206,78,33,168,25,181,210,144,79,110,223,190,77,165,82,17,174,60,58,58,202,208,208,144,72,84,134,232,126,243,230,77,86,
86,86,68,66,210,117,157,72,36,194,228,228,36,54,155,77,24,43,73,18,51,51,51,220,185,115,7,99,243,3,129,0,227,227,227,66,100,52,78,116,107,107,139,120,60,206,198,198,6,109,109,109,244,245,245,9,123,60,
30,15,86,171,173,245,255,58,1,208,40,103,122,182,182,51,135,92,174,71,237,24,191,223,207,246,246,54,197,98,81,0,117,131,80,52,26,13,62,249,228,19,76,38,19,199,143,31,103,96,96,0,89,150,185,117,235,22,
86,171,85,16,130,82,169,196,219,111,191,205,206,206,14,67,67,67,12,15,15,19,139,197,176,219,237,204,207,207,179,180,180,68,111,111,175,192,239,247,239,223,231,214,173,91,12,13,13,49,62,62,78,52,26,101,
99,99,131,133,133,5,90,91,91,169,213,106,148,203,101,118,119,119,73,165,82,36,147,73,156,78,39,199,142,29,19,8,176,88,44,50,124,96,240,118,119,119,207,31,62,110,159,244,147,19,0,35,135,159,254,199,225,
112,72,41,149,74,24,3,45,19,19,19,232,186,46,228,21,35,19,47,46,46,210,220,220,204,196,196,132,208,175,90,91,91,153,156,156,100,105,105,73,32,169,197,197,69,28,14,7,39,78,156,160,163,163,3,187,221,142,
205,102,35,18,137,240,220,115,207,97,177,88,88,89,89,17,29,199,149,149,21,142,30,61,74,48,24,36,30,143,179,179,179,195,196,196,4,94,175,151,229,229,101,116,93,167,80,40,8,97,15,96,114,114,82,200,177,197,
98,145,161,161,65,189,187,167,239,200,95,107,168,229,217,103,159,183,156,59,119,78,55,18,74,91,91,27,135,15,31,230,254,253,251,36,147,73,65,17,235,245,58,29,29,29,188,241,198,27,20,139,69,17,175,191,244,
75,191,36,136,136,195,225,32,159,207,99,177,88,152,158,158,38,159,207,139,228,103,181,90,113,187,221,56,157,78,193,168,140,154,159,207,231,249,254,247,191,47,18,147,207,231,227,244,233,211,36,18,9,246,
247,247,217,217,217,97,123,123,155,70,163,193,145,35,71,8,6,131,130,177,5,131,65,156,78,151,243,103,26,61,236,143,122,159,157,223,216,191,106,96,227,142,142,14,0,102,103,103,137,199,227,168,170,74,32,
16,96,99,99,131,114,185,204,87,190,242,21,44,22,11,31,124,240,1,55,111,222,20,221,7,163,52,181,181,181,137,14,128,65,254,13,80,95,46,151,133,102,102,180,101,47,95,190,76,91,91,27,167,79,159,166,86,171,
241,230,155,111,146,76,38,241,120,60,36,147,73,182,182,182,168,215,235,140,143,143,11,124,110,132,68,71,52,250,47,59,99,177,234,207,100,240,192,161,231,166,116,233,198,31,204,46,198,127,219,80,23,13,172,
60,59,59,203,198,198,6,62,159,79,148,24,135,195,33,12,122,188,206,150,203,101,193,133,141,233,218,90,173,134,170,170,216,237,118,220,110,55,94,175,247,137,205,49,64,136,17,82,185,92,78,220,175,209,104,
176,190,190,142,44,203,76,76,76,208,218,218,42,242,74,173,86,227,192,96,255,185,206,88,236,15,255,198,163,135,15,239,223,252,222,194,74,226,117,99,122,167,90,173,146,205,102,153,153,153,65,81,20,198,199,
199,185,114,229,10,213,106,21,187,221,78,46,151,227,204,153,51,24,83,64,146,36,9,185,215,24,75,176,88,44,79,180,83,27,141,6,181,90,141,193,193,65,209,61,200,102,179,92,186,116,9,191,223,79,185,92,198,
227,241,240,212,83,79,137,204,61,54,54,134,219,237,198,110,183,35,203,50,229,114,153,3,67,3,211,221,61,125,71,255,214,195,165,63,158,185,245,223,150,214,146,191,233,241,60,154,203,46,149,74,84,171,85,
22,22,22,4,136,175,84,42,34,166,101,89,166,86,171,17,8,4,144,36,137,213,213,85,66,161,16,129,64,0,187,221,142,221,110,23,12,199,168,181,153,76,134,88,44,6,192,206,206,142,16,250,54,55,55,113,56,28,200,
178,44,38,118,251,250,250,196,125,12,182,212,215,219,125,174,187,167,239,149,159,219,188,244,226,195,91,103,54,183,115,255,91,85,85,188,94,175,152,89,222,219,219,99,99,99,3,167,211,201,232,232,40,245,
122,157,68,34,241,196,100,172,81,66,98,177,24,161,80,72,212,239,106,181,74,58,157,102,99,99,131,112,56,140,205,102,163,209,104,80,46,151,197,6,24,45,157,90,173,70,44,22,163,165,165,69,36,187,253,253,125,
60,30,15,29,209,232,191,238,140,197,254,195,47,100,34,254,214,244,77,101,59,149,150,67,161,16,245,122,157,98,177,40,26,94,219,219,219,162,31,228,245,122,241,122,189,66,214,53,90,57,129,64,128,64,32,128,
174,235,236,238,238,178,191,191,255,68,57,41,20,10,162,55,172,105,26,205,205,205,226,241,0,155,205,134,211,233,196,108,54,179,191,191,79,103,103,167,238,118,187,157,93,93,93,213,95,232,35,0,243,15,239,
94,90,92,137,127,206,24,114,49,30,200,40,151,203,228,114,57,97,184,65,202,141,133,90,173,214,39,132,65,3,78,26,237,217,106,181,42,32,103,75,75,11,225,112,24,143,199,131,195,225,192,110,183,227,116,58,
41,20,30,53,239,99,157,209,217,238,158,190,209,191,211,167,90,166,111,222,168,20,138,37,187,33,190,151,203,101,177,240,74,165,66,161,80,16,162,224,227,179,31,63,201,140,140,49,227,166,166,38,60,30,15,
110,183,91,24,105,132,69,161,80,64,211,52,194,225,214,134,221,238,240,252,44,167,250,115,125,140,103,109,109,205,94,44,228,246,114,249,162,195,192,188,170,170,82,169,84,196,24,146,33,138,43,138,34,36,
28,3,212,24,13,0,227,207,102,179,9,99,53,77,35,151,203,97,181,90,241,251,125,117,187,221,241,76,44,22,187,245,247,230,65,173,249,185,153,197,106,93,237,173,215,235,38,99,154,207,144,121,234,245,186,48,
246,241,177,38,195,189,13,206,108,36,45,147,201,132,203,229,210,109,86,243,86,95,255,96,244,239,229,147,105,79,140,32,47,62,252,64,209,76,79,235,186,201,217,104,52,76,143,115,99,131,239,42,138,34,104,
158,201,100,122,36,170,155,168,152,76,250,45,179,197,254,107,177,88,108,253,231,189,174,255,51,0,127,146,57,16,105,69,210,85,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* JuceDemoPluginAudioProcessorEditor::mayaKnobtest_png = (const char*) resource_JuceDemoPluginAudioProcessorEditor_mayaKnobtest_png;
const int JuceDemoPluginAudioProcessorEditor::mayaKnobtest_pngSize = 8092;

// JUCER_RESOURCE: untitled1_png, 3004, "../../../Desktop/Untitled-1.png"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_untitled1_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,51,0,0,0,13,8,6,0,0,0,4,209,86,247,0,0,0,9,112,72,89,115,
0,0,11,19,0,0,11,19,1,0,154,156,24,0,0,10,79,105,67,67,80,80,104,111,116,111,115,104,111,112,32,73,67,67,32,112,114,111,102,105,108,101,0,0,120,218,157,83,103,84,83,233,22,61,247,222,244,66,75,136,128,
148,75,111,82,21,8,32,82,66,139,128,20,145,38,42,33,9,16,74,136,33,161,217,21,81,193,17,69,69,4,27,200,160,136,3,142,142,128,140,21,81,44,12,138,10,216,7,228,33,162,142,131,163,136,138,202,251,225,123,
163,107,214,188,247,230,205,254,181,215,62,231,172,243,157,179,207,7,192,8,12,150,72,51,81,53,128,12,169,66,30,17,224,131,199,196,198,225,228,46,64,129,10,36,112,0,16,8,179,100,33,115,253,35,1,0,248,126,
60,60,43,34,192,7,190,0,1,120,211,11,8,0,192,77,155,192,48,28,135,255,15,234,66,153,92,1,128,132,1,192,116,145,56,75,8,128,20,0,64,122,142,66,166,0,64,70,1,128,157,152,38,83,0,160,4,0,96,203,99,98,227,
0,80,45,0,96,39,127,230,211,0,128,157,248,153,123,1,0,91,148,33,21,1,160,145,0,32,19,101,136,68,0,104,59,0,172,207,86,138,69,0,88,48,0,20,102,75,196,57,0,216,45,0,48,73,87,102,72,0,176,183,0,192,206,16,
11,178,0,8,12,0,48,81,136,133,41,0,4,123,0,96,200,35,35,120,0,132,153,0,20,70,242,87,60,241,43,174,16,231,42,0,0,120,153,178,60,185,36,57,69,129,91,8,45,113,7,87,87,46,30,40,206,73,23,43,20,54,97,2,97,
154,64,46,194,121,153,25,50,129,52,15,224,243,204,0,0,160,145,21,17,224,131,243,253,120,206,14,174,206,206,54,142,182,14,95,45,234,191,6,255,34,98,98,227,254,229,207,171,112,64,0,0,225,116,126,209,254,
44,47,179,26,128,59,6,128,109,254,162,37,238,4,104,94,11,160,117,247,139,102,178,15,64,181,0,160,233,218,87,243,112,248,126,60,60,69,161,144,185,217,217,229,228,228,216,74,196,66,91,97,202,87,125,254,
103,194,95,192,87,253,108,249,126,60,252,247,245,224,190,226,36,129,50,93,129,71,4,248,224,194,204,244,76,165,28,207,146,9,132,98,220,230,143,71,252,183,11,255,252,29,211,34,196,73,98,185,88,42,20,227,
81,18,113,142,68,154,140,243,50,165,34,137,66,146,41,197,37,210,255,100,226,223,44,251,3,62,223,53,0,176,106,62,1,123,145,45,168,93,99,3,246,75,39,16,88,116,192,226,247,0,0,242,187,111,193,212,40,8,3,
128,104,131,225,207,119,255,239,63,253,71,160,37,0,128,102,73,146,113,0,0,94,68,36,46,84,202,179,63,199,8,0,0,68,160,129,42,176,65,27,244,193,24,44,192,6,28,193,5,220,193,11,252,96,54,132,66,36,196,194,
66,16,66,10,100,128,28,114,96,41,172,130,66,40,134,205,176,29,42,96,47,212,64,29,52,192,81,104,134,147,112,14,46,194,85,184,14,61,112,15,250,97,8,158,193,40,188,129,9,4,65,200,8,19,97,33,218,136,1,98,
138,88,35,142,8,23,153,133,248,33,193,72,4,18,139,36,32,201,136,20,81,34,75,145,53,72,49,82,138,84,32,85,72,29,242,61,114,2,57,135,92,70,186,145,59,200,0,50,130,252,134,188,71,49,148,129,178,81,61,212,
12,181,67,185,168,55,26,132,70,162,11,208,100,116,49,154,143,22,160,155,208,114,180,26,61,140,54,161,231,208,171,104,15,218,143,62,67,199,48,192,232,24,7,51,196,108,48,46,198,195,66,177,56,44,9,147,99,
203,177,34,172,12,171,198,26,176,86,172,3,187,137,245,99,207,177,119,4,18,129,69,192,9,54,4,119,66,32,97,30,65,72,88,76,88,78,216,72,168,32,28,36,52,17,218,9,55,9,3,132,81,194,39,34,147,168,75,180,38,
186,17,249,196,24,98,50,49,135,88,72,44,35,214,18,143,19,47,16,123,136,67,196,55,36,18,137,67,50,39,185,144,2,73,177,164,84,210,18,210,70,210,110,82,35,233,44,169,155,52,72,26,35,147,201,218,100,107,178,
7,57,148,44,32,43,200,133,228,157,228,195,228,51,228,27,228,33,242,91,10,157,98,64,113,164,248,83,226,40,82,202,106,74,25,229,16,229,52,229,6,101,152,50,65,85,163,154,82,221,168,161,84,17,53,143,90,66,
173,161,182,82,175,81,135,168,19,52,117,154,57,205,131,22,73,75,165,173,162,149,211,26,104,23,104,247,105,175,232,116,186,17,221,149,30,78,151,208,87,210,203,233,71,232,151,232,3,244,119,12,13,134,21,
131,199,136,103,40,25,155,24,7,24,103,25,119,24,175,152,76,166,25,211,139,25,199,84,48,55,49,235,152,231,153,15,153,111,85,88,42,182,42,124,21,145,202,10,149,74,149,38,149,27,42,47,84,169,170,166,170,
222,170,11,85,243,85,203,84,143,169,94,83,125,174,70,85,51,83,227,169,9,212,150,171,85,170,157,80,235,83,27,83,103,169,59,168,135,170,103,168,111,84,63,164,126,89,253,137,6,89,195,76,195,79,67,164,81,
160,177,95,227,188,198,32,11,99,25,179,120,44,33,107,13,171,134,117,129,53,196,38,177,205,217,124,118,42,187,152,253,29,187,139,61,170,169,161,57,67,51,74,51,87,179,82,243,148,102,63,7,227,152,113,248,
156,116,78,9,231,40,167,151,243,126,138,222,20,239,41,226,41,27,166,52,76,185,49,101,92,107,170,150,151,150,88,171,72,171,81,171,71,235,189,54,174,237,167,157,166,189,69,187,89,251,129,14,65,199,74,39,
92,39,71,103,143,206,5,157,231,83,217,83,221,167,10,167,22,77,61,58,245,174,46,170,107,165,27,161,187,68,119,191,110,167,238,152,158,190,94,128,158,76,111,167,222,121,189,231,250,28,125,47,253,84,253,
109,250,167,245,71,12,88,6,179,12,36,6,219,12,206,24,60,197,53,113,111,60,29,47,199,219,241,81,67,93,195,64,67,165,97,149,97,151,225,132,145,185,209,60,163,213,70,141,70,15,140,105,198,92,227,36,227,109,
198,109,198,163,38,6,38,33,38,75,77,234,77,238,154,82,77,185,166,41,166,59,76,59,76,199,205,204,205,162,205,214,153,53,155,61,49,215,50,231,155,231,155,215,155,223,183,96,90,120,90,44,182,168,182,184,
101,73,178,228,90,166,89,238,182,188,110,133,90,57,89,165,88,85,90,93,179,70,173,157,173,37,214,187,173,187,167,17,167,185,78,147,78,171,158,214,103,195,176,241,182,201,182,169,183,25,176,229,216,6,219,
174,182,109,182,125,97,103,98,23,103,183,197,174,195,238,147,189,147,125,186,125,141,253,61,7,13,135,217,14,171,29,90,29,126,115,180,114,20,58,86,58,222,154,206,156,238,63,125,197,244,150,233,47,103,88,
207,16,207,216,51,227,182,19,203,41,196,105,157,83,155,211,71,103,23,103,185,115,131,243,136,139,137,75,130,203,46,151,62,46,155,27,198,221,200,189,228,74,116,245,113,93,225,122,210,245,157,155,179,155,
194,237,168,219,175,238,54,238,105,238,135,220,159,204,52,159,41,158,89,51,115,208,195,200,67,224,81,229,209,63,11,159,149,48,107,223,172,126,79,67,79,129,103,181,231,35,47,99,47,145,87,173,215,176,183,
165,119,170,247,97,239,23,62,246,62,114,159,227,62,227,60,55,222,50,222,89,95,204,55,192,183,200,183,203,79,195,111,158,95,133,223,67,127,35,255,100,255,122,255,209,0,167,128,37,1,103,3,137,129,65,129,
91,2,251,248,122,124,33,191,142,63,58,219,101,246,178,217,237,65,140,160,185,65,21,65,143,130,173,130,229,193,173,33,104,200,236,144,173,33,247,231,152,206,145,206,105,14,133,80,126,232,214,208,7,97,230,
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
147,0,0,0,32,99,72,82,77,0,0,122,37,0,0,128,131,0,0,249,255,0,0,128,233,0,0,117,48,0,0,234,96,0,0,58,152,0,0,23,111,146,95,197,70,0,0,0,215,73,68,65,84,120,218,212,150,75,14,195,32,12,68,153,138,251,95,
121,186,9,173,51,245,135,180,68,42,150,178,64,3,6,227,103,19,144,100,123,27,218,198,246,176,3,0,220,53,16,0,231,96,118,183,110,7,7,113,116,144,83,20,61,52,163,172,42,186,92,48,199,213,21,179,202,225,7,
138,30,154,133,31,0,200,230,208,250,49,31,51,189,181,198,94,112,72,146,88,192,179,245,35,61,39,223,171,218,127,232,87,106,6,130,162,151,129,25,227,196,90,4,216,151,250,207,13,96,69,230,252,100,214,168,
170,254,183,221,76,47,73,107,211,185,68,122,221,44,194,0,147,152,100,126,94,62,188,186,137,26,79,213,152,134,222,143,148,241,27,132,34,93,3,149,121,40,30,103,87,55,62,162,245,64,114,67,101,241,202,33,
79,250,77,181,148,254,1,180,11,193,140,3,51,121,32,43,253,86,123,2,0,0,255,255,3,0,202,33,120,57,225,236,223,1,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* JuceDemoPluginAudioProcessorEditor::untitled1_png = (const char*) resource_JuceDemoPluginAudioProcessorEditor_untitled1_png;
const int JuceDemoPluginAudioProcessorEditor::untitled1_pngSize = 3004;

// JUCER_RESOURCE: vibratingsilveryspeakeranimatedgif_gif, 83589, "../../../Desktop/Vibrating-silvery-speaker-animated-gif.gif"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_vibratingsilveryspeakeranimatedgif_gif[] = { 71,73,70,56,57,97,236,0,227,0,230,127,0,147,155,168,167,170,182,122,131,141,141,92,86,
229,237,244,221,233,244,153,150,153,209,198,184,89,51,50,152,165,180,182,199,214,47,55,69,11,17,18,111,121,135,205,219,231,168,181,199,232,233,234,106,101,102,200,187,181,179,212,236,182,164,154,141,175,
207,254,255,255,117,76,75,82,87,102,234,245,249,198,180,172,70,72,85,186,171,163,180,186,199,202,198,199,163,163,172,27,33,36,171,155,148,119,117,121,130,139,150,33,38,41,217,228,238,134,133,138,114,106,
106,219,213,204,185,182,184,118,145,168,217,215,218,213,204,197,102,106,117,172,176,189,90,99,114,198,204,214,54,53,56,70,67,73,227,220,212,41,49,56,59,63,77,137,148,159,87,84,91,71,59,66,202,234,253,
245,253,254,188,179,171,199,212,223,37,43,48,245,246,246,149,138,136,95,62,59,233,228,221,104,114,126,196,173,167,88,70,71,141,128,121,54,39,37,159,157,165,99,92,101,107,96,94,113,108,115,21,27,29,82,
75,87,158,201,230,219,241,252,182,172,181,245,244,238,245,246,252,123,113,109,147,142,147,46,33,28,252,252,249,195,190,197,154,146,144,211,207,213,74,79,93,240,237,234,131,123,129,169,189,209,204,180,
160,36,24,21,211,191,167,161,174,193,184,189,211,237,242,239,188,225,250,252,247,253,252,246,245,246,252,246,49,44,50,87,81,77,61,47,45,208,225,238,226,223,229,24,31,27,243,239,245,37,29,35,151,195,224,
219,225,223,207,189,185,40,47,46,208,210,204,175,175,173,130,161,189,189,194,191,157,159,158,110,111,109,74,78,76,140,144,142,149,188,221,60,62,61,91,94,96,123,126,130,255,255,255,33,255,11,78,69,84,83,
67,65,80,69,50,46,48,3,1,0,0,0,33,249,4,5,0,0,127,0,44,0,0,0,0,236,0,227,0,0,7,255,128,87,87,6,132,133,134,135,119,6,119,71,140,141,141,31,144,145,1,46,46,29,10,13,17,63,33,105,55,69,38,63,119,116,41,
41,118,43,107,4,58,22,170,171,172,85,172,37,60,96,54,38,34,72,72,73,39,34,120,17,45,66,34,13,34,91,74,91,180,196,34,66,35,35,0,96,15,48,81,170,102,174,172,173,210,211,22,210,85,109,16,16,65,107,43,88,
30,30,86,31,79,79,41,229,232,28,28,79,59,18,238,26,240,240,67,243,244,67,26,18,113,113,225,225,88,86,43,22,37,92,0,112,82,162,68,129,131,219,32,16,88,200,176,161,195,135,16,35,54,20,116,168,162,161,68,
139,28,57,138,36,201,5,157,14,118,48,153,216,212,233,211,7,58,162,74,157,178,54,173,154,133,2,10,100,153,80,98,11,23,158,93,45,90,40,17,241,75,137,137,41,126,252,208,66,6,32,140,3,53,78,50,168,114,201,
178,105,43,49,219,214,4,249,102,165,234,19,9,163,52,156,219,241,100,221,147,123,18,226,197,171,71,239,158,190,125,88,250,57,176,160,38,192,192,2,6,255,9,20,32,160,80,162,93,134,98,8,228,221,123,151,162,
69,139,137,20,105,220,200,113,82,165,75,17,182,132,192,145,68,208,21,148,40,85,18,112,186,212,130,142,203,4,20,60,0,48,51,66,146,8,39,118,241,226,37,66,137,31,17,83,142,152,88,125,108,4,24,24,57,28,56,
64,101,217,242,229,219,148,173,69,161,187,166,247,138,25,105,177,72,176,162,193,10,86,173,26,186,154,187,39,86,30,89,123,248,206,122,72,235,207,130,131,4,0,50,28,156,59,151,238,221,239,124,249,74,244,
251,87,209,157,243,133,22,101,28,124,228,195,145,0,240,93,216,129,33,242,74,154,76,63,174,220,217,33,42,5,12,133,207,52,85,5,25,170,92,38,91,2,2,248,65,211,45,39,68,208,199,13,125,68,160,132,18,57,61,
152,197,13,27,240,177,65,13,11,44,80,67,13,27,108,128,1,6,47,188,208,66,3,2,164,40,64,50,54,0,16,64,7,60,204,118,219,140,183,17,224,192,26,88,172,240,13,22,44,136,99,69,28,199,165,160,193,14,66,238,0,
143,59,97,57,71,86,255,116,252,76,167,150,117,1,36,64,208,65,11,21,80,215,119,18,229,229,144,150,17,57,102,192,32,229,5,150,30,123,142,220,241,65,124,32,53,240,66,126,105,156,144,223,21,20,160,52,10,12,
112,64,16,96,83,207,220,230,0,24,0,112,22,193,13,183,32,113,67,30,121,200,96,40,14,49,36,26,131,134,55,100,129,65,31,38,150,88,162,16,40,166,56,66,138,42,180,216,167,13,45,94,218,64,3,148,166,8,192,3,
10,40,192,67,6,25,148,0,129,111,43,136,195,66,85,63,34,25,135,144,72,50,55,22,89,102,229,227,65,143,57,90,177,6,148,82,26,212,157,149,87,58,84,172,119,15,113,137,151,93,20,129,249,151,152,132,48,178,222,
122,237,73,50,9,72,66,100,98,0,14,39,8,18,194,7,28,208,97,135,29,30,212,121,103,43,22,248,32,134,5,81,232,144,65,7,216,209,34,97,18,68,32,129,6,31,49,156,17,3,14,134,230,1,232,13,50,224,11,2,9,32,44,193,
0,13,34,54,48,66,139,9,36,0,134,44,156,170,160,38,6,89,132,248,33,255,6,10,219,32,64,11,21,111,136,65,11,0,164,224,193,10,16,180,218,79,10,18,132,35,65,57,72,190,211,220,115,185,234,195,235,147,14,68,
57,229,176,199,50,148,243,119,59,63,228,165,179,229,165,71,237,17,235,125,96,38,36,148,116,208,65,182,83,92,129,131,20,222,82,176,195,14,225,204,81,103,42,44,65,96,155,14,81,60,192,103,159,38,68,128,4,
19,49,24,145,134,12,104,220,112,3,17,56,224,64,5,3,112,51,16,195,13,91,4,176,66,158,151,69,129,183,187,25,208,120,91,223,58,148,16,134,10,24,208,96,184,135,47,8,32,68,13,61,212,32,195,13,83,136,172,35,
56,198,201,28,135,113,46,139,5,115,116,210,81,247,107,205,193,82,41,87,207,116,29,75,58,150,11,53,27,116,69,234,149,249,136,181,149,44,221,66,126,56,108,113,69,8,184,79,237,193,28,86,67,128,53,186,174,
180,139,74,9,14,40,0,128,8,76,156,145,6,14,245,162,33,67,26,70,120,33,189,17,79,135,240,213,112,6,64,50,133,48,99,35,65,113,199,31,134,184,129,255,163,39,10,144,192,3,167,210,152,129,2,54,108,176,68,15,
89,160,40,196,6,52,144,80,131,18,31,88,65,249,40,84,3,217,242,203,245,136,217,174,156,228,1,7,232,0,116,55,227,78,207,78,23,17,6,166,78,117,171,187,136,235,136,198,145,51,93,107,105,17,104,26,17,138,112,
59,10,132,64,119,211,185,154,53,164,1,129,190,245,77,13,0,200,194,2,206,32,3,38,176,45,122,210,115,3,14,144,96,187,16,252,64,10,244,130,30,244,16,128,131,229,201,128,8,135,138,1,136,178,64,68,34,138,111,
3,76,32,34,135,58,180,128,13,188,0,0,6,172,145,11,48,64,130,37,100,65,0,38,120,129,12,64,32,3,17,124,96,100,44,16,153,255,106,165,185,0,114,110,58,30,128,1,22,96,176,134,3,194,39,129,16,32,150,149,30,
178,13,99,161,142,89,131,0,90,4,165,213,136,214,21,230,76,242,89,90,31,52,168,137,16,112,224,131,84,155,206,41,126,183,10,87,104,161,64,25,128,193,6,22,208,49,25,192,208,11,56,184,129,18,138,80,4,41,92,
128,255,8,8,64,0,16,136,112,129,79,142,18,8,56,64,64,26,86,217,182,182,49,33,137,33,234,152,248,12,245,33,199,109,64,6,22,203,23,13,32,135,133,219,68,193,5,53,96,192,2,250,96,130,62,156,161,7,124,192,
3,29,86,144,130,124,0,9,44,101,44,11,147,6,168,70,54,186,17,12,169,218,206,232,182,49,172,185,56,144,142,88,250,89,4,133,230,8,193,28,13,18,81,250,64,236,90,208,7,65,16,161,144,135,196,74,56,72,182,46,
167,248,192,2,60,232,208,248,100,112,6,55,120,129,122,73,144,194,9,146,128,6,182,225,0,8,163,4,229,42,67,105,132,80,46,116,149,16,197,1,19,110,192,132,88,118,44,15,76,192,40,46,101,80,3,33,198,160,7,43,
140,1,18,67,186,0,33,240,64,79,66,96,64,15,110,224,135,8,228,43,15,87,81,153,145,146,164,164,121,8,16,28,211,129,65,9,116,192,131,0,128,97,74,194,74,200,28,237,216,144,111,126,135,60,227,36,196,208,52,
226,30,11,38,109,105,47,48,192,15,146,128,187,170,106,0,72,88,255,232,141,43,204,96,134,116,217,198,2,16,176,1,71,147,88,3,18,120,129,10,140,73,194,0,76,137,80,182,2,33,148,112,133,43,68,85,153,6,85,182,
77,6,109,83,155,161,0,37,40,38,24,202,175,1,83,84,190,142,121,204,30,232,235,67,245,219,192,7,38,99,129,12,52,128,1,75,120,65,3,48,0,130,5,152,128,14,187,75,1,29,56,128,15,155,106,192,30,102,57,192,62,
172,80,205,2,240,212,102,194,42,170,67,186,115,199,214,18,192,49,122,140,224,121,136,54,152,194,92,144,157,6,8,129,20,60,24,2,10,248,150,5,57,50,69,21,158,17,141,188,88,96,5,45,124,37,19,112,224,6,55,
156,1,9,108,37,194,40,47,128,208,184,90,87,149,14,141,107,93,17,64,4,38,32,97,94,129,178,133,218,38,138,132,91,210,18,95,137,58,131,122,215,27,3,55,144,0,164,49,160,65,15,122,96,131,185,232,160,0,193,
92,192,8,48,208,161,22,220,1,140,18,80,7,7,230,65,1,14,196,3,31,104,1,199,78,97,144,128,0,220,76,103,174,141,176,255,207,144,26,52,140,16,109,182,181,237,72,236,132,240,130,219,21,97,8,33,232,224,229,
252,179,134,60,221,19,107,34,56,67,11,54,48,216,51,72,20,9,8,37,165,116,17,250,86,185,94,215,198,217,173,107,26,136,80,47,41,208,228,6,73,176,133,160,212,70,209,140,154,23,189,45,30,172,71,231,59,95,26,
4,179,6,52,24,1,42,116,96,3,200,102,161,5,53,0,193,32,53,219,14,9,208,195,192,113,128,71,231,176,160,128,18,68,129,193,216,76,45,132,37,204,102,10,87,216,156,24,38,76,97,42,17,6,33,180,96,10,54,212,128,
13,175,96,96,22,172,0,14,34,84,69,20,108,160,33,36,144,192,13,203,35,2,160,164,203,99,26,227,248,198,55,222,46,93,19,125,130,129,10,89,200,98,235,171,145,13,21,216,248,158,65,14,235,85,175,16,23,240,81,
16,48,0,4,3,91,192,18,104,208,1,174,149,96,1,12,112,98,12,72,208,135,47,238,64,192,54,61,35,63,20,172,3,24,28,225,167,194,98,109,177,88,203,230,163,198,246,89,74,189,240,82,43,255,8,72,165,9,161,15,185,
45,130,158,59,40,142,145,21,160,111,236,154,2,13,22,112,3,230,238,203,133,160,156,174,116,179,11,233,114,107,247,161,220,13,168,165,129,124,105,91,244,33,163,156,230,40,122,11,43,7,26,228,139,212,234,
173,229,123,11,214,3,26,160,90,8,191,210,65,48,105,208,130,51,44,65,6,31,96,65,128,57,112,235,33,224,195,10,212,132,129,7,38,195,3,135,101,83,116,70,45,246,132,147,170,8,165,46,149,17,21,68,83,7,112,27,
130,15,219,240,7,20,72,65,142,236,0,135,3,142,160,7,35,117,238,12,121,204,99,52,80,151,174,230,206,249,117,183,107,54,34,156,0,135,73,248,76,144,191,43,182,7,229,193,188,29,173,119,124,123,240,222,30,
200,97,176,29,37,172,12,150,96,176,37,144,224,212,103,176,223,10,82,161,4,185,225,33,15,12,128,105,24,195,236,112,119,232,47,28,48,176,2,197,63,144,102,109,42,36,227,26,103,136,155,147,138,30,3,200,25,
157,79,197,237,21,118,123,133,31,160,220,3,116,152,67,1,232,179,0,255,13,245,19,81,46,60,40,143,47,144,221,26,235,252,241,215,5,66,64,5,250,153,162,55,10,233,124,248,16,31,234,215,239,24,200,129,4,77,
103,122,168,245,245,209,12,193,205,13,76,167,250,192,2,96,153,22,64,54,197,12,64,66,10,118,160,15,172,64,28,237,226,152,12,22,44,30,236,209,197,61,194,228,17,68,211,166,48,206,35,68,235,117,144,96,4,154,
72,190,219,61,115,128,20,116,40,92,192,22,224,133,24,60,142,199,109,187,249,141,29,13,249,114,75,58,149,8,64,131,20,164,144,54,25,180,55,110,75,24,88,15,132,152,116,18,208,0,95,76,102,122,162,222,219,
54,245,242,115,95,110,128,236,18,220,251,62,6,144,32,0,125,211,7,12,144,5,2,72,2,63,144,2,10,39,50,253,144,70,185,103,1,88,240,107,23,135,16,200,242,123,168,51,119,95,82,30,180,69,38,182,245,34,35,215,
7,119,16,98,184,83,4,63,64,36,17,128,76,27,208,3,86,119,3,5,213,54,220,215,125,230,230,120,144,102,54,116,133,3,5,101,54,243,71,117,85,151,255,126,234,103,56,114,80,111,133,183,0,159,231,94,236,37,88,
139,130,3,124,96,4,56,232,92,29,130,130,75,224,2,58,0,1,75,192,6,124,0,118,68,112,4,192,149,2,250,83,21,48,16,6,118,178,2,188,71,108,112,71,129,23,104,17,199,118,17,31,183,129,74,195,78,124,6,91,69,144,
4,36,32,3,121,224,111,44,132,6,169,148,74,142,38,105,46,24,87,111,229,120,45,24,87,102,195,74,64,148,6,103,192,7,240,215,3,5,163,122,168,246,94,52,32,7,243,85,111,134,211,3,205,37,132,164,135,100,138,
210,79,251,55,136,183,148,121,168,102,7,58,208,1,6,115,3,49,176,4,55,224,15,16,183,2,105,215,1,207,176,2,203,144,64,115,20,134,113,87,134,123,100,119,140,96,119,69,131,78,183,229,129,119,128,6,184,112,
2,104,96,4,1,99,136,49,192,4,116,104,135,142,135,135,144,6,131,219,23,121,54,166,99,7,197,60,105,131,6,121,48,133,121,192,33,159,135,131,81,8,2,108,128,106,242,133,106,3,67,48,168,214,92,134,165,40,124,
128,255,40,137,210,54,31,229,94,34,117,116,53,192,7,11,208,56,37,38,2,12,224,6,121,240,81,122,208,27,74,131,5,97,240,15,4,176,138,193,214,138,16,17,71,20,248,16,99,200,113,118,231,113,236,209,84,134,209,
1,15,192,78,31,40,3,73,208,67,230,72,2,114,128,54,230,199,93,213,165,135,200,88,110,48,88,135,162,68,99,168,196,93,140,134,74,109,35,136,105,64,132,139,178,142,153,199,81,183,68,141,85,148,126,56,152,
136,45,9,142,161,182,47,228,88,142,179,70,2,131,136,75,27,208,7,43,9,2,47,192,46,49,192,0,132,40,138,46,48,120,29,16,6,237,194,96,46,0,84,219,193,77,199,66,108,1,153,58,4,121,8,198,87,149,178,136,124,
215,226,2,12,121,7,204,179,60,56,16,61,49,128,6,206,211,54,227,150,135,161,132,140,117,24,99,216,215,74,130,72,5,205,37,61,210,131,126,113,51,151,112,163,131,168,214,111,41,41,3,60,56,95,4,99,141,217,
8,122,243,165,47,132,168,40,228,40,152,112,136,33,33,162,87,32,240,1,58,0,255,0,144,149,101,11,0,0,91,200,152,22,208,1,1,240,0,17,248,118,220,84,37,80,25,149,11,49,144,83,89,8,85,201,84,120,247,0,90,249,
2,116,96,2,84,176,60,208,227,5,130,130,40,204,3,74,102,105,93,123,152,150,216,39,136,103,96,4,110,233,6,75,224,5,116,249,155,114,105,48,192,105,141,75,32,88,242,5,122,168,134,131,108,0,122,132,37,152,
70,184,40,131,185,40,50,144,5,211,137,33,45,148,5,8,99,64,89,32,76,4,35,4,97,208,1,5,16,5,94,136,153,189,87,58,219,161,77,158,233,16,176,88,124,5,153,129,175,19,31,90,217,2,38,128,7,251,210,79,156,96,
126,137,214,67,24,121,145,180,89,99,142,182,135,8,213,67,16,229,6,5,3,156,6,122,160,8,74,151,233,215,121,124,240,121,36,192,6,16,10,147,239,69,122,136,18,157,137,194,7,112,184,1,71,71,81,16,146,101,35,
144,1,85,182,4,11,224,147,168,216,107,35,64,158,112,17,23,113,20,71,231,153,158,14,241,37,235,185,158,5,121,149,143,208,96,134,97,255,103,208,120,6,94,176,99,137,199,47,250,201,159,29,233,145,162,52,164,
103,9,160,1,58,146,110,233,155,232,71,117,9,218,164,114,233,164,75,208,131,82,74,48,217,72,5,160,55,161,226,40,142,153,39,82,125,80,3,128,18,34,121,80,56,11,96,90,166,182,0,160,7,3,58,96,60,228,89,16,
65,117,158,232,233,162,15,4,91,161,41,154,131,97,163,96,48,9,2,240,2,124,32,61,50,128,4,108,99,80,11,197,125,45,104,164,64,58,74,35,217,92,194,89,117,78,186,168,140,106,160,86,167,40,140,120,165,19,42,
106,130,69,136,132,8,34,177,212,7,20,67,49,246,102,3,22,32,0,112,3,2,27,192,12,203,144,1,14,192,29,112,225,166,110,10,167,175,5,91,50,186,71,140,0,0,239,1,0,13,198,5,244,113,3,12,144,6,99,121,155,69,234,
159,213,181,135,29,9,87,52,38,93,2,106,4,254,196,164,141,250,155,196,137,131,193,153,172,194,89,151,225,120,76,222,56,169,130,137,47,239,71,136,180,132,75,131,2,33,42,36,82,107,160,0,6,227,255,111,216,
129,153,178,17,23,218,161,170,171,154,158,174,58,167,134,160,108,177,234,22,2,17,0,2,176,4,19,181,54,172,25,168,252,249,171,250,234,145,30,185,74,73,154,172,250,183,172,2,59,176,2,235,172,160,7,106,159,
199,141,56,73,132,150,234,56,40,153,5,121,64,68,175,196,81,103,224,2,25,64,3,7,131,32,152,169,6,37,96,35,14,208,143,232,202,29,158,233,170,175,42,91,177,122,4,46,2,0,35,240,2,12,208,7,34,64,4,172,180,
74,66,42,172,255,25,164,106,137,74,208,67,5,190,185,179,77,74,176,136,200,141,64,203,141,17,138,106,217,200,6,4,203,168,32,224,116,160,118,6,221,168,180,12,107,40,232,213,66,69,246,74,139,226,7,58,224,
122,32,144,5,9,224,0,49,226,4,5,192,177,33,187,170,157,89,108,114,202,174,237,202,71,46,194,41,101,181,1,74,32,160,115,213,135,255,201,175,30,217,67,58,27,151,80,170,156,65,43,161,146,186,183,124,43,169,
65,91,176,80,10,2,164,215,3,16,42,145,162,55,137,53,249,109,227,197,255,105,250,82,0,88,0,55,2,160,0,14,0,3,167,74,0,5,17,182,45,58,182,174,117,16,36,107,182,30,7,0,231,17,0,35,96,2,65,153,19,110,59,87,
253,73,93,30,169,186,52,150,179,188,201,179,8,74,156,122,11,152,241,87,187,241,199,136,141,216,131,182,139,156,64,107,180,204,218,179,32,0,157,245,179,156,213,58,142,230,72,142,104,195,87,39,48,55,50,
64,2,58,98,48,66,112,20,49,82,0,31,123,185,152,43,58,26,199,185,121,84,178,24,216,113,119,0,0,6,48,5,2,48,48,98,131,104,57,27,164,140,87,164,172,11,4,235,11,4,171,100,172,200,26,187,47,217,141,87,90,187,
82,170,187,247,123,191,139,216,131,251,235,136,139,248,136,76,118,165,220,248,187,9,26,165,132,248,121,131,136,161,64,68,115,120,117,87,119,165,104,45,52,143,36,112,4,4,64,117,66,208,1,92,123,16,108,10,
178,232,42,23,170,26,17,152,187,174,23,193,113,179,216,113,132,32,2,206,165,4,221,230,6,70,32,131,103,217,171,190,42,183,170,244,175,61,59,255,191,161,103,187,185,171,187,56,220,136,76,166,195,134,243,
195,60,216,191,124,41,192,207,90,192,114,128,161,124,160,47,252,66,115,5,117,155,251,194,99,76,144,4,112,200,47,75,48,5,58,208,3,12,96,82,148,203,177,108,122,189,216,203,102,7,49,5,98,44,198,101,91,97,
208,162,7,6,16,0,196,167,7,2,152,7,120,208,139,84,160,155,193,250,194,48,44,195,57,235,5,69,172,172,54,172,126,76,151,191,59,188,183,121,171,176,180,171,180,251,219,100,64,172,195,76,215,151,241,123,160,
6,124,47,173,68,150,77,12,155,252,242,67,132,2,68,230,215,3,66,144,1,219,217,7,48,160,6,58,181,193,4,96,170,233,202,16,34,43,178,16,81,202,30,76,0,99,220,52,220,107,17,237,161,7,71,48,5,120,64,2,72,208,
7,48,27,199,45,124,140,114,219,175,105,80,183,5,108,141,77,247,94,75,139,195,125,43,180,217,24,200,65,59,200,137,252,191,245,214,204,241,199,187,139,108,160,56,137,87,49,224,149,60,102,40,12,108,132,253,
242,67,64,52,107,121,64,255,0,44,251,2,58,165,6,106,48,27,176,128,170,31,12,194,233,252,16,115,65,198,22,104,178,132,16,0,122,16,1,32,128,6,34,128,6,58,27,199,248,90,164,8,208,190,170,219,67,186,169,164,
140,252,179,73,171,195,8,59,196,2,220,187,216,120,136,202,233,179,64,235,141,244,155,187,242,117,191,1,204,208,121,76,151,74,60,146,100,73,4,98,233,60,248,50,201,17,12,68,124,192,0,24,0,1,174,39,4,115,
192,3,29,203,3,161,12,3,231,154,174,168,252,197,13,129,202,30,60,198,34,76,119,232,113,30,174,23,1,34,96,73,210,179,154,105,32,164,187,204,190,173,219,203,2,237,168,63,27,122,184,251,204,188,187,208,190,
91,176,62,43,176,199,252,208,55,76,200,133,204,116,201,121,209,115,233,6,124,0,68,173,196,105,133,50,111,214,247,87,219,28,188,107,160,7,89,12,7,101,150,42,106,144,170,33,43,23,112,221,77,31,28,211,5,
176,202,63,195,189,231,49,5,231,17,1,75,32,2,38,144,7,84,128,203,219,53,212,171,91,93,208,195,155,242,155,255,126,202,140,208,4,67,160,3,60,176,1,251,172,139,28,213,126,41,200,245,219,111,64,44,95,88,
93,160,8,234,139,30,157,165,138,194,160,24,122,40,230,151,40,170,200,0,45,80,2,228,204,181,60,245,214,116,13,194,113,237,193,117,45,198,225,203,202,239,204,58,31,96,3,174,231,7,119,192,7,84,176,40,56,
7,172,54,75,212,166,244,149,58,171,213,117,169,131,151,205,212,77,77,180,144,173,168,191,123,209,57,168,127,145,189,172,83,77,187,153,253,136,68,140,220,12,240,219,252,146,117,18,25,95,246,54,222,134,
185,1,204,99,142,103,176,6,160,58,2,176,224,0,25,0,182,94,172,77,241,125,158,180,29,190,55,61,78,122,160,7,75,128,7,31,32,3,108,96,4,121,160,80,193,26,195,109,213,186,48,132,220,84,247,151,139,237,183,
143,205,208,79,90,151,144,21,225,5,220,172,201,61,176,201,204,100,64,220,100,88,205,221,12,96,4,248,242,121,78,231,116,25,46,157,220,124,3,190,104,126,16,224,7,12,240,161,71,129,20,243,77,37,157,137,185,
83,128,255,198,134,224,37,171,83,119,35,176,4,35,96,7,50,192,0,46,38,160,195,93,199,1,106,212,71,173,160,215,24,209,67,220,187,58,8,184,147,13,176,18,62,156,14,205,199,217,125,156,156,61,156,32,16,141,
146,218,111,82,250,126,80,203,60,97,185,92,214,183,6,66,64,2,0,80,0,60,240,181,28,140,185,178,13,227,97,43,124,182,93,8,199,70,124,138,96,52,54,48,2,52,0,6,58,144,82,36,176,154,13,53,224,67,74,99,212,
197,120,135,29,205,75,58,180,180,155,208,69,251,212,204,154,168,140,62,156,70,254,224,80,190,164,140,190,172,137,136,217,29,146,225,45,233,168,153,87,69,18,9,2,75,61,137,99,205,105,95,137,6,90,160,151,
9,128,20,109,125,185,113,145,230,47,126,158,176,69,198,116,199,41,119,176,0,2,160,3,1,0,55,113,188,154,252,12,172,129,94,212,84,192,6,140,124,221,204,253,216,57,24,133,47,137,199,121,188,172,17,78,192,
135,88,225,132,238,232,213,109,151,138,56,229,88,125,160,32,144,121,88,236,127,127,121,196,7,44,255,157,75,12,145,68,0,1,34,53,206,108,154,202,170,210,234,109,238,170,114,142,129,210,98,0,237,211,7,58,
192,5,166,150,127,185,60,199,29,201,120,170,171,74,186,137,224,215,88,191,184,219,212,71,171,199,147,142,126,127,25,192,239,213,151,201,189,164,117,105,106,4,108,228,178,43,229,138,178,151,70,235,168,
133,119,117,138,45,122,137,194,237,227,216,104,189,156,6,91,128,5,61,32,206,95,11,182,107,142,238,33,251,234,183,77,8,169,113,30,125,64,2,150,32,7,167,246,79,170,52,179,213,197,186,250,110,183,122,92,
240,161,7,205,138,158,224,241,171,122,200,122,141,138,173,176,40,216,141,135,232,233,181,91,48,254,166,240,139,42,176,77,139,217,64,12,122,192,110,160,239,39,7,253,14,152,208,105,169,52,71,87,94,112,4,
86,192,0,2,192,197,214,219,177,38,127,242,40,31,65,38,160,8,34,0,2,35,96,0,88,12,2,210,3,61,130,10,232,249,78,228,142,26,161,135,238,141,70,219,243,196,169,127,201,233,247,127,127,106,148,244,40,37,226,
7,41,226,255,7,118,150,19,137,255,2,125,144,5,80,86,151,77,93,69,61,75,221,54,44,204,217,253,121,83,255,155,71,28,138,144,245,116,61,104,169,198,59,110,110,131,3,94,240,4,46,0,2,71,64,246,96,203,234,101,
255,234,225,27,65,31,96,0,126,16,3,254,21,148,16,202,231,70,144,190,188,78,212,111,101,247,195,121,221,128,137,156,13,29,244,148,239,146,197,158,180,59,217,2,135,207,97,154,138,1,14,251,33,29,82,75,227,
99,34,66,32,4,9,34,4,89,144,237,167,214,247,140,44,233,202,45,226,227,189,191,146,15,156,200,20,3,192,238,233,61,152,47,213,156,104,189,95,87,84,144,222,74,192,7,29,208,177,194,98,189,110,93,246,5,64,
178,50,58,5,116,0,8,126,121,121,71,50,75,32,103,84,84,105,8,23,8,143,8,64,64,23,146,64,68,56,105,84,110,75,12,157,158,75,160,32,32,36,164,165,164,32,108,160,170,156,171,173,161,36,32,11,24,66,126,126,
45,125,89,27,11,52,188,11,187,188,52,190,190,192,61,189,190,53,27,66,35,35,45,89,255,174,160,158,209,209,172,160,108,162,36,61,114,192,188,114,61,32,156,210,157,36,50,49,36,135,217,114,103,105,235,145,
64,143,70,8,105,56,56,107,76,45,118,4,37,5,249,5,253,254,5,250,254,9,28,216,175,196,149,131,87,166,76,185,98,160,161,195,135,6,166,24,232,115,198,0,146,37,154,188,44,130,228,238,81,165,74,124,210,24,97,
227,37,28,131,37,214,74,245,48,37,10,149,170,147,172,96,30,250,6,170,71,13,12,2,108,97,216,80,99,151,176,5,53,122,2,29,250,243,231,182,95,43,23,100,105,33,64,72,150,30,157,150,144,56,105,242,211,39,148,
163,208,197,216,26,131,134,28,88,224,164,245,224,195,167,7,155,30,49,210,201,99,212,49,18,60,35,105,34,64,0,97,163,132,62,39,4,243,234,45,88,224,160,194,133,11,25,154,8,160,240,131,129,59,13,69,196,80,
18,33,145,23,141,140,32,181,251,40,41,36,21,54,85,103,142,98,153,234,155,52,106,157,68,29,2,37,75,136,144,23,65,127,6,237,41,180,104,235,162,176,135,33,237,33,75,68,255,3,12,83,87,89,165,10,83,230,171,
108,188,182,122,149,19,86,154,28,114,163,228,240,137,129,227,146,228,231,84,112,76,241,64,34,5,1,30,58,96,224,21,8,97,175,94,191,127,19,50,252,224,231,206,17,19,13,239,252,232,17,225,71,12,141,84,32,63,
119,247,241,81,26,18,152,77,206,52,213,99,165,203,103,208,48,64,74,84,75,44,240,66,3,66,96,176,203,106,170,17,5,219,107,177,25,37,12,47,61,209,64,91,22,47,40,65,67,84,230,16,248,89,43,41,97,163,13,87,
49,120,83,21,9,203,145,18,131,60,56,212,23,73,60,246,225,96,133,30,89,192,80,128,26,58,168,49,80,119,222,17,4,30,96,6,48,116,132,30,17,29,70,36,26,50,252,128,198,99,94,24,177,209,124,148,197,131,159,126,
88,145,210,223,74,176,252,167,27,76,163,176,162,84,11,47,100,81,97,13,89,0,181,26,132,177,161,25,33,48,70,17,19,76,13,47,136,128,193,110,157,96,134,82,84,190,29,98,37,13,49,248,82,98,42,38,41,119,6,9,
114,80,1,87,100,28,117,255,4,132,72,104,204,145,135,31,60,216,213,227,94,146,246,243,87,120,9,25,160,135,11,83,152,96,222,20,17,196,96,66,4,12,24,26,31,92,147,121,68,89,38,249,125,22,226,149,167,164,2,
224,43,224,208,208,199,45,185,176,198,19,80,124,156,217,96,132,192,194,22,204,132,70,245,199,75,22,183,129,192,128,178,80,241,6,14,53,161,108,86,76,159,93,153,24,206,18,99,149,163,14,162,28,169,26,137,
27,63,120,32,131,11,25,240,176,221,63,60,246,104,87,64,63,138,39,17,145,239,106,122,198,9,39,40,114,170,23,236,80,246,17,38,35,21,23,149,53,89,193,250,223,181,52,121,70,194,82,97,242,148,154,153,103,6,
213,43,107,193,70,28,49,155,64,5,19,76,11,35,100,49,13,149,84,69,139,141,197,125,202,225,89,56,49,240,113,198,161,237,60,226,136,183,150,196,144,130,1,55,68,58,169,94,149,246,149,144,66,153,74,100,0,122,
13,233,129,164,31,124,224,11,31,59,147,69,41,18,160,174,74,203,210,192,1,30,2,40,182,27,180,32,196,13,64,233,255,130,140,194,172,57,204,48,196,18,119,45,219,47,110,250,2,75,13,202,108,16,218,73,83,77,
243,12,8,197,244,178,156,89,254,50,192,70,12,50,244,96,4,170,146,213,39,9,17,242,172,128,132,31,14,16,148,174,119,235,90,122,169,120,12,77,1,128,1,35,124,208,2,13,130,196,16,95,147,84,228,173,111,60,253,
94,171,167,41,36,184,225,6,42,178,182,242,31,9,49,188,0,102,79,27,240,164,240,214,14,247,250,240,80,104,170,41,177,49,174,213,64,225,2,163,144,221,192,84,202,46,91,21,129,231,76,251,139,200,113,207,189,
98,26,31,57,50,137,242,150,32,48,143,9,88,100,17,198,204,121,213,140,16,226,7,69,116,135,167,38,240,129,134,30,78,158,186,136,60,170,86,18,9,38,84,196,253,10,231,162,177,17,186,76,45,45,65,195,13,13,132,
25,84,234,169,221,47,131,80,13,215,240,58,215,94,147,80,81,134,53,12,138,253,164,63,56,209,152,239,50,179,138,150,160,131,79,105,233,157,52,216,128,131,144,212,103,101,250,146,68,26,158,48,5,17,216,255,
136,59,51,211,7,187,174,240,131,31,4,38,123,119,176,129,13,38,34,131,45,224,0,62,26,49,2,14,44,39,137,23,177,74,115,155,97,223,211,144,166,10,154,212,0,65,27,144,65,234,130,216,191,34,106,141,127,102,
10,160,0,151,40,44,159,252,2,119,11,16,66,11,122,247,18,153,116,44,90,108,99,83,87,58,36,13,55,196,128,8,149,160,132,190,40,177,50,34,16,1,2,17,248,128,62,8,160,134,18,16,128,122,2,41,225,245,174,55,130,
59,232,193,15,114,144,66,4,224,115,170,181,60,71,50,34,41,201,135,114,184,180,106,136,174,67,61,192,64,11,118,130,12,100,8,81,6,251,51,98,195,96,71,20,217,41,209,39,219,48,224,0,43,132,44,141,229,71,130,
106,235,97,49,228,32,135,62,89,8,148,81,145,67,139,194,56,9,202,56,66,140,8,184,194,19,34,96,35,55,186,241,141,112,236,135,28,17,2,152,41,232,193,6,122,224,67,30,240,240,66,39,65,134,17,51,244,8,71,2,
169,62,105,97,233,20,61,4,158,42,12,4,38,133,5,241,154,255,141,148,164,175,32,102,201,75,62,241,107,193,170,16,133,20,233,33,60,133,82,42,87,226,147,87,184,56,141,52,16,129,140,203,107,37,44,201,232,78,
44,248,161,46,110,220,71,62,115,89,194,94,254,69,15,191,196,3,8,76,128,134,187,77,14,46,152,248,227,35,208,39,200,171,188,234,153,90,138,138,104,14,81,3,169,137,105,3,23,125,164,35,35,169,77,110,66,168,
155,93,35,96,72,137,69,166,22,152,147,129,88,73,142,197,190,98,18,55,52,66,158,23,136,169,76,225,73,9,28,108,193,3,72,168,37,1,8,224,128,12,228,178,0,151,186,148,166,70,96,128,24,160,225,4,50,48,166,124,
214,145,76,72,204,227,134,131,228,92,172,116,51,19,80,208,32,25,125,80,29,70,135,248,72,33,98,173,163,190,58,134,131,188,9,78,99,136,84,66,182,27,10,9,106,48,2,102,253,142,26,238,203,34,181,104,192,78,
79,24,97,121,51,205,43,25,47,0,198,52,88,97,10,54,128,3,46,247,9,199,160,2,244,151,154,138,128,28,76,32,3,67,49,73,134,51,140,255,12,35,144,135,137,41,37,77,170,89,114,197,127,122,112,131,4,241,36,11,
98,186,90,234,246,135,77,176,194,142,155,100,109,34,19,31,52,161,98,212,128,54,35,88,192,178,14,129,82,107,180,141,15,187,232,65,220,240,133,87,188,234,117,121,56,72,2,22,68,224,130,40,168,65,13,25,208,
17,28,75,96,216,95,254,210,4,70,197,67,208,20,209,36,100,74,162,169,64,192,132,28,90,53,13,103,158,98,162,107,163,1,134,94,176,128,13,96,32,87,67,188,230,35,191,170,77,74,2,48,181,223,244,26,1,145,177,
128,181,238,194,41,188,209,15,151,216,166,141,254,214,181,19,94,64,192,59,245,74,224,152,226,224,9,231,145,148,19,2,18,66,230,94,234,176,0,189,1,31,126,192,135,232,48,192,73,107,177,4,24,219,65,132,229,
184,175,56,235,131,85,150,104,34,58,16,208,96,22,125,80,138,53,211,203,213,171,129,53,127,238,133,175,132,50,105,49,39,198,166,23,175,21,6,106,22,88,91,254,6,135,174,113,115,103,129,99,58,128,153,54,130,
8,43,80,66,7,255,10,224,4,115,45,215,193,190,28,42,0,108,128,199,19,36,161,194,110,232,163,59,209,128,6,190,78,2,13,124,219,174,230,62,103,37,255,104,169,129,12,160,129,233,114,177,19,22,179,184,6,28,
125,177,17,101,76,103,97,93,213,23,183,232,77,220,224,7,2,82,142,168,28,225,192,87,94,139,76,104,189,154,81,150,2,80,131,19,20,93,179,129,172,235,209,255,212,20,64,109,112,131,24,32,213,160,138,88,135,
37,46,144,4,78,115,58,9,50,72,3,210,166,225,57,169,130,55,79,11,232,195,11,206,187,85,55,167,87,163,251,139,179,156,23,230,205,26,15,48,181,105,93,64,15,54,176,234,252,250,122,21,103,1,206,86,116,27,14,
35,12,120,166,69,30,50,18,236,9,131,158,182,145,193,254,120,244,163,1,242,79,95,234,97,4,2,136,65,18,78,144,6,202,65,166,57,93,238,116,18,198,141,6,28,164,15,135,216,40,69,75,72,220,138,84,11,33,171,160,
197,104,188,93,45,68,71,206,186,127,99,149,111,157,31,244,166,99,9,65,6,2,138,70,126,160,149,255,146,17,229,214,95,77,66,118,178,137,124,129,133,155,241,9,79,168,75,114,27,93,16,105,151,224,217,56,179,
54,64,251,16,3,17,20,52,203,94,112,3,92,222,57,238,113,95,192,202,121,16,245,181,0,198,62,154,60,237,27,108,32,193,11,86,13,218,154,215,220,213,234,29,45,156,95,124,90,6,93,210,214,251,158,239,46,248,
16,166,217,210,9,216,89,132,96,12,70,230,9,47,76,34,217,3,88,120,161,103,154,4,45,136,32,82,22,207,250,163,143,251,96,61,152,0,186,125,224,182,99,23,193,28,34,160,65,220,3,216,118,185,211,166,182,107,
232,80,116,160,144,67,22,60,155,5,12,156,119,222,244,206,249,206,77,139,131,173,229,123,223,169,165,16,110,129,34,0,168,84,209,89,170,136,185,54,126,28,228,134,67,189,225,50,93,120,76,137,96,133,14,216,
0,32,90,215,250,113,75,104,194,31,220,81,49,30,87,132,17,142,137,131,46,135,123,0,82,72,66,30,206,208,208,79,132,136,125,47,113,218,178,30,101,247,187,219,61,23,56,127,181,122,247,222,222,172,255,249,
92,137,64,7,124,47,4,191,0,1,196,100,207,213,96,155,177,22,16,3,55,132,163,114,81,39,116,161,31,95,100,32,108,161,13,13,120,118,230,47,126,220,227,94,156,243,36,252,129,199,209,32,5,115,27,243,110,224,
46,57,234,165,128,6,62,112,151,64,45,73,119,150,222,39,26,16,228,161,5,34,48,239,237,111,127,115,156,175,151,247,189,183,77,181,6,120,183,134,91,110,179,0,50,48,2,116,242,33,232,52,45,49,112,6,168,116,
97,142,55,129,144,39,121,3,96,118,88,16,0,46,176,125,118,209,70,221,183,121,156,215,41,82,112,6,169,103,42,213,101,4,96,54,110,105,39,5,105,199,7,196,241,33,0,147,21,208,212,10,29,194,7,34,32,2,117,87,
123,53,119,119,253,199,98,245,182,123,178,102,90,32,117,99,54,70,103,52,208,26,71,152,86,71,136,33,39,197,128,89,49,44,37,130,74,1,54,129,211,7,121,68,54,0,8,112,4,43,48,2,218,199,129,118,225,0,14,0,80,
83,80,4,63,80,4,72,82,126,246,146,105,205,49,110,82,64,255,47,82,144,122,128,230,42,15,181,18,113,181,10,230,208,3,66,208,0,55,112,3,181,167,131,54,151,58,120,231,102,247,70,73,4,88,136,170,113,132,52,
176,72,27,115,18,84,164,39,14,216,39,108,103,87,142,23,125,210,23,125,19,152,4,16,96,3,10,208,129,109,4,16,14,192,125,31,8,134,97,8,80,126,240,3,229,55,110,153,96,47,8,69,4,219,214,134,111,152,4,104,32,
50,43,151,67,253,1,11,31,22,45,216,130,1,34,176,106,72,208,135,117,183,131,54,199,4,185,71,68,246,22,20,50,224,58,254,147,140,89,147,38,193,114,86,134,200,111,200,240,2,80,1,74,199,183,31,90,68,108,209,
224,6,239,68,137,85,56,117,68,240,4,48,0,0,58,162,125,30,248,129,199,37,138,0,245,117,63,144,4,105,192,126,105,104,40,233,247,134,242,120,101,231,54,13,113,85,102,164,224,6,161,19,115,230,176,1,58,209,
139,125,200,131,127,152,5,194,56,140,248,163,48,65,232,123,207,248,140,71,104,38,81,243,44,120,242,44,51,97,44,33,19,129,105,192,255,141,24,105,137,23,40,2,58,48,2,230,18,56,220,119,35,230,168,6,232,232,
117,38,80,4,144,84,4,221,22,62,139,176,134,39,32,143,69,192,126,70,224,47,201,71,72,164,16,58,161,80,32,180,96,119,205,16,144,60,40,144,76,144,11,184,231,106,46,102,140,146,68,136,194,0,82,206,184,144,
174,161,107,66,96,54,1,183,27,61,132,13,197,192,124,216,232,9,84,64,4,24,57,137,21,88,100,76,144,1,1,0,6,78,16,56,14,224,125,35,73,146,96,152,142,38,32,5,105,176,109,49,36,122,200,115,118,47,249,134,69,
64,143,52,169,25,132,68,98,163,131,1,13,176,72,51,151,131,62,41,144,66,217,106,56,39,103,49,22,64,75,105,136,201,88,49,27,16,12,81,211,44,234,51,149,194,35,139,210,128,0,25,121,153,3,192,4,31,80,0,54,
240,137,37,80,150,160,24,138,37,121,146,18,38,5,68,224,109,227,243,78,115,41,5,91,192,126,42,151,52,241,167,110,61,212,18,81,3,38,96,130,1,171,182,106,129,249,139,127,88,152,67,212,81,126,215,255,26,67,
200,148,11,128,91,184,229,81,85,115,85,45,0,26,78,168,82,187,240,95,84,48,137,152,89,104,17,96,1,0,176,137,36,249,133,35,41,138,97,248,117,34,192,7,219,150,138,246,34,15,172,40,143,111,24,1,141,133,67,
54,105,139,13,68,2,52,96,26,51,7,38,166,131,155,187,201,155,241,54,148,195,104,152,194,57,59,69,168,152,188,34,20,27,176,107,169,209,2,80,9,145,87,228,136,193,16,133,225,128,0,73,48,157,148,152,4,72,176,
2,30,16,0,159,201,125,101,137,150,220,153,150,122,240,3,220,230,142,226,9,23,150,144,4,49,41,5,49,121,101,239,119,18,44,135,14,254,129,139,242,243,67,167,161,106,45,112,155,62,201,155,252,215,155,6,169,
159,98,5,44,34,149,152,50,118,156,12,51,20,86,211,72,66,192,9,84,228,132,194,67,3,76,215,9,109,233,160,220,104,0,109,0,0,96,40,146,36,137,161,162,200,3,60,160,7,91,64,80,228,135,3,163,55,122,45,201,138,
73,64,151,111,136,6,145,72,32,33,66,74,177,210,25,12,224,255,13,120,40,69,241,121,155,186,137,155,113,234,135,54,103,163,248,249,102,103,178,58,73,233,119,178,33,78,111,82,64,127,39,49,106,210,63,15,83,
168,171,209,7,125,176,136,87,49,145,22,99,45,77,7,4,39,192,164,69,182,109,22,96,3,48,160,15,159,152,161,154,250,117,69,0,158,108,105,130,171,24,166,98,138,158,101,138,162,110,135,166,160,131,69,36,192,
151,166,17,163,49,58,115,51,71,159,115,122,94,53,90,167,131,121,167,233,133,111,46,214,144,123,90,49,216,144,68,43,145,132,180,227,77,203,168,140,96,85,119,144,169,57,251,33,7,191,80,87,1,214,160,146,
90,100,16,208,1,27,120,161,84,202,157,86,250,117,108,217,134,153,22,67,242,112,118,36,26,174,104,16,3,239,87,37,176,64,149,236,57,26,80,81,124,2,240,2,166,113,26,174,10,171,176,58,163,182,103,171,184,
250,102,196,136,128,65,180,21,246,198,7,50,240,139,88,3,54,187,176,1,101,49,12,195,25,33,147,52,107,24,117,54,12,152,18,211,226,21,254,66,5,208,42,169,23,240,255,4,4,112,4,37,16,41,101,169,169,96,152,
173,38,112,101,102,216,173,134,194,7,102,135,122,49,25,147,50,240,95,230,170,52,255,241,13,230,128,1,42,240,174,239,26,175,242,26,171,251,167,131,130,121,159,6,9,73,144,84,3,204,1,73,37,114,6,198,98,33,
212,192,54,67,113,132,242,35,3,20,194,163,17,227,123,14,35,103,230,165,44,17,40,19,182,165,78,72,90,28,94,128,6,209,90,100,91,96,157,86,170,6,60,64,165,86,218,177,60,112,146,121,128,6,46,100,42,106,88,
158,225,90,151,124,144,164,166,58,10,121,41,43,52,81,124,50,59,179,166,83,179,243,74,175,57,171,179,254,7,180,144,132,3,103,16,3,76,16,1,89,58,5,31,224,2,138,27,0,35,224,7,125,208,44,227,16,3,65,52,172,
74,4,99,78,171,77,145,164,58,53,128,82,175,160,13,190,0,183,150,185,181,72,64,6,79,96,7,216,234,0,60,128,186,86,186,186,38,176,5,124,64,47,119,227,165,8,5,174,36,26,147,104,144,6,234,19,131,156,241,97,
46,251,2,42,224,255,174,119,219,170,182,89,179,129,185,127,182,42,111,244,6,73,65,36,3,56,64,55,72,112,184,91,176,5,181,48,189,126,0,0,137,75,173,126,112,6,203,146,11,73,104,19,149,123,111,103,194,81,
68,148,5,202,130,124,85,34,60,142,218,9,70,176,181,153,137,5,43,16,0,112,144,186,242,171,186,171,107,165,173,25,3,91,128,4,177,43,122,95,116,84,181,91,151,68,48,147,176,233,118,105,250,13,162,176,0,13,
208,20,13,176,192,121,40,179,174,42,159,242,90,188,116,122,188,92,197,179,169,19,3,55,32,2,37,212,186,38,32,2,91,112,131,55,232,7,10,236,7,68,245,1,41,208,1,76,176,44,45,80,55,185,38,168,224,27,107,198,
248,131,159,197,7,61,134,13,103,96,49,82,40,157,14,122,3,31,16,5,71,128,186,244,91,191,86,10,3,48,32,2,39,192,7,102,152,9,119,131,47,194,116,1,181,75,162,87,134,74,53,41,10,181,40,10,0,3,48,27,208,174,
11,188,197,8,18,163,82,68,179,121,107,179,18,220,183,185,192,4,76,192,179,144,196,255,4,27,252,193,74,48,110,123,184,135,125,16,1,49,42,2,126,240,117,98,56,5,41,240,1,102,35,119,195,233,81,146,4,195,112,
182,188,235,197,98,10,68,37,14,187,120,87,43,13,64,176,181,23,208,181,71,208,108,100,43,196,171,187,5,50,32,162,153,16,72,103,112,6,121,192,138,39,91,4,102,72,174,48,120,166,254,225,62,41,193,54,9,156,
135,92,28,188,239,170,183,17,60,198,127,200,4,55,192,4,56,192,4,151,192,4,26,252,3,29,28,1,72,146,7,55,16,1,47,121,131,82,112,131,189,140,168,34,96,2,240,146,184,122,224,158,64,67,3,124,32,94,180,177,
140,172,131,185,104,156,115,143,116,81,89,0,180,17,73,164,124,86,149,22,242,126,235,187,181,76,64,6,41,224,2,145,44,201,60,48,1,167,248,169,152,28,3,155,44,162,79,156,7,47,184,168,44,151,110,86,140,10,
114,251,67,10,156,202,170,236,174,96,220,202,124,24,144,160,117,123,102,76,203,55,48,15,82,240,3,91,96,138,55,32,3,121,16,1,38,16,2,31,176,3,41,32,255,1,18,96,5,18,96,7,86,224,1,86,240,1,38,160,4,72,160,
4,141,211,41,71,240,1,55,176,4,125,128,4,49,80,3,32,160,11,199,192,32,65,129,3,53,0,211,13,3,195,202,187,94,54,125,77,65,84,105,122,150,205,85,2,12,148,105,87,236,123,1,16,128,5,29,64,146,171,59,7,86,
138,5,245,123,196,169,183,191,34,199,206,71,213,201,160,86,87,83,76,207,245,28,131,7,178,192,2,192,197,8,162,202,50,203,202,118,7,144,56,27,144,177,140,4,193,197,121,91,112,3,68,112,3,82,112,5,17,45,209,
116,176,3,114,157,2,19,125,209,86,48,7,43,128,5,116,224,7,55,176,5,6,192,41,158,130,4,108,35,97,57,86,38,194,121,38,48,221,179,177,54,205,94,53,140,144,148,85,217,44,77,8,186,78,254,178,200,209,122,3,
79,0,1,1,80,206,74,13,3,171,59,1,73,64,4,69,64,4,134,18,62,70,32,76,228,231,201,158,28,197,48,120,170,223,117,143,166,188,213,13,160,2,9,204,213,12,172,202,253,60,115,72,48,171,115,138,255,4,72,112,3,
105,176,5,33,128,208,82,160,214,34,112,5,59,32,1,28,240,1,113,157,220,20,45,1,7,224,1,30,176,2,44,32,221,43,176,6,86,32,2,45,160,4,126,208,41,83,112,4,120,32,21,45,144,210,175,21,90,253,195,179,112,102,
193,234,53,200,185,39,68,123,24,3,189,177,168,201,7,28,64,166,200,44,40,125,58,28,125,73,240,3,100,0,0,158,93,191,158,77,196,86,170,0,92,246,3,8,160,182,70,112,6,194,20,166,170,157,196,229,154,82,34,130,
37,235,150,59,42,176,213,2,64,219,178,189,197,168,124,219,119,203,202,123,75,214,177,76,203,172,105,66,72,133,4,33,64,1,20,192,1,41,206,1,114,189,3,26,80,215,210,93,221,88,16,4,107,48,3,16,176,2,31,112,
2,31,176,5,39,48,36,38,224,1,6,192,0,49,208,2,204,23,164,231,109,193,141,61,90,6,185,1,5,153,58,188,172,49,77,35,223,73,215,13,206,23,13,235,219,105,84,151,118,148,72,47,93,27,0,10,32,196,1,78,196,10,
160,0,121,96,201,165,109,255,40,10,14,174,170,205,126,241,236,122,177,41,48,235,150,72,54,80,225,23,158,192,2,144,225,182,221,213,29,238,225,98,252,2,191,77,208,63,64,66,73,128,3,69,144,2,39,254,1,40,
238,226,26,224,220,113,112,0,7,192,2,44,128,2,146,62,3,107,80,233,90,208,6,34,240,4,107,176,5,73,192,16,30,128,5,79,192,0,50,80,105,8,56,211,139,141,211,75,238,102,5,41,140,50,192,4,23,129,120,192,83,
181,233,48,40,210,224,5,55,160,229,81,55,162,100,88,134,147,42,2,16,240,0,92,112,206,171,75,196,196,62,230,124,240,134,44,217,36,116,19,213,107,78,4,165,154,82,235,57,225,52,48,219,216,70,231,21,62,219,
121,174,225,95,125,26,240,202,231,126,78,208,7,189,142,104,80,4,20,112,226,45,142,226,28,160,1,207,237,232,144,46,233,52,62,3,65,0,5,90,16,4,109,96,5,72,32,1,43,176,5,120,240,1,80,224,3,16,48,5,75,32,
140,56,128,144,93,149,228,6,57,208,8,111,198,76,62,208,76,142,210,145,141,116,132,50,255,235,87,201,0,182,254,3,33,112,241,40,158,241,67,208,5,67,16,2,111,120,83,97,240,0,14,240,229,60,64,236,48,48,230,
99,158,6,69,80,47,225,163,17,80,125,2,13,126,101,165,26,87,177,57,98,235,182,0,21,158,243,214,78,219,60,143,32,121,222,225,167,225,174,96,29,203,243,208,233,87,128,4,227,126,226,25,207,226,114,173,1,26,
192,1,18,208,232,237,62,3,51,128,2,243,30,4,90,32,239,80,0,5,6,240,3,86,144,2,38,112,5,107,96,1,22,0,1,74,192,7,11,141,3,234,173,228,169,30,148,4,249,246,65,121,198,123,152,58,176,28,203,103,3,32,89,33,
241,254,66,4,23,223,241,29,207,1,67,80,238,33,48,4,132,31,2,71,144,2,48,0,6,106,64,242,37,47,230,40,159,36,164,173,182,105,96,84,125,208,214,63,192,1,93,32,5,160,108,143,41,170,110,222,192,54,108,131,
44,58,127,225,57,191,213,61,159,237,28,190,202,220,30,159,166,179,1,179,204,247,28,58,238,28,112,241,59,144,232,59,144,238,28,0,245,145,30,255,233,84,15,239,16,160,5,192,159,245,91,95,6,30,176,5,90,96,
1,41,160,7,86,64,246,100,176,2,13,79,184,164,197,246,233,21,247,76,94,253,10,111,253,194,152,253,3,253,198,123,40,149,210,148,247,131,130,74,56,112,249,42,94,254,42,158,226,67,0,248,28,240,4,6,208,1,9,
32,191,10,32,230,39,255,248,63,96,126,169,152,6,222,35,162,42,94,251,73,0,8,49,108,12,132,132,75,108,135,32,36,61,140,36,32,61,138,144,61,47,42,149,150,150,2,149,13,42,155,156,156,13,160,161,160,66,164,
165,66,47,167,66,45,45,76,17,72,69,20,69,73,82,87,20,182,182,59,59,28,28,113,7,113,44,51,40,88,51,51,44,30,65,90,201,90,80,204,90,196,116,16,22,107,41,1,109,85,100,22,41,56,74,76,50,27,27,50,222,223,227,
76,27,76,89,76,233,234,232,233,236,232,236,235,55,89,55,125,75,246,75,134,248,247,75,145,61,103,142,133,8,197,48,240,132,3,133,93,8,15,14,25,178,139,142,1,23,9,20,240,224,1,163,162,2,24,10,255,50,42,64,
83,36,141,17,35,105,168,120,73,195,39,207,141,34,28,66,132,184,130,70,206,160,128,135,18,145,88,212,195,17,164,153,32,22,116,186,116,41,147,38,79,162,130,54,48,101,10,21,169,27,55,182,72,161,16,226,196,
137,131,33,118,69,229,160,65,130,132,56,88,141,173,8,182,117,6,50,101,109,160,104,129,48,3,202,154,104,22,32,124,176,162,195,130,219,19,72,78,200,72,23,238,92,185,111,239,218,189,203,139,14,41,210,118,
233,252,34,141,112,198,30,3,124,135,15,223,3,241,200,31,36,196,134,238,32,220,149,11,225,66,14,185,12,4,0,0,131,199,197,138,24,53,42,232,83,228,163,71,42,84,140,224,232,115,226,7,133,31,69,100,145,128,
76,136,141,109,219,253,102,74,114,84,195,39,79,158,190,129,110,18,58,74,72,113,83,55,68,136,80,89,228,194,149,3,95,110,81,208,64,245,106,214,53,51,146,125,133,112,86,217,88,8,65,202,84,169,34,198,66,91,
59,31,8,88,104,99,193,3,14,17,234,190,173,155,63,159,239,57,193,125,5,35,197,255,16,129,79,98,196,251,216,195,70,36,103,212,68,27,3,119,20,68,93,46,186,112,176,208,66,26,164,112,7,0,0,72,4,154,69,162,
157,32,69,106,31,161,150,6,14,104,68,176,197,22,68,164,129,134,12,179,193,116,219,128,185,49,242,200,76,89,88,82,199,111,191,13,7,212,39,66,25,55,20,41,67,189,16,129,9,91,112,112,69,18,73,124,1,157,6,
182,96,166,65,46,191,96,225,164,21,116,60,177,66,25,16,172,32,6,4,90,180,113,101,16,16,68,99,134,5,100,232,144,129,14,5,116,16,70,20,110,145,17,129,18,72,116,195,196,13,229,236,149,5,60,250,249,117,159,
95,249,233,215,71,31,50,20,162,79,128,246,16,88,211,75,133,92,145,2,85,12,54,248,224,16,17,126,96,131,13,22,130,38,90,70,34,68,192,33,106,84,156,177,26,30,69,72,129,131,17,68,228,1,2,109,129,226,70,19,
35,46,210,48,211,11,0,84,82,135,13,42,204,72,99,37,62,237,36,92,40,58,234,56,84,22,126,152,112,69,8,63,160,17,194,1,93,24,201,208,16,255,7,237,16,135,7,79,28,241,195,22,108,158,240,193,26,99,181,209,101,
151,107,172,33,134,25,85,248,96,158,14,81,136,9,67,2,107,172,71,6,22,219,184,217,230,6,242,204,41,24,6,251,221,0,47,188,126,209,91,167,96,125,228,1,160,97,252,6,58,211,25,5,130,16,16,3,91,72,176,3,163,
140,234,178,104,194,116,140,48,66,164,146,106,20,134,44,35,25,129,105,26,50,160,65,36,26,30,133,131,8,76,135,12,184,136,28,36,55,2,130,170,52,8,49,99,29,178,202,58,43,112,55,14,23,202,39,2,52,208,66,31,
38,232,113,199,21,82,20,249,197,207,196,50,164,18,7,204,110,241,230,13,107,42,97,130,7,81,68,1,7,4,112,172,176,194,211,222,118,251,173,14,88,43,240,192,153,81,144,65,70,43,112,226,41,239,188,243,202,59,
54,6,104,99,208,7,218,103,35,193,246,158,112,35,113,3,9,255,253,183,143,34,36,0,252,88,64,73,196,65,221,146,26,44,9,161,6,11,165,144,194,20,35,116,64,145,164,161,133,17,134,9,104,84,124,177,12,255,72,
68,112,3,14,103,96,204,135,97,126,10,200,6,9,114,208,32,122,15,170,158,76,122,3,9,176,188,114,203,177,190,252,91,38,54,14,39,64,205,47,136,96,194,7,116,132,192,17,10,7,244,254,51,146,81,169,100,180,12,
34,174,210,130,9,118,180,209,70,182,43,120,0,195,10,4,180,101,1,183,110,97,173,3,69,0,20,96,65,20,5,76,129,132,220,71,179,45,190,217,101,187,45,239,247,110,239,137,254,250,232,71,208,7,13,12,8,172,143,
221,34,47,82,32,221,1,221,224,1,146,128,247,31,56,67,18,240,128,1,18,119,161,48,132,70,1,142,187,2,14,46,229,5,42,196,0,7,17,112,69,12,228,16,3,25,108,14,100,33,195,91,15,72,38,135,69,152,174,7,177,82,
157,8,101,228,58,76,208,74,5,176,243,196,236,70,128,1,17,232,129,14,20,96,201,116,122,7,29,191,217,2,88,82,64,195,13,148,96,5,44,180,64,21,2,88,131,181,60,224,1,43,88,193,3,107,168,130,5,148,168,196,234,
141,73,7,20,138,8,24,194,160,0,38,36,129,255,8,110,203,194,248,228,134,1,183,173,175,15,232,123,193,247,196,232,35,49,34,161,140,103,108,193,11,48,16,3,67,48,96,16,1,18,217,6,59,56,170,128,196,192,10,
41,200,69,224,246,24,56,131,69,40,5,6,48,129,11,40,114,17,209,56,46,12,63,224,67,106,66,226,6,42,96,172,114,120,144,65,12,42,24,3,82,121,174,31,28,124,68,99,104,16,66,17,122,178,117,37,124,221,9,87,136,
129,17,220,129,14,119,40,130,176,56,192,2,20,240,238,11,212,9,129,44,136,128,134,31,60,129,61,35,16,130,0,20,144,1,111,65,32,5,29,56,226,26,208,52,158,47,121,235,91,5,176,4,24,84,144,0,23,88,145,114,110,
51,35,251,204,72,198,51,70,128,140,215,204,102,11,172,137,198,85,188,160,79,137,65,68,28,21,193,65,71,208,38,6,41,144,64,30,249,184,131,62,234,17,144,38,160,3,22,14,104,72,68,122,4,36,84,104,100,5,111,
128,7,17,220,64,146,50,88,192,192,238,97,170,145,145,12,116,36,16,93,13,60,201,80,150,129,210,101,161,255,188,132,195,4,208,135,15,164,128,14,31,144,194,9,118,32,1,20,4,227,0,86,225,192,15,146,128,3,28,
156,224,9,88,240,90,24,26,96,131,112,161,201,7,46,72,193,17,87,192,158,241,40,241,152,4,32,192,74,65,129,66,21,0,64,9,69,184,193,25,95,208,2,12,180,32,130,17,84,35,81,189,121,77,166,250,200,120,216,220,
230,83,87,113,3,197,244,139,160,159,155,163,57,3,66,130,20,216,97,157,85,9,92,58,37,80,21,9,216,193,0,126,8,128,103,10,153,17,59,28,178,35,166,65,141,17,246,169,4,17,228,33,15,124,224,67,27,49,88,208,
57,118,176,64,52,232,65,22,18,80,129,58,84,224,176,133,109,168,67,87,214,58,136,186,78,0,45,0,0,42,239,192,17,142,18,131,119,86,161,192,9,128,128,3,34,152,32,5,88,112,203,4,26,32,0,235,89,0,166,29,8,38,
22,32,192,196,38,90,32,3,97,72,128,10,74,209,211,17,76,33,4,108,130,234,42,214,100,188,222,250,182,183,17,208,109,112,127,219,7,197,192,209,170,33,51,168,255,129,2,2,2,58,120,64,157,86,137,110,89,163,
107,5,180,126,0,6,30,152,20,2,29,7,215,14,185,97,174,50,96,77,4,100,112,87,73,14,244,146,35,19,221,76,78,149,5,195,34,246,189,138,85,108,8,27,235,42,21,60,10,0,67,25,193,7,238,96,128,60,60,135,5,65,224,
93,239,36,240,3,34,116,150,8,17,16,193,17,176,64,0,27,188,160,1,5,176,158,14,140,216,129,20,192,0,2,212,147,222,107,19,96,51,12,188,224,193,179,19,128,9,40,32,130,62,168,66,21,171,80,130,18,126,203,226,
22,183,248,20,138,169,35,160,62,7,58,57,44,55,32,206,133,110,116,119,28,93,15,220,65,193,24,177,131,104,204,228,184,45,120,228,52,223,173,96,229,110,192,7,164,228,97,175,249,64,132,169,54,40,186,14,158,
10,3,238,125,47,98,13,27,223,46,143,112,70,0,48,14,0,246,75,217,59,180,50,24,118,176,195,1,40,144,4,62,224,64,6,111,198,65,114,26,128,1,93,42,64,194,21,9,67,7,46,236,90,112,145,201,193,31,254,176,142,
68,255,252,4,19,152,248,135,40,86,241,138,73,241,67,23,59,186,183,167,240,156,56,247,97,27,221,52,130,80,132,248,192,115,121,204,233,0,254,248,14,48,160,162,70,132,124,72,41,28,217,98,169,225,3,229,44,
199,7,247,229,65,14,3,69,4,99,116,35,186,42,147,142,116,47,112,239,30,246,160,229,94,107,217,203,44,43,108,5,0,0,134,6,140,32,1,119,152,130,9,100,16,2,22,28,96,14,115,136,110,17,242,154,134,24,156,193,
130,222,152,19,41,234,240,196,40,92,36,12,71,132,195,182,116,224,131,12,148,160,0,48,16,64,218,214,104,28,227,76,65,2,122,232,131,205,118,36,4,21,19,229,222,248,102,49,138,91,80,98,41,199,36,142,114,220,
32,9,48,205,128,15,176,192,172,157,142,67,116,89,240,227,35,240,64,200,10,32,181,158,83,43,5,144,156,38,53,111,174,28,159,240,208,2,25,244,0,100,82,142,68,232,106,93,147,192,210,32,215,21,224,245,174,
121,237,235,150,31,54,203,240,13,118,29,138,109,131,14,124,64,15,38,200,195,7,230,112,0,255,59,176,192,14,6,235,3,21,36,121,6,55,200,0,96,11,88,128,22,235,204,3,172,21,192,5,169,77,237,28,158,38,53,56,
96,129,7,29,160,243,6,150,110,28,84,124,54,222,67,217,145,8,132,160,28,124,155,157,40,198,43,197,42,132,128,1,249,189,113,198,245,19,56,193,239,16,237,77,243,88,225,85,97,193,17,68,112,7,207,64,60,35,
68,238,64,17,28,25,146,145,164,1,99,125,192,3,26,90,125,131,87,243,21,4,114,172,181,141,109,28,88,148,175,124,215,135,189,188,203,51,191,249,10,128,225,243,246,125,192,7,4,224,7,25,24,0,164,28,205,172,
208,15,15,48,128,197,32,233,89,168,193,26,109,224,25,23,64,196,6,71,184,131,21,160,189,2,236,194,192,10,1,104,128,210,107,144,133,64,19,85,15,118,208,67,11,194,110,28,229,140,189,20,244,62,187,244,85,
97,51,113,218,45,64,34,191,113,33,204,108,86,26,118,58,5,44,160,131,130,31,46,49,51,69,125,240,142,252,200,25,64,210,7,52,84,46,15,38,104,60,254,58,55,160,200,147,255,188,131,149,175,195,174,223,240,134,
61,244,255,242,43,151,121,154,215,121,239,245,0,246,5,3,54,32,2,126,144,7,239,54,86,185,192,102,28,98,4,5,66,58,73,151,116,53,176,1,47,48,2,2,96,3,9,0,0,182,101,0,41,80,68,69,100,5,29,16,0,6,208,2,223,
64,124,198,215,2,122,224,1,202,87,51,162,224,124,196,49,125,103,183,124,45,48,42,112,132,85,183,209,15,218,71,8,116,167,102,106,166,112,119,7,126,226,119,4,48,240,119,8,100,126,130,103,26,105,224,5,94,
48,87,49,0,73,55,48,5,249,2,107,157,147,65,145,64,3,11,48,58,148,119,114,41,247,6,77,208,4,96,200,127,100,248,127,0,232,127,103,120,134,153,199,5,92,96,3,0,192,3,35,160,128,104,32,5,6,35,21,76,145,4,31,
241,17,235,69,129,91,168,116,27,160,10,35,0,0,54,176,5,38,96,2,79,96,48,79,96,56,79,96,0,91,112,3,11,80,3,23,232,97,129,118,5,115,240,130,160,80,51,10,216,0,34,64,28,162,208,110,204,23,125,68,97,255,51,
56,8,40,146,118,42,3,55,48,63,232,1,3,38,132,86,160,112,113,64,132,64,70,69,66,166,132,169,85,26,135,103,49,170,17,14,17,128,7,125,16,1,126,208,2,124,0,63,32,55,101,90,184,133,164,67,2,73,39,4,254,23,
134,98,24,134,252,231,140,255,103,134,101,40,134,100,120,121,255,39,134,10,80,7,9,48,46,10,120,3,104,224,1,211,65,56,175,129,6,32,97,49,110,224,6,52,161,133,139,240,136,47,96,98,34,86,111,39,112,4,187,
240,4,127,244,1,241,55,73,23,152,5,125,16,104,116,103,2,45,48,59,164,213,0,126,48,144,156,88,144,158,56,131,191,56,138,57,24,71,235,53,19,4,183,115,118,160,138,170,40,132,203,34,1,32,229,1,116,224,7,160,
22,6,127,55,113,181,120,139,183,232,72,33,162,4,120,224,7,122,224,7,193,200,87,196,152,116,38,71,58,41,179,7,204,200,140,207,40,147,100,72,141,101,8,134,208,120,147,97,168,0,19,144,0,96,224,0,10,240,2,
38,128,4,121,16,67,43,1,27,3,64,4,8,112,255,139,232,120,6,54,182,8,110,208,3,110,176,0,222,32,3,93,132,1,76,64,4,91,16,2,76,209,149,20,96,2,76,48,73,217,230,97,125,208,2,116,48,7,38,160,75,53,67,122,3,
233,7,2,89,144,154,24,151,67,177,137,166,64,111,2,121,131,255,38,105,59,216,144,41,18,16,16,233,108,61,215,115,113,96,5,32,5,82,225,231,7,70,72,106,81,183,152,112,117,120,34,129,49,49,176,139,126,128,
7,119,176,128,254,49,140,135,176,8,90,88,101,45,249,2,21,208,4,19,16,154,19,16,147,49,57,147,205,120,154,164,153,154,163,57,1,96,192,5,230,198,43,249,34,34,3,48,0,23,144,4,180,121,1,6,134,139,103,16,88,
36,16,149,49,64,2,98,137,3,84,89,82,38,245,3,42,1,44,69,240,3,39,240,41,21,180,117,107,132,1,13,224,115,3,41,0,35,64,90,109,217,150,65,177,137,66,161,157,97,199,137,9,105,27,0,183,151,235,85,71,56,182,
2,17,73,67,190,96,7,21,249,92,44,240,1,126,112,93,28,73,69,30,217,1,15,208,255,17,132,151,26,179,64,60,37,217,2,83,176,128,194,152,15,33,195,34,46,57,58,38,119,114,117,0,154,162,57,154,169,185,160,204,
168,160,11,186,154,160,169,0,14,32,38,35,192,7,72,16,14,26,50,155,179,121,2,73,9,4,33,1,58,53,65,55,121,147,55,49,144,87,154,130,3,76,128,3,72,176,5,63,96,156,177,33,11,105,112,6,21,100,18,107,148,129,
63,135,7,43,20,98,215,233,7,179,115,157,111,233,163,160,192,157,196,241,157,163,66,138,5,133,19,7,66,7,230,41,145,7,176,105,170,184,3,190,208,158,34,0,159,142,179,152,92,240,0,245,9,146,30,17,3,161,114,
2,122,96,0,119,240,1,31,144,7,255,25,101,49,161,8,36,231,146,91,152,107,97,152,160,171,153,160,160,25,167,8,218,160,161,25,167,111,42,154,99,48,1,78,128,53,107,192,0,145,68,4,82,160,161,179,121,1,180,
9,4,70,224,5,232,24,9,110,80,116,235,231,102,31,210,89,41,90,155,179,25,27,82,160,74,50,58,163,70,229,97,6,16,126,56,195,163,33,214,255,163,158,170,163,62,186,163,112,9,10,223,57,105,1,122,27,186,129,
164,48,145,2,51,16,145,44,0,152,207,181,44,59,64,68,82,250,1,88,103,126,30,137,165,87,112,100,71,182,79,63,34,166,134,131,87,231,37,32,34,183,153,21,168,133,24,176,7,110,138,160,121,122,167,112,138,167,
118,154,160,121,90,173,99,112,110,88,99,1,75,16,65,114,38,168,131,122,1,11,228,132,110,192,24,138,176,4,61,192,7,69,151,135,8,176,174,64,112,1,132,170,161,157,66,4,49,64,3,145,136,54,137,7,90,38,32,5,
56,247,169,252,10,170,215,185,137,60,186,163,4,153,137,155,168,28,35,128,34,51,129,92,139,161,65,235,69,27,108,96,7,115,16,171,52,212,11,77,170,112,68,52,3,119,208,2,22,22,120,187,218,1,10,100,113,135,
183,79,39,96,2,167,52,172,151,121,133,201,5,58,52,240,122,125,8,123,96,64,173,161,57,6,207,234,166,120,58,179,50,43,179,19,240,172,214,58,6,106,208,179,217,138,7,234,192,4,239,170,161,238,138,0,184,232,
8,228,202,255,0,36,192,7,190,106,4,235,138,0,64,208,174,238,250,174,139,167,133,144,184,143,24,144,7,126,80,68,38,224,66,38,16,170,253,202,150,164,183,5,2,91,182,101,107,2,53,144,180,69,122,55,12,11,121,
180,33,7,30,16,177,177,10,152,77,218,164,22,233,1,43,144,177,27,171,103,243,73,159,44,1,18,56,16,178,50,176,67,38,112,4,94,149,2,249,114,94,82,70,99,161,147,172,125,88,3,21,144,179,55,59,185,148,27,179,
149,43,185,148,75,185,57,176,185,17,246,37,115,176,4,34,128,162,238,122,155,238,74,4,168,102,4,228,202,24,75,176,180,37,5,4,236,26,181,82,123,1,81,139,155,152,19,3,249,88,103,237,103,0,115,240,1,100,107,
2,164,167,129,97,251,181,34,54,188,108,137,157,110,105,182,158,26,3,163,178,188,128,50,107,227,73,112,124,48,7,40,224,1,115,11,152,198,112,145,120,107,0,34,176,103,180,24,117,88,26,2,27,242,33,33,155,
7,125,96,59,31,144,102,136,171,47,32,151,65,160,243,122,124,176,0,61,80,129,11,133,255,185,155,155,185,60,43,179,57,96,191,249,155,191,154,187,185,155,235,4,5,48,38,110,17,3,172,32,3,177,91,186,64,32,
18,13,4,121,204,11,2,92,74,4,68,32,187,18,60,181,178,11,187,181,27,137,251,120,175,30,0,36,133,200,163,190,219,175,190,219,43,97,91,188,197,123,182,34,64,3,178,198,15,227,228,188,140,241,49,133,208,7,
208,54,183,40,96,189,117,27,183,149,40,2,179,184,152,222,251,0,176,65,120,227,155,96,183,227,1,95,21,73,152,86,42,245,67,65,239,11,191,242,171,2,57,187,191,254,251,196,254,171,6,252,59,6,254,75,197,80,
92,191,80,92,0,90,76,110,217,176,4,91,208,186,17,12,193,156,101,49,136,202,192,252,162,41,68,0,187,179,219,174,106,204,89,49,202,7,206,217,7,244,176,169,36,214,43,194,251,193,252,26,194,179,131,199,35,
92,194,215,9,89,142,48,32,42,156,170,228,58,158,228,73,8,120,32,189,210,235,74,178,218,164,198,128,2,104,185,181,125,187,195,34,48,120,135,119,120,37,33,34,63,32,79,86,96,255,7,165,87,196,252,160,170,
42,155,196,197,152,116,76,108,197,155,43,197,87,236,4,78,112,197,174,252,202,156,91,0,102,208,22,85,112,6,240,114,96,98,28,184,34,209,72,13,123,15,170,209,198,80,171,198,184,233,161,213,38,3,115,178,70,
201,33,83,63,96,59,124,76,157,121,220,199,61,42,182,200,75,81,228,138,170,43,50,107,38,67,112,122,0,109,30,197,200,52,164,138,198,48,3,27,108,2,48,160,195,222,107,123,149,234,72,129,139,3,153,188,5,83,
128,82,94,213,95,243,103,8,56,40,50,141,187,0,193,88,129,11,32,4,77,224,191,172,156,3,90,204,202,2,253,207,255,155,3,173,12,203,7,109,208,2,77,0,17,6,38,41,224,6,109,98,96,196,25,184,22,35,7,78,217,65,
82,246,132,56,224,186,109,92,193,178,11,193,235,108,14,243,128,52,6,96,5,33,48,34,133,72,188,33,54,2,190,155,210,253,26,170,109,25,205,59,58,188,245,160,186,148,6,121,44,66,19,129,140,138,144,236,81,151,
229,108,215,59,189,226,108,146,229,172,195,15,64,255,159,46,240,0,173,161,206,196,73,190,238,12,207,62,134,6,243,167,15,226,132,27,161,243,122,53,208,178,39,167,0,6,173,208,5,0,192,78,144,1,25,16,214,
100,77,208,10,61,208,9,221,213,254,92,0,37,16,61,199,68,3,230,208,13,37,101,65,37,170,106,146,116,138,135,208,64,27,29,204,193,220,198,32,61,23,229,208,13,201,145,136,69,96,59,44,13,182,123,44,98,41,221,
204,164,7,205,49,173,216,55,48,200,255,198,34,169,107,200,3,147,2,112,32,189,65,240,211,7,16,171,30,48,189,65,224,1,38,137,5,230,124,212,88,234,2,73,112,5,128,43,209,148,163,4,63,0,90,157,76,7,125,208,
70,144,129,85,179,182,178,239,43,58,22,152,5,111,160,208,99,29,192,98,29,220,98,141,214,196,221,213,3,237,207,0,92,2,230,86,30,104,66,6,12,32,31,0,37,73,37,129,87,114,48,174,110,96,27,223,181,215,79,43,
193,176,43,209,40,26,31,50,160,4,81,210,41,133,200,216,207,108,222,162,250,169,3,105,2,135,237,7,35,96,0,165,179,255,186,161,124,205,140,81,19,138,112,200,74,139,2,65,192,2,115,0,5,94,193,59,18,249,200,
115,96,7,120,160,105,165,221,1,182,247,0,194,114,120,19,221,218,63,208,67,69,148,2,120,224,31,181,189,34,3,178,65,248,204,146,197,88,3,96,224,219,25,64,0,194,29,226,99,205,202,4,64,220,199,141,214,0,29,
192,5,0,1,88,131,38,31,176,4,27,80,3,112,172,106,179,61,73,20,52,65,52,6,2,234,252,180,60,62,187,68,64,23,131,251,79,121,160,4,31,176,136,202,225,210,125,220,210,72,62,194,48,61,157,211,121,146,144,208,
192,184,129,27,120,131,180,4,39,3,91,33,189,196,16,96,157,109,12,198,48,7,43,32,225,1,96,7,59,124,218,73,237,2,56,16,2,50,160,26,129,91,65,229,251,224,88,224,1,94,101,87,150,20,160,228,196,178,44,89,129,
42,48,6,58,16,214,31,238,3,128,14,232,34,254,225,57,85,226,38,46,208,198,13,192,5,0,226,225,162,30,22,208,2,12,144,5,27,64,3,24,176,0,27,80,84,122,149,87,202,187,255,94,115,181,148,61,30,181,16,12,228,
111,146,162,5,238,1,188,43,2,132,8,205,137,141,222,47,45,170,211,89,136,125,64,174,252,112,24,224,73,217,134,124,32,120,144,217,115,16,12,63,93,189,252,61,3,116,128,7,139,137,165,72,109,123,182,151,6,
186,3,178,103,192,7,125,160,52,61,116,132,46,40,42,42,105,207,43,203,178,165,44,4,19,208,231,88,179,45,129,94,110,62,32,6,229,54,232,35,62,208,5,112,214,173,252,213,1,172,3,98,16,220,230,177,1,75,16,123,
143,120,181,126,32,4,175,6,121,164,83,162,68,32,3,75,185,209,17,124,1,104,0,193,112,54,184,110,18,1,116,128,71,38,160,4,189,130,216,35,220,210,195,203,234,58,186,234,164,39,3,44,50,235,243,157,211,13,
137,223,12,96,0,65,160,217,62,61,195,190,190,235,63,230,1,230,76,159,102,126,6,87,112,2,132,87,187,59,180,5,40,21,231,187,219,7,176,246,18,58,72,78,90,72,202,21,136,1,77,32,38,88,3,5,221,210,237,221,46,
238,31,238,4,37,174,197,95,253,255,207,69,255,225,25,80,0,112,208,52,77,147,1,197,5,137,53,128,1,177,71,124,56,58,153,27,144,7,250,104,57,16,156,4,72,112,1,221,144,239,128,141,20,121,133,7,206,69,7,93,
107,199,164,5,205,31,140,199,107,159,216,47,237,210,33,172,188,54,173,151,206,139,19,24,79,7,27,175,223,196,80,12,93,30,171,174,180,2,39,9,3,192,68,159,169,117,212,182,247,121,49,16,27,41,47,163,76,96,
59,74,154,102,48,64,7,17,32,80,50,175,151,42,75,3,185,109,181,74,151,0,123,138,53,62,80,6,80,224,243,161,31,232,98,189,238,33,158,83,138,142,214,95,157,1,112,32,203,109,189,232,37,176,6,5,32,0,57,177,
1,143,56,14,226,240,135,115,9,45,73,112,2,112,2,246,115,193,14,22,148,7,34,80,246,122,160,128,44,173,234,33,198,246,74,190,252,143,205,150,29,108,199,126,64,71,110,107,172,84,126,241,4,71,2,118,144,217,
122,79,12,7,215,229,174,52,195,122,48,5,69,157,212,102,110,123,1,0,6,16,20,2,41,63,73,141,111,255,2,1,176,6,46,96,7,20,33,0,121,240,70,110,148,170,53,150,225,143,11,8,11,53,42,19,25,58,62,101,137,138,
62,140,141,140,98,25,145,81,145,148,25,78,151,5,151,154,5,5,37,58,4,37,60,60,118,112,112,81,10,27,61,53,171,52,173,50,55,55,27,27,171,27,56,56,50,182,50,50,76,89,89,121,27,186,55,122,41,118,116,38,126,
126,38,35,2,204,205,206,205,38,38,204,210,199,206,210,2,200,200,205,201,126,13,126,35,126,45,32,36,108,75,32,75,232,229,108,32,236,36,36,61,228,232,12,243,12,121,115,43,115,51,250,250,7,26,18,7,44,88,
160,152,97,197,196,29,15,29,58,184,120,240,96,161,139,135,96,2,16,185,241,196,72,154,51,50,98,240,201,210,98,68,0,8,116,96,64,186,131,129,1,9,116,231,210,177,89,39,71,14,13,62,124,22,200,156,249,130,75,
134,73,85,160,40,90,228,232,17,36,70,149,34,17,32,160,201,146,147,2,58,224,148,32,80,64,148,29,23,58,116,68,18,208,131,134,32,25,53,248,100,157,85,67,70,255,22,93,76,152,16,209,181,225,151,12,62,27,148,
124,240,224,225,206,177,104,216,158,201,101,230,71,46,92,106,211,224,10,80,182,23,219,8,61,66,242,44,57,105,174,220,146,149,43,199,185,235,145,146,222,60,63,43,80,204,9,178,111,70,156,29,255,2,14,220,
97,98,173,157,14,15,18,130,126,232,34,64,128,36,124,232,220,112,3,51,6,141,44,66,70,128,129,176,38,72,21,11,4,18,48,88,178,123,158,97,148,239,172,198,156,41,168,6,23,39,82,163,84,169,178,179,12,25,50,
142,160,136,241,97,166,39,35,40,62,196,64,18,202,9,147,3,81,60,28,40,176,195,35,138,133,40,37,26,196,96,32,231,108,140,60,194,107,228,209,133,35,134,12,52,104,112,221,82,98,192,14,140,20,6,248,33,194,
53,115,57,163,141,53,125,21,56,215,55,201,236,37,2,60,236,32,182,210,97,236,40,70,130,28,40,205,195,27,3,116,72,54,208,12,148,177,32,1,102,0,161,48,16,29,74,88,33,218,66,161,145,22,192,67,168,25,160,196,
18,86,45,176,1,108,42,4,64,255,0,4,109,88,96,129,14,14,208,96,206,110,19,162,99,78,112,50,13,55,211,32,106,220,100,158,25,101,232,148,200,115,81,52,2,5,118,214,33,162,101,118,66,109,162,134,3,19,192,160,
128,152,29,132,1,67,9,230,89,208,70,0,130,129,0,207,42,90,233,2,22,14,103,184,113,6,26,91,24,96,197,83,71,28,243,77,130,10,210,101,87,160,5,214,181,151,31,55,184,3,130,58,18,174,211,206,59,132,109,232,
155,29,51,124,8,226,12,44,236,128,153,102,145,25,176,5,66,10,53,212,144,139,165,69,32,131,65,12,156,65,67,12,178,8,161,66,2,4,144,225,163,143,58,148,68,194,110,139,26,121,36,9,171,10,162,164,32,47,40,
128,148,121,85,64,41,229,115,207,85,225,136,178,136,52,7,29,151,25,16,117,212,151,60,40,96,237,181,10,116,96,5,15,16,160,71,128,5,16,0,208,7,124,114,144,160,88,15,103,164,33,67,4,63,60,33,1,91,86,208,
97,128,9,34,36,179,12,161,248,230,219,204,8,34,44,67,47,13,230,46,218,104,98,22,50,118,255,152,99,245,12,100,41,63,154,74,32,16,10,65,176,96,130,1,48,36,244,80,139,46,154,22,1,26,34,96,193,64,43,50,101,
209,128,10,96,244,232,35,25,81,233,214,131,145,191,81,24,156,86,171,44,89,67,29,5,68,161,131,114,101,64,233,28,178,203,49,187,28,35,102,244,252,115,118,67,13,149,137,26,106,128,135,173,152,97,40,244,208,
183,37,192,17,85,9,81,243,128,5,12,87,99,161,53,91,30,88,241,196,7,209,68,163,199,8,4,6,106,232,54,113,233,235,12,56,2,144,221,71,133,2,15,252,168,59,70,34,92,68,165,3,5,97,34,10,7,104,26,135,64,51,64,
32,129,18,33,165,16,42,105,25,7,112,194,13,72,68,177,1,3,53,132,220,0,0,37,159,124,219,39,230,156,67,164,97,235,32,9,243,146,11,52,224,128,33,202,21,171,51,207,22,8,173,172,234,204,138,81,52,39,157,124,
23,230,4,216,114,33,154,66,48,4,144,128,29,106,68,29,117,41,43,172,176,245,214,94,127,48,197,91,202,140,93,118,161,6,198,117,182,218,211,48,88,255,3,220,136,85,72,176,59,116,203,227,24,7,120,131,184,247,
136,59,28,240,33,72,74,164,224,129,11,22,143,154,184,18,72,32,97,65,10,12,108,64,67,13,27,76,254,192,183,22,200,250,163,14,143,179,131,210,111,236,232,129,28,22,160,21,173,16,39,11,92,240,68,233,130,86,
134,42,160,46,117,61,99,68,207,170,227,131,12,184,206,104,5,160,22,182,172,21,6,46,116,176,105,182,51,77,104,2,0,128,0,140,9,6,40,132,65,215,138,119,132,227,133,109,108,202,203,11,244,156,135,54,125,49,
200,4,45,40,87,132,170,7,183,118,64,72,115,142,137,129,248,62,164,55,20,136,136,68,44,216,199,20,252,96,5,43,60,100,52,164,50,77,0,164,16,129,8,192,193,2,75,88,0,171,178,32,128,4,60,160,0,39,251,145,33,
62,192,0,55,165,35,87,142,18,160,85,98,70,156,65,148,199,102,166,11,218,3,151,19,133,42,249,160,142,141,208,78,209,152,82,130,164,209,110,131,92,184,22,23,24,242,128,166,61,64,119,9,72,0,0,108,192,72,
27,24,192,6,255,83,24,219,20,166,224,72,27,232,97,108,35,200,228,242,242,245,188,230,217,80,25,126,200,3,246,206,193,195,30,42,138,29,8,99,64,4,76,196,2,202,224,237,0,35,2,8,224,88,224,135,41,252,199,
105,14,137,98,0,68,112,130,8,208,193,2,169,144,65,253,72,246,69,31,165,233,71,81,24,76,15,24,80,142,92,81,168,7,85,73,82,228,136,243,2,24,20,192,16,58,48,131,54,29,8,157,219,68,208,17,85,178,224,30,249,
72,45,30,76,224,143,181,227,194,32,31,192,5,48,184,19,12,46,112,103,2,2,240,129,35,28,1,0,247,196,231,35,41,201,200,76,250,243,159,210,184,151,217,152,215,73,5,53,192,0,66,136,1,57,12,118,24,71,153,210,
92,218,163,135,23,238,48,3,128,84,10,83,124,139,165,102,130,96,5,37,28,161,98,184,68,92,105,74,243,1,41,40,161,15,6,176,0,25,91,208,128,201,121,17,6,58,152,213,109,124,96,129,26,44,97,101,164,244,223,
51,171,50,205,200,245,84,5,145,184,153,14,148,101,158,40,144,33,104,223,140,255,202,36,44,168,199,161,76,11,76,230,220,160,2,212,73,85,66,50,228,157,137,76,228,7,0,192,85,174,26,224,145,141,196,164,13,
254,153,201,182,153,117,134,104,117,144,0,110,48,14,255,37,70,66,115,131,168,60,54,36,135,33,238,205,136,125,227,192,63,6,210,202,59,224,161,137,232,19,105,226,118,169,132,8,232,65,77,12,104,64,38,85,
64,185,48,216,108,86,52,181,64,0,24,176,128,149,253,15,37,227,168,138,1,35,87,163,5,180,64,1,4,136,74,76,205,96,84,31,144,65,117,140,184,89,5,197,185,199,78,80,139,118,232,20,36,85,215,249,78,48,100,245,
182,93,93,164,13,116,219,200,177,146,117,25,192,77,171,130,12,117,32,104,180,160,6,230,34,135,67,119,56,183,148,72,106,30,39,48,162,102,164,123,0,14,32,209,68,51,144,198,103,4,139,56,41,238,82,4,17,16,
1,4,128,217,130,182,101,18,12,97,192,166,143,202,144,58,11,152,196,178,20,194,172,59,230,39,19,172,172,113,1,89,80,1,154,162,178,63,163,178,142,17,225,140,214,56,255,93,11,38,216,166,115,182,235,124,64,
109,111,155,200,220,46,146,183,253,252,173,63,205,42,80,225,98,163,184,221,48,144,30,54,240,142,113,100,174,135,112,83,84,68,233,193,189,128,8,36,32,7,56,0,5,54,5,56,15,68,224,8,217,234,192,139,212,55,
88,17,128,183,5,86,208,65,7,248,32,4,1,52,64,0,117,8,3,82,162,34,52,11,180,224,99,41,89,7,193,50,43,51,65,200,164,6,53,193,166,104,205,115,90,161,221,145,18,227,196,196,151,38,96,206,216,78,21,193,132,
172,173,60,113,219,213,221,246,182,183,18,158,112,133,45,236,227,130,198,5,15,52,104,235,57,64,28,226,128,61,119,30,68,48,177,158,83,44,129,21,75,192,136,39,234,67,7,158,34,227,192,118,215,187,54,6,239,
17,190,69,2,150,178,84,5,97,104,82,84,144,170,44,7,32,217,72,139,242,95,0,151,36,3,39,63,185,1,67,54,196,121,254,235,147,1,63,181,203,231,4,228,151,213,121,213,5,51,88,145,185,61,51,154,211,92,214,77,
170,45,195,222,104,233,130,106,240,255,67,149,148,18,123,230,42,7,61,216,48,143,31,240,77,207,44,224,51,137,238,250,3,60,84,44,0,78,195,165,119,77,243,129,68,35,193,4,25,176,64,22,48,208,0,12,188,64,0,
92,224,129,168,115,178,28,51,232,96,1,30,198,236,58,50,199,171,86,116,165,167,33,11,3,114,176,105,212,163,106,211,17,227,52,90,31,213,192,229,115,250,91,1,77,144,45,171,21,172,96,172,190,218,193,16,158,
181,132,205,11,168,180,214,197,27,134,210,117,38,95,144,89,115,80,8,174,1,28,37,177,17,102,4,135,201,210,196,7,248,130,4,254,81,34,20,236,64,10,122,128,193,168,68,245,144,105,83,59,209,120,104,1,22,162,
16,128,208,121,187,1,232,69,78,76,153,115,57,0,48,0,190,185,154,179,57,170,242,146,207,245,84,8,10,144,74,84,124,192,156,68,56,226,130,173,205,160,3,100,247,239,3,15,188,224,6,111,48,0,18,80,7,174,154,
89,214,141,84,193,111,205,171,201,134,11,247,199,216,208,181,143,249,240,195,102,50,215,135,167,188,51,3,162,251,113,20,255,195,146,228,211,189,67,4,92,160,0,244,65,155,52,116,112,249,7,170,45,2,37,248,
161,15,0,248,81,98,145,240,2,156,115,161,102,58,128,2,185,247,231,166,148,232,212,226,110,210,236,75,232,123,95,48,80,226,16,204,178,82,83,163,62,117,240,24,24,224,130,100,103,130,177,158,245,6,119,221,
235,9,63,243,63,153,49,246,53,59,252,194,109,107,192,11,150,192,135,115,156,132,206,22,18,241,157,217,192,1,20,124,1,228,201,14,121,23,82,204,55,19,253,32,2,118,104,90,161,15,61,109,194,219,248,5,126,
176,217,11,106,16,1,37,76,1,189,14,8,173,5,36,159,19,220,8,128,70,25,210,105,26,133,3,19,226,200,100,3,15,136,214,164,41,120,29,45,104,225,130,5,96,202,151,166,222,111,5,120,25,193,9,230,106,12,22,107,
187,21,123,17,70,107,101,101,123,51,116,32,104,7,14,109,71,48,152,245,40,21,50,98,243,128,6,0,145,98,23,152,98,95,176,129,204,39,16,86,16,1,20,51,125,131,37,69,131,71,120,17,112,12,47,16,6,64,194,255,
0,72,176,5,79,16,6,97,48,1,72,97,1,72,165,5,63,162,6,31,3,15,151,213,80,227,208,10,49,160,17,211,180,36,193,18,5,161,85,29,218,113,37,210,161,29,23,244,84,92,38,10,94,102,45,0,24,128,173,231,122,177,102,
128,190,133,128,179,199,102,116,49,2,138,37,0,11,0,48,113,227,40,203,5,108,141,129,48,84,112,5,120,149,98,201,23,114,27,248,5,204,55,3,119,112,2,1,128,16,47,34,82,130,55,120,137,118,125,54,96,8,36,32,
5,20,240,4,11,17,6,251,213,51,57,19,21,47,240,115,32,80,70,39,1,87,193,241,131,191,50,19,52,160,2,215,116,51,74,88,137,4,128,127,72,83,122,230,20,85,128,4,128,97,54,133,90,7,123,95,39,107,88,152,133,90,
216,0,38,128,118,89,112,74,24,247,80,194,151,74,22,184,134,25,200,134,110,200,2,95,128,41,34,240,41,33,69,125,36,56,120,91,48,32,45,208,2,34,208,0,60,160,3,46,208,46,79,16,0,133,84,2,227,230,77,62,160,
3,57,96,18,66,226,97,213,211,255,57,85,17,3,158,6,137,53,128,1,176,66,0,75,85,137,16,0,1,250,198,127,80,197,101,82,181,106,179,245,137,99,54,128,92,245,122,163,72,138,165,88,86,167,232,23,24,208,3,11,
144,57,24,23,48,113,5,68,142,193,6,104,200,134,24,24,144,110,232,134,7,48,3,59,112,3,71,224,1,41,192,93,165,81,125,120,152,135,45,240,2,1,16,83,69,64,1,9,193,16,225,183,94,146,183,63,58,112,100,211,195,
50,74,230,40,237,70,64,65,232,110,248,5,6,158,64,9,77,149,127,250,183,127,80,21,85,177,229,137,234,104,91,7,7,107,176,103,133,35,112,133,88,104,118,132,146,13,217,32,0,34,0,0,45,208,10,250,248,107,192,
166,113,114,23,139,3,41,139,33,167,134,67,84,4,125,208,53,12,217,144,222,85,130,54,102,120,225,192,82,81,241,4,87,240,1,1,128,94,60,224,141,169,179,145,98,228,4,136,24,41,206,100,141,194,81,28,53,96,21,
53,130,1,10,64,132,249,70,78,91,182,137,156,216,137,233,56,147,235,152,85,91,135,112,96,119,255,128,241,120,86,54,164,13,200,96,3,126,208,150,113,198,24,113,83,33,71,105,103,114,231,5,104,40,1,199,71,
144,2,25,114,201,102,114,39,224,7,88,48,149,84,217,139,213,182,5,126,160,4,54,166,123,48,144,1,109,240,3,83,48,120,48,88,2,38,3,65,85,96,51,29,89,70,66,162,43,152,230,38,32,3,19,108,68,2,51,33,0,160,149,
111,25,180,127,253,150,106,231,24,72,96,214,106,2,136,91,176,102,3,117,240,142,240,24,143,192,165,128,11,114,54,223,128,152,131,177,67,203,181,143,101,232,24,73,176,3,34,210,134,4,217,134,77,41,62,44,
240,124,116,224,68,220,245,34,119,72,120,91,96,120,74,32,4,61,230,35,63,224,149,31,16,6,46,224,0,22,64,29,16,68,43,54,51,24,183,66,155,242,117,141,4,196,7,157,214,10,170,32,19,35,224,84,24,68,53,251,55,
6,252,118,122,130,4,133,197,105,156,160,168,72,175,87,102,127,9,152,165,40,152,180,39,143,128,114,32,122,208,150,140,65,24,2,67,103,100,88,55,142,225,5,20,176,255,134,203,87,153,148,89,81,39,160,4,48,
96,104,118,216,153,212,246,144,191,40,2,45,144,149,48,96,1,65,32,2,201,56,159,86,32,150,237,53,43,81,225,115,110,178,27,23,135,18,202,180,42,26,17,19,216,216,70,146,232,4,106,144,65,5,224,0,91,230,111,
118,41,85,50,169,142,137,68,147,100,102,147,101,134,147,206,201,161,180,87,32,224,192,13,13,176,97,109,169,143,13,213,138,100,200,143,18,213,7,41,22,7,28,88,167,3,217,162,63,208,7,1,96,5,244,57,149,53,
90,130,131,39,5,34,32,168,133,231,7,66,240,2,6,64,83,83,112,4,1,176,144,86,128,38,62,98,6,62,178,28,162,101,143,114,149,57,241,101,155,171,210,26,95,72,3,246,248,100,9,96,165,251,230,0,99,192,127,78,216,
101,90,154,151,86,197,122,123,217,96,161,40,138,164,168,147,180,86,166,248,114,12,153,132,138,38,128,1,124,0,48,45,211,138,193,39,87,39,202,0,105,192,1,26,72,167,222,233,157,24,200,55,17,128,7,218,178,
139,212,7,168,37,40,5,210,154,255,139,162,217,0,193,136,5,22,128,5,91,144,2,79,160,16,88,32,101,147,122,159,62,210,1,236,225,92,214,211,76,239,224,18,77,58,28,173,0,50,11,96,3,78,96,78,78,48,1,164,186,
137,253,135,151,85,181,170,172,106,91,94,74,102,0,224,142,6,56,166,208,105,80,126,48,54,125,64,160,35,186,100,140,121,148,58,133,48,94,32,5,124,131,172,27,216,5,200,202,124,33,144,7,33,248,119,231,249,
167,128,42,173,211,170,4,74,240,139,45,0,0,217,150,154,31,208,68,66,38,90,225,122,159,81,145,7,136,88,155,206,212,14,114,224,136,6,212,169,53,82,3,54,48,117,10,80,170,244,218,111,213,50,156,249,202,16,
171,39,102,175,166,72,175,250,96,127,153,147,165,200,23,182,246,12,220,240,13,47,64,160,250,56,162,117,6,15,113,151,74,12,128,6,225,51,114,199,106,167,109,152,108,120,16,1,86,80,49,9,176,139,233,217,177,
82,80,4,31,155,139,214,122,69,43,96,2,79,240,4,124,234,0,143,21,174,51,245,9,144,226,92,13,165,18,227,112,255,6,63,216,164,50,65,148,239,167,2,246,234,179,63,123,142,171,182,170,98,214,170,7,247,175,97,
122,161,206,121,86,77,75,23,13,192,72,89,64,116,231,90,74,143,98,181,254,131,181,105,112,7,153,210,181,162,235,134,40,112,5,50,112,7,21,19,79,52,230,114,244,4,173,37,229,177,82,240,139,33,43,2,18,217,
6,100,112,4,31,32,183,102,50,131,147,186,28,22,32,6,169,163,27,157,155,14,32,185,14,2,68,179,49,1,50,89,244,133,35,192,111,93,182,137,195,9,161,87,55,147,9,208,175,175,86,161,176,154,180,99,154,47,203,
240,2,149,165,131,124,59,134,12,155,157,204,52,15,69,48,34,18,160,1,163,123,172,41,182,49,86,224,1,51,182,186,172,11,173,71,224,177,91,64,168,33,171,4,45,181,2,100,176,6,83,240,130,101,50,58,150,3,5,52,
120,30,147,128,1,19,72,188,18,114,36,232,178,174,157,218,169,188,178,1,66,16,112,75,163,165,232,56,189,18,90,180,236,88,133,218,171,112,11,87,118,3,235,7,169,160,69,22,215,166,157,19,255,87,138,98,24,
88,139,6,116,176,3,33,240,5,234,43,186,20,251,5,43,122,5,121,160,7,116,8,26,52,70,163,173,11,168,245,43,173,106,43,168,179,219,0,125,240,1,70,149,154,41,208,52,48,128,63,167,5,46,169,243,140,82,129,169,
123,187,192,62,228,18,90,68,3,45,193,43,95,24,184,112,25,189,2,23,161,212,203,184,71,139,180,178,167,180,30,188,147,10,40,194,173,224,123,1,51,33,60,196,176,42,156,74,124,112,7,41,192,1,28,160,1,49,188,
190,93,128,2,18,144,4,121,128,5,118,240,34,97,80,135,188,200,177,245,244,195,211,74,168,137,54,2,213,228,35,34,16,6,245,164,53,178,194,94,179,82,201,58,118,83,137,152,136,24,130,105,16,165,70,63,104,21,
216,72,160,209,180,10,96,224,0,131,20,72,83,21,6,232,152,184,122,57,161,70,11,166,4,216,156,88,56,86,107,99,94,221,80,86,34,240,133,240,240,27,10,123,61,121,11,68,146,194,27,70,32,5,59,192,1,43,118,199,
51,60,186,176,116,7,49,96,56,130,197,186,14,89,255,130,0,48,173,121,72,168,13,208,99,35,224,64,48,160,4,0,96,0,97,144,2,249,163,63,149,92,201,71,102,70,137,200,203,254,179,24,62,72,64,87,12,77,32,179,
1,11,32,0,166,92,1,254,39,38,234,4,133,170,199,106,180,181,184,214,187,193,55,105,133,178,186,112,12,71,123,18,199,12,45,176,171,114,192,24,140,162,176,110,128,194,206,69,15,27,226,5,104,16,2,59,64,1,
20,96,199,120,156,199,109,56,195,35,119,3,45,208,52,34,21,120,208,108,200,91,149,200,131,154,135,134,42,0,66,16,6,62,210,2,91,208,0,1,128,5,86,96,76,227,92,201,81,16,3,32,128,33,137,120,24,254,233,67,
183,121,197,158,74,116,61,144,5,130,80,7,92,80,7,96,176,202,96,182,122,172,170,193,124,25,166,94,151,180,24,58,123,9,56,97,138,165,180,28,198,107,16,34,55,236,224,6,141,25,108,188,241,92,188,33,3,63,48,
34,23,109,204,67,208,5,201,188,209,110,40,1,63,192,7,1,144,186,128,55,210,158,41,205,176,43,168,120,93,47,13,32,255,2,216,176,6,22,16,6,24,96,60,114,27,142,53,77,164,184,129,14,203,20,41,180,217,57,193,
193,126,157,10,77,85,161,155,109,41,4,129,4,6,168,252,101,249,172,175,88,151,85,253,252,212,80,29,213,218,251,193,166,152,73,54,32,4,90,132,92,153,171,176,14,125,121,26,162,33,49,240,3,214,101,209,197,
124,209,67,160,209,222,201,2,28,128,3,74,176,2,22,99,135,116,237,186,0,48,168,38,173,200,245,130,12,0,32,43,91,0,0,38,16,0,43,224,2,133,61,206,58,16,0,229,64,3,26,226,159,46,211,136,73,242,216,238,220,
89,47,144,0,28,68,72,65,171,175,89,215,217,176,252,184,144,27,208,254,244,13,180,252,99,134,57,2,245,136,141,109,108,194,32,134,61,109,55,87,173,205,0,49,32,2,119,204,1,33,16,219,118,204,1,106,221,181,
33,39,5,169,177,153,130,21,120,45,55,191,62,60,205,119,237,177,34,128,7,200,192,215,38,176,163,100,176,1,208,246,1,193,35,206,53,45,84,120,64,24,213,205,211,186,146,89,62,136,141,161,236,255,169,95,200,
14,157,53,2,9,208,65,238,196,78,87,101,85,96,192,122,78,237,175,255,124,161,83,77,86,251,66,203,166,173,10,211,72,24,92,253,171,194,39,119,236,129,7,116,240,223,118,108,209,198,204,1,105,189,214,41,246,
3,105,96,2,8,225,219,82,196,195,61,92,130,247,36,220,13,46,5,16,142,149,153,228,215,88,128,4,94,217,1,48,48,94,133,77,83,135,192,63,113,166,61,214,205,192,46,209,43,159,188,42,110,82,89,146,221,3,24,96,
3,46,110,91,5,71,112,252,76,222,52,110,222,161,61,118,38,96,3,251,34,0,45,144,5,155,135,61,108,64,14,110,224,80,137,241,213,192,138,181,84,128,7,119,48,219,154,98,209,150,110,199,75,238,157,33,128,31,
10,249,204,83,78,229,174,91,210,89,62,173,120,32,154,122,176,5,66,208,1,169,115,205,71,224,2,86,176,2,207,253,187,28,185,203,193,108,221,214,168,174,127,171,80,95,216,216,36,48,77,89,48,2,149,109,156,
251,42,198,174,10,203,5,8,208,74,43,208,138,181,72,66,64,212,240,45,255,134,234,224,6,13,205,92,139,193,185,143,238,176,104,96,0,117,92,209,118,28,2,20,48,4,150,78,219,51,220,15,82,64,5,119,176,6,128,
168,16,166,65,42,35,88,229,86,222,224,32,11,178,82,32,32,120,32,2,147,228,7,126,93,83,38,224,2,97,96,5,107,208,35,14,52,43,178,18,83,63,2,7,49,48,33,16,221,50,255,137,235,26,225,26,144,221,18,209,180,
197,117,174,0,150,77,112,10,86,189,253,76,147,91,215,231,177,108,227,99,135,13,0,48,2,66,128,1,223,27,103,2,99,194,211,254,80,156,59,14,194,150,74,18,125,5,35,98,228,225,110,209,93,224,237,95,0,224,34,
242,3,70,16,1,107,176,144,158,94,135,103,59,120,184,139,79,119,29,239,74,144,215,162,41,0,148,52,2,53,179,6,53,144,144,29,144,2,54,40,240,134,157,90,115,192,7,190,145,245,254,185,18,139,129,235,4,228,
26,88,156,208,213,254,206,89,128,241,93,133,241,68,171,193,92,5,166,204,41,203,130,110,13,54,240,1,221,182,197,108,135,143,141,210,213,32,144,255,242,193,23,33,72,122,103,94,64,214,154,98,228,198,60,243,
87,208,5,20,16,2,116,106,204,184,208,53,41,64,200,27,27,244,245,68,244,176,91,234,71,47,168,47,154,104,2,112,4,2,16,0,62,130,67,6,176,2,79,128,5,38,163,225,145,5,188,58,64,7,88,127,18,16,109,221,85,204,
164,124,240,183,162,108,181,238,12,15,175,209,17,133,116,72,27,191,193,254,92,133,9,151,147,179,230,91,140,36,0,47,32,63,50,33,7,115,166,152,119,63,190,205,85,36,143,41,3,69,224,15,198,60,219,51,111,209,
253,109,209,55,191,3,39,224,143,61,143,158,35,8,234,85,62,244,136,236,177,74,128,7,30,251,162,34,219,47,1,96,3,170,30,5,24,176,239,88,16,250,22,224,28,225,44,174,63,242,187,167,47,7,189,225,24,172,127,
46,103,0,8,103,49,131,131,52,134,114,114,52,61,36,61,52,11,134,140,24,2,0,46,9,150,96,96,150,0,153,154,0,158,159,158,54,161,54,164,165,162,54,35,2,2,35,172,165,13,89,138,61,178,139,32,181,32,108,184,255,
185,32,36,181,36,190,191,188,181,184,75,196,12,198,199,94,50,69,59,18,28,206,28,20,209,210,209,33,93,33,20,67,206,87,103,120,112,118,46,41,46,226,227,1,1,228,229,232,229,31,235,236,71,238,82,240,82,120,
74,74,241,39,240,34,34,66,66,13,54,46,126,5,44,88,56,99,194,67,10,43,43,218,8,172,226,99,33,67,51,2,205,24,32,193,128,205,146,99,12,136,105,36,198,166,87,15,65,132,98,44,136,65,131,196,25,72,190,122,128,
112,228,104,193,6,12,164,0,88,154,25,83,148,204,4,160,64,153,50,197,106,132,13,77,35,132,96,168,97,232,81,35,16,196,124,177,169,216,209,86,176,94,192,130,89,44,118,236,34,3,47,124,138,80,104,70,193,217,
180,175,215,168,113,8,145,38,15,140,21,1,62,120,248,208,97,156,91,113,233,208,125,72,219,238,3,128,35,241,164,208,171,23,79,132,94,37,34,26,8,17,224,207,6,153,42,107,54,76,193,226,225,201,26,11,13,5,74,
246,1,177,74,21,49,119,248,100,180,90,117,163,46,95,32,9,25,138,255,113,70,206,172,96,178,24,201,90,176,114,195,139,126,96,30,96,194,132,19,128,77,219,59,115,143,192,73,74,64,139,13,42,123,60,226,197,
104,201,46,164,75,220,144,112,227,198,214,174,96,81,165,106,196,136,49,207,143,20,59,118,120,253,202,61,236,16,10,68,168,124,224,145,34,64,91,243,110,205,193,141,155,150,46,187,15,238,240,194,155,71,47,
175,20,17,244,2,7,30,225,194,70,128,40,22,124,160,196,19,86,60,225,193,26,10,89,112,152,100,102,52,40,134,25,16,232,17,67,69,212,109,182,17,49,202,125,4,146,35,49,240,17,131,105,137,28,162,210,74,37,145,
176,192,137,40,214,80,195,11,131,137,146,0,109,51,197,24,163,109,172,188,48,148,33,56,150,100,220,113,198,125,182,92,115,189,60,23,93,45,27,85,104,12,8,121,232,33,129,4,218,237,240,93,87,220,77,19,2,7,
26,36,97,68,17,43,156,7,3,91,46,176,231,165,58,238,173,115,4,124,242,225,241,151,153,126,213,183,23,30,66,248,33,196,8,48,140,240,129,5,81,108,177,69,10,107,255,89,81,70,21,146,49,196,160,5,98,4,1,135,
1,124,200,97,164,133,26,57,117,18,13,34,21,42,7,33,136,128,152,18,35,138,196,34,11,75,39,170,88,67,22,89,188,224,169,167,45,132,106,35,6,89,212,96,84,142,177,64,247,212,45,182,228,210,148,114,199,9,41,
213,84,25,25,201,6,26,87,100,71,65,118,208,112,144,77,148,20,76,73,129,6,69,80,129,196,10,118,180,213,1,122,111,189,229,229,92,239,145,121,132,18,247,236,69,237,9,247,192,83,15,125,34,248,209,2,0,43,52,
0,131,64,50,252,96,133,4,33,176,0,65,25,146,89,160,131,14,22,84,161,69,16,16,4,49,135,1,104,24,74,161,49,23,77,151,145,69,181,92,202,40,142,33,26,114,154,106,179,36,156,48,142,179,128,208,72,142,143,48,
172,240,47,206,85,44,12,46,80,69,231,203,115,183,184,74,85,133,84,68,112,71,118,218,61,3,172,52,33,76,201,193,15,70,196,128,197,28,29,180,213,108,179,234,177,215,78,124,71,220,245,23,61,102,82,203,87,
60,219,70,208,237,183,37,255,96,48,174,5,68,92,129,221,21,44,176,171,32,188,58,248,48,239,188,51,160,192,2,29,249,46,117,232,133,77,81,138,42,170,166,41,156,26,194,98,159,214,67,216,140,160,13,140,172,
27,59,135,177,48,172,10,249,220,34,81,229,50,221,199,199,196,112,66,174,26,148,108,50,88,212,8,59,22,31,32,88,97,71,178,50,207,156,222,151,234,68,171,179,20,216,98,187,237,207,241,224,129,135,8,161,154,
32,194,7,97,136,176,130,5,65,220,240,3,51,63,176,160,69,188,80,8,20,104,16,65,160,224,193,28,172,123,128,7,9,184,216,106,17,162,29,157,77,67,193,95,135,93,246,47,99,175,205,72,219,171,90,156,113,241,22,
107,140,48,197,195,224,141,145,23,56,72,193,129,4,26,80,255,12,52,82,66,19,86,202,99,161,193,128,1,222,116,240,64,226,138,159,147,78,180,56,231,108,0,60,145,75,94,207,207,217,94,126,121,11,2,136,176,165,
18,143,121,128,196,21,116,236,112,133,4,169,131,130,22,124,32,134,121,89,237,117,112,128,3,20,230,96,2,57,228,130,255,58,75,184,29,215,230,22,34,146,128,173,108,99,163,133,172,160,226,20,227,85,108,72,
199,211,216,193,152,87,36,35,145,160,92,211,107,210,14,186,178,29,192,125,37,9,12,240,195,26,146,229,130,152,149,111,113,113,121,207,152,112,6,128,245,65,174,125,239,99,31,182,230,115,2,252,32,65,4,2,
216,2,22,166,32,130,32,88,192,10,124,144,2,11,66,112,135,56,4,1,10,172,51,32,11,182,56,131,32,204,96,5,62,128,192,29,242,96,17,173,97,164,24,23,138,224,115,120,151,35,68,200,34,82,110,28,33,197,56,104,
60,225,105,204,41,202,3,222,216,132,81,66,35,81,65,116,41,96,210,245,176,199,157,33,92,33,4,67,8,193,21,156,17,1,6,244,97,13,48,168,161,36,111,72,142,46,229,48,90,100,234,161,16,219,215,190,77,158,192,
76,39,48,65,4,148,32,0,3,96,193,15,126,128,64,21,176,38,133,29,40,146,3,93,68,129,213,14,112,0,46,214,75,11,112,128,128,25,236,208,7,51,66,16,81,158,217,197,27,17,177,187,98,194,241,16,106,255,75,216,
164,230,232,156,60,174,173,153,122,84,30,145,46,116,40,172,68,192,0,76,202,142,6,178,209,194,238,92,3,145,20,128,33,26,86,224,1,23,60,32,12,53,36,159,226,202,177,158,198,161,207,29,6,48,0,61,56,217,73,
122,74,33,2,91,56,193,22,240,35,2,3,64,160,15,126,104,200,24,127,64,129,43,44,131,5,180,60,128,4,106,201,2,20,208,11,139,16,16,131,24,224,160,7,68,144,128,51,103,76,99,83,132,52,76,99,242,14,109,19,35,
27,197,156,73,210,148,208,45,42,182,72,227,161,24,64,133,60,20,97,122,205,224,192,14,250,214,205,175,92,129,26,187,58,129,23,92,134,133,101,193,0,12,226,155,228,58,217,121,62,76,186,163,135,154,60,193,
181,236,121,143,122,38,33,31,248,204,199,29,60,208,7,19,148,161,12,119,136,193,174,138,240,3,42,41,180,122,13,237,34,235,174,40,6,93,138,193,14,50,136,129,47,171,130,59,87,117,45,109,137,72,196,217,226,
234,187,179,165,38,120,202,44,41,48,20,22,169,147,2,67,165,206,203,27,255,30,66,192,12,13,80,73,59,93,249,21,176,190,217,149,19,80,193,8,30,96,140,11,20,240,128,241,41,75,157,150,252,210,123,228,146,201,
120,42,213,125,123,249,161,61,127,152,31,17,92,142,14,115,200,131,31,44,19,2,92,237,224,7,82,216,213,66,37,16,135,25,216,86,11,16,208,130,68,37,74,25,56,152,32,6,190,216,90,48,53,242,54,147,194,241,184,
199,197,224,93,229,24,149,190,186,49,37,114,152,227,84,208,24,216,99,80,1,13,203,32,153,97,7,41,13,66,6,43,101,224,228,64,17,24,224,6,43,96,193,10,230,20,95,101,199,119,195,103,97,82,76,241,241,236,82,
233,73,95,209,42,149,30,45,240,131,30,12,176,2,62,224,97,13,85,144,0,26,170,1,143,16,48,233,0,174,155,65,25,102,0,129,220,238,22,10,82,59,107,4,104,103,198,8,178,117,130,201,35,27,114,145,27,82,178,157,
244,195,145,82,205,198,218,150,82,234,98,148,58,108,144,129,20,12,80,88,153,250,173,155,219,139,241,148,182,224,133,52,124,96,13,86,184,172,248,108,255,88,62,205,26,53,62,158,240,44,125,35,135,7,122,90,
46,114,215,242,195,13,76,224,135,0,204,1,4,17,96,1,20,66,128,131,34,72,224,4,90,153,30,10,170,54,131,121,229,86,11,186,133,66,234,204,0,5,56,140,241,57,21,234,87,48,55,186,81,89,205,117,195,28,30,102,
28,125,225,187,57,183,13,99,28,153,238,137,217,154,145,52,244,161,171,75,18,228,16,184,249,183,197,130,83,167,110,56,2,4,96,32,179,152,173,151,146,153,229,236,143,143,122,4,33,71,46,2,17,104,95,145,237,
73,31,107,41,25,149,120,234,65,4,82,80,133,29,16,225,4,95,72,194,9,182,34,129,45,111,153,94,96,14,51,20,34,10,17,31,216,193,15,100,228,215,47,53,218,188,8,22,55,42,114,134,115,93,253,10,60,18,119,204,
110,125,92,41,75,177,235,98,65,250,138,208,53,149,18,247,118,32,5,47,144,224,198,145,124,64,122,49,219,99,155,189,151,135,150,166,175,229,142,188,105,108,205,163,211,34,16,218,229,68,96,144,30,240,129,
14,80,216,1,26,126,64,44,255,41,92,225,0,30,96,193,88,191,12,102,49,235,18,66,98,144,151,29,240,32,131,139,6,182,95,192,36,174,171,62,8,108,190,70,247,142,21,115,171,91,253,149,102,140,80,129,8,82,32,
108,160,183,171,129,237,70,59,88,223,229,222,16,146,224,133,51,4,96,13,229,140,153,202,181,45,212,161,94,210,168,153,172,180,1,36,71,79,158,81,107,220,120,192,244,39,173,133,207,81,42,225,114,30,64,43,
31,12,64,75,108,133,0,30,20,160,37,10,230,21,132,88,131,249,65,184,21,3,1,125,80,5,8,164,0,15,132,219,51,4,211,200,235,133,103,152,153,17,47,99,243,244,76,43,101,31,67,14,121,216,130,129,227,96,216,153,
246,109,208,207,120,82,119,190,59,4,13,92,193,123,49,184,177,21,204,227,232,202,138,131,199,221,126,249,205,142,26,228,112,27,25,231,39,208,57,206,247,34,180,19,244,97,104,120,240,0,12,248,96,132,43,104,
129,5,72,255,193,9,126,144,111,135,194,218,233,77,127,240,188,30,116,86,17,200,64,14,200,49,123,194,185,46,241,214,187,255,94,207,196,85,169,217,217,128,118,17,220,65,3,95,96,123,199,185,201,205,104,124,
252,155,83,50,36,17,160,119,227,101,217,208,239,127,79,1,183,113,40,105,29,2,217,0,61,52,60,39,127,110,57,76,99,218,114,63,183,22,146,241,163,4,84,162,182,15,94,56,193,150,139,80,132,43,192,182,8,26,120,
53,189,232,213,224,221,150,53,162,83,151,154,55,252,112,250,139,170,94,215,92,207,127,158,123,205,53,214,115,70,235,212,113,93,90,81,88,187,87,119,188,247,43,218,51,119,41,83,119,69,144,6,53,230,1,43,
16,73,54,20,6,143,54,73,128,71,51,130,87,23,64,134,84,51,119,105,237,147,105,67,166,105,243,4,68,249,129,7,79,176,2,39,192,6,72,224,1,65,16,2,69,160,72,247,176,3,234,199,116,186,213,126,101,37,117,5,4,
102,4,20,4,43,96,2,125,80,40,32,112,36,247,199,47,250,167,127,181,243,47,104,52,132,207,67,5,50,144,4,139,148,29,212,211,113,125,179,77,131,6,109,216,227,93,33,231,12,91,64,5,12,112,3,30,224,255,0,10,
160,99,230,52,14,202,34,14,44,215,78,25,248,78,241,21,79,83,48,5,33,56,100,58,247,134,238,131,7,249,116,7,16,96,2,110,32,3,28,16,4,212,118,13,144,179,3,44,88,53,87,180,6,13,6,1,4,80,136,177,150,91,98,
230,101,30,112,7,120,144,7,192,197,127,70,114,55,68,88,132,86,113,55,20,167,107,21,226,75,108,144,6,104,112,2,215,64,91,113,176,113,29,71,50,217,96,133,40,19,99,216,16,78,94,176,4,45,96,7,60,16,134,149,
165,114,99,72,134,102,88,139,93,18,105,238,244,109,224,102,3,66,6,130,216,2,140,244,100,125,114,120,95,233,38,2,91,96,2,88,144,2,157,24,2,80,128,2,228,87,80,160,200,130,109,240,69,101,128,136,184,213,
96,217,168,136,139,88,6,80,128,44,142,8,132,191,164,132,228,168,108,22,134,17,157,152,7,120,240,3,116,48,91,218,68,133,5,136,138,46,4,94,190,114,119,228,101,63,112,208,22,150,181,94,59,214,44,218,198,
114,96,224,99,147,134,51,241,84,144,193,248,129,33,72,255,140,197,152,120,38,160,4,55,128,7,119,112,16,50,96,4,39,16,4,101,64,1,34,240,3,87,32,5,63,16,7,175,182,2,172,67,136,185,133,136,245,242,121,93,
38,64,13,54,7,41,160,7,34,128,6,145,152,81,213,85,142,194,85,33,36,192,7,15,169,7,237,24,104,41,208,55,110,247,118,85,200,93,115,87,80,195,66,1,69,128,3,12,112,6,83,176,2,60,48,14,150,165,143,142,166,
56,96,128,134,238,5,95,233,115,84,5,233,134,30,232,129,194,152,120,89,249,134,34,144,120,80,101,2,86,160,63,94,224,133,22,0,141,229,183,5,69,144,2,95,20,146,107,48,86,112,201,116,99,133,91,115,9,5,129,
130,2,118,112,7,162,116,122,209,5,128,50,169,122,94,64,5,105,208,132,69,48,50,75,162,80,130,20,104,81,72,133,112,119,61,39,147,50,187,242,1,39,112,6,12,144,7,71,160,148,229,161,114,234,245,104,236,53,
51,81,201,56,187,88,149,240,84,144,54,128,149,137,151,4,192,136,154,113,120,144,137,167,144,31,8,140,244,177,110,74,240,255,1,51,96,0,110,144,6,71,224,68,79,96,126,69,176,5,20,176,101,98,5,151,194,89,
146,113,73,53,172,83,47,112,224,58,116,112,7,126,128,7,104,0,132,175,7,123,28,177,4,94,112,21,214,89,157,200,64,5,143,146,7,125,80,152,28,16,72,138,57,133,180,229,118,47,230,152,81,2,94,32,183,3,41,240,
3,50,96,17,120,224,2,17,248,119,79,41,159,44,119,134,206,2,154,97,66,149,224,198,129,196,8,140,214,183,154,111,248,159,68,150,110,163,164,84,251,180,5,83,96,16,50,224,5,74,224,1,100,176,2,71,224,23,34,
48,5,41,192,2,98,21,156,194,57,151,94,148,161,25,58,3,30,16,116,41,160,151,17,240,156,124,144,6,114,64,5,195,224,86,94,80,59,173,232,5,46,74,5,84,208,33,104,144,4,82,80,152,172,118,0,118,144,80,136,185,
36,82,216,163,60,57,83,94,129,133,169,40,37,38,32,3,75,16,3,66,0,3,48,64,89,233,20,0,200,135,139,237,21,23,9,144,14,9,48,144,107,24,125,29,24,135,253,9,160,173,249,255,154,174,73,15,17,160,23,196,248,
149,34,32,150,88,32,2,121,120,4,143,97,5,142,183,5,163,227,145,182,21,167,172,35,167,27,42,156,116,106,91,115,90,47,43,32,75,115,48,7,65,183,3,31,96,0,63,208,156,17,112,3,55,128,6,121,144,168,104,176,
168,51,26,166,229,119,7,93,193,12,10,165,163,7,48,138,138,73,61,139,233,163,188,18,164,143,25,22,79,96,0,17,192,133,50,0,0,96,184,44,230,192,99,227,243,164,148,148,67,105,40,45,4,73,154,29,24,140,73,128,
154,244,245,159,182,42,160,195,136,100,165,133,140,6,98,0,50,112,6,17,96,5,22,160,5,31,160,150,47,40,1,182,37,75,115,26,167,193,201,172,206,250,172,204,186,167,85,35,75,124,58,7,44,96,173,31,122,56,18,
16,116,31,74,75,30,64,169,224,122,169,164,232,163,82,104,133,193,215,43,9,56,22,187,50,22,17,128,3,94,224,6,74,96,7,14,176,153,246,9,105,129,39,165,161,89,149,208,7,171,151,102,171,253,122,171,0,11,176,
53,167,4,45,0,166,34,112,255,4,99,137,4,50,192,7,38,160,16,88,64,7,6,213,85,13,101,53,13,53,86,211,10,173,23,235,172,212,186,177,28,75,173,115,32,75,91,20,178,44,240,173,249,246,173,148,58,138,150,42,
174,153,186,123,241,56,72,93,112,133,56,5,153,79,176,50,73,144,6,110,192,7,139,193,3,203,98,78,156,105,175,46,215,170,162,137,165,241,228,139,193,40,140,1,123,180,72,187,149,123,145,15,249,48,5,106,49,
5,55,16,3,76,64,7,62,208,6,30,64,148,47,104,5,44,128,5,27,27,167,174,230,181,29,27,182,98,107,173,33,139,2,100,43,178,224,74,75,42,43,174,228,218,178,113,119,61,220,131,133,51,123,5,39,224,174,103,160,
4,41,0,73,229,16,84,99,248,143,62,59,51,54,83,165,85,170,159,163,89,144,67,59,5,89,106,180,73,27,176,173,41,176,145,147,110,72,80,176,5,235,7,119,176,140,74,32,3,50,224,7,30,80,6,109,128,5,33,160,150,
28,48,177,32,43,75,211,42,182,27,187,69,29,43,178,170,139,80,31,218,173,113,240,186,176,27,255,187,175,187,182,43,203,178,85,200,123,131,212,66,144,201,1,116,16,2,166,231,6,103,32,3,71,112,22,86,48,23,
138,83,175,144,134,159,31,48,184,131,183,159,134,75,180,69,171,154,153,182,184,212,235,154,74,245,159,45,208,45,126,32,2,1,128,5,31,80,168,50,96,0,44,96,1,101,224,1,130,74,80,86,224,106,157,103,182,31,
43,182,171,251,190,171,75,178,58,42,187,177,43,138,108,219,182,82,232,36,63,105,158,44,4,114,50,197,1,6,32,2,68,208,3,55,43,150,43,176,119,234,145,139,110,81,129,110,17,149,235,244,4,160,185,14,131,43,
154,149,198,129,6,80,154,0,16,1,170,134,105,179,90,189,30,44,160,163,180,110,166,213,2,66,179,189,83,96,5,41,208,144,50,128,4,139,65,6,229,123,4,87,96,0,20,128,39,32,123,182,240,123,195,33,75,178,242,
107,178,248,70,75,244,59,187,247,139,191,165,168,191,86,168,187,190,151,29,159,203,4,103,112,164,179,9,129,150,212,1,229,193,44,227,128,9,178,225,2,81,233,192,1,137,14,204,87,255,84,234,192,188,174,74,
144,66,235,139,28,252,193,100,124,171,233,214,7,215,7,85,120,176,189,77,102,16,62,104,147,166,164,5,229,75,7,6,64,88,31,26,7,173,155,111,57,252,161,170,91,178,35,219,186,175,235,1,63,60,200,176,171,178,
249,219,182,36,83,158,133,230,123,207,96,0,91,128,6,105,208,50,72,96,0,230,133,192,112,81,67,229,241,4,13,60,27,226,128,197,10,124,159,25,40,184,59,164,175,66,75,154,28,172,106,145,51,171,210,91,198,2,
107,171,150,131,198,166,245,115,249,208,2,38,16,0,30,64,7,62,40,3,55,192,95,22,208,185,41,112,4,33,240,4,219,154,199,124,140,111,242,59,178,61,204,195,61,140,199,132,92,200,151,218,113,225,89,138,249,
155,200,69,188,200,190,23,44,63,144,4,37,42,181,6,108,201,230,83,14,154,60,197,152,96,197,230,99,73,160,44,23,249,121,4,9,48,38,95,44,115,88,90,154,23,60,198,211,171,193,27,44,207,100,220,184,2,58,110,
159,132,115,150,35,4,235,54,5,46,176,119,126,128,4,134,154,255,160,100,96,1,56,246,4,31,144,2,129,212,186,222,26,178,149,218,204,175,235,195,19,77,187,207,28,133,137,60,196,51,181,169,84,178,77,53,53,
72,116,155,86,49,32,3,0,37,121,140,246,192,1,16,206,159,188,197,186,200,56,115,65,23,49,34,38,174,106,184,108,56,180,246,124,202,171,60,198,170,153,211,172,124,125,216,247,115,217,203,180,39,188,37,222,
114,3,0,149,2,10,209,6,43,64,7,76,173,158,18,96,5,204,108,169,21,29,7,9,53,138,26,80,191,213,99,209,152,218,163,153,10,119,111,215,36,187,119,133,134,197,66,255,123,116,218,60,8,43,108,2,121,171,114,236,
20,105,52,131,129,236,33,149,172,10,45,236,32,184,203,187,188,233,67,211,87,112,5,109,56,5,170,172,115,56,221,193,167,124,171,60,93,198,252,220,207,248,129,74,19,122,16,1,208,144,72,112,68,6,0,3,100,64,
6,90,128,2,18,64,7,50,37,1,129,68,213,17,173,178,177,75,209,64,204,163,81,184,213,61,58,104,229,122,128,131,86,50,253,123,13,117,103,88,33,240,255,3,34,144,4,56,96,4,50,144,7,72,160,7,41,0,3,30,32,51,
90,220,210,171,154,14,223,236,210,249,185,188,51,33,154,52,109,0,124,221,134,127,253,159,170,44,216,214,215,220,168,89,216,31,204,207,212,55,15,220,151,15,126,96,0,140,109,0,222,210,7,249,149,2,43,192,
46,109,128,2,41,240,1,217,241,4,204,16,104,223,122,191,225,25,196,248,91,133,165,125,187,189,215,43,117,39,72,46,40,219,70,48,152,55,96,123,118,224,167,203,98,188,91,220,219,248,217,214,45,109,51,195,
93,215,234,76,105,133,91,144,201,237,215,203,77,207,210,187,202,209,173,193,20,94,198,141,203,51,150,211,2,157,134,7,147,187,189,128,161,7,1,128,194,220,141,74,143,189,57,143,209,203,51,128,5,76,66,7,
79,16,72,80,184,173,59,250,204,213,35,196,66,44,223,138,21,13,117,199,12,163,72,1,176,37,219,124,192,7,56,128,6,120,96,2,87,208,1,74,90,222,31,176,30,112,241,210,3,222,228,77,254,94,235,124,23,148,118,
23,199,221,224,122,208,193,59,253,255,224,21,14,225,208,221,211,196,88,125,26,126,110,221,71,160,221,66,176,101,250,1,230,245,4,122,208,134,126,80,168,120,240,1,88,208,6,101,64,6,109,176,6,44,144,2,116,
128,29,76,221,63,78,29,72,224,25,205,92,221,163,68,220,152,206,112,138,208,92,138,33,32,168,82,128,6,56,16,3,158,200,4,121,16,1,56,9,129,48,96,7,118,17,0,225,192,206,156,85,224,78,222,233,116,237,124,
158,48,229,149,38,115,12,222,215,87,62,225,93,14,176,208,173,229,61,93,100,62,205,225,233,54,230,5,203,100,219,59,235,33,30,0,119,160,7,38,160,235,14,137,79,106,1,1,145,225,69,115,128,194,123,206,43,124,
254,142,63,154,200,217,113,187,133,110,218,82,200,163,99,241,3,69,112,2,121,112,6,193,107,212,125,160,4,38,160,22,88,0,3,229,109,3,119,80,51,232,12,38,156,222,233,78,206,139,64,150,51,164,126,220,166,
142,229,171,238,220,239,222,220,94,110,125,74,16,1,36,60,110,5,139,31,249,142,57,220,167,216,101,122,4,7,209,1,71,96,81,2,187,206,100,74,208,7,144,13,222,65,32,231,85,208,6,60,136,5,44,112,46,12,253,4,
152,157,187,131,148,200,177,43,200,75,210,187,211,206,232,105,32,8,182,93,168,85,21,208,74,106,233,119,81,14,130,235,30,42,191,14,238,101,238,231,46,211,59,36,45,119,112,23,165,124,149,109,168,7,129,0,
0,33,249,4,5,20,0,127,0,44,10,0,20,0,206,0,192,0,0,7,255,128,127,130,131,132,133,134,135,136,137,138,139,140,141,133,105,136,49,142,147,148,149,150,151,152,153,154,155,140,56,130,68,104,127,50,162,27,
124,127,52,61,36,32,171,36,127,32,156,176,177,178,179,180,152,56,158,105,105,70,84,70,61,103,36,192,192,169,36,61,61,114,52,52,49,52,127,169,32,170,32,108,181,210,211,212,213,132,158,130,144,70,110,127,
94,127,12,223,131,224,136,12,229,12,75,232,206,61,168,197,214,238,239,240,147,183,131,219,110,232,225,141,224,227,134,230,229,206,196,169,226,9,28,88,13,7,2,65,103,140,252,89,34,240,156,58,26,173,8,74,
156,72,233,32,14,72,105,168,184,241,194,80,92,185,88,251,22,49,80,71,177,164,201,66,184,206,44,20,135,143,18,186,151,48,57,129,144,115,70,101,196,147,56,165,29,28,164,109,163,190,70,12,97,198,60,244,114,
165,208,142,137,66,254,33,65,51,167,83,105,23,119,249,100,20,180,40,33,54,171,178,106,221,10,13,90,52,66,67,25,189,50,214,227,169,217,75,64,128,228,218,229,45,156,82,176,247,255,4,113,85,21,172,174,221,
187,192,182,194,5,122,83,206,217,191,139,46,102,244,182,228,109,33,171,89,237,22,91,204,184,177,227,198,118,181,10,138,171,8,156,223,165,128,255,94,0,34,8,65,84,141,12,127,26,138,169,21,24,51,198,127,
228,168,94,205,122,117,106,213,131,104,28,99,205,56,239,170,104,148,19,177,145,35,41,51,96,4,186,168,112,252,152,232,30,214,127,167,219,17,106,156,252,113,177,203,130,252,46,59,37,91,206,226,96,183,173,
146,107,213,219,183,68,206,133,128,27,49,194,17,233,232,162,137,137,45,42,134,151,235,63,211,201,93,11,90,86,125,241,210,236,185,11,49,32,33,169,187,119,137,192,101,180,81,97,197,9,130,21,102,234,53,167,
220,93,122,33,82,90,93,202,25,35,223,32,101,217,166,29,63,173,228,33,137,41,255,197,35,158,112,4,34,98,28,43,20,38,39,72,100,90,177,193,198,81,44,162,19,205,113,137,157,40,12,106,20,14,163,202,138,249,
13,194,6,9,124,240,1,73,135,214,0,17,32,136,134,45,116,207,42,75,153,22,97,255,93,174,100,133,227,81,135,41,34,212,87,72,6,211,14,141,204,216,102,36,34,36,168,4,36,53,156,125,104,222,97,71,190,55,72,123,
89,25,121,225,97,250,252,84,164,154,75,80,201,138,146,204,101,249,204,154,147,165,49,207,151,179,112,150,11,21,43,138,232,34,137,152,37,121,211,43,175,224,88,156,104,130,16,215,232,71,111,170,9,227,43,
173,56,38,200,48,32,224,41,8,21,28,242,185,9,103,64,68,53,160,97,71,22,106,104,48,77,190,2,39,33,253,124,67,160,57,141,242,131,15,164,45,193,197,80,122,150,182,115,231,152,130,184,145,70,167,158,162,245,
135,120,246,56,58,200,136,132,216,149,234,31,138,174,116,44,88,110,213,74,14,75,251,180,74,230,145,86,46,182,76,89,114,229,120,98,176,150,236,52,228,112,68,197,121,224,77,216,169,170,40,101,162,133,200,
43,37,111,90,27,37,43,88,178,115,167,172,127,248,7,174,34,160,234,98,143,180,91,30,7,31,124,170,170,57,154,145,227,184,91,85,80,6,27,44,148,126,213,18,103,172,43,103,22,131,76,255,137,77,122,171,239,190,
195,10,185,217,31,97,250,235,237,160,73,158,218,36,179,72,117,212,143,181,12,215,186,68,122,121,81,124,79,171,29,225,57,142,177,216,2,196,45,51,39,102,202,235,18,27,115,140,64,90,195,138,231,133,23,164,
50,91,176,161,78,122,59,25,148,79,167,42,217,156,148,158,250,12,146,147,65,58,177,71,243,170,179,152,117,152,102,202,207,116,28,11,249,199,199,8,32,192,22,192,200,58,35,181,87,206,66,219,112,205,183,174,
67,195,2,53,108,128,193,11,45,180,32,196,223,128,11,209,194,11,125,220,176,129,12,53,44,144,37,214,80,31,50,177,192,0,173,118,29,52,249,65,7,238,65,155,133,185,246,91,46,82,220,51,214,40,75,9,14,182,61,
44,192,199,6,89,96,208,7,223,47,180,222,71,22,89,28,94,195,236,53,200,176,1,234,24,252,209,58,225,24,196,158,56,68,12,59,221,102,202,20,71,46,121,89,171,240,186,115,176,68,11,130,195,230,215,30,104,106,
154,42,198,125,79,205,21,227,109,59,236,24,116,15,251,6,137,47,32,62,255,50,226,47,128,204,249,119,223,141,55,234,89,252,241,61,248,230,71,36,188,34,194,28,223,10,229,134,220,196,241,159,43,42,197,80,
245,134,72,19,81,2,72,130,187,229,237,118,176,75,32,248,18,247,7,241,213,64,16,229,83,220,32,34,56,62,242,105,111,129,179,235,81,12,2,242,46,106,77,38,26,94,99,205,165,238,197,177,240,164,225,12,128,146,
86,231,222,230,149,161,236,163,101,32,88,7,222,102,247,135,219,217,144,129,138,123,96,3,37,168,56,9,30,34,130,13,164,206,31,104,55,59,211,137,47,6,114,32,65,7,241,81,51,200,61,7,108,205,184,16,127,130,
149,182,95,176,129,115,113,58,4,162,170,247,48,186,49,195,128,180,179,225,6,134,72,8,241,5,209,16,62,92,196,50,122,184,195,33,22,81,25,200,136,226,172,30,245,141,113,128,176,126,214,1,155,42,242,211,3,
96,253,231,32,187,184,226,121,190,146,44,85,24,168,56,49,76,134,248,248,80,187,27,234,208,141,15,100,227,15,39,33,193,233,92,204,116,69,172,96,20,183,118,24,129,89,138,255,132,132,8,218,111,2,233,191,
255,21,204,54,45,60,143,43,10,168,190,217,137,145,134,52,36,4,44,17,145,70,69,148,175,140,149,148,32,31,42,40,155,84,160,67,31,42,211,226,165,80,147,151,119,89,238,44,7,1,14,160,198,84,42,74,93,141,144,
14,98,37,38,93,57,70,50,62,240,154,132,96,100,36,57,145,198,110,58,144,118,154,116,69,136,110,54,175,165,48,39,138,99,18,101,78,210,166,139,254,237,101,16,239,1,29,156,226,34,205,25,30,176,134,130,136,
165,32,56,196,200,6,38,14,155,177,184,216,124,4,10,78,94,246,64,108,70,33,206,152,116,118,157,61,22,226,152,102,17,143,59,143,197,176,52,81,15,123,70,114,198,49,22,16,131,217,217,206,145,110,28,196,35,
105,104,10,188,225,77,22,60,164,32,15,35,169,201,102,64,108,98,94,179,207,174,142,37,7,63,226,132,157,219,8,81,212,228,226,158,102,17,34,145,49,152,225,71,99,103,205,124,22,162,159,19,252,103,14,203,120,
9,51,162,209,140,57,100,169,249,236,243,174,184,32,138,161,236,255,113,232,179,254,162,76,157,110,137,167,146,217,169,179,136,209,202,70,186,111,129,70,13,169,62,69,154,79,147,98,162,150,103,132,224,45,
231,211,86,131,2,35,80,206,50,12,86,135,225,211,63,216,212,36,202,196,171,88,177,102,81,163,100,212,110,102,204,155,251,4,129,56,25,140,130,17,69,140,100,248,30,73,73,186,66,16,125,244,57,133,55,105,104,
87,177,193,234,45,51,34,166,96,255,162,11,142,68,73,46,133,72,212,100,126,42,67,161,142,177,125,178,35,163,40,22,113,210,9,14,17,174,150,184,219,14,41,72,75,147,142,47,171,113,203,90,33,178,149,85,252,
97,12,39,193,241,170,85,145,115,50,138,50,132,172,65,165,230,247,240,9,190,198,54,130,129,181,24,159,102,25,209,195,240,153,15,21,197,4,24,60,223,131,42,173,14,226,12,105,217,204,5,64,166,94,240,184,227,
79,72,147,27,106,81,73,166,68,222,205,20,7,124,31,117,71,161,195,199,38,226,154,62,4,48,38,166,131,219,68,4,56,124,113,108,198,210,88,178,146,74,65,6,161,131,192,70,255,73,218,233,191,241,130,117,52,246,
157,230,107,97,203,88,240,85,151,178,182,60,163,100,11,76,73,250,56,181,192,61,244,33,47,23,215,178,213,10,76,65,75,233,235,78,36,18,149,209,198,109,105,72,130,230,42,201,167,205,215,138,177,16,135,59,
220,108,21,241,72,147,50,16,196,150,168,37,137,227,234,64,50,78,53,32,16,94,237,124,219,227,52,32,172,23,30,216,208,177,139,64,88,178,171,176,150,199,141,100,223,24,171,41,8,50,215,110,16,254,117,68,109,
53,241,93,204,26,120,130,41,110,96,130,111,52,166,115,28,242,46,247,201,77,26,220,43,144,52,248,69,167,72,73,140,0,161,153,97,70,110,239,172,100,102,44,41,28,123,102,200,90,179,182,72,174,68,138,129,40,
201,31,118,87,135,223,181,142,121,3,104,181,86,236,17,41,10,17,72,40,112,32,135,209,90,245,109,82,150,11,98,25,137,64,216,41,194,118,67,142,181,154,71,90,146,38,83,71,211,155,14,238,93,144,23,101,130,
160,129,15,173,8,201,136,184,194,172,99,37,146,163,212,92,108,251,18,255,17,228,49,34,78,210,254,148,109,101,225,186,100,91,206,176,124,113,44,230,11,117,244,15,98,250,108,16,84,144,240,59,136,16,3,65,
82,180,216,13,42,182,170,201,39,221,220,45,123,17,136,115,118,101,253,9,105,53,103,183,187,216,6,111,242,236,28,18,85,49,52,207,216,35,2,60,110,128,3,37,238,37,139,13,122,69,221,54,202,234,106,230,110,
16,137,38,68,144,211,124,93,166,174,217,222,213,166,68,26,119,169,73,109,7,115,202,86,250,52,82,196,77,141,36,252,33,13,90,62,36,177,161,33,23,166,36,131,213,220,91,172,32,92,109,136,49,91,130,118,16,
44,68,164,5,82,62,29,158,143,61,88,179,51,183,201,107,33,80,243,121,26,4,55,248,185,193,58,181,150,31,163,163,219,107,159,247,218,151,64,71,79,130,178,221,133,118,198,147,236,207,93,82,7,232,11,54,15,
149,227,226,141,43,79,35,9,68,56,166,113,198,75,216,59,62,29,230,239,118,95,220,105,14,100,198,198,219,234,113,229,122,118,131,232,64,197,205,57,121,167,173,90,67,191,189,41,255,43,75,227,4,130,136,1,
9,132,29,64,139,38,70,134,48,47,68,247,100,62,8,186,151,153,186,67,124,118,136,227,188,245,66,84,122,19,78,221,109,65,179,13,248,173,22,204,219,78,163,69,18,208,80,234,211,242,244,106,72,122,72,71,243,
251,240,202,215,94,238,17,175,249,144,41,238,87,191,238,28,48,8,6,175,33,197,81,42,115,14,3,121,185,33,130,217,105,33,3,165,15,150,82,177,207,10,228,243,230,234,219,247,238,225,113,71,29,179,111,167,115,
108,2,52,231,104,12,177,64,130,143,169,208,184,74,202,12,178,74,91,164,129,6,148,51,158,237,238,113,249,5,165,254,2,201,255,225,246,89,96,194,178,227,174,115,205,71,26,196,191,119,18,57,212,82,119,242,
19,98,151,126,148,177,94,203,183,9,82,144,4,50,64,5,174,7,66,238,33,123,174,180,108,123,99,8,221,211,59,132,64,117,185,7,113,177,22,128,57,87,100,180,245,14,253,132,84,223,5,101,31,247,83,12,34,88,220,
64,11,82,112,114,230,38,101,0,52,53,171,48,125,184,51,8,245,119,255,8,169,179,129,168,211,129,249,228,131,58,151,9,157,151,9,53,224,117,248,197,89,164,7,97,129,38,35,117,225,51,72,177,128,154,32,5,39,
144,7,70,96,30,43,4,127,77,194,20,77,150,58,23,88,127,57,104,8,169,195,127,252,231,129,15,196,125,136,64,89,88,71,17,75,5,65,69,248,104,39,8,74,188,98,37,75,161,29,2,39,11,73,192,7,41,87,61,11,150,133,
50,84,129,185,147,131,245,119,123,51,231,110,60,56,134,58,7,132,111,54,130,67,72,9,72,118,77,36,69,29,250,54,78,29,241,21,114,248,105,181,240,130,104,112,6,86,152,69,45,71,23,136,226,12,173,132,59,93,
232,133,173,67,8,185,51,121,58,152,64,134,88,67,102,248,95,210,150,136,224,199,9,222,151,86,253,132,115,13,4,71,10,246,78,206,36,12,116,70,15,178,112,2,50,176,52,109,147,36,209,39,127,212,55,121,45,160,
59,202,88,138,247,87,8,59,136,8,28,120,134,65,8,73,69,40,85,182,165,100,224,183,136,177,88,84,251,148,86,58,132,105,79,54,124,59,21,255,13,16,18,94,17,54,0,12,248,7,125,128,135,112,65,72,208,247,137,199,
118,140,165,248,55,127,208,55,130,224,133,24,40,117,208,120,121,211,40,107,142,72,70,142,245,81,207,86,141,109,20,84,188,21,11,32,40,87,164,135,87,72,65,72,114,232,132,217,16,11,121,32,7,86,184,16,199,
33,53,89,40,7,14,116,131,57,152,140,95,56,8,23,104,138,59,184,138,144,21,144,53,128,3,28,18,3,42,41,124,115,18,90,167,112,139,41,117,115,183,37,98,106,166,12,229,39,76,134,2,116,45,3,133,150,16,1,236,
8,45,230,2,143,159,216,135,53,192,133,124,195,8,33,41,136,251,104,121,132,224,95,183,96,59,76,112,3,72,16,1,34,224,7,38,48,5,6,96,3,35,32,0,34,208,2,175,67,102,151,4,68,87,247,138,33,248,106,10,25,137,
94,148,133,217,34,114,11,81,135,153,32,5,125,16,3,128,54,137,20,51,53,5,228,64,220,115,148,132,32,4,245,152,140,72,73,121,147,224,95,76,16,149,72,48,149,74,160,4,34,176,5,86,105,2,35,160,255,7,54,96,3,
122,32,0,13,32,2,66,16,1,175,35,3,28,181,134,215,69,107,223,183,8,223,248,134,165,215,144,110,51,35,192,208,50,36,87,9,82,152,118,100,66,104,142,215,135,28,249,7,13,80,8,124,153,140,126,121,143,204,104,
138,247,135,127,51,55,134,27,48,152,82,105,152,136,185,5,91,32,8,195,41,2,34,32,8,2,96,2,122,48,2,126,96,156,74,48,56,189,131,153,182,230,138,9,105,8,163,224,95,178,179,75,164,23,23,35,226,105,188,168,
68,113,65,5,38,135,9,47,200,7,45,24,53,156,168,130,26,101,64,121,73,143,127,192,151,131,32,4,94,88,155,247,168,8,168,40,113,18,23,149,191,25,1,17,112,2,135,169,4,39,192,159,133,89,152,17,208,2,136,121,
156,202,105,2,205,217,149,150,105,56,121,247,95,139,120,157,164,64,93,111,196,146,24,229,57,107,217,87,154,208,126,208,116,161,169,226,105,27,117,140,186,195,151,238,73,143,129,67,155,95,184,59,31,137,
155,183,55,152,130,112,3,82,153,4,252,57,163,1,202,159,127,64,255,163,39,128,7,39,144,163,7,234,7,86,233,163,205,249,156,133,147,5,68,36,75,106,69,150,135,112,157,182,243,81,133,128,56,124,160,146,154,
246,109,220,185,74,33,103,92,130,192,147,141,32,5,105,87,145,168,165,23,15,49,59,176,211,58,238,9,155,135,240,2,130,115,8,33,201,8,76,240,7,250,153,4,110,250,166,39,240,130,194,105,2,63,112,5,119,192,
1,59,144,2,18,32,1,41,64,7,116,112,4,119,96,0,6,48,5,83,96,2,38,96,156,198,217,2,72,80,56,24,132,67,105,101,150,252,85,102,105,54,102,183,83,132,28,117,6,114,116,14,66,71,137,223,73,120,228,121,163,205,
183,8,97,5,138,226,131,59,98,74,8,13,144,170,178,249,158,179,105,8,173,163,148,168,8,163,4,58,163,253,121,2,137,89,4,116,250,3,6,112,167,116,176,3,121,154,2,122,250,7,86,144,2,79,64,7,31,112,172,71,96,
0,127,16,164,74,16,1,103,37,3,187,84,80,222,8,144,162,224,88,179,53,10,19,23,100,53,4,107,217,41,9,191,48,124,45,35,255,61,145,17,158,227,105,9,191,214,161,4,244,45,241,216,158,240,57,8,170,26,155,174,
218,170,56,168,140,184,73,8,83,217,159,181,122,2,91,80,4,63,208,175,87,240,7,33,192,1,127,144,167,26,176,167,113,224,1,8,203,2,44,224,1,195,250,7,31,0,168,127,48,5,126,160,4,120,192,159,125,112,86,213,
232,136,0,248,88,215,105,115,19,7,89,79,42,124,184,33,154,76,120,63,169,231,8,82,144,137,21,169,99,17,17,12,6,100,170,126,211,0,146,121,8,170,42,155,102,74,159,203,248,133,181,119,177,180,26,167,127,192,
175,117,250,7,6,64,1,127,128,167,130,144,2,133,192,2,115,128,5,88,240,7,12,75,172,15,155,172,127,144,152,207,217,160,89,128,56,1,120,102,54,132,157,54,231,153,79,250,7,152,154,107,39,99,38,158,58,99,148,
160,165,20,185,116,133,212,178,174,217,61,102,42,179,2,240,7,113,235,174,139,64,162,101,186,59,131,208,7,247,202,159,74,32,5,251,234,175,87,16,2,20,32,176,59,240,7,5,43,1,113,112,0,30,160,255,176,40,128,
2,43,48,3,40,192,180,79,251,4,197,74,7,87,80,168,206,249,7,72,112,3,189,231,95,1,201,143,242,198,143,138,208,155,107,10,173,28,21,137,118,54,137,68,119,87,230,145,4,88,154,8,39,0,108,167,37,39,158,72,
86,212,55,162,66,16,155,2,160,2,127,192,187,188,75,179,134,240,55,246,232,170,23,139,4,55,202,159,59,234,183,252,122,5,255,42,184,28,64,184,127,32,1,130,112,0,10,251,7,40,48,3,216,27,4,214,27,185,79,11,
172,125,250,176,6,96,168,91,32,2,17,224,160,1,201,173,213,132,136,130,176,166,131,217,190,107,202,166,162,80,132,202,144,68,134,116,14,170,139,103,98,211,17,104,80,174,142,144,4,40,247,78,122,184,21,90,
8,166,123,243,55,13,240,187,114,11,175,115,107,8,240,250,158,123,137,129,221,83,188,72,32,163,82,32,5,203,203,188,206,251,188,59,160,1,130,16,7,113,240,7,44,96,189,127,144,189,218,27,4,51,176,2,40,128,
176,86,128,176,30,208,167,127,58,168,135,218,2,134,3,107,101,166,255,190,131,176,166,233,187,88,189,57,115,217,121,10,46,229,44,47,54,174,113,17,10,255,154,165,41,91,110,182,162,110,232,66,86,120,19,166,
111,59,183,42,16,183,8,220,187,52,219,192,36,74,162,195,171,142,47,208,179,202,91,167,129,27,2,69,27,198,130,128,184,7,64,189,214,59,3,127,16,4,106,172,5,90,144,198,106,188,6,145,187,180,146,59,172,15,
139,185,229,203,125,143,213,129,236,203,166,239,219,155,126,204,4,59,156,127,249,23,191,33,235,82,198,34,129,84,67,25,56,80,196,141,64,1,20,144,4,105,27,37,119,116,38,182,107,170,6,76,197,189,187,187,
134,48,197,168,186,170,131,48,56,6,250,159,202,187,188,96,252,7,131,43,176,209,75,198,33,204,2,40,64,8,107,160,198,65,0,1,110,12,1,106,188,2,143,187,2,107,176,2,88,208,194,224,123,168,119,220,199,133,
192,190,130,188,166,251,167,127,250,7,191,196,188,190,135,19,178,73,36,165,75,24,86,148,17,3,69,192,8,63,64,180,20,112,5,104,224,124,199,66,37,229,165,89,242,152,255,187,115,11,197,130,192,201,7,140,8,
13,28,159,126,227,55,136,42,156,23,28,2,238,92,180,168,92,176,78,123,0,32,204,202,173,60,3,37,12,1,250,204,198,109,204,198,16,176,6,107,160,207,255,188,203,41,80,199,91,160,4,72,208,190,193,44,119,199,
60,115,11,141,204,48,26,209,128,236,164,54,233,80,66,87,151,146,33,88,114,96,2,68,219,8,87,80,4,192,86,145,156,232,76,152,241,178,123,243,182,135,192,187,82,124,192,229,140,201,168,122,206,130,0,159,136,
42,2,64,251,197,96,76,180,67,224,171,29,188,184,141,59,3,0,29,203,2,45,208,127,192,198,127,32,6,80,80,212,127,0,1,90,64,0,90,0,1,43,0,3,86,16,0,201,106,2,7,157,208,123,172,208,240,155,213,239,251,7,17,
77,8,17,13,163,202,12,173,21,141,80,75,136,145,163,245,3,31,208,209,138,80,4,21,156,7,29,138,30,254,118,19,165,154,58,79,156,8,83,172,2,7,140,215,46,237,174,48,13,155,62,250,7,91,64,167,95,236,200,69,
171,1,28,44,207,210,43,255,172,139,203,180,182,140,203,130,32,212,98,16,217,98,224,3,62,240,7,4,112,217,98,64,0,107,64,208,117,124,168,155,203,185,235,75,117,114,199,213,95,253,213,149,71,218,193,188,
204,99,205,43,7,194,21,148,97,2,119,160,214,136,112,156,126,133,196,207,210,17,85,3,31,47,155,5,98,218,210,138,16,197,190,219,210,156,76,166,116,11,164,129,253,3,0,43,184,142,76,1,67,96,216,26,176,3,207,
75,1,201,42,168,71,112,4,31,64,7,41,176,194,184,188,207,146,61,217,148,237,3,151,29,222,78,13,3,29,32,213,131,90,213,81,233,155,156,91,218,74,137,218,131,0,214,132,48,209,204,108,209,87,33,148,201,131,
20,126,64,216,136,224,183,189,247,164,92,250,50,163,121,19,38,173,59,169,170,2,195,189,201,227,76,220,9,30,220,130,208,192,2,224,7,203,234,175,202,237,200,28,224,220,28,64,1,33,208,175,84,61,156,87,57,
5,71,64,7,29,224,1,88,224,216,73,221,198,147,253,7,58,224,3,153,29,222,4,240,212,86,240,4,6,45,2,159,205,255,185,24,112,3,167,136,138,176,58,121,25,120,138,125,208,227,108,170,218,97,43,201,246,221,48,
17,144,214,168,188,8,202,192,165,24,10,16,243,241,205,121,93,7,117,240,7,80,222,8,190,155,192,120,173,210,122,141,156,2,16,183,87,9,176,167,252,188,93,192,193,130,112,5,253,58,156,82,16,156,87,249,1,1,
144,2,33,222,180,1,45,203,16,112,226,58,16,5,25,192,226,5,176,6,80,237,2,157,221,0,8,205,213,53,126,127,160,93,8,198,171,185,125,128,1,139,58,160,198,139,232,198,123,3,87,91,3,42,185,73,36,171,23,129,
194,16,121,144,214,178,93,8,191,102,4,103,176,65,179,91,37,194,240,69,11,128,58,189,109,224,81,46,8,165,222,8,226,12,220,7,188,192,35,48,2,38,240,7,122,112,5,187,250,229,21,174,1,168,236,197,63,176,225,
87,121,4,1,224,2,190,158,221,110,14,208,250,220,6,62,64,6,127,80,5,62,0,1,37,176,6,127,192,3,228,237,2,0,160,149,15,254,156,131,110,227,160,141,4,134,110,232,3,170,185,133,121,255,143,133,137,143,91,156,
131,55,0,200,69,40,27,14,21,20,42,162,42,174,141,102,33,240,1,165,172,8,188,177,60,230,113,74,51,66,3,242,88,224,83,60,229,166,190,8,191,11,220,114,43,183,113,59,2,127,224,234,202,41,235,68,251,188,120,
106,235,24,206,188,129,107,0,151,107,0,71,224,2,86,0,3,48,224,1,97,224,1,48,128,203,0,253,7,1,173,5,80,96,6,85,80,5,98,80,2,14,224,236,97,208,1,96,0,0,91,153,170,13,208,55,138,222,237,48,95,159,248,120,
163,225,30,1,53,111,138,51,236,232,168,224,169,233,206,116,161,195,16,114,176,171,71,158,8,188,161,63,169,197,132,207,177,62,5,156,215,136,80,234,81,126,234,252,62,206,35,160,2,143,105,3,176,174,172,215,
237,171,190,106,216,28,224,206,12,239,206,130,250,1,41,0,3,60,144,203,206,158,241,0,189,241,29,15,5,62,16,5,73,189,217,10,128,242,41,175,149,44,223,0,66,80,181,206,90,127,160,92,160,5,90,143,125,41,8,
206,74,8,45,96,243,125,159,140,67,234,255,164,230,94,8,61,47,233,12,67,2,83,112,7,116,48,176,134,160,4,127,144,7,124,112,12,242,254,83,148,108,49,77,188,244,6,158,8,79,239,244,79,207,8,2,255,7,143,217,
234,122,128,149,188,170,245,190,186,240,127,128,193,201,202,235,29,144,241,112,80,242,20,191,2,112,144,246,185,63,236,153,93,2,79,221,1,15,144,0,209,222,234,0,239,7,169,234,156,207,217,151,246,152,197,
125,227,151,205,95,155,207,95,160,138,218,59,224,195,7,137,111,30,136,124,81,184,173,7,177,45,249,133,128,7,140,133,68,153,15,79,45,91,63,157,255,182,164,46,8,21,80,1,77,47,229,238,31,250,163,31,229,86,
63,8,167,223,152,202,10,249,189,170,245,93,79,230,69,0,8,69,91,130,91,126,83,71,46,29,48,139,10,48,60,112,144,112,107,146,16,98,4,16,43,48,29,46,127,0,42,2,13,161,162,126,162,34,74,45,127,127,45,168,169,
173,174,175,170,173,168,172,127,47,24,89,27,53,124,49,114,36,108,127,75,173,191,32,196,197,32,108,75,193,192,38,31,31,255,59,26,176,169,124,50,124,52,36,173,201,169,195,215,36,36,61,223,52,11,53,89,24,
47,13,42,42,117,117,174,21,237,209,176,235,127,235,243,235,54,173,54,248,6,6,119,31,116,59,255,255,40,220,249,81,68,74,132,36,55,18,150,107,48,2,64,128,7,29,26,61,90,67,145,34,132,74,16,214,240,208,20,
0,128,141,17,13,132,252,17,213,128,148,31,17,13,68,136,84,69,235,157,75,88,47,250,220,200,34,163,70,12,107,32,148,253,97,195,211,88,49,100,202,150,248,249,192,97,135,203,24,121,100,88,11,154,106,9,27,
16,221,82,125,147,243,135,70,141,13,89,94,188,16,130,46,30,187,63,237,194,134,5,251,178,213,188,78,35,242,253,225,71,167,173,64,3,63,182,24,188,129,70,198,31,25,88,205,53,76,0,38,34,12,7,145,34,81,132,
179,177,67,199,143,33,87,142,44,233,167,49,169,63,66,34,75,78,37,82,178,101,203,46,99,206,172,121,147,4,8,87,60,255,248,36,6,76,167,159,182,41,142,222,200,67,227,115,233,96,78,255,92,147,218,131,170,255,
213,113,47,70,118,173,80,246,149,216,223,96,219,173,75,144,160,142,71,27,0,238,176,165,64,71,224,157,43,5,79,244,73,26,35,198,159,26,53,106,253,17,128,252,97,135,63,88,54,46,130,129,5,11,12,43,46,14,131,
18,210,226,69,139,149,37,25,55,110,21,185,247,171,247,245,101,197,196,144,180,90,47,215,218,60,245,153,79,165,181,114,26,29,18,192,210,199,31,55,240,177,90,107,192,68,8,204,83,169,116,243,77,109,225,100,
145,149,16,231,164,227,206,30,32,218,151,10,111,176,184,243,7,113,9,252,145,207,62,202,41,119,197,21,4,73,145,4,26,121,236,82,221,2,127,108,80,14,135,2,164,5,192,7,46,164,16,100,10,41,116,96,133,144,29,
77,177,94,123,90,69,70,82,99,2,60,214,192,72,138,137,72,95,126,237,221,146,75,103,176,12,35,154,79,217,164,114,96,130,209,228,193,224,46,57,21,232,10,84,178,93,88,213,85,27,118,88,7,137,33,182,2,226,157,
127,236,145,231,136,189,85,64,156,138,54,232,211,98,8,207,193,184,197,9,51,18,255,177,75,85,52,88,7,167,123,60,166,117,196,7,1,4,64,199,19,79,208,241,193,17,83,152,64,10,147,11,190,135,18,148,2,148,58,
37,73,161,164,146,170,149,178,244,161,229,46,52,244,144,230,78,61,13,104,12,80,202,140,249,14,18,50,224,177,11,50,175,53,37,218,108,83,253,177,192,2,228,108,117,206,156,123,188,241,199,27,208,66,107,167,
158,174,220,105,237,181,122,238,1,134,159,30,169,168,143,1,47,194,24,227,31,51,226,96,221,25,127,156,65,67,42,87,97,208,7,164,126,152,48,133,1,71,76,218,204,17,6,116,234,199,41,251,97,160,138,16,163,250,
33,192,31,38,68,169,106,40,34,192,130,106,170,167,70,211,94,31,89,228,161,75,172,0,134,105,235,79,176,137,217,22,153,176,68,144,135,8,50,196,144,102,152,192,124,70,108,15,169,136,147,172,156,21,236,209,
196,31,77,188,220,74,180,210,214,76,115,180,207,62,11,34,23,218,130,145,0,0,30,125,251,226,15,4,21,244,7,26,68,224,144,198,25,70,160,12,142,56,88,97,128,1,18,45,36,255,252,199,188,6,132,112,68,8,249,154,
32,130,8,45,32,1,241,31,125,180,128,7,135,2,15,92,176,31,127,60,198,246,75,13,199,141,106,45,50,109,32,195,2,20,191,242,203,151,198,168,217,182,63,118,184,212,135,199,189,68,24,230,18,196,156,188,174,
202,90,253,177,155,203,169,196,44,237,179,206,226,60,179,43,52,55,17,45,207,15,156,8,244,20,160,23,45,197,232,73,92,128,180,210,103,48,221,102,234,141,242,81,131,12,50,48,113,3,18,39,136,176,197,22,68,
19,45,136,8,39,68,32,118,66,144,138,64,170,9,35,68,41,229,219,239,36,156,48,192,33,81,86,153,42,49,69,172,11,47,199,240,100,253,104,199,72,40,38,145,129,59,140,135,8,125,244,2,91,48,12,68,200,230,31,224,
188,185,242,110,206,194,44,115,228,49,191,28,255,252,173,204,31,255,31,10,76,192,5,23,158,219,160,135,9,135,74,130,0,47,80,186,11,16,1,8,56,80,90,26,210,133,190,116,165,174,58,49,72,32,19,152,128,4,218,
141,238,118,163,67,20,66,18,34,187,8,84,255,173,36,3,27,129,30,70,224,169,237,184,2,121,173,176,90,195,22,179,24,134,61,140,63,212,160,129,28,170,183,166,139,17,3,88,173,48,1,145,60,240,7,15,28,192,14,
113,224,88,4,252,208,135,24,144,32,40,76,97,147,55,46,116,172,100,113,69,29,21,120,67,19,38,240,7,42,186,34,102,245,139,220,75,168,200,69,252,61,192,103,254,3,160,140,4,88,186,36,180,2,129,49,72,131,17,
72,96,132,6,246,32,117,103,168,78,2,137,48,187,36,156,96,116,25,212,96,66,18,82,182,239,65,137,120,122,208,67,148,74,85,42,49,57,198,49,109,155,207,72,254,144,176,41,189,130,61,174,146,88,53,100,133,141,
86,12,168,39,194,106,133,30,236,144,130,3,240,48,21,118,72,144,18,200,6,62,35,142,239,15,229,11,134,201,44,132,50,171,172,47,29,205,122,217,4,102,57,203,42,218,210,138,93,76,5,23,105,89,203,9,140,97,12,
106,152,128,2,30,16,0,124,77,161,32,165,35,215,31,46,96,64,32,252,65,129,103,160,66,42,206,128,50,116,253,33,130,255,56,248,3,17,136,192,204,36,12,192,155,101,68,67,66,208,32,187,62,142,74,0,128,20,211,
118,6,86,72,20,178,141,109,142,108,219,34,95,1,182,253,244,71,134,213,187,30,105,110,248,25,28,166,98,147,169,249,131,39,15,208,195,84,76,225,127,126,48,101,83,130,242,20,86,218,134,113,28,242,16,228,
116,249,138,46,214,178,138,23,189,165,45,255,240,203,28,228,128,7,10,216,196,7,242,21,29,2,50,243,2,127,0,2,16,16,144,6,53,254,193,13,48,237,70,84,140,176,192,5,34,0,8,68,88,102,25,47,128,132,11,236,113,
38,55,200,13,192,4,102,2,19,4,82,15,175,40,164,58,95,129,194,68,58,38,97,108,195,67,11,100,34,201,188,21,8,123,253,36,153,1,56,233,10,31,182,226,14,250,48,1,47,130,37,12,0,97,136,93,89,49,71,58,234,0,
57,42,142,1,151,209,176,98,21,199,176,81,186,218,149,163,106,200,129,3,64,154,30,78,1,112,0,61,61,233,5,84,138,192,165,173,49,42,108,100,218,25,90,138,128,84,56,211,153,204,220,255,230,54,209,64,206,60,
100,161,22,103,107,140,9,8,246,135,17,150,101,96,6,122,231,43,166,52,159,168,106,230,158,148,180,164,107,70,227,207,181,216,129,160,46,81,142,9,248,32,7,36,150,111,39,164,153,10,13,118,139,155,136,50,
107,174,116,229,232,47,135,75,220,84,12,215,21,118,189,171,71,115,224,132,194,184,224,3,134,58,65,96,153,169,210,108,182,52,21,110,96,101,234,254,144,134,155,18,214,153,41,253,238,54,101,144,135,242,94,
86,84,109,219,44,82,255,247,146,66,186,87,68,13,192,67,4,32,86,213,217,168,54,21,252,220,155,78,72,64,7,59,124,50,26,252,184,131,30,104,123,202,166,52,20,125,24,90,215,56,22,146,142,4,112,225,125,209,
248,37,44,36,252,138,28,252,97,185,22,118,130,19,212,0,210,14,140,116,10,114,73,2,17,152,112,64,4,178,84,141,84,128,169,108,72,144,186,5,58,54,167,40,29,108,74,29,139,3,34,192,46,15,178,123,193,247,132,
23,47,163,142,176,96,239,64,103,43,64,75,200,82,137,150,158,120,56,173,77,255,122,177,183,235,225,247,24,199,32,217,53,251,11,219,104,28,65,83,122,200,131,28,24,80,96,167,64,101,137,114,216,173,177,200,
225,219,10,112,65,1,116,197,176,154,45,188,102,54,95,88,205,174,112,66,42,10,83,76,16,203,72,155,73,195,193,137,141,208,70,55,224,150,10,108,108,105,119,31,27,94,194,166,34,155,50,176,113,30,110,96,78,
205,118,54,144,158,2,109,82,215,25,228,247,210,115,170,16,219,18,147,3,68,154,39,187,66,39,121,216,129,127,95,98,135,15,100,153,42,11,21,22,155,192,33,230,118,153,67,30,96,224,130,47,95,194,102,143,182,
194,194,209,192,245,31,52,172,97,14,219,225,185,6,0,96,4,110,144,192,4,10,154,105,36,240,51,76,169,192,103,154,118,183,177,142,157,241,43,108,60,226,27,68,0,15,74,224,113,81,3,201,89,73,187,130,157,169,
240,182,60,15,217,84,72,66,140,26,188,240,133,170,1,84,140,157,168,169,15,41,240,0,11,92,242,1,15,140,52,124,18,90,66,42,241,139,224,48,239,22,89,11,233,132,153,21,224,255,128,93,243,250,224,169,208,240,
174,173,36,103,94,19,192,1,231,169,243,22,148,128,4,38,20,187,58,75,163,102,42,0,205,70,103,63,59,218,40,117,44,78,199,139,99,36,68,160,118,127,184,93,81,15,186,217,33,79,58,26,40,28,88,83,25,57,213,205,
236,34,181,230,91,109,187,103,149,10,60,196,123,14,47,177,247,29,240,16,3,96,37,35,99,195,66,159,191,195,161,35,181,218,192,193,4,103,174,194,97,193,235,133,43,188,234,114,190,240,59,212,0,131,95,143,
212,107,17,96,194,93,164,97,163,86,200,65,14,70,96,54,119,109,10,109,105,131,23,207,177,155,93,4,148,144,109,149,31,148,96,232,108,57,165,149,250,242,117,18,217,239,52,239,195,185,39,9,32,220,234,188,
211,72,55,193,107,129,238,18,123,127,64,4,124,240,103,198,26,170,219,86,239,40,45,177,86,128,26,22,158,129,12,164,194,243,25,200,186,193,69,255,10,172,99,157,0,25,128,248,175,253,42,130,138,243,225,46,
118,185,102,12,206,112,118,35,160,221,227,127,64,192,77,93,178,77,6,255,153,252,4,163,180,93,81,9,54,115,19,26,95,220,198,55,144,129,10,9,54,170,162,155,146,152,124,69,187,129,242,85,121,151,197,3,154,
50,129,12,102,115,116,109,12,203,27,75,135,168,0,84,144,128,7,16,188,0,158,143,70,231,211,79,245,133,167,66,234,89,231,117,6,8,176,145,20,4,224,14,32,105,1,6,54,224,186,215,219,72,134,181,199,52,130,230,
98,185,39,109,57,181,77,98,39,119,192,103,59,61,166,124,46,193,78,122,7,11,146,246,54,131,164,18,243,181,26,19,35,26,20,210,110,79,246,20,191,160,19,32,144,2,115,32,111,90,240,18,41,96,106,90,134,13,167,
244,101,169,224,111,198,178,1,91,193,29,229,119,126,236,167,126,235,71,0,46,65,122,163,231,4,157,87,2,60,240,107,127,96,0,2,0,54,251,119,21,176,163,11,175,199,11,112,84,83,215,37,114,120,134,103,178,67,
59,217,102,59,91,224,99,246,193,78,124,23,100,223,22,37,34,144,100,153,118,115,169,38,32,79,86,61,221,39,13,241,246,95,239,224,1,41,0,86,55,96,255,29,5,86,50,22,242,7,75,151,35,24,192,33,39,226,2,10,192,
3,232,215,121,173,224,3,176,176,126,235,151,131,238,71,0,56,136,122,37,208,117,46,112,4,54,32,0,66,144,27,102,130,11,71,88,19,124,96,35,214,49,71,146,37,89,174,16,133,11,40,60,85,168,7,83,48,2,137,212,
94,5,179,89,17,24,13,146,198,124,53,135,90,134,243,37,170,149,61,218,67,54,163,86,22,231,241,1,119,16,1,11,128,43,58,129,56,80,81,121,236,130,1,45,192,16,0,224,2,118,192,3,37,144,1,126,216,135,127,224,
135,199,248,135,132,136,131,5,160,112,5,144,112,78,240,140,205,72,0,135,104,24,30,193,136,47,128,11,58,34,53,130,247,141,223,56,78,116,65,78,35,54,65,36,166,137,83,216,99,129,4,138,200,247,10,155,5,110,
237,104,138,98,210,124,252,49,49,40,99,61,172,200,55,52,164,19,109,227,1,104,216,120,46,64,7,126,192,7,215,80,134,230,3,102,98,118,29,11,209,16,125,1,3,112,32,6,203,8,11,62,16,145,173,224,121,78,64,255,
0,83,151,112,169,80,0,209,216,145,4,0,7,28,1,0,197,211,136,184,144,10,88,65,14,239,226,65,17,160,10,190,131,4,227,52,65,57,226,123,116,247,53,241,226,137,119,151,133,242,56,138,120,247,114,239,4,37,142,
1,73,171,17,67,178,178,129,157,214,55,31,40,33,122,0,116,140,87,22,1,41,0,41,136,116,7,169,116,140,34,126,79,247,0,127,1,1,19,153,10,101,144,10,17,57,145,53,248,121,157,151,145,26,73,0,209,88,2,127,0,
7,37,0,146,216,184,136,13,96,11,215,129,29,112,249,58,118,3,59,116,9,59,173,176,1,76,48,56,59,166,142,7,69,66,241,40,129,223,246,142,227,70,72,242,36,115,39,33,95,153,182,100,158,49,12,98,168,143,31,8,
130,119,176,148,101,65,7,65,114,7,125,176,0,136,147,13,177,145,56,13,148,144,11,160,35,191,216,16,194,200,3,149,144,149,127,80,6,91,249,10,19,233,135,95,249,7,128,232,154,127,64,136,114,86,0,37,0,24,106,
128,150,14,160,0,233,145,141,36,25,151,175,243,58,176,99,255,55,194,105,146,27,48,59,85,163,109,158,104,0,158,245,151,91,136,119,5,35,105,122,87,100,57,52,48,245,20,148,213,96,95,158,54,134,173,37,13,
116,32,153,47,49,154,48,208,0,53,128,56,153,84,50,95,150,96,189,24,154,14,17,6,14,9,145,102,224,10,169,233,10,171,201,149,171,233,3,98,32,6,55,216,140,127,64,155,106,160,6,14,240,159,0,202,87,31,0,0,122,
224,7,66,48,29,198,242,7,147,168,160,217,1,123,177,135,6,180,67,147,219,134,53,35,4,110,189,129,124,239,245,119,66,102,66,164,32,85,50,113,29,215,169,129,2,178,79,211,231,55,17,16,139,246,49,3,65,48,7,
46,32,4,176,129,43,79,54,27,46,120,29,27,194,29,1,160,8,112,64,0,62,96,6,102,80,5,85,112,154,241,153,140,202,24,13,202,88,131,56,88,2,253,233,10,142,192,3,14,176,2,170,151,136,255,115,160,18,99,29,12,
58,137,11,74,71,118,36,5,194,135,53,157,5,138,87,40,110,22,10,11,165,24,110,39,241,48,184,176,11,255,81,86,173,232,255,26,173,181,73,4,133,2,246,161,5,152,96,7,54,64,73,228,25,12,2,34,163,255,102,146,
190,200,29,193,152,135,88,201,163,62,234,163,168,73,6,100,32,164,175,128,154,201,184,168,124,232,140,5,208,159,5,199,3,27,161,0,127,176,8,127,192,3,78,154,9,30,224,97,0,96,2,82,202,40,103,240,122,179,
163,4,184,115,5,245,114,47,249,242,99,201,215,94,128,201,42,148,145,138,66,217,105,249,168,143,239,112,7,7,48,7,112,106,31,85,160,5,32,233,2,227,137,91,19,242,37,215,144,96,199,66,135,122,225,16,56,10,
145,85,208,163,131,234,163,134,58,168,127,192,163,60,42,164,19,137,159,243,71,150,37,128,164,5,119,169,60,224,10,97,208,8,139,128,169,128,145,150,16,144,150,144,176,2,229,81,30,254,232,1,71,146,41,180,
152,170,195,55,166,174,234,170,3,227,161,24,152,110,133,87,148,55,148,106,173,192,7,59,48,7,222,89,22,62,176,6,93,231,162,158,65,12,202,208,80,222,144,10,255,70,149,229,7,3,43,128,149,127,208,172,206,
106,255,168,100,240,163,19,235,163,212,234,3,124,184,145,72,234,159,5,55,1,48,224,173,97,240,29,29,208,1,97,96,7,224,42,169,76,250,7,77,186,2,224,1,3,236,154,2,238,138,47,202,249,99,45,55,124,15,56,105,
204,233,18,101,250,2,54,23,3,178,162,175,135,231,138,175,112,162,111,106,37,62,48,167,41,210,129,201,80,12,246,213,176,116,168,158,163,185,6,98,16,5,20,251,7,22,123,168,169,240,163,245,201,154,233,71,
155,218,58,103,10,64,169,173,16,6,252,195,63,15,240,0,46,224,2,108,11,17,39,107,7,118,96,5,118,208,1,66,162,41,54,219,151,57,91,84,61,187,170,240,56,175,29,154,138,54,129,19,178,170,175,161,17,13,63,112,
0,85,102,37,98,0,146,41,128,153,215,192,79,80,59,27,13,235,176,138,176,2,58,170,3,63,58,168,91,107,177,239,89,159,141,186,159,252,185,173,60,32,87,248,163,0,105,171,182,107,11,6,96,112,34,63,3,52,199,
1,58,83,224,63,83,240,104,235,248,7,160,8,138,130,201,42,97,218,183,98,194,255,30,209,195,127,248,42,171,53,212,125,252,40,7,31,112,0,243,230,170,62,0,146,118,96,176,7,155,19,147,219,153,225,192,167,84,
59,140,16,144,1,81,160,3,25,171,181,22,27,173,239,41,164,25,128,159,177,41,186,31,251,159,165,219,173,173,128,186,251,227,10,95,196,186,96,16,0,127,16,0,196,177,41,71,0,187,6,208,45,246,96,15,174,48,2,
254,251,191,87,168,133,246,17,18,53,119,23,215,217,55,176,16,101,78,33,101,104,176,3,138,59,175,85,128,9,30,16,0,38,131,49,211,235,111,197,138,27,13,32,0,200,234,144,4,16,5,81,32,168,155,123,168,211,218,
135,160,215,10,98,235,159,173,48,178,175,192,63,169,160,186,173,208,186,41,242,39,0,208,9,169,160,191,157,165,34,90,216,183,241,24,166,239,240,179,95,56,188,46,145,79,126,195,0,69,16,74,139,43,34,58,32,
6,4,219,1,11,0,21,182,18,163,215,96,27,139,211,46,28,242,116,120,184,2,5,224,3,219,91,5,135,138,177,210,74,173,159,71,136,230,187,121,46,59,1,165,235,255,10,103,22,13,172,155,10,77,235,198,175,208,45,
247,96,15,94,218,191,106,51,175,174,74,192,145,36,148,7,75,171,95,66,125,176,64,5,119,32,1,73,172,180,112,176,2,118,192,54,61,16,189,124,19,135,140,146,160,53,176,16,28,124,163,30,220,197,26,155,10,102,
112,140,28,155,126,56,88,198,42,140,198,194,212,194,238,11,11,173,235,10,53,220,10,64,195,191,101,145,187,120,236,179,68,38,115,192,155,152,248,42,125,171,197,19,252,232,10,13,252,192,120,28,193,112,160,
134,202,80,12,170,100,50,223,80,21,41,3,53,117,216,35,9,128,135,122,232,121,151,76,194,199,216,177,40,204,159,42,124,169,161,236,18,157,227,170,114,124,15,46,81,199,173,108,72,148,22,110,3,163,199,55,
0,162,86,229,18,128,124,203,137,251,192,203,203,42,102,0,5,43,218,1,89,176,4,40,179,115,171,148,96,225,128,35,127,80,163,79,135,163,31,172,3,220,123,168,243,73,145,158,188,173,173,96,186,102,219,205,167,
220,205,221,236,72,89,72,192,182,64,19,96,88,120,9,76,255,125,183,28,3,8,162,203,120,92,6,65,128,200,0,32,207,124,67,158,223,199,40,247,108,189,192,8,6,97,64,140,98,240,7,33,156,201,166,9,205,3,93,69,
234,123,208,48,243,7,46,252,7,215,236,10,111,140,202,174,160,202,243,202,205,244,138,133,74,245,41,193,91,3,120,19,189,8,204,55,182,156,111,169,112,2,255,80,200,86,98,1,127,192,171,155,186,46,72,109,73,
109,130,50,85,145,193,250,156,204,10,16,177,95,123,140,247,57,190,40,156,173,155,247,159,115,134,63,169,128,186,52,221,10,55,93,202,57,125,195,9,173,195,239,192,211,253,187,29,197,163,208,236,20,79,144,
49,85,183,240,124,172,120,212,63,1,163,194,16,2,59,64,200,10,253,7,80,48,167,6,219,110,191,188,98,212,91,172,249,188,21,105,65,201,15,89,159,169,32,6,109,240,7,41,189,145,252,89,208,105,125,69,214,252,
14,196,1,52,55,140,28,219,12,11,117,220,35,184,123,216,201,23,203,184,64,212,132,123,95,218,169,153,175,128,6,69,81,101,202,203,188,81,13,5,4,219,255,57,145,251,25,32,29,210,97,102,44,197,218,116,37,157,
172,174,0,5,155,61,214,31,251,10,165,107,182,102,155,182,101,241,214,54,220,211,62,205,218,46,167,199,245,88,21,67,251,14,24,115,203,169,192,0,63,208,212,4,181,206,120,204,219,43,208,1,47,0,2,221,13,220,
23,188,91,213,123,29,58,114,197,201,60,140,37,176,220,247,121,159,157,252,7,217,250,7,155,167,190,159,29,218,164,252,18,167,76,215,59,189,202,216,29,206,192,219,215,55,215,199,179,202,138,135,243,10,50,
16,2,26,32,1,95,192,2,176,245,5,173,108,6,147,0,3,9,32,207,140,108,12,81,113,118,240,141,207,189,37,131,15,224,1,14,144,189,154,173,223,205,152,194,169,176,173,34,107,186,209,176,182,169,80,202,162,29,
215,47,97,224,167,173,208,6,154,37,52,161,152,28,152,175,192,204,175,169,224,5,82,176,3,26,142,221,169,160,5,107,128,200,241,204,111,163,65,44,240,237,10,26,220,16,148,188,226,213,232,140,100,237,10,52,
174,198,175,96,227,127,128,227,189,225,17,217,252,255,10,60,46,129,215,109,37,239,84,79,178,76,184,196,187,98,198,192,20,174,192,7,132,13,13,76,62,177,98,0,113,96,16,12,148,84,228,195,130,50,115,120,151,
11,217,193,14,80,0,133,72,150,41,12,169,146,74,205,189,33,230,189,209,180,58,62,215,34,226,191,172,34,90,164,0,73,12,46,180,70,205,111,81,1,204,111,216,115,28,192,1,120,158,231,75,235,0,118,16,207,235,
178,79,193,124,213,89,141,207,47,232,139,192,72,201,106,64,198,101,137,164,46,235,232,179,68,169,7,93,211,3,30,195,176,240,51,166,44,215,176,240,17,87,88,60,107,254,128,133,228,218,91,98,13,140,60,134,
115,46,101,253,122,5,255,144,231,80,173,231,32,217,231,191,93,203,156,137,62,98,22,3,199,98,204,234,105,210,48,160,6,28,9,227,145,10,202,44,220,205,212,45,236,59,61,233,169,128,15,149,190,218,34,178,236,
102,170,105,179,193,129,250,120,67,116,142,13,76,77,234,78,221,202,24,123,234,30,16,229,139,89,67,178,241,216,224,142,86,91,129,187,124,113,210,230,222,255,223,254,205,81,103,29,13,210,221,202,238,78,
218,121,110,66,0,204,170,204,142,166,173,152,192,24,83,158,169,32,3,227,109,20,27,47,159,135,104,7,3,130,56,191,176,55,133,103,207,214,113,44,39,62,2,124,193,5,127,1,169,33,219,232,105,108,208,237,203,
214,109,253,10,212,237,57,176,0,239,184,155,230,47,7,166,124,7,90,39,1,148,85,37,27,81,44,242,81,22,222,252,104,196,69,177,228,41,223,181,141,11,3,34,209,13,186,8,101,164,65,44,75,23,223,11,246,139,42,
0,0,153,87,112,193,149,238,167,43,202,46,129,227,172,219,238,238,158,245,96,170,133,226,156,10,92,226,110,126,236,152,161,126,23,33,64,7,93,144,32,88,159,242,75,139,200,114,56,32,216,176,129,22,66,226,
187,5,238,197,74,14,234,57,131,19,176,87,142,94,169,104,221,10,190,254,194,243,58,244,46,177,191,189,145,236,166,184,36,123,124,192,216,211,10,249,142,176,252,90,62,114,80,4,20,64,234,26,30,240,172,29,
193,16,48,7,246,48,207,79,177,192,252,214,38,254,118,255,19,215,68,243,235,83,149,249,147,198,186,36,211,239,144,249,100,126,227,156,127,195,101,33,239,72,223,10,160,207,84,218,221,31,156,30,245,166,223,
138,210,222,10,182,93,20,89,31,13,81,0,1,32,57,158,145,187,19,11,236,101,9,95,27,99,159,50,11,22,131,228,23,107,220,58,227,189,241,243,157,3,191,56,29,13,41,98,244,209,208,252,206,143,187,125,43,206,16,
13,8,52,127,131,131,32,32,132,136,36,134,32,108,75,127,142,144,131,124,122,20,28,26,136,152,153,154,155,155,62,37,112,29,127,138,108,136,75,142,164,32,36,127,61,114,114,52,49,49,130,11,179,27,24,47,13,
2,42,9,96,92,10,127,10,190,153,92,195,132,196,156,199,0,131,201,199,132,54,127,206,199,35,131,38,2,156,13,66,45,125,24,127,50,11,171,133,133,135,131,36,170,139,32,166,143,145,131,114,82,28,33,59,204,241,
242,136,16,16,115,213,131,108,250,143,249,127,134,228,172,104,8,140,129,104,193,134,44,47,132,52,24,81,39,193,3,96,193,16,245,50,22,15,12,178,4,243,255,154,101,148,166,201,15,182,108,89,54,212,88,32,72,
209,161,147,227,202,153,67,71,72,93,159,43,33,56,100,156,201,201,71,21,2,112,96,108,192,68,138,31,56,81,61,88,181,18,244,135,104,141,44,219,22,218,216,213,11,211,68,102,22,9,129,137,74,83,147,13,103,210,
56,110,146,38,128,43,34,63,13,90,188,192,144,229,79,141,88,42,17,177,17,103,206,80,163,82,131,28,241,49,17,226,138,134,46,85,243,34,18,131,211,215,169,70,144,208,29,82,181,202,149,32,129,68,205,34,77,
152,11,0,152,7,92,6,17,139,140,233,129,212,63,83,17,129,73,128,49,211,50,68,201,62,15,186,58,104,132,105,173,199,4,84,195,231,81,44,89,179,49,122,152,252,131,202,92,184,69,111,227,242,115,36,71,4,76,10,
122,131,19,242,1,1,142,13,54,170,150,52,18,23,119,48,137,160,174,138,10,28,52,203,160,45,33,141,153,2,251,85,76,147,101,203,241,48,138,30,205,137,52,51,212,127,86,11,184,38,182,79,72,62,177,77,138,235,
233,47,149,124,70,129,25,56,34,255,68,165,207,15,152,50,9,23,92,21,196,173,128,129,35,110,177,148,78,125,131,4,132,216,97,222,120,243,7,66,10,169,96,67,29,143,73,22,25,101,146,129,247,135,135,85,141,103,
213,121,94,253,225,21,54,218,100,33,3,31,37,45,162,137,125,245,185,165,201,41,124,20,17,66,8,2,230,168,67,6,16,192,32,135,40,180,169,147,15,115,127,12,133,216,32,211,253,177,192,81,182,224,162,130,99,
224,113,72,136,135,153,205,35,90,50,208,108,130,21,39,92,161,247,7,138,24,228,209,141,28,132,25,18,14,33,204,153,243,86,96,44,197,112,194,141,127,0,151,163,112,58,136,177,134,29,164,148,163,201,90,136,
56,152,228,145,52,48,121,75,118,188,76,249,0,136,22,81,149,89,103,241,124,150,229,76,94,169,246,7,123,41,174,72,131,108,63,249,147,73,91,65,14,194,192,110,235,68,160,7,156,151,204,41,156,15,98,192,161,
135,35,36,40,136,9,145,126,18,117,228,32,130,98,247,228,46,135,130,136,25,102,138,90,196,104,60,54,0,240,104,38,54,120,73,72,86,255,2,248,241,101,54,97,214,80,164,40,163,152,73,36,144,106,230,246,199,
167,136,200,225,95,8,114,114,16,160,169,121,85,33,70,113,125,136,163,224,126,224,216,23,43,146,135,17,85,75,66,184,4,187,75,84,153,37,138,72,0,84,121,166,111,60,198,102,66,41,89,150,146,121,31,167,64,
222,182,15,38,44,145,128,70,17,87,200,9,174,142,158,192,193,71,15,142,124,90,49,79,254,0,100,164,172,15,10,100,208,31,240,142,32,239,161,131,228,75,200,175,154,136,24,236,176,243,140,160,26,123,99,189,
119,105,140,40,161,201,150,166,139,236,135,238,31,94,16,146,135,31,119,224,56,4,34,50,57,252,112,70,117,18,176,130,34,112,109,42,206,115,27,3,202,241,31,239,42,36,128,188,37,99,130,17,202,136,36,32,162,
136,196,62,179,9,204,100,109,192,98,15,154,18,130,10,125,48,66,171,169,181,131,244,156,15,31,91,220,97,244,32,223,30,93,149,14,196,217,33,135,41,216,94,187,68,224,105,3,213,67,199,210,9,130,182,116,53,
236,244,66,11,184,136,12,0,103,255,127,80,174,245,32,140,2,160,178,121,91,153,134,73,178,216,188,160,77,30,103,65,203,52,159,50,58,237,150,62,174,42,200,135,20,119,112,112,55,34,165,234,61,83,6,124,209,
65,144,79,59,35,98,38,212,134,197,194,174,28,65,53,120,184,117,240,94,61,57,103,204,115,125,178,215,160,253,161,57,216,207,92,133,149,52,100,103,81,3,31,171,144,83,166,180,55,167,98,51,35,128,85,172,31,
38,49,72,193,237,236,182,231,72,156,1,4,209,231,41,39,207,177,114,198,116,175,36,254,160,116,75,46,102,117,176,153,96,158,244,166,135,9,103,24,112,88,215,243,28,232,92,243,158,238,145,163,102,156,170,
25,57,12,230,19,194,237,199,77,239,96,95,251,4,164,131,122,24,96,19,159,10,220,62,6,99,191,251,21,5,22,69,121,22,218,14,135,164,198,33,165,5,10,17,89,176,66,67,192,77,44,67,115,97,187,138,203,200,38,18,
146,164,100,62,168,136,145,166,8,99,179,124,176,132,112,132,192,96,222,54,248,48,2,105,193,4,164,24,28,34,24,128,196,68,4,229,255,12,38,20,158,32,90,17,20,217,212,175,139,52,232,95,147,186,34,175,230,
73,111,52,214,227,92,1,211,19,58,178,140,228,82,222,99,26,110,108,131,38,211,221,134,124,230,155,81,250,12,0,15,38,182,207,12,62,80,213,238,144,72,69,108,33,136,16,87,196,226,43,98,241,32,46,46,110,113,
71,154,133,11,175,19,57,204,53,239,146,94,75,198,122,132,16,179,30,42,14,90,39,145,22,205,254,81,38,80,86,11,112,215,154,17,31,68,64,7,111,249,145,137,98,88,129,9,126,164,137,16,170,109,17,0,57,195,143,
14,147,184,86,16,111,21,93,12,230,165,30,84,157,26,184,16,41,182,120,129,50,149,137,129,178,25,115,22,136,9,230,4,195,39,68,58,22,238,142,7,75,229,158,100,224,7,58,236,96,137,175,108,226,31,224,176,2,
61,196,128,136,153,160,98,75,80,1,144,88,205,234,71,197,91,225,55,16,121,169,195,5,243,158,29,139,102,60,227,56,27,6,213,241,54,113,4,210,3,113,3,24,193,85,241,17,121,40,2,29,194,25,206,32,252,193,3,122,
255,200,3,97,208,101,75,253,64,162,39,237,108,5,146,214,81,36,71,202,163,139,136,4,230,61,249,25,208,107,190,200,76,38,125,21,115,76,81,177,222,17,162,15,31,100,168,76,255,96,135,59,228,97,70,132,64,34,
59,235,247,35,90,18,66,32,26,237,211,226,72,26,208,162,14,12,124,214,60,83,186,38,56,142,166,142,143,31,234,84,39,38,210,144,132,63,128,115,166,76,132,131,29,34,32,63,221,12,238,171,106,43,68,70,51,97,
152,160,246,41,37,190,11,37,74,167,117,82,231,16,149,169,153,240,30,110,142,184,137,37,112,239,15,125,196,42,67,103,0,1,15,40,11,132,7,5,71,70,205,138,36,95,114,20,152,104,37,196,64,255,169,88,146,198,
21,174,155,240,94,140,10,170,205,77,224,192,4,26,212,171,31,83,165,7,25,84,118,138,199,112,78,23,125,73,75,26,248,116,158,198,91,156,29,77,135,206,68,68,22,178,175,117,145,130,206,183,9,52,224,85,179,
184,133,131,24,22,186,32,76,132,80,167,0,253,34,218,78,171,209,71,170,22,177,137,224,167,255,60,148,219,216,180,38,200,183,184,141,238,60,236,81,13,18,116,21,180,165,24,33,41,131,73,75,71,62,18,19,197,
115,155,83,51,114,207,239,22,17,110,210,77,111,70,198,69,7,62,208,178,119,191,141,11,75,157,235,189,240,178,98,29,134,53,172,72,133,122,92,77,128,180,177,146,157,235,206,176,21,88,245,26,152,16,80,16,
195,28,254,122,142,90,150,98,63,65,28,98,125,255,75,214,211,158,21,72,199,45,175,23,153,122,159,78,181,228,179,7,14,241,38,234,145,130,62,124,248,90,129,179,101,75,148,67,155,241,241,51,188,21,38,45,97,
247,11,82,47,154,178,62,172,115,85,33,69,204,99,102,136,97,6,6,240,108,139,161,91,89,150,26,249,96,46,122,49,140,49,97,88,144,18,230,173,46,234,137,206,204,87,224,30,91,153,16,226,250,131,8,60,139,142,
1,163,56,112,243,245,170,62,214,98,14,162,106,152,185,119,36,223,152,211,49,219,42,95,249,205,244,72,65,4,238,10,226,84,198,23,97,71,30,243,152,219,194,231,62,175,110,204,70,14,52,224,164,255,154,78,56,
27,26,17,102,248,3,111,173,235,210,41,22,50,176,129,166,141,158,39,77,105,61,239,134,37,20,29,156,155,15,205,105,76,164,0,15,168,141,199,163,57,33,232,82,155,186,209,251,185,115,167,87,157,145,187,82,
246,24,191,221,180,124,93,5,151,71,143,122,126,172,206,117,94,186,156,17,89,63,24,112,154,6,235,76,174,171,235,98,215,145,216,57,141,170,167,108,205,108,2,71,117,199,216,69,152,177,167,45,143,115,150,
79,72,50,109,52,181,183,77,8,135,34,194,189,248,153,109,251,170,40,55,110,155,155,25,121,128,133,28,212,156,99,65,131,74,219,39,62,183,188,103,50,3,68,152,224,15,38,142,65,43,72,64,38,42,240,100,31,164,
8,56,63,122,38,55,130,147,34,13,131,72,130,31,66,192,219,121,59,156,25,122,192,67,31,100,176,34,248,236,219,151,252,212,135,27,244,65,5,18,24,1,17,160,70,132,4,14,240,240,146,107,162,222,132,32,121,156,
254,160,135,34,72,65,226,38,70,131,204,95,26,129,19,136,192,228,56,7,215,28,54,97,5,11,59,252,129,228,42,87,121,206,229,17,8,0,33,249,4,5,0,0,127,0,44,10,0,20,0,206,0,192,0,0,7,255,128,127,130,131,132,
133,134,135,136,137,138,139,140,141,133,70,136,124,142,147,148,149,150,151,152,153,154,155,140,64,130,104,55,127,121,162,121,53,127,114,36,75,170,75,108,127,173,156,176,177,178,179,180,151,68,158,56,56,
105,103,105,49,190,191,124,53,124,193,50,53,27,197,11,127,169,75,32,171,181,207,208,209,210,132,68,131,56,127,103,84,127,110,127,94,221,131,75,137,204,32,228,61,52,196,50,52,52,114,211,237,238,239,147,
68,213,130,103,70,84,110,220,222,141,225,225,135,171,170,191,98,208,232,1,175,160,65,105,64,174,253,73,147,230,15,136,130,204,204,197,224,195,238,160,197,139,148,60,37,252,163,235,158,62,65,206,96,245,
99,180,68,142,73,140,40,83,22,170,166,107,27,184,63,35,39,49,152,73,147,38,39,18,191,254,16,84,201,19,154,39,107,11,141,184,241,22,51,17,131,63,53,107,34,178,121,52,233,81,69,69,123,156,137,209,179,234,
51,32,64,24,122,100,212,212,38,161,127,96,195,130,45,164,180,17,137,83,103,42,90,93,91,73,94,194,52,246,255,4,121,251,104,200,43,76,177,228,242,234,205,203,134,13,95,16,108,198,14,154,217,8,196,78,108,
108,19,47,194,218,177,27,221,67,94,85,249,221,11,130,132,229,203,152,51,107,38,177,87,48,225,69,225,206,8,58,172,216,42,144,11,130,176,102,181,151,239,91,93,155,255,200,41,195,172,179,135,237,219,184,
109,215,62,156,187,135,229,189,129,85,33,125,170,8,196,196,210,165,177,50,20,42,220,232,209,85,178,105,19,50,73,253,20,245,235,235,76,210,32,180,189,34,238,203,121,87,217,245,199,78,18,242,139,8,12,97,
69,144,102,235,82,216,170,200,157,85,116,189,55,110,57,183,79,254,81,199,127,187,32,118,248,249,102,153,67,75,36,37,142,28,146,152,119,222,69,235,193,69,133,23,69,17,242,148,112,15,85,38,8,9,215,121,151,
91,102,137,92,150,159,28,217,9,210,159,127,131,156,213,140,42,227,21,82,210,31,104,72,162,208,130,239,40,215,158,23,143,73,248,92,72,202,160,37,218,110,182,109,198,215,100,148,229,229,144,101,184,137,
8,226,145,235,16,242,219,255,137,101,25,66,194,25,50,224,64,21,140,211,92,192,152,131,53,10,2,159,67,178,233,39,71,90,186,97,6,28,96,15,17,242,10,34,122,113,118,225,89,182,105,103,157,126,202,156,24,206,
103,134,76,69,165,52,168,201,168,205,123,55,10,57,90,128,223,13,72,142,95,103,214,197,15,63,48,37,2,100,153,68,222,102,157,58,250,113,198,36,157,132,184,193,7,17,50,220,73,75,158,236,9,197,39,116,163,
141,166,219,133,46,249,9,25,162,224,196,228,76,132,102,230,69,27,65,35,250,39,105,129,148,18,98,68,166,154,114,130,218,5,183,224,96,15,132,144,61,231,208,32,189,205,54,31,95,95,173,202,192,161,253,68,
136,170,112,168,22,50,217,108,182,197,186,157,160,40,18,71,8,21,49,188,152,235,37,121,174,70,99,132,132,177,66,72,110,198,114,89,102,153,90,74,152,104,180,226,188,52,210,63,134,232,165,204,109,253,193,
10,78,173,131,64,242,109,37,63,93,249,96,150,51,73,54,172,168,2,10,50,40,151,242,106,217,143,182,150,176,10,18,142,132,60,68,66,255,181,252,17,203,25,173,16,39,250,135,130,255,46,178,107,167,220,144,251,
92,95,178,213,70,170,194,125,213,53,220,195,15,119,213,212,112,79,49,213,228,196,169,54,91,212,72,230,208,176,64,50,34,78,204,239,199,33,171,135,0,16,8,236,250,135,158,133,14,182,108,43,178,21,41,40,187,
19,6,199,12,176,72,101,237,177,195,203,102,43,108,185,206,212,204,175,206,21,91,220,179,58,131,248,7,66,138,14,129,92,116,106,23,164,215,160,61,172,158,124,110,128,75,178,251,154,129,90,222,72,147,185,
23,247,168,19,129,5,115,60,24,51,119,73,220,220,32,102,75,228,11,164,61,4,54,54,208,69,31,253,71,210,75,35,13,151,107,54,194,212,202,197,187,45,233,138,33,175,120,85,38,97,126,49,35,105,101,61,168,190,
49,51,128,218,214,140,67,94,57,37,78,81,149,5,30,171,101,108,220,188,223,219,26,93,192,105,123,156,59,29,206,153,61,206,231,185,34,203,50,220,117,120,51,129,176,64,22,24,244,241,194,11,126,8,32,128,31,
66,180,224,125,247,45,188,240,71,255,22,53,208,80,112,222,103,117,133,200,161,196,89,172,19,136,35,178,211,123,199,106,125,139,121,106,236,105,243,216,223,175,176,155,176,112,103,34,76,205,82,213,181,
136,108,160,15,45,208,30,247,94,208,7,12,96,160,6,197,168,65,13,126,38,65,99,100,225,5,45,16,130,16,182,39,4,157,208,68,78,125,91,159,34,122,0,63,129,132,136,86,134,32,77,200,136,208,17,55,20,229,70,135,
184,204,82,12,1,150,202,72,15,3,66,240,131,31,90,208,135,44,108,96,63,104,3,98,16,69,164,142,158,253,108,1,198,16,194,8,70,208,130,44,136,69,107,34,236,135,95,238,5,191,140,17,110,104,33,195,10,31,54,
183,191,230,25,75,64,121,123,197,72,102,6,19,114,172,130,32,24,216,94,11,48,176,1,83,108,7,104,18,20,132,41,76,129,136,254,252,206,55,227,75,160,16,178,208,131,243,45,171,99,47,209,154,95,46,102,146,128,
172,99,99,227,233,129,219,96,164,197,246,52,237,101,49,116,5,226,12,36,54,2,157,104,1,56,20,194,11,76,65,185,63,196,145,255,142,133,0,229,34,146,177,157,237,232,6,3,34,104,0,6,72,80,64,20,54,11,103,205,
9,7,33,213,241,56,147,24,110,58,184,162,146,39,216,67,130,71,22,44,133,120,220,218,107,44,83,184,5,188,160,1,66,192,192,2,72,116,68,79,58,243,16,162,92,132,127,224,152,140,30,76,239,5,74,48,223,178,82,
81,184,69,12,114,150,1,161,29,191,22,153,28,94,54,173,92,200,75,222,194,200,242,156,202,20,104,9,211,11,31,249,150,57,190,78,254,225,103,247,68,68,52,19,97,69,34,142,198,63,47,16,1,6,254,86,147,86,152,
75,152,37,18,81,12,126,70,21,201,1,114,71,138,209,72,86,168,112,206,163,124,46,116,106,130,138,59,103,66,3,4,246,80,16,201,248,97,50,64,214,204,125,90,130,68,191,75,27,198,178,160,202,181,173,13,146,30,
195,93,142,36,178,0,129,136,179,86,228,172,202,149,140,16,152,206,149,232,59,54,42,75,124,10,68,130,44,200,243,153,248,28,4,29,133,225,73,36,38,195,158,154,72,234,61,145,40,162,5,180,96,4,89,255,168,9,
10,179,214,181,118,157,203,103,52,88,168,28,154,81,171,41,69,180,83,61,117,218,232,136,148,46,192,120,181,96,128,121,103,15,54,144,193,27,32,113,3,33,253,33,72,7,193,135,100,204,209,169,178,240,207,136,
204,113,161,135,40,113,3,209,219,166,138,40,166,19,254,44,128,15,13,189,165,43,98,144,75,157,106,142,167,49,161,147,102,240,1,152,71,50,35,56,56,193,224,38,67,250,7,189,218,147,169,74,117,42,39,9,97,82,
70,12,145,181,229,115,166,133,132,208,0,86,174,141,140,236,4,73,109,194,186,204,117,144,85,91,143,236,201,91,168,144,89,226,104,102,16,45,243,234,56,154,65,131,27,52,64,124,18,220,128,105,5,113,140,169,
26,194,60,170,197,4,74,131,150,182,126,2,205,54,105,204,42,3,110,251,153,9,29,130,132,32,242,197,88,111,230,45,158,104,142,162,62,157,205,154,206,210,10,139,190,108,168,225,64,230,31,112,117,140,56,50,
162,175,19,108,170,4,161,234,218,189,86,245,136,79,189,39,74,213,177,0,195,182,224,182,226,73,28,255,66,29,114,182,154,110,103,171,138,233,212,254,18,170,164,131,21,74,117,5,234,1,6,214,232,76,99,100,
10,87,173,77,45,107,239,153,226,73,208,211,90,117,156,32,13,88,154,213,249,65,209,97,133,48,71,33,151,217,3,242,78,71,167,112,193,90,8,169,181,147,1,49,14,108,171,48,102,248,218,104,138,19,183,177,141,
141,160,106,45,24,172,96,70,184,81,29,53,24,113,225,202,213,33,124,9,132,29,24,22,68,26,136,96,37,43,253,161,204,167,121,7,2,58,66,23,109,177,9,140,236,28,71,124,254,144,65,242,109,128,124,251,221,111,
147,229,56,74,22,15,226,169,45,86,4,208,182,43,205,180,33,209,168,5,99,155,199,160,118,10,176,162,34,69,233,73,73,71,206,89,162,249,200,144,44,114,94,2,13,54,32,132,62,120,242,135,89,160,174,12,142,49,
106,189,90,25,169,2,222,132,207,20,44,216,58,122,146,68,36,168,193,8,94,170,20,109,157,108,138,188,181,169,100,151,134,145,183,244,146,44,28,94,211,193,192,17,215,37,244,224,6,201,244,100,22,200,255,23,
77,19,255,48,208,148,155,160,180,243,169,137,237,18,122,197,34,34,44,65,70,176,128,241,206,9,98,196,105,69,207,250,58,144,93,19,194,204,49,250,15,59,155,247,102,21,37,43,62,51,190,222,2,54,128,129,80,
139,50,151,163,86,106,37,2,172,106,4,55,211,213,114,252,97,172,247,179,199,63,166,168,64,10,123,223,58,146,180,107,4,204,195,32,144,149,228,96,42,125,27,35,235,13,58,32,160,1,14,251,16,82,255,14,226,135,
253,149,110,160,247,10,104,160,17,152,18,165,28,209,239,174,237,207,26,88,83,16,155,28,175,239,204,164,240,176,94,216,46,13,41,8,106,136,144,6,57,20,234,51,220,104,212,124,62,28,31,6,208,0,131,62,100,
163,34,32,248,204,166,59,130,223,212,190,136,58,244,202,195,174,253,17,216,140,163,78,88,169,162,104,120,36,65,6,13,41,238,54,220,112,92,170,129,101,1,214,195,64,105,215,158,136,81,23,195,147,149,109,
196,95,163,238,136,82,26,130,229,86,246,217,2,230,250,130,129,114,204,139,80,100,69,155,182,14,19,255,187,24,225,225,238,64,3,14,136,219,57,89,194,57,225,19,75,114,31,58,125,103,182,47,194,196,78,191,
188,28,1,75,119,69,224,61,19,177,45,223,140,133,32,3,6,176,146,38,189,19,230,43,210,75,207,91,122,3,53,238,72,66,30,210,240,115,139,90,76,58,199,67,10,51,88,65,130,235,169,125,124,132,8,245,33,220,110,
106,71,116,114,238,40,79,41,44,80,186,76,62,188,32,171,191,189,250,214,196,77,75,95,68,127,16,63,153,198,9,56,162,60,175,222,158,54,105,197,175,28,178,144,204,202,255,190,180,197,31,196,137,45,177,0,28,
192,177,16,39,135,7,150,205,83,3,1,244,49,194,133,255,10,27,48,196,31,129,72,54,13,176,39,13,178,119,6,109,102,92,199,5,51,128,49,94,121,224,7,14,52,62,212,163,118,210,149,126,195,71,9,199,215,84,149,
96,119,180,144,114,76,37,0,239,36,125,19,71,44,213,82,83,110,80,22,218,48,0,210,32,5,45,146,91,35,113,49,70,214,83,5,98,70,32,144,7,45,32,2,197,215,128,31,39,129,121,86,255,90,16,52,114,209,150,9,159,
231,131,68,195,96,146,32,3,35,64,80,224,166,91,176,226,11,103,224,99,130,96,4,23,96,130,181,32,5,130,64,17,153,229,36,255,3,22,220,196,7,34,32,2,133,176,108,127,112,126,212,149,126,153,178,103,197,16,
119,134,48,71,158,132,134,23,168,124,170,6,74,52,32,65,96,85,3,23,148,104,148,98,94,7,70,21,76,56,13,82,144,4,49,208,125,55,214,40,190,209,50,255,144,10,61,64,91,55,16,10,132,80,111,132,32,93,194,151,
8,106,184,79,200,71,37,111,72,3,107,116,51,183,229,49,142,179,80,52,115,110,80,88,11,104,48,86,241,53,32,130,211,23,24,103,108,168,36,62,72,16,124,138,248,133,132,192,4,56,40,8,17,84,8,50,144,32,68,3,
50,38,213,98,63,56,101,198,240,2,125,228,99,252,240,20,101,226,88,49,208,58,94,193,13,208,144,4,124,192,120,31,184,38,201,227,6,86,179,127,169,176,1,59,244,7,72,0,134,192,215,136,165,149,5,76,64,93,137,
240,100,176,120,8,246,20,127,42,241,255,70,209,213,2,180,114,142,137,162,45,213,34,86,228,69,28,38,216,137,156,80,4,40,232,47,203,248,125,151,97,53,67,181,0,57,36,8,77,100,8,203,70,61,173,152,141,142,
104,121,102,120,134,81,23,104,185,8,11,248,148,84,133,136,88,234,51,97,186,83,83,196,72,28,123,50,11,69,240,49,202,232,125,140,34,67,208,1,90,24,208,0,45,48,8,216,152,136,216,120,103,149,135,8,80,198,
8,226,88,104,210,128,68,146,64,74,27,176,29,116,213,71,6,183,140,253,64,83,235,101,23,240,184,9,91,128,130,180,103,35,69,65,27,24,39,27,222,131,65,172,104,141,131,80,111,214,248,138,166,240,108,41,214,
73,21,120,17,180,184,121,171,21,147,116,245,78,24,70,63,96,85,120,116,18,128,176,16,1,50,80,145,237,130,56,126,40,73,208,65,2,52,160,65,226,19,146,116,246,7,226,83,8,138,8,134,38,185,8,41,73,9,35,135,
129,180,0,85,33,53,87,206,212,2,14,137,142,249,135,137,62,131,135,93,167,9,23,137,140,181,183,130,232,133,71,241,113,255,34,111,136,76,12,68,103,33,233,64,96,24,106,94,120,8,17,40,93,250,228,113,136,144,
96,44,201,93,156,144,96,216,181,121,247,132,87,212,85,3,66,240,130,117,104,94,52,69,3,191,53,8,57,7,11,40,216,125,232,148,35,38,49,32,164,184,54,61,86,136,221,227,150,109,169,118,54,248,150,73,57,146,
139,40,144,152,89,8,166,117,68,1,86,65,105,147,121,116,228,31,35,103,144,127,118,144,83,88,157,68,227,73,125,208,7,55,243,25,225,96,24,96,213,99,148,2,4,219,103,152,127,0,150,180,9,120,103,113,155,174,
16,28,174,242,145,26,36,153,110,249,150,192,233,143,106,71,156,220,8,124,200,169,111,211,169,153,111,164,156,248,68,3,160,19,71,190,241,134,162,39,11,57,21,74,212,67,147,91,69,28,35,33,7,189,197,149,79,
17,105,156,128,6,49,240,115,174,144,59,247,130,71,236,105,108,12,176,0,218,243,7,29,228,155,108,73,8,125,215,133,113,137,9,17,180,0,110,23,112,197,192,7,50,64,61,62,84,65,15,26,82,124,176,19,111,200,255,
126,126,70,71,43,169,84,119,150,88,128,244,10,18,177,14,40,244,20,73,192,9,82,32,3,126,104,123,3,66,36,244,53,84,169,128,1,42,160,65,33,170,8,37,138,159,116,137,126,40,169,126,53,208,45,50,32,3,195,120,
6,24,67,140,241,241,114,114,20,14,233,48,137,20,216,121,206,116,160,207,100,12,24,224,82,181,83,53,222,105,66,215,231,5,104,176,9,69,128,140,179,51,100,238,3,126,248,229,161,82,90,8,226,115,61,141,16,
106,72,201,8,166,70,89,81,50,21,76,16,1,91,96,2,83,240,1,46,48,169,1,48,2,126,208,7,52,73,2,94,122,12,104,179,163,127,70,57,9,230,169,57,248,100,53,192,55,12,138,56,32,242,51,100,165,53,18,122,9,242,136,
6,177,217,55,49,1,126,185,185,4,189,167,2,32,154,171,132,16,146,131,154,136,54,24,124,14,88,156,88,42,139,110,23,37,148,133,4,143,58,5,130,224,7,127,160,67,130,0,0,146,218,1,46,224,7,103,48,94,62,68,160,
61,0,117,157,169,166,167,6,74,209,85,12,89,176,255,54,183,132,78,15,65,83,224,249,25,70,176,147,148,112,145,68,64,143,195,113,161,78,210,89,205,64,14,11,208,0,2,64,91,13,32,8,249,58,8,222,67,103,194,41,
8,135,42,146,196,137,141,93,218,165,210,21,3,55,32,2,63,240,3,38,240,168,34,176,5,91,184,133,217,67,91,127,48,2,6,240,1,41,208,1,76,48,94,45,32,3,250,162,146,209,169,111,115,180,103,198,208,70,89,192,
7,166,138,92,163,113,6,96,149,135,155,160,167,238,50,58,32,168,38,147,49,25,27,32,0,127,208,0,249,170,179,252,24,146,222,83,148,110,57,162,148,25,176,150,25,124,122,85,176,93,202,4,11,219,176,34,160,4,
69,122,136,135,216,7,17,224,61,34,224,7,38,96,2,122,160,7,83,48,5,41,240,1,136,53,126,19,132,96,132,240,84,161,218,173,16,68,106,200,25,129,226,85,107,79,241,57,36,196,31,175,57,8,234,234,8,69,64,161,
22,42,8,159,131,33,26,138,50,156,209,3,246,138,175,131,48,165,132,160,73,255,58,8,85,138,168,127,112,3,76,128,255,3,76,192,66,76,160,176,12,91,158,104,32,3,121,112,3,17,112,2,82,176,133,153,43,2,150,155,
157,34,128,181,6,16,169,46,160,7,104,233,7,124,112,14,51,102,77,106,184,163,104,136,43,249,166,126,251,101,103,89,208,165,49,144,104,133,247,82,130,201,99,243,3,72,147,112,145,82,144,7,245,19,67,44,136,
183,100,194,25,53,240,183,251,42,8,129,74,162,240,89,184,95,136,1,136,24,124,194,167,141,76,208,184,55,144,11,82,240,3,91,240,3,82,112,3,148,27,1,38,16,2,31,176,3,41,32,1,18,96,5,18,96,7,127,224,1,86,
240,1,38,160,4,72,160,4,35,240,1,127,96,2,71,240,1,55,16,14,72,16,3,53,0,2,120,69,65,58,42,8,215,112,13,35,139,134,77,118,12,8,236,100,78,118,12,161,96,117,237,82,53,68,228,91,94,145,174,152,240,117,180,
105,133,9,71,40,121,113,76,58,139,179,131,219,65,130,27,184,189,154,148,212,216,133,112,169,184,72,128,3,73,176,176,218,123,3,68,112,3,82,56,190,127,144,2,116,176,255,3,54,156,2,229,155,190,86,48,7,43,
128,5,205,122,3,91,240,7,46,48,5,38,112,7,72,96,24,31,227,114,211,67,182,246,132,3,75,5,119,121,70,124,140,32,3,125,240,151,205,67,39,205,209,51,96,134,69,189,11,179,19,87,20,21,49,40,131,100,24,246,170,
179,42,96,175,135,240,158,133,240,179,133,155,138,191,42,156,106,135,4,55,144,6,91,16,2,63,240,7,221,75,4,92,184,3,18,240,7,31,64,7,130,208,199,132,224,1,43,192,2,30,240,7,43,176,6,86,32,2,45,160,4,126,
160,172,83,112,4,120,96,171,45,192,191,46,103,159,90,186,95,6,171,126,235,71,151,135,168,123,97,6,18,226,6,63,92,137,125,174,10,171,1,212,49,36,180,19,123,17,107,42,32,0,246,122,198,57,59,184,139,48,194,
112,73,153,131,112,136,213,75,4,82,176,189,83,112,2,50,128,4,33,64,1,20,192,1,20,240,7,28,240,7,54,172,1,57,236,1,30,96,200,88,16,4,107,48,3,16,176,2,31,112,2,31,176,5,39,112,4,122,96,2,30,96,255,0,12,
64,21,53,149,79,222,234,95,174,75,144,140,224,138,32,87,185,89,149,45,8,55,33,17,1,57,35,168,45,3,80,164,148,128,130,193,11,140,204,216,35,123,65,16,54,240,202,56,139,198,1,141,8,33,28,159,132,106,8,13,
40,62,138,251,194,63,112,5,63,144,4,56,80,4,41,240,7,20,240,1,196,252,7,26,160,204,130,16,7,7,112,0,127,192,2,40,16,210,51,240,7,107,176,6,90,208,6,34,240,4,107,176,5,73,112,5,6,224,1,88,240,4,12,32,3,
55,176,80,99,88,65,99,120,206,87,154,153,154,185,118,199,192,4,72,208,129,207,193,157,126,161,99,103,32,26,2,36,8,55,48,183,138,32,5,68,112,158,10,99,143,121,67,14,52,208,0,42,48,2,2,240,202,131,96,213,
250,74,208,134,187,171,134,112,61,132,106,189,217,251,208,104,80,4,20,48,204,54,188,3,196,156,204,127,96,190,127,224,209,44,240,7,40,32,205,35,13,5,90,16,4,109,96,5,72,32,1,43,176,5,120,240,1,80,224,3,
16,48,5,75,224,138,56,192,255,100,248,86,144,199,185,141,127,176,141,144,173,87,213,187,1,64,253,50,3,116,23,83,100,18,71,61,145,79,17,10,33,64,183,121,202,7,231,201,104,195,22,36,11,240,202,168,45,8,
89,61,203,129,155,198,83,58,168,176,45,156,125,167,184,185,208,210,87,128,4,103,61,204,199,124,204,59,48,8,26,192,1,18,192,209,31,141,2,127,48,3,40,144,215,65,240,7,120,13,5,80,96,0,63,96,5,41,96,2,87,
176,6,22,96,1,16,160,4,124,224,189,56,80,176,108,87,144,32,55,172,203,198,4,218,56,222,251,117,136,63,196,4,186,156,88,119,241,21,84,180,217,24,70,4,159,237,8,28,208,5,82,80,161,164,51,44,160,163,48,61,
102,24,134,193,82,169,237,193,89,237,193,132,144,188,133,16,194,255,42,90,126,201,184,240,253,3,39,112,214,110,205,214,199,140,204,191,13,220,116,61,215,131,16,4,16,160,5,26,174,220,204,93,6,30,176,5,
90,96,1,41,160,7,86,80,221,100,176,2,148,189,191,76,80,12,71,155,159,218,72,217,223,141,126,174,184,255,141,223,237,216,80,123,136,70,248,174,186,69,72,59,66,39,56,112,199,139,80,4,201,204,214,124,248,
72,105,21,56,4,81,33,23,99,24,47,160,2,78,142,171,127,0,229,30,76,224,81,78,229,173,45,168,154,4,62,141,138,4,104,157,167,82,112,5,23,125,209,200,156,204,7,16,7,197,141,2,88,48,210,134,252,7,26,174,225,
204,13,5,197,61,3,116,0,1,22,176,6,41,16,0,109,80,5,100,32,226,56,160,4,43,46,93,93,154,159,148,173,141,131,224,216,34,41,8,150,89,189,138,158,5,55,192,232,125,240,15,229,194,160,25,122,6,233,67,28,49,
96,0,79,224,8,33,112,5,159,104,161,71,174,50,74,206,25,245,250,228,135,128,179,184,106,213,168,222,213,5,94,208,111,41,4,135,216,147,105,125,2,39,80,204,200,252,7,33,192,1,110,29,220,113,16,7,134,188,
2,198,237,235,51,16,4,109,254,7,109,0,231,16,48,210,107,240,7,213,13,1,31,96,5,58,80,221,22,112,2,72,0,204,213,27,232,161,22,129,136,158,237,86,42,222,134,254,255,216,220,110,227,135,24,1,103,128,34,8,
23,120,162,2,166,129,41,8,119,128,235,140,240,3,69,144,167,163,221,10,201,53,42,20,102,188,89,237,228,137,32,224,57,123,198,92,109,229,106,252,193,161,32,2,33,16,2,69,112,1,87,112,0,95,64,209,23,205,1,
25,109,230,31,61,205,26,46,236,90,0,1,130,48,236,16,0,1,65,80,6,85,80,5,202,254,236,118,240,1,4,96,1,109,96,1,30,128,3,34,160,232,61,61,62,144,237,237,143,61,222,220,78,232,74,173,242,133,112,136,24,16,
1,40,219,129,52,228,182,96,202,77,196,113,7,79,224,214,137,16,196,44,130,164,238,242,10,140,54,42,187,105,25,89,240,228,117,192,8,169,158,234,172,77,203,173,173,73,224,187,5,201,156,4,73,240,5,8,175,1,
109,189,3,26,96,195,188,142,5,98,111,5,116,240,4,43,80,6,213,44,6,25,222,6,106,143,225,116,110,6,22,64,6,58,144,1,58,80,0,29,16,6,81,96,226,17,0,191,43,142,222,174,72,222,225,93,189,209,219,138,216,8,
243,185,124,255,3,217,89,122,182,171,42,142,183,243,54,38,8,87,144,2,64,111,8,120,112,145,215,64,4,121,160,55,192,136,50,42,51,26,25,55,32,0,224,228,117,96,3,140,48,229,81,62,224,179,172,95,186,10,162,
161,38,221,118,140,6,33,112,0,93,160,245,67,192,1,67,80,204,59,16,7,30,240,4,71,112,199,240,139,205,38,13,1,109,112,241,130,80,210,127,96,6,28,111,1,58,160,3,81,48,247,48,144,0,212,221,6,100,128,5,125,
222,247,72,224,138,14,24,106,80,27,243,51,255,201,55,158,184,219,31,181,121,0,152,95,44,75,79,130,238,94,177,5,18,176,3,67,208,8,93,122,183,50,139,94,21,193,25,0,154,150,117,160,2,117,112,255,184,138,
239,165,15,8,127,13,130,42,13,133,130,134,127,138,13,45,125,127,122,119,127,82,73,95,149,95,7,93,138,127,33,28,30,79,127,76,55,55,17,74,74,38,30,81,81,112,16,127,43,43,112,127,62,22,85,127,22,58,183,183,
10,15,97,169,100,100,76,17,55,161,55,127,89,55,24,127,199,154,203,200,127,255,24,24,125,207,199,207,206,24,55,125,142,216,72,55,36,12,75,222,224,154,75,75,127,36,36,103,103,61,127,223,127,12,127,73,113,
26,28,203,244,55,56,103,105,50,124,244,238,235,108,108,127,228,208,24,248,135,6,9,16,52,122,208,104,144,160,142,67,21,154,32,210,155,24,81,145,0,66,134,18,45,122,33,226,207,7,58,33,208,20,65,113,160,100,
37,13,138,56,132,8,177,133,137,140,8,91,90,200,52,97,167,77,155,53,107,254,120,128,177,130,128,14,11,22,204,212,178,117,235,15,12,0,5,44,68,41,48,5,201,182,80,138,172,53,147,122,172,170,51,101,127,144,
64,115,132,36,171,83,69,78,35,244,161,193,0,68,56,119,222,150,0,44,215,35,93,183,126,201,60,104,160,64,145,94,12,125,203,224,254,89,251,167,135,156,191,36,122,32,236,209,67,133,67,135,203,84,72,252,179,
184,238,197,63,2,84,92,28,148,232,34,6,17,122,232,80,184,130,230,143,134,146,7,190,196,163,64,33,196,15,41,104,110,40,177,130,165,133,144,22,2,214,180,129,224,193,131,255,21,43,30,254,84,153,197,27,168,
142,12,183,0,0,72,160,0,76,24,5,76,146,16,209,154,69,154,181,100,200,154,117,229,10,22,201,11,235,17,174,119,213,244,162,197,11,12,49,24,128,99,3,119,220,90,191,114,72,172,67,251,39,134,149,20,59,234,
46,187,27,67,254,121,244,114,64,8,38,76,195,48,98,138,18,65,212,152,124,144,89,36,153,0,35,32,115,7,29,127,20,129,6,39,44,160,64,210,23,242,132,80,132,114,104,252,240,68,27,22,140,32,132,0,10,100,32,11,
4,41,116,128,219,31,81,204,82,133,25,22,12,117,75,1,138,169,0,134,10,9,184,144,156,12,78,97,240,66,86,94,57,165,29,143,214,129,69,79,4,45,96,247,71,4,89,201,244,130,12,226,177,179,140,121,229,252,149,
222,122,237,180,151,130,4,41,120,54,17,30,201,200,112,215,2,121,45,195,23,126,36,164,55,80,13,135,213,33,159,128,1,10,72,160,34,18,141,32,64,31,31,164,64,199,7,82,156,176,131,4,40,204,64,146,4,18,204,
147,4,14,56,156,240,4,22,190,132,255,209,128,13,81,232,144,162,15,46,164,128,219,10,28,86,97,169,5,178,88,64,0,1,138,54,144,136,10,0,40,81,196,13,214,117,135,76,4,168,34,249,194,142,138,188,144,93,171,
217,33,217,42,118,69,186,42,83,11,55,164,69,142,94,228,176,17,24,96,235,245,67,66,10,118,100,137,18,61,74,40,146,7,31,124,212,167,137,94,108,128,160,8,153,233,36,148,69,2,21,212,81,65,5,138,252,55,145,
155,224,42,198,216,184,141,73,214,2,0,116,68,34,210,158,51,248,121,0,160,20,156,0,4,14,68,152,144,2,22,64,77,208,128,0,184,96,234,66,7,38,98,1,193,110,151,2,149,65,24,140,9,161,176,100,42,140,48,69,8,
74,32,113,43,171,164,188,57,36,119,71,106,114,107,35,105,145,87,165,34,189,254,42,71,15,36,124,211,15,8,116,120,128,165,4,117,201,144,71,30,94,62,219,79,175,210,250,53,144,57,129,17,150,133,182,219,114,
171,201,97,22,143,75,46,99,110,46,34,196,8,31,220,97,64,30,87,28,192,66,16,36,149,36,193,15,68,208,255,75,68,4,34,28,129,5,1,54,188,208,64,1,184,232,112,91,7,41,192,0,129,25,187,253,100,112,2,140,232,
184,163,0,112,155,64,129,8,125,188,246,154,34,165,4,29,244,173,66,188,144,22,8,78,174,99,158,57,127,145,108,178,34,12,164,140,165,124,124,136,146,71,120,136,43,194,134,90,209,42,34,16,13,229,228,220,3,
6,60,251,188,140,154,105,166,249,135,154,22,187,41,68,3,0,36,253,7,26,119,68,232,167,29,118,28,64,65,18,124,224,32,3,14,127,224,112,131,8,13,96,240,161,2,97,195,0,67,24,29,152,189,155,111,141,22,208,245,
170,171,106,34,128,9,79,152,80,183,107,127,200,84,138,18,45,40,146,253,198,220,203,36,31,223,47,152,247,207,147,33,107,174,158,120,154,124,160,50,203,117,241,33,86,30,114,32,142,254,228,127,72,171,200,
64,152,143,156,16,230,60,239,177,135,222,221,10,29,208,14,195,173,10,0,0,12,13,24,65,2,238,48,5,19,200,32,4,44,56,192,28,230,0,40,9,20,129,89,105,136,193,25,100,240,7,25,108,255,160,24,127,16,66,29,128,
227,40,163,132,1,55,112,16,131,25,116,224,131,12,148,160,0,48,16,192,51,116,228,187,65,252,97,10,18,208,67,31,24,97,195,63,228,13,128,33,188,213,50,94,35,19,186,77,238,136,228,27,95,206,166,132,62,69,
124,128,5,18,176,195,68,166,35,3,60,180,64,6,234,96,207,94,212,50,173,203,13,132,100,251,123,129,182,246,80,1,255,253,161,103,0,36,29,61,254,83,7,4,254,161,3,31,208,131,9,242,240,129,57,28,192,14,44,176,
131,4,118,208,7,42,120,233,12,110,144,1,58,254,176,128,230,248,142,7,47,250,23,192,58,48,135,85,184,2,14,88,224,65,7,122,183,1,67,158,238,5,66,176,151,14,27,112,58,33,252,161,35,34,232,8,16,53,230,189,
32,186,6,3,102,9,156,56,246,146,57,191,144,128,60,112,185,3,5,115,67,145,206,4,3,126,104,209,203,94,106,134,191,190,232,175,7,98,44,163,25,207,232,57,98,162,177,128,138,248,223,155,192,48,163,63,60,224,
3,2,240,131,12,12,240,174,61,193,171,143,255,105,72,195,32,207,16,3,48,101,161,6,223,177,1,15,20,224,2,23,36,192,6,71,184,131,21,38,184,2,24,236,196,10,1,104,64,33,107,144,133,29,173,170,5,122,176,131,
30,90,192,73,78,126,50,148,10,243,100,8,5,58,74,133,241,179,5,147,251,134,147,198,193,80,182,140,172,100,226,233,71,235,162,88,151,8,228,193,4,55,200,67,55,218,209,68,128,84,174,32,4,113,101,66,196,232,
191,55,188,225,127,254,75,169,38,182,69,143,158,185,244,165,5,172,192,3,84,96,3,24,124,210,15,121,192,225,149,246,184,3,186,80,193,8,64,237,75,65,192,68,200,26,108,224,5,114,178,65,2,0,224,48,3,164,192,
54,182,177,66,7,2,96,128,22,108,96,3,244,180,103,119,244,224,129,125,34,194,134,161,228,221,68,2,74,214,16,154,117,172,175,97,4,224,200,67,14,201,173,5,32,230,99,135,68,231,16,187,186,224,225,6,83,232,
3,46,57,170,137,241,217,143,6,68,245,139,66,104,240,130,50,190,161,9,77,120,195,31,76,186,140,148,154,241,177,142,85,255,41,74,183,181,7,46,112,193,6,0,224,193,8,68,224,7,52,72,97,143,28,80,73,105,254,
0,84,160,226,108,168,11,0,108,22,54,240,154,17,0,192,6,138,128,222,30,159,144,130,20,60,193,0,91,184,193,2,106,96,212,63,48,239,5,87,152,131,87,61,117,17,206,126,242,77,158,76,174,89,201,170,176,129,170,
85,45,227,160,71,91,125,69,24,146,241,85,17,178,180,3,45,41,18,1,63,180,128,15,152,203,165,91,63,10,88,48,41,132,4,11,0,211,30,14,139,88,197,46,150,189,201,68,233,48,21,209,132,198,166,244,164,123,72,
172,2,212,4,131,4,112,246,6,104,240,0,5,52,160,129,33,80,224,7,104,48,66,26,140,64,5,55,184,65,61,10,89,64,96,118,251,130,186,61,79,8,74,56,193,17,66,251,4,13,212,246,3,24,141,65,12,140,154,133,62,48,
79,150,38,128,141,0,246,213,0,63,252,193,15,61,164,8,101,16,113,186,69,204,216,83,66,240,238,90,213,162,43,134,170,5,103,230,248,152,19,233,186,93,122,224,193,15,122,240,3,120,255,197,219,171,93,222,47,
189,125,217,31,13,132,144,95,196,214,247,189,203,48,41,99,181,204,101,77,112,89,203,127,104,130,2,38,144,128,63,56,64,1,47,48,1,18,242,176,153,16,92,225,7,69,24,0,17,16,144,77,35,60,56,32,229,248,131,
27,122,224,134,5,120,80,6,24,208,10,19,136,176,133,16,148,230,208,20,48,1,19,68,236,193,230,84,184,5,116,152,67,8,225,182,175,23,47,35,198,139,80,4,40,21,33,132,142,148,53,160,45,110,193,142,27,218,87,
184,2,89,149,117,196,227,31,238,120,199,56,104,2,15,119,192,41,31,250,209,81,127,68,57,181,52,16,136,66,128,89,129,38,76,224,215,19,168,239,149,189,236,222,197,42,162,216,20,17,118,152,255,0,6,46,184,
48,11,126,208,43,76,6,48,128,11,36,97,0,154,192,1,131,141,112,134,132,232,185,61,36,96,52,14,252,76,168,66,253,96,37,166,41,194,15,78,160,237,187,84,242,59,24,104,0,30,253,224,7,4,237,139,222,244,182,
177,167,26,32,214,125,107,90,16,103,189,180,167,116,252,255,143,232,74,174,175,153,11,178,144,255,64,135,21,104,247,0,154,136,131,20,185,212,130,41,224,148,44,124,109,50,64,244,211,203,93,15,68,140,190,
6,118,152,173,172,108,101,47,123,216,194,38,185,176,131,61,1,5,56,224,55,35,224,3,18,100,32,131,19,72,225,15,216,30,192,9,228,252,135,52,80,161,76,234,104,135,122,212,243,7,102,157,33,119,76,192,1,18,
182,240,131,115,23,225,233,73,208,230,93,242,112,131,239,32,53,143,120,128,155,69,94,236,226,124,63,38,211,131,112,113,166,69,41,240,129,139,58,90,62,246,177,18,79,171,202,134,75,81,39,7,200,13,251,12,
112,135,15,124,32,15,24,191,238,17,151,0,2,18,132,116,176,169,5,121,200,53,49,108,250,158,252,202,86,38,252,201,21,1,236,49,76,192,9,183,88,3,3,240,32,3,34,72,129,218,152,199,249,5,128,96,4,47,184,161,
126,129,113,3,32,143,94,187,220,253,129,8,73,127,7,181,159,46,5,7,113,115,234,209,121,129,1,88,64,135,62,152,160,222,244,200,247,214,233,129,233,125,255,251,155,50,102,7,65,193,167,235,209,127,152,131,
100,234,57,156,34,82,48,131,183,43,34,238,233,171,83,10,150,197,81,94,241,69,32,68,77,47,96,49,176,7,96,79,96,217,19,24,131,225,39,50,236,49,152,252,251,232,255,67,248,199,240,194,91,88,96,9,168,210,29,
230,49,127,129,11,224,128,10,94,240,60,8,246,191,142,30,240,1,144,165,165,8,8,240,7,23,128,115,152,87,4,82,64,4,49,64,3,189,245,12,125,128,7,247,34,9,127,96,2,95,87,23,98,167,105,131,80,129,150,198,111,
0,199,111,34,48,2,50,128,51,222,64,62,138,112,124,56,163,74,118,48,7,44,64,32,116,80,91,203,66,107,35,232,15,112,37,16,221,148,90,233,85,72,96,32,114,142,247,125,234,231,125,62,200,120,191,182,12,232,
151,126,99,48,6,106,112,132,238,135,7,76,176,132,76,112,1,243,87,109,5,200,96,138,176,127,251,199,0,36,176,15,10,182,96,8,176,133,138,80,127,245,71,109,104,0,94,187,85,3,190,133,1,121,160,19,86,112,92,
183,71,32,249,230,255,7,91,96,105,65,131,111,126,96,2,53,64,133,186,100,112,38,104,63,112,33,7,30,160,130,242,113,4,196,146,2,122,37,94,146,67,57,81,82,94,67,5,88,53,80,1,235,39,126,242,17,132,244,0,137,
203,32,126,69,88,132,127,144,3,57,0,54,44,50,7,75,32,2,56,208,132,78,232,133,23,64,4,12,246,83,252,183,127,75,112,133,154,192,133,64,240,7,64,80,128,5,72,128,85,195,77,36,230,59,125,128,6,6,48,7,31,176,
5,115,24,77,35,80,23,107,24,91,138,32,135,48,6,112,185,71,111,112,19,3,128,179,140,32,67,106,64,38,124,122,193,7,115,128,2,69,70,15,31,0,59,130,152,7,114,213,15,71,20,45,101,210,77,251,208,3,55,136,38,
141,152,3,127,80,137,232,168,6,150,136,142,149,120,142,231,200,142,203,96,142,127,0,28,64,17,3,45,224,18,173,40,138,68,0,4,248,231,5,245,83,63,124,199,119,49,64,4,4,9,139,4,40,138,138,208,138,247,48,98,
27,0,13,21,6,129,185,177,5,38,112,123,207,67,17,38,240,255,98,23,73,17,248,6,135,203,128,111,38,32,2,52,48,57,204,40,56,92,84,130,68,23,57,138,208,7,19,180,130,242,225,1,197,66,121,50,51,133,78,246,141,
124,96,94,227,168,126,99,144,3,57,73,32,106,240,142,142,232,142,20,241,147,152,88,0,68,201,66,22,144,2,75,176,5,132,2,4,68,48,138,251,168,109,248,231,6,210,2,56,10,117,6,244,2,4,173,216,133,4,56,17,218,
196,7,239,214,7,215,48,123,115,51,135,150,150,145,244,112,145,98,103,150,91,7,55,108,121,140,245,214,2,7,129,118,246,83,124,154,112,90,210,210,68,120,48,141,146,86,23,116,128,5,86,96,7,210,244,49,35,56,
151,135,88,147,54,120,131,56,137,137,230,168,6,138,217,152,138,128,137,151,8,64,230,56,148,5,176,66,179,112,6,214,96,53,4,57,47,62,231,121,84,80,130,62,102,4,56,128,149,89,57,128,89,41,139,64,144,77,119,
145,5,245,244,28,146,242,3,34,48,145,21,248,139,203,160,150,203,80,129,46,166,129,92,87,111,125,64,133,244,115,112,227,195,255,22,214,229,49,154,160,7,19,132,2,4,130,5,196,178,52,27,21,81,255,232,100,
216,183,0,98,120,131,66,208,4,138,233,4,78,144,137,5,64,17,138,25,153,144,217,157,242,232,4,117,1,54,22,64,6,41,224,6,72,48,104,184,131,59,61,199,96,241,83,130,71,228,143,163,233,138,167,25,139,177,152,
59,105,128,3,27,192,4,198,48,10,6,96,5,44,33,145,144,65,129,95,55,2,23,57,145,26,169,9,27,105,105,27,89,111,20,216,7,124,71,149,203,32,124,107,145,51,68,167,69,119,128,2,211,152,156,79,117,7,104,176,81,
145,3,16,148,3,2,52,184,91,168,69,88,10,144,3,217,41,158,219,89,0,226,249,7,226,233,4,25,160,9,221,201,157,223,217,157,5,80,2,62,145,41,52,176,159,46,65,40,69,231,44,52,23,3,175,228,13,108,224,5,84,48,
159,88,57,128,117,97,59,160,176,159,50,64,12,180,85,4,29,97,160,22,41,140,19,56,17,23,184,123,144,225,117,207,131,81,1,25,93,80,66,15,118,217,68,127,144,2,112,176,151,242,225,255,151,118,80,123,206,226,
156,235,176,75,125,71,3,49,80,147,3,145,94,244,244,6,42,42,163,78,176,157,20,129,157,47,58,17,147,169,9,217,9,153,127,144,163,46,36,6,74,81,158,12,112,85,46,113,23,49,243,50,124,32,7,82,233,6,255,224,
6,162,9,4,76,186,149,177,168,144,64,202,132,27,32,3,74,64,7,79,128,128,206,67,32,7,170,155,10,122,170,24,105,160,244,54,2,6,96,16,128,179,14,194,183,23,193,217,23,7,113,16,66,70,2,40,16,4,44,48,7,80,64,
32,182,145,2,120,176,15,242,99,171,182,106,63,210,9,38,119,186,91,96,176,167,25,144,1,4,64,32,128,74,0,129,42,168,244,160,157,25,80,0,16,112,11,41,178,14,88,229,149,124,32,3,125,32,98,49,32,7,245,33,7,
190,114,16,159,137,3,92,40,128,166,89,128,75,72,115,162,224,50,74,240,1,183,21,74,65,115,160,8,202,134,29,89,111,200,152,100,130,49,171,245,179,113,193,137,51,251,7,75,154,32,3,43,48,3,106,90,23,88,224,
1,196,34,2,103,72,255,136,182,234,141,237,129,152,229,5,38,99,160,3,50,42,173,62,224,3,154,48,163,244,176,41,155,130,157,242,49,168,135,186,157,25,208,40,4,0,20,45,192,0,171,133,57,96,210,2,24,208,44,
204,162,140,56,99,4,127,64,103,91,184,133,164,185,12,52,23,10,73,135,7,234,179,139,34,240,134,90,39,31,20,72,129,5,226,175,195,216,117,95,218,155,168,88,37,34,202,23,8,139,146,138,128,7,105,106,49,88,
0,3,218,165,7,121,96,22,112,122,177,125,71,131,206,178,177,66,48,1,30,123,11,42,180,12,51,42,6,243,88,23,128,26,163,5,96,142,47,154,137,125,10,28,98,16,173,25,96,11,27,176,4,223,52,134,53,208,7,126,32,
4,240,35,124,10,81,167,68,32,3,116,54,154,77,121,1,104,64,144,183,19,165,46,1,12,116,240,30,38,160,4,93,247,38,23,113,160,89,26,135,177,245,60,209,36,3,209,50,171,222,32,45,7,251,140,11,103,0,65,240,176,
107,218,135,31,208,7,241,163,176,192,121,182,128,101,172,27,139,1,77,240,27,183,0,255,5,180,80,23,209,74,17,211,106,173,68,25,143,138,32,163,115,11,7,169,144,10,25,208,7,12,192,91,53,128,1,89,160,8,89,
144,117,126,128,7,27,144,7,37,150,12,4,153,4,72,112,1,46,65,4,29,4,10,162,192,44,120,144,50,116,240,145,46,102,2,152,54,17,23,73,186,3,122,150,107,9,55,115,72,160,20,232,7,202,136,138,13,245,15,21,106,
151,85,210,15,116,16,4,127,128,156,22,99,7,48,64,7,17,0,38,0,1,23,116,41,16,69,135,107,187,85,72,9,0,121,183,224,3,101,16,172,177,160,8,26,172,8,209,42,183,37,107,188,126,170,9,44,11,11,66,65,0,5,64,0,
37,176,6,5,32,0,32,176,0,27,96,162,87,229,65,87,213,73,73,171,4,73,112,2,194,64,190,138,192,159,243,202,7,121,32,2,234,171,7,156,101,165,251,90,155,159,91,32,183,231,117,101,185,196,19,233,7,233,145,176,
209,21,45,171,107,14,119,9,23,36,96,7,176,16,52,46,96,7,60,16,67,121,192,0,10,59,130,254,139,103,210,249,100,53,176,255,91,42,48,1,192,129,193,101,240,198,138,16,178,19,209,183,51,26,5,19,1,168,219,25,
163,125,250,7,37,160,3,42,204,3,60,160,197,204,171,0,27,208,3,210,139,63,81,122,3,87,197,91,27,64,40,183,195,158,252,153,5,121,16,170,81,170,7,196,178,190,249,70,155,111,130,160,164,27,140,79,187,155,
23,72,150,45,54,2,58,246,74,109,37,14,88,27,24,175,52,17,121,48,7,43,160,55,116,0,3,125,123,7,24,96,133,50,57,94,36,42,16,204,162,8,55,184,0,47,224,108,81,144,1,85,0,5,112,172,9,34,75,15,98,208,183,30,
236,183,209,122,178,216,153,1,40,171,3,112,160,163,5,0,200,118,224,2,183,16,173,2,16,97,53,32,3,100,72,134,88,213,65,213,11,10,131,166,8,219,27,170,94,121,175,181,113,7,183,135,160,91,42,31,239,60,129,
160,155,145,169,170,8,191,152,191,35,160,7,158,148,138,83,44,62,107,23,24,113,106,166,126,176,2,6,28,52,65,176,27,4,144,0,104,97,50,107,49,14,127,117,198,132,132,167,53,192,255,5,144,215,178,150,242,198,
112,236,11,203,0,5,114,43,20,19,17,172,201,188,12,121,188,199,154,112,102,94,156,34,81,80,2,13,16,30,114,160,15,49,128,119,138,80,3,48,115,59,245,129,6,104,240,200,162,106,0,8,156,37,126,64,118,111,162,
123,154,0,186,20,161,170,126,64,202,77,43,2,36,147,176,124,81,146,9,247,158,102,177,12,116,160,161,127,48,3,65,195,33,182,224,0,52,176,43,77,198,80,15,13,209,227,168,2,106,208,178,41,98,6,25,140,209,190,
16,5,114,12,5,29,28,199,34,91,6,127,224,214,62,32,183,51,138,199,61,57,1,48,160,0,54,213,1,8,83,2,41,98,1,109,16,0,218,168,31,36,192,91,127,208,205,52,7,10,247,32,122,104,176,5,255,121,205,71,176,196,
247,44,186,244,59,74,144,241,60,126,192,13,113,201,212,183,106,130,117,97,7,126,66,213,65,3,20,190,81,203,237,208,43,228,224,208,229,64,167,187,181,15,227,248,2,10,0,54,41,178,34,101,93,6,190,224,11,85,
16,178,114,28,178,112,108,214,33,75,255,199,214,218,167,61,249,7,10,160,0,203,160,0,38,194,3,16,144,210,47,11,1,0,160,87,185,150,171,129,129,15,47,161,33,18,80,27,86,64,7,6,192,190,127,160,201,148,221,
221,191,40,39,31,41,171,20,42,38,255,11,208,123,161,23,121,208,39,5,29,218,100,112,11,10,221,3,12,213,208,106,209,119,138,192,7,210,59,142,104,82,0,141,18,5,85,224,214,111,92,219,100,96,41,183,125,204,
33,43,20,2,62,224,154,176,41,46,122,132,127,0,200,203,112,215,8,83,78,46,240,178,37,0,7,183,80,2,37,208,224,95,107,20,88,208,225,181,97,27,79,0,98,19,105,2,122,64,155,75,107,129,185,199,145,64,68,202,
8,34,61,84,72,161,111,85,197,37,67,17,69,224,39,83,13,64,1,110,11,211,10,50,70,154,80,31,69,72,246,77,134,120,186,0,13,224,0,192,193,223,43,66,214,180,77,6,186,161,34,198,172,27,7,30,11,32,140,194,68,
153,225,234,7,3,60,168,8,92,208,1,111,244,7,46,0,3,1,144,0,118,160,6,21,94,225,112,0,255,7,174,224,225,30,110,5,33,222,64,98,151,207,70,12,181,195,200,160,148,29,55,69,237,7,117,232,155,183,42,227,117,
193,1,54,62,74,190,161,3,27,80,22,130,35,124,92,173,172,246,109,223,189,156,5,92,208,199,72,142,54,110,93,219,199,115,224,34,43,224,102,32,199,114,171,224,5,16,220,195,189,12,97,192,5,8,67,60,111,20,0,
1,240,0,92,14,0,1,128,215,194,35,60,81,21,226,71,32,207,19,169,7,143,144,165,73,12,68,157,59,231,65,227,139,115,216,2,81,12,227,124,177,12,170,204,127,122,17,3,7,32,33,148,109,11,192,241,1,101,1,223,243,
125,68,252,23,63,99,200,203,120,170,2,60,144,10,58,144,228,66,161,209,147,142,34,118,204,237,184,253,7,153,174,224,37,160,6,60,208,114,196,173,9,92,48,220,231,174,8,196,243,0,97,94,102,175,101,3,242,110,
0,54,48,5,37,62,5,83,240,7,6,48,235,72,204,150,170,170,165,40,158,235,115,72,202,9,183,86,183,10,236,7,81,133,122,17,1,18,194,146,64,36,218,142,66,255,14,61,32,198,124,231,227,250,129,90,246,29,209,233,
245,2,48,80,0,36,100,6,32,95,5,190,32,178,179,160,27,199,172,8,104,13,238,9,142,194,227,174,9,89,174,9,235,254,0,127,192,5,96,160,9,46,192,108,127,16,0,31,240,7,175,254,234,60,191,239,249,14,91,220,93,
155,219,109,49,241,60,231,71,127,155,148,102,0,66,64,164,108,32,24,6,71,17,86,188,43,112,225,5,119,48,3,78,115,236,187,33,11,53,176,4,240,109,107,130,83,57,234,144,198,133,61,193,106,28,173,142,114,237,
62,128,210,127,224,209,150,34,178,222,170,8,201,28,238,36,61,1,229,190,238,194,205,5,20,241,0,50,143,243,233,67,15,6,176,239,197,249,139,176,69,15,8,82,244,221,13,64,113,35,2,2,112,3,125,135,138,227,227,
191,229,173,171,19,33,7,197,190,222,15,159,41,1,64,72,204,110,218,17,74,116,25,79,134,27,219,2,10,224,19,238,103,6,81,64,6,62,192,228,138,96,41,138,224,40,199,60,229,226,222,147,119,255,242,194,189,12,
122,79,15,101,182,255,12,187,175,8,242,14,0,185,254,201,137,111,248,98,231,165,113,211,2,53,144,171,7,143,172,5,95,23,39,128,2,44,224,240,128,94,6,188,49,51,80,18,93,125,167,30,100,216,65,53,160,136,133,
164,2,124,237,126,58,128,34,172,79,11,174,143,34,39,175,8,38,155,163,193,221,114,182,79,15,185,15,68,152,69,15,67,127,155,195,175,244,92,167,160,25,104,191,178,14,8,36,61,32,36,75,127,135,136,137,127,
36,36,32,135,12,138,28,51,44,44,127,40,138,152,153,85,155,85,22,45,12,52,127,75,75,108,127,108,165,32,132,61,11,172,53,53,135,173,47,92,25,58,181,181,81,22,127,85,186,155,127,81,152,4,4,78,78,5,106,138,
10,137,92,153,203,203,54,204,207,208,209,135,2,135,13,126,137,2,217,126,2,120,52,132,142,134,204,140,169,127,144,137,68,148,148,210,203,156,62,14,160,162,163,32,165,162,228,172,11,53,50,176,173,13,5,181,
180,185,56,113,58,228,67,76,162,96,5,136,25,227,49,225,80,67,68,200,144,29,82,166,8,12,166,4,137,255,0,172,203,100,98,35,38,63,13,254,88,107,16,242,79,182,147,126,106,244,104,4,98,212,169,151,136,24,141,
43,101,142,222,15,20,7,42,121,76,180,107,147,25,29,11,14,141,90,226,72,232,31,66,161,254,228,123,133,143,85,150,48,78,116,208,210,17,133,12,25,51,88,9,250,8,134,8,97,137,63,106,30,54,124,216,36,34,34,
138,127,30,28,178,168,40,1,70,68,26,151,141,88,70,109,132,128,142,59,19,93,179,150,168,129,128,17,35,94,168,50,68,202,20,204,67,43,103,50,48,119,200,136,4,22,57,243,42,42,211,73,7,0,6,61,134,154,50,74,
244,79,40,62,124,92,237,171,33,68,129,212,90,62,170,148,89,173,245,15,129,174,4,10,20,64,196,195,97,34,137,153,216,98,2,0,32,65,157,67,54,0,56,91,166,2,19,181,67,35,58,226,149,140,168,164,72,191,2,26,
240,89,153,138,77,56,195,49,19,147,99,124,232,4,78,157,127,32,239,132,242,7,74,101,29,127,122,196,59,122,157,168,122,26,124,254,240,161,241,138,70,83,48,25,242,235,72,255,157,200,7,249,131,8,205,150,200,
4,10,144,117,8,50,106,61,163,27,34,191,229,149,13,115,209,92,227,199,54,35,52,240,130,33,45,21,178,140,76,227,100,194,6,7,40,124,161,206,1,16,234,2,133,5,4,8,176,4,13,163,148,195,30,41,228,216,7,90,124,
127,220,179,192,6,15,100,64,64,45,89,17,4,133,22,90,24,116,72,108,127,56,80,228,128,207,160,149,200,91,205,28,18,87,38,115,61,115,92,137,127,92,19,93,54,35,248,65,221,60,167,8,117,221,34,36,28,85,20,119,
127,160,145,211,1,104,234,68,162,100,85,104,97,129,14,106,128,178,82,139,214,145,194,134,35,52,208,16,67,12,161,237,131,207,11,10,68,177,163,25,5,149,7,5,20,98,36,42,70,48,196,216,246,7,67,184,45,195,
5,69,9,46,3,64,131,209,68,41,205,148,204,9,224,71,133,118,45,64,67,35,47,209,67,207,33,28,142,201,29,21,87,160,0,30,149,135,148,241,147,14,47,152,3,73,33,165,22,165,39,159,137,220,67,131,10,5,208,18,133,
162,196,254,177,40,145,255,180,49,19,233,31,147,30,82,105,52,193,5,39,151,52,118,65,72,77,116,38,64,151,197,56,92,118,153,72,42,169,62,162,136,153,226,193,138,136,5,85,248,160,67,14,144,176,184,136,157,
135,220,25,166,158,248,244,74,31,6,9,4,19,69,126,137,26,11,1,4,94,57,224,192,4,3,255,49,65,109,208,52,43,77,92,152,62,163,41,52,15,110,116,173,73,87,126,138,193,42,68,117,75,79,152,228,132,187,152,34,
173,30,240,133,185,137,188,89,203,39,175,208,89,74,151,72,213,216,231,33,121,214,176,64,22,96,148,32,21,191,6,189,134,16,88,69,26,201,3,67,6,67,196,204,179,76,194,85,180,51,79,42,50,194,112,208,216,101,
2,167,17,78,88,165,0,34,0,208,66,158,44,117,27,19,135,50,205,147,9,185,35,147,188,203,31,22,188,153,129,19,152,189,27,78,157,119,194,188,64,124,174,212,96,159,125,11,96,16,104,48,120,227,93,192,87,198,
28,124,48,194,16,46,232,100,209,127,8,39,215,195,82,154,180,145,212,158,250,97,67,74,121,130,160,158,97,255,167,114,205,146,184,137,120,209,170,4,34,146,76,246,33,85,68,113,114,187,45,34,210,34,158,46,
135,246,202,34,247,252,161,64,222,122,31,98,164,88,203,152,197,92,111,192,53,108,238,92,39,65,99,165,54,35,200,237,110,188,222,38,146,234,152,138,36,177,3,11,18,120,142,201,155,162,27,66,2,3,45,134,243,
37,189,160,233,147,103,15,50,47,48,2,163,1,150,80,130,49,14,140,209,183,237,19,41,16,169,194,105,85,148,201,165,152,48,173,136,13,136,79,251,7,226,128,105,138,87,227,217,232,33,247,32,235,41,158,241,186,
38,20,238,120,129,2,144,89,147,243,206,101,50,141,72,142,122,48,170,147,40,96,182,39,208,44,32,6,126,170,1,176,156,160,134,98,204,198,24,65,59,216,163,0,119,160,103,84,202,45,130,43,28,238,22,136,28,165,
77,203,15,38,0,137,30,96,214,8,163,80,174,114,93,115,196,199,18,209,7,52,197,97,100,10,92,96,21,108,81,163,48,93,167,37,165,112,79,158,248,196,135,24,136,138,6,234,105,69,2,28,160,134,241,169,161,255,
124,179,67,88,109,30,82,66,69,60,107,29,73,203,212,253,162,1,181,103,196,16,48,13,48,129,9,48,48,31,18,212,201,37,135,57,10,170,58,84,14,115,120,225,15,105,224,0,154,190,16,135,63,132,141,133,22,240,65,
217,58,240,7,57,196,35,99,69,9,71,15,228,160,167,25,213,40,79,121,98,133,13,156,192,16,39,16,108,12,128,3,26,52,190,248,197,63,36,32,133,137,208,29,38,0,51,70,136,173,35,27,214,208,195,8,250,176,61,46,
97,231,91,91,187,92,38,164,128,147,63,178,176,100,234,210,65,30,210,70,152,84,204,227,116,133,172,96,104,130,226,25,186,213,192,6,2,83,192,24,140,52,48,134,144,112,25,15,72,144,50,162,249,44,80,106,132,
112,14,147,70,71,238,18,161,24,126,234,5,219,83,132,0,17,145,152,203,65,226,156,135,64,195,14,14,32,129,230,221,242,121,234,122,13,117,18,209,37,67,180,237,12,123,98,98,80,176,198,138,13,168,192,153,19,
16,225,207,50,161,62,220,68,147,57,111,17,229,180,234,167,136,227,112,147,46,32,255,177,129,51,122,16,138,162,152,234,84,29,211,142,14,209,121,136,52,220,129,5,59,176,229,59,19,33,6,116,49,105,9,212,219,
204,4,79,33,57,57,8,147,70,66,97,5,13,70,16,22,134,248,237,153,174,227,130,250,214,129,205,37,41,52,155,167,164,203,73,236,242,130,5,244,64,61,154,89,217,33,58,118,188,68,64,130,30,69,144,192,14,220,57,
82,69,152,193,2,81,216,23,6,20,177,54,211,33,6,159,51,34,38,49,73,64,131,13,252,161,44,5,85,0,12,142,161,211,77,46,169,167,146,33,165,51,228,103,156,251,117,228,97,39,209,70,122,46,72,152,47,17,98,142,
169,58,149,139,92,132,6,58,236,32,4,95,208,64,85,51,145,203,12,200,17,142,148,155,96,81,24,121,193,66,202,33,76,251,160,129,221,210,186,83,215,161,239,44,136,80,203,65,17,241,73,80,98,115,174,74,139,146,
68,37,74,173,185,68,41,175,158,42,102,134,56,102,10,59,109,44,176,136,64,39,36,248,112,135,20,112,128,3,139,101,70,217,116,208,129,37,168,135,1,32,96,128,255,33,17,241,87,227,50,114,79,53,114,34,98,40,
138,143,26,128,193,1,92,120,128,78,21,192,133,48,48,75,104,152,176,8,40,119,227,73,242,30,14,90,46,4,12,72,0,67,53,81,173,228,141,75,69,4,75,9,33,8,115,82,143,59,70,144,194,14,56,64,129,29,4,119,25,101,
43,219,39,210,67,20,6,156,170,109,75,192,236,18,223,86,217,163,122,6,22,2,192,110,5,10,4,3,137,236,244,89,218,69,196,120,165,65,87,40,65,172,46,211,16,137,73,236,34,128,22,204,199,144,191,20,44,34,220,
192,84,58,42,2,18,94,64,67,8,118,64,129,255,62,35,192,81,192,32,138,159,154,136,210,193,76,70,149,77,207,228,122,144,5,124,212,129,11,117,0,3,119,41,178,172,239,58,171,147,204,56,90,225,178,217,97,68,
212,165,140,128,161,223,6,72,160,146,201,121,171,120,110,136,37,169,92,180,152,29,202,224,7,82,253,3,112,109,12,96,29,160,200,16,234,193,44,87,5,27,73,11,78,55,206,248,160,129,16,116,10,134,237,226,102,
82,74,18,45,105,49,255,178,225,249,193,69,50,32,38,37,150,150,38,132,11,214,160,134,42,141,180,152,57,150,72,50,31,34,6,63,224,0,141,255,224,95,54,3,248,77,1,40,5,13,118,136,9,58,59,145,193,119,70,4,43,
94,144,0,245,133,129,154,128,246,98,90,78,72,232,141,8,39,140,74,171,242,33,174,65,191,107,61,110,4,23,171,145,152,172,211,37,21,59,130,17,91,58,213,151,254,16,3,17,112,64,3,107,222,180,167,159,71,21,
29,224,1,179,164,22,172,244,40,186,171,11,18,115,21,98,218,199,8,18,16,6,46,128,1,12,218,77,208,65,5,61,232,40,199,143,195,155,90,154,93,26,205,61,22,17,2,142,165,138,47,96,33,237,84,115,200,1,15,116,
248,237,180,163,241,38,117,109,192,27,19,132,196,178,183,205,72,122,65,151,217,146,51,42,9,240,161,30,27,164,27,12,9,120,192,185,157,149,27,104,96,243,214,136,54,129,13,134,90,226,44,192,39,20,140,96,
67,152,194,44,223,141,45,2,76,144,230,14,99,240,112,135,253,114,58,17,53,94,243,192,15,97,50,255,29,172,196,169,153,40,76,122,158,155,207,24,76,124,17,147,227,114,141,178,48,2,62,71,147,45,95,20,47,51,
86,152,8,93,39,194,181,116,105,192,8,132,35,132,34,75,87,219,127,112,3,203,13,83,20,7,135,137,223,152,251,67,140,13,224,91,76,12,97,231,153,24,46,28,98,112,138,246,88,167,199,228,36,58,159,48,120,84,245,
44,87,166,65,177,129,2,250,172,241,167,255,97,227,238,155,242,33,220,178,27,222,60,99,181,74,211,6,0,70,32,4,12,24,213,51,213,17,197,202,216,48,246,1,106,212,141,253,70,4,26,174,32,85,157,99,162,11,112,
239,143,186,230,64,35,83,45,67,229,67,239,118,19,15,33,7,57,36,230,199,55,202,66,105,121,211,155,115,251,30,241,239,163,250,31,230,202,90,40,229,143,98,20,19,249,7,26,96,121,151,101,134,120,155,63,68,
152,89,44,230,234,40,28,165,138,56,243,14,108,158,250,141,188,137,14,241,145,179,13,51,177,200,93,205,62,6,161,232,59,178,213,179,18,26,100,161,5,35,120,192,171,3,32,124,39,57,255,222,45,140,207,200,148,
29,127,245,225,67,94,222,75,51,114,47,96,86,172,32,7,45,145,30,208,215,37,103,183,84,69,65,64,244,240,37,230,32,3,69,160,1,18,96,122,221,71,112,98,160,3,116,176,12,132,97,58,199,150,30,103,128,79,208,
133,126,161,96,72,40,231,25,99,213,3,24,32,0,0,224,2,248,119,110,140,135,113,249,151,9,195,81,124,250,71,98,249,179,90,13,96,114,67,246,115,225,182,121,165,64,91,3,180,84,222,178,108,135,32,129,83,117,
129,121,81,54,102,96,0,97,114,119,166,99,132,228,36,130,208,85,89,243,50,42,200,6,2,115,211,79,24,32,81,189,129,127,9,224,133,193,113,77,246,199,123,184,214,66,75,227,22,147,87,121,194,227,94,161,48,10,
41,103,96,130,69,105,13,152,67,73,36,133,94,192,7,69,64,1,84,165,132,30,177,9,98,112,7,52,178,112,165,163,84,135,64,133,123,178,68,103,96,123,71,37,75,152,181,10,142,176,1,47,208,0,54,128,110,191,247,
22,99,40,28,171,181,137,196,55,110,154,88,98,102,229,255,8,162,114,118,207,103,68,75,224,6,36,32,118,228,240,114,224,194,53,213,209,129,152,192,0,121,240,3,41,176,125,126,200,28,102,0,1,122,128,65,65,
55,65,94,130,138,61,16,130,85,40,31,133,84,126,121,130,98,90,136,133,54,210,10,53,240,2,66,32,0,193,81,90,96,56,141,248,39,28,128,241,2,24,32,60,144,244,134,168,178,82,10,152,138,99,39,126,48,39,75,190,
136,9,32,144,7,122,208,78,157,118,139,59,145,11,65,0,7,6,192,7,203,21,116,71,116,108,103,176,96,242,232,82,123,178,92,113,182,128,161,144,20,110,99,76,174,144,5,89,240,2,6,105,144,45,144,144,216,136,1,
89,32,51,255,184,141,141,56,71,244,212,114,243,21,102,142,208,138,220,82,79,41,85,106,163,183,142,236,200,28,16,240,7,115,96,0,104,176,92,202,54,65,40,245,84,138,196,109,232,71,123,48,35,100,183,23,13,
144,196,92,197,4,73,79,180,61,125,231,96,47,247,12,135,33,142,138,192,8,20,41,10,100,130,8,17,112,7,31,233,57,44,64,7,104,144,255,9,140,177,108,199,198,109,121,242,96,137,192,136,147,179,53,119,150,147,
125,55,116,14,182,72,141,200,33,227,8,148,244,116,96,166,176,138,114,132,128,91,163,84,213,99,132,49,112,2,55,119,148,36,19,4,30,112,109,177,88,14,117,215,148,136,193,72,13,135,9,52,64,149,152,240,136,
85,9,38,72,7,150,62,217,151,64,233,75,134,105,152,203,160,126,51,241,128,203,224,5,56,112,8,125,232,150,84,2,7,80,48,7,203,129,9,66,151,9,97,98,140,36,168,8,57,137,24,18,25,110,204,69,95,49,161,8,135,
73,150,163,89,20,204,144,149,184,85,142,153,112,102,22,40,153,230,226,3,16,112,7,121,224,154,94,37,14,133,180,141,219,56,93,83,57,64,114,230,75,12,136,154,176,148,9,194,9,13,138,121,20,202,54,148,136,
112,3,127,144,2,178,121,75,16,96,6,118,240,8,67,217,87,92,133,42,71,85,123,120,249,143,137,16,149,203,5,150,161,153,154,199,9,13,135,153,8,58,185,111,196,41,133,209,201,102,98,0,7,51,116,89,204,176,108,
119,114,255,108,235,87,123,123,153,20,219,24,158,63,233,151,52,233,17,150,211,141,86,73,156,237,233,135,102,32,6,118,32,3,188,72,38,216,121,67,158,135,159,140,68,123,73,241,153,17,9,115,192,9,13,50,129,
158,220,217,143,94,153,155,236,89,160,211,230,3,102,0,7,120,49,61,189,40,95,149,230,114,219,201,157,181,151,152,127,105,60,160,41,126,28,178,161,181,55,100,151,85,152,130,165,112,32,122,148,65,98,7,17,
144,91,66,113,146,95,82,159,101,9,38,57,201,162,46,170,152,226,152,161,25,202,157,66,6,148,220,82,158,135,180,163,146,9,5,112,96,155,2,138,119,229,120,39,245,57,15,171,152,161,139,196,162,45,74,126,14,
230,164,147,67,149,53,90,78,101,105,81,119,248,161,84,122,139,129,84,37,183,249,49,220,209,87,215,17,71,43,131,145,50,177,162,98,42,166,88,9,156,26,69,14,249,230,37,111,90,168,90,96,7,120,160,15,227,231,
85,13,26,150,47,113,152,150,131,149,97,106,57,81,234,75,165,114,169,240,117,162,133,42,153,187,0,157,236,193,255,156,81,168,25,30,146,111,167,73,95,57,116,154,155,113,24,202,38,65,155,218,170,138,96,7,
34,80,72,27,49,20,31,138,169,182,122,171,42,22,47,156,225,166,174,186,169,138,154,146,209,96,167,235,48,168,165,118,72,67,1,133,184,217,171,202,202,148,28,37,13,188,90,106,108,176,24,164,48,10,247,181,
19,119,180,172,216,154,68,207,160,25,214,67,171,222,42,170,220,42,170,185,41,78,216,90,174,153,96,128,101,70,167,3,151,171,230,90,174,33,153,8,70,23,173,101,54,174,11,100,132,160,218,174,248,250,7,50,
80,123,133,144,174,254,154,174,150,118,175,105,151,175,4,11,13,112,160,23,101,82,72,26,163,98,220,138,146,1,43,46,12,112,71,203,213,7,69,112,7,177,89,176,24,139,8,38,16,1,104,0,26,105,32,7,84,80,119,151,
234,5,167,16,177,75,224,5,40,75,5,84,144,8,82,160,8,7,80,157,25,27,179,135,176,2,137,224,1,135,240,1,127,240,3,126,128,7,17,112,3,206,153,7,64,43,122,73,16,1,45,43,179,70,91,34,151,144,15,9,118,208,60,
213,105,179,127,224,180,71,11,13,129,0,0,33,249,4,5,20,0,127,0,44,12,0,15,0,195,0,204,0,0,7,255,128,127,130,131,132,133,134,135,136,137,138,139,140,141,142,133,121,27,143,147,148,149,150,151,152,153,154,
136,64,131,72,127,73,158,136,124,155,165,166,167,168,169,138,105,135,39,160,127,72,159,55,127,146,127,53,164,127,184,170,187,188,189,190,137,8,172,105,195,105,68,73,73,68,121,127,103,32,130,75,132,11,
124,164,61,61,130,52,191,216,217,218,136,8,135,172,70,172,127,223,197,124,84,61,103,114,205,135,32,36,213,212,219,240,241,189,8,64,221,130,8,248,131,225,223,70,224,124,49,36,72,200,161,209,131,4,136,103,
206,4,177,163,22,176,154,188,135,16,49,217,19,196,42,88,191,139,70,168,16,139,17,227,95,140,129,31,13,170,115,182,164,36,155,128,131,64,140,140,200,146,165,61,97,251,112,16,75,99,4,135,204,52,103,114,
102,36,225,38,160,207,134,13,169,9,21,153,48,161,74,133,45,147,106,155,56,51,141,204,155,49,112,230,116,227,166,100,73,6,12,6,101,77,100,181,228,66,134,1,85,30,36,132,80,169,217,121,226,130,13,139,154,
211,160,155,131,207,255,202,50,66,88,182,100,33,6,236,124,138,101,83,215,205,217,191,150,242,253,193,215,173,233,25,35,135,171,202,45,90,200,42,201,186,93,233,58,30,180,68,101,59,149,108,254,44,6,204,
249,94,161,122,131,7,229,83,75,236,140,27,47,118,13,209,77,24,185,181,107,205,145,97,223,181,28,150,47,27,191,84,58,235,22,61,184,112,211,140,169,15,185,30,78,188,120,87,205,136,78,202,41,72,130,80,243,
221,17,233,209,227,125,47,152,197,140,138,85,27,111,205,166,251,160,204,221,189,102,94,194,215,106,249,214,130,182,166,108,87,16,68,102,232,17,59,133,238,70,248,247,105,47,91,229,218,141,220,157,141,251,
102,254,137,133,89,119,255,245,183,23,102,98,21,151,92,94,207,193,7,81,61,245,16,134,192,77,25,161,150,222,31,249,13,71,160,128,28,50,114,20,82,28,54,179,215,113,147,145,197,96,15,254,253,209,142,131,
217,208,87,31,77,70,40,182,132,122,146,69,22,226,58,33,230,168,99,33,57,162,183,25,3,39,161,211,160,67,44,250,18,225,48,216,241,133,225,255,140,144,217,40,160,66,58,70,41,165,72,97,173,244,135,128,225,
29,119,8,27,61,12,148,78,145,70,14,134,100,140,124,97,69,25,108,93,249,23,32,148,82,182,25,165,65,122,229,152,210,128,36,222,69,2,13,52,24,36,7,152,169,72,136,36,21,168,169,247,24,127,98,65,41,146,155,
136,10,24,86,156,12,30,122,212,94,231,253,8,130,28,28,237,201,167,41,248,252,137,218,140,100,197,214,31,136,98,85,153,232,123,130,144,138,40,149,12,62,41,96,108,179,197,32,67,12,151,106,130,207,77,84,
80,145,153,160,104,78,22,96,142,140,70,73,22,120,127,244,71,106,176,83,178,99,217,141,87,170,196,42,89,36,72,19,78,172,147,248,89,97,112,131,218,149,226,156,161,210,214,161,112,141,21,242,41,143,216,26,
235,232,141,171,150,56,8,9,103,80,4,109,35,221,212,51,12,21,32,88,216,216,113,31,38,203,97,149,201,150,26,236,190,220,122,248,158,123,252,218,171,232,161,135,178,169,37,101,78,173,235,200,132,52,217,90,
87,174,169,137,216,230,149,132,0,172,90,255,167,53,110,214,8,175,63,21,172,98,130,155,81,193,7,17,10,115,242,7,16,50,197,40,239,153,230,34,234,72,92,200,145,4,49,204,49,107,124,38,155,141,254,84,177,178,
212,254,225,151,46,37,135,230,110,26,128,206,200,64,147,114,185,73,136,119,239,57,70,98,162,60,211,220,243,188,255,210,214,49,74,34,153,43,72,110,65,19,162,86,209,130,198,101,146,169,114,118,43,28,121,
161,46,122,117,218,63,113,248,90,34,234,176,221,241,199,81,123,251,7,172,10,119,98,209,105,102,138,13,155,119,113,35,43,34,183,149,229,124,53,115,87,39,62,238,81,37,78,125,173,220,109,215,93,8,222,44,
74,119,65,39,122,55,204,41,203,38,237,140,236,195,70,25,238,147,80,164,151,110,250,80,107,131,188,218,212,8,165,141,56,214,152,81,187,4,229,149,3,33,159,69,94,176,65,35,154,251,238,138,236,176,60,30,126,
58,233,120,22,79,144,59,195,191,46,170,123,251,201,134,72,206,202,243,108,200,53,240,129,118,121,111,68,175,92,51,121,224,237,24,48,89,87,2,197,30,255,53,114,12,100,252,249,232,167,143,231,233,189,50,
159,218,85,56,254,68,186,32,6,149,87,136,165,187,117,115,185,222,211,134,109,30,197,200,34,214,247,236,21,20,161,152,15,125,127,40,222,2,22,64,131,24,44,208,120,12,60,95,2,143,55,191,229,73,110,119,134,
24,29,88,154,99,144,158,245,128,118,102,153,142,237,6,129,131,10,97,104,94,228,209,215,141,128,7,27,171,177,39,125,28,89,128,3,23,72,195,26,210,80,16,54,164,161,250,80,103,65,37,165,135,102,21,211,32,
226,146,213,179,6,157,5,52,132,40,161,195,112,133,144,170,133,8,88,224,59,145,80,208,55,67,27,254,225,134,53,88,64,13,182,8,13,43,226,48,125,60,92,156,92,112,165,16,249,41,175,131,151,26,6,9,202,68,53,
137,33,232,40,222,185,89,94,166,168,192,28,70,195,22,91,204,163,32,184,88,3,60,30,34,139,11,188,226,13,35,72,144,63,144,174,87,62,92,210,251,194,87,192,118,176,71,122,231,2,225,89,130,65,130,224,136,45,
133,56,3,88,127,8,85,64,9,218,144,255,15,121,236,227,30,241,24,202,62,234,209,143,166,44,196,2,4,249,192,226,29,50,114,7,9,91,197,24,57,190,161,48,175,16,61,0,218,89,136,166,59,140,97,242,137,224,1,222,
28,169,81,188,24,92,131,134,167,36,101,42,67,9,141,69,152,50,139,131,24,228,249,74,199,40,186,8,234,95,42,170,101,53,2,146,72,133,72,210,37,188,92,76,196,4,6,169,197,248,135,61,7,132,85,13,81,217,71,25,
12,34,153,134,88,101,35,144,41,202,26,94,195,120,212,172,210,51,178,194,164,82,1,78,69,165,203,230,88,148,50,157,208,80,196,8,221,100,13,57,63,196,194,57,26,175,138,183,88,166,45,100,32,202,81,218,66,
158,167,192,40,43,173,225,202,215,41,235,104,75,50,68,51,180,73,183,158,125,83,30,172,96,35,248,214,227,177,241,116,101,33,230,115,224,12,147,89,131,13,212,130,16,160,100,68,69,41,65,189,27,10,146,163,
235,3,75,130,8,1,210,197,212,114,57,89,187,95,82,88,81,21,255,205,169,57,133,2,22,93,64,64,204,6,214,80,143,20,255,21,132,59,45,234,71,93,170,66,158,235,100,37,62,153,115,165,166,153,73,61,153,41,32,82,
195,162,31,252,201,195,30,84,216,220,153,50,83,175,189,136,180,29,197,92,160,30,107,224,206,13,108,117,167,22,133,230,21,5,219,204,74,104,244,158,172,12,100,43,131,90,144,178,106,7,41,163,67,42,67,6,154,
16,175,182,136,38,189,4,31,93,103,73,49,19,181,3,36,209,96,230,86,109,42,74,62,238,148,20,165,213,162,70,39,177,90,26,172,214,167,182,192,97,43,109,169,172,69,52,196,144,168,235,153,101,179,97,4,252,116,
107,112,115,98,153,102,216,81,62,215,174,18,158,54,149,193,77,19,193,199,193,6,18,176,140,88,109,33,240,212,204,227,66,115,149,198,139,147,209,178,2,210,66,140,175,124,213,160,44,82,228,17,35,113,238,
171,174,0,98,12,113,241,20,90,46,74,226,189,120,220,106,35,118,74,216,77,216,241,143,215,141,224,6,197,123,66,125,69,182,124,31,91,76,186,182,209,141,184,58,245,92,207,193,12,101,74,242,194,5,130,210,
189,240,181,133,255,95,29,97,74,213,66,247,18,26,101,224,34,180,8,72,253,78,54,150,55,99,169,64,192,219,131,218,70,164,183,178,236,108,54,147,149,72,175,244,0,79,29,121,176,77,5,241,94,229,82,116,185,
138,72,101,108,43,172,9,233,82,239,16,214,93,165,126,145,106,226,117,12,162,75,224,117,236,67,82,106,222,134,54,67,63,84,133,49,135,251,250,135,44,220,212,175,27,224,235,35,132,60,74,46,103,244,152,136,
16,178,22,191,88,60,189,44,166,187,71,25,113,249,160,154,80,94,76,132,20,113,253,173,138,145,98,212,23,59,80,198,85,166,241,77,109,156,213,249,18,34,139,128,182,111,2,163,169,8,140,114,120,177,182,180,
25,114,208,185,86,254,250,2,7,244,235,215,72,141,40,204,23,187,118,139,202,221,64,22,178,64,99,66,96,185,166,242,117,230,69,1,61,230,76,4,210,26,209,141,230,113,133,220,209,122,173,52,173,43,74,180,54,
80,182,39,51,137,52,155,80,101,204,149,236,204,97,155,114,122,211,56,254,131,59,65,253,136,64,211,55,19,174,221,168,98,175,255,152,8,197,98,212,149,97,81,196,72,77,103,144,66,24,193,23,70,44,10,59,232,
87,237,152,149,234,78,14,228,171,175,55,205,105,68,184,211,198,194,158,39,14,7,27,219,150,168,22,168,147,53,155,115,200,215,165,124,101,163,214,191,205,118,122,19,34,144,208,218,84,18,229,86,68,150,177,
204,90,104,92,56,213,64,198,240,161,103,27,144,125,134,248,156,159,5,48,26,7,193,181,84,144,130,137,252,202,118,55,5,210,145,154,106,58,11,24,168,242,140,21,17,106,117,51,219,194,148,192,46,42,2,9,74,
29,18,4,141,91,145,37,76,151,163,162,169,161,130,8,3,6,223,51,140,184,146,184,80,181,227,190,198,128,208,27,129,229,146,83,120,221,210,77,117,210,49,28,205,91,48,92,29,234,81,207,180,203,7,94,184,244,
130,15,126,121,53,143,172,180,235,142,43,23,228,33,15,248,166,15,113,101,163,231,248,186,235,86,10,61,5,185,190,108,175,227,179,9,108,143,162,53,65,4,57,152,23,71,224,3,183,199,203,29,246,95,147,59,17,
4,167,68,61,153,61,137,255,100,47,29,19,138,237,35,171,243,52,146,213,240,123,16,47,23,111,214,75,33,73,185,112,144,179,200,161,1,40,63,30,242,65,140,157,17,4,87,238,32,204,174,74,231,26,118,23,92,214,
171,211,25,40,119,157,251,151,163,173,223,5,25,157,163,34,0,142,132,170,90,148,65,22,110,208,121,65,12,61,224,180,0,126,167,111,202,215,131,19,250,207,150,240,178,125,13,77,79,29,22,100,238,244,179,180,
67,160,95,9,52,120,181,117,8,238,118,235,238,196,215,221,99,160,15,133,16,62,176,131,61,136,145,147,254,157,165,54,62,35,126,220,139,49,103,177,237,253,237,219,86,22,226,202,57,159,2,120,152,68,176,28,
19,184,0,95,247,225,5,47,64,8,157,23,118,158,38,124,158,70,11,53,245,78,18,85,90,239,84,122,205,6,15,99,54,91,35,193,93,103,178,16,19,116,37,212,71,9,153,165,109,250,135,129,0,212,3,99,6,114,0,104,8,33,
215,123,121,166,105,121,134,8,9,200,85,200,199,110,234,231,110,185,199,118,121,162,21,253,245,120,150,86,115,167,64,255,50,207,83,123,152,55,82,52,80,83,34,216,2,47,96,130,190,247,7,38,200,4,6,168,83,
204,213,110,232,183,97,236,183,11,57,229,105,128,68,16,43,65,70,219,118,129,142,134,9,27,136,28,239,129,18,207,227,90,154,134,1,47,208,2,130,240,127,134,192,119,158,151,134,136,0,95,231,55,120,133,192,
69,16,225,116,183,176,71,161,244,64,110,119,8,2,209,118,25,232,8,94,32,111,62,145,18,204,162,69,65,24,128,132,72,132,130,0,114,226,247,121,7,216,105,233,102,8,244,101,104,141,240,132,166,96,97,165,150,
11,166,68,81,172,7,2,179,135,75,131,230,129,170,240,12,44,4,64,80,242,131,27,32,134,45,32,132,130,0,128,134,104,132,103,88,101,73,216,128,19,150,99,164,36,97,89,6,135,197,115,114,170,80,97,17,101,137,
122,84,139,12,212,32,49,23,60,230,163,34,161,184,9,70,165,23,11,70,2,253,151,5,0,40,4,100,56,130,0,72,136,69,40,116,73,248,119,36,71,126,132,32,3,153,246,111,220,88,139,239,71,93,135,103,9,207,20,255,
133,182,240,96,244,69,16,113,145,98,209,215,118,92,71,9,202,176,37,206,145,107,7,193,23,32,240,131,34,232,140,132,64,136,170,120,8,171,232,121,86,166,130,161,214,78,219,104,101,31,71,110,4,73,90,121,164,
97,203,150,114,10,88,142,111,24,88,180,144,101,12,244,100,155,72,8,212,83,73,169,176,25,94,24,55,75,160,140,146,16,128,127,32,4,131,64,134,169,248,7,32,41,128,69,120,8,86,246,143,135,160,141,233,182,141,
127,192,4,50,137,132,155,198,123,6,73,110,255,182,122,176,53,9,21,117,92,143,96,83,172,183,135,215,240,14,153,144,115,191,98,25,43,166,47,20,83,3,32,39,4,34,41,8,36,121,8,39,153,146,41,24,126,85,153,141,
89,22,145,51,185,149,76,112,3,187,199,123,125,32,116,212,120,147,146,48,135,23,37,120,76,216,128,160,151,101,198,228,104,179,55,148,89,168,9,41,242,28,13,242,47,253,103,146,147,0,146,38,88,130,173,104,
141,163,231,78,92,57,147,55,112,3,177,208,7,255,23,1,47,128,152,255,103,152,24,48,255,152,141,73,144,115,24,142,200,247,76,105,89,153,133,112,110,146,192,7,121,130,127,135,48,16,145,166,133,234,248,153,
157,53,151,76,25,128,13,96,8,36,25,149,138,16,118,67,103,149,1,199,4,131,32,147,55,32,152,132,137,4,17,240,7,17,112,2,45,160,4,34,32,2,66,128,7,192,121,138,45,96,152,134,57,152,89,64,81,47,56,153,202,
201,8,89,213,87,53,240,17,92,71,70,213,176,62,237,136,8,69,32,5,131,80,121,29,8,46,9,84,138,47,208,0,224,105,8,34,41,132,170,25,141,36,200,138,189,87,110,214,72,155,131,89,155,17,240,158,74,192,155,189,
89,8,126,224,7,13,208,155,74,208,2,72,64,156,94,25,9,106,169,130,177,37,153,90,117,110,91,133,110,64,153,39,252,180,82,101,49,140,119,216,8,21,103,55,94,120,87,11,192,140,66,112,154,130,208,0,79,57,8,
25,170,154,120,57,149,40,105,8,176,217,149,237,57,152,177,0,159,74,32,5,34,176,5,91,240,7,38,208,162,122,160,7,38,0,163,35,208,162,126,32,2,45,16,255,1,55,218,7,198,153,7,148,249,71,147,160,141,231,38,
108,162,71,11,52,246,156,118,231,109,23,130,54,43,242,114,115,103,12,174,240,7,69,224,8,58,243,29,187,86,3,24,80,161,135,224,148,33,233,148,206,248,140,131,96,158,42,217,154,177,41,162,177,224,158,39,
112,162,41,186,5,69,96,2,63,240,3,83,48,5,87,96,0,114,58,167,6,240,166,38,224,7,187,41,4,17,192,152,94,169,99,148,105,108,230,166,141,90,38,108,4,87,116,217,168,153,79,70,22,252,84,25,43,242,7,114,208,
160,135,128,157,30,210,129,131,83,143,204,24,158,132,96,161,89,250,7,28,90,146,97,58,116,33,122,3,73,16,11,72,144,4,39,112,2,40,170,162,107,250,3,87,16,167,119,112,7,31,16,171,116,64,7,31,64,171,31,112,
4,117,218,155,126,160,4,182,153,152,125,144,5,128,180,71,214,197,156,141,72,99,54,86,168,51,54,114,149,196,93,9,122,8,212,19,151,26,184,18,151,7,92,11,112,165,13,32,0,133,128,169,132,32,146,92,218,169,
210,88,8,98,42,255,8,132,121,12,182,137,166,42,218,166,172,106,0,33,16,2,119,16,2,31,64,1,181,58,171,41,48,175,243,122,171,119,250,7,126,128,7,45,128,7,34,160,4,47,0,172,204,164,150,237,244,146,125,133,
153,7,8,95,17,102,83,124,144,46,21,169,14,150,242,124,147,0,105,140,192,65,242,104,72,21,133,173,216,58,8,224,169,173,168,89,8,230,121,146,233,41,147,176,112,12,185,137,170,80,218,166,87,240,7,113,202,
174,240,202,1,179,74,7,59,64,175,41,96,5,52,155,2,79,112,4,38,48,5,248,218,155,45,42,2,255,202,76,240,4,164,90,53,97,17,70,116,27,192,4,207,169,137,73,138,86,240,56,9,197,72,123,181,247,40,52,144,5,21,
154,177,2,208,0,42,96,8,27,91,8,221,234,177,38,41,141,157,55,155,179,144,4,239,137,170,82,176,170,41,187,178,235,74,1,28,192,1,59,176,3,26,48,175,52,235,1,130,224,1,116,155,2,183,42,167,83,112,167,122,
176,183,34,128,4,239,245,130,153,70,164,199,90,180,107,24,147,238,212,3,88,81,255,22,111,233,168,246,183,9,127,232,93,213,122,154,24,139,177,153,154,173,226,201,169,134,16,141,35,200,138,182,121,2,17,
32,5,82,160,166,40,123,5,235,186,182,116,240,7,41,32,1,18,240,7,30,112,0,174,203,2,44,48,7,115,128,5,88,224,1,86,144,186,181,250,1,117,106,0,119,96,0,38,32,4,125,16,164,217,232,146,255,54,164,229,231,
8,34,203,4,89,198,176,251,4,68,239,81,111,158,136,9,249,199,109,222,85,3,223,41,8,42,32,0,89,171,2,88,155,8,154,170,161,227,41,149,1,24,114,165,10,186,163,91,4,69,80,186,166,27,2,127,224,182,59,32,1,113,
112,0,30,32,187,131,176,2,51,128,191,249,123,187,41,32,175,120,251,7,31,16,0,188,107,2,74,192,188,177,88,126,67,138,141,32,58,147,52,38,147,71,11,155,27,16,3,253,212,55,103,178,34,123,2,173,134,240,160,
75,67,8,68,194,193,27,16,128,89,171,189,220,123,181,216,26,194,90,171,161,26,58,134,157,106,152,184,137,170,168,186,190,165,187,182,240,171,1,173,27,255,7,118,203,2,40,128,2,88,128,191,127,16,4,127,0,
1,65,48,3,88,160,186,51,107,7,253,235,2,116,128,183,6,224,7,72,224,192,161,166,192,139,160,136,176,57,8,131,201,4,124,48,70,250,145,25,213,128,84,153,208,68,43,182,77,20,155,64,87,58,2,127,96,194,219,
91,198,88,155,198,135,160,173,220,218,198,30,251,185,167,122,182,173,58,199,235,74,8,26,32,8,173,43,1,86,240,7,40,192,199,127,176,6,62,252,195,16,0,1,51,128,187,86,96,183,118,96,7,30,96,7,29,128,183,83,
32,2,179,57,114,201,123,8,12,188,188,132,48,197,89,192,149,229,38,3,137,122,66,215,244,21,31,179,9,93,248,14,88,211,28,11,0,146,89,59,2,33,188,189,42,224,189,174,92,198,142,144,161,248,104,146,17,112,
162,162,43,5,172,186,174,41,75,1,239,43,8,111,235,203,49,155,2,30,208,199,43,0,200,65,48,200,16,160,5,90,0,1,43,192,2,30,176,2,43,96,183,182,11,3,86,144,2,56,91,192,180,32,95,56,22,162,49,57,118,52,105,
255,201,49,25,206,135,144,7,149,52,193,54,231,14,72,90,9,164,210,32,94,24,16,53,144,161,134,112,198,172,28,190,38,188,8,220,138,138,242,41,186,127,112,186,117,204,1,239,11,191,28,64,1,108,59,171,59,96,
5,248,187,6,198,28,4,199,172,204,109,16,4,58,188,6,112,64,187,208,188,2,48,224,1,79,96,0,91,48,155,16,44,178,174,24,162,153,12,162,177,249,149,132,48,162,127,112,3,58,234,16,221,213,93,135,80,13,123,152,
28,71,38,8,100,181,77,80,12,203,218,155,198,102,156,173,152,106,161,34,169,194,34,240,7,91,112,182,63,176,182,2,253,7,67,221,182,20,16,2,71,64,1,79,240,1,46,155,2,127,140,208,65,0,213,201,44,6,80,160,
5,208,172,204,112,176,2,112,224,0,208,76,205,31,96,2,77,76,11,50,249,209,153,252,209,151,252,209,35,58,11,84,76,210,131,96,152,223,100,84,80,187,8,224,55,47,235,225,16,29,172,34,189,103,3,137,80,207,174,
252,202,245,252,7,225,137,165,128,125,138,66,224,7,106,138,157,87,32,255,208,28,48,4,109,27,208,2,125,212,72,205,1,120,27,171,41,96,204,79,141,208,16,64,213,80,240,195,51,240,7,62,0,1,112,176,213,48,192,
213,48,240,1,83,160,4,106,61,214,99,231,205,105,221,218,131,201,138,37,173,214,41,201,194,74,75,84,152,71,9,92,103,121,245,214,88,48,221,3,32,89,7,141,144,181,37,108,211,218,123,185,128,29,158,45,80,216,
127,240,3,38,128,203,137,189,3,93,240,7,140,77,212,252,124,4,33,176,186,188,123,4,86,176,6,63,28,213,208,12,200,98,224,3,62,80,6,80,0,1,62,96,1,98,0,218,60,96,5,163,13,3,1,96,0,144,60,155,135,56,11,105,
221,152,124,121,223,188,39,150,246,141,158,251,9,126,159,208,28,140,123,10,100,196,66,123,194,65,211,217,2,38,92,7,192,173,8,171,172,177,13,158,181,223,171,169,201,253,7,122,0,165,91,240,3,127,176,3,95,
112,0,93,160,1,67,0,217,173,170,174,31,32,1,30,240,1,54,96,0,123,252,7,203,60,209,43,240,7,225,61,222,127,0,5,231,253,255,7,4,224,0,127,240,0,97,0,3,43,224,2,0,176,5,177,32,162,188,103,132,141,153,146,
67,215,123,66,135,4,223,215,7,72,30,150,196,217,228,183,137,63,139,219,172,209,107,72,144,138,83,250,193,47,231,68,148,177,86,13,167,185,224,11,254,7,95,206,224,52,253,7,25,219,189,223,171,177,42,107,
0,234,27,212,127,112,0,7,32,1,119,204,203,232,26,167,218,237,1,71,48,2,54,96,5,153,157,222,182,107,187,107,160,5,158,93,6,101,80,5,81,96,1,52,238,0,29,144,0,46,144,227,29,0,0,2,128,4,79,170,223,130,240,
9,72,94,233,74,110,152,251,73,233,74,158,233,127,176,233,164,138,4,137,137,1,212,195,36,42,205,47,93,194,219,132,240,9,135,128,65,155,21,113,0,181,34,11,32,0,95,238,229,192,93,7,42,16,230,98,62,207,172,
252,7,100,220,2,126,160,7,114,170,190,87,224,207,44,32,8,26,176,3,33,240,3,234,187,5,108,122,5,51,107,3,2,48,2,122,46,222,16,208,231,67,108,222,102,80,5,85,96,1,85,240,255,7,81,80,2,60,240,0,0,160,232,
97,208,232,4,140,157,132,137,1,154,254,233,159,174,228,157,190,159,157,14,11,47,0,239,241,222,161,154,75,10,251,81,84,69,177,197,246,135,6,134,112,82,136,64,202,213,112,120,10,238,229,96,190,215,197,221,
189,100,94,211,45,32,0,190,123,7,106,26,2,59,96,191,111,206,1,33,112,157,216,121,174,1,240,4,216,218,0,29,96,222,62,64,0,48,48,242,58,14,1,102,32,8,39,31,5,58,144,1,14,160,0,96,64,198,55,238,2,9,64,192,
62,126,3,243,254,2,158,14,11,160,206,185,95,11,141,39,9,146,55,15,234,136,57,156,125,228,55,102,243,28,119,141,199,132,160,12,21,57,8,12,170,34,215,80,81,21,80,1,135,80,235,86,127,240,98,14,203,42,96,
3,24,250,7,190,107,0,163,75,1,173,203,2,176,43,1,20,240,3,250,156,4,241,185,5,71,240,1,167,41,4,46,0,1,81,16,5,4,224,1,21,253,7,88,96,222,127,96,6,62,208,237,116,15,3,137,30,237,54,144,0,9,64,230,34,96,
255,2,183,233,243,137,137,152,250,136,152,180,156,152,144,239,248,180,92,8,168,24,1,146,32,54,155,24,107,217,102,148,214,0,125,93,66,93,134,132,91,27,160,2,84,63,245,165,95,8,87,95,240,96,174,224,88,127,
8,54,176,245,33,105,3,175,106,0,17,80,4,196,78,246,130,112,241,174,112,3,104,64,182,74,96,0,71,208,0,201,29,0,37,144,1,159,77,179,97,96,5,121,47,222,62,32,227,98,208,6,5,16,6,1,0,0,130,48,2,0,112,253,
35,32,2,63,160,4,154,139,151,80,9,149,81,41,156,224,127,138,35,169,194,156,74,254,135,184,49,72,95,229,197,170,8,159,79,61,168,14,220,84,63,8,167,111,8,181,126,240,86,95,240,170,127,255,212,15,8,13,127,
119,127,6,73,127,136,44,44,7,18,127,33,82,73,104,68,127,55,72,74,83,0,13,47,66,9,14,4,16,112,29,127,41,29,30,107,98,168,168,159,112,46,0,35,136,130,35,175,91,6,127,125,127,47,136,136,45,45,186,190,191,
190,189,187,127,194,191,24,186,75,75,127,202,191,32,255,36,192,208,186,52,208,108,191,211,127,114,127,61,127,215,209,127,21,224,223,222,136,117,228,127,229,117,229,127,9,0,117,2,13,31,119,6,87,125,69,
18,18,138,127,18,26,87,73,73,68,50,112,228,177,52,197,134,16,98,9,96,192,129,179,162,67,10,23,46,172,172,128,64,145,226,154,53,60,62,140,208,244,231,32,162,17,91,62,140,27,73,18,90,31,102,204,126,85,3,
81,18,209,173,110,127,24,44,171,230,11,230,54,26,48,247,0,171,240,45,156,79,113,64,163,161,75,32,64,64,128,63,83,244,220,176,135,143,197,189,29,69,254,160,249,19,35,13,165,22,91,70,188,192,240,2,128,29,
30,88,96,64,12,16,32,5,150,53,65,130,92,100,232,225,79,131,22,199,220,194,250,67,199,15,34,143,66,148,232,194,219,241,160,144,191,45,125,221,66,148,44,26,75,57,217,150,5,70,198,166,49,203,95,36,228,244,
160,177,13,145,206,63,123,46,147,4,199,153,115,207,111,234,18,252,121,245,224,131,30,61,104,138,216,145,112,224,192,159,29,28,164,78,74,99,149,73,255,159,22,66,94,100,121,49,2,140,157,223,31,2,28,57,242,
193,195,138,25,43,146,175,192,34,42,215,31,174,29,117,165,48,145,11,48,34,17,30,23,91,215,85,44,183,178,239,50,199,109,75,9,45,79,98,95,75,170,177,113,86,89,151,100,202,64,53,235,204,172,121,28,207,157,
60,193,240,84,129,40,128,93,52,91,72,176,195,61,28,112,64,129,20,68,224,64,219,25,56,200,176,1,116,27,184,5,0,68,173,28,97,131,1,6,88,49,7,10,88,116,232,129,7,46,136,144,69,22,186,108,210,203,21,118,152,
16,129,92,130,252,33,194,98,192,252,149,221,95,34,188,144,12,27,133,121,179,205,120,222,188,228,75,120,127,208,100,77,77,150,189,97,228,27,152,213,119,153,124,129,233,196,197,31,0,40,224,194,127,91,208,
17,155,129,20,60,130,3,14,127,164,97,68,12,49,240,177,193,6,53,252,177,219,8,119,12,103,195,20,35,152,48,197,19,31,126,248,135,21,127,28,209,194,152,17,30,211,139,16,132,152,48,87,139,186,52,32,104,118,
48,238,245,71,4,202,224,255,168,152,47,141,233,66,194,51,36,181,183,104,144,226,113,35,206,27,77,52,129,36,146,192,100,246,11,125,160,134,234,228,30,92,0,32,90,7,38,224,113,131,20,31,80,224,106,8,33,92,
241,7,2,10,166,65,197,25,103,80,165,203,6,89,136,112,90,155,32,109,17,210,128,247,164,240,196,19,83,32,81,67,13,121,6,122,71,138,127,216,21,216,139,128,150,68,232,164,203,228,232,11,164,139,1,73,169,52,
11,96,3,77,19,136,144,11,12,167,190,160,139,110,167,123,32,169,64,29,96,56,96,135,30,17,220,112,194,21,176,198,122,197,15,179,42,248,199,173,61,228,58,205,2,204,190,32,130,31,34,36,156,176,18,87,80,80,
224,19,177,29,225,39,31,127,240,234,75,3,116,72,224,71,118,13,248,33,136,199,191,188,232,11,181,119,69,23,141,31,206,141,244,216,163,216,22,90,83,55,147,209,240,194,125,229,150,107,46,185,70,254,113,164,
55,71,110,138,36,185,96,60,160,6,12,6,172,24,193,15,72,239,251,67,17,73,0,1,132,151,127,24,81,89,15,147,45,255,192,71,22,17,180,144,181,18,72,156,112,116,190,249,26,32,2,19,127,212,32,67,22,208,253,33,
0,29,41,32,124,178,180,208,136,236,162,91,34,8,226,215,117,30,165,204,128,182,186,172,167,13,50,227,200,240,139,183,67,138,251,71,184,51,35,50,129,46,153,250,146,105,227,143,71,206,120,228,141,79,64,46,
23,10,148,0,195,7,45,160,129,196,22,69,44,29,85,17,23,0,193,229,191,218,236,248,7,9,11,196,32,195,13,176,35,241,7,18,180,255,145,244,21,184,255,112,130,224,101,162,253,194,109,175,236,224,7,220,191,120,
44,173,93,196,11,210,98,221,117,11,170,188,160,47,14,246,75,50,228,253,221,82,12,222,248,141,8,13,225,78,227,61,227,186,76,176,248,248,54,131,255,135,185,222,44,254,199,226,152,19,224,0,29,34,84,162,87,
17,244,15,32,197,31,78,91,229,6,21,143,146,208,3,9,32,160,65,152,100,192,4,38,84,226,2,55,184,128,20,232,71,63,68,108,1,9,50,8,19,175,48,208,135,62,8,97,10,116,160,131,46,138,162,182,95,8,255,96,120,32,
60,222,117,0,37,136,23,153,208,23,199,168,94,182,16,241,152,197,96,79,23,132,251,69,247,184,17,46,12,208,44,124,226,203,97,14,215,183,62,29,54,65,135,64,228,161,250,120,64,128,18,180,173,15,104,208,203,
0,16,113,191,11,16,225,105,70,216,31,203,86,7,130,30,132,169,65,68,32,2,19,136,224,196,19,44,112,0,81,145,130,20,110,128,131,24,48,11,109,125,120,129,31,12,64,135,15,12,175,131,209,18,0,34,228,24,45,95,
32,47,80,117,172,214,220,246,72,162,190,169,228,15,45,12,204,11,129,177,18,235,197,96,1,221,88,192,49,196,247,11,245,133,79,136,56,116,36,249,28,57,6,93,56,32,3,4,240,128,30,148,192,132,174,157,64,23,
135,120,162,173,246,183,58,64,130,192,25,84,225,18,14,128,48,137,39,254,193,126,127,144,194,18,63,73,177,26,140,200,22,45,16,192,29,232,112,135,225,209,209,23,28,68,30,241,234,8,139,143,33,194,109,186,
24,94,3,242,192,194,111,81,207,148,44,225,214,56,52,24,13,154,8,73,26,255,56,9,87,22,212,49,134,110,86,114,125,149,116,164,47,190,217,195,49,136,19,17,149,172,164,26,28,160,134,12,100,0,11,98,139,221,
5,254,144,132,11,216,83,148,255,234,223,51,78,73,130,51,196,96,75,180,114,26,16,16,177,68,68,156,192,31,127,224,3,197,178,112,131,52,226,193,4,119,248,128,1,252,96,130,95,122,67,142,116,124,99,242,146,
121,76,227,9,2,4,235,73,143,97,74,9,200,146,168,80,72,129,148,6,34,54,80,135,38,120,243,15,221,68,167,55,103,74,206,151,234,34,157,233,188,233,31,74,224,78,56,124,64,69,50,64,66,2,237,121,207,167,81,193,
81,207,88,2,75,114,5,80,4,8,244,15,243,60,68,61,15,17,65,62,156,141,130,45,240,131,30,34,58,133,63,84,212,162,208,248,160,88,161,161,188,185,200,229,58,20,171,6,223,128,1,169,148,66,67,6,42,244,69,32,
7,25,174,63,240,199,23,57,128,134,26,198,224,0,96,196,180,36,106,248,131,59,197,64,135,90,220,64,23,243,156,138,40,141,32,181,41,166,199,13,185,154,255,149,55,236,41,155,128,232,162,15,17,56,152,30,134,
195,175,57,130,117,131,24,173,163,93,126,121,71,111,224,33,92,214,252,35,48,220,234,11,58,68,64,6,215,244,134,0,103,168,11,21,144,43,175,136,80,131,26,114,192,91,222,254,97,183,129,253,67,94,113,59,134,
28,144,19,17,198,197,43,34,50,224,3,59,252,180,5,55,32,219,97,179,248,7,34,120,137,177,44,107,76,53,104,131,3,4,120,23,1,248,115,26,34,184,232,196,4,89,213,76,47,192,195,193,166,32,15,19,140,22,142,30,
84,155,69,223,104,199,207,110,112,69,45,140,173,163,16,1,169,24,254,130,153,63,90,161,246,184,183,61,75,185,197,92,184,13,238,47,118,43,92,223,34,55,26,184,253,133,59,205,176,2,23,136,13,9,212,157,68,
117,169,130,171,51,244,79,187,143,249,174,119,241,135,63,202,102,17,32,13,114,208,109,14,102,130,43,28,97,10,238,237,224,103,253,84,209,57,158,140,152,192,248,96,31,120,132,158,73,73,115,9,254,109,70,
128,115,212,194,65,234,162,6,66,120,18,34,255,156,224,132,28,56,161,0,5,96,242,147,255,80,0,151,253,130,0,25,48,3,4,156,59,2,174,249,34,139,101,4,83,12,34,235,24,16,48,21,188,224,29,40,98,7,10,102,46,
61,168,5,7,163,232,21,12,224,39,1,248,105,131,30,188,179,29,115,236,7,251,126,240,6,73,101,9,107,249,11,169,184,250,66,86,208,136,43,197,234,90,162,10,140,193,9,186,136,50,164,129,241,228,38,79,250,15,
151,86,238,131,161,44,88,31,248,0,6,79,48,192,22,234,5,16,25,76,34,204,98,198,6,0,31,101,21,104,0,97,158,212,253,131,101,41,17,1,245,250,97,11,63,184,2,140,57,8,86,14,94,20,207,116,252,96,241,4,32,130,
13,176,68,169,127,108,225,163,142,77,18,243,48,35,60,137,130,6,34,235,26,174,58,84,50,211,4,88,242,31,8,192,109,93,72,25,26,76,126,48,182,5,171,131,80,4,96,10,34,16,170,224,100,77,177,48,181,91,14,254,
67,76,12,178,168,102,53,235,34,214,127,104,80,67,225,60,60,55,77,225,7,125,134,47,176,213,86,255,227,248,114,180,163,28,21,0,30,106,240,152,148,54,138,191,44,92,235,56,130,236,158,195,241,97,1,136,60,
28,6,84,224,72,76,110,27,24,25,24,7,164,33,61,220,76,99,154,219,25,208,129,24,64,4,128,45,40,161,94,17,226,67,153,20,154,80,48,33,134,6,254,4,179,64,7,202,230,86,2,132,8,149,56,129,173,183,224,239,56,
142,163,162,5,255,245,49,59,218,231,15,190,128,15,13,207,22,51,86,246,12,0,26,250,23,43,2,50,122,200,243,140,67,234,162,174,89,80,129,2,2,131,201,108,139,28,175,225,118,2,1,196,224,206,134,4,96,4,216,
169,215,97,101,78,119,133,198,0,39,96,226,131,206,119,126,98,13,107,81,126,74,96,177,9,244,0,227,128,143,195,206,246,205,49,48,235,248,65,63,244,97,144,106,189,81,73,129,113,117,66,182,12,24,2,164,152,
47,106,208,128,61,148,64,23,108,103,187,96,71,226,78,111,140,156,202,106,223,118,6,196,240,7,177,0,192,189,66,104,193,86,178,32,131,101,105,158,15,119,207,251,222,157,134,239,73,255,84,34,2,39,8,188,224,
97,28,227,145,32,254,206,122,14,235,49,131,237,94,17,201,65,72,223,9,210,202,92,230,167,164,86,243,235,140,70,68,153,18,16,216,210,251,192,23,223,247,65,200,117,209,237,229,134,60,228,4,8,183,183,167,
140,114,110,59,160,3,166,25,1,194,98,223,7,12,100,33,15,50,80,40,238,15,73,177,60,36,232,137,79,196,74,147,128,6,149,128,4,192,39,124,20,53,120,122,80,124,71,7,95,161,213,18,163,229,7,120,176,1,219,64,
19,209,6,13,167,164,95,209,64,8,132,113,125,61,32,7,220,179,104,37,82,7,60,224,4,25,16,5,204,85,40,238,180,130,233,183,126,218,86,0,4,0,101,37,32,37,0,96,3,35,240,65,127,33,123,183,128,127,10,101,53,86,
35,3,150,133,3,39,134,6,158,67,59,17,16,1,74,128,128,38,160,128,238,101,120,191,134,116,54,6,71,126,38,108,209,82,35,124,240,12,133,36,87,66,198,6,49,4,7,40,224,11,115,128,11,82,167,35,114,224,117,24,
119,56,136,160,2,92,192,83,81,240,255,7,102,240,125,224,87,18,43,88,118,190,0,105,48,248,113,37,176,78,240,103,33,178,224,49,216,161,131,125,112,127,121,48,136,121,112,3,104,176,69,68,72,128,180,147,4,
71,216,2,194,23,45,75,136,20,95,213,18,191,84,20,147,232,89,190,38,95,77,247,65,45,240,120,44,129,35,249,85,82,220,194,108,16,56,134,147,162,12,85,68,67,34,168,77,13,16,47,39,232,3,85,64,18,62,192,122,
127,0,135,190,224,78,220,102,118,190,0,101,186,229,0,14,32,22,1,144,0,54,96,131,69,177,49,120,192,11,17,80,65,245,135,89,180,131,4,73,224,140,140,8,124,193,135,128,9,72,120,122,32,112,23,197,124,153,40,
133,69,81,137,197,232,94,47,144,7,61,112,74,203,16,138,16,71,69,202,64,113,186,0,1,80,82,142,49,17,109,57,226,63,135,147,125,101,35,4,0,0,3,217,6,139,191,96,139,224,231,105,208,192,118,101,215,130,136,
80,0,159,231,139,136,192,3,97,240,0,193,88,131,196,248,65,216,113,140,188,208,2,120,144,132,71,120,2,22,105,255,145,73,40,124,113,182,132,167,113,141,216,24,13,159,197,107,220,24,108,222,40,2,125,32,3,
0,164,30,41,21,72,210,52,50,222,0,1,0,160,84,223,161,45,215,196,127,191,240,2,106,248,121,127,64,6,102,176,143,223,103,6,61,233,143,252,104,126,108,151,139,234,151,135,129,213,87,173,7,3,10,208,1,100,
1,0,53,120,131,197,232,49,13,64,35,11,147,145,25,169,48,27,201,145,73,241,10,198,215,107,31,249,149,195,211,2,89,160,121,138,114,108,66,194,45,253,133,8,234,168,11,99,7,2,133,33,113,5,118,100,136,144,
5,173,72,68,127,16,5,177,88,6,251,104,6,177,232,143,208,32,126,171,151,139,49,72,144,121,120,144,173,55,118,76,217,1,46,176,144,54,40,149,33,212,49,195,163,149,90,25,66,75,56,2,29,153,124,135,167,120,
48,66,71,38,185,1,49,128,150,166,4,25,231,24,19,129,161,3,217,118,74,233,177,86,135,49,48,4,179,43,80,146,57,121,169,11,124,169,11,176,200,147,182,137,8,158,182,155,171,39,6,70,73,144,189,136,255,152,
190,192,148,9,25,140,236,48,140,109,210,141,33,36,44,204,185,5,183,214,111,10,216,149,154,105,101,129,33,86,18,136,1,124,144,24,41,49,104,133,6,35,25,96,3,75,176,79,138,241,112,190,96,134,154,247,28,35,
240,0,151,132,8,126,25,139,191,64,6,182,9,135,187,185,155,170,48,144,192,249,7,125,117,78,99,167,0,48,16,6,162,176,144,81,41,11,2,186,132,4,90,160,4,138,153,5,97,3,215,72,99,155,185,120,137,103,124,209,
210,0,17,144,5,49,208,157,205,132,129,44,209,150,208,224,0,206,32,147,217,130,82,219,227,131,101,115,56,36,146,0,10,144,109,58,208,147,177,232,158,136,240,151,158,22,148,243,57,139,165,167,11,72,185,62,
60,160,0,99,167,11,97,16,6,56,138,163,29,160,144,0,58,140,195,120,26,108,98,2,35,80,164,29,121,26,195,88,164,15,138,103,3,215,164,155,137,7,39,73,3,45,137,8,26,8,82,12,64,56,212,52,14,98,192,112,168,248,
161,223,226,63,4,86,3,175,89,49,188,209,1,151,148,162,110,216,255,147,190,80,5,46,202,166,243,249,7,180,56,144,135,137,159,60,32,78,56,138,8,92,192,5,29,192,163,254,249,0,127,240,1,236,0,149,53,104,0,
23,50,5,136,218,85,122,96,168,134,106,3,31,225,85,97,185,153,149,88,157,196,70,150,124,80,25,14,7,25,199,70,56,231,49,14,62,48,2,130,118,108,23,184,58,219,96,147,101,82,54,24,208,0,9,81,2,81,192,166,59,
217,166,111,170,155,223,39,122,227,39,131,235,52,1,119,10,12,97,176,167,127,32,10,29,240,36,29,16,172,64,154,0,196,122,4,132,122,172,132,106,168,30,57,26,211,9,161,202,71,137,126,208,137,160,73,142,131,
70,82,65,82,121,35,1,7,85,71,142,74,229,24,165,52,25,136,64,48,167,186,1,66,96,3,29,192,3,227,247,7,44,10,159,238,233,170,186,185,122,171,103,159,121,152,159,127,144,163,58,170,100,186,240,0,250,186,175,
46,240,0,99,65,22,100,241,1,2,59,28,0,80,11,127,224,168,156,89,18,137,247,128,35,177,49,47,112,3,53,48,142,159,168,129,214,10,255,13,26,10,122,37,245,24,233,81,102,36,149,125,226,250,2,2,96,162,5,16,114,
64,89,5,100,64,6,110,154,155,181,8,152,219,150,109,182,106,101,96,160,11,1,0,6,51,107,156,9,240,1,198,74,168,136,128,176,94,73,157,129,49,76,129,34,173,131,244,24,43,65,142,147,7,82,49,33,19,225,145,6,
141,80,18,62,96,0,75,64,3,25,40,125,215,20,25,103,88,54,96,87,174,15,128,151,42,26,5,240,233,170,242,57,163,145,6,156,235,52,14,248,170,175,48,2,149,8,251,168,208,112,131,110,235,179,32,105,71,66,16,136,
226,114,74,19,203,66,81,23,96,86,102,6,112,16,181,0,164,90,136,208,3,173,147,80,103,72,48,32,107,162,151,196,178,107,10,148,112,56,163,233,106,171,74,185,62,246,10,13,128,250,11,9,16,179,227,176,182,59,
171,185,192,112,131,112,43,95,192,4,55,18,122,12,21,106,74,234,225,13,143,17,67,20,16,4,129,33,6,47,144,138,130,182,66,205,132,19,225,122,113,168,90,174,96,0,3,35,219,134,59,89,6,64,89,255,6,66,217,184,
145,86,2,117,202,3,136,160,0,120,90,18,162,17,13,53,8,0,48,210,179,159,59,95,176,48,183,121,80,3,221,240,137,108,53,154,149,231,26,37,161,5,29,16,117,112,57,170,36,128,19,52,64,115,117,85,3,135,187,181,
4,224,3,58,144,151,49,170,11,131,21,105,59,165,96,110,9,12,248,250,185,157,73,157,34,233,107,200,19,123,55,0,154,186,64,173,118,43,87,220,170,183,81,177,24,62,240,121,18,11,72,201,144,82,149,225,131,101,
66,48,89,32,4,35,128,184,4,208,134,58,16,167,136,144,10,195,123,152,6,105,188,251,89,175,127,192,171,191,240,0,152,203,188,190,192,185,37,209,179,208,91,40,12,219,103,30,211,137,213,251,63,161,10,77,202,
102,183,18,119,84,133,66,0,2,16,187,225,11,151,23,186,13,225,98,53,104,136,190,13,96,3,46,160,16,39,152,193,128,9,5,172,55,167,50,248,121,244,59,185,208,112,191,208,64,172,237,152,197,206,219,182,157,
235,11,175,208,194,48,82,90,56,152,27,180,55,180,45,100,180,171,150,255,129,216,186,24,81,160,6,163,232,142,205,4,41,102,56,196,232,37,0,0,240,0,48,192,83,237,27,135,187,72,182,136,16,185,34,92,175,79,
50,200,191,112,194,136,176,188,237,88,7,91,156,197,209,0,189,178,224,65,96,188,24,98,92,149,112,177,1,217,9,77,42,3,196,170,107,101,106,32,4,85,164,154,204,230,55,143,50,25,135,148,125,53,128,1,20,156,
0,231,90,2,138,171,10,46,59,191,191,133,191,134,124,200,190,80,131,62,251,197,86,38,45,194,182,49,157,152,5,214,187,79,70,107,180,150,231,13,220,11,35,62,160,0,75,64,195,170,153,40,200,246,55,174,121,
100,27,240,2,71,28,0,97,64,68,227,151,10,132,105,152,244,27,13,79,66,197,128,10,6,179,92,203,236,112,14,7,187,200,192,160,194,207,154,203,75,71,127,24,96,201,219,96,183,121,75,192,222,224,5,157,101,101,
4,128,1,206,64,2,95,74,61,130,38,166,104,72,151,187,97,199,96,160,0,14,192,142,231,215,109,49,72,188,208,48,1,84,76,185,129,161,14,206,107,203,208,128,255,206,92,92,40,165,229,34,157,216,206,191,156,177,
208,0,204,72,27,67,121,208,180,246,140,204,214,35,170,95,138,8,32,232,117,155,135,202,118,156,196,158,64,152,133,233,199,99,96,188,127,112,163,246,235,205,208,16,206,186,224,188,54,96,206,19,141,191,55,
54,60,127,177,21,27,32,56,210,116,198,132,102,183,138,2,13,63,192,2,113,224,179,5,128,207,225,194,173,133,17,77,206,124,181,100,90,67,20,124,199,48,176,2,37,80,126,37,112,159,48,117,167,119,202,208,12,
173,11,152,83,18,225,60,206,59,13,212,158,91,157,160,251,22,189,44,3,11,32,41,205,112,198,203,236,95,172,33,210,46,67,0,36,61,154,217,2,82,43,67,202,165,92,184,187,209,0,21,252,0,10,192,3,97,29,197,73,
137,159,53,189,56,13,13,212,228,220,214,112,11,165,138,135,29,191,115,3,249,71,69,35,21,192,35,81,4,78,13,183,81,80,0,54,162,13,129,228,173,163,204,13,165,172,121,18,44,205,54,144,0,46,176,216,106,16,
214,219,172,11,185,42,78,132,156,175,209,128,255,200,190,192,214,205,139,191,36,73,137,110,65,127,255,91,38,127,59,121,219,210,86,204,22,67,104,16,27,248,235,62,109,165,18,52,193,30,120,103,53,133,141,
94,71,44,219,139,237,0,53,122,144,184,122,167,84,60,118,103,91,40,166,2,13,62,157,191,117,230,65,153,152,81,34,112,140,129,88,189,49,32,177,53,140,84,204,29,87,202,128,104,248,91,218,114,244,40,34,69,
61,141,242,24,31,56,91,42,141,170,185,20,219,46,192,5,48,208,87,74,105,188,185,154,167,190,96,197,133,172,11,224,236,219,135,204,214,191,64,209,112,109,112,138,71,201,125,112,88,116,253,63,120,11,207,
209,196,220,151,23,36,104,192,215,159,155,1,112,96,96,200,192,12,162,76,53,2,132,61,217,253,32,66,32,0,61,13,6,152,51,1,125,69,211,136,0,3,129,236,13,86,172,211,150,203,200,35,161,225,191,16,201,113,251,
135,31,238,203,217,9,64,36,142,198,204,13,196,211,131,8,33,32,1,79,13,212,168,73,8,239,108,165,252,188,18,241,38,64,2,20,174,24,23,205,185,52,255,2,166,242,0,59,142,171,108,62,217,147,59,228,69,110,225,
191,32,209,209,128,228,73,222,18,13,32,2,188,240,225,69,125,119,80,174,61,24,186,204,166,249,11,73,80,204,148,237,3,112,176,1,213,243,76,223,162,13,32,56,227,225,74,162,168,140,216,166,162,227,56,42,222,
200,107,191,17,174,100,149,251,7,68,14,12,233,237,13,54,72,18,95,172,228,129,146,131,245,87,189,124,0,19,87,106,195,113,9,56,178,70,1,42,14,212,98,0,3,93,110,165,56,50,117,2,254,232,135,228,154,5,211,
2,13,128,227,240,162,230,61,90,197,35,140,214,190,128,182,105,187,194,45,81,99,111,93,60,148,188,217,242,189,58,192,220,209,36,174,40,41,193,12,114,80,4,134,78,217,110,72,0,35,48,117,204,140,12,252,228,
232,120,71,187,225,250,32,210,44,0,104,126,185,106,46,225,130,12,239,188,141,8,159,142,8,62,29,234,186,96,234,57,22,201,30,19,123,155,237,228,148,1,229,159,232,86,240,188,212,208,112,2,5,226,237,87,6,
7,125,212,55,51,121,161,97,126,255,119,48,193,44,208,209,0,42,160,2,149,174,227,17,126,236,201,62,225,20,78,217,200,41,160,13,40,146,197,228,239,24,112,88,53,176,234,203,70,226,71,59,226,6,79,24,212,195,
7,6,171,240,191,32,6,128,220,129,207,148,150,55,225,61,4,118,56,234,46,4,193,126,241,149,14,168,74,6,239,157,78,239,190,0,6,88,92,18,161,62,140,7,43,160,250,14,90,106,211,239,188,240,176,36,146,242,84,
26,204,54,44,158,3,140,18,56,143,13,69,64,7,20,64,243,191,160,3,16,64,8,73,149,235,232,209,207,145,1,130,220,112,13,211,198,43,47,128,27,236,174,2,54,80,7,238,126,191,156,222,241,69,126,197,162,222,244,
78,63,14,94,249,200,114,52,40,58,120,3,180,135,245,2,47,204,166,228,209,216,155,142,29,136,8,73,16,2,14,67,246,18,6,1,39,97,186,218,34,82,70,59,224,228,203,61,217,100,75,47,176,9,130,34,0,24,79,172,65,
195,171,229,93,185,202,174,11,114,238,13,248,158,239,129,223,200,208,75,245,135,159,5,150,28,3,240,182,255,248,129,20,77,215,158,104,136,144,7,63,176,165,150,175,11,42,7,7,211,64,2,106,79,30,228,153,58,
159,31,162,18,204,21,164,111,250,61,141,250,172,255,7,128,90,185,224,108,200,175,143,194,229,92,231,163,161,176,253,238,239,245,119,127,249,167,251,35,62,192,35,110,195,75,13,36,204,192,7,82,48,246,197,
15,12,81,80,235,86,173,95,177,21,230,228,187,61,220,3,8,53,27,89,24,47,47,66,13,2,54,54,0,9,9,96,96,15,146,144,127,148,96,127,152,148,9,152,156,157,158,156,139,159,127,35,162,157,164,2,2,13,13,66,45,45,
47,125,24,121,27,50,124,49,114,36,36,32,32,127,186,157,184,186,192,127,108,75,152,12,156,196,108,114,82,33,28,165,206,207,208,152,58,62,4,6,194,36,75,196,198,158,187,187,36,61,114,52,226,52,152,226,11,
130,89,132,127,136,2,35,42,140,142,143,148,149,144,151,153,152,155,162,249,152,54,209,156,164,159,80,9,240,179,170,213,43,12,89,242,200,168,193,135,198,173,92,189,60,225,226,21,44,219,31,6,75,255,182,
113,146,211,231,74,51,127,32,65,82,131,240,226,88,70,76,196,56,117,251,6,110,28,185,63,52,98,252,57,55,168,80,11,68,137,220,49,170,147,160,78,189,74,156,2,216,43,5,192,89,191,82,0,61,161,82,181,138,213,
193,88,27,24,198,160,209,227,15,68,96,17,59,97,77,137,241,19,137,62,122,66,132,28,11,146,0,4,62,61,216,28,211,200,73,45,8,150,225,198,149,27,71,147,208,139,155,170,70,232,92,212,200,81,39,191,206,0,20,
21,117,180,84,40,76,75,155,58,61,152,112,97,45,57,86,41,238,194,212,171,242,86,148,127,82,166,36,129,198,196,29,10,127,134,144,29,93,202,135,24,56,36,60,157,244,196,230,173,85,112,114,98,187,132,73,163,
110,33,67,56,81,233,229,43,184,47,96,125,130,59,49,250,115,248,211,8,27,167,6,170,98,101,144,241,44,169,84,127,97,85,217,13,43,136,97,41,143,117,146,177,229,3,233,239,206,116,136,129,1,89,123,102,182,
106,49,193,141,59,215,220,2,25,53,109,10,193,153,243,248,34,70,189,27,225,235,255,52,88,84,255,127,122,9,180,28,115,134,192,130,144,44,12,53,244,208,85,89,105,133,21,27,216,101,38,10,31,82,220,241,7,104,
224,101,200,73,6,98,16,144,130,76,18,134,200,86,48,44,129,115,134,56,237,213,86,3,58,24,220,54,95,110,237,232,101,223,125,188,5,247,71,127,253,20,134,137,140,2,37,198,156,43,47,180,120,96,84,53,252,49,
85,15,12,242,66,153,146,212,233,130,157,54,108,97,18,195,9,159,105,104,101,39,166,25,32,83,122,231,49,128,30,39,184,244,96,34,123,180,153,195,7,139,183,221,53,31,83,61,202,232,230,155,112,242,216,35,83,
47,54,103,96,58,127,60,23,195,2,114,32,41,93,68,214,57,8,161,69,23,121,226,133,145,39,132,176,195,149,140,254,161,3,4,16,88,35,138,49,95,170,7,91,92,47,209,6,19,77,131,164,147,133,33,119,221,180,38,83,
137,244,104,234,169,137,13,248,99,129,66,102,177,193,115,124,212,226,144,159,12,118,67,153,117,106,13,154,221,39,75,196,16,1,51,141,54,90,133,15,16,152,176,203,174,255,39,105,196,229,107,151,202,21,219,
31,113,157,35,200,171,132,164,25,234,139,47,146,170,45,169,216,174,10,234,83,9,189,186,226,2,124,44,224,80,106,86,65,164,149,131,192,64,56,204,51,108,164,113,130,71,193,6,107,6,20,112,232,1,162,70,218,
20,42,225,100,127,136,41,112,121,14,65,235,210,2,8,47,64,109,181,45,126,27,106,43,16,183,50,31,196,222,130,218,71,31,55,180,152,14,130,12,33,44,78,159,233,254,57,17,69,169,61,168,171,121,158,240,65,37,
5,31,213,219,168,24,115,248,81,222,164,157,64,168,75,152,3,59,4,89,56,51,143,179,226,180,157,10,41,100,31,14,23,93,224,83,26,35,148,144,44,142,33,124,36,173,19,221,252,214,200,214,57,9,97,52,75,240,33,
2,5,116,180,236,50,163,90,192,49,135,9,49,160,171,154,151,109,249,34,48,56,152,196,134,105,56,98,186,247,243,171,157,122,138,80,171,66,103,172,116,22,127,164,179,129,44,68,174,88,238,56,80,155,45,53,46,
169,25,110,181,90,154,149,146,181,8,119,208,241,245,215,255,65,192,225,129,9,50,160,171,25,70,148,102,51,140,55,136,15,188,243,206,208,6,92,213,166,9,255,188,34,221,116,3,30,46,235,116,47,244,115,185,
229,78,21,221,68,136,171,91,138,173,78,154,244,140,27,104,252,192,178,215,147,55,138,194,28,118,220,33,131,106,152,173,182,164,122,37,94,234,182,51,116,37,44,173,234,216,99,127,166,245,182,139,35,102,
238,189,228,30,181,122,234,225,154,89,118,206,119,98,196,13,38,0,91,124,241,51,204,64,71,31,17,106,151,17,49,41,181,6,58,206,151,174,237,140,192,227,216,147,0,23,176,167,132,13,176,123,125,250,158,217,
210,5,38,241,49,73,50,184,170,159,51,122,245,43,14,236,64,3,239,131,223,10,130,96,7,60,132,40,68,247,235,10,38,108,214,192,181,153,240,116,162,16,147,233,78,8,27,22,22,14,113,94,89,32,187,170,214,46,144,
196,96,11,138,194,4,6,51,56,185,21,204,1,102,122,224,131,191,154,23,165,91,149,208,133,152,48,97,39,88,136,51,241,193,16,76,165,64,28,192,104,88,53,236,112,105,255,87,157,112,67,30,138,96,65,30,102,48,
8,16,248,195,10,224,0,7,58,228,1,101,34,98,77,68,196,231,66,37,154,110,137,72,122,163,19,253,145,187,25,210,112,82,88,68,73,12,146,240,131,20,120,209,139,65,224,4,4,224,96,7,63,88,101,89,155,163,163,19,
163,167,194,128,137,162,142,228,35,77,248,168,232,46,128,97,70,20,94,88,30,5,252,248,199,78,98,2,14,48,187,3,31,32,131,197,251,117,34,27,196,104,208,34,155,184,72,6,66,111,100,33,145,226,205,106,117,157,
171,157,242,146,158,72,67,4,174,128,137,69,121,210,147,90,24,100,7,229,208,154,60,150,18,25,250,83,201,42,151,185,204,144,201,208,23,178,164,162,48,152,7,141,244,52,131,120,191,252,163,24,196,224,195,
59,228,33,61,232,67,159,106,150,176,44,201,48,147,153,13,132,161,212,102,73,75,138,184,235,93,184,156,224,31,240,64,175,108,218,147,19,196,34,164,31,248,208,154,114,230,241,124,158,203,85,147,216,121,
206,101,82,177,138,254,252,167,39,182,97,140,27,20,225,158,16,255,237,4,4,130,185,130,15,68,64,136,141,59,223,7,77,130,197,201,28,244,156,235,196,149,201,108,233,56,66,57,227,140,24,138,168,74,125,64,
70,8,204,225,14,104,136,65,57,81,130,191,141,222,82,66,203,58,168,78,219,245,206,153,154,148,166,209,88,94,47,85,74,84,76,136,1,140,150,51,64,31,104,48,83,154,254,180,20,216,177,228,39,34,56,66,119,73,
40,127,240,140,39,72,164,112,5,13,72,160,168,96,253,131,24,32,48,70,177,41,181,108,136,228,232,83,229,9,141,127,186,149,87,209,160,194,31,164,96,141,175,134,245,174,99,29,36,242,238,16,129,178,29,107,
156,53,181,136,66,211,118,83,194,162,209,126,54,61,233,31,44,116,215,198,74,52,8,65,88,195,10,236,64,7,60,228,225,22,154,49,38,42,55,75,26,206,54,110,173,213,20,226,15,56,225,85,199,154,246,15,19,133,
192,12,230,224,129,15,248,225,6,104,1,193,96,81,105,191,193,158,82,156,197,56,101,17,159,42,135,60,68,192,26,190,140,195,105,135,251,7,45,104,161,114,107,64,65,255,10,238,224,135,152,146,32,171,53,189,
173,96,55,75,93,218,70,215,31,121,132,76,18,138,0,26,187,18,247,187,168,37,43,100,125,72,89,61,224,161,15,163,148,45,26,241,55,93,246,86,247,146,110,45,226,31,168,16,3,223,22,225,14,139,242,163,119,193,
11,222,32,204,96,5,43,248,47,242,232,96,0,63,68,32,15,101,123,46,8,127,122,221,12,145,83,14,124,64,131,8,244,64,129,69,125,149,147,252,205,240,39,86,128,130,227,121,128,178,119,48,129,8,250,128,134,81,
42,24,177,160,213,234,66,217,64,5,8,163,65,10,63,136,92,126,255,160,129,11,106,248,198,157,136,223,31,226,119,60,22,176,192,14,41,248,192,29,12,160,7,17,28,248,49,191,224,21,57,59,193,128,244,64,200,8,
105,136,112,31,164,80,132,43,112,109,7,59,144,192,126,113,204,229,82,204,160,195,29,102,1,107,83,176,3,58,208,225,14,119,184,130,30,252,32,133,8,144,88,33,180,136,149,156,249,32,131,60,160,161,15,17,160,
114,149,63,195,1,58,96,89,203,90,238,178,160,65,140,2,230,57,176,192,3,31,150,0,153,203,108,102,58,80,64,200,104,54,128,164,209,28,130,207,80,128,101,93,195,242,5,1,45,220,65,123,218,31,29,238,132,143,
89,112,0,68,31,192,14,138,78,65,10,82,173,233,29,44,26,203,100,6,52,160,255,176,229,79,219,58,36,163,30,245,1,118,109,135,82,151,26,213,113,144,181,4,132,27,135,78,223,250,216,141,242,192,174,149,253,
135,93,11,183,214,200,142,118,189,88,208,108,76,120,160,19,208,150,182,182,73,163,236,110,255,129,217,219,14,183,184,199,77,220,3,144,59,67,129,0,0,33,249,4,5,0,0,127,0,44,12,0,15,0,195,0,204,0,0,7,255,
128,127,130,131,132,133,134,135,136,137,138,139,140,141,142,133,76,121,143,147,148,149,150,151,152,153,154,136,68,131,73,127,17,131,161,135,53,155,166,167,168,169,170,138,8,135,82,127,39,160,161,125,127,
89,130,50,165,127,185,171,188,189,190,191,137,105,173,8,56,8,8,104,82,82,104,55,127,49,110,130,12,132,49,53,165,114,36,130,49,192,218,219,220,136,64,135,195,173,127,173,105,56,104,68,70,105,49,49,215,
135,36,61,52,127,114,114,221,245,246,190,64,8,223,130,64,253,131,226,228,210,148,35,34,35,205,25,62,124,98,244,232,1,98,80,195,63,239,104,200,89,72,239,158,197,139,152,246,9,106,149,207,152,176,143,56,
128,224,32,178,12,77,30,62,121,242,212,88,96,141,16,27,16,47,65,208,232,49,136,68,59,140,56,115,238,107,85,140,95,191,126,197,136,16,1,50,20,135,81,131,234,214,41,229,83,3,97,13,92,27,112,177,108,247,
240,79,67,155,130,158,229,220,186,77,163,177,98,33,137,10,53,122,244,12,21,55,110,188,168,245,50,104,137,34,16,112,255,65,192,99,42,67,6,13,137,11,73,84,253,195,134,171,95,96,223,68,18,19,139,195,224,
25,35,103,159,177,117,20,237,79,99,199,143,5,45,81,26,99,166,77,184,131,216,220,252,203,121,146,191,63,63,65,235,3,42,80,160,155,189,208,14,49,88,13,141,117,235,213,174,97,71,150,75,35,6,31,107,215,250,
118,222,109,72,227,198,192,131,252,253,20,121,244,236,226,66,141,147,67,150,205,188,121,180,230,144,11,45,153,71,93,239,75,42,16,121,107,15,14,250,155,49,125,68,142,162,77,228,188,188,249,243,178,29,35,
34,161,116,34,33,154,219,49,230,203,199,221,39,81,145,2,141,164,53,132,190,252,18,183,146,253,177,4,108,3,46,215,95,128,239,157,17,195,25,61,232,21,31,78,226,0,55,220,112,2,25,151,218,32,172,249,247,159,
128,255,117,232,225,135,32,126,120,222,122,36,200,113,70,69,15,94,164,207,104,63,9,133,31,98,130,176,181,216,121,33,122,200,8,27,186,241,197,215,135,28,14,152,30,108,134,200,53,207,25,103,128,112,77,15,
40,166,248,75,255,96,19,226,71,197,90,24,190,198,156,135,57,18,98,211,149,88,102,169,37,86,132,132,8,93,100,146,129,160,160,66,131,36,169,100,47,23,76,152,6,98,138,49,224,197,99,206,241,8,81,150,11,213,
105,231,157,19,81,52,207,157,13,110,182,99,135,208,29,2,130,109,124,208,224,231,153,170,92,208,93,63,249,185,177,97,106,113,118,40,8,157,118,82,183,167,165,150,74,52,143,166,114,220,37,209,93,118,94,217,
214,127,95,74,39,7,66,214,156,129,168,42,77,34,144,134,133,132,104,248,232,59,124,86,74,93,173,117,230,137,100,158,158,246,218,233,173,125,98,229,99,160,93,158,42,3,31,170,174,122,202,112,174,34,230,5,
128,82,178,38,105,118,180,150,104,41,174,89,238,85,213,149,185,254,202,171,175,186,10,75,42,115,134,76,199,7,26,124,40,171,137,154,175,254,113,92,180,141,117,88,45,146,68,214,186,165,75,13,229,27,23,33,
70,210,154,23,9,159,254,138,87,157,92,142,155,94,33,36,156,33,3,14,217,168,75,73,63,105,190,248,36,114,228,62,42,200,255,174,20,157,248,175,168,130,22,82,101,143,134,220,196,237,174,51,93,155,87,143,195,
130,249,135,130,130,224,224,112,35,223,68,12,68,133,239,70,203,97,77,185,242,57,167,32,249,10,136,136,202,135,60,250,146,85,53,249,171,231,93,123,54,40,89,202,96,186,193,71,39,47,55,18,113,179,90,169,
23,168,91,54,241,137,229,31,85,223,204,95,172,177,1,89,9,165,189,130,170,180,128,228,22,98,132,12,104,68,141,136,162,23,20,229,44,114,203,89,153,245,157,91,55,242,156,122,173,25,152,225,133,64,103,86,
244,66,101,131,218,101,202,133,96,231,178,219,220,201,188,166,90,5,74,105,183,209,193,110,182,33,128,64,254,56,32,211,113,102,222,119,34,251,66,84,103,175,132,211,4,2,226,106,51,94,8,105,79,190,251,220,
106,22,143,220,103,144,63,51,96,176,237,253,117,94,158,34,0,210,90,248,76,86,49,93,72,67,233,70,13,55,213,27,190,14,217,134,186,221,205,113,95,31,67,106,187,143,183,19,56,229,176,156,203,230,150,216,209,
73,215,59,60,52,44,176,0,255,233,36,24,108,72,241,74,206,135,0,220,221,85,88,229,235,182,91,25,42,151,85,61,214,215,127,32,60,203,52,136,184,3,186,218,233,212,243,208,136,172,166,178,135,68,228,119,166,
75,27,207,208,151,190,11,68,168,89,84,128,22,252,124,214,175,119,228,137,126,228,105,142,255,252,103,187,151,248,11,43,122,9,32,129,168,7,130,233,13,139,128,137,240,157,82,144,214,3,54,156,176,16,11,72,
145,62,198,161,168,126,52,203,117,173,217,144,145,26,68,176,118,64,203,37,104,131,221,18,0,8,187,151,12,81,47,112,121,199,17,67,56,68,93,45,228,116,52,40,161,16,209,147,67,119,248,174,108,130,96,195,193,
6,17,143,248,4,230,2,53,116,85,235,192,6,59,29,57,239,38,75,184,159,247,54,55,196,211,77,47,46,62,106,72,22,48,208,135,23,188,192,15,2,16,128,31,132,208,130,62,242,177,5,47,232,67,22,74,1,187,203,96,38,
123,98,147,224,33,144,84,56,122,104,209,53,101,98,160,95,232,179,190,224,136,209,93,20,139,31,209,184,37,44,254,244,143,255,141,68,236,144,92,54,208,135,22,228,113,143,129,196,0,6,158,66,141,92,180,114,
3,89,120,65,11,132,32,4,61,10,33,11,61,128,13,0,57,184,197,2,169,204,130,119,169,140,166,130,8,38,248,112,102,134,132,8,207,171,28,69,55,159,205,73,75,13,249,161,122,106,132,63,189,44,0,3,66,240,131,31,
90,32,200,13,252,193,83,127,24,31,56,185,8,170,187,12,162,6,27,16,194,8,70,208,130,44,212,200,57,93,114,7,35,125,197,144,23,34,10,8,124,88,19,27,106,86,196,103,86,206,42,123,73,14,27,219,216,161,30,212,
0,3,122,108,1,6,188,57,62,241,137,79,16,15,141,225,67,13,209,171,111,90,166,22,166,188,229,242,72,128,59,98,189,176,47,22,148,3,101,36,18,66,238,253,161,7,146,252,11,62,95,149,35,248,65,43,91,2,114,163,
246,166,247,191,211,1,240,15,216,20,194,11,168,225,208,24,66,52,156,61,141,232,68,35,26,206,66,196,195,108,215,20,65,3,48,192,81,1,194,174,140,81,106,139,232,58,85,155,202,204,195,158,130,255,144,131,
12,120,227,42,18,188,143,64,147,26,153,131,44,182,52,31,217,68,136,127,120,65,3,132,128,129,241,13,162,167,69,133,235,57,23,33,81,183,10,226,46,165,152,201,2,98,169,4,26,20,82,132,2,141,103,118,24,73,
25,171,152,20,34,41,197,73,62,210,224,85,138,101,113,78,61,132,203,199,2,104,164,205,97,244,5,182,112,107,22,98,184,11,135,38,98,23,139,240,212,68,73,23,206,26,188,64,4,24,176,30,108,180,168,35,220,149,
117,176,181,17,95,54,92,8,73,157,68,40,56,44,253,26,72,63,232,195,114,137,178,124,171,161,65,41,187,89,84,134,54,133,16,62,93,0,104,77,209,197,187,46,68,16,89,88,106,9,75,152,203,142,22,40,114,86,58,105,
108,43,99,216,195,38,246,30,46,51,130,11,155,57,169,80,5,72,131,0,116,35,9,178,0,200,44,120,19,162,202,53,196,113,233,122,9,159,142,179,6,93,92,64,11,70,144,133,153,154,212,151,133,128,199,248,98,192,
18,153,22,162,97,16,250,131,120,127,8,201,172,61,147,104,219,203,33,255,76,54,215,131,13,204,242,6,49,220,128,79,223,91,84,65,240,129,179,192,232,98,57,39,5,130,26,168,115,3,255,139,95,108,46,39,85,240,
133,47,33,45,244,145,75,16,124,143,125,44,152,110,88,19,25,90,80,211,163,9,47,129,61,178,124,65,56,189,137,206,159,22,162,120,76,17,196,74,150,171,11,75,52,55,174,186,192,47,13,74,97,36,19,55,128,163,
82,236,30,216,2,68,56,2,35,205,192,130,163,113,55,156,36,205,104,96,45,187,206,196,144,40,225,178,4,26,220,160,1,152,109,114,148,55,188,213,137,42,249,15,197,83,110,124,157,12,195,39,91,180,185,62,93,
8,66,251,203,0,41,30,54,72,72,250,230,58,228,96,232,66,44,238,30,185,141,149,207,54,195,37,245,244,69,136,67,220,208,90,57,252,7,92,80,131,17,31,46,234,146,75,225,211,71,248,25,134,165,254,166,170,197,
73,52,62,74,113,131,151,83,153,139,23,192,93,236,102,197,34,143,195,241,206,194,74,52,29,45,173,178,12,232,1,6,20,218,228,82,108,181,46,76,78,68,170,247,255,204,220,194,29,98,124,121,141,110,127,31,153,
101,193,250,12,30,243,240,114,119,11,97,38,192,40,248,89,91,30,196,115,231,84,149,87,127,104,1,65,142,114,167,5,177,129,34,55,66,162,75,78,117,38,158,28,190,69,172,196,83,7,109,193,20,161,202,55,156,117,
153,164,50,198,200,171,112,232,235,147,210,228,50,45,181,29,155,135,88,131,89,14,242,206,50,136,10,58,183,250,238,14,75,180,180,154,56,181,188,9,17,15,241,197,163,6,236,125,234,161,5,151,213,240,73,68,
203,246,112,25,21,62,102,230,144,229,38,86,4,109,115,58,105,81,10,88,14,34,226,117,225,180,189,229,12,226,100,99,162,222,167,190,171,46,234,13,145,26,140,128,186,91,148,76,99,112,164,93,2,215,186,182,
190,72,195,32,92,214,88,73,131,20,97,189,110,139,143,123,112,3,182,202,249,211,236,134,10,197,25,177,236,120,111,162,227,92,84,196,46,102,50,229,30,44,96,4,11,40,244,16,161,14,68,240,125,120,38,1,239,
74,86,85,51,41,131,243,107,141,67,164,65,44,95,176,128,255,13,96,224,206,55,143,138,226,29,1,111,61,175,36,227,128,102,68,115,139,76,130,188,222,178,163,64,107,76,67,24,249,77,107,228,29,24,68,72,200,
142,220,97,240,131,243,236,112,109,164,1,54,251,144,97,176,19,194,155,80,121,132,158,59,108,228,250,30,213,156,184,87,53,34,204,89,3,99,238,180,208,35,23,220,60,43,3,220,66,72,221,23,221,110,204,105,46,
118,182,42,137,146,1,52,144,165,123,23,170,115,66,148,162,149,114,222,121,177,47,158,147,187,188,151,155,52,45,179,33,168,83,85,148,255,66,234,226,31,79,118,235,135,178,5,212,241,240,213,55,4,206,159,
50,9,208,62,190,18,65,215,125,37,240,43,190,10,191,32,181,39,164,72,146,193,6,20,81,126,159,103,4,188,224,50,226,7,32,198,196,51,123,225,33,238,39,4,125,96,115,176,100,11,106,71,9,174,164,11,179,55,9,
104,135,10,248,53,116,130,39,4,50,192,0,28,197,26,186,241,67,32,213,41,218,246,121,171,144,7,199,103,117,89,151,29,130,163,112,105,68,2,118,132,1,89,144,255,131,141,128,115,241,71,118,119,230,115,138,
112,84,168,48,121,227,195,7,152,37,119,241,34,85,143,5,62,74,1,102,9,232,39,154,135,48,135,146,105,211,145,5,108,101,115,135,199,110,241,55,118,17,55,9,56,16,95,25,200,21,120,21,106,53,32,0,185,68,86,
235,65,85,205,64,3,44,136,10,121,112,6,252,68,34,146,6,19,133,150,7,126,144,133,182,160,74,127,176,1,124,216,131,157,22,21,149,224,83,215,71,9,110,149,127,63,119,123,120,246,7,2,176,57,112,114,33,58,98,
76,180,230,6,181,133,29,167,144,82,179,113,82,64,148,26,54,149,7,45,32,2,156,166,135,140,128,115,186,48,118,64,56,87,75,134,127,188,16,15,233,114,23,11,240,97,50,48,2,214,35,105,73,8,31,235,80,36,116,
119,10,210,52,60,152,120,13,22,243,99,3,194,7,34,32,2,22,8,93,121,72,8,238,37,127,217,135,11,99,135,8,203,181,113,141,32,132,204,181,118,212,96,114,32,247,2,79,197,8,2,70,107,142,120,10,73,32,102,124,
147,35,4,115,122,28,82,255,62,61,32,4,13,112,3,204,64,8,89,56,8,124,168,131,204,24,134,202,118,127,206,200,120,218,240,129,52,160,80,64,2,32,67,228,24,223,83,85,4,214,111,169,128,26,154,36,110,198,116,
130,193,35,108,34,240,127,72,96,140,208,133,83,132,192,4,126,184,85,19,119,115,233,82,145,137,72,123,242,86,138,134,200,11,31,184,1,47,144,75,37,36,85,208,114,21,230,164,141,182,102,10,17,36,105,5,55,
110,110,160,70,154,81,62,127,176,77,24,176,144,133,96,11,195,184,135,127,0,145,56,137,8,237,118,115,207,166,100,220,199,27,83,22,95,22,150,119,110,241,67,155,167,104,49,20,146,167,208,54,136,208,23,168,
129,70,49,181,4,11,144,77,170,212,78,134,96,147,198,200,4,149,176,140,48,68,123,16,85,138,223,52,143,168,96,103,16,85,142,40,70,130,214,134,51,16,149,13,39,153,9,41,25,37,0,130,25,79,249,31,36,128,1,13,
64,108,181,176,142,131,128,135,236,248,151,204,88,108,202,134,120,200,69,150,218,32,62,77,145,11,52,176,1,225,99,255,97,213,213,8,240,64,96,140,22,56,150,192,114,14,65,151,50,232,128,112,97,97,128,212,
2,14,137,1,66,102,8,56,200,151,123,200,135,242,53,87,217,135,92,200,181,11,98,89,123,169,240,97,31,118,127,26,184,135,139,217,2,108,196,8,244,224,83,111,105,10,45,23,50,190,86,77,52,64,75,118,228,153,
127,160,80,161,89,147,134,224,77,166,153,8,68,38,150,117,245,156,158,5,84,49,4,141,169,208,120,199,37,62,27,80,97,26,216,2,105,169,132,210,20,17,218,200,148,170,80,76,123,114,19,11,55,101,107,21,72,197,
233,153,170,116,120,126,153,131,164,169,133,126,168,100,206,185,18,122,22,84,61,21,62,15,181,145,129,136,103,27,88,90,133,151,106,66,48,32,13,49,144,0,25,153,227,115,58,154,224,148,229,66,8,243,144,29,
56,50,119,12,81,142,124,116,156,159,169,74,22,58,8,55,153,156,54,119,8,61,249,151,246,137,152,202,213,74,14,21,62,247,198,138,143,199,123,251,247,86,240,118,100,30,246,162,212,208,7,125,144,33,185,104,
8,62,37,255,158,167,160,50,15,250,155,113,113,13,13,32,8,196,153,86,125,233,144,200,89,11,60,233,94,27,202,142,131,200,83,53,135,95,33,122,159,248,245,14,35,186,0,13,50,101,82,102,9,165,70,106,143,0,114,
24,240,152,21,103,40,154,224,141,124,209,47,155,103,76,250,232,24,11,144,71,199,153,161,234,88,164,68,90,8,202,233,161,69,198,83,56,183,14,19,215,20,50,48,71,238,69,162,162,165,138,240,49,101,132,8,150,
174,249,89,232,68,104,60,86,163,217,32,7,187,169,9,70,210,107,102,42,25,48,169,2,147,224,151,26,106,164,112,90,154,58,103,154,117,129,108,49,128,3,117,161,16,12,2,62,61,0,74,110,119,111,53,208,102,118,
65,157,244,85,87,130,250,93,63,88,10,24,48,93,228,197,113,13,195,99,147,160,160,81,229,16,53,177,52,28,146,166,127,32,4,134,16,154,108,122,8,121,232,142,175,183,147,200,26,21,159,90,23,56,160,32,92,185,
5,38,48,5,31,224,2,212,26,0,35,224,7,125,80,93,36,32,3,49,16,21,172,104,152,95,185,255,108,130,202,140,18,169,11,237,70,119,185,152,155,11,128,171,141,32,5,69,48,8,47,152,171,152,153,137,63,246,2,42,240,
2,180,100,8,158,153,110,125,9,138,12,169,149,236,38,159,90,184,169,202,202,48,50,128,4,208,58,5,91,176,5,126,80,8,0,48,173,29,224,2,126,112,6,133,230,94,86,10,137,138,112,113,173,169,110,96,135,125,184,
144,5,37,20,97,81,149,35,177,21,131,147,128,128,29,51,175,93,2,23,11,208,0,2,0,172,130,96,142,133,16,164,25,234,158,136,144,164,56,201,135,155,26,113,27,16,3,55,32,2,63,240,3,38,0,173,34,240,7,193,24,
140,120,100,142,126,48,2,6,240,1,41,208,1,76,80,104,45,32,3,6,85,111,102,169,154,91,250,105,215,71,127,95,151,5,124,240,55,241,228,65,61,160,42,9,74,153,127,144,7,23,240,10,127,160,182,140,0,23,227,118,
122,49,177,1,2,48,172,125,180,158,125,100,71,197,217,175,241,41,8,56,184,161,238,197,4,76,176,179,50,192,4,65,59,180,34,160,4,73,144,4,232,136,255,142,125,16,1,125,36,2,126,96,2,38,160,7,122,48,5,83,144,
2,31,128,98,114,48,72,158,149,92,64,5,160,227,74,159,172,164,100,162,200,131,175,71,104,0,25,63,98,91,17,81,244,8,239,122,35,101,2,31,208,3,17,114,225,178,48,59,8,183,27,172,66,42,154,136,208,183,182,
224,77,55,192,4,56,192,4,225,193,4,64,43,180,34,16,1,104,32,3,121,112,3,17,112,2,82,16,140,209,43,2,206,43,163,34,48,185,6,32,173,46,160,7,0,227,7,133,82,40,184,20,150,159,187,115,160,197,131,165,251,
112,89,64,113,101,164,67,136,224,83,172,181,9,105,244,30,68,51,187,86,81,3,182,91,8,249,90,8,66,214,71,128,196,187,233,104,140,27,74,188,55,96,20,82,240,3,91,240,3,82,112,3,204,27,1,38,16,2,31,176,3,41,
32,1,18,96,5,18,96,7,86,224,1,86,240,1,38,160,4,72,160,4,35,240,1,83,240,7,71,240,1,55,176,4,125,128,4,211,0,2,26,102,150,62,229,50,46,179,181,157,118,125,203,120,108,235,70,255,195,157,118,3,49,208,155,
135,160,27,93,52,153,147,224,149,136,96,58,13,49,187,152,249,163,63,138,187,180,148,187,250,91,8,170,180,144,235,56,140,237,153,147,72,128,3,73,16,180,63,240,7,55,64,4,55,240,10,15,12,193,116,176,3,96,
156,2,17,92,193,86,48,7,43,128,5,116,224,7,55,176,5,6,224,2,127,96,2,119,128,4,114,113,3,76,225,118,155,37,157,214,135,3,174,132,11,53,252,8,117,49,129,80,181,61,208,82,163,53,250,22,184,9,183,32,85,187,
2,112,196,46,123,196,132,144,196,51,123,183,133,224,196,54,27,154,77,140,197,105,176,5,33,96,192,9,76,4,69,187,3,18,192,1,31,240,197,160,44,193,18,112,0,30,224,1,43,192,2,130,176,2,107,96,180,45,160,4,
126,48,5,209,122,4,120,240,99,45,48,13,39,133,179,214,87,23,235,166,120,190,12,196,133,176,85,232,200,143,216,85,163,244,16,15,133,140,9,72,210,128,60,83,121,146,250,163,42,96,196,143,140,191,186,203,
166,237,9,138,204,0,184,68,32,5,7,60,255,5,39,112,176,33,64,1,20,192,1,229,204,1,59,240,7,59,160,1,41,240,7,18,224,1,127,192,2,30,128,5,65,176,6,51,0,1,43,240,1,177,176,5,39,112,4,122,96,2,30,96,0,12,
16,3,45,160,141,25,249,105,4,235,149,194,236,161,222,212,188,253,133,54,16,253,24,0,98,78,92,99,182,141,48,52,239,225,204,114,129,1,54,32,8,2,48,205,138,184,200,137,160,196,105,37,100,195,170,135,66,22,
188,90,252,3,87,240,3,73,128,3,69,144,2,227,252,1,20,160,206,26,160,1,165,28,7,7,112,0,131,128,2,40,48,3,107,16,212,90,208,6,34,240,4,107,176,5,73,112,5,127,48,207,79,192,0,50,128,195,11,192,199,132,160,
140,183,224,8,125,248,94,16,185,1,16,185,85,72,192,136,55,99,63,218,181,50,16,97,209,104,70,59,187,26,36,52,240,163,35,48,8,31,189,200,32,237,200,214,44,8,107,10,72,108,138,183,2,92,192,46,141,6,69,64,
1,227,12,198,59,64,206,28,160,1,238,124,202,7,192,2,44,224,211,65,240,255,7,51,240,7,80,160,5,65,208,6,127,128,4,18,176,2,91,128,7,31,0,5,62,0,1,83,176,4,16,137,3,237,86,190,151,0,184,128,201,110,76,128,
194,145,97,107,67,67,15,245,146,9,81,136,25,215,128,25,176,189,0,42,32,0,138,200,214,209,60,205,211,76,210,191,122,187,38,221,219,76,28,188,70,145,212,87,128,4,122,61,206,228,76,8,233,252,7,28,240,7,58,
29,207,138,253,7,40,160,5,130,160,5,141,13,5,80,96,0,63,96,5,41,96,2,87,176,6,22,96,1,16,160,4,124,160,192,158,170,208,60,105,154,166,121,147,22,24,184,232,200,135,92,153,147,209,240,16,71,201,47,22,164,
42,163,186,9,15,49,59,114,97,21,52,209,3,22,72,219,179,237,209,179,221,0,184,77,205,141,176,166,161,201,157,195,75,4,155,124,2,122,205,1,33,160,206,127,80,211,202,45,216,238,124,216,135,189,216,51,16,
4,16,160,5,30,78,221,214,93,6,30,176,5,90,96,1,41,160,7,86,240,221,100,176,2,90,141,194,49,236,147,199,250,187,58,169,255,213,89,189,147,113,122,8,55,16,139,109,40,15,217,65,214,188,35,110,14,1,31,19,
58,172,2,254,7,4,78,224,132,0,215,138,96,210,124,148,147,17,128,4,123,253,7,73,32,5,87,112,220,53,13,198,28,192,1,58,29,7,44,48,3,40,128,5,51,48,3,242,28,4,31,14,226,141,29,230,116,0,1,22,176,6,41,16,
0,109,80,5,100,96,226,56,160,4,129,11,123,93,136,169,123,200,4,73,58,140,89,0,184,55,9,184,122,94,11,55,208,7,250,24,47,148,121,13,62,158,8,47,69,98,166,7,2,224,74,219,130,112,228,32,29,233,248,155,191,
48,43,100,180,84,204,82,192,215,39,112,2,229,28,2,203,13,234,127,160,1,18,28,7,166,46,207,43,224,229,138,189,225,101,222,6,141,13,1,51,0,5,107,160,230,224,253,1,86,160,3,223,109,1,39,128,4,225,156,147,
117,17,232,125,232,183,129,174,231,196,254,144,196,254,222,130,224,188,201,50,171,49,104,171,134,240,9,200,145,35,30,212,119,252,178,11,146,138,8,144,30,233,211,124,228,70,94,255,233,70,14,179,73,252,
179,34,16,2,17,126,1,87,112,0,95,64,206,228,172,1,129,45,1,166,206,229,246,236,225,100,174,5,16,240,7,29,254,225,16,0,1,137,93,5,85,240,7,22,128,235,118,240,1,4,96,1,109,96,1,30,128,3,34,240,222,238,45,
218,162,221,231,128,222,231,16,79,236,182,144,142,125,78,8,233,136,1,161,96,160,105,86,112,148,112,40,85,178,67,162,83,52,22,120,237,139,64,205,146,206,200,213,188,219,192,170,83,161,176,5,28,112,5,137,
251,5,232,62,225,87,142,211,59,192,229,88,144,243,86,64,7,79,176,2,101,240,7,43,32,6,29,222,6,66,207,225,106,110,6,22,64,6,58,144,1,58,80,0,29,16,6,81,160,226,17,192,193,129,43,8,58,169,231,57,232,240,
92,201,12,92,143,197,122,190,184,55,80,241,92,191,184,127,64,11,123,131,32,166,144,139,60,214,223,86,17,15,54,8,0,131,96,3,36,143,237,148,46,8,147,78,205,50,123,187,26,101,2,127,176,201,109,115,0,93,32,
243,67,192,1,67,80,206,55,239,255,1,79,112,4,6,204,193,39,240,1,130,0,1,109,144,239,249,254,7,107,32,6,102,208,239,255,174,3,127,176,244,127,144,0,222,221,6,100,128,5,115,30,184,165,173,147,89,159,236,
201,222,245,169,143,142,24,0,246,174,191,184,180,48,200,150,149,132,217,193,32,59,248,62,206,180,67,59,170,52,96,10,172,215,78,242,115,159,8,180,237,200,40,207,237,131,64,11,122,112,7,87,32,5,73,240,5,
127,240,5,50,223,5,202,221,247,28,128,248,91,192,4,232,56,245,74,0,208,81,16,5,112,0,1,112,176,2,43,240,253,254,94,5,62,144,249,155,175,3,10,240,0,80,31,5,100,64,6,76,16,1,233,136,142,89,48,255,56,117,
3,173,159,255,217,236,158,250,15,8,24,127,24,24,55,125,135,135,72,55,36,127,127,12,75,143,12,141,141,75,141,36,103,103,61,147,147,73,155,155,149,141,146,127,149,108,127,114,52,168,127,52,36,32,52,170,
13,9,147,42,141,42,179,42,117,179,158,186,141,2,127,13,42,191,193,127,189,47,34,38,31,116,33,104,69,40,127,255,7,141,95,26,20,33,28,33,33,91,76,50,17,91,45,221,38,118,109,109,107,107,43,30,48,127,4,58,
22,22,102,85,22,127,58,241,60,48,0,5,22,81,5,83,72,72,127,76,55,55,130,0,22,26,8,176,224,32,128,127,248,97,72,212,136,95,194,135,17,84,253,1,33,41,146,163,70,165,254,48,58,163,209,211,13,93,124,118,137,
52,197,168,213,31,77,34,107,229,178,53,178,215,176,151,13,124,241,26,129,65,132,30,58,20,174,160,161,160,225,192,179,47,113,164,77,251,241,7,205,13,37,86,176,180,248,211,66,192,154,54,16,60,120,176,98,
197,195,26,119,141,170,252,89,167,35,67,60,0,141,20,128,9,163,128,73,18,34,72,48,100,33,100,16,96,218,125,252,250,192,77,232,240,79,196,132,47,34,188,64,242,162,197,11,12,49,46,50,200,184,41,35,74,70,
186,172,108,146,49,106,228,164,30,114,228,76,156,168,201,85,163,58,117,118,217,218,252,39,87,75,94,195,4,208,252,115,135,206,157,34,104,168,253,65,209,44,90,181,34,127,136,160,249,241,164,141,255,133,
17,195,20,100,240,97,1,66,138,14,138,215,68,121,87,197,204,59,174,58,10,168,4,51,203,133,89,198,105,233,194,221,71,119,47,94,189,124,245,222,109,81,183,225,210,23,140,43,178,1,165,43,178,70,16,158,2,123,
90,32,106,36,9,200,146,77,169,162,81,3,243,31,204,153,51,111,226,172,178,115,173,206,35,169,48,2,110,125,124,144,2,29,31,72,113,194,14,171,205,208,204,31,18,112,64,20,14,56,156,240,4,22,100,144,17,70,
3,54,68,161,195,112,62,184,144,66,85,43,216,86,197,137,22,240,102,1,1,4,132,209,200,47,2,168,0,128,18,69,124,244,66,35,130,52,114,215,11,55,54,146,87,143,63,222,245,199,94,121,93,55,201,71,142,89,114,
24,122,142,133,148,164,70,240,53,146,201,36,177,232,119,217,125,154,1,200,146,74,92,110,9,224,82,116,144,134,198,36,51,56,248,140,4,20,156,0,4,14,127,152,144,2,22,235,76,208,128,0,241,168,19,226,31,192,
97,1,129,59,40,174,147,65,24,9,228,34,196,48,179,76,17,194,67,75,77,255,18,129,18,79,110,34,228,141,66,110,210,199,36,108,84,164,203,123,141,78,162,158,39,228,53,18,31,35,140,160,52,18,126,88,58,182,146,
150,185,216,96,3,0,13,8,49,194,7,119,24,144,199,21,7,176,16,68,51,62,73,240,3,17,56,16,65,68,4,34,28,129,5,1,54,248,82,64,157,58,80,213,65,10,48,64,208,142,5,234,248,153,64,3,45,8,210,227,48,38,80,144,
233,182,73,190,32,10,147,156,118,148,233,71,155,54,54,158,39,241,89,114,146,168,127,84,160,75,126,246,197,91,170,149,89,202,40,68,3,96,221,113,7,26,119,176,128,130,131,118,216,113,128,182,33,201,192,38,
14,55,136,208,0,6,66,8,160,0,178,48,192,16,70,7,205,186,195,149,135,5,12,201,99,35,131,190,244,132,9,141,36,218,205,36,34,51,181,84,55,137,114,123,45,27,132,121,18,42,74,45,103,58,30,8,32,32,182,137,28,
61,208,144,243,36,238,182,219,243,147,248,5,13,239,125,61,131,21,83,2,119,76,97,130,12,33,176,112,192,28,115,64,40,193,31,124,132,255,20,3,71,124,200,176,65,22,89,8,33,68,29,94,125,168,128,196,85,193,
33,134,25,58,248,144,65,9,5,156,147,227,95,50,53,34,129,30,147,182,16,83,35,74,48,202,173,201,158,116,252,135,8,125,148,34,120,167,187,72,22,179,39,50,176,139,81,37,53,67,230,178,206,174,232,247,179,187,
21,84,222,40,189,147,216,87,65,102,119,127,160,199,31,121,124,48,199,1,118,176,96,135,4,59,244,65,133,12,87,187,33,3,38,11,44,48,200,31,66,240,16,79,1,46,116,160,123,7,115,192,1,193,10,43,192,129,5,15,
29,44,188,193,36,247,222,232,38,221,180,55,239,252,222,36,143,28,114,11,66,96,64,17,36,135,111,194,136,225,35,125,148,110,99,141,128,123,243,38,40,85,176,199,249,123,248,188,73,207,147,111,11,198,31,239,
219,240,192,7,189,200,96,192,1,83,75,160,63,5,170,167,241,7,38,152,136,65,236,178,48,36,12,216,128,7,10,112,129,11,18,96,131,35,220,193,10,80,91,193,57,206,17,128,6,44,32,11,53,24,146,6,91,240,185,207,
53,255,207,111,28,243,218,221,160,71,50,166,148,2,18,23,249,4,121,112,214,40,155,165,112,50,238,57,9,150,246,240,134,55,164,47,125,186,176,220,250,42,199,195,30,242,208,103,15,80,65,177,108,32,2,63,228,
97,10,18,72,129,254,118,176,3,109,81,193,8,80,204,132,38,100,215,136,26,108,224,5,35,16,128,13,18,0,128,17,76,193,0,41,152,202,84,172,208,129,0,24,160,5,27,216,64,6,175,197,65,15,124,206,37,153,26,20,
8,159,148,178,80,20,134,101,186,80,92,163,58,37,190,5,184,66,143,127,120,67,35,4,169,11,28,110,194,144,134,204,161,249,254,192,133,85,241,96,4,69,68,131,20,80,199,129,106,76,227,15,80,52,130,70,72,128,
41,217,209,224,130,27,16,66,11,70,0,0,27,108,193,4,38,120,2,234,158,144,130,20,252,193,0,91,248,131,236,172,184,137,23,92,97,14,122,72,153,0,26,32,2,95,244,114,19,35,228,152,243,98,18,76,79,80,171,81,
134,209,68,246,72,24,187,73,144,32,118,66,72,36,33,107,56,200,63,156,207,154,255,215,20,9,250,110,152,62,65,214,33,1,48,72,64,17,139,226,1,158,104,96,8,20,248,1,26,140,144,6,35,80,225,15,110,64,204,39,
223,179,128,26,188,160,15,13,51,129,16,148,112,130,35,84,242,9,26,104,229,7,76,64,46,43,102,97,82,67,186,195,28,76,80,71,96,22,19,152,147,136,201,189,6,69,204,23,221,45,101,75,168,148,46,50,42,174,63,
44,179,17,78,154,4,225,54,65,69,148,184,34,154,141,104,194,36,168,185,210,26,10,210,165,48,109,41,76,5,217,4,5,252,33,1,96,112,128,2,94,96,2,36,228,33,39,33,184,2,81,6,64,4,4,248,15,158,255,147,12,35,
220,208,3,55,44,64,107,50,16,4,6,152,64,132,63,132,96,26,88,165,128,9,152,240,135,192,108,13,3,247,92,202,66,231,24,81,63,220,173,162,147,232,229,47,133,160,48,175,121,141,118,34,100,202,46,88,22,51,23,
38,41,164,27,37,140,31,229,163,9,81,77,96,18,77,80,169,96,7,73,200,64,86,211,49,42,253,131,74,193,192,133,181,101,193,15,125,200,255,67,68,6,48,128,11,36,97,0,127,184,0,175,254,240,196,51,232,140,4,76,
141,1,9,98,16,3,131,61,149,66,21,250,129,53,14,245,135,31,156,0,7,70,40,237,214,254,130,129,6,148,110,18,35,136,137,31,140,217,128,222,242,242,172,47,250,101,243,42,26,204,165,28,14,143,30,133,158,101,
40,225,152,63,158,196,21,47,192,156,98,3,75,93,234,42,118,186,212,157,64,117,183,123,221,196,58,160,43,35,224,3,18,100,192,24,41,52,2,179,39,32,42,16,210,64,5,18,176,208,17,151,184,68,12,170,118,6,10,
49,1,7,72,216,194,15,84,251,135,34,20,33,9,105,56,67,105,243,112,131,191,96,209,116,120,232,5,110,134,177,219,63,52,24,142,50,25,225,110,99,34,220,23,89,88,174,34,13,215,71,71,178,220,112,85,66,158,61,
16,21,13,110,20,88,79,36,22,176,221,5,108,137,83,154,226,70,252,181,17,78,136,199,26,24,128,7,25,16,65,10,152,61,239,31,42,11,4,35,120,193,13,147,105,234,25,128,108,132,144,164,129,66,253,96,211,101,255,
251,11,27,216,112,100,192,76,1,171,1,88,64,135,62,152,160,193,155,240,195,110,123,33,0,8,199,205,193,19,182,168,67,253,144,168,19,98,4,143,44,11,85,163,92,41,18,80,136,175,17,177,219,43,6,112,56,129,58,
39,118,12,127,61,241,38,78,60,134,38,104,87,23,127,253,235,24,216,22,15,11,44,33,2,17,64,24,102,41,75,217,11,92,128,77,94,248,49,205,52,178,132,30,240,97,200,153,68,128,166,27,113,129,73,12,160,8,230,
141,129,43,54,64,136,133,224,225,77,38,144,130,30,64,150,164,221,54,88,97,47,153,4,150,127,169,48,17,136,0,55,156,36,193,35,68,162,230,142,58,166,61,25,86,151,46,168,152,5,48,212,185,206,127,64,118,178,
143,205,236,23,47,219,217,201,94,118,180,27,161,134,63,168,161,208,120,96,130,182,153,112,1,70,55,250,2,8,208,100,248,208,67,17,170,97,50,13,237,212,52,2,254,0,132,204,102,150,178,84,251,100,13,106,208,
135,191,228,193,15,83,1,217,170,177,44,18,63,8,192,15,91,224,183,172,29,220,255,136,6,99,217,4,25,68,15,3,222,236,9,152,61,41,15,192,190,20,73,39,97,153,159,53,98,12,187,192,51,180,93,188,241,145,228,
0,30,198,153,67,37,216,164,227,78,107,214,157,79,156,244,68,150,64,2,39,181,91,36,64,104,55,175,4,60,9,134,245,1,13,6,152,195,7,98,89,240,5,235,226,202,109,10,122,47,176,140,86,145,8,32,48,110,14,151,
46,54,156,130,200,142,116,23,2,12,9,187,234,32,232,73,140,225,234,88,199,248,213,63,254,7,173,55,34,7,99,224,186,213,197,254,7,39,52,34,90,49,104,65,54,218,109,242,78,3,129,10,145,166,2,8,78,8,130,74,
196,192,87,68,184,0,16,218,222,105,118,199,124,77,2,206,224,66,238,121,106,15,152,224,148,4,103,181,39,64,230,7,197,135,198,19,255,30,137,9,122,73,24,134,135,239,242,224,27,9,99,62,49,145,82,212,172,17,
243,109,196,20,105,241,98,140,255,129,236,147,200,65,181,177,110,117,145,152,222,19,199,226,77,10,150,176,5,10,177,189,17,237,118,167,164,217,80,119,72,255,128,130,8,127,191,189,222,219,29,115,28,4,152,
15,179,237,131,33,166,76,129,34,50,62,232,144,103,112,35,28,191,9,46,247,91,0,45,96,68,204,4,55,9,241,213,253,73,45,99,92,70,108,134,87,56,171,192,217,57,80,125,250,215,159,254,178,147,16,246,104,179,
64,21,206,80,8,146,227,222,248,112,119,67,123,41,177,132,254,107,50,230,236,246,7,235,54,9,123,199,110,232,22,24,92,243,23,9,51,34,63,208,75,38,0,97,62,55,125,94,22,107,89,22,121,186,224,111,125,64,110,
102,38,18,33,134,17,73,98,0,34,97,121,178,83,126,66,208,4,237,247,117,5,144,49,186,176,126,78,32,118,168,7,99,147,96,118,78,96,118,199,98,1,100,144,2,110,128,4,84,133,90,108,210,78,84,32,7,103,160,84,
227,193,6,94,32,110,186,160,119,153,245,114,198,215,8,76,144,5,255,16,1,6,96,5,215,112,74,32,67,125,35,64,125,158,128,101,174,86,112,94,38,0,15,216,7,140,67,56,232,65,24,33,166,125,79,130,6,186,198,92,
201,245,116,53,176,255,87,18,161,0,31,71,118,42,152,1,127,144,1,78,64,135,95,119,130,158,112,130,102,71,118,37,0,15,42,66,3,27,160,109,6,3,82,129,145,53,140,65,2,149,146,81,94,64,5,56,0,4,3,56,128,4,248,
114,127,32,3,218,54,136,50,144,48,172,84,4,198,128,27,2,23,116,85,232,133,23,88,125,147,208,101,165,216,38,4,5,10,98,8,46,76,194,10,150,215,102,73,226,10,124,224,71,159,244,7,53,144,5,111,32,118,78,144,
49,120,184,9,102,231,113,167,231,126,45,232,9,37,176,54,98,112,15,54,200,0,105,148,13,129,193,58,160,147,7,166,224,6,32,224,6,44,227,6,70,240,136,234,134,0,38,231,119,127,128,90,219,198,4,27,32,3,74,64,
7,79,0,106,168,232,24,94,40,138,142,129,101,46,97,2,87,168,101,35,96,0,171,160,46,115,151,17,25,1,2,154,80,51,175,232,9,120,224,8,157,130,92,162,39,75,33,101,25,53,0,6,47,56,18,51,248,139,192,24,131,57,
192,139,5,0,1,241,48,28,31,176,4,106,132,124,33,209,255,7,164,21,3,114,64,90,114,192,6,156,4,2,84,112,100,217,168,110,49,215,119,217,144,137,55,32,3,121,160,4,31,240,4,6,96,107,168,148,36,15,136,133,187,
192,111,91,230,96,2,160,7,126,32,42,26,200,123,201,181,116,219,82,9,17,167,11,2,68,69,147,176,0,42,48,6,58,48,9,4,224,3,78,249,7,62,144,36,51,8,140,31,183,139,188,232,33,91,97,1,45,192,0,89,176,1,52,128,
1,11,176,1,213,194,7,234,17,3,53,195,73,177,101,84,217,8,128,76,88,137,150,120,3,247,133,7,31,224,1,59,39,2,136,39,147,233,8,26,35,241,96,6,231,133,38,144,129,224,34,9,39,116,143,36,244,57,10,23,130,154,
82,46,178,148,108,75,25,15,127,96,6,155,64,135,98,16,149,147,144,1,189,56,149,50,88,0,100,215,144,102,231,21,98,96,153,25,0,45,27,176,4,24,84,79,243,214,7,126,32,4,121,32,7,115,151,51,129,65,4,50,96,84,
143,152,119,23,48,38,176,137,3,153,152,13,76,16,1,116,96,5,41,96,2,74,208,255,120,79,210,11,138,87,133,219,18,138,126,32,3,158,103,71,175,248,145,153,242,1,148,130,152,167,176,0,179,40,17,56,210,4,93,
17,15,80,160,21,123,67,0,78,224,157,41,168,130,167,55,135,117,88,0,112,16,5,232,25,5,25,208,7,12,48,111,53,160,22,243,246,7,9,230,7,120,176,1,121,112,80,17,112,3,85,149,4,72,112,1,217,0,155,150,232,15,
55,80,53,120,64,7,30,64,7,147,215,120,38,240,80,139,135,45,237,56,125,16,122,129,49,217,38,255,102,150,147,65,56,117,181,114,186,16,4,81,51,9,231,16,17,131,49,148,147,112,10,52,16,18,169,144,65,55,21,
99,142,89,6,80,224,9,45,250,36,44,98,149,10,249,7,188,8,7,143,137,14,5,64,0,37,176,6,5,32,0,32,16,150,245,148,70,225,40,164,19,101,151,74,144,4,39,0,151,0,106,137,89,64,136,124,0,141,6,26,38,69,116,133,
153,82,156,51,89,156,90,166,133,10,170,101,168,228,7,114,80,18,231,114,121,203,169,46,27,22,125,33,106,71,30,232,94,2,233,255,73,182,104,139,231,231,21,62,80,6,101,240,36,159,217,8,81,160,11,9,89,0,51,
218,8,37,160,3,58,202,3,60,96,7,112,112,158,10,176,1,61,224,158,168,64,3,40,153,70,243,182,1,20,98,48,184,201,164,89,144,7,225,152,137,122,144,2,118,128,160,90,246,7,17,40,121,172,54,147,252,198,106,89,
170,133,87,214,0,126,48,2,100,86,51,158,71,30,228,193,36,61,160,136,153,55,18,98,64,26,240,53,10,232,65,10,25,97,30,85,179,30,47,208,88,119,90,5,47,58,9,115,170,11,98,80,167,186,144,1,49,58,131,189,168,
3,54,74,0,42,104,7,46,16,15,150,41,0,57,83,79,50,80,3,124,128,173,106,84,3,50,144,5,228,165,109,0,106,159,225,136,124,44,41,21,119,112,101,162,218,40,159,24,147,198,137,138,159,234,115,167,170,7,170,201,
114,226,231,9,45,3,72,4,39,18,4,144,0,22,193,0,131,17,108,112,86,157,155,80,3,92,16,99,89,193,157,147,144,33,80,25,149,80,48,171,144,233,9,62,0,5,62,80,172,160,73,255,0,48,182,139,127,192,3,141,160,83,
118,192,3,195,17,5,37,208,0,49,192,0,114,32,3,100,153,7,159,148,173,121,64,94,56,80,90,104,128,6,144,42,142,6,96,7,48,144,2,6,224,7,198,48,129,23,40,112,237,186,45,168,58,147,34,128,18,115,151,92,97,10,
67,242,1,67,79,167,11,14,96,171,130,185,76,70,185,152,110,170,6,25,112,167,236,240,7,193,106,167,79,9,5,87,187,9,101,16,167,78,249,153,200,154,167,46,246,7,99,131,39,97,0,3,37,48,28,22,208,6,1,144,7,75,
128,143,36,48,111,217,74,94,223,138,3,67,118,6,104,176,5,81,8,173,71,112,101,167,170,179,53,249,115,208,211,96,87,182,8,218,135,171,158,224,170,0,251,36,208,2,95,143,48,180,218,163,10,129,129,173,70,153,
65,10,112,44,91,49,9,87,155,33,85,64,153,127,192,157,114,26,186,101,64,6,95,107,153,222,185,139,213,70,182,158,160,0,192,193,3,16,0,178,4,208,27,0,16,89,52,240,165,103,217,3,103,144,6,218,64,27,18,32,
21,86,64,255,7,6,144,160,238,248,126,239,7,73,89,52,121,243,248,147,202,219,112,30,200,45,58,192,175,154,64,10,163,48,82,217,106,139,149,91,7,5,128,149,127,80,6,102,48,172,155,128,176,39,210,8,237,112,
34,39,242,181,141,192,34,122,106,109,25,235,9,231,48,49,10,132,14,22,80,2,112,16,15,37,32,191,60,128,5,48,128,191,88,176,191,82,49,21,79,48,80,168,100,2,122,128,27,214,183,151,89,152,175,123,67,192,87,
8,152,205,187,188,218,83,9,73,235,24,4,240,182,117,215,180,228,129,24,212,25,159,179,36,59,14,224,21,159,171,21,144,233,189,153,75,190,90,65,194,229,59,177,155,144,130,127,200,3,19,0,3,208,198,5,187,211,
1,46,0,3,1,144,0,118,160,6,242,43,191,131,10,60,252,203,191,86,240,191,74,163,160,35,48,192,52,121,192,3,183,133,36,4,50,168,90,3,42,151,184,187,64,2,253,71,56,28,240,36,58,176,1,11,215,24,115,7,193,162,
39,7,212,73,53,109,8,103,89,192,5,125,26,5,225,91,5,34,156,149,31,204,255,157,228,11,153,158,139,163,42,136,64,54,53,9,97,192,5,141,48,49,48,28,0,1,240,0,29,240,7,0,16,0,99,19,49,17,51,70,255,123,4,238,
42,192,11,6,50,196,185,55,72,140,192,79,114,170,141,215,2,95,218,192,152,247,24,37,65,56,138,41,18,58,240,1,146,208,3,164,112,171,143,33,25,166,9,181,245,164,2,30,235,33,224,187,9,235,240,185,232,105,
167,119,250,148,179,138,14,206,90,2,106,192,194,113,188,9,10,112,203,127,240,0,185,236,34,15,80,195,9,192,69,170,162,42,6,96,3,83,48,192,83,48,5,54,48,204,122,48,192,147,240,128,138,220,111,219,210,120,
168,154,7,185,22,171,78,60,110,196,27,5,149,208,3,255,154,197,28,85,25,84,212,134,84,180,0,47,0,3,5,224,193,226,59,9,81,249,14,159,235,9,81,160,54,98,96,177,176,92,0,178,188,190,27,135,203,155,192,5,96,
176,207,96,224,2,251,156,0,1,240,1,71,112,4,0,64,208,5,61,204,200,220,8,157,170,208,209,12,205,159,184,11,187,100,0,66,32,255,90,108,16,189,73,187,143,127,224,5,219,242,14,90,236,81,52,211,127,165,128,
18,40,90,69,177,83,3,42,96,153,31,242,185,62,240,177,100,240,176,237,12,15,41,221,8,197,10,203,24,75,66,186,220,8,191,252,203,31,0,0,60,205,211,6,48,204,197,242,7,30,20,212,196,187,45,128,59,121,2,112,
3,224,146,116,116,37,108,172,48,189,224,35,7,207,208,40,22,16,0,12,176,0,156,44,126,157,146,51,213,43,75,150,177,0,45,160,0,233,176,148,239,16,5,164,251,210,47,253,33,109,12,203,177,156,186,34,81,203,
92,64,199,220,162,42,96,49,9,68,13,121,89,148,69,69,13,205,165,232,133,75,1,42,120,164,114,200,101,87,17,252,36,238,192,0,239,65,56,157,66,31,178,115,173,174,208,134,89,160,2,105,91,104,75,57,9,38,140,
181,231,203,148,109,61,9,10,208,113,249,172,11,96,16,11,142,81,215,184,181,208,213,103,218,138,108,147,35,244,111,159,131,41,80,76,110,49,100,205,127,192,1,51,176,209,91,233,10,210,11,144,140,208,76,214,
155,255,65,245,212,171,97,227,152,91,65,6,151,173,158,153,125,190,51,168,130,47,54,1,181,204,72,141,242,62,34,177,42,119,221,40,128,75,66,193,228,18,255,38,0,120,64,3,75,109,180,221,183,73,222,173,11,
44,144,41,62,224,0,162,0,193,67,11,46,61,16,103,220,218,166,178,84,3,13,112,44,217,73,28,151,45,211,241,204,148,101,39,158,147,208,113,205,189,215,123,83,196,234,74,92,119,195,101,93,230,7,53,32,42,253,
231,81,77,237,76,156,180,188,25,65,20,220,130,54,19,1,197,182,10,185,20,87,69,215,186,193,23,20,6,49,22,54,127,144,33,102,16,226,234,204,34,154,77,207,214,22,104,209,150,103,100,219,223,240,115,211,34,
33,218,141,64,218,70,221,204,69,29,102,188,208,91,162,49,2,47,208,56,16,44,56,11,126,18,185,102,225,147,96,132,206,11,0,146,128,222,51,163,134,178,104,139,25,228,219,53,32,4,15,19,54,62,96,198,114,218,
8,79,41,207,243,156,49,75,187,223,73,226,226,34,193,211,165,18,212,211,45,11,186,0,97,61,75,255,66,189,112,55,102,53,39,187,196,7,162,82,180,200,213,56,31,137,209,123,19,15,221,253,125,204,133,18,124,
224,10,244,33,17,109,8,6,160,153,54,8,219,8,91,203,34,206,250,198,155,240,98,53,165,186,94,158,203,158,0,221,55,197,199,86,50,230,155,112,215,166,184,9,122,77,188,5,172,101,162,209,0,47,176,4,33,65,175,
73,226,156,35,53,197,36,68,0,2,176,4,52,208,127,229,118,171,158,87,173,85,131,87,177,179,1,15,128,172,241,32,226,154,171,5,90,48,171,22,235,172,127,176,229,123,13,227,147,32,227,171,82,212,5,12,61,46,
225,111,190,208,101,168,250,170,99,136,92,9,190,11,24,61,222,208,163,3,106,192,0,159,197,234,131,153,17,174,112,136,35,93,210,47,160,0,81,144,14,102,64,153,90,219,176,197,26,207,224,249,36,54,37,215,147,
64,199,15,208,232,155,192,69,153,1,22,165,52,18,168,237,9,249,78,221,160,145,91,89,228,71,218,183,224,135,211,224,34,65,5,87,80,212,58,224,45,61,80,110,1,143,71,239,65,3,135,56,255,113,126,164,2,231,252,
33,179,122,241,51,173,238,250,61,9,44,252,36,238,254,36,117,61,68,50,142,233,153,82,221,232,72,129,11,218,101,89,224,156,220,167,11,232,17,228,178,141,6,83,253,126,58,144,3,146,96,25,13,175,188,16,95,
79,158,64,31,24,144,0,44,162,158,25,144,238,98,0,1,16,128,190,37,176,180,19,176,229,19,160,177,171,251,241,206,173,11,194,238,9,245,78,233,36,239,223,70,23,26,115,114,170,24,16,189,133,225,76,227,150,
107,79,189,11,87,128,2,51,79,66,58,176,149,25,148,224,44,51,134,147,225,10,25,12,103,169,112,65,96,208,167,160,57,211,52,138,190,27,235,0,14,208,244,180,236,108,10,0,245,47,174,11,0,32,236,86,143,236,
0,30,184,155,234,111,34,0,0,45,128,10,118,165,61,54,19,228,69,187,9,181,242,5,69,109,135,162,64,225,157,7,210,162,151,178,166,89,3,124,30,59,24,32,238,134,126,250,177,172,190,129,166,177,158,141,245,124,
92,233,254,189,239,129,251,111,126,96,3,6,238,10,248,200,107,145,235,255,24,101,63,53,8,159,246,55,223,41,81,76,25,112,95,53,241,169,17,113,230,48,168,175,247,187,192,220,170,203,217,207,223,8,130,223,
8,144,190,9,133,223,8,54,80,7,135,207,45,11,54,32,153,178,101,5,62,2,162,63,10,136,113,56,42,215,224,158,236,9,73,192,32,88,239,33,160,16,113,209,254,240,81,151,53,180,56,69,11,48,2,49,138,190,244,252,
135,23,7,8,106,19,19,10,19,127,135,135,92,127,10,136,138,136,143,144,144,9,0,145,127,54,149,152,149,35,127,155,155,143,35,160,136,38,135,2,126,126,2,2,122,53,52,61,32,36,75,75,127,108,108,143,32,182,135,
36,36,32,149,12,127,20,153,192,152,58,58,148,32,61,12,177,108,32,108,176,127,177,127,52,49,49,124,124,11,49,136,11,11,53,42,5,78,106,5,223,127,106,135,134,19,60,127,60,231,143,140,153,15,136,9,9,96,145,
0,0,9,149,148,193,193,158,159,152,155,126,38,126,26,232,249,179,74,215,161,37,179,18,210,186,245,39,215,159,93,145,188,244,57,144,175,34,162,97,127,255,22,64,98,8,34,86,15,26,209,168,101,4,217,35,163,
182,4,14,212,148,80,163,198,193,152,63,14,30,157,51,4,204,221,35,155,192,40,217,171,184,47,152,0,139,127,70,129,106,96,194,4,6,62,52,72,48,131,133,48,225,33,134,185,12,66,242,114,136,195,1,138,64,131,
89,176,208,225,143,28,103,79,109,205,138,69,162,135,156,144,34,161,129,164,145,205,134,19,30,19,156,76,112,9,183,46,77,72,142,14,225,212,11,73,158,188,76,117,240,245,3,250,179,34,170,6,126,244,140,232,
67,114,153,50,90,152,162,234,218,245,236,145,20,20,89,45,14,203,211,171,22,195,202,114,164,81,171,113,136,6,180,108,53,108,56,112,160,96,140,131,185,230,204,177,91,119,211,102,222,189,192,118,242,188,
20,108,148,128,81,192,74,1,244,51,226,5,201,90,149,72,252,233,17,245,86,231,63,157,209,236,192,154,57,159,14,2,202,149,31,108,122,104,214,161,51,210,166,85,83,75,34,219,6,21,118,99,167,171,196,104,246,
94,48,127,179,214,169,200,59,159,128,77,191,43,161,42,255,213,192,134,141,44,31,61,180,139,119,145,184,82,86,46,206,33,210,89,26,119,176,80,157,69,22,84,145,64,103,75,244,130,16,34,9,237,18,154,120,227,
29,148,13,13,35,8,2,151,122,149,112,161,192,108,149,196,167,27,38,243,61,82,95,37,47,234,83,24,36,251,161,50,130,0,47,44,208,3,115,76,45,4,217,35,146,49,84,73,17,18,236,240,160,69,81,100,128,1,36,23,18,
248,76,15,224,81,211,97,105,36,208,176,193,31,77,156,168,37,12,40,182,135,23,36,123,173,120,36,34,160,248,231,95,112,156,8,133,72,141,168,248,177,156,53,75,116,212,148,119,218,213,137,224,143,135,48,160,
39,3,104,208,49,38,80,58,100,16,9,45,78,85,102,86,70,215,200,33,135,118,108,45,64,3,6,90,70,234,229,34,37,130,249,72,60,241,5,19,227,33,161,140,96,230,166,154,116,194,102,155,106,117,228,144,44,206,100,
216,80,67,14,65,214,89,47,189,240,113,71,10,28,252,89,145,5,58,116,85,18,3,32,48,240,21,34,174,56,99,86,52,215,88,83,218,142,255,108,213,80,3,24,14,112,241,128,137,10,112,17,70,151,137,60,146,233,33,215,
34,34,216,60,160,130,210,19,140,164,252,212,201,8,1,129,34,128,8,142,50,183,20,119,24,42,195,42,115,15,65,7,150,188,135,72,177,3,7,191,216,154,207,86,45,244,210,67,156,12,252,232,238,18,140,70,179,64,
53,49,176,242,17,91,27,44,32,64,179,21,20,194,37,23,208,254,129,147,34,142,192,215,23,80,160,186,24,74,38,168,60,114,95,3,13,220,135,74,11,72,201,209,10,51,10,61,226,198,67,146,73,5,73,116,33,24,169,239,
173,22,68,145,40,192,168,34,210,12,34,32,29,108,236,114,11,247,144,133,54,117,112,81,7,24,209,82,108,98,181,24,235,245,192,123,28,31,2,64,199,155,116,12,137,183,55,54,80,230,8,27,144,80,195,142,221,41,
244,163,27,14,5,9,89,101,157,201,240,131,4,55,3,106,1,1,30,173,202,36,36,11,31,220,225,142,31,149,183,138,16,38,130,1,109,211,207,82,60,181,197,238,224,4,207,31,217,6,67,15,184,104,114,189,95,153,255,
66,88,83,195,100,142,201,130,167,45,49,11,120,144,130,206,196,240,3,7,54,199,189,47,174,1,56,67,131,158,243,62,66,139,114,31,197,144,205,222,200,54,170,81,2,39,134,49,117,225,206,30,142,184,239,127,236,
212,248,31,219,110,171,105,168,196,217,208,181,0,54,16,135,65,15,178,79,198,50,158,97,189,171,220,50,206,32,3,73,12,34,112,160,129,233,128,70,161,3,30,10,106,223,243,231,101,129,36,141,53,26,189,41,160,
237,35,36,16,6,23,240,61,59,53,24,187,39,142,8,24,98,74,146,137,241,46,10,149,183,38,167,60,1,84,174,7,171,136,147,51,230,228,20,72,4,233,32,207,65,132,28,240,64,135,90,129,47,43,62,208,193,6,104,0,17,
232,84,198,103,13,25,150,193,164,113,136,24,24,67,71,126,235,1,6,108,96,63,254,61,160,126,248,211,216,254,134,119,136,197,221,3,24,31,227,196,0,77,96,131,201,9,160,5,89,160,1,82,90,37,11,55,8,236,117,
217,121,160,188,94,117,8,42,224,225,14,247,250,67,233,46,24,140,97,232,160,255,36,143,48,223,35,16,178,139,97,133,71,26,229,9,33,72,196,150,141,44,140,32,112,247,131,33,124,214,40,195,123,216,208,106,
151,120,28,140,60,165,67,174,221,72,0,94,187,154,16,142,22,61,101,56,6,33,110,120,89,217,222,197,28,93,200,44,79,143,64,131,1,82,64,197,234,224,10,14,215,0,157,44,62,104,168,179,132,135,15,135,224,155,
162,62,242,161,5,172,80,1,130,123,225,253,48,5,143,82,198,195,106,151,202,196,166,62,229,31,59,222,209,15,0,24,129,16,48,160,163,143,136,101,122,179,16,164,3,15,52,25,165,208,11,18,104,184,2,220,44,216,
72,139,248,32,131,115,192,100,207,214,230,58,54,192,206,146,178,227,67,36,55,153,139,218,45,96,3,89,192,20,61,234,193,198,53,154,242,155,53,212,22,241,32,193,74,229,121,171,135,53,226,225,7,26,64,75,182,
44,39,78,142,241,14,100,94,166,75,86,33,104,25,22,250,224,33,220,182,131,41,22,19,40,184,162,3,38,181,227,193,159,125,46,147,208,148,38,9,137,86,72,100,49,135,6,89,255,104,193,8,30,160,187,0,212,227,155,
147,160,199,55,183,201,209,171,209,131,149,158,250,212,215,66,138,163,211,44,64,14,29,49,198,45,9,212,57,68,52,199,73,51,251,131,12,138,160,1,184,253,211,145,98,208,129,159,42,17,139,15,118,16,74,224,
249,162,4,191,194,28,78,142,81,133,2,0,128,11,74,9,31,120,0,128,127,78,237,232,54,109,240,209,114,82,181,128,247,41,147,127,26,16,68,190,237,8,115,241,116,138,157,58,119,203,76,120,97,166,59,176,233,77,
29,105,1,51,24,64,57,120,210,94,101,62,8,165,47,202,238,26,36,56,3,52,162,210,10,182,52,106,3,43,164,234,55,253,227,209,139,74,181,170,229,60,167,83,101,137,129,85,248,213,150,63,99,67,192,240,68,80,123,
54,7,123,102,229,67,17,40,160,214,181,86,167,10,85,16,195,29,148,201,54,176,60,131,80,136,8,106,120,74,168,87,190,77,230,171,124,91,0,8,172,244,130,254,196,208,155,31,157,170,85,69,58,9,255,252,112,3,
173,232,129,163,12,249,175,93,200,9,109,129,132,138,255,65,98,38,61,73,66,34,15,63,72,65,63,61,251,39,51,64,64,15,145,228,233,22,151,128,54,160,74,131,45,211,184,198,176,16,209,138,217,38,165,60,217,72,
175,178,94,32,4,230,113,19,170,24,53,229,213,64,241,130,198,174,101,45,175,224,92,74,197,74,130,228,42,151,185,66,202,4,8,242,160,7,9,20,137,186,127,18,67,16,224,96,0,62,252,106,102,6,253,224,25,212,119,
176,18,74,67,81,42,91,212,129,62,194,97,190,249,21,53,202,202,66,22,94,64,98,18,183,224,196,245,93,82,13,210,117,95,133,245,18,172,71,156,133,45,94,214,193,32,13,8,145,149,96,67,48,167,139,96,91,65,32,
8,115,48,0,26,126,229,170,10,245,84,79,8,137,133,49,22,150,48,144,168,5,26,203,97,85,38,189,74,229,133,41,44,184,45,118,212,90,170,124,89,91,120,89,64,241,204,68,118,88,213,65,2,97,130,10,17,128,34,143,
123,252,167,25,160,128,5,116,64,67,76,151,248,193,31,89,185,197,107,17,115,89,170,76,229,178,168,172,168,127,142,153,129,108,255,236,101,239,136,101,25,187,208,14,68,10,41,25,205,41,72,159,37,60,193,21,
118,240,61,54,199,45,8,65,240,0,30,148,18,87,232,120,135,66,23,26,214,89,240,12,146,7,71,130,175,140,110,14,47,245,235,229,86,183,218,51,192,114,181,221,236,233,218,59,81,47,34,56,144,2,7,36,80,83,75,
199,13,14,112,128,194,28,70,241,163,87,37,249,57,176,176,243,168,155,124,95,83,239,178,33,156,187,236,61,93,225,234,106,119,48,214,145,65,117,170,15,9,12,183,237,250,16,254,244,245,152,102,176,2,31,64,
224,14,121,104,29,157,121,250,163,81,227,89,81,135,192,48,188,93,42,232,104,91,251,218,215,246,76,176,112,193,220,61,23,82,44,165,173,4,21,110,16,221,206,138,91,95,63,254,3,28,32,96,6,59,244,193,185,244,
210,103,178,167,140,97,26,156,229,226,21,183,248,175,78,197,239,146,56,164,218,21,121,181,75,191,218,111,158,70,16,17,94,224,67,4,12,96,240,131,223,12,2,136,16,131,24,224,48,144,69,101,49,79,144,174,196,
142,20,101,113,255,141,55,27,23,58,231,27,176,142,228,16,146,215,187,35,115,142,4,21,210,253,109,151,223,148,225,98,176,131,12,174,113,114,100,68,208,41,102,94,14,207,207,98,22,140,123,245,207,68,35,175,
208,179,66,101,12,111,59,23,250,100,98,36,98,128,135,16,28,162,210,78,255,167,24,124,96,6,56,152,32,6,185,56,249,47,187,67,25,118,133,176,235,242,14,188,217,249,76,54,175,102,194,236,212,244,115,84,226,
117,243,96,80,1,220,82,140,59,117,161,224,3,45,68,61,2,218,121,142,100,33,46,139,0,19,114,231,130,15,60,149,197,46,244,106,242,21,195,123,78,27,88,59,168,247,65,253,65,10,6,8,183,228,215,218,86,40,192,
1,221,6,74,186,235,16,125,139,26,159,62,244,161,215,228,224,115,241,231,174,27,221,243,89,199,196,51,98,209,135,31,204,254,224,98,48,131,5,124,96,7,63,164,91,237,172,211,123,3,49,196,111,201,128,30,248,
155,244,106,191,255,253,229,76,236,41,24,114,38,230,243,125,109,93,49,84,65,11,118,192,131,12,42,91,190,37,98,255,2,50,11,1,82,204,170,172,168,126,175,62,223,142,150,69,173,7,9,68,128,8,45,183,126,108,
230,3,115,87,5,16,144,2,120,192,7,0,152,39,231,23,12,115,2,12,245,22,22,183,128,90,11,132,39,183,150,15,91,16,2,18,16,7,8,40,121,80,160,5,65,16,125,81,39,2,50,128,82,141,7,29,123,50,128,174,23,12,29,56,
131,145,0,131,18,244,7,34,112,7,127,240,5,35,184,126,10,120,76,90,0,7,213,183,130,202,81,117,217,231,130,123,167,93,174,115,55,75,232,122,176,98,17,114,150,47,61,216,131,90,80,133,10,24,4,43,96,2,125,
224,96,16,209,43,53,248,130,19,152,25,179,192,58,174,130,132,89,65,5,50,240,7,87,96,128,112,55,133,8,168,5,80,80,130,65,0,1,30,112,7,120,144,7,120,215,129,18,248,28,176,98,131,245,135,99,234,166,69,10,
66,61,105,128,6,39,224,118,54,117,128,110,184,126,113,88,130,101,0,5,43,96,7,118,200,133,124,152,132,47,232,130,96,152,137,246,103,17,183,150,6,127,128,7,63,224,255,39,212,177,136,164,120,8,85,56,3,112,
168,5,16,0,1,115,144,2,122,32,2,104,144,135,16,215,135,180,136,137,96,136,99,173,39,136,46,197,7,55,128,7,122,64,7,112,3,55,140,84,138,196,136,8,63,134,105,112,168,96,40,32,137,38,16,1,43,104,115,175,
194,58,160,227,135,22,225,5,84,144,6,50,144,4,69,0,69,112,67,17,138,88,140,224,56,3,152,246,99,112,128,2,30,64,7,119,224,7,120,128,6,92,184,132,132,162,135,127,64,21,102,69,5,161,145,7,125,176,141,28,
144,2,193,248,7,188,38,123,224,8,142,152,246,7,152,54,144,152,54,3,30,224,1,118,144,2,119,208,140,236,200,7,105,32,7,143,7,9,179,32,143,7,33,143,84,64,5,211,128,6,73,32,5,219,200,89,18,112,0,118,112,21,
255,56,146,89,17,4,51,32,142,38,249,99,43,128,2,40,48,7,115,128,144,59,240,1,6,240,3,234,24,1,55,112,3,104,144,7,58,137,6,60,169,145,17,192,145,87,112,7,20,64,58,31,249,145,87,113,21,34,72,146,74,153,
132,25,39,217,148,228,134,2,110,198,146,44,233,146,44,48,7,44,112,144,118,96,7,18,128,144,7,121,21,30,112,148,96,9,150,75,57,150,213,113,146,143,32,149,104,137,150,115,192,146,44,208,150,110,249,149,30,
112,149,97,121,0,34,152,148,100,121,151,127,146,150,86,233,150,45,233,150,110,25,150,127,32,146,120,57,152,197,244,151,30,240,7,93,249,7,118,73,152,140,233,89,135,121,152,129,249,8,139,217,152,148,25,
55,7,0,151,20,113,153,149,185,153,156,217,153,75,9,153,158,249,39,129,0,0,59,0,0};

const char* JuceDemoPluginAudioProcessorEditor::vibratingsilveryspeakeranimatedgif_gif = (const char*) resource_JuceDemoPluginAudioProcessorEditor_vibratingsilveryspeakeranimatedgif_gif;
const int JuceDemoPluginAudioProcessorEditor::vibratingsilveryspeakeranimatedgif_gifSize = 83589;

// JUCER_RESOURCE: download_jpg, 4685, "../../../Desktop/download.jpg"
static const unsigned char resource_JuceDemoPluginAudioProcessorEditor_download_jpg[] = { 255,216,255,224,0,16,74,70,73,70,0,1,1,0,0,1,0,1,0,0,255,219,0,132,0,9,6,7,20,18,18,21,20,16,20,20,20,20,20,20,
20,20,20,20,20,20,20,20,15,20,20,20,21,22,22,20,20,20,20,24,28,40,32,24,26,37,28,20,20,33,49,33,37,41,43,46,46,46,23,31,51,56,51,44,55,40,45,46,43,1,10,10,10,14,13,14,23,16,16,20,44,28,28,28,44,44,44,
43,44,46,44,44,44,44,55,43,55,45,45,44,47,43,44,44,50,44,43,55,55,53,44,44,44,44,44,55,44,46,55,44,55,55,44,43,55,44,55,44,45,55,44,44,44,43,255,192,0,17,8,0,170,1,40,3,1,34,0,2,17,1,3,17,1,255,196,0,
28,0,0,1,5,1,1,1,0,0,0,0,0,0,0,0,0,0,2,0,1,3,6,7,5,4,8,255,196,0,63,16,0,2,1,2,2,5,8,8,5,3,4,3,1,0,0,0,0,1,2,3,17,4,33,5,6,18,49,81,19,22,34,50,65,113,145,177,51,82,83,97,98,129,130,225,21,52,146,161,
193,20,35,240,66,114,209,241,67,162,194,36,255,196,0,24,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,255,196,0,41,17,1,1,0,2,2,1,4,0,4,7,0,0,0,0,0,0,0,1,2,17,3,18,49,33,65,81,97,4,209,225,240,19,113,129,
145,161,177,193,255,218,0,12,3,1,0,2,17,3,17,0,63,0,196,68,35,183,171,186,21,215,146,109,116,127,111,153,85,207,193,232,250,149,95,69,100,251,78,254,23,83,106,73,116,175,228,104,154,19,87,212,82,178,249,
219,50,201,67,68,46,7,59,155,90,100,139,81,31,172,252,66,230,31,196,252,126,198,199,29,22,184,14,244,90,224,103,189,58,177,190,97,124,79,199,236,46,97,252,79,199,236,108,223,133,46,0,189,22,184,14,244,
211,27,230,27,245,159,143,216,110,97,252,79,199,236,108,159,133,174,2,122,45,112,29,233,213,141,243,15,226,126,63,97,249,133,241,63,31,177,178,71,69,174,1,61,22,184,14,244,211,25,230,23,196,252,126,194,
230,23,196,252,126,198,205,248,90,224,55,225,139,128,239,77,49,174,97,124,79,199,236,55,48,254,39,227,246,54,95,194,215,1,61,22,184,14,244,211,27,90,132,253,103,227,246,27,152,127,19,241,251,27,58,209,
75,128,47,69,174,3,189,58,177,190,97,124,79,199,236,50,212,63,137,248,253,141,147,240,181,192,111,194,215,1,222,154,99,188,195,248,159,143,216,92,194,126,179,241,251,27,36,116,90,224,31,225,107,128,239,
77,49,142,97,191,89,248,139,152,95,19,241,251,27,43,209,107,128,223,133,174,3,189,52,198,249,132,253,103,227,246,27,152,127,19,241,251,27,42,209,139,128,158,139,92,7,122,105,141,243,9,250,207,196,110,
97,191,89,248,155,63,225,107,128,47,69,174,3,189,52,198,249,133,241,63,31,176,185,135,241,63,31,177,177,189,22,184,13,248,90,224,59,211,76,119,152,127,19,241,251,11,152,79,214,126,63,99,100,142,139,92,
3,252,45,112,29,233,213,139,189,67,126,179,241,251,30,60,86,165,205,46,139,254,77,198,90,45,112,60,152,141,16,184,23,189,52,249,235,29,162,234,82,235,199,46,43,113,226,55,29,45,161,19,78,234,235,184,204,
117,163,64,114,47,110,11,163,126,146,225,239,55,142,91,75,21,193,198,17,180,75,133,163,183,56,199,139,183,203,180,216,53,75,69,40,198,57,111,177,150,234,228,47,94,55,247,255,0,31,242,110,154,185,71,37,
242,57,231,86,44,56,12,26,72,247,170,86,11,15,12,130,153,193,176,236,138,193,68,86,32,96,82,10,72,81,64,51,64,216,149,130,208,13,20,56,144,246,1,172,51,136,118,6,72,6,81,31,100,120,137,128,204,20,136,
231,139,133,175,180,173,123,101,158,100,208,207,63,152,10,72,11,19,50,55,107,219,43,240,237,1,69,15,113,33,236,3,49,156,67,217,6,104,6,217,21,130,66,176,12,10,65,73,10,40,6,104,22,137,108,11,64,50,67,
137,15,96,25,160,37,77,18,216,22,128,230,227,240,73,162,135,172,186,57,56,201,53,189,51,78,171,27,162,159,172,84,178,125,204,222,53,43,231,188,93,29,137,202,60,30,93,221,130,61,154,125,127,123,233,94,
108,71,161,129,234,199,230,35,220,252,209,190,106,226,201,124,140,19,86,63,49,30,231,230,141,251,87,122,171,184,231,200,214,43,93,21,144,211,68,148,119,13,56,156,26,66,130,99,198,33,236,1,18,10,193,88,
105,0,34,176,172,41,228,155,179,118,236,91,216,12,208,86,57,211,198,201,245,90,86,82,188,114,119,113,121,198,253,153,93,174,227,166,157,210,124,82,126,32,5,89,108,197,183,216,174,115,234,227,157,147,73,
37,177,181,36,243,121,75,102,73,62,203,111,58,85,105,169,43,73,93,61,251,214,236,251,15,38,34,133,26,113,233,236,165,181,123,190,50,236,253,191,98,143,69,134,146,186,107,138,107,196,56,160,246,8,57,52,
240,147,202,202,219,47,163,25,74,251,226,227,39,116,123,232,82,217,140,99,190,201,35,197,167,113,146,165,201,108,90,210,171,24,74,252,25,210,146,40,19,155,91,13,55,57,180,174,229,181,103,149,173,177,104,
217,239,78,231,78,193,70,39,62,78,76,120,241,237,151,143,79,247,165,120,48,20,173,181,150,202,109,89,110,221,20,155,183,101,221,207,106,67,164,21,141,163,207,139,170,224,174,146,121,218,205,180,219,123,
148,109,218,7,245,41,203,102,205,59,181,240,237,37,118,174,122,157,52,218,151,108,111,111,159,105,230,134,10,210,218,189,210,114,113,86,220,231,214,187,237,18,193,32,246,14,40,135,29,91,97,43,90,239,60,
211,118,138,235,73,165,216,128,144,123,16,80,197,166,212,90,106,79,127,108,84,173,180,227,126,54,204,244,48,4,86,21,130,81,0,108,61,135,72,43,0,54,6,72,144,103,16,34,154,200,171,107,23,85,247,50,219,56,
228,85,181,138,61,25,124,252,139,10,249,243,88,125,55,210,188,216,133,172,94,155,233,94,108,71,170,57,143,85,255,0,49,30,231,230,141,255,0,87,87,69,24,6,171,254,98,61,207,248,62,130,213,174,170,255,0,
59,14,92,141,98,182,81,89,15,52,60,35,144,234,39,22,193,24,5,96,210,26,192,5,136,43,215,140,45,180,247,221,238,190,74,215,111,130,205,30,153,198,233,171,181,116,213,214,245,239,71,46,149,11,206,74,59,
75,102,89,73,231,11,56,165,36,243,205,75,55,145,81,238,113,13,68,10,52,118,99,24,222,246,73,92,154,40,138,241,75,13,8,41,74,163,218,89,57,57,217,164,163,187,192,150,133,69,82,42,81,119,139,220,214,235,
18,98,168,41,194,80,150,233,39,23,243,43,218,157,89,195,148,195,79,173,74,93,31,124,95,249,251,149,22,43,28,141,108,195,109,225,167,109,241,180,215,210,255,0,236,236,206,32,84,165,181,22,159,106,107,197,
1,229,208,245,185,74,52,231,235,65,95,190,217,158,219,28,237,92,192,78,133,21,78,165,174,165,43,89,221,108,183,145,212,176,162,189,174,49,254,196,101,234,213,166,255,0,115,183,21,127,217,248,139,21,134,
133,72,236,212,138,146,189,236,248,173,193,165,251,1,27,136,73,14,208,74,39,159,241,28,87,147,25,39,204,191,218,237,96,118,65,217,37,17,220,70,134,146,9,196,120,196,243,126,23,27,49,185,101,53,114,182,
255,0,201,254,36,40,84,79,53,71,74,115,228,219,78,113,87,113,77,169,40,190,54,236,124,15,93,122,170,17,148,228,237,24,167,38,253,201,92,205,39,137,169,201,109,194,78,56,157,39,94,208,146,118,157,60,53,
55,119,52,247,172,149,190,103,167,223,78,184,241,203,199,150,118,248,212,159,206,254,146,175,244,112,59,50,189,238,147,147,138,181,172,230,243,111,139,236,61,91,32,225,103,120,172,219,178,74,239,54,237,
149,219,226,72,28,80,182,175,107,171,240,237,240,37,81,57,56,202,83,83,115,105,36,164,157,239,189,174,140,51,222,150,119,103,191,71,206,82,79,105,237,37,43,70,86,74,252,126,87,220,81,54,200,219,36,162,
72,138,142,194,176,242,136,81,64,5,72,100,85,53,143,171,46,231,228,92,42,172,138,142,178,46,140,187,159,145,98,87,207,26,199,233,190,149,230,198,31,88,189,55,210,188,216,143,84,115,22,171,254,98,63,63,
224,250,15,86,186,171,252,236,62,124,213,127,204,71,185,249,163,232,77,91,234,163,151,35,88,174,20,150,66,10,150,225,218,56,180,138,173,69,24,182,247,37,118,6,31,18,167,117,102,164,173,120,189,246,123,
159,113,22,43,15,38,212,226,243,138,105,69,245,100,155,205,72,106,24,104,211,233,54,213,163,100,164,242,132,119,184,223,181,92,163,210,193,10,50,186,186,119,92,86,230,43,17,85,140,86,146,169,135,198,165,
85,255,0,102,170,74,47,178,47,143,137,104,129,205,211,250,45,98,40,202,47,172,149,224,248,73,127,200,181,113,85,84,35,26,234,211,141,227,239,178,220,84,116,228,142,83,209,31,254,165,136,82,183,67,101,
199,214,123,179,58,200,64,38,129,68,131,56,144,53,196,8,225,66,192,177,43,6,192,50,65,164,50,65,0,210,67,68,33,0,154,26,33,140,226,17,202,214,93,29,60,77,9,81,167,53,13,183,21,38,253,75,244,145,81,209,
73,87,197,213,173,31,69,135,95,209,225,151,101,161,233,102,189,247,203,222,139,30,186,233,103,134,194,205,211,244,181,90,163,69,45,252,165,76,174,151,109,149,223,200,243,234,190,138,84,105,194,148,119,
83,138,77,241,150,249,63,27,154,158,158,173,92,242,184,204,61,167,175,245,253,199,123,13,79,102,54,57,122,207,165,158,30,151,65,94,173,70,169,209,143,107,155,202,246,224,183,157,182,86,116,94,14,165,124,
92,241,56,136,56,198,147,116,240,244,229,255,0,181,78,246,102,187,112,99,134,238,89,248,199,215,95,63,19,243,250,118,180,109,25,170,80,141,121,109,207,101,109,202,217,57,118,171,30,216,161,146,28,56,219,
187,183,155,23,93,197,198,49,73,183,217,125,201,111,151,113,45,10,209,149,246,90,118,201,216,12,85,5,37,36,172,164,210,191,22,151,99,237,177,206,114,156,39,37,22,182,239,20,163,21,189,174,172,82,236,130,
91,217,89,118,90,26,33,216,102,136,6,174,226,163,172,189,89,119,63,34,219,87,113,81,214,78,172,187,159,145,96,249,227,88,189,55,210,188,216,195,235,31,166,250,87,155,17,234,142,98,213,111,204,71,185,249,
163,232,125,90,93,20,124,241,170,255,0,152,143,115,243,71,209,26,181,213,95,231,97,203,145,172,86,250,75,33,218,60,120,189,173,152,184,237,89,55,181,177,215,247,53,198,220,9,48,149,91,130,114,223,118,
175,107,93,45,210,183,101,206,45,39,177,231,199,97,85,72,74,155,109,41,197,198,235,122,191,105,61,197,38,5,51,67,227,167,130,171,253,54,39,209,183,253,185,246,43,188,190,79,246,46,71,135,76,232,138,120,
152,108,84,202,217,198,75,172,143,86,22,138,132,35,4,219,217,74,55,123,236,139,68,187,32,142,198,100,81,32,182,65,136,97,13,97,172,61,198,184,10,192,216,116,196,216,5,178,5,131,64,182,2,217,4,118,51,0,
144,91,32,196,54,3,52,38,132,206,110,176,105,104,225,112,245,107,203,253,17,110,43,182,83,121,66,41,118,182,251,10,42,218,78,175,245,90,74,203,58,88,8,219,220,241,53,23,255,0,49,183,139,45,216,10,27,49,
69,95,83,116,108,161,74,42,166,117,38,221,106,207,141,74,143,105,174,228,153,114,45,32,246,64,176,104,22,204,133,178,114,180,254,153,134,22,158,220,243,148,186,52,224,186,243,147,220,146,58,135,35,240,
56,188,87,245,53,36,230,227,21,26,80,125,74,92,90,92,95,17,93,120,186,118,223,39,137,237,243,245,250,161,213,141,21,82,14,85,241,50,114,175,91,172,175,209,167,29,234,17,94,227,191,176,184,43,241,237,238,
184,208,12,39,39,37,228,202,229,127,127,65,100,120,122,241,154,188,93,213,237,154,182,99,215,167,180,172,219,75,43,217,218,254,235,158,23,89,198,106,219,81,138,188,99,77,43,185,219,123,81,255,0,74,247,
149,205,208,171,28,138,126,178,174,140,187,159,145,108,141,101,40,109,45,207,50,167,172,175,163,46,231,228,39,145,243,190,177,250,111,165,121,177,11,88,253,55,210,188,216,143,84,115,22,171,254,98,61,207,
248,62,133,213,169,116,87,249,216,124,245,170,255,0,152,143,115,243,71,208,122,183,213,95,231,97,203,145,172,87,42,79,35,199,166,48,110,181,41,66,50,112,111,116,145,234,163,184,83,56,180,168,104,189,55,
83,11,37,67,26,157,183,66,166,252,189,239,181,23,8,77,52,154,105,166,174,154,220,209,226,210,58,58,158,34,27,21,85,215,99,255,0,82,124,83,38,194,97,163,74,17,132,50,140,85,145,104,244,54,50,6,76,73,145,
82,48,27,29,200,9,48,14,44,45,162,36,194,8,59,130,196,12,216,81,216,64,198,66,184,4,216,21,42,198,17,114,156,182,98,179,114,125,84,187,197,38,82,177,248,138,245,240,216,138,188,170,84,227,41,65,82,178,
179,75,143,188,178,34,219,137,210,180,97,109,186,208,141,214,212,110,247,167,185,160,176,184,218,117,83,116,167,25,165,189,197,238,101,78,172,100,241,24,110,78,148,42,203,250,69,209,154,232,218,217,182,
79,161,162,227,141,159,41,5,70,114,165,209,132,61,27,73,230,237,196,186,22,216,176,182,136,211,29,25,6,217,72,214,250,171,17,140,163,132,89,194,149,177,88,133,216,237,232,96,251,218,191,200,184,98,241,
49,165,9,84,155,180,97,23,41,119,37,114,141,170,52,101,85,79,19,86,252,166,46,163,172,239,123,198,158,234,81,179,221,146,89,113,53,62,74,184,232,202,54,141,222,247,153,239,34,167,146,176,87,50,9,177,162,
12,152,162,194,164,100,109,132,228,3,96,28,89,206,211,186,118,158,22,41,206,242,156,157,161,74,57,212,155,247,47,228,247,38,115,48,186,10,148,107,206,187,188,234,75,170,230,246,149,53,234,193,118,10,233,
197,252,61,239,63,19,218,123,253,111,217,231,208,88,44,76,234,60,70,50,110,50,146,180,48,241,127,219,167,31,139,140,142,190,35,10,164,238,220,150,86,118,118,186,190,231,246,39,5,177,19,147,146,231,150,
245,39,212,240,121,193,40,217,43,37,146,75,113,83,214,78,172,187,159,145,108,169,46,137,80,214,71,209,151,115,242,44,242,230,249,231,88,253,55,210,188,216,133,172,126,155,233,94,108,71,170,57,139,85,255,
0,49,30,231,230,143,160,117,109,244,87,249,216,124,253,170,255,0,152,143,115,243,70,255,0,171,143,162,142,92,141,98,185,209,121,13,81,145,209,150,66,155,56,180,74,65,109,145,38,24,81,41,15,180,71,113,
165,32,36,115,31,108,131,104,36,192,54,195,218,33,139,11,104,34,91,129,81,130,166,41,48,165,25,4,228,69,22,24,4,164,113,177,90,179,66,163,155,114,169,21,83,173,8,180,169,183,235,91,137,215,184,14,69,218,
57,248,157,3,78,114,132,149,74,208,149,56,42,113,112,105,61,149,196,147,71,232,122,116,102,234,109,78,164,218,182,221,71,121,37,193,51,215,180,58,99,98,75,230,22,209,18,99,202,105,111,118,247,189,203,
222,200,170,182,191,226,121,85,71,3,23,158,38,91,85,125,216,122,121,206,254,230,237,31,153,217,209,180,18,87,74,201,36,162,184,37,146,69,87,66,84,120,172,69,124,91,189,167,46,66,130,125,148,105,59,55,
243,119,239,200,187,83,133,162,145,171,233,232,145,42,144,238,100,112,97,179,32,148,135,218,35,184,46,65,83,109,139,104,129,72,43,132,26,97,237,16,169,15,182,21,53,193,147,7,108,22,192,122,178,200,170,
107,36,186,50,238,126,69,162,111,34,173,172,125,89,119,63,34,196,175,159,53,139,211,125,43,205,140,62,177,122,111,165,121,177,143,84,115,30,172,126,98,61,207,205,27,230,174,238,95,35,2,213,159,204,71,
185,249,163,121,213,201,228,190,71,62,70,177,92,105,203,33,165,34,56,60,135,56,52,146,35,237,1,113,92,3,108,27,140,152,215,1,216,73,145,54,18,0,198,96,220,72,3,218,26,76,9,8,9,34,62,208,2,184,4,216,215,
7,104,109,160,29,134,153,19,97,32,14,229,115,94,116,132,161,135,84,169,191,238,226,101,200,83,226,182,189,36,187,148,124,203,5,202,83,173,253,86,62,165,77,244,240,171,144,165,193,213,150,117,102,187,183,
92,184,149,221,208,56,24,210,132,97,5,104,211,138,140,126,93,167,105,179,203,133,165,179,20,79,113,65,196,43,129,113,16,19,99,32,110,37,32,16,105,145,54,18,0,238,48,45,137,48,15,104,107,128,216,233,129,
37,77,197,83,88,159,70,93,207,200,180,85,121,21,61,97,151,69,247,51,80,172,7,88,189,55,210,188,216,133,172,62,155,233,94,108,71,166,57,135,87,234,108,215,133,251,93,188,127,232,220,53,119,17,184,192,33,
38,154,107,122,105,174,244,106,58,173,167,212,212,93,236,223,154,222,140,103,22,54,60,52,238,137,54,142,6,139,210,73,165,153,215,134,37,28,52,219,209,113,92,131,150,66,117,81,4,173,131,112,121,84,15,42,
138,37,76,52,200,21,84,63,44,128,154,67,38,70,170,161,185,84,65,59,5,48,57,84,51,168,128,151,104,87,32,229,80,252,170,2,70,198,1,213,64,242,168,162,84,195,76,129,85,67,186,168,15,6,180,105,79,233,176,
211,168,186,246,216,166,187,93,73,229,4,189,253,191,35,155,170,218,51,146,167,8,60,218,91,83,124,106,75,165,55,226,207,22,156,196,172,70,54,20,183,211,194,174,86,124,29,105,175,237,175,146,204,178,104,
251,37,119,189,151,196,71,65,140,152,60,170,26,85,17,149,75,180,51,100,60,178,27,150,64,75,112,110,11,170,134,229,81,68,151,13,50,5,81,113,29,214,92,64,153,137,50,46,85,13,203,34,9,152,147,35,229,145,
29,92,74,69,18,226,43,89,20,141,108,199,40,194,78,251,147,59,90,75,73,36,158,102,93,173,250,109,74,233,62,140,93,223,189,246,69,27,198,37,170,46,155,157,234,191,116,98,159,126,247,230,35,197,82,110,77,
183,189,187,136,238,192,79,86,3,26,233,60,179,79,122,254,87,188,242,136,13,23,65,107,83,73,103,182,151,202,162,239,69,179,7,173,212,218,206,118,255,0,118,70,28,164,214,105,180,248,172,153,107,192,201,
184,171,187,229,218,98,227,23,109,90,26,209,75,218,67,196,126,115,210,246,144,241,51,43,8,207,88,187,105,220,232,165,237,33,226,15,57,233,123,72,126,163,51,16,235,13,180,206,115,210,246,144,241,23,57,
233,123,72,120,153,152,135,88,109,166,243,162,151,180,135,234,31,156,244,189,164,63,81,152,136,117,134,218,119,58,41,123,72,126,161,115,162,151,180,135,234,51,17,14,176,219,78,231,61,47,105,15,212,11,
214,122,94,210,30,38,102,33,214,27,105,220,232,165,237,33,226,15,57,233,123,72,126,163,51,16,235,13,180,206,115,210,246,144,241,35,196,107,101,40,197,203,148,139,178,110,201,230,223,98,70,110,69,136,93,
17,214,27,92,52,14,149,132,98,229,82,164,118,234,201,213,169,119,158,212,183,47,146,44,81,214,106,75,255,0,36,63,81,152,65,4,91,138,109,167,115,158,151,180,135,136,185,209,75,218,67,196,204,68,78,177,
118,211,185,207,75,218,67,196,30,115,210,246,144,241,51,49,14,176,219,78,231,61,47,105,15,212,15,57,233,123,72,120,153,152,135,88,109,166,189,103,165,237,33,250,134,231,69,47,105,15,19,51,16,235,13,180,
213,173,20,189,164,63,80,252,231,165,237,33,250,140,196,67,172,54,211,39,173,52,151,254,72,126,163,193,140,214,250,105,101,45,175,246,230,80,143,54,54,77,44,157,187,139,214,38,221,141,59,173,14,73,221,
236,71,133,250,114,40,218,67,28,234,190,17,91,151,242,253,231,150,164,219,109,182,219,190,247,155,24,220,154,66,16,132,104,127,255,217,0,0};

const char* JuceDemoPluginAudioProcessorEditor::download_jpg = (const char*) resource_JuceDemoPluginAudioProcessorEditor_download_jpg;
const int JuceDemoPluginAudioProcessorEditor::download_jpgSize = 4685;


//[EndFile] You can add extra defines here...
//[/EndFile]
