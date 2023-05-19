#include<stdio.h>
/**
 * Definition for a Node.*/
struct Node {
    int val;
    int numChildren;
    struct Node** children;
};
 

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

void helper(struct Node*root,int* res,int* pos)
{
    if(root==NULL)
    {
        return ;
    }
    res[(*pos)++]=root->val;
    for(int i=0;i<root->numChildren;i++)
    {
        helper(root->children[i],res,pos);
    }
}

int* preorder(struct Node* root, int* returnSize) {
    int *res=(int *)malloc(sizeof(int)*10000);
    int pos=0;
    helper(root,res,&pos);
    *returnSize=pos;

    return res;
    
}