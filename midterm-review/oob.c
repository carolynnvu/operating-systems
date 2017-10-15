#include <stdio.h>

int main() {
    int y = 1498173264;
    char x[5];
    *((int *)x) = y;
    x[4] = '\0';
    printf("%d is %p\n", y,*x);
    return 0;
}
