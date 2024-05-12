/*

Longest ZigZag Path in a Binary Tree

You are given the root of a binary tree.

A ZigZag path for a binary tree is defined as follow:

Choose any node in the binary tree and a direction (right or left).
If the current direction is right, move to the right child of the current node; otherwise, move to the left child.
Change the direction from right to left or from left to right.
Repeat the second and third steps until you can't move in the tree.
Zigzag length is defined as the number of nodes visited - 1. (A single node has a length of 0).

Return the longest ZigZag path contained in that tree.


Constraints:

The number of nodes in the tree is in the range [1, 5 * 104].
1 <= Node.val <= 100


Approach:

We perform DFS. We create a function that recursively enters the left and right children of a
node until it reaches nulltr. For a given current node we  have two cases: the current node
is either a continuation of a zigzag path or is the start of a new zigzag path. What determines
whether a current node is part of a zig zag path is whether the parent was part of a zig zag path
and the child node to be entered is right(left) child of parent that was left(right) child of 
his parent.

If we are continuing a zig zag path we enter the function with a TreeNode pointer to the child, 
increase the current length of the zig zag path, and pass parameter indicating the direction
to take to continue the zig zag path.

We only increase the size of the zig zag path if we successfully reached a new node in the path.
If null pointer is reached, we do not increase the size of the path and return the last size of the
path as the size of the zig zag path achieved.

To get obtain the length of the largest zig zag path the function returns the maximum length between the
zig path obtained from the left child and that from the right child.



*/

#include<iostream>
#include<algorithm> //for std::max


//TreeNode is a class the represents a node in a binary tree
//it has attributes a integers value and pointers to the left and right TreeNode children
//default constructor is included that creates a node with no children and zero as the integer attribute
//a constructor with integer parameter and nullptr as children
//a constructor with an integer parameter and TreeNode addresses to the left and right children
class TreeNode{
	public:
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
 		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 		TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

//for readability we include an enum direction stating whether the zig zag path continues
//towards the left or right
enum direction{left,right};


int f(TreeNode* currentNode, direction dir, unsigned short currentLength){
	 //the case we reached null pointer and return that last length of the zig zag path
    if(currentNode==nullptr) return currentLength;

	//the case where currentNode is a pointer to a TreeNode
    else {
        ++currentLength; //since we reached a new node we increase the current length of the zig zag path

        //the case where the zig zag path is conitnued by going to the left
        if(dir == direction::left)
        	//we return the maximu length between the zig zag paths going to the left and to the right
        	//since the zig path is continued to the left, when going towards the left child we pass the
        	//the current length of the zig zag path
        	//when entering moving to the right child we restart the zig zag path length to 0
            return std::max(f(currentNode->left, direction::right, currentLength), f(currentNode->right, direction::left, 0));           

	//the case where the zig zag path is continued going to the right
        else
            return std::max(f(currentNode->right, direction::left, currentLength),f(currentNode->left, direction::right, 0));
    }
}



int longestZigZag(TreeNode* root) {
	//we return the maximu between the longest zig zag path in the left and right subtreess
        return std::max(f(root->left, direction::right,0), f(root->right, direction::left, 0));
}


int main(){
	//creating a binary tree that looks like [1,1,1,null,1,null,null,1,1,null,1]
	TreeNode* root = new TreeNode(1, new TreeNode(1), new TreeNode(1));
	root->left->right = new TreeNode(1, new TreeNode(1), new TreeNode(1));
	root->left->right->left->right = new TreeNode(1);


	std::cout<<"Longest ZigZag path: "<<longestZigZag(root)<<"\n";

	return 0;

}
