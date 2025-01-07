#include<iostream>


class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;

    Node(int v, Node* p, Node* n, Node* c): val(v), next(n), prev(p), child(c) {}

};


//f is a method that flattens a doubly linked list
    //it accepts the head of the list and returns the tail of the list
    //after flattening
    Node* f(Node* currentNode){
        //we run a while loop that iterates until the end of the list
        while(currentNode!=nullptr){
            //check if thecurrent node has a child
            if(currentNode->child != nullptr){
                //we store the next node
                Node* tempNext = currentNode->next;

                //set the currentNode's next to be its child
                currentNode->next = currentNode->child;

                //we set the child's previous node to be the current node
                //this will merge the sublist starting from the child
                //with the current list
                currentNode->next->prev = currentNode;

                //we recursively flatten the doubly linked list starting from
                //the child. sublistEnd will have the pointer to the last node
                //of the flatten sublist
                Node* subListEnd = f(currentNode->child);

                //back from flatten the list starting from the child
                //we set set the currentNode's child to be null pointer
                currentNode->child = nullptr;

                //we connect the end of the flatten sublist starting from the 
                //child with the node previously following the current node
                subListEnd->next = tempNext;

                //if the node previously following the current node is not the
                //end of the list we have its pointer to previous node be the 
                //the end of the flatten sublist
                if(tempNext!=nullptr) tempNext->prev = subListEnd;

                //we continue iterating starting from the new end of the 
                //current list
                currentNode = subListEnd;
            }

            //case the node doesn't have a child
            else{
                //if the current node is the last node in the last we return it
                if(currentNode->next == nullptr) return currentNode;
                //otherwise we move on to the next node
                currentNode = currentNode->next;
            }
        }

        return currentNode;
    }

    
    Node* flatten(Node* head) {
        if(head!=nullptr) f(head);

        return head;
    }


int main(){
	//create a doubly linked list: 1->2 and then 1 has a child with doubly linked list 3->4
	Node* head = new Node(1, nullptr, nullptr, nullptr);
	head->next = new Node(2, nullptr, nullptr, nullptr);
	head->next->prev = head;
	head->child = new Node(3, nullptr, nullptr, nullptr);
	head->child->next = new Node(4, nullptr, nullptr, nullptr);
	head->child->next->prev = head->child;


	Node* listRunner = head;
	flatten(head); //flatten the list
	
	//now we print the flattened doubly linked list

	//print going forward
	while(listRunner!=nullptr){
		std::cout << listRunner->val << " ";
		if(listRunner->next == nullptr) break;
		listRunner = listRunner->next;
	}
	std::cout << "\n";

	//print going backwards
	while(listRunner!=nullptr){
		std::cout << listRunner->val << " ";
		listRunner = listRunner->prev;
	}
	std::cout << "\n";


	return 0;
}
