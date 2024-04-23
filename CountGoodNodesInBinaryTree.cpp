
/*

1448. Count Good Nodes in Binary Tree


Given a binary tree root, a node X in the tree is named good if in the path from root to X there are no nodes with a value greater than X.
Return the number of good nodes in the binary tree.

Constraints:

The number of nodes in the binary tree is in the range [1, 10^5].
Each node's value is between [-10^4, 10^4].


Approach:

We'll keep a variable called highest storing the highest value encountered in the current path.
We'll also have a variable count keeping a total of all good nodes.
For a new node encountered in the path we increase count if the node's value is >= highest.
Using dfs recursively we dive into the left and right paths and repeat the process for each node encountered until a leaf node is reached.

When we return from dfs we update the highest value to its value prior to running dfs so highest stores the highest value up that returned node.
This will make highest accurate for when dfs is run on the right node. 


*/


#include<iostream>
#include<limits>

//binary tree node class
class TreeNode{
public:
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};



//dfs accepts as argument a node to the root of the tree, a count variable storing the total number of good nodes, and the current highest value
//for the current path
void dfs(TreeNode* root, int& count, int& highest){
        if(root==nullptr) return ; //if we enter a root node we do nothing
	else{
		int temp; //temp is used to keep a copy of the current highest value before chaning its value
		if(root->val >= highest){ //the case where the current node is a  good node
			++count; //increase the count of good nodes
			temp = highest; //store the current highest value
			highest = root->val; //we update highest with the current node's value
			dfs(root->left, count, highest); //run dfs on the left subtree  to obtain the total good nodes from the left subtree
			highest = root->val; //back from dfs we set highest back to its original value
			dfs(root->right, count, highest);	//we run dfs on the right subtree to count all the good nodes in the right subtree
			highest=temp; //set highest back to its value before encountering this node's higher value
		}
		else{ //the case where the node is not a good one
			temp=highest;
			dfs(root->left, count, highest);
			highest = temp;
			dfs(root->right, count, highest);
			highest = temp;
		}

	}

}

int goodNodes(TreeNode* root) {
	//count and highest will be variable storing the total number of good nodes and the highest value encountered in a given path
	int count = 0, highest = std::numeric_limits<int>::min();

	//count and highest will be passed by reference to avoid temporary count and highest variable being created
	//for each recursive function vall to dfs
	dfs(root, count, highest);
	return count;

}

	

int main(){
	TreeNode* root = new TreeNode(2);
	root->right = new TreeNode(4);
	root->right->left = new TreeNode(10);
	root->right->right = new TreeNode(8);
	root->right->right->left = new TreeNode(4);

	std::cout<<goodNodes(root)<<"\n";

	return 0;

}


