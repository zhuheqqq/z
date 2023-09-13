#include <stdio.h>
#include <iostream>
using namespace std;

const int MAX_N = 1001;

typedef struct Node {
    int key;
    int password;
    int next; // 下一个节点的索引
} Node;

int n, m;
Node ans[MAX_N];
int pass[MAX_N];

void add() {
    for (int i = 1; i <= n; i++) {
        ans[i].key = i;
        ans[i].password = pass[i - 1];
        ans[i].next = i % n + 1; // 将链表连接成循环链表
    }
}

void solve() {
    int size = n;
    int p = 1; // 当前节点的索引
    int parent = n; // 上一个节点的索引

    printf("依次离开的人:\n");

    while (size > 0) {
        for (int i = 1; i < m; i++) {
            parent = p;
            p = ans[p].next;
        }

        printf("%d ", ans[p].key);
        m = ans[p].password;
        ans[parent].next = ans[p].next;
        size--;
        p = ans[p].next;
    }

    printf("\n");
}

int main() {
    printf("请输入人数n和数值m: ");
    scanf("%d%d", &n, &m);

    printf("请输入%d个人的密码: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &pass[i]);
    }

    add(); // 初始化静态链表
    solve();

    return 0;
}
