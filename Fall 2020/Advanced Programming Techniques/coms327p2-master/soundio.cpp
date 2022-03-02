#include "soundio.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

//creates a file filled with a list of sample values in the form of floats.

int SoundIO::OutPutSound(SoundSamples *samples, string filename){
    ofstream file;
    file.open(filename);
    for(int i =0; i < samples->length(); i++){
        file << samples->operator[](i) << endl;
    }
   
   file.close();

    return 0;

    
}