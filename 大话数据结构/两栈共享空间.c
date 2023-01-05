//两端向中间延伸
//当top1=-1,栈1为空；当top2=max,栈2为空
//top2=top1+1栈满
#define max 100
#define error 0
#define ok 1
#include<stdio.h>
#include<stdlib.h>
typedef int Status ;
typedef struct
{
    int data[max];
    int top1;
    int top2;

}S;

//插入操作
//e为插入的元素，num为插入栈1还是栈2
Status push(S *p,int e,int num){
    if(p->top1+1==p->top2){
        return error;
    }
    if(num==1){
        p->data[++p->top1]=e;
    }else if(num==2){
        p->data[--p->top2]=e;
    }
    return ok;

}
//pop
Status pop(S *p,int *e,int num){
    if(num==1){
        if(p->top1==-1){
            return error;
        }
        *e=p->data[p->top1--];
    }
    if(num==2){
        if(p->top2==max){
            return error;
        }
        *e=p->data[p->top2++];
    }
}