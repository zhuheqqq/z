#include "wrap.h"

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
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);//INADDR_ANY是常值，一般为0

    lfd=Socket(AF_INET,SOCK_STREAM,0);

    //建立连接
    ret=Bind(lfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
    
//设置上限数
    ret=Listen(lfd,128);
    

    //阻塞等待连接
    clit_addr_len=sizeof(clit_addr);
    cfd=Accept(lfd,(struct sockaddr*)&clit_addr,&clit_addr_len);
    

    //服务器开始读
    while(1)
    {
        ret=Read(cfd,buf,sizeof(buf));
        Write(STDOUT_FILENO,buf,ret);

        for(int i=0;i<ret;i++)
        {
            buf[i]=toupper(buf[i]);
        }

        //写出到buf
        Write(cfd,buf,ret);
    }
    Close(lfd);
    Close(cfd);

}

