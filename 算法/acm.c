// #include<stdio.h>
// int main(void){
//     int a,b;
//     while(scanf("%d %d",&a,&b)!=EOF){
//         printf("%d\n",a+b);
//     };
//     return 0;
// }
#include<stdio.h>
int main(void){
    int n;
    while(scanf("%d",&n)!=EOF){
        int i,j=0;
        for(i=1;i<=n;i++){
        j+=i;
    }
    printf("%d\n",j);
    printf("\n");
    };
    return 0;
}