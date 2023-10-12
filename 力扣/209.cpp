class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int k=nums.size();
        int i=0,j=0,sum=0;
        int minlen=1000000;
        while(j<k)
        {
            sum+=nums[j];
            while(sum>=target)
            {
                minlen = min(minlen, j - i + 1);
                sum-=nums[i];
                i++;
            }
    
            j++;
        }

        return minlen==1000000?0:minlen;
    }
};