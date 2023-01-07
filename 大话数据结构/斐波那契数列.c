//递归实现
#include<stdio.h>
int Fbi(int i){
    if(i<2){
        return i==0?0:1;
    }
    return Fbi(i-1)+Fbi(i-2);
}

int main(void){
    int i;
    printf("递归显示：\n");
    for(i=0;i<40;i++){
        printf("%d ",Fbi(i));
    }
    return 0;
}