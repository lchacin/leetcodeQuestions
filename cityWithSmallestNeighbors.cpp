/*

1334. Find the City With the Smallest Number of Neighbors at a Threshold Distance

There are n cities numbered from 0 to n-1. Given the array edges where edges[i] = [fromi, toi, weighti] represents 
a bidirectional and weighted edge between cities from_i and to_i, and given the integer distanceThreshold.

Return the city with the smallest number of cities that are reachable through some 
path and whose distance is at most distanceThreshold, If there are multiple such cities, 
return the city with the greatest number.

Notice that the distance of a path connecting cities i and j is equal to the sum of the edges' 
weights along that path.


Constraints:

2 <= n <= 100
1 <= edges.length <= n * (n - 1) / 2
edges[i].length == 3
0 <= fromi < toi < n
1 <= weighti, distanceThreshold <= 10^4
All pairs (fromi, toi) are distinct.


*/

#include<iostream>
#include<vector>	//for std::vector
#include<algorithm> 	//for std::count_if
#include<queue> 	//for std::priority_queue

//we create a comparator function for the priority queue in dijsktra
    //it compares two integer pairs where the first components is the 
    //current smallest weight of a path to reach the second component vertex
    //from the source vertex
    //it returns true if the second pair has a smaller weight than the first
    //this will generate a min heap where pairs with lighter paths have higher
    //priority
    static constexpr auto myComp = [](std::pair<int,int> x, std::pair<int,int> y)->bool{ return x.first > y.first;};

    int dijkstra(int& source, int& nVertices, const std::vector<std::vector<int>>& edges, const int& distanceThreshold ){

        //priority queue to store pairs of integers with the weight of the path
        //from the source to a given vertex, and the second component is the vertex
        //it is a min heap so the vertices with the lightest paths are at the top
        std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, decltype(myComp)> minHeap;

        //the stl priority queue doesn;t provide the functionality of updating
        //priority values once an element is stored in the queue.
        //Since the weight of the shortest path to a given vertex can change
        //multiple times while the vertex is still in the queue due to edge
        //relaxations, we need a way of updating the weights.
        //The visited vector stores true/false if a vertex has already been
        //added to the shortest path tree created by dijkstra.
        std::vector<int> visited(nVertices, false);

        //stores the weights of the shortest paths from the source to each vertex
        std::vector<int> d(nVertices, distanceThreshold+1);

        //initialize the weight of the path to the source vertex as zero
        d[source] = 0;

        //push the pair of the weight of the path to the source vertex and the
        //source vertex number to the priority queue
        minHeap.push({d[source],source});

        //std::pair to store the current vertex being worked on
        std::pair<int,int> currentVertex = minHeap.top();

        //we continue building the dijkstra shortest path tree until there are no
        //more vertices in the priority queue
        while(!minHeap.empty()){
            //remove the top of the priority queue
            minHeap.pop();

            //we relax all the edges that are incident to the current vertex
            for(auto& e: edges){

                //left vertex is the current vertex
                if(e[0] == currentVertex.second){
                    //we update the weight of the shortest path to the vertices adjacent to the current vertex 
                    //if the current weight of the adjacent vertex stored is more than the weight of the
                    //current vertex plus the weight of the edge connecting it to the adjacent vertex
                    //we also check that the path is not more than distanceThreshold
                    if(d[e[1]] > d[currentVertex.second] + e[2] && d[currentVertex.second] + e[2] <= distanceThreshold){
                        //we updat the weight of the shortest path to the adjacent vertex and 
                        //add it to the priority queue
                        d[e[1]] = d[currentVertex.second] + e[2];
                        minHeap.push({d[e[1]], e[1]});
                    }
                }

                //right end is the current vertex
                //same procedure as above but the current vertex is the right end of the edge
                else if(e[1] == currentVertex.second){
                    if(d[e[0]] > d[currentVertex.second] + e[2] && d[currentVertex.second] + e[2] <= distanceThreshold){
                        d[e[0]] = d[currentVertex.second] + e[2];
                        minHeap.push({d[e[0]], e[0]});
                    }
                }
            }

            //once done relxaing all edges incident to the current vertex we mark it as visited
            //so that if we encounter it again in the prioiry queue we can tell it has already 
            //been added to the shortest path tree and hence we should skip it.
            visited[currentVertex.second] = true;

            //we select the vertex with the shortest path from the source not yet 
            //in the shortest path tree.
            while(!minHeap.empty() && visited[currentVertex.second]){
                currentVertex = minHeap.top();
                if(visited[currentVertex.second]) minHeap.pop();
            }
        }

        //at this instance d stores the distance from the source to all the vertices with a distance
        //at or below the threshold. We count how many vertices were reachable and return the total
        return std::count_if(d.begin(), d.end(), [&distanceThreshold](int& x)->bool{return x!=0 && x!=distanceThreshold+1;});

    }

    int findTheCity(int& n, std::vector<std::vector<int>>& edges, int& distanceThreshold) {
        int minCities=n; //to store the minimum number of reachable cities from a given city
        int connectedCities; //to store the number of connnected cities outputted by dijsktra
        int winningCity = 0; //to store the city with the least number of adjacent cities.

        //we run dijkstra from each of the cities and obtain the number of 
        //cities that were reachable in the shortest path tree
        for(int currentCity=0; currentCity<n; ++currentCity){
            connectedCities = dijkstra(currentCity, n, edges, distanceThreshold);
            //we update the city with the least number of reachable cities if
            //the count from dijsktra was below the current minimum
            if(connectedCities <= minCities){
                winningCity = currentCity;
                minCities = connectedCities;
            }
        }

        return winningCity;
    }



int main(){
	int n = 5;
	std::vector<std::vector<int>> edges = {{0,1,2},{0,4,8},{1,2,3},{1,4,2},{2,3,1},{3,4,1}};
	int  distanceThreshold = 2;

	std::cout << "City with least number of connected cities: " << findTheCity(n, edges, distanceThreshold) << "\n";
	return 0;
}
