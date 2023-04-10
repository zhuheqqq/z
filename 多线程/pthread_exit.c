#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<pthread.h>

void *tfn(void *arg){

    int i=(int)arg;
    sleep(i);
    if(i==2){
        exit(0);//表示退出进程
        return NULL;//表示返回调用者
        pthread_exit(NULL);//表示退出当前线程
        //pthread_exit(void *ret),ret:退出值,无退出值时NULL
    }

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