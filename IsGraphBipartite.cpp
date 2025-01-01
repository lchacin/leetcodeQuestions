/*


785. Is Graph Bipartite?

There is an undirected graph with n nodes, where each node is numbered between 0 and n - 1. 
You are given a 2D array graph, where graph[u] is an array of nodes that node u is adjacent to. 
More formally, for each v in graph[u], there is an undirected edge between node u and node v. 
The graph has the following properties:

There are no self-edges (graph[u] does not contain u).
There are no parallel edges (graph[u] does not contain duplicate values).
If v is in graph[u], then u is in graph[v] (the graph is undirected).
The graph may not be connected, meaning there may be two nodes u and v such that there is no path between them.
A graph is bipartite if the nodes can be partitioned into two independent sets A and B such 
that every edge in the graph connects a node in set A and a node in set B.

Return true if and only if it is bipartite.


Constraints:

graph.length == n
1 <= n <= 100
0 <= graph[u].length < n
0 <= graph[u][i] <= n - 1
graph[u] does not contain u.
All the values of graph[u] are unique.
If graph[u] contains v, then graph[v] contains u.



*/



#include<iostream>
#include<vector>
#include<stack>


//colors for the vertices of the graph
    enum Color{Black, Red, Blue};

    bool isBipartite(std::vector<std::vector<int>>& graph) {
        //constant integer for the number of vertices in the graph
        const int NUM_VERTICES = graph.size();

        //this array will keep track of the color of the vertices
        std::vector<Color> vertexColors(NUM_VERTICES, Black);

        //visited array for DFS
        std::vector<bool> visited(NUM_VERTICES, false);

        //stack to run dfs
        std::stack<int> dfsStack;

        //to keep track of the number of vertices visited
        int visitedCount = 0;

        //to keep track of the current vertex being worked on
        //and loop index
        int currentVertex, i;

        while(visitedCount < NUM_VERTICES){
            currentVertex = -1;

            //we look a vertex not yet visited
            for(i = 0; i<NUM_VERTICES; ++i){
                //case we find a vertex not visisted
                if(!visited[i]){
                    //we let this vertex be the current vertex and break
                    //to perform dfs using it as the root
                    currentVertex = i;
                    break;
                }
            }

            //if currentvVertex is still -1 it means all the vertices have
            //been visited
            if(currentVertex == -1) break;

            //we set the color of the initial vertex as Red and push it in the stack
            vertexColors[currentVertex] = Color::Red;
            dfsStack.push(currentVertex);

            while(!dfsStack.empty()){
                currentVertex = dfsStack.top();
                dfsStack.pop();

                //if the vertex has alreadu been visited we move on 
                //to the next vertex in the stack by looping again
                if(visited[currentVertex]) continue;

                //if the vertex has not been visited, we mark it as such
                //and update the visited vertices count
                visited[currentVertex] = true;
                ++visitedCount;

                for(auto& v: graph[currentVertex]){
                    //we check if both adjacent vertices have the same color
                    //if so then the graph can't be bipartite and we return false
                    if(vertexColors[v] == vertexColors[currentVertex])
                        return false;
                    else if(!visited[v]){
                        dfsStack.push(v);
                        vertexColors[v] = (vertexColors[currentVertex]==Color::Red)?Color::Blue:Color::Red;
                    }
                }
            }
        }

        return true;
    }




int main(){
	std::vector<std::vector<int>> graph{{},{2,4,6},{1,4,8,9},{7,8},{1,2,8,9},{6,9},{1,5,7,8,9},{3,6,9},{2,3,4,6,9},{2,4,5,6,7,8}};

	std::cout << std::boolalpha << isBipartite(graph) << "\n";

	return 0; 
}

