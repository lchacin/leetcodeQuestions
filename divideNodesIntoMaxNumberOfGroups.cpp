/*

Divide Nodes Into the Maximum Number of Groups


You are given a positive integer n representing the number of nodes in an undirected graph. The nodes are labeled from 1 to n.

You are also given a 2D integer array edges, where edges[i] = [ai, bi] indicates that there is a bidirectional edge between nodes ai and bi. Notice that the given graph may be disconnected.

Divide the nodes of the graph into m groups (1-indexed) such that:

Each node in the graph belongs to exactly one group.
For every pair of nodes in the graph that are connected by an edge [ai, bi], if ai belongs to the group with index x, and bi belongs to the group with index y, then |y - x| = 1.
Return the maximum number of groups (i.e., maximum m) into which you can divide the nodes. Return -1 if it is impossible to group the nodes with the given conditions.



Constraints:

1 <= n <= 500
1 <= edges.length <= 104
edges[i].length == 2
1 <= ai, bi <= n
ai != bi
There is at most one edge between any pair of vertices.



*/


#include<iostream>
#include<vector>
#include<stack>
#include<queue>



//detectOddCycle uses dfs to explore the graph. If we encounter a vertex
    //that had already been explored during dfs, then we found a cycle
    bool detectOddCycle(int root, std::vector<std::vector<int>>& adjList, std::vector<bool>& visited, std::vector<std::vector<int>>& components){
        //create a vector that keeps tracks of each vertices distance from
        //source vertex
        std::vector<int> distanceFromRoot(adjList.size(), -1);
        distanceFromRoot[root] = 0;
        
        //stack to perform dfs
        std::stack<int> dfsStack;
        dfsStack.push(root);
        int currentVertex = root;

        //this vector will store all the vertices encountered during dfs
        std::vector<int> singleComponent;

        while(!dfsStack.empty()){
            currentVertex = dfsStack.top();
            dfsStack.pop();
            visited[currentVertex] = true;
            singleComponent.push_back(currentVertex);

            for(auto& neighbor: adjList[currentVertex]){
                if(distanceFromRoot[neighbor]==-1){
                    distanceFromRoot[neighbor] = distanceFromRoot[currentVertex]+1;
                    dfsStack.push(neighbor);
                }

                //we detect an odd cycle, return true
                else if((distanceFromRoot[currentVertex]-distanceFromRoot[neighbor]+1)%2==1)
                    return true;
            }
        }

        //we add the vector of vertices encountered to the componenets list if lists
        //passed by reference to the function
        components.push_back(singleComponent);

        return false;
    }

    //enumerated Colors data type to perform bfs
    enum Colors{ black, grey, white};


    //bfsNumberOfGroups calculate the number of groups created if we run bfs from a
    //given source vertex
    int bfsNumberOfGroups(int root, std::vector<std::vector<int>>& adjList){
        int numberOfGroups; //to store the number of groups
        std::queue<std::pair<int, int>> bfsQueue;   //to perform bfs 

        //we append to each vertex value an integer representing its group value
        std::pair<int,int> currentVertex;

        //an vector that stores the color value of each vertex during bfs
        //it will tell us what vertices have already been visited, which ones
        //are in the bfs queue and which ones haven't been visited
        std::vector<Colors> visited(adjList.size(), Colors::white);

        //push the source vertex into the bfs queue with its group number being 1
        bfsQueue.push({root, 1});

        //set the source vertex to grey color since it is now in the queue
        visited[root] = Colors::grey;

        while(!bfsQueue.empty()){
            //remove the vertex at the front of the list
            currentVertex = bfsQueue.front();
            bfsQueue.pop();

            //we update the number of groups to be the group value of the last
            //vertex removed from the queue
            numberOfGroups = currentVertex.second;
            visited[currentVertex.first]=Colors::black;

            //add all its white neighbors to the queue with the group value being
            //one more than the current vertex
            for(auto& neighbor: adjList[currentVertex.first]){
                if(visited[neighbor]==Colors::white){
                    bfsQueue.push({neighbor, currentVertex.second+1});
                    visited[neighbor]=Colors::grey;
                }
            }
        }

        //return the number of groups generated
        return numberOfGroups;
    }





    int magnificentSets(int n, std::vector<std::vector<int>>& edges) {
        //create an adjacency list
        std::vector<std::vector<int>> adjList(n);
        for(auto& edge: edges){
            adjList[edge[0]-1].push_back(edge[1]-1);
            adjList[edge[1]-1].push_back(edge[0]-1);
        }
        
        //first we determine if there is an odd length cycle in
        //the graph using dfs. If so, we return -1

        //visited is boolean vector where true means the vertex was visited and false       
        //otherwise during a round of dfs
        std::vector<bool> visited(n, false);

        //each time we run dfs from an unvisited vertex, we store the visited vertices in
        //vector, and then this vector will be a connected component stored in componenets
        std::vector<std::vector<int>> components;

        for(int i=0; i<n; ++i){
            if(visited[i]==false){
                if(detectOddCycle(i, adjList, visited, components))
                    return -1;
            }
        }

        //if we reach this point, then our graph has no odd cycles
        //so we'll have a solution to the problem

        //visited will be fully false since all vertices where visited on 
        //different rounds of dfs and components will store lists of vertices
        //where each list represents an individual connected component



        //we run bfs for each vertex of each component of the graph
        //and count the number of groups we can create

        int result = 0, tempResult, tempNGroups;


        //we iterate over each component
        for(auto& component: components){
            //if the componenet is a singleton we just increase results by 1
            if(component.size()==1) result+=1;
            else{
                //we run bfs from each vertex in the componenent and store the 
                //the one that generated the largest number of groups
                tempResult=0;
                tempNGroups=0;
                for(auto& vertex: component){
                    tempNGroups = bfsNumberOfGroups(vertex, adjList);
                    if(tempNGroups > tempResult) tempResult = tempNGroups;
                }

                //update results with the largest number of groups generated 
                //for the given component
                result += tempResult;
            }
        }

        return result;
    }




int main(){
	int n=6;

	std::vector<std::vector<int>> edges{{1,2},{1,4},{1,5},{2,6},{2,3},{4,6}};

	std::cout << magnificentSets(n, edges) << "\n";

	return 0;
}
