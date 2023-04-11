#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

pthread_mutex_t mutex1;
pthread_mutex_t mutex2;

int var1=0,var2=1;

void *tfn1(void *arg){
    pthread_mutex_lock(&mutex1);

    printf("var2=%d\n",var2);

    sleep(3);

    printf("var1=%d\n",var1);

    return NULL;

}

int main(void)
{
    int ret;
   // int var1=0,var2=1;
    pthread_t tid;

    ret=pthread_mutex_init(&mutex1,NULL);
    if(ret!=0){
        fprintf(stderr,"pthread_mutex_init error:%s\n",strerror(ret));
    }

    printf("var1=%d\n",var1);

    sleep(2);

    ret=pthread_mutex_init(&mutex2,NULL);
    if(ret!=0){
        fprintf(stderr,"pthread_mutex_init error:%s\n",strerror(ret));
    } 
    ret=pthread_create(&tid,NULL,&tfn1,NULL);
    if(ret!=0){
        fprintf(stderr,"pthread_create1 error:%s\n",strerror(ret));
    }

    printf("var2=%d\n",var2);

    ret=pthread_join(tid,NULL);

    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);

    return 0;

    
}