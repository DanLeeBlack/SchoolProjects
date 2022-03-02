#ifndef WAVE_H
#define WAVE_H

#include <iostream>
#include <string>
using namespace std;
#include "SoundSamples.h"
#include <math.h>

//abstract wave class that holds wave name and allows for versitile use of generateSamples
class Wave {
    public:
    
    SoundSamples * generateSamples(float frequency, float samplerate, float duration)const;
    virtual float generateFunction(float time) const =0;
    Wave(string name);
    private:
    string name;
};

//generates a sample of float in the shape of a sinewave
class SineWave : public Wave{
    public:
    float generateFunction(float time) const {
        float t = time - (int) time;
        return  sin(t);
    }
    SineWave(string nameIn): Wave(nameIn){}
};

//generates a sample of float in the shape of a squarewave
class SquareWave : public Wave{
    public:
    float generateFunction(float time) const {
        float t = time - (int) time;
        if(t < 0.5){
            return -1.0;
        }else{
            return 1.0;
        }
    }
    SquareWave(string nameIn): Wave(nameIn){}
};

//generates a sample of float in the shape of a Trianglewave
class TriangleWave : public Wave{
    public:
    float generateFunction(float time) const {
        float t = time - (int) time;
        if(t < 0.5){
            return (4*t)-1;
        } else{
            return (-4*t)-3;
        }
    }
    TriangleWave(string nameIn): Wave(nameIn){}
};

//generates a sample of float in the shape of a Sawtoohwave
class SawtoothWave : public Wave{
    public:
    float generateFunction(float time) const {
        float t = time - (int) time;
        return  (2*t)-1;
    }
    SawtoothWave(string nameIn): Wave(nameIn){}
};

#endif