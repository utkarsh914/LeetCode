// https://leetcode.com/problems/increasing-order-search-tree/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *	 int val;
 *	 TreeNode *left;
 *	 TreeNode *right;
 *	 TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *	 TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *	 TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
	TreeNode* increasingBST(TreeNode* root) {
		if (!root) return NULL;

		TreeNode* left = increasingBST(root->left);
		root->right = increasingBST(root->right);
		root->left = NULL;

		if (!left) return root;

		TreeNode* it = left;
		while (it and it->right) it = it->right;
		it->right = root;
		return left;
	}
};


/*
# Definition for a binary tree node.
# class TreeNode:
#	 def __init__(self, val=0, left=None, right=None):
#		 self.val = val
#		 self.left = left
#		 self.right = right

class Solution:
	def increasingBST(self, root: TreeNode) -> TreeNode:
		if not root: return None
		left = self.increasingBST(root.left)
		root.right = self.increasingBST(root.right)
		root.left = None
		
		if not left: return root
		
		itr = left
		while itr and itr.right:
			itr = itr.right
		itr.right = root
		return left
*/