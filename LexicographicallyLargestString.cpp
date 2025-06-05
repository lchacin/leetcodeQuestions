#include<iostream>


std::string answerString(std::string word, int numFriends) {
        //the case the string is one character long
        if(word.size()==1 || numFriends ==1) return word;

        //the case the largest string can only be one character long
        else if(word.size() == numFriends){
            char c = 'a';
            for(auto& letter: word){
                if(letter > c)
                    c=letter;
            }
            return std::string(1,c);
        }

        //start and end are the starting and ending indexes of the current
        //candidate for lexicographically largest substring
        int start=0, end=1;

        //temp1 and temp2 are used as index runners when comparing two substrings that
        //start with the same character
        int temp1, temp2;

        //finalWord will store the final answer and tempWord will be used for the candidates 
        //generated as we parse the entire string
        std::string finalWord = word.substr(start,1);
        std::string tempWord = "";

        while(end < word.size()){
            if(word[end] < word[start]){
                if(word.size() - (end-start+1) == numFriends - 1){
                    tempWord = word.substr(start, end-start+1);
                    if(tempWord > finalWord){
                        finalWord = tempWord;
                    }
                    //the reason start is the next character after end is because in this case we
                    //reached the limit but the character at end is less than the character at start
                    //hence starting the new word from end is futile since we know already that a word
                    //starting from that character will always be lexicographically less than the word 
                    //we just created starting from start
                    start=end+1;
                    end=start+1;
                }
                else ++end;
            }
            else if(word[end] > word[start]){
                start=end;
                end= start+1;
            }

            //the case the starting and ending characters are the same
            else{
                //the case we word[start:end] reached the largest possible partition size
                if(word.size() - (end-start+1) == numFriends - 1){

                    tempWord = word.substr(start, end-start+1);
                    //we update finalWord if tempWord is lexicographically larger
                    if(tempWord > finalWord){
                        finalWord = tempWord;
                    }
                    //start redefined to end because in this case we reached the limit but the
                    //start and end characters are the same. Therefore, the next word to consider could
                    //start from the end character
                    start=end;
                    end=start+1;
                        
                }

                //the partition hasn;t reached its max size, so we iterate over characters
                //ahead of start and end, respectively, and compare charcaters until we
                //determine which between the substrings starting from start or end is larger
                else{
                    //temp1 and temp2 start from the character after start and end
                    temp1 = start+1;
                    temp2 = end+1;

                    //we continue iterating as long as temp2 hasn't reached the end of the string
                    while(temp2<word.size()){
                        //the case where the distance from start to temp2 reached the maximum partition size
                        //this happens when temp1 and temp2 are continually the same and temp2 value is too large
                        //in this case since the substring starting from start and end are indentical,  we
                        //consider their merged value
                        if(word.size() - (temp2-start+1) == numFriends - 1){
                            tempWord = word.substr(start, temp2-start+1);
                            if(tempWord > finalWord){
                                finalWord = tempWord;
                            }
                            start=end;
                            end=start+1;
                            break;
                        }

                        //the case the character at temp1 is smaller than of temp2
                        //therefore the substring starting from end is larger than that from start
                        else if(word[temp1] < word[temp2]){
                            //we update the candidate substring to start from end
                            //and update end to be temp2
                            start=end;
                            end = temp2;
                            break;
                        }
                        //the case the character at temp1 is larger than that at temp2, and hence
                        //we let the candidate substrings end be temp2
                        else if(word[temp1] > word[temp2]){
                            end = temp2;
                            break;
                        }

                        //increment temp1 and temp2 for the cases where characters at temp1 and temp2
                        //were the same
                        ++temp1;
                        ++temp2;
                    }

                    //the case temp2 went beyond the end of the word we update end to be the temp2
                    if(temp2 == word.size()) end=temp2;
                }
            }
        }

        //out of the while loop we check the last possible candidate that wasn't checked because end or temp2 reached the end
        //of the string
        tempWord = word.substr(start, end-start);
        finalWord = std::max(finalWord, tempWord);

        return finalWord;
    }





int main(){
	std::string word = "poplpk";
	int numFriends = 2;
	std::cout << "word: " << word << "\n";
	std::cout << "number of friends: " << numFriends << "\n";
	std::cout << "largest lexicographically substring: " << answerString(word, numFriends) << "\n"; 

	return 0;
}
