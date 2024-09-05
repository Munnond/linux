#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <time.h>


void signalhand(int signal){
    int pid,status;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        if (WIFEXITED(status)) {
            printf("Child with PID %d terminated with exit status %d\n", pid, WEXITSTATUS(status));

        }
    }
}


void child_handler(int signal){
    //printf("Child process with PID %d received SIGALRM and will now exit.\n", getpid());
    exit(1);
}

int main(){
    struct rusage start_usage, end_usage;
    int i;
    signal(SIGCHLD, signalhand);
    pid_t pid;

    getrusage(RUSAGE_SELF, &start_usage);


    int status;
    for (i = 1; i <= 5; i++){
        pid=fork();
        if(pid==0){
            signal(SIGALRM, child_handler);

            alarm(i);
            printf("Child no. %d created with PID %d and parent PID %d\n",i,getpid(),getppid());
            while (1) {
                pause();
            }
            exit(i);
        }
    }
    sleep(10);

    getrusage(RUSAGE_SELF, &end_usage);

    printf("Parent process time spent:\n");
    long long user_time_sec = end_usage.ru_utime.tv_sec - start_usage.ru_utime.tv_sec;
    long long user_time_usec = end_usage.ru_utime.tv_usec - start_usage.ru_utime.tv_usec;
    double user_time = user_time_sec + user_time_usec / 1e6;
    printf("User mode: %.6f seconds\n", user_time);

    long long sys_time_sec = end_usage.ru_stime.tv_sec - start_usage.ru_stime.tv_sec;
    long long sys_time_usec = end_usage.ru_stime.tv_usec - start_usage.ru_stime.tv_usec;
    double sys_time = sys_time_sec + sys_time_usec / 1e6;
    printf("System mode: %.6f seconds\n", sys_time);

    printf("Child processes time spent:\n");
    for (i = 1; i <= 5; i++) {
        int status;
        pid_t child_pid = waitpid(-1, &status, 0);
        if (child_pid > 0 && WIFEXITED(status)) {
            struct rusage child_usage;
            getrusage(RUSAGE_CHILDREN, &child_usage);
            
            long long child_user_time_sec = child_usage.ru_utime.tv_sec;
            long long child_user_time_usec = child_usage.ru_utime.tv_usec;
            double child_user_time = child_user_time_sec + child_user_time_usec / 1e6;
            
            long long child_sys_time_sec = child_usage.ru_stime.tv_sec;
            long long child_sys_time_usec = child_usage.ru_stime.tv_usec;
            double child_sys_time = child_sys_time_sec + child_sys_time_usec / 1e6;
            
            printf("Child with PID %d:\n", child_pid);
            printf("  User mode: %.6f seconds\n", child_user_time);
            printf("  System mode: %.6f seconds\n", child_sys_time);
        }
    }
    sleep(10); 
    return 0;
}