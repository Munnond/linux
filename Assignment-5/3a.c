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
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <message_size> <message_type>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int message_size = atoi(argv[1]);
    long message_type = atol(argv[2]);
    int msgid;
    key_t key;
    struct msg_buffer msg;

    // Check if message_size is within valid bounds
    if (message_size <= 0 || message_size > MESSAGE_SIZE) {
        fprintf(stderr, "Invalid message size. Should be between 1 and %d bytes.\n", MESSAGE_SIZE);
        exit(EXIT_FAILURE);
    }

    // Generate a unique key based on the file path
    key = ftok("/tmp/1234", 'a');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create a message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Prepare the message
    msg.msg_type = message_type;
    memset(msg.msg_text, 'A', message_size); // Fill the message with 'A'
    msg.msg_text[message_size] = '\0'; // Null-terminate the message text

    // Place the message in the message queue
    if (msgsnd(msgid, &msg, message_size, 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    printf("Message placed in queue with ID %d\n", msgid);

    return 0;
}