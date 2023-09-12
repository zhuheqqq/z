
#include <stdio.h>

#define MAX_SIZE 1001

typedef struct Node {
    int key;
    int password;
    int next;
    int isDeleted;
} Node;

int n, m;
Node ans[MAX_SIZE];
int pass[MAX_SIZE];

void add() {
    for (int i = 1; i <= n; i++) {
        ans[i].key = i;
        ans[i].password = pass[i - 1];
        ans[i].next = (i % n) + 1;
        ans[i].isDeleted = 0;
    }
}

int findNext(int p) {
    int count = 0;
    while (count < m) {
        p = ans[p].next;
        if (!ans[p].isDeleted) {
            count++;
        }
    }
    return p;
}

void solve() {
    int size = n;
    int p = 1;

    printf("依次离开的人:\n");

    while (size > 0) {
        p = findNext(p);
        ans[p].isDeleted = 1;
        size--;
        if (size > 0) {
            printf("%d ", ans[p].key);
            m = ans[p].password;
        } else {
            printf("%d", ans[p].key);
        }
    }
}

int main() {
    printf("请输入人数n和数值m: ");
    scanf("%d%d", &n, &m);
    printf("请输入%d个人的密码: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &pass[i]);
    }
    add();
    solve();
    return 0;
}
