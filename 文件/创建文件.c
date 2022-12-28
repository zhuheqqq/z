#include<stdio.h>
#include<stdlib.h>
int main(void)
{
    FILE *fp;
    char ch=6;
    fp=fopen("zhuheqin.txt","a");
    // if(fp==NULL){
    //     printf("文件打开失败！");
    //     exit(0);//立即退出当前程序，返回操作系统
    // }


    // ch=getc(fp);
    // if(ch!=EOF)
    // {
    //     putchar(ch);
    // }从文件中获取字符

     putc(ch,fp);//放字符进入文件
    fclose(fp);
    return 0;
}
//保存在当前文件夹（左上角文件点开 另存为  就可以看到他的路径）
//可以自己指定文件路径 如：d:\f01\a02.txt
//表示d盘f01文件夹的文件a02.txt，其中d:\f01\就是文件路径
//fopen("d:\f01\a02.txt","w");错误，单个\被看成转义字符
//fopen("d:\\f01\\a02.txt","w")or fopen("d:/f01/a02.txt","w");  unix系统

