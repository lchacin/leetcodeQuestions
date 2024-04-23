
/*


875. Koko Eating Bananas

Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas. The guards have gone and will come back in h hours.

Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses some pile of bananas and eats k bananas from that pile. 
If the pile has less than k bananas, she eats all of them instead and will not eat any more bananas during this hour.

Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.

Return the minimum integer k such that she can eat all the bananas within h hours.


Constraints:

1 <= piles.length <= 104
piles.length <= h <= 109
1 <= piles[i] <= 109



Approach:

We let the possible eating rates to be 1 to the maximum pile size.
1 will be the case when h is large enough that Koko can eat at the slowest possible rate and still finish with a total time below h.
A rate equal to the maximum pile size will correspond to h equal to the number of available piles since this would imply
Koko needs to eat each pile in one hour.


For each rate selected we'll call a helper function "fastEnough" that checks whether eating at given rate Koko is able to finish
all the piles in less than h hours. 

We'll check the possible rates doing binary search for efficiency. When a chosen rate works, we let it be a provisional solution and 
check the middle of the lower half of the rate remaining. If it doesn't work we check the middle of the upper half of the rates remaining.


Letting the possible rates be 1 to the max pile value might seem unreasonable, but when checking using binary search then the mximum number of checks 
becomes log(1e9) ~ 30

*/


#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>


//fastEnough receives a reference to the vector containing the size of the banana piles, the rate at which Koko eats as k, and the maximum number
//of hours allowed h. It returns a boolean: true if at the rate k Koko takes <= h hours, and false otherwise
bool fastEnough( std::vector<int>& piles, int k, int h ){
	int t=0; //t will store the total time taken to eat all the banana piles at an eating rate of k
	for(auto& p: piles){ //we iterate over each banana pile
		t+=(p/k); //full number of hours taken to each groups of k bananas
		t+=(p%k>0); //the additional hour taken to eat the remaining banans
	}
	return t<=h; //if the time taken is less than or equal the limit number of ours we return true
}





int minEatingSpeed(std::vector<int>& piles, int h){
	//this is the case where the time limit is the same as the number of banana piles
	//in such a case Koko will hav to eat at a rate equal to the largest banana pile to guarantee each pile will be eaten in an hour
	if(h==piles.size()) return *std::max_element(piles.begin(), piles.end()); 


	
	int previous= *std::max_element(piles.begin(), piles.end()); //previous contains the last acceptable eating rate found
	int start=1, end=previous-1; //the start and end of the current interval considered in binary search
	int current = std::floor((end+start)/2); //current will be current eating rate being considered
	int k ; //to store the optimal eating rate
	bool fastFlag=false, success=false; //fastFlag is a flag to store the result from fastEnough and success is a flag for binary search if
						//the optimal eating rate was found

	while(!success){
		//we check if the current eating rate is acceptable
		fastFlag = fastEnough(piles,current,h);

		//the case where the eating rate is acceptable and there is no other lower possible eating rate to check
		if(fastFlag && current==start) {success=true; k=current;} //set the success flag to escape the binary search and record the optial eating rate
		
		//the case where the eating rate is acceptable but there are still lower eating rate that can be checked
		else if(fastFlag && current>start){
			previous = current; //record the acceptable eating rate
			end = current-1;	//let the end of the binary search list be the next lower eating rate
			current = std::floor((end+start)/2); //update current ot be the middle value of the lower half of eating rates left
		}

		//the case where the eating rate is not acceptable and there are no higher eating rates to test
		else if(!fastFlag && current == end) {success=true; k=previous;} //set the flag to escape binary search and let the optimal eating
										//rate be the last optimal acceptable eating rate, previous
		
		//the case where  the eating rate is not acceptable but there are still higher eating rates to test
		else if(!fastFlag && current < end){
			start = current + 1; //set start to the next higher eating rate
			current = std::floor((start+end)/2); //let current be the middle rate of the lest of higher eating rate left to test
		}
	}

	return k;

}




int main(){
	std::vector<int> piles{3,6,7,11};
	int h = 8;

	std::cout<<minEatingSpeed(piles,h)<<"\n";

	return 0;


}
