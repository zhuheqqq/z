#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct QNode{
    int data;
    struct QNode *next;
}QNode,*Qptr;
//struct of linkqueue
typedef struct{
    Qptr front,rear;//rear指向队尾
}LinkQ;
//push
bool Qpush(LinkQ *q,int e){
    Qptr s=(Qptr)malloc(sizeof(QNode));
    if(!s){
        return false;
    }
    s->data=e;
    s->next=NULL;
    q->rear->next=s;
    q->rear=s;
    return true;
}
//pop
int Qpop(LinkQ *q){
    Qptr p=(Qptr)malloc(sizeof(QNode));
    static e;
    e=q->front->data;
    p=q->front;
    q->front=q->front->next;
    free(p);
    return e;

}