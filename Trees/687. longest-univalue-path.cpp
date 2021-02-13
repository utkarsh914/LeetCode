// https://leetcode.com/problems/longest-univalue-path/

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
	int maxL = INT_MIN;
	int helper(TreeNode* root) {
		if (!root or (!root->left and !root->right)) return 0;
		int left = helper(root->left);
		int right = helper(root->right);
		int tempMax = 0, returnAnswer=0;
		if (root->left && root->left->val==root->val)
			tempMax += left + 1, returnAnswer=max(returnAnswer, left+1);
		if (root->right && root->right->val==root->val)
			tempMax += right + 1, returnAnswer=max(returnAnswer, right+1);
		maxL = max(maxL, tempMax);
		return returnAnswer;
	}
public:
	int longestUnivaluePath(TreeNode* root) {
		if (!root) return 0;
		helper(root);
		return maxL;
	}
};