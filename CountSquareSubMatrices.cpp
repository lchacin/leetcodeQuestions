/*

1277. Count Square Submatrices with All Ones

Given a m * n matrix of ones and zeros, return how many square submatrices have all ones.

Constraints:
1 <= arr.length <= 300
1 <= arr[0].length <= 300
0 <= arr[i][j] <= 1


Approach:

We use a Dynamic Programming Approach.

The subproblem is the following:

f(i,j) = matrix[i][j] if i==matrix.size()-1 and j=matrix[0].size()

f(matrix.length()-1,j) = f(matrix.length()-1,j) + f(matrix.length()-1,j+1)
f(i, matrix[0].length()-1) = f(i, matrix[0].length()-1) + f(i+1, matrix.length()-1)

f(i,j) = f(i+1,j) + f(i,j+1) - f(i+1,j+1) + matrix[i][j] + 
	(matrix[i+1][j] == matrix[i][j+1] == matrix[i+1][j+1] == 1) * (1 + min(largestSquare[i+1][j], largestSquare[i][j+1], largestSquare[i+1][j+1]))


where largest square stores the dimension of the largest square matrix of 1s that can be generated from (i,j) as the upper left corner
f will be a matrix of the size of "matrix" and will store all the square matrices of 1s in the submatrix matrix[i:][j:]

Time Complexity: O(mn)

*/


#include<iostream>
#include<vector>
#include<numeric> //for std::accumulate and std::min

//countSquares is a function that receives an mxn integer matrix by reference and returns the number of square submatrices 
//of all 1s within the matrix parameter
int countSquares(std::vector<std::vector<int>>& matrix) {
        const int ROW=matrix.size(), COL=matrix[0].size();

        //the case where the matrix is dimension 1x1
        if(ROW==1 && COL==1) return matrix.back().back();

        //the case the matrix is a single row
        //is so we merely calculate the total number of 1s and return it
        else if(ROW==1) return std::accumulate(matrix.begin()->begin(), matrix.begin()->end(),0);

	//the case the matrix is a single column
	//we tally the total number of 1s and return
        else if(COL==1){
            int acc=0;
            for(int i=0; i<ROW; ++i)
                acc+=matrix[i][COL-1];
            return acc;
        }

        //the case where the matrix has 2 or more rows and matrices

        //largestSquare will store the dimensions of the largest square matrix of 1s that can be generated with entry (i,j) as 
        //the upper left corner.
        //this will help us calculate the total number of square matrices of 1s that are generated when a new entry of 1
        //creates a square matrix of 1s and the entry is the upper left corner of the created square submatrices
        std::vector<std::vector<int>> largestSquare(ROW, std::vector<int>(COL,0)), f(ROW, std::vector<int>(COL,0));

        short i,j; //row and column indices

        //we initialize the matrix f by copying the lower right corner of matrix
        f[ROW-1][COL-1] = matrix[ROW-1][COL-1];

        //we make the last row and column of f be the accumulated number of 1s 
        for(j=COL-2; j>-1; --j)
            f[ROW-1][j] = matrix[ROW-1][j] + f[ROW-1][j+1];
        for(i=ROW-2; i>-1; --i)
            f[i][COL-1] = matrix[i][COL-1] + f[i+1][COL-1];

	//now we calculate all the remaining entries working backwards starting from the oenultimate row and upwards
        for(i=ROW-2; i>-1; --i){
        	//this loop calculates the entries backwards from the penultimate column until the first 
            for(j=COL-2; j>-1; --j){
            	//the current entry will be the sum of the total number of submatrices of 1s for the submatrix matrix[i+1:][j:]
            	//plus the total number of submatrices of 1s for the submatrix matrix[i:][j+1:], minus the duplicate counted 
            	//submatrices of 1s of submatrix matrix[i+1:][j+1:], plus 1 if the current entry is a 1
                f[i][j] = f[i+1][j] + f[i][j+1] - f[i+1][j+1] + matrix[i][j];

                //we check the case where the current, right, bottom and diagonally lower entries are all 1s
                //to see how many submatrices of 1s have been created with the current entry as the upper left corner
                if(matrix[i][j] * matrix[i+1][j] * matrix[i][j+1] * matrix[i+1][j+1] == 1){
                	//the largest possible submatrix of 1s with the current entry as the upper left corner will be 1 more than the
                	//minimum largestSquare entry among the left, bottom and diagonally lower entries of largestSquare
                    largestSquare[i][j] = 1 + std::min(largestSquare[i+1][j+1],std::min(largestSquare[i][j+1],largestSquare[i+1][j]));
                    f[i][j] += largestSquare[i][j];
                }

            }
        }

        return f[0][0]; //the upper left corner in f will store all the possible submatrices of 1s in matrix
    
    }




int main(){
	std::vector<std::vector<int>> matrix{{{1,1,1},{1,1,1},{0,1,1}}};
	std::cout<<countSquares(matrix)<<"\n";

	return 0;
}
