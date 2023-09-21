#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>

//定义运算符栈
char operatorStack[100];
int operatorTop=-1;

//定义操作数栈
char operandStack[100];
int operandTop=-1;

// 函数声明
void pushOperator(char c);//操作符入栈
char popOperator();//操作符出栈
void pushOperand(double value);//操作数入栈
double popOperand();//操作数出栈
int getOperatorPriority(char c);//获取运算符优先级
bool isOperator(char c);//判断是否是操作符
double performOperation(char operator, double operand1, double operand2);//根据操作符执行相应的运算

int main()
{
    char input[100];
    printf("请输入表达式(以#结束）：");
    scanf("%s",input);

    int length=strlen(input);
    input[length]='#';

    int i=0;
    while(i<=length)
    {
        if(input[i]==' ')
        {
            i++;
            continue;//忽略空格
        }

        if(isdigit(input[i]))//如果为操作数
        {
            char num[100];
            int j=0;

            while(isdigit(input[i])||input[i]=='.')//输入可能为小数的情况
            {
                num[j++]=input[i++];
            }
            num[j]='\0';
            double operand=atof(num);//将浮点数字符串转化为对应的浮点数
            pushOperand(operand);
            //操作数入栈
        }else if(isOperator(input[i]))
        {
            while(operatorTop!=-1&&getOperatorPriority(operatorStack[operatorTop])>=getOperatorPriority(input[i])){
                char op=popOperator();
                double operand2=popOperand();
                double operand1=popOperand();
                double result=performOperation(op,operand1,operand2);
                pushOperand(result);
            }

            pushOperator(input[i]);
            i++;

        }else if(input[i]=='#'){
            while (operatorTop != -1) {
                char op = popOperator();
                double operand2 = popOperand();
                double operand1 = popOperand();
                double result = performOperation(op, operand1, operand2);
                pushOperand(result);
            }
            break;
        }else{
            printf("无效字符：%c\n",input[i]);
            return 1;
        }
    }

    double finalResult = popOperand();
    if (operandTop == -1) {
        printf("表达式的结果：%lf\n", finalResult);
    } else {
        printf("表达式无效\n");
    }

    return 0;
}

void pushOperator(char c)
{
    operatorStack[++operatorTop]=c;
}

char popOperator()
{
    if(operatorTop==-1)
    {
        return '\0';//栈为空
    }else{
        return operatorStack[operatorTop--];
    }
}

void pushOperand(double value)
{
    operandStack[++operandTop]=value;
}

double popOperand()
{
    if(operandTop==-1)
    {
        return 0.0;//栈为空
    }else {
        return operandStack[operandTop--];
    }
}

int getOperatorPriority(char c)
{
    if(c=='+'||c=='-')
    {
        return 1;
    }else if(c=='*'||c=='/')
    {
        return 2;
    }else if(c=='<'||c=='>'||c=='='||c=='!'){
        return 3;// 关系运算符的优先级
    }else if(c=='&'||c=='|'){
        return 4;// 逻辑运算符的优先级
    }else{
        return 0;
    }
}

bool isOperator(char c)
{
    return (c=='+'||c=='-'||c=='*'||c=='/'||c=='>'||c=='<'||c=='='||c=='!'||c=='&'||c=='|');
}

double performOperation(char operator,double operand1,double operand2)
{
    switch(operator){
        case '+':
            return operand1+operand2;
        case '-':
            return operand1-operand2;
        case '*':
            return operand1*operand2;
        case '/':
            if(operand2!=0){
                return operand1/operand2;
            }else{
                printf("除数不能为0");
                exit(1);
            }
        case '<':
            return operand1 < operand2 ? 1.0 : 0.0;
        case '>':
            return operand1 > operand2 ? 1.0 : 0.0;
        case '=':
            return operand1 == operand2 ? 1.0 : 0.0;
        case '!':
            return operand1 != operand2 ? 1.0 : 0.0;
        case '&':
            return operand1 && operand2 ? 1.0 : 0.0;
        case '|':
            return operand1 || operand2 ? 1.0 : 0.0;
        default:
            printf("无效的运算符：%c\n",operator);
            exit(1);
    }
}

