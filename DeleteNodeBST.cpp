/*

450. Delete Node in a BST

Given a root node reference of a BST and a key, delete the node with the given key in the BST. 
Return the root node reference (possibly updated) of the BST.

Basically, the deletion can be divided into two stages:

Search for a node to remove.
If the node is found, delete the node.


Constraints:

The number of nodes in the tree is in the range [0, 104].
-105 <= Node.val <= 105
Each node has a unique value.
root is a valid binary search tree.
-105 <= key <= 105



Approach:


We divide this problem into three cases:
1) the root needs to be removed
2) the node to be removed is larger than its parent
3) the node to be removed is smaller than its parent


To aid us in our goal we create two helper functions:
1) travelToLeftEnd: is a function that receives a root to a BST tree and finds the node furthest to the left
2) findKey: is a function that searches for a node with value equal to key

For cases 2 and 3, whenever a node is removed from a BST tree, we'll connect the parent node to the key's right subtree.
Since all the all the nodes in the key's left subtree are smaller than those of the right subtree we need to connect
the left subtree to the smallest node in the right subtree. 

This is where we use the travelToLeftEnd helper function. We pass to it the root of the right subtree, and the function
returns a reference to the left-most node of the right subtree. We then connect this node to the left subtree.
 

*/


#include<iostream>
#include<queue>

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







//travelToLeftEnd is a helper function that returns the smallest node in a BST
    //it accepts a pointer to the root of the tree and recurisvely moves to the left
    //child until it reaches null pointer
    TreeNode* travelToLeftEnd(TreeNode* root){
            //if we reach a node with no left child, then this is the smallest node in the tree
            //and we return the reference to this node
            if(root->left == nullptr)
                return root;

            //this is the case where the current node has a left child. We move to it
            else
                return travelToLeftEnd(root->left);
    }

    //this helper function will find a particular key in a BST
    //it keeps a reference to the father of the currentNode being traversed
    std::pair<TreeNode*, TreeNode*> findKey(int& key, TreeNode* currentNode, TreeNode* parent){
        //the case where the key was not found
        if(currentNode == nullptr) return {nullptr, nullptr};

        //the case where the key was found
        //we return a references to the node containing the key and its parent
        if(currentNode->val == key)
            return {currentNode, parent};

        //the case where we are still searching for the key
        else{
            //the case where the key is larger than the value of the current node
            if(key > currentNode->val)
                //we move to the right child in search of larger node values
                //currentNode becomes the new parent node and currentNode->right the
                //currentNode
                return findKey(key, currentNode->right, currentNode);

            //the cae where the key is smaller than the current value of the node
            else return findKey(key, currentNode->left, currentNode);
        }
    }



    TreeNode* deleteNode(TreeNode* root, int& key) {
        if(root==nullptr) return root;

        //the case where the root must be removed
        if(root->val == key){
            //the case where there is no left subtree
            if(root->left==nullptr) return root->right;

            //the case where there is no right subtree
            if(root->right == nullptr) return root->left;

            TreeNode* newRoot = root->right;
            TreeNode* smallestRightSubtree = travelToLeftEnd(root->right);
            smallestRightSubtree->left = root->left;

            return newRoot;
        }


        //this is the case where the key is not the root

        //we create a pair to store the references to the node containing the key and its
        //parent node
        std::pair<TreeNode*, TreeNode*> keyLocation;

        //now we locate the key using the findKey helper function
        //the case where the key should be on the left subtree
        if(root->left!=nullptr && key < root->val){
            keyLocation = findKey(key, root->left, root);
        }
        else{ //case where it is in the right subtree
            keyLocation = findKey(key, root->right, root);
        }

        
        //we check if the key was found

        //the case where the key was not found
        if(keyLocation.first == nullptr) return root;


        //the case where the key was found
        //keyNode and keyParent store reference to the node with key value and its parent
        TreeNode* keyNode = keyLocation.first;
        TreeNode* keyParent = keyLocation.second;

        //case where the key is larger than its parent
        if(key > keyParent->val){
            //keyNode has no right subtree
            //we merely connect the key node's left subtree to the parent's pointer to right child
            if(keyNode->right==nullptr){
                keyParent->right = keyNode->left;
                return root;
            }

            //keyNode has no left subtree
            //we merely connect the key node's right subtree to the parent's pointer to right child
            else if(keyNode->left == nullptr){
                keyParent->right = keyNode->right;
                return root;
            }

            //keyNode has both left and right subtrees
            //in this case we connect the parent's right pointer to the key node's right subtree
            //we also use travelToLeftEnd to the get the left most node in the right subtree to connect
            //the key node's left subtree to it.
            TreeNode* smallestRightSubtree = travelToLeftEnd(keyNode->right);
            smallestRightSubtree->left = keyNode->left;
            keyParent->right = keyNode->right;
            return root;
        }

        //case where the key is smaller than its parent
        //the procedure is similar to the previous case
        else{
            //keyNode has no left subtree
            if(keyNode->left == nullptr){
                keyParent->left = keyNode->right;
                return root;
            }

            //keyNode has no right subtree
            if(keyNode->right == nullptr){
                keyParent->left = keyNode->left;
                return root;
            }

            //keyNode has both left and right subtrees
            TreeNode* smallestRightSubtree = travelToLeftEnd(keyNode->right);
            smallestRightSubtree->left = keyNode->left;
            keyParent->left = keyNode->right;
            return root;
        }

    }




void printTree(TreeNode* root){
	std::queue<TreeNode*> bfsQueue;
	bfsQueue.push(root);
	TreeNode* currentNode;
	
	while(!bfsQueue.empty()){
		currentNode = bfsQueue.front();
		bfsQueue.pop();

		if(currentNode==nullptr)
			std::cout<<"null, ";

		else{
			std::cout<<currentNode->val<<", ";
			bfsQueue.push(currentNode->left);
			bfsQueue.push(currentNode->right);
		}
	}
}



int main(){

	//we create the following BST: [5,3,6,2,4,null,7]
	TreeNode* root = new TreeNode(5, new TreeNode(3), new TreeNode(6));
	root->left->left = new TreeNode(2);
	root->left->right = new TreeNode(4);
	root->right->right = new TreeNode(7);

	int key = 3;

	std::cout<<"Original Tree: ";
	printTree(root);

	root = deleteNode(root,key);

	std::cout<<"\nTree without key="<<key<<": ";
	printTree(root);

	std::cout<<"\n";

	return 0;
}
