/*
  ==============================================================================

    TrackObject.cpp
    Author:  KJ1364

  ==============================================================================
*/

#include "TrackObject.h"

//Source: https://github.com/BlairCurrey/DJ-juce/blob/master/Source/Track.cpp
TrackObject::TrackObject(juce::File _file)

    :   file(_file.getFullPathName()),
        //URL already extracted (do I still need it?)
        URL(juce::URL{ _file }),
        //dont need to set track.tile with this function
        title(_file.getFileName())
{

}
