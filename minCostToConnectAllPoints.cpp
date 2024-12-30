/*

1584. Min Cost to Connect All Points


You are given an array points representing integer coordinates of some points on a 2D-plane, 
where points[i] = [xi, yi].

The cost of connecting two points [xi, yi] and [xj, yj] is the manhattan 
distance between them: |xi - xj| + |yi - yj|, where |val| denotes the absolute value of val.

Return the minimum cost to make all points connected. 
All points are connected if there is exactly one simple path between any two points.


Constraints:

1 <= points.length <= 1000
-106 <= xi, yi <= 106
All pairs (xi, yi) are distinct.


*/


#include<iostream>
#include<vector>
#include<queue>	//for std::priority_queue


//calculate manhattan distance
    int calcDistance(std::vector<int>& p1, std::vector<int>& p2){
        return std::abs(p1[0]-p2[0]) + std::abs(p1[1]-p2[1]);
    }

    int prim(std::vector<std::vector<int>>& points){

        //comparator is a binary boolean function used to help the priority
        //queue partially sort the points with their weight
        auto comparator = [](std::pair<int,int>& p1, std::pair<int,int>& p2)->bool{
            return p1.second > p2.second;
        };

        //initialize a priority queue to store adjacent points to the MST being built
        std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, decltype(comparator)> q;

        //create a boolean vector that tells what vertices have already been
        //added to the MST
        std::vector<bool> mst(points.size(), false);

        //add the arbitrary vertex chosen to the priority queue with its weight
        q.push({0, 0});

        //to stroe a chosen point
        std::pair<int, int> currentPoint;

        //integer variables to store the total distance in the MST 
        int totalDistance = 0;

        while(!q.empty()){
            //pick the point with the highest priority (smallest distance to reach from the MST)
            currentPoint = q.top();
            q.pop(); //remove point from priority queue

            //if the point is already in the mst we loop again
            if(mst[currentPoint.first]) continue;

            mst[currentPoint.first]=true; //record that the point has been added to the mst


            //we iterate over the points and the ones adjacent to the current point that are not
            //yet in the MST
            for(int i=0; i<points.size(); ++i){
                //we only check points not already in the mst
                if(!mst[i]){
                    q.push({i, calcDistance(points[i], points[currentPoint.first])});
                }
            }

            //we update the total distance with the distance of the last point chosen
            totalDistance += currentPoint.second;

        }

        return totalDistance;
    }

    int minCostConnectPoints(std::vector<std::vector<int>>& points) {
        return prim(points);
    }


int main(){
	std::vector<std::vector<int>> points{{2,-3},{-17,-8},{13,8},{-17,-15}};

	std::cout << "The minimum distance is: " << prim(points) << "\n";

	return 0;
}
