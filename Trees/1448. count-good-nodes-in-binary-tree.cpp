// https://leetcode.com/problems/count-good-nodes-in-binary-tree/
/*
Given a binary tree root, a node X in the tree is named good if in the path from root to X
there are no nodes with a value greater than X.
Return the number of good nodes in the binary tree.

*/

class Solution {
public:
	int goodNodes(TreeNode* r, int max_=INT_MIN) {
		if (!r) return 0;
		int currAns = max_ <= r->val;
		max_ = max(max_, r->val);
		return goodNodes(r->left, max_) + goodNodes(r->right, max_) + currAns;
	}
};