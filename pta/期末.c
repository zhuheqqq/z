//逆序
#include<stdio.h>
int main(void)
{
    int n,i,j=0;
    scanf("%d",&n);
    while(n>0){
        i=n%10;
        j=j*10+i;
        n/=10;
    }
    printf("%d",j);
    return 0;
}