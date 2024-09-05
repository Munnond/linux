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
    int size;
    key_t key;
    message_buf msg_send;
    key= ftok("/tmp/1234", 65);
    msqid=msgget(key, 0666 | IPC_CREAT);

    printf("Enter Size:\n");
    scanf("%d", &size);
    printf("Enter you message : \n");
    scanf("%s",msg_send.text);
    msg_send.type=100-size;
    msgsnd(msqid, &msg_send, size, 0);
    printf("Message Sent.\n");
}