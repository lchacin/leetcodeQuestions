/*

53. Maximum Subarray

Given an integer array nums, find the subarray with the largest sum, and return its sum.


Constraints:
- 1 <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4


Approach:

We use dynamic programming.

Our subproblem is the defined as

f(i) = nums.back() if i=nums.length()-1
f(i) = nums[i] if f(i+1) < 0, otherwise f(i) =  f(i+1) + nums[i]

The reasoning behind working backwards is that when trying to determine a solution moving forward,
you come to the realization that when deciding whether to extend the current subarray to include 
the following value in our current sum, if the value is negative we need to know that the max subrray
starting from the following value has a net positive sum.

Therefore it'd be better to work backwards, so that when we reach the current value, we would already know
the max sum of the subarray starting from the following value.


*/

#include<iostream>
#include<vector>




int maxSubArray(std::vector<int>& nums) {
        //the case the nums array has only one element
        if(nums.size()==1) return nums[0];

        //maxVal will contain the largest sum of a subarray currently calculated
        //lastVal will have the last sum of a subarray calculate
        int maxVal=nums.back(), lastVal=nums.back(); 

        //revIter is a reverse iterator that start from the penultimate value
        //of the nums array. We'll use it to iterate over values in nums
        auto revIter = nums.rbegin()+1;      

        //the while iterates backwards until reviter reaches the start of the nums array
        //with each iteration it calculates the max sum of a subarray starting from
        //the current nums value.
        while(revIter!=nums.rend()){
            //the case where the max sum of the subarray starting from the value
            //in front of the current one is negative.
            //In this case the max sum of the subarray starting from the current
            //value would be the current value since extanding it with the
            //the max sum subarray starting with the following value would
            //lead to a lower sum, since it is negative.
            if(lastVal<0) lastVal= *revIter; 
            //since the max sum of the subarray starting from the following value
            //is positive, we would like to append our current value to it
            //so the current value's max sum subarray is increased.
            else lastVal += *revIter; 

            //if the max sum of the subarray starting from the current value is
            //larger than the maximum sum of all subarrays so far calculated
            //we update maxVal to store the new max sum
            if(lastVal>maxVal) maxVal=lastVal;

            //move the iterator backward
            ++revIter;
        }
        //out of the while loop maxVal has the maximum subarray sum of all possible
        //subarrays
        return maxVal; 
    }



int main(){
	std::vector<int> nums{-2,1,-3,4,-1,2,1,-5,4,10,-1,-2};

	std::cout<<"Max subarray sum: "<<maxSubArray(nums)<<"\n";

	return 0;
}
