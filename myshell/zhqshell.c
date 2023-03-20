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


#define YES 1
#define NO 0

#define DFL_PROMPT "zhq_shell~$ "

#define MAX 128

int pass=0;//标记&

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
void mypipe(char *argv[], int cnt);
//实现多重管道'|'
void setup();//屏蔽信号
void callCommandWithPipe(char *argv[], int count);//
void fatal(char *s1,char *s2,int n);
char * next_cmd(char *prompt,FILE *fp);//放置缓冲空间
int execute(char *argv[]);//执行命令
void * emalloc(size_t n);//添加了错误提示
char * newstr(char *s,int l);
void freelist(char **list);
void * erealloc(void *p,size_t n);


int main()
{
    char *cmdline,*prompt,**argv=NULL;
    int i=1;
    const char *mark=" ";
    void setup();//忽略信号

    prompt=DFL_PROMPT;
    setup();

    while((cmdline=next_cmd(prompt,stdin))!=NULL)
    {
        argv[0]=strtok(cmdline,mark);
        while(argv[i]=strtok(NULL,mark)){
            i++;
        }
        process(argv,i);
        
        free(cmdline);
    }
    return 0;
}

void setup()
{
    //按下ctrl+c或者是delete没有反应，屏蔽此信号
    signal(SIGINT,SIG_IGN);//设置某一信号的对应动作，错误返回-1
    //SIG_IGN忽略前一个参数所代表的信号
    signal(SIGQUIT,SIG_IGN);/*忽略ctrl+\*/
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
        signal(SIGQUIT,SIG_DFL);
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



char * next_cmd(char *prompt,FILE *fp)
{
    char *buf;
    int bufspace=0;
    int pos=0;
    int c;

    printf("%s",prompt);//打印标志
    while((c=getc(fp))!=EOF){//当命令行有输入时
        if(pos+1>=bufspace)
        {
            if(bufspace==0)
                buf=emalloc(BUFSIZ);//分配缓存空间
            else
                buf=erealloc(buf,bufspace+BUFSIZ);//增加长度
            bufspace+=BUFSIZ;
        }
        if(c=='\n')
            break;//命令结束
        buf[pos++]=c;
    }

        if(c==EOF&&pos==0)
            return NULL;
        buf[pos]='\0';//放置到缓冲区
        return buf;//返回值是指向缓冲区的指针
    }





void * emalloc(size_t n)
{
    void *rv;
    if((rv=malloc(n))==NULL)
        fatal("out of memory","",1);
    return rv;
}

char * newstr(char *s,int l)
{
    char *rv=emalloc(l+1);
    rv[l]='\0';
    strncpy(rv,s,l);
    return rv;
}

void freelist(char **list)
{
    char **cp=list;
    while(*cp)
        free(*cp++);
    free(list);
}


void * erealloc(void *p,size_t n)
{
    void *rv;
    if((rv=realloc(p,n))==NULL)
            fatal("realloc()failed","",1);
    return rv;
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
    for(i=0;i<cnt;i++){
        if(strcmp(argv[0],">")==0){
            flag=2;
        }
        if(strcmp(argv[0],"|")==0){
            flag=3;
        }
        if(strcmp(argv[0],">>")==0){
            flag=4;
        }
        if(strcmp(argv[0],"<")==0){
            flag=5;
        }
        if(strcmp(argv[0],"<<")==0){
            flag=6;
        }
        if(strcmp(argv[0],"&")==0){
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

void mydup(char *argv[])//重定向使输出输出到文件中
{
    char *str[MAX]={NULL};
    int i=0;

    while(strcmp(argv[i],">")){
        str[i]=argv[i];//存入之前的参数
        i++;
    }
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

    for(i=0;i<count;i++){
        if(!strcmp(argv[i],"|")){//遇到管道符则进入记录其位置
            ret[number++]=i;
        }
    }

    int cmd_count=number+1;
    char *cmd[cmd_count][10];

    for(i=0;i<cmd_count;i++){//将命令以管道分割符分好
        int j,n=0,i=0;
        if(i==0){
            for(j=0;j<ret[i];j++){
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



}