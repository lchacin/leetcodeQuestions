/*

435. Non-overlapping Intervals

Given an array of intervals intervals where intervals[i] = [starti, endi], return the minimum number of intervals you need to 
remove to make the rest of the intervals non-overlapping.



Constraints:

1 <= intervals.length <= 105
intervals[i].length == 2
-5 * 104 <= starti < endi <= 5 * 104


Approach:

We take a greedy approach. We first sort the intervals in order of right-most value, and then we take the interval that
ends first, and discard all other overlapping intervals. We then pick the first non-verlapping interval and repeat the procedure
with the remaning intervals.

*/



#include<iostream>
#include<vector>
#include<algorithm>



int main(){
	std::vector<std::vector<int>> intervals{{3,6},{1,4},{1,2},{2,4},{3,5}};
	std::sort(intervals.begin(), intervals.end(), [](auto& int1, auto& int2)->bool{ return int1[1]<int2[1];});
	int removed=0;

	int last=0;
	for(int i=1; i<intervals.size(); ++i){
		if(intervals[i][0]<intervals[last][1]){
			++removed;
			continue;
		}
		else last = i;
	}

	std::cout<<"intervals removed: "<<removed<<"\n";

	return 0;

}
