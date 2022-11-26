#include<stdio.h>
#include<stdlib.h>
//creat linked list
struct node
{
    int data;
    struct node *next;
};
int main(void)
{
    struct node *head,*p,*q,*t;//定义指针
    int i,n,a;
    scanf("%d",&n);
    head=NULL;
    for(i=1;i<=n;i++){
        scanf("%d",&a);
        p=(struct node *)malloc(sizeof(struct node));//创建节点并让p指向该节点
        p->data=a;
        p->next=NULL;
        if(head==NULL){
            head=p;
        }else{
            q->next=p;//？
        }
        q=p;
    }
    scanf("%d",&a);
    t=head;
    while(t!=NULL){
        if(t->next==NULL||t->next->data>a){
            p=(struct node *)malloc(sizeof(struct node));
            p->data=a;
            p->next=t->next;
            t->next=p;
            break;
        }
        t=t->next;
    }
    t=head;
    while(t!=NULL){
        printf("%d ",t->data);
        t=t->next;
    }
    free(p);
    return 0;
}