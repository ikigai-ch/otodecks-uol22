/*
  ==============================================================================

    DJAudioPlayer.h
    Author:  KJ1364

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class DJAudioPlayer :   public AudioSource
//                        public AudioProcessor
{
  public:

    DJAudioPlayer(juce::AudioFormatManager& _formatManager);
    ~DJAudioPlayer();

    /**Tells the source to prepare for playing. (pure virtual fuction) https://docs.juce.com/master/classAudioSource.html#a36fc2484ead8fb8dc03be57d09dd5735*/
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    /**pure virtual fuction. Called repeatedly to fetch subsequent blocks of audio data. https://docs.juce.com/master/classAudioSource.html#a36fc2484ead8fb8dc03be57d09dd5735*/
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    /**Base class for objects that can produce a continuous stream of audio. (pure virtual fuction) https://docs.juce.com/master/classAudioSource.html#a36fc2484ead8fb8dc03be57d09dd5735*/
    void releaseResources() override;
    
    /**Loads tracks into the audio players*/
    void loadURL(URL audioURL);
    /** Controls volume (increase/decrease)*/
    void setGain(double gain);
    /**Set audio playback speed*/
    void setSpeed(double ratio);
    /**Controls playback position*/
    void setPosition(double posInSecs);
    /**Sets the range of the slide that controls the postion into relation of the length of the audio file / Gets relative position of the playhead*/
    void setPositionRelative(double pos);

    //Source: https://docs.juce.com/master/classIIRFilterAudioSource.html
    /**IIR Filter Low Pass*/
    void changeMakeLowPass(double freq);
    /**IIR Filter Low Pass*/
    void changeMakeHighPass(double freq);
    /**IIR Filter Low Pass*/
    void changeMakeBandPass(double freq);

    /**Starts transport source/playback*/
    void start();
    /**Stops transport source/playback*/
    void stop();

    /** get the relative position of the playhead */
    double getPositionRelative();
    
    /**Public so Playlist can access*/
    AudioTransportSource transportSource;
    
    /**Since getNextAudioBlock can only be called on either  IIRFilterAudiosource or resampleSource
     There has to be a boolean to control what filter should be applied*/
    bool AudioBlockSpeed{false};

private:
    AudioFormatManager& formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    ResamplingAudioSource resampleSource{&transportSource, false, 2};
//    ToneGeneratorAudioSource toneGeneratorSource;
    
    IIRFilterAudioSource IIRfilter{&transportSource, false};
    
    /**to store double sampleRate and make it available for other functions*/
    float lastSampleRate;
};




