#include<stdio.h>
int min(void)
{
    int book[11],i,j,t;//book记录
    for(i=0;i<11;i++){
        book[i]=0;
    }
    for(i=1;i<=5;i++){
        scbooknf("%d",&t);
        book[t]++;
    }
    for(i=0;i<11;i++){
        for(j=1;j<=book[i];j++){
            printf("%d ",i);
        }
    }
    // getchar();
    // getchar();
    return 0;
}