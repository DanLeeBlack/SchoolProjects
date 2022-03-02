#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "process.h"
#include "gensnd.h"
#include <string.h>
#include "iosnd.h"


struct wave{
    char name[256];
    char type[9];
    float delay;
    float attenuation;
};

struct soundbox{
    char name[256];
    char waves[50][256];
    float values[50];
    int count;
};

struct song{
    char sName[256];
    int note;
    float start;
    float duration;
};








int main(int argc, char *argv[]){
  
   FILE *in = fopen(argv[0],"r");
   FILE *out = fopen(argv[1], "w+");
   int samplerate;
   struct wave waves[256];
   int waveCount = 0;
   struct soundbox box[256];
   int boxcount=0;
   struct song song[256];
   int songcount =0;
   struct song temp;
    char phase[256];
    float songlength;
    float hertz;
    struct sound *output;
    int counter = 0;
    struct sound *wavebox[256];
    float weight[256];
    int waveboxcount = 0;
    int counter2 = 0;
    struct sound *tempsound;

   if(in == NULL){
       printf("Error opening file");
       return 0;
   }
   
   fscanf(in, "%s", phase);

   if(strcmp(phase, "SAMPLERATE")== 0 ){
       fscanf(in, "%d", &samplerate);
   } else {
       printf("in file missing SAMPLERATE");
       return 0;
   }

   fscanf(in, "%s", phase);

   if(strcmp(phase, "WAVE")!= 0 ){
       printf("in file missing WAVE");
   }
    //assigns wave values
   while(strcmp(phase, "WAVE")== 0 || waveCount != 256){
       fscanf(in,"%s",waves[waveCount].name);
       fscanf(in,"%s",waves[waveCount].type);
       fscanf(in,"%f %f",&waves[waveCount].delay, &waves[waveCount].attenuation);
       waveCount++;
        if (waveCount == 256){
            printf("acheived max waves");
        }
       fscanf(in, "%s", phase);
   }

   if(strcmp(phase, "SOUND")!= 0 ){
       printf("in file missing SOUND");
   }
    //assigns unconstructed sound values
    while(strcmp(phase, "SOUND")== 0 && boxcount !=256){
       fscanf(in,"%s",phase);
        strcpy(box[boxcount].name,phase);
        box[boxcount].count = 0;
        fscanf(in,"%s",phase);
       while(strcmp(phase, "SOUND")!= 0 || strcmp(phase, "SONG")!=0){
           fscanf(in, "%f",&box[boxcount].values[box[boxcount].count]);
           box[boxcount].waves[box[boxcount].count];
            box[boxcount].count++;
           fscanf(in, "%s",phase);
       }
       boxcount++;
   }

    if(strcmp(phase, "SONG")!= 0 ){
       printf("in file missing SONG");
   }

    //allocates song values to array until eof file or array is maxed
   while(fscanf(in,"%s %d %f %f",song[songcount].sName,&song[songcount].note,&song[songcount].start,&song[songcount].duration)!= EOF|| songcount != 256){
       songcount++;
   }
   if(songcount==256){
       printf("Song values have maxed out at 256 values.  Program will continue with provided values");
   }
   //sorts song values depending there start time
    for(int i =0; i<songcount;i++){
        for(int j = 1; j < songcount ; j++){
            if(song[j].start < song[i].start){
                temp = song[i];
                song[i]=song[j];
                song[j]=temp;
            }
        }
    }

    //finds total length of song;
    songlength = song[0].start + song[0].duration;
    for(int i = 1; i < songcount;i++){
        if(song[i].start + song[i].duration > songlength){
            songlength = song[i].start + song[i].duration;
        }
    }

    //creates the values for the output sound array for allocation
    output->rate = (float)samplerate;
    output->length = round(songlength);
    output->samples = (float*) malloc(output->length*sizeof(float));
    if(output->samples==NULL){

        return 0;
    }

    // assignes 0 values to all elements in array
    for(int i = 0; i < output->length; ++i){
        output->samples[i]=0.0;
    }

    //allocates values to outputs samples by creating sounds from all previous inputs and allocating into the correct sample locations based on song struct start and duration values
    for(int i = 0; i < songcount;i++){
        //assigns values to hertz for the specific song value
        hertz = 2.0*((song[i].note-49.0)/12.0)*440.0;
        //finds the unconstructed sound to be constructed into an array for mixing
        while( strcmp(song[i].sName,box[counter].name)!=0 || counter==boxcount){
            counter++;
        }
        if(counter != boxcount){
            
            waveboxcount = box[counter].count;

            //makes values of an array of sounds and assigns weights as to weight array
            for(int j = 0; j < waveboxcount;j++){
                weight[j]=box[counter].values[j];
                while(strcmp(waves[counter2].name,box[counter].name)!=0 || counter2==waveCount){
                    counter2++;
                }
                 if(strcmp(waves[counter2].type,"sine") == 0){
                     wavebox[j] = gensine(hertz,samplerate,song[i].duration);
                 } else if(strcmp(waves[counter2].type,"square") == 0){
                    wavebox[j] = genSquare(hertz,samplerate,song[i].duration);
                 } else if(strcmp(waves[counter2].type,"triangle") == 0){
                     wavebox[j] = genTriangle(hertz,samplerate,song[i].duration);
                 } else if(strcmp(waves[counter2].type,"saw") == 0){
                     wavebox[j] = genTriangle(hertz,samplerate,song[i].duration);
                 }
                    //applies reverb and frees non reverbed sound
                 if(waves[counter2].delay > 0){
                     tempsound = wavebox[j];
                     wavebox[j] = reverb(tempsound, waves[counter2].delay,waves[counter2].attenuation);
                     free(tempsound);
                 }

            }
            //adds the desired sound into the output array and frees the now unneeded memory;
            tempsound = mix(wavebox,weight,waveboxcount);
            for(int k = 0; k < round(song[i].duration*samplerate);k++){
                int offset = k +  + round(song[i].start*samplerate);
                output->samples[offset] = output->samples[offset] + tempsound->samples[k];
            }
            free(tempsound);
            for (int k = 0; k < waveboxcount; k++){
                free(wavebox[k]);
            }
        }


    }

    outputSound(output, out);
    fclose(in);
    fclose(out);


}