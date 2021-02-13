// https://leetcode.com/problems/path-sum-iii/
// https://leetcode.com/problems/path-sum-iii/discuss/141424/Python-step-by-step-walk-through.-Easy-to-understand.-Two-solutions-comparison.-%3A-)

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


/*
1. Brute Force: O(nlogn) ~ O(n^2)
1.1 High level walk-through:
(Define return) Define a global var: self.numOfPaths in the main function.
(1st layer DFS) Use recursive traverse to go through each node (can be any order: pre, in, post all fine).
(2nd layer DFS) For each node, walk all paths. If a path sum equals to the target: self.numOfPaths += 1
Return result: return self.numOfPaths
*/
class Solution {

	int count=0;

	void dfs(TreeNode* root, int target) {
		if (!root) return;
		findAllPaths(root, target);
		dfs(root->left, target);
		dfs(root->right, target);
	}

	void findAllPaths(TreeNode* root, int target) {
		if (!root) return;
		if (root->val == target) count++;
		findAllPaths(root->left, target-root->val);
		findAllPaths(root->right, target-root->val);
	}

public:
	int pathSum(TreeNode* root, int targetSum) {
		if (!root) return 0;
		dfs(root, targetSum);
		return count;
	}
};



/*
2. Memorization of path sum: O(n)
2.1 High level walk through
In order to optimize from the brutal force solution, we will have to think of a clear way to memorize the intermediate result. Namely in the brutal force solution, we did a lot repeated calculation. For example 1->3->5, we calculated: 1, 1+3, 1+3+5, 3, 3+5, 5.
This is a classical 'space and time tradeoff': we can create a dictionary (named cache) which saves all the path sum (from root to current node) and their frequency.
Again, we traverse through the tree, at each node, we can get the currPathSum (from root to current node). If within this path, there is a valid solution, then there must be a oldPathSum such that currPathSum - oldPathSum = target.
We just need to add the frequency of the oldPathSum to the result.
During the DFS break down, we need to -1 in cache[currPathSum], because this path is not available in later traverse.


*/
class Solution {
	int count=0;
	unordered_map<int,int> freq;

	void dfs(TreeNode* root, int target, int curPathSum) {
		if (!root) return;
		curPathSum += root->val;
		int oldPathSum = curPathSum-target;
		count += freq[oldPathSum];
		freq[curPathSum]++;

		dfs(root->left, target, curPathSum);
		dfs(root->right, target, curPathSum);
		freq[curPathSum]--;
	}

public:
	int pathSum(TreeNode* root, int target) {
		freq[0] = 1;
		dfs(root, target, 0);
		return count;
	}
};