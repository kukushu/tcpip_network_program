#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>

#define SIZEOF_BUF 50

void error_handling(char *);
int main(int argc, char* argv[]) {
    int sock_id;
    struct sockaddr_in server_addr;
    char message_to_server[SIZEOF_BUF];
    char message_from_server[SIZEOF_BUF];
    
    memset(message_to_server, 0, sizeof(message_to_server));
    memset(message_from_server, 0, sizeof(message_from_server));
    memset(&server_addr, 0, sizeof(server_addr));

    if ((sock_id = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        error_handling("socket error");
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));
    if (connect(sock_id, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
        error_handling("connect error");
    } else {
        puts("Connected..................");
    }
   
   	while (1) { 
        puts("enter Q to quit");
        int strlen_mes = read(1, message_to_server, SIZEOF_BUF - 1);
        if (!strcmp(message_to_server, "q\n") || !strcmp(message_to_server, "Q\n")) {
            break;
        }
        write(sock_id, message_to_server, strlen(message_to_server));
        strlen_mes = read(sock_id, message_from_server, SIZEOF_BUF - 1);
        printf("message from server:%s\n", message_from_server);
        
        memset(message_from_server, 0, sizeof(message_from_server));
        memset(message_to_server, 0, sizeof(message_to_server));

    }
    close(sock_id);


    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputs("\n", stderr);
    exit(1);
}
