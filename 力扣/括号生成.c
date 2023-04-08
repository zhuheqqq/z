//利用回溯算法,与深度优先遍历很像
#define MAXSIZE 1430

char **generateParenthesis(int n,int *returnSize){
    char *str=(char *)calloc((2*n+1),sizeof(char));
    char **result=(char **)malloc(sizeof(char *)*MAXSIZE);

    *returnSize=0;

    generate(0,0,n,str,0,result,returnSize);

    return result;
}

void generate(int left,int right,int n,char *str,int index,char **result,int *returnSize){
    if(left==n&&right==n){
        result[(*returnSize)]=(char *)calloc((2*n+1),sizeof(char));
        strcpy(result[(*returnSize)++],str);

        return;
    }

    if(left<n){
        str[index]='(';
        generate(left+1,right,n,str,index+1,result,returnSize);
    }

    if(right<n&&left>right){
        str[index]=')';
        generate(left,right+1,n,str,index+1,result,returnSize);
    }
}