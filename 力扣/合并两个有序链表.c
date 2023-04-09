/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2){
    struct ListNode*list3=(struct ListNode *)malloc(sizeof(struct ListNode));
    struct ListNode*p3=list3;
    struct ListNode*head=list3;
    
    while(list1!=NULL&&list2!=NULL){
        if(list1->val<list2->val){
            p3->next=list1;
            list1=list1->next;
            p3=p3->next;
            p3->next=NULL;
        }else{
            p3->next=list2;
            list2=list2->next;
            p3=p3->next;
            p3->next=NULL;
        }
    }
    if(list1==NULL){
            p3->next=list2;
        }else{
            p3->next=list1;
        }
    return head->next;

}