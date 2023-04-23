// Single-producer , single-consumer Queue
//借助条件变量模拟生产者消费者问题
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int i=0;//生产者序号
int j=0;//消费者序号
#define SIZE 10//最大容纳量

// 链表作为共享数据,需被互斥量保护
struct SPSCQueue {
   int num;
   struct SPSCQueue *next;
    int cnt;
} typedef SPSCQueue;

struct SPSCQueue *head;//头指针

//静态初始化一个条件变量和一个互斥量
pthread_cond_t has_product=PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;

//生产者
void *producer(void *arg)
{
    SPSCQueue *temp;
    for(;;)
    {
        temp=malloc(sizeof(SPSCQueue));
        temp->num=rand()%1000+1;//模拟生产一个产品
        head->cnt++;
        printf("-第%d个Produce %lu------------------------------%d\n",++i,pthread_self(),temp->num);//输出提示信息
        
        pthread_mutex_lock(&lock);//加锁

        if(temp->cnt==SIZE){//队列已满
            pthread_cond_wait(&has_product,&lock);//生产者阻塞等待,pthread_cond_wait返回时,重写加锁mutex
        }
        
        SPSCQueue *p;
        p=head->next;
        head->next=temp;
        temp->next=p;//头插法入队列

        pthread_mutex_unlock(&lock);//解锁

        pthread_cond_signal(&has_product);//将等待在该条件变量上的一个线程唤醒

        sleep(rand()%5);
    }
    return NULL;
}

//消费者
void *consumer(void *arg)
{
    SPSCQueue *temp;

    for(;;)
    {
        pthread_mutex_lock(&lock);//消费者加锁

        while(head->next==NULL)//多线程阻塞时,可能会出现线程被唤醒但队列为空的情况,所以需要循环判断
        {
            pthread_cond_wait(&has_product,&lock);//消费者阻塞等待,pthread_cond_wait返回时,重写加锁mutex

        }

        temp=head;
        while(temp->next->next!=NULL)//!找到尾节点上一个节点
        {
            temp=temp->next;
        }

        printf("-第%d个Cosumer %lu-----------------------------%d\n",++j,pthread_self(),temp->next->num);//输出提示信息
        head->cnt--;
        pthread_mutex_unlock(&lock);//解锁
        pthread_cond_signal(&has_product);//唤醒线程

        free(temp->next);
        temp->next=NULL;//这一步很重要,否则segmentation fault

        sleep(rand()%5);
    }
    return NULL;
}

int main(int argc,char *argv[])
{
    head=(SPSCQueue *)malloc(sizeof(SPSCQueue));
    head->next=NULL;
    head->cnt=0;

    pthread_t pid,cid;
    srand(time(NULL));

    int ret=pthread_create(&pid,NULL,producer,NULL);
    if(ret!=0)
    {
        fprintf(stderr,"pthread_create error:%s\n",strerror(ret));
        exit(1);
    }

    ret=pthread_create(&cid,NULL,consumer,NULL);
    if(ret!=0)
    {
        fprintf(stderr,"pthread_create error:%s\n",strerror(ret));
        exit(1);
    }

    ret=pthread_join(pid,NULL);
    if(ret!=0)
    {
        fprintf(stderr,"pthread_join error:%s\n",strerror(ret));
        exit(1);
    }

    ret=pthread_join(cid,NULL);
    if(ret!=0)
    {
        fprintf(stderr,"pthread_join error:%s\n",strerror(ret));
        exit(1);
    }

    ret=pthread_mutex_destroy(&lock);
    if(ret!=0)
    {
        fprintf(stderr,"pthread_mutex_destroy error:%s\n",strerror(ret));
        exit(1);
    }

    ret=pthread_cond_destroy(&has_product);
    if(ret!=0)
    {
        fprintf(stderr,"pthread_cond_destroy error:%s\n",strerror(ret));
        exit(1);
    }

    return 0;

}