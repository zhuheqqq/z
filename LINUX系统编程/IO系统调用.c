//实现 cp命令
// ./copy oldfile newfile

//size_t用来表示一种计数，比如有多少东西被拷贝，“适于计量内存中可容纳的数据项目个树的无符号整数类型
//ssize_t表示可以被执行读写操作的数据块的大小，与size_t类似，但必须是signed

#include<sys/stat.h>
#include<fcntl.h>
#include"tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc,char *argv[])
{
    int inputFd,outputFd,openFlags;
    mode_t filePerms;//无符号八进制数
    ssize_t numRead;
    char buf[BUF_SIZE];

    if(argc!=3||strcmp(argv[1],"--help")==0){
        usageErr("%s old-file new-file\n",argv[0]);

        //open input and output files

        inputFd=open(argv[1],O_RDONLY);
        if(inputFd==-1){
            reeExit("opening file %s",argv[1]);

            openFlags=O_CREAT|O_WRONLY|O_TRUNC;
            filePerms=S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH;
            outputFd=open(argv[2],openFlags,filePerms);
            if(outputFd==-1){
                errExit("opening file %s",argv[2]);

                //transfer data until we encounter end of input or an error

                while((numRead=read(inputFd,buf,BUF_SIZE))>0){
                    if(write(outputFd,buf,numRead)!=numRead){
                        fatal("couldn't write whole buffer");
                    }
                    if(numRead==-1){
                        errExit("read");
                    }
                    if(close(inputFd)==-1){
                        errExit("read");
                    }
                    if(close(outputFd)==-1){
                        errExit("close output");
                    }

                    exit(EXIT_SUCCESS);
                }
            }
        }
    }

}