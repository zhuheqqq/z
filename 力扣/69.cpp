class Solution {
public:
    int mySqrt(int x) {
        int i=0,r=x,middle=0,ans=-1;
        while(i<=r)
        {
            int middle=i+(r-i)/2;
            if((long long)middle*middle<=x)
            {
                ans=middle;
                i=middle+1;
            }else{
                r=middle-1;
            }
        }

        return ans;

    }
};