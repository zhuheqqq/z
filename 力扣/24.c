/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

//先判断特殊情况，然后双指针

struct ListNode* swapPairs(struct ListNode* head){
    if(head==NULL||head->next==NULL)
    {
        return head;
    }

    int flag=1;
    struct ListNode* ptr=malloc(sizeof(struct ListNode*));
    struct ListNode* tail=malloc(sizeof(struct ListNode*));

    ptr=head;
    tail=head->next;

    while(tail->next!=NULL)
    {
        int a=ptr->val;
        ptr->val=tail->val;
        tail->val=a;

        ptr=tail->next;
        if(ptr->next==NULL)
        {
            flag=0;
            break;
        }else{
            tail=ptr->next;
        }
        
    }
    if(flag==1)
    {
        int a=ptr->val;
        ptr->val=tail->val;
        tail->val=a;
    }
    

    return head;

}

//看官方题解用递归做更简单