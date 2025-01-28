/*
Maximum Number of Fish in a Grid

You are given a 0-indexed 2D matrix grid of size m x n, where (r, c) represents:

A land cell if grid[r][c] = 0, or
A water cell containing grid[r][c] fish, if grid[r][c] > 0.
A fisher can start at any water cell (r, c) and can do the following operations any number of times:

Catch all the fish at cell (r, c), or
Move to any adjacent water cell.
Return the maximum number of fish the fisher can catch if he 
chooses his starting cell optimally, or 0 if no water cell exists.

An adjacent cell of the cell (r, c), is one of the cells (r, c + 1), (r, c - 1), (r + 1, c) or (r - 1, c) if it exists.


Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 10
0 <= grid[i][j] <= 10

*/


#include<iostream>
#include<vector>
#include<stack>


int findMaxFish(std::vector<std::vector<int>>& grid) {
        //nxm 2D array that tells is a fishing location has already been explored
        std::vector<std::vector<bool>> visited(grid.size(), std::vector<bool>(grid[0].size(), false));

        int i,j; //looping variables
        const int nRow = grid.size(), nCol = grid[0].size();


        std::stack<std::pair<int,int>> dfsStack; //stack to perform dfs
        std::pair<int,int> currentLocation;      //pair to store the current location in dfs

        int maxFish = 0, currentFish;   //to store the running fish count and the max number of fish

        for(i=0; i<nRow; ++i){
            for(j=0; j<nCol; ++j){
                //we check if the location (i,j) has already been explored or if it is land
                if(visited[i][j] || grid[i][j]==0) continue;

                //perform dfs and add the number of fish  explored
                currentFish=0;
                dfsStack.push({i,j});

                while(!dfsStack.empty()){
                    currentLocation = dfsStack.top();
                    dfsStack.pop();
                    if(!visited[currentLocation.first][currentLocation.second])
                        visited[currentLocation.first][currentLocation.second]= true;
                    else continue;
                    
                    currentFish+=grid[currentLocation.first][currentLocation.second];

                    //check square above
                    if(currentLocation.first!=0 && grid[currentLocation.first-1][currentLocation.second]!=0 && !visited[currentLocation.first-1][currentLocation.second])
                        dfsStack.push({currentLocation.first-1, currentLocation.second});

                    //check square below
                    if(currentLocation.first!=nRow-1 && grid[currentLocation.first+1][currentLocation.second]!=0 && !visited[currentLocation.first+1][currentLocation.second])
                        dfsStack.push({currentLocation.first+1, currentLocation.second});
                    
                    //check square to the left
                    if(currentLocation.second!=0 && grid[currentLocation.first][currentLocation.second-1]!=0 && !visited[currentLocation.first][currentLocation.second-1])
                        dfsStack.push({currentLocation.first, currentLocation.second-1});
                    
                    //check square to the right
                    if(currentLocation.second!=nCol-1 && grid[currentLocation.first][currentLocation.second+1]!=0 && !visited[currentLocation.first][currentLocation.second+1])
                        dfsStack.push({currentLocation.first, currentLocation.second+1});
                }

                //if the fish in currentFish is more than maximum number of fish so far captured
                //in previous dfs runs, we update the maximum number of fish
                if(currentFish > maxFish) maxFish=currentFish;

            }
        }

        return maxFish;

    }




int main(){

	std::vector<std::vector<int>> grid{
		{9, 1, 1, 6, 9, 7, 9, 1, 10, 8}, 
		{2, 5, 6, 1, 3, 5, 9, 7, 10, 10}, 
		{9, 2, 2, 9, 5, 0, 8, 2, 10, 0}, 
		{9, 2, 6, 3, 10, 2, 0, 9, 0, 7}, 
		{10, 3, 7, 10, 5, 3, 5, 9, 3, 9}, 
		{10, 2, 9, 7, 8, 5, 10, 8, 5, 4}, 
		{6, 3, 5, 5, 7, 2, 8, 8, 1, 0}, 
		{5, 7, 3, 8, 6, 9, 9, 8, 10, 2}
	};

	std::cout << findMaxFish(grid) << "\n";

	return 0;


}
