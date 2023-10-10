class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int k=nums.size();
        int right=0,left=0;
        while(right<=k-1)
        {
            if(nums[right]==0)
            {
                right++;
            }else if(nums[right]!=0)
            {
                nums[left]=nums[right];
                right++;
                left++;
            }
        }

        for(int i=left;i<right;i++)
        {
            nums[i]=0;
        }

        

    }
};