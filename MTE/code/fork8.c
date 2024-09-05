#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<errno.h>

#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
int main(int argc,char* arhv[]) {
    if(mkfifo("mufifo",0777)==-1){
        if(errno!=EEXIST){
            printf("Could not create fifo file\n");
            return 1;
        }
    }
    printf("Opening...\n");
    int fd = open("myfifo",O_RDWR);
    printf("Opened\n");
    int x=97;
    write(fd,&x,sizeof(x));
    printf("Written\n");
    close(fd);
    printf("Closed\n");

    return 0;
}