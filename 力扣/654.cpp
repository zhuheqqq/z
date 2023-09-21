/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

//递归
class Solution {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        return construct(nums,0,nums.size()-1);

    }

    TreeNode* construct(const vector<int>& nums,int left,int right){
        if(left>right)
        {
            return nullptr;
        }
        int big=left;
        for(int i=left+1;i<=right;i++)
        {
            if(nums[i]>nums[big])
            {
                big=i;
            }
        }

        TreeNode* node=new TreeNode(nums[big]);
        node->left=construct(nums,left,big-1);
        node->right=construct(nums,big+1,right);

        return node;
    }
};