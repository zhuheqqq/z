#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(void)
{
    char *str=(char *)malloc(sizeof(char));
    int i=0,n,cnt=0;
    // scanf("%s",str);
    // n=strlen(str);
    // for(i=0;i<n-1;i++){
    //     if(str[i]=='e'&&str[i+1]=='i'){
    //         cnt++;
    //     }
    // }
    // printf("%d",cnt);
    while((str[i]=getchar())!='#'){
        if(str[i]=='i'&&str[i-1]=='e'){
            cnt++;
        }
        i++;
    }
    printf("%d",cnt);
}
