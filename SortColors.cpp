/*

75. Sort Colors


Given an array nums with n objects colored red, white, or blue, sort them in-place so that 
objects of the same color are adjacent, with the colors in the order red, white, and blue.

We will use the integers 0, 1, and 2 to represent the color red, white, and blue, respectively.

You must solve this problem without using the library's sort function.

Constraints:

n == nums.length
1 <= n <= 300
nums[i] is either 0, 1, or 2.


*/



#include<iostream>
#include<vector>



//this function performs build algorithm to produce a max-heap
    //in-place
    void buildMaxHeap(std::vector<int>& nums){
        int leftChild, rightChild, i;
        int temp;
        for(int j=(nums.size()-1)/2; j>-1; --j){
            leftChild = j*2+1;
            rightChild = j*2+2;
            i=j;

            while(leftChild < nums.size()){
                if(rightChild < nums.size()){
                    if(nums[leftChild] >= nums[rightChild] && nums[i] < nums[leftChild]){
                        temp = nums[i];
                        nums[i] = nums[leftChild];
                        nums[leftChild] = temp;
                        i=leftChild;
                    }

                    else if(nums[rightChild] > nums[leftChild] && nums[i] < nums[rightChild]){
                        temp = nums[i];
                        nums[i] = nums[rightChild];
                        nums[rightChild] = temp;
                        i=rightChild;
                    }
                    
                    else break;
                }

                else if(nums[i] < nums[leftChild]){
                    temp = nums[i];
                    nums[i] = nums[leftChild];
                    nums[leftChild] = temp;
                    i=leftChild;
                }
                
                else break;

                leftChild = i*2+1;
                rightChild = i*2+2;
                
            }
        }
    }

    //percolates down a value if any of the children is larger than itself
    //in place
    void percolateDown(std::vector<int>& nums, int start, int end){
        int leftChild = 2*start+1;
        int rightChild = 2*start+2;
        int temp;
        while(leftChild < end){
            if(rightChild < end){
                if(nums[leftChild] > nums[start] && nums[leftChild] >= nums[rightChild]){
                    temp = nums[start];
                    nums[start] = nums[leftChild];
                    nums[leftChild] = temp;
                    start = leftChild;
                }

                else if(nums[rightChild] > nums[start]){
                    temp = nums[start];
                    nums[start] = nums[rightChild];
                    nums[rightChild] = temp;
                    start = rightChild;
                }

                else break;
            }

            else if(nums[leftChild] > nums[start]){
                temp = nums[start];
                nums[start] = nums[leftChild];
                nums[leftChild] = temp;
                start = leftChild;
            }

            else break;

            leftChild = 2*start+1;
            rightChild = 2*start+2;
        }
    }

    void sortColors(std::vector<int>& nums) {
        //perform build-heap alogrithm to make a min heap
        buildMaxHeap(nums);

        int temp;
        int end=nums.size()-1;
        while(end>0){
            //swap the first last values
            temp=nums[end];
            nums[end]=nums[0];
            nums[0]=temp;

            //now percolate down
            percolateDown(nums, 0, end);

            --end;

        }
        
    }




int main(){
	std::vector<int> nums{2,0,2,1,1,0};

	sortColors(nums);

	for(auto& x: nums) std::cout << x << " ";
	std::cout << "\n";


	return 0;
	
}
