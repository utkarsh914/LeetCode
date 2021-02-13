// https://leetcode.com/problems/sum-root-to-leaf-numbers/

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
	int sumNumbers(TreeNode* root) {
		if (!root) return 0;
		if (!root->left && !root->right) return root->val;
		int left = 0, right = 0;
		if (root->left) {
			root->left->val += root->val*10;
			left = sumNumbers(root->left);
		}
		if (root->right) {
			root->right->val += root->val*10;
			right = sumNumbers(root->right);
		}
		return left+right;
	}
};