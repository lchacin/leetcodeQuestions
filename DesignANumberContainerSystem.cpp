/*

2349. Design a Number Container System

Design a number container system that can do the following:

Insert or Replace a number at the given index in the system.
Return the smallest index for the given number in the system.
Implement the NumberContainers class:

NumberContainers() Initializes the number container system.

void change(int index, int number) 
Fills the container at index with the number. 
If there is already a number at that index, replace it.

int find(int number) 
Returns the smallest index for the given number, 
or -1 if there is no index that is filled by number in the system.


Constraints:

1 <= index, number <= 109
At most 105 calls will be made in total to change and find.

*/


#include<iostream>
#include<unordered_map>
#include<set>


class NumberContainers {
public:
    std::unordered_map<int, int> indexToNumber;
    std::unordered_map<int,std::set<int>> numberToIndex;
    NumberContainers(){
    }
    
    void change(int index, int number) {
        //the case the index has no number assigned to it
        if(!indexToNumber.contains(index)){
            //we add the keyvalue pair index-number to the indexToNumber
            //hashmap
            indexToNumber[index]=number;

            //now we add the index to the avl tree of indexes corresponding
            //to number

            //the case number has never been added
            if(!numberToIndex.contains(number))
                numberToIndex[number] = {index};
            //the case number is in the NumberContainer so we add
            //index to its avl tree of indexes
            else
                numberToIndex[number].insert(index);
        }

        //the index already has a number assigned to it
        else{
            //we first go to the avl tree of the number currently
            //assigned to index, and have index be removed from
            //it avl tree
            numberToIndex[indexToNumber[index]].erase(index);

            //we check if the avl tree of the number that previously
            //was stored at index, is empty. If so, we remove
            //that number from the numberToIndex hash map
            if(numberToIndex[indexToNumber[index]].empty())
                numberToIndex.erase(indexToNumber[index]);
            
            //now we assign the new number to the index
            indexToNumber[index] = number;

            //and we add the index to the number's avl tree
            //the case the number is already in the numberToIndex hash map
            if(numberToIndex.contains(number))
                numberToIndex[number].insert(index);
            //otherwise we insert the number with an avl tree with index
            else
                numberToIndex[number] = {index};
        }
    }
    

    int find(int number) {
        //we see if number is in the numberToIndex hashmap
        if(numberToIndex.contains(number))
            //if so we return the smallest index in it's avl tree
            //of indexes
            return *numberToIndex[number].begin();

        //if the number is not in the hashmap
        return -1;
    }

    void printContainer(){
	for(auto& pair: indexToNumber) std::cout << "(" << pair.first << "," << pair.second << ") ";
	std::cout << "\n";
    }
};



int main(){
	NumberContainers  myContainer;
	
	//perform the following operations
	// ["NumberContainers","change","change","change","find","change","find","change","find"]
	//[[],[1,50],[2,60],[3,70],[50],[3,80],[50],[1,90],[50]]

	myContainer.change(1,50);
	myContainer.printContainer();
	myContainer.change(2,60);
	myContainer.printContainer();
	myContainer.change(3,70);
	std::cout << "index of " << 50 << " = " << myContainer.find(50) << std::endl;
	myContainer.printContainer();
	myContainer.change(3,80);
	myContainer.printContainer();
	std::cout << "index of " << 50 << " = " << myContainer.find(50) << std::endl;
	myContainer.printContainer();
	myContainer.change(1,90);
	myContainer.printContainer();
	std::cout << "index of " << 50 << " = " << myContainer.find(50) << std::endl;
	myContainer.printContainer();

	return 0;
}
