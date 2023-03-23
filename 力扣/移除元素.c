int removeElement(int* nums, int numsSize, int val){
    //将等于val的数全部置为-1，然后排序输出
    int cnt=numsSize;
    int i,j,t;
    for(i=0;i<numsSize;i++){
        if(nums[i]==val){
            nums[i]=-1;
            cnt--;
        }
    }
    for(i=0;i<numsSize-1;i++){
        for(j=0;j<numsSize-i-1;j++){
            if(nums[j]<nums[j+1]){
                t=nums[j];
                nums[j]=nums[j+1];
                nums[j+1]=t;
            }

        }
    }

    return cnt;


}