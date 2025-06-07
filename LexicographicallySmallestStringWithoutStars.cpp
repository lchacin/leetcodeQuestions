#include<iostream>
#include<vector>
#include<queue>


std::string clearStars(std::string& s) {
        //this lambda will sort the pairs of character/index in the priority queue first in descending
        //order based on character ascii value and then in ascending index value
        auto comparator = [](std::pair<int,int>& p1, std::pair<int,int>& p2)->bool{
            if(p1.first < p2.first) return false;
            else if(p1.first == p2.first) return p1.second < p2.second;

            return true;
        };

        //this priority queue will be a min-heap for the pair of character and indexes generated
        //from the chracters in the string passed as argument
        std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, decltype(comparator)> minHeap;

        //this variable will store the size of the result string
        int returnStringSize = s.size();

        for(int i=0; i<s.size(); ++i){
            //the case we encounter an asterick
            if(s[i]=='*'){
                //case the minheap was empty. We merely change the star to a blank character
                if(minHeap.empty()){
                    s[i]=' ';
                    --returnStringSize;
                }

                //the case the minHeap is not empty. The top contains the character and index location
                //of the lexicographically smallest character so far encountered in the string
                //we change both the asterick and the smallest character into blank characters
                else{
                    auto tempPair = minHeap.top();
                    minHeap.pop();
                    s[i]=' ';
                    s[tempPair.second] = ' ';

                    returnStringSize -= 2;
                }
            }

            //the case we encountered an alphabet character, we add it to the minHeap with its index location
            else{
                minHeap.push({s[i],i});
            }
        }

        //out of the for loop, out string will now have blank characters scattered throuhgout, these will
        //be removed to return the smallest lexicographical string

        std::string returnString(returnStringSize,' ');
        int j=0;
        for(int i=0; i<s.size(); ++i){
            if(s[i] != ' ') returnString[j++] = s[i];
        }

        return returnString;
    }


int main(){
	std::string s = "abc*de*fgh*";

	std::cout << "input string: " << s << "\n";
	std::cout << "result: " << clearStars(s) << "\n";

	return 0;

}
