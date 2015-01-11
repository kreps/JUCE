/*
==============================================================================

This file was auto-generated by the Jucer!

It contains the basic startup code for a Juce application.

==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

AudioProcessor* JUCE_CALLTYPE createPluginFilter();

const float kfDefaultBypass = 0.0f;
const float kfDefaultGain = 1.0f;
const float kfDefaultDelay = 0.0f;
const float kfDefaultDelayTime = 0.01f;
const float kfDefaultPan = 0.5f;
const float kfDefaultMidSide = 0.5f;
const int knMaxDelayBufferLength= 24000;


//==============================================================================
JuceDemoPluginAudioProcessor::JuceDemoPluginAudioProcessor()
	: delayBuffer(2, knMaxDelayBufferLength)
{
	// Set up some default values..
	m_fGain = kfDefaultGain;
	m_fDelay = kfDefaultDelay;
	m_fDelayTime = kfDefaultDelayTime;
	m_fPan = kfDefaultPan;
	//m_fBypass = kfDefaultBypass;
	m_fMidSideParam = kfDefaultMidSide;
	m_fThreshold = 1.0f;
	m_fReverbSize = 0.5f;
	lastUIWidth = 400;
	lastUIHeight = 200;

	lastPosInfo.resetToDefault();
	delayPosition = 0;
	m_dFreq = 0;
	m_ic = IIRCoefficients::makeHighPass (getSampleRate(), m_dFreq);
	m_filterL.setCoefficients( m_ic );
	m_filterR.setCoefficients( m_ic );
	
}

JuceDemoPluginAudioProcessor::~JuceDemoPluginAudioProcessor()
{}

//==============================================================================
int JuceDemoPluginAudioProcessor::getNumParameters()
{
	return totalNumParams;
}

float JuceDemoPluginAudioProcessor::getParameter(int index)
{
	// This method will be called by the host, probably on the audio thread, so
	// it's absolutely time-critical. Don't use critical sections or anything
	// UI-related, or anything at all that may block in any way!
	switch (index)
	{
	case bypassParam:
		return bypass;
	case gainParam:
		return m_fGain;
	case delayParam:
		return m_fDelay;
	case delayTimeParam:
		return m_fDelayTime;
	case panParam:
		return m_fPan;
	case midSideParam:
		return m_fMidSideParam;
	case thresholdParam:
		return m_fThreshold;
	case hpfParam:
		return m_dFreq;
	case reverbSizeParam:
		return m_fReverbSize;
	default:
		return 0.0f;
	}
}

void JuceDemoPluginAudioProcessor::setParameter(int index, float newValue)
{
	// This method will be called by the host, probably on the audio thread, so
	// it's absolutely time-critical. Don't use critical sections or anything
	// UI-related, or anything at all that may block in any way!
	switch (index)
	{
	case bypassParam:
		bypass = newValue;
		break;
	case gainParam:
		m_fGain = newValue;
		break;
	case delayParam:
		m_fDelay = newValue;
		break;
	case delayTimeParam:
		m_fDelayTime = newValue;
		break;
	case panParam:
		m_fPan = newValue;
		break;
	case midSideParam:
		m_fMidSideParam = newValue;
		break;
	case thresholdParam:
		m_fThreshold = newValue;
		break;
	case hpfParam:
		m_dFreq = newValue;
		break;
	case reverbSizeParam:
		m_fReverbSize = newValue;
		break;
	default:
		break;
	}
}

float JuceDemoPluginAudioProcessor::getParameterDefaultValue(int index)
{
	switch (index)
	{
	case bypassParam: return kfDefaultBypass;
	case gainParam:     return kfDefaultGain;
	case delayParam:    return kfDefaultDelay;
	case delayTimeParam:    return kfDefaultDelayTime;
	case panParam:    return kfDefaultPan;
	case midSideParam:    return kfDefaultMidSide;
	case thresholdParam: return 1.0f;
	case hpfParam: return 0.0f;
	case reverbSizeParam: return 0.0f;
	default:            break;
	}

	return 0.0f;
}

const String JuceDemoPluginAudioProcessor::getParameterName(int index)
{
	switch (index)
	{
	case bypassParam:		return "bypass";
	case gainParam:			return "gain";
	case delayParam:		return "delay";
	case delayTimeParam:    return "delay time";
	case panParam:			return "pan";
	case midSideParam:		return "mid/side";
	case thresholdParam:	return "threshold";
	case hpfParam:			return "hpf";
	case reverbSizeParam: return "reverb size";
	default:				break;
	}

	return String::empty;
}

const String JuceDemoPluginAudioProcessor::getParameterText(int index)
{
	return String(getParameter(index), 2);
}

//==============================================================================
void JuceDemoPluginAudioProcessor::prepareToPlay(double sampleRate, int /*samplesPerBlock*/)
{
	// Use this method as the place to do any pre-playback
	// initialisation that you need..
	delayBuffer.clear();
}

void JuceDemoPluginAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
	//keyboardState.reset();
}

void JuceDemoPluginAudioProcessor::reset()
{
	// Use this method as the place to clear any delay lines, buffers, etc, as it
	// means there's been a break in the audio's continuity.
	delayBuffer.clear();
	//m_Reverb.reset();
}

float JuceDemoPluginAudioProcessor::sigmoid(float x) 
{ 
	if(fabs(x)<1) 
		return x*(1.5f - 0.5f*x*x); 
	else 
		return x > 0.f ? 1.f : -1.f; 
}

float JuceDemoPluginAudioProcessor::distortion(float in, float threshold)
{
  if (in>threshold || in<-threshold)
  {
    in= (in + fabs(fabs(fmod(in - threshold, threshold*4)) - threshold*2) - threshold)/2.0f;
  }
  return in;
}

float JuceDemoPluginAudioProcessor::Saturate(float x, float t) { 
	if(abs(x)<t) 
		return x; 
	else { 
		if(x > 0.0f) 
		    return   t + (1.f-t)*sigmoid((x-t)/((1-t)*1.5f)); 
		else
			return -(t + (1.f-t)*sigmoid((-x-t)/((1-t)*1.5f))); } } 


//float JuceDemoPluginAudioProcessor::Saturate(float x, float t)
//{
//	//threshold
//	//t = 0.5f;
//	if(fabs(x)<t)
//		return x;
//	else
//	{
//		if(x > 0.f)
//			return t + (1.f-t)*tanh((x-t)/(1-t));
//		else
//			return -(t + (1.f-t)*tanh((-x-t)/(1-t)));
//	}
//}

void JuceDemoPluginAudioProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{

	if (bypass == 1.0f || getNumInputChannels() < 2)
	{
		return;
	}

	const int numSamples = buffer.getNumSamples();

	int dp = 0;

	//calculate left and right gain according to pan param
	float lGain = 1;
	float rGain = 1;
	if (m_fPan < 0.5f)
	{ 
		rGain = 1 - (0.5f - m_fPan) * 2;
	} else
		if (m_fPan > 0.5f)
		{
			lGain = 1 - (m_fPan - 0.5f) * 2;
		}

		float fMidGain = 1.0f;
		float fSideGain= 1.0f;
		if (m_fMidSideParam > 0.5f){
			fMidGain = 1- (m_fMidSideParam-0.5f)*2;
		} else if(m_fMidSideParam < 0.5f){
			fSideGain = 1 - (0.5f - m_fMidSideParam) * 2;
		}

		float* leftData = buffer.getWritePointer(LEFT_CHANNEL);
		float* rightData = buffer.getWritePointer(RIGHT_CHANNEL);
		float* leftDelayData = delayBuffer.getWritePointer (LEFT_CHANNEL);
		float* rightDelayData = delayBuffer.getWritePointer (RIGHT_CHANNEL);
		dp = delayPosition;
		m_ic = IIRCoefficients::makeHighPass (getSampleRate(), m_dFreq);
		m_filterL.setCoefficients( m_ic );
		m_filterR.setCoefficients( m_ic );
		m_filterL.processSamples(leftData,numSamples);
		m_filterR.processSamples(rightData,numSamples);
		
		//m_Reverb.setSampleRate(getSampleRate());
		juce::Reverb::Parameters params = m_Reverb.getParameters();
		params.roomSize = m_fReverbSize;
		params.dryLevel = 0.0f;//this depends on general dry on/off button only on or off is possible
		params.damping = 0.0f;
		//params.freezeMode = 0.0f;//0 or 1
		//params.wetLevel = 1.0f; //this depends on general wet gain control
		params.width = 1.0f; 
		//params.damping = 0.0f;
		m_Reverb.setParameters(params);
		//m_Reverb.setParameters(juce::Reverb::Parameters());
		m_Reverb.processStereo(leftData,rightData,numSamples);
		
		for (int i = 0; i < numSamples; ++i)
		{
			//float coef_S = m_fMidSideParam*0.5;

			float m = fMidGain*(leftData[i] + rightData[i]) / 2;
			float s = fSideGain*((rightData[i] - leftData[i]) / 2);

			leftData[i] = distortion((m - s)*lGain*m_fGain,m_fThreshold);
			rightData[i] = distortion((m + s)*rGain*m_fGain,m_fThreshold);

			//delay implementation
			const float inLeft = leftData[i];
			leftData[i] += leftDelayData[dp];
			leftDelayData[dp] = ( inLeft) * m_fDelay;

			const float inRight = rightData[i];
			rightData[i] += rightDelayData[dp];
			rightDelayData[dp] = (inRight) * m_fDelay;

			
			if (++dp >= static_cast<int>(m_fDelayTime * knMaxDelayBufferLength))
				dp = 0;
		}
		delayPosition = dp;

		// In case we have more outputs than inputs, we'll clear any output
		// channels that didn't contain input data, (because these aren't
		// guaranteed to be empty - they may contain garbage).
		for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
			buffer.clear(i, 0, buffer.getNumSamples());

		// ask the host for the current time so we can display it...
		AudioPlayHead::CurrentPositionInfo newTime;

		if (getPlayHead() != nullptr && getPlayHead()->getCurrentPosition(newTime))
		{
			// Successfully got the current time from the host..
			lastPosInfo = newTime;
		} else
		{
			// If the host fails to fill-in the current time, we'll just clear it to a default..
			lastPosInfo.resetToDefault();
		}
}

