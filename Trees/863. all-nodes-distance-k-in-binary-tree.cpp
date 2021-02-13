/*
https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *	 int val;
 *	 TreeNode *left;
 *	 TreeNode *right;
 *	 TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
	vector<int> ans;
	map<TreeNode*, TreeNode*> parent;
	set<TreeNode*> visited;

	void findParents(TreeNode* root) {
		if (!root) return;
		if (root->left) {
			parent[root->left] = root;
			findParents(root->left);
		}
		if (root->right) {
			parent[root->right] = root;
			findParents(root->right);
		}
	}

	void dfs(TreeNode* root, int K) {
		if (visited.count(root)) return;
		visited.insert(root);
		if (K == 0) {
			ans.push_back(root->val);
			return;
		}
		if (root->left) dfs(root->left, K-1);
		if (root->right) dfs(root->right, K-1);
		if (parent[root]) dfs(parent[root], K-1);
	}

	vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
		parent[root] = NULL;
		findParents(root);
		dfs(target, K);
		return ans;
	}
};