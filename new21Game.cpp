/*
New 21 Game

Alice plays the following game, loosely based on the card game "21". Alice starts with 0 points and draws numbers while she has less than k points. During each draw, she gains an integer number of points randomly from the range [1, maxPts], where maxPts is an integer. Each draw is independent 
and the outcomes have equal probabilities. Alice stops drawing numbers when she gets k or more points.

Return the probability that Alice has n or fewer points.

Answers within 10-5 of the actual answer are considered accepted.


Constraints:

0 <= k <= n <= 104
1 <= maxPts <= 104

*/


#include<iostream>
#include<vector>


double new21Game(int n, int k, int maxPts) {
        if(k==0) return 1.0; //if k=0 the game ends immediately with no draws and hence score of 0 always ;ess than or equal to n
        if(k==1){ //in this case the game finishes in one turn
            //the case where all values drawn will be less than or equal to n
            if(n>=maxPts) return 1.0;
            return double(n-k+1) / maxPts;
        }

        int j, score; //looping variables
        double doubleMaxPts = maxPts;

        //let's first calculate the probabilities of getting to each of the scores of
        //1 to k-1
        //we'll do so in a score increasing fashion sotring the previous results
        //otained in a dynamic programming fashion
        std::vector<double> scoreProbs(k); //we'll use indexes 1 to k-1
        scoreProbs[0] = 1;
        scoreProbs[1] = scoreProbs[0]*(1.0/doubleMaxPts);
 
        if(maxPts < k){
            for(j=2; j<=maxPts; ++j)
                scoreProbs[j] = (scoreProbs[j-1] * (1+doubleMaxPts)) / doubleMaxPts;
            for(; j<k; ++j)
                scoreProbs[j] = (scoreProbs[j-1] * (1+doubleMaxPts) - scoreProbs[j-1-maxPts]) / doubleMaxPts;
        }
        else{

            for(j=2; j<k; ++j)
                scoreProbs[j] = (scoreProbs[j-1] * (1+doubleMaxPts)) / doubleMaxPts;
        }
        //out of the for loop scoreProbs contains the probabilities of reaching
        //of the the different intermediate scores whilst playing the game

        //for(auto& p: scoreProbs) std::cout << p << " ";


        double result= 0;

        for(j = std::max(k-maxPts,0); j < k; ++j){
            result += (std::min(j+maxPts,n)-k+1)/doubleMaxPts * scoreProbs[j];
        }


        return result;
    }


int main(){
	int n=21, k=17, maxPts=10;

	std::cout <<  new21Game(n,k,maxPts) << "\n";

	return 0;

}
