//打印
// A
// BC
// DEF
// GHIJ
// KLMNO
// PQRSTU
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
    for(i=0;i<n;i++){
        for(j=(i*(i+1)/2);j<((i+1)*(i+2))/2;j++){
            printf("%c",a[j]);
        }
        printf("\n");
    }
    return ;
}
//谢谢 今天的孽是自己造的