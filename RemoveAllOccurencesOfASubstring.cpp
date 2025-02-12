/*

1910. Remove All Occurrences of a Substring


Given two strings s and part, perform the following operation on s until all occurrences of the substring part are removed:

Find the leftmost occurrence of the substring part and remove it from s.
Return s after removing all occurrences of part.

A substring is a contiguous sequence of characters in a string.


Constraints:

1 <= s.length <= 1000
1 <= part.length <= 1000
s​​​​​​ and part consists of lowercase English letters.

*/


#include<iostream>
#include<stack>


std::string removeOccurrences(std::string& s, std::string& part) {
        //the case string s is smaller than part
        if(s.size()<part.size()) return s;


        std::stack<char> myStack;
        std::string tempLetters;
        auto iter = s.begin();
        int i; //looping variable



        while(iter != s.end()){
            //add new letter to the back of tempLetters
            tempLetters.push_back(*iter);

            //the case  tempLetters went beyond the size of part
            if(tempLetters.size() > part.size()){
                //place the letter in front of tempLetters in the stack,
                //and remove it
                myStack.push(tempLetters.front());
                tempLetters.erase(0,1);
            }

            //move to the next character in string s
            ++iter;

            //now we check if the word stored in tempLetter is the word we want to remove

            //case tempLetters stores the word to remove
            if(tempLetters == part){
                //now we remove the word from tempLetter and fill it
                //with letters from the stack
                for(i = 0; i<part.size() && !myStack.empty(); ++i){
                    tempLetters.pop_back(); //remove last letter
                    tempLetters.insert(tempLetters.begin(),myStack.top()); //add new front letter
                    myStack.pop(); //remove top letter from stack
                }

                //case we exited the for loop because the stack became empty 
                //we continue removing the remaining letters from the word to remove
                while(i !=part.size()){
                    tempLetters.pop_back();
                    ++i;
                }
            }
        }

        //out of the while loop we are done removing the word to remove
        //from the given string and include any remaining values left in the stack

        while(!myStack.empty()){
            tempLetters.insert(tempLetters.begin(),myStack.top());
            myStack.pop();
        }


        return tempLetters;

    }


int main(){

	std::string s = "daabcbaabcbc";
	std::string part = "abc";

	std::string resultingString = removeOccurrences(s, part);

	std::cout << resultingString << "\n";

	return 0;
}
