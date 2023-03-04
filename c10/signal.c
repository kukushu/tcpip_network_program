#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void timeout(int signal) {
    if (signal == SIGALRM) {
        puts("alarm....");
        alarm(2);
    }
}

void keyboard(int signal) {
    if (signal == SIGINT) {
        puts("ctrl + c...");
    }
}






int main(int argc, char *argv[]) {
    signal(SIGALRM, timeout);
    signal(SIGINT, keyboard);
    alarm(2);
    for (int i = 0; i < 3; i ++) {
        puts("wait...............");
        sleep(100);
    }



    return 0;
}