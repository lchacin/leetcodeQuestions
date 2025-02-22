/*

1028. Recover a Tree From Preorder Traversal

We run a preorder depth-first search (DFS) on the root of a binary tree.
At each node in this traversal, we output D dashes (where D is the depth of this node), 
then we output the value of this node.  

If the depth of a node is D, the depth of its immediate child is D + 1.  
The depth of the root node is 0. 
If a node has only one child, that child is guaranteed to be the left child.

Given the output traversal of this traversal, recover the tree and return its root.

Constraints:

The number of nodes in the original tree is in the range [1, 1000].
1 <= Node.val <= 109

*/

#include<iostream>
#include<cctype>


//TreeNode struct for a binary tree
struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };


void f(TreeNode* root, int rootHeight, std::string& treeString, int& counter){
        //if counter is the last index of treeString then there is no other charcters
        //left to explore
        if(treeString.size()-1 == counter) return;

        int nDashes = 0; //to store the number of dashes to read
        int i;          //looping varible

        //loop to count the number of dashes
        for(i=counter+1; i<treeString.size(); ++i){
            if(treeString[i]=='-') ++nDashes;
            else break;
        }

        //if the number of dashes is one more than the current height then it means the following
        //number is this root's left child
        if(nDashes == rootHeight + 1){
            //loop to count the number of digis in the number after the dashes
            int nDigits = 0;
            for(i=counter+nDashes+1; i<treeString.size(); ++i){
                if(std::isdigit(treeString[i])) ++nDigits;
                else break;
            }
            //convert the subtring with the digits into the corresponding number
            int val = std::stoi(treeString.substr(counter+nDashes+1, counter+nDashes+nDigits+1));

            //create and add the left child with its value
            root->left = new TreeNode(val);
            counter += nDashes + nDigits;

            //recursively enter f to create the left subtree
            f(root->left, nDashes, treeString, counter);

            //back from creating the left subtree we
            //now repeat the same process for the following number in the treeString
            //and see if it is a right child and recursively enter f to create right subtree
            nDashes = 0;
            for(i=counter+1; i<treeString.size(); ++i){
                if(treeString[i]=='-') ++nDashes;
                else break;
            }
            if(nDashes == rootHeight + 1){
                
                val = std::stoi(treeString.substr(counter+nDashes+1, counter+nDashes+nDigits+1));
                nDigits = 0;
                for(int i=counter+nDashes+1; i<treeString.size(); ++i){
                    if(std::isdigit(treeString[i])) ++nDigits;
                    else break;
                }
                root->right = new TreeNode(val);
                counter += nDashes + nDigits;
                f(root->right, nDashes, treeString, counter);
            }
        }
    }


    TreeNode* recoverFromPreorder(std::string& traversal) {
        int counter=0;  //to store the last traversal character added to the tree
        int rootHeight=0;   //to store the height of the root
        int nDigits = 0;    //to store the number of digits in the number to store in the tree

        //we iterate over the digits in the number to add to the tree
        //and count them
        for(int j=counter; j<traversal.size(); ++j){
            if(std::isdigit(traversal[j])) ++nDigits;
            else break;
        }
        //add the root to the tree with its corresponding value
        TreeNode* root = new TreeNode(stoi(traversal.substr(0,nDigits)));

        //update counter 
        counter+=nDigits-1;

        //enter f and generate the left and right subtrees
        f(root, rootHeight, traversal, counter);

        return root;
    }


void printTree(TreeNode* root){
	if(root!=nullptr){
		if(root->left){
			printTree(root->left);
		}
		if(root->right){
			printTree(root->right);
		}
		std::cout << root->val << " ";
	}
}

int main(){
	std::string traversal = "1-401--349---90--88";
	auto root = recoverFromPreorder(traversal);

	
	printTree(root);

	return 0;
}
