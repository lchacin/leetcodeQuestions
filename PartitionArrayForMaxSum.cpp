/*

1043. Partition Array for Maximum Sum

Given an integer array arr, partition the array into (contiguous) subarrays of length at most k. 
After partitioning, each subarray has their values changed to become the maximum value of that subarray.

Return the largest sum of the given array after partitioning. 
Test cases are generated so that the answer fits in a 32-bit integer.


Constraints:

1 <= arr.length <= 500
0 <= arr[i] <= 109
1 <= k <= arr.length



Approach:

We take a DP approach.

We define our sub-problem to be

f(i,j):= maximum sum of the array from index i to index j
f(i,i) = arr[i]
f(i,j) = arr[m]*(j-i+1)   if j-i < k where  i<=m<=j and arr[m] is the maximum values in arr subarray from index i to j
f(i,j) = max( f(i,i) + f(i+1,j), f(i,i+1) + f(i+2,j),..., f(i,i+k-1) + f(i+k,j))

*/



#include<iostream>
#include<vector>
#include<algorithm> //for std::max_element


int f(int i, int  j, int& k, std::vector<int>& arr, std::vector<std::vector<int>>& m){
        if(m[i][j]!=-1) return m[i][j]; //the case where we've already calculate the maximum sum of the subarray from index i to j

        //the case where the number of elements from i to j is <= k
        else if(j-i<k) m[i][j] = *std::max_element(arr.begin()+i, arr.begin()+j+1) * (j+1-i);

        //the case where the number of elements from i to j is > k
        else{
        	//we calculate the f(i,j) by getting maximum sum of f(i,i+z) + f(i+z+1,j)
            for(int z=0; z<k; ++z){
            	//the case where f(i,i+z) hasn't been calculated yet
            	//we find the maximum value from index i to i+z and multiply the corresponding arr value by the number of elements from i to i+z
                if(m[i][i+z] == -1) m[i][i+z] = *std::max_element(arr.begin()+i, arr.begin()+i+z+1)*(z+1);

                //the case where f(i+z+1,j) hasn't been calculated
                //we recursively enter f to find the maximum sum from i+z+1 to j
                if(m[i+z+1][j] == -1) m[i+z+1][j] = f(i+z+1,j,k,arr,m);

                //we store f(i,j) in the matrix m to be the maximum of the current f(i,j) value and the sum of f(i,z) + f(z+1,j)
                m[i][j] = std::max(m[i][j], m[i][i+z]+m[i+z+1][j]);
            }
        }
        return m[i][j]; //we the value computed of f(i,j)
}


int maxSumAfterPartitioning(std::vector<int>& arr, int& k) {
        int SIZE = arr.size();

        //we create a SIZExSIZE matrix to store the f(i,j) values
        std::vector<std::vector<int>> m(SIZE, std::vector<int>(SIZE,-1));

        return f(0,SIZE-1,k,arr,m);
}



int main(){
	std::vector<int> arr{1,4,1,5,7,3,6,1,9,9,3};
	int k=4;

	std::cout<<maxSumAfterPartitioning(arr,k)<<"\n";

	return 0;

}
