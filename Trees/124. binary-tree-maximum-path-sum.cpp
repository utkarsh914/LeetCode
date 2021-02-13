// https://leetcode.com/problems/binary-tree-maximum-path-sum/

// https://leetcode.com/problems/binary-tree-maximum-path-sum/discuss/389609/Full-Explanation-article-with-pseudo-code-Beats-JAVA-100-time-and-100-space-Solution

class Solution {
	int result = INT_MIN;
	int helper(TreeNode* root) {
		if (!root) return 0;
		// recur on left & right
		int left = helper(root->left);
		int right = helper(root->right);
		// compute all 3 possible paths
		int leftPath = root->val + left;
		int rightPath = root->val + right;
		int completePath = root->val + left + right;
		// update result based on 4 possible paths
		int maxPath = max(max(root->val, leftPath), max(rightPath, completePath));
		result = max(result, maxPath);
		// returned path must contain root node and not have the completePath
		// so chose max from rest 3 possibilities from above
		return max(root->val, max(leftPath, rightPath));
	}

public:
	int maxPathSum(TreeNode* root) {
		helper(root);
		return result;
	}
};

// or even cleaner
// if left/right is less than zero, dont consider it (take 0 instead)
class Solution {
	int result = INT_MIN;
	int helper(TreeNode* root) {
		if (!root) return 0;
		int left = max(helper(root->left), 0);
		int right = max(helper(root->right), 0);
		result = max(result, node->val + left + right);
		return root->val + max(left, right);
	}

public:
	int maxPathSum(TreeNode* root) {
		helper(root);
		return result;
	}
};