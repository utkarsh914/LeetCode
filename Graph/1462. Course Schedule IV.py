# https://leetcode.com/problems/course-schedule-iv/

'''
There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1.
You are given an array prerequisites where prerequisites[i] = [ai, bi]
indicates that you must take course bi first if you want to take course ai.

For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
You are also given an array queries where queries[j] = [uj, vj]. For the jth query,
you should answer whether the course uj is a prerequisite of the course vj or not.
Note that if course a is a prerequisite of course b and course b is a prerequisite of course c,
then, course a is a prerequisite of course c.

Return a boolean array answer, where answer[j] is the answer of the jth query.

 

Example 1:


Input: numCourses = 2, prerequisites = [[1,0]], queries = [[0,1],[1,0]]
Output: [false,true]
Explanation: course 0 is not a prerequisite of course 1 but the opposite is true.
'''







'''
Imagine if the courses are nodes of a graph. We need to build an array isReachable[i][j].
Start a bfs from each course i and assign for each course j you visit isReachable[i][j] = True.
Answer the queries from the isReachable array.
'''
class Solution:
	def checkIfPrerequisite(self, N: int, P: List[List[int]], Q: List[List[int]]) -> List[bool]:
		isReachable = [[False] * N for _ in range(N)]
		G = collections.defaultdict(list)
		for u, v in P: G[u].append(v)
		
		def dfs(n, u, vis):
			isReachable[n][u] = True
			vis[u] = True
			for v in G[u]:
				if not vis[v]:
					dfs(n, v, vis)
					
		for n in range(N):
			dfs(n, n, [False] * N)
			
		return [isReachable[u][v] for u, v in Q]
		
		
		



'''
use Floyd Warshall to find evry node to every node shortest path
for query [a, b] if path from a->b is infinite, means not a prerequisite
'''
class Solution:
	def checkIfPrerequisite(self, N: int, P: List[List[int]], Q: List[List[int]]) -> List[bool]:
		# initialize dp table
		dp = [[10000] * N for _ in range(N)]
		for u, v in P: dp[u][v] = 1
		for i in range(N): dp[i][i] = 0
			
		# fill dp table
		for k in range(N):
			for i in range(N):
				for j in range(N):
					dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j])
		
		return [True if dp[u][v] < 10000 else False for u, v in Q]
		
