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
void *worker();