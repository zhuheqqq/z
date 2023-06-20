#include"wrap.h"
#include<pthread.h>
#include<signal.h>
#include<strings.h>//bzero头文件

#define SRV_PORT 9999

/*void perr_exit(const char *s)
{
    perror(s);
    exit(-1);
}*/

void catch_child(int signum)
{
    while(waitpid(0,NULL,WNOHANG)>0);
    return ;
}

int main(int argc,char *argv[])
{
    int lfd,cfd,ret,i;
    char buf[BUFSIZ];
    pid_t pid;
    struct sockaddr_in srv_addr,clit_addr;
    socklen_t clit_addr_len;

    memset(&srv_addr,0,sizeof(srv_addr));//将地址结构清零
    //bzero(&srv_addr,sizeof(srv_addr));这个函数功能与上面的函数相同，但是更简单好记
    srv_addr.sin_family=AF_INET;
    srv_addr.sin_port=htons(SRV_PORT);
    srv_addr.sin_addr.s_addr=htonl(INADDR_ANY);

    lfd=Socket(AF_INET,SOCK_STREAM,0);

    Bind(lfd,(struct sockaddr *)&srv_addr,sizeof(srv_addr));

    Listen(lfd,128);

    clit_addr_len=sizeof(clit_addr);

    while(1)
    {
        
        cfd=Accept(lfd,(struct sockaddr *)&clit_addr,&clit_addr_len);

        //创建子进程
        pid=fork();
        if(pid<0)
        {
            perr_exit("fork error");
        }else if(pid==0)
        {
            close(lfd);
            break;
        }else{
            struct sigaction act;
            act.sa_handler=catch_child;
            act.sa_flag=0;
            sigemptyset(&act.sa_mask);
            ret=sigaction(SIGCHLD,&act,NULL);
            if(ret!=0)
            {
                perr_exit("sigaction error");
            }
            close(cfd);
            continue;
        }
    }

    if(pid==0)
    {
        for(;;){
            ret=Read(cfd,buf,sizeof(buf));
            if(ret==0)
            {
                close(cfd);
                exit(1);   
            }

            for(i=0;i<ret;i++)
            {
                buf[i]=toupper(buf[i]);//小写转大写
            }

            write(cfd,buf,ret);
            write(STDOUT_FILENO,buf,ret);

        }
        
       
    }

    return 0;
}