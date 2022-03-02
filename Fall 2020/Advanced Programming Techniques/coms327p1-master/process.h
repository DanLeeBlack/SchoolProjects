#ifndef PROCESS_H
#define PROCESS_H



struct sound * mix(struct sound *s[], float w[], int c);

struct sound * modulate(struct sound *s1,struct sound *s2);

struct sound * filter(struct sound *s, float fir[], int c);

struct sound * reverb(struct sound *s, float delay, float attenuation);

struct sound * echo(struct sound *s, float delay, float attenuation);


#endif