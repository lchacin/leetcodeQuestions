/*


1143. Longest Common Subsequence


Given two strings text1 and text2, return the length of their longest common subsequence. 
If there is no common subsequence, return 0.

A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without 
changing the relative order of the remaining characters.

For example, "ace" is a subsequence of "abcde".
A common subsequence of two strings is a subsequence that is common to both strings.


Constraints:
-----------

1 <= text1.length, text2.length <= 1000
text1 and text2 consist of only lowercase English characters.



Approach:
--------

Our defined subproblem

f(i,j) := the length of the maximum common subsequence between S and S' up to ther ith and jth characters respectively


for i>1 and j>1
f(i,j) = 1 + f(i-1, j-1) if S[i] = S[j] and max( f(i,j-1) , f(i-1,j) ) otherwise


Now we define the initial value conditions:
f(1,1) = 1 if S[1] = S'[1] and 0 otherwise
f(i,1) = 1 if S[i] = S'[1] and f(i-1,1) otherwise
f(1,j) = 1 if S[1] = S'[j] and f(1,j-1) otherwise


We'll create a matrix with the initial value conditions. Then will iterate row by row, left to right, filling up the
matrix with the resutls from f(i,j).


*/


#include<iostream>
#include<vector>

//longestCommonSubsequence receives two string objects by reference
//it calculates and returns the length of the longest common subsequence between both strings
int longestCommonSubsequence(std::string& text1, std::string& text2) {
	//the case where each just one character
        if(text1.size()==1 && text2.size()==1) return text1[0]==text2[0];

	//we create a matrix to store the value of f(i,j)s
        std::vector<std::vector<short>> matrix(text1.size(),std::vector<short>(text2.size(),0));
        matrix[0][0] = text1[0]==text2[0]; // set the condition for the first letter of each string
        short i=0, j=0;
	
	//add the condition for f(i,1)s
        for(i=1; i<text1.size(); ++i){
            if(text1[i]==text2[j])
                matrix[i][j] = 1;
            else
                matrix[i][j] = matrix[i-1][j];
        }

	//add the condition for f(1,j)s
        i=0;
        for(j=1; j<text2.size(); ++j){
            if(text1[i]==text2[j])
                matrix[i][j] = 1;
            else
                matrix[i][j] = matrix[i][j-1];
        }

	//now that the first row and first column are fully filled
	//we can fill up the rest of the matrix with the general f(i,j) condition defined above
        for(i=1; i<text1.size(); ++i){
            for(j=1; j<text2.size(); ++j){
                if(text1[i]==text2[j])
                    matrix[i][j] = matrix[i-1][j-1] + 1;
                else
                    matrix[i][j] = std::max(matrix[i-1][j], matrix[i][j-1]);
            }
        }

	//the length of the maximum subsequence shared by S and S' will be in the bottom right corner
        return matrix.back().back();
    }






int main(){
	std::string S1("ccgcctacctg"), S2("atatcgctcgc");
	std::cout<<longestCommonSubsequence(S1,S2)<<"\n";

	return 0;


}
