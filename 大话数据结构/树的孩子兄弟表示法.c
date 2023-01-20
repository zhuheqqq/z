#define max_tree_size 100

typedef struct CSNode{
    int data;
    struct CSNode *firstchild,*rightsib;
}CSNode,*CSNode;