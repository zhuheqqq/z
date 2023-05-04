//笑死白写了看错题目了除非吃完饭根本不放下
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<errno.h>
#include<math.h>
#include<time.h>
#include<unistd.h>

#define N 5

pthread_mutex_t chopstick[N];

int philosophers[N]={1,2,3,4,5};

void *philosopher(void *arg)
{
    int ID=*(int *)arg;
    int left,right;//左右筷子的编号,需要保持一致

    switch(ID){
        case 0:
            left=4;
            right=0;
            break;
        case 1:
            left=0;
            right=1;
            break;
        case 2:
            left=1;
            right=2;
            break;
        case 3:
            left=2;
            right=3;
            break;
        case 4:
            left=3;
            right=4;
            break;
    }

    int i=ID;//哲学家

    for(;;)
    {
        printf("哲学家%d在思考\n",i);
        sleep(1);//哲学家在思考
        printf("哲学家%d饿了\n",i);
        //哲学家拿左筷子
        pthread_mutex_lock(&chopstick[left]);
        printf("哲学家%d拿起左筷子%d\n",i,left);

        //申请右筷子,防止出现死锁
        if(pthread_mutex_trylock(&chopstick[right])==EBUSY)//此时右筷子被别的哲学家拿着
        {
            pthread_mutex_unlock(&chopstick[left]);//放下左筷子
            printf("哲学家%d放下左筷子%d\n",i,left);
            continue;
        }
            //此时如果没有进入if语句,trylock则加锁成功
            printf("哲学家%d拿起右筷子%d\n",i,right);
            printf("哲学家%d正在吃饭\n",i);
            sleep(1);
            //放下左右筷子
            pthread_mutex_unlock(&chopstick[left]);
            printf("哲学家%d放下左筷子%d\n",i,left);
            pthread_mutex_unlock(&chopstick[right]);
            printf("哲学家%d放下右筷子%d\n",i,right);
        
        
    }


}

int main()
{
    srand(time(NULL));
    pthread_t philo[N];

    for(int i=0;i<N;i++){
        pthread_create(&philo[i],NULL,philosopher,&philosophers[i]);
    }

    for(int i=0;i<N;i++){
        pthread_join(philo[i],NULL);
    }

    return 0;

}