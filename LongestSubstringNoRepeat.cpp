#include<iostream>
#include<unordered_map>


int lengthOfLongestSubstring(std::string& s) {
        //maxLength will store the maximum length of subarray without repeated characters
        //runningLength will store the length of the current subarray without repeated characters
        //start will store the starting index of the current subarray 
        int maxLength = 0, runningLength = 0, start = 0;

        //hashmap with keys equal to an ASCII character and value equal to the index of the
        //last time the character was encountered in the string
        std::unordered_map<char,int> map;

        //we loop over the characters in the string
        for(int i = 0; i<s.size(); ++i){
            //if the character is not in the hash map or if the index of the last time
            //it was encountered was before the start of the current subarray
            if(!map.contains(s[i]) || map[s[i]] < start){
                //we add the key-value pair or update the index of the current character key
                map[s[i]] = i;
                ++runningLength; //update the size of the current subarray
            }

            //the case the current character is present in out current subarray
            else{
                //we update maxLength if the runningLength is greater
                if(runningLength > maxLength) maxLength = runningLength;

                //update start to be the index following the index of the character in the
                //subarray we have found to be equal to the current character
                start = map[s[i]] + 1;

                //update the runningLength to be the length from the current character to the
                //updated start
                runningLength = i - map[s[i]];

                //update the index of the previously enountered current character 
                //to be the current index
                map[s[i]] = i;
            }
        }

        return std::max(runningLength, maxLength);
    }



int main(){
	std::string s = "abcabcbb";
	std::cout << lengthOfLongestSubstring(s) << "\n";

	return 0;
}
