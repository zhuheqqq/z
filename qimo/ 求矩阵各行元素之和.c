#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(void)
{
    int n,m,i,j;
    scanf("%d %d",&n,&m);
    int a[n][m];
    int b[n];
    memset(b,0,sizeof(b));
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            scanf("%d",&a[i][j]);
        }
    }
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            b[i]+=a[i][j];
        }
    }
    for(i=0;i<n;i++){
        printf("%d\n",b[i]);
    }
}