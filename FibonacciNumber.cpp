/*

509. Fibonacci Number

The Fibonacci numbers, commonly denoted F(n) form a sequence, called the Fibonacci sequence, 
such that each number is the sum of the two preceding ones, starting from 0 and 1. That is,


COntraints:
0 <= n <= 30


Approach:

We use memoization to store the two previous fibonacci numbers obtained to calculate the new one.
Once we calculate the new one we discard the oldest of the three fibonacci numbers currently obtained
and keep the latest two. We proceed in this fashion, calculating the following number until we reach
the nth fibonacci number.

*/


#include<iostream>

//fib is a function that calculates the nth fibonacci number.
//it accepts an integer reference parameter, n, representing the nth fibonacci number
//it is supposed to calculate.
//it returns an integer equal to the nth fibonacci number
int fib(int& n) {
	//two base casses for the oth and 1st fibonacci numbers
	if(n==0) return 0;
        if(n==1) return 1;

        //we reduce n by two since we've already considered two first cases
        n-=2;
        int first=0, second=1, temp; //first and second store two consecutive fibonacci numbers
        				//temp serves as placeholder when updating first and second to be 
        				//the latest consecutive fib numbers
        				
        //the while loop iterates until we obtain the nth fibonacci number that will be stored in second
        while(n>-1){
            temp=second; //temp stores the value of second
            second+=first; //update second to be the new fibonacci number
            first=temp; //update first to be the previous value of second
            --n;
        }
        
        return second;
    }


int main(){
	int n=30;
	std::cout<<"The "<<n<<" fibnacci number is: "<<fib(n)<<"\n";

	return 0;
}
