#include <stdio.h>
struct test {
    int a;
    char b[1];
};
int main() {
    struct test aa;
    struct test bb;
    aa.a = 1;
    bb = aa;
    printf("%d\n", bb.a);

    return 0;
}
