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



// #include<stdio.h>
// int main(void)
// {
//     int n;
//     scanf("%d",&n);
//     if(n==0){
//         printf("sign(%d) = 0",n);
//     }else if(n>0){
//         printf("sign(%d) = 1",n);
//     }else{
//         printf("sign(%d) = -1",n);
//     }
//     return 0;
// }



// #include<stdio.h>
// #include<stdlib.h>
// int main(void)
// {
//     int n,i,j,k=0,m=0,max,t,cnt=0;
//     scanf("%d",&n);
//     int (*a)[6]=(int(*)[6])malloc(sizeof(int)*n*6);
//     for(i=0;i<n;i++){
//         for(j=0;j<n;j++){
//             scanf("%d",&a[i][j]);
//         }
//     }
//     for(i=0;i<n;i++){
//         cnt=0;
//         max=a[i][0];
//         for(j=0;j<n;j++){
//             if(a[i][j]>max){
//                 max=a[i][j];
//                 k=i;
//                 m=j;
//             }
//             for(t=0;t<n;t++){
//                 if(max>a[t][j]){
//                     cnt=1;
//                 }
//             }
//             if(cnt==0){
//                 break;
//             }
//         }
//     }
//     if(cnt==1){
//         printf("NONE");
//     }else{
//         printf("%d %d",k,m);
//     }
// }


// #include <stdio.h>
// #define MAXN 6

// int main(void) {
//     int n, matrix[MAXN][MAXN], i, j, k, i_max, j_min;

//     scanf("%d", &n);  //输入阶数
//     for (i = 0; i < n; i++) {  //输入数据
//         for (j = 0; j < n; j++) {
//             scanf("%d", &matrix[i][j]);
//         }
//     }
//     for (i = 0; i < n; i++) {
//         i_max = matrix[i][0];
//         for (j = 0; j < n; j++) {  //找到该行最大数
//             if (matrix[i][j] > i_max) {
//                 i_max = matrix[i][j];
//             }
//         }
//         for (j = 0; j < n; j++) {
//             j_min = matrix[0][j];
//             for (k = 0; k < n; k++) {  //找到该列最小数
//                 if (matrix[k][j] < j_min) {
//                     j_min = matrix[k][j];
//                 }
//             }
//             if (matrix[i][j] == i_max) {
//                 if (matrix[i][j] == j_min) {
//                     printf("%d %d\n", i, j);

//                     return 0;
//                 }
//             }
//         }
//     }
//     printf("NONE\n");

//     return 0;
// }



// #include<stdio.h>
// #include<string.h>
// #include<stdlib.h>
// int main(void)
// {
//     char str[80];
//     gets(str);
//     int i=0,len;
//     len=strlen(str);
//     while(str[i]!='#'){
//         if(str[i]>='a'&&str[i]<='z'){
//             str[i]=str[i]-'a'+'A';
//         }else if(str[i]>='A'&&str[i]<='Z'){
//             str[i]=str[i]-'A'+'a';
//         }
//         i++;
//     }
//     for(i=0;i<len-1;i++){
//         printf("%c",str[i]);
//     }
//     return 0;
// }


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(void)
{
    char ch[80];
    int a[127]={0};
    int i;
    gets(ch);
    for(i=0;i<strlen(ch);i++){
        a[ch[i]]++;
    }
    for(i=0;i<127;i++){
        if(a[i]!=0){
            printf("%c",i);
        }
    }
    return 0;
}