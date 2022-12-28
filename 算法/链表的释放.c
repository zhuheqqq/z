void clearLink(link head)
{
    while(head->next!=NULL){
        q=head;
        head=head->next;
        free(q);
    }
}