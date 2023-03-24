# 实现自己的shell

[TOC]

## 项目简介

## 一些实现shell需要用到的函数

### execvp函数

包含头文件：#include <unistd.h>

函数定义：int execvp(const char *file, char * const argv []);

函数说明：execvp()会从环境变量所指的目录中查找符合参数 file 的文件名, 找到后执行该文件, 然后将第二个参数argv 传给该执行的文件。

返回值：如果执行成功则函数不会返回, 执行失败则直接返回-1.

该函数可以实现一些shell中需要实现的一些外部命令，如ls、echo、cat等，不过，像一些外部命令如cd等，还是需要自己写函数来实现。从某种意义上来说，这大大减轻了我们的工作量，毕竟上个项目实现自己的ls敲得很想死(bushi

### getcwd函数和chdir函数

这两个函数主要用来实现cd功能：

- getcwd函数获取当前工作目录并返回一个指向缓冲区的指针
- chdir函数更改进程工作目录，成功返回0,错误返回1

### fork函数

fork()是什么？

一个进程，包括代码、数据和分配给进程的资源。fork（）函数通过系统调用创建一个与原来进程几乎完全相同的进程，也就是两个进程可以做完全相同的事，但如果初始参数或者传入的变量不同，两个进程也可以做不同的事。
一个进程调用fork（）函数后，系统先给新的进程分配资源，例如存储数据和代码的空间。然后把原来的进程的所有值都复制到新的新进程中，只有少数值与原来的进程的值不同。

上面的话通俗理解就是: fork是复制进程的函数，程序一开始就会产生一个进程，当这个进程(代码)执行到fork()时，fork就会复制一份原来的进程即就是创建一个新进程,我们称子进程，而原来的进程我们称为父进程，此时父子进程是共存的，他们一起向下执行代码。

注意的一点：就是调用fork函数之后，一定是两个进程同时执行fork函数之后的代码，而之前的代码以及由父进程执行完毕。

fork的返回值问题:

在父进程中，fork返回新创建子进程的进程ID；

在子进程中，fork返回0；

如果出现错误，fork返回一个负值；  

getppid():得到一个进程的父进程的PID;

getpid():得到当前进程的PID;

*注意:在fork函数执行完毕后，如果创建新进程成功，则出现两个进程，一个是子进程，一个是父进程。在子进程中，fork函数返回0，在父进程中，fork返回新创建子进程的进程ID。我们可以通过fork返回的值来判断当前进程是子进程还是父进程。

此函数主要用于管道和重定向的实现

简单理解就是，父进程可以fork出多个子进程，子进程共享父进程中的数据并执行不同的功能，这大大提高了进程的效率。



### pipe函数

#### 管道的创建

   管道是由调用pipe函数来创建

```c
#include <unistd.h>
int pipe (int fd[2]);
                         //返回:成功返回0，出错返回-1     
```

 fd参数返回两个文件描述符,fd[0]指向管道的读端,fd[1]指向管道的写端。fd[1]的输出是fd[0]的输入。

#### 无名管道特点：

1.半双工，数据在同一时刻只能在一个方向上流动
2.数据只能从管道的一端写入，从另一端读出
3.写入管道的数据遵循先入先从出的规则
4.管道所传送的数据不是无格式的，这要求管道的读出方和写入方必须约定好数据的格式，如多少字节算一个消息
5.管道不是普通的文件，不属于某个文件系统，其只存在于内存中
6.管道在内存中对应一个缓冲区，不同的系统其大小不一定相同
7.从管道读数据是一次性操作，数据一旦被读走，它就从管道中丢弃，释放空间以便写更多的数据
8.管道没有名字，只能在具有公共祖先的进程(父进程和子进程，或两个兄弟进程)之间使用
详见此篇博客https://blog.csdn.net/weixin_44471948/article/details/120846877

pipe函数用来实现管道，pipe可以创建出多个管道，合理的关闭或打开管道的读写端可以共享管道中的数据，实现进程之间的通信！

### dup函数和dup2函数

这两个函数主要用来复制文件描述符，从而实现重定向，读者可以自行阅读《LINUX系统编程手册》或者csdn一下(嘘我要偷懒！

## 代码实现(代码中有详细讲解)

### 打印提示符函数

就是打开你的终端就会输出的提示符（终端也是一种shell）

```c
void colorprint(){
    char *name="zhuheqin@zhuheqin-ThinkPad-E14-Gen-4";
    printf("\033[1m\033[32m%s\033[0m",name);
    printf(":");
    getcwd(lujing,sizeof(lujing));
    printf("\033[1m\033[34m%s\033[0m",lujing);
    printf("$ ");

    fflush(stdout);//清空缓冲区
}
```

### 屏蔽信号函数

仔细阅读该项目的要求就会发现其中一条是要求实现屏蔽一些信号如ctrl+c等

这个函数就将实现此功能

```c
void setup()
{
    //按下ctrl+c或者是delete没有反应，屏蔽此信号
    signal(SIGINT,SIG_IGN);//设置某一信号的对应动作，错误返回-1
    //SIG_IGN忽略前一个参数所代表的信号
    signal(SIGHUP,SIG_IGN);
}
```

### 参数标记函数

```c
int isdo(char *argv[],int cnt){
    int flag=10,i;
    if(argv[0]==NULL){
        return 0;
    }
    if(strcmp(argv[0],"cd")==0){
        flag=1;
    }
    for(i=0;i<cnt;i++){
        if(strcmp(argv[i],">")==0){
            flag=2;
        }
        if(strcmp(argv[i],"|")==0){
            flag=3;
        }
        if(strcmp(argv[i],">>")==0){
            flag=4;
        }
        if(strcmp(argv[i],"<")==0){
            flag=5;
        }
        if(strcmp(argv[i],"&")==0){
            pass=1;
            argv[i]=NULL;
        }
    }
    return flag;

}
```

### 执行外部命令函数

主要是对execvp函数的一些完善和包装

```c
int execute(char *argv[])
{
    int pid;
    int child_info=-1;

    if(argv[0]==NULL)
        return 0;
    if((pid=fork())==-1)
        perror("fork");
    else if(pid==0){
        signal(SIGINT,SIG_DFL);
        signal(SIGQUIT,SIG_DFL);
        execvp(argv[0],argv);
        perror("cannot execute command");
        exit(1);
    }
    else{
        if(wait(&child_info)==-1)
            perror("wait");//父进程等待子进程
    }

    return child_info;
}
```

其实此函数的返回值没有什么用，可以将函数类型改为void。

### cd函数

#### cd + "路径"

- 直接使用getcwd函数获取当前路径后保存再使用chdir函数更改目录路径

#### cd + "-" 回到此目录之前所在目录

- 保存当前路径并添加至strcwd（自身定义的用来保存路径的数组）
- 更改目录到之前所在目录

#### cd + "~"

- 使用getcwd函数获取当前路径并保存到之前定义的数组中
- chdir回到主目录

其实通过对上面cd功能的总结，不难发现，其实对于cd功能的实现主要分为两步

- getcwd函数获取当前路径并保存在数组中
- chdir更改目录路径

代码如下

```c
char strcwd[MAX];//保存路径
void mycd(char *argv[]){
    if(argv[1]==NULL){
        getcwd(strcwd,sizeof(strcwd));
        chdir("/home");
    }else if(strcmp(argv[1],"~")==0){
        getcwd(strcwd,sizeof(strcwd));
        chdir("/home/zhuheqin");

    }else if(strcmp(argv[1],"-")==0){//返回进入此目录之前所在的目录
        char strcwd1[MAX];
        getcwd(strcwd1,sizeof(strcwd1));
        chdir(strcwd);
        printf("%s\n",strcwd);
        strcpy(strcwd,strcwd1);
    }else{
        getcwd(strcwd,sizeof(strcwd));
        chdir(argv[1]);
    }
    

}
```

### 重定向

#### >

```c
//重定向没有实现--已解决
void mydup(char *argv[])//重定向使输出输出到文件中
{
    char *str[MAX]={NULL};
    int i=0;

    while(strcmp(argv[i],">")){
        str[i]=argv[i];//存入之前的参数
        i++;
    }
  //  printf("%s",str[i]);
    int number=i;//记录参数个数
    int flag=isdo(argv,number);
    i++;

    int filefdout=dup(1);//获取新的文件描述符
    int fd=open(argv[i],O_WRONLY|O_CREAT|O_TRUNC,0666);

    dup2(fd,1);//指定新文件描述符为1

    //fork新进程
    pid_t pid=fork();
    if(pid<0){
        perror("fork");
        exit(1);
    }else if(pid==0){//child
        if(flag==3){
        callCommandWithPipe(str,number);
        }else{
            //execvp(str[0],str);
            execute(str);//两种都可以
        }
    }else if(pid>0){
        if(pass==1){
            pass=0;
            printf("%d\n",pid);
            return;
        }
        waitpid(pid, NULL, 0);
    }
    dup2(filefdout,1);
}
```

#### >>

```c
//和mydup几乎一模一样
void mydup2(char *argv[])//重定向使输出输出到文件中
{
    char *str[MAX]={NULL};
    int i=0;

    while(strcmp(argv[i],">>")){
        str[i]=argv[i];//存入之前的参数
        i++;
    }
    int number=i;//记录参数个数
    int flag=isdo(argv,number);
    i++;

    int filefdout=dup(1);//获取新的文件描述符
    int fd=open(argv[i],O_WRONLY|O_CREAT|O_APPEND,0666);

    dup2(fd,1);//关闭标准输出，返回大于1的文件描述符

    //fork新进程
    pid_t pid=fork();
    if(pid<0){
        perror("fork");
        exit(1);
    }else if(pid==0){//child
        if(flag==3){//有管道的情况
            callCommandWithPipe(str,number);
        }else{
            execvp(str[0],str);
        }
    }else if(pid>0){
        if(pass==1){
            pass=0;
            printf("%d\n",pid);
            return;
        }
        waitpid(pid, NULL, 0);
    }
    dup2(filefdout,1);
}
```

#### <

```c
void mydup3(char *argv[])
{
    char *str[MAX]={NULL};
    int i=0;

    while(strcmp(argv[i],"<")){
        str[i]=argv[i];
        i++;
    }
    i++;

    int number=i;
    int flag=isdo(argv,number);

    int filefdin=dup(0);
    int fd=open(argv[i],O_RDONLY,0666);
    dup2(fd,0);

    pid_t pid=fork();
    if(pid<0){
        if(pass==1){
            pass=0;
            printf("%d\n",pid);
            return;
        }
        perror("fork");
        exit(1);
    }else if(pid==0){
        if(flag==3){
            callCommandWithPipe(str,number);
        }else{
            execvp(str[0],str);
        }

    }else if(pid>0){
        waitpid(pid,NULL,0);
    }
    dup2(filefdin,0);
}
```

#### 进阶

其实可以将上述三个函数合成一个函数,利用一些if else

代码可以自己实现一下,超级简单!

### 多重管道

```c
void callCommandWithPipe(char *argv[],int count)//多重管道
{
    int ret[10]={0};//记录管道的位置
    int number=0;//记录命令个数
    int i;
    pid_t pid;

    for(i=0;i<count;i++){
        if(!strcmp(argv[i],"|")){//遇到管道符则进入记录其位置
            ret[number++]=i;
        }
    }

    int cmd_count=number+1;
    char *cmd[cmd_count][10];

    for(int i=0;i<cmd_count;i++){//将命令以管道分割符分好
        
        if(i==0){
            int n=0;
            for(int j=0;j<ret[i];j++){
                cmd[i][n++]=argv[j];
            }
            cmd[i][n]=NULL;
        }else if(i==cmd_count-1){
            int n=0;
            for(int j=ret[i-1]+1;j<count;j++){
                cmd[i][n++]=argv[j];
            }
            cmd[i][n]=NULL;
        }else{
            int n=0;
            for(int j=ret[i-1]+1;j<ret[i];j++){
                cmd[i][n++]=argv[j];
            }
            cmd[i][n]=NULL;
        }
    }

  //创建管道
  int fd[number][2];
  for(i=0;i<number;i++){
    pipe(fd[i]);
  }
  //创建子进程
  for(i=0;i<cmd_count;i++){
    pid=fork();
    if(pid==0){
        break;
    }
  }
  if(pid==0){//child
    if(number){//保证单向通信
        if(i==0){
            dup2(fd[0][1],1);//绑定写端
            close(fd[0][0]);//关闭读端

            for(int j=1;j<cmd_count-1;j++){//其他管道读写端全部关闭
                close(fd[j][1]);
                close(fd[j][0]);
            }
        }else if(i==number){//最后一个管道
            dup2(fd[i-1][0],0);//绑定读端
            close(fd[i-1][1]);//关闭写端

            for(int j=0;j<cmd_count-2;j++){
                close(fd[j][1]);
                close(fd[j][0]);
            }
        }else{
            dup2(fd[i-1][0],0);
            close(fd[i-1][1]);
            dup2(fd[i][1],1);
            close(fd[i][0]);

            for(int j=0;j<number;j++){
                if(j!=(i-1)&&j!=i){
                    close(fd[j][0]);
                    close(fd[j][1]);
                }
            }
        }
    }
  
  execvp(cmd[i][0],cmd[i]);//文件名和路径
  perror("execvp");
  exit(1);
  }
  
    for(i=0;i<number;i++){
        close(fd[i][0]);
        close(fd[i][1]);
    }
    if(pass==1){
            pass=0;
            printf("%d\n",pid);
            return;
        }
       // waitpid(pid, NULL, 0);
    
    for(int j=0;j<number;j++){
        wait(NULL);
    }
    
}
```

## 完整代码

```c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>//chdir()所在头文件
#include<signal.h>
#include<sys/wait.h>
#include<ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <wait.h>
#include <fcntl.h>
#include<readline/readline.h>
#include<readline/history.h>


#define YES 1
#define NO 0

//#define DFL_PROMPT "zhq_shell~$ "

#define MAX 128

int pass=0;//标记&
char lujing[1000];//cd功能保存路径

void process(char *argv[], int number);
int isdo(char *argv[], int cnt);
// cd命令
void mycd(char *argv[]);
//输出重定向'>'
void mydup(char *argv[]);
//输出重定向'>>'
void mydup2(char *argv[]);
//输入重定向'<'
void mydup3(char *argv[]);
//管道'|'
//void mypipe(char *argv[], int cnt);
//实现多重管道'|'
void setup();//屏蔽信号
void callCommandWithPipe(char *argv[], int count);//
int execute(char *argv[]);//执行命令
void colorprint();


int main()
{
    
    char *argv[MAX]={NULL};
    char *cmdline=NULL;

    setup();
    

//没有循环出现--解决
//段错误
    while(1){
        colorprint();

        setup();

        cmdline=readline(" ");

        if(cmdline==NULL){//屏蔽ctrl+D
            printf("\n");
            continue;
        }
        
        char *mark=" ";
        int i=1;
        argv[0]=strtok(cmdline,mark);

        while(argv[i]=strtok(NULL,mark)){
            i++;
        }

        process(argv,i);
        free(cmdline);

    }
   
   free(argv);

    return 0;
    
}

void colorprint(){
    char *name="zhuheqin@zhuheqin-ThinkPad-E14-Gen-4";
    printf("\033[1m\033[32m%s\033[0m",name);
    printf(":");
    getcwd(lujing,sizeof(lujing));
    printf("\033[1m\033[34m%s\033[0m",lujing);
    printf("$ ");

    fflush(stdout);//清空缓冲区
}

void setup()
{
    //按下ctrl+c或者是delete没有反应，屏蔽此信号
    signal(SIGINT,SIG_IGN);//设置某一信号的对应动作，错误返回-1
    //SIG_IGN忽略前一个参数所代表的信号
    signal(SIGHUP,SIG_IGN);
}

void fatal(char *s1,char *s2,int n)
{
    fprintf(stderr,"Error:%s,%s\n",s1,s2);
    exit(n);
}

void process(char *argv[],int cnt){
    int flag=isdo(argv,cnt);
    if(pass==1){
        cnt--;
    }
    if(flag==1){
        mycd(argv);
    }else if(strcmp(argv[0],"exit")==0){
        printf("exit\n有停止的任务\n");
        exit(0);
    }else if(flag==2){
        mydup(argv);
    }else if(flag==3){
        callCommandWithPipe(argv,cnt);
    }else if(flag==4){
        mydup2(argv);
    }else if(flag==5){
        mydup3(argv);
    }else if(flag==10){
        execute(argv);
    }
}

int execute(char *argv[])
{
    int pid;
    int child_info=-1;

    if(argv[0]==NULL)
        return 0;
    if((pid=fork())==-1)
        perror("fork");
    else if(pid==0){
        signal(SIGINT,SIG_DFL);
        //signal(SIGQUIT,SIG_DFL);
        execvp(argv[0],argv);
        perror("cannot execute command");
        exit(1);
    }
    else{
        if(wait(&child_info)==-1)
            perror("wait");
    }

    return child_info;
}



//管道fd[0]为读端，fd[1]为写端,pipe单向，有名管道双向
//在父进程中，fork返回新创建子进程的进程ID；在子进程中，fork返回0；    



int isdo(char *argv[],int cnt){
    int flag=10,i;
    if(argv[0]==NULL){
        return 0;
    }
    if(strcmp(argv[0],"cd")==0){
        flag=1;
    }
    //奇怪 flag的值一直都会被改变
    for(i=0;i<cnt;i++){
        if(strcmp(argv[i],">")==0){
            flag=2;
        }
        if(strcmp(argv[i],"|")==0){
            flag=3;
        }
        if(strcmp(argv[i],">>")==0){
            flag=4;
        }
        if(strcmp(argv[i],"<")==0){
            flag=5;
        }
        if(strcmp(argv[i],"&")==0){
            pass=1;
            argv[i]=NULL;
        }
    }
    return flag;

}

char strcwd[MAX];
void mycd(char *argv[]){
    if(argv[1]==NULL){
        getcwd(strcwd,sizeof(strcwd));
        chdir("/home");
    }else if(strcmp(argv[1],"~")==0){
        getcwd(strcwd,sizeof(strcwd));
        chdir("/home/zhuheqin");

    }else if(strcmp(argv[1],"-")==0){//返回进入此目录之前所在的目录
        char strcwd1[MAX];
        getcwd(strcwd1,sizeof(strcwd1));
        chdir(strcwd);
        printf("%s\n",strcwd);
        strcpy(strcwd,strcwd1);
    }else{
        getcwd(strcwd,sizeof(strcwd));
        chdir(argv[1]);
    }
    

}

//重定向没有实现--已解决
void mydup(char *argv[])//重定向使输出输出到文件中
{
    char *str[MAX]={NULL};
    int i=0;

    while(strcmp(argv[i],">")){
        str[i]=argv[i];//存入之前的参数
        i++;
    }
  //  printf("%s",str[i]);
    int number=i;//记录参数个数
    int flag=isdo(argv,number);
    i++;

    int filefdout=dup(1);//获取新的文件描述符
    int fd=open(argv[i],O_WRONLY|O_CREAT|O_TRUNC,0666);

    dup2(fd,1);//指定新文件描述符为1

    //fork新进程
    pid_t pid=fork();
    if(pid<0){
        perror("fork");
        exit(1);
    }else if(pid==0){//child
        if(flag==3){
        callCommandWithPipe(str,number);
        }else{
            //execvp(str[0],str);
            execute(str);
        }
    }else if(pid>0){
        if(pass==1){
            pass=0;
            printf("%d\n",pid);
            return;
        }
        waitpid(pid, NULL, 0);
    }
    dup2(filefdout,1);
}

//和mydup几乎一模一样
void mydup2(char *argv[])//重定向使输出输出到文件中
{
    char *str[MAX]={NULL};
    int i=0;

    while(strcmp(argv[i],">>")){
        str[i]=argv[i];//存入之前的参数
        i++;
    }
    int number=i;//记录参数个数
    int flag=isdo(argv,number);
    i++;

    int filefdout=dup(1);//获取新的文件描述符
    int fd=open(argv[i],O_WRONLY|O_CREAT|O_APPEND,0666);

    dup2(fd,1);//关闭标准输出，返回大于1的文件描述符

    //fork新进程
    pid_t pid=fork();
    if(pid<0){
        perror("fork");
        exit(1);
    }else if(pid==0){//child
        if(flag==3){//有管道的情况
            callCommandWithPipe(str,number);
        }else{
            execvp(str[0],str);
        }
    }else if(pid>0){
        if(pass==1){
            pass=0;
            printf("%d\n",pid);
            return;
        }
        waitpid(pid, NULL, 0);
    }
    dup2(filefdout,1);
}

void mydup3(char *argv[])
{
    char *str[MAX]={NULL};
    int i=0;

    while(strcmp(argv[i],"<")){
        str[i]=argv[i];
        i++;
    }
    i++;

    int number=i;
    int flag=isdo(argv,number);

    int filefdin=dup(0);
    int fd=open(argv[i],O_RDONLY,0666);
    dup2(fd,0);

    pid_t pid=fork();
    if(pid<0){
        if(pass==1){
            pass=0;
            printf("%d\n",pid);
            return;
        }
        perror("fork");
        exit(1);
    }else if(pid==0){
        if(flag==3){
            callCommandWithPipe(str,number);
        }else{
            execvp(str[0],str);
        }

    }else if(pid>0){
        waitpid(pid,NULL,0);
    }
    dup2(filefdin,0);
}

void callCommandWithPipe(char *argv[],int count)//多重管道
{
    int ret[10]={0};//记录管道的位置
    int number=0;//记录命令个数
    int i;
    pid_t pid;

    for(i=0;i<count;i++){
        if(!strcmp(argv[i],"|")){//遇到管道符则进入记录其位置
            ret[number++]=i;
        }
    }

    int cmd_count=number+1;
    char *cmd[cmd_count][10];

    for(int i=0;i<cmd_count;i++){//将命令以管道分割符分好
        
        if(i==0){
            int n=0;
            for(int j=0;j<ret[i];j++){
                cmd[i][n++]=argv[j];
            }
            cmd[i][n]=NULL;
        }else if(i==cmd_count-1){
            int n=0;
            for(int j=ret[i-1]+1;j<count;j++){
                cmd[i][n++]=argv[j];
            }
            cmd[i][n]=NULL;
        }else{
            int n=0;
            for(int j=ret[i-1]+1;j<ret[i];j++){
                cmd[i][n++]=argv[j];
            }
            cmd[i][n]=NULL;
        }
    }

  //创建管道
  int fd[number][2];
  for(i=0;i<number;i++){
    pipe(fd[i]);
  }
  //创建子进程
  for(i=0;i<cmd_count;i++){
    pid=fork();
    if(pid==0){
        break;
    }
  }
  if(pid==0){//child
    if(number){//保证单向通信
        if(i==0){
            dup2(fd[0][1],1);//绑定写端
            close(fd[0][0]);//关闭读端

            for(int j=1;j<cmd_count-1;j++){//其他管道读写端全部关闭
                close(fd[j][1]);
                close(fd[j][0]);
            }
        }else if(i==number){//最后一个管道
            dup2(fd[i-1][0],0);//绑定读端
            close(fd[i-1][1]);//关闭写端

            for(int j=0;j<cmd_count-2;j++){
                close(fd[j][1]);
                close(fd[j][0]);
            }
        }else{
            dup2(fd[i-1][0],0);
            close(fd[i-1][1]);
            dup2(fd[i][1],1);
            close(fd[i][0]);

            for(int j=0;j<number;j++){
                if(j!=(i-1)&&j!=i){
                    close(fd[j][0]);
                    close(fd[j][1]);
                }
            }
        }
    }
  
  execvp(cmd[i][0],cmd[i]);//文件名和路径
  perror("execvp");
  exit(1);
  }
  
    for(i=0;i<number;i++){
        close(fd[i][0]);
        close(fd[i][1]);
    }
    if(pass==1){
            pass=0;
            printf("%d\n",pid);
            return;
        }
       // waitpid(pid, NULL, 0);
    
    for(int j=0;j<number;j++){
        wait(NULL);
    }
    
}



```

