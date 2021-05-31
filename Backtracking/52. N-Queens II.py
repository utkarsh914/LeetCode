# https://leetcode.com/problems/n-queens-ii/

'''
In this problem, we can go row by row,
and in each position, we need to check
if the column, the 45° diagonal and the 135° diagonal
had a queen before.
'''

class Solution:
	def totalNQueens(self, n: int) -> int:
		grid = [['.']*n for _ in range(n)]
		self.count = 0
		self.backtrack(grid, n, 0)
		return self.count
					
			
	def backtrack(self, grid, n, row):
		if row == n:
			self.count += 1
			return
		for col in range(n):
			if self.canPlace(grid, n, row, col):
				grid[row][col] = 'Q'
				self.backtrack(grid, n, row+1)
				grid[row][col] = '.'
	
	
	def canPlace(self, grid, n, x, y) -> bool:
		# check in coloumn
		for i in range(x):
			if grid[i][y] == 'Q': return False
		# check top left diag
		i, j = x, y
		while i >= 0 and j >= 0:
			if grid[i][j] == 'Q': return False
			i, j = i-1, j-1
		# check top right diag
		i, j = x, y
		while i >= 0 and j < n:
			if grid[i][j] == 'Q': return False
			i, j = i-1, j+1
		# yes, can be placed now
		return True
			