// https://leetcode.com/problems/01-matrix/

/*
Given an m x n binary matrix mat, return the distance of the nearest 0 for each cell.

The distance between two adjacent cells is 1.

 

Example 1:


Input: mat = [[0,0,0],[0,1,0],[0,0,0]]
Output: [[0,0,0],[0,1,0],[0,0,0]]
Example 2:


Input: mat = [[0,0,0],[0,1,0],[1,1,1]]
Output: [[0,0,0],[0,1,0],[1,2,1]]
 

Constraints:

m == mat.length
n == mat[i].length
1 <= m, n <= 104
1 <= m * n <= 104
mat[i][j] is either 0 or 1.
There is at least one 0 in mat.
*/




/*
do bfs from every zero at once
*/
class Solution {
public:
	vector<vector<int>> updateMatrix(vector<vector<int>>& m) {
		int R = m.size(), C = m[0].size();
		vector<vector<int>> ans(R, vector<int> (C));
		queue<pair<int,int>> q;

		for (int i = 0; i < R; i++)
			for (int j = 0; j < C; j++)
				if (m[i][j] == 0) q.push({ i , j});

		int steps = 0;

		while (!q.empty()) {
			int size = q.size();
			while (size--) {
				auto [x,y] = q.front(); q.pop();
				ans[x][y] = steps;
				vector<pair<int,int>> cords {
					{x+1, y}, {x-1,y}, {x,y+1}, {x,y-1}
				};
				for (auto& [i,j] : cords) {
					if (i<0 or i>=R or j<0 or j>=C or m[i][j]!=1) continue;
					q.push({ i, j });
					m[i][j] = -1; // mark visited
				}
			}
			steps++;
		}

		return ans;
	}
};