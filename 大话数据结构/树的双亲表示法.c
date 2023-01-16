#define max_tree_size 100

typedef struct PTNode{//结点结构
    int data;//结点数据
    int parent;//双亲位置
}PTNODE;

typedef struct{//树位置
    PTNODE nodes[max_tree_size];//结点数组
    int r,n;//根的位置和结点数
}PTree;