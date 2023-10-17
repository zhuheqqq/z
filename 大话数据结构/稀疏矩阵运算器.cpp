#include "稀疏矩阵运算器.h"

using namespace std;

#define ERROR 0
#define OK 1

TripleMatrix::~TripleMatrix()
{

}

TripleMatrix::TripleMatrix(int m,int n)
{
    mu=m;
    nu=n;
}

//根据行号列号获得稀疏矩阵的值
int TripleMatrix::getItem(int row,int col)
{
    if(row>mu||col>nu)//超过范围
    {
        return 0;
    }

    for(int i=0;i<num;i++)//遍历三元组
    {//发现行列号匹配的三元组
        if(data[i].row==row&&data[i].col==col){
            return data[i].item;
        }
    }

    return 0;
}

//三元组的插入需要大量移动元素
int TripleMatrix::setItem(int row,int col,int item)
{
    if(row>mu||col>nu)//超过范围
    {
        return ERROR;
    }

    if(num==MAX)//已存最大
    {
        return ERROR;
    }

    if(item==0)
    {
        return OK;
    }

    //先找到合适的位置
    int index=0;
    while(index<num)
    {//如果要找的row和col比已有的行列号大
        if(row>data[index].row){
            index++;
        }else if(row==data[index].row&&(col>data[index].col)){
            index++;
        }else{
            break;
        }
    }

    if((row==data[index].row)&&(col==data[index].col)){
       //当前行列元素已经存在，则将新输入的数据替换三元组的item值
       data[index].item=item; 
    }else{
        for(int i=num;i>index;i--)
        {
            data[i].row=data[i-1].row;
            data[i].col=data[i-1].col;
            data[i].item=data[i-1].item;
        }

        //在index位置存入新的元素
        data[index].row=row;
        data[index].col=col;
        data[index].item=item;
        //元素个数+1
        num++;
    }
    return OK;
}

//打印稀疏矩阵
void TripleMatrix::printMatrix()
{
    int tripleIndex=0;
    cout<<"打印矩阵："<<endl;

    for(int i=1;i<=mu;i++)
    {
        for(int j=1;j<=nu;j++)
        {
            if(i==data[tripleIndex].row&&j==data[tripleIndex].col){
                cout<<data[tripleIndex].item<<"\t";
                tripleIndex++;
            }else{
                cout<<"0\t";
            }
        }
        cout<<endl;
    }
    cout<<"矩阵有"<<mu<<"行"<<nu<<"列，"<<"共"<<num<<"个非零元素"<<endl;
    return;
}

//打印三元组数组
void TripleMatrix::printTriple()
{
    cout<<"打印三元组数组："<<endl;
    cout<<"row\tcol\titem"<<endl;
    for(int i=0;i<num;i++)
    {
        cout<<data[i].row<<"\t"<<data[i].col<<"\t"<<data[i].item<<endl;
    }
}

void inputMatrix(int m,int n,int num,TripleMatrix& triple)
{
    int row,col,item;
    for(int i=1;i<=num;i++)
    {
        cout<<"请依次输入行、列、非零元：";
        cin>>row>>col>>item;
        if(item!=0)
        {
            if(triple.setItem(row,col,item)==ERROR){
                cout<<"不能正确存储";
                break;
            }
        }
    }
}

bool matrixAdd(TripleMatrix a,TripleMatrix b,TripleMatrix& result)
{
    if(a.mu!=b.mu||b.mu!=result.mu||a.nu!=b.nu||b.nu!=result.nu)
    {
        return false;
    }else{
        for(int i=1;i<=a.mu;i++)
        {
            for(int j=1;j<=a.nu;j++)
            {
                int item=a.getItem(i,j)+b.getItem(i,j);
                //如果计算出来的值不为0
                if(item!=0)
                {
                    result.setItem(i,j,item);
                }
            }
        }
        return true;
    }
}

int main()
{
    int m,n,num;
    cout<<"请输入第一个矩阵的行，列，非零元的个数：";
    cin>>m>>n>>num;
    cout<<"第一个矩阵："<<endl;
    TripleMatrix tripleA(m,n);
    inputMatrix(m,n,num,tripleA);

    tripleA.printMatrix();

    cout<<"请输入第二个矩阵的行，列,非零元个数：";
    cin>>m>>n>>num;
    cout<<endl<<"第二个矩阵："<<endl;
    TripleMatrix tripleB(m,n);
    inputMatrix(m,n,num,tripleB);

    tripleB.printMatrix();

    TripleMatrix tripleResult(m,n);
    if(matrixAdd(tripleA,tripleB,tripleResult))
    {
        cout<<endl<<"矩阵相加后："<<endl;

        tripleResult.printMatrix();
    }else{
        cout<<"矩阵不能相加"<<endl;
    }

    return 0;

}

