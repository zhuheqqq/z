class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res(n,vector<int>(n,0));
        int startx=0,starty=0;//元素的起始位置
        int offset=1;//收缩圈的右边界
        int loop=n/2;//圈的循环次数
        int middle=n/2;//n为奇数的情况需要单独讨论
        int count=1;//用来给圈的空格赋值

        int i,j;

        while(loop--)
        {
            i=startx,j=starty;
            for(j=starty;j<n-offset;j++)//向右行进
            {
                res[i][j]=count;
                count++;
            }

            for(j;i<n-offset;i++)//向下行进
            {
                res[i][j]=count;
                count++;
            }

            for(i;j>starty;j--)//向左行进
            {
                res[i][j]=count;
                count++;
            }

            for(j;i>startx;i--)//向上行进
            {
                res[i][j]=count;
                count++;
            }

            startx++;
            starty++;

            offset++;

        }

        if(n%2!=0)
        {
            res[middle][middle]=count;
        }

        return res;

    }
};