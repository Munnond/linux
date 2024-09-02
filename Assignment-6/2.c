#include <stdio.h>
#include <unistd.h>

int main() {
    printf("uid=%d, euid=%d\n", getuid(), geteuid());
    return 0;
}
//sudo -s
//password
//./2
//chmod u+s ./2
//./2
//chmod u-s ./2
//./2
