/*
  ==============================================================================

    WaveformDisplay.h
    Author:  KJ1364
  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class WaveformDisplay    : public Component, 
                           public ChangeListener
{
public:
    WaveformDisplay( AudioFormatManager & 	formatManagerToUse,
                    AudioThumbnailCache & 	cacheToUse );
    ~WaveformDisplay();
    
    /**draw content*/
    void paint (Graphics&) override;
    /**redraw content when window is resized*/
    void resized() override;

    /**pure virtual function to receive  the callback.*/
    void changeListenerCallback (ChangeBroadcaster *source) override;

    /**load URL to extract to get audio thumb*/
    void loadURL(URL audioURL);

    /** set the relative position of the playhead*/
    void setPositionRelative(double pos);

private:
    AudioThumbnail audioThumb;
    bool fileLoaded; 
    double position;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
