# LINUX网络编程



[TOC]

## 协议

协议就是数据传输和数据的解释的一组规则

TCP协议注重数据的传输,http协议注重数据的解释

### 常见的协议

传输层常见的协议有TCP/UDP协议

应用层常见协议有HTTP协议,IGMP协议

网络层常见的协议有IP协议,ICMP协议,IGMP协议

网络接口层常见协议有ARP协议,RARP协议

### UDP用户数据报协议

UDP用户数据协议是OSI参考模型中一种无连接的传输层协议,提供面向事务的简单不可靠信息传送服务

![](/home/zhuheqin/Downloads/UDP数据报.png)

TCP传输控制协议是一种面向连接的,可靠的,基于字节流的传输层通信协议(SCTP与TCP类似,但他还提供消息边界,传输级别多宿支持以及将头端阻塞减少到最小的一种方法)

HTTP超文本传输协议是互联网上应用最为广泛的一种网络协议

FTP是文件传输协议

IP协议是因特网互联协议

ICMP协议是Internet控制报文协议,它是TCP/IP的子协议,用于IP主机,路由器之间传递控制信息

IGMP协议是Internet组管理协议,是因特网协议家族中的一个组播协议,该协议运行于主机和组播路由器之间

ARP协议是正向地址解析协议,通过已知的IP,寻找对应主机的MAC地址

RARP是反向地址转换协议,通过MAC地址确定IP地址

## 分层模型

### OSI七层模型:物数网传会表应

物理层  数据链路层  网络层  传输层  会话层  表示层  应用层

### 数据链路层(封装了物理网络的电气细节)

该层实现了网卡接口的网络驱动程序,以处理数据在物理媒介(如以太网,令牌环)上的传输,常用的两个协议是ARP协议和RARP协议,实现了IP地址和机器物理地址之间的**相互转换**.数据链路层使用物理地址寻址一台机器,所以网络层必须先将目标机器的ip地址转换成物理地址,也就是ARP协议的用途

经过数据链路层封装的数据称为帧

### 网络层(封装了网络连接的细节)

网络层实现了数据包的选路和转发,最核心的协议是ip协议,根据数据包的目的ip来决定如何投递它,另外一个是ICMP协议,用于检测网络连接

### 传输层(封装了一条端到端的逻辑通信链路)

传输层为两台主机上的应用程序提供端对端的通信,只关心通信的起始端和目的端,不在乎数据包的中转过程,常见的协议有TCP协议,UDP协议,SCTP协议

### 应用层

负责处理应用程序的逻辑,在用户空间中实现

## 通信过程

这里有一张图片

网络传输流程:数据没有封装之前不能在网络中传递

数据-应用层-传输层-网络层-链路层

### 以太网帧协议

ARP协议:根据IP地址获取mac地址

以太网帧协议:根据mac地址,完成数据包的传输

### IP协议

版本:IPv4,IPv6--4位

TTL:time to live设置数据包在路由节点中的跳转上限.没经过一个路由节点,该值-1,减为0的路由,有义务将该数据包丢弃

源IP:32位--4字节              192.168.1.108---点十分进制  IP地址---二进制

目的IP:32位--4字节

IP地址:可以在网络中,唯一标识一台主机

端口号:可以在网络的一台主机上,唯一标识一个进程

IP地址+端口号:可以在网络环境中,唯一标识一个进程

## 网络套接字socket

一个文件描述符指向一个套接字(该套接字内部由内核借助两个缓冲区实现)

在通信过程中,套接字一定是成对出现的

### 网络字节序

在计算机网络中，不同的计算机体系结构可能使用不同的字节序（byte order），即数据在内存中存储的方式不同。为了在网络上实现数据传输的正确性和可靠性，通常需要进行字节序的转换。

在套接字编程中，IP地址和端口号通常以主机字节序（即本地字节序）的形式存储。但是，在进行网络通信时，这些数据需要在不同计算机之间进行传输，因此需要将它们转换为网络字节序（即大端字节序）的形式，以确保数据在不同计算机之间传输时能够正确解析。

