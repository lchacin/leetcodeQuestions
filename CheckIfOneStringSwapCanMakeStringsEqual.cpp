/*

170.Check if One String Swap Can Make Strings Equal

You are given two strings s1 and s2 of equal length. A string swap is an operation where you choose 
two indices in a string (not necessarily different) and swap the characters at these indices.

Return true if it is possible to make both strings equal by performing at most one string swap 
on exactly one of the strings. Otherwise, return false.


Constraints:

1 <= s1.length, s2.length <= 100
s1.length == s2.length
s1 and s2 consist of only lowercase English letters.


*/

#include<iostream>


bool areAlmostEqual(std::string& s1, std::string& s2) {
        //if the size of both strings are different then
        //no swapping will make them the same
        if(s1.size() != s2.size()) return false;

        //looping variable and variable to count
        //how many corresponding letters differ
        int i, count=0;

        //we iterate over both strings and count the number
        //characters that differ
        for(i=0; i<s1.size(); ++i)
            if(s1[i]!=s2[i]) ++count;

        //if no corresponding characters differed, we return true
        if(count == 0) return true;

        //if one or more than two correpsonding characters differ
        //then we won't be able to make both strings equal with only
        //one swap. We return false
        else if(count != 2) return false;

        //we iterate back from the start and look for the first characters
        //that differ, and then we search ahead for another character difference
        for(i=0; i<s1.size(); ++i){
            //found the first characters that differ
            if(s1[i]!=s2[i]){
                //loop to find the other two characters that differ
                for(int j=i+1; j<s2.size(); ++j){
                    //found the other two characters that differ
                    if(s1[j]!=s2[j])
                        //return true if the swap makes the corresponding characters
                        //equal.
                        return s1[i]==s2[j] && s2[i]==s1[j];
                }
            }
        }

        
        return true;
    }



int main(){
	std::string s1="bank", s2="kanb";
	std::cout << areAlmostEqual(s1,s2) << "\n";
	return 0; 
}
