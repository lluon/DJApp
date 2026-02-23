/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 23 Feb 2026 8:09:05pm
    Author:  lluon

  ==============================================================================
*/

#include "DJAudioPlayer.h"

//==============================================================================
// section 10.65: Use _formatManager as the parameter to initialize the member
DJAudioPlayer::DJAudioPlayer(juce::AudioFormatManager& _formatManager)
: formatManager(_formatManager)
{
}

//==============================================================================
DJAudioPlayer::~DJAudioPlayer()
{
    // Destructor
}

void DJAudioPlayer::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void DJAudioPlayer::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    transportSource.getNextAudioBlock(bufferToFill);
}

void DJAudioPlayer::releaseResources()
{
    transportSource.releaseResources();
}

//==============================================================================
bool DJAudioPlayer::loadURL (const juce::URL& url)
{
    auto* reader = formatManager.createReaderFor(url.getLocalFile());
    
    if (reader != nullptr)
    {
        auto newSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource = std::move(newSource);
        return true;
    }
    
    return false; // Return false if loading failed
}

//==============================================================================
void DJAudioPlayer::play()
{
    transportSource.start(); // Start or resume playback
}

//==============================================================================
void DJAudioPlayer::stop()
{
    transportSource.stop(); // Stop playback
}

//==============================================================================
void DJAudioPlayer::setPosition (double posInSecs)
{
    transportSource.setPosition(posInSecs); // Seek to position
}

//==============================================================================
void DJAudioPlayer::setGain (double gain)
{
    transportSource.setGain(gain); // Set volume level
}
