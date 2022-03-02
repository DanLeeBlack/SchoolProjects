# coms3272

# SoundSamples.cpp
    SoundSample() - default constructor

    SoundSamples(float* samplesIn, int totalIn, float samplerateIn) - Constructor of SoundSamples with array of samples, total number of samples, and given rate

    SoundSamples(int totalIn, int samplerateIn)- Constructs a zeroed SoundSample given total sample number and sample rate


    getSampleRate() - samplerate getter

    Length() - total sample getter

    SoundSamples(const SoundSamples& soundIn) - copy constructor

    operator=(const SoundSamples& soundIn) - copy operator

    operator[](const int index) - sample index

    operator+(SoundSamples rhs) - creates a new SoundSample with the rhs samples add to the end of the originating sample


# wave.cpp
    generateSample(float frequency, float samplerate, float duration) -modular sample generation based on subclass generate function


# soundio.cpp
    OutPutSound(SoundSamples *samples, string filename) - creates a file filled with a list of sample values in the form of floats.


# main.cpp
    main()-creates a file filled with a list of sample values in the form of floats based on parameters given by used when prompted.

# TestMain.pp
    main()-//generates a file of float values based on promted input from the user