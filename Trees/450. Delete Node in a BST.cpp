// https://leetcode.com/problems/delete-node-in-a-bst/

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
	TreeNode* deleteNode(TreeNode* root, int key) {
		if (!root) return NULL;
		TreeNode* dummy = new TreeNode(0, root, NULL);
		TreeNode *prev = dummy, *cur = root;
		// find key, and its parent node
		while (cur and cur->val != key) {
			prev = cur;
			if (key < cur->val)
				cur = cur->left;
			else cur = cur->right;
		}
		// key not found
		if (!cur) return dummy->left;

		// if leaf node, delete it and return root
		if (!cur->left and !cur->right) {
			if (prev->left == cur) prev->left = NULL;
			else prev->right = NULL;
			delete cur;
			return dummy->left;
		}

		// if only one side has a subtree
		if (cur->left == NULL) {
			if (prev->left == cur) prev->left = cur->right;
			else prev->right = cur->right;
			return dummy->left;
		}
		else if (cur->right == NULL) {
			if (prev->left == cur) prev->left = cur->left;
			else prev->right = cur->left;
			return dummy->left;
		}

		// now, both the sides have a subtree
		// find a leaf node on the right subtree to replace with cur node
		prev = cur;
		TreeNode* next = cur->right;
		while (next and next->left) {
			prev = next;
			next = next->left;
		}

		// replace cur's data with the leaf(next)
		cur->val = next->val;
		// delete next
		// again 3 cases arise
		// either it is leaf, or it has only right subtree
		if (!next->left and !next->right) {
			if (prev->left == next) prev->left = NULL;
			else prev->right = NULL;
			delete next;
		}
		else {
			if (prev->left == next) prev->left = next->right;
			else prev->right = next->right;
			delete next;
		}
		
		return dummy->left;
	}
};










class Solution {
public:
	TreeNode* deleteNode(TreeNode* root, int key) {
		if (!root) return NULL;
		TreeNode* dummy = new TreeNode(0, root, NULL);
		TreeNode *prev = dummy, *cur = root;
		// find key, and its parent node
		while (cur and cur->val != key) {
			prev = cur;
			if (key < cur->val)
				cur = cur->left;
			else cur = cur->right;
		}
		// key not found
		if (!cur) return dummy->left;

		// if leaf node, or only one side has a subtree
		// delete it and return root
		if (!cur->left or !cur->right) {
			deleteNode(prev, cur);
			return dummy->left;
		}

		// now, both the sides have a subtree
		// find a leaf node on the right subtree to replace with cur node
		prev = cur;
		TreeNode* next = cur->right;
		while (next and next->left) {
			prev = next;
			next = next->left;
		}

		// replace cur's data with the leaf(next)
		cur->val = next->val;
		// now delete next
		// again only 2 cases arise
		// either it is leaf, or it has only right subtree
		// deleteNode() fn takes care of these 2 cases too
		deleteNode(prev, next);
		return dummy->left;
	}


	void deleteNode(TreeNode* prev, TreeNode* cur) {
		// don't do anything if both subtree are present
		if (cur->left and cur->right) return;
		// if leaf node, delete it
		if (!cur->left and !cur->right) {
			if (prev->left == cur) prev->left = NULL;
			else prev->right = NULL;
			delete cur;
		}
		// if only one side has a subtree, transplant that subtree
		else {
			TreeNode * subtree = cur->left ? cur->left : cur->right;
			if (prev->left == cur) prev->left = subtree;
			else prev->right = subtree;
			delete cur;
		}
	}
};