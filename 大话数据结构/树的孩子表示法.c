#define max_tree_size 100

typedef struct CTNode{//孩子结点
    int child;//结点在表头数组中的下标
    struct CTNode *next;
}*ChildPtr;

typedef struct{//表头结点
    int data;
    ChildPtr firstchild;
}CTBox;

typedef struct{//树结构
    CTBox nodes[max_tree_size];
    int r,n;
}CTree;