#include<stdio.h>
#include<string.h>
#include<stdlib.h>
// #include<unistd.h>
// #include<sys/wait.h>
// #include<errno.h>
#include <process.h>

int main(int argc,char* arhv[]) {
    _execvp("ping","ping","google.com",NULL);
    printf("Ping finished executing\n");
    return 0;
}