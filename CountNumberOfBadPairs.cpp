/*

2364. Count Number of Bad Pairs

You are given a 0-indexed integer array nums. A pair of indices (i, j) is a bad pair if i < j 
and j - i != nums[j] - nums[i].

Return the total number of bad pairs in nums.


Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 109

*/


#include<iostream>
#include<unordered_map>
#include<vector>


    long long countBadPairs(std::vector<int>& nums) {
        //based on the restriction we see that nums.length is at most 10^5
        //hence the total number of considered pairs is in the order of 
        //10^10, therefore we need totalCount to be long long
        long long totalCount = 0;

        //to store differences between a value in nums and its index
        int diff;

        //hash map where keys are difference between value in nums and its
        //corresponding index
        std::unordered_map<int,int> diffCountMap;

        //we iterate values in nums
        for(int i=0; i<nums.size(); ++i){
            //we calculate the difference between the value in nums and its index
            diff = nums[i] - i;

            //we check if this difference is already in the hash map
            if(diffCountMap.contains(diff)){
                //if so we add the total number of previous differences that
                //did not equal to the current difference
                totalCount += i - diffCountMap[diff];

                //we update the total count of diff so far seen
                ++diffCountMap[diff];
            }

            //case diff has never been obtained before
            else{
                //update total count be the total number of diff values previously
                //obtained which is the current index
                totalCount += i;

                //add diff to the hashmap
                diffCountMap[diff]=1;
            }
            
        }

        return totalCount;

    }



int main(){
	std::vector<int> nums{4,1,3,3};

	std::cout << countBadPairs(nums) << "\n";

	return 0;

}
