#include<iostream>
#include<vector>


bool increasingTriplet(std::vector<int>& nums){
	if(nums.size()<3) return false;

	int i=0,j=-1;

	for(int index=1; index<nums.size(); ++index){
		if(nums[index] < nums[i]) i=index;
		else if(j==-1 && nums[index] > nums[i]) j=index;
		else if(j!=-1 && nums[index] > nums[i] && nums[index]<nums[j]) j=index;
		else if(j!=-1 && nums[index] > nums[j]) return true;
	}

	return false;
}


int main(){
	std::vector<int> nums{2,4,-2,-3};
	std::cout<<std::boolalpha<<"Increasing Triplet found? "<<increasingTriplet(nums)<<"\n";
	
	return 0; 


}
