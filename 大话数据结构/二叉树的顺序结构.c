#include "stdio.h"
#include "stdlib.h"
#include <stdbool.h>

#include "math.h"
#include "time.h"

#define MAXSIZE 100       /* 存储空间初始分配量 */
#define MAX_TREE_SIZE 100 /* 二叉树的最大结点数 */

typedef struct
{
    int level, order; /* 结点的层,本层序号(按满二叉树计算) */
} position;

bool visit(int c)
{
    printf("%d\n", c);
    return true;
}

// 构造空二叉树，因为T是固定数组，不会改变，故不需要& 
bool InitBitree(int T[MAX_TREE_SIZE]){
    int i;
    for(i=0;i<MAX_TREE_SIZE;i++){
        T[i]=0;
    }
    return true;
}

//按层序次序输入二叉树中结点的值(字符型或整型), 构造顺序存储的二叉树T
bool CreateBiTree(int *T){
    int i=0;
    printf("请按层序输入结点的值(整型),0表示空结点,输999结束。结点数≤%d:\n",MAX_TREE_SIZE);
    while(i<10){
        T[i]=i+1;
        if(i!=0&&T[(i+1)/2-1]==0&&T[i]!=0){
            printf("出现无双亲的非根结点%d\n",T[i]);
			exit(0);
        }
        i++;
    }
    while(i<MAX_TREE_SIZE){
        T[i]=0;
        i++;
    }
    return true;
}

//判断是否为空
bool BiTreeEmpty(int *T){
    if(T[0]==0){//树为空
        return true;
    }
    return false;
}

//返回树的深度
int BiTreeDepth(int *T){
    int i,j=-1;
    for(i=MAX_TREE_SIZE-1;i>=0;i--){
        if(T[i]!=0){
            break;
        }
        i++;
        do{
            j++;
        }while(i>=powl(2,j));
        return j;
    }
}

//当T不空,用e返回T的根,返回OK;否则返回ERROR,e无定义
bool Root(int *T,int *e){
    if(BirTreeEmpty(T)){
        return false;
    }
    *e=T[0];
    return true;
}

//返回处于位置e(层,本层序号)的结点的值
int Value(int *T,position e){
    return T[(int)powl(2,e.level-1)+e.order-2];
}