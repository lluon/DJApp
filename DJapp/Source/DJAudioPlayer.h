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

class DJAudioPlayer
{
    public:
        DJAudioPlayer();    // constructor/ intitialize player
    
        ~DJAudioPlayer();   // destructor/ clean up resources

        bool loadURL(const juce::URL& url); //loads audio file from anywhere
    
        void play();        // start / resume audio playback
    
        void stop();        // stop / reset to beginning
        
        void setPosition(double posInSecs); // setting position to 0.0 in seconds
        
        void setGain(double gain); // set the volume level (0 to 1)
};
