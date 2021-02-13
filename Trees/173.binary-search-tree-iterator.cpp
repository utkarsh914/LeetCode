/*
https://leetcode.com/problems/binary-search-tree-iterator/submissions/

Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.

Calling next() will return the next smallest number in the BST.

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
class BSTIterator {
private:
	stack<TreeNode*> stk;
	
	TreeNode* findSmallest(TreeNode* root) {
		while (root) stk.push(root), root=root->left;
		return stk.empty() ? NULL : stk.top();
	}
	
public:
	BSTIterator(TreeNode* root) {
		findSmallest(root);
	}
	
	/** @return the next smallest number */
	int next() {
		TreeNode* ans = stk.top();
		stk.pop();
		if (ans->right) findSmallest(ans->right);
		return ans->val;
	}
	
	/** @return whether we have a next smallest number */
	bool hasNext() {
		if (!stk.empty()) return true;
		else return false;
	}
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */