/*

1679. Max Number of K-Sum Pairs

You are given an integer array nums and an integer k.

In one operation, you can pick two numbers from the array whose sum equals k and 
remove them from the array.

Return the maximum number of operations you can perform on the array.


Constraints:

1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
1 <= k <= 10^9


Approach:

We first sort the array in ascending order.

We use an index runner that runs forward from the front, called leftRunner, and another moving backwards
from the end, called rightRunner.

We record the value stored at leftRunner and calculate the value we need to search as k-nums[leftRunner].
We search for this value from the back. If the value ar rightRunner is greater than the value we are searching
for, we move rightRunner to the left. If the value at rightRunner is less than the value we are searching
for, it means the value we are searching for is not present in the nums array. Lastly, if the value we are
searching for is located at rightRunner, we increase the total of k-sum pairs.

We finish this process when leftRunner surpasses rightRunner.

Since we traverse the entire array once, this would occur in O(n)

But since we sorted the array, the overall time complexity is O(nlog(n))


*/


#include<iostream>
#include<vector>
#include<algorithm> //for std::sort

int maxOperations(std::vector<int>& nums, int& k) {
        if(nums.size()==1) return 0;

	//we sort the nums array in ascending order
        std::sort(nums.begin(), nums.end());

        //leftRunner will store an index value that starts from the left
        //rightRunner will store an index value that starts from the back of the nums array
        //target will store the corresponding second pair value of nums[leftRunner]
        //total will store the total number of k-sum pairs
        int leftRunner=0, rightRunner=nums.size()-1, target, total=0;


	//we stop the pricess when leftRunner surpasses rightRunner
        while(leftRunner<rightRunner){
        	//we calculate the value of target which we'll search for
            target = k - nums[leftRunner];

            //the case when target is less than nums[leftRunner]. In this case we won't find 
            //a corresponding pair value since nums[leftRunner] is supposed to be the smaller of the
            //two values in the pair
            if(target < nums[leftRunner]) break;

            //this while loop searches for the corresponding greater pair value moving from the right
            while(leftRunner<rightRunner){
            	//case we find the target value
                if(nums[rightRunner] == target){
                    ++total; //increase total number of k-value pairs
                    --rightRunner; //move rightRunner further to the left
                    break;
                }
                //case when target is lower than the current nums[rightRunner], and hence we need
                //to keep on moving to the left in search for lower values
                else if(nums[rightRunner] > target)
                    --rightRunner;
                //the case when target is greater than nums[rightRunner], this means target is not present
                //is not present in the array, or that another target values is not available in case
                //a previous equal target value was already used
                else
                    break;
            }

		//once done with the current lower value in the k-sum pair we move on to the next one
            ++leftRunner;
        }

        return total;
    }



int main(){
	std::vector<int> nums{3,1,3,4,3};
	int k=6;

	std::cout<<maxOperations(nums,k)<<"\n";


	return 0;


}
