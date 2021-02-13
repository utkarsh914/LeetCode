// https://leetcode.com/problems/maximum-difference-between-node-and-ancestor/

/*
Given the root of a binary tree, find the maximum value V for which there exist different nodes A and B where V = |A.val - B.val| and A is an ancestor of B.
A node A is an ancestor of B if either: any child of A is equal to B, or any child of A is an ancestor of B.
*/

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



// ******** top-down *******
class Solution {
public:
	int maxAncestorDiff(TreeNode* r, int mn=1e6, int mx=-1) {
		if (!r) return mx - mn;
		mx = max( mx, r->val );
		mn = min( mn, r->val );
		int left = maxAncestorDiff(r->left, mn, mx);
		int right = maxAncestorDiff(r->right, mn, mx);
		return max(left, right);
	}
};



// ******* bottom-up *******
class Solution {
	int diff;
public:
	int maxAncestorDiff(TreeNode* root) {
		diff = INT_MIN;
		getSmallest(root);
		getLargest(root);
		return diff;
	}
	
	int getSmallest(TreeNode* r) {
		if (!r) return INT_MAX;
		int left = getSmallest(r->left);
		int right = getSmallest(r->right);
		// update the difference
		if (left != INT_MAX) diff = max(diff, abs(r->val - left));
		if (right != INT_MAX) diff = max(diff, abs(r->val - right));
		return min({left, right, r->val});
	}
	
	int getLargest(TreeNode* r) {
		if (!r) return INT_MIN;
		int left = getLargest(r->left);
		int right = getLargest(r->right);
		// update the difference
		if (left != INT_MIN) diff = max(diff, abs(r->val - left));
		if (right != INT_MIN) diff = max(diff, abs(r->val - right));
		return max({left, right, r->val});
	}
};





//OR, find min, max simultaneously
class Solution {
	int diff;
public:
	int maxAncestorDiff(TreeNode* root) {
		diff = INT_MIN;
		getMinMax(root);
		return diff;
	}
	
	array<int,2> getMinMax(TreeNode* r) {
		if (!r) return { INT_MAX, INT_MIN };
		auto left = getMinMax(r->left);
		auto right = getMinMax(r->right);
		// update the difference
		if (left[0] != INT_MAX) {
			diff = max(diff, abs(r->val - left[0]));
			diff = max(diff, abs(r->val - left[1]));
		}
		if (right[0] != INT_MAX) {
			diff = max(diff, abs(r->val - right[0]));
			diff = max(diff, abs(r->val - right[1]));
		}
		return {min({left[0], right[0], r->val}), max({left[1], right[1], r->val})};
	}
};