#include <iostream>
using namespace std;
#include "SoundSamples.h"
#include <math.h>

//default constructor of SoundSampels
SoundSamples::SoundSamples(): total(0), samplerate(8000.0){
    
}

//Constructor of SoundSamples with array of samples, total number of samples, and given rate
SoundSamples::SoundSamples(float* samplesIn, int totalIn, float samplerateIn){
    total = totalIn;
    samplerate = samplerateIn;
    samples = new float[totalIn];
    for(int i =0; i < totalIn; i++){
        samples[i]=samplesIn[i];
    }
}

//Constructs a zeroed SoundSample given total sample number and sample rate
SoundSamples::SoundSamples(int totalIn, int samplerateIn){
    total = totalIn;
    samplerate = (float)samplerateIn;
    samples = new float[totalIn];
    for(int i =0; i < totalIn; i++){
        samples[i]=0.0;
    }
}

//getter sample rate
float SoundSamples::getSampleRate()const{
    return samplerate;
}

//getter total samples
int SoundSamples::length() const{
    return total;
}

//copy constructor
SoundSamples::SoundSamples(const SoundSamples& soundIn){
    total = soundIn.total;
    samplerate = soundIn.samplerate;
    samples = new float[total];
    for(int i =0; i < total; i++){
        samples[i]=soundIn.samples[i];
    }
}

// copy = operator
SoundSamples& SoundSamples:: operator=(const SoundSamples& soundIn){
    if(this != &soundIn){
        total = soundIn.total;
        samplerate = soundIn.samplerate;
        delete samples;
        samples = new float[soundIn.total];
        for(int i =0; i < total; i++){
            samples[i]=soundIn.samples[i];
        }        
    }
    return *this;
}
float& SoundSamples:: operator[](const int index){
    return samples[index];
}

//creates a new SoundSample with the rhs samples add to the end of the originating sample
SoundSamples SoundSamples:: operator+(SoundSamples rhs){
    SoundSamples returnSound(total + rhs.total, (int) samplerate);
    for(int i =0; i < total; i++){
        returnSound[i]=samples[i];
    }
    for(int i = 0; i < rhs.total;i++){
        returnSound[total+i] = rhs[i];
    }
    return returnSound;
}

void SoundSamples:: reverb2( float delay, float attenuation){
    

    if(delay < 0){
        cout << "delay value is out of parameters"<<endl;
    } else if(attenuation < 0){
        cout << "attenuation is out of perameters"<< endl;
    } else {
        int sdelay = round(samplerate  * delay);
        
        SoundSamples *temp = new SoundSamples(total,samplerate);

        for(int i =0; i < total; i++){
            if(i-sdelay >0){
                temp->operator[](i) = samples[i] + (temp->operator[](i-sdelay) * attenuation) ;
            } else {
                temp->operator[](i) = samples[i];
            }
        }
        *this = *temp;

    }

}

void SoundSamples:: adsr(float atime, float alevel, float dtime, float slevel, float rtime){
    if((atime + dtime + rtime) > ((float)total/samplerate)){
        cout <<"total adsr time is longer than SoundSample" << endl;
    }else if(alevel < slevel){
        cout << "alevel is smaller than slevel" << endl;
    } else if(atime < 0|| dtime < 0 ||rtime < 0){
        cout << "a time value is a negative number" << endl;
    }else {
    
        float mod = 0.0;
        int amodlength = round(atime*samplerate);
        float aincrement = alevel/(atime*samplerate);
        int dmodlength = round(dtime*samplerate)+amodlength;
        float dincrement = (alevel - slevel)/(dtime*samplerate);
        int rmodlength = total - round(rtime*samplerate);
        float rincrement = slevel/(rtime*samplerate);

        for(int i =0; i < amodlength; i++){
            samples[i]=samples[i]*mod;
            mod = mod + aincrement;
        }
        for(int i = amodlength; i < dmodlength; i++){
            samples[i]=samples[i]*mod;
            mod = mod - dincrement;
        }

        mod = mod - rincrement;
        for(int i = rmodlength; i < total; i++){
            samples[i]=samples[i]*mod;
            mod = mod - rincrement;
        }
    }


}