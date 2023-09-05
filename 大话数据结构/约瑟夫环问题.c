#include <stdio.h>
#include <stdlib.h>

// 定义一个节点结构表示圆圈中的人
struct Node {
    int data;            // 存储人的编号
    struct Node* next;   // 指向下一个节点
};

// 创建一个新的节点
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 移除指定节点，并返回下一个节点的指针
struct Node* removeNode(struct Node* current) {
    struct Node* nextNode = current->next;
    current->next = nextNode->next;
    free(nextNode);
    return current->next;
}

// 解决约瑟夫环问题
int josephus(int n, int m) {
    // 创建一个循环链表，表示圆圈中的人
    struct Node* head = createNode(1);  // 创建第一个人
    struct Node* current = head;

    for (int i = 2; i <= n; i++) {
        current->next = createNode(i);  // 创建其他人
        current = current->next;
    }
    current->next = head;  // 形成循环

    // 从起始位置开始数数和移除
    current = head;
    struct Node* prev = NULL;
    int count = 1;

    while (current->next != current) {  // 直到只剩下一个人
        if (count == m) {
            current = removeNode(current);  // 移除第M个人
            count = 1;
        } else {
            prev = current;
            current = current->next;
            count++;
        }
    }

    int survivor = current->data;
    free(current);
    return survivor;
}

int main() {
    int n, m;

    // 输入总人数和数数的步长
    printf("请输入总人数：");
    scanf("%d", &n);
    printf("请输入数数的步长：");
    scanf("%d", &m);

    // 调用josephus函数解决问题
    int survivor = josephus(n, m);

    // 输出最后剩下的人的编号
    printf("最后剩下的人的编号是: %d\n", survivor);

    return 0;
}
