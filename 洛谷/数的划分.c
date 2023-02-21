//用到dp
#include<stdio.h>  
int F[201][7];
int main(void)
{
    int i,j,n,m;
    scanf("%d%d",&n,&m);
//    for(i=1;i<=n;i++)F[i][1]=F[i][i]=1;
    F[0][0]=1;//i==j时方案数为1 
    for(i=1;i<=n;i++)
        for(j=1;j<=m&&j<=i;j++)
            F[i][j]=F[i-j][j]+F[i-1][j-1];
    printf("%d",F[n][m]);
    return 0;
}