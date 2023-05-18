
#include<stdio.h>
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void preorder(struct TreeNode* root,int* res,int* returnSize)
{
    if(root==NULL)
    {
        return ;
    }
    res[(*returnSize)++]=root->val;
    preorder(root->left,res,returnSize);
    preorder(root->right,res,returnSize);
}

int* preorderTraversal(struct TreeNode* root, int* returnSize){
    int *res=(int *)malloc(sizeof(int)*500);
    *returnSize=0;
    preorder(root,res,returnSize);

    return res;

}