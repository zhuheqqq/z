#define max 100
#include<stdio.h>
#include<stdbool.h>
typedef struct{
    int data[max];
    int front;
    int rear;
}S;
//init
bool init(S *Q){
    Q->front=0;
    Q->rear=0;
    return true;
}
//返回队列当前长度
int Slength(S Q){
    return (Q.rear-Q.front+max)%max;
}
//enter
bool Senter(S *Q,int e){
    if((Q->rear+1)%max==Q->front){
        return false;
    }
    Q->data[Q->rear]=e;
    Q->rear=(Q->rear+1)%max;
    return true;

}
//pop
int Spop(S *Q){
    if(Q->rear==Q->front){
        return false;
    }
    static int key;
    key=Q->data[Q->front];
    Q->front=(Q->front+1)%max;
    return key;//if key==0?

}