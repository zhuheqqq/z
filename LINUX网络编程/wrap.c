#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/socket.h>

void perr_exit(const char *s)
{
    perror(s);
    exit(-1);
}

int Accept(int fd,struct sockaddr *sa,socklen_t *salenptr)
{
    int n;

again:
    if((n=accept(fd,sa,salenptr))<0)
    {
        if((errno==ECONNABORTED)||(errno==EINTR))
        {
            goto again;
        }else{
            perr_exit("accept error");
        }
    }

    return n;
}

int Bind(int fd,const struct sockaddr *sa,socklen_t salen)
{
    int n;

    if((n=bind(fd,sa,salen))<0)
    {
        perr_exit("bind_error");
    }
    return n;
}

int Connect(int fd,const struct sockaddr *sa,socklen_t salen)
{
    int n;

    if((n=connect(fd,sa,salen))<0)
    {
        perr_exit("connect error");
    }

    return n;
}

int Listen(int fd,int backlog)
{
    int n;

    if((n=listen(fd,backlog))<0)
    {
        perr_exit("listen error");
    }

    return n;
}

int Socket(int family,int type,int protocol)
{
    int n;

    if((n=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        perr_exit("socket error");
    }

    return n;
}