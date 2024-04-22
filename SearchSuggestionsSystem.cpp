/*

1268. Search Suggestions System

You are given an array of strings products and a string searchWord.

Design a system that suggests at most three product names from products after each character of searchWord is typed. 
Suggested products should have common prefix with searchWord. 
If there are more than three products with a common prefix return the three lexicographically minimums products.

Return a list of lists of the suggested products after each character of searchWord is typed.


Constraints:

1 <= products.length <= 1000
1 <= products[i].length <= 3000
1 <= sum(products[i].length) <= 2 * 104
All the strings of products are unique.
products[i] consists of lowercase English letters.
1 <= searchWord.length <= 1000
searchWord consists of lowercase English letters.




Approach:

This solution involves the use of Tries.
A TrieNode and Trie classes have been created. Each TrieNode will store an array of 26 TrieNodes corresponding to the possible 26 letters in the alphabet.
Each TrieNode stores a boolean indicating if the current TrieNode represnet the end of a full word.

We'll create a Trie tree using the list of product names provided to us. Then for each increasing prefix of the searchword passed as an argument
we'll recursively traverse the TrieTree in alphabetical order starting from the last prefix letter and we'll create a list wit the first three
complete words we come across. After the third complete word we stop the tree traversal and add the list of three words to a final list of lists.



*/

#include<iostream>
#include<stack>
#include<vector>
#include<memory>

//class TrieNode is a tree node with a children vector of TireNodes, a boolean endOfWord variable to signal the current TrieNode the end of a 
//word. It also had a constructor that initializes the children vector to be of size 26 corresponding to 26 letters in the alphabet and 
//endOfWord to false.
class TrieNode{
public:
	std::vector<TrieNode*> children;
	bool endOfWord;
	TrieNode()
		: children(26,nullptr), endOfWord(false) {}
};


//class Trie represents a Trie tree. It is an aggregation of TrieNodes. 
//it has an insert, getThreeWords, and suggestedProducts methods.
//It has as a attributes root and current, both pointers to TrieNodes, where root represents the top of the tree and current represents
//a TriteNode pointer used to traverse the tree
class Trie{
	private:
		TrieNode* root;
		TrieNode* current;
	public:
		Trie():root(new TrieNode), current(nullptr)
		{}

		//insert receives a string word that gets added to the tree letter by letter
		void insert(std::string& word){
			current = root;
			//we iterate over the letters in the word
			for(char& c: word){
				//of the letters is already a child of the current TrieNode, we have current move to ot
				if(current->children[c-97]!=nullptr)
					current = current->children[c-97];
				//if the current letter has doesnt have c as a child, we create a new TrieNode for it and then
				//current move to it
				else{
					current->children[c-97] = new TrieNode;
					current = current->children[c-97];
				}
			}
			//after inserting the last letter in the word we mark its TrieNode as set its endOfWord attribute to true
			current->endOfWord = true;
		}


	//getThree words is a mehtod that receives the root of the tree (or subtree), runningWord which is a string representing the current
	//word being created as the Trie tree gets traversed in alphabetical order, and a runninList vector of strings that will store
	//the first three complete words encountered 
	void getThreeWords(TrieNode* root, std::string& runningWord, std::vector<std::string>& runningList){
		if(runningList.size() == 3) return ; //if we've already obtained three complete words we exit
		if(root->endOfWord) runningList.push_back(runningWord); //if we reach a complete word we store it

		//this for loop will iterate over the 26 possible letters in order and will continue expanding runningWord with characters available
		for(int i=0; i<26; ++i){
			if(runningList.size()==3) break;
			else if(root->children[i]!=nullptr){ //this is the case where the current letter has the ith letter as its child
				runningWord.push_back(i+97); //if so we add it to runningWord
				//we recursively move to the TrieNode child corresponding to the ith letter
				getThreeWords(root->children[i], runningWord, runningList);
				//back from getThreeWords we remove the letter we added so we can create a different runningWord
				//based on a different expanding letter
				runningWord.pop_back(); 
			}
		}
		return ;
	}


	//suggestedProducts will return a list of lists of product names that have the same prefix as the searchWord for each possible
	//prefix of searchWord.
	//it receives a list of product names, a searhcWord, and a list of list of strings.
	//all parameters are passed by reference to avoid copies when during the return process
        void suggestedProducts(std::vector<std::string>& products, std::string& searchWord, std::vector<std::vector<std::string>>& returnList){
                std::string tempPrefix; //this will store the current searchWord's prefix
                std::vector<std::string> runningList; //this is the current list corresponding to the current prefix
                TrieNode* startingNode=root; 
                for(auto& c: searchWord){ //we iterate over the letters in searchWord expanding the prefix for each iteration
                        tempPrefix.push_back(c); //expand prefix
                        startingNode = startingNode->children[c-97]; //we check if current TrieNode has a child with new letter added
									//to the prefix
                        if(startingNode==nullptr){ //if current TrieNode did not have a child with the new letter than there are no
						//product names with the current prefix

				//we fill ip returnList with empty lists since there will be no product names
				//with subsequent larger prefixes
                                while(returnList.size()!=searchWord.size()) returnList.push_back({});
                                return ;
                        }
			//if there is a child with the new letter, we call getThreeWords to lookup for the three product names
			//with the same current prefix
			getThreeWords(startingNode, tempPrefix, runningList);
                       
			returnList.push_back(runningList); //we add the list to the list of lists
                        runningList.clear(); //clear the runningList so we can use it to find the new product names for the new prefix
                }
                return ;
        }


};





int main(){
	//define the list of product names and the search word
	std::vector<std::string> products{"mobile","mouse","moneypot","monitor","mousepad"};
	std::string searchWord = "mouse";

	Trie myTrie; //create the Trie object
	//insert the product names
	for(auto& w: products)
		myTrie.insert(w);

	//now we use suggestedProducts Trie object method to get the list of list of names of product with the same prefixes
	//as searhcWord
	std::vector<std::vector<std::string>> returnList;
	myTrie.suggestedProducts(products,searchWord, returnList);
	
	//now we print the list of lists
	for(auto& l: returnList){
		for(auto& w: l)
			std::cout<<w<<" ";
		std::cout<<"\n";
	}

	return 0;

}


