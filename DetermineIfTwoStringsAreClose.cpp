
/*


1657. Determine if Two Strings Are Close


Two strings are considered close if you can attain one from the other using the following operations:

Operation 1: Swap any two existing characters.
For example, abcde -> aecdb
Operation 2: Transform every occurrence of one existing character into another existing character, and do the same with the other character.
For example, aacabb -> bbcbaa (all a's turn into b's, and all b's turn into a's)
You can use the operations on either string as many times as necessary.

Given two strings, word1 and word2, return true if word1 and word2 are close, and false otherwise.



Constraints:

1 <= word1.length, word2.length <= 105
word1 and word2 contain only lowercase English letters.




Approach:


The first observation is that swapping two letters or converting two different letters into another letter and vice-versa, will not change
the overall list of frequencies. That is, if there is a letter in the first word that has a frequency of 5, for example, there has to be 
another letter in the second word with a frequency of 5. And, if there is not a letter in the first word with a frequency of 6, for example, 
there can't be a letter of frequency 6 in the second word.


The second observation is that both the first and second word must have the same distinct letters. That is, neither of the operations will
change the distinct letters that a word has.


Based on these two operationis there are two aspects to check when deciding if the two words can be obtained using the two listed operations:
They need to have the same distinct letters and the list of frequencies of both words must be the same


*/




#include<iostream>
#include<unordered_map>



bool closeStrings(std::string& word1, std::string& word2) {

	//map1 and map2 are hash maps that will store as key a letters of word1 and word2 accordingly,
	//and values will be the frequency of each letter
        std::unordered_map<char, int> map1, map2;


	//we iterate over word1 and word2 storing key-value pairs and updating frequencies of each letter
        for(auto& c: word1){
                if(map1.contains(c)) ++map1[c];
                else map1[c]=1;
        }

        for(auto& c: word2){
            if(map2.contains(c)) ++map2[c];
            else map2[c]=1;
        }

	
	// here we check the condition that both words should have the same distinct letters
	//we iterate through map1 and make sure that map2 contains the same keys
        for(auto& p: map1){
            if(!map2.contains(p.first)) return false; //we return false if map2 doesn't contain a key (a letter) present in map1
        }


	//now we proceed to check the condition that the list of frequencies need to be the same


	//map11 and map22 are hash maps with key being the distinct frequencies of the 
	//letters in each of word1 and word2 respectively, and value will be the number of times
	//each frequency takes place. e.g if in the original word letters a and b (and no other letter) have frequencies of 3,
	//then map11 will have a key-value pair of key=3 and value=2 
        std::unordered_map<int,int> map11, map22;


	//we iterate over map1 and map2 and store the value (the frequency of a letter) in their key-value pairs as the
	//the keys in map11 and map22 and the value will be the number times these frequencies take place 
        for(auto& p: map1){
                if(map11.contains(p.second)) ++map11[p.second];
                else map11[p.second]=1;
        }

        for(auto& p: map2){
                if(map22.contains(p.second)) ++map22[p.second];
                else map22[p.second]=1;
        }

	//if the list of frequencies are the same then map11 and map22 will be equal.
	//soo we return the truth value of the equality comparison of map11 and map22
	return map11 == map22; 
}


int main(){
	std::string s1("uau"), s2("ssx");

	std::cout<<std::boolalpha<<closeStrings(s1,s2)<<"\n";



	return 0;

}
