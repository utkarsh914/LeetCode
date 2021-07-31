// https://leetcode.com/problems/maximum-sum-bst-in-binary-tree/submissions/

/*
Given a binary tree root, the task is to return the maximum sum of all keys of any sub-tree which is also a Binary Search Tree (BST).

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.
 

Example 1:



Input: root = [1,4,3,2,4,2,5,null,null,null,null,null,null,4,6]
Output: 20
Explanation: Maximum sum in a valid Binary search tree is obtained in root node with key equal to 3.
Example 2:



Input: root = [4,3,null,1,2]
Output: 2
Explanation: Maximum sum in a valid Binary search tree is obtained in a single root node with key equal to 2.
Example 3:

Input: root = [-4,-2,-5]
Output: 0
Explanation: All values are negatives. Return an empty BST.
Example 4:

Input: root = [2,1,3]
Output: 6
Example 5:

Input: root = [5,4,8,3,null,6,3]
Output: 7
 

Constraints:

The given binary tree will have between 1 and 40000 nodes.
Each node's value is between [-4 * 10^4 , 4 * 10^4].
*/






/*
Create a datastructure with 4 parameters: (isBST, sum, minLeft, maxLeft).
In each node compute theses parameters, following the conditions of a Binary Search Tree.
*/
class Solution {
	int ans;
public:
	int maxSumBST(TreeNode* r) {
		this->ans = 0;
		recur(r);
		return ans;
	}
	// array -> < isBst, sum, min, max >
	array<int,4> recur(TreeNode* r) {
		if (!r) return { 1, 0, INT_MAX, INT_MIN };
		if (!r->left and !r->right) {
			ans = max(ans, r->val);
			return { 1, r->val, r->val, r->val };
		}

		auto left = recur(r->left);
		auto right = recur(r->right);
		auto cur = left;

		cur[0] = left[0] and right[0] and left[3] < r->val and right[2] > r->val; //isBST
		cur[1] = left[1] + right[1] + r->val; // sum
		cur[2] = min( min(left[2], right[2]), r->val ); // min Value
		cur[3] = max( max(left[3], right[3]), r->val ); // max Value
	
		if (cur[0]) ans = max(ans, cur[1]);
		return cur;
	}
};




/*
****** without global variable ******

tuple: (isBST, sum, minLeft, maxLeft, ans).
*/
class Solution {
public:
	int maxSumBST(TreeNode* r) {
		return recur(r)[4];
	}
	// array -> < isBst, sum, min, max >
	array<int,5> recur(TreeNode* r) {
		if (!r) return { 1, 0, INT_MAX, INT_MIN, 0 };
		if (!r->left and !r->right) {
			return { 1, r->val, r->val, r->val, max(0, r->val) };
		}

		auto left = recur(r->left);
		auto right = recur(r->right);
		auto cur = left;

		cur[0] = left[0] and right[0] and left[3] < r->val and right[2] > r->val; //isBST
		cur[1] = left[1] + right[1] + r->val; // sum
		cur[2] = min( min(left[2], right[2]), r->val ); // min Value
		cur[3] = max( max(left[3], right[3]), r->val ); // max Value
		// ans is max of ans from left, right, and cur (if current root is a BST)
		cur[4] = max( max(left[4], right[4]), (cur[0] ? cur[1] : 0) ); // ans

		return cur;
	}
};