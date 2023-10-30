#include <stdio.h>

int main() {
    int a[5] = {1,2,3,4,5,0};
    printf("%zu\n", sizeof(a));
    int *ptr  = (int*)(&a+1);
    printf("%zu\n", sizeof(ptr));
    printf("%d\n", *(ptr-1));

    return 0;
}