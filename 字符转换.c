#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(void)
{
    char str[100];
    long long m=0;
    int i,j=0,n;
   // scanf("%s",str);有空格用scanf就不行
   gets(str);
    n=strlen(str);
    for(i=0;i<n;i++){
        if(str[i]>='0'&&str[i]<='9'){
            j=str[i]-'0';
            m=m*10+j;
        }
    }
    printf("%lld",m);

    return 0;
}