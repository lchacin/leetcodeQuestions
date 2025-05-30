#include<iostream>
#include<vector>
#include<unordered_map>
#include<limits>




//dfs runs depth frist search from the startingNode, and on the way records the distance
    //of the nodes traversed through from the startingNode
    std::unordered_map<int, int> dfs(std::vector<int>& graph, int startingNode){
        std::unordered_map<int,int> map; //to record the distance from startingNode to a given node
        int runningDistance = 0;    //to keep track of the distance of a node from startingNode

        int currentNode, nextNode = startingNode; //to record the node being worked on during BFS
        std::vector<bool> visited(graph.size(), false); //to record that nodes that have all already been visited

        //we continue moving to the next nodes until there is no next node, denoted by -1
        while(nextNode != -1){
            currentNode = nextNode; //update the current node
            visited[currentNode] = true;    //mark the currentNode as visited
            map[currentNode] = runningDistance; //record the distance of the currentNode from the startingNode
            ++runningDistance; //update the distance for the next node

            //update nextNode to be the currentNode neighbor that isn;t yet visited or -1 if no neighbor exists
            nextNode = (graph[currentNode] != -1 && !visited[graph[currentNode]]) ? (graph[currentNode]) : -1;
        }

        //return the generate hash map
        return map;
    }

    int closestMeetingNode(std::vector<int>& edges, int node1, int node2) {
        //we run depth first search from node1 and node2
        auto map1 = dfs(edges, node1);
        auto map2 = dfs(edges, node2);


        int solution=edges.size()+2;    //to record the node generating the minimax distance
        int runningMinMax = std::numeric_limits<int>::max(); //to record the minimax distance
        int tempDistance; //to record the distance obtained from of the currentNode from node1 and node2

        //we iterate over the nodes that were reached via dfs from node1
        for(auto& p: map1){
            //we check if the reachable node was also reachable from node2
            if(map2.contains(p.first)){

                //calculate the max distance between that of reaching node1 and node2
                tempDistance = std::max(p.second,map2[p.first]);

                //if the max distance is smaller than the current minimum max distance, we update the solution
                //and the runningMinMax
                if(tempDistance < runningMinMax){
                    runningMinMax = tempDistance;
                    solution = p.first;
                }
                //this is the case we obtained minimum max from a vertex of lower index
                //so we update just the solution
                else if(tempDistance == runningMinMax && p.first < solution)
                    solution = p.first;
            }
        }

        
        if(solution == edges.size()+2) return -1;

        return solution;
    }





int main(){
	std::vector<int> edges{2,2,3,-1};
	int node1=0, node2=1;
	std::cout << closestMeetingNode(edges,node1,node2) << "\n";

	return 0;
}
