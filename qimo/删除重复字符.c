#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(void)
{
    char ch[80];
    int a[127]={0};
    int i;
    gets(ch);
    for(i=0;i<strlen(ch);i++){
        a[ch[i]]++;
    }
    for(i=0;i<127;i++){
        if(a[i]!=0){
            printf("%c",i);
        }
    }
    return 0;
}//删除重复字符