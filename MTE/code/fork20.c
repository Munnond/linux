#include<stdio.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

int x=0;

void handler_sigusr1(int sig){
    if(x==0)
        printf(" (HINT) Remember that multiplication is repetitive addition!\n");
}

int main(int argc,char* arhv[]) {
    int pid = fork();
    if(pid==-1){
        return 1;
    }

    if(pid==0){
        // child process
        sleep(5);
        kill(getppid(),SIGUSR1);
    }
    else{
        struct sigaction sa;
        sa.sa_flags = SA_RESTART;
        sa.sa_handler = &handler_sigusr1;
        sigaction(SIGUSR1,&sa,NULL);


        // parent process
        
        printf("What is the result of 3 x 5 : ");
        scanf("%d",&x);
        if(x==15){
            printf("Right!\n");
        }
        else{
            printf("Wrong!\n");
        }
        wait(NULL);
    }
    return 0;
}