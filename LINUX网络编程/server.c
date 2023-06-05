#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<pthread.h>
#include<sys/socket.h>
#include<ctype.h>
#include<arpa/inet.h>

#define SERV_PORT 9527
//#define BUFSIZE 4096

void sys_err(const char*str)
{
    perror(str);
    exit(1);
}

int main(int argc,char *argv[])
{
    //创建socket
    int lfd=0,cfd=0;
    int ret=0;
    char buf[BUFSIZ];//系统自带8192
    struct sockaddr_in serv_addr,clit_addr;
    socklen_t clit_addr_len;

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(SERV_PORT);
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);

    lfd=socket(AF_INET,SOCK_STREAM,0);
    if(lfd==-1)//检查返回值
    {
        sys_err("socket error");
    }

    //建立连接
    ret=bind(lfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
    if(ret==-1)
    {
        sys_err("bind error");
    }
//设置上限数
    ret=listen(lfd,128);
    if(ret==-1)
    {
        sys_err("listen error");
    }

    //阻塞等待连接
    clit_addr_len=sizeof(clit_addr);
    cfd=accept(lfd,(struct sockaddr*)&clit_addr,&clit_addr_len);
    if(cfd==-1)
    {
        sys_err("accept error");
    }

    //服务器开始读
    while(1)
    {
        ret=read(cfd,buf,sizeof(buf));
        write(STDOUT_FILENO,buf,ret);

        for(int i=0;i<ret;i++)
        {
            buf[i]=toupper(buf[i]);
        }

        //写出到buf
        write(cfd,buf,ret);
    }
    close(lfd);
    close(cfd);

}