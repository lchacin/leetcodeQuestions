/*


643. Maximum Average Subarray I


You are given an integer array nums consisting of n elements, and an integer k.

Find a contiguous subarray whose length is equal to k that has the maximum average value and return this value. 
Any answer with a calculation error less than 10-5 will be accepted.



Constraints:

n == nums.length
1 <= k <= n <= 105
-104 <= nums[i] <= 104


Approach:

In order to obtain an O(n) solution we use a running sum as opposed to calculating the sum of k terms
each time the window of size k is shofted forward. That is, every time the window shifts one unit to the right, we 
remove the first term and add the new term.

Since the largest average is unchanged by the quotient, we focus on finding the largest sum, and only at the very end
will we divide by k.


*/



#include<iostream>
#include<vector>
#include<numeric>
#include<algorithm>


double findMaxAverage(std::vector<int>& nums, int& k) {
	//the case where the window size is the same as the size of the list of numbers.
	//in this case we merely return the average of all the numbers
        if(nums.size()==k) return std::accumulate(nums.begin(), nums.end(), 0.0)/k;

	//the case where the window size is 1.
	//in this case we return the largest value in the list of numbers
	else if(k==1) return *std::max_element(nums.begin(), nums.end());

	else{
		int start=0, end=k-1; //start and end will store the index of the first and last values in the moving window
		
		//runningSum stores the value of the running sum. 
		//We initialize it to the sum of the values in the starting window 
		double runningSum= std::accumulate(nums.begin(), nums.begin()+k, 0.0);

		//max sum stores the current largest sum of the running window 
		double maxSum = runningSum;

		//the while loop will remove the first element of running window and add next element to the right.
		//it then compares the sum of this new window of values with maxSum to determine whether a larger
		//sum has been obtained
		while(end<nums.size()-1){
			++end;
			runningSum = runningSum - nums[start] + nums[end];
			maxSum = std::max(runningSum, maxSum);
			++start;
		}
	
		//out of the while loop maxSum has the largest sum of a moving window /
		//we divide it by k to obtain the average
		return maxSum/k;
	}
	
}




int main(){
	std::vector<int> nums{1,12,-5,-6,50,3};
	int k = 4;

	std::cout<<findMaxAverage(nums,k)<<"\n";
	return 0;

}
