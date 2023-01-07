#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
//create LinkStack
typedef struct NODE{
    int data;
    struct S *next;
}node,*LinkStackptr;

typedef struct{
    LinkStackptr top;
    int count;
}LinkStack;
//push
bool push (LinkStack *S,int e){
    LinkStackptr s=(LinkStackptr)malloc(sizeof(node));
    s->data=e;
    s->next=S->top;
    S->top=s;
    S->count++;
    return true;
}
//pop
int pop(LinkStack *S){
    LinkStackptr p;
    if(S->count==0){
        return false;
    }
    static int t;
    p=S->top;
    t=p->data;
    S->top=S->top->next;
    S->count--;
    free(p);
    return t;
}

