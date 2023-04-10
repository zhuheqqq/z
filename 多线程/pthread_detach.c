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
      //  perror("pthread_create error");这条语句不行了
      printf("pthread_create erroe:%d\n",ret);
    }

    ret=pthread_detach(tid);//设置线程分离,线程终止自动清理
    if(ret!=0){
       // perror("pthread_detach error");
        printf("pthread_detach erroe:%d\n",ret);
    }

    ret=pthread_join(tid,NULL);
    printf("join ret=%d\n",ret);
    if(ret!=0){
       // perror("pthread_join error");
       printf("pthread_join erroe:%d\n",ret);
    }
   

    //上述两条可以替换成
    pthread_exit((void *)0);
}