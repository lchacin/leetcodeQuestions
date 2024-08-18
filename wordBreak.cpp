/*

139. Word Break

Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated sequence of one or more dictionary words.

Note that the same word in the dictionary may be reused multiple times in the segmentation.


Constraints:
1 <= s.length <= 300
1 <= wordDict.length <= 1000
1 <= wordDict[i].length <= 20
s and wordDict[i] consist of only lowercase English letters.
All the strings of wordDict are unique.


*/


#include<iostream>
#include<unordered_set>
#include<vector>




void f(std::string& word, int startingIndex, std::unordered_set<std::string>& wordMap, std::vector<std::vector<int>>& substringChecked, std::vector<bool>& validStart, bool& success){
        //we check if the startingIndex reached the end of original string
        //this means that we were able to partition the string into words in the dictionary
        if(startingIndex == word.size()){
            success = true; //set success to true
        }
        else{ //the case where we haven't reached the end of the original string

            //this for loops over the remaining characters in the string, which are supposed to 
            //be a potential ending character for a word in the dictionary with the starting index
            //being startingIndex
            //we loop as long as we haven't reached the last character in the original string,
            //success is not true (no partition of the strong into words in the dictionary has been found)
            //and the current character is not a character for which no valid partition of the remaining 
            //characters is successful with startingIndex as the starting index.
            for(int endingIndex = startingIndex; endingIndex < word.size() && !success && validStart[startingIndex]; ++endingIndex){
                //the case we haven't checked if the substring from startingIndex to endingIndex
                //is a word in the dictionary
                if(substringChecked[startingIndex][endingIndex] == -1){
                    //we check if the substring from startingIndex to endingIndex is a word in the dictionary
                    //be checking if it is contained in the hash table storing dictionary words
                    //the matrix substringChecked will now be 1 or 0 depending if the substring was in the
                    //dictionary or not
                    substringChecked[startingIndex][endingIndex] = 
                                wordMap.contains(word.substr(startingIndex, endingIndex-startingIndex+1));
                }

                //if the substring is a valid dictioinary word and we haven't yet encountered
                //a valid partition, we include the current valid substring in our partition and
                //enter f recursively with endingINdex+1 as the new starting index for the new
                //substring to be built
                if(substringChecked[startingIndex][endingIndex] && !success){
                    f(word, endingIndex+1, wordMap, substringChecked, validStart, success);
                }
            }

            //if we reached here it means that now valid parition can be made with a substring
            //starting at startingIndex.
            //this will allows us to avoid checking solutions that have startingIndex as the starting index
            validStart[startingIndex] = false;
        }
    }

    bool wordBreak(std::string& s, std::vector<std::string>& wordDict) {
        bool success = false; //boolean to indicate if a solution was found

        //substringChecked is matrix of {-1,0,1} entries that tell us if a subtring starting at
        //row index and ending at column index is a valid substring (1) or not (0). It will initially
        //store -1s to represent that a given substring has never been checked
        std::vector<std::vector<int>> substringChecked(s.size(), std::vector<int>(s.size(), -1));
        
        //we create a hash table storing the words in the wordDict vector. Doing so allows of O(1) search
        std::unordered_set<std::string> wordMap(wordDict.begin(), wordDict.end(), success);

        //boolean vector telling us if from a given starting index for a substring, a valid partition
        //of the original string into dictionary words is possible
        //it helps us avoid doing repeated work
        std::vector<bool> validStart(s.size(), true);


        f(s, 0, wordMap, substringChecked, validStart, success);
        return success;

    }



int main(){

	std::string s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";

	std::vector<std::string> wordDict{"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"};
	
	std::cout<< "wordDict: ";
	for(auto& word: wordDict)
		std::cout<< word <<", ";
	std::cout << std::endl;
	
	std::cout << std::boolalpha << "Can " << s << " be broken into a partition of dictionary words? : " << wordBreak(s, wordDict) << "\n";

	
	

	return 0;


}
