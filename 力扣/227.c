//栈 基本运算器

int calculate(char * s){
    int n=strlen(s);
    int stk[n],top=0;
    int num=0;
    char preSign='+';

    for(int i=0;i<n;i++)
    {
        if(isdigit(s[i]))//将数字字符转换为数字
        {
            num=num*10+(int)(s[i]-'0');
        }

        if(!isdigit(s[i])&&s[i]!=' '||i==n-1)
        {
            switch(preSign){
                case '+':
                    stk[top++]=num;
                    break;
                case '-':
                    stk[top++]=-num;
                    break;
                case '*':
                    stk[top-1]=stk[top-1]*num;
                    break;
                case '/':
                    stk[top-1]=stk[top-1]/num;
                    break;
            }
            preSign=s[i];
            num=0;
        }
    }

    int ret = 0;
    for (int i = 0; i < top; i++) {
        ret += stk[i];
    }
    return ret;

}