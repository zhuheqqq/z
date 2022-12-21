// #include<stdio.h>
// #include<stdlib.h>
// //creat linked list
// struct node
// {
//     int data;
//     struct node *next;
// };
// int main(void)
// {
//     struct node *head,*p,*q,*t;//定义指针
//     int i,n,a;
//     scanf("%d",&n);
//     head=NULL;
//     for(i=1;i<=n;i++){
//         scanf("%d",&a);
//         p=(struct node *)malloc(sizeof(struct node));//创建节点并让p指向该节点
//         p->data=a;
//         p->next=NULL;
//         if(head==NULL){
//             head=p;
//         }else{
//             q->next=p;//？
//         }
//         q=p;
//     }
//     scanf("%d",&a);
//     t=head;
//     while(t!=NULL){
//         if(t->next==NULL||t->next->data>a){
//             p=(struct node *)malloc(sizeof(struct node));
//             p->data=a;
//             p->next=t->next;
//             t->next=p;
//             break;
//         }
//         t=t->next;
//     }
//     t=head;
//     while(t!=NULL){
//         printf("%d ",t->data);
//         t=t->next;
//     }
//     free(p);
//     return 0;
// }


#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node *next;
};
typedef struct node NODE;
NODE *create();
void print(NODE *head);
void insert(NODE *head,int t);
int main(void)
{
    NODE *h;
    int d;
    h=create();
    print(h);
    while(1){
        printf("请输入插入的正整数:");
        scanf("%d",&d);
        if(d<0){
            break;
        }
        insert(h,d);
        print(h);
    }
    
    return 0;
}
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
    p->next=NULL;
    return head;
}
void print(NODE *head)
{
    NODE *p;
    p=head->next;
    if(p==NULL){
        printf("该链表为空\n");
    }else{
        printf("数据为:");
        while(p!=NULL){
            printf("->%d",p->data);
            p=p->next;
        }
        printf("\n");
        return;
    }

}
void insert(struct node *head,int t)
{
    struct node *p,*q,*r;
    r=(struct node *)malloc(sizeof(NODE));
    r->data=t;
    q=head;
    p=head->next;
    while(p!=NULL){
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