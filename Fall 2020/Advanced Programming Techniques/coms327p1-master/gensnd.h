#ifndef GENSND_H
#define GENSND_H

#include "sound.h"



struct sound * gensine (float hertz, float sample_rate, float duration);

struct sound * genDTMF(char key, float sample_rate, float duration);

struct sound * genSilence(float sample_rate, float duration);

struct sound * genSquare(float hertz, float sample_rate, float duration);

struct sound * genTriangle(float hertz, float sample_rate, float duration);

struct sound * genSawtooth(float hertz,  float sample_rate, float duration);

#endif