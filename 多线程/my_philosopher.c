#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<time.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

#define N 5

sem_t chopsticks[N];//信号量的类型

int philosophers[N]={0,1,2,3,4};//哲学家的编号

void *philosopher(void *arg)
{
    int i=*(int *)arg;//代表哲学家的编号以此区分哲学家
    int left=i;//在逆时针的座位下,左筷子编号与哲学家本身相同
    int right=(i+1)%N;//右筷子环形加1
    //如果是顺时针座位则左右筷子编号颠倒

    while(1)
    {
        if(i%2==0){//偶数哲学家先拿右边的筷子,再拿左边的
            printf("哲学家%d正在思考\n",i);
            sleep(1);


            printf("哲学家%d饿了\n",i);
            sem_wait(&chopsticks[right]);
            printf("哲学家%d拿起筷子%d,现在哲学家%d手上有一支筷子\n",i,right,i);
            sem_wait(&chopsticks[left]);
            printf("哲学家%d拿起筷子%d,现在哲学家%d手上有两根筷子,可以吃饭\n",i,left,i);
            sleep(1);

            sem_post(&chopsticks[right]);
            printf("哲学家%d放下筷子%d\n",i,right);
            sem_post(&chopsticks[left]);
            printf("哲学家%d放下筷子%d\n",i,left);
        }else{
            printf("哲学家%d正在思考\n",i);
            sleep(1);


            printf("哲学家%d饿了\n",i);
            sem_wait(&chopsticks[left]);
            printf("哲学家%d拿起筷子%d,现在哲学家%d手上有一支筷子\n",i,left,i);
            sem_wait(&chopsticks[right]);
            printf("哲学家%d拿起筷子%d,现在哲学家%d手上有两根筷子,可以吃饭\n",i,right,i);
            sleep(1);

            sem_post(&chopsticks[left]);
            printf("哲学家%d放下筷子%d\n",i,left);
            sem_post(&chopsticks[right]);
            printf("哲学家%d放下筷子%d\n",i,right);
        }
        
    }
}

int main()
{
    srand(time(NULL));
    pthread_t philo[N];

    int i=0;
//初始化信号量
    for(i=0;i<N;i++){
        sem_init(&chopsticks[i],0,1);
    }
//循环创建线程
    for(i=0;i<N;i++){
        pthread_create(&philo[i],NULL,philosopher,&philosophers[i]);
    }
//挂起线程
    for(i=0;i<N;i++){
        pthread_join(philo[i],NULL);
    }
//销毁信号量
    for(i=0;i<N;i++){
        sem_destroy(&chopsticks[i]);
    }

    return 0;
}