#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<time.h>
#include<signal.h>

int main(int argc,char* arhv[]) {
    int pid=fork();
    if(pid==-1){
        return 1;
    }
    if(pid==0){
        while(1){
            printf("Some text goes here\n");
            usleep(50000);
        }
    }
    else{
        kill(pid,SIGSTOP);
        int t;
        do{
            printf("Time in seconds for exacution: ");
            scanf("%d",&t);
            if(t>0){
                kill(pid,SIGCONT);
                sleep(t);
                kill(pid,SIGSTOP);
            }
        }while(t>0);
        // kill(pid,SIGSTOP);
        // sleep(1);
        // kill(pid,SIGCONT);
        // sleep(1);
        kill(pid,SIGKILL);
        wait(NULL);
    }
    return 0;
}