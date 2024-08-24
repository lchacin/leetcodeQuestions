/*

2574. Left and Right Sum Differences

Given a 0-indexed integer array nums, find a 0-indexed integer array answer where:

answer.length == nums.length.
answer[i] = |leftSum[i] - rightSum[i]|.
Where:

leftSum[i] is the sum of elements to the left of the index i in the array nums. If there is no such element, leftSum[i] = 0.
rightSum[i] is the sum of elements to the right of the index i in the array nums. If there is no such element, rightSum[i] = 0.
Return the array answer.

Constraints:

1 <= nums.length <= 1000
1 <= nums[i] <= 105


*/


#include<iostream>
#include<algorithm> //for std::transform
#include<vector>



//leftRightDifference receives as paramter a reference to an integer vector and returns 
    //a vector containing the difference between the left and right sums of the parameter vector
    std::vector<int> leftRightDifference(std::vector<int>& nums) {
        //create vectors to store leftSum and rightSum
        std::vector<int> leftSum(nums.size(),0), rightSum(nums.size(),0);

        //this lambda adds accepts a new value and a accumulator and returns their sum
        //we use auto to make the lambda more flexible to the data type used
        auto prefixLambda = [](auto& newVal, auto& acc)->auto {return newVal+acc;};

        //use transform to obtain the leftSum and rightSUm
        //for rightSum we use a reverse iterator to move from the back to the front of the nums vector
        std::transform(nums.begin(), nums.end()-1, leftSum.begin(), leftSum.begin()+1, prefixLambda);
        std::transform(nums.rbegin(), nums.rend()-1, rightSum.rbegin(), rightSum.rbegin()+1, prefixLambda);

        std::vector<int> answer(nums.size());
        //use transform again to fill up answer with the absolute difference between the corresponding values in leftSum and rightSum
        std::transform(leftSum.begin(), leftSum.end(), rightSum.begin(), answer.begin(), [](auto& l, auto& r)->auto{return std::abs(l-r);});
  
        return answer;
    }



int main(){
	std::vector<int> nums{10,4,8,3};

	auto answer = leftRightDifference(nums);

	for(auto& val: answer)
		std::cout << val << ", ";
	std::cout<<std::endl;

	return 0;
}
