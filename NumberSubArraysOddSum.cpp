/*

Number of Sub-arrays With Odd Sum


Given an array of integers arr, return the number of subarrays with an odd sum.

Since the answer can be very large, return it modulo 109 + 7.


Constraints:

1 <= arr.length <= 105
1 <= arr[i] <= 100



*/


#include<iostream>
#include<vector>
#include<numeric>


int numOfSubarrays(std::vector<int>& arr) {
        //create a prefix sum of the values in vector arr
        std::partial_sum(arr.begin(), arr.end(), arr.begin());

        //variables to store the total number of even and odd subrray sums
        //that start from the first index
        //and the total number of odd sum subarrays generated 
        long totalEven = 0 , totalOdd = 0;
        long total = 0;

        //we iterate over the prefix sum values
        for(auto& x: arr){
            //if the value is odd
            if(x%2){
                ++totalOdd; //update totalOdd 
                //then update total by the total number of
                //of previously subarrays ending with an even 
                //moded by 10^9 + 1
                //since this means we could generate odd subrrays
                //by removing the even subarrays from the 
                //sum up to the current value
                total += totalEven%(1000000000 + 7) + 1;
            }

            //repeat the same process for those ending with even prefix sum
            //values
            else{
                ++totalEven;
                total += totalOdd%(1000000000 + 7);
            }
        }

        //return the total moded by 10^9 + 1
        return total % (1000000000 + 7);        
    }



int main(){
	std::vector<int> nums{64,69,7,78,31,83,47,84,47,6,67};

	std::cout <<  numOfSubarrays(nums) << "\n";


	return 0;


}
