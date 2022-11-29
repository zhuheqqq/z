#include<stdio.h>
#include<stdlib.h>
void buxiangqimingzi(int *a,int *b,int *c,int n);
int main(void)
{
    int n,i;
    scanf("%d",&n);
    int *a=(int *)malloc(sizeof(int)*n);
    int *b=(int *)malloc(sizeof(int)*n);
    int *c=(int *)malloc(sizeof(int)*n);
    for(i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    for(i=0;i<n;i++){
        scanf("%d",&b[i]);
    }
    for(i=0;i<n;i++){
        printf("%d ",a[i]);
    }
    printf("\n");
    for(i=0;i<n;i++){
        printf("%d ",b[i]);
    }
    printf("\n");
    buxiangqimingzi(a,b,c,n);

}
void buxiangqimingzi(int *a,int *b,int *c,int n)
{
    int i;
    for(i=0;i<n;i++){
        c[i]=a[i]+b[i];
    }
    for(i=0;i<n;i++){
        printf("%d ",c[i]);
    }
    return;
}
