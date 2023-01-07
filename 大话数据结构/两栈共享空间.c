//两端向中间延伸
//当top1=-1,栈1为空；当top2=max,栈2为空
//top2=top1+1栈满
#define max 100
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct
{
    int data[max];
    int top1;
    int top2;

}S;

//插入操作
//e为插入的元素，num为插入栈1还是栈2
bool push(S *p,int e,int num){
    if(p->top1+1==p->top2){
        return false;
    }
    if(num==1){
        p->data[++p->top1]=e;
        return true;
    }else if(num==2){
        p->data[--p->top2]=e;
        return true;
    }
    

}
//pop
int  pop(S *p,int num){
    if(num==1){
        if(p->top1!=-1){
           return  p->data[p->top1--];
        }
    }
    if(num==2){
        if(p->top2!=max){
           return p->data[p->top2++];
        }
    }
    return 0;
}

int main(void){
    S s={
        .top1=-1,
        .top2=max
    };
    S *p=&s;
    //int *e=NULL;
    int n=9,num=1;
   // pop(p,e,num);
    printf("%d\n",push(p,n,num));
    printf("%d\n",pop(p,num));
    
    return 0;
}