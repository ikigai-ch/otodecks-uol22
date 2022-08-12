/*
  ==============================================================================

    PlaylistComponent.cpp
    Author:  KJ1364

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"
#include <cmath>
#include<iostream>
#include<algorithm>
#include<string>
#include <fstream>

//#include "DJAudioPlayer.h"

//==============================================================================
PlaylistComponent::PlaylistComponent(DJAudioPlayer* _getFileMetaData, DeckGUI* _deckGUI1, DeckGUI* _deckGUI2)
                                    : getFileMetaData(_getFileMetaData),
                                        deckGUI1(_deckGUI1),
                                        deckGUI2(_deckGUI2)
            
{    
    //set headers of list and such
    tableComponent.getHeader().addColumn("Track Title", 1, 100 );
    tableComponent.getHeader().addColumn("Length", 2, 100 );
    tableComponent.getHeader().addColumn(" ", 3, 100);
    tableComponent.getHeader().addColumn(" ", 4, 100);
    tableComponent.getHeader().addColumn(" ", 5, 100);
    tableComponent.getHeader().addColumn(" ", 6, 100);
   
    //pass data. pointer to a model
    //this since this function is the model
    tableComponent.setModel(this);
    
    addAndMakeVisible(tableComponent);
    tableComponent.setColour(TableListBox::backgroundColourId, Colour::fromString("#E9E9E9"));
    
    //load files into playlist
    addAndMakeVisible(playListLoad);
    playListLoad.setLookAndFeel(&otherLookAndFeelButtonsPC);
    
    addAndMakeVisible(searchBox);
    searchBox.setColour(TextEditor::backgroundColourId, Colour::fromString("#BBC3CD"));
    
    addAndMakeVisible(searchButton);
    searchButton.setLookAndFeel(&otherLookAndFeelButtonsPC);
    
    addAndMakeVisible(resetButton);
    resetButton.setLookAndFeel(&otherLookAndFeelButtonsPC);
    
    addAndMakeVisible(saveLibrary);
    saveLibrary.setLookAndFeel(&otherLookAndFeelButtonsPC);
    
    addAndMakeVisible(loadLibrary);
    loadLibrary.setLookAndFeel(&otherLookAndFeelButtonsPC);
    
    playListLoad.addListener(this);
    searchBox.addListener(this);
    searchButton.addListener(this);
    resetButton.addListener(this);
    loadLibrary.addListener(this);
    saveLibrary.addListener(this);
}

PlaylistComponent::~PlaylistComponent()
{
    
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
    g.fillAll(Colour::fromString("#BBC3CD"));

    g.setColour (juce::Colours::transparentWhite);
    g.drawRect (getLocalBounds(), 0);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("PlaylistComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    tableComponent.setBounds(0,getHeight()/10,
                             getWidth(),(getHeight() - getHeight()/10));
    playListLoad.setBounds(0, 0,
                           getWidth()*0.5,getHeight()/20);
    saveLibrary.setBounds(getWidth()*0.5, 0,
                          getWidth()/4, getHeight()/20);
    loadLibrary.setBounds(getWidth()*0.75, 0,
                          getWidth()/4, getHeight()/20);

    searchBox.setBounds(0, getHeight()/20,
                        getWidth()*0.5,getHeight()/20);
    searchButton.setBounds(getWidth()*0.5,getHeight()/20,
                           getWidth()/4,getHeight()/20);
    resetButton.setBounds(getWidth()*0.75,getHeight()/20,
                           getWidth()/4,getHeight()/20);
}

int  PlaylistComponent::getNumRows ()
{
    return trackTitles.size();
}

void PlaylistComponent::paintRowBackground (   Graphics & g, //variable name for the incoming graphics
                            int rowNumber,
                            int width,
                            int height,
                            bool rowIsSelected)
{
    if (rowIsSelected)
    {
        g.fillAll(Colour::fromString("#C43F1D"));
    }
    else
    {
        g.fillAll(Colour::fromString("#BBC3CD"));
    }
}

void PlaylistComponent::paintCell (    Graphics & g,
                    int rowNumber,
                    int columnId,
                    int width,
                    int height,
                    bool rowIsSelected)
{
    if(columnId == 1)
    {
        g.drawText(trackTitles[rowNumber].title,
                   2, 0,
                   width - 4, height,
                   Justification::centredLeft, true);
    }
    if(columnId == 2)
    {
        g.drawText(trackTitles[rowNumber].length,
                   2, 0,
                   width - 4, height,
                   Justification::centredLeft, true);
    }
    if(columnId == 6)
    {
        g.drawText(trackTitles[rowNumber].found,
                   2, 0,
                   width - 4, height,
                   Justification::centredLeft, true);
    }
}

Component * PlaylistComponent::refreshComponentForCell (int rowNumber,
                                                        int columnId,
                                                        bool isRowSelected,
                                                        Component *existingComponentToUpdate)
                                                        //existing component is essentially a bit of data that's used to
                                                        //store the components. So if you want to draw
                                                        //a custom component, you need to put it into this bit of data.
{
    //Button for top GUI Deck
    if(columnId == 3)
    {
        if (existingComponentToUpdate == nullptr) // is null we haven't create the component yet
        {
            TextButton* buttonLeft = new TextButton{"play top deck"};
            
            //Initial idea:https://github.com/shamiejegan/UOL-CM2005/blob/main/Source/PlaylistComponent.cpp
            //but their implementation had limitations so I used letters instead of integers
            std::string id{std::to_string(rowNumber)+"l"};
            buttonLeft->setComponentID(id);
            buttonLeft->setLookAndFeel(&otherLookAndFeelButtonsPC);
            
            buttonLeft->addListener(this);
            existingComponentToUpdate = buttonLeft;
            DBG(getComponentID());
        }
    }
    //Button for bottom GUI Deck
    if(columnId == 4)
    {
        if (existingComponentToUpdate == nullptr) // is null we haven't create the component yet
        {
            TextButton* buttonRight = new TextButton{"play bottom deck"};
            
            //Initial idea:https://github.com/shamiejegan/UOL-CM2005/blob/main/Source/PlaylistComponent.cpp
            //but their implementation had limitations so I used letters instead of integers
            std::string id{std::to_string(rowNumber)+"r"};
            buttonRight->setComponentID(id);
            buttonRight->setLookAndFeel(&otherLookAndFeelButtonsPC);
            
            buttonRight->addListener(this);
            existingComponentToUpdate = buttonRight;
            DBG(buttonRight->getComponentID());
        }
    }
    //delete button
    if(columnId == 5)
    {
        if (existingComponentToUpdate == nullptr) // is null we haven't create the component yet
        {
            TextButton* buttonDelete = new TextButton{"delete"};
 
            //but their implementation had limitations so I used letters instead of integers
            std::string id{std::to_string(rowNumber)+"d"};
            buttonDelete->setComponentID(id);
            buttonDelete->setLookAndFeel(&otherLookAndFeelButtonsPC);
            
            buttonDelete->addListener(this);
            existingComponentToUpdate = buttonDelete;
            DBG(buttonDelete->getComponentID());
        }
    }
    return existingComponentToUpdate;
}

//Source: https://forum.juce.com/t/display-array-of-files-to-table/47827
//Source: https://github.com/BlairCurrey/DJ-juce/blob/master/Source/PlaylistComponent.cpp only initial idea
//code was adapted by me
void PlaylistComponent::loadTrack ()
{
    FileChooser chooser{"Select a file..."};
    if (chooser.browseForFileToOpen())
    {
        TrackObject track{ chooser.getResult() };
        getFileMetaData->loadURL(juce::URL{ chooser.getResult() });
        double trackLength { getFileMetaData->transportSource.getLengthInSeconds()};
    
        int minutes, seconds;
        String min, sec;
        seconds = trackLength;
        minutes = seconds/60;

        //Source: https://stackoverflow.com/questions/9138790/cant-use-modulus-on-doubles
        min = std::to_string(minutes%60);
        sec = std::to_string(seconds%60);
    
        //String minutes = std::to_string(trackLength/60);
        DBG(track.file);

        track.length = min + "." + sec;
        trackTitles.push_back(track);
        
        //call resized to update the table
        tableComponent.resized();
    }
}

//Source: https://github.com/BlairCurrey/DJ-juce/blob/master/Source/Track.h
//Source: www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/
void PlaylistComponent::saveCurrLibrary()
{
    std::ofstream myTrackTitles;
    myTrackTitles.open("OtoDecksLibrary.csv");
    
    for (TrackObject& to : trackTitles)
    {
        myTrackTitles << to.file << "\n";
    }
    myTrackTitles.close();
}

//initial inspiration from github https://github.com/BlairCurrey/DJ-juce/blob/master/Source/Track.h
void PlaylistComponent::openPrevLibarary()
{
    try{
        //Source: https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/
        std::ifstream myTrackTitles("OtoDecksLibrary.csv");
        
        std::string pathName;
        
        if(myTrackTitles.is_open())
        {
            while(std::getline(myTrackTitles, pathName))
            {
                File file {pathName};
                loadCSVTrack (file);
            }
        }
        myTrackTitles.close();
    }catch(std::exception const& e){
        DBG("No file found");
    }
//    else
//    {
//        throw std::runtime_error("Could not open file");
//    }
    
}

void PlaylistComponent::loadCSVTrack (File pathName)
{
    TrackObject track{ pathName };

    getFileMetaData->loadURL(juce::URL{ pathName });
    double trackLength { getFileMetaData->transportSource.getLengthInSeconds()};

    int minutes, seconds;
    String min, sec;
    
    seconds = trackLength;
    minutes = seconds/60;
    
    //Source: https://stackoverflow.com/questions/9138790/cant-use-modulus-on-doubles
    min = std::to_string(minutes%60);
    sec = std::to_string(seconds%60);
    
    track.length = min + "." + sec;

    trackTitles.push_back(track);
    
    //call resized to update the table
    tableComponent.resized();
}

void PlaylistComponent::searchLibrary(String searchText)
{
    //iteratates libarary
    for (int i = 0; i < trackTitles.size(); ++i)
    {
        //Reset "FOUND".
        trackTitles[i].found = "";
        //checks if a track matches
        if(trackTitles[i].title.toStdString().find(searchText.toStdString()) != std::string::npos)
        {
            trackTitles[i].found = "FOUND";
            //Source: https://forum.juce.com/t/listbox-redraw-problems/8106/4
            tableComponent.repaint();
        }
    }
}

//Source: https://www.cplusplus.com/reference/vector/vector/erase/
void PlaylistComponent::eraseTrack(int rownumber)
{
    trackTitles.erase(trackTitles.begin() + rownumber);
    tableComponent.repaint();
    tableComponent.resized();
}

void PlaylistComponent::resetSearch()
{
    for (int i = 0; i < trackTitles.size(); ++i)
    {
            trackTitles[i].found = "";
            tableComponent.repaint();
    }
}

void PlaylistComponent::buttonClicked (Button* button)
{
    if (button == &playListLoad)
    {
        loadTrack();
    }
    if (button == &saveLibrary)
    {
        saveCurrLibrary();
    }
    if (button == &loadLibrary)
    {
        openPrevLibarary();
    }
    if (button == &searchButton) 
    {
        if(searchBox.getText() != "" && searchBox.getText() != " ")
        {
            searchLibrary(searchBox.getText());
        }
    }
    if (button == &resetButton)
    {
        resetSearch();
    }
    
    //Initial idea:https://github.com/shamiejegan/UOL-CM2005/blob/main/Source/PlaylistComponent.cpp
    //but their implementation had limitations so I used letters instead of integers
    String idButton = (button->getComponentID());
    if (idButton.toStdString().find("r") != std::string::npos)
    {
        //convert string into interger to remove r from ID
        int newID = std::stoi(idButton.toStdString());
        
        DBG(newID);
        deckGUI2->player->loadURL(URL {trackTitles[newID].URL});
        deckGUI2->waveformDisplay.loadURL(URL{trackTitles[newID].URL});
    }
    //check if left button was clicked
    if (idButton.toStdString().find("l") != std::string::npos)
    {
        //convert string into interger to remove r from ID
        int newID = std::stoi(idButton.toStdString());
        
        deckGUI1->player->loadURL(URL {trackTitles[newID].URL});
        deckGUI1->waveformDisplay.loadURL(URL{trackTitles[newID].URL});
    }
    if (idButton.toStdString().find("d") != std::string::npos)
    {
        //convert string into interger to remove r from ID
        int newID = std::stoi(idButton.toStdString());
        
        eraseTrack(newID);
    }
}
