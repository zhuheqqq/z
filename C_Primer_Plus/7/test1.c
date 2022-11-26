//winter with u
#include<stdio.h>
#include<string.h>
int main(void)
{
    int cnt1=0,cnt2=0,cnt3=0;
    char key;
    while((key=getchar())!='#'){
        if(key==' '){
            cnt1++;
        }else if(key=='\n'){
            cnt2++;
        }else{
            cnt3++;
        }
    }
    printf("%d %d %d\n",cnt1,cnt2,cnt3);

    return 0;
}