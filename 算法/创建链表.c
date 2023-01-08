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

int main(void)
{
    struct node *head,*p,*q,*t;
    int i,n,a;
    scanf("%d",&n);
    head=NULL;
    for(i=1;i<=n;i++){
        scanf("%d",&a);
        p=(struct node *)malloc(sizeof(struct node));
        p->data=a;
        p->next=NULL;
        if(head==NULL){
            head=p;
        }else{
            q->next=p;
        }
        q=p;
    }
    t=head;
        while(t!=NULL){
            printf("%d ",t->data);
            t=t->next;
        }
        getchar();
        getchar();
        free(p);
        return 0;
}

//头插法
Link newList(int a[],int n)
{
    head=(Link)malloc(sizeof(Node));
    head->next=NULL;
    for(i=0;i<n;i++){
        node=(Link)malloc(sizeof(Node));
        node->data=a[i];
        node->next=head->next;
        head->next=node;
    }
    return head;//和数组a的顺序相反
}

//尾插法
Link newLink(int a[],int n)
{
    head=(Link)malloc(sizeof(Node));
    head->next=NULL;
    r=head;
    for(i=0;i<n;i++){
        node=(Link)malloc(sizeof(Node));
        node->data=a[i];
        node->next=NULL;
        r->next=node;
        r=node;
    }
    r->next=NULL;//很重要，忘记造成死循环
    return head;
}