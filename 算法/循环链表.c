//将单链表的首尾相接，将终端节点的指针域改为指向头节点，构成单循环链表
NODE *create()
{
    NODE *head,*p,*q;
    int t;
    head=(struct node *)malloc(sizeof(NODE));
    p=head;
    while(1){
        printf("请输入一个正整数：");
        scanf("%d",&t);
        if(t<0){
            break;
        }
        q=(struct node *)malloc(sizeof(NODE));
        q->data=t;
        p->next=q;
        p=q;
    }
    p->next=head;
    return head;
}


//插入
void insert(struct node *head,int t)
{
    struct node *p,*q,*r;
    r=(struct node *)malloc(sizeof(NODE));
    r->data=t;
    q=head;
    p=head->next;
    while(p!=head){
        if(p->data<t){
            q=p;
            p=p->next;
        }else{
            break;
        }
    }
    q->next=r;
    r->next=p;
    return;
}
//所有的操作与单链表相同，改while条件即可，改成p!=head;