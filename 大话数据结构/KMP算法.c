//计算next数组
//String[0]均表示String的长度
#define MAXSIZE 100
typedef char String[MAXSIZE+1];
void get_next(String T,int *next){
    int i=1,k=0;
    next[1]=1;
    while(i<T[0]){
        if(k==0||T[i]==T[k]){
            ++i;
            ++k;
            next[i]=k;
        }else{
            k=next[k];
        }
    }
}
//
int Index_KMP(String S,String T,int pos)
{
    int i=pos,j=1;
    int next[255];
    get_next(T,next);
    while(i<=S[0]&&j<=T[0])
    {
        if(j==0||S[i]==T[j])
        {
            ++i;
            ++j;
        }
        else{
        j=next[j];//指针退回到特殊位置，i不变
        }
    }
    if(j>T[0]){
        return i-T[0];
    }else{
        return 0;
    }

}