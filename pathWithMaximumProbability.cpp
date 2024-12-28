/*

1514. Path with Maximum Probability

You are given an undirected weighted graph of n nodes (0-indexed), 
represented by an edge list where edges[i] = [a, b] is an undirected edge 
connecting the nodes a and b with a probability of success of traversing that edge succProb[i].

Given two nodes start and end, find the path with the maximum probability of success to go 
from start to end and return its success probability.

If there is no path from start to end, return 0. 
Your answer will be accepted if it differs from the correct answer by at most 1e-5.


Constraints:

2 <= n <= 10^4
0 <= start, end < n
start != end
0 <= a, b < n
a != b
0 <= succProb.length == edges.length <= 2*10^4
0 <= succProb[i] <= 1
There is at most one edge between every two nodes.


*/



#include<iostream>
#include<queue>		//for std::priority_queue
#include<vector>	//for std::vector


std::vector<double> modified_dijkstra(int nVertices, int source, std::vector<std::vector<int>>& edges, std::vector<double>& probs, std::vector<std::vector<std::pair<int, double>>>& adjacency_matrix){

        //we initialize a vector where each index corresponds to the max
        //probability of reaching a vertex from the source
        std::vector<double> maxReachProbabilities(nVertices, 0.0);

        //set the source to have probability of reach of 1
        maxReachProbabilities[source] = 1.0; 

        //comparator binary function for the priority queue
        //it will return true if the first pair comes before the second pair. By before, we mean
        //that the vertex in the pair has a lower probability being reached.
        auto probComparator = [](std::pair<int, double>& v1, std::pair<int,double>& v2)->bool{ return v1.second < v2.second;};

        //priority queue to store pairs composed of a vertex index and the probability of reaching it
        //from the source
        std::priority_queue<std::pair<int, double>, std::vector<std::pair<int,double>>, decltype(probComparator)> priorityQueue;

        //to store the node chosen from the top of the priority queue
        std::pair<int,double> currentNode{source, maxReachProbabilities[source]};
        priorityQueue.push(currentNode);

        //a boolean vector to keep track of what vertices have already been added to the 
        //dijkstra shortest path tree
        std::vector<bool> visited(nVertices, false);


        int i;
        double product;
        

        while(!priorityQueue.empty()){
            currentNode = priorityQueue.top();
            priorityQueue.pop();

            if(visited[currentNode.first]) continue;

            //now we relax all the edges incident to the current node
            for(auto& neighbor: adjacency_matrix[currentNode.first]){
                //we check if the right-end vertex is not yet in the shortest-path tree
                    if(!visited[neighbor.first]){
                        //if so, we relax the edge by updating the right-end's probability if it is larger
                        //reaching it via the current node
                        //and we add the right-end node with it sprobability to the priority queue
                        product = maxReachProbabilities[currentNode.first] * neighbor.second;
                        if(maxReachProbabilities[neighbor.first] < product){
                                maxReachProbabilities[neighbor.first] = product;
                                priorityQueue.push({neighbor.first, product});
                        }
                    }
                }

            //once we relax all the edges we add the current node to the shortest-path tree
            visited[currentNode.first] = true;

        }


        //out of the while loop, we are done with dijkstra. We return the vector of maximum probability paths
        //of reaching a given vertex from the source

        return maxReachProbabilities;

    }

    double maxProbability(int n, std::vector<std::vector<int>>& edges, std::vector<double>& succProb, int start_node, int end_node) {


        //create the adjancency matrix woth probabilities
        std::vector<std::vector<std::pair<int,double>>> adjacency_matrix(n);
        for(int i=0; i<edges.size(); ++i){
            adjacency_matrix[edges[i][0]].push_back({edges[i][1], succProb[i]});
            adjacency_matrix[edges[i][1]].push_back({edges[i][0], succProb[i]});
        }
        

        auto maxReachProbabilities = modified_dijkstra(n, start_node, edges, succProb, adjacency_matrix);

        return maxReachProbabilities[end_node];
    }


int main(){
	int n=3;
	std::vector<std::vector<int>> edges{{0,1},{1,2},{0,2}};
	std::vector<double> succProb = {0.5,0.5,0.3};
	int start_node = 0, end_node = 2;

	std::cout << maxProbability(n, edges, succProb, start_node, end_node) << "\n";

	return 0;
}
