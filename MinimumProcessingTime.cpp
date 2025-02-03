/*

2895. Minimum Processing Time

You have a certain number of processors, each having 4 cores. The number of tasks to be executed is four times the number of processors. 
Each task must be assigned to a unique core, and each core can only be used once.

You are given an array processorTime representing the time each processor becomes available and an 
array tasks representing how long each task takes to complete. Return the minimum time needed to complete all tasks.


Constraints:

1 <= n == processorTime.length <= 25000
1 <= tasks.length <= 105
0 <= processorTime[i] <= 109
1 <= tasks[i] <= 109
tasks.length == 4 * n


*/


#include<iostream>
#include<vector> //for std::vector
#include<algorithm> //for std::sort



int minProcessingTime(std::vector<int>& processorTime, std::vector<int>& tasks) {
        //we sort the processing times in increasing order
        std::sort(processorTime.begin(), processorTime.end());

        //we sort the tasks in decreasing order
        std::sort(tasks.begin(), tasks.end(), [](auto& x, auto& y)->bool{return x>y;});

        int maxTime = 0;

        //we pair the longest taks with the smallest processor times
        //each iteration we update max time to be the max between the 
        //current max time and the time to process the next batch of
        //four tasks with the next processor
        for(int i=0; i<processorTime.size(); ++i)
            maxTime = std::max(maxTime, processorTime[i]+tasks[4*i]);

        return maxTime;
    }



int main(){
	std::vector<int> processorTime{8,10,7};
	decltype(processorTime) tasks{2,2,3,1,8,7,4,5, 10,10,10,10};

	std::cout << minProcessingTime(processorTime, tasks) << "\n";

	return 0;
}
