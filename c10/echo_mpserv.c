#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *);
void child_proc(int signal);

int main(int argc, char *argv[]) {
    int sock_id;
    int client_sock_id;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    if ((sock_id = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        error_handling("socket error");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[1]));
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sock_id, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1)
        error_handling("bind error");
    if (listen(sock_id, 10) == -1)
        error_handling("listen error");
    
    signal(SIGCHLD, child_proc);

    while (1) {
        int client_addr_sz = sizeof(client_addr);
        client_sock_id = accept(sock_id, (struct sockaddr *) &client_addr, &client_addr_sz);
        if (client_sock_id == -1) {
            puts("accept -1");
            continue;
        }
        puts("there is a new child\n");
        __pid_t pid = fork();
        if (pid == -1) {
            puts("fork -1");
            close(client_sock_id);
            continue;
        } else if(pid == 0) {
            close(sock_id);
            int strlen = 0;
            char buf[100];
            while ((strlen = read(client_sock_id, buf, 100)) != 0) {
                write(client_sock_id, buf, strlen);
            }
            close(client_sock_id);
            puts("client dissconnected......");
            return 0;
        } else {
            close(client_sock_id);
        }
    }
    close(sock_id);
    return 0;
}

void error_handling(char *message) {
    puts(message);
    exit(1);
}
void child_proc(int signal) {
    int status;
    waitpid(-1, &status, WNOHANG);
    puts("remove child proc");
}