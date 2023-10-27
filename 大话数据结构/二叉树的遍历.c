#include <stdio.h>
#include <stdlib.h>

// 二叉树节点结构
struct TreeNode {
    char data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// 创建一个新的二叉树节点
struct TreeNode* createNode(char value) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 构建二叉树
struct TreeNode* buildTree() {
    char value = getchar();
    if (value == '#') {
        return NULL; // 空节点
    }
    if (value == ' ') {
        return buildTree(); // 跳过空格并继续读取下一个字符
    }
    
    struct TreeNode* root = createNode(value);
    root->left = buildTree();
    root->right = buildTree();
    return root;
}

// 前序遍历
void preorderTraversal(struct TreeNode* root) {
    if (root == NULL) return;
    printf("%c ", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

// 中序遍历
void inorderTraversal(struct TreeNode* root) {
    if (root == NULL) return;
    inorderTraversal(root->left);
    printf("%c ", root->data);
    inorderTraversal(root->right);
}

// 后序遍历
void postorderTraversal(struct TreeNode* root) {
    if (root == NULL) return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%c ", root->data);
}

int main() {
    printf("请输入二叉树结构 (A/B/# 表示节点/左子树/空节点): ");
    struct TreeNode* root = buildTree();

    // 前序遍历
    printf("前序遍历结果: ");
    preorderTraversal(root);
    printf("\n");

    // 中序遍历
    printf("中序遍历结果: ");
    inorderTraversal(root);
    printf("\n");

    // 后序遍历
    printf("后序遍历结果: ");
    postorderTraversal(root);
    printf("\n");

    return 0;
}

