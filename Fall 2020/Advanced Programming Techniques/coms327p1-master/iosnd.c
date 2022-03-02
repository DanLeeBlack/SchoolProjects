#include "iosnd.h"


//send the samples values to the provided file
int outputSound(struct sound *s, FILE * f){
   if(s == NULL|| s->samples ==NULL||s->length<1||s->rate < 1){
       return 1;
   }
   else{
    int samples = s->length;
    for(int i = 0; i < samples; ++i){
        fprintf(f,"%f\n",s->samples[i]);

    }
   }
    return 0;

}