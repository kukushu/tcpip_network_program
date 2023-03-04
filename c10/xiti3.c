#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main() {
    int fd = open("test", O_RDONLY);
    __pid_t pid = fork();
    if (pid == 0) {
        printf("child %d \n", fd);
    } else {
        printf("parent %d \n", fd);
    }
    close(fd);
    puts("end");

    return 0;
}