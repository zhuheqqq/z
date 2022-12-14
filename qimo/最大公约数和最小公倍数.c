#include <stdio.h>
#include <math.h>
int main(void)
{
	int m,n;
	int a;
	int c;
	scanf("%d %d",&m,&n);
	a = m*n;
	while(m != n)
	{
		if(m>n)
		{
			m = m-n;
		}else
		{
			n = n-m;
		}
	}
	c = a/m;
	printf("%d %d",m,c);
	return 0;
}

