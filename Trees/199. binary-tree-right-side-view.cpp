// https://leetcode.com/problems/binary-tree-right-side-view/

/*
pick Last node in every level, in level order traversal
*/

class Solution {
public:
	vector<int> rightSideView(TreeNode* root) {
		vector<int> ans;
		if (!root) return ans;
		
		queue<TreeNode*> q;
		q.push(root);
		
		while (!q.empty()) {
			int size = q.size();
			while (size--) {
				auto curr = q.front(); q.pop();
				// size=0 means it is last node of this level
				if (size == 0) ans.push_back(curr->val);
				if (curr->left) q.push(curr->left);
				if (curr->right) q.push(curr->right);
			}
		}
		
		return ans;
	}
};