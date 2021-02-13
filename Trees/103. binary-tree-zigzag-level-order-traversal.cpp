/*
https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/submissions/
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
	vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
		vector<vector<int>> ans;
		if (!root) return ans;
		deque<TreeNode*> q;
		int level = 0;
		q.push_back(root);
		while (!q.empty()) {
			level++;
			int size = q.size();
			vector<int> currLevel;
			while (size--) {
				TreeNode* curr;
				if (level%2 == 1) {
					curr = q.back(); q.pop_back();
					if (curr->left) q.push_front(curr->left);
					if (curr->right) q.push_front(curr->right);
				}else {
					curr = q.front(); q.pop_front();
					if (curr->right) q.push_back(curr->right);
					if (curr->left) q.push_back(curr->left);
				}
				currLevel.push_back(curr->val);
			}
			ans.push_back(currLevel);
		}
		return ans;
	}
};