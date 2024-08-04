#include <stdio.h>
#include<sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include<sys/wait.h>

int count = 0;

int main() {  

    printf("Initial value of count: %d\n", count);

    pid_t pid = fork();

    if (pid < 0) {
        
    } else if (pid == 0) {
        count++;
        printf("Child process: count = %d\n", count);
        _exit(1);
    } else {
        wait(NULL);
        printf("Parent process: count = %d\n", count);
    }

}