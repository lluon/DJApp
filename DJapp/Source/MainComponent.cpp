#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // SECTION 9.11: Setting up audio formats
    formatManager.registerBasicFormats();
    
    // Section 5.3 & 7.5: Adding GUI Widgets
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(gainSlider);
    addAndMakeVisible(loadButton);
    
    // section 7.5 & 9.6: Button labels
    playButton.setButtonText("PLAY");
    stopButton.setButtonText("STOP");
    loadButton.setButtonText("LOAD");
    
    // section 7.4, 7.8, 9.6: Register the Listeners
    playButton.addListener(this);
    stopButton.addListener(this);
    gainSlider.addListener(this);
    loadButton.addListener(this);
    
    // section 8.32: Gain slider range
    gainSlider.setRange(0, 1);

    setSize (800, 600);
    setAudioChannels (0, 2);
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    // section 10.64: delegate to player1
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    // section 10.65: delegate to player1
    player1.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    // section 10.66: delegate to player1
    player1.releaseResources();
}

//==============================================================================
void MainComponent::buttonClicked(juce::Button* button) //section 7.6
{
    if (&loadButton == button)
    {
        // section 9.6: Use FileChooser for loading
        juce::FileChooser chooser {"Select a sound file..."};
        
        if (chooser.browseForFileToOpen())
        {
            // section 10.67: call player1 to load the selected file
            player1.loadURL(juce::URL{chooser.getResult()});
        }
    }
    
    if (&playButton == button)
    {
        // section 10.68: delegate play to player1
        player1.play();
    }
    else if (&stopButton == button)
    {
        // section 10.69: delegate stop to player1
        player1.stop();
    }
}

//==============================================================================
void MainComponent::sliderValueChanged(juce::Slider *slider)
{
    if (slider == &gainSlider)
    {
        // section 10.70: delegate gain change to player1
        player1.setGain(gainSlider.getValue());
    }
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // Fill the background
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    // section 5.4 & 7.5: Position GUI components
    auto rowHeight = getHeight() / 5;
    
    playButton.setBounds(0, 0, getWidth(), rowHeight);
    stopButton.setBounds(0, rowHeight, getWidth(), rowHeight);
    loadButton.setBounds(0, rowHeight * 2, getWidth(), rowHeight);
    gainSlider.setBounds(0, rowHeight * 3, getWidth(), rowHeight);
}
