/*

131. Palindrome Partitioning

Given a string s, partition s such that every substring of the partition is a palindrome. 
Return all possible palindrome partitionings of s.


Constraints:

1 <= s.length <= 16
s contains only lowercase English letters.


*/


#include<iostream>
#include<vector>




//this a helper function checks if a substring of a string is a palindrome
    //its parameters are a string reference of the original string, and integer variables
    //storing the start and and ending indexes of the desired subtring
    bool isPalindrome(std::string& s, int startIndex, int endIndex){
        //loop checking that the starting and ending indexes have equal characters
        //as long as the startIndex is smaller than endIndex
        while(startIndex < endIndex){
            //if the corresponding characters are not the same then we immediately output false
            if(s.at(startIndex) != s.at(endIndex)) return false;
            else{ //the case the characters are the same
                //move startIndex forward and endIndex backward respectively to check the following
                //two characters
                ++startIndex;
                --endIndex;
            }
        }

        //out of the while loop it means the substring is a palindrome
        return true;
    }


    //method f searches for all possible palindrome partitions of a given string passed by reference
    //it also has as parameters the startingIndex of all the substrings to be checked
    //a vector of strings, currentPartition, by reference that stores the current palindrome partiion being generated
    //palinPartitions that stores all the palindrome partitions created thus far, and isPalinMatrix
    //that stores -1,0,1 to indicate whether subtring with a given starting and ending index is a palindrome
    //it serves to avoid repeating the palindrom checks for the same substring more than once
    void f(std::string& s, int startingIndex, std::vector<std::string>& currentPartition,
            std::vector<std::vector<std::string>>& palinPartitions, std::vector<std::vector<int>>& isPalinMatrix){
        
        //case where the starting index is one-past-last index, indicating that currentPartition
        //successfully stores a palindrome partition of the substring s
        if(startingIndex == s.size()){
            //we add the partition to the vector of palindrome partitions
            palinPartitions.push_back(currentPartition);
            return;
        }


        for(int i = startingIndex; i<s.size(); ++i){
            //first we see if we've already checked if the current substring is a palindrome.
            if(isPalinMatrix[startingIndex][i] == -1){ //the case we have not yet chcecked this substring before
                //we use the isPalindrome function to check and store the result so we don't have to check it again
                isPalinMatrix[startingIndex][i] = isPalindrome(s,startingIndex,i);
            }

            //case where the current substring is a palindrome
            if(isPalinMatrix[startingIndex][i] == 1){
                //we store the current substring into the current palindrome partition being constructed
                currentPartition.push_back(s.substr(startingIndex, i-startingIndex+1));

                //we recursively enter f again to check for addiitonal palindromes in the remaining substring 
                //beyonnd index i
                f(s, i+1, currentPartition, palinPartitions, isPalinMatrix);

                //back from f, all the possible palindrome partitions including the palindrome substring
                //starting at startingIndex and ending at i have been added to the vector of palindrome partitions

                //we remove the last palindrome created so the loop can continue searching for additional 
                //palindrome substrings starting at startingIndex but now ending at larger indexes than i
                currentPartition.pop_back();
            }
        }
    }

    std::vector<std::vector<std::string>> partition(std::string& s) {
        //this matrix will store boolean values corresponding to whether a substring starting
        //at index i and ending at index j is a palindrome
        std::vector<std::vector<int>> isPalinMatrix(s.size(), std::vector<int>(s.size(),-1));

        std::vector<std::vector<std::string>> palinPartitions; //vector containing vector of partitions
        std::vector<std::string> currentPartition; //to store a specific partition

        //f will find all all the possible palindrome partitions and store them in palinPartitions
        f(s,0, currentPartition, palinPartitions, isPalinMatrix);

        return palinPartitions;
    }




int main(){
	std::cout<<"Enter a string of length at most 16 with only a-z characters: ";
	std::string userInput;
	std::cin>>userInput;
	auto palinPartitions = partition(userInput);

	for(auto& partition: palinPartitions){
		for(auto& substring: partition)
			std::cout<< substring << " ";
		std::cout<<std::endl;
	}
	std::cout<<"\n";
	return 0;
}
