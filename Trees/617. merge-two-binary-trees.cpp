// https://leetcode.com/problems/merge-two-binary-trees/

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

// ************ merge both trees in the left tree *********
class Solution {
public:
	TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
		if (!t1) return t2;
		if (!t2) return t1;
		// both t1 and t2 are not NULL now
		t1->val += t2->val;
		t1->left = mergeTrees(t1->left, t2->left);
		t1->right = mergeTrees(t1->right, t2->right);
		return t1;
	}
};








class Solution {
public:
	TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
		if (!t1 && !t2) return NULL;
		if (t1 && t2) {
			TreeNode* root = new TreeNode(t1->val + t2->val);
			root->left = mergeTrees(t1->left, t2->left);
			root->right = mergeTrees(t1->right, t2->right);
			return root;
		}
		return t1 ? t1 : t2;
	}
};










// ************ merge both trees in the left tree (unnecessarily more complex way) *********
class Solution {
	void merge(TreeNode* t1, TreeNode* t2, TreeNode* parent, bool isLeft) {
		if (!t1 && !t2) return;
		if (t1 && t2) {
			t1->val += t2->val;
		} else if (!t1 && t2) {
			if (isLeft) parent->left = new TreeNode(t2->val);
			else parent->right = new TreeNode(t2->val);
		}
		parent = isLeft ? parent->left : parent->right;
		merge(t1 ? t1->left : NULL, t2 ? t2->left : NULL, parent, true );
		merge(t1 ? t1->right: NULL, t2 ? t2->right: NULL, parent, false);
	}

public:
	TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
		if (!t1) return t2;
		if (!t2) return t1;
		t1->val += t2 ? t2->val : 0;
		merge(t1->left, t2->left, t1, true);
		merge(t1->right, t2->right, t1, false);
		return t1;
	}
};