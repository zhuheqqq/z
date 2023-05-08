//创建线程池
//初始化线程池
//消耗任务即工作者消耗线程
//添加任务
//销毁线程池
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>
#include<time.h>

//任务队列的创建
typedef struct task
{
    void(*task_signal)(void *arg);//任务指针,指向一个待完成的任务(函数)
    void *arg;//函数的参数
    struct task *next;//指向上述任务指针的下一个任务
}task;

//线程池
typedef struct threadpool
{
    int threadnum;//线程池里线程的数量
    int tasknum;//任务的数量

    task *first;//指向第一个任务
    task *end;//指向最后一个任务

    pthread_mutex_t mutexpool;//锁住线程池
    pthread_cond_t isempty;//任务队列是否为空

    int pooldestroy;//销毁线程池,销毁为1,否则为0


}threadpool;

//工作者完成任务
void *worker(void *arg)
{
    threadpool *pool=(threadpool *)arg;//强制类型转换

    while(1){
        pthread_mutex_lock(&pool->mutexpool);//锁住整个线程池

        //判断任务队列是否为空以及线程池是否关闭
        if(pool->first==NULL&&!pool->pooldestroy){
            //阻塞等待直到被唤醒
            pthread_cond_wait(&pool->isempty,&pool->mutexpool);
        }

        //如果线程池被关闭或者销毁
        if(pool->pooldestroy==1){
            //解锁并销毁线程
            pthread_mutex_unlock(&pool->mutexpool);
            pthread_exit(NULL);
        }

        //如果上述情况没有发生或者是阻塞的线程被重新唤醒,则开始执行任务
        task *t=pool->first;
        pool->first=t->next;
        pool->tasknum--;
        free(t);
        t=NULL;
    }
}

//线程池的初始化
threadpool* threadinit(int num)
{
    //在堆区分配内存
    threadpool *pool=(threadpool *)malloc(sizeof(threadpool));

    pool->threadnum=num;
    pool->tasknum=0;
    pool->first=NULL;
    pool->end=NULL;

    pthread_mutex_init(&pool->mutexpool,NULL);
    pthread_cond_init(&pool->isempty,NULL);

    pool->pooldestroy=0;

    for(int i=0;i<num;i++){
        pthread_t tid;
        pthread_create(&tid,NULL,worker,pool);
    }
    return pool;
}



//往任务队列里添加任务
void Taskadd(threadpool *pool,void (*task_signal)(void *),void *arg)
{
    //如果线程池已经关闭或者被销毁
    if(pool->pooldestroy==1){
        return;
    }

    pthread_mutex_lock(&pool->mutexpool);//锁住整个线程池

    task *t=(task *)malloc(sizeof(task));
    t->arg=arg;
    t->task_signal=task_signal;
    t->next=NULL;

    //如果任务队列中没有任务
    if(pool->first==NULL)
    {
        pool->first=t;
        pool->end=t;
    }else{
        //如果任务队列中还有任务,则添加新的任务到任务队列的尾部
        pool->end->next=t;
        pool->end=t;
    }

    pool->tasknum++;//任务数量++

    pthread_cond_signal(&pool->isempty);//唤醒阻塞的线程
    pthread_mutex_unlock(&pool->mutexpool);//解锁线程池

}

//销毁线程池
void Pooldestroy(threadpool *pool)
{
    if(pool==NULL)
    {
        return;
    }

    pool->pooldestroy=1;//给线程池一个信号,让他自己销毁

    for(int i=0;i<pool->threadnum;i++){
        pthread_cond_signal(&pool->isempty);//逐个销毁线程
    }

    pthread_mutex_destroy(&pool->mutexpool);//销毁锁
    pthread_cond_destroy(&pool->isempty);//销毁条件变量

    free(pool);
    pool=NULL;
}