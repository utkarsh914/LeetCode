# https://leetcode.com/problems/pseudo-palindromic-paths-in-a-binary-tree/

'''
Given a binary tree where node values are digits from 1 to 9.
A path in the binary tree is said to be pseudo-palindromic
if at least one permutation of the node values in the path is a palindrome.

Return the number of pseudo-palindromic paths going from the root node to leaf nodes.

Example 1:



Input: root = [2,3,1,3,1,null,1]
Output: 2 
Explanation: The figure above represents the given binary tree.
There are three paths going from the root node to leaf nodes:
the red path [2,3,3], the green path [2,1,1], and the path [2,3,1].
Among these paths only red path and green path are pseudo-palindromic paths
since the red path [2,3,3] can be rearranged in [3,2,3] (palindrome)
and the green path [2,1,1] can be rearranged in [1,2,1] (palindrome).
Example 2:

'''









# Definition for a binary tree node.
# class TreeNode:
#	 def __init__(self, val=0, left=None, right=None):
#		 self.val = val
#		 self.left = left
#		 self.right = right

'''
for every path, we basically need to see,
if we can make a palindrome from all the nodes in this path.
It is possible if we have freq of all the values in the path to be even,
and at most one freq to be odd.

so we keep track of freq of all the vals in the path
and when we encounter a leaf, we verify the frequencies
'''
class Solution:
	def pseudoPalindromicPaths (self, root: TreeNode) -> int:		
		def dfs(root):
			if not root: return
			count[root.val] += 1;
			if not root.left and not root.right:
				even, odd = 0, 0
				for i in count:
					if i % 2 == 0: even += 1
					else: odd += 1
				if odd <= 1: self.ans += 1
			
			dfs(root.left)
			dfs(root.right)
			count[root.val] -= 1;
		
		count = [0] * 10;
		self.ans = 0
		dfs(root)
		return self.ans




# no global variable
class Solution:
	def pseudoPalindromicPaths (self, root: TreeNode) -> int:		
		def dfs(root):
			if not root: return 0
			ans = 0
			count[root.val] += 1;
			
			if not root.left and not root.right:
				even, odd = 0, 0
				for i in count:
					if i % 2 == 0: even += 1
					else: odd += 1
				if odd <= 1: ans += 1
			
			ans += dfs(root.left) + dfs(root.right)
			count[root.val] -= 1;
			return ans
		
		count = [0] * 10;
		return dfs(root)




'''
Recursively iterate all paths from root to leaves,
count the occurrence of each digits in an integer.

Use this integer as a bit mask.
Also c++, we can use bitmask directly.

Whenever meet an element,
toggle the corresponding bit using ^ operation.

At the leaf node,
check if the count has only one bit that is 1.

We use lowbit to help count this.

Time O(N)
Space O(K + H)
'''

def pseudoPalindromicPaths(self, root, count = 0):
	if not root: return 0
	count ^= 1 << (root.val - 1) # flip the bit
	res = self.pseudoPalindromicPaths(root.left, count) + self.pseudoPalindromicPaths(root.right, count)
	if root.left == root.right: # another way of detecting a left
		if count & (count - 1) == 0:
			res += 1
	return res