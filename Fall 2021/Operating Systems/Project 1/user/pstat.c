#include "user/user.h"
#include "kernel/pstat.h"





//prints pstat values of processes
int main(){
   
   // creates a pstat structure and then fills it with values from using getpstat
   struct pstat ps;
   getpstat(&ps);
   
   
   printf("pid      ticks       queue \n");
   
   //iterates through ps to find inuse programs and prints there pstats where relevent
    for(int i = 0; i < NPROC; i++){
        if(ps.inuse[i] == 1){
        printf("  %d        %d      %d\n",ps.pid[i],ps.ticks[i], ps.queue[i]);
        }
    }
    return 0;
}