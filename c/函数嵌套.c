#include <stdio.h>

double calc_pow( double x, int n );

int main()
{
    double x;
    int n;

    scanf("%lf %d", &x, &n);
    printf("%.0f\n", calc_pow(x, n));

    return 0;
}

double calc_pow( double x, int n )
{
    // int i=1,j;
    // if(i<=n){
    //     j*=calc_pow(x,n);
    //     i++;
    // }
    // return j;
    int i,j;
    j=x;
    for(i=2;i<=n;i++){
        x*=j;
    }
    return x;
}
#include <stdio.h>
#include <math.h>
int isprime(int x);
int main(int argc,const char *argv[])
{
	int n,k;
	scanf("%d %d",&n,&k);
	int sum=0;
	for(int j=n;j>=2;j--)
	{
		if(isprime(j))
		{
			sum+=j;
	        if(k==1)
			{
			  printf("%d=",j);
	                    break;
			}
			if(j==2)
			{
			   printf("%d=",j);
		    }else
			{
		    	printf("%d+",j);
			}
			k--;
		}	
	}
	printf("%d",sum);
	return 0;
}
int isprime(int x)
{
	int flag=1;
	for(int i=2;i<=sqrt(x);i++)
	{
		if(x%i==0&&x!=2)
		{
			flag=0;
			break;
		}
	}
	return flag;
}