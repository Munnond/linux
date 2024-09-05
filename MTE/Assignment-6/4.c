#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <sys/ipc.h>

int main() {
    // Replace this with the actual UID of user A

    // Open "myfile" and print the file descriptor
    int fd = open("myfile", O_RDONLY);
    printf("Initial file descriptor: %d\n", fd);

    // Print the current user ID and effective user ID
    printf("Initial uid=%d, euid=%d\n", getuid(), geteuid());
    uid_t user_uid ;
    printf("Enter uid :");
    scanf("%d",&user_uid);
    setuid(user_uid);
    seteuid(user_uid);

    // Print the user ID and effective user ID after setuid() and seteuid()
    printf("After setuid and seteuid: uid=%d, euid=%d\n", getuid(), geteuid());

    close(fd);
    // Open "myfile" again and print the new file descriptor
    int new_fd = open("myfile", O_RDONLY);
    
    printf("New file descriptor: %d\n", new_fd);
    close(new_fd);

    return 0;
}
