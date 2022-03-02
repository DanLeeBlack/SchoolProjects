#include "wave.h"
#include "soundio.h"
#include "SoundSamples.h"
#include <vector>

//generates a file of float values based on promted input from the user
int main (){

    int waveNumber;
    float rdelay;
    float rattenuation;
    float asdrAlevel;
    float asdrAtime;
    float asdrDtime;
    float asdrSlevel;
    float asdrRtime;
    string filename;
    vector<int> notes;
    int note;
    Wave *sound;
    SoundIO io;
    SoundSamples song;
    SoundSamples silence(0.25*8000.0, 8000.0);
    SoundSamples *temp;
    SoundSamples hold;
    int counter = 1;

    //prompt for wave type
    cout << "Please enter a number to pick a wave type." << endl << "1 for sine wave" << endl << "2 for triangle wave" << endl << "3 for square wave" << endl << "4 for saw wave" << endl;
    cin >> waveNumber;

    if(waveNumber > 4 || waveNumber < 0){
        cout << "You have provided an inapromprate value" << endl;
        return 0;
    }
    
    //prompt for reverb and asdr prameters
    cout << "Please provide reverb parameters in the form of 2 float numbers seperated by a space the first number is delay and the second number is attenuation" << endl << "first number is delay and the second number is attenuation" << endl << "(i.e. 1.0 2.0)"<< endl;
    cin >> rdelay >> rattenuation;

    cout << "Please provide ADSR parameters in the for of 5 float numbers seperated by spaces" << endl << "the numbers in order are Atime, Alevel, Dtime, Slevel, Rtime" "(i.e. 0.5 0.8 0.2 0.4 0.6)" << endl;
    cin >> asdrAtime >> asdrAlevel >> asdrDtime >> asdrSlevel >> asdrRtime;

    //prompt for file to write to
    cout << "Please provide a storage file name" << endl;
    cin >> filename;

    //prompt for musical notes to play
    cout << "Please provide a series of note numbers terminating with negative number" << endl << "i.e. 44 75 23 -1" << endl;

    //adds notes to a holding vector and checks for a negative value to end while loop
    cin >> note;
    while (note > 0){
        notes.push_back(note);
        cin >> note;
    }
    notes.push_back(note);

    //generates wave based on earlier input
    if(waveNumber == 1){
        sound = new SineWave("sine");
    }else if(waveNumber ==2 ){
        sound = new TriangleWave("triangle");
    }else if(waveNumber ==3 ){
        sound = new SquareWave("square");       
    }else if(waveNumber ==4 ){
        sound = new SawtoothWave("saw");
    }


    //loop making sound samples based on earlier input to a temp holder, then applies reverb and asder until it is appended to song for holding
    note = notes.front();
    while (note > 0){
        temp = sound->generateSamples((2.0*((note-49.0)/12.0)*440.0),8000.0,1.0);
        temp->reverb2(rdelay,rattenuation);
        temp->adsr(asdrAtime,asdrAlevel,asdrDtime,asdrSlevel,asdrRtime);
        hold = temp->operator+(silence);
        delete temp;
        song = song+hold;
        note = notes.at(counter);
        counter++;
    }

    //song is made into temp to be made a pointer for use in SoundIO io
    temp->operator=(song);
    io.OutPutSound(temp,filename);
    return 0;
}