#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node *next;
};
typedef struct node NODE;
NODE *create();
void print(NODE *head);
void dele(NODE *head,int t);
int main(void){
    NODE *h;
    int data;
    h=create();
    print(h);
    while(1){
        printf("输出待删除节点的值：");
        scanf("%d",&data);
        if(data<0){
            break;
        }
        dele(h,data);
        print(h);
    }
    return 0;

}
NODE *create(){
    NODE *head,*p,*q;
    int t;
    head=malloc(sizeof(NODE));
    p=head;
    while(1){
        printf("请输入一个正整数：");
        scanf("%d",&t);
        if(t<0){
            break;
        }
        q=malloc(sizeof(NODE));
        q->data=t;
        p->next=q;
        p=q;
    }
    p->next=NULL;
    return head;
}
void print(NODE *head){
    NODE *p;
    p=head->next;
    if(p==NULL){
        printf("该链表为空！\n");
    }else{
        printf("数据为：\n");
        while(p!=NULL){
            printf("->%d",p->data);
            p=p->next;
        }
    }
    printf("\n");
}
void dele(NODE *head,int t)
{
    NODE *p,*q;
    q=head;
    p=head->next;
    while(p!=NULL)
    {
    if(p->data==t){
        q->next=p->next;
        free(p);
        break;
    }else{
        q=p;
        p=p->next;
    }
    }
    if(p==NULL){
        printf("无符合条件的节点");
    }
    return;
}