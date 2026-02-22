#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  :  public juce::AudioAppComponent, // section 9.25
                        public juce::Button::Listener, // Section 7.2
                        public juce::Slider::Listener // Section 7.8

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
    
    void buttonClicked(juce::Button* button) override;//Section 7.3

    void sliderValueChanged (juce::Slider* slider) override;// section 7.8
    
private:
    //==============================================================================
    // Your private member variables go here...
    
    juce::TextButton loadButton; // section 9.6 file chooser
    juce::TextButton playButton; // Section 5,1 Adding a GUI Widget
    juce::TextButton stopButton; // Section 7,5 Member Variable Declaration
    juce::Slider gainSlider; // Section 7,7 Add a slider
    juce::Random random; // section 8.2 making noise
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource; //section 9.3
    juce::AudioTransportSource transportSource; //section 9.2
    juce::AudioFormatManager formatManager; // section 9,1 setting up audioformat...

    bool playing = false; //section 8,3 state variables for sound control
    double gain = 0.5;     // sction 8,32 Gain slider
    float phase = 0.0f; // section 8,4 Making Waves
    float freq = 0.0f; // section 8.5 lure of sirens
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
