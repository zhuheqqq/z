#include<stdio.h>
int main() 
{
	int N,xsum=0;
	int s[1000],x[1000];
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		scanf("%d",&s[i]);
		x[i]=100;
	}
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
		{
			if(x[j]-s[i]>=0)
			{
				x[j]-=s[i];
				printf("%d %d\n",s[i],j+1);
				if(xsum<j+1)
					xsum=j+1;
				break;
			}
		}
	printf("%d\n",xsum);
	return 0;
}
//装箱问题