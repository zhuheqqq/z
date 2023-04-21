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