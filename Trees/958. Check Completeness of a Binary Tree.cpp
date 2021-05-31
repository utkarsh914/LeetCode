// https://leetcode.com/problems/check-completeness-of-a-binary-tree/

/*
Given the root of a binary tree, determine if it is a complete binary tree.

In a complete binary tree, every level, except possibly the last,
is completely filled, and all nodes in the last level are as far left as possible.
It can have between 1 and 2h nodes inclusive at the last level h.
*/




/*
Use BFS to do a level order traversal,
add childrens to the bfs queue,
until we met the first empty node.

For a complete binary tree,
there should not be any node after we met an empty one.
*/
class Solution {
public:
	bool isCompleteTree(TreeNode* r) {
		queue<TreeNode*> q;
		q.push(r);
		bool gotANull = false;

		while (!q.empty()) {
			auto cur = q.front(); q.pop();
			if (!cur) gotANull = true;
			else {
				// we have already got a NULL.
				// after getting a NULL, there shouldn't be any non-NULL node
				if (gotANull) return false;
				q.push(cur->left);
				q.push(cur->right);
			}
		}

		return true;
	}
};



/*
# Definition for a binary tree node.
# class TreeNode:
#	 def __init__(self, val=0, left=None, right=None):
#		 self.val = val
#		 self.left = left
#		 self.right = right

class Solution:
	def isCompleteTree(self, root: TreeNode) -> bool:
		q = collections.deque()
		q.append(root)
		gotANone = False
		
		while q:
			cur = q.popleft()
			if cur == None: gotANone = True
			else:
				if gotANone: return False
				q.append(cur.left)
				q.append(cur.right)
		
		return True
*/