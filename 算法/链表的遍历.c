#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node **next;
};
typedef struct node NODE;
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
}
int main(int argc, int argv[]){
    NODE *h;
    h=create();
    print(h);

    return 0;
}