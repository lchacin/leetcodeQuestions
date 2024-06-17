/*

1641. Count Sorted Vowel Strings

Given an integer n, return the number of strings of length n that consist only of vowels (a, e, i, o, u) 
and are lexicographically sorted.

A string s is lexicographically sorted if for all valid i, s[i] is the same as or comes 
before s[i+1] in the alphabet.


Constraints:
1 <= n <= 50


Approach:

Typically when we perform DP we do so because there is a lot of repition in the naive solution
that we could avoid recalculating by storing previously calculated results.

Nontheless, we notice that if we were to solve this problem the naive way by generating all possible
strings and increase a total count variable when generated, we don't encounter repetitions.

This hints at the fact that we should not calculate the total count by generating the strings themselves
but instead generate the total count by using previous total count results for lower n values.


We define our sub-problem as follow:

f(i,j):= the total number of strings of size i that end with jth vowel that are lexicographically ordered

Base cases:
f(1,j):= total number of strings of length 1
f(1,j) = 5

f(i,1):= total number of strings of length i that end with vowel 'a'
f(i,1) = 5 


General case:
f(i,j) = f(i-1,j) + f(i,j-1)


Time complexity: O(n*5) = O(n)

*/

#include<iostream>
#include<vector>
#include<numeric> //for std::accumulate

int countVowelStrings(int& n) {
	//the case of strings of length 1
        if(n==1) return 5;

        //the defined sub-problem shows that an individual value of
        //a row only repends on the same value avoe in the previous row
        //and the previous value in the current row.
        //therefore we don't have to create a matrix with n rows 
        //instead we create a matrix of two rows, where each time
        //we need to calculate a new row, we let the present second
        //row be the first row, and then proceed to update the second
        //row with a new row

        //matrix of two rows and five columns for each vowel
        std::vector<std::vector<int>> f(2, std::vector<int>(5,1));

        unsigned iteration; 
        for(iteration=1; iteration<n; ++iteration){
            //since there are only 5 columns, we can perform an optimization
            //by loop unrolling the loop that would iterate over columns of f
            //by explicitly calculating the five entries in the row corresponding
            //to the five columns for each vowel
            f[1][1] = f[0][1] + f[1][0];
            f[1][2] = f[0][2] + f[1][1];
            f[1][3] = f[0][3] + f[1][2];
            f[1][4] = f[0][4] + f[1][3];

            //we update the first row to be the second row, so in the next
            //loop iteration we calculate the new second row
            f[0][1]=f[1][1];
            f[0][2]=f[1][2];
            f[0][3]=f[1][3];
            f[0][4]=f[1][4];
        }

        //we add up all the cases in the last row and return it
        return std::accumulate(f[1].begin(), f[1].end(), 0);
        
    }



int main(){
	int n=33;
	std::cout<<"Total number of lexicographically ordered string vowels of length "<<n<<": "<<countVowelStrings(n)<<"\n";

	return 0;

}
