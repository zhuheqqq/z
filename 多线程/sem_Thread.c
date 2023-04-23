//利用信号量实现单生产者消费者模型
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<semaphore.h>

#define NUM 5
int i=0;
int j=0;

struct SPSCQueue {
   int num;
   struct SPSCQueue *next;
    int cnt;
} typedef SPSCQueue;

struct SPSCQueue *head;//头指针
sem_t blank_number,product_number;//空格子信号量,产品信号量

//静态初始化一个条件变量和一个互斥量
// pthread_cond_t has_product=PTHREAD_COND_INITIALIZER;
// pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;

//生产者
void *producer(void *arg)
{
    SPSCQueue *temp;
    for(;;)
    {
        sem_wait(&blank_number);//生产者将空格数--,为0阻塞等待
        temp=malloc(sizeof(SPSCQueue));
        temp->num=rand()%1000+1;//模拟生产一个产品
        head->cnt++;
        printf("-第%d个Produce %lu------------------------------%d\n",++i,pthread_self(),temp->num);//输出提示信息
        
        //pthread_mutex_lock(&lock);//加锁

        
        
        SPSCQueue *p;
        p=head->next;
        head->next=temp;
        temp->next=p;//头插法入队列

        sem_post(&product_number);//将产品数++


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
       sem_wait(&product_number);//消费者将产品数--,为0则阻塞等待

        temp=head;
        while(temp->next->next!=NULL)//!找到尾节点上一个节点
        {
            temp=temp->next;
        }

        printf("-第%d个Cosumer %lu-----------------------------%d\n",++j,pthread_self(),temp->next->num);//输出提示信息
        head->cnt--;

        sem_post(&blank_number);//消费掉以后,将空格数++

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

    int ret=sem_init(&blank_number,0,NUM);//初始化空格信号量为5,线程间共享--0
    if(ret!=0)
    {
        fprintf(stderr,"pthread_create error:%s\n",strerror(ret));
        exit(1);
    }
    ret=sem_init(&product_number,0,0);//产品数为0
    if(ret!=0)
    {
        fprintf(stderr,"pthread_create error:%s\n",strerror(ret));
        exit(1);
    }

    ret=pthread_create(&pid,NULL,producer,NULL);
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

    ret=sem_destroy(&blank_number);
    if(ret!=0)
    {
        fprintf(stderr,"sem_destroy error:%s\n",strerror(ret));
        exit(1);
    }

    ret=sem_destroy(&product_number);
    if(ret!=0)
    {
        fprintf(stderr,"sem_destroy error:%s\n",strerror(ret));
        exit(1);
    }

    return 0;

}