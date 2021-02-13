// https://leetcode.com/problems/complete-binary-tree-inserter/

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
class CBTInserter {
	vector<TreeNode*> tree;
public:
	CBTInserter(TreeNode* root) {
		if (!root) return;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty()) {
			int s = q.size();
			while (s--) {
				TreeNode* curr = q.front(); q.pop();
				tree.push_back(curr);
				if (curr->left) q.push(curr->left);
				if (curr->right) q.push(curr->right);
			}
		}
	}
	
	int insert(int v) {
		int idx = tree.size();
		TreeNode* currNode = new TreeNode(v);
		TreeNode* parent = tree[(idx-1)/2];
		if (!parent->left)
			parent->left = currNode;
		else
			parent->right = currNode;
		tree.push_back(currNode);
		return parent->val;
	}
	
	TreeNode* get_root() {
		return !tree.empty() ? tree[0] : NULL;
	}
};

/**
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter* obj = new CBTInserter(root);
 * int param_1 = obj->insert(v);
 * TreeNode* param_2 = obj->get_root();
 */