#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include<sys/wait.h>

int count = 0;

int main() {
    pid_t pid;

    printf("Initial value of count: %d\n", count);

    pid = vfork(); 
    // change above to fork

    if (pid < 0) {
        perror("vfork failed");
        exit(1);
    }
    else if (pid == 0) {
        count++;
        printf("Child process: count = %d\n", count);
        _exit(0); 
    } 
    else {
        printf("Parent process: count = %d\n", count);
    }

    return 0;
}