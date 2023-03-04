#include <stdio.h>

void fun(int a) {
    printf("Value of a is %d\n", a);
}
int main() {
    int a[10];
    a[0] = 1;
    int (*aa)[10];
    aa = &a;

    printf("%d\n", (*aa)[0]);


    return 0;
}