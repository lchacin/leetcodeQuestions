/*

111. Minimum Depth of Binary Tree

Given a binary tree, find its minimum depth.
The minimum depth is the number of nodes along the shortest path from the root 
node down to the nearest leaf node.
Note: A leaf is a node with no children.


Constraints:

The number of nodes in the tree is in the range [0, 105].
-1000 <= Node.val <= 1000


*/


#include<iostream>



// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
 


//findMinDepth has parameters that store the root of a binary tree
    //and two short reference variables that store the current and minimum depths so far
    //achieved
    void findMinDepth(const TreeNode* root, short& currentDepth, short& minDepth){
        //case root is a leaf
        if(root->left == nullptr && root->right == nullptr)
            minDepth = std::min(currentDepth, minDepth);

        //case root is not a leaf
        else{
            //case root has a left child
            if(root->left) {
                ++currentDepth;//increase currentDepth since we'll move to the left child
                findMinDepth(root->left, currentDepth, minDepth);
                --currentDepth;//back from the left subtree we decrease currnetDepth back to the initial depth
            }
            //case root has a right child
            if(root->right) {
                ++currentDepth;
                findMinDepth(root->right, currentDepth, minDepth);
                --currentDepth;
            }
        }
    }
    
    int minDepth(const TreeNode* root) {
        //the case the tree is empty
        if(root == nullptr) return 0;

        short minDepth=10000, currentDepth=1; //to store the minimum and running depths
        findMinDepth(root, currentDepth, minDepth);

        return minDepth;
    }



int main(){
	//binary tree [3,9,20,null,null,15,7]
	TreeNode* root = new TreeNode(3, new TreeNode(9), new TreeNode(20, new TreeNode(15), new TreeNode(7)));

	std::cout << "minimum depth: " << minDepth(root) << "\n";

	return 0;

}
