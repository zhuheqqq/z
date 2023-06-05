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

TCP传输控制协议是一种面向连接的,可靠的,基于字节流的传输层通信协议

UDP用户数据协议是OSI参考模型中一种无连接的传输层协议,提供面向事务的简单不可靠信息传送服务

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

网络数据流有大端和小端之分.发送主机通常将发送缓冲区的数据按内存地址从低到高的顺序发出,接收主机把从网络上接到的字节依次保存在接收缓冲区中,也是按内存地址从低到高的顺序保存,因此,网络数据流的地址:先发出的数据是低地址,后发出的数据是高地址

网络数据流采用大端字节序,即低地址高字节

为使网络程序具有可移植性,有以下库函数做网络字节序和主机字节序的转换

```c
#include<arpa/inet.h>

//本地转网络,IP协议
uint32_t htonl(uint32_t hostlong);//h表示host,n表示network,l表示32位长整数,s表示16位短整数
//针对port端口
uint16_t htons(uint16_t hostshort);
uint32_t ntohl(uint32_t netlong);
uint16_t ntohs(uint16_t netshort);
```

如果主机是小端字节序,这些函数做相应的转换,如果是大端字节序,这些函数将原封不动的返回

### IP地址转换函数

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
int bind(int sockfd,const struct sockaddr*addr,socklen_t len);
/*sockfd:socket函数返回值

初始化addr
struct sockaddr_in addr;
addr.sin_family=AF_INET;
addr.sin_port=htons(port);
addr.sin_addr.s_addr=htonl(INADDR_ANY);
addr:传入参数,(struct sockaddr*)&addr

addrlen:sizeof(addr)地址结构的大小

返回值:成功返回0,失败返回-1并设置errno
```

listen()函数:设置同时与服务器建立连接的上限数(同时进行三次握手的客户端数量)

```c
int listen(int sockfd,int backlog)l;
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