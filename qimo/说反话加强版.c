#include <stdio.h>

int main()
{
    char str[500001] = { '0' };  //初始化
    int size = -1; //数组大小
    int s = 0; //一组字符串（单词）长度
    int i = 0;
    int j = 0;
    do
    {
        size++;
        scanf("%c", &str[size]);
    } while (str[size] != '\n'); //输入

    // 按空格分割字符串 并打印输出

    for (i = size - 1; i >= 0; i--) //从数组末尾开始
    {
        if (str[i] == ' ' && s != 0)
        {
            for (j = i + 1; j <= i + s; j++)//输出一组字符串
                printf("%c", str[j]);

            s = 0;

            while (i >= 0 && str[i] == ' ')//跳过连续空格
                i--;

            if (i > 0 && str[i] != ' ')//当前位置前面还有非空格字符
                printf(" ");
        }

        if (str[i] != ' ')//统计单词长度
            s++;


        if (i == 0)
        {
            for (j = 0; j < s; j++)
                printf("%c", str[j]);
        }
    }
    return 0;
}
//说反话加强版