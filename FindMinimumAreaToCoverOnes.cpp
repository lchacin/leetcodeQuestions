/*

3195. Find the Minimum Area to Cover All Ones I

You are given a 2D binary array grid. Find a rectangle with horizontal and vertical 
sides with the smallest area, such that all the 1's in grid lie inside this rectangle.

Return the minimum possible area of the rectangle.

Constraints:

1 <= grid.length, grid[i].length <= 1000
grid[i][j] is either 0 or 1.
The input is generated such that there is at least one 1 in grid.


*/


#include<iostream>
#include<vector>


int minimumArea(std::vector<std::vector<bool>>& grid) {
        int xMin=-1, xMax=-1, yMin=-1, yMax=-1;

        int row, col;
        bool done=false;

        //we find the first set bit 
        for(row=0; row<grid.size() && !done; ++row){
            for(col=0; col<grid[0].size() && !done; ++col){
                if(grid[row][col]){
                    xMin=col; xMax = col;
                    yMin=row; yMax = row;
                    done=true;
                }
            }
        }
        --row; //to undo the row increment at the end of the outer for loop

        //now we look for other bits
        for(;row<grid.size(); ++row){
            for(;col<grid[0].size(); ++col){
                if(grid[row][col]){
                    //if the column index is less than the current xMin we update xMin
                    if(col < xMin) xMin = col;
                    //if the column index is more than the current xMax we update xMax
                    else if(col > xMax) xMax=col;

                    //similarily we check for updates for yMin and yMax
                    if(row < yMin) yMin=row;
                    else if(row > yMax) yMax = row;
                }
            }
            col = 0; //once we are done with the current row we reset the column index to 0 again
                    //to start traversing the next row
        }


        return (xMax-xMin+1)*(yMax-yMin+1);
    }



int main(){
	std::vector<std::vector<bool>> grid {{0,0,0,0,0,0},{0,1,1,0,1,0},{1,0,0,1,0,0},{1,0,1,0,0,0},{0,0,0,0,0,0}};

	std::cout << "Minimum area to cover all 1s: " << minimumArea(grid) << "\n";

	return 0;
}
