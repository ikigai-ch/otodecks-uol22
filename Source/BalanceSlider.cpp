/*
  ==============================================================================

    BalanceSlider.cpp
    Author:  KJ1364

  ==============================================================================
*/

#include <JuceHeader.h>
#include "BalanceSlider.h"

//==============================================================================
BalanceSlider::BalanceSlider(DeckGUI* _deckGUI1, DeckGUI* _deckGUI2)
                            :   deckGUI1(_deckGUI1),
                                deckGUI2(_deckGUI2)
{
    addAndMakeVisible(balanceSlider);
    balanceSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    balanceSlider.setColour(Slider::thumbColourId, Colours::transparentWhite);
    balanceSlider.setColour(Slider::backgroundColourId, Colour::fromString("#BBC3CD"));
    balanceSlider.setColour(Slider::trackColourId, Colour::fromString("#BBC3CD"));
    balanceSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    
    //set range
    balanceSlider.setRange(0.0, 1.0);

    balanceSlider.addListener(this);
}

BalanceSlider::~BalanceSlider()
{
}

void BalanceSlider::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
    g.fillAll(Colour::fromString("#EFF2F5"));

    g.setColour (juce::Colours::transparentWhite);
    g.drawRect (getLocalBounds(), 0);   // draw an outline around the component

    g.setColour (juce::Colours::darkgrey);
    g.setFont (14.0f);
    
    g.setColour(Colour::fromString("#BBC3CD"));
    //Rectangle over thumb for other look and feel
    g.fillRoundedRectangle(getWidth()*0.125,
                           ((getHeight() - getHeight()/40) - getHeight()*balanceSlider.getValue()),
                           getWidth()*0.725,
                           getHeight()/20,
                           10.0f);
    //lines
    for(int i = 1; i < 40; ++i)
    {
        g.drawLine(0, i * getHeight()/40,
                   getWidth(), i * getHeight()/40,
                   1.0f);
    }
    g.drawLine(0, getHeight() - getHeight()/40,
               getWidth(), getHeight() - getHeight()/40 ,
               5.0f);
    g.drawLine(0, getHeight()/40,
               getWidth(), getHeight()/40 ,
               5.0f);
}

void BalanceSlider::sliderValueChanged (Slider *slider)
{
    if(slider == &balanceSlider)
    {
        if(balanceSlider.getValue() > 0.5)
        {
            deckGUI1->player->setGain(slider->getValue());
            deckGUI2->player->setGain(1 - slider->getValue());
        }
        else if(balanceSlider.getValue() < 0.5)
        {
            deckGUI2->player->setGain(1 - slider->getValue());
            deckGUI1->player->setGain(slider->getValue());
        }
    }
}

void BalanceSlider::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    balanceSlider.setBounds(0, 0,
                            getWidth(),
                            getHeight());
}
