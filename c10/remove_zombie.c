#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

void child_handler(int signal) {
    int status;
    __pid_t pid = waitpid(-1, &status, WNOHANG);
    if (WIFEXITED(status)) {
        printf("Child message : %d\n", WEXITSTATUS(status));
    }
}

int main(int argc, char *argv[]) {
    __pid_t pid;
    pid = fork();
    if (pid == 0) {
        printf("child\n");
        sleep(30); 
        return 3;
    } else {
        printf("parent begin\n");
        signal(SIGCHLD, child_handler);
        printf("after signal\n");
        sleep(40);
    }



    return 0;
}


