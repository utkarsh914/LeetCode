# https://leetcode.com/problems/shortest-bridge/


class Solution:
	def shortestBridge(self, G: List[List[int]]) -> int:
		# BFS to paint one island to color -> '2'
		def paint(G, r, c):
			q = collections.deque()
			G[r][c] = 2
			q.append((r, c))

			while q:
				cur = q.popleft()
				i, j = cur[0], cur[1]
				for x, y in ((i-1, j), (i+1, j), (i, j-1), (i, j+1)):
					if x<0 or x>=R or y<0 or y>=C or G[x][y]!=1: continue
					q.append((x, y))
					G[x][y] = 2


		# it expands the current color to given cell
		def expand(G, i, j, color):
			if i<0 or i>=R or j<0 or j>=C: return False
			if G[i][j] == 0: G[i][j] = color + 1
			return G[i][j] == 1


		# main function here ----
		R, C, color = len(G), len(G[0]), 2
		# paint first island
		found = False
		for i in range(R):
			if found: break
			for j in range(C):
				if G[i][j] == 1:
					paint(G, i, j)
					found = True
					break

		while True:
			for i in range(R):
				for j in range(C):
					if G[i][j] == color and (expand(G, i-1, j, color) or expand(G, i, j-1, color) or expand(G, i, j+1, color) or expand(G, i+1, j, color)):
						return color - 2
			color += 1

		return 0

