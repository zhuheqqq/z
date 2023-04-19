//删除有序数组中的重复项
int removeDuplicates(int* nums, int numsSize){
    int i,j;
    int size=numsSize;
    int *nums1=nums;
    for(i=0,j=1;i<size-1;i++){
        if(nums1[i+1]<=nums1[i]){
            numsSize--;
        }else{
            nums[j]=nums1[i+1];
            j++;
        }
    }

    return numsSize;

}