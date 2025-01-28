/*
1462. Course Schedule IV


There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. 
You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you 
must take course ai first if you want to take course bi.

For example, the pair [0, 1] indicates that you have to take course 0 before you can take course 1.
Prerequisites can also be indirect. If course a is a prerequisite of course b, 
and course b is a prerequisite of course c, then course a is a prerequisite of course c.

You are also given an array queries where queries[j] = [uj, vj]. For the jth query, 
you should answer whether course uj is a prerequisite of course vj or not.

Return a boolean array answer, where answer[j] is the answer to the jth query.


Constraints:

2 <= numCourses <= 100
0 <= prerequisites.length <= (numCourses * (numCourses - 1) / 2)
prerequisites[i].length == 2
0 <= ai, bi <= numCourses - 1
ai != bi
All the pairs [ai, bi] are unique.
The prerequisites graph has no cycles.
1 <= queries.length <= 104
0 <= ui, vi <= numCourses - 1
ui != vi


*/


#include<iostream>
#include<vector>    //for std::vector
#include<queue>	    //for std::queue
#include<algorithm> //for std::sort

    enum Colors{ white, grey, black};

    //performs breadth first search from a root value on a graph represented by an adjacecny list
    //and marks vertices reached as true in the boolean visited vector
    void bfs(int root, std::vector<std::vector<int>>& adjList, std::vector<bool>& visited){
        std::queue<int> bfsQ;
        std::vector<Colors> vertexColors(adjList.size(), Colors::white);
        bfsQ.push(root);
        vertexColors[root] = Colors::grey;
        int currentVertex;


        while(!bfsQ.empty()){
            currentVertex = bfsQ.front();
            bfsQ.pop();
            vertexColors[currentVertex] = Colors::black;

            for(auto& neighbor: adjList[currentVertex]){
                if(vertexColors[neighbor] == Colors::white){
                    bfsQ.push(neighbor);
                    vertexColors[neighbor] = Colors::grey;
                }
            }

            visited[currentVertex] = true;
        }
    }



    std::vector<bool> checkIfPrerequisite(int numCourses, std::vector<std::vector<int>>& prerequisites, std::vector<std::vector<int>>& queries) {
        //create the adjacency list
        std::vector<std::vector<int>> adjList(numCourses);
        for(auto& prereq: prerequisites)
            adjList[prereq[0]].push_back(prereq[1]);        


        //indexedQueries will store pairs with queries with their original index
        std::vector<std::pair<int, std::vector<int>>> indexedQuery;
        for(int i=0; i<queries.size(); ++i)
            indexedQuery.push_back({i, queries[i]});

        //we sort indexedQueries by the prerequesite value of the query
        std::sort(indexedQuery.begin(), indexedQuery.end(), [](auto& p1, auto& p2)->bool{return p1.second[0] <  p2.second[0];});

        //answers will store the results of the queries
        std::vector<bool> answers(queries.size(), false);


        int currentQuery = 0;   //stores the currentQUery being answered
        int currentRoot;        //stores the currentRoot vertex for BFS

        //we run a while loop until all queries have been answered
        while(currentQuery < queries.size()){
            //currentRoot will be the prerequesite value of the currentQuery in indexedQuery
            currentRoot = indexedQuery[currentQuery].second[0];

            //visited will store the courses that were visited when performing bfs from currentRoot
            //if a course was visited (has value true) it means that currentRoot is a prerequisite course for it
            std::vector<bool> visited(numCourses, false);

            //run bfs from currentRoot. We pass the adjList graph and the visited vector by reference
            bfs(currentRoot, adjList, visited);
            
            //we check if the currentQuery's course beig considered was visited
            if(visited[indexedQuery[currentQuery].second[1]]){
                //we use the original query's index and mark it as true
                answers[indexedQuery[currentQuery].first]=true; 
            }

            //we check any other queries that have currentRoot as a prerequeiste course to avoid
            //running bfs again from the same root vertex
            while(currentQuery+1 < queries.size() 
                && indexedQuery[currentQuery+1].second[0] == indexedQuery[currentQuery].second[0]){
                    ++currentQuery;
                    if(visited[indexedQuery[currentQuery].second[1]])
                        answers[indexedQuery[currentQuery].first]=true;
            }

            //we move on to the next query
            ++currentQuery;

        }


        return answers;
    }



int main(){
	int numCourses = 18;
	std::vector<std::vector<int>> prerequisites{
		{8,9},{13,12},{8,10},{12,2},{16,15},{14,12},{17,15},
		{15,2},{3,5},{5,6},{2,3},{6,7},{4,6},{1,2},{1,3},{2,4},{2,7}
	};

	std::vector<std::vector<int>> queries{{4,7},{1,0},{6,7},{8,11},{0,11},{17,1}};

	auto answers = checkIfPrerequisite(numCourses, prerequisites, queries);
	for(int i=0; i< answers.size(); ++i)
		std::cout << std::boolalpha << answers[i]<< " ";
	std::cout << "\n";

	return 0;
}
