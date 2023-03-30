//实现排列组合
#include<stdio.h>

int a[10],book[10],n;

void dfs(int step){
    int i;
    if(step==n+1){//临界条件
        for(i=1;i<=n;i++){
            printf("%d",a[i]);
        }
        printf("\n");

        return;
    }

    for(i=1;i<=n;i++){//尝试每一种可能
        if(book[i]==0){
            a[step]=i;
            book[i]=1;
            dfs(step+1);//继续下一步
            book[i]=0;
        }
    }
    return;//返回
}

int main(){
    scanf("%d",&n);
    dfs(1);
    getchar();
    getchar();

    return 0;
}