#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
#include<ctype.h>


#define YES 1
#define NO 0

#define DFL_PROMPT "zhq_shell $ "

#define is_delim(x) ((x)==' '||(x)=='\t')

char *next_cmd();
char **splitline(char*);
void freelist(char**);
void *emalloc(size_t);
void *erealloc(void *,size_t);
int execute(char **);
void fatal(char *,char *,int);


enum states {NEUTRAL,WANT_THEN,THEN_BLOCK};//枚举
enum results {SUCCESS,FAIL};

static int if_state=NEUTRAL;
static int if_result=SUCCESS;
static int last_stat=0;

int main()
{
    char *cmdline,*prompt,**arglist;
    int result;
    void setup();

    prompt=DFL_PROMPT;
    setup();

    while((cmdline=next_cmd(prompt,stdin))!=NULL)
    {
        if((arglist=splitline(cmdline))!=NULL){
            result=process(arglist);
            freelist(arglist);
        }
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

int syn_err(char *msg)
{
    if_state=NEUTRAL;
    fprintf(stderr,"syntax error:%s\n",msg);
    return -1;
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

int ok_to_execute()
{
    int rv=1;
    if(if_state==WANT_THEN){
        syn_err("then expected");
        rv=0;
    }else if(if_state==THEN_BLOCK&&if_result==SUCCESS){
        rv=1;
    }else if(if_state==THEN_BLOCK&&if_result==FAIL)
    {
        rv=0;
    }
    return rv;

}

int is_control_command(char *s)
{
    return(strcmp(s,"if")==0||strcmp(s,"then")==0||strcmp(s,"fi")==0);
}

int do_control_command(char **args)
{
    char *cmd=args[0];
    int rv=-1;

    if(strcmp(cmd,"if")==0){
        if(if_state!=NEUTRAL){
             rv=syn_err("if unexpected");
        }else{
            last_stat=process(args+1);
            if_result=(last_stat==0?SUCCESS:FAIL);
            if_state=WANT_THEN;
            rv=0;
        }

    }else if(strcmp(cmd,"then")==0){
        if(if_state!=WANT_THEN){
            rv=syn_err("then unexpected");

        }else{
            if_state=THEN_BLOCK;
            rv=0;
        }
    }else if(strcmp(cmd,"else")==0){
        if(if_state!=WANT_THEN){
            rv=syn_err("else unexpected");

        }else{
            if_state=THEN_BLOCK;
            rv=0;
        }
    }else if(strcmp(cmd,"fi")==0){
        if(if_state!=THEN_BLOCK){
            rv=syn_err("fi unexpected");

        }else{
            if_state=NEUTRAL;
            rv=0;
        }
    }
    else{
        fatal("internal error processing:",cmd,2);
        return rv;
    }

}


int process(char ** args)
{
    int rv=0;
    if(args[0]==NULL)
    rv=0;
    else if(is_control_command(args[0])){
        rv=do_control_command(args);
    }
    else if(ok_to_execute()){
        rv=execute(args);
    }
    return rv;
}


char *next_cmd(char *prompt,FILE *fp)
{
    char *buf;
    int bufspace=0;
    int pos=0;
    int c;

    printf("%s",prompt);
    while((c=getc(fp))!=EOF){
        if(pos+1>=bufspace)
        {
            if(bufspace==0)
                buf=emalloc(BUFSIZ);
            else
                buf=erealloc(buf,bufspace+BUFSIZ);
            bufspace+=BUFSIZ;
        }
        if(c=='\n')
            break;
        buf[pos++]=c;
    }

        if(c==EOF&&pos==0)
            return NULL;
        buf[pos]='\0';
        return buf;
    }



char **splitline(char*line)
{
    char *newstr();
    char **args;
    int spots=0;
    int bufspace=0;
    int argnum=0;
    char *cp=line;
    char *start;
    int len;

    if(line==NULL)
        return NULL;

    args=emalloc(BUFSIZ);
    bufspace=BUFSIZ;
    spots=BUFSIZ/sizeof(char*);

    while(*cp!='\0'){
        while(is_delim(*cp))
            cp++;
        if(*cp=="\0")
            break;
        if(argnum+1>=spots)
        {
            args=erealloc(args,bufspace+BUFSIZ);
            bufspace+=BUFSIZ;
            spots+=(BUFSIZ/sizeof(char*));
        }

        start=cp;
        len=1;
        while(*++cp!='\0'&&!(is_delim(*cp)))
            len++;
        args[argnum++]=newstr(start,len);
    }
    args[argnum]=NULL;
    return args;
}

void *emalloc(size_t n)
{
    void *rv;
    if((rv=malloc(n))==NULL)
        fatal("out of memory","",1);
    return rv;
}

char *newstr(char *s,int l)
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


void *erealloc(void *p,size_t n)
{
    void *rv;
    if((rv=realloc(p,n))==NULL)
            fatal("realloc()failed","",1);
    return rv;
}

            



