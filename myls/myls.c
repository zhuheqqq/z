#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>
#include<pwd.h>
#include<linux/limits.h>
#include<time.h>
#include<grp.h>
#include<dirent.h>


#define PARAM_NONE 0  //none
#define PARAM_A    1  //a
#define PARAM_L    2  //l
#define PARAM_I    4  //i
#define PARAM_T    8  //t
#define PARAM_r   16 //r
#define PARAM_R    32 //R

#define MAX 80

#define NORMAL 0
#define GREEN 1
#define BLUE 2
#define S_BLUE 3
#define YELLOW 4

int g_linelen=MAX;
int g_maxlen;

void my_err(const char *err,int line)
{
	fprintf(stderr,"line:%d ",line);
	perror(err);//打印错误原因
	if(errno!=13)
	{
		exit(1);
	}else{
		printf("无权限");
	}
}

void color_print(char *name,int color)
{
	if(color==NORMAL)
		printf(" %-s",name);
	else if(color==GREEN)
		printf("\033[1;32m %-s\033[0m" "",name);
	else if(color==BLUE)
		printf("\033[1;34m %-s\033[0m" "",name);
}

void l_print(struct stat statres,char *name,int color)
{
	char statres_time[32];


	// if(stat(fname,&statres)<0)
	// {
	// 	perror("stat()");
	// 	exit(1);
	// }

	if(S_ISREG( statres.st_mode))
		printf("-");
	else if(S_ISDIR(statres.st_mode))
		printf("d");
	else if(S_ISSOCK(statres.st_mode))
		printf("s");
	else if(S_ISCHR(statres.st_mode))
		printf("c");
	else if(S_ISBLK(statres.st_mode))
		printf("b");
	else if(S_ISFIFO(statres.st_mode))
		printf("p");
	else if(S_ISLNK(statres.st_mode))
		printf("l");
/*	else
		return '?';*/

	if(statres.st_mode&S_IRUSR)
		printf("r");
	else
		printf("-");
	if(statres.st_mode&S_IWUSR)
		printf("w");
	else
		printf("-");
	if(statres.st_mode&S_IXUSR)
		printf("x");
	else
		printf("-");


	if(statres.st_mode&S_IRUSR)
		printf("r");
	else
		printf("-");
	if(statres.st_mode&S_IWUSR)
		printf("w");
	else
		printf("-");
	if(statres.st_mode&S_IXUSR)
		printf("x");
	else
		printf("-");


	if(statres.st_mode&S_IRUSR)
		printf("r");
	else
		printf("-");
	if(statres.st_mode&S_IWUSR)
		printf("w");
	else
		printf("-");
	if(statres.st_mode&S_IXUSR)
		printf("x");
	else
		printf("-");
	printf("\t");

	struct passwd *psd;
	struct group *grp;

	psd=getpwuid(statres.st_uid);
	grp=getgrgid(statres.st_gid);

	printf("%4ld ",statres.st_nlink);
	printf("%-8s ",psd->pw_name);
	printf("%-8s",grp->gr_name);
	printf("%6ld",statres.st_size);

	strcpy(statres_time,ctime(&statres.st_mtime));
	statres_time[strlen(statres_time)-1]='\0';
	printf("%s",statres_time);

	color_print(name,color);
	printf("\n");
}

//if no l
void no_l_print(char *name,int color)
{
	int i,len;
	if(g_linelen<g_maxlen)
	{
		printf("\n");
		g_linelen=MAX;
	}

	len=strlen(name);
	len=g_maxlen-len;

	color_print(name,color);

	for(i=0;i<len;i++)
	{
		printf(" ");
	}
	printf(" ");

	g_linelen-=(g_maxlen+2);
}

void i_print(char *name,int color)
{
	int i,len;
	struct stat statres;

	if(g_linelen<g_maxlen)
	{
		printf("\n");
		g_linelen=MAX;
	}

	if(lstat(name,&statres)<0)
	{
		my_err("lstat",__LINE__);
	}

	printf("%ld",statres.st_ino);

	len=strlen(name);
	len=g_maxlen-len;

	color_print(name,color);

	for(i=0;i<len;i++)
		printf(" ");
	printf(" ");

	g_linelen-=(g_maxlen+2+8);
}

