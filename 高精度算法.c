//高精度加法
#include<stdio.h>
#include<string.h>
int main(void)
{
    int a[10000]={0},b[10000]={0},c[10000]={0},la,lb,lc,i;
    char s1[10000],s2[10000];
    scanf("%s",s1);
    scanf("%s",s2);
    la=strlen(s1);
    lb=strlen(s2);
    for(i=0;i<la;i++){
        a[la-i]=s1[i]-'0';
    }
    for(i=0;i<lb;i++){
        b[lb-i]=s2[i]-'0';
    }
    if(la>lb){
        lc=la;
    }else{
        lc=lb;
    }
    for(i=0;i<=lc;i++){
        c[i]+=a[i]+b[i];
        c[i+1]=c[i]/10;
        c[i]%=10;
    }
    if(c[lc]==0&&lc>0){
        lc--;
    }
    for(i=lc;i>0;i--){
        printf("%d",c[i]);
    }
    return 0;

}
#include<stdio.h>
#include<string.h>
int main(void)
{
    int len_max,i;   //len_max用来记录最大字符串长度，以便相加、输出
    char m[999],n[999];    
    int a[999]={0},b[999]={0},c[999]={0};//初始化为0，方便后续输出
    scanf("%s%s",m,n);
    if(strlen(m)>strlen(n))
        len_max=strlen(m);
    else len_max=strlen(n);
    for(i=0;i<strlen(m);i++){    
        a[i]=m[strlen(m)-1-i]-'0';//将低位放前面，高位放后面，以便进位
    }
    for(i=0;i<strlen(n);i++){
        b[i]=n[strlen(n)-1-i]-'0';
    }
    int k=0;    //用来进位
    for(i=0;i<=len_max;i++){    //不要忘了“=”
        c[i]=a[i]+b[i]+k;
        k=c[i]/10;
        c[i]%=10;
    }
    int flag=0;    //使用flag判断最高位并实现输出
    for(i=len_max;i>=0;i--){    //倒序输出
        if(c[i])
            flag=1;
        if(flag)
            printf("%d",c[i]);
    }
    if(!flag) printf("0");  //特判 0；
    return 0;
}
//高精度减法
#include<stdio.h>
#include<string.h>
int main(void)
{
    char s1[10000],s2[10000],s3[100000];
    int a[10000]={0},b[10000]={0},c[10000]={0},i,j=0,la,lb,lc;
    scanf("%s",s1);
    scanf("%s",s2);
    if(strlen(s1)<strlen(s2)){
        j=1;
        strcpy(s3,s1);
        strcpy(s1,s2);
        strcpy(s2,s3);
    }
     la=strlen(s1);
    lb=strlen(s2);
    for(i=0;i<la;i++){
        a[la-i]=s1[i]-'0';//这里从1开始，到la结束
    }
     for(i=0;i<lb;i++){
        b[lb-i]=s2[i]-'0';
    }
    if(la>lb){
        lc=la;
    }else{
        lc=lb;
    }
    for(i=1;i<=lc;i++){//所以这里也要从1开始
        if(a[i]<b[i]){
            a[i+1]--;
            c[i]=a[i]+10-b[i];
        }else{
            c[i]=a[i]-b[i];
        }
    }
    while(c[lc]==0&&lc>1){
        lc--;
    }
    if(j==1){
        printf("-");
    }
    for(i=lc;i>0;i--){
        printf("%d",c[i]);
    }
    return 0;
}
//高精度乘法
// #include<stdio.h>
// #include<string.h>
// int main()
// {
//     char s1[10000],s2[10000];
//     int a[10000],b[10000],c[10000]={0},i,j,la,lb,lc;
//     scanf("%s",s1);
//     scanf("%s",s2);
//     la=strlen(s1);
//     lb=strlen(s2);
//     for(i=0;i<la;i++){
//         a[la-i]=s1[i]-'0';//这里从1开始，到la结束
//     }
//      for(i=0;i<lb;i++){
//         b[lb-i]=s2[i]-'0';
//     }
//     lc=la+lb;
//     for(i=1;i<=la;i++){
//         for(j=1;j<=lb;j++){
//             c[i+j-1]+=a[i]*b[j];
//             c[i+j]+=c[i+j-1]/10;
//             c[i+j-1]%=10;
//         }
//     }
//         if(c[lc]==0&&lc>0){
//             lc--;
//         }
//         for(i=lc;i>0;i--){
//             printf("%d",c[i]);
//         }
//         return 0;

<<<<<<< HEAD
// }
=======
}
>>>>>>> 2869a05329134118fb092dc3da6dc54a26bcb3d0
