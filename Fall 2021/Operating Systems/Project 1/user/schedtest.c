#include "user/user.h"


int main( int argc, char *argv[] )  {
    int loops = atoi(argv[1]);
    int count = atoi(argv[2]);
    int acc = 0;
    while (loops > 0){
        sleep(count);
        for(int i = 0; i < count; i++){
            acc += i;
        }
        acc =0;
    }
   exit(0);
}