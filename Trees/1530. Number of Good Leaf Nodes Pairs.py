# 1530. Number of Good Leaf Nodes Pairs

'''
Given the root of a binary tree and an integer distance.
A pair of two different leaf nodes of a binary tree is said to be good
if the length of the shortest path between them is less than or equal to distance.

Return the number of good leaf node pairs in the tree.
'''

# Definition for a binary tree node.
# class TreeNode:
#	 def __init__(self, val=0, left=None, right=None):
#		 self.val = val
#		 self.left = left
#		 self.right = right

class Solution:
	def countPairs(self, root: TreeNode, distance: int) -> int:
		count = 0
		def dfs(node):
			nonlocal count
			if not node:
				return []
			if not node.left and not node.right:
				return [1]
			left = dfs(node.left)
			right = dfs(node.right)
			count += sum(l + r <= distance for l in left for r in right)
			return [n + 1 for n in left + right if n + 1 < distance]
		
		dfs(root)
		return count