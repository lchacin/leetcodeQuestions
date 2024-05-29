/*

2542. Maximum Subsequence Score

You are given two 0-indexed integer arrays nums1 and nums2 of equal length n and a positive integer k. 
You must choose a subsequence of indices from nums1 of length k.

For chosen indices i0, i1, ..., ik - 1, your score is defined as:

The sum of the selected elements from nums1 multiplied with the minimum of the selected elements from nums2.
It can defined simply as: (nums1[i0] + nums1[i1] +...+ nums1[ik - 1]) * min(nums2[i0] , nums2[i1], ... ,nums2[ik - 1]).
Return the maximum possible score.

A subsequence of indices of an array is a set that can be derived from the set {0, 1, ..., n-1} by deleting some or no elements.


Constraints:

n == nums1.length == nums2.length
1 <= n <= 1e5
0 <= nums1[i], nums2[j] <= 1e5
1 <= k <= n



Approaches
----------


Naive Approach:
-------------

We can learn from the naive approach.
The Naive approach will have us check every possible combination of size k from nums1, and then minimum nums2 value among the k
chosen value from nums1 to then calculate the score.

The issue with this approach is that we have (n choose k) possible combinations to choose from in nums1. For example, if n=40 and k=20
(40 choose 20) will alone be over one hundred billion possible combinations. Given that n can go up to one hundred thousand, the sheer amount 
of possible combinations makes this solution infeasible. 

What is the big take-away from considering the naive approach? It tells us that any feasible solution will have to be one that does not consider
all the possible combinations. The optimal solution will have to be one that ignores many combinations because checking them is unnecessary. The
optimal solution will be involve a GREEDY APPROACH.


O(N^2) Approach:
---------------

After determining the solution should be greedy, we try to determine the "OPTIMAL SUB-STRUCTURE PROPERTY". We want to determine sub-problems
that when solved individually, their solutions can be put together to determine an overall solution to the problem.

We decide to iterate over each possible value of nums2, and for each value try to determine the highest possible score given that the minimum of
the combination of size k from nums1 is the current value of nums2. 

Before obtaining the solution with this method, we sort the nums1 array in descending order, so the first combination of size k obtained for
which the given nums2 value is the minimum of all the k corresponding values is the highest possible score. We record this score and move on to the
following nums2 value and find its possible highest score. If this new score is higher than the current highest score obtained, we update the
current highest score.

This solution is an O(N^2) solution because in the worst case scenario for each  nums2 value we need to traverse an O(N) amount of values of nums1
to obtain the first k elements for which their corresponding nums2 values are higher than the current nums2 value.

Given that N can go up to 1e5, this would imply a solution that coudl require over 10 billion oprations, which albeit doable, it is not optimal.



O(Nlog(N)) Approach:
-------------------

The problem with the O(N^2) approach is that for each nums2 value being considered, we are bounded to check all nums1 values until we are able
to muster a combination of size k. We would like to search for these k values in nums1 in a more efficient manner. But since the values in nums1
are tied to their corresponding values in nums2, any attempt to sort num1 values to make their selection more efficient is futile because
it would require sorting nums1 value for every new nums2 value as minimum being considered. 

This leads us to change from a sub-structure problem for each nums2 value, to a sub-structure problem for each new nums1 value being considered.
That is, we sort nums1 in descending order and record the score of the first k elements, and we'll update the maximum score for each new
nums1 element considered.  

For those with a mathematical background, this approach is similar to Newton-Raphson or Gradient Descent Algorithms where we seek to find local
minimums and maximums be moving into the direction of steepest descent based on the information known locally. For every new nums1 being
considered we have the optimal score up to that new value.

The benefit of sorting nums1 values in descneding order is that for every new nums1 value being considered, we know that a potential higher
score will not be obtained due to a higher sum of nums1 values (since the all of the nums1 values previously considered would be greater than or
equal to the present one), instead it would be due to a higher minimum nums2 value, that when multiplied with the sum of the k nums1 values
in the combination, will yield a higher score, albeit the score itself being less than before. 

Ok, let's go a bit more granular. When considering a new nums1 value, how do we proceed? We first determine whether its corresponding nums2 value
is larger than the current minimum nums2 value in the current optimal group. If it isn't than we move on to the next nums1 value. If its,
we determine whether removing one of the current nums1 values in the sum and replacing it with the current nums1 value, yields a higher score.

The nums1 value that will be removed will be the one corresponding to the current minimum nums2 value in the group, this way by adding
the nums1 value, the group will have a higher minimum nums2 value. 

Finally, here is where the Heap data structure/ Priority Queue comes into play. We would want an efficient way of knowing which nums1
value corresponds to the current minimum nums2 value in the group. We don't want to have to iterate over all elements in the group, every time
a new nums1 value is considered, to determine if the new nums1 value has a larger nums2 value than the current minimum. Therefore we create
a min-heap that stores the largest k nums2 values explored up to that point in the process. 

When considering a new nums1 value, we compare its corresponding nums2 value with the top of the heap, and if the its nums2 value is larger
than the top of the heap we remove the current top of the heap and add the new nums2-nums1 pair to the heap. 
If the score was larger, we calculate the score of a new size k where we replace the nums1 member corresponding to the previous top of the heap 
with the new nums1 value being considered. If the score is higher we update the current max score. That is the min-heap at all points in time
will store the nums2-nums1 pair with the largest nums2 values, even if some of this pairs are not part of the current max score.

The reasoning behind storing a nums2-nums1 pair in the heap, even if such a new pair didn't lead a to a higher score, is that we want to be 
forward looking is leave room to the potential cases where previous pairs that didn't lead to higher scores, could combine with future
nums2-nums1 pairs to allow for much greater minimum nums2 value in the group to the point that they surpass any other score that might have
a larger sum of nums1 value but a lower minimum nums2.

Everytime we add a new nums2-nums1 pair to the heap, the heap will add it and partially sort its value in O(log(N)). Since we iterate over all
nums1 values once, this leads to an O(Nlog(N)) solution. 




Why not dynamic programming?
----------------------------

You should consider DP, but then realize that it doesn't provide any benefits. DP provides optimizatin by storing previously calculated results
and save us the overhead of having to recalculate them when they are repeatedly required again in further processes in the algo. 
In our search for the optimal group of size k, there is no repeated calculations. At any point in time we are always considering a new possible
combination. Even when approach the proble  with backracking, there is also no duplicate work for which DP would help. 



Final take-away:
----------------

This is a great problem that tests your ability of determining when a problem deserves a greedy approach; it gets you to think
about the "OPTIMAL SUB-STRUCTURE PROPERTY" and the contraints which is key to quickly determine whether a problem deserves a greedy 
approach in an interview. 

The use of the heap data-structure is literally a black-box working behind the scenes, as if concurrently, sorting elements as they get added. 

It took me several days to finally get to the solution. I have mixed feelings because it is a medium question, and normally they would 
take me 1-2hrs to determine the optimal approach, yet I feel fulfillment as well from the learning process -- going back-and-forth exploring new
options, hitting a wall, turning around and exploring a different path -- which I wouldn't have experienced had I just looked at the solution
on the first day of trying.

*/ 


