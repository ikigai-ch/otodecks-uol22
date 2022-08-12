/*
  ==============================================================================

    BalanceSlider.h
    Author:  KJ1364

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "OtherLookAndFeel.h"
#include "DeckGUI.h"


//==============================================================================
/*
*/
class BalanceSlider  :  public juce::Component,
                        public Slider::Listener
{
    
public:
    BalanceSlider(DeckGUI* _deckGUI1,
                  DeckGUI* _deckGUI2);
    
    ~BalanceSlider() override;
    /**draw content*/
    void paint (juce::Graphics&) override;
    /**redraw content when window is resized*/
    void resized() override;
    
    /** implement Slider::Listener */
    void sliderValueChanged (Slider *slider) override;
    

private:
    
    Slider balanceSlider;
    
    OtherLookAndFeel otherLookAndFeel;
    
    double position;
    
    DeckGUI* deckGUI1;
    DeckGUI* deckGUI2;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BalanceSlider)
};
