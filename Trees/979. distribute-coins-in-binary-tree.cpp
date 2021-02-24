// https://leetcode.com/problems/distribute-coins-in-binary-tree/

/*
You are given the root of a binary tree with n nodes
where each node in the tree has node.val coins and there are n coins total.

In one move, we may choose two adjacent nodes and move one coin from one node to another.
(A move may be from parent to child, or from child to parent.)

Return the number of moves required to make every node have exactly one coin.
*/

/*
We traverse childs first (post-order traversal), and return the ballance of coins.
For example, if we get '+3' from the left child, that means that the left subtree has 3 extra coins to move out.
If we get '-1' from the right child, we need to move 1 coin in.
So, we increase the number of moves by 4 (3 moves out left + 1 moves in right).
We then return the final ballance:
r->val (coins in the root) + 3 (left) + (-1) (right) - 1 (keep one coin for the root).

image: https://assets.leetcode.com/users/votrubac/image_1548011422.png
*/

class Solution {
public:
	int distributeCoins(TreeNode* r) {
		int moves = 0;
		balance(r, moves);
		return moves;
	}

	int balance(TreeNode* r, int& moves) {
		if (!r) return 0;
		int left = balance(r->left, moves);
		int right = balance(r->right, moves);
		moves += abs(left) + abs(right);
		return r->val + left + right - 1;
	}

};