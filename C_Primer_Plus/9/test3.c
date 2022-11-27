#include<stdio.h>
void print(char x,int y,int z);
int main(void)
{
    char ch;
    int m,n,i;
    scanf("%c",&ch);
    scanf("%d %d",&m,&n);
    print(ch,m,n);
    return 0;

}
void print(char x,int y,int z){
    int i,j;
    for(i=0;i<z;i++){
        for(j=0;j<y;j++){
            printf("%c",x);
        }
        printf("\n");
    }
    return;
}