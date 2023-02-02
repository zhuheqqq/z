#include "string.h"
#include "stdio.h"    
#include "stdlib.h"   

#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100 /* 存储空间初始分配量 */

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码,如OK等 */
typedef char TElemType;
typedef enum {Link,Thread} PointerTag;	/* Link=0表示指向左右孩子指针, */
										/* Thread=1表示指向前驱或后继的线索 */

typedef struct BiThrNode{
    TElemType data;
    struct BiThrNode *lchild,*rchild;
    PointerTag LTag;
    PointerTag RTag;
}BiThrNode,*BiThrTree; 

//前序输入构造二叉线索树
//0表示空结点
Status CreateBiThrTree(BiThrTree *T){
    TElemType h;
    scanf("%c",&h);

    if(h==0){
        *T=NULL;
    }else{
        *T=(BiThrTree)malloc(sizeof(BiThrNode));
        if(!*T){
            exit(0);
        }
        (*T)->data=h;
        CreateBiThrTree(&(*T)->lchild);
        if((*T)->lchild){
            (*T)->LTag=Link;
        }
        CreateBiThrTree(&(*T)->rchild);
        if((*T)->rchild){
            (*T)->RTag=Link;
        }
    }
    return OK;
}

//中序遍历进行中序线索化
BiThrTree pre;//全局变量指向刚刚访问过的结点
void InThreading(BiThrTree p){
    if(p){
        InThreading(p->lchild);
        if(!p->lchild){
            p->LTag=Thread;
            p->lchild=pre;
        }
        if(!pre->rchild)
        {
            pre->RTag=Thread;
            pre->rchild=p;
        }
        pre=p;
        InThreading(p->rchild);
    }
}