#ifndef SOUND_H
#define SOUND_H

typedef struct sound_t sound;

struct sound {

    float *samples;
    int length;
    float rate;
    
};

#endif