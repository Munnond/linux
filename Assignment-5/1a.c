// C Program for Message Queue (Writer Process) 
#include <stdio.h> 
#include <stdlib.h>
#include <sys/ipc.h> 
#include <sys/msg.h>

#define MSG_SIZE 100 

// structure for message queue 
struct message { 
	long mesg_type; 
	char mesg_text[MSG_SIZE]; 
}; 

int main() 
{ 
	int msgid;
    struct message msg;
    
    printf("Part(a):\n\n");

    for(int i=0;i<5;i++){
        key_t key = ftok("/home/nisarg/Desktop/OS/Linux_Programing/Assignment-5",i+1);
        if(key==-1){
            return 1;
        }

        //create a message queue
        msgid = msgget(key,0666 | IPC_CREAT);

        if(msgid==-1){
            return 2;
        }

        printf("Created message queue with id : %d\n",msgid);

        // delete the message queue
        if(msgctl(msgid,IPC_RMID,NULL)==-1){
            return 3;
        }

        printf("Deleted message queue with id : %d\n\n",msgid);

    }

    printf("Part(b):\n\n");

    for(int i=0;i<5;i++){
        msgid = msgget(IPC_PRIVATE,0666 | IPC_CREAT);
        if(msgid==-1){
            return 4;
        }

        printf("created message queue with id : %d\n",msgid);

        msg.mesg_type=1;

        snprintf(msg.mesg_text,MSG_SIZE,"This is message %d",i+1);

        if(msgsnd(msgid , &msg,sizeof(msg.mesg_text),0)==-1){
            return 5;
        }

        printf("Sent message to queue with id : %d\n\n",msgid);
    }

	return 0; 
} 
