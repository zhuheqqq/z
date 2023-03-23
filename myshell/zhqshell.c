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


