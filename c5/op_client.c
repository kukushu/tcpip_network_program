#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>

#define SIZEOF_BUF 10

void error_handling(char *);

int main(int argc, char* argv[]) {
    int sock;
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        error_handling("socket error");
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
        error_handling("connect error");
    } else {
        puts("Connect............");
    }

    int message[10];
    memset(message, 0, sizeof(message));

    int count = 0;
    printf("Operate count : ");
    scanf("%d", &count);
    printf("\n");
    write(sock, &count, 4);


    for (int i = 0; i < count; i ++) {
        printf("Opetare %d : ", i + 1);
        scanf("%d", message + i);
        printf("\n");
    }
    
    char buf;

    printf("Operator : ");
    getchar(); 
    buf = getchar();
    printf("\n");

    write(sock, message, 4 * count);

    write(sock, &buf, 1);
    int result = 0;
    read(sock, &result, 4);

    printf("the result is : %d\n", result);

    







    close(sock);

    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputs("\n", stderr);
    exit(1);
}
