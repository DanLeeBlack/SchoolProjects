#ifndef SOUNDIO_H
#define SOUNDIO_H

#include <iostream>
#include <string>
using namespace std;
#include "SoundSamples.h"

//creates a file filled with a list of sample values in the form of floats.
class SoundIO{
    public:
    int OutPutSound(SoundSamples *samples, string filename);
};



#endif