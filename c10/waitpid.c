#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int status;
    __pid_t pid = fork();
    if (pid == 0) {
        sleep(10);
        return 10;
    } else {
        while (!waitpid(-1, &status, WNOHANG)) {
            sleep(3);
            puts("sleep : 3 s");
        }
        if (WIFEXITED(status))
            printf("child send %d\n", WEXITSTATUS(status));
    }





    return 0;
}