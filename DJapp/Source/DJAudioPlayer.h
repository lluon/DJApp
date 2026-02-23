/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 23 Feb 2026 8:09:05pm
    Author:  lluon

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

/*
    This component is a simple audio player component,
    which mainly handles loading, play and stop control,
    position seeking, and volume adjustment.
*/
//==============================================================================

// section 10.61: DJAudioPlayer now inherits from AudioSource
class DJAudioPlayer : public juce::AudioSource
{
public:
    // section 10.62: Constructor takes a reference to the manager
    DJAudioPlayer(juce::AudioFormatManager& _formatManager);
    ~DJAudioPlayer() override;

    // section 10.63: Standard AudioSource lifecycle methods
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    /** Loads audio file from a URL */
    bool loadURL(const juce::URL& url);
    
    /** Start / resume audio playback */
    void play();
    
    /** Stop playback */
    void stop();
    
    /** Set the playback position in seconds */
    void setPosition(double posInSecs);
    
    /** Set the volume level (0 to 1) */
    void setGain(double gain);

private:
    // section 10.64: Reference to the manager held in MainComponent
    juce::AudioFormatManager& formatManager;

    // Reader, managed by unique_pointer because its lifetime is tied to file selection
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;

    // Playback controller
    juce::AudioTransportSource transportSource;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DJAudioPlayer)
};
