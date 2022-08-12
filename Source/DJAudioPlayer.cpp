/*
==============================================================================

 DJAudioPlayer.cpp
 Author:  KJ1364

==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(AudioFormatManager& _formatManager)
                                : formatManager(_formatManager)
{
    
}
DJAudioPlayer::~DJAudioPlayer()
{

}

void DJAudioPlayer::prepareToPlay (int samplesPerBlockExpected, double sampleRate) 
{
    //makes double sampleRate available for other functions such as
    //changeMakeLowPass etc.
    lastSampleRate = sampleRate;
    
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    //apply prepareToPlay to IIRfilter
    IIRfilter.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void DJAudioPlayer::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    //check if AudioBlockSpeed is true or not
    //if true getNextAudioBlock is called on resampleSource else IIRFilter
    if (AudioBlockSpeed == false)
    {
        IIRfilter.getNextAudioBlock(bufferToFill);
    }
    else
    {
        resampleSource.getNextAudioBlock(bufferToFill);
    }
}
void DJAudioPlayer::releaseResources()
{
    transportSource.releaseResources();
    resampleSource.releaseResources();
    IIRfilter.releaseResources();
}

void DJAudioPlayer::loadURL(URL audioURL)
{
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) // good file!
    {       
        std::unique_ptr<AudioFormatReaderSource> newSource (new AudioFormatReaderSource (reader, 
                                                                                         true));
        transportSource.setSource (newSource.get(), 0, nullptr, reader->sampleRate);             
        readerSource.reset (newSource.release());
    }
}

void DJAudioPlayer::setGain(double gain)
{
    if (gain < 0 || gain > 1.0)
    {
        std::cout << "DJAudioPlayer::setGain gain should be between 0 and 1" << std::endl;
    }
    else
    {
        transportSource.setGain(gain);
    }
}

void DJAudioPlayer::setSpeed(double ratio)
{
  if (ratio < 0.0 || ratio > 3.0)
    {
        std::cout << "DJAudioPlayer::setSpeed ratio should be between 0 and 100" << std::endl;
    }
    else
    {
        resampleSource.setResamplingRatio(ratio);
    }
}

void DJAudioPlayer::setPosition(double posInSecs)
{
    transportSource.setPosition(posInSecs);
}

void DJAudioPlayer::setPositionRelative(double pos)
{
     if (pos < 0 || pos > 1.0)
    {
        std::cout << "DJAudioPlayer::setPositionRelative pos should be between 0 and 1" << std::endl;
    }
    else
    {
        double posInSecs = transportSource.getLengthInSeconds() * pos;
        setPosition(posInSecs);
    }
}


//https://docs.juce.com/master/classIIRFilterAudioSource.html
void DJAudioPlayer::changeMakeLowPass(double freq)
{
    IIRfilter.setCoefficients(IIRCoefficients::makeLowPass(lastSampleRate, freq));
}

void DJAudioPlayer::changeMakeHighPass(double freq)
{
    IIRfilter.setCoefficients(IIRCoefficients::makeHighPass(lastSampleRate, freq));
}

void DJAudioPlayer::changeMakeBandPass(double freq)
{
    IIRfilter.setCoefficients(IIRCoefficients::makeBandPass(lastSampleRate, freq));
}



void DJAudioPlayer::start()
{
    transportSource.start();
    
}
void DJAudioPlayer::stop()
{
    transportSource.stop();
}

double DJAudioPlayer::getPositionRelative()
{
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}
