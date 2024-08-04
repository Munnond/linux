#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define NUM_CHILDREN 5

void signal_handler(int sig) {
    int status;
    pid_t pid;

    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        if (WIFEXITED(status)) {
            printf("Child with PID %d exited with status %d\n", pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child with PID %d terminated by signal %d\n", pid, WTERMSIG(status));
        }
    }
}

int main() {
    pid_t pid;
    struct sigaction sa;

    // Set up the signal handler
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // Fork 5 children
    for (int i = 0; i < NUM_CHILDREN; i++) {
        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            int alarm_time = i + 1;
            printf("Child %d with PID %d setting alarm for %d seconds\n", i, getpid(), alarm_time);
            alarm(alarm_time); // Set alarm to expire after i + 1 seconds
            pause(); // Wait for the alarm to expire
            exit(i); // Exit with status i
        }
    }

    // Parent process waits for all children to exit
    while (1) {
        pause(); // Wait for signals
    }

    return 0;
}