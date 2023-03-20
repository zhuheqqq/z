//利用栈的思想，很巧妙
bool isValid(char * s){
    int i,top=0;
    char t;
    char a[10000]=" ";
    while(s[i]!='\0'){
        if(s[i]=='('||s[i]=='{'||s[i]=='['){
            if(s[i]=='('){
                t=')';
            }
            if(s[i]=='{'){
                t='}';
            }
            if(s[i]=='['){
                t=']';
            }
            a[++top]=t;
        }else{
            if(s[i]!=a[top]){
                return false;
            }else{
                top--;
            }
        }
        i++;
    }
    if(top==0){
        return true;
    }
    return false;

}