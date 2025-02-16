/*

2698. Find the Punishment Number of an Integer


Given a positive integer n, return the punishment number of n.

The punishment number of n is defined as the sum of the squares of all integers i such that:
- 1 <= i <= n
- The decimal representation of i * i can be partitioned into contiguous substrings 
such that the sum of the integer values of these substrings equals i.


Constraints:

1 <= n <= 1000


*/


#include<iostream>
#include<string>


bool f(std::string valueToBreak, int originalValue){
        //case the values subtracted from the original value were too much
        if(originalValue < 0) return false;

        //case we have subtracted enough to make the original value zero
        //we'll return true if valueToBreak is zero or has no more digits left to subtract from
        //original value. Otherwise we return false
        else if(originalValue == 0)  return valueToBreak.size()==0 || std::stoi(valueToBreak) == 0;

        bool result=false;

        //each iteration of the for loop subtracts from the original value the integer
        //created from digits positions 0 to i in valueToBreak and reenters function f
        //with the remaining digits a the new valueToBreak and the subtraction result
        //as the new original value
        for(int i=0; i<valueToBreak.size(); ++i){
            result = f(valueToBreak.substr(i+1, valueToBreak.size()),
                            originalValue - std::stoi(valueToBreak.substr(0,i+1)));
            //if result is true we stop
            if(result) break;
        }

        return result;
    }


    int punishmentNumber(int n) {
        int total = 0;
        for(int i=1; i<=n; ++i){
            if(f(std::to_string(i*i), i)) total+=(i*i);
        }
        return total;   
    }



int main(){
	std::cout << "punishment number of 37: " << punishmentNumber(37) << "\n";
	return 0;
}
