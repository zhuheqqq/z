#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(void)
{
    char *str=(char *)malloc(sizeof(char));
    int cnt=0,i=0,n;
    while((str[i]=getchar())!='#'){
        if(str[i]=='.'){
            str[i]='!';
            cnt++;
        }else if(str[i]=='!'){
            str[++i]='!';
            cnt++;
        }
        i++;
    }
    printf("%s",str);
    printf("%d\n",cnt);
    free(str);
    return 0;
    
}