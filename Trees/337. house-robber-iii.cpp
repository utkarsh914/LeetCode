/*
https://leetcode.com/problems/house-robber-iii/

The thief has found himself a new place for his thievery again.
There is only one entrance to this area, called the "root." Besides the root,
each house has one and only one parent house. After a tour,
the smart thief realized that "all houses in this place forms a binary tree".
It will automatically contact the police if two directly-linked houses were broken into on the same night.
Determine the maximum amount of money the thief can rob tonight without alerting the police.

Example 1:

Input: [3,2,3,null,3,null,1]

     3
    / \
   2   3
    \   \ 
     3   1

Output: 7 
Explanation: Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.
*/

class Solution {
public:
	int rob(TreeNode* root, bool canCollectRoot=true) {
		pair<int,int> ans = dfs(root);
		// return max of including the root, and excluding it
		return max(ans.first, ans.second);
	}
	
	pair<int,int> dfs(TreeNode* root) {
		pair<int,int> result = {0,0};
		if (!root) return result;
		pair<int,int> left = dfs(root->left);
		pair<int,int> right = dfs(root->right);
		// including the current root node
		result.first = root->val + left.second + right.second;
		// excluding the current root node
		result.second = max(left.first, left.second) + max(right.first, right.second);
		return result;
	}
};

// ********* recursive (gives TLE) ******
int rob(TreeNode* root, bool canCollectRoot=true) {
	if (!root) return 0;
	int v1 = 0;
	if (canCollectRoot)
		v1 = root->val + rob(root->left,0) + rob(root->right,0);
	int v2 = rob(root->left,1) + rob(root->right,1);
	return max(v1, v2);
}

// ********** ALTERNATIVE DFS **********
//max_include_root = root->val + max_donot_include_root_left + max_donnot_include_root_right
//max_donot_include_root = max(max_include_root_left, max_donnot_include_root_left) + max(max_include_root_right, max_donnot_include_root_right)

class Solution {
public:
	int rob(TreeNode* root) {
		int max_include_root = 0;
		int max_donnot_include_root = 0;
		return dfs(root, max_include_root, max_donnot_include_root);
	}
	
	int dfs(TreeNode* root, int& max_include_root, int& max_donnot_include_root) {
		if (root == NULL) {
			max_include_root = 0;
			max_donnot_include_root = 0;
			return 0;
		}
		int max_donnot_include_root_left = 0;
		int max_donnot_include_root_right = 0;

		int max_include_root_left = 0;
		int max_include_root_right = 0;

		int max_left = dfs(root->left, max_include_root_left, max_donnot_include_root_left);
		int max_right = dfs(root->right, max_include_root_right, max_donnot_include_root_right);

		max_include_root = root->val + max_donnot_include_root_left + max_donnot_include_root_right;
		max_donnot_include_root = max_left + max_right;

		return max(max_include_root, max_donnot_include_root);
	}
};