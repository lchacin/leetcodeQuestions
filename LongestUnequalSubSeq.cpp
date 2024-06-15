/*


You are given a string array words and a binary array groups both of length n, where words[i] is associated with groups[i].

Your task is to select the longest alternating subsequence from words. A subsequence of words is alternating if for any two 
consecutive strings in the sequence, their corresponding elements in the binary array groups differ. Essentially, 
you are to choose strings such that adjacent elements have non-matching corresponding bits in the groups array.

Formally, you need to find the longest subsequence of an array of indices [0, 1, ..., n - 1] denoted as 
[i0, i1, ..., ik-1], such that groups[ij] != groups[ij+1] for each 0 <= j < k - 1 and then find the words 
corresponding to these indices.

Return the selected subsequence. If there are multiple answers, return any of them.

Note: The elements in words are distinct.


Constraints:
1 <= n == words.length == groups.length <= 100
1 <= words[i].length <= 10
groups[i] is either 0 or 1.
words consists of distinct strings.
words[i] consists of lowercase English letters.



Approach:

We use DP. 

The subproblem is defined as
f(n-1)=1
f(i_j) = f(i_j+1) + 1 where  groups[k]==groups[i_j] for i_j <  k < i_j+1 and groups[i_j+1] != groups[i_j]


That is we work backwards from the end of groups. At any index i we let f[i] be one more than the next value in f
that its corresponding index is an opposite binary value than that at index i


*/



#include<iostream>
#include<vector>


std::vector<std::string> getLongestSubsequence(std::vector<std::string>& words, std::vector<int>& groups) {
        const int N=words.size(); //N is the length of the words vector
        
        //the case the words array has only one word. We returns this word
        if(N==1) return {words[0]};

        //we create a vector of length N to store the lengths of the maximum alternating 
        //subsequences starting from each index
        std::vector<short> f(N,-1);
        f[N-1]=1; //the initial condition is that the maximum alternating sequence starting
                    //from the last words is 1
        short i,j; //indexes to iterate over groups

        //outer for loop iterates over groups vector in reverse order
        for(i=N-2; i>-1; --i){
            for(j=i+1; j<N; ++j){ //iterates over groups starting from index i+1 until the end
                if(groups[j]!=groups[i]){ //j is first index having a binary value opposite to 
                                            //the one at index i
                    f[i]=f[j]+1; //we let the length of the maximum alternating subsequence be
                                //one more than the one starting at index j
                    break;
                }
            }

            //if f[i] is still -1 it means in the inner for-loop we didn't find a binary value after
            //index i that was opposite to that of index i
            if(f[i]==-1) f[i]=1; //so the maximum length of an alternating subsequence starting at i is 1 
        }

        //out of the for loops, f now stores the maximum lengths of the alternating subsequences
        //starting at each corresponding index

        //we create a vector of strings to store the strings in the maximum length alternating subsequence
        std::vector<std::string> alternatingSubSeq;
        alternatingSubSeq.reserve(f[0]); //we make sure to reserve enough memory at compile-time to store
                                        //all the needed strings. f[0] stores the maxmimum length
        alternatingSubSeq.push_back(words[0]); //we insert the first word since it always be part of maximum
                                                //length alternating subsequences
        
        //i iterates over the words in the maximum length alternating subsequence
        for(i=0; i<N; ++i){
            for(j=i+1;j<N;++j){ //j is an index runner that searches for the next word in the maximmum length
                                //alternating subsequence
                if(f[j]==f[i]-1){ //if the maximum length is one less than that at index i it means
                                //we've found the next word in the maximum length alternating subsequence
                    
                    //we use std::move to move the string into alternatingSubSeq and not perform a copy
                    alternatingSubSeq.push_back(std::move(words[j])); //we add the word to our string vector
                    break; //we break to move to the next word
                }
            }
            //we move i all the way up to j so we can continue looking for the next word in the subsequence
            i=j-1; //we let i be j-1 because the outer for-loop will increase i by 1 as well
        }

        //out of the for-loop alternatingSubSeq contains all the strings in the maximum length alternating
        //subsequence

        return alternatingSubSeq;
    }




int main(){
	std::vector<std::string> words{"a","b","c","d","asf","qwe","ry","cxvb","rey","nrty"};
	std::vector<int> groups{1,0,1,1,0,0,1,1,1,1};

	std::vector<std::string> longestAlternatingSubSeq(getLongestSubsequence(words,groups));

	std::cout<<"Longest Unequal Subsequence is: ";
	for(auto& word: longestAlternatingSubSeq)
		std::cout<<word<<", ";
	std::cout<<"\n";


	return 0;
}

