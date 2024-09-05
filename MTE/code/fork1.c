#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc,char* argv[]) {
    int id =fork();
    if(id!=0){
        fork();
    }
    // printf("Hello World from id: %d\n",id);
    printf("Hellow World\n");
    // if(id==0){
    //     printf("Hello from child process\n");
    // }
    // else{
    //     printf("Hellow from the main process\n");
    // }
    return 0;
}