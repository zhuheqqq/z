#include<stdio.h>
#include<string.h>
int main(void)
{
    char str[100];
    char k;
    int i,n,cnt=0;
    gets(str);
    scanf("%c",&k);
    n=strlen(str);
    for(i=0;i<n;i++){
        if(str[i]==k){
           cnt++;
        }
    }

    printf("%d",cnt);

    return 0;

}