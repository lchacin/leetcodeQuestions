/*
94. Binary Tree Inorder Traversal

Given the root of a binary tree, return the inorder traversal of its nodes' values.


Constraints:

The number of nodes in the tree is in the range [0, 100].
-100 <= Node.val <= 100

*/


#include<iostream>
#include<vector>


//binary tree node struct
  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };



//traverse receives a vector of integers reference and the root of a binary tree
    //it traverses a binary tree in in-order form and stores the values in the vector argument
    void traverse(std::vector<int>& values, TreeNode* root){
        //check if the there is a left subtree
        if(root->left)
            traverse(values, root->left); //if we perform in-rder traversal of left subtree
        values.push_back(root->val); //back from traversing the left-subtree we add the current
                                    //value to the vector
        //check if there is a right subtree
        if(root->right != nullptr)
            traverse(values, root->right); //if so we traverse the right subtree
    }

    std::vector<int> inorderTraversal(TreeNode* root) {
        //check if the tree is empty
        if(root == nullptr) return {};

        std::vector<int> values;
        traverse(values, root);

        return values;
        
    }



int main(){
	//create a tree [1,null,2,3]
	TreeNode* root = new TreeNode(1, nullptr, new TreeNode(2, new TreeNode(3), nullptr));
	
	auto values = inorderTraversal(root);
	
	//print values
	for(auto& val: values)
		std::cout << val <<", ";
	std::cout << std::endl;

	return 0;

}
