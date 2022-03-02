#include<stdio.h>

#include<math.h>
#include "process.h"
#include "gensnd.h"
#include<stdlib.h>



struct sound * mix(struct sound *s[], float w[], int c){


    int total = 0;
    for (int i = 0; i < c; i++){
        if(total < s[i]->length){
            total = s[i]->length;
        }
    }


    struct sound *wave = (struct sound *)malloc(sizeof(sound *));
        if(wave==NULL){

            return NULL;
        }
    float *array = (float*) malloc(total*sizeof(float));
        if(array==NULL){

            return NULL;
        }

//sets all values to zero for the new array
    for(int i = 0; i < total; i++){
        array[i]=0.0;
    }

    for (int i = 0; i < total; i++){
        for(int j = 0; j < c; j++){
            if(s[j]->length < total){
                array[i] = array[i] + 0.0;
        } else {
            array[i]= array[i]+((s[j]->samples[i])*(w[j]));
         }
        }

    }

    wave -> length = total;
    wave -> samples = array;
    wave -> rate = s[0]->rate;

    return wave;
}


// multiplys the sample values together
struct sound * modulate(struct sound *s1,struct sound *s2){
        if(s1->length != s2->length){
            return NULL;
        }

    int total = s1->length;

    struct sound *wave = (struct sound *)malloc(sizeof(sound *));
        if(wave==NULL){

            return NULL;
        }
    float *array = (float*) malloc(total*sizeof(float));
        if(array==NULL){

            return NULL;
        }

    for(int i = 0; i < total; i++){
        array[i] = (s1->samples[i]) * (s2->samples[i]);
    }

    wave -> length = total;
    wave -> samples = array;
    wave -> rate = s1->rate;

    return wave;

}


//filters a sound structure based on values in fir and c
struct sound * filter(struct sound *s, float fir[], int c){

    int total = s->length;

    struct sound *wave = (struct sound *)malloc(sizeof(sound *));
        if(wave==NULL){

            return NULL;
        }
    float *array = (float*) malloc(total*sizeof(float));
        if(array==NULL){

            return NULL;
        }

    for(int i = 0; i < total; i++){
        array[i]=0.0;
}


    for(int i = 0; i < total; i++){
        for(int j =0; j < c; j++){
            if(i-j > -1){
             array[i] = array[i] +((s->samples[i-j])*fir[j]);
                }
            }
        }

    wave -> length = total;
    wave -> samples = array;
    wave -> rate = s->rate;

    return wave;

}


// distorats sound to appear as if a sort echo happens 
struct sound * reverb(struct sound *s, float delay, float attenuation){
    
    if(s == NULL){
        return NULL;
    }

    if(delay > 0.1 || delay < 0.0){
        return NULL;
    }

    if(attenuation > 1.0 || attenuation < 0.0){
        return NULL;
    }
    
    int total = round(s->length*delay +1);
    float fir[total];

    for(int i = 0; i < total; i++){
        fir[i] = 0.0;
    }
    fir[0] = 1;
    fir[total -1] = attenuation;

    struct sound *wave = filter(s,fir,total);
    return wave;
}


//similar to reverb with wider delay window
struct sound * echo(struct sound *s, float delay, float attenuation){
    if(s == NULL){
        return NULL;
    }

    if(delay > 1.0 || delay < 0.1){
        return NULL;
    }

    if(attenuation > 1.0 || attenuation < 0.0){
        return NULL;
    }
    
    int total = round(s->length*delay +1);
    float fir[total];

    for(int i = 0; i < total; i++){
        fir[i] = 0.0;
    }
    fir[0] = 1;
    fir[total -1] = attenuation;

    struct sound *wave = filter(s,fir,total);
    return wave;
}