/*
  ==============================================================================

    TrackObject.h
    Author:  KJ1364

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

//Source: https://github.com/BlairCurrey/DJ-juce/blob/master/Source/Track.h
class TrackObject
{
    public:
        /**track object to then push into component*/
        TrackObject(juce::File _file);
        juce::String file;
        juce::URL URL;
        juce::String title;
        juce::String length;
        juce::String found;
};
