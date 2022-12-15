#include<stdio.h>
#include<string.h>
int main()
{char a[200],
b[10];
int k=0;
for(int i=0;i<4;i++){
scanf("%s",a);
int len=strlen(a);
b[k++]=a[len-2];
b[k++]=a[len-1]; }
b[k]='\0';
puts(b);
//printf("\n");
return 0;}
//藏为是