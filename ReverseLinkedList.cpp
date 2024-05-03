/*

206. Reverse Linked List

Given the head of a singly linked list, reverse the list, and return the reversed list.


Approach:

We take the iterative approach using a stack. We create a stack and add to it a null pointer.
We traverse the Linked list storing the nodes in the stack. Once we get the last node
we assign to its next pointer the address of the node at the top of the stack.
We then pop the node on the stack and repeat the process with the node popped until the stack is empty.
The last node will be assigned null pointer as its next address since null pointer was initially added 
to the stack at initialization.

*/



#include<iostream>
#include<stack>


struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
 };



ListNode* reverseList(ListNode* head){
	//the case where the linked list has no nodes
	if(head==nullptr) return nullptr;

	//we create a stack where the list nodes will be stored
	std::stack<ListNode*> myStack;
	myStack.push(nullptr); //we add null pointer so when we start popping the nodes from the stack
				//the last node will get nullptr assigned as its next pointer

	//we push the list nodes in the linked list until we reach the end of the list
	while(head!=nullptr){
		myStack.push(head);
		head=head->next;
	}

	//npw we set out new head as the last node pushed into the list
	head = myStack.top();
	ListNode* listRunner = nullptr; //a placeholder ListNode pointer to store the pointers popped from the stack
	
	//the while loop stores the node at the top of the stack, pops it, and lets the next pointer of the
	//popped node be the list node at the top of the stack
	while(myStack.size()!=1){
		listRunner = myStack.top();
		myStack.pop();
		listRunner->next = myStack.top();
	}

	return head; //we return the updated head of the list
}



int main(){
	ListNode* head = new ListNode(0);
	ListNode* copyHead = head;
	for(int i=1; i<10; ++i){
		head->next = new ListNode(i);
		head = head->next;
	}

	head = copyHead;
	std::cout<<"Original List: ";
	while(head!=nullptr){
		std::cout<<head->val<<" ";
		head = head->next;
	}
	std::cout<<"\n";

	head=reverseList(copyHead);

	std::cout<<"Reversed List: ";
	while(head!=nullptr){
		std::cout<<head->val<<" ";
		head = head->next;
	}
	std::cout<<"\n";

	return 0;
}
