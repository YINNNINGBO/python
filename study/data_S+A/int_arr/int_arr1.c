#include <stdio.h>
#include <string.h>

#if 0
int majorityElement(int* nums, int numsSize) {
    int times = 0;
    int a;
    if(0 == (numsSize/2) ){
        return nums[0];
    }
    for(int i = 0; i < numsSize; i++){
        for(int j = 0;j< numsSize;j++){
            //如果相等 计数加1
            if(nums[i] == nums[j]){
                times++;
                
            } 
        }
        //判断满足条件
                if(times > (numsSize/2) ){
                   a = nums[i];
                   break;
                }
        times = 0;
       
    } 
   return a;
}
#endif

/**
 * 使用摩尔投票算法，不仅解决了原来的 O(n²) 时间复杂度问题，
 * 还大大优化了代码，减少了不必要的循环，达到了 O(n) 的时间复杂度，
 * 并且通过 O(1) 的空间优化了内存使用。
 */
int majorityElement(int *nums, int numsSize)
{
    int count = 0;
    int candidate = -1;

    // 第一遍遍历找到候选元素
    for (int i = 0; i < numsSize; i++)
    {
        if (count == 0)
        {
            candidate = nums[i];
        }
        count += (nums[i] == candidate) ? 1 : -1;
    }

    // 这里不需要第二遍扫描，因为题目中已经保证了众数的存在。
    return candidate;
}

int main()
{
    int nums[] = {3, 3, 4};
    printf("***************%d\n ", majorityElement(nums, sizeof(nums) / sizeof(nums[0])));
    return 0;
}