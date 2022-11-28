//十进制->二进制  未成功
#include<stdio.h>
void binary(unsigned long n);
int main(void)
{
    unsigned long n;
    printf("enter an integer:\n");
    while(scanf("lu",&n)==1){
        printf("binary equivalent:");
        binary(n);
        putchar('\n');
        printf("enter an integer:\n");
    }
    printf("Done.\n");
    return 0;
}
void binary(unsigned long n){
    int r;
    r=n%2;
    if(n>=2){
        binary(n/2);
    }
    putchar((r==0) ? '0':'1');
    return;
}
