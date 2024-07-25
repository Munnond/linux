#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Hello my pid is %d\n", getpid());
    exit(0);
    return 0;
}