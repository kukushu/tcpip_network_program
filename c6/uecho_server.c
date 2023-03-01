#include "../lib/lib.h"

int main(int argc, char *argv[]) {
    int sock_id;

    if ((sock_id = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        error_handling("socket error");
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(atoi(argv[1]));
    if (bind(sock_id, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
        error_handling("bind error");
    }

    for (int i = 0; i < 5; i ++) {
        printf("the %d time\n", i + 1);

        struct sockaddr_in client_addr;
        int client_addr_sz = sizeof(client_addr);
        int strlen = 0;
        char message[10];
        memset(message, 0, sizeof(message));
        if ((strlen = recvfrom(sock_id, message, 9, 0, (struct sockaddr *) &client_addr, &client_addr_sz)) == -1)
            error_handling("recvfrom error");
        if (sendto(sock_id, message, strlen, 0, (struct sockaddr *) &client_addr, client_addr_sz) == -1)
            error_handling("sento error");
        
        char str_arr[20];
        char *str_ptr;
        str_ptr = inet_ntoa(client_addr.sin_addr);
        strcpy(str_arr, str_ptr);
        printf("from %s\n", str_arr);
    }

    close(sock_id);
    return 0;
}