#include<iostream>
#include<vector>
#include<algorithm> //for std::sort
#include<queue> //for std::priority _queue


//maxScore receives two reference to integer vectors containing the values in nums1 and nums2, and an integer reference
//representing the size of the combination
long long maxScore(std::vector<int>& nums1, std::vector<int>& nums2, int& k){
        // return 0;
        //we create a counter variable for the for loop and record the size of nums1 and nums2

        int i, size=nums1.size();

	//the case where nums1 and nums2 only have one value
        if(size==1) return nums1[0]*nums2[0];

        //the case where the size of the group is 1, therefore we search for the pair with the highest
        //product of nums1 and nums2 corresponding values and return this as the highest score possible
        if(k==1){
            int score=0;
            for(i=0; i<size; ++i){
                if(score<nums1[i]*nums2[i]) score=nums1[i]*nums2[i];
            }
            return score;
        }

	//currentSum will store the sum of the nums1 values of the k elements with the largest nums2 values considered so far
        long long currentSum=0;

	//numPair will be a vector of nums2-nums1 pairs 
        std::vector<std::pair<int,int>> numPair;
        numPair.reserve(size); //to avoid run-time overhead of a vector having to be transfered to another memory location due to 
        			//its size surpassing the allotted sequential memory, we tell the compiler to reserve enough
        			//memory to store all possible pairs 

	//we add the correspoing nums1-nums2 pairs to numPair
        for(i=0; i<size; ++i)
                numPair.push_back({nums2[i],nums1[i]});

	//we create two lambdas. num1Comp will be used to sort the numPair by the num1 values in descending order, 
	//and num2Comp will be passed to the heap so it sorts the pairs by num2 value 
        auto num1Comp = [](std::pair<int,int>& p1, std::pair<int,int>& p2)->bool{ return p1.second < p2.second;};
        auto num2Comp = [](std::pair<int,int>& p1, std::pair<int,int>& p2)->bool{ return p1.first > p2.first;};

        //sort numPair by largest nums1 value
        std::sort(numPair.begin(), numPair.end(), num1Comp);

        //we create a priority queue that stores integer pairs. It will use an underlying vector of integer pairs, and it uses
        //num2Comp as its comparison function. num2Comp will make num2Heap a min-heap 
        std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, decltype(num2Comp)> num2Heap(num2Comp);

	//we iterate over the first k pairs in numPair, record the sum of their num1 values, and then add them to num2Heap
	//we sort numPair in ascending order since std::vector only allows for pop_back, hence we read the back of numPair
	//for every new num2-num1 pair explored.
        for(i=0; i<k; ++i){
                currentSum+=numPair.back().second;
                num2Heap.emplace(numPair.back());
                numPair.pop_back();
        }

	//currentMaxScore store the present maxmimum score achieved. for the first k elements explored it will be the sum
	//of their num1 values times the num2 value at the top of the heap representing their minimum num2 value
        long long currentMaxScore = currentSum*num2Heap.top().first;

        //tempPair will be used to store the back of the of the numPair vector. tempTop will be used to store
        //the pair at the top of the min-heap
        std::pair<int,int> tempPair, tempTop;
        long long tempScore; //tempScore is used to store the score of the combination of k elements when we replace
        			//the element at the top of the heap with the new tempPair popped from numPair

	//we iterate over all num2-num1 pairs in numPair until it is empty
        while(!numPair.empty()){
                tempPair=numPair.back();
                numPair.pop_back();
                //we check if the new num2-num1 pair popped from tempPair has larger num2 value than the top of the min-heap
                if(tempPair.first > num2Heap.top().first){
                	//if so we record the pair at the top of the heap and pop it
                        tempTop = num2Heap.top();
                        num2Heap.pop();

                        //we add the new num2-num1 pair with a larger num2 value than tempTop to the min-heap
                        num2Heap.push(tempPair);

                        //after adding tempPair to the min-heap the  heap will internally partially sort the pairs and place a new pair at the
                        //top corresponding to the one with the new minimum num2 value

                        //we record the new score with the new pair as a part of the combination of size k
                        //we do so by subtracting the num1 value of the pair removed from currentSum aand adding the num1 value
                        //of the new pair. We then multiply it with the new minimum num2 value of the group obtained from the top
                        //of the min-heap
                        currentSum = currentSum +  tempPair.second - tempTop.second;
                        tempScore = currentSum * num2Heap.top().first;

                        //if the current max score is smaller than the tempScore, we update the max score
                        if(currentMaxScore < tempScore)
                                currentMaxScore = tempScore;
                }
        }
        
        return currentMaxScore;
}



int main(){
	std::vector<int> nums1{93,463,179,2488,619,2006,1561,137,53};
	std::vector<int> nums2{345,229,976,2086,567,726,1640,2451,1829};
	int k=4;
	
	std::cout<<maxScore(nums1,nums2,k)<<"\n";
	return 0;
}
