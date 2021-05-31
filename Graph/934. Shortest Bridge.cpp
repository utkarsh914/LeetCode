// https://leetcode.com/problems/shortest-bridge/










/*
We first paint one of the islands using DFS with color 2,
so we can easily identify island #1 and island #2.

Then we start expanding island #2 by paining connected empty area.
Each round, we increase the color (3, 4, and so on)
so we can keep track of the newly painted area.
This ends when we "bump" into the first island.
*/
class Solution {
	int R, C;
public:
	int shortestBridge(vector<vector<int>>& A) {
		R = A.size(), C = A[0].size();
		// find first island and paint it to 2
		for (int i = 0, found = 0; i < R and !found; i++)
			for (int j = 0; j < C and !found; j++)
				if (A[i][j] == 1) paint(A, i, j), found = 1;

		// start expanding the island
		// we increase the color on every level of expanding
		for (int color = 2; ; color++) {
			for (int i = 0; i < R; i++) {
				for (int j = 0; j < C; j++) {
					// if we met the other island while expanding from current cell, return ans
					if (A[i][j] == color and (
						   expand(A, i-1, j, color)
						or expand(A, i, j-1, color)
						or expand(A, i, j+1, color)
						or expand(A, i+1, j, color)
						))
						return color - 2;
				}
			}
		}

		return 0;
	}

	// BFS to paint one island to color -> '2'
	void paint(vector<vector<int>>& A, int r, int c) {
		int dr[] = {-1, 0, 0, 1}, dc[] = {0, -1, 1, 0};
		queue<array<int,2>> q;
		A[r][c] = 2;
		q.push({ r, c });

		while (!q.empty()) {
			auto cur = q.front(); q.pop();
			for (int k = 0; k < 4; k++) {
				int x = cur[0] + dr[k], y = cur[1] + dc[k];
				if (x<0 or x>=R or y<0 or y>=C or A[x][y]!=1)
					continue;
				A[x][y] = 2;
				q.push({ x, y });
			}
		}
	}

	bool expand(vector<vector<int>>& A, int i, int j, int color) {
		if (i<0 or i>=R or j<0 or j>=C) return false;
		if (A[i][j] == 0) A[i][j] = color + 1;
		return A[i][j] == 1; // met with second island
	}
};