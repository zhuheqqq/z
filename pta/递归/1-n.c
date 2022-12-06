#include<stdio.h>
int plus(int n);
int main(void)
{
    int n;
    scanf("%d",&n);
     printf ("%d\n", plus(n));
}
int plus(int n)
{
    int sum=0,i;
    if(n<=0){
        return 0;
    }else{
        for(i=0;i<=n;i++){
            sum+=i;
        }
        return sum;
        
    }
}