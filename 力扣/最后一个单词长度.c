int lengthOfLastWord(char * s){
    int i=0,cnt=0,flag=1;
    int len=strlen(s);
    char arr[len+1];
    char *p=s+len-1;

    for(i=0;p>=s;p--,i++){
        arr[i]=*p;
    }
    arr[i]='\0';

    for(i=0;i<len;i++){
        if(arr[i]!=' '){
            cnt++;
            flag=0;
        }else if(arr[i]==' '&&flag==0){
            break;

        }
    }
    return cnt;



}