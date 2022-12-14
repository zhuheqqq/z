#include<stdio.h>
#include<math.h>
int prime(int x)
{
  int i;
  for(i=2;i<=sqrt(x);i++)
  {
    if(x%i==0)
      return 0;
  }
  return 1;
}
int main()
{
  int n,i,m=3,k=0;
  scanf("%d",&n);
  n=pow(2,n)-1;
  for(i=3;m<=n;i++)
  {
    if(prime(m)==1)
    {
      printf("%d\n",m);
      k++;
    }
    m=pow(2,i)-1;  
  }
  if(k==0)
    printf("None");
  return 0;
}