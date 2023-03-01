#include "../lib/lib.h"

int main(int argc, char *argv[]) {
    int sock_id;

    if ((sock_id = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        error_handling("socket error");
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));

    while (1) {
        puts("enter q to quit:");
        char message[10];
        memset(message, 0, sizeof(message));
        fgets(message, sizeof(message), stdin);
        if (!strcmp(message, "q\n")) {
            break;
        }
        sendto(sock_id, message, sizeof(message) - 1, 0, (struct sockaddr *) &server_addr, sizeof(server_addr));
        struct sockaddr_in client_addr;
        memset(&client_addr, 0, sizeof(message));
        int client_addr_sz = sizeof(client_addr);
        int str_len = 0;
        str_len = recvfrom(sock_id, message, sizeof(message) - 1, 0, (struct sockaddr *) &client_addr, &client_addr_sz);
        message[str_len] = 0;
        printf("Message : %s\n", message);

    }


    close(sock_id);
    return 0;
}

