/*
  ==============================================================================

    DeckGUI.h
    Author:  KJ1364

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "OtherLookAndFeel.h"
#include "OtherLookAndFeelButtons.h"

//==============================================================================
/*
*/


/**enum class for radio buttons. defines radio buttons group IDs*/
enum RadioButtonIds
{
    audioBlockButtons = 101,
    stopAndPlay = 111
};

class DeckGUI    :  public Component,
                    public Button::Listener,
                    public Slider::Listener,
                    public FileDragAndDropTarget,
                    public Timer
{
public:
    DeckGUI(DJAudioPlayer* player, 
           AudioFormatManager & 	formatManagerToUse,
           AudioThumbnailCache & 	cacheToUse );
    ~DeckGUI();

    /**draw content*/
    void paint (Graphics&) override;
    /**redraw content when window is resized*/
    void resized() override;

     /** implement Button::Listener */
    void buttonClicked (Button *) override;

    /** implement Slider::Listener */
    void sliderValueChanged (Slider *slider) override;

    /**Checks if a file is being dragged.*/
    bool isInterestedInFileDrag (const StringArray &files) override;
    
    /**Checks whether a file has benn dropped*/
    void filesDropped (const StringArray &files, int x, int y) override; 

    /**The user-defined callback routine that actually gets called periodically.*/
    /**check for waveform changes*/
    void timerCallback() override;
    
    bool audioClicked = false;
    bool IIRClicked = false;
    
    //need to be public for playlist
    DJAudioPlayer* player;
    WaveformDisplay waveformDisplay;

private:

    TextButton playButton{"PLAY"};
    TextButton stopButton{"STOP"};
    TextButton loadButton{"LOAD"};
    TextButton audioBlock {"Change Speed"};
    TextButton IIRBlock {"Change IIR"};
    
    Label makeLowLabel{"Low Pass"};
    Label makeHighLabel{"High Pass"};
    Label makeBandLabel{"Band Pass"};
    Label volLabel{"Volume"};
    Label speedLabel{"Speed"};

  
    //Sliders to change audio output
    Slider volSlider{"Volume"};
    Slider speedSlider;
    Slider posSlider;
    
    Slider makeLowPassSlider;
    Slider makeHighPassSlider;
    Slider makeBandPassSlider;
    
    //Source: https://www.youtube.com/watch?v=po46y8UKPOY&list=PLLgJJsrdwhPxa6-02-CeHW8ocwSwl2jnu&index=7
    OtherLookAndFeel otherLookAndFeel;
    OtherLookAndFeelButtons otherLookAndFeelButtons;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
