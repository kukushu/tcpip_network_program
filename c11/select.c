#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>

int main(int argc, char *argv[]) {
    fd_set fdread, temp;

    FD_ZERO(&fdread);
    FD_SET(0, &fdread);

    struct timeval timeout;


    while (1) {
        temp = fdread;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        int retval = select(1, &temp, 0, 0, &timeout);
        if (retval == 0) {
            puts("there is a timeout");
            continue;
        } else if (retval == -1) {
            puts("select error!");
            exit(1);
        } else {
            if (FD_ISSET(0, &temp)) {
                char buf[100];
                int strlen = read(0, buf, 99);
                buf[strlen] = 0;
                printf("message from console: %s\n", buf);
            }
        }

    }
    return 0; 
}