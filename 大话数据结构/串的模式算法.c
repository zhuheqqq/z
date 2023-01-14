#define MAXSIZE 100
typedef char String[MAXSIZE+1];
int index(String S,String T,int pos){
    int i=pos;
    int j=1;
    while(i<=S[0]&&j<=T[0]){
        if(S[i]==T[i]){
            ++i;
            ++j;
        }else{
            i=i-j+2;
            j=1;
        }
    }
    if(j>T[0]){
        return i-T[0];
    }else{
        return 0;
    }

}