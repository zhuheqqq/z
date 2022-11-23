//打印
// F
// FE
// FED
// FEDC
// FEDCB
// FEDCBA
#include<stdio.h>
void print(char a[],int n);
int main(void)
{
    char a[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int n;
    scanf("%d",&n);
    print(a,n);

    return 0;

}
void print(char a[],int n)
{
    int i,j;
    for(i=n;i>=0;i--){
        for(j=0;j<=n-i;j++){
            printf("%c",a[n-j]);
        }
        printf("\n");
    }
    return ;
}