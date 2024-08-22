/*

Given a binary tree, determine if it is height-balanced.
A height-balanced binary tree is a binary tree in which the depth of the two subtrees of 
every node never differs by more than one.


Example:

Input: root = [1,2,2,3,3,null,null,4,4]
Output: false


Constraints:

The number of nodes in the tree is in the range [0, 5000].
-104 <= Node.val <= 104

*/


#include<iostream>



struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };


//height returns a pair where the first component is the height of the tree and the second
    //is a boolean if the tree is balanced
    std::pair<int,bool> height(TreeNode* root){
        if(root == nullptr) return {0,true}; //if the tree node is nullptr is a tree with height 0 and balanced

        //if the root is not nullptr we enter height with the left and right subtrees
        //leftPair and rightPair will tell us the height of the left and right subtrees and whether
        //if each is balanced
        auto leftPair = height(root->left), rightPair(height(root->right));

        //we return a pair with the height of the current tree and whether the current tree is balanced
        //it will be balanced if the left and right subtrees were balanced and if the height if the left and right
        //subtrees differ by at most 1
        return {1+std::max(leftPair.first, rightPair.first), std::abs(leftPair.first - rightPair.first) < 2 && leftPair.second && rightPair.second};
        
    }

    bool isBalanced(TreeNode* root) {
        //we the height/balance pair information using the height funciton
        auto resultPair{height(root)};
        return resultPair.second; //return the second component telling us if the current tree is balanced
    }


int main(){
	//Input: root = [1,2,2,3,3,null,null,4,4]
	TreeNode* root = new TreeNode(1,new TreeNode(2,new TreeNode(3, new TreeNode(4), new TreeNode(4)), new TreeNode(3)), new TreeNode(2));
	
	std::cout << std::boolalpha << isBalanced(root) << "\n";
	return 0;

}
