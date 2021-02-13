// https://leetcode.com/problems/validate-binary-search-tree/submissions/

class Solution {
public:
	bool isValidBST(TreeNode* root, TreeNode* minV=NULL, TreeNode* maxV=NULL) {
		if (!root) return true;
		if ((minV && root->val <= minV->val) or (maxV && root->val >= maxV->val)) return false;
		return isValidBST(root->left, minV, root) and isValidBST(root->right, root, maxV);
	}
};