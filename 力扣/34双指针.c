//给你一个按照非递减顺序排列的整数数组 nums，和一个目标值 target。请你找出给定目标值在数组中的开始位置和结束位置。

//如果数组中不存在目标值 target，返回 [-1, -1]。

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* searchRange(int* nums, int numsSize, int target, int* returnSize){
    int *array=(int *)malloc(sizeof(int)*2);
    *returnSize=2;
    int i=0;
    for(i=0;i<2;i++){
        array[i]=-1;
    }
    int *left=nums;
    int *right=nums+numsSize-1;
    for(;left<=right;){
        if(*left==target){
            array[0]=(left-nums);
        }else{
            left++;
        }
        if(*right==target){
            array[1]=(right-nums);
        }else{
            right--;
        }
        if (array[0] != -1 && array[1] != -1) {
             break;
         }
    }

    return array;

}