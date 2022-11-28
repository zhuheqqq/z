#include<stdio.h>
#include<stdlib.h>
int main(void)
{
    int i,j,t,n;
    scanf("%d",&n);
    int *a=(int *)malloc(sizeof(int)*n);
    for(i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    for(i=0;i<n-1;i++){
        for(j=0;j<n-1-i;j++){
            if(a[j]>a[j+1]){
                t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
            }
        }
    }
    for(i=0;i<n;i++){
        printf("%d ",a[i]);
    }
    return 0;
}