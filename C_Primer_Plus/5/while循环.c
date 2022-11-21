#include<stdio.h>
#define H 60
int main(void)
{
    int n;
    scanf("%d",&n);
    while(n>=0){
        int i,j;
        i=n/H;
        j=n%H;
        if(i<=1&&j<=1){
        printf("It is %d hour %d minute",i,j);
        }else if(i>1&&j>1){
        printf("It is %d hours %d minutes",i,j);
    }else if(i>1&&j<=1){
        printf("It is %d hours %d minute",i,j);
}else{
    printf("It is %d hour %d minutes",i,j);
}
scanf("%d",&n);
    }
    return 0;
}