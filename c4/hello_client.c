#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>

void error_handling(char *);
int main(int argc, char* argv[]) {
    int sock_id;
    struct sockaddr_in server_addr;
    char message[50];
    memset(message, 0, sizeof(message));
    memset(&server_addr, 0, sizeof(message));

    if ((sock_id = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        error_handling("socket error");
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));
    if (connect(sock_id, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
        error_handling("connect error");
    }
   
   	 
    int strlen_mes = read(sock_id, message, sizeof(message) - 1);
    if (strlen_mes == -1) 
        error_handling("read error");
    else 
    puts(message);
    close(sock_id);





    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputs("\n", stderr);
    exit(1);
}
