/*

1726. Tuple with Same Product

Given an array nums of distinct positive integers, return the number of tuples (a, b, c, d) 
such that a * b = c * d where a, b, c, and d are elements of nums, and a != b != c != d.

Constraints:

1 <= nums.length <= 1000
1 <= nums[i] <= 104
All elements in nums are distinct.


*/


#include<iostream>
#include<vector>
#include<unordered_map>


int tupleSameProduct(std::vector<int>& nums) {
        //to store the sets of four values that produce 
        //a specific product
        int count = 0;

        //hash map to keep track of the number of times a specific
        //product between two values in nums shows up
        std::unordered_map<int,int> productCountMap;

        int i,j; //looping variables

        //we iterate over distinct pairs of values in nums
        for(i = 0; i<nums.size(); ++i){
            for(j=i+1; j<nums.size(); ++j){
                //if the product of value at indexes i and j
                //is already in the hash map
                if(productCountMap.contains(nums[i]*nums[j])){
                    //we update the number of times the product
                    //shows in the hash map
                    ++productCountMap[nums[i]*nums[j]];

                    //we update the total count of sets that 
                    //produce the same product
                    count += productCountMap[nums[i]*nums[j]]-1;
                }

                //case this is the first time
                else{
                    productCountMap[nums[i]*nums[j]] = 1;
                }
            }
        }

        //multiply by 8 count all the possible orders of each individual
        //set that will give the same product
        return 8*count;
    }


int main(){
	std::vector<int> nums{10,5,15,8,6,12,20,4};

	std::cout << tupleSameProduct(nums) << "\n";

	return 0;


}

