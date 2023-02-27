#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SIZEOF_BUF 10

void error_handling(char *);

int main(int argc, char *argv[]) {
    int sock_server_id;         //socket descriptor
    int sock_client_id;
    
    if ((sock_server_id = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        error_handling("sockte error");
    }
   
    struct sockaddr_in server_addr;         //address
    struct sockaddr_in client_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[1]));
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sock_server_id, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        error_handling("bind error");
    }

    if (listen(sock_server_id, 10) == -1) {
        error_handling("listen error");
    }

    int sizeof_addr = 0;
    for (int i = 0; i < 5; i ++) {
        sizeof_addr = sizeof(client_addr);
        if ((sock_client_id = accept(sock_server_id, (struct sockaddr *)&client_addr, &sizeof_addr)) == -1) {
            error_handling("accetp error");
        }

        char *str;
        char str_arr[20];
        str = inet_ntoa(client_addr.sin_addr);
        strcpy(str_arr, str);

        int client_port = ntohs(client_addr.sin_port);
        printf("IP : %s  port : %d \n", str_arr, client_port); 

/****************************
 * calculator
******************************************/
        int message[SIZEOF_BUF];
        memset(message, 0, sizeof(message));
        int count = 0;
        read(sock_client_id, &count, 4);
        printf("the message : %d\n", count); 

        read(sock_client_id, message, count * 4);
        char buf;
        int result;
        read(sock_client_id, &buf, 1);
        switch (buf) {
            case '+' : {
                    result = 0;
                    for (int i = 0; i < count; i ++) {
                        result += message[i];
                    }
                }
                break;
            case '*' : {
                    result = 1;
                    for (int i = 0; i < count; i ++) {
                        result *= message[i];
                    }
                }
                break;
            case '-' : {
                    result = message[0];
                    for (int i = 1; i < count; i ++) {
                        result -= message[i];
                    }
                }
            
        }
        printf("the result : %d\n", result);
        write(sock_client_id, &result, 4);

/***************************
 * end
********************************************************/

        close(sock_client_id);
        sizeof_addr = 0;
        memset(&client_addr, 0, sizeof(client_addr));
    }

    close(sock_server_id);
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputs("\n", stderr);
    exit(1);
}