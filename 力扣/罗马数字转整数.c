int romanToInt(char * s){
    int num=0;
    int len=strlen(s);
    int i;

    for(i=0;i<len-1;i++){
        if(s[i]=='I'&&s[i+1]=='V')
        {
            num+=4;
            s[i]=s[i+1]='A';
        }else if(s[i]=='I'&&s[i+1]=='X'){
            num+=9;
            s[i]=s[i+1]='A';
        }else if(s[i]=='X'&&s[i+1]=='L'){
            num+=40;
            s[i]=s[i+1]='A';
        }else if(s[i]=='X'&&s[i+1]=='C'){
            num+=90;
            s[i]=s[i+1]='A';
        }else if(s[i]=='C'&&s[i+1]=='D'){
            num+=400;
            s[i]=s[i+1]='A';
        }else if(s[i]=='C'&&s[i+1]=='M'){
            num+=900;
            s[i]=s[i+1]='A';
        }
    }

    for(i=0;i<len;i++){
        switch(s[i]){
            case 'A':
            num+=0;
            break;

            case 'I':
            num+=1;
            break;

            case 'V':
            num+=5;
            break;

            case 'X':
            num+=10;
            break;

            case 'L':
            num+=50;
            break;

            case 'C':
            num+=100;
            break;

            case 'D':
            num+=500;
            break;

            case 'M':
            num+=1000;
            break;
        }
    }

    return num;

}