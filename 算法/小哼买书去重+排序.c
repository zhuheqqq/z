#include<stdio.h>
#include<stdlib.h>
int main(void)
{
    int i,j,t,n;
    scanf("%d",&n);
    int a[1100]={0};
    for(i=0;i<n;i++){
        scanf("%d",&t);
        a[t]=1;
    }
    for(i=0;i<1100;i++){
        if(a[i]==1){
            printf("%d ",i);
        }
    }

    return 0;
}