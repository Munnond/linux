#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO1 "/tmp/fifo1" // FIFO for file contents (server -> client)
#define FIFO2 "/tmp/fifo2" // FIFO for file name (client -> server)
#define BUFFER_SIZE 1024

void client() {
    // Open FIFO2 for writing (send file name to server)
    int fifo2 = open(FIFO2, O_WRONLY);
    if (fifo2 < 0) {
        perror("client open FIFO2");
        exit(EXIT_FAILURE);
    }

    // Open FIFO1 for reading (receive file contents from server)
    int fifo1 = open(FIFO1, O_RDONLY);
    if (fifo1 < 0) {
        perror("client open FIFO1");
        exit(EXIT_FAILURE);
    }

    // Get the file name from user input
    char filename[256];
    printf("Enter the file name: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0'; // Remove newline character

    // Send the file name to the server
    write(fifo2, filename, strlen(filename) + 1);
    close(fifo2); // Close FIFO2 after sending the file name

    // Read and display the file content from the server
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;
    while ((bytesRead = read(fifo1, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytesRead);
    }
    close(fifo1); // Close FIFO1 after reading the file content
}

void server() {
    // Open FIFO2 for reading (receive file name from client)
    int fifo2 = open(FIFO2, O_RDONLY);
    if (fifo2 < 0) {
        perror("server open FIFO2");
        exit(EXIT_FAILURE);
    }

    // Open FIFO1 for writing (send file contents to client)
    int fifo1 = open(FIFO1, O_WRONLY);
    if (fifo1 < 0) {
        perror("server open FIFO1");
        exit(EXIT_FAILURE);
    }

    // Read the file name from the client
    char filename[256];
    read(fifo2, filename, sizeof(filename));
    close(fifo2); // Close FIFO2 after receiving the file name

    // Open the file
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Read the file contents and send them to the client
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;
    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        write(fifo1, buffer, bytesRead);
    }
    close(fd); // Close the file descriptor
    close(fifo1); // Close FIFO1 after sending the file contents
}

int main() {
    // Create FIFOs (named pipes)
    if (mkfifo(FIFO1, 0666) < 0 ) {
        perror("mkfifo FIFO1");
        exit(EXIT_FAILURE);
    }
    if (mkfifo(FIFO2, 0666) < 0 ) {
        perror("mkfifo FIFO2");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process (server)
        server();
    } else {
        // Parent process (client)
        client();
        wait(NULL); // Wait for the child process to finish
        printf("\n");
    }

    // Remove FIFOs after use
    unlink(FIFO1);
    unlink(FIFO2);

    return 0;
}