具体来说，网络字节序采用的是大端字节序，即高位字节存放在低地址处，低位字节存放在高地址处。例如，32位的IP地址0x12345678在网络字节序下的表示方式为0x78 0x56 0x34 0x12。而在小端字节序的计算机上，该IP地址的内存中的表示方式为0x78 0x56 0x34 0x12，而在大端字节序的计算机上，该IP地址的内存中的表示方式为0x12 0x34 0x56 0x78。

网络数据流有大端和小端之分.发送主机通常将发送缓冲区的数据按内存地址从低到高的顺序发出,接收主机把从网络上接到的字节依次保存在接收缓冲区中,也是按内存地址从低到高的顺序保存,因此,网络数据流的地址:先发出的数据是低地址,后发出的数据是高地址

网络数据流采用大端字节序,即低地址高字节

为使网络程序具有可移植性,有以下库函数做网络字节序和主机字节序的转换

```c
#include<arpa/inet.h>

//本地转网络,IP协议,htonl()函数将主机字节序的32位IP地址转换为网络字节序的32位IP地址
uint32_t htonl(uint32_t hostlong);//h表示host,n表示network,l表示32位长整数,s表示16位短整数
uint32_t ntohl(uint32_t netlong);

//针对port端口
uint16_t htons(uint16_t hostshort);
uint16_t ntohs(uint16_t netshort);
```

如果主机是小端字节序,这些函数做相应的转换,如果是大端字节序,这些函数将原封不动的返回

### IP地址转换函数

在网络通信中，数据传输需要通过IP地址来标识发送方和接收方的网络地址。套接字是一种用于在计算机之间进行网络通信的抽象概念，它需要使用IP地址和端口号来确定通信的目标。在套接字中，IP地址通常以字符串形式表示，例如"192.168.1.1"。但是，在网络设备中，IP地址通常以二进制形式存储和传输，例如32位的IPv4地址。因此，在套接字和网络设备之间传输IP地址时，需要进行字符串和二进制之间的转换。这个过程被称为IP地址转换。

在套接字编程中，IP地址转换可以使用各种库和函数来实现。例如，在C语言中，可以使用inet_addr函数将字符串形式的IP地址转换为二进制形式，使用inet_ntoa函数将二进制形式的IP地址转换为字符串形式。在Python中，可以使用socket库中的inet_aton和inet_ntoa函数来进行IP地址转换。这些函数的使用可以使套接字编程更加方便和易于实现。

```c
#include<arpa/inet.h>
int inet_pton(int af,const void *src,char* dst);//将点分十进制的ip地址转换为网络字节序
```

af指代当前使用的ip协议(IPv4/IPv6),其中AF_INET代表IPv4,AF_INET6代表IPv6

src:传入,ip地址(点分十进制)

dst:传出,转换后的网络字节序的ip地址

返回值:成功返回1,返回0说明src指向的不是一个有效的ip地址,失败返回-1

```c
const char *inet_ntop(int af,const void *arc,char *dst,socklen_t size);
```

基本同上

size:dst缓冲区的大小

返回值:成功返回dst,失败返回NULL

### sockaddr地址结构

![](/home/zhuheqin/Pictures/sockaddr地址结构.png)

由于历史原因,我们一般定义struct sockaddr_in,然后在函数接口中强转成struct sockaddr

```c
struct sockaddr_in addr;
//初始化addr
addr.sin_family=AF_INET/AF_INET6//指明使用的IP协议
addr.sin_port=htons(9527);//端口号

int dst;
inet_pton(AF_INET,"192.157.22.45",(void*)&dst);//这里因为结构体嵌套结构,所以必须这样初始化
addr.sin_addr.s_addr=dst;//这里我们一般使用一个宏INADDR_ANY,代表取出系统中有效的任意ip地址,默认取出二进制类型
//addr.sin_addr.s_addr=htonl(INADDR_ANY)
bind(fd,(struct sockaddr*)&addr,size);
```

## socket模型创建流程

**一个服务器和一个客户端进行通信时,一共会用到三个套接字**,其中两个进行通信,另外一个监听

### 服务器端

socket()函数:创建一个socket套接字

```c
#include<sys/socket.h>
int socket(int domain,int type,int protocol);
/*domain:指明所使用的ip协议,AF_INET/AF_INET6
type:所选用的数据传输协议,有流式协议(SOCK_STREAM)和数据报式协议(SOCK_DGRAM)
protocol:一般为0表示根据type选定相应的协议

返回值:成功返回新套接字所对应的文件描述符,失败返回-1并设置errno*/
```

