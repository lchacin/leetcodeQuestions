/*


2462. Total Cost to Hire K Workers

You are given a 0-indexed integer array costs where costs[i] is the cost of hiring the ith worker.

You are also given two integers k and candidates. We want to hire exactly k workers according to the following rules:

You will run k sessions and hire exactly one worker in each session.
In each hiring session, choose the worker with the lowest cost from either the first candidates workers or the last candidates workers. 
Break the tie by the smallest index.

For example, if costs = [3,2,7,7,1,2] and candidates = 2, then in the first hiring session, we will choose the 4th worker 
because they have the lowest cost [3,2,7,7,1,2].
In the second hiring session, we will choose 1st worker because they have the same lowest cost as 4th worker but they 
have the smallest index [3,2,7,7,2]. Please note that the indexing may be changed in the process.

If there are fewer than candidates workers remaining, choose the worker with the lowest cost among them. Break the tie by the smallest index.
A worker can only be chosen once.

Return the total cost to hire exactly k workers.



Constraints:

1 <= costs.length <= 105 
1 <= costs[i] <= 105
1 <= k, candidates <= costs.length



Approach:

We'll traverse the costs vector starting from the left and from the right using two index runners.
We'll use a min-heap data structure to store the values from the left and right sides correspondingly to always
have the minimum value at the top of the heap, and so for each new value read the min-heap will partially sort the
new set of values.

We carry a total sum that we update with the next minimum value between the lowest value in the min-heaps from the left
and right sides. 

*/

#include<iostream>
#include<vector>
#include<queue> //for std::priority_queue
#include<algorithm> //for std::sort

long long totalCost(std::vector<int>& costs, int& k, int& candidates) {
        long long totalCost=0;

        //this is the case where the number of candidates to consider in each of the k sessions is more than half of the
        //the total number of employees.
        //this means that we would already know all of the employees on the first session, and hence we merely sort all the 
        //employee costs and pick the lowest k values
        if(candidates > costs.size()/2){
            std::sort(costs.begin(), costs.end());
            for(int i=0; i<k; ++i)
                totalCost+=costs[i];
            return totalCost;
        }


	//the case where the candidate number is less than half the total number of employees and hence we'll have at least one
	//session where not all the employees costs would be considered

        int leftRunner=0, rightRunner=costs.size()-1; //index runners to traverse the costs vector from the left and right sides

	//this is the binary comparison function used to sort employee cost - index pairs in for the heap to be a min-heap
	//we first sort by employee cost, and if the costs are the same, then we compare by index value
        auto comp = [](std::pair<int,int>& p1, std::pair<int,int>& p2)->bool{
                if(p1.first > p2.first) return true;
                else if(p1.first==p2.first) return p1.second>p2.second;
                else return false;
        };

	//create two min-heaps for the ledt and right side traversals of the costs vector
        std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, decltype(comp)> leftQ(comp), rightQ(comp);

        int i;

        //we iterate over the first candidate number of eomployee costs from the left and the right sides of the costs vector
        for(i=0; i<candidates; ++i){
                leftQ.push({costs[leftRunner], leftRunner});
                rightQ.push({costs[rightRunner],rightRunner});
                ++leftRunner;
                --rightRunner;
        }
        --leftRunner; ++rightRunner;

	//now we start the process finding the lowest employee cost from the left and right sides, and adding the lowest cost
	//to its corresponding min-heap. We then update the left or right index runners 
        for(i=0; i<k; ++i){

        	//the case where the lowest employee cost is on the left side 
            if(leftQ.top().first <= rightQ.top().first){
                totalCost+=leftQ.top().first; //update total cost with the cost at the top of the left min-heap
                leftQ.pop(); //remove the top of the heap so we can get the next smallest employee cost
                ++leftRunner; //move the leftRunner to the following index
                if(leftRunner>=rightRunner) break; //if leftRunner surpasses the rightRunner then both heaps have all of the remaining
                					//emplyee costs left stored in its corresponding heaps
                					//so we break 
               	//leftRunner has not caught up with rightRunner so we add the new employee cost to the min-heap 
                leftQ.push({costs[leftRunner], leftRunner}); 
            }

		//the case where the lowest emplyee cost is on the right side
            else if(leftQ.top().first > rightQ.top().first){
                totalCost+=rightQ.top().first;
                rightQ.pop();
                --rightRunner;
                if(rightRunner<=leftRunner) break;
                rightQ.push({costs[rightRunner], rightRunner});
            }
        }


	//out of the loop we check if we have completed all k sessions.

	//this is the case where we still have some session left, but the left and right min-heaps have all the remaining employee costs
	//stored in them
        if(i<k){
            ++i; //update  i since the prior break statement didn't allow the for loop to increase i before exiting

            //since the left and right min-heaps contain all remaining emplyee cost we merely repeatedly choose the lowest employee
            //between both heaps and update total cost. We do this until we reach a total of k sessions
            while(i<k){
            	//the case where the left min-heap is empty and solely choose from the right heap
                if(leftQ.empty()){
                    totalCost+=rightQ.top().first;
                    rightQ.pop();
                }
                //the case where the right min-heap is empty and we choose from the left min-heap
                else if(rightQ.empty()){
                    totalCost+=leftQ.top().first;
                    leftQ.pop();
                }
                else if(leftQ.top().first <= rightQ.top().first){
                    totalCost+=leftQ.top().first;
                    leftQ.pop();
                }
                else{
                    totalCost+=rightQ.top().first;
                    rightQ.pop();
                }
                ++i;
            }
        }

        return totalCost;
}

int main(){
//	std::vector<int> costs{17,12,10,2,7,2,11,20,8};
	std::vector<int> costs{1,2,4,1};
	int k=3, candidates=3;
	std::cout<<totalCost(costs,k,candidates)<<"\n";

	return 0;
}
