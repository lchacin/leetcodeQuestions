/*

1318. Minimum Flips to Make a OR b Equal to c

Given 3 positives numbers a, b and c. 
Return the minimum flips required in some bits of a and b to make ( a OR b == c ). (bitwise OR operation).
Flip operation consists of change any single bit 1 to 0 or change the bit 0 to 1 in their binary representation.

Constraints:

1 <= a <= 10^9
1 <= b <= 10^9
1 <= c <= 10^9


Approach:

Since we want bitwise OR between a and b to be c, for each of c's bit there are two cases:
1) if c's bit is 1, then one flip will be needed if neither of a or b's corresponding bit is 1
2) if c's bit is 0, then a flip will be needed for each of a's or b's corresponding bit if the are 1s.


In order to analyze a, b, and c's bits individually we use the mod operator and modular divide them by 2
iteratively until all three of them are zero. The last bit will be the remainder obtained after the modular division.
We update the number of flips based on the observations made from 1) and 2)

Then we do away with a, b and c's last bit by doing a bitwise right shift. 

*/


#include<iostream>


//minFlips is a function the accepts three integers a, b and c by reference
//and returns the minium number of flips that must be performed on a and b to get 
//bitwise OR between them to be c
int minFlips(int& a, int& b, int& c) {
	//reaminderA, remainderB, and remainderC will store the remainder of a, b and c
	//when divided by 2
        bool remainderC, remainderA, remainderB;
        short flips=0; //stores the total number of bits that were flipped

	//while loop counts the number of bits flipped until c becomes zero
        while(c!=0){
        	//we obtain each of a,b and c's last bit by getting their remainders when divided by 2
            remainderC=c%2; remainderA=a%2; remainderB=b%2;
            c>>=1; a>>=1; b>>=1; //we remove the last bit by performing right shift operation on each them

		//the case where c's last bit was a 1
            if(remainderC){
            	//if a or b's last bit ia a 1 there is no need to flip any other their bits
                if(remainderA||remainderB)
                    continue;

                //the case where neither a or b's last bit was 1. We flip one of their bits so the bitwise OR becomes 1
                ++flips; 
            }

            //the case where c's last bit was 0
            else{
            	//we';; need to flip a and b's bit if any was 1
                if(remainderA) ++flips;
                if(remainderB) ++flips;
            }
        }

        //out of the while loop we have left to continue flipping a or b's bits if any of them
        //is not zero.
        while(a!=0){
            if(a%2) ++flips;
            a>>=1;
        }

        while(b!=0){
            if(b%2) ++flips;
            b>>=1;
        }

        return flips;
    }





int main(){
	int a=10, b=9, c=1;
	std::cout<<"Total flips: "<<minFlips(a,b,c)<<"\n";

	return 0;
}
