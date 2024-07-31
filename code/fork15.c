#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<fcntl.h>

int main(int argc,char* arhv[]) {
    int pid = fork();
    if(pid==-1){
        return 1;
    }

    if(pid==0){
        // child process
        int err = execlp("ping","ping","-c","1","google.com",NULL);
        if(err==-1){
            printf("Could not find program to execute!\n");
            return 2;
        }

    }
    else{
        int wstatus;
        // parent process
        wait(&wstatus);
        if(WIFEXITED(wstatus)){
            int statusCode= WEXITSTATUS(wstatus);
            if(statusCode==0){
                printf("Success!\n");
            }
            else{
                printf("Failure with status code %d\n",statusCode);
            }
        }
        printf("Some post processing goes here!\n");
    }
    return 0;
}