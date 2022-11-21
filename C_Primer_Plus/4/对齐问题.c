#include<stdio.h>
#include<string.h>
int main(void)
{
    char name1[40],name2[40];
    printf("Please input your first name:");
    scanf("%s",name1);
    printf("Please input your last name:");
    scanf("%s",name2);
    int n1,n2;
    n1=strlen(name1);
    n2=strlen(name2);
    printf("%s %s\n",name1,name2);
    printf("%*d",n1,n1);//特殊用法，*可以替换成n1
    printf("%*d\n",n2+1,n2);
    printf("%s %s\n",name1,name2);
    printf("%-d%*d",n1,n1+1,n2);
    return 0;
}