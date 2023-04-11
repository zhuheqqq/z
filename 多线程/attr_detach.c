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

    pthread_attr_t attr;
    int ret=pthread_attr_init(&attr);//初始化线程属性
    if(ret!=0){
        printf("pthread_attr_init error:%d\n",ret);
        exit(1);
    }

    ret=pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);//设置线程属性为分离属性
    if(ret!=0){
        printf("pthread_attr_setdetachstate error:%d\n",ret);
        exit(1);
    }
   

    ret=pthread_create(&tid,&attr,tfn,NULL);
    if(ret!=0){
        perror("pthread_create error");
    }
   
    ret=pthread_attr_destroy(&attr);
    if(ret!=0){
        printf("pthread_attr_destroy error:%d\n",ret);
        exit(1);
    } 

   // sleep(1);//

    ret=pthread_join(tid,NULL);
    if(ret!=0){
        printf("pthread_join error:%d\n",ret);//线程分离后不能被回收
        exit(1);
    }

    printf("main:pid=%d,tid=%d\n",getpid(),pthread_self());


    //sleep(1);
    //return 0;

    //上述两条可以替换成
    pthread_exit((void *)0);
}