#include "stdio.h"    
#include "stdlib.h"
#include "stdbool.h" 
#include "string.h"  

#include "math.h"  
#include "time.h"


#define MAXSIZE 100

typedef char String[MAXSIZE];
String str;


typedef struct BiTNode{
    char data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

void CreateBiTree(BiTree *T){
    char ch;
    int index=1;
    scanf("%c",&ch);
    ch=str[index++];
    if(ch=='#') 
		*T=NULL;
	else
	{
		*T=(BiTree)malloc(sizeof(BiTNode));
		if(!*T)
			exit(0);
		(*T)->data=ch; /* 生成根结点 */
		CreateBiTree(&(*T)->lchild); /* 构造左子树 */
		CreateBiTree(&(*T)->rchild); /* 构造右子树 */
	}

}