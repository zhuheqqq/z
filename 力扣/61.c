//将最后一个节点与头节点相连，然后移动头指针即可

struct ListNode* rotateRight(struct ListNode* head, int k){
    struct ListNode* ptr=head;
    int n=0;
    if(ptr==NULL)
    {
        return head;
    }else{
        while(ptr->next!=NULL)
        {
            ptr=ptr->next;
            n++;
        }
        n=n+1;

        ptr->next=head;
        k=k%n;

        while(n-k)
        {
            head=head->next;
            k++;
        }
        while(ptr->next!=head)
        {
            ptr=ptr->next;
        }
        ptr->next=NULL;
    }
    return head;
        
}