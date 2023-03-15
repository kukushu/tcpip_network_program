#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>

void error_handling(char *message) {
    fputs(message, stderr);
    exit(1);
}

int main(int argc, char *argv[]) {
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    if ((serv_sock = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        error_handling("socket error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    
    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind        error");
    if (listen(serv_sock, 5) == -1)
        error_handling("list error");
  
    fd_set reads, temps;
    struct timeval timeout;
    socklen_t addr_sz = sizeof(clnt_addr);
    if ((clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_addr, &addr_sz)) == -1)
        error_handling("accept error");
    else 
        printf("new connect\n"); 
    FD_ZERO(&reads);
    FD_SET(clnt_sock, &reads);
    int maxfd = clnt_sock + 1;
    printf("server sock %d        client sock %d\n", serv_sock, clnt_sock);


    while (1) {
        temps = reads;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        int result = select(maxfd, &temps, 0, 0, &timeout);
        printf("result %d\n", result);
        if (result == -1) {
            error_handling("select error");
        } else if (result == 0) {
        } else {
            if (FD_ISSET(clnt_sock, &temps)) {
                char buf[100];
                int strlen = read(clnt_sock, buf, 99);
                if (strlen == 0) {
                    FD_CLR(clnt_sock, &reads);
                    close(clnt_sock);
                    break; 
                }
                printf("nice\n");
            }
        }

    }

    close(serv_sock);

    return 0;
}
