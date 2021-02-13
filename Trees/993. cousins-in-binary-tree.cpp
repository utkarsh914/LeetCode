/*
https://leetcode.com/problems/cousins-in-binary-tree/
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
class Solution {
public:
	bool isCousins(TreeNode* root, int x, int y);
};

bool Solution::isCousins(TreeNode* root, int x, int y) {
	queue<TreeNode*> q;
	int dx, dy;
	TreeNode* px = NULL;
	TreeNode* py = NULL;
	q.push(root);
	int level = 0;
	while (!q.empty()) {
		level++;
		int size = q.size();
		while (size--) {
			TreeNode* curr = q.front(); q.pop();
			// push children
			if (curr->left) {
				q.push(curr->left);
				if (curr->left->val == x) {
					dx = level;
					px = curr;
				}
				else if (curr->left->val == y) {
					dy = level;
					py = curr;
				}
			}
			if (curr->right) {
				q.push(curr->right);
				if (curr->right->val == x) {
					dx = level;
					px = curr;
				}
				else if (curr->right->val == y) {
					dy = level;
					py = curr;
				}
			}
		}
	}
	if (!px or !py) return false;
	return (dx==dy and px!=py);
}