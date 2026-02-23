/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 23 Feb 2026 8:09:05pm
    Author:  lluon

  ==============================================================================
*/


#include "DJAudioPlayer.h"


//==============================================================================
DJAudioPlayer::DJAudioPlayer()
{
    // initialize audio object
}

//==============================================================================
DJAudioPlayer::~DJAudioPlayer()
{
    // clean up audio object
}
//==============================================================================
bool DJAudioPlayer::loadURL (const juce::URL& url)
{
    return false; //load file return if ok
}

//==============================================================================
void DJAudioPlayer::play()
{
    //start, resume playback
}
//==============================================================================
void DJAudioPlayer::stop()
{
    //stop, rewind
}
//==============================================================================
void DJAudioPlayer::setPosition (double posInSecs)
{
    // position seeker
}
//==============================================================================
void DJAudioPlayer::setGain (double gain)
{
    // set volume
}
