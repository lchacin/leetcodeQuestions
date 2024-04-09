/* Description: Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums 
except nums[i]. The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer. You must write an algorithm that runs in 
O(n) time and without using the division operation.


Approach: For each nums[i], answer[i] will be the product of all elements in nums above and below index i. Therefore we'll create two prefix 
product arrays, one with forward prefix product and a second with prefix product in reverse order.

Element i-1 of forward prefix product contains the product of all elements of nums up to index i-1, and Element i+1 of reverse prefix product has 
the product of all elements in nums index n-1 to i+1.

Lastly, answer[i] will be the product of element i-1 of forward prefix product and element i+1 of reverse prefix product

*/



/* Constraints:

2 <= nums.length <= 10^5 -30 <= nums[i] <= 30 The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer

*/



#include<iostream> 
#include<vector>


//this function will output a vector where for each element is the product of all the remaining elements in nums except current element

std::vector<int> productExceptSelf(std::vector<int>& nums){ 
	std::vector<int> result(nums.size(),0); //vector to store the result 
	int i; //index to iterate in for loops


	//now we calculate the forward prefix product
	std::vector<int> FPP(nums); 
	
	//now we calculate the moving product
	for(i=1; i<FPP.size(); ++i)
		FPP[i]*=FPP[i-1];
	

	//now we calculate the reverse prefix product
	std::vector<int> RPP(nums); 
	for(i=nums.size()-2; i>-1; --i)
		RPP[i]*=RPP[i+1];
	
	
	//Now we calculate the final result each element i in result will be the product of FPP's i-1 and RPP's i+1
	result[0]=RPP[1]; 
	result.back() = FPP[nums.size()-2]; 
	for(i=1; i<nums.size()-1; ++i)
		result[i] = FPP[i-1]*RPP[i+1];


	return result; //cast to an r-reference to avoid an additional copy in the return process
}


auto printVec = [](auto& vec){
	for(auto& val: vec) 
		std::cout<<val<<",";
	std::cout<<"\n";
};


int main(){ 
	
	std::vector<int> nums{5,2,3,4}; 
	auto result = productExceptSelf(nums);
	
	printVec(result);	


	nums = {-1,1,0,-3,3};
	result = productExceptSelf(nums);
	
	printVec(result);
	return 0;

}

