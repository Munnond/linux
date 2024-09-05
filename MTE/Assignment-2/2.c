#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
 
void signalhand(int signal){
    int pid,status;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        if (WIFEXITED(status)) {
            printf("Child with PID %d terminated with exit status %d\n", pid, WEXITSTATUS(status));
        }
    }
}

int main(){
    int i;
    signal(SIGCHLD, signalhand);
    pid_t pid;
    int status;
    for (i = 1; i <= 5; i++)
    {
        pid=fork();
        if(pid==0)
        {
            printf("Child no. %d created with PID %d and parent PID %d\n",i,getpid(),getppid());
            exit(i);
        }
       
    }
    sleep(10);
}