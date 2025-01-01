/*

886. Possible Bipartition

We want to split a group of n people (labeled from 1 to n) into two groups of any size. 
Each person may dislike some other people, and they should not go into the same group.

Given the integer n and the array dislikes where dislikes[i] = [ai, bi] indicates that the 
person labeled ai does not like the person labeled bi, return true if it is possible to split 
everyone into two groups in this way.


Constraints:

1 <= n <= 2000
0 <= dislikes.length <= 104
dislikes[i].length == 2
1 <= ai < bi <= n
All the pairs of dislikes are unique.



*/




#include<iostream>
#include<vector>
#include<stack>


enum Colors{Black, Red, Blue};

    bool possibleBipartition(int n, std::vector<std::vector<int>>& dislikes) {
        //we create an adjacency 2D ragged array
        std::vector<std::vector<int>> adjacency_matrix(n);
        for(auto& e: dislikes){
            adjacency_matrix[e[0]-1].push_back(e[1]-1);
            adjacency_matrix[e[1]-1].push_back(e[0]-1);
        }


        //now we perform dfs on the graph and color the vertices red or blue
        //to determine if the graph is bipartite or not

        //visited array to keep track what vertices have been visited in dfs
        std::vector<int> visited(n, false);

        //array to keep track of the colors of each of the vertices
        std::vector<Colors> vertexColors(n, Colors::Black);

        //stack to store the vertices of the graph during dfs
        std::stack<int> dfsStack;

        int currentVertex;      //to store the current vertex being worked on in dfs
        int visitedCount = 0;   //to store the total number of vertices visited
        int i;                  //loop variable

        while(visitedCount < n){
            //we find a vertex not yet visited to perform dfs from
            currentVertex = -1;
            for(i=0; i<n; ++i){
                //vertex i has not been visisted. We make it the root of dfs and break
                if(!visited[i]){
                    currentVertex = i;
                    break;
                }
            }

            //now we perform dfs from currentVertex
            dfsStack.push(currentVertex);               //push currentVertex into the stack
            vertexColors[currentVertex] = Colors::Red;  //color the vertex red

            while(!dfsStack.empty()){
                currentVertex = dfsStack.top();
                dfsStack.pop();

                //mark the vertex chosen as visited and update the visitedCount
                visited[currentVertex] = true;
                ++visitedCount;

                for(i=0; i<adjacency_matrix[currentVertex].size(); ++i){

                    //we check if the adjacent vertex has the same color
                    if(vertexColors[adjacency_matrix[currentVertex][i]] == vertexColors[currentVertex])
                            return false;   //if so then graph is not bipartite
                        
                    //if the adjacent vertex has not been visited we give it the opposite
                    //color to the current vertex and add it to the stack
                    else if(!visited[adjacency_matrix[currentVertex][i]]){
                        vertexColors[adjacency_matrix[currentVertex][i]] = (vertexColors[currentVertex]==Colors::Red)?(Colors::Blue):(Colors::Red);
                        dfsStack.push(adjacency_matrix[currentVertex][i]);
                    }

                    //if the adjacent vertex was already visited then we skip it
                }
                
            }
        }

        return true;

    }



int main(){
	int n =4;
	std::vector<std::vector<int>>  dislikes = {{1,2}, {2,3}, {3,4}, {2,4}};

	std::cout << std::boolalpha << possibleBipartition(n, dislikes) << "\n";

	return 0;

}
