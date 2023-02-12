//使hello不输出在终端而是在指定的文件中
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

#define FNAME "/LINUX系统编程"

int main(void){

    int fd;

    close(1);
    fd=open(FNAME,O_WRONLY|O_CREAT|O_TRUNC,0600);
    if(fd<0){
        perror("open():");
        exit(1);
    }




    puts("hello!");

    exit(0);
}