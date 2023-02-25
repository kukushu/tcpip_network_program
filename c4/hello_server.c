#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>


// two arguments hello_server.c and port

void error_handling(char* );

int main(int argc, char* argv[]) {
    int sock_id;
    int client_sock_id;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int sizeof_client_addr;
    char* message = "just message";
    char str_arr[20];

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));
    memset(&str_arr, 0, sizeof(str_arr));


    if ((sock_id = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
        error_handling("socket error");
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[1]));
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sock_id, (struct sockaddr*) &server_addr, sizeof(server_addr)) == -1) {
        error_handling("bind error");
    }
    if (listen(sock_id, 10) == -1) {
        error_handling("listen error");
    }
    sizeof_client_addr = sizeof(client_addr);
    if ((client_sock_id = accept(sock_id, (struct sockaddr *) &client_addr, &sizeof_client_addr)) == -1) {
        error_handling("accetp error");
    }

    char *str;
    str = inet_ntoa(client_addr.sin_addr);
    strcpy(str_arr, str);
    int client_port = ntohs(client_addr.sin_port);
    printf("IP : %s  port : %d \n", str_arr, client_port); 


    int count = write(client_sock_id, message, strlen(message));
    close(sock_id);
    close(client_sock_id);



    return 0;
}

void error_handling(char* message) {
    fputs(message, stderr);
    fputs("\n", stderr);
    exit(1);
}
