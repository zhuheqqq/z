#include<stdio.h>
int main(void)
{
    int n,i,j;
    printf("请输入天数：");
    scanf("%d",&n);
    i=n/7;
    j=n%7;
    if(i>1&&j>1){
        printf("%d days are %d weeks, %d days",n,i,j);
    }else if(i>1&&j<=1){
        printf("%d days are %d weeks, %d day",n,i,j);
    }else if(i<=1&&j>1){
        printf("%d days are %d week, %d days",n,i,j);
    }else {
        printf("%d day is %d week, %d day",n,i,j);
    }

    return 0;
}