bind()函数:往socket绑定一个地址结构(ip+port)

```c
#include<arpa/inet.h>
int bind(int sockfd,const struct sockaddr*addr,socklen_t len);
/*sockfd:socket函数返回值

初始化addr
struct sockaddr_in addr;
addr.sin_family=AF_INET;
addr.sin_port=htons(port);
addr.sin_addr.s_addr=htonl(INADDR_ANY);
如果是IPV6,则上述代码改为addr.sin6_addr=in6addr_any;
addr:传入参数,(struct sockaddr*)&addr

addrlen:sizeof(addr)地址结构的大小

返回值:成功返回0,失败返回-1并设置errno
```

listen()函数:设置同时与服务器建立连接的上限数(同时进行三次握手的客户端数量)

```c
int listen(int sockfd,int backlog);
/*sockfd:socket函数返回值
backlog:上限数值,最大值128

返回值:成功返回0,失败返回-1并设置errno*/
```

accept()函数:阻塞等待客户端建立连接,成功返回一个与客户端连接成功的socket文件描述符

```c
int accept(int sockfd,struct sockaddr*addr,socklen_t *addrlen);
/*sockfd:socket函数返回值
addr:传出参数,传出的是成功与服务器建立连接的那个客户端的地址结构(ip+port)

socklen_t clit_addr_len=sizeof(addr);
addrlen:传入传出,传入addr夫人大小,传出的是客户端addr的实际大小.传入函数取地址

返回值:成功返回能与服务器进行数据通信的socket对应的文件描述符,失败返回-1并设置errno*/
```

### 客户端

connect()函数:与现有的socket服务器建立连接

```c
int connect(int sockfd,const struct sockaddr *addr,socklen_t addrlen);
/*sockfd:socket函数返回值
addr:传入参数,传入服务器的地址结构
同样的,addr需要被初始化
addr.sin_family=AF_INET;
addr.sin_port=要求跟服务端bind时设定的port完全一致
addr.sin_addr.s_addr
inet_pton(AF_INET,"服务器的ip地址",&addr.sin_addr.s_addr);

addrlen:服务器的地址结构大小

返回值:成功返回0,失败返回-1并设置errno

如果不使用bind绑定客户端地址结构,采用"隐式绑定"(客户端的ip和port有系统自动分配)
```

## TCP通信流程分析

server:

- socket():创建socket
- bind():绑定服务器地址结构
- listen():设置监听上限
- accept():阻塞监听客户端连接
- read(fd):读socket获取客户端数据
- 大小写转换:toupper()
- write(fd)
- close()

client:

- socket():创建一个socket
- connect():与服务器建立连接
- write():写数据到socket
- read():读转换后的数据
- 显示读取结果
- close()

## serve的实现

```c
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
```

## client的实现

```c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<pthread.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define SERV_PORT 9527

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

int main(int argc,char *argv[])
{
    int cfd;
    int count=10;
    char buf[BUFSIZ];
    struct sockaddr_in serv_addr;//服务器地址结构
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(SERV_PORT);
    inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr.s_addr);//将ip地址转换成网络字节序
    //serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);

    cfd=socket(AF_INET,SOCK_STREAM,0);
    if(cfd==-1)
    {
        sys_err("socket error");
    }

    int ret=connect(cfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
    if(ret==-1)
    {
        sys_err("connect error");
    }

    while(--count)
    {
        write(cfd,"hello\n",6);
        ret=read(cfd,buf,sizeof(buf));
        write(STDOUT_FILENO,buf,ret);
        sleep(1);
    }
    close(cfd);

    return 0;
}
```

## TCP通信时序(三次握手和四次挥手)

### 三次握手

主动发起连接请求端，发送SYN标志位，请求建立连接。携带序号号、数据字节数、滑动窗口大小。

被动接受建立连接请求端，发送ACK标志位，同时携带SYN请求标志位。携带序号、确认序号、数据字节数、滑动窗口大小。

主动发起连接请求端，发送ACK标志位，应答服务器连接请求。携带确认序号。

