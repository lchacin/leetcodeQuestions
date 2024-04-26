/*

1456. Maximum Number of Vowels in a Substring of Given Length

Given a string s and an integer k, return the maximum number of vowel letters in any substring of s with length k.
Vowel letters in English are 'a', 'e', 'i', 'o', and 'u'.

Constraints:

1 <= s.length <= 105
s consists of lowercase English letters.
1 <= k <= s.length


Approach:

In order to keep the solution as O(n), we checking each letter leaving and entering the sliding window and update
the maximum number of vowels in a window of size k if the total number of vowels in the window exceed the maximum
number of vowels obtained so far.

To check if a letter is a vowel, we create a hash map with the five vowels 'a', 'e', 'i', 'o' and 'u'. If the 
character being tested is in the hash map this means it is a vowel, otherwise it is a consonant.


*/



#include<iostream>
#include<unordered_set>
#include<numeric>


int maxVowels(std::string& s, int& k) {
	//a hash map containing the vowels in the dictionary
        std::unordered_set<char> vowelsMap{'a','e','i','o','u'};

	//the case where the sliding window is the same size as the string itself
	//in this case merely count the number of vowels in the string
        if(s.size()==k) 
		//we use accumulate to counter the number of vowels
		//it will iterate from the beginning to the end of the string using its iterators
		//we pass to it a binary lambda that receives as first argument an accumulator value and the second argument
		//will be the current character in the stirng being tested. It increases the accumulator is the characters 
		//is a vowel
		//in its capture clause we pass the vowelsMap hash map by reference so the lambda can have to it and use
		//it to check for vowels
		return std::accumulate(s.begin(), s.end(), 0,
            [&vowelsMap](int&& acc, char& c)->int { acc+=vowelsMap.contains(c); return acc;} );
       
	//this is the case where the sliding window is size 1.
	//In this case the maximum number of characters in the sliding window is 1. Hence we merely check if
	//any of the characters is a vowel, if so we return 1 immediately. If none are vowels, we return 0
	if(k==1){
            for(auto& c: s)
                if(vowelsMap.contains(c)) return 1;
            return 0;
        }



        int start=0, end=k-1; //start and end will be the index for the start and end of the sliding window
        int maxVowels = 0; //maxVowels will keep the maximum number of vowels encountered in a sliding window 

	//totalVowels stores the total number of vowels in a sliding window
        int totalVowels = std::accumulate(s.begin(), s.begin()+end+1, 0,
            [&vowelsMap](int&& acc, char& c)->int { acc+=vowelsMap.contains(c); return acc;} );
        
	
        maxVowels=totalVowels;
        

	//the while loop will iterate over every possible sliding window of size k
	//for each iteration is removes the first element of the sliding window and adds the next right element to it
	//it tallies the total number of vowels in the sliding window, and it updates maxVowels if the totalVowels exceeds maxVowels
        while(end<s.size()-1){
            if(vowelsMap.contains(s[start])) --totalVowels;
            ++start;
            ++end;
            if(vowelsMap.contains(s[end])) ++totalVowels;
            if(totalVowels>maxVowels){
                maxVowels = totalVowels;
                if(maxVowels == k) break; //this is an optimization. Since maxVowels can't exceed k, we exit the while
					//loop the very momemnt maxVowels hits k and desist from checking the remaining sliding windows
            }
        }

        return maxVowels;
    }



int main(){
	std::string s="abciiidef";
	int k=3;

	std::cout<<"Total number of vowels in \""<<s<<"\" : "<<maxVowels(s,k)<<"\n";

	return 0;
}
