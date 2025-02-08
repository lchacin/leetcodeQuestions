/*

3160. Find the Number of Distinct Colors Among the Balls

You are given an integer limit and a 2D array queries of size n x 2.

There are limit + 1 balls with distinct labels in the range [0, limit]. 
Initially, all balls are uncolored. For every query in queries that is of the form [x, y], 
you mark ball x with the color y. After each query, you need to find the number of 
distinct colors among the balls.

Return an array result of length n, where result[i] denotes the number of distinct colors after ith query.

Note that when answering a query, lack of a color will not be considered as a color.


Constraints:

1 <= limit <= 109
1 <= n == queries.length <= 105
queries[i].length == 2
0 <= queries[i][0] <= limit
1 <= queries[i][1] <= 109



*/


#include<iostream>
#include<vector>
#include<unordered_map>


std::vector<int> queryResults(int limit, std::vector<std::vector<int>>& queries) {
        //a hash map to store ball keys and their color value
        std::unordered_map<int,int> ballColorMap;

        //hash map to store each color with its number of balls
        std::unordered_map<int,int> colorCountMap;

        //vector to store the color count after each querie
        std::vector<int> countVector;


        for(auto& querie: queries){
            //we check if the current ball has already been given
            //a color
            if(ballColorMap.contains(querie[0])){
                //if so, we decrease the total count of balls
                //with the color currently held by the current ball
                --colorCountMap[ballColorMap[querie[0]]];

                //if the count of the current ball's color went down
                //to 0, we remove the color
                if(colorCountMap[ballColorMap[querie[0]]]==0)
                    colorCountMap.erase(ballColorMap[querie[0]]);

                //now we proceed to increase the count of the new
                //color to be assigned to the current ball

                //we check if the color has already been given to a ball
                //if so we increase the count
                if(colorCountMap.contains(querie[1]))
                    ++colorCountMap[querie[1]];
                //otherwise we add it to the map with a count of 1
                else 
                    colorCountMap[querie[1]] = 1;

                //lastly we change the color of the current ball
                ballColorMap[querie[0]] = querie[1];
            }

            //the case the current ball has never been given a color
            else{
                //we assign the current color to the current ball
                ballColorMap[querie[0]] = querie[1];

                //we check if the color has already been given to a ball
                //if so we increase the count
                if(colorCountMap.contains(querie[1]))
                    ++colorCountMap[querie[1]];
                //otherwise we add it to the map with a count of 1
                else 
                    colorCountMap[querie[1]] = 1;
                
            }

            countVector.push_back(colorCountMap.size());
        }

        //the size of the colorCountMap tells us the number of
        //distinct colors

        return countVector;
    }


int main(){
	std::vector<std::vector<int>> queries{{1,3},{2,3},{3,4},{4,5},{5,6},{0,3}};
	int limit = 6;

	auto countVector = queryResults(limit, queries);
	for(auto& count: countVector)
		std::cout << count << " ";
	std::cout << "\n";

	return 0;
}
