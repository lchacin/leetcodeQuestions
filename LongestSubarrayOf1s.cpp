/*

1493.Longest Subarray of 1's After Deleting One Element

Given a binary array nums, you should delete one element from it.
Return the size of the longest non-empty subarray containing only 1's in the resulting array. 
Return 0 if there is no such subarray.

Constraints:

1 <= nums.length <= 105
nums[i] is either 0 or 1.


Approach:

We iterate over the array checking whether a value is 1 or 0.
We carry a previous sum storing the sum of the 1s in the last consecutive sequence of 1s,
a current sum carrying the sum of the 1s in the current consecutive sequence of 1s, and a max sum
storing the current maximum of consecutive sequence of 1s after removing one element.

As we traverse the array we update the current sum for each 1 encountered. When we encounter a 0, 
we update max sum if the current sum and the previous sum added up to a higher value than max sum.
We let the previous sum be the current sum and restart the current sum with 0.

*/


#include<iostream>
#include<vector>
#include<cstdlib> //for uint_fast32_t


//longestSubarray returns the length of the maximum number of consecutive 1s of a subarray after removing
//only one element of nums. It receives nums as a reference to a vector of binary intergers
int longestSubarray(std::vector<int>& nums) {
	//previousSum stores the sum of 1s of the last subarray of consecutive 1s
	//currentSum stores the sum of the 1s of the current subarray of consecutive 1s
	//maxSum stores the maximum length of a subarray of consecutive 1s after removing an element
        uint_fast32_t previousSum=0, currentSum=0, maxSum=0;
        uint_fast32_t runner=0; //runner will be the current index
        uint_fast32_t size=nums.size();

        //while loop runs until runner is at the past-the-end index
        while(runner!=size){
        	//the case where a zero is encountered
            if(nums[runner]==0){
            	//we update maxSum if currentSum plus previousSum is higher than the current maxSum
                maxSum = std::max(maxSum, currentSum+previousSum);
                previousSum = currentSum; //let previousSum be the currentSum
                currentSum = 0; //restart the currentSum
                ++runner; //advance the index
            }
            else{ //the case where current value is 1
                currentSum+=1; //increase currentSum
                ++runner;
            }

        }

        //if the currentSum is the same as the size of the nums vector, then this means
        //no zeros were encountered. In such a case we need to remove one of the 1s in currentSum and
        //return its value
        if(currentSum==size) return currentSum-1;

        //the case where a zero was entountered. We do one last update of maxSum since the while loop
        //ends without doing one last update
        return std::max(maxSum, currentSum+previousSum);
    }


int main(){
	std::vector<int> nums{0,1,1,1,0,1,1,0,1};
	std::cout<<longestSubarray(nums)<<"\n";

	return 0;
}
