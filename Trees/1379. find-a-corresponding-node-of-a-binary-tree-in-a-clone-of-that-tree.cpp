// https://leetcode.com/problems/find-a-corresponding-node-of-a-binary-tree-in-a-clone-of-that-tree/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *	 int val;
 *	 TreeNode *left;
 *	 TreeNode *right;
 *	 TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// ********** doesnt handle duplicate values *********
class Solution {	
public:
	TreeNode* getTargetCopy(TreeNode* original, TreeNode* cloned, TreeNode* target) {
		if (!cloned) return NULL;
		if (cloned->val == target->val)
			return cloned;
		TreeNode* left = getTargetCopy(cloned->left);
		TreeNode* right = getTargetCopy(cloned->right);
		return left ? left : right;
	}
};







// ********** handles duplicate values (using BFS) *********
class Solution {	
public:
	// perform bfs simultaneously in both trees. when got the target in orig tree, return the node of cloned tree
	TreeNode* getTargetCopy(TreeNode* original, TreeNode* cloned, TreeNode* target) {
		if (!original) return NULL;
		queue<pair<TreeNode*, TreeNode*>> q;
		q.push({original, cloned});
		while (!q.empty()) {
			original = q.front().first, cloned = q.front().second; q.pop();
			if (original == target)
				return cloned;
			if (original->left)
				q.push({original->left, cloned->left});
			if (original->right)
				q.push({original->right, cloned->right});
		}
		return NULL;
	}
};



// ********** handles duplicate values (using DFS) *********
class Solution {
public:
	// perform dfs simultaneously in both trees. when got the target in orig tree, return the node of cloned tree
	TreeNode* getTargetCopy(TreeNode* original, TreeNode* cloned, TreeNode* target) {
		if (!original) return NULL;
		if (original == target)	return cloned;
		TreeNode* left = getTargetCopy(original->left, cloned->left, target);
		TreeNode* right = getTargetCopy(original->right, cloned->right, target);
		return left ? left : right;
	}
};