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
int g_maxlen;//最长文件名，以此为标准

void my_err(const char *err,int line)
{
	fprintf(stderr,"line:%d ",line);
	perror(err);//打印错误原因
	if(errno!=13)
	{
		exit(0);
	}else{
		printf("无权限\n");
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


int cmp(const void *_a,const void *_b)  
{
    char *a=(char*)_a;
    char *b=(char*)_b;
    return strcmp(a,b);
}

void ls_l(struct stat statres,char *name,int color)
{
	char statres_time[32];


	// if(stat(fname,&statres)<0)
	// {
	// 	perror("stat()");
	// 	exit(1);
	// }

	if(S_ISREG(statres.st_mode))
		printf("-");
	else if(S_ISDIR(statres.st_mode)){
		printf("d");
		color=BLUE;
	}
	else if(S_ISSOCK(statres.st_mode))
		printf("s");
	else if(S_ISCHR(statres.st_mode))
		printf("c");
	else if(S_ISBLK(statres.st_mode))
		printf("b");
	else if(S_ISFIFO(statres.st_mode))
		printf("f");
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
	printf(" ");

	struct passwd *psd;
	struct group *grp;

	psd=getpwuid(statres.st_uid);
	grp=getgrgid(statres.st_gid);

	printf("%ld ",statres.st_nlink);
	printf("%-8s ",psd->pw_name);
	printf("%-8s",grp->gr_name);
	printf("%6ld",statres.st_size);

	strcpy(statres_time,ctime(&statres.st_mtime));
	statres_time[strlen(statres_time)-1]='\0';
	printf("  %s",statres_time);

	color_print(name,color);
	printf("\n");
}

//if no l
void ls_no_l(char *name,int color)
{
	int i,len;
	if(g_linelen<g_maxlen)
	{
		printf("\n");//位置不够换行
		g_linelen=MAX;
	}

	len=strlen(name);
	len=g_maxlen-len;//用最大长度对齐

	color_print(name,color);

	for(i=0;i<len;i++)
	{
		printf(" ");
	}
	//printf(" ");

	g_linelen-=(g_maxlen+2);
}

void ls_i(char *name,int color)
{
	int i,len;
	struct stat statres;

	if(g_linelen<g_maxlen)
	{
		printf("\n");
		g_linelen=MAX;
	}

	if(lstat(name,&statres)==-1)
	{
		my_err("lstat",__LINE__);
	}

	printf("%ld",statres.st_ino);

	len=strlen(name);
	len=g_maxlen-len;
	//printf("len=%d",len);
	color_print(name,color);

	for(i=0;i<len;i++)
		printf(" ");
//	printf(" ");

	g_linelen-=(g_maxlen+2+8);
}





void ls_R(char*name,int flag)  
 
{
DIR * dir;
struct dirent  *ptr;
int     i,count = 0;
struct stat buf;
char name_dir[10000];
if(chdir(name)<0)                              //将输入的目录改为当前目录，下面操作的前提
{ 
    if(lstat(name,&buf)==-1)
          {  if(errno==13)
              { printf("Permission denied\n");
                return;
              }
              else if(strncmp(name,"/proc",4)==0)
                 { printf("this is a /proc file\n");
                   return;
                 }
            else 
             my_err("lstat",__LINE__);
          }
}
if(getcwd(name_dir,10000)<0){
  my_err("getcwd",__LINE__);                   //获取当前目录的绝对路径（重要，下面的打开目录的操作需要这个路径，否则需要手动添加）
}
 printf("%s:\n",name_dir);
 
 dir = opendir(name_dir);     //用新获得的路径打开目录
if(dir==NULL){
  my_err("opendir",__LINE__);
}
 
  g_maxlen=0;
while((ptr = readdir(dir))!=NULL){
  if(g_maxlen<strlen(ptr->d_name))
         g_maxlen = strlen(ptr->d_name);
    count++;
}
closedir(dir);
 
//动态数组(用静态数组会爆)
  char**filenames =(char**)malloc(count*sizeof(char*));    //要进行初始化 
  memset(filenames,0,sizeof(char*)*count);
 
for(i=0;i<count;i++){
 
  filenames[i]=(char*)malloc(256*sizeof(char));
  memset(filenames[i],0,sizeof(char)*256);
}
 
 
int j,len=strlen(name_dir);
dir = opendir(name_dir);
for(i=0;i<count;i++){
    ptr = readdir(dir);
    if(ptr == NULL){
      my_err("readdir",__LINE__);
    }
 
    strcat(filenames[i],ptr->d_name);   
}
for(i=0;i<count;i++)
   print(flag,filenames[i]);
  printf("\n");
                          //递归实现核心部分
 
      for(i=0;i<count;i++){
 
          if(lstat(filenames[i],&buf)==-1)
          {  if(errno==13)
              { printf("Permission denied\n");
                return;
              }
              else if(strncmp(filenames[i],"/proc",4)==0)
                 { printf("this is a /proc file\n");
                   return;
                 }
            else 
             my_err("lstat",__LINE__);
          }
          if(strcmp(filenames[i],"..")==0)
          continue;
          if(filenames[i][0]=='.')
          continue;
          if(S_ISDIR(buf.st_mode)){
            int h=0;
            g_linelen=MAX;
            ls_R(filenames[i],flag);
          }
          else if(!S_ISDIR(buf.st_mode))
           {
             continue;
           }
               chdir("../");          //处理完一个目录后返回上一层
        }
 
    
    for(i=0;i<count;i++)
    {
      free(filenames[i]);
    }
    free(filenames);
    closedir(dir);          
    }


// void dir_print(int flag,char *path)
// {
// 	DIR *dir;
// 	struct dirent *ptr;
// 	int count=0;
// 	struct stat statres;
// //	char **filename;

// 	//filename=(char **)malloc(sizeof(char *)*20000);

// 	int i;
// 	//for(i=0;i<20000;i++)
// 	//	filename[i]=(char *)malloc(PATH_MAX+1);

// 	long *filetime;
// 	filetime=(long *)malloc(sizeof(long)*20000);

// 	char temp[PATH_MAX];
// 	long timeTemp;

// 	dir=opendir(path);
// 	if(dir==NULL)
// 		my_err("opendir",__LINE__);

// 	while((ptr=readdir(dir))!=NULL)
// 	{
// 		if(g_maxlen<strlen(ptr->d_name))
// 			g_maxlen=strlen(ptr->d_name);
// 		count++;
// 	}

// 	closedir(dir);

// 	//动态数组
// 	char**filename=(char**)malloc((count)*sizeof(char*));
// 	memset(filename,0,sizeof(char*)*(count));

// 	for(i=0;i<count;i++)
// 	{
// 		filename[i]=(char*)malloc(1024*sizeof(char));
// 		memset(filename[i],0,sizeof(char)*1024);
// 	}

	

	

// 	int j,k;
// 	int len=strlen(path);

// 	dir=opendir(path);

// 	for(k=0;k<count;k++)
// 	{
// 		ptr=readdir(dir);
// 		if(ptr==NULL)
// 			my_err("readdir",__LINE__);
// 		strncpy(filename[k],path,len);
// 		filename[k][len]=0;
// 		strcat(filename[k],ptr->d_name);
// 		filename[k][len+strlen(ptr->d_name)]=0;
// 		lstat(filename[k],&statres);
// 		filetime[k]=statres.st_mtime;
// 	}

// 	closedir(dir);

// 	if(flag&PARAM_T)
// 	{
// 		for(k=0;k<count-1;k++)
// 		{
// 			for(j=0;j<count-1-k;j++)
// 			{
// 				if(filetime[j]<filetime[j+1])
// 				{
// 					timeTemp=filetime[j];
// 					filetime[j]=filetime[j+1];
// 					filetime[j+1]=timeTemp;
// 					strcpy(temp,filename[j]);
// 					strcpy(filename[j],filename[j+1]);
// 					strcpy(filename[j+1],temp);
// 				}
// 			}
// 		}
// 	}else{
//             for(k=0;k<count-1;k++)
//             {
//                 for(j=0;j<count-1-k;j++)
//                 {
//                     if(strcmp(filename[j],filename[j+1])>0)
//                     {
//                         strcpy(temp,filename[j]);
//                         strcpy(filename[j],filename[j+1]);
//                         strcpy(filename[j+1],temp);
//                     }
//                 }
//             }
// 		}
//         if(flag&PARAM_R){
//             if(flag&PARAM_r){
//                 for(k=count-1;k>=0;k--){
//                     print(flag,*filename[k]);
//                 }
//                 for(k=count-1;k>=0;k--){
//                     if((stat(filename[k],&statres))==-1){
//                         my_err("stat",__LINE__);
//                     }
//                     if(S_ISDIR(statres.st_mode))
//                     {
//                         len=strlen(filename[k]);
//                     if(filename[k][len-1]=='.'&&filename[k][len-2]=='/'||filename[k][len-1] == '.' && filename[k][len-2] == '.' && filename[k][len-3] == '/')
//                     {
//                         continue;
//                     }
//                     printf("\n\n%s:",filename[k]);


//                     len=strlen(filename[k]);
//                     strcat(filename[k],"/");
//                     dir_print(flag,filename[k]);
//                 }else{
//                     print(flag,filename[k]);
//                 }
//             }
//         }else{
//             for(k=0;k<count;k++){
//                 stat(filename[k],&statres);
//                 if(S_ISDIR(statres.st_mode)){
//                     len=strlen(filename[k]);
//                     if(filename[k][len-1] == '.' && filename[k][len-2] == '/' ||

//             filename[k][len-1] == '.' && filename[k][len-2] == '.' && filename[k][len-3] == '/'){
//                 continue;
//             }
//             printf("\n\n%s:\n",filename[k]);

//             len=strlen(filename[k]);
//             strcat(filename[k],"/");
//             dir_print(flag,filename[k]);
//                 }else{
//                     print(flag,filename[k]);
//                 }
//             }
//         }
//     }else{
//         if(flag&PARAM_r){
//             for(k=count-1;k>=0;k--){
//                 print(flag,filename[k]);
//             }
//         }else{
//             for(k=0;k<count;k++){
//                 print(flag,filename[k]);
//             }
//         }
//     }

//     if((flag&PARAM_L)==0){
//         printf("\n");
//     }

//     for(k=0;k<20000;k++){
//         free(filename[k]);
//     }

//     free(filename);
//     free(filetime);

// }
void dir_print(int flag,char*path)
{
    DIR *dir;
    struct dirent * ptr;
    int cnt=0;  //计算文件个数
    char filename[256][PATH_MAX+1];
    long filetime[256];
    char tmpfilename[PATH_MAX+1];
    struct stat buf;
    dir=opendir(path);
    if(dir==NULL)
    {
        my_err("opendir",__LINE__);
    }
    while((ptr=readdir(dir))!=NULL)
     {
         int hanzi=0;
         int nohanzi=0;
         for(int i=0;i<strlen(ptr->d_name);i++)
          {    
              if(ptr->d_name[i]<0)
              hanzi++;
              else
              nohanzi++;
          }
        int len=hanzi*2+nohanzi;
        if(g_maxlen<len)
        g_maxlen=len;
 
        cnt++;
     }
     closedir(dir);
 
     if(cnt>256)  //过多文件
      printf("%d :too many files under this dir",__LINE__);
      
      dir=opendir(path);
     for(int i=0;i<cnt;i++)
     {
         if((ptr=readdir(dir))==NULL)
          {
              my_err("readdir",__LINE__);
          }
 
         strncpy(filename[i],path,strlen(path));
         filename[i][strlen(path)]='\0';
         strcat(filename[i],ptr->d_name);
         filename[i][strlen(path)+strlen(ptr->d_name)]='\0';
       //printf("%d %s\n",i,filename[i]);
         
 
     }
      closedir(dir);
       if(flag&PARAM_T)
        {    
             flag-=PARAM_T;
             struct stat buf;
             for(int i=0;i<cnt;i++)
              {
                  if(lstat(filename[i],&buf)==-1)
                   {
                       my_err("lstat",__LINE__);
                   }
                   filetime[i]=buf.st_mtime;
              }
 
                for(int i=0;i<cnt;i++)
                   for(int j=i;j<cnt;j++)
                     if(filetime[j]>filetime[i])
                      {
                          long int t;
                          t=filetime[i];
                          filetime[i]=filetime[j];
                          filetime[j]=t;
                      }
            
        }
        else   //用文件名首字母排序
         {
              qsort(filename,cnt,sizeof(filename[0]),cmp);          
 
         }
           //for(int i=0;i<cnt;i++)
            //printf("%d %s\n",i,filename[i]);
          int total=0;
         //计算总量
          if(flag&PARAM_A)   //包括隐藏文件
           {
               for(int i=0;i<cnt;i++)
                {
                    if(lstat(filename[i],&buf)==-1)
                     {
                         my_err("lstat",__LINE__);
                     }
                    total=total+buf.st_blocks/2; 
                }
           }
          else
           {
                for(int i=0;i<cnt;i++)
                {   
                    if(lstat(filename[i],&buf)==-1)
                     {   
                         my_err("lstat",__LINE__);
                     }
                     if(filename[i][2]!='.')
                    total=total+buf.st_blocks/2; 
                }
           }
 
           if(flag&PARAM_L)
            {
               printf("总用量 %d\n",total);
            }
 
 
            if(flag&PARAM_r)
              {    flag-=PARAM_r;
                  if(flag&PARAM_R)  
                    {       flag-=PARAM_R;
                            ls_R(path,flag);
                    }
                    else
                     {    
                         for(int i=cnt-1;i>=0;i--)
                           {  
                           print(flag,filename[i]);
                           }
                     }
              }
            else
             {
                     if(flag&PARAM_R)
                      {   flag-=PARAM_R;
                          ls_R(path,flag);
                      }
                      else
                       {   
                           for(int i=0;i<cnt;i++)
                            {   
                                 print(flag,filename[i]);
                            }
                       }
 
             }
 
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
if(flag&PARAM_T)
    flag-=PARAM_T;

switch(flag)
{
    case PARAM_NONE:
        if(name[0]!='.')
            ls_no_l(name,color);
        break;
    case PARAM_L://-l
        if(name[0]!='.')
            ls_l(statres,name,color);
        break;
    case PARAM_A://-a
        ls_no_l(name,color);
        break;
    case PARAM_A+PARAM_I://-ai
        ls_i(name,color);
        break;
        case PARAM_A+PARAM_L:;//-al
        ls_l(statres,name,color);
        break;
    case PARAM_I+PARAM_L://-il
        if(name[0]!='.')
        {
            printf(" %ld",statres.st_ino);
            ls_l(statres,name,color);
	}
        break;
    case PARAM_L+PARAM_A+PARAM_I:
         printf("%ld ",statres.st_ino);
	 ls_l(statres,name,color);
         break;
    case PARAM_I:
         if(name[0]!='.')
            ls_i(name,color);
         break;
    default:
         break;
    }
}


int main(int argc, char *argv[])
{
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
    for(i = 0;i < j;i++) 
    {
        if(param[i] == 'a'){
            flag_param |= PARAM_A;//利用位运算
            continue;
        } else if(param[i] == 'l'){
            flag_param |= PARAM_L;
            continue;
        }else if(param[i] == 'i'){
            flag_param |= PARAM_I;
            continue;
        }else if(param[i] == 'r'){
            flag_param |= PARAM_r;
            continue;
        }else if(param[i] == 't'){
            flag_param |= PARAM_T;
            continue;
        }else if(param[i] == 'R'){
            flag_param |= PARAM_R;
            continue;
        }else{
            printf("my_ls: incalid option -%c\n", param[i]);
            exit(1);
        }
    }

    param[j] = 0;

    //默认为当前路径
    if((num+1) == argc) {
        strcpy(path,"./");
        path[2] = '\0';
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
            if(S_ISDIR(statres.st_mode)){
                //如果目录最后忘记了/则加上
                if(path[strlen(argv[i]) - 1] != '/') {
                    path[strlen(argv[i])]  = '/';
                    path[strlen(argv[i])+1] = '\0';
                }else 
                    path[strlen(argv[i])] = '\0';

                dir_print(flag_param,path);//按照目录输出
                i++;
            }else{
                //按照文件输出
                print(flag_param,path);
                i++;
            }
        }
    }while(i < argc);

    return 0;
}







