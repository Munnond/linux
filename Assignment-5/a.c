#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_SIZE 100

struct message {
    long msg_type;
    char msg_text[MSG_SIZE];
};

int main() {
    int msgid;
    struct message msg;
    
    // Part (a): Create and delete message queue five times
    printf("Part (a): Create and delete message queues\n");
    for (int i = 0; i < 5; i++) {
        // Generate a unique key for each queue
        key_t key = ftok("/home/nisarg/Desktop/OS/Linux_Programing", i + 1);
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
        
        printf("Created message queue with id: %d\n", msgid);

        // Delete the message queue
        if (msgctl(msgid, IPC_RMID, NULL) == -1) {
            perror("msgctl");
            exit(EXIT_FAILURE);
        }
        
        printf("Deleted message queue with id: %d\n\n", msgid);
    }

    // Part (b): Create a message queue with IPC_PRIVATE and place a message in it
    printf("Part (b): Create message queues with IPC_PRIVATE and send messages\n");
    for (int i = 0; i < 5; i++) {
        // Create a message queue with IPC_PRIVATE
        msgid = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);
        if (msgid == -1) {
            perror("msgget");
            exit(EXIT_FAILURE);
        }
        
        printf("Created message queue with id: %d\n", msgid);

        // Prepare a message
        msg.msg_type = 1; // Message type
        snprintf(msg.msg_text, MSG_SIZE, "This is message %d", i + 1);

        // Send the message
        if (msgsnd(msgid, &msg, sizeof(msg.msg_text), 0) == -1) {
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }
        
        printf("Sent message to queue with id: %d\n\n", msgid);

        // Note: The message queue is not deleted here, but you can add that functionality if needed
    }

    return 0;
}
