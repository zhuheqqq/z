#include<stdio.h>
int main(void)
{
    float n;
    char name[40];
    scanf("%f\n",&n);
    scanf("%s",name);
    printf("%s,you are %f meter tall",name,n/100.0);
}