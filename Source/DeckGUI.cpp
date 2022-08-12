/*
  ==============================================================================

    DeckGUI.cpp
    Author:  KJ1364

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "DeckGUI.h"
#include "OtherLookAndFeel.h"
#include "OtherLookAndFeelButtons.h"

//==============================================================================

DeckGUI::DeckGUI(DJAudioPlayer* _player,
                AudioFormatManager & 	formatManagerToUse,
                AudioThumbnailCache & 	cacheToUse
           ) : player(_player), 
               waveformDisplay(formatManagerToUse, cacheToUse)
{

    addAndMakeVisible(playButton);
    playButton.setLookAndFeel(&otherLookAndFeelButtons);
    
    addAndMakeVisible(stopButton);
    stopButton.setLookAndFeel(&otherLookAndFeelButtons);
    
    addAndMakeVisible(audioBlock);
    audioBlock.setLookAndFeel(&otherLookAndFeelButtons);
    
    addAndMakeVisible(IIRBlock);
    IIRBlock.setLookAndFeel(&otherLookAndFeelButtons);
    
    //volume slide
    addAndMakeVisible(volSlider);
    volSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    volSlider.setColour(Slider::trackColourId, Colour::fromString("#C43F1D"));
    volSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);

    addAndMakeVisible(speedSlider);
    speedSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    speedSlider.setColour(Slider::trackColourId, Colour::fromString("#C43F1D"));
    speedSlider.setTextBoxStyle(juce::Slider::TextBoxRight, true, 0, 0);
    speedSlider.setColour(Slider::textBoxTextColourId, Colours::darkgrey);
    
    addAndMakeVisible(waveformDisplay);
    
    addAndMakeVisible(posSlider);
    posSlider.setColour(Slider::thumbColourId, Colour::fromString("#BBC3CD"));
    posSlider.setColour(Slider::backgroundColourId, Colour::fromString("#E9E9E9"));
    posSlider.setColour(Slider::trackColourId, Colour::fromString("#C43F1D"));
    posSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    
    //low pass slider
    addAndMakeVisible(makeLowPassSlider);
    makeLowPassSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    makeLowPassSlider.setTextBoxStyle(juce::Slider::NoTextBox, false,0, 0);
    makeLowPassSlider.setLookAndFeel(&otherLookAndFeel);
    
    //high pass slider
    addAndMakeVisible(makeHighPassSlider);
    makeHighPassSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    makeHighPassSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    makeHighPassSlider.setLookAndFeel(&otherLookAndFeel);
    
    //Band pass slider
    addAndMakeVisible(makeBandPassSlider);
    makeBandPassSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    makeBandPassSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    makeBandPassSlider.setLookAndFeel(&otherLookAndFeel);
    makeBandPassSlider.setHelpText("Make");
    
    //labels for filters and sliders
    addAndMakeVisible(makeLowLabel);
    makeLowLabel.setColour(Label::textColourId, Colours::darkgrey);
    makeLowLabel.setText("Low Pass", juce::dontSendNotification);
    makeLowLabel.setJustificationType (juce::Justification::centred);
    
    addAndMakeVisible(makeHighLabel);
    makeHighLabel.setColour(Label::textColourId, Colours::darkgrey);
    makeHighLabel.setText("High Pass", juce::dontSendNotification);
    makeHighLabel.setJustificationType (juce::Justification::centred);
    
    addAndMakeVisible(makeBandLabel);
    makeBandLabel.setColour(Label::textColourId, Colours::darkgrey);
    makeBandLabel.setText("Band Pass", juce::dontSendNotification);
    makeBandLabel.setJustificationType (juce::Justification::centred);
    
    addAndMakeVisible(volLabel);
    volLabel.setColour(Label::textColourId, Colours::darkgrey);
    volLabel.setText("Volume", juce::dontSendNotification);
    volLabel.setJustificationType (juce::Justification::centred);
    
    addAndMakeVisible(speedLabel);
    speedLabel.setColour(Label::textColourId, Colours::darkgrey);
    speedLabel.setText("Speed", juce::dontSendNotification);
    speedLabel.setJustificationType (juce::Justification::centred);
    
    //add listeners
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    
    audioBlock.addListener(this);
    IIRBlock.addListener(this);

    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);
    
    makeLowPassSlider.addListener(this);
    makeHighPassSlider.addListener(this);
    makeBandPassSlider.addListener(this);

    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.0, 3.0);
    posSlider.setRange(0.0, 1.0);
    
    makeLowPassSlider.setRange(1.0, 21000.0);
    makeHighPassSlider.setRange(1.0, 3000.0);
    makeBandPassSlider.setRange(25.0, 8000.0);

    startTimer(500);
    
    //define radio Buttons to switch
    audioBlock.setRadioGroupId (audioBlockButtons);
    IIRBlock.setRadioGroupId (audioBlockButtons);
    
    stopButton.setRadioGroupId(stopAndPlay);
    playButton.setRadioGroupId(stopAndPlay);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background
    g.fillAll(Colour::fromString("#EFF2F5"));
    
    g.setColour (Colours::transparentWhite);
    g.drawRect (getLocalBounds(), 0);   // draw an outline around the component

    g.setColour (Colours::darkgrey);
    g.setFont (14.0f);
}

void DeckGUI::resized()
{
    double rowH = getHeight() / 11;
    
    playButton.setBounds(0, rowH*0.5, getWidth()/6, rowH*0.75);
    stopButton.setBounds(getWidth()/5, rowH*0.5, getWidth()/6, rowH*0.75);
    
    audioBlock.setBounds(getWidth() - getWidth()/4,rowH * 4.5,
                         getWidth()/5, rowH*0.75);
    IIRBlock.setBounds(getWidth() - getWidth()/4, rowH* 5.5,
                       getWidth()/5, rowH*0.75);
    
    volSlider.setBounds(getWidth()/24, rowH * 2,
                        getWidth()/12, rowH * 5.5);
    volLabel.setBounds(getWidth()/24, rowH * 1.25,
                       getWidth()/12, rowH);
    
    speedSlider.setBounds(getWidth()/24 * 6, rowH * 2 ,
                          getWidth()/12, rowH * 5.5);
    speedLabel.setBounds(getWidth()/24 * 6, rowH * 1.25,
                           getWidth()/12, rowH);

    makeLowPassSlider.setBounds(getWidth()/3, rowH/2,
                                getWidth()/3, rowH * 3);
    
    makeLowLabel.setBounds(getWidth()/3, rowH*1.5,
                           getWidth()/3, rowH);
    
    makeHighPassSlider.setBounds(getWidth() - getWidth()/3 , rowH/2,
                                getWidth()/3, rowH * 3);
    makeHighLabel.setBounds(getWidth() - getWidth()/3, rowH*1.5,
                           getWidth()/3, rowH);
    
    makeBandPassSlider.setBounds(getWidth()/3, rowH * 4,
                                 getWidth()/3,rowH * 3);
    makeBandLabel.setBounds(getWidth()/3, rowH*5,
                           getWidth()/3, rowH);

    
    waveformDisplay.setBounds(0, rowH * 8, getWidth(), rowH * 3);
    posSlider.setBounds(0, rowH * 7.5, getWidth(), rowH);
}
//check if a button was clicked
void DeckGUI::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        std::cout << "Play button was clicked " << std::endl;
        //change look of play button
        playButton.setColour(TextButton::buttonColourId, Colour::fromString("#C43F1D"));
        player->start();
        //change look of stop button if needed
        stopButton.setColour(TextButton::buttonColourId, Colours::transparentWhite);
    }
     if (button == &stopButton)
    {
        std::cout << "Stop button was clicked " << std::endl;
        //change look of stop button 
        stopButton.setColour(TextButton::buttonColourId, Colour::fromString("#C43F1D"));
        player->stop();
        //change look of play button if needed
        playButton.setColour(TextButton::buttonColourId, Colours::transparentWhite);
    }
    //toggle to switch between ressampleSource.getNextAudioBlock and IIRfilter.getNextAudioBlock
    if (button == &audioBlock)
    {
        audioBlock.setColour(TextButton::buttonColourId, Colour::fromString("#C43F1D"));
        player->AudioBlockSpeed = true;
        IIRBlock.setColour(TextButton::buttonColourId, Colours::transparentWhite);
    }
    if (button == &IIRBlock)
    {
        IIRBlock.setColour(TextButton::buttonColourId, Colour::fromString("#C43F1D"));
        player->AudioBlockSpeed = false;
        audioBlock.setColour(TextButton::buttonColourId, Colours::transparentWhite);
    }
}

//check if slider value was changed to trigger
void DeckGUI::sliderValueChanged (Slider *slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }

    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }
    
    if (slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue());
    }
    if (slider == &makeLowPassSlider)
    {
        player->changeMakeLowPass(slider->getValue());
    }
    if (slider == &makeHighPassSlider)
    {
        player->changeMakeHighPass(slider->getValue());
    }
    if (slider == &makeBandPassSlider)
    {
        player->changeMakeBandPass(slider->getValue());
    }
}

bool DeckGUI::isInterestedInFileDrag (const StringArray &files)
{
  std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
  return true; 
}

void DeckGUI::filesDropped (const StringArray &files, int x, int y)
{
  std::cout << "DeckGUI::filesDropped" << std::endl;
  if (files.size() == 1)
  {
      player->loadURL(URL{File{files[0]}}); //what did I do wrong?
      waveformDisplay.loadURL(URL{File{files[0]}});
  }
}

void DeckGUI::timerCallback()
{
    waveformDisplay.setPositionRelative(
    player->getPositionRelative());
}


    

