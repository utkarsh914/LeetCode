// https://leetcode.com/problems/binary-tree-coloring-game/

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
	TreeNode* X_Node;
	bool btreeGameWinningMove(TreeNode* root, int n, int x);
	TreeNode* findXNode(TreeNode* root, int X);
	int countNodes(TreeNode* root);
};

TreeNode* Solution::findXNode(TreeNode* root, int X) {
	if (!root) return NULL;
	if (root->val == X) return root;
	TreeNode* left = findXNode(root->left, X);
	if (left) return left;
	TreeNode* right = findXNode(root->right, X);
	if (right) return right;
	return NULL;
}

int Solution::countNodes(TreeNode* root) {
	if (!root or root==X_Node) return 0;
	int lc = countNodes(root->left);
	int rc = countNodes(root->right);
	return 1 + lc + rc;
}

bool Solution::btreeGameWinningMove(TreeNode* root, int n, int X) {
	if (!root) return false;
	X_Node = findXNode(root, X);
	int left = countNodes(X_Node->left);
	int right = countNodes(X_Node->right);
	int parent = n - (left+right+1);
	int blue = max( parent, max(left, right));
	return blue > (n-blue);
}


// ============= SHORTER ==========

class Solution {
public:
	int left, right, val;
	bool btreeGameWinningMove(TreeNode* root, int n, int x) {
		val = x, n = count(root);
		return max(max(left, right), n - left - right - 1) > n / 2;
	}

	int count(TreeNode* node) {
		if (!node) return 0;
		int l = count(node->left), r = count(node->right);
		if (node->val == val)
			left = l, right = r;
		return l + r + 1;
	}
};