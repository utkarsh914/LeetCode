// https://leetcode.com/problems/minimum-number-of-days-to-disconnect-island/

/*
Given a 2D grid consisting of 1s (land) and 0s (water).
An island is a maximal 4-directionally (horizontal or vertical) connected group of 1s.

The grid is said to be connected if we have exactly one island,
otherwise is said disconnected.

In one day, we are allowed to change any single land cell (1) into a water cell (0).

Return the minimum number of days to disconnect the grid.
*/







/*
Return 0 if the grid is already disconnected.
Return 1 if changing a single land to water disconnect the island.
Otherwise return 2.
We can disconnect the grid within at most 2 moves.
*/
class Solution {
	int R, C;
	vector<int> parent;

public:
	int minDays(vector<vector<int>>& G) {

		R = G.size(), C = G[0].size();
		parent.resize(R*C);
		if (numberOfIslands(G) != 1) return 0;

		// try removing 1 land, and check if island is disconnected
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				if (G[i][j] == 0) continue;
				G[i][j] = 0;
				if (numberOfIslands(G) != 1) return 1;
				G[i][j] = 1;
			}
		}

		return 2;
	}

	int numberOfIslands(vector<vector<int>>& G) {
		int dr[] = {-1,1,0,0}, dc[] = {0,0,-1,1};
		// reset parent vector
		for (int i = 0; i < R*C; i++)
			parent[i] = i;

		// make unions
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				if (G[i][j] != 1) continue;
				for (int k = 0; k < 4; k++) {
					int x = i+dr[k], y = j+dc[k];
					if (x<0 or x>=R or y<0 or y>=C or G[x][y]!=1) continue;
					uni(ind(i, j), ind(x, y));
				}
			}
		}

		// count how many diff islands are present
		unordered_set<int> set;
		for (int i = 0; i < R; i++)
			for (int j = 0; j < C; j++)
				if (G[i][j] == 1) set.insert(find(ind(i, j)));

		return set.size();
	}

	int find(int x) {
		if (parent[x] != x)
			parent[x] = find(parent[x]);
		return parent[x];
	}

	void uni(int x, int y) {
		x = find(x), y = find(y);
		if (x != y) parent[y] = x;
	}

	int ind(int i, int j) {
		return i*C + j;
	}
};

/*
Observation
ans <= 2
ans is always less-equal to 2

why?
for any island we can remove the two blocks
around the bottom left corner to make it disconnected.

x x x
x . x
x x x
can be changed to

x x x
x . .
x . x

we need to check for only when ans is 1 or 0

ans = 1
we remove a block and check if it disconnects the islands

ans = 0
we check if there are > 1 islands already
*/