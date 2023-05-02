
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h> 


#define NUM 5

int eaters = 0;

//-------------------一些信号量----------------
sem_t sem_fork[NUM];
sem_t sem_eaters;
void sem_mutex_init()
{
	int i;
	for(i = 0;i < NUM; ++i)
		if(sem_init(&sem_fork[i],0,1) == -1)
		{
			printf("sem_init失败，退出!\n");
			exit(1);
		}
	if(sem_init(&sem_eaters,0,1) == -1)
	{
		printf("sem_init失败，退出!\n");
		exit(1);
	}
	return ;
}

void philosopher()
{
	for(;;)
	{
		sleep(3);
		
		pthread_t tid = pthread_self();
		tid %= 5;//这是给线程编号从0-4的一种比较简单的方法，使得和sem_fork[0] -sem_forks[4]对应
		//先拿右手边的叉子，再拿左手边的叉子
		if(tid % 2 == 1)
		{
			printf("%d号哲学家正在思考...\n",tid);
			sem_wait(&sem_fork[tid]);
			sem_wait(&sem_fork[(tid+1)%5]);


			sem_wait(&sem_eaters);
			eaters++;

			printf("%d号哲学家正在用餐，目前有%d个用餐者\n",tid,eaters);
			//吃完了
			sem_post(&sem_eaters);
			
			sem_post(&sem_fork[(tid+1)%5]);
			sem_post(&sem_fork[tid]);

			sem_wait(&sem_eaters);
			eaters--;
			sem_post(&sem_eaters);

		}
		else
		{
			printf("%d号哲学家正在思考...\n",tid);
			sem_wait(&sem_fork[(tid+1)%5]);
			sem_wait(&sem_fork[tid]);
			


			sem_wait(&sem_eaters);
			eaters++;

			printf("%d号哲学家正在用餐，目前有%d个用餐者\n",tid,eaters);
			//吃完了
			sem_post(&sem_eaters);
			
					
			sem_post(&sem_fork[tid]);
			sem_post(&sem_fork[(tid+1)%5]);
			sem_wait(&sem_eaters);
			eaters--;
			sem_post(&sem_eaters);

		}
		
		
	}
}

int main(void)
{
	int i;
	pthread_t philosopher_threads[NUM];
	for(i = 0; i < NUM; ++i)
	{
		if(pthread_create(&philosopher_threads[i],NULL,philosopher,philosopher_threads) != 0)
		{
			printf("创建第%d个哲学家进程失败！\n",i+1);
			exit(1);
		}
	}

	
	sem_mutex_init();
	

	for(i = 0; i < NUM; ++i)
	{
		pthread_join(philosopher_threads[i],NULL);
	}

	return 0;

}