void dir_print(int flag,char *path)
{
	DIR *dir;
	struct dirent *ptr;
	int count=0;
	struct stat statres;
	char **filename;

	filename=(char **)malloc(sizeof(char *)*20000);

	int i;
	for(i=0;i<20000;i++)
		filename[i]=(char *)malloc(PATH_MAX+1);

	long *filetime;
	filetime=(long *)malloc(sizeof(long)*20000);

	char temp[PATH_MAX];
	long timeTemp;

	dir=opendir(path);
	if(dir==NULL)
		my_err("opendir",__LINE__);

	while((ptr=readdir(dir))!=NULL)
	{
		if(g_maxlen<strlen(ptr->d_name))
			g_maxlen=strlen(ptr->d_name);
		count++;
	}

	closedir(dir);

	if(count>20000)
		my_err("too many files under the directory",__LINE__);

	int j;
	int len=strlen(path);

	dir=opendir(path);

	for(i=0;i<count;i++)
	{
		ptr=readdir(dir);
		if(ptr==NULL)
			my_err("readdir",__LINE__);
		strncpy(filename[i],path,len);
		filename[i][len]=0;
		strcat(filename[i],ptr->d_name);
		filename[i][len+strlen(ptr->d_name)]=0;
		lstat(filename[i],&statres);
		filetime[i]=statres.st_mtime;
	}

	closedir(dir);

	if(flag&PARAM_T)
	{
		for(i=0;i<count-1;i++)
		{
			for(j=0;j<count-1-i;j++)
			{
				if(filetime[j]<filetime[j+1])
				{
					timeTemp=filetime[j];
					filetime[j]=filetime[j+1];
					filetime[j+1]=timeTemp;
					strcpy(temp,filename[j]);
					strcpy(filename[j],filename[j+1]);
					strcpy(filename[j+1],temp);
				}
			}
		}
	}else{
            for(i=0;i<count-1;i++)
            {
                for(j=0;j<count-1-i;j++)
                {
                    if(strcmp(filename[j],filename[j+1])>0)
                    {
                        strcpy(temp,filename[j]);
                        strcpy(filename[j],filename[j+1]);
                                strcpy(filename[j+1],temp);
                    }
                }
            }
		}
        if(flag&PARAM_R){
            if(flag&PARAM_r){
                for(i=count-1;i>=0;i--){
                    print(flag,filename[i]);
                }
                for(i=count-1;i>=0;i--){
                    if((stat(filename[i],&statres))==-1){
                        my_err("stat",__LINE__);
                    }
                    if(S_ISDIR(statres.st_mode))
                    {
                        len=strlen(filename[i]);
                    if(filename[i][len-1]=='.'&&filename[i][len-2]=='/'||filename[i][len-1] == '.' && filename[i][len-2] == '.' && filename[i][len-3] == '/')
                    {
                        continue;
                    }
                    printf("\n\n%s:",filename[i]);


                    len=strlen(filename[i]);
                    strcat(filename[i],"/");
                    dir_print(flag,filename[i]);
                }else{
                    print(flag,filename[i]);
                }
            }
        }else{
            for(i=0;i<count;i++){
                stat(filename[i],&statres);
                if(S_ISDIR(statres.st_mode)){
                    len=strlen(filename[i]);
                    if(filename[i][len-1] == '.' && filename[i][len-2] == '/' || 
            filename[i][len-1] == '.' && filename[i][len-2] == '.' && filename[i][len-3] == '/'){
                continue;
            }
            printf("\n\n%s:\n",filename[i]);

            len=strlen(filename[i]);
            strcat(filename[i],"/");
            dir_print(flag,filename[i]);
                }else{
                    print(flag,filename[i]);
                }
            }
        }
    }else{
        if(flag&PARAM_r){
            for(i=count-1;i>=0;i--){
                print(flag,filename[i]);
            }
        }else{
            for(i=0;i<count;i++){
                print(flag,filename[i]);
            }
        }
    }

    if((flag&PARAM_L)==0){
        printf("\n");
    }

    for(i=0;i<20000;i++){
        free(filename[i]);
    }

    free(filename);
    free(filename);

}






