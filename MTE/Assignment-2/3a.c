#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

int i;

void sighand(int sig){
    int pid,status;
    printf("Child with PID %d terminated with exit status %d\n", getpid(), i);
}

int main(){
  signal(SIGALRM, sighand);
  pid_t pid;
    int status;

    for (i = 1; i <= 5; i++){
        pid=fork();
        if(pid==0){
            printf("Child no. %d created with PID %d and parent PID %d\n",i,getpid(),getppid());
            alarm(i);
            for(;;);
            exit(i);
        }
    }
    sleep(10);  
    sleep(10);  
    sleep(10);  
}
