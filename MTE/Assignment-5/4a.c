#include <sys/ipc.h> 
#include <stdio.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/msg.h>

typedef struct msdgbuf{
    long type;
    char text[1024];
}message_buf;

int main()
{
    int msqid;
    key_t key;
    message_buf read_msg;
    key= ftok("/tmp/1234", 65);
    msqid=msgget(key, 0666 | IPC_CREAT);
    int c;
    c=(msgrcv(msqid, &read_msg, strlen(read_msg.text), -99, 0));
    read_msg.text[c]='\0';
    printf("Value of c %d\n", c);
    printf("Received Message : %s \n", read_msg.text);
    printf("Received Size : %ld\n", strlen(read_msg.text));
}