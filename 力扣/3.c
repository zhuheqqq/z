//无重复字符串的最长子串
int lengthOfLongestSubstring(char * s){
    int i=0,j=0,max=0;
    int left=0,right=0;
    int flag=0,len=strlen(s);
    for(i=0;i<len;i++){
        if(left<right){
            flag=0;
            for(j=left;j<right;j++){
                if(s[j]==s[right]){
                    flag=1;
                    break;
                }
            }
            if(flag==1){
                left=j+1;
            }
        }
        max=(right-left+1)>max?(right-left+1):max;
        right++;
    }
    return max;

}