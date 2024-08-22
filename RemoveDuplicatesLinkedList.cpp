#include<iostream>


//ListNode is a node of a linked list
struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
 };


 ListNode* deleteDuplicates(ListNode* head) {
        //the case where the list is empty pr has only one node
        if(head==nullptr || head->next==nullptr) return head;

        //we create two nodes and assign them to the first two nodes
        ListNode *previousNode = head, *currentNode = head->next;;

        //we traverse the linked list with both nodes one after the other
        //so we can compare the value of two consecutive nodes
        //we stop when the current node reaches null pointer
        while(currentNode!=nullptr){
            //we check if the current and previous nodes have the same value
            if(currentNode->val == previousNode->val){ //duplicate value case
                //we have the previous node link to the node in front of
                //the current node
                previousNode->next = currentNode->next;
                delete currentNode; //deallocate the memory 
                currentNode = previousNode->next; //current node moves to the node ahead
            }
            else{ //the case where the value in both nodes is distinct
                //move each node one node forward
                previousNode = currentNode; 
                currentNode = currentNode->next;
            }
        }

        return head; //return the head of the original list
        
    }



int main(){
	//create list 1,1,2,2,3,3
	ListNode* head = new ListNode(1, new ListNode(1, new ListNode(2, new ListNode(2, new ListNode(3, new ListNode(3))))));

	head = deleteDuplicates(head);

	ListNode* listRunner = head;
	while(listRunner!=nullptr){
		std::cout << listRunner -> val <<", ";
		listRunner = listRunner -> next;
	}

	std::cout << "\n";


	return 0;
}

	
