/*

3066. Minimum Operations to Exceed Threshold Value II

You are given a 0-indexed integer array nums, and an integer k.

In one operation, you will:

Take the two smallest integers x and y in nums.
Remove x and y from nums.
Add min(x, y) * 2 + max(x, y) anywhere in the array.
Note that you can only apply the described operation if nums contains at least two elements.

Return the minimum number of operations needed so that all elements of the array are greater than or equal to k.



Constraints:

2 <= nums.length <= 2 * 105
1 <= nums[i] <= 109
1 <= k <= 109
The input is generated such that an answer always exists. 
That is, there exists some sequence of operations after which all elements 
of the array are greater than or equal to k.




*/


#include<iostream>
#include<vector>
#include<queue>
#include<functional>



int minOperations(std::vector<int>& nums, int k) {
        //we create a priority queue min heap
        std::priority_queue<long, std::vector<long>, std::greater<long>> pq(nums.begin(), nums.end(), std::greater<long>());


        //to store the smallest two values in the min heap
        long a,b;
        //to store the number of operations
        int count = 0 ;

        //continue removing the first two values of the priority queue
        //and add back 2*minumum + maximum 
        while(pq.top() < k && pq.size() > 1){
            a=pq.top();
            pq.pop();
            b=pq.top();
            pq.pop();
            pq.push(a*2 + b);
            ++count;
        }

        return count;
    }



int main(){

	std::vector<int> nums{2,11,10,1,3};
	int k=10;


	std::cout << minOperations(nums, k) << "\n";

	return 0;

}
