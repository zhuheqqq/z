#include<stdio.h>

int n,m,p,q,min=999999999;

int a[51][51],book[51][51];

void dfs(int x,int y,int step){
    int next[4][2]={
        {0,1},
        {1,0},
        {0,-1},
        {-1,0}
    };
    int tx,ty,k;
    if(x==p&&y==q){
        if(step<min){
            min=step;
        }
        return ;
    }
//枚举四种走法
    for(k=0;k<=3;k++){
        //计算下一个点的坐标
        tx=x+next[k][0];
        ty=y+next[k][1];
//判断是否越界
        if(tx<1||tx>n||ty<1||ty>m){
            continue;
        }
//判断是否为障碍物或者已经在路径中
        if(a[tx][ty]==0&&book[tx][ty]==0){
            book[tx][ty]=1;//标记已经走过
            dfs(tx,ty,step+1);//尝试下一个点
            book[tx][ty]=0;//尝试结束，取消标记
        }
    }
    return ;
}

int main()
{
    int i,j,startx,starty;
  //  读入n行m列
    scanf("%d %d",&n,&m);
//读入迷宫
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            scanf("%d",&a[i][j]);
        }
    }
    //读入起点和终点坐标
    scanf("%d %d %d %d",&startx,&starty,&p,&q);

    book[startx][starty]=1;
    dfs(startx,starty,0);

    printf("%d",min);
    getchar();
   // getchar();

    return 0;
}
