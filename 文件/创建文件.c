#include<stdio.h>
int main(void)
{
    fopen("zhuheqin.txt","w");
    
    return 0;
}
//保存在当前文件夹（左上角文件点开 另存为  就可以看到他的路径）
//可以自己指定文件路径 如：d:\f01\a02.txt
//表示d盘f01文件夹的文件a02.txt，其中d:\f01\就是文件路径
//fopen("d:\f01\a02.txt","w");错误，单个\被看成转义字符
//fopen("d:\\f01\\a02.txt","w")or fopen("d:/f01/a02.txt","w");  unix系统

