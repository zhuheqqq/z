#include<stdio.h>
#include<string.h>
int main(void)
{
    char str[100];
    char a[100];
    int i,j;
    gets(str);
    j=strlen(str);
    for(i=0;i<j;i++){
        if(str[i]>='a'&&str[i]<='z'){
            a[i]=219-(str[i]-'0');
        }
        if(str[i]>='A'&&str[i]<='Z'){
            a[i]=155-(str[i]-'0');
        }
    }
    puts(a);

    return 0;
}