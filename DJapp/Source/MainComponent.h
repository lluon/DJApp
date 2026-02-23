#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h" // section 10.61

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  :  public juce::AudioAppComponent, // section 9.25
                        public juce::Button::Listener, // Section 7.2
                        public juce::Slider::Listener  // Section 7.8
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;
    
    /** Section 7.3: Callback for button clicks */
    void buttonClicked(juce::Button* button) override;

    /** Section 7.8: Callback for slider movements */
    void sliderValueChanged (juce::Slider* slider) override;
    
private:
    //==============================================================================
    juce::AudioFormatManager formatManager; // section 9.1 setting up audioformat...
    DJAudioPlayer player1 {formatManager};  // section 10.62: delegate audio to player class
    
    // bool loadURL(const juce::URL& audioURL); // section 9.71: commented out as player1 handles this now
    
    juce::TextButton loadButton; // section 9.6 file chooser
    juce::TextButton playButton; // Section 5.1 Adding a GUI Widget
    juce::TextButton stopButton; // Section 7.5 Member Variable Declaration
    juce::Slider gainSlider;     // Section 7.7 Add a slider

    // --- Section 8 & 9 Legacy Variables (Commented out) ---
    // juce::Random random;                                         // section 8.2
    // std::unique_ptr<juce::AudioFormatReaderSource> readerSource; // section 9.3
    // juce::AudioTransportSource transportSource;                  // section 9.2
    // bool playing = false;                                        // section 8.3
    // double gain = 0.5;                                           // section 8.32
    // float phase = 0.0f;                                          // section 8.4
    // float freq = 0.0f;                                           // section 8.5
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
