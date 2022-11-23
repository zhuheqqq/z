#include<stdio.h:
#include<stdlib.h>
#include"node.h"
typedef struct node{
    int value;
    struct node *next;
}Node;

int main(void){
    Node *head=NULL;
    int number;
    do{
        scanf("%d",&number);
        if(number!=-1){
            //add to link-list
            Node *p=(Node*)malloc(sizeof(Node));
            p->value=number;
            p->next=NULL;
            //find the last
            Node *last=head;
            while(last->next){
                last=last->next;
            }
            //attach
        }
    }while(number!=-1);
}