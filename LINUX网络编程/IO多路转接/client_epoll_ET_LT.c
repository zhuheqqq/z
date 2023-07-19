#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<signal.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/epoll.h>
#include<unistd.h>

#define SERV_PORT 9000
#define MAXLINE 10

int main()
{
    struct sockaddr_in servaddr;
    char buf[MAXLINE];
    int sockfd,i;
    char ch='a';

    sockfd=socket(AF_INET,SOCK_STREAM,0);

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    inet_pton(AF_INET,"127.0.0.1",&servaddr.sin_addr);
    servaddr.sin_port=htons(SERV_PORT);

    connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

    while(1)
    {
        //aaaa\n
        for(i=0;i<MAXLINE/2;i++)
        {
            buf[i]=ch;
        }

        buf[i-1]='\n';
        ch++;

        //bbbb\n
        for(;i<MAXLINE;i++)
        {
            buf[i]=ch;
        }
        buf[i-1]='\n';
        ch++;

        write(sockfd,buf,sizeof(buf));
        sleep(5);
    }

    close(sockfd);

    return 0;
}