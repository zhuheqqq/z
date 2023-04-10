#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<pthread.h>

void *tfn(void *arg){//回调函数
    printf("thread:pid=%d,tid=%d",getpid(),pthread_self());
    return NULL;
}

int main(int argc,char *argv[]){
    pthread_t tid;

    printf("main:pid=%d,tid=%d\n",getpid(),pthread_self());

    int ret=pthread_create(&tid,NULL,tfn,NULL);
    if(ret!=0){
        perror("pthread_create error");
    }
    sleep(1);
    return 0;

    //上述两条可以替换成
    //pthread_exit((void *)0)
}