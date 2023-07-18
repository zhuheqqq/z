#include "wrap.h"
#include<sys/select.h>

#define SERV_PORT 6666

int main(int argc,char *argv[])
{
    int listenfd,connfd;
    char buf[BUFSIZ];

    struct sockaddr_in clie_addr,serv_addr;
    socklen_t clie_addr_len;

    listenfd=Socket(AF_INET,SOCK_STREAM,0);

    int opt=1;
    setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));//多路复用

    bzero(&serv_addr,sizeof(serv_addr));

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(SERV_PORT);
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);

    Bind(listenfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));

    Listen(listenfd,128);

    fd_set rset,allset;
    int ret,maxfd=0;
    maxfd=listenfd;

    FD_ZERO(&allset);//清空文件描述符集合
    FD_SET(listenfd,&allset);//添加待监听的文件到监听集合中

    while(1)
    {
        rset=allset;
        ret=select(maxfd+1,&rset,NULL,NULL,NULL);
        if(ret<0)
        {
            perr_exit("select error");

        }

        if(FD_ISSET(listenfd,&rset))//判断listenfd是否在监听集合中
        {
            clie_addr_len=sizeof(clie_addr);
            connfd=Accept(listenfd,(struct sockaddr *)&clie_addr,&clie_addr_len);//建立连接---不会阻塞

            FD_SET(connfd,&allset);//将新产生的fd,添加到监听集合中，监听数据读事件

            if(maxfd<connfd)
            {
                maxfd=connfd;
            }

            if(ret==1)
            {
                continue;//说明select之返回一个并且是listenfd,后续操作无需执行
            }
        }

        for(int i=listenfd+1;i<=maxfd;i++)//处理满足读事件的fd
        {
            if(FD_ISSET(i,&rset)){
                int n=read(i,buf,sizeof(buf));//找到满足读事件的fd
                if(n==0)//检测到客户端已经关闭
                {
                    close(i);
                    FD_CLR(i,&allset);//将关闭的fd从监听集合中移除

                }

                for(int j=0;j<n;j++)
                {
                    buf[j]=toupper(buf[j]);
                }

                write(STDOUT_FILENO,buf,n);
            }
        }
    }

    Close(listenfd);

    return 0;
}