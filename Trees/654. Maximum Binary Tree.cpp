// https://leetcode.com/problems/maximum-binary-tree/



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
	TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
		return build(nums, 0, nums.size()-1);
	}
	
	TreeNode* build(vector<int>& nums, int lo, int hi) {
		if (lo > hi) return nullptr;
		int m = max_element(nums.begin()+lo, nums.begin()+hi+1) - nums.begin();
		TreeNode* root = new TreeNode(nums[m]);
		root->left = build(nums, lo, m-1);
		root->right = build(nums, m+1, hi);
		return root;
	}
};







/*
The key idea is:

We scan numbers from left to right, build the tree one node by one step;
We use a stack to keep some (not all) tree nodes and ensure a decreasing order;
For each number, we keep pop the stack until empty or a bigger number;
The bigger number (if exist, it will be still in stack) is current number's root,
and the last popped number (if exist) is current number's left child
(temporarily, this relationship may change in the future);
Then we push current number into the stack.
*/

TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
	vector<TreeNode*> stk;

	for (int i = 0; i < nums.size(); i++) {
		TreeNode *cur = new TreeNode(nums[i]);
		while (!stk.empty() and stk.back()->val < cur->val) {
			cur->left = stk.back();
			stk.pop_back();
		}
		// nodes in the stack means node i is the right child of (i-1)th node
		if (!stk.empty()) {
			stk.back()->right = cur;
		}
		stk.push_back(cur);
	}
	
	return stk[0];
}