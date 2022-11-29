#include<stdio.h>
void dou(int a[][5],int j);
int main(void)
{
    int a[3][5]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    int i,j;
    for(i=0;i<3;i++){
        for(j=0;j<5;j++){
            printf("%4d",a[i][j]);
        }
        printf("\n");
    }
    dou(a,3);
    return 0;
}
void dou(int a[][5],int j)
{
    int i,k;
    for(i=0;i<j;i++){
        for(k=0;k<5;k++){
            a[i][k]*=2;
        }
    }
    for(i=0;i<j;i++){
        for(k=0;k<5;k++){
            printf("%4d ",a[i][k]);
        }
        printf("\n");
    }
    return;
}