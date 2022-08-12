/*
  ==============================================================================

    OtherLookAndFeelButtons.h
    Author:  KJ1364

  ==============================================================================
*/
#include "../JuceLibraryCode/JuceHeader.h"
#pragma once

class OtherLookAndFeelButtons : public LookAndFeel_V4
{
public:
    /** initial look and feel for buttons*/
    OtherLookAndFeelButtons()
    {
        setColour(TextButton::buttonColourId, Colours::transparentWhite);
        setColour(TextButton::textColourOffId, Colours::darkgrey);
    }
    
};
