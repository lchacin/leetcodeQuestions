/*

216. Combination Sum III


Find all valid combinations of k numbers that sum up to n such that the following conditions are true:

Only numbers 1 through 9 are used.
Each number is used at most once.
Return a list of all possible valid combinations.
The list must not contain the same combination twice, and the combinations may be returned in any order.


Contraints:
2 <= k <= 9
1 <= n <= 60


Approach:

We create a recursive function that creates a list with a potential combination adding a new number  with each
recursive level. The function has a parameter sotring the sum of the list being created. When the sum hits
the desired target value we add the list to a list of successful combination that the function carries
as a parameter reference.

With each recursive level we only consider a new value greater than the value of the last number tested, this
ensures that the recursive function never consideres duplicate combinations. The recursive functions has a parameter
telling what should be the starting value it should consider, and we only enter additional recursive calls if the
list is not larger than the maximum length. 



*/


#include<iostream>
#include<vector>

//f is the recusrive function that will find all the combinations of length k that add up to n
//it accepts two int parameters, start and sum, where start is the first value considered to be added in the current
//combination being built, and sum is the current sum of the combination being created.
//it also accepts to integer references, target and size, which are k and n in the question explanation
//the function also accepts a reference to an integer vector which is the current combination being created
//and a referece to vector of integer vectors which stores all the successful combinations
void f(int start, int sum, int& target, int& size, std::vector<int>& carryList, std::vector<std::vector<int>>& finalList){
	//the case where the sum of the current combination is target and the length of the combination is the desired size
	if(sum==target && carryList.size()==size)
		finalList.push_back(carryList); //we add the combination to final list of combination

	//this is the case where the sum of the current combination exceeds the desired target value
	else if(sum>target)
		return; 

	//this is the case where the current combination does not added up to target 
	else{
		//the for loop will iterate over all the values greater than start and less than 10
		//ensuring that will only consider value greater than the last value added to the current combination
		for(short i=start; i<10; ++i){
			//this if statement checks if the current combination's length is less than the allowed size
			if(carryList.size() < size){
				carryList.push_back(i); //add the new value to the combination
				 //recursively enter f to continue expanding the combination
				 //with the new starting value being one more than the last value added, and
				 //with the updated sum being the old sum plus the last value added
				f(i+1, sum+i, target, size,carryList, finalList);
				//back from the recursive call we remove the last added value so we can add the next one
				carryList.pop_back();
			}
		}
	}
}


//combinationSums receives two integers by reference: k, the length of the desired combinations.
//and n, the desired sum of the combinations. combinationSums returns a list of integer lists
//containing all the possible combinations of values from 1-9 of length k that add up to n
std::vector<std::vector<int>> combinationSums(int& k, int& n){
//        short maxSum=0, minSum=0;
//        short i=9,j=1;
//        while(i>9-k){
//            maxSum+=i; minSum+=j;
//            ++j; --i;
//        }
//        if(n>maxSum || n<minSum) return {};
	
	std::vector<int> carryList; //carryList will be passed by reference to f and will be used to store a single combination
	std::vector<std::vector<int>> finalList; //finalList will store all the successful combinations found
	f(1,0,n,k,carryList, finalList); 
	return finalList;
}




int main(){
	int k=3, n=9;
	auto allPossibleCombinations = combinationSums(k,n);
	std::cout<<"[";
	for(auto& subList: allPossibleCombinations){
		std::cout<<"[";
		for(auto& x: subList)
			std::cout<<x<<",";
		std::cout<<"], ";
	}
	std::cout<<"]\n";

	return 0;
}




