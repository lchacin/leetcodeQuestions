/*

145. Binary Tree Postorder Traversal

Given the root of a binary tree, return the postorder traversal of its nodes' values.

Constraints:

The number of the nodes in the tree is in the range [0, 100].
-100 <= Node.val <= 100

*/

#include<iostream>
#include<vector>


// Definition for a binary tree node.
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };



    //f performs a postorder traversal of a binary tree whose root is a pointer
    //parameter. Postorder traversal is done using recursive dfs and the values
    //are stored in an integer reference parameter vector 
    void f(TreeNode* root, std::vector<int>& treeValues){
        //if we have a left child we traverse the left subtree
        if(root->left)
            f(root->left, treeValues);
        //back from the left subtree we traverse the right subtree
        if(root->right)
            f(root->right, treeValues);

        //back from the left and right subtree we store the current node
        treeValues.push_back(root->val);
    }


    std::vector<int> postorderTraversal(TreeNode* root) {
        //if the tree is empty and the root is null pointer
        if(root == nullptr) return {};

        std::vector<int> treeValues; //to store tree values
        f(root, treeValues);

        return treeValues;
    }


int main(){
	TreeNode* root = new TreeNode(1, nullptr, new TreeNode(2, new TreeNode(3), nullptr));

	auto treeValues = postorderTraversal(root);
	for(auto& val: treeValues)
		std::cout << val << ", ";
	std::cout<<"\n";

	return 0;

}
