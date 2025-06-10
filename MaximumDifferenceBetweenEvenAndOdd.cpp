#include<iostream>
#include<vector>


int maxDifference(std::string& s) {
        //we create a vector of size 26 where we record the count of each of the 26
        //lowercase English letters
        std::vector<int> letterCount(26, 0);

        //a variable to record the maximum number of odd count letters and the minimum
        //number of even count letters
        int maxOddFreq=0, minEvenFreq=s.size();

        //we iterator over the characters in the string and
        //update the count of the character seen
        for(auto& letter: s)
            ++letterCount[letter-97];
        
        //done with the first for loop now each character count represents
        //the total number of each letter
        for(auto& count: letterCount){
            //the case the count was odd
            if(count%2){
                //if the count is larger than the largest odd count seen we update the max odd count
                if(count > maxOddFreq) 
                    maxOddFreq = count;
            }
            //case the count was even
            else if(count!=0){
                //if the count is smaller than the smallest even count yet, we update min even count
                if(count < minEvenFreq)
                    minEvenFreq = count;
            }

        }
        
        
        return maxOddFreq-minEvenFreq;
    }


int main(){
	std::string inputString = "aaaaabbc";
	std::cout << "input string: " << inputString << "\n";
	std::cout << "maximum odd minus even difference: " << maxDifference(inputString) << "\n";

	return 0;

}