//==============================================================================
AudioProcessorEditor* JuceDemoPluginAudioProcessor::createEditor()
{
	return new JuceDemoPluginAudioProcessorEditor(this);
}

//==============================================================================
void JuceDemoPluginAudioProcessor::getStateInformation(MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// Here's an example of how you can use XML to make it easy and more robust:

	// Create an outer XML element..
	XmlElement xml("MYPLUGINSETTINGS");

	// add some attributes to it..
	xml.setAttribute("uiWidth", lastUIWidth);
	xml.setAttribute("uiHeight", lastUIHeight);
	xml.setAttribute("gain", m_fGain);
	xml.setAttribute("delay", m_fDelay);
	xml.setAttribute("delayTime", m_fDelayTime);
	xml.setAttribute("pan", m_fPan);

	// then use this helper function to stuff it into the binary blob and return it..
	copyXmlToBinary(xml, destData);
}

void JuceDemoPluginAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.

	// This getXmlFromBinary() helper function retrieves our XML from the binary blob..
	ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	if (xmlState != nullptr)
	{
		// make sure that it's actually our type of XML object..
		if (xmlState->hasTagName("MYPLUGINSETTINGS"))
		{
			// ok, now pull out our parameters..
			lastUIWidth = xmlState->getIntAttribute("uiWidth", lastUIWidth);
			lastUIHeight = xmlState->getIntAttribute("uiHeight", lastUIHeight);

			m_fGain = (float)xmlState->getDoubleAttribute("gain", m_fGain);
			m_fDelay = (float)xmlState->getDoubleAttribute("delay", m_fDelay);
			m_fDelayTime = (float)xmlState->getDoubleAttribute("delayTime", m_fDelay);
			m_fPan = (float)xmlState->getDoubleAttribute("pan", m_fPan);
		}
	}
}

const String JuceDemoPluginAudioProcessor::getInputChannelName(const int channelIndex) const
{
	return String(channelIndex + 1);
}

const String JuceDemoPluginAudioProcessor::getOutputChannelName(const int channelIndex) const
{
	return String(channelIndex + 1);
}

bool JuceDemoPluginAudioProcessor::isInputChannelStereoPair(int /*index*/) const
{
	return true;
}

bool JuceDemoPluginAudioProcessor::isOutputChannelStereoPair(int /*index*/) const
{
	return true;
}

bool JuceDemoPluginAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool JuceDemoPluginAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool JuceDemoPluginAudioProcessor::silenceInProducesSilenceOut() const
{
	return false;
}

double JuceDemoPluginAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new JuceDemoPluginAudioProcessor();
}
