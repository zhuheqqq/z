// #include<stdio.h>
// int main(void)
// {
//     float a,b;
//     b=2.0e20+1.0;
//     a=b-2.0e20;
//     printf("%f\n",a);
//     return 0;
// }
//float最多6-7位有效数字
//double最少13位有效数字，大约15-16位
#include<stdio.h>
int main(void)
{
    float f=7.89;
    float g=8.99;
    printf("%d %d",f,g);
}
//不会输出7,8,而是一些奇奇怪怪的负数