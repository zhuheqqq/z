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
#define PARAM_S    64  //s

#define MAX 80

#define NORMAL 0
#define GREEN 1
#define BLUE 2
#define S_BLUE 3
#define YELLOW 4

int g_linelen=MAX;//剩余长度
int g_maxlen;//最长文件名，以此为标准

void my_err(const char *err,int line)
{
	fprintf(stderr,"line:%d ",line);
	perror(err);//打印错误原因
	if(errno!=13)//13代表无权限
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
    char *b=(char*)_b;//强制类型转换
    return strcmp(a,b);//返回差值，标准cmp写法，是快排函数的一部分
}

void ls_l(struct stat statres,char *name,int color)
{
	char statres_time[32];
    char ch;
   

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
	else if(S_ISLNK(statres.st_mode)){
        printf("l");
        ch='l';
    }
		
/*	else
		return '?';*/

	if(statres.st_mode&S_IRUSR)//所有者权限
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


	if(statres.st_mode&S_IRUSR)//组用户权限
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


	if(statres.st_mode&S_IRUSR)//其他用户组权限
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

	printf("%ld ",statres.st_nlink);//硬链接数
	printf("%-8s ",psd->pw_name);//uid用户信息
	printf("%-8s",grp->gr_name);//gid组信息
	printf("%11ld",statres.st_size);//文件大小

	strcpy(statres_time,ctime(&statres.st_mtime));//时间
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

	if(lstat(name,&statres)==-1)//lstat返回文件相关信息，如果遇到符号链接不会展开，而是直接返回符号链接本身
	{
		my_err("lstat",__LINE__);
	}

	printf("%-20ld",statres.st_ino);//文件i结点号

	len=strlen(name);
	len=g_maxlen-len;
	//printf("len=%d",len);
	color_print(name,color);

	for(i=0;i<len;i++)
		printf(" ");
//	printf(" ");

	g_linelen-=(g_maxlen+2+8);
}

// void ls_s(char *name,int color)
// {
// 	struct stat statres;
// 	if(lstat(name,&statres)==-1)
// 	{
// 		my_err("lstat",__LINE__);
// 	}
// 	int i,len=strlen(name);
// 	/*g_linelen-=(g_maxlen+12);
// 	if(g_linelen<=g_maxlen)
// 	{
// 		printf("\n");
// 		g_linelen=MAX;
// 	}*/
// 	if(g_linelen<g_maxlen)
//         {
//                 printf("\n");
//                 g_linelen=MAX;
//         }

//           printf("%7ld",statres.st_blocks/2);


//         len=strlen(name);
//         len=g_maxlen-len;
//         //printf("len=%d",len);
//         color_print(name,color);

//         for(i=0;i<len+1;i++)
//                 printf(" ");

	
	  
// }

int ls_R(char*name,int flag)  
 
{
DIR * dir;
struct dirent  *ptr;
int     i,count = 0;
struct stat buf;
char name_dir[10000];
if(chdir(name)<0)       //无权限，跳过                       //将输入的目录改为当前目录，下面操作的前提
{ 
    
    if(errno==13){//定位错误原因，指文件拒绝访问许可
        errno=0;
        printf("%s/%s:",name_dir,name);
        printf("no perssion\n");
    }else{
        my_err("chdir",__LINE__);
    }

    return -1;
}
if(getcwd(name_dir,10000)<0){//getcwd将当前目录的绝对路径复制到name_dir
  my_err("getcwd",__LINE__); 
  return 0;                  //获取当前目录的绝对路径（重要，下面的打开目录的操作需要这个路径，否则需要手动添加）
}//拼接目录获取绝对路径
 //绝对路径是一个文件实际存在与硬盘的位置，相对路径是与自身的目标档案相关的位置
 printf("%s:\n",name_dir);
 
 dir = opendir(name_dir);     //用新获得的路径打开目录
//if(dir==NULL){
  //my_err("opendir",__LINE__);
  if(dir==NULL){
    if(errno==13){
        errno=0;
        printf("no perssion\n");
    }else{
        my_err("opendir",__LINE__);
    }
    return 0;
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
 
  filenames[i]=(char*)malloc(1024*sizeof(char));
  memset(filenames[i],0,sizeof(char)*1024);
}
 
 
int j,len=strlen(name_dir),h=0;
dir = opendir(name_dir);
for(i=0;i<count;i++){
    ptr = readdir(dir);
    if(ptr == NULL){
     // my_err("readdir",__LINE__);
     if(errno==13){
        errno=0;
        printf("no perssion\n");
     }else{
        my_err("readdir",__LINE__);
     }
     continue;
    }
 
    strcat(filenames[h++],ptr->d_name);   
}
for(i=0;i<h;i++)
   print(flag,filenames[i]);
  printf("\n");
                          //递归实现核心部分
 
      for(i=0;i<h;i++){
 
          if(lstat(filenames[i],&buf)==-1)
          {  if(errno==13)
              { errno=0;
              printf("%s/%s\n",name_dir,filenames[i]);
                printf("Permission denied\n");
                //return;
              }
              free(filenames[i]);
              continue;
          }
              else{
                if(strcmp(filenames[i],"..")==0)
                {
                    free(filenames[i]);
                    continue;
                }else if(strcmp(filenames[i],".")==0){
                    free(filenames[i]);
                    continue;
                }else if(S_ISDIR(buf.st_mode)){
                    if(ls_R(filenames[i],flag)!=-1){
                        chdir("../");
                    }
                    free(filenames[i]);
                }else if(!S_ISDIR(buf.st_mode)){
                    continue;
                    free(filenames[i]);
                }

              }
          }
        free(filenames);
        closedir(dir);
        return 1;
      }
            
            

        
