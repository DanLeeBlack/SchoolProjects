#ifndef SOUNDSAMPLES_H
#define SOUNDSAMPLES_H

//A class to hold array of samples in the form of floats with relavent getters to samplerate and length
class SoundSamples{
    public:
    SoundSamples();
    SoundSamples(float* samplesIn, int totalIn, float samplerateIn);
    SoundSamples(int totalIn, int samplerateIn);
    float getSampleRate() const;
    int length() const;
    SoundSamples(const SoundSamples& soundIn);
    SoundSamples& operator=(const SoundSamples& soundIn);
    float& operator[](const int index);
    SoundSamples operator+( SoundSamples rhs);
    void reverb2( float delay, float attenuation);
    void adsr(float atime, float alevel, float dtime, float slevel, float rtime);
    private:
    float* samples;
    int total;
    float samplerate;


};









#endif