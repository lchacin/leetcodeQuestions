/*

206. Reverse Linked List

Given the head of a singly linked list, reverse the list, and return the reversed list.


Approach:

We take the recursive approach.
We define a nested lambda function within the reverseList function, the will perform the reversal 
of the linked list recursively.
It carries as arguments a pointer to the previous list node and a pointer to the current list node.

It recursively enters the lambda function with the pointer to the current node as the pointer to the
previous node and the pointer to the next node as the current pointer.
Once the pointer to the next node is nullptr we set the new head to be last node on the list and
the pointer to the next node will be the pointer to the previous node that we carry with every function call.

When returnning from the functional calls the current node's pointer to the next node is set to be the 
previous node 


*/



#include<iostream>
#include<functional>

struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
};



ListNode* reverseList(ListNode*& head) {
        if(head==nullptr) return head;
        ListNode *myNull = nullptr, *newHead = nullptr;

	//a nested lambda function that will recursively perform the reversal of the linked list
	//it receives to ListNode pointer arguments as reference and returns void.
        std::function<void(ListNode*&, ListNode*&)> f = [&newHead, &f](ListNode*& prev, ListNode*& curr)->void {
		//where we haven't reached the last node in the list
            if(curr->next != nullptr){
                f(curr, curr->next); //we recursively enter the lambda with curr as the pointer to the previous
					//node and curr->next the pointer to the current node
                curr->next = prev; //back from the recursive calls we set the pointer to the next node to tbe 
					//previous node
            }
		//we reached the last node
            else{
                newHead = curr; //we let the last node be the new head of the linked list
                newHead->next = prev; //we set its next pointer to be the pointer to the previous node
            }
        };


	//we call  the lambda with myNull as the previous node and head as the current node
	//letting myNull be the previous node will make the first node, which will be the last node in the
	//reversed linked list, be assigned nullptr as its next pointer.
        f(myNull, head);

        return newHead;
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
