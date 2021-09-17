'''
https://leetcode.com/problems/minimum-swaps-to-arrange-a-binary-grid/


Given an n x n binary grid, in one step you can choose two adjacent rows of the grid and swap them.

A grid is said to be valid if all the cells above the main diagonal are zeros.

Return the minimum number of steps needed to make the grid valid, or -1 if the grid cannot be valid.

The main diagonal of a grid is the diagonal that starts at cell (1, 1) and ends at cell (n, n).

 

Example 1:


Input: grid = [[0,0,1],[1,1,0],[1,0,0]]
Output: 3
Example 2:


Input: grid = [[0,1,1,0],[0,1,1,0],[0,1,1,0],[0,1,1,0]]
Output: -1
Explanation: All rows are similar, swaps have no effect on the grid.
Example 3:


Input: grid = [[1,0,0],[1,1,0],[1,1,1]]
Output: 0
 

Constraints:

n == grid.length
n == grid[i].length
1 <= n <= 200
grid[i][j] is 0 or 1

'''





'''

Key Idea
This problem can be easily converted to a problem of finding number of swaps required to sort the array of integers when only adjacent swaps are allowed.

We all numbers above the main diagonal to be zero. This means that first row should at least have n-1 zeros at the end, Second row should at least have n-2 zeros at the end, and so on.

So first we find the zeros at the end of each row and make an integer array. Then simply find the number of swaps required to sort it based on the number of zeros in descending order.

Note
A thing to note here is that we don't necessarily want the array to be sorted. As long as index i has more than or equal to n-i-1 zeros, we are good.


-- NOTE --
I am processing the array of count of zeros in reverse
i.e. I expect array to look like [0,1,2,3,4,5] for n = 6
i.e. each element in array should be >= its index
'''
class Solution:
	def minSwaps(self, grid: List[List[int]]) -> int:
		n = len(grid)
		
		arr = []
		# find the number of zeros fromlast in every row
		for i in range(n-1, -1, -1):
			cnt, j = 0, n-1
			while j >= 0 and grid[i][j] == 0:
				cnt += 1
				j -= 1
			arr.append(cnt)
		
		# find the number of adjacent swaps
		# in order to arrange in increasing order
		swaps = 0
		for i in range(n-1, -1, -1):
			if arr[i] >= i: continue
			j = i
			while j >= 0 and arr[j] < i:
				j -= 1
			if j < 0: return -1 # not possible
			while j < i:
				arr[j], arr[j+1] = arr[j+1], arr[j]
				j += 1
				swaps += 1
		
		return swaps
