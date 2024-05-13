/*

Maximum Level Sum of a Binary Tree

Given the root of a binary tree, the level of its root is 1, the level of its children is 2, and so on.
Return the smallest level x such that the sum of all the values of nodes at level x is maximal.


Constraints:
The number of nodes in the tree is in the range [1, 104].
-105 <= Node.val <= 105


Approach:

We perform bfs to traverse the binary search tree row by row. We make use of a queue data structure to store
the nodes of each row in order. Since we need to compute the sum of the values in each of the nodes, we
need a way to know when the algorithm is done traversing an individual row.

To this end, we initialize the queue with the root followed by a null pointer. When performing bfs every time 
we pop a null pointer from the queue, it will serve as a signal that we are done iterating over a row. For every
node we encounter we keep the sum of the current row and once the null pointer is encounter we update the max row
sum -- and the row number corresponding to the row with maximum sum -- if the current maximum row sum is less than the 
sum of the current row.


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



int maxLevelSum(TreeNode* root){
	std::queue<TreeNode*> bfsQueue; //queue of pointers to TreeNode to perform bfs

	//we initialize the queue by pushing the root and a nullpointer to indicate the end of the tree's first row
	bfsQueue.push(root);
	bfsQueue.push(nullptr);

	TreeNode* currentNode; //TreeNode pointer to store the addresses popped from the queue

	//maxSum will store the maximum sum of the values in a row of the BST. tempSum is used to some the values
	//in each of the rows. CurrentLevel will store the row number currenlty being traversed, and maxLevel
	//will store the row number of the row with the maximum sum of its values
	int maxSum=-1e6, tempSum=0, currentLevel=1, maxLevel=1;

	//we perform bfs until there is only one elemenet left in the queue. This will occur when 
	//only null pointer is left corresponding to the last row of the BST
	while(bfsQueue.size()!=1){
		//we store the front address at the front of the queue and remove it from the queue
		currentNode=bfsQueue.front();
		bfsQueue.pop();

		//we check that it is not null pointer, then end of the row
		if(currentNode != nullptr){
			//we update tempSum and add the children of the current node to the queue
			tempSum += currentNode->val;
			if(currentNode->left) bfsQueue.push(currentNode->left);
			if(currentNode->right) bfsQueue.push(currentNode->right);
		}

		//the case where we reached the end of the row
		else{
			//we check if the sum of the current row traversed is larger than maxSum
			if(maxSum < tempSum){
				//if so we update the maxSum and the maxLevel to the sum of the current row
				//and the current row number
				maxSum=tempSum;
				maxLevel = currentLevel;
			}

			//reset tempSum to 0 so it can store the sum of a new row. Update the current number
			//being traversed as well
			tempSum = 0;
			++currentLevel;

			//we add null pointer to the queue to indicate that the last row just added to the queue
			//via the insertion of children, is now over
			bfsQueue.push(nullptr);
		}

	}

	//out of the while loop we are left to make one last update corresponding to the last row of the BST
	if(maxSum < tempSum){
		maxSum=tempSum;
		maxLevel = currentLevel;
	}


	
	return maxLevel;

}




int main(){
	//create a tree: [-100,-200,-300,-20,-5,-10,null]
	//to test the maxLevelSum function
	TreeNode* root = new TreeNode(-100, new TreeNode(-200), new TreeNode(-300));
	root->left->left = new TreeNode(-20);
	root->left->right = new TreeNode(-5);
	root->right->left = new TreeNode(-10);

	std::cout<<"Maximum Level is: " << maxLevelSum(root)<<"\n";


	return 0;

}

