class Solution {
public:
    bool backspaceCompare(string s, string t) {
            int i=s.size()-1;
            int j=t.size()-1;
            int k=0;
            int scnt=0,tcnt=0;
            int s1[201],t1[201];

            memset(s1,0,sizeof(s1));
            memset(t1,0,sizeof(t1));
            while(i>=0)
            {
                if(s[i]=='#')
                {
                    scnt++;
                }else if(scnt>0)
                {
                    scnt--;
                }else{
                    s1[k]=s[i];
                    k++;
                }
                i--;
            }

            k=0;
            while(j>=0)
            {
                if(t[j]=='#')
                {
                    tcnt++;
                }else if(tcnt>0)
                {
                    tcnt--;
                }else{
                    t1[k]=t[j];
                    k++;
                }
                j--;
            }

            int result=memcmp(s1,t1,201);
            if(result==0)
            {
                return true;
            }else{
                return false;
            }

    }
};