//逆序
// #include<stdio.h>
// int main(void)
// {
//     int n,i,j=0;
//     scanf("%d",&n);
//     while(n>0){
//         i=n%10;
//         j=j*10+i;
//         n/=10;
//     }
//     printf("%d",j);
//     return 0;
// }
// #include<stdio.h>
// #include<stdlib.h>
// #include<string.h>
// int main(void)
// {
//     int n,m,i,j;
//     scanf("%d %d",&n,&m);
//     int a[n][m];
//     int b[n];
//     memset(b,0,sizeof(b));
//     for(i=0;i<n;i++){
//         for(j=0;j<m;j++){
//             scanf("%d",&a[i][j]);
//         }
//     }
//     for(i=0;i<n;i++){
//         for(j=0;j<m;j++){
//             b[i]+=a[i][j];
//         }
//     }
//     for(i=0;i<n;i++){
//         printf("%d\n",b[i]);
//     }
// }
// #include<stdio.h>
// #include<math.h>
// int main(void)
// {
//     double a,b,c;
//     double s,area;
//     scanf("%lf %lf %lf",&a,&b,&c);
//     if(a+b>c&&a+c>b&&b+c>a){
//         s=(a+b+c)/2;
//         area=sqrt(s*(s-a)*(s-b)*(s-c));
//         printf("area = %.2f; perimeter = %.2f",area,2*s);
//     }else{
//         printf("These sides do not correspond to a valid triangle");
//     }
//     return 0;

// }
//interest=money×(1+rate) year−money
// #include<stdio.h>
// #include<math.h>
// int main(void)
// {
//     int year;
//     double mon,rate,inte;
//     scanf("%lf %d %lf",&mon,&year,&rate);
//     inte=mon*pow((1+rate),year)-mon;
// printf("interest = %.2f",inte);
// return 0;

// }