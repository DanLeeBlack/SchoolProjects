#include "wave.h"
#include "soundio.h"
#include "SoundSamples.h"

//creates a file filled with a list of sample values in the form of floats based on parameters given by used when prompted.
int main(){
    int wavetype;
    float samplerate;
    float frequency;
    float duration;
    string filename;
    Wave *sound;
    SoundIO io;
    cin >> wavetype;

    cout << "Please input a number:" << endl << "1: for sine" << endl << "2: for square" << endl << "3: for triangle" << endl << "4: for sawtooth" << endl;
    if(wavetype == 1){
        sound = new SineWave("sine");
    }else if(wavetype ==2 ){
        sound = new SquareWave("square");
    }else if(wavetype ==3 ){
        sound = new TriangleWave("triangle");
    }else if(wavetype ==4 ){
        sound = new SawtoothWave("saw");
    }else{
        cout << "The option used is not within the parameters of the program. Please choose between 1,2,3, or 4" << endl;
        return 0;
    }

    cout << "Please input a samplerate, frequency, and duration" << endl;
    cin>> samplerate >> frequency >> duration;
    
    SoundSamples *samples = sound->generateSamples(frequency, samplerate, duration);

    cout << "Please input the intended filename";
    cin >> filename;

    io.OutPutSound(samples, filename);


}