void dir_print(int flag,char*path)
{
    DIR *dir;
    struct dirent * ptr;
    int cnt=0;  //计算文件个数
   // char filename[256][PATH_MAX+1];
    long filetime[256];
    char tmpfilename[PATH_MAX+1];
    struct stat buf;
    dir=opendir(path);
    if(dir==NULL)
    {
        my_err("opendir",__LINE__);
    }
    while((ptr=readdir(dir))!=NULL)//?
     {
         int k=0;
         int q=0;
         for(int i=0;i<strlen(ptr->d_name);i++)
          {    
              if(ptr->d_name[i]<0)
              k++;
              else
              q++;
          }
        int len=k*2+q;
        if(g_maxlen<len)
        g_maxlen=len;
 
        cnt++;
     }
     closedir(dir);
 
     //if(cnt>256)  //过多文件
      //printf("%d :too many files under this dir",__LINE__);
      char **filename=(char**)malloc(sizeof(char *)*(cnt+1));
     for(int i=0;i<cnt+1;i++)
      filename[i]=(char*)malloc(sizeof(char)*100);
      dir=opendir(path);
     for(int i=0;i<cnt;i++)
     {
         if((ptr=readdir(dir))==NULL)
          {
              my_err("readdir",__LINE__);
          }
 
         strncpy(filename[i],path,strlen(path));//将path里的字符串以path开始的前strlen（path）个字节复制到filename的数组里，并返回filename
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
             // qsort(filename,cnt,sizeof(filename[0]),cmp);//快排函数，第一个参数是地址（参与排序的首地址），第二个是需要排序的数量，第三个是每一个元素占用的空间，cmp为函数          
            for(int i=0;i<cnt;i++)
               {
                 for(int j=i+1;j<cnt;j++)
                  {
                    if(strcmp(filename[i],filename[j])>0)
                     {
                       char tmp[1024];
                        strcpy(tmp,filename[i]);
                        strcpy(filename[i],filename[j]);
                        strcpy(filename[j],tmp);
                     }
                  }
               }     
         }
         
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
 
           if(flag&PARAM_L||flag&PARAM_S)
            {
               printf("总用量 %d\n",total);
            }
 
 
            if(flag&PARAM_r)//判断有无-r参数，利用位运算
              { //   flag-=PARAM_r;
                  if(flag&PARAM_R)  
                    {       flag-=PARAM_R;
                            ls_R(path,flag);
                    }
                    else
                     {   flag-=PARAM_r; 
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
	    for(int i=0;i<cnt+1;i++)
    {
      free(filename[i]);
    }
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
if(flag&PARAM_r)//作用同上
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
            printf("%-15ld",statres.st_ino);
            ls_l(statres,name,color);
	}
        break;
    case PARAM_L+PARAM_A+PARAM_I://-lai
         printf("%-15ld",statres.st_ino);
	 ls_l(statres,name,color);
         break;
    case PARAM_I://-i
         if(name[0]!='.')
            ls_i(name,color);
         break;
    case PARAM_S://-s
	if(name[0]!='.')
	       printf("%7ld",statres.st_blocks/2);
           ls_no_l(name,color);
        break;
    case PARAM_I+PARAM_S://-si
	if(name[0]='.'){
		printf("%-15ld",statres.st_ino);
		printf("%7ld",statres.st_blocks/2);
        ls_no_l(name,color);
	}
	break;
     case PARAM_L+PARAM_S://-sl
	if(name[0]='.'){
		printf("%-15ld",statres.st_ino);
		ls_l(statres,name,color);
	}
	break;

     case PARAM_L+PARAM_S+PARAM_A://-asl
	printf("%-7ld",statres.st_blocks/2);
	ls_l(statres,name,color);
	break;
     case PARAM_I+PARAM_S+PARAM_L://-isl
	if(name[0]='.'){
		printf("%-15ld",statres.st_ino);
		printf("%-7ld",statres.st_blocks/2);
		ls_l(statres,name,color);
	}
	break;
     case PARAM_A+PARAM_S:
        printf("%7ld",statres.st_blocks/2);
        ls_no_l(name,color);
	break;
     case PARAM_I+PARAM_S+PARAM_A:
        printf("%-15ld",statres.st_ino);
        printf("%7ld",statres.st_blocks/2);
        ls_no_l(name,color);
	break;
     case PARAM_I+PARAM_A+PARAM_L+PARAM_S:
        printf("%-15ld",statres.st_ino);
        printf("%-7ld",statres.st_blocks/2);
        ls_l(statres,name,color);
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
        }else if(param[i]=='s'){
		flag_param|=PARAM_S;
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
            //得到具体路径，修改为绝对路径
            strcpy(path, argv[i]);
            // if(stat(path,&statres) == -1)
            //     my_err("stat",__LINE__);
            if(stat(argv[i],&statres)==-1)
                    {   if(errno==13)
                       {
 
                        printf("Perssion denied\n");
                        errno=0;
                       }
                        else 
                        my_err("lstat",__LINE__);
                    }
            //判断是否为目录文件 
            if(S_ISDIR(statres.st_mode)){
                //如果目录最后忘记了/则加上
                if(path[strlen(argv[i]) - 1] != '/') {
                    path[strlen(argv[i])]  = '/';
                    path[strlen(argv[i])+1] = '\0';
                }else 
                    path[strlen(argv[i])] = '\0';
		printf("%s\n",path);
                if(chdir(path)==-1)   //更换到dath目录下
                {
                my_err("chdir",__LINE__);
                }
                dir_print(flag_param,path);//按照目录输出
                i++;
            }else{
                //按照文件输出
                print(flag_param,path);
                i++;
            }
            printf("\n");
        }
    }while(i < argc);

    return 0;
}


