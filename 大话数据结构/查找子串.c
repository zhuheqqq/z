#include "string.h"
#include "stdio.h"    
#include "stdlib.h"
#include<stdbool.h>   

#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 40
typedef int Status;		/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType;	/* ElemType类型根据实际情况而定，这里假设为int */

typedef char String[MAXSIZE+1]; /*  0号单元存放串的长度 */
//生成一个其值等于chars的串
bool StrAssign(String T,char *chars){
    if(strlen(chars)>MAXSIZE){
        return false;
    }
    T[0]=strlen(chars);
    int i;
    for(i=1;i<T[0];i++){
        T[i]=*(chars+i-1);
    }
    return true;
}
//复制串
char StrCopy(String T,String S){
    if(strlen(S)<MAXSIZE){
        int i;
        for(i=0;i<strlen(S);i++){
            T[i]=S[i];
        }
        T[i]='\0';
        return T;
    }
}
//清空串
bool ClearString(String S){
    int i;
    for(i=0;i<strlen(S);i++){
        S[i]='\0';
    }
    return true;
}
//判断是否为空串
bool StringEmpty(String S ){
    if(S[0]==0){//首元素为元素个数
        return true;
    }
    return false;
}
//返回串的长度
int StrLength(String S){
    return strlen(S);
}
//若S>T,返回值>0...
int StrCompare(String S,String T){
    int i;
    for(i=1;i<=S[0]&&i<=T[0];i++){
        if(S[i]>T[i]){
            return S[i]-T[i];
        }else if(S[i]<T[i]){
            return S[i]-T[i];
        }
    }
    return 0;
}
//T为S1和S2连接的新串
char Concat(String T,String S1,String S2){
    if(MAXSIZE>strlen(S1)+strlen(S2)){
        int i,j,k;
        T[0]=strlen(S1)+strlen(S2);
        for(i=0;i<=strlen(S1);i++){
            T[i]=S1[i];
        }
        for(j=i,k=0;j<T[0];j++){
            T[j]=*(S2+1+k);
        }
        T[j]='\0';
        return T;
    }
}
//