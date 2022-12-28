// prior data next
#include<stdio.h>
#include<stdlib.h>
typedef struct _node{
    int data;
    struct _node *prior,*next;
}node;

struct node *create(int n)
{
    node *prior,*next,*h;
    prior=next=(node *)malloc(sizeof(node));
    node *p;
    int i=n,d=0;
    printf("请输入数据：\n");
    for(i=n;i>0;i--){
        p=(node *)malloc(sizeof(node));
        scanf("%d",&d);
        p->data=d;
        p->prior=NULL;
        p->next=NULL;
        prior->next=p;
        p->prior=prior;
        prior=p;
    }
    node *first;
    first=h->next;
    return first;
}