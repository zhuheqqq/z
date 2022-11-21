#include<stdio.h>
double square(double n);
int main(void)
{
    double n;
    printf("Please input a decimal:");
    scanf("%lf",&n);
    printf("%f",square(n));
    return 0;
}
double square(double n)
{
    double t;
    t=n*n*n;
    return t;
}
// #include<stdio.h>
// int MAX(int a,int b);
// int main(void)
// {
//     int a,b;
//     scanf("%d %d",&a,&b);
//     printf("%d",MAX(a,b));
//     return 0;
// }
// int MAX(int a,int b)
// {
//     return a>b?a:b;
// }