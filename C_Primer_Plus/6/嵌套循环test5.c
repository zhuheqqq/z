//打印金字塔
//     A
//    ABA
//   ABCBA
//  ABCDCBA
// ABCDEDCBA

#include <stdio.h>
#include<string.h>
int main(void)
{
	int n,i,b,c,d;
	char ch='A';
    char key,a[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    scanf("%c",&key);
    for(i=0;i<strlen(a);i++){
        if(a[i]==key){
            n=i+1;
        }
    }
	for(i=1;i<=n;i++)
	{
		ch='A';
		for(b=0;b<n-i;b++)
		{
			putchar(32);
		}
		for(c=0;c<i;c++)
		{
			printf("%c",ch++);
		}
		ch--;
		for(d=0;d<i-1;d++)
		{
			printf("%c",--ch);
		}
		printf("\n");
	}
	return 0;
}
