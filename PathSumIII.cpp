/*


437. Path Sum III

Given the root of a binary tree and an integer targetSum, return the number of paths where the sum of the values along the path equals targetSum.
The path does not need to start or end at the root or a leaf, but it must go downwards (i.e., traveling only from parent nodes to child nodes).


Constraints:

The number of nodes in the tree is in the range [0, 1000].
-109 <= Node.val <= 109
-1000 <= targetSum <= 1000


Approach:

We use dfs from a given root to travel through every path starting at the root and keep a running sum keeping track the total value of the
path. In the dfs we store pairs of a pointer to the current tree node and a the running sum up to and including the given node. This way
when we push pairs into the stack and later on pop them, the tree node will be paired with the running sum up to that node.

This is important since running dfs without storing the run sum of a particular node, will then make it highly challenging to undo changes
to a general running sum when we checking sums further up the tree once paths ending  at the leaves are done being processed.

We then call the function on the left and right subtrees correspondingly, and return the total count from the left subtree, right subtree and the 
current tree.


*/

#include<iostream>
#include<stack>

//TreeNode of a binary tree
//stores an integer state, and pointer to the left and right children.
class TreeNode{
	public:
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode(): val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode*  left, TreeNode* right): val(x), left(left), right(right) {} 
};


//global variables to avoid multiple copies created when pathSum is called recursively
int runningSum; //stores the sum of the current path of a tree
std::stack<std::pair<TreeNode*, int>> myStack; //a stack to perform dfs. It stores pairs of TreeNode pointers and the running sum up to that node
std::pair<TreeNode*, int> currentPair; //a placeholder pair object to store pairs popped from the stack


//pathSum receives a pointer to the root of the tree and the targetSum as a reference interger
//it performs dfs on the tree with root, root, and keeps stores pairs of tree nodes and a running sum of the current path up to that trre node
// it returns the total number of paths that have a total sum equal to targetSum
int pathSum(TreeNode* root, int& targetSum){
	if(root==nullptr) return 0; //return zero if root is null pointer

	//now we run dfs on the tree with root, root.
	runningSum = 0;
	int count = 0; //stores the number of paths that have a total sum equal to target sum
	myStack.push({root,root->val + runningSum}); 
	while(!myStack.empty()){
		currentPair = myStack.top();
		myStack.pop();
		if(currentPair.second ==  targetSum) ++count; //of the current node has a running sum equal to the target sum we record it in count
		if(currentPair.first->left != nullptr) 
			myStack.push({currentPair.first->left, currentPair.second + currentPair.first->left->val});
		if(currentPair.first->right != nullptr) 
			myStack.push({currentPair.first->right, currentPair.second + currentPair.first->right->val});
	}

	//we recursively call pathSum on the left and right subtrees, and their particular count values are tallied together with the main 
	//tree's count and returned as the solution to all the paths with total sum equal to targetSum
	return count + pathSum(root->left, targetSum) + pathSum(root->right, targetSum);

}


int main(){
	//create tree [10,5,-3,3,2,null,11,3,-10,null,1]
	TreeNode* root = 
		new TreeNode(10,
			new TreeNode(5,
				new TreeNode(3,new TreeNode(3), new TreeNode(-10)), 
				new TreeNode(2,nullptr, new TreeNode(1))
				),
			new TreeNode(-3,
				nullptr,
				new TreeNode(11)
			)
		);
	int targetSum = 8;
	std::cout<<pathSum(root, targetSum)<<"\n";

	return 0;
}
