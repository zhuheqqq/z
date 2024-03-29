#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<pthread.h>

void *tfn(void *arg){

    int i=(int)arg;
    sleep(i);

    printf("--I'm %dth thread:pid=%d,tid=%d\n",i+1,getpid(),pthread_self());
    return NULL;

}

int main(int argc,char *argv[]){
    int i;
    int ret;
    pthread_t tid;
    for(i=0;i<5;i++){
        ret=pthread_create(&tid,NULL,tfn,(void *)i);//值传递
        if(ret!=0){
            perror("pthread_create error");
        }
    }

    sleep(i);
    printf("main:I'm main,pid=%d,tid=%d\n",getpid(),pthread_self());
    return 0;
}