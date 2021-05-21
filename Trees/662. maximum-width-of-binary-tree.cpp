// https://leetcode.com/problems/maximum-width-of-binary-tree/

/*
Given the root of a binary tree, return the maximum width of the given tree.

The maximum width of a tree is the maximum width among all levels.

The width of one level is defined as the length between the end-nodes
(the leftmost and rightmost non-null nodes), where the null nodes
between the end-nodes are also counted into the length calculation.

It is guaranteed that the answer will in the range of 32-bit signed integer.

Example 1:


Input: root = [1,3,2,5,3,null,9]
Output: 4
Explanation: The maximum width existing in the third level with the length 4 (5,3,null,9).

Example 2:


Input: root = [1,3,null,5,3]
Output: 2
Explanation: The maximum width existing in the third level with the length 2 (5,3).

Example 3:


Input: root = [1,3,2,5]
Output: 2
Explanation: The maximum width existing in the second level with the length 2 (3,2).

Example 4:


Input: root = [1,3,2,5,null,null,9,6,null,null,7]
Output: 8
Explanation: The maximum width existing in the fourth level with the length 8 (6,null,null,null,null,null,null,7).
 

Constraints:

The number of nodes in the tree is in the range [1, 3000].
-100 <= Node.val <= 100
*/










/*
The idea is to use heap indexing:

        1
   2         3
 4   5     6   7
8 9 x 11  x 13 x 15
Regardless whether these nodes exist:

Always make the id of left child as parent_id * 2;
Always make the id of right child as parent_id * 2 + 1;
So we can just:

Record the id of left most node when first time at each level
of the tree during an pre-order run.(you can tell
by check the size of the container to hold the first nodes);
At each node, compare the distance from it the
left most node with the current max width;
*/
class Solution {
public:
	int widthOfBinaryTree(TreeNode* root) {
		queue<pair<TreeNode*, unsigned long>> q;
		q.push({ root, 0});
		unsigned long ans = 1;

		while (!q.empty()) {
			unsigned long F = 0, L = 0;

			for (int i = q.size()-1, j = 0; i >= 0; i--, j++) {
				auto cur = q.front(); q.pop();
				if (j == 0) F = cur.second; // first in this level
				if (i == 0) L = cur.second; // last in this level
				if (cur.first->left) q.push({ cur.first->left, 2L*cur.second+1L });
				if (cur.first->right) q.push({ cur.first->right, 2L*cur.second+2L });
			}

			ans = max(ans, L - F + 1);
		}

		return ans;
	}
};