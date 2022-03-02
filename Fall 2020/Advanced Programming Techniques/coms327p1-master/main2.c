#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "gensnd.h"

/* 
Takes an input of 10 chararacters (0-9, *,#,a-d/A-D) and creates a DTMF for each character followed by silence in the for of a value between -1 and 1 for a sample rate of 8000 htz
*/
int main(){

    char char1, char2, char3, char4, char5, char6, char7, char8, char9, char10;

    printf("please input the desired 10-digit telephone number\n");
    printf("input as a single string ie:\n");
    printf("18005551234\n");
    scanf("%c%c%c%c%c%c%c%c%c%c\n", &char1, &char2, &char3, &char4, &char5, &char6, &char7, &char8, &char9, &char10);

    genDTMF(char1);
    gensil(8000,.25);
    genDTMF(char2);
    gensil(8000,.25);
    genDTMF(char3);
    gensil(8000,.25);
    genDTMF(char4);
    gensil(8000,.25);
    genDTMF(char5);
    gensil(8000,.25);
    genDTMF(char6);
    gensil(8000,.25);
    genDTMF(char7);
    gensil(8000,.25);
    genDTMF(char8);
    gensil(8000,.25);
    genDTMF(char9);
    gensil(8000,.25);
    genDTMF(char10);
    

    return 0;
}