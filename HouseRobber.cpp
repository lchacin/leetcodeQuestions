/*

198. House Robber


You are a professional robber planning to rob houses along a street. 
Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them 
is that adjacent houses have security systems connected and it will automatically contact the police if two 
adjacent houses were broken into on the same night.

Given an integer array nums representing the amount of money of each house, return the maximum amount 
of money you can rob tonight without alerting the police.


Constraints:
1 <= nums.length <= 100
0 <= nums[i] <= 400


Approach:

We perform backward dynamic programming. Moving backward from the last house, we define our subproblem to
be:

f(n) = nums[n]
f(n-1) = max(nums[n-1], nums[n])
f(i) = max(nums[i] + f(i-2), f(i-1))

It says that anytime we are considering whether robbing a house we check if maximum stash between robbing the current house
plus the maximum stash starting two house further down or the maximum stash starting from the following house without
robbing the current one.

We perform memoization by recording the maxmium stash starting from the following house or from two houses firther down

*/



#include<iostream>
#include<vector>


int rob(std::vector<int>& nums) {
	//the case where there is only one house
        if(nums.size()==1) return nums.back();

	//the case there are only two houses
        if(nums.size()==2) return std::max(nums[0], nums[1]);


        unsigned short max2 = nums.back(); //stores the maxmimum profit starting two house further down
        unsigned short max1 = std::max(nums.back(), nums[nums.size()-2]); //stores the maximum profit starting from the following house
        unsigned short maxStash; //stores the current maxmimum stash

	//we iterate backwards starting from the third to last house
        for(short i=nums.size()-3; i>-1; --i){
		//we update maxStash bu comparing the stash from robbing the current house and adding the maximum stash
		//starting from two houses firther down with not robbing the current house and keeping the maximum stash
		//starting from the following house
                maxStash = std::max<unsigned int>(nums[i]+max2, max1);
		
		//we update the maxsimum stash of two houses down to be the maximum stash from the following house
		//we update the maximum stash of the following house to be the current maxStash
                max2 = max1;
                max1 = maxStash;
        }

        return maxStash;

}

int main(){
	std::vector<int> nums{2,7,9,3,1};
	std::cout<<rob(nums)<<"\n";

	return 0;

}
