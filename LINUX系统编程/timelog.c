#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define FNAME "/tmp/bigfile"
#define BUFSIZE 1024

int main(int argc,char **argv)
{
	FILE *fp;
	char buf[BUFSIZE];
	int count=0;
	time_t stamp;
	struct tm *tm;

	fp=fopen(FNAME,"a+");
	if(fp==NULL)
	{
		perror("fopen");
		exit(1);
	}

	while(fgets(buf,BUFSIZE,fp)!=NULL)
		count++;

	while(1)
	{
		time(&stamp);
		tm=localtime(&stamp);
		fprintf(fp,"%-4d%d-%d-%d %d:%d:%d\n",++count,\
				tm->tm_year, tm->tm_mon, tm->tm_mday,\
				 tm->tm_hour, tm->tm_min, tm->tm_sec);

		sleep(1);
	}