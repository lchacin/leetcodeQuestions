
#include<iostream>
#include<vector>


	//to be used in the case the array was rotated, it will locate the index
    //where the original end value of the array before it was rotated
    int tailSearch(std::vector<int>& nums, int x, int y, int w){
        //the case we found the tail
        if(x+1 == y && nums[x] > nums[y]) return x;

        //we move x forward if the value at num[x] is greater than num[y]
        //and store x's value before moving in w in case we need to go back to it
        else if(nums[x] > nums[y])
            return tailSearch(nums, (x+y)/2, y, x);
        
        //we move y backward to the posiition of x if num[x] is less than num[y]
        //and we move x back to its previous value at w
        else return tailSearch(nums, w, x, w);
    }

    int binarySearch(std::vector<int>& nums, int target, int start, int end){
        if(start > end) return -1;

        if(nums[(start+end)/2] == target) return (start+end)/2;

        else if(nums[(start+end)/2] < target) return binarySearch(nums, target, (start+end)/2 + 1, end);

        else return binarySearch(nums, target, start, (start+end)/2 - 1);
    }

    int main() {

	std::vector<int> nums{4,5,6,7,0,1,2};
	int target = 0;

        //the case the nums array is not rotated
        if(nums[0] <= nums.back()){
            std::cout <<  binarySearch(nums, target, 0 ,nums.size()-1);
        }

        //now
        int breakPoint = tailSearch(nums, 0, nums.size()-1, 0);
        //now that we know the break point we search for the target in the lower and upper lists
        //separately

        int location = -1;
        location = binarySearch(nums, target, 0, breakPoint);
        if(location != -1) std::cout << location;


        std::cout << binarySearch(nums, target, breakPoint+1, nums.size()-1);
	return 0;
}
