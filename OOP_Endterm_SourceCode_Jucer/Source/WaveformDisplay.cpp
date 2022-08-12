/*
  ==============================================================================

    WaveformDisplay.cpp
    Author:  KJ1364
  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(AudioFormatManager & 	formatManagerToUse,
                                 AudioThumbnailCache & 	cacheToUse) :
                                 audioThumb(1000, formatManagerToUse, cacheToUse), 
                                 fileLoaded(false), 
                                 position(0)
                          
{
  audioThumb.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background
    g.fillAll(Colour::fromString("#E9E9E9"));

    g.setColour (Colours::transparentWhite);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colour::fromString("#C43F1D"));
    if(fileLoaded)
    {
        audioThumb.drawChannel(g,
                             getLocalBounds(),
                             0,
                             audioThumb.getTotalLength(),
                             0,
                             1.0f);
        g.setColour(Colour::fromString("#BBC3CD"));
        g.drawLine(position * getWidth(), 0, position * getWidth(), getHeight(), 5.0f);
    }
    else 
    {
      g.setFont (20.0f);
      g.drawText ("File not loaded...", getLocalBounds(),
                  Justification::centred, true);   // draw some placeholder text
    }
}

void WaveformDisplay::resized()
{
}

void WaveformDisplay::loadURL(URL audioURL)
{
      audioThumb.clear();
      fileLoaded  = audioThumb.setSource(new URLInputSource(audioURL));
      if (fileLoaded)
      {
        std::cout << "wfd: loaded! " << std::endl;
        repaint();
      }
      else {
        std::cout << "wfd: not loaded! " << std::endl;
      }
}

void WaveformDisplay::changeListenerCallback (ChangeBroadcaster *source)
{
    std::cout << "wfd: change received! " << std::endl;
    repaint();
}

void WaveformDisplay::setPositionRelative(double pos)
{
  if (pos != position && pos > 0)
  {
    position = pos;
    repaint();
  }
}