一般是由客户端发起的，但是不绝对，大多数情况是

SYN：标志位，专门用来请求建立通信连接

ACK：应答标志位，表示收到了来建立连接的请求

seq:序列号，随机生成

ack：确认号，如果数据包按顺序到达，确认号就是上一个已成功接收的数据包的序列号加上数据包的长度。

SYN和ACK都是首部的标志位，而ACK和SYN的值是对数据流的标记

三次握手发生在内核空间，在用户空间的体现是accept()函数和connect()函数成功执行并且返回了

### 数据通信

三次握手的最后一次握手同时开始传输数据

### 四次挥手

断开连接需要四次挥手（半关闭）

主动关闭连接请求端，发送FIN标志位

被动关闭连接请求端，应答ACK标志位，此时半关闭完成

被动关闭连接请求端，发送FIN标志位

主动关闭连接请求端，发送ACK标志位，此时连接全部关闭

## 滑动窗口（TCP流量控制）

服务器可以不必接受一条就回复一条，可以先批量回复，一条回执将客户端前面所有的数据都回复

不论是客户端还是服务器端都有缓冲区，滑动窗口来指定缓冲区的大小

如果发送端发送的速度较快，接收端接收数据后处理的速度较慢，而接受缓冲区的大小是固定的，就会丢失数据，TCP协议通过滑动窗口机制解决这一问题

发送给连接对端，本端的缓冲区大小（实时），保证数据不会丢失。

## 多进程服务器并发

### 多进程并发服务器思路

**进程数据不共享只复制，所以可以分别关闭文件描述符**

伪代码如下：

```c
pid_t pid;
int listenfd,connfd;//监听套接字和已连接套接字
listenfd=Socket(...);//创建监听套接字
Bind(listenfd,...);//绑定地址
Listen(listenfd,LISTENQ);//设置监听上限
for(;;)
{
    connfd=Accept(listenfd,...);//阻塞等待连接
    if((pid=Fork())==0)//如果是子进程
    {
        Close(listenfd);
        //对于child来说，不需要用于建立连接的套接字所以关闭
        //父子进程共享监听与连接的套接字，子进程关闭监听套接字，只是监听套接字的被引用次数-1,不影响父进程继续监听与新的客户端连接
        doit(connfd);//伪代码，处理请求
        Close(connfd);
        exit(0);
    }else if(pid>0)//如果是父进程
    {
        Close(connfd);//这里同样是-1
        /*while(1)
        {
            waitpid(0,NULL,WNOHANG);//WNOHANG告知内核在在没有已终止的子进程时不要阻塞
        }//这里如果以循环非阻塞状态去回收子进程，此时有客户端进来无法accept，如果不回收则会变成僵尸进程*/
        //这部分代码应该注册信号捕捉函数，在回调函数中完成子进程的回收
        continue;
    }
}

```

## 多线程并发服务器

### 多线程并发服务器思路

**线程中文件描述符共享不能关**，还有就是线程最好不要和信号一起用

```c
pthread_t tid;
int listenfd,connfd;//监听套接字和已连接套接字
listenfd=Socket(...);//创建监听套接字
Bind(listenfd,...);//绑定地址
Listen(listenfd,LISTENQ);//设置监听上限
while(1)
{
    connfd=Accept(listenfd,...);
    pthread_create(&tid,NULL,tfn,NULL);//tfn是回调函数
    pthread_detach(tid);
}
//子线程：
void *tfn(void *arg)
{
    //注意这里不能关闭监听套接字
    doit(connfd);
}
```

## TCP状态时序图

1.主动发起连接请求端：CLOSE--发送SYN--SENT_SYN--接收ACK、SYN--SENT_SYN--发送ACK--ESTABLISHED（数据通信态）

2.主动关闭连接请求端：ESTABLISHED（数据通信态）--发送FIN--FIN_WAIT_1--接收ACK--FIN_WAIT_2（半关闭）--接收对端发送FIN--FIN_WAIT_2（半关闭）--回发ACK--TIME_WAIT（只有主动关闭连接才会经历这个状态）--等待2MSL--CLOSE

3.被动接受连接请求端：CLOSE--LISTEN--接收SYN同时发送ACK、SYN--SYN_RCVD--接收ACK--ESTABLISHED（数据通信态）

