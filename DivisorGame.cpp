#include<iostream>
#include<vector>


bool divisorGame(const int& n) {
        if(n==1) return false; //the base case of the DP solution. When n=1 Alice loses.

        //the case where n is greater than 1

        //we create a vector<bool> to store the results of the game
        //true:=win, false:=lose
        //we initialize it to false 
        std::vector<bool> gameResult(n+1,false);

        //i will iterate over the integers from 2 to n
        //divisor will be an integer from 1 to i-1, that will be tested as potential factor of n
        short END=n+1,i, divisor; 

        //outer for-loop will iterate in increasing order over the cases where the game
        //starts with an integer from 2 all the way to n, finding the solution
        //to each of these particular cases one at a time.
        for(i=2; i<END; ++i){ 
            //this inner for-loop will iterate over the integers from 1 to i-1
            //checking to see which ones are factors for i.
            for(divisor=1; divisor<i; ++divisor){
                //if divisor is a factor of i we check the game result of
                //i-divisor and set the game result for i to be the win if 
                //the result if i-j was lose
                if(i%divisor==0 && gameResult[i-divisor]==false){
                    gameResult[i]=true;
                    break;
                }
            }
        }

        //out of the for-loop gameResult stores all the gameResult for starting integers
        //1 to n. 
        return gameResult.back(); //we return the last game result calculated
    }



int main(){
	int startingValue=1000;
	std::cout<<"Game starts with "<<startingValue<<" written on the board: ";
	(divisorGame(startingValue))?(std::cout<<"Alice wins\n"):(std::cout<<"Bob wins\n");

	return 0;
}
