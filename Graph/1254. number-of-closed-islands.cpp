// https://leetcode.com/problems/number-of-closed-islands/

/*
all islands except those containing border elements of grid are closed.
so, first invalidate all groups having any border element in them.
then count the number of groups

****** alternative way to understand ******
flood fill the islands first, then count the number of remaining islands
*/

class Solution {
	int R, C;
public:
	int closedIsland(vector<vector<int>>& g) {

		this->R = g.size(), this->C = g[0].size();
		int count = 0;

		// top and bottom row
		for (int j=0; j<C; j++) {
			if (g[0][j] == 0) dfs(g, 0, j);
			if (g[R-1][j] == 0) dfs(g, R-1, j);
		}
		// left && right col
		for (int i=0; i<R; i++) {
			if (g[i][0] == 0) dfs(g, i, 0);
			if (g[i][C-1] == 0) dfs(g, i, C-1);
		}

		for (int i=1; i<R-1; i++) {
			for (int j=1; j<C-1; j++) {
				if (g[i][j] == 0) {
					dfs(g, i, j);
					count++;
				}
			}
		}

		return count;
	}

	void dfs(vector<vector<int>>& g, int r, int c) {
		g[r][c] = -1;
		int dr[] = {-1, 1, 0, 0}, dc[] = {0, 0, -1, 1};
		for (int i=0; i<4; i++) {
			int x = r+dr[i], y = c+dc[i];
			if (x<0 or x>=R or y<0 or y>=C or g[x][y]!=0) continue;
			dfs(g, x, y);
		}
	}
};