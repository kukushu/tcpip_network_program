#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    __pid_t pid = fork();
    if (pid == 0) {
        printf("I am the child\n");
    } else {
        printf("I am parent\n");
        sleep(30);
    }
    if (pid == 0) {
        puts("end child\n");
    } else {
        puts("end parent\n");
    }

    return 0;
}
