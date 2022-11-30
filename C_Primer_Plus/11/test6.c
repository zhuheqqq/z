int is_within(char ch,char *p)
{
    int len,i;
    len=strlen(ch);
    for(i=0;i<n;i++){
        if(*(p+i)==s){
            return 1;
        }
    }
    return 0;

}