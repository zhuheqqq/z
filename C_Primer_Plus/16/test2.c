//调和平均数
#include <stdio.h>
#define HARMONIC_MEAN(X, Y) ( 1/(1/X+1/Y) )
int main(void)
{
 double x, y;
 scanf("%lf%lf",&x, &y);
 printf("harmonic mean of %g and %g : %g\n",x, y, HARMONIC_MEAN(x, y));
 return 0;
}