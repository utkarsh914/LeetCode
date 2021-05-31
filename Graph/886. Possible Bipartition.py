# https://leetcode.com/problems/possible-bipartition/


class Solution:
	def possibleBipartition(self, n: int, dislikes: List[List[int]]) -> bool:
		G = collections.defaultdict(list)
		color = [-1] * (n+1)
		for u, v in dislikes:
			G[u].append(v)
			G[v].append(u)
			
		def isBipartite():
			for i in range(1, n+1):
				if color[i] == -1 and not canPartition(i, 1):
					return False
			return True
		
		def canPartition(u, col):
			color[u] = col
			
			for v in G[u]:
				if color[v] == -1:
					if not canPartition(v, col ^ 1):
						return False
				elif color[v] == col:
					return False
			return True
		
		return isBipartite()