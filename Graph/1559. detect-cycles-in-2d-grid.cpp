/*
https://leetcode.com/problems/detect-cycles-in-2d-grid/

Given a 2D array of characters grid of size m x n, you need to find if there exists any cycle consisting of the same value in grid.
A cycle is a path of length 4 or more in the grid that starts and ends at the same cell. From a given cell, you can move to one of the cells adjacent to it - in one of the four directions (up, down, left, or right), if it has the same value of the current cell.
Also, you cannot move to the cell that you visited in your last move. For example, the cycle (1, 1) -> (1, 2) -> (1, 1) is invalid because from (1, 2) we visited (1, 1) which was the last visited cell.
Return true if any cycle of the same value exists in grid, otherwise, return false.

Example 1:
Input: grid = [["a","a","a","a"],["a","b","b","a"],["a","b","b","a"],["a","a","a","a"]]
Output: true
Explanation: There are two valid cycles shown in different colors in the image below:

Example 2:
Input: grid = [["c","c","c","a"],["c","d","c","c"],["c","c","e","c"],["f","c","c","c"]]
Output: true
Explanation: There is only one valid cycle highlighted in the image below:

Example 3:
Input: grid = [["a","b","b"],["b","z","b"],["b","b","a"]]
Output: false
*/


// **** similar to detect cycle in a graph (or number of islands) *****
class Solution {
public:

int R, C;
vector<int> parent;

int find(int x) {
	if (parent[x] != x)
		parent[x] = find(parent[x]);
	return parent[x];
}

void uni(int x, int y) {
	x = find(x);
	y = find(y);
	if (x != y) {
		parent[y] = x;
	}
}

int ind(int i, int j) {
	return i*C + j;
}

bool isValid(int r, int c, char ch, vector<vector<char>>& grid) {
	return (r>=0 && r<R && c>=0 && c<C && grid[r][c]==ch);
}

bool containsCycle(vector<vector<char>>& grid) {
	R = grid.size(), C = grid[0].size();
	parent = vector<int> (R*C);
	for (int i=0; i<parent.size(); i++)
		parent[i]=i;
	for (int i=0; i<R; i++) {
		for (int j=0; j<C; j++) {
			int px = find(ind(i,j));
			if (isValid(i+1,j,grid[i][j],grid)) {
				int py=find(ind(i+1,j));
				if (px == py) return true;
				uni(ind(i,j), ind(i+1,j));
			}
			if (isValid(i,j+1,grid[i][j],grid)) {
				int py=find(ind(i,j+1));
				if (px == py) return true;
				uni(ind(i,j), ind(i,j+1));
			}
		}
	}
	return false;
}};