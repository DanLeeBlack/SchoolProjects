#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "gensnd.h"
#include <string.h>

//checks if a charater is a valid input for a phone pad
int validChar(char c){
    char valid[] = "1234567890*#abcdABCD";
    int true = 0;
    for(int i = 0;i<strlen(valid);++i){
        if(c == valid[i]){
            true = 1;
            
        }
    }
    return true;
}

//prints sound samples values to stdout
void printSound(struct sound * s){
    int samples = s->length;
    for(int i = 0; i < samples; ++i){
        printf("%f\n",s->samples[i]);
    }
}


//makes DTMF output and sends to a file if provided otherwise will send to stdout
int main(int argc, char* argv[]){
    
    struct sound * noise;
//handles no input
    if(argc == 1){
        printf("To use program please enter one of the flowing styles of commands:\n\n");
        printf("dtmf 5551212 output.wav\n");
        printf("The above will print sample values for the number (5551212) into the provided file (output.wav)\n\n");
        printf("dtmf 5551212\n");
        printf("The aboe will print the sample vlaues for the numver(5551212) into the standard out\n");
        printf("valid inputs are (1,2,3,4,5,6,7,8,9,0,*,#,a,b,c,d,A,B,C,D)\n");
        return 0;
    }
    //checks the first input arguemnt for validity
    else if(argc ==2 || argc ==3){
        for(int i = 0; i < strlen(argv[1]); ++i){
            if( validChar( argv[1][i] ) == 0){
                fprintf(stderr,"Please input a valid numberpad value a a minimum\n");
                return 0;
            }
        }

    }

//sends first input arguemnet sample values to stdout
    if(argc == 2){
        for(int i = 0; i < strlen(argv[1]); ++i){
            noise = genDTMF2(argv[2][i],8000,.5);
            printSound(noise);
            free(noise->samples);
            free(noise);
            noise = genSilence(8000,.25);
            printSound(noise);
            free(noise->samples);
            free(noise);
        }
    }
    //sends first input arguemnet sample values to provided file in second input arguement
    else if(argc == 3){
        FILE *file;
        file = fopen(argv[2],"w+");

        for(int i = 0; i < strlen(argv[1]); ++i){
            noise = genDTMF2(argv[2][i],8000,.5);
            outputSound(noise,file);
            free(noise->samples);
            free(noise);
            noise = genSilence(8000,.25);
            outputSound(noise,file);
            free(noise->samples);
            free(noise);
        }
        fclose(file);
    }
    return 0;
}