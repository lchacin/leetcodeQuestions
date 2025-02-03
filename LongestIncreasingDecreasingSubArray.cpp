/*

3105. Longest Strictly Increasing or Strictly Decreasing Subarray

You are given an array of integers nums. Return the length of the longest
subarray of nums which is either strictly increasing or strictly decreasing.


Constraints:

1 <= nums.length <= 50
1 <= nums[i] <= 50


*/


#include<iostream>
#include<vector>


int longestMonotonicSubarray(std::vector<int>& nums) {
        //if was only have one number we return true
        if(nums.size()==1) return true;

        //tempCount will store the length of the current
        //monotonic sequence, and maxCount will store the longest
        //monotonic sequence encountered so far
        int tempCount=1, maxCount=0;

        //increasing is a variable that tell us if we are in
        //an increasing (1), decreasing (-1) or neither (0) sequence
        int increasing = 0;

        for(int i=1; i<nums.size(); ++i){
            //the case the current number is the same as the previous one
            if(nums[i]==nums[i-1]){
                //check if the tempCount is longer than the current max
                //length so far
                maxCount = std::max(maxCount, tempCount);

                //reset increasing back to 0
                increasing = 0;

                //set tempCount back to 1
                tempCount = 1;
            }

            //the case the current number is larger than the previous one
            else if(nums[i] > nums[i-1]){
                //the case were in an increasing sequence
                //we update tempCount
                if(increasing == 1) ++tempCount;

                //the case we were not increasing or decreasing
                else if(increasing == 0){
                    ++tempCount;

                    //update increasing to 1 to indicate
                    //we entered an increasing subsequence
                    increasing = 1;
                }
                
                else{
                    maxCount = std::max(maxCount, tempCount);
                    tempCount = 2;
                    increasing = 1; 
                }
            }

            //the case the current number is smaller than the previous one
            else{
                //if we were in a decreasing sequence we update the tempCount
                if(increasing == -1) ++tempCount;

                //if we were in neither a decreasing or increasing sequence
                //we update the count and indicate that we entered a decreasing
                //sequence
                else if(increasing == 0){
                    ++tempCount;
                    increasing = -1;
                }

                //the case we were in an increasing sequence
                else{
                    //update maxCount, set the current sequence back to 2
                    //and indicate we enter a decreasing sequence
                    maxCount = std::max(maxCount, tempCount);
                    tempCount = 2;
                    increasing = -1; 
                }
            }
        }

        return std::max(maxCount, tempCount);
    }



int main(){
	std::vector<int> nums{1,9,7,1};

	std::cout << longestMonotonicSubarray(nums) << "\n";


	return 0;
}
