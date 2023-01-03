#define OK 1
#define ERROR 0
#define MAXSIZE 20
typedef int ElemType;
typedef struct
{
    ElemType data[MAXSIZE];
    int length;
} SqList;
typedef int Status;//函数类型，值是函数结果状态代码

Status GetElem(SqList L, int i, ElemType *e)//e返回L中第i个元素的值
{
    if (L.length == 0 || i < 1 || i > L.length)
    {
        return ERROR;
    }
    *e = L.data[i - 1];
    return OK;
}