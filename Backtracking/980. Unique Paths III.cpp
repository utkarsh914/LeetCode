// https://leetcode.com/problems/unique-paths-iii/

/*
On a 2-dimensional grid, there are 4 types of squares:

1 represents the starting square.  There is exactly one starting square.
2 represents the ending square.  There is exactly one ending square.
0 represents empty squares we can walk over.
-1 represents obstacles that we cannot walk over.
Return the number of 4-directional walks from the starting square to the ending square, that walk over every non-obstacle square exactly once.

 

Example 1:

Input: [[1,0,0,0],[0,0,0,0],[0,0,2,-1]]
Output: 2
Explanation: We have the following two paths: 
1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)
Example 2:

Input: [[1,0,0,0],[0,0,0,0],[0,0,0,2]]
Output: 4
Explanation: We have the following four paths: 
1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2),(2,3)
2. (0,0),(0,1),(1,1),(1,0),(2,0),(2,1),(2,2),(1,2),(0,2),(0,3),(1,3),(2,3)
3. (0,0),(1,0),(2,0),(2,1),(2,2),(1,2),(1,1),(0,1),(0,2),(0,3),(1,3),(2,3)
4. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2),(2,3)
Example 3:

Input: [[0,1],[2,0]]
Output: 0
Explanation: 
There is no path that walks over every empty square exactly once.
Note that the starting and ending square can be anywhere in the grid.
 

Note:

1 <= grid.length * grid[0].length <= 20
*/






/*
--- Backtracking ----

can be optimized if we convert the grid's rows into bitmasks.
mark visitable cells as 1 and others as 0
*/
class Solution {
	int R, C, count;
public:
	int uniquePathsIII(vector<vector<int>>& g) {
		count = 0;
		R = g.size(), C = g[0].size();
		int startX, startY;
		int stepsRemain = 0;
		// find starting coords and number of steps to be taken
		// to reach the destination cell
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				if (g[i][j] == 1) startX = i, startY = j;
				else if (g[i][j] == 0) ++stepsRemain;
			}
		}
		
		g[startX][startY] = 1000; // mark visited
		backtrack(g, startX, startY, stepsRemain);
		return count;
	}

	void backtrack(vector<vector<int>>& g, int i, int j, int stepsRemain) {
		vector<pair<int,int>> cords {{i,j+1}, {i,j-1}, {i-1,j}, {i+1,j}};
		for (auto& [x, y] : cords) {
			if (x<0 or x>=R or y<0 or y>=C) continue;
			if (g[x][y] == 2 and stepsRemain == 0) {
				count++;
				continue;
			}
			if (g[x][y] != 0) continue;
			g[x][y] = 1000; // mark visited
			backtrack(g, x, y, stepsRemain - 1);
			g[x][y] = 0; // unmark visited
		}
	}
};