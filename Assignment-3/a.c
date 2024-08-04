#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 1024

void client(int pipe2[], int pipe1[]) {
    close(pipe2[0]); // Close unused read end of pipe2
    close(pipe1[1]); // Close unused write end of pipe1

    // Get the file name from user input
    char filename[256];
    printf("Enter the file name: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0'; // Remove newline character

    // Send the file name to the server
    write(pipe2[1], filename, strlen(filename) + 1);
    close(pipe2[1]); // Close write end of pipe2 after sending the file name

    // Read and display the file content from the server
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;
    while ((bytesRead = read(pipe1[0], buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytesRead);
    }
    close(pipe1[0]); // Close read end of pipe1
}

void server(int pipe2[], int pipe1[]) {
    close(pipe2[1]); // Close unused write end of pipe2
    close(pipe1[0]); // Close unused read end of pipe1

    // Read the file name from the client
    char filename[256];
    read(pipe2[0], filename, sizeof(filename));
    close(pipe2[0]); // Close read end of pipe2 after receiving the file name

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
        write(pipe1[1], buffer, bytesRead);
    }
    close(fd); // Close the file descriptor
    close(pipe1[1]); // Close write end of pipe1 after sending the file contents
}

int main() {
    int pipe1[2], pipe2[2];

    // Create the pipes
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process (server)
        server(pipe2, pipe1);
    } else {
        // Parent process (client)
        client(pipe2, pipe1);
        wait(NULL); // Wait for the child process to finish
        printf("\n");
    }

    return 0;
}