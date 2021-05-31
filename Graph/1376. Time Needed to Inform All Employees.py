# https://leetcode.com/problems/time-needed-to-inform-all-employees/

'''
A company has n employees with a unique ID for each employee from 0 to n - 1.
The head of the company is the one with headID.

Each employee has one direct manager given in the manager array
where manager[i] is the direct manager of the i-th employee, manager[headID] = -1.
Also, it is guaranteed that the subordination relationships have a tree structure.

The head of the company wants to inform all the company employees of an urgent piece of news.
He will inform his direct subordinates, and they will inform their subordinates,
and so on until all employees know about the urgent news.

The i-th employee needs informTime[i] minutes to inform all of his direct subordinates
(i.e., After informTime[i] minutes, all his direct subordinates can start spreading the news).

Return the number of minutes needed to inform all the employees about the urgent news.

 

Example 1:

Input: n = 1, headID = 0, manager = [-1], informTime = [0]
Output: 0
Explanation: The head of the company is the only employee in the company.
Example 2:


Input: n = 6, headID = 2, manager = [2,2,-1,2,2,2], informTime = [0,0,1,0,0,0]
Output: 1
Explanation: The head of the company with id = 2 is the direct manager
of all the employees in the company and needs 1 minute to inform them all.
The tree structure of the employees in the company is shown.

'''








# we just need to find the deepest path from the root
# question says that all the children of a node are at the same distance from it

class Solution:
	def numOfMinutes(self, n: int, headID: int, manager: List[int], informTime: List[int]) -> int:
		# build graph
		graph = [[] for _ in range(n)]
		for i, val in enumerate(manager):
			if i != headID:
				graph[val].append(i)
				
		# do dfs to find the longest path from root
		def dfs(u):
			vis[u] = True
			ans = 0
			# iterate over all children
			for v in graph[u]:
				if not vis[v]:
					ans = max(ans, dfs(v))
			return ans + informTime[u]
		
		vis = [False] * n
		return dfs(headID)





# we don't need vis array, as it is a Tree

class Solution:
	def numOfMinutes(self, n: int, headID: int, manager: List[int], informTime: List[int]) -> int:
		# build graph
		graph = [[] for _ in range(n)]
		for i, val in enumerate(manager):
			if i != headID: graph[val].append(i)
				
		# do dfs to find the longest path from root
		def dfs(u):
			return max([dfs(v) for v in graph[u]] or [0]) + informTime[u]
		
		return dfs(headID)
