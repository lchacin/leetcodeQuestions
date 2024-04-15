/*

215. Kth Largest Element in an Array

Given an integer array nums and an integer k, return the kth largest element in the array.

Note that it is the kth largest element in the sorted order, not the kth distinct element.

Can you solve it without sorting?


Constraints:

1 <= k <= nums.length <= 105
-104 <= nums[i] <= 104




Approach:
Since we can't sort, we'll use a max-heap.
In C++ a priority queue is a max=heap, so we can use the STL priority queue.

Adding to an element to the priority queue will be in O(log(N)) since in the worst case scenario
each added element to the heap, will require ReHeap for each level in the tree.

Doing this for each element will give us an algo that runs in O(Nlog(N)).
Incidentally, this will also be the asymptotic time of doing it by first sorting the queue with merge-sort of quick-sort.

We then remove the first k-1 elements and the top element of the remaning heap will the be the kth largest element

*/



#include<iostream>
#include<queue>
#include<vector>
#include<functional>




int findKthLargest(std::vector<int>& nums, int k) {
        if(nums.size()==1) return nums[0]; //this is the case of nums having only 1 element

	//we create the prioirity queue with template type int. The underlying container will be an STL vector of integer type
	//and the comparison function will the STL std::less than function object.
	//we create the priority queue using the constructor that takes in iterators to the start and end of the nums vector
        std::priority_queue<int, std::vector<int>, std::less<int>> maxHeap(nums.begin(), nums.end(), std::less<int>{});

	//now that the max heap is created, we remove the first k-1 elements
        while(k>1){ maxHeap.pop(); --k;}

	//we return the top of the heap which is the kth largest element
        return maxHeap.top();
}



int main(){
	//example 1
	std::vector<int> vec{3,2,1,5,6,4};
	std::cout<<findKthLargest(vec,2)<<"\n";
	
	//example 2
	vec = {3,2,3,1,2,4,5,5,6};
	std::cout<<findKthLargest(vec,4)<<"\n";

	return 0;
}
