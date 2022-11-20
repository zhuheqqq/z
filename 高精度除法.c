//高精度除法1
#include<stdio.h>
#include<string.h>
int main(void)
{
    char s[10000];
    int i,a[100000],b,la,x=0,c[10000],lc;
    scanf("%s",s);
    scanf("%d",&b);
    la=strlen(s);
    for(i=1;i<=la;i++){
        a[i]=s[i-1]-'0';
    }
    for(i=1;i<=la;++i){
        c[i]=(x*10+a[i])/b;
        x=(x*10+a[i])%b;
    }
    lc=1;//0在第一位时需要删除
    while(c[lc]==0&&lc<la){
        lc++;
    }
    for(i=lc;i<=la;++i){
        printf("%d",c[i]);
    }
    return 0;
}