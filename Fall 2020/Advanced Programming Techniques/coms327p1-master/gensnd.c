#include<stdio.h>

#include<math.h>
#include "gensnd.h"
#include<stdlib.h>
#define PI 3.14159

/*
returns a sound struct countaining the peramiters of the sound wave.
*/
struct sound * gensine (float hertz, float sample_rate, float duration){
    int total = round(sample_rate * duration);
    float cycle = sample_rate / hertz;
    float mark = ( PI * 2)/cycle;
    float cSam = 0;
    float value;

    float *array;
    struct sound *wave = (struct sound *)malloc(sizeof(sound *));
    if(wave==NULL){

        return NULL;
    }
    array = (float*) malloc(total*sizeof(float));
    if(array==NULL){

        return NULL;
    }
 

    //assigns sin values to sample array
    for(int i = 0; i < total; ++i){
       value = sin(cSam);
        array[i]=value;
        cSam = cSam + mark;
    }

    
    
    wave -> samples = array;
    wave -> length = total;
    wave ->rate = sample_rate;

    return wave;

}

/*
    Creates a sound struct usind DTMF sounds
*/

struct sound * genDTMF(char key, float sample_rate, float duration){
    struct sound * toneA;
    struct sound * toneB;

    //creates 2 sound structs based on the provided char
    if(key == '1'){
        toneA = gensine(697, sample_rate, duration);
        toneB = gensine(1209, sample_rate, duration);
    }
    else if(key == '2'){
        toneA = gensine(697, sample_rate, duration);
        toneB = gensine(1336, sample_rate, duration);
    }
     else if(key == '3'){
        toneA = gensine(697, sample_rate, duration);
        toneB = gensine(1477, sample_rate, duration);
    }
     else if(key == 'a' || key == 'A'){
        toneA = gensine(697, sample_rate, duration);
        toneB = gensine(1633, sample_rate, duration);
    }
     else if(key == '4'){
        toneA = gensine(770, sample_rate, duration);
        toneB = gensine(1209, sample_rate, duration);
    }
     else if(key == '5'){
        toneA = gensine(770, sample_rate, duration);
        toneB = gensine(1336, sample_rate, duration);
    }
     else if(key == '6'){
        toneA = gensine(770, sample_rate, duration);
        toneB = gensine(1477, sample_rate, duration);
    }
     else if(key == 'b' || key == 'B'){
        toneA = gensine(770, sample_rate, duration);
        toneB = gensine(1633, sample_rate, duration);
    }
     else if(key == '7'){
        toneA = gensine(852, sample_rate, duration);
        toneB = gensine(1209, sample_rate, duration);
    }
     else if(key == '8'){
        toneA = gensine(852, sample_rate, duration);
        toneB = gensine(1336, sample_rate, duration);
    }
     else if(key == '9'){
        toneA = gensine(852, sample_rate, duration);
        toneB = gensine(1477, sample_rate, duration);
    }
     else if(key == 'c' || key == 'C'){
        toneA = gensine(852, sample_rate, duration);
        toneB = gensine(1633, sample_rate, duration);
    }
     else if(key == '*'){
        toneA = gensine(941, sample_rate, duration);
        toneB = gensine(1209, sample_rate, duration);
    }
     else if(key == '0'){
        toneA = gensine(941, sample_rate, duration);
        toneB = gensine(1336, sample_rate, duration);
    }
     else if(key == '#'){
        toneA = gensine(941, sample_rate, duration);
        toneB = gensine(1477, sample_rate, duration);
    }
     else if(key == 'd' || key == 'D'){
        toneA = gensine(941, sample_rate, duration);
        toneB = gensine(1633, sample_rate, duration);
    }
    else {
        printf("That value is not within the bounds\n");
        return 0;
    }

    //adds and divides by 2 the samples of toneA and B and puts the values back into toneA for return;
    for(int i = 0; i < toneA->length; ++i){
        toneA->samples[i]= (toneA->samples[i]+toneB->samples[i])/2;
    }

    //release memory created in gensine2 for toneB and it's samples array
    free(toneB-> samples);
    free(toneB);
    return toneA;
}

/*
    generates a silent tone using a vlaue of 0
*/
struct sound * genSilence(float sample_rate, float duration){
    
    int total = round(sample_rate * duration);
    float *array;
    struct sound *wave = (struct sound *)malloc(sizeof(sound *));
    if(wave==NULL){

        return NULL;
    }
    array = (float*) malloc(total*sizeof(float));
    if(array==NULL){

        return NULL;
    }

    // assignes 0 values to all elements in array
    for(int i = 0; i < total; ++i){
        array[i]=0.0;
    }

    wave -> samples = array;
    wave -> length = total;
    wave ->rate = sample_rate;

    return wave;
}

struct sound * genSquare(float hertz, float sample_rate, float duration){
    int total = round(sample_rate * duration);
    float cycle = sample_rate / hertz;
    float value;

    float *array;
    struct sound *wave = (struct sound *)malloc(sizeof(sound *));
    if(wave==NULL){

        return NULL;
    }
    array = (float*) malloc(total*sizeof(float));
    if(array==NULL){

        return NULL;
    }
 

    //assigns -1.0 or 1.0 values to sample array based on location within a period in the cycle
    for(int i = 0; i < total; ++i){
       value = fmodf(i,cycle);
       if(value < cycle/2){
            array[i]=-1.0;
        }else{
            array[i]=1.0;
        }
    }

    
    
    wave -> samples = array;
    wave -> length = total;
    wave ->rate = sample_rate;

    return wave;
}

struct sound * genTriangle(float hertz, float sample_rate, float duration){
    int total = round(sample_rate * duration);
    float cycle = sample_rate / hertz;
    float value;

    float *array;
    struct sound *wave = (struct sound *)malloc(sizeof(sound *));
    if(wave==NULL){

        return NULL;
    }
    array = (float*) malloc(total*sizeof(float));
    if(array==NULL){

        return NULL;
    }
 

    //assigns -1.0 to 1.0 values to sample array based on location within a period in the cycle
    for(int i = 0; i < total; ++i){
       value = fmodf(i,cycle);
       if(value < cycle/2){
            array[i]=4*(value/cycle)-1;
        }else{
            array[i]=-4*(value/cycle)+3;
        }
    }

    
    
    wave -> samples = array;
    wave -> length = total;
    wave ->rate = sample_rate;

    return wave;
}

struct sound * genSawtooth(float hertz,  float sample_rate, float duration){
        int total = round(sample_rate * duration);
    float cycle = sample_rate / hertz;
    float value;

    float *array;
    struct sound *wave = (struct sound *)malloc(sizeof(sound *));
    if(wave==NULL){

        return NULL;
    }
    array = (float*) malloc(total*sizeof(float));
    if(array==NULL){

        return NULL;
    }
 

    //assigns -1.0 or 1.0 values to sample array based on location within a period in the cycle
    for(int i = 0; i < total; ++i){
       value = fmodf(i,cycle);
       
        array[i]=2*(value/cycle)-1;
        
    }

    
    
    wave -> samples = array;
    wave -> length = total;
    wave ->rate = sample_rate;

    return wave;
}