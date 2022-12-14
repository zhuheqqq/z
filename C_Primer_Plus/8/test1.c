#include<stdio.h>
#include<stdlib.h>
int main(void)
{
    char ch;
    FILE *fp;
    char fname[50];
    int count=0;
    scanf("%s",fname);
    fp=fopen(fname,"r");
    if(fp==NULL){
        printf("Failed to open file.\n");
        exit(1);
    }
    while((ch=getc(fp))!=EOF){
        count++;
    }
    printf("文件%s的字符数为%d\n",fname,count);
    fclose(fp);
    return 0;
}
