// https://leetcode.com/problems/all-possible-full-binary-trees/

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
	unordered_map<int, vector<TreeNode*>> dp;
public:
	vector<TreeNode*> allPossibleFBT(int N) {
		
		if (N % 2 == 0) return vector<TreeNode*> ();
		if (N==1) return { new TreeNode(0) };
		if (dp.count(N)) return dp[N];

		vector<TreeNode*> ans;

		for (int i=1, j=N-2; i<=N-2 && j>=1; i+=2, j-=2) {
			auto leftAns = allPossibleFBT(i);
			auto rightAns = allPossibleFBT(j);
			for (auto& left : leftAns) {
				for (auto& right : rightAns) {
					ans.push_back(new TreeNode(0, left, right));
				}
			}
		}

		return dp[N] = ans;
	}
};








// to avoid creating frankenstien trees

class Solution {

	TreeNode* clone(TreeNode* root) {
		TreeNode* new_root = new TreeNode(0);
		new_root->left = (root->left) ? clone(root->left) : nullptr;
		new_root->right = (root->right) ? clone(root->right) : nullptr; 
		return new_root;
	}

	vector<TreeNode*> allPossibleFBT(int N) {
		std::vector<TreeNode*> ret;
		if (1 == N) {
			ret.emplace_back(new TreeNode(0));
		} else if (N % 2) {
			for (int i = 2; i <= N; i += 2) {
			auto left = allPossibleFBT(i - 1);
			auto right = allPossibleFBT(N - i);
			for (int l_idx = 0; l_idx < left.size(); ++l_idx) {
				for (int r_idx = 0; r_idx < right.size(); ++r_idx) {
				ret.emplace_back(new TreeNode(0));
				// If we're using the last right branch, then this will be the last time this left branch is used and can hence
				// be shallow copied, otherwise the tree will have to be cloned
				ret.back()->left = (r_idx == right.size() - 1) ? left[l_idx] : clone(left[l_idx]);
				// If we're using the last left branch, then this will be the last time this right branch is used and can hence
				// be shallow copied, otherwise the tree will have to be cloned
				ret.back()->right = (l_idx == left.size() - 1) ? right[r_idx] : clone(right[r_idx]);
				}
			}
			}
		}
		return ret;
	}
};