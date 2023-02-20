#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<glob.h>

#define PAT "/etc/a*.conf"

#if 0
int errfunc(const char *errpath,int eerrno)
{
	puts(errpath);
	fprintf(stderr,"ERROR MSG:%s\n",sterror(eerror));
}
#endif
int main(int argc,char *argv[])
{
	glob_t globres;
	int i,err;

	err=glob(PAT,0,NULL,&globres);
	if(err)
	{
		printf("Error code=%d\n",err);
		exit(1);
	}

	for(i=0;i<globres.gl_pathc;i++)
	{
		puts(globres.gl_pathv[i]);
	}

	globfree(&globres);

	exit(0);
}