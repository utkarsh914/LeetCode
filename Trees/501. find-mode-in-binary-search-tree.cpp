// https://leetcode.com/problems/find-mode-in-binary-search-tree/
// ****** SOLVE IN O(1) space ******

class Solution {
	int maxF = INT_MIN, currF = 0;
	int prev = INT_MIN;
	vector<int> ans;

	void inorder(TreeNode* r, bool pushToAns) {
		if (!r) return;
		inorder(r->left, pushToAns);
		if (prev == r->val) currF++;
		else currF = 1;
		if (!pushToAns) maxF = max(maxF, currF);
		else if (pushToAns && currF==maxF) ans.push_back(r->val);
		prev = r->val;
		inorder(r->right, pushToAns);
	}

public:
	vector<int> findMode(TreeNode* root) {
		ans.clear();
		// get max frequency
		inorder(root, false);
		// push all nodes having freq=maxfreq to ans
		prev = INT_MIN, currF = 0;
		inorder(root, true);
		return ans;
	}
};