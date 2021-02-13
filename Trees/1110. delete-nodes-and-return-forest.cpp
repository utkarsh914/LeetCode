// https://leetcode.com/problems/delete-nodes-and-return-forest/

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

	vector<TreeNode*> ans;
	unordered_set<int> to_del;

	void deleteNodes(TreeNode* &root) {
		if (root->left) deleteNodes(root->left);
		if (root->right) deleteNodes(root->right);
		if (to_del.count(root->val)) {
			if (root->left) ans.push_back(root->left);
			if (root->right) ans.push_back(root->right);
			root = NULL;
		}
	}

	vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        if (!root) return ans;
        
		for (auto i: to_delete)
			to_del.insert(i);

		deleteNodes(root);
		if (root) ans.push_back(root);
		
		return ans;
	}
};