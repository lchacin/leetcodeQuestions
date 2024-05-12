/*

Maximum Twin Sum of a Linked List

In a linked list of size n, where n is even, the ith node (0-indexed) of the linked list is known as 
the twin of the (n-1-i)th node, if 0 <= i <= (n / 2) - 1.

For example, if n = 4, then node 0 is the twin of node 3, and node 1 is the twin of node 2. 
These are the only nodes with twins for n = 4. The twin sum is defined as the sum of a node and its twin.

Given the head of a linked list with even length, return the maximum twin sum of the linked list.


Constraints:

The number of nodes in the list is an even integer in the range [2, 105].
1 <= Node.val <= 105


Approach:

We'll iterate through the entire list to calculate its size.
Then we'll iterate over the first half of the linked list storing the value of each
node in a stack. 

For the second half of the linked list for every node will calculate the sum of the value of
the node and the value at the top of the stack. It the sum is larger than the current value
of the maximum twin sum, we update it, pop the top of the stack, and move to the next node in the
list.


The keu is the use of the stack since its FIFO storage allows us to explore the value in the
nodes of the first half of the list in reverse order.

*/


#include<iostream>
#include<stack>


//a struct representing the node of a linked list
//each object stores an integer and a pointer to the next linked list node
struct ListNode {
     int val;
     ListNode *next;

     //default constructor
     //defines val to zero and assigns nullptr to the next pointer
     ListNode() : val(0), next(nullptr) {}

     //constructor with int parameter passed for val
     //it assigns the integer parameter to x and assigns nullptr to next
     ListNode(int x) : val(x), next(nullptr) {}

     //constructor with integer and address of next linked list node
     //assigns the integer parameter to val and the address to the next ListNode to next
     ListNode(int x, ListNode *next) : val(x), next(next) {}
};


//pairSum is function that receives a pointer to the head of a linked list as paraneter
//it calculates the maximum twin sum of the linked list and returns its value as an integers
//the length of the linked list must be even and its size must be at least 2. The linked list
//must store integers
int pairSum(ListNode* head) {
	//we define a pointer to a ListNode that will serve to traverse the linked list
	ListNode* listRunner=head;
	int i, size=0; //i will be used as a for loop iterator index and size will be the size of the list

	//we iterate through the entire list and record its size
	while(listRunner!=nullptr){
		++size;
		listRunner = listRunner->next;
	}

	listRunner=head;

	//we declare a stack to store the values in the first half of the list
	std::stack<int> firstHalf;
	int middle=size/2; //value of the middle index of the list

	//we iterate over the first half of the linked list and store the values in each
	//of the nodes in the stack
	for(i=0; i<middle; ++i){
		firstHalf.push(listRunner->val);
		listRunner = listRunner->next;
	}

	int twinMax=0; //declare an integers variable to store the maximum twin sum

	//we restart the iteration of the list until the end
	while(listRunner!=nullptr){
		//we update twinMax if the sum of the top of the stack and the current 
		//node is larger than the current twinMax
		if(listRunner->val + firstHalf.top() > twinMax)
			twinMax = listRunner->val + firstHalf.top();
		listRunner = listRunner->next; //move to the next node
		firstHalf.pop(); //remove the top of the stack
	}

	return twinMax;

}



int main(){

	ListNode* head = new ListNode(5);
	head->next = new ListNode(4);
	head->next->next = new ListNode(2);
	head->next->next->next = new ListNode(1);

	std::cout<<"Maximum twin sum: "<< pairSum(head)<<"\n";


	return 0;


}
