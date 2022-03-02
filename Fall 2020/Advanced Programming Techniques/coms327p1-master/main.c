#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "gensnd.h"


/*
Creates a series of values between -1 and 1 for a given frequency (htz), Sample rate(htz), and duration (seconds)
*/
int main(){
    
    double freq;
    double sample;
    double duration;
    double sine;

    printf("Please input a frequency, sample, and duration: \n");

    scanf("%lf", &freq);
    scanf("%lf", &sample);
    scanf("%lf", &duration);

    gensine(freq,sample,duration);

    return 0;

}