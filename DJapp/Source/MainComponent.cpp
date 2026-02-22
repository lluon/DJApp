#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    
    formatManager.registerBasicFormats(); //SECTION 9.11
    
    for (const auto* audioFormat : formatManager) //section 9.12
    {
     DBG(audioFormat->getFormatName());
    };
    
    playButton.setButtonText("PLAY");   // section 7,5 button labels
    stopButton.setButtonText("STOP");   // section 7,5 button labels
    
    
    addAndMakeVisible(playButton);  // Section 5,3  Adding a GUI Widget
    addAndMakeVisible(stopButton);  // Section 7,5  Adding to UI
    addAndMakeVisible(gainSlider);  // Section 7,7  Add a slider
    
    
    playButton.addListener(this);   // section 7.4 Register the Listener
    stopButton.addListener(this);   // section 7.8 Register the Listener
    gainSlider.addListener(this);   // section 7.8 Register the Listener
    
    
    gainSlider.setRange(0,1); //section 8.32 Gain slider

    URL audioURL("file:///Users/pandora/Desktop/DJapp/DJapp/asset/Ornella.wav"); //SECTION 9.32
    
    auto reader = formatManager.createReaderFor(audioURL.getLocalFile());
    
    if (reader!=nullptr)
    {
        auto newSource std::make_unique<juce::AudioFormatReaderSource>(reader, true);
    }
    AudioFormatReader * reader = formatManager.createReaderFor (audioURL.getLocalFile());
    
    if(reader)
    {
        auto newSource = std::make_unique<AudioFormatReaderSource>(reader, true);
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource = std::move(newSource);
    }
    else
    {
        DBG("Something went wrong loading the file");
    }
    
    
    setSize (800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}
//==============================================================================
void MainComponent::buttonClicked(juce::Button* button) //section 7,6
{
    DBG ("MainComponent::buttonClicked:Button clicked"); //section 7,6
    if (&playButton == button)
    {
        playing = true; // section 8,31 stop and astart
        freq = 0; //section 8,5 lure of sirens
    }
    else if (&stopButton == button)
    {
        playing = false;
    }
}
//==============================================================================
void MainComponent::sliderValueChanged(juce::Slider *slider)
{
    if (slider == &gainSlider)
    {
        DBG("MainComponent::sliderValueChanged: gainSlider " <<gainSlider.getValue());
        gain = gainSlider.getValue(); // 8.32 Gain slider
    }
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.
    TransportSource.prepareToPlay(samplesPerBlockExpected, sampleRate); // section 9.21
    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferTofill)
{
    
    if (!playing) // SECTION 8.3.1: start and stop (controlling the sound)
    {
        bufferTofill.clearActiveBufferRegion();
        return;
    }
 /*
    int numChannels = block.buffer->getNumChannels();  // SECTION 8,2 making a noise

    auto* leftChannel = numChannels > 0 ? block.buffer->getWritePointer(0, block.startSample) : nullptr;
    auto* rightChannel = numChannels > 1 ? block.buffer->getWritePointer(1, block.startSample) : nullptr;

    for (int i = 0; i < block.numSamples; ++i)     // SECTION 8.32 gain slider
    {
        auto sample = std::fmod(phase,1.f)*2. - 1.; // SECTION 8.4 making waves
        sample *= 0.1 * gain;
        phase += std::fmod(freq ,0.01f);     // SECTION 8.5 Lure of the sirens
        freq += 0.0000005f;
        
        if (leftChannel)  leftChannel[i] = sample;
        if (rightChannel)  rightChannel[i] = sample;
    }
 */
    TransportSource.getNextAudioBlock(bufferTofill);
    
}
void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.
    TransportSource.releaseResources(); //section 9,23
    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    
    

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    
    auto rowHeight = getHeight()/5;
    
    playButton.setBounds(0, 0, getWidth(), rowHeight); // Section 5,4  Add GUI...
    stopButton.setBounds(0, rowHeight, getWidth(), rowHeight);// Section 7,5
    gainSlider.setBounds(0,rowHeight*2,getWidth(),rowHeight);// Section 7,5

    // Section 4, debug printing
        DBG ( "w:" <<getWidth()<< "h:"<< getHeight());


}
