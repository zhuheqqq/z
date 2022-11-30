#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char mystrncpy(char s1[],char s2[],int n);
int main(void)
{
    char *str=(char *)malloc(sizeof(char));
    int n;
    scanf("%d\n",&n);
    char *s1=(char *)malloc(sizeof(char)*n);
    gets(str);
    mystrncpy(s1,str,n-1);
    puts(s1);

}
char mystrncpy(char s1[],char s2[],int n)
{
     int i=strlen(s2),j=0;
     if(n>=i){
        for(j=0;j<i;j++){
            s1[j]=s2[j];
        }
        s1[i+1]='\0';
     }else{
        for(j=0;j<n;j++){
            s1[j]=s2[j];
        }
        s1[n+1]='\0';
     }

     return *s1;
}