/*

1695. Maximum Erasure Value

You are given an array of positive integers nums and want to erase a subarray containing unique elements. 
The score you get by erasing the subarray is equal to the sum of its elements.

Return the maximum score you can get by erasing exactly one subarray.

An array b is called to be a subarray of a if it forms a contiguous subsequence of a, that is, 
if it is equal to a[l],a[l+1],...,a[r] for some (l,r).

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 104


*/

#include<iostream>
#include<vector>


int maximumUniqueSubarray(std::vector<int>& nums) {
        //the case nums only has one value stored
	if(nums.size() == 0) return nums[0];

        int back = 0, front = 1; //a back and front pointer to iterate over the nums array
        std::vector<bool> found(100000, false);	//to record whether a value in 1-100000 has been encountered
        int runningSum = nums[0], maxSum = 0;	//to store the sum of the current subarray and the maximum subarray sum 
        found[nums[0]] = true;

	//we iterate over nums until the front pointer reaches the end
        while(front < nums.size()){
		//the case the value at front has already been encountered in the current subarray
            if(found[nums[front]]){
		//we update maximum sum if running sum has a larger subarray value
                maxSum = std::max(runningSum, maxSum);

		//now we increment the back pointer removing the values of the current subarray
		//from running Sum and from the found array. This is to prepare running sum and the found 
		//boolean array fro the new subarray to traverse
                while(nums[front] != nums[back]){
                    found[nums[back]] = false;
                    runningSum -= nums[back];
                    ++back;
                }

		//n0w we repeat the same procedure on the duplicate value
                found[nums[back]] = false;
                runningSum -= nums[back];
                ++back;
            }
            
	//we begin generating the new subarray
            runningSum += nums[front];
            found[nums[front]] = true;
            ++front;
        }

	
        return std::max(runningSum, maxSum);
    }



int main(){
	std::vector<int> nums{1, 9, 7, 10, 7, 8, 8, 2, 2, 2, 3, 1, 5, 7, 7, 10, 10, 4, 3, 8};
	std::cout << maximumUniqueSubarray(nums) << "\n";

	return 0;
}
