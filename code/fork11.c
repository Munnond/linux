#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<errno.h>
#include<fcntl.h>

int main(int argc,char* arhv[]) {
    int pid =fork();
    if(pid==-1){
        return 1;
    }
    if(pid==0){
        int file =open("pingResults.txt",O_WRONLY | O_CREAT,0777);
        if(file==-1){
            return 2;
        }
        printf("The fd to pingResults: %d\n",file);
        dup2(file,STDOUT_FILENO);
        // printf("The duplicated fd: %d\n",file2);
        close(file);
        // printf("Test\n");


        // child process
        int err = execlp("ping","ping","-c","3","google.com",NULL);
        if(err==-1){
            printf("Could not find program to execute!\n");
            return 2;
        }
        // printf("This should not be print on terminal");
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
        printf("Success!\n");
        printf("Some post processing goes here!\n");
    }

    
    return 0;
}