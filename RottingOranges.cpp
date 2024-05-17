/*

994. Rotting Oranges


You are given an m x n grid where each cell can have one of three values:

0 representing an empty cell,
1 representing a fresh orange, or
2 representing a rotten orange.
Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.

Return the minimum number of minutes that must elapse until no cell has a fresh orange. 
If this is impossible, return -1.


Constraints:
m == grid.length
n == grid[i].length
1 <= m, n <= 10
grid[i][j] is 0, 1, or 2.


Approach:

We need to locate the rotting oranges in the grid. From each orange we perfrom BFS which will simulate
neighboring fresh oranges rotting due to contact with rotten oranges. Each BFS will have its own queue
with neighboring fresh oranges added to it. One round of iterations of each BFS will constitute an elapsed minute
and therefore the total number of minutes until no fresh oranges are left equal the number of iterations
taken by the last BFS process to finish.

At the end we check to see if the there are any fresh oranges left in the grid. This can happen in the case
a fresh orange exists that is not reachable from a rotten orange, i.e. a fresh orange that lives in a tree
disconnected from the all of the BFS trees.  



*/


#include<iostream>
#include<vector>
#include<queue> //for std::queue
#include<algorithm> //for std::find


//orangeRotting recieves a reference to an integer matrix of 0s, 1s and 2s representing an empty space, 
//a fresh orange and rotten orange correspondingly and returns an integer representing the number of minutes
//required for the grid to be free from fresh oranges/
int orangesRotting(std::vector<std::vector<int>>& grid) {
        //the case where the grid is only one node
        if(grid.size()==1 && grid[0].size()==1){
            //if the node has a fresh orange than it will never become rotten
            if(grid[0][0]==1) return -1; 

            //this case where there is a rotten orange or no orange
            return 0;
        }

        short row,col, nRows=grid.size(), nCols = grid[0].size();
        std::vector<std::queue<std::pair<short,short>>> bfsQueues;




        //first we locate the positions of the 2s and add them to bfsStartingLocations
        //we also change color of the 0s location to black and 2s location to grey
        for(row=0; row<nRows; ++row){
            for(col=0; col<nCols; ++col){
                if(grid[row][col] == 2)
                    bfsQueues.emplace_back(std::queue<std::pair<short,short>>({{row,col},{-1,-1}}));
            }
        }

        //record the number of bfs queues created
        short nBFS = bfsQueues.size(), currentBFS;
        std::vector<bool> activeQueues(nBFS,true); //each bit represents the status of one of the bfs being performed.      1:=active, 0:=inactive
        
        std::pair<short,short> currentNode; //to store the current node in the grid being worked on
        short totalMinutes = 0; //to record the maximum number of bfs iterations out of all the bfs
                                //until no more fresh oranges are encountered
        bool flag; //flag is used to signal that a fresh orange was encountered

        //while that performs bfs from all the starting rotten oranges. The while loop stops
        //when there are no active queues remaining
        while(std::find(activeQueues.begin(), activeQueues.end(), true) != activeQueues.end()){
            flag=false;

            //we itreate over all the bfs queues and continue performing bfs the active queues
            for(currentBFS=0; currentBFS<nBFS; ++currentBFS){
                //if the queue is inactive we continue to the next queue
                if(activeQueues[currentBFS]==false) continue;

                //this whie loop iterates over the nodes in the current bfs queue until the dummy node {-1,-1}
                //is reached which will break the loop from inside
                while(true){

                    //obtain the node in the fronit of the queue and remove it
                    currentNode = bfsQueues[currentBFS].front();
                    bfsQueues[currentBFS].pop();

                    //we reach the dummy node inidicating the end of the list of all the nodes from a previous bfs cycle
                    //we add another dummy {-1,-1} to indicate the end of the current bfs cycle and break to go
                    //to another bfs taking place
                    if(currentNode.first==-1){
                        bfsQueues[currentBFS].push({-1,-1});
                        break;
                    }

                    //case of where the grid has multiple rows and columns
                    //for each node we check the nodes above, below, left and right to see if any of them
                    //is a fresh orange. If so, we add the node to the queue and change the grid value
                    //from 1 to 2 to signal that the current fresh orange is now rotten
                    if(grid[0].size()!=1 && grid.size()!=0){
                        if(currentNode.first!=0 && grid[currentNode.first-1][currentNode.second]==1){
                            bfsQueues[currentBFS].push({currentNode.first-1, currentNode.second});
                            grid[currentNode.first-1][currentNode.second]=2;
                            flag=true;
                        }
                        if(currentNode.second!=0 && grid[currentNode.first][currentNode.second-1]==1){
                            bfsQueues[currentBFS].push({currentNode.first, currentNode.second-1});
                            grid[currentNode.first][currentNode.second-1]=2;
                            flag=true;
                        }
                        if(currentNode.second!=nCols-1 && grid[currentNode.first][currentNode.second+1]==1){
                            bfsQueues[currentBFS].push({currentNode.first, currentNode.second+1});
                            grid[currentNode.first][currentNode.second+1]=2;
                            flag=true;
                        }
                        if(currentNode.first!=nRows-1 && grid[currentNode.first+1][currentNode.second]==1){
                            bfsQueues[currentBFS].push({currentNode.first+1, currentNode.second});
                            grid[currentNode.first+1][currentNode.second] = 2;
                            flag=true;
                        }
                    }


                    //case when the grid has only one row
                    else if(grid.size()==1){
                        if(currentNode.second!=nCols-1 && grid[currentNode.first][currentNode.second+1]==1){
                            bfsQueues[currentBFS].push({currentNode.first,currentNode.second+1});
                            grid[currentNode.first][currentNode.second+1]=2;
                            flag=true;
                        }
                        if(currentNode.second!=0 && grid[currentNode.first][currentNode.second-1]==1){
                            bfsQueues[currentBFS].push({currentNode.first, currentNode.second-1});
                            grid[currentNode.first][currentNode.second-1]=2;
                            flag=true;
                        }
                    }

                    //case when the grid has only one column
                    else if(grid[0].size()==1){
                        if(currentNode.first!=0 && grid[currentNode.first-1][currentNode.second]==1){
                            bfsQueues[currentBFS].push({currentNode.first-1, currentNode.second});
                            grid[currentNode.first-1][currentNode.second]=2;
                            flag=true;
                        }
                        if(currentNode.first!=nRows-1 && grid[currentNode.first+1][currentNode.second]==1){
                            bfsQueues[currentBFS].push({currentNode.first+1, currentNode.second});
                            grid[currentNode.first+1][currentNode.second]=2;
                            flag=true;
                        }
                    }
                    
                }
                //out of the while loop we are done with a round of bfs for the current bfs queue

                //if the current queue is has only a dummy node it means this bfs is over
                //so we label it as innactive in the vector<bool>
                if(bfsQueues[currentBFS].size()==1) activeQueues[currentBFS]=false;
            }
            //out of the for loop we have performed a round of bfs for all the bfs queues

            //after performing a round of bfs for all the bfs taking place
            //we increase the number of minutes by one if a fresh orange was encountered
            if(flag) ++totalMinutes;
        }
        
        //at the end of all the bfs, we check if there is any fresh orange left in the grid
        //this happened if the fresh orange was located in a tree disconnected from the trees
        //containing rotten oranges
        for(row=0; row<nRows; ++row){
            for(col=0; col<nCols; ++col){
                if(grid[row][col]==1)
                    return -1;
            }
        }

        return totalMinutes;

    }




int main(){
	std::vector<std::vector<int>> map{{2,1,1},{1,1,0},{0,1,1}};
	std::cout<<"Number of minutes for the map to be free of fresh orange: "<<orangesRotting(map)<<"\n";


	return 0;

}
