/*

2411. Smallest Subarrays With Maximum Bitwise OR

You are given a 0-indexed array nums of length n, consisting of non-negative integers. For each index i from 0 to n - 1, you must determine the size of the minimum sized non-empty subarray of nums starting at i (inclusive) that has the maximum possible bitwise OR.

In other words, let Bij be the bitwise OR of the subarray nums[i...j]. You need to find the smallest subarray starting at i, such that bitwise OR of this subarray is equal to max(Bik) where i <= k <= n - 1.
The bitwise OR of an array is the bitwise OR of all the numbers in it.

Return an integer array answer of size n where answer[i] is the length of the minimum sized subarray starting at i with maximum bitwise OR.

A subarray is a contiguous non-empty sequence of elements within an array.


Constraints:

n == nums.length
1 <= n <= 105
0 <= nums[i] <= 109


*/

#include<iostream>
#include<vector>


std::vector<int> smallestSubarrays(std::vector<int>& nums) {
        //vector to store the minimum size subarrays of maximum bitwise OR where the subarray starts at
        //each given index
        std::vector<int> returnVec(nums.size());
        returnVec.back() = 1; //right value has only one subarray, namely itself
        
        //activatedBits will record the bits that have been activated by all values to the right
        //of the current value
        std::vector<std::pair<int,int>> activatedBits(32, {0,-1}); //first value in pair is the state of a bit, and
                                                                    //the second value is the index of the last
                                                                    //nums value seen that had the bit set
        int subArrayEnd; //to store the end of the maximum bitwise subarray of minimum length starting from the given index
        int currentBit; //to store the bit of the starting value being worked on

        int i=nums.size()-1, j; //i will store the index of the nums value being considered and j will 
                                //iterate over the 32 bit positions of 32-bit integer.


        //now we record the set bits from the last number in nums
        int tempValue = nums[i]; //will store the value left after dividing nums[i] by 2 multiple times
        j = 31;
        while(tempValue != 0){
            currentBit = tempValue % 2; //obtain the last bit 
            tempValue >>= 1; //divide the value by 2 via shift operator

            //check if the bit was set and store the set bit with the index of the current nums value
            if(currentBit == 1)
                activatedBits[j] = {1, i}; //record bits as active and the smallest
                                            //of the value that provided it
            --j; //move on the next bit
        }



        --i; //move to the next value in nums (we iterate backwards)

        //now we analyze the remaining values in nums
        for(; i > -1; --i){
                subArrayEnd = i; //the end of the minimum subarray of max or value has an initial 
                                    //equal to the index of the current value 
                tempValue = nums[i];
                j = 31;

                //we first go over the bits set in the current value
                while(tempValue != 0){
                    currentBit = tempValue % 2;
                    tempValue >>= 1;

                    //the case the bit was not set but another value already seen in nums did have this bit
                    //set, therefore the subarray should extend to at least this value becasue inlduing this
                    //value in the OR will increase the OR result
                    if(currentBit == 0 && activatedBits[j].first == 1){
                        //we update the subArrayEnd if the index of the number that had this bit set
                        //is further away from the current index than the current end
                        subArrayEnd = std::max(subArrayEnd, activatedBits[j].second);
                    }
                    //the case the bt was set in the current number, we update the index of the number
                    //that last had this bit set
                    else if(currentBit == 1){
                        activatedBits[j] = {1,i};
                    }

                    --j; //move to the next bit
                }
                //out of the while loop now all the remianing bits are not set for the current value

                //we check if the remaining bits were set for other values
                while(j>-1){
                    //if so we update the end of the subarray because these values will increase the OR
                    if(activatedBits[j].first == 1)
                        subArrayEnd = std::max(subArrayEnd, activatedBits[j].second);
                    --j;
                }

                //at this points subArrayEnd stores the postion of the last value containing a set bit
                //that increases the OR of the subarray

                //we record the length of the subarray
                returnVec[i] = subArrayEnd - i + 1;

        }
        

        return returnVec;
    }



int main(){
	std::vector<int> nums{1,0,2,1,3};

	auto result = smallestSubarrays(nums);

	for(auto& x: result)
		std::cout << x << ",";

	return 0;

}
