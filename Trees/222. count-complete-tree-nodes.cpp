// https://leetcode.com/problems/count-complete-tree-nodes/

/*
Given the root of a complete binary tree, return the number of the nodes in the tree.

According to Wikipedia, every level, except possibly the last,
is completely filled in a complete binary tree,
and all nodes in the last level are as far left as possible.
It can have between 1 and 2h nodes inclusive at the last level h.

Design an algorithm that runs in less than O(n) time complexity.
*/




// ***** O(logN * logN) *****
class Solution {
public:
	int countNodes(TreeNode* r) {
		if (!r) return 0;
		int leftDepth = 0, righttDepth = 0;
		// move left ptr to leftmost node of bottom-most level
		// move left ptr to rightmost node of bottom-most level
		for (auto i = r; i != NULL; i = i->left, leftDepth++);
		for (auto i = r; i != NULL; i = i->right, rightDepth++);
		if (leftDepth == rightDepth) return pow(2, left) - 1;

		return 1 + countNodes(r->left) + countNodes(r->right);
	}
};
/*
The idea is to find whether a subtree is full binary tree or not.
If it is then we can directly count the nodes, otherwise check recursively.


if (leftDepth == rightDepth) return pow(2, left) - 1;

above line makes sure on each level/depth of the tree,
only one node can possibly trigger the recursion.

Therefore it becomes
h (height of the tree=logN) + (h-1) + (h-2)...+1 = O(h^2) = O(logN*logN)
*/





// ***** O(N) *****
class Solution {
public:
	int countNodes(TreeNode* r) {
		if (!r) return 0;
		return 1 + countNodes(r->left) + countNodes(r->right);
	}
};