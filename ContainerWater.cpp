/*

11. Container With Most Water

You are given an integer array height of length n. There are n vertical lines drawn such that the two endpoints of 
the ith line are (i, 0) and (i, height[i]).

Find two lines that together with the x-axis form a container, such that the container contains the most water.
Return the maximum amount of water a container can store.

Notice that you may not slant the container.

Constraints:

n == height.length
2 <= n <= 105
0 <= height[i] <= 104


Approach:

Naive Solution:
--------------

We would check the area of every possible container and record the maximum value.
We'd do this by using two loops. The outer loop would iterate over heights representing the left side of the container, and the inner loop
would iterate over all indexes greater than the index of the left height. We calculate the minimum of the left and right heights and multiply it
with the difference in index values which would represent the length of the rectangle.

Complexity = O(n^2)



Optimal Solution:
----------------

Since the optimal solution aspires to be of a faster order of complexity than O(n^2), its would have to be a solution that does not check
all possible containers. That is, the solution would have to  find a way of forgoing checking the areas of some containers because doing so 
would be redundant.

To achieve this we first create a new vector of interger pairs, where the pairs represent the height and the corresponding index. The reason
we want the index is because the index is used to calculate the length of the rectangle. 
We sort this vector of integer pairs in ascending order by height, and equal heights are then sorted further by index.

We employ a greedy approach: this is the key to not having to check all possible containers.
The crucial part of any greedy approach is defining the optimal "SUB-STRUCTURE PROPERTY" where we decompose the problem into subproblems
and their optimal solution is part of the optimal solution of the entire problem.

The subproblem s is defined as:
	Find the maximum container area for a container of a given height.
	
We iterate over the sorted vector of height-index pairs and for each pair we find the maximum container area where the height is the height
of the current pair. As we iterate of the pairs we keep track of a maximum area quantity obtained.

How do we obtain the maximum area for a given height?
The neat thing about sorting the height-index pairs in ascending order is that we are guaranteed that all heights to the right of the 
current pair are greater than or equal to the current height. Therefore we are guaranteed that all containers created with a right height
being any of the heights of the pairs above will yield a container with the height being the current height.

Hence to obtain the largest area we merely need to check which of the pairs above has the largest index distance from the current index.


How make this solution O(nlog(n))?

Sorting the pairs was done in O(nlog(n)). What we need to be careful about now is that we don't want to have to locate the pair with maximum distnace
from the current pair every time we consider a new pair. That would render the solution O(n^2).

Instead we store the index location of height-index pairs corresponding to the right and left-most indexes with 
heights greater than or equal to the current pair.  We only update the right and left-most indexes whenever we look at pairs in the vector of
height-index pairs neyond any of the two indexes, since this would mean we can't use the pairs at the right or left-most indexes because
they no longer have heights greater than the current height and hence we wouldn't be considering a container with height being the current height.

Since the left and right-most indexes will only get updated up to index corresponding to the last pair in the vector of height-index pairs,
this means these update only occur in O(n), making the entire solution O(nlog(n)).

This write up can be cryptic, take a look at the solution and it will all make sense.


*/

#include<iostream>
#include<vector>
#include<algorithm>



int maxArea(std::vector<int>& height) {
	//we create a vector to store height-index pairs
        std::vector<std::pair<int,int>> sortedHeight;
        sortedHeight.reserve(height.size()); //we tell the compiler to reserve enough memory for the sortedHeight vector


        int i=0; //integer to represent the index corresponding to a given height

        //iterate over the heights and add them to the sortedHeights vector with their corresponding index
        for(auto& h: height)
            sortedHeight.push_back({h, i++}); 

	//we create a binary comparison function that will compare two height-index pairs
	//it returns true if the the first pair has a height less than the second pair
	//if the heights are of equal value then it returns true if the first pair has a smaller index
        auto comp = [](std::pair<int,int>& p1, std::pair<int,int>& p2)->bool{
                if(p1.first<p2.first) return true;
                if(p1.first==p2.first && p1.second < p2.second) return true;
                return false;
        };

	//we sort the sortedHeight vector using the comp comparison function
	//the sortedHeight vector is now sorted in ascending order by height value and index
        std::sort(sortedHeight.begin(), sortedHeight.end(), comp);

        int minIndex, maxIndex; //min and maxIndex will store the index location in the sortedHeight vector corresponding to the 
        			//the left-most and right most pairs with heights greater than or equal to the a given pair
        
         
        int size=height.size();

        //we iterate over the pairs in the sortedHeight vector and recording the index location of the pairs with the left-most and right-most
        //index location in the original height vector 
        for(i=0; i<size; ++i){
        	//the left-most and irght-most correspond to the pairs in height with indexes 0 and size-1
        	//so once we get to them we store their index locations
            if(sortedHeight[i].second ==0) minIndex = i;
            else if(sortedHeight[i].second == size-1) maxIndex = i;
        }

        i=0;
        int j=0;
        int maxVolume = 0, tempVolume=0; //maxVolume will store the maxmimum area so far obtained and tempVolume the max area for the height of
        				//the current pair

        //we iterate over each pair in sortedHeights
        //and for each we find its corresponding maximum area. If th area is larger than the current maxmimum area, we update maximum area
        while(i<size){
        	//the case where the current pair no longer has a height greater than or equal to the recorded left-most pair .
        	//therefore we need to update the location of the left-most pair by finding the pair to the right of the current
        	//pair in sortedHeights that has the smallest index in the original heigts vector
            if(i>minIndex){
                minIndex = i;
                for(j=i; j<size; ++j){
                	//remeber that sortedHeight pairs contain the index corresponding to the original height vector
                	//so we search, comparing the indexes of pairs to the right of the current pair with index of the stored left-most pair.
                    if(sortedHeight[j].second < sortedHeight[minIndex].second) //this means we found a new pair in sortedHeights with an index
                    								//further to the left than the current one stored
                        minIndex = j; //so we update the index location of this left-most pair in sortedHeights
                    }
            }

		//this is the case where the current pair is past the presently stored index in sotredHeights corresponding
		//to the right-most pair in thebheights vector with height greater than or equal to the current pair
            if(i>maxIndex){
                maxIndex = i;
                for(j=i; j<size; ++j){
                    if(sortedHeight[j].second > sortedHeight[maxIndex].second)
                        maxIndex = j;
                }
            }

		//we record the highest area with height being the height of the current pair multiplying the height with the
		//maximum distance to the left-most or right-most pair with a greater than or equal to heightb value
            tempVolume = sortedHeight[i].first * std::max(sortedHeight[i].second - sortedHeight[minIndex].second, sortedHeight[maxIndex].second-sortedHeight[i].second);

		//if the obtained area is larger than the current max area, we update it
            if(tempVolume > maxVolume) maxVolume=tempVolume;
            
            ++i; //we move the following pair in the sortedHeight vector
        }
        
        return maxVolume;

    }



int main(){
	std::vector<int> height{1,8,6,2,5,4,8,3,7};

	std::cout<<maxArea(height)<<"\n";

	return 0;


}
