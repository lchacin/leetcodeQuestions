/*

Group the People Given the Group Size They Belong To


There are n people that are split into some unknown number of groups. 
Each person is labeled with a unique ID from 0 to n - 1.

You are given an integer array groupSizes, where groupSizes[i] is the size of the 
group that person i is in. For example, if groupSizes[1] = 3, then person 1 must be in a group of size 3.

Return a list of groups such that each person i is in a group of size groupSizes[i].

Each person should appear in exactly one group, and every person must be in a group. 
If there are multiple answers, return any of them. 
It is guaranteed that there will be at least one valid solution for the given input.


Constraints:

groupSizes.length == n
1 <= n <= 500
1 <= groupSizes[i] <= n



*/


#include<iostream>
#include<map>
#include<vector>



std::vector<std::vector<int>> groupThePeople(std::vector<int>& groupSizes) {
        //we create an AVL tree with keys equal to the group
        //the group size
        std::map<int, std::vector<int>> map;
        
        int i,j; //looping variables

        //we iterate over the group sizes of each person
        for(i=0; i<groupSizes.size(); ++i){
            //if the group size is already in the AVL tree
            //we add the person to the group
            if(map.contains(groupSizes[i]))
                map[groupSizes[i]].push_back(i);
            
            //otherwise we add the new group size to the AVL with
            //the person
            else map[groupSizes[i]] = {i};
        }

        //out of the for loop the AVL tree groups each person
        //by their their group size

        //we create a list of lists that will store each
        //group of the size corresponding to the size each 
        //person belongs to
        std::vector<std::vector<int>> ListOfLists;

        //we loop over the key-value pairs in the AVL tree
        for(auto& pair: map){
            while(pair.second.size()!=0){
                //we create a group to be added to ListOfLists
                std::vector<int> group;

                //the size of the group will be the value of the 
                //current key, and will fill it people from the 
                //list corresponding to that key 
                for(j=0; j<pair.first; ++j){
                    group.push_back(pair.second.back());
                    pair.second.pop_back();
                }

                //once the group is filled up to the size of the key
                //we add it to the ListOfLists
                ListOfLists.push_back(group);

                //we continue iterating until the list of people
                //corresponding to the current key is empty
            }
        }

        return ListOfLists;
    }



int main(){

	std::vector<int> groupSizes{3,3,3,3,3,1,3};

	auto groups = groupThePeople(groupSizes);

	std::cout << "{";
	for(auto& group: groups){
		std::cout << "{";
		for(auto& x: group) std::cout <<x <<" ";
		std::cout << "} ";
	}
	std::cout << "}";


	return 0;
}

