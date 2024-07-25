#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>

int main()
{

    pid_t CPID;

    printf("PId of Main Program: %d\n", (int)getpid());

    CPID = fork();

    printf("PId of Child Program: %d\n", (int)CPID);
    
    // if(CPID == (int)getpid()){
    //     printf("PIds of Child Program and Main Program are SAME\n");
    // }
    // else{
    //     printf("PIds of Child Program and Main Program are NOT SAME\n");
    // }

    return 0;
}