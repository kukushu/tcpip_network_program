#include <string.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    char message[50];
    memset(message, 0, sizeof(message));

    int strlen_message = read(1, message, sizeof(message - 1));
    printf("the value of message : %d\n", strlen_message);
    puts(message);

    if (!strcmp(message, "q")) {
        printf("no \\n\n");
    } else {
        printf("need \\n\n");
    }


    return 0;
}
