/*

560. Subarray Sum Equals K

Given an array of integers nums and an integer k, return the total number of subarrays whose sum 
equals to k.

A subarray is a contiguous non-empty sequence of elements within an array.


Constraints:

1 <= nums.length <= 2 * 104
-1000 <= nums[i] <= 1000
-107 <= k <= 107

*/




#include<iostream>
#include<vector>
#include<unordered_map>	//for std::unordered_map
#include<numeric> //for std::partial_sum

int subarraySum(std::vector<int>& nums, int k) {
        //create a prefix sum vector using std::partial_sum
        std::vector<int> prefixSum(nums.size());
        std::partial_sum(nums.begin(), nums.end(), prefixSum.begin());

        //create a hashmap with keys equal to a value of the prefux sum
        //and values equal to the number of times they appear in the
        //prefix sum
        std::unordered_map<int,int> map;

        int total = 0;

        //we add a zero to the map so that values of the prefux equal to the
        //target are counted
        map.insert({0,1});

        //we iterate through every value in the prefix sum and check if 
        //the current value minus the target is in the prefux sum
        //if so we increase our total
        //we then check if the current prefix sum key is not in the 
        //hashmap. If so, we add it it to the hash map with value equal 1
        //otherwise we increment the total value count.
        for(int i=0; i<nums.size(); ++i){
            if(map.contains(prefixSum[i]-k))
                total += map[prefixSum[i]-k];
            if(!map.contains(prefixSum[i])) map.insert({prefixSum[i],1});
            else ++map[prefixSum[i]];

        }

        return total;
        
        
    }


int main(){
	std::vector<int> nums{1,2,1,2,1};
	int k=3;

	std::cout << subarraySum(nums, k) << "\n";
	
	return 0;
}
