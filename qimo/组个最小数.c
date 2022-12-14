#include<stdio.h>
int main(int argc, char const *argv[])
{
	int i,j;
	int x[9];
	for(i=0;i<10;i++)
		scanf("%d",&x[i]);
	for(i=1;i<10;i++)
		if(x[i])
		{	printf("%d",i);  x[i]--;  break;	}
	for(i=0;i<10;i++)
		while(x[i])
		{	printf("%d",i);	x[i]--;		}
	return 0;
}
