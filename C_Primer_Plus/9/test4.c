#include<stdio.h>
 double harmonic_mean(double x,double y);
 int main(void)
 {
    double i,j;
    scanf("%lf %lf",&i,&j);
    printf("%.2f",harmonic_mean(1.0/i,1.0/j));

    return 0;
 }
  double harmonic_mean(double x,double y)
 {
    double aver;
    aver=(x+y)/2.0;
    return (1.0/aver);
 }