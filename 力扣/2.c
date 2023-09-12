struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    struct ListNode *head=NULL,*tail=NULL;
    int flag=0;

    while(l1||l2)
    {
        int n1=l1?l1->val:0;
        int n2=l2?l2->val:0;
        int sum=(n1+n2+flag)%10;
        

        if(!head){
            head=tail=malloc(sizeof(struct ListNode));
            head->val=sum;
            head->next=NULL;
            tail->next=NULL;
        }else{
            tail->next=malloc(sizeof(struct ListNode));
            tail->next->val=sum;
            tail=tail->next;
            tail->next=NULL;
        }
        flag=(n1+n2+flag)/10;

        if(l1){
            l1=l1->next;
        }
        if(l2)
        {
            l2=l2->next;
        }
    }

    if(flag>0)
    {
        tail->next=malloc(sizeof(struct ListNode));
        tail->next->val=flag;
        tail=tail->next;
        tail->next=NULL;
    }

    return head;

}