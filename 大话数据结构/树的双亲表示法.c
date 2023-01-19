#define max_tree_size 100

typedef struct PTNode{//结点结构
    int data;//结点数据
    int parent;//双亲位置和下标若一致，则该下标中的data即为它的双亲
}PTNODE;

typedef struct{//树位置
    PTNODE nodes[max_tree_size];//结点数组
    int r,n;//根的位置和结点数
}PTree;

//静态链表