#include<iostream>
#include<vector>
#include<cmath>


int maximalSquare(std::vector<std::vector<char>>& matrix) {
        int runningMax = 0;
        int x;
        int nRows=matrix.size(), nCols=matrix[0].size();
        std::vector<std::vector<int>> f(nRows, std::vector<int>(nCols,0));
        
        for(int i=0; i<nRows; ++i){
            f[i][0] = matrix[i][0]-48;
            if(f[i][0] > runningMax) runningMax = f[i][0];
        }
        for(int j=0; j<nCols; ++j){
            f[0][j] = matrix[0][j]-48;
            if(f[0][j] > runningMax) runningMax = f[0][j];
        }

        for(int i=1; i<nRows; ++i){
            for(int j=1; j<nCols; ++j){
                if(matrix[i][j]-48 == 0) f[i][j] = 0;
                else if(std::min(std::min(f[i-1][j],f[i][j-1]), f[i-1][j-1]) == 0){
                    f[i][j] = 1;
                    if(f[i][j] > runningMax) runningMax = 1;
                }
                else{
                    x = std::min(f[i-1][j-1], std::min(f[i-1][j], f[i][j-1]));
                    x = std::sqrt(x);
                    f[i][j] = (x+1)*(x+1);
                    if(f[i][j] > runningMax) runningMax = f[i][j];
                }
            }
        }

        return runningMax;

        
    }



int main(){
	std::vector<std::vector<char>> matrix{{'1','0','1','0','0'},{'1','0','1','1','1'},{'1','1','1','1','1'},{'1','0','0','1','0'}};

	std::cout << maximalSquare(matrix) << "\n";

	return 0;
}
