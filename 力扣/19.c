//删除链表的倒数第n个节点
#include<stdio.h>
//Definition for singly-linked list.
struct ListNode {
int val;
struct ListNode *next;
};
 


struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
    int i=0,cnt=1;
    struct ListNode *p=head;
    struct ListNode *q=head->next;
    while(q!=NULL){
        p=q;
        q=q->next;
        cnt++;
    }

    if(n==1){
        if(cnt==1){
            return NULL;
        }else{
            p->next=NULL;
        }

    }

    q=head;

    if(cnt==n){
        return head->next;
    }

    for(i=0;i<cnt-n-1;i++){
        q=q->next;
    }
    q->next=q->next->next;

    
    return head;
    

}

//快慢指针解法
struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
    //设置哑结点
    struct ListNode* dummyHead = malloc(sizeof(struct ListNode));
    dummyHead->next = head;
    //设置双指针
    struct ListNode* fast = dummyHead;
    struct ListNode* slow = dummyHead;
    //fast 先走 N+1 步
    while (n--) {
        fast = fast->next;
    }
    fast = fast->next;
    //fast 和 slow 同时向后移动直到 fast 指向 NULL
    while (fast) {
        fast = fast->next;
        slow = slow->next;
    }
    //删除结点并释放结点空间
    struct ListNode* temp = slow->next;
    slow->next = slow->next->next;
    free(temp);
    //注意返回的是 dummy->next 而不是 head
    return dummyHead->next;
}

