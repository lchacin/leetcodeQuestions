#include<iostream>
#include<queue>
#include<vector>


    enum Color{RED, BLUE};
    enum bfsColor{WHITE, GREY, BLACK};

    //this method will run BFS and color, red or blue, the graph passed by reference 
    //it will also keep track of the color of each node. 
    //it returns an array with the total count of red and blue nodes
    std::vector<int> bfs(std::vector<std::vector<int>>& graph, std::vector<Color>& nodeColor){
        std::vector<int> totalRedBlue(2,0); //array to keep track total number of red and blue nodes
        std::queue<int> bfsQ; //queue to perform bfs

        //to keep track of the color of the node for purposes of the BFS
        std::vector<bfsColor> nodeColorBFS(graph.size(), bfsColor::WHITE);
        
        int currentNode = 0; //to keep track of the current node
        bfsQ.push(currentNode); //add node 0 to the queue
        nodeColorBFS[currentNode] = bfsColor::GREY;

        //to keep track of the current node color. We start with red by default
        Color currentColor = Color::RED; 
        nodeColor[currentNode] = currentColor;


        while(!bfsQ.empty()){
            //remove the node at the front of the queue
            currentNode = bfsQ.front();
            bfsQ.pop();
            currentColor = nodeColor[currentNode];
            ++totalRedBlue[currentColor]; //update the total count of red or blue nodes


            //add all of the current node's neighbors to the queue
            for(int& neighbor: graph[currentNode]){
                //check that the neighbor is valid
                if(nodeColorBFS[neighbor] == bfsColor::WHITE){
                    //neighbor is valid so we change its color to grey and add it to the queue
                    nodeColorBFS[neighbor] = bfsColor::GREY;
                    bfsQ.push(neighbor);
                    nodeColor[neighbor] = (nodeColor[currentNode])?(Color::RED):(Color::BLUE);
                }
            }

            //done with adding the valid neighbors to the queue we turn the current node's color 
            //black
            nodeColorBFS[currentNode]=bfsColor::BLACK;
        }

        return totalRedBlue;
    }

    std::vector<int> maxTargetNodes(std::vector<std::vector<int>>& edges1, std::vector<std::vector<int>>& edges2) {
        //let's first create the graph representations using adjacency lists

        //creating graph 1
        std::vector<std::vector<int>> graph1(edges1.size()+1);
        //fill up the adjacecny list with each node's neighbors
        //the graph is undirecrted therefore for each edge, the end nodes are neighbors of each other
        for(auto& edge: edges1){
            graph1[edge[0]].push_back(edge[1]);
            graph1[edge[1]].push_back(edge[0]);
        }

        //repeat the same to create graph 2
        std::vector<std::vector<int>> graph2(edges2.size()+1);
        for(auto& edge: edges2){
            graph2[edge[0]].push_back(edge[1]);
            graph2[edge[1]].push_back(edge[0]);
        }

        //now we run BFS to traverse each graph separately
        //while traversing the graph we color each graph red and blue and keep track
        //of the total number of red and blue nodes in each graph
        std::vector<Color> nodeColor1(edges1.size()+1), nodeColor2(edges2.size()+1);

        auto totalRedBlue1 = bfs(graph1, nodeColor1);
        auto totalRedBlue2 = bfs(graph2, nodeColor2);


        std::vector<int> answers(edges1.size()+1, 0);
        for(int i=0; i<edges1.size()+1; ++i){
            if(nodeColor1[i]) //case node color is Color::BLUE
                answers[i] = totalRedBlue1[Color::BLUE] + std::max(totalRedBlue2[Color::BLUE], totalRedBlue2[Color::RED]);
            else //case node color is Color::RED
                answers[i] = totalRedBlue1[Color::RED] + std::max(totalRedBlue2[Color::BLUE], totalRedBlue2[Color::RED]);
        }

        return answers;
        
    }


int main(){
	std::vector<std::vector<int>> edges1{{0,1},{0,2},{2,3},{2,4}};
	decltype(edges1) edges2{{0,1},{0,2},{0,3},{2,7},{1,4},{4,5},{4,6}};
	
	auto answers = maxTargetNodes(edges1, edges2);

	std::cout << "answers: ";
	for(auto& x: answers) std::cout << x << " ";
	std::cout << "\n";

	return 0;
}
