#include<iostream>
#include<queue> //for priority queue
#include<unordered_set> //for hash table
#include<vector>

class SmallestInfiniteSet {
private:
	int sequenceStart; //keeps the next element in the infinite sequence not in the minHeap
	int removedElement; //temporary variable to store the last element removed from the sequence or heap
	std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap; //will store the elements poppped from the sequence
	std::unordered_set<int> inHeap; //this hash table will be use to tell us what elements are in the minHeap in O(1)
public:
    SmallestInfiniteSet(): sequenceStart(1), removedElement(0),  minHeap(std::greater<int>{}), inHeap() {}


	//popSmallest removes the smallest element in the sequence, including those elements were once removed and added back
    int popSmallest() {
	//we first check if there are elements in the minHeap, since these should be popped first than those
	//that haven't ever been popped
	if(!minHeap.empty()){
		removedElement=minHeap.top(); //we store the smallest value in the minHeap
		minHeap.pop(); //we remove the smallest value in the minHeap
		inHeap.erase(removedElement); //we erase the value removed from the hash table since it is no longer in the minHeap
		return removedElement; 
	}
	//this is the case the minHeap is empty
	return sequenceStart++; //we return the next value in the infinite sequence and let sequenceStart be the next element
    }

	//addBack adds an element previously removed back into the sequence
	//if the element is already in the sequence it does nothing
    void addBack(int num) {
	//we check if num is in the minHeap or is a value in the sequence that has not been ever popped
	if(num >= sequenceStart || inHeap.contains(num)) return;
	
	//since num is not in sequence we added it back by adding it to the minHeap and recording its value in the inHeap hash table
	minHeap.push(num);
	inHeap.insert(num);
	
    }
};



int main(){
	SmallestInfiniteSet mySet;
	
	for(int i=0; i<10; ++i) std::cout<<mySet.popSmallest()<<" ";

	mySet.addBack(5);
	mySet.addBack(2);
	mySet.addBack(7);

	std::cout<<"\n";
	std::cout<<mySet.popSmallest()<<" ";
	std::cout<<mySet.popSmallest()<<" ";
	std::cout<<mySet.popSmallest()<<" ";
	std::cout<<mySet.popSmallest()<<" ";
	std::cout<<"\n";
	return 0;


}
