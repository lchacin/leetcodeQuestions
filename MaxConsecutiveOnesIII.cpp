/*

1004. Max Consecutive Ones III


Given a binary array nums and an integer k, return the maximum number of consecutive 1's in the array 
if you can flip at most k 0's.



Code
Testcase
Testcase
Test Result
1004. Max Consecutive Ones III
Solved
Medium
Topics
Companies
Hint
Given a binary array nums and an integer k, return the maximum number of consecutive 1's in the array if you can flip at most k 0's.

 

Example 1:

Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
Output: 6
Explanation: [1,1,1,0,0,1,1,1,1,1,1]
Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.
Example 2:

Input: nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3
Output: 10
Explanation: [0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.
 

Constraints:

1 <= nums.length <= 105
nums[i] is either 0 or 1.
0 <= k <= nums.length


Approach:

The question description mentions the use of a binary search and a prefix sum together with a sliding window.
Instead, we'll use a form of sliding window implemented using a queue.

The queue will store the indexes where the 0s are located in the array. We traverse the nums array, store the
indexes where the 0s are located, once k zero indexes are stored we search search for an additional one to
determine what is the last index we should count in our current subsequence of consecutive 1s.

Once the k+1 zero, or the end of the array, is located, the number of consective 1s will be the index stored 
in the back of the queue minus the start index which had been previously saved in start variable. We pop the 
front of the queue which stores the index of the first (out of the k) zero, and let the new start index be that index
plus one. If the k+1 zero was not found because we reached the end of the nums array, then we merely subtract
the index following the end of the array minus start.

*/



#include<iostream>
#include<vector>
#include<queue>

int longestOnes(std::vector<int>& nums, int& k){
	//this is the case where k is as large as the nums array and hence the possible number of 
	//consecutive 1s is the size of the array
        if(k==nums.size()) return k;

        //this is the case where we are not allowed to switch any of the 0s and we merely look
        //for the longest sequence of consecutive 1s
        if(k==0){
        //we create max1s and tempMax to store the maximum number of consectuve 1s and temporary maximum number
        //of consectuive 1s respectively as we traverse the nums array
            int max1s=0, tempMax=0;
            for(auto& x: nums){
                if(x) tempMax+=1; //we encounter 1 so we update our tempMax

               //the case where we encounter a zero
                else{
                    if(tempMax){ //if tempMax was carrying a positive sum, this means we arrived at the end
                    		//of the current sequence of consecutive 1s
                        max1s = std::max(max1s, tempMax); //we update max1s with tempMax if tempMax was longer
                        				//sequence of consecutive 1s than the current max1s
                        tempMax=0; //restart tempMax to  0 so it can store a new length of consectuive 1s
                    }
                }
            }
            return std::max(max1s, tempMax); //we do one final update, since tempMax could have ended with the last
            				//element in the array, in which case max1 wouldn't have been updated
        }
        


        //this is the general case of the question
        int max1s=0;
        int runner = 0; //runner store the indexes as we traverese the nums array
        int start = 0; //start will store the starting index of the current sequence of consecutive 1s being considered
        std::queue<int> zeroQ; //zeroQ will store the indexes of the location of the 0 elements

        //we iterate over the nums array until the end
        while(runner != nums.size()){
        	//we start a nested while loop to store the indexes of the first k+1 zeros
        	//we exit the while loop when the zeroQ is of size k+1 or if runner reaches the end of the array
                while(zeroQ.size() < k+1 && runner != nums.size()){
                        if(nums[runner] == 0) zeroQ.push(runner); // if we encounter a zero we store its index
                        ++runner; //move runner to the next index
                }
                //out of the nested while loop we check if exited because k+1 zeros were stored
                if(zeroQ.size() > k){
                	//if so we update max1s. the back of zeroQ stores the index of the k+1 zero and start is the
                	//index of the first of the k zeros, so the difference gives us the length of the consecutive 1s
                    max1s = std::max(max1s, zeroQ.back() - start); //if longer than the current max1s, max1 is updated
                    start = zeroQ.front()+1; //start is now the index after the first zero
                    zeroQ.pop(); //we remove the first zero so we can go ahead and look for the next k+1 zero
                }
                
                else if(zeroQ.size()==0) return nums.size(); //this is the case where no 0s were encountered
                                                        //i.e. all the values traversed were 1s
        }

	//out of the while loop runner we check for the last sequence of k consecutive ones that ended
	//with the end of the nums array and not because a k+1 zero was encountered
        zeroQ.push(runner); 
        max1s = std::max(max1s, zeroQ.back() - start); 
        						


        return max1s;
    }



int main(){
	std::vector<int> nums{1,1,1,0,0,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1};
	int k=3;
	
	std::cout<<longestOnes(nums,k)<<"\n";

	return 0;
}
