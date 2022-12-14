#include <stdio.h>
#include <math.h>
#include <time.h>
 
int main()
{
    int n;
    scanf("%d",&n);
 
    for(int i=pow(10,n-1);i<=pow(10,n)-1;i++){
        int sum=0;
        int temp=i;
        while(sum<=i && temp!=0){//sum>i不用判断了，加快程序速度
            int every=1;
            int mod=temp % 10;
            for(int j=1;j<=n;j++) every*=mod;//位数的n次方
            sum+=every;//每一位求和
            temp/=10;
        }
        if(sum==i){
            printf("%d\n",i);
        }
    }
 
    return 0;
}