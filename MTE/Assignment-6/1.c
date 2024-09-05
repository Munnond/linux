#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int flag = 0; // Global flag

void signal_handler(int signo) {
    if (signo == SIGUSR1) {
        flag = 1; // Set flag to 1 when SIGUSR1 is received
    }
}

void WAIT_PARENT() {
    // Wait until flag is set to 1
    while (flag == 0) {
        pause(); // Pause until a signal is received
    }
}

void TELL_CHILD(pid_t child_pid) {
    kill(child_pid, SIGUSR1); // Send SIGUSR1 to the child process
}

int main() {
    pid_t pid;

    // Install signal handler for SIGUSR1
    signal(SIGUSR1, signal_handler);
    

    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }
    else if (pid == 0) {
        // Child process
        WAIT_PARENT(); // Wait for signal from parent
        printf("Child process continues.\n");
        printf("Flag is :%d\n",flag);
        exit(0);
    } 
    else {
        // Parent process
        sleep(1); // Ensure child is ready to receive signal
        TELL_CHILD(pid); // Send signal to child
        printf("Parent process continues.\n");
        printf("Flag is :%d\n",flag);
        wait(NULL); // Wait for child process to finish
        exit(0);
    }
}
