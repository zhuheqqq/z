typedef struct BiTNode{
    char data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;


BiTNode*  CreateBiTree(BiTree T){
    char ch;
    //scanf("%c",ch);
    if(ch=='#'){
        T=NULL;
    }else{
        T=(BiTree)malloc(sizeof(BiTNode*));
        T->data=ch;
        T->lchild=CreateBiTree(T->lchild);
        T->rchild=CreateBiTree(T->rchild);
    }
    return T;
}

void CreateBiTree(BiTree *T)
{ 
	char ch;
	int treeIndex=1;
	/* scanf("%c",&ch); */
	ch=str[treeIndex++];

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
