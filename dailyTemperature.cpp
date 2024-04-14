/*
Daily Temperatures

Given an array of integers temperatures represents the daily temperatures, return an array answer such that answer[i] is the number 
of days you have to wait after the ith day to get a warmer temperature. If there is no future day for which this is possible, 
keep answer[i] == 0 instead.

Constraints:

    1 <= temperatures.length=N  <= 105
    30 <= temperatures[i] <= 100


Explanation:

If we use two indexes i and j where i represents the current value and j is the index for the values beyond index i,
and we determine the number of steps to the next higher values than temperature[i], this would lead to an O(N^2) solution.

The issue lies with the fact that as j iterates through temperature values for j>i, we are only comparing temperature[j] to
temperature[i] without determining output[j]s as we go.

Instead, we would like an approach that doesn't obtain output[i] in order of i, but instead it obtains output[i]s based  on
the first temperature[i] for which the following value is greater than it.

For this approach we make use of a monotonically decreasing stack. 
The stack will store pairs of temperature value with its index.
If a new temperature value is less than or equal the top of the stack we add it to the stack.
If a new temperature value is greater than the top of the stack we loop removing the top of the stack,
let output[index of top of stack] equal the difference in indexes of i and index of top of the stack,
and stop when the stack is either empty or the top of the stack is no longer smaller than temperature[i].

This approach leads to a stack that is  at all times top-bottom monotonically decreasing.

*/



#include<iostream>
#include<stack>
#include<vector>

std::vector<int> dailyTemperatures(std::vector<int>& temperatures){
	//the case where we only one temperature reading
	if(temperatures.size()==1) return {0};

	//the use of two or more temperatures
	std::stack<std::pair<int&, int>> decreasingStack; //stack used to create a monotonically increasing stack. Stores references to the elements stored 
						//in temperature
	int i=0, steps=0; //i will be the index in temperature and steps will be the number of steps we have taken from index
	std::vector<int> output(temperatures.size(),0); //for each index it will store the number of steps to the next higher temperature


	//we are done when index reaches the end
	for(;i<temperatures.size(); ++i){
		//if the stack is empty or the new temperature value is <= the top of the stack
		if(decreasingStack.empty() || temperatures[i] <= decreasingStack.top().first)
			decreasingStack.push({temperatures[i],i});
		//the case where the new temprature is greater than the top of the stack
		else{
			//we loop removing the top of the stack until the stack is empty or the top of the stack is not less
			//than the new temperature value
			//every time we remove the top of the stack we add the number of steps from the index of 
			//the top of the stack to the new higher temperature
			while(!decreasingStack.empty() && temperatures[i] >  decreasingStack.top().first){
				output[decreasingStack.top().second] = i - decreasingStack.top().second;
				decreasingStack.pop();
			}
			decreasingStack.push({temperatures[i],i}); //lastly we add the new temperature to the stack
		}
	}

	return output;
}


int main(){
	std::vector<int> temps{73,74,75,71,69,72,76,73};
	auto output = dailyTemperatures(temps);
	for(auto& val: output) std::cout<<val<<" ";
	std::cout<<"\n";

	return 0;
}