4.ESTABLISTED（数据通信态）--接收FIN、发送ACK--CLOSE_WAIT（说明对端[主动关闭连接端]处于半关闭状态）--发送FIN--LAST_ACK--接收ACK--CLOSE

2MSL时长：（一定出现在主动关闭连接请求端)保证最后一个ACK能成功被对端接收（等待期间，对端没收到我发送的ACK，对端会再次发送FIN请求）

四次握手完成

## 端口复用函数

在server的tcp连接没有完全断开之前不允许重新监听是不合理的。因为，tcp连接没有完全断开指的是connfd没有完全断开，而我们重新监听的是listenfd,虽然占用的是同一个端口，但ip地址不同，connfd对应的是与末讴歌客户端通讯的具体的ip地址，而listenfd对应的是wildcard address.解决这个问题的方法是使用sesockopt函数设置socket描述符的选项SO_REUSEADDR为1,表示允许创建端口号相同但IP地址不同的多个SOCKET描述符。

```cpp
 #include <sys/socket.h>

       int setsockopt(int socket, int level, int option_name,
           const void *option_value, socklen_t option_len);

```

```cpp
#include <sys/socket.h>

       int getsockopt(int socket, int level, int option_name,
           void *restrict option_value, socklen_t *restrict option_len);

```

定义一个opt=1表示设置端口复用

```cpp
int opt =1;
setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,(void *)&opt,sizeof(opt));
```

## 半关闭和shutdown函数

终止网络连接的方法是调用close函数，不过close函数有两个限制可以通过shutdown函数来避免:

1. close把描述符的引用计数减一，只有该引用标为0才会关闭套接字。
2. close会终止读写两个方向的数据传送。

```cpp
#include<sys/socket.h>
int shutdown(int sockfd,int howto);
howto：SHUT_RD关闭读端
    SHUT_WR关闭写端
    SHUT_RDWR关闭读写端
```

## 多路i/0转接

不再由应用程序自己监视客户端连接，而是由内核替应用程序监视文件

### select函数

```cpp
#include <sys/select.h>

       typedef /* ... */ fd_set;

       int select(int nfds, fd_set *_Nullable restrict readfds,
                  fd_set *_Nullable restrict writefds,
                  fd_set *_Nullable restrict exceptfds,
                  struct timeval *_Nullable restrict timeout);

```

```cpp
nfds指的是select管理的所有描述符中最大的那个加1，文件描述符表中文件描述符最大的那个+1
readfds对应读事件
writefds对应写事件
exceptfds对应异事件,均为传入传出参数
timeout定时阻塞监控时间:
	NULL永远等下去
    设置timeval等待固定时间
    设置timeval里时间均为0,检查描述符后立即返回轮询
返回值是返回所有监听集合中的所有文件描述符中有事件发生的总个数
```

```cpp
void FD_CLR(int fd, fd_set *set);将一个文件描述符从监听集合中移除
int  FD_ISSET(int fd, fd_set *set);判断一个文件描述符是否在监听集合中
void FD_SET(int fd, fd_set *set);将待监听的文件描述符添加到监听集合中
void FD_ZERO(fd_set *set);清空一个文件描述符集合
 
```

### select多路转接思路

伪代码

```cpp
lfd=socket();创建套接字
bind();绑定地址结构
listen();设置监听上限
fd_set rset,allset;创建监听集合
FD_ZERO(&allset);将监听集合清空
FD_SET(lfd,&allset);将lfd添加至监听集合中
while(1)
{
    rset=allset;保存监听集合
    ret=select(lfd+1,&rset,NULL,NULL,NULL);监听文件描述符集合对应事件
    if(ret>0)//有监听的描述符满足对应事件
    {
        if(FD_ISSET(lfd,&rset)){//1在0不在
            cfd=accept();建立连接返回用于通信的文件描述符
            FD_SET(cfd,&allset);添加到监听通信描述符集合中
        }
        for(i=lfd+1;i<=最大文件描述符;i++)//在文件描述符表中，总是会从最小的tian qi
        {
          	FD_ISSET(i,&rset);看是否有读写事件发生
            read();
            小写转大写
            write();
        }
    }
}
```

