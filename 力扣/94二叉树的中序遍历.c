#include<stdio.h>
/**
 * Definition for a binary tree node.
**/
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
 


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

void preorder(struct TreeNode* root,int *res,int* returnSize)
{
    if(root==NULL)
    {
        return;
    }
    preorder(root->left,res,returnSize);
    res[(*returnSize)++]=root->val;
    preorder(root->right,res,returnSize);
}

int* inorderTraversal(struct TreeNode* root, int* returnSize){
    int *res=(int *)malloc(sizeof(int)*2000);
    *returnSize=0;
    preorder(root,res,returnSize);

    return res;

}