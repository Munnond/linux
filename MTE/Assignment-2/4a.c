#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/resource.h>


int i;

void print_rusage()
{
    struct rusage usage;

    getrusage(RUSAGE_SELF, &usage);
    double user_time = usage.ru_utime.tv_sec + usage.ru_utime.tv_usec/1e6;
    double sys_time = usage.ru_stime.tv_sec + usage.ru_stime.tv_usec/1e6;
    printf("Parent time in user mode: %f seconds\n", user_time);
    printf("Parent time in system mode: %f seconds\n", sys_time);

    getrusage(RUSAGE_CHILDREN, &usage);
    user_time = usage.ru_utime.tv_sec + usage.ru_utime.tv_usec/1e6;
    sys_time = usage.ru_stime.tv_sec + usage.ru_stime.tv_usec/1e6;
    printf("Child time in user mode: %f seconds\n", user_time);
    printf("Child time in system mode: %f seconds\n", sys_time);
}
void sighand(int sig)
{
    int pid,status;
    printf("Child with PID %d terminated with exit status %d\n", getpid(), i);
}

int main()
{
    signal(SIGALRM, sighand);
    pid_t pid;
    int status;

    for (i = 1; i <= 5; i++)
    {
        pid=fork();
        if(pid==0)
        {
            printf("Child no. %d created with PID %d and parent PID %d\n",i,getpid(),getppid());
            alarm(i);
            sleep(5);
            exit(i);
        }
    }
    while(wait(NULL)>0); 
    print_rusage();
    sleep(10);  
}
