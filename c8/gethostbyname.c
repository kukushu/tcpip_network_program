#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

void error_handling(char *messae);

int main(int argc, char *argv[]) {
    struct hostent host;
    memset(&host, 0, sizeof(host));
    struct hostent *host_p;
    host_p = gethostbyname(argv[1]);
    if (!host_p) {
        error_handling("gethostbyname error");
    }
    host.h_addr_list = host_p->h_addr_list;
    host.h_addrtype = host_p->h_addrtype;
    host.h_aliases = host_p->h_aliases;
    host.h_length = host_p->h_length;
    host.h_name = host_p->h_name;

    printf("Official name : %s\n", host.h_name);
    for (int i = 0; host.h_aliases[i]; i ++) {
        printf("aliases %d : %s\n", i + 1, host.h_aliases[i]);
    }
    for (int i = 0; host.h_addr_list[i]; i ++) {
        printf("IP %d : %s\n", i + 1, inet_ntoa(*(struct in_addr *) host.h_addr_list[i]));
    }


    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputs("\n", stderr);
    exit(1);
}
