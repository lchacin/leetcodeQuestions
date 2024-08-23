#include<numeric>
#include<iostream>
#include<vector>



//NUmArray is a class that has as state two integer vectors.
//one is a vector of integers and the other is a vector storing the prefix
//sum of the values in the original integer vector
class NumArray {
public:
    std::vector<int> nums;
    std::vector<int> prefixSum; //stores prefix sum of nums vector
public:
    //constructor receives reference to a integer vector
    //and it instantiates the prefixSum state using std::partialSum
    NumArray(const std::vector<int>& nums): prefixSum(nums), nums(nums) {
        std::partial_sum(nums.begin(), nums.end(), prefixSum.begin());
    }
    
    //sum range returns the sum of the integers in nums from index left to right inclusive
    //it receives the left and and right indexes as rvalue reference parameters
    int sumRange(int&& left, int&& right) {
        //for efficiency we calculate the sum making use of the prefixSum vector
        //by subtracting the value at left-1 from right
        //if left is 0 then we merely return right index value of prefix sum
        return (left==0)?(prefixSum[right]):(prefixSum[right] - prefixSum[left-1]);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */


int main(){
	std::vector<int> nums{-2,0,3,-5,2,-1};
	NumArray* obj = new NumArray(nums);

	std::cout << "nums: ";
	for(auto& val : nums) std::cout << val <<" ";
	std::cout << "\n";

	std::cout<< "sum of values from index 0 to 2 : " << (obj->sumRange(0,2)) << "\n";
	std::cout<< "sum of values from index 2 to 5 : " << (obj->sumRange(2,5)) << "\n";
	std::cout<< "sum of values from index 0 to 5 : " << (obj->sumRange(0,5)) << "\n";

	return 0;
}
