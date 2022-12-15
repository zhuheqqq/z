#include<stdio.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
    int ch;
    FILE *fp;
    unsigned long count=0;
    if(argc!=2)
    {
        printf("Usage: %s filename\n",argv[0]);
        exit(EXIT_FAILURE);
    }
    if((fp=fopen(argv[1],"r"))==NULL)
    {
        printf("can't open %s\n",argv[1]);
        exit(EXIT_FAILURE);
    }
    while((ch=getc(fp))!=EOF)
    {
        putc(ch,stdout);
        count++;
    }
    fclose(fp);
    printf("File %s has %lu character\n",argv[1],count);

    return 0;
}
//Usage: /home/zhuheqin/clone/z/C_Primer_Plus/13/使用标准IO函数 filename