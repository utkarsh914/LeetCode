// https://leetcode.com/problems/find-duplicate-subtrees/

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
	vector<TreeNode*> ans;
	unordered_map<string, int> mp;

	string preorder(TreeNode* r) {
		if (!r) return "N";
		string serial = "."+to_string(r->val)+"." + "," + preorder(r->left) + "," + preorder(r->right);
		mp[serial]++;
		if (mp[serial] == 2) ans.push_back(r);
		return serial;
	}

public:
	vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
		preorder(root);
		return ans;
	}
};



// ************** efficient ***********
// use codes to encode a serial into a 64 bit integer

class Solution {
public:
	vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
		m.clear();
		res.clear();
		dfs(root);
		return res;
	}

private:
	uint64_t dfs(TreeNode* r) {
		if (nullptr == r) return 0;
		uint64_t id = static_cast<uint64_t>(r->val) << 32 | static_cast<uint64_t>(dfs(r->left)) << 16 | dfs(r->right);
		auto& ct = m[id];
		if (!ct.second) ct.second = m.size();
		if (++ct.first == 2) res.push_back(r);
		return ct.second;
	}

	unordered_map<uint64_t, pair<int, int>> m;
	vector<TreeNode*> res;
};