void print(int flag,char *pathname)
{
int i,j;
struct stat statres;
char name[PATH_MAX+1];
int color =NORMAL;

for(i=0,j=0;i<strlen(pathname);i++)
{
    if(pathname[i]=='/')
    {
        j=0;
        continue;
        //continue语句的作用是跳过本次循环体中余下尚未执行的语句
        //立即进行下一次的循环条件判定，可以理解为仅结束本次循环。
    }
    name[j++]=pathname[i];
}
name[j]=0;

lstat(pathname,&statres);

if(S_ISDIR(statres.st_mode))
    color=BLUE;
if((statres.st_mode&S_IXUSR)&&color!=BLUE)
    color=GREEN;
if(flag&PARAM_R)
    flag-=PARAM_R;
if(flag&PARAM_r)
    flag-=PARAM_r;

switch(flag)
{
    case PARAM_NONE:
        if(name[0]!='.')
            no_l_print(name,color);
        break;
    case PARAM_L:
        if(name[0]!='.')
            l_print(statres,name,color);
        break;
    case PARAM_A:
        no_l_print(name,color);
        break;
    case PARAM_A+PARAM_I:
        i_print(name,color);
        break;
        case PARAM_A+PARAM_L:;
        l_print(statres,name,color);
        break;
    case PARAM_I+PARAM_L:
        if(name[0]!='.')
        {
            printf(" %ld",statres.st_ino);
            dir_print(flag,name);
            break;
            case PARAM_L+PARAM_A+PARAM_I:
            printf("%ld ",statres.st_ino);
            dir_print(flag,name);
            break;
            case PARAM_I:
            if(name[0]!='.')
                i_print(name,color);
            break;
            default:
            break;
        }
    }
}


int main(int argc, char *argv[]) {
    int i;
    int j;
    int k;
    int num;
    char path[PATH_MAX+1];
    char param[32];
    int  flag_param = PARAM_NONE;
    struct stat  statres;

    j = 0;
    num = 0;

    //解析其参数，以-为标志
    for(i = 1; i < argc;i++) {
        if(argv[i][0] == '-') {
            for(k = 1;k < strlen(argv[i]);k++,j++) {
                param[j] = argv[i][k];
            }
            num++;
        }
    }


    //利用位运算确定具体参数
    for(i = 0;i < j;i++) {
        if(param[i] == 'a'){
            flag_param |= PARAM_A;//利用位运算
            continue;
        }
        else if(param[i] == 'l'){
            flag_param |= PARAM_L;
            continue;
        } 
        else if(param[i] == 'i'){
            flag_param |= PARAM_I;
            continue;
        } 
        else if(param[i] == 'r'){
            flag_param |= PARAM_r;
            continue;
        } 
        else if(param[i] == 't'){
            flag_param |= PARAM_T;
            continue;
        }else if(param[i] == 'R'){
            flag_param |= PARAM_R;
            continue;
        }    
        else{
            printf("my_ls: incalid option -%c\n", param[i]);
            exit(1);
        }
    }

    param[j] = 0;

    //默认为当前路径
    if((num+1) == argc) {
        strcpy(path,"./");
        path[2] =  0;
        dir_print(flag_param,path);
        return 0;
    }

    i = 1;
    do{ 
        if(argv[i][0] == '-') {
            i++;
            continue;
        } else {
            //得到具体路径
            strcpy(path, argv[i]);
            if(stat(path,&statres) == -1)
                my_err("stat",__LINE__);

            //判断是否为目录文件 
            if(S_ISDIR(statres.st_mode)) {
                //如果目录最后忘记了/则加上
                if(path[strlen(argv[i]) - 1] != '/') {
                    path[strlen(argv[i])]  = '/';
                    path[strlen(argv[i])+1] = 0;
                }
                else 
                    path[strlen(argv[i])] = 0;

                dir_print(flag_param,path);//按照目录输出
                i++;
            } else {
                //按照文件输出
                print(flag_param,path);
                i++;
            }
        }
    } while(i < argc);

    return 0;
}






