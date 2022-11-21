#include<stdio.h>
#include<float.h>
int main(void)
{
    double n=1.0/3.0;
    float m=1.0/3.0;
    printf("%.6f %.6f\n",n,m);
    printf("%.12f %.12f\n",n,m);
    printf("%.16f %.16f\n",n,m);
    printf("%d %d",FLT_DIG,DBL_DIG);

    return 0;
}