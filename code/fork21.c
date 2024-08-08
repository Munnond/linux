#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<errno.h>
#include<time.h>

// 2 processes
// 1) Child process should generate random numbers and send them to the parent
// 2) Parent is going to sum all the numbers and print the result

int main(int argc,char* arhv[]) {
    int fd[2];
    if(pipe(fd)==-1){
        return 2;
    }
    int pid = fork();
    if(pid==0){
        close(fd[0]);
        int n,i;
        int arr[10];
        srand(time(NULL));
        n=rand()%10+1;
        printf("Generated: ");
        for(i=0;i<n;i++){
            arr[i]=rand()%11;
            printf("%d ",arr[i]);
        }
        if(write(fd[1],&n,sizeof(int))<0){
            return 4;
        }
        printf("\nSent n = %d\n",n);
        if(write(fd[1],arr,sizeof(int)*n)<0){
            return 3;
        }
        close(fd[1]);
    }
    else{
        close(fd[1]);
        // parent process

        int arr[10];
        int n,i,sum=0;
        if(read(fd[0],&n,sizeof(int))<0){
            return 5;
        }
        if(read(fd[0],arr,sizeof(int)*n)<0){
            return 6;
        }
        close(fd[0]);
        for(int i=0;i<n;i++){
            sum+=arr[i];
        }
        printf("Result is: %d\n",sum);
        wait(NULL);

    }
    return 0;
}