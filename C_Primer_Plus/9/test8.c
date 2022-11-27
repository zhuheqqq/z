//改进power函数
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
double power(double x,int y);
int main(void)
{
    double n,j;
    int i;
    scanf("%lf %d",&n,&i);
    j=power(n,i);
    printf("%.2f",j);

    return 0;

}
double power(double x,int y)
{
    int i,j;
    if(y>0){
    for(i=1;i<y;i++){
        x*=x;
        return x;
    }
    }else{
        for(i=1;i<abs(y);i++){
            x*=x;
            return (1.0/x);
        }
    }
}