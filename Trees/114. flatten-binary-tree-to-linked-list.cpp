// https://leetcode.com/problems/flatten-binary-tree-to-linked-list/

/*
Given the root of a binary tree, flatten the tree into a "linked list":

The "linked list" should use the same TreeNode class where the right child pointer points to the next node in the list and the left child pointer is always null.
The "linked list" should be in the same order as a pre-order traversal of the binary tree.
*/

class Solution {
public:
	void flatten(TreeNode* r) {
		if (!r) return;
		flatten(r->left);
		flatten(r->right);
		// copy right subtree ptr temporarily
		TreeNode* right = r->right;
		// move left subtree to right
		r->right = r->left;
		r->left = NULL;
		// go to the endmost of moved subtree (right presently)
		// and place the copied right subtree there
		TreeNode* it = r;
		while (it->right)	it = it->right;
		it->right = right;
	}
};



// *** without global variable ***
class Solution {
public:
	void flatten(TreeNode* r) {
		flatten(r, NULL);
	}
	
	TreeNode* flatten(TreeNode* root, TreeNode* prev) {
		if (!root) return prev;
		
		prev = flatten(root->right, prev);
		prev = flatten(root->left, prev);

		root->right = prev;
		root->left = NULL;
		prev = root;
		return prev;
	}
};




class Solution {
	TreeNode* prev = NULL;
public:
	void flatten(TreeNode* r) {
		if (!r) return;

		flatten(r->right);
		flatten(r->left);

		r->right = prev;
		r->left = NULL;
		prev = r;
	}
};