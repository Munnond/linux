#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>

#define MESSAGE_SIZE 1024  // Define maximum message size

// Define a structure for the message queue
struct msg_buffer {
    long msg_type;
    char msg_text[MESSAGE_SIZE];
};

int main(int argc, char *argv[]) {
    int message_size = atoi(argv[1]);
    long message_type = atol(argv[2]);
    int msgid;
    key_t key;
    struct msg_buffer msg;

    // Generate a unique key based on the file path
    key = ftok("/tmp/1234",'a');

    // Create a message queue
    msgid = msgget(key,0666|IPC_CREAT);

    // Prepare the message
    msg.msg_type = message_type;
    memset(msg.msg_text, 'A', message_size); // Fill the message with 'A'
    msg.msg_text[message_size] = '\0'; // Null-terminate the message text

    // Place the message in the message queue
    msgsnd(msgid, &msg,message_size, 0);

    printf("Message placed in queue with ID %d\n", msgid);

    return 0;
}