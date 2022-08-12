/*
  ==============================================================================

    PlaylistComponent.h
    Author:  KJ1364

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>
#include "TrackObject.h"
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include <cmath>
#include<iostream>
#include<algorithm>
#include <fstream>



//==============================================================================
/*
*/

/**other look and feel for playlist component buttons*/
class OtherLookAndFeelButtonsPC : public LookAndFeel_V4
{
public:
    /** initial look and feel for buttons*/
    OtherLookAndFeelButtonsPC()
    {
        setColour(TextButton::buttonColourId,Colour::fromString("#E9E9E9"));
        setColour(TextButton::textColourOffId, Colours::darkgrey);
    }
};

class PlaylistComponent  :  public juce::Component,
                            public juce::TableListBoxModel,
                            public Button::Listener,
                            public TextEditor::Listener
{
public:
    PlaylistComponent(DJAudioPlayer* _getFileMetaData,
                      DeckGUI* _deckGUI1,
                      DeckGUI* _deckGUI2);
    
    ~PlaylistComponent() override;

    /**draw content*/
    void paint (juce::Graphics&) override;
    /**redraw content when window is resized*/
    void resized() override;
    
    /**return number of rows in table*/
    int getNumRows () override;
    /**paints background of row*/
    void paintRowBackground (   Graphics &,
                                int rowNumber,
                                int width,
                                int height,
                                bool rowIsSelected) override;
    /**draws cell*/
    void paintCell (    Graphics &,
                        int rowNumber,
                        int columnId,
                        int width,
                        int height,
                        bool rowIsSelected) override;
    /**updates/creates component for cell https://docs.juce.com/master/classTableListBoxModel.html#a07767e4e5a3812e486c187705b0921bd*/
    Component * refreshComponentForCell (int rowNumber,
                                         int columnId,
                                         bool isRowSelected,
                                         Component *existingComponentToUpdate) override;
    /**button click event listener*/
    void buttonClicked (Button *) override;
    /**load  track into library*/
    void loadTrack ();
    /**load data from the csv into the table and display track infromation*/
    void loadCSVTrack (File pathName);
    /**save library as a csv*/
    void saveCurrLibrary ();
    /**open previous library*/
    void openPrevLibarary();
    /**search library for track*/
    void searchLibrary(String searchText);
    /**reset the search results*/
    void resetSearch();
    /**erase track from playlist*/
    void eraseTrack(int rownumber);        
    
private:
    
    TableListBox tableComponent;
    TextButton playListLoad{"LOAD"};
    TextButton loadLibrary{"LOAD LIBRARY"};
    TextButton saveLibrary{"SAVE LIBRARY"};
    TextButton searchButton{"SEARCH"};
    TextButton resetButton{"RESET SEARCH"};
    
    
    //change type to TrackObject
    std::vector<TrackObject> trackTitles;
    
    String getLength(URL trackURL);
    
    TextEditor searchBox;
    
    //Source: https://github.com/BlairCurrey/DJ-juce
    DJAudioPlayer* getFileMetaData;
    DeckGUI* deckGUI1;
    DeckGUI* deckGUI2;

    OtherLookAndFeelButtonsPC otherLookAndFeelButtonsPC;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
