#include<iostream>

#define MAX 100

using namespace std;

typedef struct{
    int row,col;//三元组的行号、列号
    int item;//三元组的值
}Triple;

class TripleMatrix{
public:
    Triple data[MAX];//非零元三元组
    int mu,nu,num;//矩阵的行数、列数和非零元的个数
public:
    TripleMatrix(int m,int n);
    ~TripleMatrix();

    int setItem(int row,int col,int item);//根据行号列号非零元，再添加一个三元组项
    int getItem(int row,int col);//根据行号列号，获得矩阵元素值
    void printMatrix();//按矩阵方式打印稀疏矩阵
    void printTriple();//打印三元组数组
};