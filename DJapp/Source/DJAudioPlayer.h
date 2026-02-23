/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 23 Feb 2026 8:09:05pm
    Author:  lluon

  ==============================================================================
*/

#pragma once    //operate once

#include <JuceHeader.h> //include premade JuceHeader class

/*
    This component is a simple audio player component,
    who mainly load, play and stop control, position seeking
    and volume adjustment
*/
//==============================================================================

class DJAudioPlayer //simple audio player component
{
    public:
        DJAudioPlayer();    // constructor/ intitialize
    
        ~DJAudioPlayer();   // destructor/ allocated memory cleaner

        bool loadURL(const juce::URL& url); //loads audio file from URL
    
        void play();        // start or resume audio playback
    
        void stop();        // stop audio playback if already then null
        
        void setPosition(double posInSecs); // setting position to 0.0 in seconds
        
        void setGain(double gain); // set the volume level
};
