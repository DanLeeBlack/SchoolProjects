#include "wave.h"
Wave::Wave(string nameIn){
name = nameIn;
}

//modular sample generation based on subclass generate function
SoundSamples * Wave::generateSamples(float frequency, float samplerate, float duration)const{
    int total = samplerate * duration;
    float time = 0.0;
    float * samples = new float[total];
    

    for(int i = 0;i<total; i++){
        samples[i] = generateFunction(time * frequency);
        time = time + (1.0/samplerate);
    }

    SoundSamples * sound = new SoundSamples(samples , total, samplerate);
    return sound;

}
