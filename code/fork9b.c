#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<errno.h>

#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<time.h>

int main(int argc,char* arhv[]) {
    int arr[5];
    int fd = open("sum",O_RDONLY);
    if(fd==-1){
        return 1;
    }
    int i;
    for(i=0;i<5;i++){
        if(read(fd,&arr[i],sizeof(int))==-1){
            return 2;
        }
        printf("Recieved %d\n",arr[i]);
    }
    close(fd);

    int sum=0;
    for(int i=0;i<5;i++){
        sum+=arr[i];
    }
    printf("Result is %d\n",sum);
    return 0;
}