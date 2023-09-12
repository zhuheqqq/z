/*#include <stdio.h>
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
}*/



//
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
using namespace std;
typedef struct List{//链表
    int key;
    int password;
    struct List *next;
}list;
int n,m;
list *ans = NULL;
int pass[1001];
void add(){
    list *head,*body,*tail;
    head = (list*)malloc(sizeof(list));
    head->key = 1;
    head->password = pass[0];//赋值密码
    tail = head;
    for(int i = 2;i<=n;i++){
        body = (list*)malloc(sizeof(list));
        body->key = i;
        body->password = pass[i-1];
        tail->next = body;
        body->next = NULL;
        tail = body;
    }
    tail->next = head;//头尾链接，循环链表
    ans = head;
}
void solve(){
    int size = n;
    list *p = ans;
    list *parent = ans;//设置它为p的上一个指针.
    while(parent->next!=ans){
        parent = parent->next;
    }
    printf("依次离开的人:\n") ;
    while(p->next!=p){
        for(int i = 1;i<m;i++){//数到m的人离开
            parent = p;
            p = p->next;
        }
        printf("%d ",p->key);
        m = p->password;
        parent->next = p->next;
        free(p);
        p = parent->next;
    }
    printf("%d",p->key);
}
int main(){
    printf("请输入人数n和数值m :");
    scanf("%d%d",&n,&m);//n个人、每数到m出列 。
    printf("请输入%d个人的密码 :",n);
    for(int i = 0;i<n;i++){
    	scanf("%d",&pass[i]);
	}
    add();//先将n个人都加入链表
    solve();
    return 0;
}
 
 