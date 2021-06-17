# https://leetcode.com/problems/coloring-a-border/

'''
Given a 2-dimensional grid of integers, each value in the grid represents the color of the grid square at that location.

Two squares belong to the same connected component if and only if they have the same color and are next to each other in any of the 4 directions.

The border of a connected component is all the squares in the connected component that are either 4-directionally adjacent to a square not in the component, or on the boundary of the grid (the first or last row or column).

Given a square at location (r0, c0) in the grid and a color, color the border of the connected component of that square with the given color, and return the final grid.

 

Example 1:

Input: grid = [[1,1],[1,2]], r0 = 0, c0 = 0, color = 3
Output: [[3, 3], [3, 2]]
Example 2:

Input: grid = [[1,2,2],[2,3,2]], r0 = 0, c0 = 1, color = 3
Output: [[1, 3, 3], [2, 3, 3]]
Example 3:

Input: grid = [[1,1,1],[1,1,1],[1,1,1]], r0 = 1, c0 = 1, color = 2
Output: [[2, 2, 2], [2, 1, 2], [2, 2, 2]]
 

Note:

1 <= grid.length <= 50
1 <= grid[0].length <= 50
1 <= grid[i][j] <= 1000
0 <= r0 < grid.length
0 <= c0 < grid[0].length
1 <= color <= 1000
'''









'''
Use a DFS to find every square in the component. Then for each square, color it if it has a neighbor that is outside the grid or a different color.


I do dfs first, and mark the whole connected component of grid[r0][c0] as -1

now, traverse matrix again and
 - mark all boundary elements as -2

traverse again,
 elements -1 are non-boundary ele, restore them to original color
 elements -2 are boundary ele, make them equal to 'color'
'''
class Solution:
	def colorBorder(self, grid: List[List[int]], r0: int, c0: int, color: int) -> List[List[int]]:
		R, C, origColor = len(grid), len(grid[0]), grid[r0][c0]
		# do dfs and mark the connected component of cell [r0][c0] as -1
		def dfs(x, y):
			grid[x][y] = -1
			for i, j in [(x+1,y), (x-1,y), (x,y+1), (x,y-1)]:
				if i>=0 and i<R and j>=0 and j<C and grid[i][j]==origColor:
					dfs(i, j)

		# returns True if the curr cell is a boundary cell
		def isBoundary(x, y):
			for i, j in [(x+1,y), (x-1,y), (x,y+1), (x,y-1)]:
				if i<0 or i>=R or j<0 or j>=C or (grid[i][j] != -1 and grid[i][j] != -2):
					return True
			return False



		dfs(r0, c0)

		for i in range(R):
			for j in range(C):
				if grid[i][j] == -1 and isBoundary(i, j):
					grid[i][j] = -2

		# restore colors of all non-boundary elements (i.e. -1)
		# and paint all boundary ele (-2)
		for i in range(R):
			for j in range(C):
				if grid[i][j] == -1:
					grid[i][j] = origColor
				elif grid[i][j] == -2:
					grid[i][j] = color

		return grid