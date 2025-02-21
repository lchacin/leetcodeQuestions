/*

1261. Find Elements in a Contaminated Binary Tree

Given a binary tree with the following rules:

root.val == 0
For any treeNode:
If treeNode.val has a value x and treeNode.left != null, then treeNode.left.val == 2 * x + 1
If treeNode.val has a value x and treeNode.right != null, then treeNode.right.val == 2 * x + 2
Now the binary tree is contaminated, which means all treeNode.val have been changed to -1.

Implement the FindElements class:

FindElements(TreeNode* root) Initializes the object with a contaminated binary tree and recovers it.
bool find(int target) Returns true if the target value exists in the recovered binary tree.


Constraints:

TreeNode.val == -1
The height of the binary tree is less than or equal to 20
The total number of nodes is between [1, 104]
Total calls of find() is between [1, 104]
0 <= target <= 106


*/

#include<iostream>
#include<unordered_set>

class TreeNode{
	public:
		int val;
		TreeNode* left;
		TreeNode* right;

		TreeNode(int val_): val(val_), left(nullptr), right(nullptr){}
		TreeNode(int val_, TreeNode* left_, TreeNode* right_): val(val_), left(left_), right(right_){}
};

class FindElements {
private:
    //we create a hash table to store the values in the binary tree
    std::unordered_set<int> treeVec;

    //buildTree updates the nodes in the tree to have their
    //corresponding index value and stores them in the hash table 
    void buildTree(TreeNode* root){
        //add the value in the root to the hash table
        treeVec.insert(root->val);

        //if there is a left child
        if(root->left){
            //update the value of the left child and recursively
            //call buildTree on the left subtree
            root->left->val = 2*root->val+1;
            buildTree(root->left);
        }

        //if there is a right child
        if(root->right){
            //update the value of the right child and recursively
            //call buildTree on the right subtree
            root->right->val = 2*root->val+2;
            buildTree(root->right);
        }
    }

public:
    FindElements(TreeNode* root){
        //set the value of the root to be zero
        root->val=0;

        //update the values of each node in the tree using buildTree 
        //helper function
        buildTree(root);
    }
    
    bool find(int target) {
        //check if the target is in the hash table
        return treeVec.contains(target);
    }
};



int  main(){
	//create tree if the form [0,null,2,null,null,5,null,null,null,null,null,11]
	TreeNode* root = new TreeNode(0,nullptr, new TreeNode(2,new TreeNode(5,new TreeNode(11),nullptr),nullptr));

	FindElements elementFinder(root);

	std::cout << std::boolalpha << elementFinder.find(1) << " " <<  elementFinder.find(3) << " " <<  elementFinder.find(5) << "\n";
	
	return 0;

}
