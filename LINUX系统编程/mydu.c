//查看内存//查看内存

#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<glob.h>

#define SIZE 1024

static int  path_noloop(const char *path)
{
	char *pos;

	pos=strrchr(path,'/');
	if(pos==NULL)
		exit(1);
	if(strcmp(pos+1,".")==0||strcmp(pos+1,"..")==0)
		return 0;
	return 1;
}

static long long  mydu(const char *path)
{
	char nextpath[SIZE];
	struct stat statres;
	glob_t globres;
	long long sum;
	int i;

	if(lstat(path,&statres)<0)
	{
		perror("lstat()");
		exit(1);
	}

	if(!S_ISDIR(statres.st_mode)){
		return statres.st_blocks;
	}

	strncpy(nextpath,path,SIZE);
	strncat(nextpath,"/*",SIZE);
        glob(nextpath,0,NULL,&globres);

	
	strncpy(nextpath,path,SIZE);
        strncat(nextpath,"/.*",SIZE);
        glob(nextpath,GLOB_APPEND,NULL,&globres);

	sum=0;
	for(i=0;i<globres.gl_pathc;i++)
	{
		if(path_noloop(globres.gl_pathv[i]))
		sum+=mydu(globres.gl_pathv[i]);
	}

	sum+=statres.st_blocks;

	return sum;

}
int main(int argc,char **argv)
{
	if(argc<2)
	{
		fprintf(stderr,"Usage...\n");
		exit(1);
	}

	mydu(argv[1]);

	printf("%lld\n",mydu(argv[1])/2);





	exit(0);
}