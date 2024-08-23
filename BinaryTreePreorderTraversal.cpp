#include<iostream>
#include<vector>
#include<stack>

 // Definition for a binary tree node.
  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };


//preorderTraversal has a TreeNode pointer argument representing the
    //the root of a binary tree. It traverses the the tree in preorder form
    //using DFS with a stack.
    //it returns a vector with the values in the tree in preorder traversal
    std::vector<int> preorderTraversal(TreeNode* root) {
        if(root == nullptr) return {};

        std::stack<TreeNode*> myStack; //stack to perform dfs
        myStack.push(root);
        TreeNode* currentNode=nullptr;
        std::vector<int> preorderTree; //int vector to store values in tree nodes

        while(!myStack.empty()){ //dfs stops when the stack is empty
            //the top nod eis always the root of particular subtree
            currentNode = myStack.top();
            myStack.pop();

            //we record the value in the vector
            preorderTree.push_back(currentNode->val);

            //we add the right node and then the left.
            //the reason is that we want the left node to be on top of the right
            //node so we record the value of the left node first as per preorder traversal
            if(currentNode->right)
                myStack.push(currentNode->right);
            if(currentNode->left)
                myStack.push(currentNode->left);
        }

        return preorderTree;
    }


int main(){

	TreeNode* root = new TreeNode(1, nullptr, new TreeNode(2, new TreeNode(3), nullptr));
	auto treeValues = preorderTraversal(root);

	for(auto& val: treeValues)
		std::cout << val << ", ";
	std::cout << "\n";

	return 0;

}
